const express = require('express');
const router = express.Router();
const resources = require('./../resources/model');

router.route('/').get(function (req, res, next) {
    res.send(resources.app.sensors);
    next();
});
router.route('/temperature').get(function (req, res, next) {
    res.send(resources.app.sensors.temperature);
    next();
});
router.route('/humidity').get(function (req, res, next) {
    res.send(resources.app.sensors.humidity);
    next();
  });

  module.exports = router;