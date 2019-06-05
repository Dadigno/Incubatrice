require('dotenv').config({ path: 'variables.prod.env' });

const httpServer = require('./servers/http');

// Require all the sensor plugins we need
const fanPlugin = require('./plugins/fan');
const humPlugin = require('./plugins/humidity');
const lampPlugin = require('./plugins/lamp');
const tempPlugin = require('./plugins/temperature');

fanPlugin.start({'simulate': true, 'frequency': 1000});
humPlugin.start({'simulate': true, 'frequency': 1000});
lampPlugin.start({'simulate': true, 'frequency': 1000});
tempPlugin.start({'simulate': true, 'frequency': 1000});
 
const database = require('./database/database');
database.startLogger({'frequency': 4000});

const bot = require('./telegram/bot');
bot.start({'run': false});


httpServer.listen(process.env.port, function () {
    console.info('Iot incubator started!!');
 });

 