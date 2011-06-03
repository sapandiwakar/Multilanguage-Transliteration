 




/*------tree creation---------*/

node * create_tree()			//returns the root node pointer
{
	node *root=(node *)malloc(sizeof(node ));
	strcpy(root->node_tkn,"--ROOT--");
	strcpy(root->node_tag,"--SSF--");
	root->childs=NULL;
	root->child_count=0;
	root->parent=NULL;
	root->OR=NULL;
	return root;
	
}

/*------node creation---------*/

node * create_node (node *parent)		
{
	node *tmp=(node *)malloc(sizeof(node));
	tmp->node_tkn[0]='\0';	
	tmp->node_tag[0]='\0';
	tmp->childs=NULL ;
	tmp->child_count=0;
	tmp->parent=parent ;
	tmp->OR=NULL ;
	return tmp;
}

/*---------node creation with attributes given-------*/
node * create_node_with_attr(char tkn[], char tag[], char fs[], node *parent)
{
	node *tmp=(node *)malloc(sizeof(node));
	strcpy(tmp->node_tkn, tkn);
	strcpy(tmp->node_tag, tag);
	tmp->childs= NULL;
	tmp->child_count=0;
	tmp->parent= parent;
	tmp->OR= read_or_node(fs);
	return tmp;
}

/*------or node creation------*/

or_node * create_or_node ( )
{
	or_node *tmp=(or_node *)malloc(sizeof(or_node));
	tmp->fs_count	= 0;
	return tmp;
}

/*------feature structure creation-------*/

fs_struct *create_fs_struct()
{
	fs_struct *tmp=(fs_struct *) malloc(sizeof( fs_struct));
	tmp->keys=NULL;
	tmp->hash = g_hash_table_new(g_str_hash, g_str_equal);
	tmp->key_count=0;
	return tmp;
}


/*-----------convert int to string---------*/

void int_to_str(int num,char *str)
{
	sprintf(str, "%d", num);
/*	int i;
	for(i=0; num!=0; num=num/10, i++)
	{
		str[i]=(char)(num%10+'0');
	}
	str[i]='\0';*/
}

/* Reads ssf from the file specified */

void read_ssf_from_file (node *tree, char filename[])	//reads a ssf from file into node tree
{	
	FILE *f;
	f=fopen(filename,"r");
	read_ssf(tree,f);	
	fclose(f);
}


/*----------read ssf from FILE *f--------*/

void read_ssf(node *tree, FILE *f)
{
	
	char str[1000];
	char index[100];		//first coloumn of ssf (e.g  1.2.2)
	int flag=-1 ;
	char ch ;
	
	
	while(fscanf(f,"%c",&ch)!=EOF)
	{
		str[0]='\0';
		index[0]='\0';

		if(ch!='\t' && ch!='\n' && ch!='#' && ch!='<')
		{
			node *tmp= create_node ( tree );		
			fseek(f, -1 , SEEK_CUR);
			fscanf(f, "%s",index);			//index
			fscanf(f, "%c", &ch);
			fscanf(f, "%s", tmp->node_tkn);		//token
			fscanf(f, "%c", &ch);
			if(ch!='\n')				
			{
				fscanf(f, "%c", &ch);
				if(ch!='\t' && ch!='\n')	//if there is a tag
				{
					fseek(f, -1, SEEK_CUR);
					fscanf(f, "%s", tmp->node_tag);
					fscanf(f, "%c", &ch);
					if(ch!='\n')		//feature structure
					{
						fscanf(f, "%c", &ch);
						if(ch!='\t' && ch!='\n')	
						{
							char tmp_fs[500];
							fseek(f, -1, SEEK_CUR);
							fscanf(f, "%[^\n]", tmp_fs);
							fgetc(f);
							tmp->OR = read_or_node(tmp_fs);
						}
					}
				}
				else if(ch=='\t')		//if there is no tag
				{
					fscanf(f, "%c", &ch);
					if(ch!='\t' && ch!='\n')	
					{
						char tmp_fs[500];
						fseek(f, -1, SEEK_CUR);
						fscanf(f, "%[^\n]", tmp_fs);
						fgetc(f);
						tmp->OR = read_or_node(tmp_fs);
					}

				}				
				
			}

			tree->childs = g_list_append ( tree->childs, (void *)tmp);
			tree->child_count++;

			if ( strcmp(tmp->node_tkn, "((")==0 )
			{
				read_ssf( (node *) g_list_nth_data(tree->childs,tree->child_count-1),f ) ;
			}

			
		}
		else if(ch=='\t')
		{
			fscanf(f, "%s",str);
			if(strcmp(str,"))")==0)
			{
				fscanf(f, "%[^\n]",str);
				fgetc(f);
				return;
			}
			else
			{
				fscanf(f, "%[^\n]",str);
				fgetc(f);
			}
		}

		else if(ch=='#')
		{
			fscanf(f, "%[^\n]", str);
			fgetc(f);
		}
		else if(ch=='<' || ch=='\n')
		{
			fseek(f, -1, SEEK_CUR);
			return;
		}
		
		
	}
	
}

