/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/01 00:19:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# define CUSTOM 10

# include "minishell.h"

typedef struct s_builtins
{
	char	**cmd;
	char	*cmd_path;
	char	*cmd_to_execute;
}			t_builtins;

char		*find_cmd(char *cmd, char **env, t_builtins *data);
void		get_cmd(char *str, char **env);
int			valid_input(char **env, t_builtins *data);
int			execute_builtin(char **env, t_builtins *data);
int			cmd_echo(t_builtins *data);
int			cmd_pwd(void);
int			cmd_env(char **env);

#endif