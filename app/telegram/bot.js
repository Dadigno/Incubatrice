const Telegraf = require('telegraf'); //api reference
const proxy = require('./middleware/proxy');
const resources = require('./../resources/model');
const observer = require("node-observer");
const authorized = require('./authorized');


const bot = new Telegraf(process.env.BOT_TOKEN); //inizialize the telegram bot Telegraf(toker, options)

const params = ({'run': false});

const temperature = resources.app.sensors.temperature;
const humidity = resources.app.sensors.humidity;
const lamp = resources.app.actuators.lamp;
const fan = resources.app.actuators.fan;


exports.start = function (params) {

  if (params.run) {
    observe();
    bot.launch();
  }
}

function observe() {
  observer.subscribe(this, "err", function (who, data) {
    console.log("Errore: " + data);
    sendError(data);
  });
};

function sendError(data) {
  bot.telegram.sendMessage(authorized[0], "Errore dalla incubatrice: " + data);
}
bot.use(proxy());
bot.command('status', ctx => {
  ctx.reply('Ultima lettura');
  ctx.reply('temperatura: ' + temperature.value + temperature.unit + '\n' +
    'humidity: ' + humidity.value + humidity.unit + '\n' +
    'fan: ' + fan.value + fan.unit + '\n' +
    'lamp: ' + lamp.value);
});
bot.command('accendiLampada', ctx => {
  ctx.reply('comando accendi lampada');
  lamp.value = true;
});
bot.command('spegniLampada', ctx => {
  ctx.reply('comando spegni lampada');
  lamp.value = false;
});
bot.command('accendiVentola', ctx => {
  ctx.reply('comando ventola');
});




