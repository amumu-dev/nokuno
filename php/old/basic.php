<?php
	$header = "";
	$input = ($argc>1) ? $argv[1] : "�ƥ���";
	$post = array("status"=>mb_convert_encoding($input,"UTF-8"));
	http("http://social_ime:nokunokuno@twitter.com/statuses/update.xml","POST","",$post);
	/*
	$url     : http://����Ϥޤ�URL( http://user:pass@host:port/path?query )
	$method  : GET, POST, HEAD�Τ����줫(�ǥե���Ȥ�GET)
	$headers : Ǥ�դ��ɲåإå�
	$post    : POST�λ�����������ǡ������Ǽ��������("�ѿ�̾"=>"��")
	*/
	function http($url, $method="GET", $headers="", $post=array(""))
	{
		/* URL��ʬ�� */
		$URL = parse_url($url);

		/* �����꡼ */
		if (isset($URL['query'])) {
			    $URL['query'] = "?".$URL['query'];
		} else {
			    $URL['query'] = "";
		}

		/* �ǥե���ȤΥݡ��Ȥ�80 */
		if (!isset($URL['port'])) $URL['port'] = 80;

		/* �ꥯ�����ȥ饤�� */
		$request  = $method." ".$URL['path'].$URL['query']." HTTP/1.0\r\n";

		/* �ꥯ�����ȥإå� */
		$request .= "Host: ".$URL['host']."\r\n";
		$request .= "User-Agent: PHP/".phpversion()."\r\n";

		/* Basicǧ���ѤΥإå� */
		if (isset($URL['user']) && isset($URL['pass'])) {
			    $request .= "Authorization: Basic ".base64_encode($URL['user'].":".$URL['pass'])."\r\n";
		}

		/* �ɲåإå� */
		$request .= $headers;

		/* POST�λ��ϥإå����ɲä���������URL���󥳡��ɤ����ǡ�����ź�� */
		if (strtoupper($method) == "POST") {
			    while (list($name, $value) = each($post)) {
				            $POST[] = $name."=".urlencode($value);
					        }
						    $postdata = implode("&", $POST);
						        $request .= "Content-Type: application/x-www-form-urlencoded\r\n";
							    $request .= "Content-Length: ".strlen($postdata)."\r\n";
							        $request .= "\r\n";
								    $request .= $postdata;
		} else {
			    $request .= "\r\n";
		}

		/* WEB�����Ф���³ */
		$fp = fsockopen($URL['host'], $URL['port']);

		/* ��³�˼��Ԥ������ν��� */
		if (!$fp) {
			    die("ERROR\n");
		}

		/* �׵�ǡ������� */
		fputs($fp, $request);

		/* �����ǡ������� */
		$response = "";
		while (!feof($fp)) {
			    $response .= fgets($fp, 4096);
		}

		/* ��³��λ */
		fclose($fp);

		/* �إå���ʬ�ȥܥǥ���ʬ��ʬΥ */
		$DATA = split("\r\n\r\n", $response, 2);

		/* �ꥯ�����ȥإå��򥳥��ȥ����Ȥ��ƽ��� */
		echo "<!--\n".$request."\n-->\n";

		/* �쥹�ݥ󥹥إå��򥳥��ȥ����Ȥ��ƽ��� */
		echo "<!--\n".$DATA[0]."\n-->\n";

		/* ��å������ܥǥ������ */
		echo $DATA[1];
	}
?>

