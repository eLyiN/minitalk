# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 12:36:39 by aarribas          #+#    #+#              #
#    Updated: 2022/05/28 12:36:42 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= talk.a

SRCS= server.c client.c

OBJ= $(SRCS:.c=.o)

$(NAME): $(OBJ)
	@echo "\033[36m"--Compilando--"\033[0m ";
	@make -C libft/
	@cp libft/libft.a .
	@ar rcs $(NAME) $(OBJ)
	@clear

all: $(NAME)

re: fclean all

clean:
	@rm -rf $(NAME) $(OBJ) a.out server client
	@make -C ./libft fclean
	@clear
	@echo "\033[34m"🗑️\  Todo depurado correctamente  \🗑️"\033[0m"

fclean: clean
		@rm -rf ./libft.a talk.a

.PHONY: all clean re fclean