int efcount = 0;
int efvcount = 0;
void readeachline(char path[]){
     int fd = open(path, O_RDONLY);
     int l = lseek(fd, 0, SEEK_END);
     lseek(fd, 0, 0);        
	 close(fd);
	 
	 char *str, *str1;
	 str = (char*)malloc((l + 1) * sizeof(char));
     
	 FILE *fp = fopen(path, "r");
	 int i = 0, j = 0, found, numcount = 0, lastn = 0;
	 char line[1000], line1[1000];
	 while(1)
	 {
	 	str[i] = fgetc(fp);

	 	if(str[i] >= 'A' && str[i] <= 'Z' && search(a, 1))
	 		line[j] = str[i] + 32;
	 	else
	 	    line[j] = str[i];
		 line1[j] = str[i];
	 	
	 	if(str[i] == EOF)
	 	{
			line[j] = '\0';
			line1[j] = '\0';
			found = searchtrie(head, line);
			
			if(found  && !search(a, 6))
			{
				
				if(!search(a, 4))
				{
					if(search(a, 8))
					{
						//printf("\n%s ", path);
						printf("%s%s:%s ", KMAG, path, KNRM);						
					}
					if(search(a, 5))
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);
					printf("\n");
				}
				efcount++;
				numcount++;
	 		}
			 else if(!found && search(a, 6))
	 		{
				if(!search(a, 4))
				{
					if(search(a, 8) && str[i + 1] != '\0')
					{
						printf("%s%s:%s ", KMAG, path, KNRM);						
					}

					if(search(a, 5) && str[i + 1] != '\0')
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);	
				}
				efvcount++;
				numcount++;	
	 		}
			 break;
		}
		 	if(line[j] == '\n')
	 	{
	 		
			line[j] = '\0';
			line1[j] = '\0';
			found = searchtrie(head, line);
			if(found  && !search(a, 6))
			{
				if(!search(a, 4))
				{
					if(search(a, 8))
					{
							printf("%s%s:%s ", KMAG, path, KNRM);						
					}
					if(search(a, 5))
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);	
				}
				efcount++;
				numcount++;	
	 		}
			 else if(!found && search(a, 6))
	 		{	
	 			if(!search(a, 4))
				{
					if(search(a, 8))
					{
						printf("%s%s:%s ", KMAG, path, KNRM);							
					}

					if(search(a, 5))
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);	
				}
				efvcount++;
				numcount++;	
	 		}
			lastn = i + 1; 
			 j = -1;
			}
		 if(numcount == num)
		 	break;
		 
		 
		j++;
		i++;	
	  } 
	  if(search(a, 4) )	 
	  {
		if(search(a, 8))
			printf("%s%s:%s ", KMAG, path, KNRM);										
		 if(search(a, 6))
			printf("%d \n", efvcount - 1);
		else
			printf("%d \n", efcount);
	  }
}
void makeitline(char str[], int index){
	int l = strlen(str), i, j;
	i = index;
	char line[1000];
	while(str[i] != '\n' && i != 0){
		i--;
	}
	if(i != 0){
		i++;
	}
	j = 0;
	while(i < l && str[i] != '\n')
	{
		line[j] = str[i];
		i++; j++;
	}
	line[j] = '\0';
	if(!searchtrie(head, line))
		insert(&head, line);
}