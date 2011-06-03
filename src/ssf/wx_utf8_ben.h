//**************************************
// FILE     : wx_utf8_ben.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts bengali text from wx to utf. The main function calls the function wx_utf8_ben for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined as 
 * follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char halanta_ben[4]={"্"};
char con_eng[]={'k','K','g','G','f','c','C','j','J','F','t','T','d','D','N','w','W','x','X','n','p','P','b','B','m','y','r','l','S','R','s','h'};
char con_ben_hal[][7]= {{"ক্"}, {"খ্"}, {"গ্"}, {"ঘ্"}, {"ঙ্"}, {"চ্"}, {"ছ্"}, {"জ্"}, {"ঝ্"}, {"ঞ্"}, {"ট্"}, {"ঠ্"}, {"ড্"}, {"ঢ্"}, {"ণ্"}, {"ত্"}, {"থ্"}, {"দ্"}, {"ধ্"}, {"ন্"}, {"প্"}, {"ফ্"}, {"ব্"}, {"ভ্"}, {"ম্"}, {"য্"}, {"র্"}, {"ল্"}, {"শ্"}, {"ষ্"}, {"স্"}, {"হ্"}};
char con_ben[][4]= {{"ক"}, {"খ"}, {"গ"}, {"ঘ"}, {"ঙ"}, {"চ"}, {"ছ"}, {"জ"}, {"ঝ"}, {"ঞ"}, {"ট"}, {"ঠ"}, {"ড"}, {"ঢ"}, {"ণ"}, {"ত"}, {"থ"}, {"দ"}, {"ধ"}, {"ন"}, {"প"}, {"ফ"}, {"ব"}, {"ভ"}, {"ম"}, {"য"}, {"র"}, {"ল"}, {"শ"}, {"ষ"}, {"স"}, {"হ"}};
char vow_eng[] = {'a','A','i','I','u','U','e','E','o','O','M','H','z','q','Q','Z'};
char vow_ben[][4]= {{"অ"}, {"আ"}, {"ই"}, {"ঈ"}, {"উ"}, {"ঊ"}, {"এ"}, {"ঐ"}, {"ও"}, {"ঔ"}, {"ং"}, {"ঃ"}, {"ঁ"}, {"ঋ"},  {"ৠ"}, {"়"}}; 
char vow_ben_matra[][4] = {{""}, {"া"}, {"ি"}, {"ী"}, {"ু"}, {"ূ"}, {"ে"}, {"ৈ"}, {"ো"}, {"ৌ"}, {"ং"}, {"ঃ"}, {"ঁ"},  {"ৃ"}, {"ৄ"}, {"়"}, {"্"}};

/*
 * Function to convert from wx to utf8
 */
char *wx_utf8_ben(unsigned char *wx_string)
{
	char *utf8_string = malloc(6*strlen(wx_string));
	if (utf8_string == NULL) { printf("Can't allocate memory for utf8_string\n"); exit;}

	
int i=0,j=0,k=0,con_ind=0,vow_ind=0,next_vow_ind=0,first_vow_ind=0,flag_con,flag_vow,flag_first_vow,next_flag_vow;
char ch,ch_next,ch_next_next;
while(*(wx_string+i) != '\0') {
	ch=(*(wx_string+i));

	ch_next = (*(wx_string+i+1));
	ch_next_next=(*(wx_string+i+1+1));
	if (ch =='v') {
			ch = 'b';
	}
	if (ch_next =='v') {
		ch_next = 'b';
	}
	if (ch_next_next =='v') {
		ch_next_next = 'b';
	}
	flag_con=0;
	flag_vow=0;
	next_flag_vow=0;
	flag_first_vow=0;
	
	if(((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'))){
		/* check after a consonant , there is a vowel,
		 then output the corresponding utf8 character */
		for(k=0;k<=32;k++){if(con_eng[k] == ch){con_ind=k;flag_con=1;}}
		for(k=0;k<=15;k++){if(vow_eng[k] == ch){first_vow_ind=k;flag_first_vow=1;}}
		for(k=0;k<=15;k++){if(vow_eng[k] == ch_next){vow_ind=k;flag_vow=1;}}
		for(k=0;k<=15;k++){if(vow_eng[k] == ch_next_next){next_vow_ind=k;next_flag_vow=1;}}
		if((flag_con) &&(flag_vow)){
			if(ch_next == 'a'){
				sprintf(utf8_string+j,"%s",con_ben[con_ind]);
				j=j+3;
				i=i+2;
			}
			else if(ch_next == 'Z'){
				if(next_flag_vow){
					sprintf(utf8_string+j,"%s",con_ben[con_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",vow_ben_matra[vow_ind]);
					j=j+3;

					if(ch_next_next != 'a'){
						sprintf(utf8_string+j,"%s",vow_ben_matra[next_vow_ind]);
						j=j+3;
					}
					i=i+3;
				}				
				else{ 
					sprintf(utf8_string+j,"%s",con_ben[con_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",vow_ben_matra[vow_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",halanta_ben);
					j=j+3;
					i=i+2;
				}	
			}
			else{
				sprintf(utf8_string+j,"%s",con_ben[con_ind]);
				j=j+3;
				sprintf(utf8_string+j,"%s",vow_ben_matra[vow_ind]);
				j=j+3;
				i=i+2;
			}
		}
		else if((flag_first_vow)){
			sprintf(utf8_string+j,"%s",vow_ben[first_vow_ind]);
			j=j+3;
			i=i+1;
			flag_first_vow=0;
		}
		else if(flag_con){
			sprintf(utf8_string+j,"%s",con_ben_hal[con_ind]);
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



