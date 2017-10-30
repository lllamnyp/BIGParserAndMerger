#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include "parseBig.h"

char * get_extension(char * s)
{
	int i = strlen(s);
	
	for (i; i >= 0; i--)
	{
		if (s[i] == '.') return s + i;
	}
	return s + strlen(s);				// For loop ended without finding dot -> no extension -> return pointer to null terminator of s.
}

int main(int argc, char * argv[])
{
	struct BIGHeader hp;
	char outname[250];
	char fullname[250];
	FILE * f;
    DIR *d;
    bool hash_match = false;
    struct dirent *dir;
    
    printf("Please wait while directory is being scanned...");

	strcpy(outname, "./cache/");
	strcpy(outname + 8, argv[2]); // outname now points to "./cache/[hash=argv[2]]"
   	
	f = fopen(outname, "r");
	
	if (f)
	{
		fscanf(f, "%[^\n]", fullname); // the first line of f should be the hash of that dir
		if (strcmp(fullname, argv[3]) == 0) {hash_match = true;}
		fclose(f);
	}

	if (!hash_match)
	{
	    d = opendir(argv[1]);
	
	    if (d)
	    {
			strcpy(fullname, argv[1]); // put the path into fullname
			char * name = fullname + strlen(fullname); // create a pointer to the end of that
			strcpy(name, "\\"); name++; // append a slash; increment the pointer
			    	
			f = fopen(outname, "w");
			fputs(argv[3], f); fprintf(f, "\n");
			
		    while ((dir = readdir(d)) != NULL)
		    {
		    	if (strcmp(get_extension(dir->d_name), ".big") == 0)
		    	{
		        	strcpy(name, dir->d_name);
					parse_big(fullname, &hp);
					put_big(&hp, f);
				}
		    }
		    fclose(f);
		    closedir(d);
		}
	}
	return 0;
}
