<?php
class Test {
	public $member0 = 0;
	public $member1 = 1;
	public $member2 = 2;
	public $member3 = 3;
}
for($i=0;$i<1000000;$i++) {
	$result[] = new Test();
}
echo 'Memory: '.memory_get_usage()."\n";
?>

