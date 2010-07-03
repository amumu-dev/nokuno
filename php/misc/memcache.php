<?php
$memcache = new Memcache;
$memcache->connect('localhost', 11211) or die ("Could not connect");

for ($i = 0; $i < 10; $i++) {
    $memcache->set("key$i", "value$i");
}
$items = $memcache->getStats('items');
foreach( $items['items'] as $key => $item ){
    $number = $item['number'];
    $dump = $memcache->getStats('cachedump', $key, $number*2);
    foreach( $dump as $ckey => $carr ){
        $value = $memcache->get($ckey);
        echo "$ckey\t$value\n";
    }
}
