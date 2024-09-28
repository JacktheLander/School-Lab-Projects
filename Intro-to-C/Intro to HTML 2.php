<html>
<body>
<h1>Page 2</h1>
<?php
	$a = $_POST["a"];
	$b = $_POST["b"];
	$c = $_POST["c"];
	$d = $_POST["d"];
	$e = $_POST["e"];
	$guesses = [$a, $b, $c, $d, $e];

	for($i=0; $i<5; $i++){
		$randoms[$i] = rand(1,20);
		for($j=$i-1; $j>=0; $j--){
			if($randoms[$i]==$randoms[$j]){
				$i--;
				break;}
		}
	}
	$count = 0;
	for($k=0; $k<5; $k++){
		for($l=0; $l<5; $l++){
			if($randoms[$k]==$guesses[$l]){
				$count ++;}
		}
	}
	echo $count;
	echo " guesses match the randoms!";
?>
<form action="lab4.php" method = "POST">
	<input type = "submit" value = "Play again?"/>
</form>


<body>
<html>

