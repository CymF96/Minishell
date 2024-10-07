# include "../minishell.h"

int	dollar_expansion(t_msh *msh, int *i, t_type type)
{
	if (type == DOLLAR)
		expand_dollars(msh, i);
	else
		return (0);
	return (1);
}


int	count(t_msh *msh)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (msh->input[i])
	{
		if (msh->input[i] == '$' && msh->input[i + 1] == '?')
			count++;
		i++;
	}
	return (count);
}

void	exit_error_addition(t_msh *msh)
{
	char	*code_exit;
	int		i;
	int		j;
	char	*exit_error_num;
	int		len;

	i = 0;
	j = 0;
	exit_error_num = ft_itoa(msh->exit_error);
	len = ft_strlen(exit_error_num);
	code_exit = malloc(ft_strlen(msh->input + 1) + (count(msh)));
	while (msh->input[i])
	{
		if (msh->input[i] == '\"')
			i++;
		if (msh->input[i] == '$' && msh->input[i + 1] == '?')
		{
			ft_strlcpy(code_exit + j, exit_error_num, len + 1);
			j += len;
			i += 2;
		}
		else if (msh->input[i])
			code_exit[j++] = msh->input[i++];
	}
	code_exit[j] = '\0';
	ft_printf("%s: command not found\n", code_exit);
	free(code_exit);
	free(exit_error_num);
}

void	check_exit_status_cmd(t_msh *msh, int flag)
{
	char	*exit_message;

	if (msh->exit_error)
		exit_message = strerror(msh->exit_error);
	else if (msh->exit_error < 0)
		ft_printf("Error unknown\n");
	if (flag == 1)
		ft_printf("%d: %s\n", msh->exit_error, exit_message);
	else
		ft_printf("%d\n", msh->exit_error);
}