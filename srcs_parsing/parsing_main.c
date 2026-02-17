/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:53:41 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:38:19 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo lalka | grep la | wc -l > out.txt > out2.txt
// static t_pipeline	*set_temp_pipeline(void)
// {
// 	t_pipeline	*pipeline;

// 	pipeline = malloc(sizeof(t_pipeline));
// 	pipeline->cmd.args = ft_calloc(3, sizeof(char *));
// 	pipeline->cmd.args[0] = ft_strdup("echo");
// 	pipeline->cmd.args[1] = ft_strdup("lalka");
// 	pipeline->cmd.args[2] = NULL;
// 	pipeline->cmd.redirects = NULL;
// 	pipeline->next = malloc(sizeof(t_pipeline));
// 	pipeline->next->cmd.args = ft_calloc(3, sizeof(char *));
// 	pipeline->next->cmd.args[0] = ft_strdup("grep");
// 	pipeline->next->cmd.args[1] = ft_strdup("la");
// 	pipeline->next->cmd.args[2] = NULL;
// 	pipeline->next->cmd.redirects = NULL;
// 	pipeline->next->next = malloc(sizeof(t_pipeline));
// 	pipeline->next->next->cmd.args = ft_calloc(3, sizeof(char *));
// 	pipeline->next->next->cmd.args[0] = ft_strdup("wc");
// 	pipeline->next->next->cmd.args[1] = ft_strdup("-l");
// 	pipeline->next->next->cmd.args[2] = NULL;
// 	pipeline->next->next->cmd.redirects = malloc(sizeof(t_redirects));
// 	pipeline->next->next->cmd.redirects->type = REDIR_OUT;
// 	pipeline->next->next->cmd.redirects->target = ft_strdup("out.txt");
// 	pipeline->next->next->cmd.redirects->quote_delim = FALSE;
// 	pipeline->next->next->cmd.redirects->next = malloc(sizeof(t_redirects));
// 	pipeline->next->next->cmd.redirects->next->type = REDIR_OUT;
// 	pipeline->next->next->cmd.redirects->next->target = ft_strdup("out2.txt");
// 	pipeline->next->next->cmd.redirects->next->quote_delim = FALSE;
// 	pipeline->next->next->cmd.redirects->next->next = NULL;
// 	pipeline->next->next->next = NULL;
// 	return (pipeline);
// }


int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_pipeline	*pipeline;
	char		*line;

	((void)argc, (void)argv);
	shell.envp = envp;
	shell.last_status = 0;
	ft_printf(P "MINIsHELL > " R);
	line = get_next_line(0);
	while (line)
	{
		if (*line && !ft_isallspaces(line))
		{
			pipeline = parse_line(line, shell);
			if (pipeline)
			{
				print_pipeline(pipeline);
				free_pipeline(pipeline);
			}
		}
		free(line);
		ft_printf(P "MINIsHELL > " R);
		line = get_next_line(0);
	}
	ft_printf("exit\n");
	return (0);
}
