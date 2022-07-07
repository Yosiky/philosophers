/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:23:37 by kostya            #+#    #+#             */
/*   Updated: 2022/05/20 15:01:00 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RED			0x00ff0000
# define GREEN			0x0000ff00
# define BLUE			0x000000ff
# define YELLOW			0x00ffff00
# define PURPLE			0x00ff00ff
# define CYAN			0x0000ffff
# define WHITE			0x00ffffff
# define BLACK			0x00000000

# define TERM_BLACK		"\x1b[1;90m"
# define TERM_RED		"\x1b[1;91m"
# define TERM_GREEN		"\x1b[1;92m"
# define TERM_YELLOW	"\x1b[1;93m"
# define TERM_BLUE		"\x1b[1;94m"
# define TERM_PURPLE	"\x1b[1;95m"
# define TERM_CYAN		"\x1b[1;96m"
# define TERM_WHITE		"\x1b[1;97m"
# define TERM_RESET		"\x1b[0m"

# define TEXT			TERM_WHITE
# define OK				TERM_GREEN
# define WARNING		TERM_YELLOW
# define ERROR			TERM_RED
# define INFO			TERM_BLUE
# define RESET			TERM_RESET

#endif
