<?php
print "hash:".myhash('256',2009)."\n";
print "hash:".myhash('255',2009)."\n";
function myhash($key, $backet) {
	$result = 751;
	for( $i = 0; $i < mb_strlen($key); $i++ ) {
		print $key[$i]."\n";
		$result = $result * 37 + (int)$key[$i];
	}
	return $result % $backet;
}
?>
