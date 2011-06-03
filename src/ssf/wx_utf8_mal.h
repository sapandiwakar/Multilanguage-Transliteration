//**************************************
// FILE     : wx_utf8_mal.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts malayalam text from wx to utf. The main function calls the function wx_utf8_mal for the conversion of each line. The line is then
 * read character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined
 * as follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char utf_mal_wx2utf[110][20] = {{"സ്റ്റ്"}, {"ന്‍റ്"}, {"ണ്‍"}, {"ര്‍"}, {"ല്‍"}, {"ള്‍"}, {"ന്‍"}, {"ഴ്"}, {"ള്"}, {"റ്"}, {"ന്ത്"}, {"ങ്ക്"}, {"ദ്ധ്"}, {"ന്ദ്"}, {"ഷ്ട്"}, {"ത്ഥ്"}, {"ത്മ്"}, {"ശ്ച്"}, {"ച്ഛ്"}, {"സ്സ്"}, {"ക്ത്"}, {"ണ്മ്"}, {"ണ്ഡ്"}, {"ബ്ധ്"}, {"ന്വ്"}, {"ഞ്ച്"}, {"ത്ഭ്"}, {"ന്ധ്"}, {"ഹ്ന്"}, {"ഹ്മ്"}, {"ഹ്ല്"}, {"ന്മ്"}, {"ബ്ല്"}, {"മ്ല്"}, {"ശ്ല്"}, {"സ്ല്"}, {"ന്ഥ്"}, {"ജ്ഞ്"}, {"ള്ള്"}, {"ഞ്ഞ്"}, {"ണ്ട്"}, {"ക്ക്"}, {"ക്ട്"}, {"ത്ത്"}, {"ച്ച്"}, {"ങ്ങ്"}, {"ഗ്ഗ്"}, {"ജ്ജ്"}, {"ട്ട്"}, {"ഡ്ഡ്"}, {"ണ്ണ്"}, {"ദ്ദ്"}, {"പ്പ്"}, {"ബ്ബ്"}, {"മ്മ്"}, {"വ്വ്"}, {"യ്യ്"}, {"ല്ല്"}, {"ക്ഷ്"}, {"ക്"}, {"ഖ്"}, {"ഗ്"}, {"ഘ്"}, {"ങ്"}, {"ച്"}, {"ഛ്"}, {"ജ്"}, {"ഝ്"}, {"ഞ്"}, {"ട്"}, {"ഠ്"}, {"ഡ്"}, {"ഢ്"}, {"ണ്"}, {"ത്സ്"}, {"ത്"}, {"ഥ്"}, {"ദ്"}, {"ധ്"}, {"ന്ന്"}, {"ന്"}, {"പ്"}, {"ഫ്"}, {"ബ്"}, {"ഭ്"}, {"മ്"}, {"യ്"}, {"ര്"}, {"ല്"}, {"വ്"}, {"ശ്"}, {"ഷ്"}, {"സ്"}, {"ഹ്"}, {"അ"}, {"ആ"}, {"ഇ"}, {"ഈ"}, {"ഉ"}, {"ഊ"}, {"ഋ"}, {"എ"}, {"ഏ"}, {"ഐ"}, {"ഒ"}, {"ഓ"}, {"ഔ"}, {"അം"}, {" ആം"}, {"ം"}};

unsigned char eng_mal_wx2utf[110][20] = {{"srYrY"}, {"nZrY"}, {"NZ"}, {"rZ"}, {"lZ"}, {"lYZ"}, {"nZ"}, {"lYY"}, {"lY"}, {"rY"}, {"nw"}, {"fk"}, {"xX"}, {"nx"}, {"Rt"}, {"wW"}, {"wm"}, {"Sc"}, {"cC"}, {"ss"}, {"kw"}, {"Nm"}, {"ND"}, {"bX"}, {"np"}, {"Fc"}, {"wB"}, {"nX"}, {"hn"}, {"hm"}, {"hl"}, {"nm"}, {"bl"}, {"ml"}, {"Sl"}, {"sl"}, {"nW"}, {"jF"}, {"lYlY"}, {"FF"}, {"Nt"}, {"kk"}, {"kt"}, {"ww"}, {"cc"}, {"ff"}, {"gg"}, {"jj"}, {"tt"}, {"DD"}, {"NN"}, {"xx"}, {"pp"}, {"bb"}, {"mm"}, {"vv"}, {"yy"}, {"ll"}, {"kR"}, {"k"}, {"K"}, {"g"}, {"G"}, {"f"}, {"c"}, {"C"}, {"j"}, {"J"}, {"F"}, {"t"}, {"T"}, {"d"}, {"D"}, {"N"}, {"ws"}, {"w"}, {"W"}, {"x"}, {"X"}, {"nn"}, {"n"}, {"p"}, {"P"}, {"b"}, {"B"}, {"m"}, {"y"}, {"r"}, {"l"}, {"v"}, {"S"}, {"R"}, {"s"}, {"h"}, {"a"}, {"A"}, {"i"}, {"I"}, {"u"}, {"U"}, {"q"}, {"eV"}, {"e"}, {"E"}, {"oV"}, {"o"}, {"O"}, {"aM"}, {"AM"}, {"M"}};

