<?php
$query = parse_option($argv);
if (isset($query)) {
    spell($query, 'standard');
} else {
    foreach (file('php://stdin') as $line) {
        $count = 0;
        $query = explode("\t", $line);
        output($query[0], 0, 'count');
        spell($query[0], 'count');
        echo "$count\n";
    }
}

// parse options
function parse_option($argv) {
    if (isset($_GET['q'])) {
        header("Content-Type: text/plain");
        $query = $_GET['q'];
    } else if (count($argv) >= 2) {
        $query = $argv[1];
    }
    return $query;
}
// spell correction
function spell($query, $format) {
    $start = time();

    // 1-best
    output($query, 1, $format);

    //alphabet
    $alphabet = array(" ");
    for ($i = 0; $i < 26; $i++) {
        $alphabet[] = chr(ord("a") + $i);
    }
    //edit 1
    foreach (edit($query, $alphabet) as $x) {
        output($x, 0, $format);
    }
    //edit 2
    foreach (edit($query, $alphabet) as $x) {
        foreach (edit($x, $alphabet) as $y) {
            output($y, 0, $format);
        }
        $now = time();
        if ($now - $start > 50) {
            break;
        }
    }
}
// edit operation
function edit($input, $alphabet) {
    $result = array();
    for ($i = 0; $i < strlen($input); $i++) {
        //replace
        $cand = $input;
        foreach($alphabet as $char) {
            $cand[$i] = $char;
            $result[] = $cand;
        }
        //insert
        foreach($alphabet as $char) {
            $cand = substr($input, 0, $i) . $char . substr($input, $i);
            $result[] = $cand;
        }
        //delete
        $cand = substr($input, 0, $i) . substr($input, $i+1);
        $result[] = $cand;

        //transpose
        $cand = $input;
        list($cand[$i], $cand[$i+1]) = array($cand[$i+1], $cand[$i]);
        $result[] = $cand;
    }
    return $result;
}
// output result
function output($query, $prob, $format) {
    global $count;
    if ($format == "standard") {
        echo "$query\t$prob\n";
    } else if ($format == "local") {
        echo "$query\t";
    } else if ($format == "count") {
        $count++;
    }
}
