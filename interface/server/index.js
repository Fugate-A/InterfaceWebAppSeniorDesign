require('dotenv').config(); //env vars
const express = require('express');
const cors = require('cors'); //cross origin
const apiRoutes = require('./api'); //routes file
const { connectToDatabase } = require('./server'); //require mongo connection

const app = express();
const port = 5000;
const host = process.env.BackendHost //|| '0.0.0.0'; // Use 0.0.0.0 for network accessibility

app.use(cors()); // Allow all origins for now 
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

connectToDatabase();

// Use the API routes
app.use('/api', apiRoutes);

// Start the server
app.listen(port, host, () => {
  console.log(`Backend server is running on http://${host}:${port}`);
});
