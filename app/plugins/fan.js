const resources = require('./../resources/model');
let observer = require("node-observer");

const model = resources.app.actuators.fan;

let interval;
const pluginName = resources.app.actuators.fan.name;
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

function observe(what) { observer.subscribe(this, what.name, function (who, data) { setVelocity(what.name, data); }); };

function setVelocity(name, value) {
  if (!localParams.simulate) {
    //const arduino = require('./../hardware/arduino');
    //arduino.send(name, value);
    
  }
  console.info('Changed value of %s to %s', name, value);
};

function connectHardware() { 
  const arduino = require('./../hardware/arduino');
  interval = setInterval(function () { model.value = arduino.fan; }, localParams.frequency);
  console.info('Hardware %s actuator started!', pluginName); 
};

function simulate() {
  interval = setInterval(function () {
    model.value += 1;
    if (model.value > 255) { model.value = 0; }
    //showValue();
  }, localParams.frequency);
  console.info('Simulated %s actuator started!', pluginName);
};

function showValue() { console.info('%s value pwm = %s', pluginName, model.value); };
