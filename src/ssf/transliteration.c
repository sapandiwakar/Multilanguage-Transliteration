#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<getopt.h>
#include "c_api_v2.h"
#include "preprocessor.h"
#include "wx_utf8_ben.h"
#include "wx_utf8_hin.h"
#include "wx_utf8_kan.h"
#include "wx_utf8_mal.h"
#include "wx_utf8_pan.h"
#include "wx_utf8_tam.h"
#include "wx_utf8_tel.h"
#include "utf8_wx_ben.h"
#include "utf8_wx_hin.h"
#include "utf8_wx_kan.h"
#include "utf8_wx_mal.h"
#include "utf8_wx_pan.h"
#include "utf8_wx_tam.h"
#include "utf8_wx_tel.h"

unsigned char* convert_wx2utf (unsigned char* my_string);
unsigned char* convert_utf2wx (unsigned char* my_string);
char* wx_utf8_tgt(char* word);
void child_hin(node* mynode);
void set_flag (char* argv);
void child_tkn(node* mynode);

static int help_flag=0;

int flag_ben = 0;
int flag_hin = 0;
int flag_kan = 0;
int flag_mal = 0;
int flag_pan = 0;
int flag_tam = 0;
int flag_tel = 0;

char *tgt = NULL; 
int main(int argc ,char *argv[])
{
	char *to_convert = NULL;
        char *mode = NULL;
        char *input_file= NULL;
        char *output_file= NULL;
	int mode_flag = 0;

        int c;

       	while (1)
       	{
        	static struct option long_options[] =
               	{
                	/* These options set a flag. */
                       	{"help", no_argument,       &help_flag, 1},
                       	/* These options don't set a flag.
                       	   We distinguish them by their indices. */
                       	{"tlang",     required_argument, 0, 'd'},
                       	{"to_convert", required_argument, 0, 't'},
                       	{"mode",  required_argument, 0, 'm'},
                       	{"input_file",  required_argument, 0, 'i'},
                       	//{"test",  required_argument, 0, 't'},
                       	{"output_file",    required_argument, 0, 'o'},
                       	{0, 0, 0, 0}
               	};
               	/* getopt_long stores the option index here. */
               	int option_index = 0;

               	c = getopt_long (argc, argv, "d:t:i:o", long_options, &option_index);

               /* Detect the end of the options. */
              	if (c == -1)
               		break;

              	switch (c)
               	{
                       	case 0:
                        	/* If this option set a flag, do nothing else now. */
                               	if (long_options[option_index].flag != 0)
                                	break;
                               	printf ("option %s", long_options[option_index].name);
                               	if (optarg)
                                	printf (" with arg %s", optarg);
                               	printf ("\n");
                               	break;

                       case 'd':
                               tgt=optarg;
                               break;
                       case 't':
                                to_convert=optarg;
				set_flag(to_convert);
                                break;

                       case 'm':
                               mode=optarg;
			       if (!strcmp(mode, "debug")) {
					system("mkdir -p out.tmp");
					mode_flag = 1;
			       } else {
				       mode_flag = 0;
			       }
                               break;
                       case 'i':
                               input_file=optarg;
                               if(input_file==NULL)
                               {
                                       printf("Error: Please specify the input file\n");
                                       exit(0);
                               }
                               break;

                       case 'o':
                               output_file=optarg;
                               if(output_file==NULL)
                               {
                                       printf("Error: Please specify the output file\n");
                                       exit(0);
                               }
                               break;
                       default:
                               abort ();
               }
       }

       if (help_flag)
       {
               printf("MultiLanguage Transliteration (6th July 2009)\n");
               printf("usage: ./transilteration  --tlang=" " [--mode=" "] [--to_convert=" "] --input_file=" " --output_file\n");
               exit(1);
       }

       if (to_convert == NULL) {
	       set_flag("all");
       }
	if (tgt == NULL) {
		printf("Please Specify target language\n");
		exit(1);
	}
	if (input_file == NULL) {
		printf("Please Specify input file\n");
		exit(1);
	}
	if(output_file == NULL) {
		printf("Please Specify output file\n");
		exit(1);
	}

	/* Please keep all the files that you are using have this as the basic code */
	circle *tree;   				// create the doc object
	tree=create_circle(NULL); 			// initialize the datastructure
	read_ssf_from_file(tree,input_file);  		// read from the file into tree
	int sentence=sentences(tree);
	node * temp[sentence]; 				// create the node object to store all the nodes retuned
	int count=0,i,k;  				// count to count the # of sentences or nodes returned
	count=traverse_tree(tree,temp,count); 		// function which returns all the sentence nodes into temp

	for(i=0;i<count;i++) {
		child_hin(temp[i]);
		child_tkn(temp[i]);
	}
	print_tree_to_file(tree, output_file);
	if (mode_flag)
		print_tree_to_file(tree, "out.tmp/converted");

	return 0;
}

