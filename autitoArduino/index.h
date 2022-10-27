const char MAIN_page[] PROGMEM = R"=====(
<html>
  <HEAD>
     <TITLE>AutoWifi</TITLE>
     <meta name='viewport' content='user-scalable=no'/>
  </HEAD>




<CENTER>
  <div style="display: table;
  margin-top: 1%;
  position: absolute;
  top: 0;
  left: 0;
  height: 100%;
  width: 100%;">
<div style="display: table-cell;vertical-align: middle">
<div style = " margin-left: auto;
margin-right: auto;
width: 1000px">
  <body>
    <div style = "text-align: right;">
      <button id='modebutton' style='height:80px;width:25%;font-size:30px;margin-right: 5%;'>MODO SECUENCIA</button>
    </div>
    <br><br><br>
<div id="divSequence" style="display:none;overflow:hidden;">
<form name='cntrform'>
  <input type='hidden' id='strmvmnt' name='strmvmnt' value=''>                                   <! --  00   -->
  <input style='height:60%;width:40%;font-size:100px'  type='button' value=' &uarr; ' onClick="incr('&uarr;')"/>         <! --  01   -->
  <br><br><br>
  <input style='height:60%;width:40%;font-size:100px ; margin-right: 2%'  type='button' onClick="incr('&larr;')" value=' &larr; '/>         <! --  02   -->
  <input  style='height:60%;width:40%;font-size:100px' type="button" onClick="incr('&rarr;')" value=' &rarr; '/>         <! --  03   -->
  <br><br><br>
  <input style='height:60%;width:40%;font-size:100px' type='button' onClick="incr('&darr;')" value=' &darr; '/>         <! --  04   -->
  <br><br><br>
  <input style='height:60%;width:40%;font-size:100px; margin-right: 2%; background-color:lightskyblue;' type='button' onClick="incr('&#9887')" value=' Pew '/>
  <input style='height:60%;width:40%;font-size:100px;background-color:indianred;' type='button' onClick='borrar()' value='Clear'/> <! --  06   -->
           <! --  05   -->
  
  <br><br>             
  <input style='height:60%;width:80%;font-size:100px;background-color: lightgreen' type='button' onclick='sendSequence()' value='Enviar: '>               <! --  07   -->
</form>
</div>

<div id="divNormal" >
<form name="normalForm">
  <input style='height:60%;width:40%;font-size:100px' name='F' type='button' onClick="sendChar('f')" value=' &uarr; ' /><br><br><br>
  <input style='height:60%;width:40%;font-size:100px ; margin-right: 2%' name='L' onClick="sendChar('L')" type='button' value=' &larr; ' />
  <input style='height:60%;width:40%;font-size:100px' name='R' type='button' onClick="sendChar('R')" value=' &rarr; ' /><br><br><br>
  <input style='height:60%;width:40%;font-size:100px' name='B' type='button' onClick="sendChar('b')" value=' &darr; ' /><br><br><br>
  <input style='height:60%;width:40%;font-size:100px; margin-right: 2% ; background-color: lightskyblue' name='P' onClick="sendChar('P')" type='button' value='Pew'>
  <input style='height:60%;width:40%;font-size:100px ;background-color:indianred' name='S' onClick="sendChar('S')" type='button' value='Stop'>

  <br><br>
  <input style='height:60%;width:40%;font-size:100px;visibility:hidden ; background-color: lightgreen' name='P' onClick="sendChar('P')" value='Pew'>
</form>

</div>
</div>
</div>
</div>
</CENTER>
<script lenguage="JavaScript">
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
    request.open('GET', '/?' + char + '&' + d.getTime(), true);
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
    request.open('GET', '/?E=' + tempstr + '&' + d.getTime(), true);
    request.send();
  }   
</script>
</body>
</html>
)=====";
