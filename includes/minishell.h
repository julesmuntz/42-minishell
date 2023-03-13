/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:19:09 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/13 14:14:04 by julmuntz         ###   ########.fr       */
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
# include <errno.h>
# include <sys/stat.h>
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
	int				called;
	char			*cmd;
	char			**arg;
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

typedef struct s_garbge
{
	void			*ptr;
	struct s_garbge	*next;
}					t_garbage;

typedef struct s_data
{
	t_lst			*l;
	char			*tmp;
	char			*user;
	char			**env;
	int				env_size;
	char			*prompt;
	t_export		*x;
	t_garbage		*g;
	int				pipefd[2];
	int				pipe;
	int				in;
	int				out;
	int				heredoc;
}					t_data;

extern int	g_exit_code;

//					PARSING
int					parsing(t_data *d, char *str);
int					init_list(t_data *d, t_tok *t);
int					new_tok(t_tok **t, char *str, int j);
void				free_tok(t_tok *t);
int					ft_tok_size(t_tok *t);
void				tok_extract(t_tok **t, t_tok **dest, t_tok *elem);
void				ft_free_tab(char **tab);
void				ft_lst_add_back(t_lst **l, t_lst *new);
t_lst				*ft_lst_free(t_lst *l);
int					init_arg(t_lst *new, t_tok *t);
int					init_redir(t_redir **tab, t_tok *t);
int					redirect(t_data *d, t_lst *l);
void				ft_free_redir(t_redir *ptr);
char				*expand_vars(t_data *d, char *str);
int					parse_quotes(char *str);
int					ft_tok_join(t_tok *t, char **str);
int					remove_quotes(char *s, char **str);

//					EXECUTION
int					exe_cmd(t_data *d);
void				child(t_data *d, t_lst *l);
void				exec_error(char *str, char **arg, t_data *d);
int					find_cmd(char **str, char **env);
int					check_builtins(char *str);
int					execute_builtin(t_data *d, t_lst *l);
int					refresh_prompt(t_data *d);
void				handle_ctrls(int sig);
void				free_stuff(t_data *d);
void				child_exit_error(char *s, char **arg, t_data *d, int error);
void				exit_shell(t_data *d, int code);

//					BUILTINS
int					cmd_echo(t_data *d, t_lst *l);
int					cmd_cd(t_data *d, t_lst *l);
int					cmd_pwd(t_data *d);
int					cmd_exit(t_data *d);
int					var_cmd(t_data *d, t_lst *l);

//					ENVIRONMENT
char				**init_env(char **env, t_data *d);
t_export			*init_export(t_data *d);
void				copy_export(t_export *src, t_export **dst, t_data *d);
void				sort_export(t_export **node);
int					get_var(t_data *d, char *arg, int *plus);
int					create_var(t_export *current, t_data *d, int found);
int					update_var(t_export *curr, t_data *d, char *arg, int *plus);
char				**update_env(t_data *d);
char				*ft_getenv(char *key, t_data *d);
int					ft_setenv(char *key, char *value, t_data *d);

//					GC
void				*galloc(void *ptr, size_t size, t_data *d);
void				free_garbage(t_garbage **g);

#endif
