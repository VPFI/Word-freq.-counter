/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:18:57 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/08 20:10:51 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void	print_top(t_dict *dict)
{
	int	i;
	int	j;
	int	max;
	int	top_count;

	i = 0;
	j = 0;
	max = 100;
	top_count = 10;
	printf("|-----------------------------------------------|\n");
	printf("    		    TOP %i\n", top_count);
	while(i < top_count && max > 0)
	{
		j = 0;
		while (j < dict->cap && i < top_count)
		{
			if (dict->entries[j].key && (dict->entries[j].value) == max)
			{
				printf("        (%03i) | %-12s -----> %02i\n", j, dict->entries[j].key, dict->entries[j].value);
				i++;	
			}
			j++;
		}
		max--;
	}
}
void	print_dict(t_dict *dict)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("|====================[-+-]======================|\n");
	printf("     Entry cap --> %i | %i <-- Current words\n", dict->cap, dict->current);
	printf("|-----------------------------------------------|\n");
	while(i < dict->current)
	{
		if (dict->entries[j].key)
		{
			printf("        (%03i) | %-12s -----> %i\n", j, dict->entries[j].key, dict->entries[j].value);
			i++;
		}
		j++;
	}
	printf("|====================[---]======================|\n");
}
char *ft_tolower_str(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
	return (s);
}
unsigned int	hash(char *word)
{
	unsigned int res;
	int		i;
	char	c;

	res = 0;
	i = 0;
	while (word[i])
	{
		c = word[i];
		res += res * 13 + c; 
		i++;
	}
	return res;	
}
t_entry	create_entry(char *word)
{
	t_entry	ntry;

	ntry.key = ft_strdup(word);
	ntry.value = 1;
	return (ntry);
}
void	add_word(char *word, t_dict *dict, int *col_num)
{
	int		i;
	int		hash_index;

	i = 0;
	hash_index = hash(word) % dict->cap;
	printf("hash: %i --- hash_index: %i\n", hash(word), hash_index);
	if ((dict->current) > 0)
	{
		if ((dict->entries[hash_index].key) && ft_strncmp((dict->entries[hash_index].key), word, ft_strlen(word) - 1))
		{
			printf(" !! Collisao on hash_index: %i\n", hash_index);
			*col_num = *col_num + 1; //pq col_num++ no va? lo sabremos en el nuevo capitulo de Eralonso
			while ((dict->entries[hash_index].key) && ft_strncmp((dict->entries[hash_index].key), word, ft_strlen(word) - 1))
				hash_index++;
			printf(" !! New index after collisao: %i\n", hash_index);
			
		}
		if (!(dict->entries[hash_index].key))
		{
			dict->entries[hash_index] = create_entry(word);
			dict->current++;
		}
		else
			dict->entries[hash_index].value++;
	}
	else
	{
		dict->entries[hash_index] = create_entry(word);
		dict->current++;
	}
	printf("---------------------------------------------------\n");
}
void	proces_line(char *line, t_dict *dict, int *col_num)
{
	char	**list_words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	list_words = ft_split(line, ' ');
	free(line);
	while (list_words[i])
	{
		if ((list_words[i][ft_strlen(list_words[i]) - 1]) == '\n')
			list_words[i][ft_strlen(list_words[i]) - 1] = '\0';	
		if (!ft_isalpha(list_words[i][ft_strlen(list_words[i]) - 1]))
			list_words[i][ft_strlen(list_words[i]) - 1] = '\0';
		list_words[i] = ft_tolower_str(list_words[i]);
		i++;
	}
	i = 0;
	while (list_words[i])
	{
		printf("Word: %s\n", list_words[i]);
		add_word((list_words[i]), dict, col_num);
		i++;
	}
	free(list_words);
}

int main(int argc, char **argv)
{
	int     fd;
	int		*col_num;
	char    *line;
	char    *word;
	t_dict	*dict;

	fd = open(argv[1], O_RDONLY);
	col_num = (int *)malloc(sizeof(int) * 1);
	*col_num = 0;
	dict = (t_dict *)malloc(sizeof(t_dict) * 1);
	dict->cap = 200;
	dict->entries = (t_entry *)malloc(sizeof(t_entry) * dict->cap);
	dict->current = 0;
	print_dict(dict);
	while ((line = get_next_line(fd)))
	{
		//printf("NEW line ------ %s\n", line);
		if (line[0] != '\n')
			proces_line(line, dict, col_num);
	}
	print_dict(dict);
	printf("         Final number of collisions: %03i\n", *col_num);
	print_top(dict);
}
// cc hash_main.c hash.h libft/libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c