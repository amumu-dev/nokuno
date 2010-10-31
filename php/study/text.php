<?php
$file = $_REQUEST['file'];
$text = $_REQUEST['text'];
if (get_magic_quotes_gpc()) {
    $text = stripslashes($text);
}
if(isset($file) && isset($text)) {
    $fp = fopen("./data/".$file,"w");
    fwrite($fp, $text);
    fclose($fp);
}
