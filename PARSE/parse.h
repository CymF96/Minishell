/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:37:03 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/23 11:42:07 by mcoskune         ###   ########.fr       */
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
	int		**poi;
	int		here_fd;
	t_token	*head;
}	t_parse;

typedef enum e_symbols
{
	IO_I = 1,
	HEREDOC = 2,
	IO_O = 3,
	APPEND = 4,
	PIPE = 5,
	AND = 6,
	OR = 7,
	L_PAR = 8,
	R_PAR = 9,
	W_C = 10,
};


#endif
