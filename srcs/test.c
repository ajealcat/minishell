#include <stdio.h>
#include <stdlib.h>

void	free_list(dblist **list) //double ** car la fontction doit directement effectuer
{								//des modifications sur les objets de la liste
	t_token	*tmp;
	t_token	*del;
	
	if (*list != NULL)
	{
		tmp = (*list)->head;
		while (tmp != NULL)
		{
			del = tmp;
			tmp = tmp->next;
			free(del);
		}
		free(*list);
		(*list) = NULL;
	}
}

int add_list(t_token *node)
{
//	dblist	*list;

//	list = NULL;
    if (list->tail == NULL)
    {
        node->prev = NULL;
		list->head = node;
		list->tail = node;
    }
    else
    {
		list->tail->next = node; //on relie le dernier element de la liste vers le nouvel element
		node->prev = list->tail; //on fait pointer prev vers le dernier element de la liste
		list->tail = node; //on fait pointer la fin de la liste vers le nouvel element
    }
    return (SUCCESS);
}

t_token create_node(char *str, int category)
{
    t_token	*new_node;

	printf("create node\n");
    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return (0);
    new_node->type = category;
    new_node->value = str;
    new_node->next = NULL;
	printf("create node before add_list?\n");
 //   add_list(new_node);
    return (new_node);
}

int main()
{
   
    char str[] = "echo plop";
   
    token_word(str);
    return(0);

}