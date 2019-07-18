#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <dirent.h>
/*
Note
I have declared many global variables across many files, hence I we can't really use a .h file here
*/ 
#include "globals.c"	
#include "choose.c"
#include "priority.c"
#include "trie.c"
#include "foref.c"
#include "dot.c"
#include "brackets.c"
#include "reg.c"
#include "kmp.c"	
#include "rec_files.c"	
#include "help.c"
int main(int argc, char *argv[]){
	if(argc == 1)
	{
		printf("use ./try --help for help \n");
		return 2;
	}
	if(!strcmp(argv[1], "--help"))
	{
		showhelp();
		return 0;
	}
	if(argc < 3)
	{
		printf("\n bad arguements \n");
		return 130;
	}
	char files[10][20], options[10][3];	
	int i, count_file = 0, count_word = 0;
	strcpy(word[0], " ");
	strcpy(word[1], " ");
	
	for(i = 1; i < argc; i++){
		if(isword(argv[i]))
			strcpy(word[count_word++], argv[i]);
		if(isoption(argv[i]))
			strcpy(options[count_option++], argv[i]);
		if(isfile(argv[i]))
			strcpy(files[count_file++], argv[i]);
	}
	
	a = decide_priority(options, count_option);	

	head = getNewTrieNode();
	
	if(isreg(argv[1]))
	{
		int dotc = 0;
		for(i = 0; i < strlen(argv[1]); i++)
		{
			if(argv[1][i] == '.')
				dotc++;
		}
		if(dotc >= 2)
		{
			strcpy(files[0], files[1]);
		}
		reg(argv[1], files[0]);                            //everthing about reg
		return 0;
	}



	if(num != INT_MAX && !(search(a, 9))){
		printf("%d in command without using -m", num);
		exit(0);
	}

	if(count_file == 0 && search(a, 10))
	{
		return 2;
	}

	FILE *fp;
	fp = fopen("temp.txt", "w");
	
	if(search(a, 12) || search(a, 11))
	{	
		ef = 1;
	}
	if(search(a, 12) && !search(a, 11)){
		for(i = 1; i < argc; i++){
			if(!strcmp(argv[i], "-e") && (isword(argv[i + 1]) || ( (strlen(argv[i + 1]) > 2) && argv[i][0] == '-' ) )   ){
				kmp(argv[i + 1], files[0]);
			}
		}
		readeachline(files[0]);
	}
	if(search(a, 12)){
		for(i = 1; i < argc; i++){
			if(!strcmp(argv[i], "-e") && (isword(argv[i + 1]) || ( (strlen(argv[i + 1]) > 2) && argv[i][0] == '-' ) )   ){
				fputs(argv[i + 1], fp);
				fputc('\n', fp);
			}
		}
	}
	
	char str[100];
	if(search(a, 11)){
		 FILE *fp1 = fopen(files[0], "r");	
		if(!fp1)
		{
			printf("File not found \n");
			exit(0);
		}
		while(fgets(str, 100, fp1)){
			fputs(str, fp);
		}
	}	
	fclose(fp);

	if(search(a, 11) || search(a, 12))
	{
		if(count_file == 1 && search(a, 11))
		{
			printf("\n Bad arguements only one file specified \n");
			exit(0);
		}
		 fp = fopen("temp.txt", "r");
		 while(fgets(str, 100, fp)){
			str[strlen(str) - 2] = '\0';
			kmp(str, files[1]);	 	
		 }
	}
	
	if((search(a, 11) && search(a, 12)) || search(a, 11)) {
		readeachline(files[1]);
		exit(0);
	}

	if(!strcmp(word[1], " ")){
		for(i = 0; i < count_file; i++)
			kmp(word[0], files[i]);
	}
	
	if(!strcmp(word[1], " "))
		strcpy(word[1], word[0]);
	
	if(a[0] == 0){
		rec(word[1]);
	}
	fclose(fp);
	remove("temp.txt");
	
	if(nofile && search(a, 10))
	{
		return 2;
	}

	if(search(a, 10))
	{
		return 1;
	}
	return 0;
}
