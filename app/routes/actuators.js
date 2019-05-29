const express = require('express'); //uso express
const observer = require("node-observer");  //uso un osservatore
const router = express.Router();  //metto express.Router() in const router cosi da utilizzarlo sotto
const resources = require('./../resources/model');  //importo il model che contiere le risorse così da resouces posso accedere alle risorse che voglio

//GET REQUEST
router.route('/').get(function (req, res) { //next è la succesiva funzione middlwware che fa chiamata in catena 
    req.result = resources.iot.actuators;  //restituisco il model di sensor quindi tutta la lista dei sensori
});
router.route('/lamp').get(function (req, res) {
    req.result = resources.iot.actuators.lamp;
});
router.route('/fan').get(function (req, res) {
    req.result = resources.iot.actuators.fan;
});

//PUT REQUEST
router.route('/fan').put(function (req, res) {
    observer.send(this, "fan", req.body.value);
});
router.route('/lamp').put(function (req, res) {
    observer.send(this, "lamp", req.body.value);
});

module.exports = router;
