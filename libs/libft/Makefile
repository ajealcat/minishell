# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 11:00:12 by ajearuth          #+#    #+#              #
#    Updated: 2021/12/29 17:09:05 by ajearuth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRCS := ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strlen.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_atoi.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_strdup.c ft_calloc.c ft_strjoin.c ft_substr.c ft_itoa.c ft_strtrim.c ft_split.c ft_strmapi.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr_base_fd.c ft_atoi_base.c 

bonus := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	ft_lstiter.c ft_lstmap.c 

OBJS := $(SRCS:.c=.o)
OBJSBONUS := $(bonus:.c=.o)
CC := gcc -c -o
LINKER := ar rcs 
FLAGS := -Wall -Wextra -Werror

$(NAME):	$(OBJS)
	$(LINKER) $(NAME) $(OBJS)

all:	$(NAME)

bonus:	$(OBJSBONUS) $(OBJS)
	$(LINKER) $(NAME) $(OBJSBONUS) $(OBJS)

$(OBJSD)%.o:    $(SRCSD)%.c
	$(CC) $@ $^ $(FLAGS) 

clean:
	rm -rf $(OBJS) $(OBJSBONUS)

fclean:    clean
	rm -f $(NAME) 

re:		fclean all

.PHONY:		all clean fclean re
