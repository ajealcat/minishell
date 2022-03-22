# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 14:18:00 by ajearuth          #+#    #+#              #
#    Updated: 2022/03/22 12:03:41 by ajearuth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

# Project sources and objs 

SRCS = main.c \
		prompt.c \
		parse.c \
		init.c \
		protection_quote.c \
		token_list.c \
		is_it_available.c \
		token_others.c \
		utils.c \
		free.c \
		token_quote.c \
	
SRCSD = srcs/
OBJSD = objs/
OBJS = $(addprefix $(OBJSD), $(SRCS:.c=.o))

 # Libft sources and objs 

 LIBSD = libs/
 LIBFTD = $(addprefix $(LIBSD), libft/)
 LIBFT = $(addprefix $(LIBFTD), libft.a)

 LIBS = $(LIBFT)
 LIBS_MAKE = make -C
 CC = clang -c -o
 COMPIL = clang
 FLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(COMPIL) -lreadline $(FLAGS) $(OBJS) $(LIBS) -o $@
	@echo "\033[0;32m\n          _         "
	@echo "   ______/ \-.   _  "
	@echo ".-/     (    o\_//    *~o~o~* OK *~o~o~* "
	@echo " |  ___  \_/\---'   "
	@echo "  |_||  |_||        "
	@echo "\033[0;35m                     Bonne correction !"


$(OBJSD)%.o: $(SRCSD)%.c
	mkdir -p $(OBJSD)
	$(CC) $@ $(FLAGS) -I $(LIBFTD) $<

 $(LIBS):
	$(LIBS_MAKE) $(LIBFTD) all 

clean:
	rm -rf $(OBJSD)
	$(LIBS_MAKE) $(LIBFTD) clean

fclean:	clean
	rm -rf $(NAME)
	$(LIBS_MAKE) $(LIBFTD) fclean

re: fclean all 

.PHONY: all bonus clean fclean re
