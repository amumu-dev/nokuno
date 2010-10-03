<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Googleかな漢字変換APIのテスト</title>
</head>
<body>
<h1>Googleかな漢字変換APIのテスト</h1>
<p>
<a href="http://www.google.com/intl/ja/ime/cgiapi.html">Google CGI API for Japanese Input</a>のテストです。
以下のフォームに入力してください。
</p>
<form>
<input type="text" name="query"/>
<input type="submit" value="変換">
</form> 
<?php
if (isset($_GET['query'])) {
    $query = $_GET['query'];
    $result = `./fetch.py -q $query`;
    $lines = explode("\n", $result);
    echo "<table border='1'>";
    foreach($lines as $line) {
        if(strlen($line) == 0) continue;
        echo "<tr>";
        $items = explode("\t", $line);
        foreach($items as $item) {
            echo "<td>$item</td>";
        }
        echo "</tr>";
    }
    echo "</table>";
}
?>
</body>
</html>
