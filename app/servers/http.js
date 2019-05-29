const express = require('express'); //importo express
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const bodyParser = require('body-parser');
const app = express();
app.use(bodyParser.json());
app.use('/app/actuators', actuatorsRoutes);
app.use('/app/sensors', sensorRoutes);
app.get('/app', function (req, res) { res.send('Questa è la pagina iniziale dell\'applicazione di controllo della mia incubatrice') });


module.exports = app;
