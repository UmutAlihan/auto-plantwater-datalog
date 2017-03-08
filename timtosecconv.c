#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	int hrs = 0;
	int mins = 0; 
	int secs = 0;

	char time[] = "00:00:10";
	sscanf(time,"%d:%d:%d", &hrs, &mins, &secs);
	printf("%d,%d,%d\n", hrs,mins,secs);
	int totsec = (hrs*60*60) + (mins*60) + secs;
	printf("%d\n", totsec);
	return 0;
}


