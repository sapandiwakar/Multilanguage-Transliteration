#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char* preprocess(unsigned char* my_string);
char* find_lang(unsigned char *utf_string);
/*
int main()
{
	int bytes_read;
  	int nbytes = 10000;
  	char *my_string;

        while(1){
	  	my_string = (char *) malloc (nbytes + 1);
	
		if (my_string == NULL) { 
			printf("Can't allocate memory\n"); 
			break;
		}

		bytes_read = getline (&my_string, &nbytes, stdin);

	  	if (bytes_read == -1) {break; }
	  	else {
			printf("%s",preprocess(my_string));
		}
		
		free(my_string);
	   }

  	return 0;
}
*/
unsigned char* preprocess(unsigned char* my_string)
{
	unsigned  char ch;
	unsigned char* word = (char *) malloc(strlen(my_string)) ;
	unsigned char* word_line = (char *) malloc(strlen(my_string)*5);
	int i = 0;
	int j = 0;
	int k = 0;

	while(*(my_string+i) != '\0'){
		ch = *(my_string+i);
		sprintf(word+k, "%c", ch);
		k ++;
		i ++;
		if (ch == ' ') {
			char* converted_word;
			converted_word = find_lang(word);
			sprintf(word_line+j, "%s", converted_word);
			j += strlen(converted_word);
			k = 0;
			while(*(my_string+i) != '\0' && *(my_string+i) == ' ') {
				i ++;
			}
		}
	}

	char* converted_word;
	converted_word = find_lang(word);
	sprintf(word_line+j, "%s", converted_word);
	j += strlen(converted_word);

	return word_line;

}
	
	
char* find_lang(unsigned char *utf_string)
{
	char* lang = (char *) malloc(strlen(utf_string) + 5);
	int i = 0;
	unsigned char ch;
	unsigned char ch_next;
	while (*(utf_string+i) != '\0') {
		ch = *(utf_string+i);
		if (!isascii(ch)) {
			ch_next = *(utf_string+i+1);			
			if (ch_next == 164 || ch_next == 165) {
				sprintf(lang, "~hin~%s", utf_string);
				return lang;
			} else if (ch_next == 166 || ch_next == 167) {
				sprintf(lang, "~ben~%s", utf_string);
				return lang;
			} else if (ch_next == 178 || ch_next == 179) {
				sprintf(lang, "~kan~%s", utf_string);
				return lang;
			} else if (ch_next == 180 || ch_next == 181) {
				sprintf(lang, "~mal~%s", utf_string);
				return lang;
			} else if (ch_next == 168 || ch_next == 169) {
				sprintf(lang, "~pan~%s", utf_string);
				return lang;
			} else if (ch_next == 174 || ch_next == 175) {
				sprintf(lang, "~tam~%s", utf_string);
				return lang;
			} else if (ch_next == 176 || ch_next == 177) {
				sprintf(lang, "~tel~%s", utf_string);
				return lang;
			} else {
				sprintf(lang, "~oth~%s", utf_string);
				return lang;
			}
		} else {
			i ++;
		}
	}
	sprintf(lang, "~eng~%s", utf_string);
	return lang;
}
