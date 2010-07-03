<?php
function do_post_request($url, $data, $optional_headers = null)
{
	$params = array('http' => array(  
		'method' => 'POST',  
		'content' => $data  
	));  
	if ($optional_headers !== null) { 
		$params['http']['header'] = $optional_headers;  
	} 
	$ctx = stream_context_create($params); 
	$fp = fopen($url, 'rb', false, $ctx);  
	if (!$fp) { 
		throw new Exception("Problem with $url, $php_errormsg"); 
	} 
	$response = stream_get_contents($fp); 
	if ($response === false) { 
		throw new Exception("Problem reading data from $url, 
		$php_errormsg"); 
	} 
	return $response;
}
//投稿する文字列
$input = ($argc>1) ? $argv[1] : "テスト";
$post = urlencode(mb_convert_encoding("status=".$input."\r\n","UTF-8"));
//Basic認証用のヘッダ
$header = "Authorization: Basic ".base64_encode("nokunokuno@gmail.com:nokunokuno")."\r\n";
//ポスト
$result = do_post_request("http://twitter.com/statuses/update.xml", $post, $header);
print $result['content'];
print $result['response'];
?>
