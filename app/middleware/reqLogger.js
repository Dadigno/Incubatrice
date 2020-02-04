const mongoose = require('mongoose');
const db = require('../database/database');

module.exports = function () {

    return function (req, res, next) {
        
        next();
    }
};