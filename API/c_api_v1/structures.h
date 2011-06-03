
/************         Data structures of Shakti Standard Format     *************/

/*--------feature structure---------*/
struct fs_struct {
	int key_count ; 
	GList *keys;	//keys are stored here in the order given in the input file
			///and these can be used in hash table to get the same 
			//order while printing the ssf
	GHashTable* hash ;		
};
typedef struct fs_struct fs_struct;

/*-------OR Node -------*/
struct or_node {
	int fs_count;	
	fs_struct *fs[5];
};
typedef struct or_node or_node;


/*------Node--------*/

struct node {
	char node_tkn[100];		//node's name  ----- also called field one
	char node_tag[100];		//node's tag   ----- also called field two   
	GList *childs;			//a list containing node's children
	int child_count;		//number of children i.e size of the list childs
	struct node *parent;		//parent of this node
	or_node *OR;	
} ;
typedef struct node node;




struct list_of_nodes {			//list of nodes 
	int size;			//list size
	node **l;			//list of node pointers
};
typedef struct list_of_nodes list_of_nodes;


struct list_of_or_nodes {		//list of or nodes
	int size;			//list size
	or_node **l;			//list of or_node pointers
};
typedef struct list_of_or_nodes list_of_or_nodes;

struct list_of_fs_structs {		//list of fs structures
	int size;			//list size
	fs_struct **l;			//list of fs structure pointers
};
typedef struct list_of_fs_structs list_of_fs_structs;

