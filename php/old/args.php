<?php
//���ޥ�ɥ饤��ξ��
if(isset($argv)) {
	array_shift($argv);
	$args = implode( "&", $argv);
	parse_str( $args, $_REQUEST);
}
print_r($_REQUEST);
?>
