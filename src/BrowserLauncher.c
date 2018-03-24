#include "BrowserLauncher.h"

char bookmarkNames[MAX_ENTRIES][MAX_NAME_LENGTH];
char bookmarkLinks[MAX_ENTRIES][MAX_LINK_LENGTH];
int storedLinks = 0;

int main(int argv, char **argc)
{
	char *config_path;
	char *homeDir = getenv("HOME");
	char *defaultLocationInHome = "/.config/BrowserLauncher/config";

    switch(argv)
    {
		case 1:
            // Use default path
			config_path = (char *) malloc((strlen(homeDir)+strlen(defaultLocationInHome))*sizeof(char));
            strcpy(config_path, homeDir);
			strcat(config_path, defaultLocationInHome);
            break;

        case 2:
            // Use custom path or display help
            if(!strcmp("-h", argc[1]))
            {
                printHelp();
                exit(0);
            }
            else
            {
                config_path = (char *) malloc((strlen(argc[1]+1)*sizeof(char)));
                strcpy(config_path, argc[1]);
            }

            break;

        default:
            printf("Invalid command\nTry '-h' for more information.\n");
            exit(0);
            break;
    }

	parseConfigFile(config_path);

	int entry = rofiMenu();
	if(entry != -1)
	{
		startBrowser(bookmarkLinks[entry]);
	}

    return 0;
}

void printHelp()
{
    printf("Help message.\n");
}

void parseConfigFile(char* path)
{
	FILE *fp;

	fp = fopen(path, "r");

	if(fp == NULL) {
	    printf("Error while opening file: %s\n", path);
	    exit(1);
	}
	else
	{
		char charBuffer;
		int line = 1;

		while((charBuffer = getc(fp)) != EOF)
		{
			if(charBuffer == '#')
			{
				while(getc(fp) != '\n');
				line++;
			}
			else
			{
				int charCounter = 0;

				while(charBuffer != EOF && charBuffer != ':')
				{
					if(charCounter != MAX_NAME_LENGTH - 1)
					{
						bookmarkNames[storedLinks][charCounter++] = charBuffer;
					}
					else
					{
						printf("ERROR: Link name on line: %d, in file: %s is to long.\n", line, path);
						exit(1);
					}
					charBuffer = getc(fp);
				}
				bookmarkNames[storedLinks][charCounter] = '\0';

				charBuffer = getc(fp);
				while(charBuffer == ' ' || charBuffer == '\t')
				{
					 charBuffer = getc(fp);
				}

				charCounter = 0;

				while(charBuffer != EOF && charBuffer != '\n')
				{
					if(charCounter != MAX_LINK_LENGTH - 1)
					{
						bookmarkLinks[storedLinks][charCounter++] = charBuffer;
					}
					else {
						printf("ERROR: Link on line %d, in config file %s is to long.\n", line, path);
					}
					charBuffer = getc(fp);
				}
				bookmarkLinks[storedLinks][charCounter] = '\0';

				if(++storedLinks == MAX_ENTRIES)
				{
					printf("ERROR: On line: %d, in file %s.\nTo many entries.\n", line, path);
				}

				line++;
			}
		}
	}
}

int rofiMenu() {

	char *commandFirst = "echo -e \"";
	char *commandLast = "\" | rofi -dmenu -p Sites";
	char *command;

	if((command = (char *) malloc(strlen(commandFirst) + strlen(commandLast) + MAX_NAME_LENGTH*storedLinks)) == NULL)
	{
		printf("ERROR: malloc failed.\n");
		exit(0);
	}

	command[0] = '\n';
	command = strcat(command,commandFirst);

	int i;
	for(i = 0; i < storedLinks - 1; i++) {
		command = strcat(command,bookmarkNames[i]);
		command = strcat(command,"\n");
	}
	command = strcat(command,bookmarkNames[i]);
	command = strcat(command, commandLast);

	FILE *fp;

	fp = popen(command, "r");
	if(fp == NULL) {
		printf("ERORR: Failed to run command");
	}

	free(command);

	char output[MAX_NAME_LENGTH];
	fgets(output, MAX_NAME_LENGTH-1, fp);

	output[strlen(output)-1] = '\0';

	for(int i = 0; i < storedLinks; i++)
	{
		if(strcmp(bookmarkNames[i], output) == 0)
		{
			return i;
		}
	}

	return -1;
}

void startBrowser(char *url)
{
	char *command;
	if((command = (char *) malloc(strlen("xdg-open ") + strlen(url))) == NULL)
	{
		printf("ERROR: malloc failed.\n");
		exit(0);
	}

	command = strcpy(command, "xdg-open ");
	command = strcat(command, url);

	system(command);
	free(command);
}
