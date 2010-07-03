<?php
if ($argc < 3) {
    echo "php stream.php user password\n";
    return;
}
$user = $argv[1];
$password = $argv[2];
while (true) {
    $stream = fopen("http://{$user}:{$password}@stream.twitter.com/1/statuses/sample.json", "r");
    while ($json = fgets($stream )) {
        echo preg_replace("/\n/","",$json)."\n";
    }
    fclose($stream);
    sleep(60);
}
