#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
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
	char fullname[250];
	FILE * f;
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);

    if (d)
    {
    	strcpy(fullname, argv[1]); // put the path into fullname
    	char * name = fullname + strlen(fullname); // create a pointer to the end of that
    	strcpy(name, "\\"); name++; // append a slash; increment the pointer
    	
		f = fopen("out", "w");
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

	return 0;
}
