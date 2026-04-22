const express = require('express');
const cors = require('cors');
const { DatabaseSync } = require('node:sqlite');
const fs = require('node:fs');
const path = require('node:path');

const app = express();
const PORT = process.env.PORT || 3000;

// Đảm bảo thư mục data tồn tại
const dbDir = path.join(__dirname, 'data');
if (!fs.existsSync(dbDir)) {
    fs.mkdirSync(dbDir, { recursive: true });
}

// Khởi tạo SQLite Native (Node 22.5+)
const db = new DatabaseSync(path.join(dbDir, 'logs.db'));

// Setup Database Schema
db.exec(`
    CREATE TABLE IF NOT EXISTS logs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        type TEXT,
        content TEXT,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
    )
`);

// Chuẩn bị sẵn các câu lệnh SQL (Prepared Statements) để tối ưu hiệu năng
const insertLog = db.prepare('INSERT INTO logs (type, content) VALUES (?, ?)');
const getLatestLogs = db.prepare(`
    SELECT id, type, content, timestamp 
    FROM (
        SELECT * FROM logs ORDER BY id DESC LIMIT 100
    ) 
    ORDER BY id ASC
`);

// Enable CORS and JSON parsing
app.use(cors());
app.use(express.json());

// Biến lưu lệnh chờ cho ESP32
let pendingCommand = "";

// ==========================================
// WEB ENDPOINTS
// ==========================================

// Trang chủ: Gửi file HTML giao diện
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'ai_studio_code.html'));
});

// 1. Web gửi lệnh
app.post('/command', (req, res) => {
    const { command } = req.body;
    
    if (!command) {
        return res.status(400).json({ error: "Missing command" });
    }

    pendingCommand = command;

    try {
        insertLog.run('cmd', command);
        res.json({ status: "ok" });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// 2. Web lấy logs (Chỉ lấy 100 dòng mới nhất, tối ưu hiệu năng)
app.get('/logs', (req, res) => {
    try {
        const rows = getLatestLogs.all();
        res.json(rows);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// ==========================================
// ESP32 ENDPOINTS
// ==========================================

// 3. ESP32 kiểm tra lệnh mới (Polling)
app.get('/command', (req, res) => {
    res.send(pendingCommand);
    pendingCommand = ""; // Xóa lệnh sau khi đã gửi cho ESP32
});

// 4. ESP32 tải dữ liệu/phản hồi lên
app.post('/upload', (req, res) => {
    const { data } = req.body;
    
    if (!data) {
        return res.status(400).json({ error: "Missing data" });
    }

    const isRes = data.startsWith("OK") || data.startsWith("ERROR");
    const type = isRes ? "res" : "data";

    try {
        insertLog.run(type, data);
        res.json({ status: "ok" });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// Start Server
app.listen(PORT, () => {
    console.log(`🚀 Modern Remote Serial Monitor Server running at port ${PORT}`);
    console.log(`📂 SQLite Database: ./data/logs.db`);
});
