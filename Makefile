# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: neleon <neleon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 19:15:32 by neleon            #+#    #+#              #
#    Updated: 2024/12/15 23:28:57 by neleon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN			= \033[0;32m\e[1m
RESET			= \e[0m\033[0m

NAME			= minishell

EXEC_DIR		= src/exec/
EXEC			= children.c exec.c init_cmds.c exec_utils.c redir_input.c\
				redir_input_utils.c redir_output.c exec_cmd.c builtins.c\
				init_cmds_utils.c cmd_utils.c interactive_mode.c heredoc.c
SRC				+= $(addprefix ${EXEC_DIR}, ${EXEC})

MAIN_DIR		= src/main/
MAIN			= main.c
SRC				+= $(addprefix ${MAIN_DIR}, ${MAIN})

PARSING_DIR		= src/parsing/
PARSING			= init_struct.c parse_env.c parse_cmd.c parse_err.c parse_err2.c\
				expand_all.c expand_core.c expand_dquote.c expand_word.c expand_utils.c expand_utils2.c\
				token_core.c token_create.c token_quote.c token_var.c token_type.c
SRC				+= $(addprefix ${PARSING_DIR}, ${PARSING})

PROMPT_DIR		= src/prompt/
PROMPT			= prompt.c
SRC				+= $(addprefix ${PROMPT_DIR}, ${PROMPT})

SIGNAL_DIR		= src/signal/
SIGNAL			= signals.c signals2.c
SRC				+= $(addprefix ${SIGNAL_DIR}, ${SIGNAL})

UTILS_DIR		= src/utils/
UTILS			= gc_core.c gc_env.c gc_split.c utils.c err_msg.c\
				utils2.c gc_utils.c gc_itoa.c
SRC				+= $(addprefix ${UTILS_DIR}, ${UTILS})

BUILTINS_DIR	= src/builtins/
BUILTINS		= env.c pwd.c echo.c export.c unset.c exit.c cd.c export_utils_2.c\
				export_utils.c
SRC				+= $(addprefix ${BUILTINS_DIR}, ${BUILTINS})

G_HEADER		= hgenerator

OBJ				= ${SRC:.c=.o}
CLIBS			= -Llibft -lft

CC				= cc
RM				= rm -rf

CFLAGS			= -Wall -Wextra -Werror -Ilibft -g3

%.o : %.c
		@${CC} ${CFLAGS} -c $< -o $@

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

re: fclean
		make all

test: $(SRC)
	@echo SRC = ${SRC}

.PHONY: all clean fclean re run
