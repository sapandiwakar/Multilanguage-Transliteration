
//Inserts attr values in all the fs's present in or_node
//if any fs is already having attr then it is updated. 
//Returns 0 on failure and 1 on success.
int add_attr_val(or_node *OR, char attr[], char value[])
{
	if (OR==NULL)
	{
		return 0;
	}
	else
	{
		int i;
		for (i=0; i<OR->fs_count; i++)
		{
			add_attr_val_2(OR->fs[i], attr, value);
		}
		return 1;
	}
}

//This inserts attr in a particular fs
//If fs already contains attr, then 0 (error) is returned.
//Else attr is inserted & 1 is returned.

int add_attr_val_2(fs_struct *fs, char attr[], char value[])
{
	if (fs==NULL)
		return 0;
	else
	{
		if( g_hash_table_lookup(fs->hash, attr)==NULL)
		{
			fs->key_count++;
			fs->keys=g_list_append(fs->keys, g_strdup(attr));
			g_hash_table_insert(fs->hash, g_strdup(attr), g_strdup(value));
			return 1;
		}
		else
			return 0;
	}
}

//This updates the "attr" in all the fs's of the or_node which contains the key "attr"
int update_attr_val(or_node *OR, char attr[], char value[])
{
	if (OR==NULL)
		return 0;
	else
	{
		int i;
		for (i=0; i<OR->fs_count; i++)
		{
			update_attr_val_2(OR->fs[i], attr, value);
		}
		return 1;
	}
}

//update attr value in the fs.
//If fs does not contain attr 0 is returned.
int update_attr_val_2(fs_struct *fs, char attr[], char value[])
{
	if (fs==NULL)
		return 0;
	else
	{
		if(g_hash_table_lookup(fs->hash, attr)!=NULL)
		{
			g_hash_table_insert(fs->hash, g_strdup(attr), g_strdup(value));
			return 1;
		}
		else
			return 0;
	}
}

//Deletes attr from or_node
int del_attr(or_node *OR, char attr[])
{
	if (OR==NULL)
		return 0;
	else
	{
		int i;
		for (i=0; i<OR->fs_count; i++)
		{
			delete_attr_2(OR->fs[i], attr);
		}
		return 1;
	}

}

//Deletes attr from fs_struct.
//if no key with attr is found 0 is returned. 
int delete_attr_2(fs_struct *fs, char attr[])
{
	if (fs==NULL)
		return 0;
	else if (g_hash_table_lookup(fs->hash, attr)!=NULL)
	{

		//removing attr from the list keys 
		GList *start= fs->keys;
		char *str;
		int j;
		for(j=0; j< fs->key_count; j++)
		{
			str= (char *)g_list_nth_data(start, 0);
			if(strcmp(str, attr)==0)
			{
				fs->keys= g_list_remove_link(fs->keys, start);
				break;
			}
			start= g_list_next(start);
		}	

		//decreasing the key count
		fs->key_count--;

		//removing from the hash table
		g_hash_table_remove(fs->hash, attr);
		return 1;
	}
	else
		return 0;

}

char *get_attr_val(fs_struct *fs, char attr[])
{
	char *str= (char *)g_hash_table_lookup(fs->hash, attr);
	if(str!=NULL)
		return str;
	else
	{
		str=(char *)malloc(sizeof(char));
		*str='\0';
		return str;
	}
}

//a rcursive call which returns a list
GList * tmp_get_nodes_with_attr_val(node *N, char attr[], char val[], GList *tmp)
{
	int i;
	if (N==NULL )
		return tmp;
	if(N->OR!=NULL)
	{
		for (i=0; i< N->OR->fs_count; i++)
		{
			if(g_hash_table_lookup(N->OR->fs[i]->hash, attr)!=NULL)
			{
				if ( strcmp((char *)g_hash_table_lookup( N->OR->fs[i]->hash, attr), val)==0)
				{
					tmp= g_list_append(tmp, (void *)N);
					break;
				}
			}
		}
	}
	GList *start= N->childs;
	for (i=0; i< N->child_count; i++)
	{
		tmp= tmp_get_nodes_with_attr_val( (node *)g_list_nth_data(start, 0), attr, val, tmp);
		start= g_list_next(start);
	}
	return tmp;
}

//get a list of nodes with or_node (fs) attrs equal to val
list_of_nodes *get_nodes_with_attr_val(node *N, char attr[], char val[])
{
	GList *tmp=NULL;
      	tmp= tmp_get_nodes_with_attr_val(N, attr, val, tmp);
	
	list_of_nodes *L= make_list_of_nodes_from_glist(tmp);
	g_list_free(tmp);

	return L;
}

void delete_fs_struct_from_or_node(or_node *OR, int pos)
{
	if (OR==NULL)
		return;
	int i;
	free(OR->fs[pos]);
	for(i=pos; i<OR->fs_count-1; i++)
	{
		OR->fs[i]=OR->fs[i+1];
	}
	OR->fs[OR->fs_count-1]=NULL;
	OR->fs_count--;
	return;
}

void add_fs_struct_to_or_node(or_node *OR, fs_struct *fs)
{
	OR->fs[OR->fs_count]=fs;
	OR->fs_count++;
}
 
