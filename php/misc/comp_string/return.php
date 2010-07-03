<?php
for($i=0;$i<1000;$i++){
	$result = func();
}
function func(){
	return str_repeat( "あいうえお", 1000000);
}
