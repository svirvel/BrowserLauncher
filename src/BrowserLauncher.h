#ifndef _BROWSER_LAUNCHER_H_
#define _BROWSER_LAUNCHER_H_

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Configuration
#define DEFAULT_CONFIG_PATH "~/.config/BrowserLauncher/config"
#define LENGTH_DEFAULT_CONFIG_PATH 33

#define MAX_ENTRIES 10
#define MAX_LINK_LENGTH 50
#define MAX_NAME_LENGTH 20

//Prototypes
void printHelp(void);
void parseConfigFile(char* path);
void printMenu(void);
int rofiMenu(void);
void startBrowser(char *url);

#endif
