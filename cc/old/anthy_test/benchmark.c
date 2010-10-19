#include <stdlib.h>
#include <stdio.h>
#include <anthy/anthy.h>

anthy_context_t ac;
struct anthy_conv_stat cs;
int i,j,k;

int main(int argc,char **argv){
	if(anthy_init()) {
		printf("anthy_init() is failed.\n");
		return 1;
	}
	anthy_set_personality("");
	ac = anthy_create_context();
	if(!ac) {
		printf("anthy_create_context() is failed.\n");
		return 1;
	}
	//準備完了！
	for(k=0; k<1000; k++){
	  anthy_set_string(ac, "わたしのなまえはおくのです。");
	  //anthy_commit_segment(ac);
	  anthy_get_stat(ac, &cs);
	  //printf("segment:%d\n",cs.nr_segment);
	  for(i=0; i<cs.nr_segment; i++){
	    struct anthy_segment_stat ss;
	    anthy_get_segment_stat(ac,i,&ss);
	    //printf("can:%d,len:%d |", ss.nr_candidate, ss.seg_len);
	    for(j=0; j<ss.nr_candidate; j++){
	      char buffer[256];
	      anthy_get_segment(ac,i,j,buffer,256);
	      //printf(" %s ", buffer);
	    }
	    //printf("\n");
	  }
	  //printf("\n");
	  //anthy_print_context(ac);
	}
	anthy_release_context(ac);
	anthy_quit();
	return 0;
}
