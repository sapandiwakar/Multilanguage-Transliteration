#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<getopt.h>
#include "preprocessor.h"
#include "wx_utf8_ben.h"
#include "wx_utf8_hin.h"
#include "wx_utf8_kan.h"
#include "wx_utf8_mal.h"
#include "wx_utf8_pan.h"
#include "wx_utf8_tam.h"
#include "wx_utf8_tel.h"
#include "utf8_wx_ben.h"
#include "utf8_wx_hin.h"
#include "utf8_wx_kan.h"
#include "utf8_wx_mal.h"
#include "utf8_wx_pan.h"
#include "utf8_wx_tam.h"
#include "utf8_wx_tel.h"

unsigned char* convert_wx2utf (unsigned char* my_string);
unsigned char* convert_utf2wx (unsigned char* my_string);
char* wx_utf8_tgt(char* word);
void set_flag (char* argv);

static int help_flag=0;

int flag_ben = 0;
int flag_hin = 0;
int flag_kan = 0;
int flag_mal = 0;
int flag_pan = 0;
int flag_tam = 0;
int flag_tel = 0;

char *tgt = NULL; 
int main(int argc ,char *argv[])
{
	char *to_convert = NULL;
        char *mode = NULL;
        char *input_file= NULL;
        char *output_file= NULL;

	int bytes_read;									// Variable to store the number of bytes read.
  	int nbytes = 50000;								// Variable to specify maximum number of bytes to read
  	char *my_string = (char *) malloc (nbytes + 1);					// Variable to store input string
	char *tagged;									// Variable to store the preprocessed string	
	char *converted_utf, *converted_wx;

	FILE *fin;
	FILE *fout;
	FILE *fout_mode1;
	FILE *fout_mode2;
	FILE *fout_mode3;
	int mode_flag = 0;

        int c;

       	while (1)
       	{
        	static struct option long_options[] =
               	{
                	/* These options set a flag. */
                       	{"help", no_argument,       &help_flag, 1},
                       	/* These options don't set a flag.
                       	   We distinguish them by their indices. */
                       	{"tlang",     required_argument, 0, 'd'},
                       	{"to_convert", required_argument, 0, 't'},
                       	{"mode",  required_argument, 0, 'm'},
                       	{"input_file",  required_argument, 0, 'i'},
                       	//{"test",  required_argument, 0, 't'},
                       	{"output_file",    required_argument, 0, 'o'},
                       	{0, 0, 0, 0}
               	};
               	/* getopt_long stores the option index here. */
               	int option_index = 0;

               	c = getopt_long (argc, argv, "d:t:i:o", long_options, &option_index);

               /* Detect the end of the options. */
              	if (c == -1)
               		break;

              	switch (c)
               	{
                       	case 0:
                        	/* If this option set a flag, do nothing else now. */
                               	if (long_options[option_index].flag != 0)
                                	break;
                               	printf ("option %s", long_options[option_index].name);
                               	if (optarg)
                                	printf (" with arg %s", optarg);
                               	printf ("\n");
                               	break;

                       case 'd':
                               tgt=optarg;
                               break;
                       case 't':
                                to_convert=optarg;
				set_flag(to_convert);
                                break;

                       case 'm':
                               mode=optarg;
			       if (!strcmp(mode, "debug")) {
					system("mkdir -p out.tmp");
					fout_mode1 = fopen("out.tmp/tagged", "w");
					fout_mode2 = fopen("out.tmp/converted_wx", "w");
					fout_mode3 = fopen("out.tmp/converted_utf", "w");
					mode_flag = 1;
			       } else {
				       mode_flag = 0;
			       }
                               break;
                       case 'i':
                               input_file=optarg;
                               if(input_file==NULL)
                               {
                                       printf("Error: Please specify the input file\n");
                                       exit(0);
                               } else {
					fin = fopen (input_file, "r");
				}
                               break;

                       case 'o':
                               output_file=optarg;
                               if(output_file==NULL)
                               {
                                       printf("Error: Please specify the output file\n");
                                       exit(0);
                               } else {
					fout = fopen (output_file, "w");
				}
                               break;
                       default:
                               abort ();
               }
       }

       if (help_flag)
       {
               printf("MultiLanguage Transliteration (6th July 2009)\n");
               printf("usage: ./transilteration  --tlang=" " --mode=" " --to_convert=" " --input_file=" " --output_file\n");
               exit(1);
       }

       if (to_convert == NULL) {
	       set_flag("all");
       }
	if (tgt == NULL) {
		printf("Please Specify target language\n");
		exit(1);
	}

        while(1){
	  	my_string = (char *) malloc (nbytes + 1);
	
		if (my_string == NULL) { 
			printf("Can't allocate memory\n"); 
			break;
		}

		if (input_file != NULL) {
			bytes_read = getline (&my_string, &nbytes, fin);		// Take a line of input from file
		} else {
			bytes_read = getline (&my_string, &nbytes, stdin);		// Take a line of input from stdin
		}

	  	if (bytes_read == -1) {break; }
	  	else {
			tagged = preprocess(my_string);
			if (mode_flag)
				fprintf(fout_mode1,"%s", tagged);
			converted_wx = convert_utf2wx(tagged);
			if (mode_flag)
				fprintf(fout_mode2, "%s", converted_wx);
			converted_utf = convert_wx2utf(converted_wx);
			if (output_file != NULL) {
				fprintf(fout, "%s", converted_utf);							// Print the converted line
			} else {
				printf("%s", converted_utf);							// Print the converted line
			}
			if (mode_flag)
				fprintf(fout_mode3, "%s", converted_utf);
			free(my_string);
		}	
	
	}

	return 0;
}

