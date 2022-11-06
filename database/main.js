const http = require('http');

const MongoClient = require('mongodb').MongoClient
const url = 'mongodb://127.0.0.1:27017'
let db;
let commandsCollection;
let wifiCollection;
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
  
    commandsCollection = db.collection('commands')
    wifiCollection = db.collection('wifis')
    
    console.log(`MongoDB Connected: ${url}`)
  }
)


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
    if(jsonData["commands"]){
      const index = jsonData["index"];
      if(jsonData["commands"][index + 1]){
        let orderedArray = [...jsonData["commands"].slice(index+1)]
        orderedArray = [...orderedArray,...jsonData["commands"].slice(0,index+1)]
        jsonData["commands"] = [...orderedArray]
      }
      try{
        await commandsCollection.insertMany(jsonData["commands"] , options);
      }
      catch(err){
        console.log(err)
      }
    }
    else{
      console.log("Empty Data")
    }
  
  if(jsonData["wifi"]){
    jsonData["wifi"].forEach(async el => {
      try{
        await wifiCollection.update(
          {
            SSID : el.SSID
          }, 
           {
            $setOnInsert: el
           },
           {upsert: true}
        )
      }
      catch(err){
        console.log(err)
      }
    })
  }
  });
}).on('error', err => {
  console.log('Error: ', err.message);
});
}

