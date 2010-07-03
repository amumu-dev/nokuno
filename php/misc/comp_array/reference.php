<?php
for($i=0;$i<1000;$i++){
	ref($arg);
}
function ref(&$arg){
	$arg = range(0,100000);
}
