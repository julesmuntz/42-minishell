/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:29:49 by julmuntz          #+#    #+#             */
/*   Updated: 2022/09/29 17:46:43 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFFER_SIZE 100
# define TRUE 1
# define FALSE 0

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# include "../src/minishell.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t			ft_arrnbrlen(int *n);
size_t			ft_arrstrlen(char **s);
int				ft_atoi(char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_convert_base(int n, int base);
void			ft_free_lines(char **lines);
char			*get_next_line(int fd);
int				ft_hexlen(int n);
int				ft_hexlen_u(unsigned int n);
int				ft_hexlen_ul(unsigned long int n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_ischar(int c, int i);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isspace_null(int c);
char			*ft_itoa(int n);
size_t			ft_linelen(char *line);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*d)(void *));
void			ft_lstdelnode(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*d)(void *));
void			ft_lstdisplay(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));
t_list			*ft_lstnew(void *content);
void			*ft_lstpop(t_list **lst);
int				ft_lstsize(t_list *lst);
void			*ft_memchr(void *s, int c, size_t n);
int				ft_memcmp(void *s1, void *s2, size_t n);
void			*ft_memcpy(void *dst, void *src, size_t n);
void			*ft_memmove(void *dst, void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
int				ft_nbrcmp(int *array, int size);
int				*ft_nbrcpy(int *n1, int *n2);
int				ft_nbrlen(int n);
unsigned int	ft_nbrlen_u(unsigned int n);
int				ft_pow(int nbr, int pow);
int				ft_printf(const char *str, ...);
int				ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char *s);
void			ft_putendl_fd(char *s, int fd);
void			ft_puthex_u_lower(unsigned int n);
void			ft_puthex_u_upper(unsigned int n);
void			ft_puthex_ul(unsigned long int n);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr_u(unsigned int n);
void			ft_putstr(char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_puttab(char *s);
void			ft_puttabs(char *s, int nbr);
int				ft_scanf(char *fmt, ...);
int				*ft_sort_int_tab(int *tab, int size);
char			**ft_split(char *s, char c);
int				ft_sqrt(int nbr);
char			*ft_strcat(char *dest, char *src);
char			*ft_strchr(char *s, int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strcpy(char *s1, char *s2);
char			*ft_strdup(char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlcat(char *dst, char *src, size_t size);
size_t			ft_strlcpy(char *dst, char *src, size_t size);
size_t			ft_strlen(char *s);
char			*ft_strmapi(char *s, char (*f)(unsigned int, char));
int				ft_strncmp(char *s1, char *s2, size_t n);
size_t			ft_strnlen(char *str, size_t maxlen);
char			*ft_strnstr(char *full, char *part, size_t len);
char			*ft_strrchr(char *s, int c);
char			*ft_strrstr(char *full, char *part, size_t len);
char			*ft_strtrim(char *s1, char *set);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			ft_swap(char *a, char *b);
int				ft_tolower(int c);
int				ft_toupper(int c);

#endif