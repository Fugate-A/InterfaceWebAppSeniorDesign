const express = require('express');
const router = express.Router();
const { getClient } = require('./server'); //mongo

// Save box configuration to MongoDB
router.post('/save-configuration', async (req, res) => {
  const { items } = req.body;
  const client = getClient(); // Get the MongoDB client

  if (!client) {
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db( process.env.LocalRoomName );                       //database name in mongo that is configurable in one spot in the env for any application, can hold more than configuartions such as users
    const configurationCollection = db.collection('Configurations');         //collection name for where chair are stored
    
    await configurationCollection.insertOne({ items });                     // Create a new collection document with the sent items (chairs)
    
    res.status(201).json({ message: 'Configuration saved successfully!' }); //respond success

  } catch (error) {
    console.error('Error saving configuration:', error);                    //log error and send response
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
    const db = client.db( process.env.LocalRoomName );             
    const layoutsCollection = db.collection('Configurations');     
    const layouts = await layoutsCollection.find({}).toArray();

    res.json({ layouts });                                        //gets fetched layouts

  } catch (error) {
    console.error('Error loading layouts:', error);               //log the error and send response
    res.status(500).json({ message: 'Failed to load layouts.' });
  }
});

// Example GET request for testing purposes
router.get('/example', (req, res) => {
  console.log('Received GET request to /api/example');
  res.json({ message: 'Hello from the backend API!' });
});

module.exports = router;
