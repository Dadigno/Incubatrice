const Telegraf = require('telegraf'); //api reference
const proxy = require('./middleware/proxy');
const resources = require('./../resources/model');
const bot = new Telegraf('826345410:AAGkH0QKBxBjC8neRNotOViRr_zqwXSiWr0'); //inizialize the telegram bot Telegraf(toker, options)

const temperature = resources.app.sensors.temperature;
const humidity = resources.app.sensors.humidity;
const lamp = resources.app.actuators.lamp;
const fan = resources.app.actuators.fan;
bot.use(proxy());
bot.command('status', ctx => {
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
bot.command('accendiVentola', ctx => { ctx.reply('comando ventola'); });
module.exports = bot;