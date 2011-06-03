//**************************************
// FILE     : wx_utf8_tam.c(tamil)
// AUTHOR(S): Pulkit Goyal & Sapan Diwakar
// PART OF  : Convertor
// CREATED  : 15th June, 2009
//
// MODIFIED LAST : 15th June, 2009
//***************************************

/*
 * This converter converts tamil text from wx to utf. The main function calls the function wx_utf8_tam for the conversion of each line. The line is then read
 * character by character and the conversion is done according to the language rules regarding consonants, matra and vowels using the arrays defined as 
 * follows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char eng_tam_wx2utf[300][6] = {{"a"}, {"A"}, {"i"}, {"I"}, {"u"}, {"U"}, {"eV"}, {"e"}, {"E"}, {"oV"}, {"o"}, {"O"}, {"H"}, {"Sra"}, {"ka"}, {"kA"}, {"ki"}, {"kI"}, {"ku"}, {"kU"}, {"keV"}, {"ke"}, {"kE"}, {"koV"}, {"ko"}, {"kO"}, {"k"}, {"fa"}, {"fA"}, {"fi"}, {"fI"}, {"fu"}, {"fU"}, {"feV"}, {"fe"}, {"fE"}, {"foV"}, {"fo"}, {"fO"}, {"f"}, {"ca"}, {"cA"}, {"ci"}, {"cI"}, {"cu"}, {"cU"}, {"ceV"}, {"ce"}, {"cE"}, {"coV"},[50] {"co"}, {"cO"}, {"c"}, {"Fa"}, {"FA"}, {"Fi"}, {"FI"}, {"Fu"}, {"FU"}, {"FeV"}, {"Fe"}, {"FE"}, {"FoV"}, {"Fo"}, {"FO"}, {"F"}, {"ta"}, {"tA"}, {"ti"}, {"tI"}, {"tu"}, {"tU"}, {"teV"}, {"te"}, {"tE"}, {"toV"}, {"to"},{"tO"}, {"t"}, {"nYa"}, {"nYA"}, {"nYi"}, {"nYI"}, {"nYu"}, {"nYU"}, {"nYeV"}, {"nYe"}, {"nYE"}, {"nYoV"}, {"nYo"}, {"nYO"}, {"nY"}, {"Na"}, {"NA"}, {"Ni"}, {"NI"}, {"Nu"}, {"NU"}, {"NeV"}, {"Ne"}, {"NE"}, {"NoV"}, {"No"},{"NO"}, {"N"}, {"wa"}, {"wA"}, {"wi"}, {"wI"}, {"wu"}, {"wU"},[111] {"weV"}, {"we"}, {"wE"}, {"woV"}, {"wo"}, {"wO"}, {"w"},{"na"}, {"nA"}, {"ni"}, {"nI"}, {"nu"}, {"nU"}, {"neV"}, {"ne"}, {"nE"}, {"noV"}, {"no"}, {"nO"}, {"n"}, {"pa"}, {"pA"}, {"pi"}, {"pI"}, {"pu"}, {"pU"}, {"peV"}, {"pe"}, {"pE"}, {"poV"}, {"po"}, {"pO"}, {"p"}, {"ma"}, {"mA"}, {"mi"}, {"mI"}, {"mu"}, {"mU"},{"meV"}, {"me"}, {"mE"}, {"moV"}, {"mo"}, {"mO"}, {"m"}, {"ya"}, {"yA"}, {"yi"}, {"yI"}, {"yu"}, {"yU"},{"yeV"}, {"ye"}, {"yE"}, {"yoV"}, {"yo"}, {"yO"}, {"y"}, {"lYYa"}, {"lYYA"}, {"lYYi"}, {"lYYI"}, {"lYYu"}, {"lYYU"}, {"lYYeV"}, {"lYYe"}, {"lYYE"}, {"lYYoV"}, {"lYYo"}, {"lYYE"},{"lYY"}, {"lYa"},{"lYA"}, {"lYi"}, {"lYI"}, {"lYu"}, {"lYU"}, {"lYeV"}, {"lYe"}, {"lYE"}, {"lYoV"},{"lYo"}, {"lYO"}, {"lY"}, {"rYa"}, {"rYA"}, {"rYi"}, {"rYI"},[200] {"rYu"}, {"rYU"}, {"rYeV"}, {"rYe"}, {"rYE"}, {"rYoV"}, {"rYo"}, {"rYO"}, {"rY"}, {"ra"}, {"rA"}, {"ri"}, {"rI"}, {"ru"}, {"rU"},{"reV"}, {"re"}, {"rE"}, {"roV"}, {"ro"}, {"rO"}, {"r"}, {"la"}, {"lA"}, {"li"}, {"lI"}, {"lu"}, {"lU"}, {"leV"}, {"le"}, {"lE"}, {"loV"}, {"lo"}, {"lO"}, {"l"}, {"va"}, {"vA"}, {"vi"}, {"vI"}, {"vu"}, {"vU"}, {"veV"}, {"ve"}, {"vE"}, {"voV"}, {"vo"}, {"vO"}, {"v"}, {"Ra"}, {"RA"}, {"Ri"}, {"RI"}, {"Ru"}, {"RU"}, {"ReV"}, {"Re"}, {"RE"}, {"RoV"}, {"Ro"}, {"RO"}, {"R"}, {"sa"}, {"sA"}, {"si"}, {"sI"}, {"su"}, {"sU"}, {"seV"}, {"se"}, {"sE"},[270] {"soV"}, {"so"}, {"sO"}, {"S"}, {"ja"}, {"jA"}, {"ji"}, {"jI"}, {"ju"}, {"jU"}, {"jeV"}, {"je"}, {"jE"}, {"joV"}, {"jo"}, {"jO"}, {"j"}, {"ha"}, {"hA"}, {"hi"}, {"hI"}, {"hu"}, {"hU"}, {"heV"}, {"he"}, {"hE"}, {"hoV"}, {"ho"}, {"hO"}, {"h"}};

char utf_tam_wx2utf[300][15] = {{"அ"},{"ஆ"},{"இ"},{"ஈ"},{"உ"},{"ஊ"},{"எ"},{"ஏ"},{"ஐ"},{"ஒ"},{"ஓ"},{"ஔ"},{"ஃ"},{"ஸ்ர"},{"க"},{"கா"},{"கி"},{"கீ"},{"கு"},{"கூ"},{"கெ"},{"கே"},{"கை"},{"கொ"},{"கோ"},{"கௌ"},{"க்"},{"ங"},{"ஙா"},{"ஙி"},{"ஙீ"},{"ஙு"},{"ஙூ"},{"ஙெ"},{"ஙே"},{"ஙை"},{"ஙொ"},{"ஙோ"},{"ஙௌ"},{"ங்"},{"ச"},{"சா"},{"சி"},{"சீ"},{"சு"},{"சூ"},{"செ"},{"சே"},{"சை"},{"சொ"},{"சோ"},{"சௌ"},{"ச்"},{"ஞ"},{"ஞா"},{"ஞி"},{"ஞீ"},{"ஞு"},{"ஞூ"},{"ஞெ"},{"ஞே"},{"ஞை"},{"ஞொ"},{"ஞோ"},{"ஞௌ"},{"ஞ்"},{"ட"},{"டா"},{"டி"},{"டீ"},{"டு"},{"டூ"},{"டெ"},{"டே"},{"டை"},{"டொ"},{"டோ"},{"டௌ"},{"ட்"},{"ன"},{"னா"},{"னி"},{"னீ"},{"னு"},{"னூ"},{"னெ"},{"னே"},{"னை"},{"னொ"},{"னோ"},{"னௌ"},{"ன்"},{"ண"},{"ணா"},{"ணி"},{"ணீ"},{"ணு"},{"ணூ"},{"ணெ"},{"ணே"},{"ணை"},{"ணொ"},{"ணோ"},{"ணௌ"},{"ண்"},{"த"},{"தா"},{"தி"},{"தீ"},{"து"},{"தூ"},{"தெ"},{"தே"},{"தை"},{"தொ"},{"தோ"},{"தௌ"},{"த்"},{"ந"},{"நா"},{"நி"},{"நீ"},{"நு"},{"நூ"},{"நெ"},{"நே"},{"நை"},{"நொ"},{"நோ"},{"நௌ"},{"ந்"},{"ப"},{"பா"},{"பி"},{"பீ"},{"பு"},{"பூ"},{"பெ"},{"பே"},{"பை"},{"பொ"},{"போ"},{"பௌ"},{"ப்"},{"ம"},{"மா"},{"மி"},{"மீ"},{"மு"},{"மூ"},{"மெ"},{"மே"},{"மை"},{"மொ"},{"மோ"},{"மௌ"},{"ம்"},{"ய"},{"யா"},{"யி"},{"யீ"},{"யு"},{"யூ"},{"யெ"},{"யே"},{"யை"},{"யொ"},{"யோ"},{"யௌ"},{"ய்"},{"ழ"},{"ழா"},{"ழி"},{"ழீ"},{"ழு"},{"ழூ"},{"ழெ"},{"ழே"},{"ழை"},{"ழொ"},{"ழோ"},{"ழௌ"},{"ழ்"},{"ள"},{"ளா"},{"ளி"},{"ளீ"},{"ளு"},{"ளூ"},{"ளெ"},{"ளே"},{"ளை"},{"ளொ"},{"ளோ"},{"ளௌ"},{"ள்"},{"ற"},{"றா"},{"றி"},{"றீ"},{"று"},{"றூ"},{"றெ"},{"றே"},{"றை"},{"றொ"},{"றோ"},{"றௌ"},{"ற்"},{"ர"},{"ரா"},{"ரி"},{"ரீ"},{"ரு"},{"ரூ"},{"ரெ"},{"ரே"},{"ரை"},{"ரொ"},{"ரோ"},{"ரௌ"},{"ர்"},{"ல"},{"லா"},{"லி"},{"லீ"},{"லு"},{"லூ"},{"லெ"},{"லே"},{"லை"},{"லொ"},{"லோ"},{"லௌ"},{"ல்"},{"வ"},{"வா"},{"வி"},{"வீ"},{"வு"},{"வூ"},{"வெ"},{"வே"},{"வை"},{"வொ"},{"வோ"},{"வௌ"},{"வ்"},{"ஷ"},{"ஷா"},{"ஷி"},{"ஷீ"},{"ஷு"},{"ஷூ"},{"ஷெ"},{"ஷே"},{"ஷை"},{"ஷொ"},{"ஷோ"},{"ஷௌ"},{"ஷ்"},{"ஸ"},{"ஸா"},{"ஸி"},{"ஸீ"},{"ஸு"},{"ஸூ"},{"ஸெ"},{"ஸே"},{"ஸை"},{"ஸொ"},{"ஸோ"},{"ஸௌ"},{"ஸ்"},{"ஜ"},{"ஜா"},{"ஜி"},{"ஜீ"},{"ஜு"},{"ஜூ"},{"ஜெ"},{"ஜே"},{"ஜை"},{"ஜொ"},{"ஜோ"},{"ஜௌ"},{"ஜ்"},{"ஹ"},{"ஹா"},{"ஹி"},{"ஹீ"},{"ஹு"},{"ஹூ"},{"ஹெ"},{"ஹே"},{"ஹை"},{"ஹொ"},{"ஹோ"},{"ஹௌ"},{"ஹ்"}};

char *wx_utf8_tam(unsigned char *wx_string)
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

		for (k = 0; k < 300; k ++) {
			if (!strcmp(ch5, eng_tam_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_tam_wx2utf[k]);
				j += strlen(utf_tam_wx2utf[k]);
				i += strlen(eng_tam_wx2utf[k]);
				break;
			} else if (!strcmp(ch4, eng_tam_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_tam_wx2utf[k]);
				j += strlen(utf_tam_wx2utf[k]);
				i += strlen(eng_tam_wx2utf[k]);
				break;
			} else if (!strcmp(ch3, eng_tam_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_tam_wx2utf[k]);
				j += strlen(utf_tam_wx2utf[k]);
				i += strlen(eng_tam_wx2utf[k]);
				break;
			} else if (!strcmp(ch2, eng_tam_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_tam_wx2utf[k]);
				j += strlen(utf_tam_wx2utf[k]);
				i += strlen(eng_tam_wx2utf[k]);
				break;
			} else if (!strcmp(ch1, eng_tam_wx2utf[k])) {
				sprintf(utf8_string+j, "%s", utf_tam_wx2utf[k]);
				j += strlen(utf_tam_wx2utf[k]);
				i += strlen(eng_tam_wx2utf[k]);
				break;
			}
		}

		if (k == 300) {
			sprintf(utf8_string+j,"%c",ch1[0]);
			j = j+1;
			i++;
		}
	}
	return utf8_string;
}
