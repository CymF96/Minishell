/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:37:03 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/16 11:40:51 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_token
{
	int				start_pos;
	int				end_pos;
	int				type;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char	**parsed_args;
	// int		squt_count;
	// int		dqut_count;
	// int		pthz_count;
	// int		num_of_pipe;
	t_token	*head;
}	t_parse;

typedef enum e_par
{
	EMPTY = 0,
	TEXT = 1,
	NUM = 2,
} e_par;

#endif