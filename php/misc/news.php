<?php
require_once 'Services/Yahoo/JP/News.php';

try {
    $yahoo = Services_Yahoo_JP_News::factory('topics');
    // あなたのAppIDをセットしてください
    $yahoo->withAppID('PEAR_Services_Y_JP');
    $yahoo->setWord('サッカー');

    $result = $yahoo->submit();

    foreach ($result as $entry) {
        print('Title : ' . $entry['topicname'] .
                ' : URL : ' . $entry['url'] . "\n");
    }
} catch (Services_Yahoo_Exception $e) {
    echo('Error.');
}
?>
