<?php
while ($json = fgets(STDIN)) {
    $twitter = json_decode($json, true);
    if(preg_match('/[ァ-ヶーぁ-ん]/u',$twitter['text']))
        echo $json;
}
