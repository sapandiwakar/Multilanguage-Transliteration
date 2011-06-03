//**************************************
// FILE     : wx_utf8.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 16th June, 2009
//
// MODIFIED LAST : 16th June, 2009
//***************************************

/*
 * This converter converts malayalam text from wx to utf. The main function calls the function wx_utf8 for the conversion of each line. The line is then
 * read character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined
 * as follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


unsigned char utf_mal[204][20] = {{"സ്റ്റ്"}, {"ന്റ്"}, {"ണ്‍"}, {"ര്‍"}, {"ല്‍"}, {"ള്‍"}, {"ന്‍"}, {"ഴ്"}, {"ള്"}, {"റ്"}, {"ന്ത്"}, {"ങ്ക്"}, {"ദ്ധ്"}, {"ന്ദ്"}, {"ഷ്ട്"}, {"ത്ഥ്"}, {"ത്മ്"}, {"ശ്ച്"}, {"ച്ഛ്"}, {"സ്സ്"}, {"ക്ത്"}, {"ണ്മ്"}, {"ണ്ഡ്"}, {"ബ്ധ്"}, {"ന്വ്"}, {"ഞ്ച്"}, {"ത്ഭ്"}, {"ന്ധ്"}, {"ഹ്ന്"}, {"ഹ്മ്"}, {"ഹ്ല്"}, {"ന്മ്"}, {"ബ്ല്"}, {"മ്ല്"}, {"ശ്ല്"}, {"സ്ല്"}, {"ന്ഥ്"}, {"ജ്ഞ്"}, {"ള്ള്"}, {"ഞ്ഞ്"}, {"ണ്ട്"}, {"ക്ക്"}, {"ക്ട്"}, {"ത്ത്"}, {"ച്ച്"}, {"ങ്ങ്"}, {"ഗ്ഗ്"}, {"ജ്ജ്"}, {"ട്ട്"}, {"ഡ്ഡ്"}, {"ണ്ണ്"}, {"ദ്ദ്"}, {"പ്പ്"}, {"ബ്ബ്"}, {"മ്മ്"}, {"വ്വ്"}, {"യ്യ്"}, {"ല്ല്"}, {"ക്ഷ്"}, {"സ്റ്റ"}, {"ന്റ"}, {"﻿ണ്‍"},  {"ര്‍"},  {"ല്‍"},  {"ള്‍"},  {"ന്‍"}, {"ഴ"},  {"ള"}, {"റ"}, {"ന്ത"}, {"ങ്ക"}, {"ദ്ധ"}, {"ന്ദ"}, {"ഷ്ട"}, {"ത്ഥ"}, {"ത്മ"}, {"ശ്ച"}, {"ച്ഛ"}, {"സ്സ"}, {"ക്ത"}, {"ണ്മ"}, {"ണ്ഡ"}, {"ബ്ധ"}, {"ന്വ"}, {"ഞ്ച"}, {"ത്ഭ"}, {"ന്ധ"}, {"ഹ്ന"}, {"ഹ്മ"}, {"ഹ്ല"}, {"ന്മ"}, {"ബ്ല"}, {"മ്ല"}, {"ശ്ല"}, {"സ്ല"}, {"ന്ഥ"}, {"ജ്ഞ"}, {"ള്ള"}, {"ഞ്ഞ"}, {"ണ്ട"}, {"ക്ക"}, {"ക്ട"}, {"ത്ത"}, {"ച്ച"}, {"ങ്ങ"}, {"ഗ്ഗ"}, {"ജ്ജ"}, {"ട്ട"}, {"ഡ്ഡ"}, {"ണ്ണ"}, {"ദ്ദ"}, {"പ്പ"}, {"ബ്ബ"}, {"മ്മ"}, {"വ്വ"}, {"യ്യ"}, {"ല്ല"}, {"ക്ഷ"}, {"ക്"}, {"ഖ്"}, {"ഗ്"}, {"ഘ്"}, {"ങ്"}, {"ച്"}, {"ഛ്"}, {"ജ്"}, {"ഝ്"}, {"ഞ്"}, {"ട്"}, {"ഠ്"}, {"ഡ്"}, {"ഢ്"}, {"ണ്"}, {"ത്സ്"}, {"ത്"}, {"ഥ്"}, {"ദ്"}, {"ധ്"}, {"ന്ന്"}, {"ന്"}, {"പ്"}, {"ഫ്"}, {"ബ്"}, {"ഭ്"}, {"മ്"}, {"യ്"}, {"ര്"}, {"ല്"}, {"വ്"}, {"ശ്"}, {"ഷ്"}, {"സ്"}, {"ഹ്"}, {"ക"}, {"ഖ"}, {"ഗ"}, {"ഘ"}, {"ങ"}, {"ച"}, {"ഛ"}, {"ജ"}, {"ഝ"}, {"ഞ"}, {"ട"}, {"ഠ"}, {"ഡ"}, {"ഢ"}, {"ണ"}, {"ത്സ"}, {"ത"}, {"ഥ"}, {"ദ"}, {"ധ"}, {"ന്ന"}, {"ന"}, {"പ"}, {"ഫ"}, {"ബ"}, {"ഭ"}, {"മ"}, {"യ"}, {"ര"}, {"ല"}, {"വ"}, {"ശ"}, {"ഷ"}, {"സ"}, {"ഹ"}, {"അ"}, {"ആ"}, {"ഇ"}, {"ഈ"}, {"ഉ"}, {"ഊ"}, {"ഋ"}, {"എ"}, {"ഏ"}, {"ഐ"}, {"ഒ"}, {"ഓ"}, {"ഔ"}, {"അം"}, {" ആം"}, {"ം"}};

unsigned char eng_mal[204][20] = {{"srYrY"}, {"nZrY"}, {"NZ"}, {"rZ"}, {"lZ"}, {"lYZ"}, {"nZ"}, {"lYY"}, {"lY"}, {"rY"}, {"nw"}, {"fk"}, {"xX"}, {"nx"}, {"Rt"}, {"wW"}, {"wm"}, {"Sc"}, {"cC"}, {"ss"}, {"kw"}, {"Nm"}, {"ND"}, {"bX"}, {"np"}, {"Fc"}, {"wB"}, {"nX"}, {"hn"}, {"hm"}, {"hl"}, {"nm"}, {"bl"}, {"ml"}, {"Sl"}, {"sl"}, {"nW"}, {"jF"}, {"lYlY"}, {"FF"}, {"Nt"}, {"kk"}, {"kt"}, {"ww"}, {"cc"}, {"ff"}, {"gg"}, {"jj"}, {"tt"}, {"DD"}, {"NN"}, {"xx"}, {"pp"}, {"bb"}, {"mm"}, {"vv"}, {"yy"}, {"ll"}, {"kR"}, {"srYrYa"}, {"nZrYa"}, {"NZa"}, {"rZa"}, {"lZa"}, {"lYZa"}, {"nZa"}, {"lYYa"}, {"lYa"}, {"rYa"}, {"nwa"}, {"fka"}, {"xXa"}, {"nxa"}, {"Rta"}, {"wWa"}, {"wma"}, {"Sca"}, {"cCa"}, {"ssa"}, {"kwa"}, {"Nma"}, {"NDa"}, {"bXa"}, {"npa"}, {"Fca"}, {"wBa"}, {"nXa"}, {"hna"}, {"hma"}, {"hla"}, {"nma"}, {"bla"}, {"mla"}, {"Sla"}, {"sla"}, {"nWa"}, {"jFa"}, {"lYlYa"}, {"FFa"}, {"Nta"}, {"kka"}, {"kta"}, {"wwa"}, {"cca"}, {"ffa"}, {"gga"}, {"jja"}, {"tta"}, {"DDa"}, {"NNa"}, {"xxa"}, {"ppa"}, {"bba"}, {"mma"}, {"vva"}, {"yya"}, {"lla"}, {"kRa"}, {"k"}, {"K"}, {"g"}, {"G"}, {"f"}, {"c"}, {"C"}, {"j"}, {"J"}, {"F"}, {"t"}, {"T"}, {"d"}, {"D"}, {"N"}, {"ws"}, {"w"}, {"W"}, {"x"}, {"X"}, {"nn"}, {"n"}, {"p"}, {"P"}, {"b"}, {"B"}, {"m"}, {"y"}, {"r"}, {"l"}, {"v"}, {"S"}, {"R"}, {"s"}, {"h"}, {"ka"}, {"Ka"}, {"ga"}, {"Ga"}, {"fa"}, {"ca"}, {"Ca"}, {"ja"}, {"Ja"}, {"Fa"}, {"ta"}, {"Ta"}, {"da"}, {"Da"}, {"Na"}, {"wsa"}, {"wa"}, {"Wa"}, {"xa"}, {"Xa"}, {"nna"}, {"na"}, {"pa"}, {"Pa"}, {"ba"}, {"Ba"}, {"ma"}, {"ya"}, {"ra"}, {"la"}, {"va"}, {"Sa"}, {"Ra"}, {"sa"}, {"ha"}, {"a"}, {"A"}, {"i"}, {"I"}, {"u"}, {"U"}, {"q"}, {"eV"}, {"e"}, {"E"}, {"oV"}, {"o"}, {"O"}, {"aM"}, {"AM"}, {"M"}};

char vow_eng_mal[16] = {'a','A','i','I','u','U','e','E','o','O','H','q','Q', 'O', '\b'};
char vow_mal_matra[16][4] = {{""}, {"ാ"}, {"ി"}, {"ീ"}, {"ു"}, {"ൂ"}, {"േ"}, {"ൈ"}, {"ോ"}, {"ൌ"},{"ഃ"}, {"ൃ"}, {"ൄ"}, {"ൗ"}, {"്"}}; 

unsigned char *utf_wx_mal(unsigned char *wx_string)
{
	unsigned char *utf8_string = malloc(strlen(wx_string));
	if (utf8_string == NULL) { printf("Can't allocate memory for utf8_string\n"); exit;}

	
	int i=0,j=0,k=0,l,m,con_ind=0,vow_ind=0,next_vow_ind=0,first_vow_ind=0,flag_con,flag_vow,flag_first_vow,next_flag_vow;
	unsigned char ch_next[4];
	while(*(wx_string+i) != '\0') {
		unsigned char ch1[4];
		unsigned char ch2[7];
		unsigned char ch3[10];
		unsigned char ch4[13];
		unsigned char ch5[16];

		if (!isascii(*(wx_string+i))) {
		
			for (k = 0; k < 16; k ++) {
				ch5[k] = *(wx_string+i+k);
			}
			ch5[k] = '\0';

			for (k = 0; k < 12; k ++) {
				ch4[k] = *(wx_string+i+k);
			}
			ch4[k] = '\0';
			for (k = 0; k < 9; k ++) {
				ch3[k] = *(wx_string+i+k);
			}
			ch3[k] = '\0';

			for (k = 0; k < 6; k ++) {
				ch2[k] = *(wx_string+i+k);
			}
			ch2[k] = '\0';
			for (k = 0; k < 3; k ++) {
				ch1[k] = *(wx_string+i+k);
			}
			ch1[k] = '\0';
		} else {
			sprintf(utf8_string+j, "%c", *(wx_string+i));
			j ++;
			i ++;
			continue;
		}
		
		for (k = 0; k < 204; k ++) {
			if (!strcmp(ch5, utf_mal[k])) {
				sprintf(utf8_string+j, "%s", eng_mal[k]);
				j += strlen(eng_mal[k]);
				i += strlen(utf_mal[k]);
				ch_next[0] = *(wx_string+i);
				ch_next[1] = *(wx_string+i+1);
				ch_next[2] = *(wx_string+i+2);
				ch_next[3] = '\0';

				if (k < 190) {
					if (!strcmp(ch_next, "െ")) {
						sprintf(utf8_string+j, "\b");
						j --;
						sprintf(utf8_string+j, "eV");
						j += 2;
						i += 3;
					} else {
						for (l = 0; l < 14; l ++) {
							if (!strcmp(ch_next, vow_mal_matra[l])) {
								sprintf(utf8_string+j, "\b");
								j --;
								sprintf(utf8_string+j, "%c", vow_eng_mal[l]);
								j += 1;
								i += 3;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch4, utf_mal[k])) {
				sprintf(utf8_string+j, "%s", eng_mal[k]);
				j += strlen(eng_mal[k]);
				i += strlen(utf_mal[k]);
				ch_next[0] = *(wx_string+i);
				ch_next[1] = *(wx_string+i+1);
				ch_next[2] = *(wx_string+i+2);
				ch_next[3] = '\0';
				if (k < 190) {
					if (!strcmp(ch_next, "െ")) {
						sprintf(utf8_string+j, "\b");
						j --;
						sprintf(utf8_string+j, "eV");
						j += 2;
						i += 3;
					} else {
						for (l = 0; l < 14; l ++) {
							if (!strcmp(ch_next, vow_mal_matra[l])) {
								sprintf(utf8_string+j, "\b");
								j --;
								sprintf(utf8_string+j, "%c", vow_eng_mal[l]);
								j ++;
								i += 3;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch3, utf_mal[k])) {
				sprintf(utf8_string+j, "%s", eng_mal[k]);
				j += strlen(eng_mal[k]);
				i += strlen(utf_mal[k]);
				ch_next[0] = *(wx_string+i);
				ch_next[1] = *(wx_string+i+1);
				ch_next[2] = *(wx_string+i+2);
				ch_next[3] = '\0';
				if (k < 190) {
					if (!strcmp(ch_next, "െ")) {
						sprintf(utf8_string+j, "\b");
						j --;
						sprintf(utf8_string+j, "eV");
						j += 2;
						i += 3;
					} else {
						for (l = 0; l < 14; l ++) {
							if (!strcmp(ch_next, vow_mal_matra[l])) {
								sprintf(utf8_string+j, "\b");
								j --;
								sprintf(utf8_string+j, "%c", vow_eng_mal[l]);
								j += 1;
								i += 3;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch2, utf_mal[k])) {
				sprintf(utf8_string+j, "%s", eng_mal[k]);
				j += strlen(eng_mal[k]);
				i += strlen(utf_mal[k]);
				ch_next[0] = *(wx_string+i);
				ch_next[1] = *(wx_string+i+1);
				ch_next[2] = *(wx_string+i+2);
				ch_next[3] = '\0';
				if (k < 190) {
					if (!strcmp(ch_next, "െ")) {
						sprintf(utf8_string+j, "\b");
						j --;
						sprintf(utf8_string+j, "eV");
						j += 2;
						i += 3;
					} else {
						for (l = 0; l < 14; l ++) {
							if (!strcmp(ch_next, vow_mal_matra[l])) {
								sprintf(utf8_string+j, "\b");
								j --;
								sprintf(utf8_string+j, "%c", vow_eng_mal[l]);
								j += 1;
								i += 3;
							}
						}
					}
				}
				break;
			} else if (!strcmp(ch1, utf_mal[k])) {
				sprintf(utf8_string+j, "%s", eng_mal[k]);
				j += strlen(eng_mal[k]);
				i += strlen(utf_mal[k]);
				ch_next[0] = *(wx_string+i);
				ch_next[1] = *(wx_string+i+1);
				ch_next[2] = *(wx_string+i+2);
				ch_next[3] = '\0';
				if (k < 190) {
					if (!strcmp(ch_next, "െ")) {
						sprintf(utf8_string+j, "\b");
						j --;
						sprintf(utf8_string+j, "eV");
						j += 2;
						i += 3;
					} else {
						for (l = 0; l < 14; l ++) {
							if (!strcmp(ch_next, vow_mal_matra[l])) {
								sprintf(utf8_string+j, "\b");
								j --;
								sprintf(utf8_string+j, "%c", vow_eng_mal[l]);
								j += 1;
								i += 3;
							}
						}
					}
				}
				break;
			}
		}
		if (k == 204) {
			for (m = 0; m < 15; m ++ ) {
				if (!strcmp(ch1, vow_mal_matra[m])) {	
					if (m == 14) {
						sprintf(utf8_string+j, "%c", vow_eng_mal[m]);
						j --;
						i += 3;
						break;
					}
					sprintf(utf8_string+j, "\b");
					j --;
					sprintf(utf8_string+j, "%c", vow_eng_mal[m]);
					j ++;
					i += 3;
					break;
				}
			}
			if (m == 15) {
					if (!strcmp(ch1, "ൊ")) {
						sprintf(utf8_string+j, "\b");
						j --;
						sprintf(utf8_string+j,"oV");
						j += 2;
						i += 3;
					} else {
						sprintf(utf8_string+j,"%s", ch1);
						i += 3;
						j += 3;
					}
			}
			
		}
	}
	return utf8_string;
}

