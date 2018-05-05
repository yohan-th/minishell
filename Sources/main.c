/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 19:23:25 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 19:23:25 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"


int     main(int ac, char **av, char **envp)
{
	char	*fd;
	char	**cmd;
	pid_t	father;
	char	*pathcmd;

	while (1)
	{
		get_next_line(0, &fd);
		cmd = ft_strsplit(fd, ' ');
		free(fd);
		father = fork();
		if (father == 0)
		{
			pathcmd = path_cmd(cmd[0], envp);
			execve(pathcmd, cmd, NULL);
			printf("EXIT\n");
		}
		free_tab(cmd);
	}
}
