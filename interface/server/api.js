const express = require('express');
const { ObjectId } = require('mongodb'); // Import ObjectId for MongoDB operations
const router = express.Router();
const { getClient } = require('./server'); // Import the MongoDB client

// Constants for APF
const ATTRACTIVE_CONSTANT = 1.0;  // Scaling factor for attractive force
const REPULSIVE_CONSTANT = 100.0; // Scaling factor for repulsive force
const REPULSIVE_THRESHOLD = 50;   // Distance threshold for repulsive force
const MAX_STEP_SIZE = 10;         // Maximum movement step size for each iteration
const ROTATION_STEP_SIZE = 5;     // Step size for rotation (in degrees)

// Utility function to calculate Euclidean distance
const calculateDistance = (pos1, pos2) => {
  return Math.sqrt(Math.pow(pos2.x - pos1.x, 2) + Math.pow(pos2.y - pos1.y, 2));
};

// Function to compute attractive force
const computeAttractiveForce = (currentPosition, targetPosition) => {
  const distance = calculateDistance(currentPosition, targetPosition);
  const forceMagnitude = ATTRACTIVE_CONSTANT * distance;
  const direction = {
    x: (targetPosition.x - currentPosition.x) / distance,
    y: (targetPosition.y - currentPosition.y) / distance,
  };
  return {
    x: forceMagnitude * direction.x,
    y: forceMagnitude * direction.y,
  };
};

// Function to compute repulsive force from obstacles
const computeRepulsiveForce = (currentPosition, obstacles) => {
  let totalForce = { x: 0, y: 0 };
  obstacles.forEach((obstacle) => {
    const distance = calculateDistance(currentPosition, obstacle);
    if (distance < REPULSIVE_THRESHOLD) {
      const forceMagnitude = REPULSIVE_CONSTANT * (1 / distance - 1 / REPULSIVE_THRESHOLD);
      const direction = {
        x: (currentPosition.x - obstacle.x) / distance,
        y: (currentPosition.y - obstacle.y) / distance,
      };
      totalForce.x += forceMagnitude * direction.x;
      totalForce.y += forceMagnitude * direction.y;
    }
  });
  return totalForce;
};

// Function to compute the resultant force (attractive + repulsive)
const computeResultantForce = (currentPosition, targetPosition, obstacles) => {
  const attractiveForce = computeAttractiveForce(currentPosition, targetPosition);
  const repulsiveForce = computeRepulsiveForce(currentPosition, obstacles);
  return {
    x: attractiveForce.x + repulsiveForce.x,
    y: attractiveForce.y + repulsiveForce.y,
  };
};

// Function to limit the step size of the movement
const limitStepSize = (force) => {
  const magnitude = Math.sqrt(force.x * force.x + force.y * force.y);
  if (magnitude > MAX_STEP_SIZE) {
    return {
      x: (force.x / magnitude) * MAX_STEP_SIZE,
      y: (force.y / magnitude) * MAX_STEP_SIZE,
    };
  }
  return force;
};

// Function to calculate rotation step towards target rotation
const calculateRotationStep = (currentRotation, targetRotation) => {
  const rotationDiff = targetRotation - currentRotation;
  if (Math.abs(rotationDiff) <= ROTATION_STEP_SIZE) {
    return targetRotation; // Snap to target rotation if close enough
  }
  return currentRotation + Math.sign(rotationDiff) * ROTATION_STEP_SIZE;
};

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

// Simulate movement from Layout 1 to Layout 2 using Artificial Potential Fields
router.post('/move-to-layout', (req, res) => {
  const { layout1Items, layout2Items, obstacles } = req.body;

  console.log('Simulating movement from Layout 1 to Layout 2 using APF');

  const movements = layout1Items.map((chair, index) => {
    const targetPosition = layout2Items[index];
    let currentPosition = { ...chair }; // Initialize with the current chair position
    const movementPath = [currentPosition]; // Keep track of the movement path

    // Phase 1: Simulate movement to target x and y
    while (calculateDistance(currentPosition, targetPosition) > 1) { // Threshold for arrival
      const resultantForce = computeResultantForce(currentPosition, targetPosition, obstacles);
      const step = limitStepSize(resultantForce);
      currentPosition = {
        x: currentPosition.x + step.x,
        y: currentPosition.y + step.y,
        rotation: currentPosition.rotation, // Keep rotation unchanged during this phase
      };
      movementPath.push(currentPosition); // Record the step
    }

    // Phase 2: Simulate rotation in place after reaching target x, y
    while (currentPosition.rotation !== targetPosition.rotation) {
      currentPosition = {
        x: currentPosition.x, // Keep x and y unchanged
        y: currentPosition.y,
        rotation: calculateRotationStep(currentPosition.rotation, targetPosition.rotation), // Rotate chair in place
      };
      movementPath.push(currentPosition); // Record the step
    }

    return {
      chairIndex: index + 1,
      movementPath,
    };
  });

  res.json({
    message: 'Movement simulation completed using Artificial Potential Fields.',
    movements,
  });
});

module.exports = router;
