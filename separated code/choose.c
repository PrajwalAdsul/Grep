int num = INT_MAX;
int search(int *a, int s){
	int i;
	for(i = 0; i < count_option; i++){
		if(a[i] == s){
			return 1;
		}
	}
	return 0;
}
int isnumber(char str[]){
	int i = 0;
	if(str[i] == '0')
	{
		printf("\n bad number \n");
		exit(0);
	}
	while(i < strlen(str)){
		if(str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	num = atoi(str);
	return 1;
}
int isword(char str[]){
	if(str[0] == '-')
		return 0;
	if(isnumber(str)){
		return 0;
	}
	int i = 0;
	while(i < strlen(str)){
		if(str[i] == '.')
			return 0;
		i++;
	}	
	return 1;
}
int isoption(char str[]){
	if(strlen(str) == 2 && str[0] == '-')
		return 1;
	return 0;
}
int isfile(char str[]){
		int i = 0;
	while(i < strlen(str)){
		if(str[i] == '.')
			return 1;
		i++;
	}	
	return 0;	
}
int isreg(char str[])
{
	int l = strlen(str);
	int i;
	for(i = 0; i < l; i++)
	{
		if(str[i] == '$' || str[i] == '^' || str[i] == '.' || str[i] =='[' || str[i] == ':')
			return 1;
	}
	return 0;
}
