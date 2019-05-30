const express = require('express'); //uso express
const observer = require("node-observer");  //uso un osservatore
const router = express.Router();  //metto express.Router() in const router cosi da utilizzarlo sotto
const resources = require('./../resources/model');  //importo il model che contiere le risorse così da resouces posso accedere alle risorse che voglio

//GET REQUEST
router.route('/').get(function (req, res, next) { //next è la succesiva funzione middlwware che fa chiamata in catena 
    req.result = resources.app.actuators;
    next();
});
router.route('/lamp').get(function (req, res, next) {
    req.result = resources.app.actuators.lamp;
    next();
});
router.route('/fan').get(function (req, res, next) {
    req.result = resources.app.actuators.fan;
    next();
});

//PUT REQUEST
router.route('/fan').put(function (req, res, next) {
    observer.send(this, resources.app.actuators.fan.name, req.body.value);
    resources.app.actuators.fan.value = req.body.value;
    req.result = resources.app.actuators.fan;
    next();

});
router.route('/lamp').put(function (req, res, next) {
    observer.send(this, resources.app.actuators.lamp.name, req.body.value);
    resources.app.actuators.lamp.value = req.body.value;
    req.result = resources.app.actuators.lamp;
    next();
});

module.exports = router;
