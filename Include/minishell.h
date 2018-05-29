/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 20:58:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 20:58:23 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# include "../Libft/Includes/libft.h"

char	*path_cmd(char *cmd, char **envp);
void	builtin_cd(char **cmd, char ***envp);
void	builtin_setenv(char ***envp, char *key, char *value);
void	builtin_unsetenv(char ***envp, char *key);
void	builtin_delenv(char ***envp, char *key);
char 	**rmv_key_env(char **envp, char *key);
void	builtin_env(char ***envp, char *key);
void	builtin_echo(char **cmd);
char	**strsplit_mnshl(char **str, char **envp);
void	mnshlt_error(char *type);

void	free_tab(char **tab);
char	*check_builtin(char **cmd, char ***envp);
char	*get_envp(char **envp, char *var);
char	*get_var(char *var_key);
char 	**ft_arrdup(char **arr);
void 	ft_strdelchar(char **str, char c);
char 	*get_cur_dir(void);
int 	ft_arrlen(char **arr);

/*
** Hard test
** <echo "$HOME"'$HOME'$HOME +$HOME>
** <echo "debut \" fin">
** <echo 'debut \' suite' fin'>
** se mettre dans un path qui contient un lien et <cd -L -L -P -L .>
** lancer minishell et <cd -> --> bash: cd: OLDPWD not set
** <mkdir test> && <chmod 000 test> && <cd test>
** <cd \./> && pwd
** cd folder1///./folder2/.// && pwd
*/

#endif
