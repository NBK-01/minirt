
_END		=	\e[0m

_GREEN		=	\e[32m
_WHITE		=	\e[37m

_MUP		=	\e[1A
_ERASE		=	\e[K

CNT = 1

STRING_SRC	= ft_memset ft_bzero ft_memchr ft_memcpy ft_strdup ft_strlcpy ft_strncmp ft_strchr ft_strrchr ft_strlen ft_memmove ft_strlen ft_strnstr ft_strlcat

CTYPE_SRC	= ft_isalpha ft_isalnum ft_isdigit ft_isprint ft_isspace ft_tolower ft_toupper ft_isascii

LIST_SRC	= ft_lstadd_back ft_lstclear ft_lstiter ft_lstmap ft_lstsize ft_lstadd_front ft_lstdelone ft_lstlast ft_lstnew

STDLIB_SRC	= ft_atoi ft_calloc

CUSTOM_SRC	= ft_itoa ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_putchar_fd ft_split ft_strjoin ft_strtrim ft_substr ft_striteri ft_strmapi

STRING_SRCS		= $(addprefix srcs/string/, $(addsuffix .c, ${STRING_SRC}))

CTYPE_SRCS		= $(addprefix srcs/ctype/, $(addsuffix .c, ${CTYPE_SRC}))

STDLIB_SRCS		= $(addprefix srcs/stdlib/, $(addsuffix .c, ${STDLIB_SRC}))

CUSTOM_SRCS		= $(addprefix srcs/custom/, $(addsuffix .c, ${CUSTOM_SRC}))

LIST_SRCS		= $(addprefix srcs/list/, $(addsuffix .c, ${LIST_SRC}))

HEAD		= ./includes/libft.h

STRING_OBJS		= $(addprefix objs/string/, $(addsuffix .o, $(STRING_SRC)))

CTYPE_OBJS		= $(addprefix objs/ctype/, $(addsuffix .o, $(CTYPE_SRC)))

STDLIB_OBJS		= $(addprefix objs/stdlib/, $(addsuffix .o, $(STDLIB_SRC)))

CUSTOM_OBJS		= $(addprefix objs/custom/, $(addsuffix .o, $(CUSTOM_SRC)))

LIST_OBJS		= $(addprefix objs/list/, $(addsuffix .o, $(LIST_SRC)))

NAME = libft.a

CC			= cc
RM			= rm -f
AR			= ar rc
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror
OK_COLOR    	= \033[0;32m
_END		=	\e[0m
_GREEN		=	\e[32m
_WHITE		=	\e[37m
_MUP		=	\e[1A
_ERASE		=	\e[K


objs/%.o:	srcs/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "\033[?25l"
	@printf "$(_ERASE)\r"
	@printf "$<$(_END)\n"
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(OK_COLOR)*"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT) + 1))))
	@printf "\r$(_MUP)"


${NAME}:	${STRING_OBJS} ${CTYPE_OBJS} ${LIST_OBJS} ${CUSTOM_OBJS} ${STDLIB_OBJS}
	@${AR} ${NAME} ${STRING_OBJS} ${CTYPE_OBJS} ${LIST_OBJS} ${CUSTOM_OBJS} ${STDLIB_OBJS}
	@${RN} ${NAME}


all:		${NAME}

clean:
			@rm -rf ${STRING_OBJS} ${CTYPE_OBJS} ${LIST_OBJS} ${CUSTOM_OBJS} ${STDLIB_OBJS} rm -rf objs/

fclean:		clean
		@${RM} ${NAME}
			@${RM} $(NAME)

re:			fclean all

.PHONY:		all  clean fclean re
