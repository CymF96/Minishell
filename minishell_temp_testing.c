// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

// Assuming these are your included headers for the structs and functions
#include "minishell.h"  // Contains t_msh, t_pexe, etc.

// void print_envp(char **envp)
// {
//     int i;

//     if (envp == NULL)
//     {
//         ft_printf("No environment variables set.\n");
//         return;
//     }

//     for (i = 0; envp[i] != NULL; i++)
//     {
//         ft_printf("%s\n", envp[i]);
//     }
// }

// // Function to add a fake environment variable to msh->envp
// void add_fake_env_vars(t_msh *msh)
// {
//     char **new_envp;
//     int env_size;
//     int i;

//     // Count the current number of environment variables
//     for (env_size = 0; msh->envp && msh->envp[env_size] != NULL; env_size++)
//         ;

//     // Allocate memory for the new environment array with additional space for new variables
//     new_envp = malloc((env_size + 3) * sizeof(char *)); // +3 for 2 new vars + NULL terminator
//     if (new_envp == NULL)
//     {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }

//     // Copy existing environment variables
//     for (i = 0; i < env_size; i++)
//     {
//         new_envp[i] = strdup(msh->envp[i]);
//         if (new_envp[i] == NULL)
//         {
//             perror("strdup");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Add new environment variables
//     new_envp[env_size] = strdup("PATH=/usr/local/bin:/usr/bin:/bin"); // Example PATH
//     if (new_envp[env_size] == NULL)
//     {
//         perror("strdup");
//         exit(EXIT_FAILURE);
//     }

//     new_envp[env_size + 1] = strdup("HOME=/home/testuser"); // Example HOME
//     if (new_envp[env_size + 1] == NULL)
//     {
//         perror("strdup");
//         exit(EXIT_FAILURE);
//     }

//     // NULL-terminate the new environment array
//     new_envp[env_size + 2] = NULL;

//     // Free the old envp array if it exists
//     if (msh->envp != NULL)
//     {
//         for (i = 0; i < env_size; i++)
//             free(msh->envp[i]);
//         free(msh->envp);
//     }

//     // Assign the new envp to msh
//     msh->envp = new_envp;
// }


int main(void)
{
    t_msh *msh;
    t_pexe *cmd_node;
    t_pexe *cmd_node_2;
    t_pexe *cmd_node_3;
    // t_pexe *cmd_node_4;

    // Allocate memory for the t_msh struct
    msh = (t_msh *)malloc(sizeof(t_msh));
    if (msh == NULL)
    {
        perror("Error allocating memory");
        return EXIT_FAILURE;
    }
    clean_msh_init(msh);
    // add_fake_env_vars(msh);
    // Allocate and initialize the first command node (echo)
    cmd_node = (t_pexe *)malloc(sizeof(t_pexe));
    if (cmd_node == NULL)
    {
        perror("Error allocating memory for cmd_node");
        free(msh);
        return EXIT_FAILURE;
    }
    clean_init_pexe_node(cmd_node);
    cmd_node->cmd = strdup("cat");  // First command is "echo"
    cmd_node->group_id = 0;          // Example group_id
    cmd_node->type = EXE;         // Assuming "echo" is a built-in comman       // Initially, no next node
    cmd_node->option = malloc(2 * sizeof(char *));
    cmd_node->option[0] = strdup("cat");
    cmd_node->option[1] = NULL;
    cmd_node->p_index = 0;

    // Allocate and initialize the next command node (Hello)
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
    cmd_node_2->cmd = strdup("test.txt");  // Next command is "Hello"
    cmd_node_2->group_id = 0;           // Same group_id as echo
    cmd_node_2->type = STRING;    
    // cmd_node_2->option = malloc(2 * sizeof(char *));     // You might want to adjust this if "Hello" is a different type
    // cmd_node_2->option[0] = strdup("cat");       // End of the command chain
    cmd_node_2->prev = cmd_node;
    cmd_node_2->p_index = 1;

    // // Attach cmd_node to msh
    // msh->pipe_nb = 0;  // No pipes for this simple test
    // msh->exit_error = 0;

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
    cmd_node_3->cmd = strdup("wc");  // Next command is "Hello"
    cmd_node_3->group_id = 1;           // Same group_id as echo
    cmd_node_3->type = EXE;
    cmd_node_3->option = malloc(3 * sizeof(char *));     // You might want to adjust this if "Hello" is a different type
    cmd_node_3->option[0] = strdup("wc");
    cmd_node_3->option[1] = strdup("-l");          // You might want to adjust this if "Hello" is a different type
    cmd_node_3->option[2] = NULL; 
    cmd_node_3->next = NULL;            // End of the command chain
    cmd_node_3->prev = cmd_node_2;
    cmd_node_3->p_index = 0;

    //Attach cmd_node to msh
    // msh->pipe_nb = 0;  // No pipes for this simple test
    // msh->exit_error = 0;

    // cmd_node_4 = (t_pexe *)malloc(sizeof(t_pexe));
    // if (cmd_node_4 == NULL)
    // {
    //     perror("Error allocating memory for cmd_node_4");
    //     free(cmd_node->cmd);
    //     free(cmd_node);
    //     free(msh);
    //     return EXIT_FAILURE;
    // }
    // clean_init_pexe_node(cmd_node_4);
    // cmd_node_3->next = cmd_node_4;   
    // cmd_node_4->cmd = strdup("test3");  // Next command is "Hello"
    // cmd_node_4->group_id = 01;           // Same group_id as echo
    // cmd_node_4->type = STRING;         // You might want to adjust this if "Hello" is a different type
    // // cmd_node_4->next = NULL;            // End of the command chain
    // cmd_node_4->prev = cmd_node_3;
    // cmd_node_4->p_index = 3;

    // Attach cmd_node to msh
    msh->pexe = cmd_node;
    msh->pipe_nb = 1;  // No pipes for this simple test
    msh->exit_error = 0;

    // Run the execution function
    // if (msh->pipe_nb > 0)
    //     ft_pipex(msh);
    execution(msh);
    // print_envp(msh->envp);
    // execution(msh);
    // print_envp(msh->envp);
    exit_cleanup(NULL, msh, 0, 1);

    // Clean up

    return EXIT_SUCCESS;
}
