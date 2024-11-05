const { MongoClient } = require('mongodb');
const WebSocket = require('ws');  // Import WebSocket
const http = require('http');  // Required for the HTTP server
require('dotenv').config();  // Load environment variables

let client;  // MongoDB client instance
let wsClient = null;  // WebSocket client instance for ESP32 communication

// MongoDB connection setup
const connectToDatabase = async () => {
  try {
    const uri = process.env.LocalMachineMongoURL;  // MongoDB URI from .env

    if (!uri) {
      throw new Error('MongoDB URI is not defined in the environment variables.');
    }

    // Create a MongoClient for the local MongoDB (note: SSL is disabled for local connections)
    client = new MongoClient(uri, {
      useUnifiedTopology: true,
    });

    // Connect to MongoDB and ping the database
    await client.connect();
    await client.db('admin').command({ ping: 1 });
    console.log('Successfully connected to local MongoDB');
  } catch (error) {
    console.error('Error connecting to MongoDB:', error.message);
    process.exit(1);  // Exit process on failure
  }
};

// Function to get the MongoDB client
const getClient = () => {
  return client;
};

// Create an HTTP server (needed for WebSocket)
const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/plain' });
  res.end('WebSocket Server Running\n');
});

// Set up WebSocket on top of the HTTP server
const setupWebSocket = (server) => {
  const wss = new WebSocket.Server({ server });

  wss.on('connection', (ws) => {
    console.log('New WebSocket client connected');
    wsClient = ws;  // Store this WebSocket client for external use

    // Handle incoming WebSocket messages
    ws.on('message', (message) => {
      console.log(`Received message from client: ${message}`);
      ws.send(`Server received: ${message}`);  // Echo message back to client
    });

    // Handle WebSocket closing
    ws.on('close', () => {
      console.log('Client disconnected');
      wsClient = null;  // Clear the client reference on disconnect
    });

    // Handle WebSocket errors
    ws.on('error', (error) => {
      console.error('WebSocket error:', error);
    });
  });

  console.log('WebSocket server is running');
};

// Function to send a command to the connected ESP32 via WebSocket
const sendCommandToESP32 = (command) => {
  if (wsClient && wsClient.readyState === WebSocket.OPEN) {
    wsClient.send(command);
    console.log(`Sent command to ESP32: ${command}`);
  } else {
    console.error('WebSocket client not connected or not ready');
  }
};

// Start the server and WebSocket
const startServer = async () => {
  await connectToDatabase();  // Connect to MongoDB

  // Use global settings for WebSocket from the .env file
  const WS_PORT = process.env.WS_PORT || 8081;  // Default WebSocket port
  const WS_HOST = '0.0.0.0';  // Bind to all available interfaces

  // Listen for HTTP requests and WebSocket connections
  server.listen(WS_PORT, WS_HOST, () => {
    console.log(`WebSocket server running at ${WS_HOST}:${WS_PORT}`);
  });

  // Set up WebSocket functionality
  setupWebSocket(server);
};

// Start the server
startServer();

module.exports = { connectToDatabase, getClient, sendCommandToESP32 };
