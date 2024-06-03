# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 18:11:04 by mbuchs            #+#    #+#              #
#    Updated: 2023/11/03 18:11:04 by mbuchs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
COMP = gcc
CFLAGS = -Wall -Werror -Wextra

LIB = ft_strlen.c\
	ft_atoi.c\
	ft_strdup.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strncmp.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isprint.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_memset.c\
	ft_strnstr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\

ADDITIONAL = get_next_line.c\

BONUS =	ft_lstadd_back.c\
	ft_lstadd_front.c\
	ft_lstlast.c\
	ft_lstnew.c\
	ft_lstsize.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstmap.c\

SRC = $(LIB) $(ADDITIONAL)
SRCS = $(LIB) $(ADDITIONAL) $(BONUS)

OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(COMP) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus : $(OBJBONUS)
	ar -rcs $(NAME) $(OBJBONUS)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJBONUS)

clean :
	rm -f $(OBJBONUS)

fclean : clean
	rm -f $(NAME)
	rm -f libft.so

re : fclean all

.PHONY: all fclean clean re bonus so
