/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   strsplit_mnshl.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 18:53:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 18:53:39 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

/*
** {while (*(str - 1) == '\\' && *str != '\'')} permet de sauter les
** cotes {`"} echappées sauf {'} qui ne peut pas etre echappé (que sur la fin)
** /!\ le cas où la commande est pas cote {"echo"} et que la lecture de {str-1}
** est protege --> segfault ou {str - 1} == '\' (improbable) --> value false
**
** cas non gerés :
** echo 1'2
** echo `ls -l`
** echo test' && echo test'
** en regle general les cotes necessitent d'etre entourées d'espace
*/

int		get_nbr_arg(char *str)
{
	int nb_arg;

	nb_arg = 0;
	while (*str)
	{
		if (ft_strchr("'`\"", *str) && *(str - 1) != '\\')
		{
			nb_arg += 1;
			if (!(ft_strchr(str + 1, *str)))
				mnshlt_error("quote missing");
			str = ft_strchr(str + 1, *str);
			while (*(str - 1) == '\\' && *str != '\'')
				str = ft_strchr(str + 1, *str);
			while (*str && *(str + 1) != ' ')
				str++;
		}
		else if (*str != ' ')
		{
			nb_arg += 1;
			while (*str && *str != ' ')
				str++;
		}
		str++;
	}
	return (nb_arg);
}

/*
** Permet de supprimer les {\} et de transformer les var de env uniquement
** si {end_arg} est double cote ou back cote {`"} ou sans rien
** echo "$HOME" '$HOME' `$HOME` $HOME
** --> /Users/ythollet $HOME /Users/ythollet /Users/ythollet
*/

char	*revised_arg(char *arg, char end_arg, char **envp)
{
	char *tmp;
	char *var;

	while (ft_strchr(arg, '\\'))
		ft_strdelchar(&arg, '\\');
	if (ft_strchr(arg, '$') && ft_strchr("\"` ", end_arg))
	{
		tmp = ft_strchr(arg, '$');
		var = ft_strsub(tmp, 1, (size_t)ft_strlen(tmp + 1));
		tmp[0] = '\0';
		tmp = get_envp(envp, var);
		free(var);
		if (tmp == NULL)
			return (ft_strnew(1));
		else
		{
			var = ft_strjoin(arg, tmp);
			free(arg);
			return (var);
		}
	}
	return (arg);
}

char	*get_arg(char **str, char end_arg, char **envp)
{
	int		len_arg;
	char	*ret;

	len_arg = 0;
	while (**str && **str != end_arg)
	{
		len_arg++;
		(*str)++;
		if (**str == end_arg && *((*str) - 1) == '\\')
		{
			(*str)++;
			len_arg++;
		}
	}
	ret = ft_strsub((*str) - len_arg, 0, len_arg);
	if (ft_strchr("'`\"", **str))
		(*str)++;
	ret = revised_arg(ret, end_arg, envp);
	return (ret);
}

/*
** Le {*str} dans le while est une securité si nb_arg = {get_nbr_arg} est faux
*/

char	**strsplit_mnshl(char *str, char **envp)
{
	char	**cmd;
	int		nb_arg;
	char	end_arg;
	int		i;

	nb_arg = get_nbr_arg(str);
	cmd = (char **)malloc(sizeof(char *) * nb_arg + 1);
	end_arg = 0;
	i = 0;
	while (i < nb_arg && *str != 0)
	{
		if (*str == '\'' || *str == '"' || *str == '`')
			end_arg = *str++;
		else if (*str != ' ')
			end_arg = ' ';
		else
			end_arg = 0;
		if (end_arg)
			cmd[i++] = get_arg(&str, end_arg, envp);
		else
			str++;
	}
	cmd[i] = NULL;
	return (cmd);
}
