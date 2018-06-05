/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   strsplit_mnshl2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 20:27:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/29 20:27:35 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

int		mnshl_argsub_env(char **arg, int i, char **envp)
{
	char	*tmp;
	char	*var;
	size_t	len;

	tmp = *arg + i;
	len = 1;
	while (tmp[len] && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
		len++;
	if (len == 1)
		return (i);
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
		return (i - 1);
	else
		return (i + ft_strlen(var) - 1);
}

int		get_nbr_arg(char *str)
{
	int		nb_arg;
	int		i;
	char	quote;

	nb_arg = 0;
	i = 0;
	while (str && str[i])
	{
		while (ft_strchr("\t ", str[i]))
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

char	define_quote_bgn(char c)
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
