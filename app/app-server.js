// Load the databse, the http server, the websocekt server and the model
//const db = require('./database');
const httpServer = require('./servers/http');
const resources = require('./resources/model');

// Require all the sensor plugins we need
/*const ledsPlugin = require('./plugins/ledsPlugin');
const pirPlugin = require('./plugins/pirPlugin');
const tempPlugin = require('./plugins/tempPlugin');
const lightPlugin = require('./plugins/lightPlugin');
*/

const server = httpServer.listen(resources.app.port, function () {
    console.info('Your WoT Pi is up and running');
 });
