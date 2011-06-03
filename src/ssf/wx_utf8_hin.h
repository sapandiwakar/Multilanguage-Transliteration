//**************************************
// FILE     : wx_utf8_hin.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts hindi text from wx to utf. The main function calls the function wx_utf8_hin for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined as 
 * follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char halanta_hin[4]={"्"};
char con_eng_hin[]={'k','K','g','G','f','c','C','j','J','F','t','T','d','D','N','w','W','x','X','n','p','P','b','B','m','y','r','l','v','S','s','R','h'};
char con_hnd_hal[][7]={{"क्"},{"ख्"},{"ग्"},{"घ्"},{"ङ्"},{"च्"},{"छ्"},{"ज्"},{"झ्"},{"ञ्"},{"ट्"},{"ठ्"},{"ड्"},{"ढ्"},{"ण्"},{"त्"},{"थ्"},{"द्"},{"ध्"},{"न्"},{"प्"},{"फ्"},{"ब्"},{"भ्"},{"म्"},{"य्"},{"र्"},{"ल्"},{"व्"},{"श्"},{"स्"},{"ष्"},{"ह्"}};
char con_hnd[][4]=
{{"क"},{"ख"},{"ग"},{"घ"},{"ङ"},{"च"},{"छ"},{"ज"},{"झ"},{"ञ"},{"ट"},{"ठ"},{"ड"},{"ढ"},{"ण"},{"त"},{"थ"},{"द"},{"ध"},{"न"},{"प"},{"फ"},{"ब"},{"भ"},{"म"},{"य"},{"र"},{"ल"},{"व"},{"श"},{"स"},{"ष"},{"ह"}};
char vow_eng_hin[] = {'a','A','i','I','u','U','e','E','o','O','M','H','z','q','Q','Z'};
char vow_hnd[][4]={{"अ"},{"आ"},{"इ"},{"ई"},{"उ"},{"ऊ"},{"ए"},{"ऐ"},{"ओ"},{"औ"},{"ं"},{"ः"},{"ँ"},{"ऋ"},{"ॠ"},{"़"}};
char vow_hnd_matra[][4] = {{""},{"ा"},{"ि"},{"ी"},{"ु"},{"ू"},{"े"},{"ै"},{"ो"},{"ौ"},{"ं"},{"ः"},{"ँ"},{"ृ"},{"ॄ"},{"़"},{"्"}};

char *wx_utf8_hin(unsigned char *wx_string)				// Function to convert from wx to utf8
{
	char* utf8_string = malloc(6*strlen(wx_string));
	if (utf8_string == NULL) { printf("Can't allocate memory for utf8_string\n"); exit;}

	
int i=0,j=0,k=0,con_ind=0,vow_ind=0,next_vow_ind=0,first_vow_ind=0,flag_con,flag_vow,flag_first_vow,next_flag_vow;
char ch,ch_next,ch_next_next;
while(*(wx_string+i) != '\0') {
	ch=(*(wx_string+i));
	ch_next = (*(wx_string+i+1));
	ch_next_next=(*(wx_string+i+1+1));
	flag_con=0;
	flag_vow=0;
	next_flag_vow=0;
	flag_first_vow=0;
	
	if(((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'))){
		/* check after a consonant , there is a vowel,
		 then output the corresponding utf8 character */
		for(k=0;k<=32;k++){if(con_eng_hin[k] == ch){con_ind=k;flag_con=1;}}
		for(k=0;k<=15;k++){if(vow_eng_hin[k] == ch){first_vow_ind=k;flag_first_vow=1;}}
		for(k=0;k<=15;k++){if(vow_eng_hin[k] == ch_next){vow_ind=k;flag_vow=1;}}
		for(k=0;k<=15;k++){if(vow_eng_hin[k] == ch_next_next){next_vow_ind=k;next_flag_vow=1;}}
		if((flag_con) &&(flag_vow)){
			if(ch_next == 'a'){
				sprintf(utf8_string+j,"%s",con_hnd[con_ind]);
				j=j+3;
				i=i+2;
			}
			else if(ch_next == 'Z'){
				if(next_flag_vow){
					sprintf(utf8_string+j,"%s",con_hnd[con_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",vow_hnd_matra[vow_ind]);
					j=j+3;

					if(ch_next_next != 'a'){
						sprintf(utf8_string+j,"%s",vow_hnd_matra[next_vow_ind]);
						j=j+3;
					}
					i=i+3;
				}				
				else{ 
					sprintf(utf8_string+j,"%s",con_hnd[con_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",vow_hnd_matra[vow_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",halanta_hin);
					j=j+3;
					i=i+2;
				}	
			}
			else{
				sprintf(utf8_string+j,"%s",con_hnd[con_ind]);
				j=j+3;
				sprintf(utf8_string+j,"%s",vow_hnd_matra[vow_ind]);
				j=j+3;
				i=i+2;
			}
		}
		else if((flag_first_vow)){
			sprintf(utf8_string+j,"%s",vow_hnd[first_vow_ind]);
			j=j+3;
			i=i+1;
			flag_first_vow=0;
		}
		else if(flag_con){
			sprintf(utf8_string+j,"%s",con_hnd_hal[con_ind]);
			j=j+6;
			i=i+1;
		}
		else {
			sprintf(utf8_string+j,"%c",ch);
			j = j+1;
			i++;
		}
	}
	else {
	/*for non-ascii characters print as it is*/
		sprintf(utf8_string+j,"%c",ch);
		j = j+1;
		i++;
	}
}
	return utf8_string;
}


