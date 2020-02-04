//mi definisce come sono fatti i dati che verranno salvati nel database
const mongoose = require('mongoose');

const logStatusSchema = new mongoose.Schema({ 
    Unit_Temperature: {type: String},
    temperature: { type: String },
    Unit_Humidity: {type: String},
    humidity: { type: String },
    Unit_Fan: {type: String},
    fan: { type: String },
    Unit_Lamp: {type: String},
    lamp: { type: String },
    timestamp: { type: Date, default: Date.now }
});

logStatusSchema.index({ type: 1 });
logStatusSchema.plugin(require('mongoose-paginate'));

//posso chiamare il nome della collazione 'Mesurement' lo schema di riferimento
module.exports = mongoose.model('StatusLog', logStatusSchema);
