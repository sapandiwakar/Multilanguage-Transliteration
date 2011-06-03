
//**************************************
// FILE     : utf8_wx.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_api_v2.h"

#define HIN_START 128
#define MATRA_START1 1
#define MATRA_END1 3 
#define MATRA_START2 60
#define MATRA_END2 60
#define MATRA_START3 62
#define MATRA_END3 76

#define VOW_FIRST_START1 5
#define VOW_FIRST_END1 11
#define VOW_FIRST_START2 15
#define VOW_FIRST_END2 16
#define VOW_FIRST_START3 19
#define VOW_FIRST_END3 20

#define CON_START 21
#define CON_END 57

#define NUM_START 96
#define NUM_END 111

char* utf_wx(unsigned char *ch);
void child(node* mynode);

char eng[] = {' ', 'z', 'M', 'H', ' ', 'a','A','i','I','u','U', 'q', 'L', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', 'k', 'K', 'g', 'G', 'f', 'c', 'C', 'j', 'J', 'F', 't', 'T', 'd', 'D', 'N', 'w', 'W', 'x', 'X', 'n', 'n', 'p', 'P', 'b', 'B', 'm', 'y', 'r', 'r', 'l', ' ', ' ', 'v', 'S', 'R', 's', 'h', ' ', ' ', 'Z', ' ', 'A', 'i', 'I', 'u', 'U', 'q', 'Q', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', ' ', ' ', '`', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Q', ' ', ' ', ' ', '.', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int main(int argc ,char *argv[])
{

	/* Please keep all the files that you are using have this as the basic code */
	circle *tree;   // create the doc object
	tree=create_circle(NULL); // initialize the datastructure
	read_ssf_from_file(tree,argv[1]);  // read from the file into tree
	int sentence=sentences(tree);
	node * temp[sentence];   // create the node object to store all the nodes retuned
	int count=0,i,k;  // count to count the # of sentences or nodes returned
	count=traverse_tree(tree,temp,count); // function which returns all the sentence nodes into temp
	
	for(i=0;i<count;i++) {
		child(temp[i]);
		print_tree(temp[i]); // replace with your desired function
	}
		      
	return 0;
}


void child(node* mynode)
{
	int i;
	if (mynode != NULL) {
		char *tkn = get_field(mynode, 1);
			if (*tkn != '\0') {
				char *wx_tkn = utf_wx(tkn);
				if (strcmp(tkn, "--ROOT--")) {
		 			strcpy(mynode -> node_tkn, wx_tkn);
				}


			}
		if (mynode->OR!=NULL) {
			for (i = 0; i < mynode->OR->fs_count; i ++ ) {
	       		        char *root = get_attr_val(mynode->OR->fs[i], "root");
	       		        char *cm = get_attr_val(mynode->OR->fs[i], "cm");
	       		        char *suffix = get_attr_val(mynode->OR->fs[i], "suffix");
	       		        char *name = get_attr_val(mynode->OR->fs[i], "name");
	       		        char *head = get_attr_val(mynode->OR->fs[i], "head");
				if (*root != '\0') {
					char *wx_root = utf_wx(root);
					update_attr_val_2(mynode->OR->fs[i],"root", wx_root);
				}
				if (*cm != '\0') {
					char *wx_cm = utf_wx(cm);
					update_attr_val_2(mynode->OR->fs[i],"cm", wx_cm);
				}
				if (*suffix != '\0') {
					char *wx_suffix = utf_wx(suffix);
					update_attr_val_2(mynode->OR->fs[i],"suffix", wx_suffix);
				}
				if (*name != '\0') {
					char *wx_name = utf_wx(name);
					update_attr_val_2(mynode->OR->fs[i],"name", wx_name);
				}
				if (*head != '\0') {
					char *wx_head = utf_wx(head);
					update_attr_val_2(mynode->OR->fs[i],"head", wx_head);
				}
			}
		}
	}
				//
	//if (modify_field(mynode, 1, converted_ch)) {

        /*if (mynode->OR!=NULL) {
		char *root= get_attr_val(mynode->OR->fs[0], "root");
		printf("root--> %s\n", root);*/

	list_of_nodes *list = getchildren(mynode);

	for (i = 0; i < list->size; i+=1) {
       		child(list -> l[i]);
        }
}

char* utf_wx(unsigned char *ch)
{
	char *utf8_string = malloc(strlen(ch));
	if (utf8_string == NULL) { printf("Can't allocate memory for utf8_string\n"); exit;}

	unsigned char ch1[4];
	unsigned char ch2[4];
	unsigned char ch3[4];
	int i = 0;
	int j = 0;
	int k;
	int a;
	int b;
	int index;
	
		
	while ( ch1[0] = *(ch+i) ) {
		if (ch1[0] == '\n') {
			sprintf(utf8_string+j, "\n");
			j++;
			return;
		} else if (ch1[0] == '\0') {
			i++;
			continue;
 		} else if (isascii(ch1[0])) {
			sprintf(utf8_string+j, "%c", ch1[0]);
			j++;
			i++;
			continue;
		}
		ch1[1] = *(ch+i+1);
		ch1[2] = *(ch+i+2);
		ch1[3] = '\0';
		i += 3;
		
		if (ch1[1] == 164) {
			index = ch1[2] - HIN_START;
			if ((index >= VOW_FIRST_START1 && index <= VOW_FIRST_END1) || (index >= VOW_FIRST_START2 && index <= VOW_FIRST_END2) || (index >= VOW_FIRST_START3 && index <= VOW_FIRST_END3)) {
				sprintf(utf8_string+j, "%c", eng[index]);
				j++;
			} else if ((index >= MATRA_START1 && index <= MATRA_END1) || (index >= MATRA_START2 && index <= MATRA_END2) || (index >= MATRA_START3 && index <= MATRA_END3)) {
					sprintf(utf8_string+j, "%c", eng[index] );
					j++;
					continue;
			} else {
				sprintf(utf8_string+j, "%c", eng[index]);
				j++;
				ch2[0] = *(ch+i);
				if (ch2[0] == '\n') {
					sprintf(utf8_string+j, "a\n");
					j += 2;
					return;
				} else if (ch2[0] == '\0') {
					i++;
					continue;
		 		} else if (isascii(ch2[0])) {
					sprintf(utf8_string+j, "a%c", ch2[0]);
					j += 2;
					i++;
					continue;
				}

				ch2[1] = *(ch+i+1);
				ch2[2] = *(ch+i+2);
				ch2[3] = '\0';

				if (ch2[1] == 164) {
					index = ch2[2] - HIN_START;
					if ((index >= MATRA_START3 && index <= MATRA_END3)) {
						sprintf(utf8_string+j, "%c", eng[index] );
						j ++;
						i += 3;
					} else if (index == MATRA_START2) {
						sprintf(utf8_string+j, "%c", eng[index]);
						j++;
						i += 3;
						ch3[0] = *(ch+i);
						if (ch3[0] == '\n') {
							sprintf(utf8_string+j, "a\n");
							j += 2;
						} else if (ch3[0] == '\0') {
							i++;
							continue;
				 		} else if (isascii(ch3[0])) {
							sprintf(utf8_string+j, "a%c", ch3[0]);
							j += 2;
							i++;
							continue;
						}

						ch3[1] = *(ch+i+1);
						ch3[2] = *(ch+i+2);
						ch3[3] = '\0';
			
						if (ch3[1] == 164) {
							index = ch3[2] - HIN_START;
							if ((index != 2) && (index >= MATRA_START1 && index <= MATRA_END1) || (index >= MATRA_START3 && index <= MATRA_END3)) {
								sprintf(utf8_string+j, "%c", eng[index] );
								j ++;
								i += 3;
								continue;
							} else if (index == 2) {
								sprintf(utf8_string+j, "a");
								j++;
							} else if (index >= CON_START && index <= CON_END) {
								sprintf(utf8_string+j, "a");
								j++;
								continue;
							} else {								
								continue;
							}
						} else if (ch3[1] == 165) {
							index = ch3[2] - HIN_START + 64;
							if ((index >= MATRA_START3 && index <= MATRA_END3)) {
								sprintf(utf8_string+j, "%c", eng[index] );
								j++;
								i += 3;
							} else {
								i += 3;
								continue;
							}
						} else {
							sprintf (utf8_string+j, "%s", ch3);
							j += 3;
						} 
					} else {
						sprintf(utf8_string+j, "a");
						j ++;
					}
				} else if (ch2[1] == 165) {
					index = 64 + ch2[2] - HIN_START;
					if ((index >= MATRA_START2 && index <= MATRA_END2) || (index >= MATRA_START3 && index <= MATRA_END3)) {
						sprintf(utf8_string+j, "%c", eng[index] );
						j ++;
						i += 3;
					} else if (index == (141 + 64 - HIN_START)) {
						i +=3;
						continue;
					} else {
						sprintf(utf8_string+j, "a"); 			 
						j ++;
					}
				}
			}
		} else if (ch1[1] == 165) {
			index = 64 + ch1[2] - HIN_START;
			if (index >= NUM_START && index <= NUM_END) {
				sprintf(utf8_string+j, "%c", eng[index]);
				j ++;
			}
		} else {

			sprintf(utf8_string+j, "%s", ch1);
			j ++;
		}
		
	}
	return utf8_string;
}
