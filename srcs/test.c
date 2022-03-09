#include <stdio.h>
#include <stdlib.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int ft_strlen_space(char *str)
{
    int i;

     i = 0;

     while(str[i] != ' ')
        ++i;
    return(i);
}

int token_word(char *str)
{
	int j;
    int i = 0;
    int size;
	char *tmp;

    size = ft_strlen_space(str);
    tmp = malloc(sizeof(char) * size + 1);
	
	j = 0;
    
	while (ft_isalpha(str[i]) == 1)
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	printf("tmp = %s\n", tmp);
	//create_node(tmp, word, token); 
    return (0);
}

int main()
{
   
    char str[] = "echo plop";
   
    token_word(str);
    return(0);

}