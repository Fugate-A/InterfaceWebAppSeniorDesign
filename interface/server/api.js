const express = require('express');
const { ObjectId } = require('mongodb'); // Import ObjectId for MongoDB operations
const router = express.Router();
const { getClient, sendCommandToESP32 } = require('./server'); // Import MongoDB client and WebSocket command function

// Constants for Artificial Potential Fields (APF)
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
    return targetRotation;
  }
  return currentRotation + Math.sign(rotationDiff) * ROTATION_STEP_SIZE;
};

// Save box configuration to MongoDB
router.post('/save-configuration', async (req, res) => {
  const { layoutName, items } = req.body;
  console.log('Received request to save configuration:', { layoutName, items });

  const client = getClient();

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  if (!layoutName || !items || !Array.isArray(items)) {
    console.error('Invalid layout data provided:', { layoutName, items });
    return res.status(400).json({ error: 'Invalid layout data provided' });
  }

  try {
    const db = client.db(process.env.LocalRoomName);
    const configurationCollection = db.collection('Configurations');
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

  const client = getClient();

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName);
    const layoutsCollection = db.collection('Configurations');
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

  const client = getClient();

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName);
    const layoutsCollection = db.collection('Configurations');

    if (!ObjectId.isValid(layoutId)) {
      console.error('Invalid ObjectId format:', layoutId);
      return res.status(400).json({ error: 'Invalid layoutId format' });
    }

    const layout = await layoutsCollection.findOne({ _id: new ObjectId(layoutId) });

    if (layout) {
      console.log('Layout found:', layout);
      res.json({ items: layout.items || [] });
    } else {
      console.error('Layout not found for layoutId:', layoutId);
      res.status(404).json({ error: 'Layout not found' });
    }
  } catch (error) {
    console.error('Error loading layout configuration:', error);
    res.status(500).json({ message: 'Failed to load layout configuration.' });
  }
});

