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

void	mnshlt_error(char *type)
{
	char *fd;

	if (ft_strcmp(type, "quote missing"))
	{
		ft_printf("quote> ");
		get_next_line(0, &fd);
		ft_printf(
				"[1]   T'étais à la recherche d'un outsanding project avec ce "
						"test de nazis ? Garde le pour 21/42 sh\n");
	}
	exit(1);
}

/*
** En realite OLDPWD n'existe pas au lieu d'avoir une valeur vide
*/

int     main(int ac, char **av, const char **envp)
{
	char	*fd;
	char	**cmd;
	char	*pathcmd;
	char 	**dup_envp;

	dup_envp = ft_arrdup(envp);
	builtin_delenv(&dup_envp, "OLDPWD");
	ft_printf("$>");
	while (1)
	{
		get_next_line(0, &fd);
		cmd = strsplit_mnshl(fd, dup_envp);
		free(fd);
		if (check_builtin(cmd, &dup_envp) && !(fork()))
		{
			pathcmd = path_cmd(cmd[0], dup_envp);
			execve(pathcmd, cmd, dup_envp);
			printf("EXIT\n");
			exit(1);
		}
		wait(NULL);
		ft_printf("$>");
		free_tab(cmd);
	}
}
