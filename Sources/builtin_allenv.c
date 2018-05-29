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

char 	**rmv_key_env(char **envp, char *key)
{
	int		i;
	int 	y;
	char 	**ret;
	char 	*var;

	ret = (char **)malloc(sizeof(char *) * ft_arrlen(envp));
	i = 0;
	y = 0;
	while (y < ft_arrlen(envp))
	{
		var = get_var(envp[y]);
		if (ft_strcmp(var, key) == 0)
			y++;
		free(var);
		if (envp[y] != NULL)
			ret[i] = ft_strdup(envp[y]);
		i++;
		y++;
	}
	free_tab(envp);
	ret[i] = NULL;
	return (ret);
}

void	builtin_unsetenv(char ***envp, char *key)
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
			free(env_key);
			(*envp)[i] = ft_strjoin(key, "=");
			break ;
		}
		free(env_key);
		i++;
	}
}

char	**append_key_env(char **envp, char *key, char *value)
{
	int		i;
	char 	**ret;

	ret = (char **)malloc(sizeof(char *) * ft_arrlen(envp) + sizeof(char *) * 2);
	i = 0;
	while (i < ft_arrlen(envp))
	{
		ret[i] = ft_strdup(envp[i]);
		i++;
	}
	free_tab(envp);
	ret[i++] = ft_strjoin_mltp(3, key, "=", value);
	ret[i] = NULL;
	return (ret);
}

void	builtin_setenv(char ***envp, char *key, char *value)
{
	int		i;
	char	*env_key;
	BOOL	new_key;

	new_key = 1;
	i = 0;
	while ((*envp)[i] != NULL)
	{
		env_key = get_var((*envp)[i]);
		if (ft_strcmp(key, env_key) == 0)
		{
			new_key = 0;
			free(env_key);
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin_mltp(3, key, "=", value);
			break ;
		}
		free(env_key);
		i++;
	}
	if (new_key)
		*envp = append_key_env(*envp, key, value);
}

void	builtin_env(char ***envp, char *key)
{
	int		i;
	BOOL	found;

	i = 0;
	found = 0;
	while ((*envp)[i] != NULL)
	{
		if (key == NULL)
			printf("%s\n", (*envp)[i++]);
		else if (ft_strcmp(key, get_var((*envp)[i++])) == 0)
		{
			printf("%s\n", ft_strchr((*envp)[--i], '=') + 1);
			found = 1;
			break ;
		}
	}
	if (key != NULL && found == 0)
		printf("minishell: env: %s not found\n", key);
}
