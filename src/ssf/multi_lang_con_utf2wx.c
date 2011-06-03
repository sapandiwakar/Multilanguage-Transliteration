#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_api_v2.h"
#include "preprocessor.h"
#include "utf8_wx_ben.h"
#include "utf8_wx_hin.h"
#include "utf8_wx_kan.h"
#include "utf8_wx_mal.h"
#include "utf8_wx_pan.h"
#include "utf8_wx_tam.h"
#include "utf8_wx_tel.h"

unsigned char* convert (unsigned char* my_string);
void child_hin(node* mynode);
void set_flag (char* argv);
void child_tkn(node* mynode);

int flag_ben = 0;
int flag_hin = 0;
int flag_kan = 0;
int flag_mal = 0;
int flag_pan = 0;
int flag_tam = 0;
int flag_tel = 0;

int main(int argc ,char *argv[])
{
	set_flag(argv[3]);
	/* Please keep all the files that you are using have this as the basic code */
	circle *tree;   				// create the doc object
	tree=create_circle(NULL); 			// initialize the datastructure
	read_ssf_from_file(tree,argv[1]);  		// read from the file into tree
	int sentence=sentences(tree);
	node * temp[sentence]; 				// create the node object to store all the nodes retuned
	int count=0,i,k;  				// count to count the # of sentences or nodes returned
	count=traverse_tree(tree,temp,count); 		// function which returns all the sentence nodes into temp

	for(i=0;i<count;i++) {
		child_hin(temp[i]);
		child_tkn(temp[i]);
	}
	print_tree_to_file(tree, argv[2]);

	return 0;
}

void child_hin(node* mynode)
{
        char *root;
        char *cm;
        char *suffix;
        char *name;
        char *head;
	char *tagged_root, *tagged_cm, *tagged_suffix, *tagged_head, *tagged_name;
	char *wx_root, *wx_cm, *wx_suffix, *wx_head, *wx_name;
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
					tagged_root = preprocess(root);
					wx_root = convert(tagged_root);
					update_attr_val_2(mynode->OR->fs[i],"root", wx_root);
				}
				if (*cm != '\0') {
					tagged_cm = preprocess(cm);
					wx_cm = convert(tagged_cm);
					update_attr_val_2(mynode->OR->fs[i],"cm", wx_cm);
				}
				if (*suffix != '\0') {
					tagged_suffix = preprocess(suffix);
					wx_suffix = convert(tagged_suffix);
					update_attr_val_2(mynode->OR->fs[i],"suffix", wx_suffix);
				}
				if (*name != '\0') {
					tagged_name = preprocess(name);
					wx_name = convert(tagged_name);
					update_attr_val_2(mynode->OR->fs[i],"name", wx_name);
				}
				if (*head != '\0') {
					tagged_head = preprocess(head);
					wx_head = convert(tagged_head);
					update_attr_val_2(mynode->OR->fs[i],"head", wx_head);
				}
			}
		}
	}

	list = getchildren(mynode);

	for (i = 0; i < list->size; i+=1) {
       		child_hin(list -> l[i]);
        }
}

void child_tkn(node* mynode)
{
	char *tagged_tkn;
	char *wx_tkn;
	char *tkn;
        list_of_nodes *list;
	int i;
	if (mynode != NULL) {
		tkn = get_field(mynode, 1);
		if (*tkn != '\0') {
			tagged_tkn = preprocess(tkn);
			wx_tkn = convert(tagged_tkn);
			if (strcmp(tkn, "--ROOT--")) {
	 			strcpy(mynode -> node_tkn, wx_tkn);
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
	char *to_convert = (char*)malloc(100);
	int i = 0;
	int j = 0;

	while(*(argv+i) != '\0'){
		ch = *(argv+i);
		if (ch != ','){
			sprintf(to_convert+j, "%c", ch);
			j ++;
			i ++;
		} else {
			if (!strcmp(to_convert,"ben")) {
				flag_ben = 1;
			} else if (!strcmp(to_convert,"hin")) {
				flag_hin = 1;
			} else if (!strcmp(to_convert,"kan")) {
				flag_kan = 1;
			} else if (!strcmp(to_convert,"pan")) {
				flag_pan = 1;
			} else if (!strcmp(to_convert,"mal")) {
				flag_mal = 1;
			} else if (!strcmp(to_convert,"tam")) {
				flag_tam = 1;
			} else if (!strcmp(to_convert,"tel")) {
				flag_tel = 1;
			} else if (!strcmp(to_convert, "all")) {
				flag_ben = 1;
				flag_hin = 1;
				flag_kan = 1;
				flag_mal = 1;
				flag_pan = 1;
				flag_tam = 1;
				flag_tel = 1;
			} else if (!strcmp(to_convert, "none")) {
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
			if (!strcmp(to_convert,"ben")) {
				flag_ben = 1;
			} else if (!strcmp(to_convert,"hin")) {
				flag_hin = 1;
			} else if (!strcmp(to_convert,"kan")) {
				flag_kan = 1;
			} else if (!strcmp(to_convert,"pan")) {
				flag_pan = 1;
			} else if (!strcmp(to_convert,"mal")) {
				flag_mal = 1;
			} else if (!strcmp(to_convert,"tam")) {
				flag_tam = 1;
			} else if (!strcmp(to_convert,"tel")) {
				flag_tel = 1;
			} else if (!strcmp(to_convert, "all")) {
				flag_ben = 1;
				flag_hin = 1;
				flag_kan = 1;
				flag_mal = 1;
				flag_pan = 1;
				flag_tam = 1;
				flag_tel = 1;
			} else if (!strcmp(to_convert, "none")) {
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

unsigned char* convert (unsigned char* my_string)
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
	
