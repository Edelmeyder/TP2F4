  let lastfield = 7;
  let secuenceMode = false;
  let d = new Date();
  const modebutton = document.getElementById('modebutton');

  modebutton.addEventListener('click', function handleClick() {
    secuenceMode = !secuenceMode;
    modebutton.textContent = secuenceMode ? "MODO NORMAL" : "MODO SECUENCIA"
    document.getElementById('divSequence').style.display = secuenceMode ? "inline" : "none"
    document.getElementById('divNormal').style.display = secuenceMode ? "none" : "inline"
  });

  function incr(parmtr)
  {
    document.cntrform[0].value = document.cntrform[0].value + parmtr;
    document.cntrform[lastfield].value = 'Enviar: ' + document.cntrform[0].value;
  }
  function borrar() 
  {
    document.cntrform[0].value = '';
    document.cntrform[lastfield].value = 'Enviar: ';
  }

  function sendChar(char){
    let request = new XMLHttpRequest();
    request.timeout = 1000;
    request.open('GET', '/?' + char + '&' + d.getTime(),true);
    request.send();
  }

  function sendSequence()
  {
    let request = new XMLHttpRequest();
    
    let tempstr = '';

    request.onreadystatechange = function() 
    {
      if (this.readyState == 4 && this.status == 200) 
      {
        borrar();
      }
    }

    const cant = document.cntrform[0].value.length;
    for (let i = 0; i < cant; i++) 
    {
      switch (document.cntrform[0].value.charCodeAt(i)){
        case 8593:
          tempstr = tempstr+'F';
          break;
        case 8595:
          tempstr = tempstr+'B';
          break;
        case 8592:
          tempstr = tempstr+'L';
          break;
        case 8594:
          tempstr = tempstr+'R';
          break;
        case 9887: 
          tempstr = tempstr+'P';
          break;
        default:
          break;
      }
    }
    request.timeout = 1000;
    request.open('GET', '/?E=' + tempstr + '&' +  d.getTime(), true);
    request.send();
  }