/* creates or_node from  string */
 
or_node * read_or_node( char str[])
{
	int i=0, j=0, k=0, flag=0 , m=0, flag1=0;
	char str1[200], str2[200];
	str1[0]= '\0'; str2[0]= '\0';
	or_node *tmp = create_or_node();
	int len= strlen(str);
	while (m<len)
	{
		switch (str[i])
		{
			case '/':
			case '>':
			case '|':
				str1[j]= '\0'; str2[k]= '\0';
				j=0; k=0; flag=0;
				if ( str1[0]!='\0' && str2[0]!='\0')
				{

					if(strcmp(str1, "af"))		//if string is not af
					{
					
						tmp->fs[tmp->fs_count-1]->keys=g_list_append(tmp->fs[tmp->fs_count-1]->keys,g_strdup(str1));	

						tmp->fs[tmp->fs_count-1]->key_count ++;

						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup(str1), g_strdup(str2));						
					}


					else
					{
						tmp->fs[tmp->fs_count-1]->keys=g_list_append(tmp->fs[tmp->fs_count-1]->keys,g_strdup(str1));	

						tmp->fs[tmp->fs_count-1]->key_count ++; //af is treated as one key

						char attr[9][20] ;
						int m, len=strlen(str2), count=0, pos=0;
						for (m=0; m < len; m++)
						{
							if(str2[m]=='{' && flag1==0)
								flag1=1;
							else if(str2[m]=='}' && flag1==1)
								flag1=0;
							if( str2[m]==',' && flag1==0)
							{
								attr[count][pos]='\0';
								count ++;
								pos=0;
							}
							else 
							{
								attr[count][pos] = str2[m];
								pos++;
							}
						}
						attr[count][pos]='\0';
						
						//printf("attr--->%s,%s,%s,%s,%s,%s,%s,%s\n", attr[0],attr[1],attr[2], attr[3], attr[4], attr[5], attr[6], attr[7]);


						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("root"), g_strdup(attr[0]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("category"), g_strdup(attr[1]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("gender"), g_strdup(attr[2]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("number"), g_strdup(attr[3]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("pers"), g_strdup(attr[4]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("case"), g_strdup(attr[5]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("vib"), g_strdup(attr[6]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("tam"), g_strdup(attr[7]));	
					}
					str1[0]='\0';str2[0]='\0';			

				}
				break;

			case '=':
				flag=1;
				break;

			case '<':
				tmp->fs_count ++;
				tmp->fs[tmp->fs_count-1]= create_fs_struct();
				str1[0]='\0';
				str2[0]='\0';
				break;

			default :
				if (str[i]=='{' && flag1==0)
					flag1=1;
				else if(str[i]=='}' && flag1==1)
					flag1=0;
				if(flag==0)
					str1[j++]= str[i];
				else
					str2[k++]= str[i];
				break ;
		}
		i++;
		m++;
	}
	
	return tmp;

}

/* Creates  fs_struct from string */

fs_struct * read_fs( char str[])
{
	int i=0, j=0, k=0, flag=0 , m=0, flag1=0;
	char str1[200], str2[200];
	str1[0]= '\0'; str2[0]= '\0';
	fs_struct *fs = create_fs_struct();
	int len= strlen(str);
	while (m<len)
	{
		switch (str[i])
		{
			case '/':
			case '>':
				str1[j]= '\0'; str2[k]= '\0';
				j=0; k=0; flag=0;
				if ( str1[0]!='\0' && str2[0]!='\0')
				{

					if(strcmp(str1, "af"))		//if string is not af
					{
					
						fs->keys=g_list_append(fs->keys,g_strdup(str1));	

						fs->key_count ++;

						g_hash_table_insert( fs->hash, g_strdup(str1), g_strdup(str2));						
					}


					else
					{
						fs->keys=g_list_append(fs->keys,g_strdup(str1));	

						fs->key_count ++; //af is treated as one key

						char attr[9][20] ;
						int m, len=strlen(str2), count=0, pos=0;
						for (m=0; m < len; m++)
						{
							if(str2[m]=='{' && flag1==0)
								flag1=1;
							else if(str2[m]=='}' && flag1==1)
								flag1=0;
							if( str2[m]==',' && flag1==0)
							{
								attr[count][pos]='\0';
								count ++;
								pos=0;
							}
							else 
							{
								attr[count][pos] = str2[m];
								pos++;
							}
						}
						attr[count][pos]='\0';
						
						//printf("attr--->%s,%s,%s,%s,%s,%s,%s,%s\n", attr[0],attr[1],attr[2], attr[3], attr[4], attr[5], attr[6], attr[7]);


						g_hash_table_insert( fs->hash, g_strdup("root"), g_strdup(attr[0]));	
						g_hash_table_insert( fs->hash, g_strdup("category"), g_strdup(attr[1]));	
						g_hash_table_insert( fs->hash, g_strdup("gender"), g_strdup(attr[2]));	
						g_hash_table_insert( fs->hash, g_strdup("number"), g_strdup(attr[3]));	
						g_hash_table_insert( fs->hash, g_strdup("pers"), g_strdup(attr[4]));	
						g_hash_table_insert( fs->hash, g_strdup("case"), g_strdup(attr[5]));	
						g_hash_table_insert( fs->hash, g_strdup("vib"), g_strdup(attr[6]));	
						g_hash_table_insert( fs->hash, g_strdup("tam"), g_strdup(attr[7]));	
					}
					str1[0]='\0';str2[0]='\0';			

				}
				break;

			case '=':
				flag=1;
				break;

			case '<':
				break;
			case ' ':
			case '\t':
				break;
			default :
				if (str[i]=='{' && flag1==0)
					flag1=1;
				else if(str[i]=='}' && flag1==1)
					flag1=0;
				if(flag==0)
					str1[j++]= str[i];
				else
					str2[k++]= str[i];
				break ;
		}
		i++;
		m++;
	}
	
	return fs;

}

//returns or_node in string format
char * make_or_node_to_string ( or_node *OR)
{
	int i; 
	if (OR==NULL)
	{
		char *str= (char *)malloc(sizeof(char));
		str[0]='\0';		
		return str;
	}
	char *str=(char *)malloc(1000*sizeof(char));
	str[0]='\0';
	for (i=0 ; i< OR->fs_count; i++)
	{
		strcat ( str, make_fs_struct_to_string ( OR->fs[i] ) );
		if ( i < OR->fs_count-1 )
			strcat (str, "|");
	}
	return str;
}

// Returns the feature structure in string format


char *make_fs_struct_to_string ( fs_struct *fs)
{
	if(fs!=NULL)
	{
		int i;
		char *str=(char *)malloc(500*sizeof(char));
		strcpy(str,"<");
		GList *start=fs->keys;
		char *tmp;
		for (i=0; i< fs->key_count; i++)
		{
			tmp=(char *)g_list_nth_data(start, 0);
			if ( strcmp(tmp, "af") )	//if key is not "af"
			{
				strcat ( str, tmp);
				strcat ( str, "=");
				strcat ( str, (char *)g_hash_table_lookup(fs->hash, tmp) );
				strcat (str, "/");
			}
			else
			{
				strcat (str, "af=");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "root"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "category"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "gender"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "number"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "pers"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "case"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "vib"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "tam"));
				strcat (str,"/");
			}
			start=g_list_next(start);
		}
		if(fs->key_count==0)
		{
			str[strlen(str)]='>';
			str[strlen(str)+1]='\0';
		}
		else
		{
			str[strlen(str)-1]='>';
			str[strlen(str)]='\0';
		}
		return str;
	}
	else
	{
		char *str= (char *)malloc(sizeof(char));
		str[0]='\0';
		return str;
	}	
}



/*Prints the tree in SSF format */

void print_tree(node *tree)
{
	int n=0;
	node *tmp=(node *)g_list_nth_data(tree->childs,n);
	char ind[10];
	while(tmp!=NULL)
	{
		int_to_str ( n+1, ind);
		print_node(tmp, ind);
		n++;
		tmp=(node *)g_list_nth_data(tree->childs,n);
	}
}


/* prints the node with index starting from ind */

void print_node(node *tree ,char ind[])
{
	char *node_fs=  make_or_node_to_string(tree->OR);
	printf("%s\t%s\t%s\t%s\n",ind, tree->node_tkn, tree->node_tag, node_fs);
	free(node_fs);
	int i, n=0;
	char ind_tmp[100],ind_append[10];
	node *tmp= (node *)g_list_nth_data(tree->childs,0);	
	int len=strlen(ind);
	GList *start=tree->childs;
	while( tmp!=NULL )
	{
		
		strcpy(ind_tmp,ind);
		strcat(ind_tmp,".");
		int_to_str(n+1, ind_append);
		strcat(ind_tmp,	ind_append );
		print_node(tmp,ind_tmp);
		n++;
		tree->childs=g_list_next(tree->childs);
		tmp= (node *)g_list_nth_data(tree->childs,0);
	}
	tree->childs = start;
	if (strcmp(tree->node_tkn,"((")==0)
		printf("\t))\t\t\n");
	return;

}	

//prints the tree to file
void print_tree_to_file(node *tree, char *filename)
{
	FILE *f=fopen(filename, "w");
	int n=0;
	node *tmp=(node *)g_list_nth_data(tree->childs,n);
	char ind[10];
	while(tmp!=NULL)
	{
		int_to_str ( n+1, ind);
		print_node_to_file(tmp, ind,f);
		n++;
		tmp=(node *)g_list_nth_data(tree->childs,n);
	}
	fclose(f);
}

//prints the node to the file
void print_node_to_file(node *tree ,char ind[],FILE *f)
{
	char *node_fs=  make_or_node_to_string(tree->OR);
	fprintf(f, "%s\t%s\t%s\t%s\n",ind, tree->node_tkn, tree->node_tag, node_fs);
	free(node_fs);
	int i, n=0;
	char ind_tmp[100],ind_append[10];
	node *tmp= (node *)g_list_nth_data(tree->childs,0);	
	int len=strlen(ind);
	GList *start=tree->childs;
	while( tmp!=NULL )
	{
		
		strcpy(ind_tmp,ind);
		strcat(ind_tmp,".");
		int_to_str(n+1, ind_append);
		strcat(ind_tmp,	ind_append );
		print_node_to_file(tmp,ind_tmp,f);
		n++;
		tree->childs=g_list_next(tree->childs);
		tmp= (node *)g_list_nth_data(tree->childs,0);
	}
	tree->childs = start;
	if (strcmp(tree->node_tkn,"((")==0)
		fprintf(f,"\t))\t\t\n");
	return;

}

//prints the tree to fileptr
void print_tree_to_fileptr(node *tree, FILE *f)
{
	int n=0;
	node *tmp=(node *)g_list_nth_data(tree->childs,n);
	char ind[10];
	while(tmp!=NULL)
	{
		int_to_str ( n+1, ind);
		print_node_to_file(tmp, ind,f);
		n++;
		tmp=(node *)g_list_nth_data(tree->childs,n);
	}
}



/*only prints the attributes of this node*/

void print_attr_of_node(node *N)
{
	char *node_fs=make_or_node_to_string(N->OR);
	printf("%s\t%s\t%s", N->node_tkn, N->node_tag, node_fs);
	free(node_fs);	
}

//prints attrs of or node
void print_attr_of_or_node(or_node *OR)
{
	char *node_fs=make_or_node_to_string(OR);
	printf("%s", node_fs);
	free(node_fs);
}

/* Prints the node without any index */
void print_node_without_index(node *N)
{
	char *node_fs= make_or_node_to_string(N->OR);
	printf("%s\t%s\t%s\n", N->node_tkn, N->node_tag, node_fs );
	free(node_fs);
	node *tmp;
	int i;
	GList *start=N->childs;
	for (i=0; i< N->child_count; i++)
	{
		if(i!=0)
			N->childs = g_list_next(N->childs);
		tmp=(node *)g_list_nth_data(N->childs, 0);
		print_node_without_index(tmp);
	}
	N->childs=start;
	if (strcmp(N->node_tkn,"((")==0)
		printf("\t))\t\t\n");
	return;

}
