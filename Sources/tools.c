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
** Retourne le path absolu.
** On commence avec 8 octet puis on monte puissance 2
*/

char	*get_cur_dir(void)
{
	size_t	buf;
	char	*dir;

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
	int	jump;
	int	i;

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

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * ft_arrlen(arr) + sizeof(char *));
	i = 0;
	while (arr[i] != NULL)
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab != NULL && tab[i] != NULL)
		free(tab[i++]);
	if (tab != NULL)
		free(tab);
}
