# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 10:45:26 by ahaarij           #+#    #+#              #
#    Updated: 2024/05/01 13:47:10 by ahaarij          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -pthread
# CFLAGS += -g3 -fsanitize=address
RM = rm -rf
SRCS = 	real.c \
		start_the_race.c \
		handy_man.c \
		sewing.c \
		doctors_appointment.c \
		daily_routine.c \
		bob_the_builder.c \

SRC = $(addprefix ./srcs/,$(SRCS))
OBJ = $(SRC:.c=.o)
GREY		= $'\x1b[30m
RED			= $'\x1b[31m
GREEN		= $'\x1b[32m
YELLOW		= $'\x1b[33m
BLUE		= $'\x1b[34m
PURPLE		= $'\x1b[35m
CYAN		= $'\x1b[36m
WHITE		= $'\x1b[37m


define HEADER

 _____                                                                                _____ 
( ___ )                                                                              ( ___ )
 |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | 
 |   | .______    __    __   __   __        ______     ______     ______     ______   |   | 
 |   | |   _  \  |  |  |  | |  | |  |      /  __  \   /  __  \   /  __  \   /  __  \  |   | 
 |   | |  |_)  | |  |__|  | |  | |  |     |  |  |  | |  |  |  | |  |  |  | |  |  |  | |   | 
 |   | |   ___/  |   __   | |  | |  |     |  |  |  | |  |  |  | |  |  |  | |  |  |  | |   | 
 |   | |  |      |  |  |  | |  | |  `----.|  `--'  | |  `--'  | |  `--'  | |  `--'  | |   | 
 |   | | _|      |__|  |__| |__| |_______| \______/   \______/   \______/   \______/  |   | 
 |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| 
(_____)                                                                              (_____)

endef
export HEADER

all: $(NAME) 
	@echo ""
	@echo "${GREEN}$$HEADER"
	@echo "$(YELLOW)Created: $(words $(OBJ)) object file(s) for Philosophers"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ): $(SRC)
	@$(CC) $(CFLAGS) -c $?
	@mv *.o srcs

clean:	
	@$(RM) $(OBJ)
	@echo ""
	@echo "${RED}$$HEADER"
	@echo "$(YELLOW)Removed: $(words $(OBJ)) object file(s) from Philosophers"

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all clean