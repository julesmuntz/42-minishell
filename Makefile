# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 17:17:08 by julmuntz          #+#    #+#              #
#    Updated: 2023/01/29 18:39:55 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR		= 	src/
SRC			=	main.c						\
				check_input.c				\
				cmd_echo.c					\
				cmd_pwd.c					\
				cmd_env.c					\

OBJDIR		= 	obj/
OBJ			= 	$(addprefix $(OBJDIR), $(SRC:.c=.o))

NAME		= 	minishell
LIBFT		=	./libft

CC			= 	cc
RM			= 	rm -f
CFLAGS		= 	-Wall -Wextra -Werror -g

$(OBJDIR)%.o:	$(SRCDIR)%.c
					@mkdir -p $(OBJDIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ) libft/libft.a
					@$(CC) -g $^ -o $@

all:			$(NAME)

libft/libft.a:
					@$(MAKE) -j 500 --no-print-directory -C $(LIBFT) libft.a

clean:
					$(RM) -r $(OBJDIR)
					$(RM) -r libft/obj/

fclean:			clean
					$(RM) $(NAME)
					$(RM) $(B_NAME)
					$(RM) libft/libft.a

re:				fclean all

.PHONY:			all clean fclean re