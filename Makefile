# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 22:25:37 by oayyoub           #+#    #+#              #
#    Updated: 2025/01/04 18:57:02 by oayyoub          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

BGreen = \033[1;32m
BYellow = \033[1;33m
BBlue = \033[1;34m
BPurple = \033[1;38;5;205m
BRed = \033[1;31m
RESET = \033[0m

UTILS = ft_split.c utils_1.c utils_2.c utils_strings.c ft_printf.c get_next_line_utils_bonus.c
MANDATORY = pipex.c
BONUS = pipex_bonus.c get_next_line_bonus.c 
BONUS_FLAG = .bonus

OBJ = $(MANDATORY:.c=.o) $(UTILS:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o) $(UTILS:.c=.o)

all: logo $(NAME)

$(NAME): $(OBJ)
	@echo "\n$(BBlue)Building $(BPurple)$(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(BGreen)Done!$(RESET)"

%.o: %.c
	@echo -n "$(BYellow).$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

bonus: logo_bonus $(BONUS_FLAG)

$(BONUS_FLAG): $(OBJ_BONUS)
	@echo "\n$(BBlue)Building $(BPurple)$(NAME) [Bonus]$(RESET)"
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)
	@echo "$(BGreen)Bonus Done!$(RESET)"
	@touch $(BONUS_FLAG)

logo:
	@echo "$(BGreen)"
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
	@echo "$(BPurple)By: oayyoub$(RESET)"

logo_bonus:
	@echo "$(BGreen)"
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝  BONUS"
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
	@echo "$(BPurple)By: oayyoub$(RESET)"

clean:
	@echo "$(BRed)Cleaning object files...$(RESET)"
	rm -f $(OBJ) $(OBJ_BONUS)
	@rm -f $(BONUS_FLAG)

fclean: clean
	@echo "$(BRed)Cleaning program...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus logo logo_bonus clean fclean re
