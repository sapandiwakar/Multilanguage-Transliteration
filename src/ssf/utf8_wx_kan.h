//**************************************
// FILE     : utf8_wx.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts kannada text from utf to wx. The main function calls the function utf_wx_kan for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the caracter boundaries
 * defined next and the map defined in form of an array after the character boundaries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Define Character boundries
 */
#define KAN_START_KAN 128
#define MATRA_START_KAN1 1
#define MATRA_END_KAN1 3 
#define MATRA_START_KAN2 60
#define MATRA_END_KAN2 60
#define MATRA_START_KAN3 62
#define MATRA_END_KAN3 76

#define VOW_FIRST_START_KAN1 5
#define VOW_FIRST_END_KAN1 11
#define VOW_FIRST_START_KAN2 15
#define VOW_FIRST_END_KAN2 16
#define VOW_FIRST_START_KAN3 19
#define VOW_FIRST_END_KAN3 20

#define CON_START_KAN 21
#define CON_END_KAN 57

#define NUM_START_KAN 96
#define NUM_END_KAN 111

char* utf_wx_kan(unsigned char *ch);

char eng_kan[] = {' ', 'z', 'M', 'H', ' ', 'a','A','i','I','u','U', 'q', 'L', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', 'k', 'K', 'g', 'G', 'f', 'c', 'C', 'j', 'J', 'F', 't', 'T', 'd', 'D', 'N', 'w', 'W', 'x', 'X', 'n', 'n', 'p', 'P', 'b', 'B', 'm', 'Y', 'r', 'r', 'l', ' ', ' ', 'v', 'S', 'R', 's', 'h', ' ', ' ', 'Z', ' ', 'A', 'i', 'I', 'u', 'U', 'q', 'Q', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', ' ', ' ', '`', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Q', ' ', ' ', ' ', '.', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


char* utf_wx_kan(unsigned char *ch)
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
		if (!strcmp(ch1, "ಎ")) {
			sprintf(utf8_string+j, "eV");
			j += 2;
		} else if (!strcmp(ch1, "ಒ")) {
			sprintf(utf8_string+j,"oV");
			j += 2;
		} else if (!strcmp(ch1, "ಳ")) {
			sprintf(utf8_string+j, "lY");
			j += 2;
		} else if (ch1[1] == 178) {
			index = ch1[2] - KAN_START_KAN;
			if ((index >= VOW_FIRST_START_KAN1 && index <= VOW_FIRST_END_KAN1) || (index >= VOW_FIRST_START_KAN2 && index <= VOW_FIRST_END_KAN2) || (index >= VOW_FIRST_START_KAN3 && index <= VOW_FIRST_END_KAN3)) {
				sprintf(utf8_string+j, "%c", eng_kan[index]);
				j++;
			} else if ((index >= MATRA_START_KAN1 && index <= MATRA_END_KAN1) || (index >= MATRA_START_KAN2 && index <= MATRA_END_KAN2) || (index >= MATRA_START_KAN3 && index <= MATRA_END_KAN3)) {
					sprintf(utf8_string+j, "%c", eng_kan[index] );
					j++;
					continue;
			} else {
				sprintf(utf8_string+j, "%c", eng_kan[index]);
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

				if (ch2[1] == 178) {
					index = ch2[2] - KAN_START_KAN;
					if ((index >= MATRA_START_KAN3 && index <= MATRA_END_KAN3)) {
						sprintf(utf8_string+j, "%c", eng_kan[index] );
						j ++;
						i += 3;
					} else if (index == MATRA_START_KAN2) {
						sprintf(utf8_string+j, "%c", eng_kan[index]);
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
			
						if (ch3[1] == 178) {
							index = ch3[2] - KAN_START_KAN;
							if ((index != 2) && (index >= MATRA_START_KAN1 && index <= MATRA_END_KAN1) || (index >= MATRA_START_KAN3 && index <= MATRA_END_KAN3)) {
								sprintf(utf8_string+j, "%c", eng_kan[index] );
								j ++;
								i += 3;
								continue;
							} else if (index == 2) {
								sprintf(utf8_string+j, "a");
								j++;
							} else if (index >= CON_START_KAN && index <= CON_END_KAN) {
								sprintf(utf8_string+j, "a");
								j++;
								continue;
							} else {								
								continue;
							}
						} else if (ch3[1] == 179) {
							index = ch3[2] - KAN_START_KAN + 64;
							if ((index >= MATRA_START_KAN3 && index <= MATRA_END_KAN3)) {
								sprintf(utf8_string+j, "%c", eng_kan[index] );
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
				} else if (ch2[1] == 179) {
					index = 64 + ch2[2] - KAN_START_KAN;
					if ((index >= MATRA_START_KAN2 && index <= MATRA_END_KAN2) || (index >= MATRA_START_KAN3 && index <= MATRA_END_KAN3)) {
						sprintf(utf8_string+j, "%c", eng_kan[index] );
						j ++;
						i += 3;
					} else if (index == (141 + 64 - KAN_START_KAN)) {
						i +=3;
						continue;
					} else {
						sprintf(utf8_string+j, "a"); 			 
						j ++;
					}
				}
			}
		} else if (ch1[1] == 179) {
			index = 64 + ch1[2] - KAN_START_KAN;
			if (index >= NUM_START_KAN && index <= NUM_END_KAN) {
				sprintf(utf8_string+j, "%c", eng_kan[index]);
				j ++;
			}
		} else {

			sprintf(utf8_string+j, "%s", ch1);
			j +=3;
		}
	}
	return utf8_string;
}
