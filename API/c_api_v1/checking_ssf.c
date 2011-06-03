#include "c_api_v1.h"

main(int argc ,char *argv[])
{
	int i;

	/*checking for creation and printing the tree ---Working*/
	node *tree ;
	tree=create_tree();
	read_ssf_from_file(tree, argv[1]);
	print_tree(tree);
	printf("Checked read and print\n\n");



	/*checking for get_nth_child ----Working*/
	node *child = get_nth_child(tree, 2);
	print_node_without_index(child);
	printf("Checked get_nth_child\n\n");

	/*checking for getchildren-----Working*/
	list_of_nodes *l1;
	l1=getchildren(tree);
	printf("\n\nsize=%d\n", l1->size);
	for (i=0; i< l1->size; i++)
	{
		print_attr_of_node(l1->l[i] );
		printf("\n");
	}
	printf("Checked getchildren\n\n");


	/*checking for getleaves----Working*/
	list_of_nodes *l2;
	l2=getleaves(tree);
	printf("\n\nsize=%d\n", l2->size);
	for (i=0; i< l2->size; i++)
	{
		print_attr_of_node(l2->l[i] );
		printf("\n");
	}
	printf("Checked getleaves\n\n");
	
	/*checking for getleaves_child---Working*/
	list_of_nodes *l3;
	l3=getleaves_child(l1->l[1]);
	printf("\n\nsize=%d\n", l3->size);
	for (i=0; i< l3->size; i++)
	{
		print_attr_of_node(l3->l[i] );
		printf("\n");
	}
	printf("Checked getleaves_child\n\n");

	/*checking for get_nodes---Working*/
	list_of_nodes *l4;
	l4=get_nodes(2,"NNS",tree);
	printf("\n\nsize=%d\n",l4->size);
	for (i=0; i< l4->size; i++)
	{
		print_attr_of_node(l4->l[i]);
		printf("\n");
	}
	printf("Checked get_nodes\n\n");


	/*checking for get_pattern---Working*/
	list_of_nodes *l5;
	l5=get_pattern(2,".*N.*",tree);
	printf("\n\nsize=%d\n",l5->size);
	for (i=0; i< l5->size; i++)
	{
		print_attr_of_node(l5->l[i]);
		printf("\n");
	}
	printf("Checked get_pattern\n\n");

	//checking for delete_node------Working
	//printf("%d\n",delete_node(l5->l[1]));
	//print_tree(tree);

	//checking for count_leaf_nodes ----Working
	printf("count of leaf nodes----%d\n\n", count_leaf_nodes(tree));

	//checking for get_field(s)  ----Working 
	char *str;
       	str=get_field(l5->l[1],1);
	printf("%s\n",str);
	str=get_fields(l5->l[1]);
	printf("%s\n", str);
	printf("Checked get_field and get_fields\n\n");


	//checking for get_next_node  and get_previos_node----Working
	node *N;
	N=get_next_node(l1->l[1]);
	str=get_fields(N);
	printf("%s\n", str);
	N=get_previous_node(l1->l[1]);
	str=get_fields(N);
	printf("%s\n", str);
	printf("Checked get_next_node & get_previous_node\n\n");


	//checking for insert_node_position------Working
	node *M;
	M=create_node_with_attr("iiit","NNP","<loc=hyd>",NULL);
	insert_node_into_position(tree,M,1);
	print_tree(tree);
	printf("Checked insert_node_position\n\n");
	
	/*Checkin print_attr_of_or_node--------Working*/	
	print_attr_of_or_node(M->OR);
	printf("\nChecked print_attr_of_or_node\n\n");
		
}


