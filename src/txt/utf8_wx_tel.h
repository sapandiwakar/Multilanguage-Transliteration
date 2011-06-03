//**************************************
// FILE     : utf8_wx.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************


/*
 * This converter converts telugu text from utf to wx. The main function calls the function utf_wx_tel for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the caracter boundaries
 * defined next and the map defined in form of an array after the character boundaries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Define character boundries
 */
#define TEL_START_TEL 128
#define MATRA_START_TEL1 1
#define MATRA_END_TEL1 3 
#define MATRA_START_TEL2 60
#define MATRA_END_TEL2 60
#define MATRA_START_TEL3 62
#define MATRA_END_TEL3 76

#define VOW_FIRST_START_TEL1 5
#define VOW_FIRST_END_TEL1 11
#define VOW_FIRST_START_TEL2 15
#define VOW_FIRST_END_TEL2 16
#define VOW_FIRST_START_TEL3 19
#define VOW_FIRST_END_TEL3 20

#define CON_START_TEL 21
#define CON_END_TEL 57

#define NUM_START_TEL 96
#define NUM_END_TEL 111

char* utf_wx_tel(unsigned char *ch);			// Function to convert from utf8 to wx

char eng_tel[] = {' ', 'z', 'M', 'H', ' ', 'a','A','i','I','u','U', 'q', 'L', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', 'k', 'K', 'g', 'G', 'f', 'c', 'C', 'j', 'J', 'F', 't', 'T', 'd', 'D', 'N', 'w', 'W', 'x', 'X', 'n', 'n', 'p', 'P', 'b', 'B', 'm', 'y', 'r', 'r', 'l', ' ', ' ', 'v', 'S', 'R', 's', 'h', ' ', ' ', 'Z', ' ', 'A', 'i', 'I', 'u', 'U', 'q', 'Q', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', ' ', ' ', '`', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Q', ' ', ' ', ' ', '.', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char* utf_wx_tel(unsigned char *ch)
{
	char *utf8_string = malloc(strlen(ch));
	if (utf8_string == NULL) { printf("Can't allocate memory for utf8_string\n"); exit;}

	unsigned char ch1[4];
	unsigned char ch2[4];
	unsigned char ch3[4];
	int i = 0;
	int j = 0;
	int k;
	int a;
	int b;
	int index;
	
		
	while ( ch1[0] = *(ch+i) ) {
		if (ch1[0] == '\n') {
			sprintf(utf8_string+j, "\n");
			j++;
			break;
		} else if (ch1[0] == '\0') {
			sprintf(utf8_string + j, "a");
			j++;
			i++;
			break;
 		} else if (isascii(ch1[0])) {
			sprintf(utf8_string+j, "%c", ch1[0]);
			j++;
			i++;
			continue;
		}
		ch1[1] = *(ch+i+1);
		ch1[2] = *(ch+i+2);
		ch1[3] = '\0';
		i += 3;
		
		if (ch1[1] == 176) {
			index = ch1[2] - TEL_START_TEL;
			if ((index >= VOW_FIRST_START_TEL1 && index <= VOW_FIRST_END_TEL1) || (index >= VOW_FIRST_START_TEL2 && index <= VOW_FIRST_END_TEL2) || (index >= VOW_FIRST_START_TEL3 && index <= VOW_FIRST_END_TEL3)) {
				sprintf(utf8_string+j, "%c", eng_tel[index]);
				j++;
			} else if ((index >= MATRA_START_TEL1 && index <= MATRA_END_TEL1) || (index >= MATRA_START_TEL2 && index <= MATRA_END_TEL2) || (index >= MATRA_START_TEL3 && index <= MATRA_END_TEL3)) {
					sprintf(utf8_string+j, "%c", eng_tel[index] );
					j++;
					continue;
			} else {
				sprintf(utf8_string+j, "%c", eng_tel[index]);
				j++;
				ch2[0] = *(ch+i);
				if (ch2[0] == '\n') {
					sprintf(utf8_string+j, "a\n");
					j += 2;
					break;
				} else if (ch2[0] == '\0') {
					sprintf(utf8_string+j, "a");
					i++;
					break;
		 		} else if (isascii(ch2[0])) {
					sprintf(utf8_string+j, "a%c", ch2[0]);
					j += 2;
					i++;
					continue;
				}

				ch2[1] = *(ch+i+1);
				ch2[2] = *(ch+i+2);
				ch2[3] = '\0';

				if (ch2[1] == 176) {
					index = ch2[2] - TEL_START_TEL;
					if ((index >= MATRA_START_TEL3 && index <= MATRA_END_TEL3)) {
						sprintf(utf8_string+j, "%c", eng_tel[index] );
						j ++;
						i += 3;
					} else if (index == MATRA_START_TEL2) {
						sprintf(utf8_string+j, "%c", eng_tel[index]);
						j++;
						i += 3;
						ch3[0] = *(ch+i);
						if (ch3[0] == '\n') {
							sprintf(utf8_string+j, "a\n");
							j += 2;
						} else if (ch3[0] == '\0') {
							sprintf(utf8_string + j, "a");
							i++;
							//continue;
				 		} else if (isascii(ch3[0])) {
							sprintf(utf8_string+j, "a%c", ch3[0]);
							j += 2;
							i++;
							continue;
						}

						ch3[1] = *(ch+i+1);
						ch3[2] = *(ch+i+2);
						ch3[3] = '\0';
			
						if (ch3[1] == 176) {
							index = ch3[2] - TEL_START_TEL;
							if ((index != 2) && (index >= MATRA_START_TEL1 && index <= MATRA_END_TEL1) || (index >= MATRA_START_TEL3 && index <= MATRA_END_TEL3)) {
								sprintf(utf8_string+j, "%c", eng_tel[index] );
								j ++;
								i += 3;
								continue;
							} else if (index == 2) {
								sprintf(utf8_string+j, "a");
								j++;
							} else if (index >= CON_START_TEL && index <= CON_END_TEL) {
								sprintf(utf8_string+j, "a");
								j++;
								continue;
							} else {								
								continue;
							}
						} else if (ch3[1] == 177) {
							index = ch3[2] - TEL_START_TEL + 64;
							if ((index >= MATRA_START_TEL3 && index <= MATRA_END_TEL3)) {
								sprintf(utf8_string+j, "%c", eng_tel[index] );
								j++;
								i += 3;
							} else {
								i += 3;
								continue;
							}
						} else {
							sprintf (utf8_string+j, "%s", ch3);
							j += 3;
						} 
					} else {
						sprintf(utf8_string+j, "a");
						j ++;
					}
				} else if (ch2[1] == 177) {
					index = 64 + ch2[2] - TEL_START_TEL;
					if ((index >= MATRA_START_TEL2 && index <= MATRA_END_TEL2) || (index >= MATRA_START_TEL3 && index <= MATRA_END_TEL3)) {
						sprintf(utf8_string+j, "%c", eng_tel[index] );
						j ++;
						i += 3;
					} else if (index == (141 + 64 - TEL_START_TEL)) {
						i +=3;
						continue;
					} else {
						sprintf(utf8_string+j, "a"); 			 
						j ++;
					}
				}
			}
		} else if (ch1[1] == 177) {
			index = 64 + ch1[2] - TEL_START_TEL;
			if (index >= NUM_START_TEL && index <= NUM_END_TEL) {
				sprintf(utf8_string+j, "%c", eng_tel[index]);
				j ++;
			}
		} else {

			sprintf(utf8_string+j, "%s", ch1);
			j +=3;
		}
	}
	return utf8_string;
}
