const bot = require('./../bot');

module.exports = function () {
    return function (ctx, next) {

    next();
    }
};