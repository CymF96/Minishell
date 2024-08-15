/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:13:04 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/06 10:17:36 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
int		create_list(t_gnl **list, int fd);
int		found_new_line(t_gnl *list);
void	append(t_gnl **list, char *buff);
t_gnl	*find_last_node(t_gnl *list);
char	*get_line(t_gnl *list);
int		len_to_new_line(t_gnl *list);
void	copy_str(t_gnl *list, char *str);
void	clean_up(t_gnl **list);
void	dealloc(t_gnl **list, t_gnl *clean_node, char *buff);

#endif
