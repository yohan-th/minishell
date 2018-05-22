/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 16:05:47 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/07 16:05:47 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	builtin_delenv(char ***envp, char *key)
{
	int		i;
	char	*env_key;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		env_key = get_var((*envp)[i]);
		if (ft_strcmp(key, env_key) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin(key, "=");
			break ;
		}
		i++;
	}
}

void	builtin_setenv(char ***envp, char *key, char *value)
{
	int		i;
	char	*env_key;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		env_key = get_var((*envp)[i]);
		if (ft_strcmp(key, env_key) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin_mltp(3, key, "=", value);
			break ;
		}
		i++;
	}
}

void	builtin_env(char ***envp)
{
	int		i;

	i = 0;
	while ((*envp)[i] != NULL)
		ft_printf("%s\n", (*envp)[i++]);
}
