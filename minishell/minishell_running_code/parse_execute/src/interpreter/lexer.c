#include "interpreter.h"

static void remove_not_lexeme(char **line)
{
    while (**line && ft_strchr(" \n\t", **line))
        (*line)++;
}

static t_token *get_special_token(t_token *token, char **line, int *cur_option)
{
	token->value = get_special_item(line, cur_option);
	if (*cur_option & CUR_REDIRECT)
		token->type = CUR_REDIRECT;
	else if (*cur_option & CUR_PIPE)
		token->type = CUR_PIPE;
	return (token);
}

static t_token *get_plain_token(t_token *token, char **line, int *cur_option)
{
	token->value = get_plain_item(line, cur_option);
	if (cur_option & CUR_REDIRECT) // 리다이렉트인 경우
	{
		token->type = CUR_AFTER_FD;
		*cur_option &= CUR_CMD;
	}
	else if (*cur_option & CUR_CMD) // 이미 CMD가 있는경우
		token->type = CUR_ARG;
	else
	{
		*cur_option |= CUR_CMD;
		token->type = CUR_CMD;
	}
	return (token);
}

static t_list	*scan_line(char **line, int *cur_option)
{
	t_list *ret;
	t_token *token;

	while (*line)
	{
		remove_not_lexeme(&line)
		token = (t_token *)malloc(sizeof(t_token));
		if (token == NULL)
		{
			exit(1);
			return (MALLOC_ERROR);
		}
		if (ft_strchr("|<>", **line))
			token = get_special_token(token, line, cur_option);
		else
			token = get_plain_token(token, line, cur_option);
		ret = ft_lstnew(token);
 		ret = ret->next;
	}
	return ret; // 이거 어느위치인지 체크 구조체 원포인터일때 링크는 넘어갈까 안넘어갈까
}
/*
static t_lexer *init_lexer(char *line, t_list *tokens)
{
	t_lexer *ret;

	ret = (t_lexer *)malloc(sizeof(t_lexer));
	if (ret == NULL)
	{
		exit(1);
		return (MALLOC_ERROR);
	}
	ret->line = line;
	ret->tokens = tokens;
	ret->start = -1;
	ret->end = -1;

	return (ret);
}
*/
t_lexer *lexical_analyzer(char *line)
{
	t_list		*tokens;
	char		*save_line;
	int			cur_option;

	save_line = line;
	cur_option = CUR_NONE;
	tokens = scan_line(&line, &cur_option);
	return (init_lexer(save_line, tokens));
}

    //scanning
    //lexeme 구분
    //token 포인터 배열 메모리할당
    //tokenizing


/*
int 	set_quote_option(char *line)
{
	int quote_opt;

	quote_opt = SET_NONE;
	while (*line)
	{
		if (*line == "'")
			quote_opt ^= SET_QUOTE;
		else if (*line == '"')
			quote_opt ^= SET_DQUOTE;

		line++;
	}

}이거 나중에 체크하는게 나을듯
*/