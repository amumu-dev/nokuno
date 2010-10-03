<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Googleかな漢字変換APIのテスト</title>
<style>
.nokuno {
    border-top: 1px solid #ccc;
    border-left: 1px solid #ccc;
}

.nokuno td {
    padding: 3px 8px;
    border-bottom: 1px solid #ccc;
    border-right: 1px solid #ccc;
}
</style>
</head>
<body>
<h1><a href="./">Googleかな漢字変換APIのテスト</a></h1>
<p>
<a href="http://www.google.com/intl/ja/ime/cgiapi.html">Google CGI API for Japanese Input</a>のテストです。
以下のフォームに入力してください。
</p>
<form>
<input type="text" name="query" value="<?php echo $_GET['query'];?>"/>
<input type="submit" value="変換">
</form> 
<?php
if (isset($_GET['query'])) {
    $query = $_GET['query'];
    $result = `./fetch.py -q $query`;
    $lines = explode("\n", $result);
    echo "<table class='nokuno' cellpadding='0' cellspacing='0'>";
    foreach($lines as $line) {
        if(strlen($line) == 0) continue;
        echo "<tr>";
        $items = explode("\t", $line);
        foreach($items as $item) {
            echo "<td>$item</td>";
        }
        echo "</tr>\n";
    }
    echo "</table>";
}
?>
</body>
</html>
