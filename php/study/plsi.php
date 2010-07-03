<?php
$num_iter = 10;
$beta = 1.0;
$num_cluster = 3;

$vectors = read_vectors();
$documents = array();
foreach($vectors as $v) {
  $documents[] = $v['vector'];
}
list($pdz, $pwz, $pz) = plsi($documents, $num_cluster, $num_iter, $beta);
for ($i = 0; $i < count($pdz); $i++) {
  print $vectors[$i]['id']."\t";
  foreach( $pdz[$i] as $val ) {
    printf( "%.4f ", $val );
  }
  print "\n";
}
/*
print_r($pdz);
print_r($pwz);
print_r($pz);
 */

# Format: id\tval1,val2,val3,...
function read_vectors() {
  $vectors = array();
  while ($line = fgets(STDIN)) {
    $line = trim($line);
    if(empty($line)) {
      continue;
    }
    list($id, $vecstr) = mb_split("\t", $line);
    if (!$id || !$vecstr) {
      echo "Illegal format: $line\n";
    }
    $vector = mb_split(",", $vecstr);
    $vectors[] = array(
      'id'     => $id,
      'vector' => $vector,
    );
  }
  return $vectors;
}
function init_random($nrow, $ncol) {
  $results = array();
  for( $i=0; $i < $nrow; $i++) {
    $arr = array();
    $sum = 0;
    for( $j=0; $j < $ncol; $j++) {
      $r = rand();
      $arr[] = $r;
      $sum += $r;
    }
    foreach($arr as $key=>$val) {
      $arr[$key] = $val / $sum;
    }
    $results[] = $arr;
  }
  return $results;
}
function expect($pdz, $pwz, $pz, $num_doc, $num_word, $num_cluster, $beta) {
  $scores = array();
  for($id = 0; $id < $num_doc; $id++) {
    for($iw = 0; $iw < $num_word; $iw++) {
      $denominator = 0;
      for( $iz = 0; $iz < $num_cluster; $iz++) {
        $denominator += $pz[$iz] *
          ($pwz[$iw][$iz] * $pdz[$id][$iz]) * $beta;
      }
      for( $iz = 0; $iz < $num_cluster; $iz++) {
        $numerator = $pz[$iz] *
          ($pwz[$iw][$iz] * $pdz[$id][$iz]) * $beta;
        $scores[$id][$iw][$iz] = $denominator ?
          $numerator / $denominator : 0;
      }
    }
  }
  return $scores;
}
function plsi($documents, $num_cluster, $num_iter, $beta) {
  $num_doc = count($documents);
  $num_word = count($documents[0]);
  $pdz = init_random($num_doc, $num_cluster);
  $pwz = init_random($num_word, $num_cluster);
  $pz = array();
  for($i = 0; $i < $num_cluster; $i++) {
    $pz[$i] = 1/$num_cluster;
  }

  for ($i = 0; $i < $num_iter; $i++) {
    $scores = expect( $pdz, $pwz, $pz, $num_doc, $num_word, $num_cluster, $beta);
    list($pdz, $pwz, $pz) = maximize($scores, $documents, $pdz, $pwz, $pz, $num_doc, $num_word, $num_cluster);
  }
  return array($pdz, $pwz, $pz);
}

function maximize($scores, $documents, $pdz, $pwz, $pz, $num_doc, $num_word, $num_cluster) {
  $pdz_new = array();
  $pwz_new = array();
  $pz_new = array();

  $denominators = array();
  $sum_denom = 0;
  for($iz = 0; $iz < $num_cluster; $iz++) {
    $denominator = 0;
    for ($id = 0; $id < $num_doc; $id++) {
      for ($iw = 0; $iw < $num_word; $iw++) {
        $denominator += $documents[$id][$iw] * $scores[$id][$iw][$iz];
      }
    }
    $denominators[] = $denominator;

    # update pdz
    for ($id = 0; $id < $num_doc; $id++) {
      $numerator = 0;
      for ($iw = 0; $iw < $num_word; $iw++) {
        $numerator += $documents[$id][$iw] * $scores[$id][$iw][$iz];
      }
      $pdz_new[$id][$iz] = $numerator / $denominator;
    }
    # update pwz
    for ($iw = 0; $iw < $num_word; $iw++) {
      $numerator = 0;
      for ($id = 0; $id < $num_doc; $id++) {
        $numerator += $documents[$id][$iw] * $scores[$id][$iw][$iz];
      }
      $pwz_new[$iw][$iz] = $numerator / $denominator;
    }

  }
  # update pz
  $denom_sum = 0;
  foreach( $denominators as $val ) {
    $denom_sum += $val;
  }
  for ($iz = 0; $iz < $num_cluster; $iz++) {
    $pz_new[$iz] = $denominators[$iz] / $denom_sum;
  }
  return array($pdz_new, $pwz_new, $pz_new);
}
?>
