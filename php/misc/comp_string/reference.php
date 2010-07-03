<?php
for($i=0;$i<1000;$i++){
	ref($arg);
}
function ref(&$arg){
	$arg = str_repeat( "あいうえお", 1000000);
}