// Simulate movement from Layout 1 to Layout 2 using APF
router.post('/move-to-layout', (req, res) => {
  const { layout1Items, layout2Items, obstacles } = req.body;

  console.log('Simulating movement from Layout 1 to Layout 2 using APF');

  const movements = layout1Items.map((chair, index) => {
    const targetPosition = layout2Items[index];
    let currentPosition = { ...chair };
    const movementPath = [currentPosition];

    while (calculateDistance(currentPosition, targetPosition) > 1) {
      const resultantForce = computeResultantForce(currentPosition, targetPosition, obstacles);
      const step = limitStepSize(resultantForce);
      currentPosition = {
        x: currentPosition.x + step.x,
        y: currentPosition.y + step.y,
        rotation: currentPosition.rotation,
      };
      movementPath.push(currentPosition);
    }

    while (currentPosition.rotation !== targetPosition.rotation) {
      currentPosition = {
        x: currentPosition.x,
        y: currentPosition.y,
        rotation: calculateRotationStep(currentPosition.rotation, targetPosition.rotation),
      };
      movementPath.push(currentPosition);
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

// Endpoint to send commands with command and value fields to ESP32 via WebSocket
router.post('/send-command', (req, res) => {
  const { command, value } = req.body;

  // Validate required fields
  if (!command) {
    return res.status(400).json({ error: 'Command is required' });
  }

  // Construct the message format
  const fullCommand = value !== undefined
    ? `${command},${value}` // Include value if provided
    : `${command},0`;       // Default to "0" for value if undefined

  sendCommandToESP32(fullCommand); // Send the message to ESP32
  console.log(`Command sent to ESP32: ${fullCommand}`);
  res.json({ message: `Command '${fullCommand}' sent to ESP32.` });
});

// Endpoint to store current chair positions sent by anchors
router.post('/store-current-chair-poss', async (req, res) => {
  const { links } = req.body; // Extract 'links' array from the JSON payload

  if (!links || !Array.isArray(links)) {
    return res.status(400).json({ error: 'Invalid or missing links data' });
  }

  const client = getClient();

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName);
    const positionsCollection = db.collection('CurrentPositions');

    // Process each link object
    const operations = links.map(({ A, R, dBm }) => {
      return {
        updateOne: {
          filter: { anchorId: A }, // Filter by anchor address
          update: {
            $set: {
              range: R,
              rxPower: dBm,
              updatedAt: new Date()
            },
            $setOnInsert: { tagId: "Tag1" } // Replace "Tag1" with a unique tag ID if needed
          },
          upsert: true // Perform upsert operation
        }
      };
    });

    // Perform bulk upsert operations
    const result = await positionsCollection.bulkWrite(operations);

    res.status(200).json({
      message: 'Position data stored successfully',
      matchedCount: result.matchedCount,
      modifiedCount: result.modifiedCount,
      upsertedCount: result.upsertedCount
    });
  } catch (error) {
    console.error('Error storing position data:', error);
    res.status(500).json({ message: 'Failed to store position data.' });
  }
});

// Endpoint to retrieve current positions for use in movement calculations
router.get('/current-chair-positions', async (req, res) => {
  console.log('Received request to fetch current chair positions');

  const client = getClient();

  if (!client) {
    console.error('Database client is not connected.');
    return res.status(500).json({ error: 'Database not connected' });
  }

  try {
    const db = client.db(process.env.LocalRoomName);
    const currentPositionsCollection = db.collection('CurrentPositions');

    // Fetch all position data from MongoDB
    const positions = await currentPositionsCollection.find({}).toArray();

    // Transform data for the frontend visualization
    const formattedPositions = positions.map((pos) => ({
      shortAddress: pos.shortAddress || 'Unknown', // Unique identifier of the tag
      range: pos.range || 0,                      // Distance to anchor
      rxPower: pos.rxPower || 0,                  // Received signal power
      anchorId: pos.anchorId || 'Unknown'         // Anchor identifier
    }));

    console.log('Returning positions:', formattedPositions);
    res.status(200).json({ positions: formattedPositions });
  } catch (error) {
    console.error('Error fetching positions:', error);
    res.status(500).json({ error: 'Failed to fetch positions.' });
  }
});
// Endpoint to calculate path and send motor commands
router.post('/calculate-path', async (req, res) => {
  const { targetPosition, currentPositions } = req.body;

  if (!targetPosition || !Array.isArray(currentPositions)) {
    return res.status(400).json({ error: 'Invalid target position or current positions data.' });
  }

  console.log('Received request to calculate delta movement to:', targetPosition);

  try {
    // Only consider the first chair for movement
    const currentPosition = currentPositions[0];

    if (!currentPosition) {
      return res.status(400).json({ error: 'No valid current position provided.' });
    }

    // Calculate deltas
    const deltaX = targetPosition.x - currentPosition.x;
    const deltaY = targetPosition.y - currentPosition.y;

    console.log(`Calculated deltas: X = ${deltaX}, Y = ${deltaY}`);

    // Send motor commands for deltaX and deltaY
    if (deltaX !== 0) {
      const commandX = deltaX > 0 ? 'translateRight' : 'translateLeft';
      const valueX = Math.abs(deltaX);
      await sendMotorCommand(commandX, valueX);
    }

    if (deltaY !== 0) {
      const commandY = deltaY > 0 ? 'moveForward' : 'moveBackward';
      const valueY = Math.abs(deltaY);
      await sendMotorCommand(commandY, valueY);
    }

    res.json({
      message: 'Motor commands sent successfully.',
      deltaX,
      deltaY,
    });
  } catch (error) {
    console.error('Error sending motor commands:', error);
    res.status(500).json({ error: 'Failed to send motor commands.' });
  }
});

// Helper function to determine motor command
const determineCommand = (step) => {
  // Determine motor command based on step direction
  if (Math.abs(step.x) > Math.abs(step.y)) {
    return step.x > 0 ? 'translateRight' : 'translateLeft';
  } else {
    return step.y > 0 ? 'moveForward' : 'moveBackward';
  }
};

// Helper function to calculate movement value
const calculateMovementValue = (step) => {
  // Calculate magnitude of movement
  return Math.sqrt(step.x * step.x + step.y * step.y);
};

// Helper function to send motor command via WebSocket
const sendMotorCommand = async (command, value) => {
  const fullCommand = `${command},${value}`;
  sendCommandToESP32(fullCommand); // Send the command to the ESP32 via WebSocket
  console.log(`Command sent to ESP32: ${fullCommand}`);
};


module.exports = router;
