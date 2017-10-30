struct BIGHeader
{
	char * fullname;
	char comment[120];
	double t;
	double aoi;
	double pola;
	double res;
	double min;
	double max;
	int scans;
	char range;
};

void parse_big(char * fname, struct BIGHeader * head);

void print_big(struct BIGHeader * hp);

void put_big(struct BIGHeader * head, FILE * f);
