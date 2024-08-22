const mongoose = require('mongoose');

const chairConfigurationSchema = new mongoose.Schema({
  items: [
    {
      id: Number,
      x: Number,
      y: Number,
      width: Number,
      height: Number,
      rotation: Number
    }
  ],
  createdAt: {
    type: Date,
    default: Date.now
  }
});

const ChairConfiguration = mongoose.model('ChairConfiguration', chairConfigurationSchema);
module.exports = ChairConfiguration;
