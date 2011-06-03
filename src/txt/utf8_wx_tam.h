//**************************************
// FILE     : wx_utf8.c
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts tamil text from wx to utf. The main function calls the function wx_utf8 for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined as 
 * follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char eng_tam[300][6] = {{"a"}, {"A"}, {"i"}, {"I"}, {"u"}, {"U"}, {"eV"}, {"e"}, {"E"}, {"oV"}, {"o"}, {"O"}, {"H"}, {"Sra"},  {"kA"}, {"ki"}, {"kI"}, {"ku"}, {"kU"}, {"keV"}, {"ke"}, {"kE"}, {"koV"}, {"ko"}, {"kO"}, {"k"}, {"ka"}, {"fA"}, {"fi"}, {"fI"}, {"fu"}, {"fU"}, {"feV"}, {"fe"}, {"fE"}, {"foV"}, {"fo"}, {"fO"}, {"f"}, {"fa"}, {"cA"}, {"ci"}, {"cI"}, {"cu"}, {"cU"}, {"ceV"}, {"ce"}, {"cE"}, {"coV"}, {"co"}, {"cO"}, {"c"}, {"ca"}, {"FA"}, {"Fi"}, {"FI"}, {"Fu"}, {"FU"}, {"FeV"}, {"Fe"}, {"FE"}, {"FoV"}, {"Fo"}, {"FO"}, {"F"}, {"Fa"}, {"tA"}, {"ti"}, {"tI"}, {"tu"}, {"tU"}, {"teV"}, {"te"}, {"tE"}, {"toV"}, {"to"},{"tO"}, {"t"}, {"ta"}, {"NA"}, {"Ni"}, {"NI"}, {"Nu"}, {"NU"}, {"NeV"}, {"Ne"}, {"NE"}, {"NoV"}, {"No"},{"NO"}, {"N"}, {"Na"}, {"wA"}, {"wi"}, {"wI"}, {"wu"}, {"wU"}, {"weV"}, {"we"}, {"wE"}, {"woV"}, {"wo"}, {"wO"}, {"w"}, {"wa"}, {"nA"}, {"ni"}, {"nI"}, {"nu"}, {"nU"}, {"neV"}, {"ne"}, {"nE"}, {"noV"}, {"no"}, {"nO"}, {"n"}, {"na"}, {"pA"}, {"pi"}, {"pI"}, {"pu"}, {"pU"}, {"peV"}, {"pe"}, {"pE"}, {"poV"}, {"po"}, {"pO"}, {"p"}, {"pa"}, {"mA"}, {"mi"}, {"mI"}, {"mu"}, {"mU"},{"meV"}, {"me"}, {"mE"}, {"moV"}, {"mo"}, {"mO"}, {"m"}, {"ma"}, {"yA"}, {"yi"}, {"yI"}, {"yu"}, {"yU"},{"yeV"}, {"ye"}, {"yE"}, {"yoV"}, {"yo"}, {"yO"}, {"y"}, {"ya"}, {"lYYA"}, {"lYYi"}, {"lYYI"}, {"lYYu"}, {"lYYU"}, {"lYYeV"}, {"lYYe"}, {"lYYE"}, {"lYYoV"}, {"lYYo"}, {"lYYE"}, {"lYY"}, {"lYYa"}, {"lYA"}, {"lYi"}, {"lYI"}, {"lYu"}, {"lYU"}, {"lYeV"}, {"lYe"}, {"lYE"}, {"lYoV"},{"lYo"}, {"lYO"}, {"lY"}, {"lYa"}, {"rYA"}, {"rYi"}, {"rYI"}, {"rYu"}, {"rYU"}, {"rYeV"}, {"rYe"}, {"rYE"}, {"rYoV"}, {"rYo"}, {"rYO"}, {"rY"}, {"rYa"}, {"nYA"}, {"nYi"}, {"nYI"}, {"nYu"}, {"nYU"}, {"nYeV"}, {"nYe"}, {"nYE"}, {"nYoV"}, {"nYo"}, {"nYO"}, {"nY"}, {"nYa"}, {"rA"}, {"ri"}, {"rI"}, {"ru"}, {"rU"},{"reV"}, {"re"}, {"rE"}, {"roV"}, {"ro"}, {"rO"}, {"r"}, {"ra"}, {"lA"}, {"li"}, {"lI"}, {"lu"}, {"lU"}, {"leV"}, {"le"}, {"lE"}, {"loV"}, {"lo"}, {"lO"}, {"l"}, {"la"}, {"vA"}, {"vi"}, {"vI"}, {"vu"}, {"vU"}, {"veV"}, {"ve"}, {"vE"}, {"voV"}, {"vo"}, {"vO"}, {"v"}, {"va"}, {"RA"}, {"Ri"}, {"RI"}, {"Ru"}, {"RU"}, {"ReV"}, {"Re"}, {"RE"}, {"RoV"}, {"Ro"}, {"RO"}, {"R"}, {"Ra"}, {"sA"}, {"si"}, {"sI"}, {"su"}, {"sU"}, {"seV"}, {"se"}, {"sE"}, {"soV"}, {"so"}, {"sO"}, {"s"}, {"sa"}, {"jA"}, {"ji"}, {"jI"}, {"ju"}, {"jU"}, {"jeV"}, {"je"}, {"jE"}, {"joV"}, {"jo"}, {"jO"}, {"j"}, {"ja"}, {"hA"}, {"hi"}, {"hI"}, {"hu"}, {"hU"}, {"heV"}, {"he"}, {"hE"}, {"hoV"}, {"ho"}, {"hO"}, {"h"}, {"ha"}};
