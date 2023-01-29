/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/29 22:08:46 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CUSTOM 10

# include "../libft/libft.h"

typedef struct s_builtins
{
	char			**cmd;
	char			*cmd_to_execute;
}	t_builtins;

/////////////  B  U  I  L  T  I  N  S  ////////////////////////////////////////
int		get_cmd(int arc, char **arv, char **env);
int		valid_input(char **env, t_builtins *data);
int		execute_builtin(char **env, t_builtins *data);
int		cmd_echo(t_builtins *data);
int		cmd_pwd(void);
int		cmd_env(char **env);

#endif