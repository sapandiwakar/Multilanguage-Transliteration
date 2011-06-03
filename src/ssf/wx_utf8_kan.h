//**************************************
// FILE     : wx_utf8_kan.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts kannada text from wx to utf. The main function calls the function wx_utf8_kan for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined as 
 * follows.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char halanta_kan[4]={"್"};
char con_eng_kan[]={'k','K','g','G','f','c','C','j','J','F','t','T','d','D','N','w','W','x','X','n','p','P','b','B','m','y','r','l','v','S','R','s','h','Y'};
char con_kan_hal[][7]= {{"ಕ್"}, {"ಖ್"}, {"ಗ್"}, {"ಘ್"}, {"ಙ್"}, {"ಚ್"}, {"ಛ್"}, {"ಜ್"}, {"ಝ್"}, {"ಞ್"}, {"ಟ್"}, {"ಠ್"}, {"ಡ್"}, {"ಢ್"}, {"ಣ್"}, {"ತ್"}, {"ಥ್"}, {"ದ್"}, {"ಧ್"}, {"ನ್"}, {"ಪ್"}, {"ಫ್"}, {"ಬ್"}, {"ಭ್"}, {"ಮ್"}, {"ಯ್"}, {"ರ್"}, {"ಲ್"}, {"ವ್"}, {"ಶ್"}, {"ಷ್"}, {"ಸ್"}, {"ಹ್"}, {"ಯ್"}};
char con_kan[][4]= {{"ಕ"}, {"ಖ"}, {"ಗ"}, {"ಘ"}, {"ಙ"}, {"ಚ"}, {"ಛ"}, {"ಜ"}, {"ಝ"}, {"ಞ"}, {"ಟ"}, {"ಠ"}, {"ಡ"}, {"ಢ"}, {"ಣ"}, {"ತ"}, {"ಥ"}, {"ದ"}, {"ಧ"}, {"ನ"}, {"ಪ"}, {"ಫ"}, {"ಬ"}, {"ಭ"}, {"ಮ"}, {"ಯ"}, {"ರ"}, {"ಲ"}, {"ವ"}, {"ಶ"}, {"ಷ"}, {"ಸ"}, {"ಹ"}, {"ಯ"}};
char vow_eng_kan[] = {'a','A','i','I','u','U','e','E','o','O','M','H','q','Q','Z'};
char vow_kan[][4]= {{"ಅ"}, {"ಆ"}, {"ಇ"}, {"ಈ"}, {"ಉ"}, {"ಊ"}, {"ಏ"}, {"ಐ"}, {"ಓ"}, {"ಔ"}, {"ಃ"}, {"ಋ"}, {"ೠ"}, {" ಼"}};
char vow_kan_matra[][4] = {{"ಾ"}, {"ಿ"}, {"ೀ"}, {"ು"}, {"ೂ"}, {"ೇ"}, {"ೈ"}, {"ೋ"}, {"ೌ"}, {"ಂ"}, {"ಃ"}, {"ೃ"}, {"ೄ"}, {"್"}};

/*
 * Function to convert from wx to utf8
 */
char *wx_utf8_kan(unsigned char *wx_string)
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
			for(k=0;k<=32;k++){if(con_eng_kan[k] == ch){con_ind=k;flag_con=1;}}
			for(k=0;k<=15;k++){if(vow_eng_kan[k] == ch){first_vow_ind=k;flag_first_vow=1;}}
			for(k=0;k<=15;k++){if(vow_eng_kan[k] == ch_next){vow_ind=k;flag_vow=1;}}
			for(k=0;k<=15;k++){if(vow_eng_kan[k] == ch_next_next){next_vow_ind=k;next_flag_vow=1;}}
			if (ch == 'e' && ch_next == 'V') {
				sprintf(utf8_string+j, "ಎ");
				i += 2;
				j += 3;
			} else if (ch=='o' && ch_next=='V') {
				sprintf(utf8_string+j, "ಒ");
				i += 2;
				j += 3;
			} else if (ch == 'l' && ch_next == 'Y') {
				sprintf(utf8_string+j, "ಳ");
				i += 2;
				j += 3;
			} else if((flag_con) &&(flag_vow)){
				if(ch_next == 'a'){
					sprintf(utf8_string+j,"%s",con_kan[con_ind]);
					j=j+3;
					i=i+2;
				} else if (ch_next == 'e' && ch_next_next == 'V') {
					sprintf(utf8_string+j, "ಎ");
					i += 3;
					j += 3;
				} else if (ch_next =='o' && ch_next_next =='V') {
					sprintf(utf8_string+j, "ಒ");
					i += 3;
					j += 3;
				} 
				else if(ch_next == 'Z'){
					if(next_flag_vow){
						sprintf(utf8_string+j,"%s",con_kan[con_ind]);
						j=j+3;
						sprintf(utf8_string+j,"%s",vow_kan_matra[vow_ind]);
						j=j+3;

						if(ch_next_next != 'a'){
							sprintf(utf8_string+j,"%s",vow_kan_matra[next_vow_ind]);
							j=j+3;
						}
						i=i+3;
					}				
					else{ 
						sprintf(utf8_string+j,"%s",con_kan[con_ind]);
						j=j+3;
						sprintf(utf8_string+j,"%s",vow_kan_matra[vow_ind]);
						j=j+3;
						sprintf(utf8_string+j,"%s",halanta_kan);
						j=j+3;
						i=i+2;
					}	
				}
				else{
					sprintf(utf8_string+j,"%s",con_kan[con_ind]);
					j=j+3;
					sprintf(utf8_string+j,"%s",vow_kan_matra[vow_ind]);
					j=j+3;
					i=i+2;
				}
			}
			else if((flag_first_vow)){
				sprintf(utf8_string+j,"%s",vow_kan[first_vow_ind]);
				j=j+3;
				i=i+1;
				flag_first_vow=0;
			}
			else if(flag_con){
				sprintf(utf8_string+j,"%s",con_kan_hal[con_ind]);
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




