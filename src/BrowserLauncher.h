#ifndef _BROWSER_LAUNCHER_H_
#define _BROWSER_LAUNCHER_H_

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Configuration
#define MAX_ENTRIES 15
#define MAX_LINK_LENGTH 120
#define MAX_NAME_LENGTH 20

//Prototypes
void printHelp(void);
void parseConfigFile(char* path);
void printMenu(void);
int rofiMenu(void);
void startBrowser(char *url);

#endif
