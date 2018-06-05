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

int		file_exist(char *filename)
{
	struct stat	buffer;

	return (stat(filename, &buffer) == 0);
}

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

/*
** Recherche le bon path de {cmd} dans les differents path de {envp PATH}
** si non trouvé ou PATH inexistant on retourne {cmd}
*/

char	*path_cmd(char *cmd, char **envp)
{
	char	*ret;
	char	**all_path;
	int		i;

	if (get_envp(envp, "PATH"))
		all_path = ft_strsplit(get_envp(envp, "PATH"), ':');
	else
		all_path = NULL;
	ret = NULL;
	i = 0;
	while (all_path != NULL && all_path[i] != NULL)
	{
		ret = ft_strjoin_mltp(3, all_path[i++], "/", cmd);
		if (access(ret, X_OK) == 0)
			break ;
		ft_strdel(&ret);
	}
	free_tab(all_path);
	if (ret && access(ret, X_OK) == 0)
		return (ret);
	free(ret);
	if (cmd && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
		return (ft_strdup("invalide commande"));
}
