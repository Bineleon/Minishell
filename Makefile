# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: neleon <neleon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 16:39:09 by neleon            #+#    #+#              #
#    Updated: 2024/09/12 19:52:43 by neleon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN			= \033[0;32m\e[1m
RESET			= \e[0m\033[0m

NAME			= minishell

EXEC_DIR	= src/exec/
EXEC		=
SRC			+= $(addprefix ${EXEC_DIR}, ${EXEC})

MAIN_DIR	= src/main/
MAIN		= main.c
SRC			+= $(addprefix ${MAIN_DIR}, ${MAIN})

PARSING_DIR	= src/parsing/
PARSING		= 00_parsing.c 01_init_struct.c
SRC			+= $(addprefix ${PARSING_DIR}, ${PARSING})

PROMPT_DIR	= src/prompt/
PROMPT		= prompt.c
SRC			+= $(addprefix ${PROMPT_DIR}, ${PROMPT})

SIGNAL_DIR	= src/signal/
SIGNAL		= signal_handler.c
SRC			+= $(addprefix ${SIGNAL_DIR}, ${SIGNAL})

UTILS_DIR	= src/utils/
UTILS		= lst_utils.c
SRC			+= $(addprefix ${UTILS_DIR}, ${UTILS})

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
	@${RM} $(OUTPUT_LEAKS)
	@echo "${GREEN}Full clean  : DONE!${RESET}"

re: fclean all

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean fclean re run
