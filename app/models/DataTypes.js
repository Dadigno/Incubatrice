//elenco i campi "type" che potrò assegnare a ogni dato salvato nella collection
const DataTypes = Object.freeze({
    temperature: "temperature [C°]",
    humidity: "humidity [%]",
    fan: "fan velocity [%]",
    lamp: "lamp [true, false]"
});
//esporto in modo da utilizzare i tipi definiti quando faccio una chiamata al database
module.exports = DataTypes;
