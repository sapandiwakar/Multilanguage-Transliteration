#include "c_api_v2.h"			// Include file for c_api
#include<unistd.h>
#include<getopt.h>

int main()
{
	char *mode = NULL;
	char *path = NULL;
	char *stype = NULL;
	char *slang = NULL;
	char *tlang = NULL;
	char *src= NULL;
	char *tgt= NULL;	
	int c;

	while (1)
	{
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"help", no_argument, &help_flag, 1},
			/* These options don't set a flag.
			   We distinguish them by their indices. */
			{"mode",     required_argument, 0, 'm'},
			{"path", required_argument, 0, 'p'},
			{"stype",  required_argument, 0, 'y'},
			{"srlang",  required_argument, 0, 's'},
			{"tlang",  required_argument, 0, 't'},
			{"src",    required_argument, 0, 'a'},
			{"tgt",    required_argument, 0, 'b'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "m:p:y:s:t:a:b:",
				long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'm':
				mode=optarg;
				break;
			case 'p':
				path=optarg;
				if (path == NULL) {
					pritnf("Please Specify the Path as defined in --help\n)";
					return -1;
				}
				break;

			case 'y':
				stype=optarg;
				if (stype == NULL) {
					pritnf("Please Specify the Source Type as defined in --help\n)";
					return -1;
				}
				break;
			case 's':
				slang=optarg;
				if (slang == NULL) {
					pritnf("Please Specify the Soruce Language as defined in --help\n)";
					return -1;
				}
				break;

			case 't':
				tlang=optarg;
				if (tlang == NULL) {
					pritnf("Please Specify the Target Language as defined in --help\n)";
					return -1;
				}
				break;

			case 'a':
				src=optarg;
				if (src == NULL) {
					pritnf("Please Specify the Source Font as defined in --help\n)";
					return -1;
				}
				break;

			case 'b':
				tgt=optarg;
				if (path == NULL) {
					pritnf("Please Specify the Target Font as defined in --help\n)";
					return -1;
				}

				break;

			default:
				abort ();
		}
	}

	if (!strcmp(src, "wx") && !strcmp(tgt, "utf")) {
		
	  	//Call wx_utf
	} else if (!strcmp(src, "utf") && !strcmp(tgt, "wx")) {
		//Call utf_wx
	}

	return 0;
}
