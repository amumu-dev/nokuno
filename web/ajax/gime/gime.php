<?php 
$base = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text=";
$query = $_GET['q'];
$url = $base.$query;
$result = file_get_contents($url);
$object = json_decode($result, true);
echo $object;
