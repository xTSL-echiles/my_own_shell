# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eoddish <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 17:40:26 by eoddish           #+#    #+#              #
#    Updated: 2021/07/03 18:42:56 by eoddish          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS		=  engine/execve.c engine/main.c engine/pipes.c engine/read_term.c\
			   engine/utils.c engine/utils2.c engine/utils3.c\
			   parser/buildin.c parser/ft_add_pipe.c parser/ft_call.c \
			   parser/ft_check_here.c parser/ft_check_pipe.c parser/ft_env.c\
			   parser/ft_export.c parser/ft_here_redir.c parser/ft_parse_arg.c\
			   parser/ft_parse_env.c parser/ft_parse_in.c parser/ft_parse_out.c\
			   parser/ft_parse_pipe.c parser/ft_parse_quotes.c parser/ft_parser.c\
			   parser/ft_unset.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

#RED_FLAGS		= -I/Users/eoddish/.brew/Cellar/readline/8.1/include\
			  -L/Users/eoddish/.brew/Cellar/readline/8.1/lib\
			  -lreadline 
RECH_FLAGS		= -I/Users/echiles/.brew/opt/readline/include\
				-L/Users/echiles/.brew/opt/readline/lib\
				-lreadline
%.o: %.c	
			$(CC) $(CFLAGS) -c $< -o $@

RM			= rm -f

LIBFT		= libft

LIBFT_NAME	= libft.a

MAKE		= make -C

$(NAME):	$(OBJS)
			$(MAKE) $(LIBFT)
			$(CC) $(CFLAGS) -I/includes/minishell.h $(OBJS) $(RECH_FLAGS) libft/libft.a -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(LIBFT)/$(LIBFT_NAME) $(LIBFT)/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all, clean, fclean, re

.SILENT:
