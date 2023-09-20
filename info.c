#include "shell.h"

/**
 * clsinfo - initializes info_t struct
 * @info: struct address
 */
void clsinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * putinfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void putinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strspt(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _duplstr(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		_repl_alias(info);
		_repl_vars(info);
	}
}

/**
 * freeinfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeinfo(info_t *info, int all)
{
	strfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_out_list(&(info->env));
		if (info->history)
			free_out_list(&(info->history));
		if (info->alias)
			free_out_list(&(info->alias));
		strfree(info->environ);
			info->environ = NULL;
		ptrfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
