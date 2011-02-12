<?php
header("Content-Type: text/plain");
$query = $_GET['q'];

$dataset = file("dataset.txt");
$dictionary = array();
foreach ($dataset as $line) {
    $keyvalue = explode("\t", trim($line), 2); 
    $dictionary[$keyvalue[0]] = $keyvalue[1];
}
if (array_key_exists($query, $dictionary)) {
    $candidates = explode("\t", $dictionary[$query]);
    $prob = 1.0 / count($candidates);
    foreach ($candidates as $cand) {
        echo "$cand\t$prob\n";
    }
} else {
    echo "$query\t1.0\n";
}
