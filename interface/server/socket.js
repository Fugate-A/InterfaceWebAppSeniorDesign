const http = require('http');
const socketIo = require('socket.io');

// Function to initialize WebSocket server
const initializeWebSocket = (app) => {
  const server = http.createServer(app);

  // Initialize Socket.IO for WebSocket communication
  const io = socketIo(server, {
    cors: {
      origin: '*', // Allow any origin for simplicity (restrict this in production)
      methods: ['GET', 'POST'],
    }
  });

  // WebSocket event handler
  io.on('connection', (socket) => {
    console.log('A new client connected:', socket.id);

    // Handle messages from the web client
    socket.on('message', (message) => {
      console.log('Received message from client:', message);

      // Send a response back to the client (or forward to ESP32)
      socket.emit('response', `Server received: ${message}`);
    });

    // Handle ESP32-specific messages
    socket.on('esp-message', (message) => {
      console.log('Received message from ESP32:', message);

      // Broadcast ESP32 message to all connected web clients
      io.emit('esp-message', message);
    });

    // Handle WebSocket disconnection
    socket.on('disconnect', () => {
      console.log('Client disconnected:', socket.id);
    });
  });

  // Start the WebSocket server on a different port
  const PORT = process.env.SOCKET_PORT || 8081;
  server.listen(PORT, () => {
    console.log(`WebSocket server is running on port ${PORT}`);
  });
};

module.exports = initializeWebSocket;
