/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:12:01 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/15 22:36:50 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_up(t_gnl **list)
{
	t_gnl	*last_node;
	t_gnl	*new_node;
	int		i;
	int		j;
	char	*buff;

	i = 0;
	j = 0;
	buff = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_gnl));
	if (!buff || !new_node)
		return ;
	last_node = find_last_node(*list);
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
		buff[j++] = last_node->content[i];
	buff[j] = '\0';
	new_node->content = buff;
	new_node->next = NULL;
	dealloc(list, new_node, buff, 0);
}

char	*get_line(t_gnl *list)
{
	int		len;
	char	*full_str;

	if (!list)
		return (NULL);
	len = len_to_new_line(list);
	full_str = malloc (len + 1);
	if (!full_str)
		return (NULL);
	copy_str(list, full_str);
	return (full_str);
}

void	append(t_gnl **list, char *buff, t_msh *msh)
{
	t_gnl	*new_node;
	t_gnl	*last_node;


	if (msh->interrupted)
	{
		if (*list != NULL)
			dealloc(list, NULL, NULL, 1);
		if (buff != NULL)
			free (buff);
		return ;
	}
	last_node = find_last_node (*list);
	new_node = malloc (sizeof(t_gnl));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buff;
	new_node->next = NULL;
}

int	create_list(t_gnl **list, int fd, t_msh *msh)
{
	int		char_read;
	char	*buff;

	while (!found_new_line (*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (0);
		if (msh->interrupted)
		{
			if (list != NULL)
				dealloc(list, NULL, NULL, 1);
			if (buff != NULL)
				free (buff);
			return (-1);
		}
		char_read = read (fd, buff, BUFFER_SIZE);
		if (char_read == -1)
			return (free(buff), -1);
		if (!char_read)
			return (free(buff), 0);
		buff[char_read] = '\0';
		append(list, buff, msh);
	}
	return (0);
}

char	*get_next_line(int fd, t_msh *msh)
{
	static t_gnl	*list = NULL;
	char			*next_line;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = create_list (&list, fd, msh);
	if (!list || i == -1)
		return (NULL);
	next_line = get_line(list);
	clean_up(&list);
	return (next_line);
}
