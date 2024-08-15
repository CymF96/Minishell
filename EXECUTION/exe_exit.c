#include "execution.h"

void	check_if_exit(t_msh msh)
{
	if (ft_strlen(msh.input) == 4 && !ft_strncmp("exit", msh.input, 4))
		exit_cleanup("User says 'Be Gone Thot!'", &msh, 0);
}
