<?php
	
	// ������������ URL
	$url = 'http://www.social-ime.com/';

	// 1. �����
	$ch = curl_init();

	// 2. ������������ URL ������
	curl_setopt($ch, CURLOPT_URL, $url);

	// 3. curl_exec ��¹Ԥ����Ȥ�������ͤȤ�������(TRUE)/����(FALSE)�ǤϤʤ���
	//    HTML�ʤɤ���(ʸ����)���֤��褦�ˤ���
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

	// 4. �����Ȥ˥�����������
	$data = curl_exec($ch);

	// 5. ��̤�ɽ������
	print $data;

	// 6. ��³���Ĥ���
	curl_close($ch);

?> 
