// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

// Assuming these are your included headers for the structs and functions
#include "minishell.h"  // Contains t_msh, t_pexe, etc.

void print_envp(char **envp)
{
    int i;

    if (envp == NULL)
    {
        ft_printf("No environment variables set.\n");
        return;
    }

    for (i = 0; envp[i] != NULL; i++)
    {
        ft_printf("%s\n", envp[i]);
    }
}

// Function to add a fake environment variable to msh->envp
void add_fake_env_vars(t_msh *msh)
{
    char **new_envp;
    int env_size;
    int i;

    // Count the current number of environment variables
    for (env_size = 0; msh->envp && msh->envp[env_size] != NULL; env_size++)
        ;

    // Allocate memory for the new environment array with additional space for new variables
    new_envp = malloc((env_size + 3) * sizeof(char *)); // +3 for 2 new vars + NULL terminator
    if (new_envp == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy existing environment variables
    for (i = 0; i < env_size; i++)
    {
        new_envp[i] = strdup(msh->envp[i]);
        if (new_envp[i] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
    }

    // Add new environment variables
    new_envp[env_size] = strdup("PATH=/usr/local/bin:/usr/bin:/bin"); // Example PATH
    if (new_envp[env_size] == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    new_envp[env_size + 1] = strdup("HOME=/home/testuser"); // Example HOME
    if (new_envp[env_size + 1] == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    // NULL-terminate the new environment array
    new_envp[env_size + 2] = NULL;

    // Free the old envp array if it exists
    if (msh->envp != NULL)
    {
        for (i = 0; i < env_size; i++)
            free(msh->envp[i]);
        free(msh->envp);
    }

    // Assign the new envp to msh
    msh->envp = new_envp;
}


int main(void)
{
    t_msh *msh;
    t_pexe *cmd_node = NULL;
    t_pexe *cmd_node_2 = NULL;
    t_pexe *cmd_node_3 = NULL;
    t_pexe *cmd_node_4 = NULL;
    t_pexe *cmd_node_5 = NULL;
    t_pexe *cmd_node_6 = NULL;
    t_pexe *cmd_node_7 = NULL;
    // t_pexe *cmd_node_8 = NULL;
    // t_pexe *cmd_node_9 = NULL;
    // t_pexe *cmd_node_10 = NULL;

    // Allocate memory for the t_msh struct
    msh = (t_msh *)malloc(sizeof(t_msh));
    if (msh == NULL)
    {
        perror("Error allocating memory");
        return EXIT_FAILURE;
    }
    clean_msh_init(msh);
    // add_fake_env_vars(msh);

    ////COMMAND NODE
    cmd_node = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node == NULL)
    {
        perror("Error allocating memory for cmd_node");
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node);
    cmd_node->cmd = strdup("echo");  // First command is "echo"
    cmd_node->group_id = 0;          // Example group_id
    cmd_node->type = EXE;         // Assuming "echo" is a built-in comman       // Initially, no next node
    cmd_node->p_index = 0;

    ////COMMAND NODE2
    cmd_node_2 = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node_2 == NULL)
    {
        perror("Error allocating memory for cmd_node_2");
        free(cmd_node->cmd);
        free(cmd_node);
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node_2);
    cmd_node->next = cmd_node_2;   
    cmd_node_2->cmd = strdup("Hello");  // Next command is "Hello"
    cmd_node_2->group_id = 0;           // Same group_id as echo
    cmd_node_2->type = STRING;    
    cmd_node_2->prev = cmd_node;
    cmd_node_2->p_index = 1;

    ////COMMAND NODE3
    cmd_node_3 = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node_3 == NULL)
    {
        perror("Error allocating memory for cmd_node_3");
        free(cmd_node->cmd);
        free(cmd_node);
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node_3);
    cmd_node_2->next = cmd_node_3;   
    cmd_node_3->cmd = strdup("grep");  // Next command is "Hello"
    cmd_node_3->group_id = 1;           // Same group_id as echo
    cmd_node_3->type = EXE;
    cmd_node_3->next = cmd_node_4;            // End of the command chain
    cmd_node_3->prev = cmd_node_2;
    cmd_node_3->p_index = 0;

    ////COMMAND NODE4
    cmd_node_4 = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node_4 == NULL)
    {
        perror("Error allocating memory for cmd_node_4");
        free(cmd_node->cmd);
        free(cmd_node);
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node_4);
    cmd_node_3->next = cmd_node_4;   
    cmd_node_4->cmd = strdup("-o");  // Next command is "Hello"
    cmd_node_4->group_id = 1;           // Same group_id as echo
    cmd_node_4->type = STRING;         // You might want to adjust this if "Hello" is a different type
    cmd_node_4->prev = cmd_node_3;
    cmd_node_4->p_index = 1;

    ////COMMAND NODE5
    cmd_node_5 = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node_5 == NULL)
    {
        perror("Error allocating memory for cmd_node_5");
        free(cmd_node->cmd);
        free(cmd_node);
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node_5);
    cmd_node_4->next = cmd_node_5;   
    cmd_node_5->cmd = strdup("l");  // Next command is "Hello"
    cmd_node_5->group_id = 1;           // Same group_id as echo
    cmd_node_5->type = STRING;         // You might want to adjust this if "Hello" is a different type           // End of the command chain
    cmd_node_5->prev = cmd_node_4;
    cmd_node_5->p_index = 2;

    ////COMMAND NODE6
    cmd_node_6 = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node_6 == NULL)
    {
        perror("Error allocating memory for cmd_node_6");
        free(cmd_node->cmd);
        free(cmd_node);
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node_6);
    cmd_node_5->next = cmd_node_6;   
    cmd_node_6->cmd = strdup("wc");  // Next command is "Hello"
    cmd_node_6->group_id = 2;           // Same group_id as echo
    cmd_node_6->type = EXE;
    cmd_node_6->next = cmd_node_7;            // End of the command chain
    cmd_node_6->prev = cmd_node_5;
    cmd_node_6->p_index = 0;

    ////COMMAND NODE7
    cmd_node_7 = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node_7 == NULL)
    {
        perror("Error allocating memory for cmd_node_7");
        free(cmd_node->cmd);
        free(cmd_node);
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node_7);
    cmd_node_6->next = cmd_node_7;   
    cmd_node_7->cmd = strdup("-l");  // Next command is "Hello"
    cmd_node_7->group_id = 2;           // Same group_id as echo
    cmd_node_7->type = STRING;
    cmd_node_7->next = NULL;            // End of the command chain
    cmd_node_7->prev = cmd_node_6;
    cmd_node_7->p_index = 1;

    // ////COMMAND NODE8
    // cmd_node_8 = (t_pexe *)malloc(sizeof(t_pexe));
    // if (cmd_node_8 == NULL)
    // {
    //     perror("Error allocating memory for cmd_node_8");
    //     free(cmd_node->cmd);
    //     free(cmd_node);
    //     free(msh);
    //     return EXIT_FAILURE;
    // }
    // clean_init_pexe_node(cmd_node_8);
    // cmd_node_7->next = cmd_node_8;   
    // cmd_node_8->cmd = strdup("li");  // Next command is "Hello"
    // cmd_node_8->group_id = 1;           // Same group_id as echo
    // cmd_node_8->type = STRING;
    // cmd_node_8->next = NULL;            // End of the command chain
    // cmd_node_8->prev = cmd_node_7;
    // cmd_node_8->p_index = 1;

    // ////COMMAND NODE9
    // cmd_node_9 = (t_pexe *)malloc(sizeof(t_pexe));
    // if (cmd_node_9 == NULL)
    // {
    //     perror("Error allocating memory for cmd_node_9");
    //     free(cmd_node->cmd);
    //     free(cmd_node);
    //     free(msh);
    //     return EXIT_FAILURE;
    // }
    // clean_init_pexe_node(cmd_node_9);
    // cmd_node_8->next = cmd_node_9;   
    // cmd_node_9->cmd = strdup("wc");  // Next command is "Hello"
    // cmd_node_9->group_id = 2;           // Same group_id as echo
    // cmd_node_9->type = EXE;
    // cmd_node_9->next = cmd_node_10;            // End of the command chain
    // cmd_node_9->prev = cmd_node_8;
    // cmd_node_9->p_index = 0;

    // ////COMMAND NODE10
    // cmd_node_10 = (t_pexe *)malloc(sizeof(t_pexe));
    // if (cmd_node_10 == NULL)
    // {
    //     perror("Error allocating memory for cmd_node_10");
    //     free(cmd_node->cmd);
    //     free(cmd_node);
    //     free(msh);
    //     return EXIT_FAILURE;
    // }
    // clean_init_pexe_node(cmd_node_10);
    // cmd_node_9->next = cmd_node_10;   
    // cmd_node_10->cmd = strdup("-l");  // Next command is "Hello"
    // cmd_node_10->group_id = 2;           // Same group_id as echo
    // cmd_node_10->type = STRING;
    // cmd_node_10->next = NULL;            // End of the command chain
    // cmd_node_10->prev = cmd_node_9;
    // cmd_node_10->p_index = 1;

    // Attach cmd_node to msh
    msh->pexe = cmd_node;
    msh->pipe_nb = 2;  // No pipes for this simple test
    msh->exit_error = 0;

    execution(msh);
    exit_cleanup(NULL, msh, 0, 1);

    return EXIT_SUCCESS;
}
