const serialport = require('serialport');
const values = require('./resources/model');
const observer = require("node-observer");  //uso un osservatore

const portName = values.port;

const sp = new serialport(portName, {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: new serialport.parsers.Readline("\r\n")
});

sp.on('data', function (input) {
    var res = input.toString().split(";");
    //console.log(res);
    if (res[0] == 'H') {
        values.temperature = res[1];
        values.humidity = res[2];
        values.lamp = res[3];
        values.fan = res[4];
        values.err = res[5];
    }
    if (res[0] == 'E') {
        observer.send(this, "err", res[1] );
        values.err = res[1];
    }
});

module.exports = values;