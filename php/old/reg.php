<?php
mb_ereg("<td>[��-��]*<\/td>","<td>��</td>\n<td>������</td>",$furigana);
for ($i=0; $i<count($furigana); $i+=1) {
	print $furigana[$i]."\n";
}
?>
