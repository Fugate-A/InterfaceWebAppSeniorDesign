const { MongoClient, ServerApiVersion } = require('mongodb');
require('dotenv').config(); // Load environment variables

let client; // This will hold the MongoClient instance

const connectToDatabase = async () => {
  try {
    // Retrieve the MongoDB connection string from environment variables
    const uri = process.env.LocalMachineMongoURL;

    if (!uri) {
      throw new Error('MongoDB URI is not defined in the environment variables.');
    }

    // Create a MongoClient with SSL, retryWrites, and stable API version
    client = new MongoClient(uri, {
      ssl: true, // Force SSL
      retryWrites: true,
      serverApi: {
        version: ServerApiVersion.v1,
        strict: true,
        deprecationErrors: true,
      },
    });

    // Connect to MongoDB and ping the database to check connection
    await client.connect();
    await client.db("admin").command({ ping: 1 });
    console.log('Successfully connected to MongoDB Atlas');

  } catch (error) {
    console.error('Error connecting to MongoDB Atlas:', error.message);
    process.exit(1); // Exit the process with failure
  }
};

const getClient = () => {
  return client; // Return the MongoClient instance
};

module.exports = { connectToDatabase, getClient };
