#include <stdio.h>
char	**my_split(char *s, char *sepa);

int main()
{
	
	char **temp = my_split(NULL, ", .a");
	if (temp == NULL)
		printf("NULL\n");

	for(int i = 0; temp[i] != NULL; i++)
		printf("%s\n", temp[i]);	
}