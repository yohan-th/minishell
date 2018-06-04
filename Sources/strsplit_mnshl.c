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
		return (i - 1);
	else
		return (i + ft_strlen(var));
}

int		mnshl_argsub_tilde(char **arg, int i, char **envp)
{
	char	*tmp;
	char	*var;

	tmp = *arg + i;
	tmp[0] = '\0';
	var = get_envp(envp, "HOME");
	if (var == NULL)
		tmp = ft_strjoin_mltp(2, *arg, *arg + i + 1);
	else
		tmp = ft_strjoin_mltp(3, *arg, var, *arg + i + 1);
	free(*arg);
	*arg = ft_strdup(tmp);
	free(tmp);
	if (var == NULL)
		return (i - 1);
	else
		return (i + ft_strlen(var));
}

int 	mnshl_argsub(char **arg, int i, char **envp, char end_arg)
{
	if ((*arg)[i] == '$' && end_arg != '\'')
	{
		return (mnshl_argsub_env(arg, i, envp));
	}
	else if ((*arg)[i] == '~' && end_arg == ' ' && i == 0 && (*arg)[i + 1] == '\0')
		return (mnshl_argsub_tilde(arg, i, envp));
	else
		return (i + 1);
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
	int		i;
	char	*strdelchar;

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
		else if (arg[i] == '$' || arg[i] == '~')
			i = mnshl_argsub(&arg, i, envp, end_arg);
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
	char	quote;
	char	*arg;

	i = 0;
	while (ft_strchr("\t ", (*str)[i]))
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
	char	*free_str;

	nb_arg = get_nbr_arg(*str);
	cmd = (char **)malloc(sizeof(char *) * nb_arg + sizeof(char *));
	end_arg = 0;
	free_str = *str;
	i = 0;
	while (i < nb_arg)
		cmd[i++] = get_arg(str, envp);
	cmd[i] = NULL;
	if (nb_arg > 0)
		ft_strdel(&free_str);
	return (cmd);
}
