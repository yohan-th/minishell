/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/06 23:35:03 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/06 23:35:03 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

/*
** se poisitonne au dernier '/' et remet a '\0' jusqu'a la fin
** sauf si on est a la racine
*/

char	*cd_rmv_last_path(char *cur_dir)
{
	char *tmp;

	if (ft_strlen(cur_dir) > 1)
	{
		tmp = ft_strchr(cur_dir, '/') + 1;
		while (ft_strchr(tmp, '/'))
			tmp = ft_strchr(tmp, '/') + 1;
		while (*tmp)
			*tmp++ = '\0';
	}
	return (cur_dir);
}

void	cd_change_env(char ***envp, char *pwd, char *old_pwd, char *dir)
{
	if (!pwd || access(pwd, X_OK) == -1)
	{
		if (!pwd)
			ft_printf("minishell: cd: $HOME env not set\n");
		else if (errno == 13)
			ft_printf("minishell: cd: %s: Permission denied\n", dir);
		else if (errno == 20)
			ft_printf("minishell: cd: %s: Not a directory\n", dir);
		else if (errno == 2)
			ft_printf("minishell: cd: %s: No such file or directory\n", dir);
	}
	else
	{
		chdir(pwd);
		builtin_setenv(envp, "PWD", pwd);
		builtin_setenv(envp, "OLDPWD", old_pwd);
	}
}

int		cd_move(char ***envp, char *cur_dir, char *dir)
{
	char	*tmp;

	if (ft_strchr(dir, '~') && !get_envp(*envp, "HOME"))
		return (mnshlt_error("$HOME env not set"));
	if (dir[0] == '~')
		tmp = ft_strjoin(get_envp(*envp, "HOME"), dir + 1);
	else if (ft_strcmp(dir, get_envp(*envp, "HOME")) == 0)
		tmp = ft_strdup(dir);
	else
		tmp = ft_strjoin_mltp(4, cur_dir, "/", dir, "/");
	cd_change_env(envp, tmp, cur_dir, dir);
	free(tmp);
	return (1);
}

/*
** Supprime les doublons de / et .
** /fld1///fld2/././fld3 --> /fld1/fld2/fld3
*/

void	cd_clean_path(char *pwd)
{
	int		i;
	char	*ptn;

	i = 0;
	while (pwd && pwd[i])
	{
		ptn = pwd + i;
		if (pwd[i] == '/' && pwd[i + 1] == '/')
			ft_strdelchar(&ptn, '/');
		else if (pwd[i] == '/' && pwd[i + 1] == '.' && (i + 2) < ft_strlen(pwd)
			&& pwd[i + 2] == '/')
		{
			ft_strdelchar(&ptn, '/');
			ft_strdelchar(&ptn, '.');
		}
		else
			i++;
	}
	i--;
	while (pwd && ft_strchr("./ ", pwd[i]))
		pwd[i--] = '\0';
}

/*
** Par default cd suit les links (option -L)
*/

void	builtin_cd(char **cmd, char ***envp)
{
	int		i;
	char	*cur_dir;

	i = 1;
	while (cmd[i] != NULL && cmd[i][0] == '-' && cmd[i][1] != '\0')
		i++;
	if ((cmd[i - 1][0] == '-' && cmd[i - 1][ft_strlen(cmd[i - 1]) - 1] == 'P')
			|| get_envp(*envp, "PWD") == NULL)
		cur_dir = get_cur_dir();
	else
		cur_dir = ft_strdup(get_envp(*envp, "PWD"));
	if (cmd[i] == NULL || ft_strlen(cmd[i]) == 0)
		cd_change_env(envp, get_envp(*envp, "HOME"), cur_dir, "HOME");
	else if (ft_strcmp(cmd[i], "-") == 0 && get_envp(*envp, "OLDPWD") == NULL)
		ft_printf("minishell: cd: OLDPWD not set\n");
	else if (ft_strcmp(cmd[i], "-") == 0)
		cd_change_env(envp, get_envp(*envp, "OLDPWD"), cur_dir, "OLDPWD");
	else if (ft_strcmp(cmd[i], "..") == 0)
		cd_change_env(envp, cd_rmv_last_path(cur_dir), cur_dir, "RMV_LAST");
	else
		cd_move(envp, cur_dir, cmd[i]);
	cd_clean_path(get_envp(*envp, "PWD"));
	free(cur_dir);
}