char vow_eng_mal_wx2utf[15] = {'a','A','i','I','u','U','e','E','o','H','q','Q', 'O', '\b'};
char vow_mal_matra_wx2utf[15][4] = {{""}, {"ാ"}, {"ി"}, {"ീ"}, {"ു"}, {"ൂ"}, {"േ"}, {"ൈ"}, {"ോ"},{"ഃ"}, {"ൃ"}, {"ൄ"}, {"ൗ"}, {"്"}}; 

char *wx_utf8_mal(unsigned char *wx_string)
{
	char* utf8_string = malloc(6*strlen(wx_string));
	if (utf8_string == NULL) { printf("Can't allocate memory for utf8_string\n"); exit;}

	
	int i=0,j=0,k=0,l,con_ind=0,vow_ind=0,next_vow_ind=0,first_vow_ind=0,flag_con,flag_vow,flag_first_vow,next_flag_vow;
	char ch,ch_next,ch_next_next;
	while(*(wx_string+i) != '\0') {
		char ch1[2];
		char ch2[3];
		char ch3[4];
		char ch4[5];
		char ch5[6];

		ch5[0] = ch4[0] = ch3[0] = ch2[0] = ch1[0] = *(wx_string+i);
		ch5[1] = ch4[1] = ch3[1] = ch2[1] = *(wx_string+i+1);
		ch5[2] = ch4[2] = ch3[2] = *(wx_string+i+2);
		ch5[3] = ch4[3] = *(wx_string+i+3);
		ch5[4] = *(wx_string+i+4);
		ch5[5] = ch4[4] = ch3[3] = ch2[2] = ch1[1] = '\0';

		for (k = 0; k < 110; k ++) {
			if (!strcmp(ch5, eng_mal_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_mal_wx2utf[k]);
				j += strlen(utf_mal_wx2utf[k]);
				i += strlen(eng_mal_wx2utf[k]);
				ch_next = *(wx_string+i);				
				if ( k >= 0 && k < 94) {
					if (ch_next == 'a') {
						sprintf(utf8_string+j, "\b\b\b");
						j -= 3;
						i ++;
					} else if (ch_next == 'e') {
						ch_next_next = *(wx_string+i+1);
						if (ch_next_next == 'V') {
							sprintf(utf8_string+j, "\b\b\b");
							j -= 3;
							sprintf(utf8_string+j, "െ");
							j += 3;
							i += 2;
						}
					} else { 	
						for (l = 0; l < 15; l ++) {
							if (ch_next == vow_eng_mal_wx2utf[l]) {
								sprintf(utf8_string+j, "\b\b\b");
								j -= 3;
								sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
								j += 3;
								i ++;
								break;
							}
						}
					}
				}				
				break;
			} else if (!strcmp(ch4, eng_mal_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_mal_wx2utf[k]);
				j += strlen(utf_mal_wx2utf[k]);
				i += strlen(eng_mal_wx2utf[k]);
				ch_next = *(wx_string+i);				
				if ( k >= 0 && k < 94) {
					if (ch_next == 'a') {
						sprintf(utf8_string+j, "\b\b\b");
						j -= 3;
						i ++;
					} else if (ch_next == 'e') {
						ch_next_next = *(wx_string+i+1);
						if (ch_next_next == 'V') {
							sprintf(utf8_string+j, "\b\b\b");
							j -= 3;
							sprintf(utf8_string+j, "െ");
							j += 3;
							i += 2;
						} else {
							for (l = 0; l < 15; l ++) {
								if (ch_next == vow_eng_mal_wx2utf[l]) {
									sprintf(utf8_string+j, "\b\b\b");
									j -= 3;
									sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
									j += 3;
									i ++;
									break;
								}
							}
						}

					} else { 	
						for (l = 0; l < 16; l ++) {
							if (ch_next == vow_eng_mal_wx2utf[l]) {
								sprintf(utf8_string+j, "\b\b\b");
								j -= 3;
								sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
								j += 3;
								i ++;
								break;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch3, eng_mal_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_mal_wx2utf[k]);
				j += strlen(utf_mal_wx2utf[k]);
				i += strlen(eng_mal_wx2utf[k]);
				ch_next = *(wx_string+i);				
				if ( k >= 0 && k < 94) {
					if (ch_next == 'a') {
						sprintf(utf8_string+j, "\b\b\b");
						j -= 3;
						i ++;
					} else if (ch_next == 'e') {
						ch_next_next = *(wx_string+i+1);
						if (ch_next_next == 'V') {
							sprintf(utf8_string+j, "\b\b\b");
							j -= 3;
							sprintf(utf8_string+j, "െ");
							j += 3;
							i += 2;
						} else {
							for (l = 0; l < 15; l ++) {
								if (ch_next == vow_eng_mal_wx2utf[l]) {
									sprintf(utf8_string+j, "\b\b\b");
									j -= 3;
									sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
									j += 3;
									i ++;
									break;
								}
							}
						}
					} else { 	
						for (l = 0; l < 15; l ++) {
							if (ch_next == vow_eng_mal_wx2utf[l]) {
								sprintf(utf8_string+j, "\b\b\b");
								j -= 3;
								sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
								j += 3;
								i ++;
								break;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch2, eng_mal_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_mal_wx2utf[k]);
				j += strlen(utf_mal_wx2utf[k]);
				i += strlen(eng_mal_wx2utf[k]);
				ch_next = *(wx_string+i);				
				if ( k >= 0 && k < 94) {
					if (ch_next == 'a') {
						sprintf(utf8_string+j, "\b\b\b");
						j -= 3;
						i ++;
					} else if (ch_next == 'e') {
						ch_next_next = *(wx_string+i+1);
						if (ch_next_next == 'V') {
							sprintf(utf8_string+j, "\b\b\b");
							j -= 3;
							sprintf(utf8_string+j, "െ");
							j += 3;
							i += 2;
						} else {
							for (l = 0; l < 15; l ++) {
								if (ch_next == vow_eng_mal_wx2utf[l]) {
									sprintf(utf8_string+j, "\b\b\b");
									j -= 3;
									sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
									j += 3;
									i ++;
									break;
								}
							}
						}
					} else { 	
						for (l = 0; l < 15; l ++) {
							if (ch_next == vow_eng_mal_wx2utf[l]) {
								sprintf(utf8_string+j, "\b\b\b");
								j -= 3;
								sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
								j += 3;
								i ++;
								break;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch1, eng_mal_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_mal_wx2utf[k]);
				j += strlen(utf_mal_wx2utf[k]);
				i += strlen(eng_mal_wx2utf[k]);
				ch_next = *(wx_string+i);				
				if ( k >= 0 && k < 94) {
					if (ch_next == 'a') {
						sprintf(utf8_string+j, "\b\b\b");
						j -= 3;
						i ++;
					} else if (ch_next == 'e') {
						ch_next_next = *(wx_string+i+1);
						if (ch_next_next == 'V') {
							sprintf(utf8_string+j, "\b\b\b");
							j -= 3;
							sprintf(utf8_string+j, "െ");
							j += 3;
							i += 2;
						} else {
							for (l = 0; l < 15; l ++) {
								if (ch_next == vow_eng_mal_wx2utf[l]) {
									sprintf(utf8_string+j, "\b\b\b");
									j -= 3;
									sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
									j += 3;
									i ++;
									break;
								}
							}
						
						}
					} else { 
						for (l = 0; l < 15; l ++) {
							if (ch_next == vow_eng_mal_wx2utf[l]) {
								sprintf(utf8_string+j, "\b\b\b");
								j -= 3;
								sprintf(utf8_string+j, "%s", vow_mal_matra_wx2utf[l]);
								j += 3;
								i ++;
								break;
							}
						}
					}
				}
				break;
			}
		}

		if (k == 110) {
			if (ch1[0] != 'V') {
				sprintf(utf8_string+j,"%c",ch1[0]);
				j = j+1;
				i++;
			} else {
				i ++;
			}
		}
	}
	return utf8_string;
}

