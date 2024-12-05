# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/12/05 20:52:51 by bineleon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN			= \033[0;32m\e[1m
RESET			= \e[0m\033[0m

NAME			= minishell

EXEC_DIR	= src/exec/
EXEC		= children.c exec.c init_cmds.c exec_utils.c redir_input.c redir_output.c\
				exec_cmd.c exec_builtins.c
SRC			+= $(addprefix ${EXEC_DIR}, ${EXEC})

MAIN_DIR	= src/main/
MAIN		= main.c
SRC			+= $(addprefix ${MAIN_DIR}, ${MAIN})

PARSING_DIR	= src/parsing/
PARSING		= init_struct.c parse_env.c token_check.c parse_error.c\
						token.c 00_expand.c 01_expand.c 02_expand.c 03_expand.c 04_expand_utils.c


SRC			+= $(addprefix ${PARSING_DIR}, ${PARSING})

PROMPT_DIR	= src/prompt/
PROMPT		= prompt.c
SRC			+= $(addprefix ${PROMPT_DIR}, ${PROMPT})

SIGNAL_DIR	= src/signal/
SIGNAL		= signal_handler.c
SRC			+= $(addprefix ${SIGNAL_DIR}, ${SIGNAL})

UTILS_DIR	= src/utils/
UTILS		= lst_utils.c garbage_collector.c split.c utils.c error_mess.c
SRC			+= $(addprefix ${UTILS_DIR}, ${UTILS})

BUILTINS_DIR	= src/builtins/
BUILTINS		= env.c pwd.c echo.c export.c unset.c exit.c cd.c
SRC			+= $(addprefix ${BUILTINS_DIR}, ${BUILTINS})

G_HEADER	= hgenerator

OBJ			= ${SRC:.c=.o}
CLIBS		= -Llibft -lft

CC			= cc
RM			= rm -rf

#Conditionnal flags depending on the building version
cflags.release	:= -Wall -Wextra -Werror -Ilibft
cflags.gdb		:= -g3
cflags.sanitize	:= -g3 -fsanitize=address
CFLAGS			= ${cflags.release} ${cflags.${build}}
export			CFLAGS

%.o : %.c
		@${CC} ${CFLAGS} -g3 -c $< -o $@

${NAME}:${OBJ}
		@${MAKE} --no-print-directory -C libft
		@${CC} ${CFLAGS} ${OBJ} ${CLIBS} -o ${NAME} -lreadline
		@echo "${GREEN}Minishell   : DONE!${RESET}"

all: ${NAME}

run: re
		./minishell

clean:
	@${RM} ${OBJ}
	@${MAKE} --no-print-directory -C libft fclean
	@echo "${GREEN}Clean       : DONE!${RESET}"

fclean: clean
	@${RM} ${NAME}
	@echo "${GREEN}Full clean  : DONE!${RESET}"

re: fclean all

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean fclean re run
