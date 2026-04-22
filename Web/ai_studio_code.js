const express = require('express');
const cors = require('cors');
const { Pool } = require('pg');

const app = express();
const PORT = process.env.PORT || 3000;

// PostgreSQL Connection Pool
const pool = new Pool({
    user: process.env.DB_USER || 'postgres',
    host: process.env.DB_HOST || 'ttlab-db',
    database: process.env.DB_NAME || 'serial_monitor',
    password: process.env.DB_PASSWORD || 'password',
    port: process.env.DB_PORT || 5432,
});

// Enable CORS and JSON parsing
app.use(cors());
app.use(express.json());

// In-memory variable to hold the latest command for the ESP32
let pendingCommand = "";

// Initialize Database
const initDb = async () => {
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
    } catch (err) {
        console.error("❌ Error initializing database:", err.message);
    }
};
initDb();

// ==========================================
// WEB ENDPOINTS
// ==========================================

// 1. Web sends a command
app.post('/command', async (req, res) => {
    const { command } = req.body;
    
    if (!command) {
        return res.status(400).json({ error: "Missing command" });
    }

    pendingCommand = command;

    try {
        await pool.query(
            'INSERT INTO logs (type, content) VALUES ($1, $2)',
            ['cmd', command]
        );
        res.json({ status: "ok" });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// 2. Web fetches all logs
app.get('/logs', async (req, res) => {
    try {
        const result = await pool.query('SELECT type, content, timestamp FROM logs ORDER BY timestamp ASC');
        res.json(result.rows);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// ==========================================
// ESP32 ENDPOINTS
// ==========================================

// 3. ESP32 polls for the latest command
app.get('/command', (req, res) => {
    res.send(pendingCommand);
    pendingCommand = "";
});

// 4. ESP32 uploads serial data/responses
app.post('/upload', async (req, res) => {
    const { data } = req.body;
    
    if (!data) {
        return res.status(400).json({ error: "Missing data" });
    }

    const isRes = data.startsWith("OK") || data.startsWith("ERROR");
    const type = isRes ? "res" : "data";

    try {
        await pool.query(
            'INSERT INTO logs (type, content) VALUES ($1, $2)',
            [type, data]
        );
        res.json({ status: "ok" });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// Start Server
app.listen(PORT, () => {
    console.log(`🚀 Modern Remote Serial Monitor Server running at port ${PORT}`);
});
