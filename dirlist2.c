#include <stdio.h>
#include <dirent.h>

long int findsize(char files[])
{
	FILE* fp = fopen(files, "r");
	if (fp == NULL) 
	{
		printf("nee\n");
		return -1;
	}
	fseek(fp, 0L, SEEK_END);
	long int res = ftell(fp);
	fclose(fp);

	return res;
}

main(void)
{
	struct dirent *files;
	DIR *dir = opendir(".");
	if (dir == NULL)
	{
		printf("haha stuk");
		return 0;
	}
	
	while((files = readdir(dir)) != NULL)
		printf("%s\n", files->d_name);
	
	long int res = findsize(files);
	if(res != -1)
		printf("%ld\n", res);
	return 0;
	closedir(dir);
}

