const char pageHeader_1[]  PROGMEM = R"header1(
<!DOCTYPE html>
<html>
<head>
<title>Robojax ESP32 Servo Motor Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
* {box-sizing: border-box}
.table{
    width:100%;
    display:table;
}
.row{
    display:table-row;
}


.fixedCell {
    width:15%;
    display:table-cell;

}

.cell{
    display: table-cell;
    background: green;
}

.progress_bar {
  font-size: 20px;  
  text-align: right;
  padding-top: 10px;
  padding-bottom: 10px;
  padding-right:10px;
  color: white;
  float:left;
  background-color:#34c0eb;  
}

.buttonsDiv {
  display: flex;
  justify-content: center;
  float:auto;
}
.startStop{
     font-size: 20px;
   background-color: #f44336;
    color: #ffffff;
    border-color: #f44336;  
    border: none;
    display: inline-block;
    padding: 7px 10px;
    vertical-align: middle;    
}

)header1";



const char pageHeader_2[] PROGMEM = R"robojaxSpeed2( 
.nextprev a.rj-right, .nextprev a.rj-left {
    background-color: #f44336;
    color: #ffffff;
    border-color: #f44336;
}
.angleButton a {
    font-size: 40px;
    border: 1px solid #cccccc;
    display: table-caption;
  
}


.nextprev a {
    font-size: 20px;
    border: 1px solid #cccccc;
}
.rj-right {
    float: right!important;
}
.rj-left {
    float: left!important;
}
.rj-btn, .rj-button {
    border: none;
    display: inline-block;
    padding: 7px 10px;
    vertical-align: middle;
    overflow: hidden;
    text-decoration: none;
    color: inherit;
    background-color: inherit;
    text-align: center;
    cursor: pointer;
    white-space: nowrap;
}
</style>
</head>
<body>

<h1>Robojax ESP32 Servo Motor control</h1>)robojaxSpeed2";


////////////////for motor 1 part 1///////////////
const char servo1Control_p1[] PROGMEM = R"robojaxSpeed3(
<h2>Servo 1 Control</h2>
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/servo?do=s1less">-</a>
            </div>        

        </div><!--fixedCell -->


        <div class="progress_bar bar1">)robojaxSpeed3";


////////////////for servo1 1 part 2///////////////
const char servo1Control_p2[] PROGMEM = R"robojaxSpeed4( deg.</strong></div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/servo?do=s1more">+</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row -->
</div><!--table -->   
<div class="table">
    <div class="row"> 
    <div class="row">
         <div class="fixedCell angleButton colspan">    
          <a class="rj-btn" href="/move?angle=0">0</a>
         </div>
        <div class="fixedCell angleButton colspan">       
          <a class="rj-btn angleButton" href="/move?angle=45">45</a>
         </div>
         
        <div class="fixedCell angleButton colspan">         
          <a class="rj-btn" href="/move?angle=90">900</a>
         </div>
         
        <div class="fixedCell angleButton colspan">        
          <a class="rj-btn" href="/move?angle=135">135</a>
         </div>
         
        <div class="fixedCell angleButton colspan">      
          <a class="rj-btn" href="/move?angle=180">180</a>
         </div>                                                      
    </div><!--row -->
</div><!--table -->  
)robojaxSpeed4";
