#include "libft.h"
#include <stdbool.h>

bool	ft_char(char c, const char *str)
{
	while (*str)
	{
		if (*str++ != c)
			return (false);
	}
	return (true);
}