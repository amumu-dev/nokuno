<?php
// データベースに接続し、選択する
$link = mysql_connect('localhost', 'mysql')
    or die('Could not connect: ' . mysql_error());
echo 'Connected successfully';
mysql_select_db('test') or die('Could not select database');

// SQL クエリを実行する
$query = 'SELECT * FROM words';
$result = mysql_query($query) or die('Query failed: ' . mysql_error());

// HTML に結果を出力する
echo "<table>\n";
while ($line = mysql_fetch_array($result, MYSQL_ASSOC)) {
    echo "\t<tr>\n";
    foreach ($line as $col_value) {
        echo "\t\t<td>$col_value</td>\n";
    }
    echo "\t</tr>\n";
}
echo "</table>\n";

// 結果セットを開放する
mysql_free_result($result);

// 接続を閉じる
mysql_close($link);
?>
