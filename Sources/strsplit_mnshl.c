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

char 	define_quote_bgn(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '"')
		return ('"');
	else
		return (' ');
}

/*
** Déplace str jusqu'a la fin de l'arg et retourn sa len
*/

int		nxt_arg(char **str, int i, char quote)
{
	while ((*str)[i] && (*str)[i] != quote)
	{
		i++;
		if ((*str)[i] && (*str)[i - 1] == '\\' && (*str)[i] == quote &&
			quote != '\'')
			i++;
		if (quote == ' ' && ft_strchr("'\"", (*str)[i]))
			quote = (*str)[i++];
		if (ft_strchr("'\"", quote) && (*str)[i] == quote &&
			!ft_strchr("\0 ", (*str)[i + 1]))
		{
			quote = ' ';
			i++;
		}
	}
	return (i);
}

int		get_nbr_arg(char *str)
{
	int		nb_arg;
	int		i;
	char 	quote;

	nb_arg = 0;
	i = 0;
	while (str[i])
	{
		while (ft_strchr("\t ",str[i]))
			i++;
		if (!str[i])
			break ;
		else
			nb_arg += 1;
		quote = define_quote_bgn(str[i]);
		if (ft_strchr("'\"", quote))
			i++;
		i = nxt_arg(&str, i, quote);
	}
	return (nb_arg);
}

int		mnshl_argsub_env(char **arg, int i, char **envp)
{
	char	*tmp;
	char 	*var;
	size_t	len;

	tmp = *arg + i;
	len = 1;
	while (tmp[len] && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
		len++;
	if (len == 1)
		return (i + 1);
	tmp[0] = '\0';
	tmp = ft_strsub(tmp, 1, len - 1);
	var = get_envp(envp, tmp);
	free(tmp);
	if (var == NULL)
		tmp = ft_strjoin_mltp(2, *arg, *arg + i + len);
	else
		tmp = ft_strjoin_mltp(3, *arg, var, *arg + i + len);
	free(*arg);
	*arg = ft_strdup(tmp);
	free(tmp);
	if (var == NULL)
		return (i);
	else
		return (i + ft_strlen(var));
}

/*
** Permet de supprimer les {\} et de transformer les var de env uniquement
** si {end_arg} est double cote ou back cote {"} ou sans rien
** echo "$HOME" '$HOME' $HOME
** --> /Users/ythollet $HOME /Users/ythollet
** /!\ le cas d'un {\} en fin de ligne n'est pas gere
*/

char	*mnshl_quotesub(char *arg, char end_arg, char **envp)
{
	int 	i;
	char 	*strdelchar;

	i = 0;
	while (arg[i])
	{
		strdelchar = arg + i;
		if (end_arg == ' ' && arg[i] == '\\')
			ft_strdelchar(&strdelchar, arg[i]);
		else if (end_arg == ' ' && ft_strchr("'\"", arg[i]))
			ft_strdelchar(&strdelchar, end_arg = arg[i]);
		else if (arg[i] == '\\' && arg[i + 1] == end_arg && end_arg != '\'')
			ft_strdelchar(&strdelchar, arg[i]);
		else if (arg[i] == '\\' && arg[i + 1] != end_arg && end_arg != '\'')
			ft_strdelchar(&strdelchar, arg[i]);
		else if (arg[i] == '$' && end_arg != '\'')
			i = mnshl_argsub_env(&arg, i, envp) - 1;
		else if (end_arg != ' ' && arg[i] == end_arg)
		{
			ft_strdelchar(&strdelchar, end_arg);
			end_arg = ' ';
		}
		i++;
	}
	return (arg);
}

char	*get_arg(char **str, char **envp)
{
	int		bgn_arg;
	int		i;
	char 	quote;
	char 	*arg;

	i = 0;
	while (ft_strchr("\t ",(*str)[i]))
		i++;
	bgn_arg = i;
	quote = define_quote_bgn((*str)[i]);
	if (ft_strchr("'\"", quote))
		i++;
	i = nxt_arg(str, i, quote);
	arg = ft_strsub(*str, bgn_arg, i - bgn_arg);
	*str = *str + i;
	arg = mnshl_quotesub(arg, ' ', envp);
	return (arg);
}

/*
** Le {*str} dans le while est une securité si nb_arg = {get_nbr_arg} est faux
*/

char	**strsplit_mnshl(char **str, char **envp)
{
	char	**cmd;
	int		nb_arg;
	char	end_arg;
	int		i;
	char 	*free_str;

	nb_arg = get_nbr_arg(*str);
	cmd = (char **)malloc(sizeof(char *) * nb_arg + sizeof(char *));
	end_arg = 0;
	free_str = *str;
	i = 0;
	while (i < nb_arg)
		cmd[i++] = get_arg(str, envp);
	cmd[i] = NULL;
	ft_strdel(&free_str);
	return (cmd);
}
