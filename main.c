#include "shell.h"


int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
		{
			writePrompt(void);
		}

… /* The code continues below */
	}
	return(0);
}
