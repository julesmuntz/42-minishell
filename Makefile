# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 17:17:08 by julmuntz          #+#    #+#              #
#    Updated: 2023/03/13 15:46:11 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	srcs/
SRC 		=	main.c					\
				main2.c					\
				$(addprefix parsing/,	\
				env.c					\
				tok_utils.c				\
				lst_utils.c				\
				tab_utils.c				\
				parse.c					\
				parse2.c				\
				init_arg.c				\
				init_redir.c			\
				expand.c				\
				expand2.c				\
				ft_tok_join.c			\
				remove_quotes.c			\
				)						\
				$(addprefix exec/,		\
				execute.c				\
				check_builtin.c			\
				search_path.c			\
				redirect.c				\
				child.c					\
				handle_errors.c			\
				)						\
				$(addprefix builtins/,	\
				cmd_echo.c				\
				cmd_pwd.c				\
				cmd_cd.c				\
				cmd_exit.c				\
				var_utils.c				\
				var_cmd.c				\
				env_utils.c				\
				export_utils.c			\
				)						\
				$(addprefix libft/,		\
				ft_strcmp.c				\
				ft_strcpy.c				\
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
				ft_putstr.c				\
				ft_count_chars.c		\
				ft_bigcat.c				\
				ft_strcat.c				\
				ft_sort_array.c			\
				ft_strdel.c				\
				ft_fprintf.c			\
				ft_realloc.c			\
				ft_itoa.c				\
				ft_str_is.c				\
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
					@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

all:			$(NAME)

clean:
					$(RM) -r $(OBJ_DIR)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
