<?php
	$header = "";
	$input = ($argc>1) ? $argv[1] : "テスト";
	$post = array("status"=>mb_convert_encoding($input,"UTF-8"));
	http("http://social_ime:nokunokuno@twitter.com/statuses/update.xml","POST","",$post);
	/*
	$url     : http://から始まるURL( http://user:pass@host:port/path?query )
	$method  : GET, POST, HEADのいずれか(デフォルトはGET)
	$headers : 任意の追加ヘッダ
	$post    : POSTの時に送信するデータを格納した配列("変数名"=>"値")
	*/
	function http($url, $method="GET", $headers="", $post=array(""))
	{
		/* URLを分解 */
		$URL = parse_url($url);

		/* クエリー */
		if (isset($URL['query'])) {
			    $URL['query'] = "?".$URL['query'];
		} else {
			    $URL['query'] = "";
		}

		/* デフォルトのポートは80 */
		if (!isset($URL['port'])) $URL['port'] = 80;

		/* リクエストライン */
		$request  = $method." ".$URL['path'].$URL['query']." HTTP/1.0\r\n";

		/* リクエストヘッダ */
		$request .= "Host: ".$URL['host']."\r\n";
		$request .= "User-Agent: PHP/".phpversion()."\r\n";

		/* Basic認証用のヘッダ */
		if (isset($URL['user']) && isset($URL['pass'])) {
			    $request .= "Authorization: Basic ".base64_encode($URL['user'].":".$URL['pass'])."\r\n";
		}

		/* 追加ヘッダ */
		$request .= $headers;

		/* POSTの時はヘッダを追加して末尾にURLエンコードしたデータを添付 */
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

		/* WEBサーバへ接続 */
		$fp = fsockopen($URL['host'], $URL['port']);

		/* 接続に失敗した時の処理 */
		if (!$fp) {
			    die("ERROR\n");
		}

		/* 要求データ送信 */
		fputs($fp, $request);

		/* 応答データ受信 */
		$response = "";
		while (!feof($fp)) {
			    $response .= fgets($fp, 4096);
		}

		/* 接続を終了 */
		fclose($fp);

		/* ヘッダ部分とボディ部分を分離 */
		$DATA = split("\r\n\r\n", $response, 2);

		/* リクエストヘッダをコメントアウトして出力 */
		echo "<!--\n".$request."\n-->\n";

		/* レスポンスヘッダをコメントアウトして出力 */
		echo "<!--\n".$DATA[0]."\n-->\n";

		/* メッセージボディを出力 */
		echo $DATA[1];
	}
?>

