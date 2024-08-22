#include "../minishell.h"

// int main(int ac, char **av, char **envp)
// {
// 	t_msh	msh;

// 	(void)av;
// 	input_validate(ac, envp);
// 	clean_initialize(&msh);
// 	while (1)
// 	{
// 		msh.input = readline("Heart of Gold>> ");
// 		if (msh.input == NULL)
// 			exit_cleanup("Problem in user input", &msh, errno);
// 		add_history(msh.input);
// 		check_if_exit(msh);
// 		if (parse_main(&msh) == 0)
// 			execution(&msh);
// 		free(msh.input);
// 		msh.input = NULL;
// 	}
// }