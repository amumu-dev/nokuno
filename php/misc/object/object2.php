<?php
class Test {
	public $member0;
	public $member1;
	public $member2;
	public $member3;
	function __construct($i) {
		$this->member0 = $i;
		$this->member1 = $i+1;
		$this->member2 = $i+2;
		$this->member3 = $i+3;
	}
}
for($i=0;$i<1000000;$i++) {
	$result[] = new Test($i);
}
echo 'Memory: '.memory_get_usage()."\n";
?>

