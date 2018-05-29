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

int 	clean_exit(char ***cmd, char ***dup_env, char **pathcmd)
{
	free(*pathcmd);
	free_tab(*cmd);
	free_tab(*dup_env);
	return (1);
}

void	mnshlt_error(char *type)
{
	if (ft_strcmp(type, "setenv usage") == 0)
	{
		printf("minishell: setenv: invalid argument\n"
						  "usage: setenv VAR VALUE\n");
	}
	else if (ft_strcmp(type, "unsetenv usage") == 0)
	{
		printf("minishell: unsetenv: invalid argument\n"
						  "usage: unsetenv VAR\n");
	}
	else if (ft_strcmp(type, "env usage") == 0)
		printf("minishell: env: invalid argument\nusage: env VAR\n");
}

/*
** Dans bash OLDPWD n'existe pas au lieu d'avoir une valeur vide
*/

int     main(int ac, char **av, char **envp)
{
	char	*fd;
	char	**cmd;
	char	*pathcmd;
	char 	**dup_envp;
	char 	*built_in;

	dup_envp = ft_arrdup(envp);
	builtin_unsetenv(&dup_envp, "OLDPWD");
	while (1)
	{
		ft_printf("$>");
		get_next_line(0, &fd);
		cmd = strsplit_mnshl(&fd, dup_envp);
		pathcmd = path_cmd(cmd[0], dup_envp);
		built_in = check_builtin(cmd, &dup_envp);
		if (built_in && ft_strcmp("exit", built_in) == 0)
			return (clean_exit(&cmd, &dup_envp, &pathcmd));
		else if (!(built_in) && ft_strcmp(pathcmd, "invalide commande") == 0)
			printf("minishell: invalide commande: %s\n", cmd[0]);
		else if (!(built_in) && cmd[0] && !(fork()))
			execve(pathcmd, cmd, dup_envp);
		wait(NULL);
		free(pathcmd);
		free_tab(cmd);
	}
}
