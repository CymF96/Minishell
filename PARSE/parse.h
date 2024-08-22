/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:37:03 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/22 20:39:26 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_token
{
	char			*token;
	int				start_pos;
	int				end_pos;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char	*modified;
	int		size_modified;
	int		here_fd;
	t_token	*head;
}	t_parse;

typedef enum e_symbols
{
	IO_I = '<',
	HEREDOC,
	IO_O = '>',
	APPEND,
	PIPE = '|',
	AND = '&',
	OR,
	L_PAR = '(',
	R_PAR = ')',
	W_C = '*',
};


#endif
