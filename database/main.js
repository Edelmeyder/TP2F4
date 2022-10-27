const http = require('http');

const MongoClient = require('mongodb').MongoClient
const url = 'mongodb://127.0.0.1:27017'
let db;
let dataCollection;
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
    // Specify the database you want to access
    dataCollection = db.collection('commands')
    
    console.log(`MongoDB Connected: ${url}`)
  }
)

async function test (){
try {
  const asd = [{'value':'J','date':123},{'value':'P','date':124},{'value':'F','date':125}]
  console.log(asd)
  await dataCollection.insertMany(asd , options);
  }
  catch(err){
    console.log(err)
  }
}
var intervalId = setInterval(test
  , 3000);
  
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
      console.log(jsonData["commands"]);
      
    }
    else{
      console.log("Empty Data")
    }
  });
}).on('error', err => {
  console.log('Error: ', err.message);
});
}

