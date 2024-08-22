require('dotenv').config(); // Load environment variables
const express = require('express');
const cors = require('cors');
const apiRoutes = require('./api'); // Import your API routes
const { connectToDatabase } = require('./server'); // Import the function to connect to the database

const app = express();
const port = 5000;

// Middleware
app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Connect to MongoDB
connectToDatabase();

// Use the API routes
app.use('/api', apiRoutes);

// Additional route directly in index.js for demonstration
app.get('/api/example-direct', (req, res) => {
  console.log('Received request to /api/example-direct');
  res.json({ message: 'Hello from Express backend directly in index.js!' });
});

// Start the server
app.listen(port, () => {
  console.log(`Backend server is running on http://localhost:${port}`);
});
