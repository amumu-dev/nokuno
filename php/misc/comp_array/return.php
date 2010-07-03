<?php
for($i=0;$i<1000;$i++){
	$result = func();
}
function func(){
	return range(0,100000);
}
