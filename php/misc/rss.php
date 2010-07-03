<?php
foreach($argv as $key=>$val) {
	if($key!=0) {
		print_r( simplexml_load_file($val) );
	}
}
?>

