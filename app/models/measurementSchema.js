//mi definisce come sono fatti i dati che verranno salvati nel database
const mongoose = require('mongoose');

const measurementSchema = new mongoose.Schema({ 
    type: { type: String, required: true },
    value: { type: String },
    timestamp: { type: Date, default: Date.now }
});

measurementSchema.index({ type: 1 });
measurementSchema.plugin(require('mongoose-paginate'));

//posso chiamare il nome della collazione 'Mesurement' lo schema di riferimento
module.exports = mongoose.model('Measurement', measurementSchema);
