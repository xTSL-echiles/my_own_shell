# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eoddish <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 17:40:26 by eoddish           #+#    #+#              #
#    Updated: 2020/11/26 15:23:53 by eoddish          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_putnbr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_strdup.c ft_calloc.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strchr.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlcat.c ft_strlcpy.c ft_memcmp.c ft_memchr.c ft_toupper.c ft_tolower.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_strlen.c

OBJS		= $(SRCS:.c=.o)

BONUSOBJS	= $(BONUSSRCS:.c=.o)

NAME		= libft.a

CC			= gcc

RM			= rm -f

AR			= ar

CFLAGS		= -Wall -Wextra -Werror

$(NAME):	$(OBJS)
			$(AR) -rcs $@ $^

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(BONUSOBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all, clean, fclean, all

.SILENT:
