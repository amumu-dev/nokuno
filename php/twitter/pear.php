<?php
require_once "Services/Twitter.php";

$user = 'socialime';
$pass = 'nokunokuno';

$st =& new Services_Twitter($user, $pass);
$st->setAppName('Social IME for Twitter');
$st->setUpdate('APIテスト');
?>
