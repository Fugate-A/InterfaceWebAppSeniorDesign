const express = require('express');
const cors = require('cors');

const app = express();
const port = 5000;

// Middleware
app.use(cors()); // Enable CORS for all routes
app.use(express.json()); // Enable JSON body parsing for POST requests
app.use(express.urlencoded({ extended: true })); // Enable URL-encoded body parsing for POST requests

// Import API routes
const apiRoutes = require('./api');

// Use the API routes
app.use('/api', apiRoutes); // All routes defined in api.js will have the prefix `/api`

// Additional route directly in index.js for demonstration
app.get('/api/example-direct', (req, res) => {
  console.log('Received request to /api/example-direct');
  res.json({ message: 'Hello from Express backend directly in index.js!'});
});

// Start the server
app.listen(port, () => {
  console.log(`Backend server is running on http://localhost:${port}`);
});
