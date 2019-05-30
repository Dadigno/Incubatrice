const mongoose = require('mongoose');
const mongoosePaginate = require('mongoose-paginate');  //gestisce la papginazione dei risultati

mongoose.Promise = global.Promise; 
mongoose.connect('mongodb://localhost:27017/wotserver-prod');
const database = mongoose.connection;

database.on('error', (err) => {
  console.error('Database connection error '+ err.message);
});

mongoosePaginate.paginate.options = { 
  lean: false,
};

require('./models/measurementSchema');
require('./models/logSchema');

module.exports = database;