const http = require('http');


var intervalId = setInterval(request
  , 3000);
  
function request(){  
http.get('http://192.168.4.1/distance', res => {
  let data = [];
  console.log('Status Code:', res.statusCode);

  res.on('data', c => {
    data.push(c);
  });
  
  res.on('end', () => {
    let dataString = Buffer.concat(data).toString();
    let jsonData = JSON.parse(dataString);
    if(jsonData){
      const index = jsonData["index"];
      if(jsonData["commands"][index + 1]){
        let orderedArray = [...jsonData["commands"].slice(index+1)]
        orderedArray = [...orderedArray,...jsonData["commands"].slice(0,index+1)]
        jsonData["commands"] = [...orderedArray]
      }
    }
  });
}).on('error', err => {
  console.log('Error: ', err.message);
});
}

