/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/04 17:43:29 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./constants.h"
#include "../libft/ft_printf/includes/ft_printf.h"
#include "../libft/gnl/get_next_line_bonus.h"
#include "../libft/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void  ft_prompt(void);

#endif
