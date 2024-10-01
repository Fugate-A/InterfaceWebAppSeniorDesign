const express = require('express');
const { ObjectId } = require('mongodb'); // Import ObjectId for MongoDB operations
const router = express.Router();
const { getClient } = require('./server'); // Import the MongoDB client

// Save box configuration to MongoDB
router.post('/save-configuration', async (req, res) => {
  const { layoutName, items } = req.body;
  console.log('Received request to save configuration:', { layoutName, items });

  const client = getClient(); // Get the MongoDB client instance

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  if (!layoutName || !items || !Array.isArray(items)) {
    console.error('Invalid layout data provided:', { layoutName, items });
    return res.status(400).json({ error: 'Invalid layout data provided' });
  }

  try {
    const db = client.db(process.env.LocalRoomName); // Access the MongoDB database
    const configurationCollection = db.collection('Configurations'); // Access the configurations collection

    // Insert the layout configuration into MongoDB
    const result = await configurationCollection.insertOne({ layoutName, items });

    if (result.acknowledged) {
      console.log('Configuration saved successfully!');
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
  console.log('Received request to load layouts');
  
  const client = getClient(); // Get the MongoDB client instance

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName); // Access the MongoDB database
    const layoutsCollection = db.collection('Configurations'); // Access the collection
    
    // Fetch all layouts, project only the relevant fields (layoutName and items)
    const layouts = await layoutsCollection.find({}, { projection: { layoutName: 1, items: 1 } }).toArray();
    
    console.log('Layouts loaded:', layouts);
    res.json({ layouts });
  } catch (error) {
    console.error('Error loading layouts:', error);
    res.status(500).json({ message: 'Failed to load layouts.' });
  }
});

// Load specific configuration by ID
router.get('/load-configuration/:layoutId', async (req, res) => {
  const { layoutId } = req.params;
  console.log('Received request to load configuration for layoutId:', layoutId);

  const client = getClient(); // Get the MongoDB client instance

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName); // Access the MongoDB database
    const layoutsCollection = db.collection('Configurations'); // Access the collection

    // Check if the layoutId is a valid MongoDB ObjectId
    if (!ObjectId.isValid(layoutId)) {
      console.error('Invalid ObjectId format:', layoutId);
      return res.status(400).json({ error: 'Invalid layoutId format' });
    }

    // Fetch the specific layout by its ID
    const layout = await layoutsCollection.findOne({ _id: new ObjectId(layoutId) });

    if (layout) {
      console.log('Layout found:', layout);
      res.json({ items: layout.items || [] }); // Ensure items is at least an empty array
    } else {
      console.error('Layout not found for layoutId:', layoutId);
      res.status(404).json({ error: 'Layout not found' });
    }
  } catch (error) {
    console.error('Error loading layout configuration:', error);
    res.status(500).json({ message: 'Failed to load layout configuration.' });
  }
});

// Example GET request for testing purposes
router.get('/example', (req, res) => {
  console.log('Received GET request to /api/example');
  res.json({ message: 'Hello from the backend API!' });
});

module.exports = router;
