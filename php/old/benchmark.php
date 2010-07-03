<?php
	$start = microtime(true);
	for($i=0;$i<10;$i++) {
		$t1 = microtime(true);
		$fp = fsockopen("social-ime.com",110);
		fwrite($fp,"CONVERT ‚ ‚ ‚ \n\n");
		$result =  fgets($fp);
		fwrite($fp,"CANCEL\n\n");
		fclose($fp);
		$t2 = microtime(true);
		echo "time:".($t2-$t1)."\n";
		//echo "result:".$result;
	}
	$end = microtime(true);
	echo "total:".($end-$start)."\n";
?>
