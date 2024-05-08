/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:23:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/07 18:41:49 by vperez-f         ###   ########.fr       */
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

#endif