<?php
if (!isset($argc)) {
    header("Content-Type: text/plain");
    $query = $_GET['q'];
} if ($argc < 2) {
    $query = "cofee";
} else {
    $query = $argv[1];
}
$appid = "5061CD1C64F6015A128E51FE1FDFDC3B18D0610A";
$base = "http://api.search.live.net/xml.aspx";
$ns = "http://schemas.microsoft.com/LiveSearch/2008/04/XML/spell";
$url = "$base?Appid=$appid&sources=spell&query=$query";
$xml = simplexml_load_file($url);
$xml->registerXPathNamespace('spl', $ns);
//print_r($xml);
$values = $xml->xpath('//spl:Value');
if (count($values) > 0) {
    $prob = 1.0 / count($values);
    foreach ($values as $value) {
        echo "$value\t$prob";
    }
} else {
    echo "$query\t\n";
}
