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

int		check_argc(int argc, char **argv)
{
	if (argc == 1)
		return (0);
	else
	{
		ft_printf("minishell: don't need option(s)\n"
					"usage: %s\n", argv[0]);
		return (1);
	}
}

int		mnshlt_error(char *type)
{
	if (ft_strcmp(type, "setenv usage") == 0)
	{
		ft_printf("minishell: setenv: invalid argument\n"
					"usage: setenv VAR VALUE\n");
	}
	else if (ft_strcmp(type, "unsetenv usage") == 0)
	{
		ft_printf("minishell: unsetenv: invalid argument\n"
					"usage: unsetenv VAR\n");
	}
	else if (ft_strcmp(type, "env usage") == 0)
		ft_printf("minishell: env: invalid argument\nusage: env VAR\n");
	else if (ft_strcmp(type, "$HOME env not set"))
		printf("minishell: cd ~: $HOME env not set\n");
	return (0);
}

/*
** command unknown est pour kill le fork
*/

int		run_cmd(char **cmd, char ***envp, char *pathcmd)
{
	char *built_in;

	built_in = check_builtin(cmd, envp);
	if (built_in && ft_strcmp("exit", built_in) == 0)
	{
		free(pathcmd);
		free_tab(cmd);
		free_tab(*envp);
		return (0);
	}
	else if (!(built_in) && ft_strcmp(pathcmd, "command not found") == 0)
		ft_printf("minishell: %s: command not found\n", cmd[0]);
	else if (!(built_in) && ft_strcmp(pathcmd, "cmd is directory") == 0)
		ft_printf("minishell: %s: is a directory\n", cmd[0]);
	else if (!(built_in) && cmd[0] && cmd[0][0] && !(fork()))
		execve(pathcmd, cmd, *envp);
	return (1);
}

/*
** Lorsqu'on lance minishell, OLDPWD ne doit pas exister, on le del de dup_envp
*/

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**cmd;
	char	*pathcmd;
	char	**dup_envp;

	if (check_argc(ac, av))
		return (0);
	dup_envp = ft_arrdup(envp);
	dup_envp = rmv_key_env(dup_envp, "OLDPWD");
	line = NULL;
	while (1)
	{
		ft_printf("$>");
		get_next_line(0, &line);
		cmd = strsplit_mnshl(line, dup_envp);
		free(line);
		pathcmd = path_cmd(cmd[0], dup_envp);
		//printf("pathcmd <%s>\n", pathcmd);
		if (pathcmd && !(run_cmd(cmd, &dup_envp, pathcmd)))
			return (1);
		wait(NULL);
		free(pathcmd);
		free_tab(cmd);
	}
}
