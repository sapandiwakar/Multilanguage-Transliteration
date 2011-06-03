#include<stdlib.h> 

/************         Data structure of Shakti Standard Format     *************/
/* This function was written by M.R.Chethan for the semester project*/

/* Initialise the datastructure of circle */
/* circle contains the tree structure of CML format with all the tbis,sentenceids,docids and segments etc... if they are in CML format or else it will only contain the sentence ids */

circle *create_circle(circle *parent)
{
	circle *tmp=(circle *)malloc(sizeof(circle));
	tmp->id=0;
	tmp->number=0;
	tmp->name[0]='\0';
	tmp->segment[0]='\0';
	tmp->bullet[0]='\0';
	tmp->encode[0]='\0';
	tmp->SSFVersion=2.0;
	tmp->number_of_childs=0;
	tmp->start_child=0;
	tmp->childs=NULL;
	tmp->sentences=0;
	if(parent!=NULL)
		tmp->parent=parent;
	else
		tmp->parent=NULL;
	return tmp;
}

/* Datastructure defined */
/* old work which was done by Siva Reddy */

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
/*
void read_ssf_from_file (node *tree, char filename[])	//reads a ssf from file into node tree
{	
	FILE *f;
	f=fopen(filename,"r");
	read_ssf(tree,f);	
	fclose(f);
}
*/

/*----------read ssf from FILE *f--------*/
/* This function is used to handle the new version v2  reading */
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

		if(ch!='\t' && ch!='\n' && ch!='#')
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
	
	}
	
}

/* creates or_node from  string */
 
or_node * read_or_node( char str[])
{
	int i=0, j=0, k=0, flag=0 ;
	char str1[200], str2[200];
	str1[0]= '\0'; str2[0]= '\0';
	or_node *tmp = create_or_node();
	while (str[i]!='\0')
	{
		switch (str[i])
		{
			case '>':
			case ' ':
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

						char attr[8][20] ;
						int m, len=strlen(str2), count=0, pos=0;
						for (m=0; m < len; m++)
						{
							if( str2[m]==',' )
							{
								attr[count][pos]='\0';
								count ++;
								pos=0;
							}
							else if( str2[m]!='\'')
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
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("something"), g_strdup(attr[6]));	
						g_hash_table_insert( tmp->fs[tmp->fs_count-1]->hash, g_strdup("else"), g_strdup(attr[7]));	
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
				if(flag==0)
					str1[j++]= str[i];
				else
					str2[k++]= str[i];
				break ;
		}
		i++;
	}
	
	return tmp;

}

/* Creates  fs_struct from string */

fs_struct * read_fs( char str[])
{
	int i=0, j=0, k=0, flag=0 ;
	char str1[200], str2[200];
	str1[0]= '\0'; str2[0]= '\0';
	fs_struct *fs = create_fs_struct();
	while (str[i]!='\0')
	{
		switch (str[i])
		{
			case ' ':
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

						char attr[8][20] ;
						int m, len=strlen(str2), count=0, pos=0;
						for (m=0; m < len; m++)
						{
							if( str2[m]==',' )
							{
								attr[count][pos]='\0';
								count ++;
								pos=0;
							}
							else if (str[2]!='\'')
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
						g_hash_table_insert( fs->hash, g_strdup("something"), g_strdup(attr[6]));	
						g_hash_table_insert( fs->hash, g_strdup("else"), g_strdup(attr[7]));	
					}
					str1[0]='\0';str2[0]='\0';			

				}
				break;

			case '=':
				flag=1;
				break;

			case '<':
				break;

			default :
				if(flag==0)
					str1[j++]= str[i];
				else
					str2[k++]= str[i];
				break ;
		}
		i++;
	}
	
	return fs;

}


char * make_or_node_to_string ( or_node *OR)
{
	int i; 
	if (OR==NULL)
	{
		char *str=(char *)malloc(sizeof(char));
		str[0]='\0';
		return str;
	}
	char *str=(char *)malloc(1000*sizeof(char));
	str[0]='\0';
	for (i=0 ; i< OR->fs_count; i++)
	{
		strcat ( str, make_fs_struct_to_string ( OR->fs[i] ) );
		if ( i < OR->fs_count-1 )
			strcat (str, " ");
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
		strcpy(str,"<fs ");
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
				strcat (str, " ");
			}
			else
			{
				strcat (str, "af=\'");
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
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "something"));
				strcat (str,",");
				strcat (str, (char *)g_hash_table_lookup(fs->hash, "else"));
				strcat (str,"\' ");
			}
			start=g_list_next(start);
		}
		str[strlen(str)-1]='>';
		str[strlen(str)]='\0';
		return str;
	}
	else
	{
		char *str=(char *)malloc(sizeof(char));
		str[0]='\0';
		return str;
	}	
}



