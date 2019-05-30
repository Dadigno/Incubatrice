const resources = require('./../resources/model');
let observer = require("node-observer");

const model = resources.app.actuators.lamp;

let interval;
const pluginName = resources.app.actuators.lamp.name;
let localParams = { 'simulate': false, 'frequency': 2000 };

exports.start = function (params) {
    localParams = params;
    observe(model);
    if (localParams.simulate) { simulate(); }
    else { connectHardware(); }
};

exports.stop = function () {
    clearInterval(interval);
    console.info('%s plugin stopped!', pluginName);
};

function observe(what) { observer.subscribe(this, what.name, function (who, data) { switchOnOff(what.name, data); }); };

function switchOnOff(name, value) {
    console.info('Change detected by plugin for %s = %s', name, value);
    if (!localParams.simulate) {
        //const arduino = require('./../hardware/arduino');
        //arduino.send(name, value);
        console.info('Changed value of %s to %s', name, value);
    }
};

function connectHardware() { console.info('Hardware %s actuator started!', pluginName); };

function simulate() {
  interval = setInterval(function () {
    // effetuo un cambiamento del model, l'observer se ne accorgerà..
    if (model.value) { model.value = false; } 
    else { model.value = true; }
    showValue(); 
  }, localParams.frequency);

  console.info('Simulated %s actuator started!', pluginName);
};

function showValue() { console.info('%s value = %s', pluginName, model.value); };
  
