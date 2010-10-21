#include <stdlib.h>
#include <stdio.h>
#include <anthy/anthy.h>

anthy_context_t ac;
struct anthy_conv_stat cs;
int i,j;

int main(int argc,char **argv){
	if(anthy_init()) {
		printf("anthy_init() is failed.\n");
		return 1;
	}
	anthy_set_personality("noname");
	anthy_set_personality("default");
	ac = anthy_create_context();
	anthy_set_reconversion_mode(ac,ANTHY_RECONVERT_AUTO);
	if(!ac) {
		printf("anthy_create_context() is failed.\n");
		return 1;
	}
	//準備完了！
	//anthy_set_string(ac, "にわんご");
	anthy_set_string(ac, "りりかる");
	printf("Version:%s\n",anthy_get_version_string ());
	printf("getenv:%s\n",getenv("ANTHY_HISTORY_FILE"));
	anthy_get_stat(ac, &cs);
//	anthy_commit_segment(ac, 0, 3);	//確定＋学習
/*
	anthy_resize_segment(ac, 0, +1);
	anthy_resize_segment(ac, 0, +1);
	anthy_resize_segment(ac, 0, +1);
*/
	anthy_get_stat(ac, &cs);	//文節数が変化した可能性も
	printf("segment:%d\n",cs.nr_segment);
	for(i=0; i<cs.nr_segment; i++){
		struct anthy_segment_stat ss;
		anthy_get_segment_stat(ac,i,&ss);
		//printf("can:%d,len:%d |", ss.nr_candidate, ss.seg_len);
		for(j=0; j<ss.nr_candidate; j++){
			char buffer[256];
			anthy_get_segment(ac,i,j,buffer,256);
			printf(" %s ", buffer);
		}
		printf("\n");
	}
	printf("\n");
	//anthy_print_context(ac);
	anthy_release_context(ac);
	anthy_quit();
	return 0;
}
