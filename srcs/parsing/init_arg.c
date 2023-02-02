#include "minishell.h"

int	init_arg(t_lst *new, t_tok *t)
{
	int		size;
	int		i;
	t_tok	*tmp;

	if (t)
	{
		new->cmd = ft_strdup(t->str);
		if (!new->cmd)
			return (free_tok(t), 1);
		size = ft_tok_size(t);
		new->arg = malloc((size + 1) * sizeof(char *));
		if (!new->arg)
			return (free(new->cmd), free_tok(t), 1);
		i = 0;
		tmp = t;
		while (i < size)
		{
			new->arg[i] = ft_strdup(tmp->str);
			if (!new->arg[i])
				return (free(new->cmd), free_tok(t), ft_free_tab((new->arg)), 1);
			tmp = tmp->next;
			i++;
		}
		new->arg[i] = NULL;
	}
//	print_tab(new->arg);
	return (free_tok(t), 0);
}