unsigned char* convert_utf2wx (unsigned char* my_string)
{	
	unsigned char ch;
	unsigned char *converted;
	unsigned char *converted_line = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *converted_line_untagged = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *word = (char *) malloc(strlen(my_string)*6 + 1);
	char tag[4];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	while(*(my_string+i) != '\0') {		
		ch = *(my_string+i);
		if (ch == '~') {			
			j = 0;
			tag[0] = *(my_string+i+1);
			tag[1] = *(my_string+i+1+1);
			tag[2] = *(my_string+i+1+1+1);
			tag[3] = '\0';
			i += 5;
			while (*(my_string+i) != '\0'){
				ch = *(my_string+i);
				if (ch != ' ') {
					sprintf(word+j, "%c", ch);
					j ++;
					i ++;
				} else {
					if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
						converted = utf_wx_ben(word);
					} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
						converted = utf_wx_hin(word);
					} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
						converted = utf_wx_kan(word);
					} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
						converted = utf_wx_pan(word);
					} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
						converted = utf_wx_mal(word);
					} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
						converted = utf_wx_tam(word);
					} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
						converted = utf_wx_tel(word);
					} else {
						converted = word;
					}
					i ++;
					while (*(my_string+i) == ' ' && *(my_string+i) != '\0') {
						i ++;
					}
					break;
				}
			}
			if (*(my_string+i) == '\0') {
				if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
					converted = utf_wx_ben(word);
				} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
					converted = utf_wx_hin(word);
				} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
					converted = utf_wx_kan(word);
				} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
					converted = utf_wx_pan(word);
				} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
					converted = utf_wx_mal(word);
				} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
					converted = utf_wx_tam(word);
				} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
					converted = utf_wx_tel(word);
				} else {
					converted = word;
				}
				sprintf(converted_line+k, "~%s~%s",tag, converted);
				k += 2 + 3 + strlen(converted);
				sprintf(converted_line_untagged+l, "%s", converted);
				l += strlen(converted);
			} else {
				sprintf(converted_line+k, "~%s~%s ",tag, converted);
				k += 3 + 3 + strlen(converted);
				sprintf(converted_line_untagged+l, "%s ", converted);
				l += 1 + strlen(converted);
			}
		} else {
			sprintf(converted_line+k, "%c", ch);
			i ++;
			k ++;
		}
	}
	return converted_line;
}
	
void set_flag (char* argv)
{
	char ch;
	char *to_convert_wx2utf = (char*)malloc(100);
	int i = 0;
	int j = 0;

	while(*(argv+i) != '\0'){
		ch = *(argv+i);
		if (ch != ','){
			sprintf(to_convert_wx2utf+j, "%c", ch);
			j ++;
			i ++;
		} else {
			if (!strcmp(to_convert_wx2utf,"ben")) {
				flag_ben = 1;
			} else if (!strcmp(to_convert_wx2utf,"hin")) {
				flag_hin = 1;
			} else if (!strcmp(to_convert_wx2utf,"kan")) {
				flag_kan = 1;
			} else if (!strcmp(to_convert_wx2utf,"pan")) {
				flag_pan = 1;
			} else if (!strcmp(to_convert_wx2utf,"mal")) {
				flag_mal = 1;
			} else if (!strcmp(to_convert_wx2utf,"tam")) {
				flag_tam = 1;
			} else if (!strcmp(to_convert_wx2utf,"tel")) {
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "all")) {
				flag_ben = 1;
				flag_hin = 1;
				flag_kan = 1;
				flag_mal = 1;
				flag_pan = 1;
				flag_tam = 1;
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "none")) {
				flag_ben = 0;
				flag_hin = 0;
				flag_kan = 0;
				flag_mal = 0;
				flag_pan = 0;
				flag_tam = 0;
				flag_tel = 0;
			}
			i ++;
			j = 0;
	
		}
		
		if (*(argv+i) == '\0'){
			if (!strcmp(to_convert_wx2utf,"ben")) {
				flag_ben = 1;
			} else if (!strcmp(to_convert_wx2utf,"hin")) {
				flag_hin = 1;
			} else if (!strcmp(to_convert_wx2utf,"kan")) {
				flag_kan = 1;
			} else if (!strcmp(to_convert_wx2utf,"pan")) {
				flag_pan = 1;
			} else if (!strcmp(to_convert_wx2utf,"mal")) {
				flag_mal = 1;
			} else if (!strcmp(to_convert_wx2utf,"tam")) {
				flag_tam = 1;
			} else if (!strcmp(to_convert_wx2utf,"tel")) {
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "all")) {
				flag_ben = 1;
				flag_hin = 1;
				flag_kan = 1;
				flag_mal = 1;
				flag_pan = 1;
				flag_tam = 1;
				flag_tel = 1;
			} else if (!strcmp(to_convert_wx2utf, "none")) {
				flag_ben = 0;
				flag_hin = 0;
				flag_kan = 0;
				flag_mal = 0;
				flag_pan = 0;
				flag_tam = 0;
				flag_tel = 0;
			}
		}
	}
}		

