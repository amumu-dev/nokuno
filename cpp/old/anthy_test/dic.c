#include <stdlib.h>
#include <stdio.h>
#include <anthy/anthy.h>
#include <anthy/dicutil.h>

int i,j;

int main(int argc,char **argv){
	anthy_dic_util_init();
	//anthy_dic_util_set_personality("default");
	//printf("anthydir:%s\n", anthy_dic_util_get_anthydir());
	//anthy_priv_dic_delete();
	//int first = anthy_priv_dic_select_first_entry();
	//int next = anthy_priv_dic_select_next_entry();
	
	if( anthy_priv_dic_add_entry("ふじょし", "腐女子", "#T35", 500) == -1 )
		printf("failed\n");
	anthy_dic_util_quit();
	return 0;
}
