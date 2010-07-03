<?php
function my_http_get($url) {
	$h=fopen($url,'r');
	$meta_data=stream_get_meta_data($h); // both PHP4, PHP5 OK
	$headers=$meta_data['wrapper_data'];
	$result['content']=stream_get_contents($h); // only PHP5, you need write the function for PHP4
	fclose($h);
	if (preg_match('/^HTTP\/([0-9]\.[0-9]) ([0-9]+)/',$headers[0],$matches)) {
		$result['response']=$matches[2];
	}
	return $result;
}
$input = ($argc>1) ? $argv[1] : "¥Æ¥¹¥È";
$kana = urlencode(mb_convert_encoding($input,"UTF-8"));
my_http_get("http://frec.hbbox.net/LimeServer/?uid=guest&cmd=addwords&words=$kana");
?>
