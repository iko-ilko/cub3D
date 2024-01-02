#include <stdio.h>
char	**ft_split(char *s, char *sepa);

int main()
{
	
	char **temp = ft_split(NULL, ", .a");
	if (temp == NULL)
		printf("NULL\n");

	for(int i = 0; temp[i] != NULL; i++)
		printf("%s\n", temp[i]);	
}