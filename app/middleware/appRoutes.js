const resources = require('./../resources/model');


module.exports = function () {

    return function (req, res, next) {
        req.result = resources;
        next();
    }
};