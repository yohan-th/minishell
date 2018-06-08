/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/05 23:20:46 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/05 23:20:46 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_var(char *var_key)
{
	int		i;
	char	*ret;

	i = 0;
	while (var_key[i] != '=')
		i++;
	ret = ft_strnew(i);
	ft_strncpy(ret, var_key, i);
	return (ret);
}

char	*get_envp(char **envp, char *var)
{
	char *tmp;

	tmp = NULL;
	while (*envp != NULL)
	{
		tmp = get_var(*envp);
		if (ft_strcmp(tmp, var) == 0)
			break ;
		free(tmp);
		envp++;
	}
	if (*envp != NULL)
		free(tmp);
	else
		return (NULL);
	return (ft_strchr(*envp, '=') + 1);
}

int		is_directory(char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

char	*check_cmd(char *cmd)
{
	if (cmd && is_directory(cmd))
		return (ft_strdup("cmd is directory"));
	else
		return (ft_strdup("command not found"));
}

/*
** Recherche le bon path de {cmd} dans les differents path de {envp PATH}
** si non trouvé ou PATH inexistant on retourne {cmd}
*/

char	*path_cmd(char *cmd, char **envp)
{
	char	*ret;
	char	**all_path;
	int		i;

	if (cmd == NULL)
		return (NULL);
	all_path = ft_strsplit(get_envp(envp, "PATH"), ':');
	ret = NULL;
	i = 0;
	while (get_envp(envp, "PATH") && all_path[i] != NULL &&
			!ft_strchr(cmd, '/'))
	{
		ret = ft_strjoin_mltp(3, all_path[i++], "/", cmd);
		if (access(ret, X_OK) != -1)
			break ;
		ft_strdel(&ret);
	}
	free_tab(all_path);
	if ((ret && access(ret, X_OK) != -1))
		return (ret);
	else if (!is_directory(cmd) && access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	return (check_cmd(cmd));
}
