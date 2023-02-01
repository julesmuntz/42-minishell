# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 17:17:08 by julmuntz          #+#    #+#              #
#    Updated: 2023/01/29 22:07:59 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	srcs/
SRC 		=	main.c					\
				history.c				\
				$(addprefix parsing/,	\
				env.c					\
				tok_utils.c				\
				lst_utils.c				\
				tab_utils.c				\
				parse.c					\
				parse2.c				\
				)						\
				$(addprefix builtins/,	\
				get_cmd.c				\
				check_input.c			\
				cmd_echo.c				\
				cmd_pwd.c				\
				cmd_env.c				\
				)						\
				$(addprefix libft/,		\
				ft_strcmp.c				\
				ft_strlcpy.c			\
				ft_strdup.c				\
				ft_strtrim.c			\
				ft_superatoi.c			\
				ft_strjoin.c			\
				ft_arrlen.c				\
				ft_free_lines.c			\
				ft_isspace.c			\
				ft_split.c				\
				ft_strchr.c				\
				ft_strnstr.c			\
				ft_substr.c				\
				ft_calloc.c				\
				ft_bzero.c				\
				ft_strlen.c				\
				)

OBJ_DIR		=	obj/
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC			=	cc
CFLAGS		=	-Iincludes -Wall -Wextra -Werror -g
RM			=	rm -f

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

all:			$(NAME)

clean:
					$(RM) -r $(OBJ_DIR)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
