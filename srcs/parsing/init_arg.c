#include "minishell.h"

static int	init_arg2(t_lst *new, t_tok *t, int size)
{
	int		i;
	t_tok	*tmp;

	i = 0;
	tmp = t;
	while (i < size)
	{
		new->arg[i] = ft_strdup(tmp->str);
		if (!new->arg[i])
			return (1);
		tmp = tmp->next;
		i++;
	}
	new->arg[i] = NULL;
	return (0);
}

int	init_arg(t_lst *new, t_tok *t)
{
	int		size;

	if (t)
	{
		new->cmd = ft_strdup(t->str);
		if (!new->cmd)
			return (free_tok(t), 1);
		size = ft_tok_size(t);
		new->arg = malloc((size + 1) * sizeof(char *));
		if (!new->arg)
			return (free(new->cmd), free_tok(t), 1);
		if (init_arg2(new, t, size))
			return (free(new->cmd), free_tok(t), \
			ft_free_tab((new->arg)), 1);
	}
	return (free_tok(t), 0);
}
