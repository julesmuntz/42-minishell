/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:21:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/06 11:59:53 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define TRUE 1
# define FALSE 0

# include "minishell.h"

size_t	ft_arrstrlen(char **s);
void	ft_free_lines(char **lines);
int		ft_isspace(int c);
int		ft_isspace_null(int c);
char	**ft_split(char *s, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strnstr(char *full, char *part, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
char	*ft_strdup(char *s);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_strtrim(char *s1, char *set);
int		ft_superatoi(char *nptr, int *res);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_count_chars(char *str, char c);
char	*ft_strcat(char *dest, char *src);
char	*ft_bigcat(char *s1, char *s2, char *s3, char *s4);
void	ft_sort_arrstr(char **s, int size);
char	*ft_strncpy(char *s1, const char *s2, unsigned int n);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
void	ft_strdel(char **s);
int		ft_nbrlen(int n);
int		ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_puterr(char *s);
int		ft_fprintf(const int fd, const char *str, ...);
void	*ft_realloc(void *ptr, size_t size);

#endif
