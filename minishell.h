/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/14 17:53:47 by mcoskune         ###   ########.fr       */
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

typedef struct s_token
{
	int				start_pos;
	int				end_pos;
	int				type;
	struct s_token	prev;
	struct s_token	next;
}	t_token;

typedef struct s_parse //parsing structure
{
	char	**poi;
	int		squt_count;
	int		dqut_count;
	int		pthz_count;
	
	int		num_of_pipe;
}	t_parse;

typedef struct s_msh //master structure 'minishell'
{
	char		*input;
	char		**parsed_args; // needed for execution
	t_parse		*parse;
	t_parent	*parent_str;
}	t_msh;

typedef enum e_par
{
	PARANTH_L,
	PARANTH_R,
	PIPE,
	DQT_L,
	DQT_R,
	SQT_L,
	SQT_R,
	REDIR
};


/*------- INPUT_VALIDATE -------*/
void	input_validate(int ac, char **envp);

/*------- INITIALIZE -------*/
void	clean_initialize(t_msh *sdata);

/*------- PARSE USER INPUT -------*/
void	parse_input(t_msh *msh);

/*------- EXECUTION -------*/
void	check_if_exit(t_msh msh);

/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag);

#endif