const http = require('http');
const MongoClient = require('mongodb').MongoClient
const url = 'mongodb://127.0.0.1:27017'

let db;
let index;
let commandCollection;
let wifiCollection;
let distanceCollection;
const options = { ordered: true };
MongoClient.connect(
  url,
  {
    useNewUrlParser: true,
    useUnifiedTopology: true
  },
  (err, client) => {
    if (err) {
      return console.log(err)
    }
    db = client.db('autitoDatabase')
  
    commandCollection = db.collection('commands')
    wifiCollection = db.collection('wifis')
    distanceCollection = db.collection('distances')
    
    console.log(`MongoDB Connected: ${url}`)
  }
)

function orderArray(initArray){
  let orderedArray = [...initArray.slice(index+1)]
  orderedArray = [...orderedArray,...initArray.slice(0,index+1)]
  return [...orderedArray]
}

var intervalId = setInterval(request
  , 15000);
  
async function request(){  
http.get('http://192.168.4.1/data', res => {
  let data = [];
  console.log('Status Code:', res.statusCode);

  res.on('data', c => {
    data.push(c);
  });
  
  res.on('end', async () => {
    let dataString = Buffer.concat(data).toString();
    let jsonData = JSON.parse(dataString);
  
    if(jsonData){
      console.log(jsonData)
      const sentTime = jsonData["time"];
      const realTime = Date.now();
      if(jsonData["commands"]){
        index = jsonData["indexC"];
        if(jsonData["commands"][index + 1]){
          jsonData["commands"] = orderArray(jsonData["commands"])
        }
        jsonData["commands"].forEach((value,index) => {
          jsonData["commands"][index]["date"] = new Date(parseInt(value["date"])).toUTCString()
        })
        try{
          await commandCollection.insertMany(jsonData["commands"] , options);
        }
        catch(err){
          console.log(err)
        }
      }
      if(jsonData["wifi"]){
        index = jsonData["indexW"];
        if(jsonData["wifi"][index + 1]){
          jsonData["wifi"] = orderArray(jsonData["wifi"])
        }
        jsonData["wifi"].forEach( (value,index) => {
          jsonData["wifi"][index]["date"] = new Date((realTime - (sentTime - value["date"]))).toUTCString() 
        })
        try{
          await wifiCollection.insertMany(jsonData["wifi"] , options);
        }
        catch(err){
          console.log(err)
        }
      }

      if(jsonData["distance"]){
        const distanceSave = {
          "distance" : jsonData["distance"],
          "date" : new Date(realTime).toUTCString()
        }
        try{
          await distanceCollection.insertOne(distanceSave);
        }
        catch(err){
          console.log(err)
        }
      }
  }
  else{
    console.log("Empty Data")
  }
});
}).on('error', err => {
  console.log('Error: ', err.message);
});
}

