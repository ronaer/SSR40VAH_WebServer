const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<! -- WebPage tasarım kodları -->
<! -- Web sayfamızı const char olarak tanımlayalım ve flash bellek için PROGMEM ile Raw String (R) kullanalım -->
<html>
  <head>
  <meta charset='utf-8'>
		<TITLE>Dr.TRonik YouTube</TITLE>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" rel="stylesheet">
    <style>
      html {
        font-family: Calibri;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }

      .slidecontainer {
        width: 100%;
        
      }

      .slider {
        -webkit-appearance: none;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: #e8aa0c; 
        outline: none;
        opacity: 0.5;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 2;

      }
      
      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #670ce8;
        cursor: pointer;
      }
      
      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #4CAF50;
        cursor: pointer;
      }
     
        
   .btn{
    position: relative;
    border-radius: 12px;
    width: 18%;
    height: 35px;
    border: 2px solid #4CAF50;
    outline: none;
    cursor: pointer;  
    background-color: #b8f5d0;  
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 20px;
   }
    </style>
  </head>

  <body>
   <body bgcolor=white>
	  <center>
	   <h1><I><B><font color=#f04107>ESP8266 Servo/SSR40VAH Kontrol</font></B> </I></h1>	
	   <hr size=1 width=250 align=“center” color=#ed0c75>
     <br><br>
     <div class="slidecontainer"></div>
     <input type="range" min="0" max="180" value="0" class="slider" id="myRange">      
     <p><font size="5" color=#9b0ced>Işık Düzeyi: <span id="demo"></span></font></p>       
     <font size="4" color=#aca0b8>(0-180) </font>
     <br><br>
     <button type="button" onclick="sendData_btn(1)" class="btn">DEMO</button>
     <br><br>
     <button type="button" onclick="sendData_btn(2)" class="btn"> 1/4</button>
     <button type="button" onclick="sendData_btn(3)" class="btn">1/2</button>
     <br><br>
     <button type="button" onclick="sendData_btn(4)" class="btn">ON</button>
     <button type="button" onclick="sendData_btn(5)" class="btn">OFF</button>
     <label><span id="isiStatusSERVO"></span></label>    
    
      <script>
        setInterval(function() {
        Time_Date();
        }, 1000); 

        function sendData(pos) {
         var xhttp = new XMLHttpRequest();
         xhttp.onreadystatechange = function() {
         if (this.readyState == 4 && this.status == 200) {
         console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setPOS?servoPOS="+pos, true);
        xhttp.send();
      } 
        
      function sendData_btn(StatusServo) { 
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) { 
            document.getElementById("SERstate1").innerHTML = this.responseText;     
          }
        };
        
        xhttp.open("GET", "setSERVO?;servoState=" + StatusServo, true);   
        xhttp.send();
      }

      function getDataSERVO() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("isiStatusSERVO").innerHTML = this.responseText;
          }
        };
        xhttp.open("put", "readSER", true);    
        xhttp.send();
        }
      var slider = document.getElementById("myRange");
      var output = document.getElementById("demo");
      output.innerHTML = slider.value;
      slider.oninput = function() {
        output.innerHTML = this.value;
        sendData(output.innerHTML);
      }

      function Time_Date() {
        var t = new Date();
        document.getElementById("time").innerHTML = t.toLocaleTimeString();
        var d = new Date();
        const dayNames = ["Pazar", "Pazartesi", "Salı", "Çarşamba", "Perşembe", "Cuma","Cumartesi"];
        const monthNames = ["OCAK", "ŞUBAT", "MART", "NİSAN", "MAYIS", "HAZİRAN","TEMMUZ", "AĞUSTOS", "EYLÜL", "EKİM", "KASIM", "ARALIK"];
        document.getElementById("date").innerHTML = d.getDate() + "/" + monthNames[d.getMonth()] + "/" + d.getFullYear()+ "/" + dayNames[d.getDay()];
      }

    </script>
          
     <br><br>
      <hr size=1 width=250 align=“center” color=#ed0c75>	
	<br>
	 <i class="far fa-calendar-check" style="font-size:1.0rem;color:black";></i>     
     <span id="date" style="font-size:1.0rem ; "></span>
	 <br>
	  
	 <i class="far fa-clock" style="font-size:1.0rem;color:purple;"></i>
     <span style="font-size:1.0rem;">Saat: </span>
     <span id="time" style="font-size:1.0rem;"></span>	 
	 <br>
	 <a href=https://www.youtube.com/channel/UCrDlm8ldOOh5cG5prINb77w target=_blank> Dr.TRonik & YouTube...</a>	
	 <i class="fab fa-youtube" style="font-size:1.2rem;color:red;"></i>		  

   

  </body>

</html>
)=====";