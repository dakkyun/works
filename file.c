#include <stdio.h>
int main()
{
	FILE *fp;
    int i;
	char a = 55;
	
    for(i = 0;i < 2;i++){
        fp = fopen("file.txt","w");
        fclose(fp);    
                    
	    fp = fopen("file.txt","w");
	    fprintf(fp, "%c\n", a);
        a++;
	    
	    fclose(fp);
    }
	
	return 0;
}
