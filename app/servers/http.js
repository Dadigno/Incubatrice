const express = require('express'); //importo express
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const bodyParser = require('body-parser');

const converter = require('./../middleware/converter');
const logger = require('./../middleware/logger');

const measurementRoutes = require('./../routes/measurements');

const app = express();

app.use(bodyParser.json());
app.use('/app/measurements', measurementRoutes);
app.use('/app/actuators', actuatorsRoutes);
app.use('/app/sensors', sensorRoutes);
app.get('/app', function (req, res) { res.send('Questa è la pagina iniziale dell\'applicazione di controllo della mia incubatrice') });
app.use(logger());
app.use(converter());
//creo un file di log nel database, ovverio una lista degli ultimi N dati rilavati dai sensori temperatura e umidità


module.exports = app;
