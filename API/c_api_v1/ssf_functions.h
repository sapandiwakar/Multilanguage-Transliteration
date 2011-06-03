
//Gives a particular field of a given node.
char *get_field(node *N, int number )
{
	char *str=(char *)malloc(500*sizeof(char));
	if ( N==NULL)
		str[0]='\0';
	else
	{
		switch (number)
		{
			case 1:
				strcpy(str, N->node_tkn) ;
				break;
			case 2:
				strcpy(str, N->node_tag) ;
				break;
			case 3:
				strcpy(str, make_or_node_to_string(N->OR));
				break;				
		}
	}
	return str;
}

// Gives all the fields in string format
char *get_fields (node *N )
{
	char *str=(char *)malloc(1000*sizeof(char));
	if (N==NULL)
		str[0]='\0';
	else
	{
		sprintf(str,"%s\t%s\t%s\0", N->node_tkn, N->node_tag, make_or_node_to_string(N->OR));
	}
	return str;
}


//inserts the child at the given position. 
//If posistion > (parent->child_count) it will insert be inserted at the end
int insert_node_into_position(node *parent, node *child, int position)
{
	if ( position < 0)
		return 0;
	else
	{
		child->parent= parent;
		parent->childs= g_list_insert(parent->childs, (void *)child, position);
		parent->child_count ++;
		return 1;
	}
}


//gets the nth child
node *get_nth_child(node *N, int number)
{
	if (N==NULL || number > N->child_count || number < 0 )
	       return NULL;
	else
	{
		return (node *)g_list_nth_data(N->childs, number);
	}
}

//Returns next sibling of a given node.
node *get_next_node(node *N)
{
	
	if ( N==NULL || N->parent==NULL)
		return NULL;
	else 
	{
		GList *tmp=N->parent->childs;
		tmp = g_list_find (tmp, N);
		return (node *)g_list_nth_data(tmp, 1);
	}
}


//Returns parent of a given node.
node *get_parent(node *N)
{
	if (N==NULL)
		return NULL;
	else
		return N->parent;
}


//Returns previous sibling of a given node.
node *get_previous_node(node *N)
{
	if ( N==NULL || N->parent==NULL)
		return NULL;
	else 
	{
		GList *tmp=N->parent->childs;
		tmp = g_list_find (tmp, N);
		tmp =	g_list_previous(tmp);
		return (node *)g_list_nth_data(tmp, 0);
	}
}

//Modifies a particular field of a given node.
//returns 1 on success and 0 on failure
//You can also modify or_node here
int modify_field(node *N, int number,char str[])
{
	if (N==NULL)
	{
		return 0;
	}
	else
	{
		if (number==1)
			strcpy(N->node_tkn, str);
		else if (number==2)
			strcpy(N->node_tag, str);
		else if (number==3)
		{
			free(N->OR);
			N->OR= read_or_node(str);
		}
		else 
			return 0;
		return 1;
	}
}


//returns 1 on succefull delition else 0
int delete_node(node *N)
{
	node *parent=N->parent;
	if (parent==NULL)
		return 0;	
	parent->childs= g_list_remove(parent->childs, N);
	int len=g_list_length(parent->childs);
	if ( len < parent->child_count )
	{
		parent->child_count= len;
		return 1;
	}
	else
		return 0;
}




// creates list of nodes
list_of_nodes * create_list_of_nodes(int size)
{
	list_of_nodes *tmp=(list_of_nodes *) malloc (sizeof(list_of_nodes));
	tmp->size=size;
	tmp->l=(node **)malloc(size*sizeof(node *));
	return tmp;
}

// creates list of or_nodes
list_of_or_nodes * create_list_of_or_nodes(int size)
{
	list_of_or_nodes *tmp=(list_of_or_nodes *) malloc(sizeof(list_of_or_nodes));
	tmp->size=size;
	tmp->l=(or_node **)malloc(size*sizeof(or_node *));
	return tmp;
}

//creates list of fs structures
list_of_fs_structs *create_list_of_fs_structs(int size)
{
	list_of_fs_structs *tmp=(list_of_fs_structs *) malloc(sizeof(list_of_fs_structs));
	tmp->size=size;
	tmp->l=(fs_struct **)malloc(size*sizeof(fs_struct *));
	return tmp;
}

 



/*---------finding whether a string matches a pattern---------*/

int match(const char *string, char *pattern)
{
	int    status;
	regex_t    re;

	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
		return(0);      /* report error */
	}
	status = regexec(&re, string, (size_t) 0, NULL, 0);
	regfree(&re);
	if (status != 0) {
		return(0);      /* report error */
	}
	return(1);
}

// make a list_of_nodes from glist

list_of_nodes *make_list_of_nodes_from_glist(GList *L)
{
	int size= g_list_length(L);
	GList *start=L;
	list_of_nodes *tmp = create_list_of_nodes(size);
	int i;
	for (i=0;i<size; i++)
	{
		if(i!=0)
			L= g_list_next(L);
		tmp->l[i]=(node *) g_list_nth_data(L, 0);
	}
	L=start;
	return tmp;
}



