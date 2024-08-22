const express = require('express');
const router = express.Router();
const { getClient } = require('./server'); // Import MongoDB client

// Save box configuration to MongoDB
router.post('/save-configuration', async (req, res) => {
  const { items } = req.body;
  const client = getClient(); // Get the MongoDB client

  if (!client) {
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db('YourDatabaseName'); // Use your actual database name
    const Configuration = db.collection('Configuration'); // Use your actual collection name
    // Create a new Configuration document with the received items
    await Configuration.insertOne({ items });

    // Respond with a success message
    res.status(201).json({ message: 'Configuration saved successfully!' });
  } catch (error) {
    // Log the error and send an error response
    console.error('Error saving configuration:', error);
    res.status(500).json({ message: 'Failed to save configuration.' });
  }
});

// Example GET request for testing purposes
router.get('/example', (req, res) => {
  console.log('Received GET request to /api/example');
  res.json({ message: 'Hello from the backend API!' });
});

module.exports = router;
