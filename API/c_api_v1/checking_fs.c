#include "c_api_v1.h"

main(int argc ,char *argv[])
{
	/*checking for creation and printing the tree ---Working*/
	node *tree ;
	tree=create_tree();
	read_ssf_from_file(tree, argv[1]);
	print_tree(tree);
	printf("\n\n");

	node *child= get_nth_child(tree, 2);
	print_node_without_index(child);
	printf("\n\n");

	/*Checking add_attr_val-----Working*/
	add_attr_val(child->OR, "iiit", "hyderabad");
	printf("%s\n", make_or_node_to_string(child->OR)) ;
	printf("Checked add_attr_val\n\n");
		
	/*Checking update_attr_val--------Working*/
	update_attr_val(child->OR, "iiit", "Andhrapradesh" );
	printf("%s\n", make_or_node_to_string(child->OR)) ;
	printf("Checked update_attr_val\n\n");

	/*Checking add_attr_val_2--------Working*/
	add_attr_val_2(child->OR->fs[0], "gvs", "reddy");
	printf("%s\n", make_fs_struct_to_string(child->OR->fs[0]));
	printf("Checked add_attr_val_2\n\n");

	/*Checking update_attr_val_2------Working*/
	update_attr_val_2(child->OR->fs[0],"gvs", "goli");
	printf("%s\n", make_fs_struct_to_string(child->OR->fs[0]));
	printf("Checked update_attr_val_2\n\n");

	/*Checking del_attr & del_attr_2------Working*/
	del_attr(child->OR, "iiit");
	printf("%s\n", make_or_node_to_string(child->OR)) ;
	printf("Checked del_attr & del_attr_2\n\n");

	/*Checking get_attr_val--------Working*/
	printf("%s\n", get_attr_val(child->OR->fs[0], "gvs"));			
	printf("Checked get_attr_val\n\n");

	/*Checking get_nodes_with_attr_val--------Working*/
	list_of_nodes *L= get_nodes_with_attr_val(tree, "head", "3");
	printf("%d\n", L->size);
	int i;
	for (i=0; i<L->size; i++)
	{
		print_attr_of_or_node(L->l[i]->OR);
		printf("\n");
	}		
	
	/*Checking delete_fs_struct_from_or_node---Working*/
	printf("\n\nbefore deleton-----");
	print_attr_of_or_node(child->OR);
	printf("\n");
	delete_fs_struct_from_or_node(child->OR, 1);
	printf("after deletion----");
	print_attr_of_or_node(child->OR);
	printf("\n");
	printf("Checked delete_fs_struct_from_or_node\n\n");

	/*Checking add_fs_struct_to_or_node-----Working*/
	fs_struct *fs=read_fs("<af=watch,,,,3,0,,/new=fs/head=3>");
	add_fs_struct_to_or_node(child->OR, fs);
	print_attr_of_or_node(child->OR);
	printf("\n");
	printf("Checked add_fs_struct_to_or_node\n\n");
}
