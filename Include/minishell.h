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
# include <sys/wait.h>

# include "../Libft/Includes/libft.h"

char	*path_cmd(char *cmd, char **envp);
void	builtin_cd(char **cmd, char ***envp);
void	builtin_setenv(char ***envp, char *key, char *value);
void	builtin_unsetenv(char ***envp, char *key);
void	builtin_delenv(char ***envp, char *key);
char	**rmv_key_env(char **envp, char *key);
void	builtin_env(char ***envp, char *key);
void	builtin_echo(char **cmd);
char	**strsplit_mnshl(char **str, char **envp);
int		mnshlt_error(char *type);

void	free_tab(char **tab);
char	*check_builtin(char **cmd, char ***envp);
char	*get_envp(char **envp, char *var);
char	*get_var(char *var_key);
char	**ft_arrdup(char **arr);
void	ft_strdelchar(char **str, char c);
char	*get_cur_dir(void);
int		ft_arrlen(char **arr);
char	define_quote_bgn(char c);
int		nxt_arg(char **str, int i, char quote);
int		get_nbr_arg(char *str);
int		mnshl_argsub_env(char **arg, int i, char **envp);

/*
** Hard test
** <  echo ~ ~test"  '$USER  \""+\\$USER+$US\ER+'  t"e$USER  \'>
** <echo "test>
** <echo test\>
** <echo 'test\'
** lancer minishell et <cd -> bash: cd: OLDPWD not set
** se mettre dans un path qui contient un lien et <cd -L -L -P -L .>
** puis <cd -L -P .>
** <mkdir test1> && <chmod 666 test1> && <cd test> --> Fail
** <mkdir test2> && <chmod 111 test2> && <cd test2> --> OK
** <cd \./> && pwd
** <cd ~/folder>
** cd folder1///./folder2/.// && pwd
** setenv PATH change_exec_directory && ls && /bin/ls
** unsetenv PATH && ls && /bin/ls
** cat * | ./minishell
** env -i ./minishell && cd - && unsetenv PATH && echo $HOME && cd ~
** ./minishell && unsetenv HOME && cd $random --> HOME not set
** ./minishell < "n'importe quel fichier"
*/

#endif
