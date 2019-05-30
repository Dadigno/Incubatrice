const mongoose = require('mongoose');
const db = require('./../database');
const Log = mongoose.model('Log');
const Measurement = mongoose.model('Measurement');

module.exports = function () {

    return function (req, res, next) {
        console.info('Logger called!');
        if (req.method == 'GET') {
            console.info('Faccio un log nuovo e cancello quello vecchio');
            var a = new Date(); // Current date now.
            var diff = (a - 1000 * 60 * 10);
            Measurement.find({ "timestamp": { $gte: new Date(diff) } }, function (err, docs) {
                db.dropCollection('logs');
                Log.insertMany(docs);
            });
        }
        next();
    }
};