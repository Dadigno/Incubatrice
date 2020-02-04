require('dotenv').config({ path: 'variables.prod.env' });


const express = require('express'); //importo express
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const bodyParser = require('body-parser');

// Securing
const https = require('https');
const fs = require('fs');
const cert_file = './resources/caCert.pem'; // The certificate
const key_file = './resources/privateKey.pem'; // The private key
const passphrase = 'pippo';  // The password of the private key
const config = { key: fs.readFileSync(key_file), cert: fs.readFileSync(cert_file), passphrase: passphrase };
const auth = require('./../middleware/auth');

//middleware
const converter = require('./../middleware/converter');
const appRoutes = require('../middleware/appRoutes');

const app = express();

exports.start = function () {
    app.listen(process.env.port, function () {
        console.info('Http server started');
     });
}

app.use(bodyParser.json());
app.use(auth());

app.use('/app/actuators', actuatorsRoutes);
app.use('/app/sensors', sensorRoutes);
app.use('/app',appRoutes);
app.get('/', function (req, res) { res.send('Questa è la pagina iniziale dell\'applicazione di controllo della mia incubatrice') });
app.use(converter());
//creo un file di log nel database, ovverio una lista degli ultimi N dati rilavati dai sensori temperatura e umidità

// Add HTTPS support
const server = https.createServer(config, app);
