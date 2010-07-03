<?php
$file = $_REQUEST['file'];
$text = $_REQUEST['text'];
if (get_magic_quotes_gpc()) {
  $text = stripslashes($text);
}
if(isset($file) && isset($text)) {
  if( preg_match('/[^0-9a-zA-Z]/', $file ) ) {
    $message = "error: {$file} is invalid file name.";
  } else {
    $fp = fopen("./data/".$file,"w");
    fwrite($fp, $text);
    fclose($fp);
    $message = "OK: file {$file} is written.";
  }
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body>
<h2>Text uploader using only GET request</h2>
<p><?php echo htmlspecialchars($message);?></p>
<p><a href="data/">file list</a></p>
<form method="GET" action="./">
<p>
file name:<br>
<input type="text" name="file">
</p>
<p>
text:<br>
<textarea name="text" cols="100" rows="40"></textarea>
</p>
<input type="submit" value="write">
</form>
<p>
direct use:<br>
http://nokuno.shisobu.in/text/?file=filename&amp;text=databody
</p>
</body>
</html>
