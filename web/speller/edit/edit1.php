<?php
if (isset($_GET['q'])) {
    header("Content-Type: text/plain");
    $query = $_GET['q'];
} else if ($argc >= 2) {
    $query = $argv[1];
} else {
    $query = "cofee";
}
echo "$query\t1\n";

$alphabet = array(" ");
for ($i = 0; $i < 26; $i++) {
    $alphabet[] = chr(ord("a") + $i);
}
for ($i = 0; $i < strlen($query); $i++) {
    //replace
    $cand = $query;
    foreach($alphabet as $char) {
        $cand[$i] = $char;
        echo "$cand\t0\n";
    }
    //insert
    foreach($alphabet as $char) {
        $cand = substr($query, 0, $i) . $char . substr($query, $i);
        echo "$cand\t0\n";
    }
    //delete
    $cand = substr($query, 0, $i) . substr($query, $i+1);
    echo "$cand\t0\n";
}
