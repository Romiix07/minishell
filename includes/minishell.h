/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:20:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/31 12:28:49 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

typedef struct s_string {
	char			*string;
	struct s_string	*prev;
	struct s_string	*next;
}	t_string;

typedef struct s_historic {
	struct s_string	*head;
	struct s_string	*tail;
}	t_hist;

typedef struct s_env {
	char			*name;
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_shell {
	char				**input;
	struct s_historic	*hist;
	struct s_env		*env;
	int					return_value;
}	t_shell;

char	**get_input(t_shell *shell);
char	**str_to_tab(char *s);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
int		ft_strlen_c(const char *s, char c);
int		ft_strlen_ischarset(const char *s, const char *charset);
int		ft_strlen_isncharset(const char *s, const char *charset);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_charset(char c, const char *charset);
void	*ft_calloc(void **ptr, int size);
char	*concatenate_str(char *s, char c);
char	*free_tab(char **tab, int limit);
char	*get_classic_word(char **ret, char *s, int *i, char *charset);
char	*get_quote(char **ret, char *s, int *i, char c);
char	*get_dollar(char **ret, char *s, int *i);
char	*get_same_char(char **ret, char *s, int *i, char c);
int		go_to_function(t_shell *shell);
t_env	*init_env(char **env);
t_env	*ft_envnew(char *s);
int		free_env(t_env *env);
char	*init_env_name(char *s);
char	*init_env_var(char *s);
int		print_env(t_env *env);
void	*free_items(void **item_1, int size_1, void **item_2, int size_2);
char	**get_arg_tab(char **tab);
int		return_error(char *s);

int		ft_echo(char **arg, char *filename);

t_hist	*init_historic(void);
int		add_hist(t_hist *hist, char *s);
int		free_hist(t_hist *hist);

int		init_shell(t_shell **shell, char **env);
int		free_shell(t_shell **shell);

int		ft_export(char **input, t_env *env);
t_env	*get_env_var(char *s, t_env *env);

#endif
