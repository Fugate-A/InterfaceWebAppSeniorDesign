require('dotenv').config(); //env vars
const express = require('express');
const cors = require('cors'); //cross origin
const apiRoutes = require('./api'); //routes file
const { connectToDatabase } = require('./server'); //require mongo connection

const app = express();
const port = 5000;

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

connectToDatabase();

// Use the API routes
app.use('/api', apiRoutes);

// Start the server
app.listen(port, () => {
  console.log(`Backend server is running on http://localhost:${port}`);
});
