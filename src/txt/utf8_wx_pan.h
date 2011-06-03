//**************************************
// FILE     : utf8_wx.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts punjabi text from utf to wx. The main function calls the function utf_wx_pan for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the caracter boundaries
 * defined next and the map defined in form of an array after the character boundaries.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Define character boundries
 */
#define HIN_START_PAN 128
#define MATRA_START_PAN1 2
#define MATRA_START_PAN2 60
#define MATRA_END_PAN2 60
#define MATRA_START_PAN3 62
#define MATRA_END_PAN3 76

#define VOW_FIRST_START_PAN1 5
#define VOW_FIRST_END_PAN1 11
#define VOW_FIRST_START_PAN2 15
#define VOW_FIRST_END_PAN2 16
#define VOW_FIRST_START_PAN3 19
#define VOW_FIRST_END_PAN3 20

#define CON_START_PAN1 21
#define CON_END_PAN1 57
#define CON_START_PAN2 112
#define CON_END_PAN2 113

#define S_INDEX 56

#define NUM_START_PAN 96
#define NUM_END_PAN 111

char* utf_wx_pan(unsigned char *ch);			// Function to convert from utf8 to wx

char eng_pan[] = {' ', ' ', 'z', ' ', ' ', 'a','A','i','I','u','U', 'q', 'L', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', 'k', 'K', 'g', 'G', 'f', 'c', 'C', 'j', 'J', 'F', 't', 'T', 'd', 'D', 'N', 'w', 'W', 'x', 'X', 'n', 'n', 'p', 'P', 'b', 'B', 'm', 'y', 'r', 'r', 'l', ' ', ' ', 'v', 'S', ' ', 's', 'h', ' ', ' ', 'Z', ' ', 'A', 'i', 'I', 'u', 'U', 'q', 'Q', ' ', ' ', 'e', 'E', ' ', ' ', 'o', 'O', ' ', ' ', '`', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Q', ' ', ' ', ' ', '.', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'M', 'Y'};

char* utf_wx_pan(unsigned char *ch)
{
	unsigned char ch1[4];
	unsigned char ch2[4];
	unsigned char ch3[4];
	char *wx_string = malloc(strlen(ch));
	if (wx_string == NULL) { printf("Can't allocate memory for wx_string\n"); exit;}
	int i = 0;
	int j = 0;
	int k;
	int a;
	int b;
	int index;
	
		
	while ( ch1[0] = *(ch+i) ) {
		if (ch1[0] == '\n') {
			sprintf(wx_string+j, "\n");
			j ++;
			break;
		} else if (ch1[0] == '\0') {
			sprintf(wx_string + j, "a");
			i ++;
			break;
 		} else if (isascii(ch1[0])) {
			sprintf(wx_string+j, "%c", ch1[0]);
			i++;
			j++;
			continue;
		}
		ch1[1] = *(ch+i+1);
		ch1[2] = *(ch+i+2);
		ch1[3] = '\0';
		i += 3;
		
		if (ch1[1] == 168) {
			index = ch1[2] - HIN_START_PAN;
			if ((index >= VOW_FIRST_START_PAN1 && index <= VOW_FIRST_END_PAN1) || (index >= VOW_FIRST_START_PAN2 && index <= VOW_FIRST_END_PAN2) || (index >= VOW_FIRST_START_PAN3 && index <= VOW_FIRST_END_PAN3)) {
				sprintf(wx_string+j, "%c", eng_pan[index]);
				j ++;
			} else if ((index == MATRA_START_PAN1) || (index >= MATRA_START_PAN2 && index <= MATRA_END_PAN2) || (index >= MATRA_START_PAN3 && index <= MATRA_END_PAN3)) {
					sprintf(wx_string+j, "%c", eng_pan[index] );
					j ++;
					continue;
			} else {
				sprintf(wx_string+j, "%c", eng_pan[index]);
				j ++;
				ch2[0] = *(ch+i);
				if (ch2[0] == '\n') {
					sprintf(wx_string+j, "a\n");
					j += 2;
					break;
				} else if (ch2[0] == '\0') {
					sprintf(wx_string + j, "a");
					break;
		 		} else if (isascii(ch2[0])) {
					sprintf(wx_string+j, "a%c", ch2[0]);
					j += 2;
					i++;
					continue;
				}

				ch2[1] = *(ch+i+1);
				ch2[2] = *(ch+i+2);
				ch2[3] = '\0';

				if (ch2[1] == 168) {
					index = ch2[2] - HIN_START_PAN;
					if ((index >= MATRA_START_PAN3 && index <= MATRA_END_PAN3)) {
						sprintf(wx_string+j, "%c", eng_pan[index] );
						j ++;
						i += 3;
					} else if (index == MATRA_START_PAN2) {
						sprintf(wx_string+j, "%c", eng_pan[index]);
						j ++;
						i += 3;
						ch3[0] = *(ch+i);
						if (ch3[0] == '\n') {
							sprintf(wx_string+j, "a\n");
							j += 2;
						} else if (ch3[0] == '\0') {
							sprintf(wx_string + j, "a");
							break;
				 		} else if (isascii(ch3[0])) {
							sprintf(wx_string + j, "a%c", ch3[0]);
							j += 2;
							i++;
							continue;
						}

						ch3[1] = *(ch+i+1);
						ch3[2] = *(ch+i+2);
						ch3[3] = '\0';
			
						if (ch3[1] == 168) {
							index = ch3[2] - HIN_START_PAN;
							if ((index >= MATRA_START_PAN3 && index <= MATRA_END_PAN3)) {
								sprintf(wx_string+j, "%c", eng_pan[index] );
								j ++;
								i += 3;
								continue;
							} else if (index == 2) {
								sprintf(wx_string+j, "a");
								j ++;
							} else if (index >= CON_START_PAN1 && index <= CON_END_PAN1) {
								sprintf(wx_string+j, "a");
								j ++;								
								continue;
							} else {								
								continue;
							}
						} else if (ch3[1] == 169) {
							index = ch3[2] - HIN_START_PAN + 64;
							if ((index >= MATRA_START_PAN3 && index <= MATRA_END_PAN3)) {
								sprintf(wx_string+j, "%c", eng_pan[index] );
								j ++;
								i += 3;
							} else {
								i += 3;
								continue;
							}
						} else {
							sprintf (wx_string+j, "%s", ch3);
							j +=3;
						} 
					} else {
						sprintf(wx_string+j, "a");
						j ++;
					}
				} else if (ch2[1] == 169) {
					index = 64 + ch2[2] - HIN_START_PAN;
					if ((index >= MATRA_START_PAN2 && index <= MATRA_END_PAN2) || (index >= MATRA_START_PAN3 && index <= MATRA_END_PAN3)) {
						sprintf(wx_string+j, "%c", eng_pan[index] );
						j ++;
						i += 3;
					} else if (index == (141 + 64 - HIN_START_PAN)) {
						i +=3;
						continue;
					} else {
						sprintf(wx_string+j, "a"); 			 
						j ++;
					}
				}
			}
		} else if (ch1[1] == 169) {
			index = 64 + ch1[2] - HIN_START_PAN;
			if (index >= NUM_START_PAN && index <= NUM_END_PAN) {
				sprintf(wx_string+j, "%c", eng_pan[index]);
				j ++;
			} else {
				sprintf(wx_string+j, "%c", eng_pan[index]);
				j ++;
			}
		} else {

			sprintf(wx_string+j, "%s", ch1);
			j += 3;
		}
	}
	return wx_string;
}
