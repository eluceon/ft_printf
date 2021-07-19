# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/28 13:07:42 by eluceon           #+#    #+#              #
#    Updated: 2020/12/11 11:11:07 by eluceon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

B&W = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT = libft.a
LIBFTDIR = ./libft/
LIBFTHEADER = libft.h
LIBFTHEADERDIR = ./libft/includes/

NAME = libftprintf.a
HEADER = libftprintf.h
HEADERDIR = ./includes/

SRCS = ft_printf.c ft_check_string.c ft_type_d.c ft_type_u.c ft_type_c.c \
		ft_type_s.c ft_type_x.c ft_type_p.c ft_type_percent.c \
		ft_type_n.c ft_printf_utils.c

SRCDIR = ./srcs/

OBJS = $(SRCS:.c=.o)
OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR)
	cp $(LIBFTDIR)$(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)
	@echo "$(PURPLE) Library $(NAME) has been created $(B&W)"

-include $(DEP)


$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -MMD -c $< -o $@ $(CFLAGS)
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) has been created $(B&W)"


clean:
	$(MAKE)	clean -C $(LIBFTDIR)
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE)	fclean -C $(LIBFTDIR)
	$(RM) $(NAME)
	@echo "$(RED) Library $(NAME) has beeb deleted $(B&W)"

re:	fclean all

.PHONY: all bonus clean fclean re
