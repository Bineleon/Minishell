# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/11/07 16:27:44 by bineleon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN			= \033[0;32m\e[1m
RESET			= \e[0m\033[0m

NAME			= minishell

EXEC_DIR	= src/exec/
EXEC		= children.c exec.c init_cmds.c exec_utils.c redir_input.c redir_output.c exec_cmd.c
SRC			+= $(addprefix ${EXEC_DIR}, ${EXEC})

MAIN_DIR	= src/main/
MAIN		= main.c
SRC			+= $(addprefix ${MAIN_DIR}, ${MAIN})

PARSING_DIR	= src/parsing/
PARSING		= parsing.c init_struct.c parse_env.c token_check.c parse_error.c expand.c\
					token.c
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
BUILTINS		= env.c pwd.c echo.c
SRC			+= $(addprefix ${BUILTINS_DIR}, ${BUILTINS})

G_HEADER	= hgenerator

OBJ			= ${SRC:.c=.o}
CLIBS		= -Llibft -lft

CC			= cc
RM			= rm -rf

#Conditionnal flags depending on the building version
cflags.release	:= -Wall -Wextra -Werror -Isrc -Ilibft
cflags.gdb		:= -g3
cflags.sanitize	:= -g3 -fsanitize=address
CFLAGS			= ${cflags.release} ${cflags.${build}}
export			CFLAGS

%.o : %.c
		@${CC} ${CFLAGS} -g3 -c $< -o $@

${NAME}:${OBJ}
		@${MAKE} --no-print-directory -C libft
		@${CC} ${CFLAGS} ${OBJ} ${CLIBS} -g3 -o ${NAME} -lreadline
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
	@${RM} $(OUTPUT_LEAKS)
	@echo "${GREEN}Full clean  : DONE!${RESET}"

re: fclean all

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean fclean re run
