<?php
	
	// アクセスする URL
	$url = 'http://www.social-ime.com/';

	// 1. 初期化
	$ch = curl_init();

	// 2. アクセスする URL を設定
	curl_setopt($ch, CURLOPT_URL, $url);

	// 3. curl_exec を実行したときに戻り値として成功(TRUE)/失敗(FALSE)ではなく、
	//    HTMLなどの値(文字列)を返すようにする
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

	// 4. サイトにアクセスする
	$data = curl_exec($ch);

	// 5. 結果を表示する
	print $data;

	// 6. 接続を閉じる
	curl_close($ch);

?> 