/*Prints the tree in SSF format in version 2*/

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
/*
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
*/
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
		strcat(ind_tmp, ind_append );
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
/* This code is written by M.R.Chethan on 26 May 2009 */




/* This function takes an file as input and reads the file into the memory */

void read_ssf_from_file(circle *start,char *filename)
{
	FILE *fp,*fp1;
	fp=fopen(filename,"r");
	char a,scan[10000];
	int i=0,end=0,write_into_file=0;
	strcat(start->name,"ROOT:");
	strcat(start->name,filename);
	start->id=1;
	int sentences=0,initial_state=1,document_state=0,head_state=0,body_state=0,text_state=0,tb_state=0,sentence_state=0;
	/* read the file sequentially will work for both CML And multiple sentences */

	while(1)
	{
		char ch;
		if(fscanf(fp,"%c",&ch)==EOF)
			end=1;
		if(ch=='\n'||end==1)
		{
			scan[i]='\0';
			char temp_scan[1000];
			int k=0,m=0;
			/* first remove all the spaces and tabs from the tags and create an string out of it ex :<documentdocid="5"> after  removing*/
			for(k=0;k<strlen(scan);k++)
				if(scan[k]!=' '&&scan[k]!='\t')
					if(scan[k]=='"')
					{
						temp_scan[m++]=scan[k];
						temp_scan[m++]=' ';
					}
					else	
						temp_scan[m++]=scan[k];
			temp_scan[m]='\0';
			char segment[8],bullet[8],encode[50];
			float SSFVersion=2.0;
			/* check for the syntax of document tag in input file*/
			if(strstr(temp_scan,"<documentdocid=\"")!=NULL && initial_state==1)
			{
				int docid=1,docnumber=1;
				sscanf(temp_scan,"<documentdocid=\" %d\" docnumber=\" %d\" >",&docid,&docnumber);
				circle *temp=create_circle(start);
				strcat(temp->name,"document");
				temp->id=docid;
				temp->number=docnumber;
				if(start->number_of_childs==0)
					start->start_child=docid;
				start->number_of_childs++;
				start->childs=g_list_append(start->childs,(void *)temp);
				start=((circle *)g_list_nth_data(start->childs,docid-(start->start_child)));
				document_state=1;initial_state=0;
			/* if present set the document_set=1 */
			}

			/* check for the syntax of body tag in input file */
			else if(strstr(temp_scan,"<body>")!=NULL&& document_state)
			{
				int bodyid=1;
				circle *temp=create_circle(start);
				strcat(temp->name,"body");
				temp->id=bodyid;
				if(start->number_of_childs==0)
					start->start_child=bodyid;
				start->number_of_childs++;
				start->childs=g_list_append(start->childs,(void *)temp);
				start=((circle*)g_list_nth_data(start->childs,bodyid-(start->start_child)));
				body_state=1;document_state=0;
			/* if present set the body_state=1 */
			}
			/* check for the syntax of body in input file */

			else if(strstr(temp_scan,"<body")!=NULL&& document_state)
			{
				int bodyid=1;	
				sscanf(temp_scan,"<bodyencode=\" %s SSFVersion=\" %f\" >",encode,&SSFVersion);
				encode[strlen(encode)-1]='\0';
				//printf("encode:%s SSFVersion:%f\n",encode,SSFVersion);
				circle *temp=create_circle(start);
				strcat(temp->name,"body");
				strcat(temp->encode,encode);
				temp->SSFVersion=SSFVersion;
				temp->id=bodyid;
				if(start->number_of_childs==0)
					start->start_child=bodyid;
				start->number_of_childs++;
				start->childs=g_list_append(start->childs,(void *)temp);
				start=((circle*)g_list_nth_data(start->childs,bodyid-(start->start_child)));
				body_state=1;document_state=0;
			
				/* if present set the body_state=1 */
			}

			/* check for the syntax of tbnumber in input file */
			else if(strstr(temp_scan,"<tbnumber=\"")!=NULL && body_state)
			{

				int number=1;
				char tmp[100];
				sscanf(temp_scan,"<tbnumber=\" %d\" segment=\" %s bullet=\" %s",&number,segment,bullet);
				segment[strlen(segment)-1]='\0';
				bullet[strlen(bullet)-2]='\0';
				circle * temp=create_circle(start);
				strcat(temp->name,"tb");
				temp->number=number;
				strcat(temp->segment,segment);
				strcat(temp->bullet,bullet);
				if(start->number_of_childs==0)
					start->start_child=number;
				start->number_of_childs++;
				start->childs=g_list_append(start->childs,(void *)temp);
				start=((circle *)g_list_nth_data(start->childs,number-(start->start_child)));
				tb_state=1;body_state=0;
			}

			/* check for the syntax of text in input file */
			else if(strstr(temp_scan,"<text>")!=NULL&& tb_state)
			{
				int number=1;
				/* code when segment=yes */
				if(strcmp(segment,"yes")==0)
				{
					circle *temp1=create_circle(start);
					strcat(temp1->name,"text");
					if(start->number_of_childs==0)
						start->start_child=number;
					start->number_of_childs++;
					start->childs=g_list_append(start->childs,(void *)temp1);
					start=((circle*)g_list_nth_data(start->childs,number-1));
					if(start->number_of_childs==0)
						start->start_child=number;
					start->number_of_childs++;
					node * temp=create_tree();
					start->childs=g_list_append(start->childs,(void *)temp);


					fp1=fopen("temporary_file","w+");
					write_into_file=1;


				}
				/* else if segment=no*/
				else if(strcmp(segment,"no")==0)
				{
					circle * temp=create_circle(start);
					if(start->number_of_childs==0)
						start->start_child=number;
					start->number_of_childs++;
					strcat(temp->name,"text");
					start->childs=g_list_append(start->childs,(void *)temp);
					start=((circle *)g_list_nth_data(start->childs,number-(start->start_child)));
				}
				text_state=1;tb_state=0;
			}

			/* check for the syntax of Sentenceid in input file*/
			else if(strstr(temp_scan,"<Sentenceid=\"")!=NULL)
		//	else if(strstr(temp_scan,"<Sentenceid=\"")!=NULL&&	text_state)
			{	
				int id;
				sscanf(temp_scan,"<Sentenceid=\" %d\" >",&id);
				circle *temp1=create_circle(start);
				if(start->number_of_childs==0)
					start->start_child=id;
				start->number_of_childs++;
				strcat(temp1->name,"Sentence");
				temp1->id=id;
				start->childs=g_list_append(start->childs,(void *)temp1);
				start=((circle*)g_list_nth_data(start->childs,id-(start->start_child)));
				start->number_of_childs++;
				node * temp=create_tree();
				sentences++;
				start->childs=g_list_append(start->childs,(void*)temp);
				fp1=fopen("temporary_file","w+");	
				write_into_file=1;
				sentence_state=1;text_state=0;
				/* set the sentence_state=1 */
			}

			/* check for the closing tag of Sentence */
			else if(strstr(temp_scan,"</Sentence>")!=NULL)
		//	else if(strstr(temp_scan,"</Sentence>")!=NULL && sentence_state)
			{
				if(write_into_file==1)
				{
					fseek(fp1,0,SEEK_SET);
					read_ssf(((node *)g_list_nth_data(start->childs,0)),fp1); 
					write_into_file=0;
					fclose(fp1);
				}
					start=start->parent;
					text_state=1;sentence_state=0;
				/* set the sentence_state=0 */
			}

			/* check for the closing tag of text */
			else if(strstr(temp_scan,"</text>")!=NULL && text_state)
			{	
				if(write_into_file==1)
				{	
					fseek(fp1,0,SEEK_SET);
					read_ssf(((node *)g_list_nth_data(start->childs,0)),fp1); // call with this
					fclose(fp1);
					write_into_file=0;		
				}
				sentences++;
				start=start->parent;
				tb_state=1;text_state=0;
			}

			/* check for the closing tag of tb */
			else if(strstr(temp_scan,"</tb>")!=NULL && tb_state)
			{	
				start=start->parent;
				body_state=1;tb_state=0;
			}

			/* check for the closing tag of body */
			else if(strstr(temp_scan,"</body>")!=NULL && body_state)
			{
				start=start->parent;
				document_state=1;body_state=0;
			}

			/* check for the closing tag of document */
			else if(strstr(temp_scan,"</document>")!=NULL && document_state)
			{
				start=start->parent;
				initial_state=1;document_state=0;
			}
			else if(write_into_file==1)
				fprintf(fp1,"%s\n",scan);
			i=0;
			if(end==1)
				break;
		}
		else
			scan[i++]=ch;

	}
	/* count the number of sentences in the file and have it in start->sentences*/
	system(" rm -rf temporary_file");
	start->sentences=sentences;
	fclose(fp);
}

