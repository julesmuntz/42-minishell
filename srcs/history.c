#include "minishell.h"

int	ft_history(t_data *d, char **str)
{
	char	*s;

	s = ft_strtrim(*str, " ");
	free(*str);
	if (!s)
		return (1);
	*str = s;
	if (!d->tmp || (d->tmp && ft_strcmp(s, d->tmp) && s[0]))
		add_history(s);
	free(d->tmp);
	d->tmp = ft_strdup(s);
	if (!d->tmp)
		return (free(s), 1);
	return (0);
}
