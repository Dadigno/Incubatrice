// Load the databse, the http server, the websocekt server and the model
//const db = require('./database');
const db = require('./database');
const httpServer = require('./servers/http');
const resources = require('./resources/model');

// Require all the sensor plugins we need
const fanPlugin = require('./plugins/fan');
const humPlugin = require('./plugins/humidity');
const lampPlugin = require('./plugins/lamp');
const tempPlugin = require('./plugins/temperature');

fanPlugin.start({'simulate': false, 'frequency': 1000});
humPlugin.start({'simulate': true, 'frequency': 1000});
lampPlugin.start({'simulate': false, 'frequency': 1000});
tempPlugin.start({'simulate': true, 'frequency': 1000});
 
const server = httpServer.listen(resources.app.port, function () {
    console.info('Your WoT Pi is up and running');
 });
