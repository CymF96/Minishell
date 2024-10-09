#include "../minishell.h"

void	check_remove_heredoc(t_msh *msh, int heredoc, int infile, int g)
{
	t_pexe	*delme;
	t_pexe	*current;

	current = msh->pexe;
	while (current != NULL)
	{
		if (current->type == HEREDOC && heredoc && infile \
				&& current->group_id == g)
		{
			delme = current;
			current = current->next;
			current->prev = delme->prev;
			delme->prev->next = current;
			unlink(delme->cmd);
			free(delme->temp);
			free(delme);
			delme = NULL;
		}
		current = current->next;
	}
}

void	check_heredoc_infile(t_msh *msh)
{
	int	heredoc;
	int	infile;
	int	g_infile;
	t_pexe	*head;

	head = msh->pexe;
	heredoc = 0;
	infile = 0;
	while (msh->pexe != NULL)
	{
		if (msh->pexe->type == HEREDOC)
			heredoc = 1;
		if (msh->pexe->type == INFILE)
		{
			infile = 1;
			g_infile = msh->pexe->group_id;
		}
		msh->pexe = msh->pexe->next;
	}
	msh->pexe = head;
	check_remove_heredoc(msh, heredoc, infile, g_infile);
	msh->pexe = head;
}

void	remove_node(t_msh *msh, int heredoc, int g)
{
	t_pexe	*current;
	t_pexe	*delme;

	current = msh->pexe;
	while (current != NULL)
	{
		if (current->type == HEREDOC && heredoc > 1 \
				&& current->group_id == g)
		{
			heredoc--;
			delme = current;
			current = current->next;
			current->prev = delme->prev;
			delme->prev->next = current;
			unlink(delme->cmd);
			free(delme->cmd);
			free(delme);
			delme = NULL;
		}
		else
			current = current->next;
	}

}

void	check_double_heredoc(t_msh *msh)
{
	t_pexe	*head;
	int		heredoc;
	int		g;

	heredoc = 0;
	head = msh->pexe;
	while (msh->pexe != NULL)
	{
		if (msh->pexe->type == HEREDOC)
		{
			g = msh->pexe->group_id;
			heredoc++;
		}
		msh->pexe = msh->pexe->next;
	}
	msh->pexe = head;
	remove_node(msh, heredoc, g);
	msh->pexe = head;
}


void	sort_pexe(t_msh *msh)
{
	t_pexe	*current;
	t_pexe	*next;
	int		loop;

	loop = 1;
	while (loop)
	{
		loop = 0;
		current = msh->pexe;
		while (current != NULL && current->next != NULL)
		{
			next = current->next;
			if (current->group_id > next->group_id || (current->group_id == \
				next->group_id && current->p_index > next->p_index))
			{
				swap(current, next);
				current = next;
				next = next->next;
				if (next != NULL && current->type == HEREDOC && next->type == STRING \
						&& current->group_id == next->group_id)
				{
					next->p_index = current->p_index++;
					swap(current, next);
				}
				loop = 1;
			}
			current = current->next;
		}
	}
	check_heredoc_infile(msh);
	check_double_heredoc(msh);
}