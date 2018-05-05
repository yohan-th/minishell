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

int 	file_exist (char *filename)
{
	struct stat   buffer;
	return (stat (filename, &buffer) == 0);
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

char	*srch_envp(char **envp, char *var)
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
	free(tmp);
	return (ft_strchr(*envp, '=') + 1);
}

/*
** Recherche le bon path de cmd dans les differents path de env PATH
*/

char	*path_cmd(char *cmd, char **envp)
{
	char	*ret;
	char	**all_path;
	char	*real_path;
	int		i;

	all_path = ft_strsplit(srch_envp(envp, "PATH"), ':');
	ret = NULL;
	i = 0;
	while (all_path[i] != NULL)
	{
		ret = ft_strjoin_mltp(3, all_path[i++], "/", cmd);
		if (file_exist(ret))
			break ;
	}
	free_tab(all_path);
	return (ret);
}