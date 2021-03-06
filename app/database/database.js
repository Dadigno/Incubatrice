const mongoose = require('mongoose');
const mongoosePaginate = require('mongoose-paginate');  //gestisce la papginazione dei risultati
const StatusLog = require('./models/logStatusSchema');
const DataTypes = require('./models/DataTypes');
const resources = require('./../resources/model');

mongoose.Promise = global.Promise;
mongoose.connect(process.env.DATABASE, { useNewUrlParser: true });
mongoose.set('useCreateIndex', true);
mongoosePaginate.paginate.options = {
  lean: false,
};


let intLogger = 0;
exports.startLogger = function (params) {
  intLogger = setInterval(function () {
    (new StatusLog({ Unit_Temperature: DataTypes.temperature, temperature: resources.app.sensors.temperature.value,
                     Unit_Humidity: DataTypes.humidity, humidity: resources.app.sensors.humidity.value,
                     Unit_Fan: DataTypes.fan, fan: resources.app.actuators.fan.value,
                     Unit_Lamp: DataTypes.lamp, lamp: resources.app.actuators.lamp.value
    })).save();
  }, params.frequency);
  console.info('Status logger started at frequency of %s: ', params.frequency);
};

exports.stopLogger = function () {
  clearInterval(intLogger);
  console.info('Logger stopped');
};

mongoose.connection.on('error', (err) => {
  console.error('Database connection error ' + err.message);
  this.stopLogger();
});


require('./models/logStatusSchema');
