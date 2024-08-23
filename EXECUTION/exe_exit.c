/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:13:12 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 14:13:13 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_if_exit(t_msh *msh)
{
	if (ft_strlen(msh->input) == 4 && !ft_strncmp("exit", msh->input, 4))
		exit_cleanup("User says 'Be Gone Thot!'", &msh, 0);
}