char utf_tam[300][15] = {{"அ"},{"ஆ"},{"இ"},{"ஈ"},{"உ"},{"ஊ"},{"எ"},{"ஏ"},{"ஐ"},{"ஒ"},{"ஓ"},{"ஔ"},{"ஃ"},{"ஸ்ர"},{"கா"},{"கி"},{"கீ"},{"கு"},{"கூ"},{"கெ"},{"கே"},{"கை"},{"கொ"},{"கோ"},{"கௌ"},{"க்"},{"க"},{"ஙா"},{"ஙி"},{"ஙீ"},{"ஙு"},{"ஙூ"},{"ஙெ"},{"ஙே"},{"ஙை"},{"ஙொ"},{"ஙோ"},{"ஙௌ"},{"ங்"},{"ங"},{"சா"},{"சி"},{"சீ"},{"சு"},{"சூ"},{"செ"},{"சே"},{"சை"},{"சொ"},{"சோ"},{"சௌ"},{"ச்"},{"ச"},{"ஞா"},{"ஞி"},{"ஞீ"},{"ஞு"},{"ஞூ"},{"ஞெ"},{"ஞே"},{"ஞை"},{"ஞொ"},{"ஞோ"},{"ஞௌ"},{"ஞ்"},{"ஞ"},{"டா"},{"டி"},{"டீ"},{"டு"},{"டூ"},{"டெ"},{"டே"},{"டை"},{"டொ"},{"டோ"},{"டௌ"},{"ட்"},{"ட"},{"ணா"},{"ணி"},{"ணீ"},{"ணு"},{"ணூ"},{"ணெ"},{"ணே"},{"ணை"},{"ணொ"},{"ணோ"},{"ணௌ"},{"ண்"},{"ண"},{"தா"},{"தி"},{"தீ"},{"து"},{"தூ"},{"தெ"},{"தே"},{"தை"},{"தொ"},{"தோ"},{"தௌ"},{"த்"},{"த"},{"நா"},{"நி"},{"நீ"},{"நு"},{"நூ"},{"நெ"},{"நே"},{"நை"},{"நொ"},{"நோ"},{"நௌ"},{"ந்"},{"ந"},{"பா"},{"பி"},{"பீ"},{"பு"},{"பூ"},{"பெ"},{"பே"},{"பை"},{"பொ"},{"போ"},{"பௌ"},{"ப்"},{"ப"},{"மா"},{"மி"},{"மீ"},{"மு"},{"மூ"},{"மெ"},{"மே"},{"மை"},{"மொ"},{"மோ"},{"மௌ"},{"ம்"},{"ம"},{"யா"},{"யி"},{"யீ"},{"யு"},{"யூ"},{"யெ"},{"யே"},{"யை"},{"யொ"},{"யோ"},{"யௌ"},{"ய்"},{"ய"},{"ழா"},{"ழி"},{"ழீ"},{"ழு"},{"ழூ"},{"ழெ"},{"ழே"},{"ழை"},{"ழொ"},{"ழோ"},{"ழௌ"},{"ழ்"},{"ழ"},{"ளா"},{"ளி"},{"ளீ"},{"ளு"},{"ளூ"},{"ளெ"},{"ளே"},{"ளை"},{"ளொ"},{"ளோ"},{"ளௌ"},{"ள்"},{"ள"},{"றா"},{"றி"},{"றீ"},{"று"},{"றூ"},{"றெ"},{"றே"},{"றை"},{"றொ"},{"றோ"},{"றௌ"},{"ற்"},{"ற"},{"னா"},{"னி"},{"னீ"},{"னு"},{"னூ"},{"னெ"},{"னே"},{"னை"},{"னொ"},{"னோ"},{"னௌ"},{"ன்"},{"ன"},{"ரா"},{"ரி"},{"ரீ"},{"ரு"},{"ரூ"},{"ரெ"},{"ரே"},{"ரை"},{"ரொ"},{"ரோ"},{"ரௌ"},{"ர்"},{"ர"},{"லா"},{"லி"},{"லீ"},{"லு"},{"லூ"},{"லெ"},{"லே"},{"லை"},{"லொ"},{"லோ"},{"லௌ"},{"ல்"},{"ல"},{"வா"},{"வி"},{"வீ"},{"வு"},{"வூ"},{"வெ"},{"வே"},{"வை"},{"வொ"},{"வோ"},{"வௌ"},{"வ்"},{"வ"},{"ஷா"},{"ஷி"},{"ஷீ"},{"ஷு"},{"ஷூ"},{"ஷெ"},{"ஷே"},{"ஷை"},{"ஷொ"},{"ஷோ"},{"ஷௌ"},{"ஷ்"},{"ஷ"},{"ஸா"},{"ஸி"},{"ஸீ"},{"ஸு"},{"ஸூ"},{"ஸெ"},{"ஸே"},{"ஸை"},{"ஸொ"},{"ஸோ"},{"ஸௌ"},{"ஸ்"},{"ஸ"},{"ஜா"},{"ஜி"},{"ஜீ"},{"ஜு"},{"ஜூ"},{"ஜெ"},{"ஜே"},{"ஜை"},{"ஜொ"},{"ஜோ"},{"ஜௌ"},{"ஜ்"},{"ஜ"},{"ஹா"},{"ஹி"},{"ஹீ"},{"ஹு"},{"ஹூ"},{"ஹெ"},{"ஹே"},{"ஹை"},{"ஹொ"},{"ஹோ"},{"ஹௌ"},{"ஹ்"},{"ஹ"}};