void child_hin(node* mynode)
{
        char *root;
        char *cm;
        char *suffix;
        char *name;
        char *head;
	char *utf_root, *utf_cm, *utf_suffix, *utf_head, *utf_name;
	char *wx_root, *wx_cm, *wx_suffix, *wx_head, *wx_name;
	char *tagged_root, *tagged_cm, *tagged_suffix, *tagged_head, *tagged_name;
	list_of_nodes *list;
	int i;
	if (mynode != NULL) {
		if (mynode->OR!=NULL) {
			for (i = 0; i < mynode->OR->fs_count; i ++ ) {
	       		        root = get_attr_val(mynode->OR->fs[i], "root");
	       		        cm = get_attr_val(mynode->OR->fs[i], "cm");
	       		        suffix = get_attr_val(mynode->OR->fs[i], "suffix");
	       		        name = get_attr_val(mynode->OR->fs[i], "name");
	       		        head = get_attr_val(mynode->OR->fs[i], "head");
				if (*root != '\0') {
					if (root[0]  == '@') {
						tagged_root = preprocess(root);
						wx_root = convert_utf2wx(tagged_root);
						utf_root = convert_wx2utf(wx_root);
						update_attr_val_2(mynode->OR->fs[i],"root", utf_root);
					}
				}
				if (*cm != '\0') {
					if (cm[0] == '@') {
						tagged_cm = preprocess(cm);
						wx_cm = convert_utf2wx(tagged_cm);
						utf_cm = convert_wx2utf(wx_cm);						
						update_attr_val_2(mynode->OR->fs[i],"cm", utf_cm);
					}
				}
				if (*suffix != '\0') {
					if (suffix[0] == '@') {
						tagged_suffix = preprocess(suffix);
						wx_suffix = convert_utf2wx(tagged_suffix);
						utf_suffix = convert_wx2utf(wx_suffix);
						update_attr_val_2(mynode->OR->fs[i],"suffix", utf_suffix);
					}
				}
				if (*name != '\0') {
					if (name[0] == '@') {
						tagged_name = preprocess(name);
						wx_name = convert_utf2wx(tagged_name);
						utf_name = convert_wx2utf(wx_name);
						update_attr_val_2(mynode->OR->fs[i],"name", utf_name);
					}
				}
				if (*head != '\0') {
					if (head[0] == '@') {
						tagged_head = preprocess(head);
						wx_head = convert_utf2wx(tagged_head);
						utf_head = convert_wx2utf(wx_head);
						update_attr_val_2(mynode->OR->fs[i],"head", utf_head);
					}
				}
			}
		}
	}

	list = getchildren(mynode);

	for (i = 0; i < list->size; i+=1) {
       		child_hin(list -> l[i]);
        }
}

