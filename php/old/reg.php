<?php
mb_ereg("<td>[あ-ん]*<\/td>","<td>あ</td>\n<td>あいう</td>",$furigana);
for ($i=0; $i<count($furigana); $i+=1) {
	print $furigana[$i]."\n";
}
?>
