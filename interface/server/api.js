const express = require('express');
const router = express.Router();
const { getClient } = require('./server'); // Import the MongoDB client

// Save box configuration to MongoDB
router.post('/save-configuration', async (req, res) => {
  const { layoutName, items } = req.body;
  const client = getClient(); // Get the MongoDB client instance

  if (!client) {
    return res.status(500).json({ error: 'Database not connected' });
  }

  if (!layoutName || !items || !Array.isArray(items)) {
    return res.status(400).json({ error: 'Invalid layout data provided' });
  }

  try {
    const db = client.db(process.env.LocalRoomName); // Access the MongoDB database
    const configurationCollection = db.collection('Configurations'); // Access the configurations collection

    // Insert the layout configuration into MongoDB
    const result = await configurationCollection.insertOne({ layoutName, items });

    if (result.acknowledged) {
      res.status(201).json({ message: 'Configuration saved successfully!' });
    } else {
      throw new Error('Failed to save configuration');
    }
  } catch (error) {
    console.error('Error saving configuration:', error);
    res.status(500).json({ message: 'Failed to save configuration.' });
  }
});

// Load layouts from MongoDB
router.get('/load-layouts', async (req, res) => {
  const client = getClient(); // Get the MongoDB client instance

  if (!client) {
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName); // Access the MongoDB database
    const layoutsCollection = db.collection('Configurations'); // Access the collection
    
    // Fetch all layouts, project only the relevant fields (layoutName and items)
    const layouts = await layoutsCollection.find({}, { projection: { layoutName: 1, items: 1 } }).toArray();
    
    res.json({ layouts });
  } catch (error) {
    console.error('Error loading layouts:', error);
    res.status(500).json({ message: 'Failed to load layouts.' });
  }
});

// Example GET request for testing purposes
router.get('/example', (req, res) => {
  console.log('Received GET request to /api/example');
  res.json({ message: 'Hello from the backend API!' });
});

module.exports = router;
