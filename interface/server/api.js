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
    const db = client.db('YourDatabaseName');                               // Replace with your actual database name
    const configurationCollection = db.collection('Configuration');         // Replace with your actual collection name
    
    await configurationCollection.insertOne({ items });                     // Create a new collection document with the sent items (chairs)
    
    res.status(201).json({ message: 'Configuration saved successfully!' }); // Respond with a success message

  } catch (error) {
    console.error('Error saving configuration:', error);                    // Log the error and send an error response
    res.status(500).json({ message: 'Failed to save configuration.' });
  }
});

// Load layouts from MongoDB
router.get('/load-layouts', async (req, res) => {
  const client = getClient(); // Get the MongoDB client

  if (!client) {
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db('YourDatabaseName');                     // Replace with your actual database name
    const layoutsCollection = db.collection('Configuration');     // Replace with your actual collection name
    const layouts = await layoutsCollection.find({}).toArray();

    res.json({ layouts });                                        // Respond with the fetched layouts

  } catch (error) {
    console.error('Error loading layouts:', error);               // Log the error and send an error response
    res.status(500).json({ message: 'Failed to load layouts.' });
  }
});

// Example GET request for testing purposes
router.get('/example', (req, res) => {
  console.log('Received GET request to /api/example');
  res.json({ message: 'Hello from the backend API!' });
});

module.exports = router;
