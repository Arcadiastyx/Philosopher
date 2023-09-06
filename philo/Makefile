# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 15:53:11 by inaranjo          #+#    #+#              #
#    Updated: 2023/08/31 16:39:52 by inaranjo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c\
		ft_00_input_pars.c\
		ft_01_init_all.c\
		ft_02_philo_routine.c\
		ft_03_maitre_dhotel.c\
		ft_time_request.c\
		ft_utils.c\

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all : subsystems $(NAME)

%.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -g -c $< -o ${<:.c=.o}
	@printf $(UP)$(CUT)

subsystems :
	@echo $(B)

$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(SRC)]...$(X)
	@echo $(G)Finished [$(SRC)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@rm -f $(OBJ)
	@echo $(R)Removed [$(OBJ)]$(X)


fclean: clean
	@rm -f $(NAME)
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

.PHONY: all clean fclean re