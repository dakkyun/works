#include <stdio.h>
int main()
{
	FILE *fp;
	char a = 1,b = 2,c = 3;
	
	fp = fopen("file.txt","w");
	fprintf(fp, "%c\n", a);
	
	fclose(fp);

	fp = fopen("file.txt","w");
	fclose(fp);
	
	return 0;
}
