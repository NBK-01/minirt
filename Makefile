NAME = minirt

HEADER = ./headers/

AUTHOR = nkanaan && mmuhaise

LIBFT = lib/libft.a

MLX = lib/mlx/libmlx.a

INC = -I ./lib/mlx

LIB = -L ./lib/mlx -lmlx -lXext -lX11 -lm -lbsd

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address


SRCS = main init/parse init/validation

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))

SHELL := /bin/bash

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
OK_COLOR    	= \033[0;32m
_END		=	\e[0m
_GREEN		=	\e[32m
_WHITE		=	\e[37m
_MUP		=	\e[1A
_ERASE		=	\e[K


all: header $(NAME) 

	@printf "\033[?25h"
header:
	@printf "%b" "$(OK_COLOR)"
	@echo ".------..------."
	@echo "|4.--. ||2.--. |"
	@echo "| :/\: || (\/) |"
	@echo "| :\/: || :\/: |"
	@echo "| '--'4|| '--'2|"
	@echo "'------''------'"
	@echo "MINIRT"

	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)$(NO_COLOR)\n"
	@echo

objs/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${INC} -c $< -o $@
	@printf "\033[?25l"
	@printf "$(_ERASE)\r"
	@printf "$<$(_END)\n"
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(OK_COLOR)*"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT) + 1))))
	@printf "\r$(_MUP)"


$(NAME):	$(OBJS) $(MLX) $(LIBFT) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(LIBFT) $(LIB)
	@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(LIBFT):
			@make -C ./lib
			@printf "%-53b%b" "$(COM_COLOR)LIBFT Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(MLX):
			@make -C ./lib/mlx/
			@printf "%-53b%b" "$(COM_COLOR)MLX Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

clean:
			rm -rf $(OBJS) ./objs
			@make clean -C ./lib
			@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


fclean:		clean
				rm $(NAME)
				rm ./lib/libft.a
				@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY: 	all clean fclean re

.SILENT: 	clean fclean re all

