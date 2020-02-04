const resources = require('../resources/model');

const model = resources.app.sensors.humidity;
const pluginName = resources.app.sensors.humidity.name;


let localParams = { 'simulate': false, 'frequency': 2000 };
let interval;
//Inizio della lettura dei valore dal sensore
exports.start = function (params) {
    localParams = params;
    //controllo se il sensosre è in modalità simulazione
    if (localParams.simulate) { simulate(); }
    else { connectHardware(); }
};

//fermo la lettura dal sensore
exports.stop = function () {
    if (localParams.simulate) { clearInterval(interval); }
    else { sensor.unexport(); }
    console.info('%s plugin stopped!', pluginName);
};

//configuro l'hardware 
function connectHardware() {
    const arduino = require('./../hardware/arduino');
    interval = setInterval(function () { model.value = arduino.humidity; }, localParams.frequency);
    console.info('Hardware %s sensor started!', pluginName);
};
//modalità di simulaizione
function simulate() {
    interval = setInterval(function () {
        model.value += 1;
    }, localParams.frequency);
    console.info('Simulated %s sensor started!', pluginName);
};

