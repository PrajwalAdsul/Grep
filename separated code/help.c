void showhelp(){
	printf("%s", KRED);
	printf("  Usage: grep [OPTION]... PATTERN [FILE]... \n  Search for PATTERN in each FILE.\n  Example: grep -i 'hello world'  main.c \n");
	printf("%s", KGRN);
	printf("  -r       traverse through directories nd grep\n");
	printf("  -w       force PATTERN to match only whole words\n");
	printf("  -m[NUM]  stop after NUM matches\n");
	printf("  -q       returns a value so that grep can be used by other programs\n");
	printf("  -i       ignore case distinctions\n");
	printf("  -v       select non-matching lines\n");
	printf("  -n       print line number with output lines\n");
	printf("  -c       print only a count of matching lines per FILE\n");
	printf("  -b       print the byte offset with output lines\n");
	printf("  -f       search pattern from file\n");
	printf("  -e       to match word starting with non-alphabet character or for searching multiple patterns\n");
	printf("  -h       suppress the file name prefix on output\n");
	printf("  -H       print the file name for each match\n");
	printf("%s", KYEL);
	printf("  for regular expressions\n");		
	printf("  ^word    grep only those lines whose starting word is word\n");
	printf("  word$    grep only those lines whose ending word is word\n");
	printf("  w.r.     . can hold any values\n");
	printf("  [abc][cd]s    choose between characters in brackets and grep\n");
	printf("%s  Can use any combinations of above commands \n %s eg:- ./project word -v -i -w -c file.txt\n", KCYN, KGRN);
}
