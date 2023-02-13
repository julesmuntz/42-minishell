/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:19:09 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/13 15:55:21 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define COLOR_A "\1\033[38;5;220m\2"
# define COLOR_B "\1\033[38;5;221m\2"
# define COLOR_C "\1\033[38;5;222m\2"
# define COLOR_D "\1\033[38;5;223m\2"
# define COLOR_E "\1\033[0m\2"
# define PROMPT "@minishell:"
# define CUSTOM 10
# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"

typedef struct s_tok
{
	char			*str;
	struct s_tok	*next;
}					t_tok;

typedef struct s_redir
{
	char			*str;
	int				type;
}					t_redir;

typedef struct s_lst
{
	int				pid;
	char			*cmd;
	char			**arg;
	char			**arg_d;
	t_redir			*infile;
	t_redir			*outfile;
	struct s_lst	*next;
}					t_lst;

typedef struct s_export
{
	char			*key;
	char			*value;
	char			*new_key;
	char			*new_value;
	struct s_export	*next;
}					t_export;

typedef struct s_data
{
	t_lst			*l;
	char			*tmp;
	char			**env;
	char			*prompt;
	t_export		*x;
}					t_data;

char				**free_tab(char **tab, int i);
void				ft_free_redir(t_redir *ptr);
char				**init_env(char **env);
int					parsing(t_data *d, char *str);
int					init_list(t_data *d, t_tok *t);
int					new_tok(t_tok **t, char *str, int j);
void				free_tok(t_tok *t);
int					ft_tok_size(t_tok *t);
void				tok_extract(t_tok **t, t_tok **dest, t_tok *elem);
void				ft_free_tab(char **tab);
void				exit_shell(t_data *d, int code);
void				ft_lst_add_back(t_lst **l, t_lst *new);
t_lst				*ft_lst_free(t_lst *l);
void				print_tab(char **tab);		//temp
int					ft_history(t_data *d, char **str);
int					init_arg(t_lst *new, t_tok *t);
void				print_redir(t_redir *tab);	//temp
int					init_redir(t_redir **tab, t_tok *t);
char				*expand_vars(t_data *d, char *str);
int					parse_quotes(char *str);
int					ft_tok_join(t_tok *t, char **str);
int					remove_quotes(char *s, char **str);

int					exe_cmd(t_data *d);
int					find_cmd(char **str, char **env);
int					check_builtins(char *str);
int					execute_builtin(t_data *d, t_lst *l);

void				cmd_echo(t_lst *l);
int					cmd_cd(t_data *d, t_lst *l);
int					cmd_pwd(void);
int					cmd_export(t_data *d, t_lst *l);
void				cmd_env(t_data *d, t_lst *l);
void				cmd_exit(t_data *d);
int					refresh_prompt(t_data *d);
char				*find_dir(char *str, char **env);
void				handle_ctrl_c(int sig);
void				sort_export(t_export *node);
t_export			*create_export_list(char **env);
t_export			*free_export(t_export *node);

#endif
