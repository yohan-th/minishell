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

void	cd_change_env(char ***envp, char *pwd, char *old_pwd)
{
	if (chdir(pwd) == -1)
		printf("minishell: cd: OLDPWD not set\n");
	else
	{
		builtin_setenv(envp, "PWD", pwd);
		builtin_setenv(envp, "OLDPWD", old_pwd);
	}
}

void	cd_move(char ***envp, char *cur_dir, char *dir)
{
	char	*tmp;

	if (dir[0] == '~')
		tmp = ft_strjoin(get_envp(*envp, "HOME"), dir + 1);
	else
		tmp = ft_strjoin_mltp(3, cur_dir, "/", dir);
	access(tmp, W_OK);
	if (errno == 13)
		printf("minishell: cd: %s: Permission denied\n", dir);
	else if (errno == 2)
		printf("minishell: cd: %s: No such file or directory\n", dir);
	else
		cd_change_env(envp, tmp, cur_dir);
	free(tmp);
}

void	cd_clean_path(char *pwd)
{
	int i;

	i = 0;
	while (*pwd)
	{
		if (*pwd == '/' && *(pwd + 1) == '/')
			ft_strdelchar(&pwd, '/');
		else if (*pwd == '/' && *(pwd + 1) == '.' && *(pwd + 2) == '/')
		{
			ft_strdelchar(&pwd, '/');
			ft_strdelchar(&pwd, '.');
		}
		else
			pwd++;
	}
	pwd--;
	while (ft_strchr("./ ", *pwd))
		*pwd-- = '\0';
}

/*
** Par default cd suit les links (option -L)
*/

void	builtin_cd(char **cmd, char ***envp)
{
	BOOL	opt_p;
	int		i;
	char 	*cur_dir;

	opt_p = 0;
	i = 1;
	while (cmd[i] != NULL && cmd[i][0] == '-' && cmd[i][1] != '\0')
		i++;
	if (cmd[i - 1][0] == '-' && cmd[i - 1][ft_strlen(cmd[i - 1]) - 1] == 'P')
		opt_p = 1;
	if (opt_p)
		cur_dir = get_cur_dir();
	else
		cur_dir = ft_strdup(get_envp(*envp, "PWD"));
	if (cmd[i] == NULL)
		cd_change_env(envp, get_envp(*envp, "HOME"), cur_dir);
	else if (ft_strcmp(cmd[i], "-") == 0)
		cd_change_env(envp, get_envp(*envp, "OLDPWD"), cur_dir);
	else if (ft_strcmp(cmd[i], "..") == 0)
		cd_change_env(envp, cd_rmv_last_path(cur_dir), cur_dir);
	else
		cd_move(envp, cur_dir, cmd[i]);
	cd_clean_path(get_envp(*envp, "PWD"));
	free(cur_dir);
}
