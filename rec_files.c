void listFilesRecursively(char *path);
void rec(char path[])
{
    listFilesRecursively(path);
}
void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
	
	if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
			if(isfile(path))
			{
				kmp(word[0], path);
			}		
            listFilesRecursively(path);
        }
    }
    closedir(dir);
}
