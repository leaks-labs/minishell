/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:21:55 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/12 16:40:38 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int main() {

    //const char *str = "get_replaced";
    // Initialize Readline history
    using_history();

    char *input = readline("Enter a command: ");
    while (input != NULL && *input != '\0') {
        // Add the entered command to the history
        add_history(input);

        // Print the commands from the history
        for (int i = history_length; i >= 0; i--) {
            HIST_ENTRY *entry = history_get(i);
            if (entry != NULL) {
                printf("\nHistory[%d]: %s\n\n", i, entry->line);
            }
        }

        // Free the input buffer
        free(input);

        // Get the next input
        input = readline("Enter a command: ");
        rl_on_new_line();
        rl_replace_line("v", 0);
        rl_redisplay();
        printf("\n");
        //fprintf(stdout, "-->%s\n", rl_line_buffer);

    }

    // Clean up history and input
    free(input);
    rl_clear_history();
    return 0;
}


