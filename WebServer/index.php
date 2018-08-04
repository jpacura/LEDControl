<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
   "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
	<head>
		<title>LED CONTROL PAGE</title>
		<link rel="stylesheet" type="text/css" href="index.css"/>
		
		<?php
		include 'php_serial.class.php';
		$serial = new phpSerial;
		$serial->deviceSet("/dev/ttyACM0");
		$serial->confBaudRate(9600);
		$serial->confCharacterLength(8);
		$serial->deviceOpen();
		if($_SERVER["REQUEST_METHOD"] == "POST")
		{			
			$LED1RED = $_POST["led1red"];
			$LED1GREEN = $_POST["led1green"];
			$LED1BLUE = $_POST["led1blue"];
			$LED2RED = $_POST["led2red"];
			$LED2GREEN = $_POST["led2green"];
			$LED2BLUE = $_POST["led2blue"];
			$LED3RED = $_POST["led3red"];
			$LED3GREEN = $_POST["led3green"];
			$LED3BLUE = $_POST["led3blue"];
			
			$var = "1,$LED1RED,$LED1GREEN,$LED1BLUE,$LED2RED,$LED2GREEN,$LED2BLUE,$LED3RED,$LED3GREEN,$LED3BLUE";
			
			$serial->sendMessage($var);
		}
		?>
		
		<?php
			sleep(1);
			$serial->sendMessage("2");
			
			$return = "";
			
			do
			{
				$return = $serial->readPort();
			} while($return == "");
			
			$estring = explode("," , $return);
			
			$READLED1RED = $estring[0];
			$READLED1GREEN = $estring[1];
			$READLED1BLUE = $estring[2];
			$READLED2RED = $estring[3];
			$READLED2GREEN = $estring[4];
			$READLED2BLUE = $estring[5];
			$READLED3RED = $estring[6];
			$READLED3GREEN = $estring[7];
			$READLED3BLUE = $estring[8];
		?>
		
		<script>
			function changeScreenColors()
			{ 
				var led1red = <?php echo $READLED1RED;?>;
				var led1green = <?php echo $READLED1GREEN;?>;
				var led1blue = <?php echo $READLED1BLUE;?>;
				var led1rgbstring = "rgb(" + led1red + "," + led1green + "," + led1blue + ")";
				document.getElementById("led1color").style.backgroundColor=led1rgbstring;
				
				var led2red = <?php echo $READLED2RED;?>;
				var led2green = <?php echo $READLED2GREEN;?>;
				var led2blue = <?php echo $READLED2BLUE;?>;
				var led2rgbstring = "rgb(" + led2red + "," + led2green + "," + led2blue + ")";
				document.getElementById("led2color").style.backgroundColor=led2rgbstring;
				
				var led3red = <?php echo $READLED3RED;?>;
				var led3green = <?php echo $READLED3GREEN;?>;
				var led3blue = <?php echo $READLED3BLUE;?>;
				var led3rgbstring = "rgb(" + led3red + "," + led3green + "," + led3blue + ")";
				document.getElementById("led3color").style.backgroundColor=led3rgbstring;
			}
			
			function selectCurrentValues()
			{
				var led1red = <?php echo $READLED1RED;?>;
				var led1green = <?php echo $READLED1GREEN;?>;
				var led1blue = <?php echo $READLED1BLUE;?>;
				var led2red = <?php echo $READLED2RED;?>;
				var led2green = <?php echo $READLED2GREEN;?>;
				var led2blue = <?php echo $READLED2BLUE;?>;
				var led3red = <?php echo $READLED3RED;?>;
				var led3green = <?php echo $READLED3GREEN;?>;
				var led3blue = <?php echo $READLED3BLUE;?>;
				
				document.getElementById("led1red").value=led1red;
				document.getElementById("led1green").value=led1green;
				document.getElementById("led1blue").value=led1blue;
				document.getElementById("led2red").value=led2red;
				document.getElementById("led2green").value=led2green;
				document.getElementById("led2blue").value=led2blue;
				document.getElementById("led3red").value=led3red;
				document.getElementById("led3green").value=led3green;
				document.getElementById("led3blue").value=led3blue;
			}
		</script>
	</head>
	
	<body>
		<h2>Joe Pacura's Quest Project</h2>
		<h2>for AP Computer Science</h2>
		<hr />
		
		<h2>LED STATUS:</h2>
		
		<div id="led1color"></div>
		<div id="led2color"></div>
		<div id="led3color"></div>
		<br style="clear:both" />
		
		<h2>LED CONTROLS:</h2>
		
		<form name="controls" method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
			<div id="led1control" class="controlbox">
				<p>LED 1:</p>
				
				<input type="text" id="led1red" name="led1red" size=3 value="0"> RED<br />
				<input type="text" id="led1green" name="led1green" size=3 value="0"> GREEN<br />
				<input type="text" id="led1blue" name="led1blue" size=3 value="0"> BLUE<br />
			</div>
			
			<div id="led2control" class="controlbox">
				<p>LED 2:</p>
				
				<input type="text" id="led2red" name="led2red" size=3 value="0"> RED<br />
				<input type="text" id="led2green" name="led2green" size=3 value="0"> GREEN<br />
				<input type="text" id="led2blue" name="led2blue" size=3 value="0"> BLUE<br />
			</div>
			
			<div id="led3control" class="controlbox">
				<p>LED 3:</p>
				
				<input type="text" id="led3red" name="led3red" size=3 value="0"> RED<br />
				<input type="text" id="led3green" name="led3green" size=3 value="0"> GREEN<br />
				<input type="text" id="led3blue" name="led3blue" size=3 value="0"> BLUE<br />
			</div>
			
			<br style="clear:both" /><br />
			<input type="submit" value="Modify LEDs" />
		</form>
		
		<script>changeScreenColors();</script>
		<script>selectCurrentValues();</script>
	</body>
</html>
