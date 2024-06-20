// server.js
const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

// MongoDB Atlas connection URI
const mongoURI = 'mongodb+srv://stathisrav:stathis2001@cluster0.q5nesqa.mongodb.net/iotdb?retryWrites=true&w=majority';

// Connect to MongoDB
mongoose.connect(mongoURI)
  .then(() => {
    console.log('MongoDB connected successfully');
  })
  .catch((err) => {
    console.error('MongoDB connection error:', err);
  });

// Define Schema
const sensorSchema = new mongoose.Schema({
  timestamp: Date,
  value: Number
});

// Define Model
const SensorData = mongoose.model('sensor_data', sensorSchema, 'sensor_data');

// API Endpoint to fetch sensor data
app.get('/api/sensor-data', async (req, res) => {
  try {
    const sensorData = await SensorData.find();
    res.json(sensorData);
  } catch (error) {
    console.error('Error fetching sensor data:', error);
    res.status(500).json({ message: 'Internal server error' });
  }
});

// Start Server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
