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
<table border="1">
<tr>
<td>
<?php
echo $_GET['query'];
?>
</td>
</tr>
</table>
</body>
</html>