unsigned char* convert_utf2wx (unsigned char* my_string)
{	
	unsigned char ch;
	unsigned char *converted;
	unsigned char *converted_line = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *converted_line_untagged = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *word = (char *) malloc(strlen(my_string)*6 + 1);
	char tag[4];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	while(*(my_string+i) != '\0') {		
		ch = *(my_string+i);
		if (ch == '~') {			
			j = 0;
			tag[0] = *(my_string+i+1);
			tag[1] = *(my_string+i+1+1);
			tag[2] = *(my_string+i+1+1+1);
			tag[3] = '\0';
			i += 5;
			while (*(my_string+i) != '\0'){
				ch = *(my_string+i);
				if (ch != ' ') {
					sprintf(word+j, "%c", ch);
					j ++;
					i ++;
				} else {
					if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
						converted = utf_wx_ben(word);
					} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
						converted = utf_wx_hin(word);
					} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
						converted = utf_wx_kan(word);
					} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
						converted = utf_wx_pan(word);
					} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
						converted = utf_wx_mal(word);
					} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
						converted = utf_wx_tam(word);
					} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
						converted = utf_wx_tel(word);
					} else {
						converted = word;
					}
					i ++;
					break;
				}
			}
			if (*(my_string+i) == '\0') {
				if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
					converted = utf_wx_ben(word);
				} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
					converted = utf_wx_hin(word);
				} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
					converted = utf_wx_kan(word);
				} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
					converted = utf_wx_pan(word);
				} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
					converted = utf_wx_mal(word);
				} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
					converted = utf_wx_tam(word);
				} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
					converted = utf_wx_tel(word);
				} else {
					converted = word;
				}
			}

			sprintf(converted_line+k, "~%s~%s",tag, converted);
			k += 2 + 3 + strlen(converted);
			sprintf(converted_line_untagged+l, "%s", converted);
			l += strlen(converted);
		} else {
			sprintf(converted_line+k, "%c", ch);
			i ++;
			k ++;
		}
	}
	return converted_line;
}
	

void child_tkn(node* mynode)
{
	char *wx_tkn, *utf_tkn, *tagged_tkn;
	char *tkn;
        list_of_nodes *list;
	int i;
	if (mynode != NULL) {
		tkn = get_field(mynode, 1);
		if (*tkn != '\0') {
			if (tkn[0] == '@') {
				tagged_tkn = preprocess(tkn);
				wx_tkn = convert_utf2wx(tagged_tkn);
				utf_tkn = convert_wx2utf(wx_tkn);
				if (strcmp(tkn, "--ROOT--")) {
		 			strcpy(mynode -> node_tkn, utf_tkn);
				}
			}
		}
		
	}

	list = getchildren(mynode);

	for (i = 0; i < list->size; i+=1) {
       		child_tkn(list -> l[i]);
        }
}

