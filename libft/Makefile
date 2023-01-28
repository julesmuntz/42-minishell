# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 17:50:33 by julmuntz          #+#    #+#              #
#    Updated: 2022/06/02 17:26:40 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	ft_atoi.c					\
    			ft_bzero.c					\
    			ft_calloc.c					\
    			ft_convert_base.c			\
    			ft_free_lines.c				\
				get_next_line.c				\
    			ft_hexlen.c					\
    			ft_isalnum.c				\
    			ft_isalpha.c				\
    			ft_isascii.c				\
    			ft_ischar.c					\
    			ft_isdigit.c				\
    			ft_isprint.c				\
    			ft_itoa.c   				\
				ft_linelen.c				\
				ft_lstadd_back.c			\
				ft_lstadd_front.c			\
				ft_lstclear.c				\
				ft_lstdelone.c				\
				ft_lstdisplay.c				\
				ft_lstiter.c				\
				ft_lstlast.c				\
				ft_lstmap.c					\
				ft_lstnew.c					\
				ft_lstpop.c					\
				ft_lstsize.c				\
    			ft_memchr.c 				\
    			ft_memcmp.c 				\
    			ft_memcpy.c 				\
    			ft_memmove.c				\
    			ft_memset.c 				\
    			ft_nbrcmp.c 				\
    			ft_nbrcpy.c 				\
    			ft_nbrlen.c 				\
				ft_pow.c					\
				ft_printf.c					\
    			ft_putchar.c				\
    			ft_putendl.c				\
    			ft_puthex.c					\
    			ft_putnbr.c					\
    			ft_putstr.c					\
    			ft_puttab.c					\
    			ft_split.c					\
    			ft_sqrt.c					\
    			ft_scanf.c					\
    			ft_sort_int_tab.c			\
    			ft_strcat.c					\
    			ft_strchr.c					\
    			ft_strcmp.c					\
    			ft_strcpy.c					\
    			ft_strdup.c					\
    			ft_striteri.c				\
    			ft_strjoin.c				\
    			ft_strlen.c					\
    			ft_strmapi.c				\
    			ft_strnstr.c				\
    			ft_strtrim.c				\
    			ft_substr.c					\
    			ft_swap.c					\
    			ft_tolower.c				\
    			ft_toupper.c				\
				$(addprefix ft_printf/,		\
				convert_char.c				\
				convert_decimal.c			\
				convert_hex_lower.c			\
				convert_hex_pointer.c		\
				convert_hex_upper.c			\
				convert_integer.c			\
				convert_string.c			\
				convert_unsigned.c			\
				)

OBJDIR		= 	obj/

OBJ			= 	$(addprefix $(OBJDIR), $(SRC:.c=.o))

NAME		= 	libft.a

CC			= 	cc
RM			= 	rm -f
CFLAGS		= 	-Wall -Wextra -Werror -g

$(OBJDIR)%.o:	%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
					@ar rcs $@ $^

all:			$(NAME)

clean:
					$(RM) -r $(OBJDIR)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re