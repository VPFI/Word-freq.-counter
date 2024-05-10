/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:23:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/10 19:34:17 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef hash_H
# define hash_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_entry
{
	char	*key;
	int		value;	
}			t_entry;

typedef struct s_dict
{
	t_entry	*entries;
	int		current;
	int		cap;	
}			t_dict;

char *ft_tolower_str(char *s);

unsigned int	hash(char *word);

t_entry	create_entry(char *word, int freq);

void	print_top(t_dict *dict, int top_count, int col_num);
void	print_dict(t_dict *dict, int col_num);
void    print_your_words(t_dict *dict, char **word, int argc);
void	free_entries(t_entry *entries, int n);
void	expand_dict(t_dict *dict, int *col_num);
void	add_word(char *word, t_dict *dict, int *col_num);
void	proces_line(char *line, t_dict *dict, int *col_num);

#endif