void set_flag (char* argv)
{
	char ch;
	char *to_convert_wx2utf = (char*)malloc(100);
	int i = 0;
	int j = 0;

	while(*(argv+i) != '\0'){
		ch = *(argv+i);
		if (ch != ','){
			sprintf(to_convert_wx2utf+j, "%c", ch);
			j ++;
			i ++;
		} else {
			if (!strcmp(to_convert_wx2utf,"ben")) {
				flag_ben = 1;
			} else if (!strcmp(to_convert_wx2utf,"hin")) {
				flag_hin = 1;
			} else if (!strcmp(to_convert_wx2utf,"kan")) {
				flag_kan = 1;
			} else if (!strcmp(to_convert_wx2utf,"pan")) {
				flag_pan = 1;
			} else if (!strcmp(to_convert_wx2utf,"mal")) {
				flag_mal = 1;
			} else if (!strcmp(to_convert_wx2utf,"tam")) {
				flag_tam = 1;
			} else if (!strcmp(to_convert_wx2utf,"tel")) {
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "all")) {
				flag_ben = 1;
				flag_hin = 1;
				flag_kan = 1;
				flag_mal = 1;
				flag_pan = 1;
				flag_tam = 1;
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "none")) {
				flag_ben = 0;
				flag_hin = 0;
				flag_kan = 0;
				flag_mal = 0;
				flag_pan = 0;
				flag_tam = 0;
				flag_tel = 0;
			}
			i ++;
			j = 0;
	
		}
		
		if (*(argv+i) == '\0'){
			if (!strcmp(to_convert_wx2utf,"ben")) {
				flag_ben = 1;
			} else if (!strcmp(to_convert_wx2utf,"hin")) {
				flag_hin = 1;
			} else if (!strcmp(to_convert_wx2utf,"kan")) {
				flag_kan = 1;
			} else if (!strcmp(to_convert_wx2utf,"pan")) {
				flag_pan = 1;
			} else if (!strcmp(to_convert_wx2utf,"mal")) {
				flag_mal = 1;
			} else if (!strcmp(to_convert_wx2utf,"tam")) {
				flag_tam = 1;
			} else if (!strcmp(to_convert_wx2utf,"tel")) {
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "all")) {
				flag_ben = 1;
				flag_hin = 1;
				flag_kan = 1;
				flag_mal = 1;
				flag_pan = 1;
				flag_tam = 1;
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "none")) {
				flag_ben = 0;
				flag_hin = 0;
				flag_kan = 0;
				flag_mal = 0;
				flag_pan = 0;
				flag_tam = 0;
				flag_tel = 0;
			}
		}
	}
}		

unsigned char* convert_wx2utf (unsigned char* my_string)
{	
	unsigned char ch;
	unsigned char *converted_wx2utf;
	unsigned char *converted_wx2utf_line = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *converted_wx2utf_line_untagged = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *word = (char *) malloc(strlen(my_string)*6 + 1);
	char tag[4];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	while(*(my_string+i) != '\0') {		
		ch = *(my_string+i);
		if (ch == '~') {			
			j = 0;
			tag[0] = *(my_string+i+1);
			tag[1] = *(my_string+i+1+1);
			tag[2] = *(my_string+i+1+1+1);
			tag[3] = '\0';
			i += 5;
			while (*(my_string+i) != '\0'){
				ch = *(my_string+i);
				if (ch != ' ') {
					sprintf(word+j, "%c", ch);
					j ++;
					i ++;
				} else {
					if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else {
						converted_wx2utf = word;
					}
					i ++;
					break;
				}
			}
			if (*(my_string+i) == '\0') {
					if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else {
						converted_wx2utf = word;
					}
			}

			sprintf(converted_wx2utf_line+k, "~%s~%s",tag, converted_wx2utf);
			k += 2 + 3 + strlen(converted_wx2utf);
			sprintf(converted_wx2utf_line_untagged+l, "%s", converted_wx2utf);
			l += strlen(converted_wx2utf);
		} else {
			sprintf(converted_wx2utf_line+k, "%c", ch);
			i ++;
			k ++;
		}
	}
	return converted_wx2utf_line_untagged;
}

char* wx_utf8_tgt(char* word)
{
	char* converted_wx2utf;
	if ( (!strcmp(tgt, "ben")) ) {
		converted_wx2utf = wx_utf8_ben(word);
	} else if ( (!strcmp(tgt, "hin")) ) {
		converted_wx2utf = wx_utf8_hin(word);
	} else if ( (!strcmp(tgt, "kan")) ) {
		converted_wx2utf = wx_utf8_kan(word);
	} else if ( (!strcmp(tgt, "mal")) ) {
		converted_wx2utf = wx_utf8_mal(word);
	} else if ( (!strcmp(tgt, "pan")) ) {
		converted_wx2utf = wx_utf8_pan(word);
	} else if ( (!strcmp(tgt, "tam")) ) {
		converted_wx2utf = wx_utf8_tam(word);
	} else if ( (!strcmp(tgt, "tel")) ) {
		converted_wx2utf = wx_utf8_tel(word);		
	} else {
		converted_wx2utf = word;
	}

	return converted_wx2utf;
}
	
