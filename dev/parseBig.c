#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parseBig.h"

char get_range(double min, double max)
{
	if (0. < min && min < 300. || 300. < max && max < 1200.) return 'F';
	if (300. < min && min < 1000. || 3000. < max && max < 6000.) return 'M';
	if (1500. < min && min < 4000. || 6000. < max && max < 10000.) return 'N';
	return 'V';
}

void parse_big(char * fname, struct BIGHeader * head) // Take a struct pointer and populate it from a .big file
{	
	FILE * f;
	char * ss[5];
	char * const buff = malloc(250 * sizeof(char));
	char * pos;
	double min;
	double max;
	
	head->fullname = fname;		// !!! This is a pointer type, make no assumptions that the name stored at that memory location won't change !!!
	
	f = fopen(fname, "r");
	
	fgets(buff, 250, f); // get first line
	
	ss[0] = buff;
	pos = strstr(ss[0], ", T=");	pos[0] = '\0'; ss[1] = pos + 4;		// Split the string at memory location buff
	pos = strstr(ss[1], "K, ");		pos[0] = '\0'; ss[2] = pos + 3;		// into
	pos = strstr(ss[2], "/");		pos[0] = '\0'; ss[3] = pos + 1;		// these
	pos = strstr(ss[3], ", ");		pos[0] = '\0'; ss[4] = pos + 2;		// five
	pos = strstr(ss[4], "scans");	pos[0] = '\0';						// tokens

	sscanf(ss[0], "%[^\0]", head->comment);	// write the five tokens
	sscanf(ss[1], "%lf", &head->t);			// to the memory assigned
	sscanf(ss[2], "%lf", &(head->aoi));		// for the struct
	sscanf(ss[3], "%lf", &(head->pola));	// head
	sscanf(ss[4], "%d",  &(head->scans));	// now buff can be reused
	
	fgets(buff, 250, f); 		// Skip
	fgets(buff, 250, f);		// two lines
	fscanf(f, "%10c", buff);	// and read the first 10 chars of the third

	sscanf(buff, "%10lf", &min); // reading only 10 chars from buff so we don't have to terminate with null
	
	fgets(buff, 250, f);		// Go to next line
	fscanf(f, "%10c", buff);	// 10 more chars
	sscanf(buff, "%10lf", &max);// next wavelength obtained
	
	head->res = max > min ? max - min : min - max;	// resolution is difference between two adjacent wavelengths
	
	fseek(f, -300, SEEK_END);	// 300 chars before EOF is certainly somewhere in the 2nd-to-last line
	fgets(buff, 250, f);		// read remainder of that line

	fscanf(f, "%10c", buff);	// and read the first 10 chars of the last line

	sscanf(buff, "%10lf", &max); // only 10 chars
	
	free(buff);
	
	fclose(f);
	
	if (min>max)
	{
		min -= max; max += min; min = max - min;
	}
	
	head->min = min;
	head->max = max;
	
	head->range = get_range(min, max);
		
}

void print_big(struct BIGHeader * hp)
{
	for (char * i = hp->comment; i[0] != '\0'; printf("%c", 0[i++])) {}
	printf("\nTemperature: %.1f K\n", hp->t);
	printf("Angle of incidence: %.1f\n", hp->aoi);
	printf("Polarizer azimuth: %.1f\n", hp->pola);
	printf("No. of scans: %d\n", hp->scans);
	printf("Resolution: %.2f cm-1\n", hp->res);
	printf("Min energy: %.2f cm-1\n", hp->min);
	printf("Max energy: %.2f cm-1\n", hp->max);
	printf("Spectral range identifier: %c", hp->range);
}

void put_big(struct BIGHeader * head, FILE * f) // Write the header to an open file as tab-
{												// separated values and terminate with newline.
	fputs(head->fullname, f);
	fprintf(f, "\t");
	fputs(head->comment, f);
	fprintf(f, "\t%.1f\t%.1f\t%.1f\t%d\t%.2f\t%.2f\t%.2f\t%c\n", head->t,head->aoi,head->pola,head->scans,head->res,head->min,head->max,head->range);
}
