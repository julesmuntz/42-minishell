/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/28 11:35:36 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CUSTOM 10

# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_lst
{
	char			*cmd;
	char			**arg;
	char			*infile;
	char			*outfile;
	char			**limiter;
	int				append;
	struct s_lst	*next;
}					t_lst;

typedef struct s_data
{
	t_lst			*p;
	char			**env;
}					t_data;

typedef struct s_testing
{
	char			**env;
	char			**cmd;
	char			**arg;
	char			**paths;
	char			*cmd_to_execute;
	int				nbr_arg;
}	t_testing;

/////////////  B  U  I  L  T  I  N  S  ////////////////////////////////////////
int	cmd_echo(t_testing *data);

#endif