list_of_nodes *getchildren( node *Node )			//childrens of this node
{
	list_of_nodes *tmp = make_list_of_nodes_from_glist(Node->childs);
	return tmp;	
}


GList *tmp_getleaves(node *Node, GList *L)			//gets leaves to List L...Internal function....users can ignore
{
	if (Node->child_count==0)
		L=g_list_append(L, (void *) Node);
	else
	{
		int i=0;
		GList *start = Node->childs;
		for (i=0; i<Node->child_count; i++)
		{
			if(i!=0)
				Node->childs = g_list_next(Node->childs);
			L=tmp_getleaves((node *) g_list_nth_data(Node->childs, 0), L);
		}
		Node->childs = start;
	}
	return L;

}

list_of_nodes *getleaves (node *Node)				//gets all leaves of this node/sub tree
{
	GList *L=NULL;
	L=tmp_getleaves (Node, L);

	list_of_nodes *tmp= make_list_of_nodes_from_glist(L);	
	return tmp;
}


int tmp_count_leaf_nodes(node *tree, int sum)
{
	if (tree->child_count==0)
	{
		sum++;
		return sum;
	}
	else
	{
		int i;
		GList *start=tree->childs;
		for (i=0; i<tree->child_count; i++)
		{
			if (i!=0)
				tree->childs=g_list_next(tree->childs);
			sum= tmp_count_leaf_nodes((node *)g_list_nth_data(tree->childs, 0), sum);
		}
		tree->childs= start;
	}
	return sum;
}

//Counts the number of leaf nodes in a tree/sub tree
int count_leaf_nodes(node *tree)
{
	return tmp_count_leaf_nodes(tree, 0);
}

list_of_nodes *getleaves_child (node *Node )			//gets the childs which are also leaves
{
	GList *L=NULL;
	int i;
	node *temp;
	for (i=0; i<Node->child_count; i++)
	{
		temp = (node *) g_list_nth_data(Node->childs, i);
		if (temp->child_count==0)
			L=g_list_append(L, (void *) temp);
	}

	list_of_nodes *tmp= make_list_of_nodes_from_glist(L);
	return tmp;	
}

GList *tmp_get_nodes(int num, char str[], node *tree, GList *L) // internal function to get a list of nodes with particular field value Note:implemented using Depth first search
{
	int i;
	if (strcmp(tree->node_tag, "--SSF--"))
	{
		if (num==1)
		{
			if ( strcmp(tree->node_tkn, str)==0 )
				L=g_list_append(L, (void *)tree);
		}
		else if (num==2)
		{
			if ( strcmp(tree->node_tag, str)==0)
				L=g_list_append(L, (void *)tree);
		}	
	}
	GList *start=tree->childs;
	node *tmp;
	for (i=0; i<tree->child_count; i++)
	{
		if (i!=0)
		{
			tree->childs=g_list_next(tree->childs);
		}		
		tmp=(node *)g_list_nth_data(tree->childs,0);
		L=tmp_get_nodes(num, str, tmp, L);
	}
	tree->childs=start;
	return L;
}

//gets nodes which have particular field values in a tree/sub tree  
//--Note Feature structure is "NOT INCLUDED" here
list_of_nodes *get_nodes(int fieldnumber, char str[], node *tree)
{
	if (fieldnumber > 2 || fieldnumber < 1)
		return NULL;
	GList *L=NULL;
	L=tmp_get_nodes(fieldnumber, str, tree, L);

	list_of_nodes *tmp= make_list_of_nodes_from_glist(L);
	g_list_free(L);
	return tmp;
}

GList *tmp_get_pattern (int num, char pattern[], node *tree, GList *L)
{
	int i;
	GList *start=tree->childs;
	node *tmp;
	if (strcmp(tree->node_tag,"--SSF--"))
	{
		switch (num)
		{

			case 1:
				if ( match(tree->node_tkn, pattern) )
				{
					L=g_list_append(L, (void *)tree);
				}
				break;
			case 2:
				if ( match(tree->node_tag, pattern) )
					L=g_list_append(L, (void *)tree);
				break;
			case 3:
				if ( match(make_or_node_to_string(tree->OR), pattern) )
					L=g_list_append(L, (void *)tree);
				break;

		}
	}	

	for (i=0; i<tree->child_count; i++)
	{
		if (i!=0)
		{
			tree->childs=g_list_next(tree->childs);
		}		
		tmp=(node *)g_list_nth_data(tree->childs,0);
		L=tmp_get_pattern(num, pattern, tmp, L);
	}
	tree->childs=start;
	return L;

}

//gets nodes which have particular pattern field values in a tree/sub tree  
//--Note Feature structure is "INCLUDED" here
list_of_nodes *get_pattern(int fieldnumber, char pattern[], node *tree)
{
	if (fieldnumber > 3 || fieldnumber < 1)
		return NULL;
	GList *L=NULL;
	L=tmp_get_pattern(fieldnumber, pattern, tree, L);

	list_of_nodes *tmp= make_list_of_nodes_from_glist(L);
	g_list_free(L);
	return tmp;
}