char *utf_wx_tam(unsigned char *utf8_string)
{
	unsigned char *wx_string = malloc(6*strlen(utf8_string));
	if (wx_string == NULL) { printf("Can't allocate memory for wx_string\n"); exit;}

	
	int i=0,j=0,k=0,l,con_ind=0,vow_ind=0,next_vow_ind=0,first_vow_ind=0,flag_con,flag_vow,flag_first_vow,next_flag_vow;
	char ch,ch_next,ch_next_next;
	while(*(utf8_string+i) != '\0') {
		char ch1[4];
		char ch2[7];
		char ch3[10];
		char ch4[13];
		char ch5[16];

		for (k = 0; k < 15; k ++) {
			ch5[k] = *(utf8_string+i+k);
		}
		ch5[k] = '\0';

		for (k = 0; k < 12; k ++) {
			ch4[k] = *(utf8_string+i+k);
		}
		ch4[k] = '\0';
		for (k = 0; k < 9; k ++) {
			ch3[k] = *(utf8_string+i+k);
		}
		ch3[k] = '\0';

		for (k = 0; k < 6; k ++) {
			ch2[k] = *(utf8_string+i+k);
		}
		ch2[k] = '\0';
		for (k = 0; k < 3; k ++) {
			ch1[k] = *(utf8_string+i+k);
		}
		ch1[k] = '\0';

		for (k = 0; k < 300; k ++) {
			if (!strcmp(ch5, utf_tam[k])) {
				sprintf(wx_string+j, "%s", eng_tam[k]);
				j += strlen(eng_tam[k]);
				i += strlen(utf_tam[k]);
				break;
			} else if (!strcmp(ch4, utf_tam[k])) {
				sprintf(wx_string+j, "%s", eng_tam[k]);
				j += strlen(eng_tam[k]);
				i += strlen(utf_tam[k]);
				break;
			} else if (!strcmp(ch3, utf_tam[k])) {
				sprintf(wx_string+j, "%s", eng_tam[k]);
				j += strlen(eng_tam[k]);
				i += strlen(utf_tam[k]);
				break;
			} else if (!strcmp(ch2, utf_tam[k])) {
				sprintf(wx_string+j, "%s", eng_tam[k]);
				j += strlen(eng_tam[k]);
				i += strlen(utf_tam[k]);
				break;
			} else if (!strcmp(ch1, utf_tam[k])) {
				sprintf(wx_string+j, "%s", eng_tam[k]);
				j += strlen(eng_tam[k]);
				i += strlen(utf_tam[k]);
				break;
			}
		}

		if (k == 300) {
			sprintf(wx_string+j,"%c",ch1[0]);
			j ++;
			i ++;
		}
	}
	return wx_string;
}


