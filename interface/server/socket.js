const http = require('http');
const socketIo = require('socket.io');

let esp32Socket = null; // This will store the ESP32 socket when it connects

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

      // If the message is identifying the ESP32
      if (message === 'ESP32_CONNECTED') {
        console.log('ESP32 connected with ID:', socket.id);
        esp32Socket = socket; // Save the ESP32 socket
      }

      // Forward commands to the ESP32
      if (esp32Socket && message === 'MOVE_CHAIRS') {
        console.log('Forwarding command to ESP32:', message);
        esp32Socket.emit('esp-command', 'MOVE_CHAIRS'); // Send command to ESP32
      }

      // Send a response back to the web client
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
      if (socket === esp32Socket) {
        console.log('ESP32 disconnected');
        esp32Socket = null;
      }
    });
  });

  // Start the WebSocket server on a different port, binding to 0.0.0.0 (all network interfaces)
  const PORT = process.env.SOCKET_PORT || 8081;
  const HOST = '0.0.0.0'; // Bind to all network interfaces
  server.listen(PORT, HOST, () => {
    console.log(`WebSocket server is running on ${HOST}:${PORT}`);
  });
};

module.exports = initializeWebSocket;
