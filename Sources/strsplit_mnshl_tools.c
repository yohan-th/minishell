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
