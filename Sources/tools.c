/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/05 23:19:43 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/05 23:19:43 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

/*
** Si pas d'option P on corrige le PATH pour garder le link
*/

char	*keep_link_path(char *cur_dir, char *oldpwd)
{
	return (cur_dir);
}

/*
** Retourne le path absolu.
** On commence avec 8 octet puis on monte puissance 2
*/

char 	*get_cur_dir(void)
{
	size_t	buf;
	char 	*dir;

	buf = 8;
	dir = ft_strnew(buf);
	while (getcwd(dir, buf) == NULL)
	{
		free(dir);
		buf *= 2;
		dir = ft_strnew(buf);
	}
	return (dir);
}

/*
** Delete 1 fois {c} dans {str} si trouvé
*/

void	ft_strdelchar(char **str, char c)
{
	int		jump;
	char	*ret;
	int 	i;

	jump = 0;
	i = 0;
	while ((*str)[i - jump])
	{
		if ((*str)[i] == c)
			jump = 1;
		(*str)[i] = (*str)[i + jump];
		i++;
	}
	if (jump)
		(*str)[i] = '\0';
}

int 	ft_arrlen(const char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char 	**ft_arrdup(const char **arr)
{
	int		i;
	char 	**ret;

	ret = (char **)malloc(sizeof(char *) * ft_arrlen(arr) + 1);
	i = 0;
	while (arr[i] != NULL)
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	return (ret);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

/*
** Si on on rentre dans un builtin on retourne 0
** pour ne pas lancer de fork
*/
int 	check_builtin(char **cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd[0]) == 0)
		builtin_echo(cmd, envp);
	else if (ft_strcmp("cd", cmd[0]) == 0)
		builtin_cd(cmd, envp);
	else if (ft_strcmp("setenv", cmd[0]) == 0)
		;
	else if (ft_strcmp("unsetenv", cmd[0]) == 0)
		;
	else if (ft_strcmp("env", cmd[0]) == 0)
		builtin_env(envp);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		;
	else
		return (1);
	//write(1, "\n", 1);
	return (0);
}
