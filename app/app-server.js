
const httpServer = require('./servers/http');

// Require all the sensor plugins we need
const fanPlugin = require('./plugins/fan');
const humPlugin = require('./plugins/humidity');
const lampPlugin = require('./plugins/lamp');
const tempPlugin = require('./plugins/temperature');
const database = require('./database/database');
const bot = require('./telegram/bot');

fanPlugin.start({'simulate': true, 'frequency': 1000});
humPlugin.start({'simulate': true, 'frequency': 1000});
lampPlugin.start({'simulate': true, 'frequency': 1000});
tempPlugin.start({'simulate': true, 'frequency': 1000});
database.startLogger({'frequency': 4000});
bot.start({'run': false});
httpServer.start();

 