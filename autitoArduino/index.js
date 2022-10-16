var lastfield = 7;
  let secuenceMode = false;
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

  function changeMode(){
    console.log("ENTROI ACA")
   
  }

  function sendit()
  {
    var request = new XMLHttpRequest();
    var d = new Date();
    var tempstr = '';

    request.onreadystatechange = function() 
    {
      if (this.readyState == 4 && this.status == 200) 
      {
        borrar();
      }
    }

    for (var i = 0; i < document.cntrform[0].value.length; i++) 
    {
      if      (document.cntrform[0].value.charCodeAt(i) == 8593)
       tempstr = tempstr+'F';
      else if (document.cntrform[0].value.charCodeAt(i) == 8595)
       tempstr = tempstr+'B';
      else if (document.cntrform[0].value.charCodeAt(i) == 8592)
       tempstr = tempstr+'L';
      else if (document.cntrform[0].value.charCodeAt(i) == 8594)
       tempstr = tempstr+'R';
      else if (document.cntrform[0].value.charCodeAt(i) == 9887)
       tempstr = tempstr+'P';
    }
    request.open('GET', '/?E=' + tempstr + d.getTime(), true);
    request.send();
  }