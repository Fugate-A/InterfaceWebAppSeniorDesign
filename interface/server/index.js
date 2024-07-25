const express = require('express');
const cors = require('cors');
const app = express();
const port = 5000;

// Enables CORS requests
app.use(cors());

// API routes in api.js
const apiRoutes = require('./api');
app.use('/api', apiRoutes); // for routes with the prefix `/api`

// Additional route directly in index.js for demonstration
app.get('/api/example-direct', (req, res) => {
  console.log('Received request to /api/example-direct');
  res.json({ message: 'Hello from Express backend directly in index.js!' });
});

// Start the server
app.listen(port, () => {
  console.log(`Backend server is running on http://localhost:${port}`);
});