/* This function will read the datastructure and print into the file */

void print_tree_to_file(circle * start,char *filename)
{
	FILE *fp,*fp1;
	char inputfilename[50];
	sscanf(start->name,"ROOT:%s",inputfilename);
	fp=fopen(inputfilename,"r");
	fp1=fopen(filename,"w");
	int print=0;
	char a,scan[1000];
	int i=0,end=0,write_into_file=0;
	int initial_state=1,document_state=0,head_state=0,body_state=0,text_state=0,tb_state=0,sentence_state=0;
	/* The procedure followed is just the same as the read_file_into_tree */
	while(1)
	{
		char ch;
		if(fscanf(fp,"%c",&ch)==EOF)
			end=1;
		if(ch=='\n'||end==1)
		{
			scan[i]='\0';
			char temp_scan[1000];
			int k=0,m=0;
			for(k=0;k<strlen(scan);k++)
				if(scan[k]!=' '&&scan[k]!='\t')
					if(scan[k]=='"')
					{
						temp_scan[m++]=scan[k];
						temp_scan[m++]=' ';
					}
					else	
						temp_scan[m++]=scan[k];
			temp_scan[m]='\0';
			char segment[8],bullet[8];
			if(strstr(temp_scan,"<documentdocid=\"")!=NULL && initial_state==1)
			{
				int docid=1,docnumber=1;
				sscanf(temp_scan,"<documentdocid=\" %d\" docnumber=\" %d\" >",&docid,&docnumber);
				fprintf(fp1,"%s\n",scan);
				start=((circle *)g_list_nth_data(start->childs,docid-(start->start_child)));
				document_state=1;initial_state=0;
			}

			else if(strstr(temp_scan,"<body>")!=NULL&& document_state)
			{
				int bodyid=1;
				fprintf(fp1,"%s\n",scan);
				start=((circle*)g_list_nth_data(start->childs,bodyid-(start->start_child)));
				body_state=1;document_state=0;
			}

			else if(strstr(temp_scan,"<body")!=NULL&& document_state)
			{
				int bodyid=1;
				fprintf(fp1,"%s\n",scan);
				start=((circle*)g_list_nth_data(start->childs,bodyid-(start->start_child)));
				body_state=1;document_state=0;
			}

			else if(strstr(temp_scan,"<tbnumber=\"")!=NULL && body_state)
			{
				int number=1;
				sscanf(temp_scan,"<tbnumber=\" %d\" segment=\" %s bullet=\" %s",&number,segment,bullet);
				fprintf(fp1,"%s\n",scan);
				segment[strlen(segment)-1]='\0';
				bullet[strlen(bullet)-2]='\0';
				start=((circle *)g_list_nth_data(start->childs,number-(start->start_child)));
				tb_state=1;body_state=0;
			}

			else if(strstr(temp_scan,"<text>")!=NULL&& tb_state)
			{
				int number=1;
				fprintf(fp1,"%s\n",scan);
				if(strcmp(segment,"yes")==0)
				{
					start=((circle*)g_list_nth_data(start->childs,number-(start->start_child)));
					print=1;
				}
				else if(strcmp(segment,"no")==0)
				{
					start=((circle*)g_list_nth_data(start->childs,number-(start->start_child)));
				}
				text_state=1;tb_state=0;
			}

			else if(strstr(temp_scan,"<Sentenceid=\"")!=NULL)
	//		else if(strstr(temp_scan,"<Sentenceid=\"")!=NULL&&	text_state)
			{	
				int id;
				sscanf(temp_scan,"<Sentenceid=\" %d\" >",&id);
				fprintf(fp1,"%s\n",scan);
				print=1;
				start=((circle*)g_list_nth_data(start->childs,id-(start->start_child)));
				sentence_state=1;text_state=0;
			}

			else if(strstr(temp_scan,"</Sentence>")!=NULL)
	//		else if(strstr(temp_scan,"</Sentence>")!=NULL && sentence_state)
			{
				if(print==1)
					{
						print=0;
						print_tree_to_fp((node *)g_list_nth_data(start->childs,0),fp1);
					}
				fprintf(fp1,"%s\n",scan);
				start=start->parent;
				text_state=1;sentence_state=0;
			}

			else if(strstr(temp_scan,"</text>")!=NULL && text_state)
			{	
				
				if(print==1)
				{
					print=0;	
					print_tree_to_fp(((node*)g_list_nth_data(start->childs,0)),fp1);
				}
				fprintf(fp1,"%s\n",scan);
				start=start->parent;
				tb_state=1;text_state=0;
			}

			else if(strstr(temp_scan,"</tb>")!=NULL && tb_state)
			{	
				start=start->parent;
				body_state=1;tb_state=0;
				fprintf(fp1,"%s\n",scan);
			}

			else if(strstr(temp_scan,"</body>")!=NULL && body_state)
			{
				start=start->parent;
				document_state=1;body_state=0;
				fprintf(fp1,"%s\n",scan);
			}
			else if(strstr(temp_scan,"</document>")!=NULL && document_state)
			{
				start=start->parent;
				initial_state=1;document_state=0;
				fprintf(fp1,"%s\n",scan);
			}
			else if(end==0 &&print==0)
				fprintf(fp1,"%s\n",scan);
			i=0;
			if(end==1 && print==0)
			{
				fprintf(fp1,"%s",scan);
				break;
			}
		}
		else
			scan[i++]=ch;
	}
}
/* This function is used to print a datastructure to a file pointer */
void print_tree_to_fp(node *tree, FILE *f)
{
	int n=0;
	node *tmp=g_list_nth_data(tree->childs,n);
	char ind[10];
	while(tmp!=NULL)
	{
		int_to_str ( n+1, ind);
		print_node_to_file(tmp, ind,f);
		n++;
		tmp=g_list_nth_data(tree->childs,n);
	}
}
/* This function will traverse through the datastructure and put all the pointers to the sentences into temp variable and returns the number of sentences*/
int traverse_tree(circle *start,node **temp,int count)
{
        int i;
	/* Go through all the childs in the datastructure recursively and check for the Sentence tag name */
        for(i=0;i<start->number_of_childs;i++)
        {
                if(strcmp(start->name,"Sentence")==0)
                        temp[count++]=((node *)g_list_nth_data(start->childs,i));
                else if(strcmp(start->name,"text")==0 && strcmp((start->parent)->segment,"yes")==0)
                        temp[count++]=((node *)g_list_nth_data(start->childs,i));
                else
                        count=traverse_tree((circle *)g_list_nth_data(start->childs,i),temp,count);
        }
        return count;
}
/* This function returns the nodes having particular tbids */
int nodes_tb(circle *start,node **temp,int count,int tbid_start,int tbid_end)
{
        int i;
        for(i=0;i<start->number_of_childs;i++)
        {
                if(strcmp(start->name,"Sentence")==0 && ((start->parent)->parent)->number>=tbid_start && ((start->parent)->parent)->number<=tbid_end)
                        temp[count++]=((node *)g_list_nth_data(start->childs,i));
                else if(strcmp(start->name,"text")==0 && (start->parent)->number>=tbid_start && (start->parent)->number<=tbid_end && strcmp((start->parent)->segment,"yes")==0)
                        temp[count++]=((node *)g_list_nth_data(start->childs,i));
                else
                        count=nodes_tb((circle *)g_list_nth_data(start->childs,i),temp,count,tbid_start,tbid_end);
        }
        return count;

}
/* This function returns the nodes with particular bodyid,tbid and sentenceid */
node *particular_node(circle *start,int docid,int bodyid,int tbid,int sentenceid)
{
	circle *temp=start;
	if(docid<=temp->number_of_childs && docid>=1)
		temp=(circle *)g_list_nth_data(temp->childs,docid-1);
	if(bodyid<=temp->number_of_childs && bodyid>=1)
		temp=(circle *)g_list_nth_data(temp->childs,bodyid-1);
	if(tbid<=temp->number_of_childs && tbid>=1)
		temp=(circle *)g_list_nth_data(temp->childs,tbid-1);
	temp=(circle *)g_list_nth_data(temp->childs,0);
	if(sentenceid==0)
		return (node *)	g_list_nth_data(temp->childs,0);
	else if(sentenceid <= temp->number_of_childs+temp->start_child && sentenceid>=temp->start_child)
	{
		temp=(circle *)g_list_nth_data(temp->childs,sentenceid-(temp->start_child));
		return (node *)g_list_nth_data(temp->childs,0);
	}
}
/* returns the number of sentences in the datastructure */
int sentences(circle * start)
{
	return start->sentences;
}




/* This code was written by M.R.Chethan on 26 May 2009 */
