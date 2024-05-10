/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:18:57 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/10 20:53:36 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void    print_top(t_dict *dict, int top_count, int col_num)
{
	int i;
	int j;
	int max;

	i = 0;
	j = 0;
	max = 5000;
	printf("\n");
	printf("|====================[-++-]======================|\n");
	printf("    Entry cap --> %i || %i <-- Current words\n", dict->cap, dict->current);
	printf("          Final number of collisions: %03i\n", col_num);
	printf("|------------------------------------------------|\n");
	printf("                     TOP %i\n", top_count);
	printf("|------------------------------------------------|\n");
	while(i < top_count && max > 0)
	{
		j = 0;
		while (j < dict->cap && i < top_count)
		{
			if (dict->entries[j].key && (dict->entries[j].value) == max)
			{
				printf("        (%04i) | %-12s -----> %02i\n", j, dict->entries[j].key, dict->entries[j].value);
				i++;    
			}
			j++;
		}
		max--;
	}
	printf("|------------------------------------------------|\n");
}
void    print_your_words(t_dict *dict, char **words, int argc)
{
	int i;
	int j;
	int	printed;

	i = 0;
	j = 0;
	printed = 0;
	printf(" 	   -- Selected Words Frequency -- \n");
	printf("|##################################################|\n");
	if (!ft_isalpha(words[argc - 1][0]))
		argc--;
	while(i < argc)
	{
		j = 0;
		printed = 0;
		while (j < dict->cap)
		{	
			if (dict->entries[j].key && !ft_strcmp(dict->entries[j].key, ft_tolower_str(words[i])))
			{
				printf("        (%04i) | %-12s -----> %02i\n", j, dict->entries[j].key, dict->entries[j].value);
				printed = 1;
				//i++;
			}
			j++;
		}
		if (!printed)
			printf("        (%04i) | %-12s -----> %03i -Not Found- \n", 0, words[i], 0);
		i++;
	}
	printf("|##################################################|\n");
}
void    print_dict(t_dict *dict, int col_num)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("|====================[-+-]======================|\n");
	printf("     Entry cap --> %i | %i <-- Current words\n", dict->cap, dict->current);
	printf("         Final number of collisions: %03i\n", col_num);
	printf("|-----------------------------------------------|\n");
	while(i < dict->current)
	{
		if (dict->entries[j].key)
		{
			printf("        (%04i) | %-12s -----> %02i\n", j, dict->entries[j].key, dict->entries[j].value);
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

unsigned int    hash(char *word)
{
	unsigned int res;
	int     i;
	char    c;

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
t_entry create_entry(char *word, int freq)
{
	t_entry ntry;

	ntry.key = ft_strdup(word);
	ntry.value = freq;
	return (ntry);
}
void    re_addword(t_entry *temp, char *word, int freq, int cap, int *col_num)
{
	int     hash_index;

	hash_index = hash(word) % cap;
	//printf("hash: %i --- hash_index: %i\n", hash(word), hash_index);
	if ((temp[hash_index].key) && ft_strcmp((temp[hash_index].key), word))
	{
		//printf(" !! Collisao on hash_index: %i\n", hash_index);
		*col_num = *col_num + 1; //pq col_num++ no va? lo sabremos en el nuevo capitulo de Eralonso
		while ((temp[hash_index].key) && ft_strcmp((temp[hash_index].key), word))
			hash_index++;
		//printf(" !! New index after collisao: %i\n", hash_index);
	}
	if (!(temp[hash_index].key))
	{
		temp[hash_index] = create_entry(word, freq);
	}
}
void    free_entries(t_entry *entries, int n)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < n) //entries[i].key --> t_entry *entries
	{
		if (entries[j].key)
		{
			free(entries[j].key);
			i++;
		}
		j++;
	}
	free(entries);
}
void    expand_dict(t_dict *dict, int *col_num)
{
	t_entry *temp;
	int     i;
	int     j;
	int     hash_index;

	i = 0;
	j = 0;
	dict->cap = dict->cap * 2;
	temp =  (t_entry *)malloc(sizeof(t_entry) * dict->cap);
	while (i < dict->current)
	{
		if (dict->entries[j].key)
		{
			re_addword(temp, dict->entries[j].key, dict->entries[j].value, dict->cap, col_num);
			i++;
			//printf("Word from dict: %s --> %i\n", dict->entries[j].key, dict->entries[j].value);
		}
		j++;
	}
	free_entries(dict->entries, dict->current);
	dict->entries = temp;
	//free(temp);
}
void    add_word(char *word, t_dict *dict, int *col_num)
{
	int     hash_index;

	hash_index = hash(word) % dict->cap;
	//printf("hash: %i --- hash_index: %i\n", hash(word), hash_index);
	if ((dict->current) > 0)
	{
		if ((dict->entries[hash_index].key) && ft_strcmp((dict->entries[hash_index].key), word))
		{
			//printf(" !! Collisao on hash_index: %i\n", hash_index);
			*col_num = *col_num + 1; //pq col_num++ no va? lo sabremos en el nuevo capitulo de Eralonso
			while ((dict->entries[hash_index].key) && ft_strcmp((dict->entries[hash_index].key), word))
				hash_index++;
			//printf(" !! New index after collisao: %i\n", hash_index);
			
		}
		if (!(dict->entries[hash_index].key))
		{
			dict->entries[hash_index] = create_entry(word, 1);
			dict->current++;
			if (dict->current == (dict->cap * 3 / 4))
				expand_dict(dict, col_num);
		}
		else
			dict->entries[hash_index].value++;
	}
	else
	{
		dict->entries[hash_index] = create_entry(word, 1);
		dict->current++;
	}
	//printf("---------------------------------------------------\n");
}
void    proces_line(char *line, t_dict *dict, int *col_num)
{
	char    **list_words;
	int     i;
	int     j;

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
		//printf("Word: %s first C: %i\n", list_words[i], ft_isalpha(list_words[i][0]));
		if (ft_isalpha(list_words[i][0]))
			add_word((list_words[i]), dict, col_num);
		free(list_words[i]);
		i++;
	}
	free(list_words[i]);
	free(list_words);
}

int main(int argc, char **argv)
{
	int     fd;
	int     *col_num;
	char    *line;
	char    *word;
	t_dict  *dict;

	if (argc < 2)
	{
		printf("Invalid arguments: remember --> text.file + Optional(words_to_find) + top_count\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	col_num = (int *)malloc(sizeof(int) * 1);
	*col_num = 0;
	dict = (t_dict *)malloc(sizeof(t_dict) * 1);
	dict->cap = 100;
	dict->entries = (t_entry *)malloc(sizeof(t_entry) * dict->cap);
	dict->current = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\n')
			proces_line(line, dict, col_num);
	}
	//print_dict(dict, *col_num);
	if (ft_atoi(argv[argc - 1]))
		print_top(dict, ft_atoi(argv[argc - 1]), *col_num);
	else
		print_top(dict, 10, *col_num);
	if (argc > 3)
		print_your_words(dict, argv + 2, argc - 2);
	free(col_num);
	free_entries(dict->entries, dict->current);
	free(dict);
}
// cc hash_main.c hash.h libft/libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
// ./a.out test.txt . . . .