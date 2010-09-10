<?php
$file = stream_get_contents(STDIN);
$compressed = gzcompress($file); 
echo 'before :'.strlen($file)."\n";
echo 'after :'.strlen($compressed)."\n";
echo 'before(urlencode) :'.strlen(urlencode($file))."\n";
echo 'after(urlencode) :'.strlen(urlencode($compressed))."\n";
//echo gzuncompress($compressed);

