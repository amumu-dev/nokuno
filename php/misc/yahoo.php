<?php
if (isset($argv) && realpath($argv[0]) == realpath(__FILE__)) {
    print getFreq('未踏');
}
function getFreq($query) {
    $appid = 'u4LdhVaxg65V6WltXWPCAvXZExdsAPTYUMT0VxYU4bADHlr.AUSdfl7wVLF5hB3b';
    $query = urlencode($query);
    $url = "http://search.yahooapis.jp/WebSearchService/V1/webSearch?appid=$appid&query=$query&results=1";
    $result = simplexml_load_file($url);
    return $result['totalResultsAvailable'];
}
?>
