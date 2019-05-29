const express = require('express');
const router = express.Router();
const resources = require('./../resources/model');

router.route('/').get(function (req, res) {
    req.result = resources.app.sensors;
});
router.route('/temperature').get(function (req, res) {
    req.result = resources.app.sensors.temperature;
});
router.route('/humidity').get(function (req, res) {
    req.result = resources.app.sensors.humidity;
  });

  module.exports = router;