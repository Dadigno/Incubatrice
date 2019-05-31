const bot = require('./../bot');
const authorized = [92526015];  //autorizzati ad usare il bot

module.exports = function () {
    return function (ctx, next) {
       
        if (!isAuthorized(ctx)) {
            console.log('Tentativo di accesso da: ' + ctx.from.id);
            ctx.reply('Access denied \nNon sei autorizzato ad usare questo bot');
            return;
        }
        next();
    }
};

function isAuthorized(ctx) {    //dice se l'utente fa parte della lista degli autorizzati a utilizzare il bot
    for (i = 0; i < authorized.length; i++) {
        if (authorized[i] == ctx.from.id) return true;
    }
    return false;
}

