const express = require('express');
const router = express.Router();

// Example GET route
router.get('/example', (req, res) => {
  console.log('Received GET request to /api/example'); // Log to console
  res.json({ message: 'Hello from the backend API!' });
});

// Example POST route
router.post('/example', (req, res) => {
  console.log('Received POST request to /api/example'); // Log to console
  res.json({ message: 'Hello from the backend API post!' });
});

// Add more routes as needed

module.exports = router; // Export the router
