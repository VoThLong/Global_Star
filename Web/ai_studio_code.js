const express = require('express');
const cors = require('cors');
const { Pool } = require('pg');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3000;

const pool = new Pool({
    user: process.env.DB_USER || 'postgres',
    host: process.env.DB_HOST || 'db',
    database: process.env.DB_NAME || 'serial_monitor',
    password: process.env.DB_PASSWORD || 'password',
    port: process.env.DB_PORT || 5432,
});

app.use(cors());
app.use(express.json());
app.use(express.text()); // Thêm hỗ trợ nhận text/plain

let commandQueue = [];
let lastEsp32Seen = Date.now();

// Tự động đẩy lệnh kiểm tra sức khỏe mỗi 5 phút
setInterval(() => {
    const healthCmd = "AT+DEVINITSTATUS?";
    commandQueue.push(healthCmd);
    console.log(`[AUTO] Health check queued: ${healthCmd}`);
}, 300000);

const initDb = async (retries = 5) => {
    while (retries) {
        try {
            await pool.query(`
                CREATE TABLE IF NOT EXISTS logs (
                    id SERIAL PRIMARY KEY,
                    type TEXT,
                    content TEXT,
                    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            `);
            console.log("✅ Database initialized");
            return;
        } catch (err) {
            console.error(`❌ Error initializing database (${retries} retries left):`, err.message);
            retries -= 1;
            await new Promise(res => setTimeout(res, 5000));
        }
    }
};
initDb();

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'ai_studio_code.html'));
});

app.get('/history-view', (req, res) => {
    res.sendFile(path.join(__dirname, 'history.html'));
});

app.get('/history', async (req, res) => {
    try {
        const result = await pool.query('SELECT * FROM logs ORDER BY id DESC');
        res.json(result.rows);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/command', async (req, res) => {
    const { command } = req.body;
    if (!command) return res.status(400).json({ error: "Missing command" });
    commandQueue.push(command);
    try {
        await pool.query('INSERT INTO logs (type, content) VALUES ($1, $2)', ['cmd', command]);
        res.json({ status: "ok" });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/logs', async (req, res) => {
    try {
        const result = await pool.query(`
            SELECT id, type, content, timestamp 
            FROM (SELECT * FROM logs ORDER BY id DESC LIMIT 100) AS sub 
            ORDER BY id ASC
        `);
        res.json(result.rows);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/status', (req, res) => {
    const now = Date.now();
    const isEsp32Online = (now - lastEsp32Seen) < 15000; 
    res.json({ 
        server: "online", 
        esp32: isEsp32Online ? "online" : "offline",
        lastSeenSecondsAgo: Math.floor((now - lastEsp32Seen) / 1000)
    });
});

app.post('/heartbeat', (req, res) => {
    lastEsp32Seen = Date.now();
    res.status(200).send("ok");
});

app.get('/command', (req, res) => {
    lastEsp32Seen = Date.now();
    if (commandQueue.length > 0) {
        const cmd = commandQueue.shift(); 
        res.send(cmd);
        console.log(`📤 Sent command to ESP32: ${cmd}`);
    } else {
        res.send(""); 
    }
});

// Endpoint upload nhận text/plain để tránh lỗi JSON parse
app.post('/upload', async (req, res) => {
    let data = req.body; // Với express.text(), body sẽ là chuỗi text trực tiếp
    
    if (!data || typeof data !== 'string') {
        // Fallback nếu ESP32 vẫn gửi JSON (cho tương thích ngược)
        if (req.body && req.body.data) data = req.body.data;
        else return res.status(400).send("Missing data");
    }

    const isRes = data.startsWith("OK") || data.startsWith("ERROR") || data.includes("OK\r") || data.includes("\nOK");
    const type = isRes ? "res" : "data";

    try {
        await pool.query('INSERT INTO logs (type, content) VALUES ($1, $2)', [type, data]);
        res.status(200).send("ok");
    } catch (err) {
        console.error("❌ DB Insert Error:", err.message);
        res.status(500).send(err.message);
    }
});

app.listen(PORT, () => {
    console.log(`🚀 Modern Remote Serial Monitor Server running at port ${PORT}`);
});
