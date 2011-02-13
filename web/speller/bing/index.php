<?php
if (isset($_GET['q'])) {
    header("Content-Type: text/plain");
    $query = $_GET['q'];
} else if ($argc >= 2) {
    $query = $argv[1];
} else {
    $query = "cofee";
}
//$appid = "5061CD1C64F6015A128E51FE1FDFDC3B18D0610A";
$appid = "F123BC971CAF06D542CA8AFE5AD589CA77F7F36A";
$base = "http://api.search.live.net/xml.aspx";
$ns = "http://schemas.microsoft.com/LiveSearch/2008/04/XML/spell";
$url = "$base?Appid=$appid&sources=spell&query=$query";
$xml = simplexml_load_file($url);
$xml->registerXPathNamespace('spl', $ns);
//print_r($xml);
$values = $xml->xpath('//spl:Value');
$values[] = $query;
if (count($values) > 0) {
    $prob = 1.0 / count($values);
    foreach ($values as $value) {
        echo "$value\t$prob";
    }
} else {
    echo "$query\t1.0\n";
}
