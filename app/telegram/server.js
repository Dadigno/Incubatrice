//rifaccio il server http con express. Cosa deve fare?
// - effettuare get verso i nodi per ottenere dati in formato JSON
// - ricevere le post generate per ricevere dati dai nodi

const express = require('express');
const http = require("http");
const bodyParser = require('body-parser');
const path = require('path');
const app = express();
var nodeList = [];  //nodi che si sono connessi alla rete
//const ip_server = "192.168.178.40";
const ip_server = "192.168.43.125";

app.get('/', function (req, res) { res.sendFile(path.join(__dirname + '/index.html')) }) //ritorna pagina iniziale
app.post('/node', bodyParser.json(), function (req, res) { //ricevo un formato json e parso name e id
  //se il nodo non è presente lo aggiungo
  if (req.body && req.body.name && req.body.id) {
    addNode(req.socket.remoteAddress, req.body.name, req.body.id);
    console.log("lista nodi:");
    console.log(nodeList);
    //console.log("lista nodi:\n" + nodelist);
  }
  res.send("ok");
})

app.get('/page', function (req, res) { 
  http.request(options, (response) => callback_request(response));
});

function callback_request(response) {  //funzione chiamata in risposta ad un comando verso un nodo
  response.on('data', function (chunk) {  //data è l'evento che indica l'arrivo di dati
  });
  console.log("Server responded with status code: " + response.statusCode);
}

const options = {  //opzioni del pacchetto http di richiesta di una azione da inviare al nodo
  hostname: "",
  path: "/",
  method: "GET",
  headers: {Accept: "text/plain"}
}

function addNode(ipAddress, name, id) {  //aggiungi il nodo se non ancora presente
  for (i = 0; i < nodeList.length; i++) {
    if (ipAddress == nodeList[i].ipAddress) return;
  }
  nodeList.push(new node(ipAddress, name, id));
  console.log("Nodo aggiunto");
}

function node(ipAddress, nameNode, id) {  //costruttore di un oggetto di tipo nodo
  this.ipAddress = ipAddress;
  this.nameNode = nameNode;
  this.id = id;
}



app.listen(8000, ip_server);