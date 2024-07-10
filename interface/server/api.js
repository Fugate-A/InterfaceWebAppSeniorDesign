const express = require('express');
const router = express.Router();

// Example route
router.get('/example', (req, res) => {
  res.json({ message: 'Hello from the backend API!' });
});

// Add more routes as needed

module.exports = router;