unsigned char* convert_wx2utf (unsigned char* my_string)
{	
	unsigned char ch;
	unsigned char *converted_wx2utf;
	unsigned char *converted_wx2utf_line = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *converted_wx2utf_line_untagged = (char*)malloc(strlen(my_string)*6 + 1);
	unsigned char *word = (char *) malloc(strlen(my_string)*6 + 1);
	char tag[4];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	while(*(my_string+i) != '\0') {		
		ch = *(my_string+i);
		if (ch == '~') {			
			j = 0;
			tag[0] = *(my_string+i+1);
			tag[1] = *(my_string+i+1+1);
			tag[2] = *(my_string+i+1+1+1);
			tag[3] = '\0';
			i += 5;
			while (*(my_string+i) != '\0'){
				ch = *(my_string+i);
				if (ch != ' ') {
					sprintf(word+j, "%c", ch);
					j ++;
					i ++;
				} else {
					if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else {
						converted_wx2utf = word;
					}
					i ++;
					while (*(my_string+i) == ' ' && *(my_string+i) != '\0') {
						i ++;
					}
					break;
				}
			}
			if (*(my_string+i) == '\0') {
					if ( (!strcmp(tag,"ben")) && (flag_ben) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"hin")) && (flag_hin) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"kan")) && (flag_kan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"pan")) && (flag_pan) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"mal")) && (flag_mal) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tam")) && (flag_tam) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else if ( (!strcmp(tag,"tel")) && (flag_tel) ) {
						converted_wx2utf = wx_utf8_tgt(word);
					} else {
						converted_wx2utf = word;
					}
					sprintf(converted_wx2utf_line+k, "~%s~%s",tag, converted_wx2utf);
					k += 2 + 3 + strlen(converted_wx2utf);
					sprintf(converted_wx2utf_line_untagged+l, "%s", converted_wx2utf);
					l += strlen(converted_wx2utf);
			} else {
				sprintf(converted_wx2utf_line+k, "~%s~%s ",tag, converted_wx2utf);
				k += 3 + 3 + strlen(converted_wx2utf); 
				sprintf(converted_wx2utf_line_untagged+l, "%s ", converted_wx2utf);
				l += 1 + strlen(converted_wx2utf);
			}
		} else {
			sprintf(converted_wx2utf_line+k, "%c", ch);
			i ++;
			k ++;
		}
	}
	return converted_wx2utf_line_untagged;
}

char* wx_utf8_tgt(char* word)
{
	char* converted_wx2utf;
	if ( (!strcmp(tgt, "ben")) ) {
		converted_wx2utf = wx_utf8_ben(word);
	} else if ( (!strcmp(tgt, "hin")) ) {
		converted_wx2utf = wx_utf8_hin(word);
	} else if ( (!strcmp(tgt, "kan")) ) {
		converted_wx2utf = wx_utf8_kan(word);
	} else if ( (!strcmp(tgt, "mal")) ) {
		converted_wx2utf = wx_utf8_mal(word);
	} else if ( (!strcmp(tgt, "pan")) ) {
		converted_wx2utf = wx_utf8_pan(word);
	} else if ( (!strcmp(tgt, "tam")) ) {
		converted_wx2utf = wx_utf8_tam(word);
	} else if ( (!strcmp(tgt, "tel")) ) {
		converted_wx2utf = wx_utf8_tel(word);		
	} else {
		converted_wx2utf = word;
	}

	return converted_wx2utf;
}
	
