//**************************************
// FILE     : wx_utf8_pan.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts punjabi text from wx to utf. The main function calls the function wx_utf8_pan for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined as 
 * follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char halanta_pan[4]={"੍"};
char con_eng_pan[]={'k','K','g','G','f','c','C','j','J','F','t','T','d','D','N','w','W','x','X','n','p','P','b','B','m','y','r','l','v','S','s','R','h'};
char con_pan[][4] = {{"ਕ"}, {"ਖ"}, {"ਗ"}, {"ਘ"}, {"ਙ"}, {"ਚ"}, {"ਛ"}, {"ਜ"}, {"ਝ"}, {"ਞ"}, {"ਟ"}, {"ਠ"}, {"ਡ"}, {"ਢ"}, {"ਣ"}, {"ਤ"}, {"ਥ"}, {"ਦ"}, {"ਧ"}, {"ਨ"}, {"ਪ"}, {"ਫ"}, {"ਬ"}, {"ਭ"}, {"ਮ"}, {"ਯ"}, {"ਰ"}, {"ਲ"}, {"ਵ"}, {"ਸ਼"}, {"ਸ"}, {"R"}, {"ਹ"}};
char con_pan_hal[][7] = {{"ਕ੍"}, {"ਖ੍"},{"ਗ੍"},{"ਘ੍"},{"ਙ੍"},{"ਚ੍"},{"ਛ੍"},{"ਜ੍"},{"ਝ੍"},{"ਞ੍"},{"ਟ੍"},{"ਠ੍"},{"ਡ੍"},{"ਢ੍"},{"ਣ੍"},{"ਤ੍"}, {"ਥ੍"},{"ਦ੍"},{"ਧ੍"},{"ਨ੍"},{"ਪ੍"},{"ਫ੍"},{"ਬ੍"},{"ਭ੍"},{"ਮ੍"},{"ਯ੍"},{"ਰ੍"},{"ਲ੍"},{"ਵ੍"},{"ਸ਼੍"},{"ਸ੍"}, {" "}, {"ਹ੍"}};
char vow_eng_pan[] = {'a','A','i','I','u','U','e','E','o','O','z', 'M', 'Y', 'Z'};
char vow_pan[][4] = {{"ਅ"}, {"ਆ"}, {"ਇ"}, {"ਈ"}, {"ਉ"}, {"ਊ"}, {"ਏ"}, {"ਐ"}, {"ਓ"}, {"ਔ"}, {"ਂ"}, {"ੱ"}, {"ੰ"}, {"਼"}};
char vow_pan_matra[][4] = {{""},{"ਾ "}, {"ਿ"}, {"ੀ"}, {"ੁ"}, {"ੂ"}, {"ੇ"}, {"ੈ"}, {"ੋ"}, {"ੌ"}, {"ਂ"}, {"ੱ"}, {"ੰ"}, {"਼"}};

/*
 * Function to convert from wx to utf8
 */
char *wx_utf8_pan(unsigned char *wx_string)
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
			for(k=0;k<=32;k++){if(con_eng_pan[k] == ch){con_ind=k;flag_con=1;}}
			for(k=0;k<=15;k++){if(vow_eng_pan[k] == ch){first_vow_ind=k;flag_first_vow=1;}}
			for(k=0;k<=15;k++){if(vow_eng_pan[k] == ch_next){vow_ind=k;flag_vow=1;}}
			for(k=0;k<=15;k++){if(vow_eng_pan[k] == ch_next_next){next_vow_ind=k;next_flag_vow=1;}}
			if((flag_con) &&(flag_vow)){
				if(ch_next == 'a'){
					sprintf(utf8_string+j,"%s",con_pan[con_ind]);
					j=j+3;
					i=i+2;
				}
				else if(ch_next == 'Z'){
					if(next_flag_vow){
						sprintf(utf8_string+j,"%s",con_pan[con_ind]);
						j=j+3;
						sprintf(utf8_string+j,"%s",vow_pan_matra[vow_ind]);
						j=j+3;

						if(ch_next_next != 'a'){
							sprintf(utf8_string+j,"%s",vow_pan_matra[next_vow_ind]);
							j=j+3;
						}
						i=i+3;
					}				
					else{ 
						sprintf(utf8_string+j,"%s",con_pan[con_ind]);
						j=j+3;
						sprintf(utf8_string+j,"%s",vow_pan_matra[vow_ind]);
						j=j+3;
						sprintf(utf8_string+j,"%s",halanta_pan);
						j=j+3;
						i=i+2;
					}	
				}
				else{
					sprintf(utf8_string+j,"%s",con_pan[con_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",vow_pan_matra[vow_ind]);
					j=j+3;
					i=i+2;
				}
			}
			else if((flag_first_vow)){
				sprintf(utf8_string+j,"%s",vow_pan[first_vow_ind]);
				j=j+3;
				i=i+1;
				flag_first_vow=0;
			}
			else if(flag_con){
				sprintf(utf8_string+j,"%s",con_pan_hal[con_ind]);
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



