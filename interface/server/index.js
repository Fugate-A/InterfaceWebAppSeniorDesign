const express = require('express');
const cors = require('cors'); // Import cors package
const app = express();
const port = 5000;

// Enable all CORS requests
app.use(cors());

// Define your API routes here
app.get('/api/example', (req, res) => {
  console.log('Received request to /api/example');
  res.json({ message: 'Hello from Express backend!' });
});

app.listen(port, () => {
  console.log(`Backend server is running on http://localhost:${port}`);
});
