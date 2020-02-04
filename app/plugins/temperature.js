const resources = require('./../resources/model');
//importo lo schema

const model = resources.app.sensors.temperature;
const pluginName = resources.app.sensors.temperature.name;
const unit = resources.app.sensors.temperature.unit;
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
    interval = setInterval(function () { model.value = arduino.temperature; }, localParams.frequency);
    console.info('Hardware %s sensor started!', pluginName);
};
//modalità di simulaizion
function simulate() {
    //setInterval mi permette di chiamare una callback ogni tot tempo passato come parametro
    interval = setInterval(function () { 
      model.value += 1;
    }, localParams.frequency);
    console.info('Simulated %s sensor started!', pluginName);
  };
  
  function showValue() { console.info('%s value = %s %s \n #######', pluginName, model.value, unit); };
  