/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/29 16:00:44 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CUSTOM 10

# include "../libft/libft.h"

typedef struct s_builtins
{
	char			**env;
	char			**cmd;
	char			**arg;
	char			**paths;
	char			*cmd_to_execute;
}	t_builtins;

/////////////  B  U  I  L  T  I  N  S  ////////////////////////////////////////
int		valid_input(t_builtins *data);
int		execute_builtin(t_builtins *data);
int		cmd_echo(t_builtins *data);
int		cmd_pwd(void);

#endif