#include "c_api_v1.h"
main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Usage: ./<prog_name> <input_ssf_file>\n");
		exit(1);
	}
	node *tree=create_tree();
	read_ssf_from_file(tree, argv[1]);
	print_tree(tree);
}

