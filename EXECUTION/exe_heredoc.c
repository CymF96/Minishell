// #include "../minishell.h"

// void	double_red_left(t_msh *msh)
// {
// 	pid_t	pids;
// 	int		save_stdin;
	
// 	save_stdin = dup(STDIN_FILENO);
// 	open_file_input(msh);
// 	if (msh->pexe->next)
// 		msh->pexe = msh->pexe->next;
// 	pids = fork();
// 	if (pids == 0)
// 		check_type(msh);
// 	else
// 	{
// 		wait(NULL);
// 		msh->fd[0] = 0;
// 		msh->fd[1] = 1;
// 		dup2(save_stdin, STDIN_FILENO);
// 	}
// }