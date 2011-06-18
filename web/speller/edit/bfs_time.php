<?php
$query = parse_option($argv);
if (isset($query)) {
    bfs($query, 'standard');
} else {
    $precision_sum = 0.0;
    $recall_sum = 0.0;
    $count = 0;
    foreach (file('php://stdin') as $line) {
        $query = explode("\t", $line);
        $answer = array_fill_keys(array_slice($query, 1), false);
        bfs($query[0], 'eval');
        $count ++;
    }
    // output evaluate
    print "P: $precision_sum\n";
    print "R: $recall_sum\n";
    print "C: $count\n";
    $ep = $precision_sum / $count;
    $er = $recall_sum / $count;

    print "EP: $ep\n";
    print "ER: $er\n";

    $ef1 = 1.0/(0.5*(1.0/$ep+1.0/$er));
    print "EF1: $ef1\n";
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
// breath first spell generation
function bfs($input, $format) {
    $start = time();
    //alphabet
    $alphabet = array(" ");
    for ($i = 0; $i < 26; $i++) {
        $alphabet[] = chr(ord("a") + $i);
    }

    // output 1-best
    output($input, 1, $format);

    // queue
    $queue = array($input);

    // breath first
    while (count($queue) > 0) {
        $candidate = array_shift($queue);
        foreach (edit($candidate, $alphabet) as $cand) {
            output($cand, 0, $format);
            array_push($queue, $cand);
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
    if ($format == "standard") {
        echo "$query\t$prob\n";
    } else if ($format == "local") {
        echo "$query\t";
    } else if ($format == "eval") {
        global $answer, $precision_sum, $recall_sum;
        if (isset($answer[$query]) && $answer[$query] === false) {
            $answer[$query] = true;
            $precision_sum += $prob;
            $recall_sum += 1.0 / count($answer);
        }
    }
}
