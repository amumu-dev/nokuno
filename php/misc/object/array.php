<?php
$result = array();
for($i=0;$i<1000000;$i++) {
	$result[] = array('member0'=>0,'member1'=>1,'member2'=>2,'member3'=>3);
}
echo 'Memory: '.memory_get_usage()."\n";
?>

