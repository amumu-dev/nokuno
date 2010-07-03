<?php
while ($json = fgets(STDIN)) {
    $twitter = json_decode($json, true);
    if(preg_match('/[ァ-ヶーぁ-ん]/u',$twitter['text']))
    echo $twitter['user']['name'].':'.$twitter['text'] . PHP_EOL;
}
