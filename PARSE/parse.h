/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:37:03 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 17:03:04 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_token
{
	
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	
	t_token	*tkn;
}	t_parse;


#endif