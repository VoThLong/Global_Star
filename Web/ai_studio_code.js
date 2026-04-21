const express = require('express');
const cors = require('cors');
const sqlite3 = require('sqlite3').verbose();

const app = express();
const PORT = 3000;

// Enable CORS and JSON parsing
app.use(cors());
app.use(express.json());

// In-memory variable to hold the latest command for the ESP32
let pendingCommand = "";

// Initialize SQLite Database
const db = new sqlite3.Database('./logs.db', (err) => {
    if (err) console.error("Error opening database:", err.message);
});

// Create table if it doesn't exist
db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS logs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        type TEXT,
        content TEXT,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);
});

// ==========================================
// WEB ENDPOINTS
// ==========================================

// 1. Web sends a command
app.post('/command', (req, res) => {
    const { command } = req.body;
    
    if (!command) {
        return res.status(400).json({ error: "Missing command" });
    }

    // Store in memory for the ESP32 to fetch
    pendingCommand = command;

    // Save to database
    db.run(
        `INSERT INTO logs (type, content, timestamp) VALUES (?, ?, datetime('now', 'localtime'))`,['cmd', command], 
        function(err) {
            if (err) return res.status(500).json({ error: err.message });
            res.json({ status: "ok" });
        }
    );
});

// 2. Web fetches all logs
app.get('/logs', (req, res) => {
    db.all(`SELECT type, content, timestamp FROM logs ORDER BY timestamp ASC`,[], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

// ==========================================
// ESP32 ENDPOINTS
// ==========================================

// 3. ESP32 polls for the latest command
app.get('/command', (req, res) => {
    // Send the pending command as a plain string
    res.send(pendingCommand);
    
    // Clear it so it is only sent once
    pendingCommand = "";
});

// 4. ESP32 uploads serial data/responses
app.post('/upload', (req, res) => {
    const { data } = req.body;
    
    if (!data) {
        return res.status(400).json({ error: "Missing data" });
    }

    // Determine log type based on content
    const isRes = data.startsWith("OK") || data.startsWith("ERROR");
    const type = isRes ? "res" : "data";

    // Save to database
    db.run(
        `INSERT INTO logs (type, content, timestamp) VALUES (?, ?, datetime('now', 'localtime'))`,[type, data], 
        function(err) {
            if (err) return res.status(500).json({ error: err.message });
            res.json({ status: "ok" });
        }
    );
});

// Start Server
app.listen(PORT, () => {
    console.log(`🚀 Remote Serial Monitor Server running at http://localhost:${PORT}`);
});