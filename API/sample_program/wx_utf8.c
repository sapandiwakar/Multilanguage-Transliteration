
#include "c_api_v2.h"			// Include file for c_api
#include "wx_utf.c"			// Include file for Wx2Utf8 converter
#include<unistd.h>
#include<getopt.h>

void child(node* mynode);		// Function to handle
void modify_tree(node* mynode);
int main(int argc,char *argv[])
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
				char *utf_tkn = wx_utf8(tkn);
				if (strcmp(tkn, "--ROOT--")) {
		 			strcpy(mynode -> node_tkn, utf_tkn);
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
					char *utf_root = wx_utf8(root);
					update_attr_val_2(mynode->OR->fs[i],"root", utf_root);
				}
				if (*cm != '\0') {
					char *utf_cm = wx_utf8(cm);
					update_attr_val_2(mynode->OR->fs[i],"cm", utf_cm);
				}
				if (*suffix != '\0') {
					char *utf_suffix = wx_utf8(suffix);
					update_attr_val_2(mynode->OR->fs[i],"suffix", utf_suffix);
				}
				if (*name != '\0') {
					char *utf_name = wx_utf8(name);
					update_attr_val_2(mynode->OR->fs[i],"name", utf_name);
				}
				if (*head != '\0') {
					char *utf_head = wx_utf8(head);
					update_attr_val_2(mynode->OR->fs[i],"head", utf_head);
				}
			}
		}
	}

	list_of_nodes *list = getchildren(mynode);

	for (i = 0; i < list->size; i+=1) {
       		child(list -> l[i]);
        }
}

