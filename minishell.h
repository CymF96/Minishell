/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 17:19:24 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <linux/limits.h>
# include "./LIBFT/libft.h"
# include "./PARSE/parse.h"

typedef struct s_child //fork and pipe
{
	int		fd_in;
	int		fd_out;
	char	**commands;
}	t_child;

typedef struct s_parent //fork and pipe
{
	int		fd_in;
	int		fd_out;
	int		num_of_child;
	char	*heredoc;
	char	*heredoc_delim;
	pid_t	*pids;
	t_child	*children;
}	t_parent;

typedef struct s_msh //master structure 'minishell'
{
	char		*input;
	char		**parsed_args; // needed for execution
	char		**envp; // keep the array in the structure to be sure to print all env var if env builtin function is called?
	t_parse		*parse;
	t_parent	*parent_str;
}	t_msh;

typedef enum e_type
{
	COMMAND,
	STRING,
	DQT,
	SQT,
	
};



/*------- INPUT_VALIDATE -------*/
void	input_validate(int ac, char **envp);

/*------- INITIALIZE -------*/
void	clean_initialize(t_msh *msh);


/*------- EXECUTION -------*/
void	check_if_exit(t_msh msh);
int		execution(t_msh *msh);
void	check_builtin_cmd(t_msh *msh, char *cmd, int i);
void	check_exit_status_cmd(t_msh *msh, char *cmd);
void	cmd_exit(t_msh *msh);
void	cmd_echo(t_msh *msh, int i);
void	cmd_pwd(void);
void	cmd_cd(t_msh *msh, int i);
void	cmd_env(t_msh *msh);
void	check_exit_status_cmd(t_msh *msh, char *cmd);

/*------- PARSE USER INPUT -------*/
int	parse_main(t_msh *msh);

/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag);

#endif