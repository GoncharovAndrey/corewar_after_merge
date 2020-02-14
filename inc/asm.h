/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoyette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:27:17 by jgoyette          #+#    #+#             */
/*   Updated: 2020/02/02 15:39:17 by jgoyette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"
# include "asm_op.h"

//# define NOPS						10
# define NO_FLAG					0
# define FLAG_A						1
# define NO_BYTES					0
# define PRINT_BYTES				1
# define ERROR_MALLOC               "Can't allocate memory"
# define ERROR_NO_NAME_COMMAND      "Champion name command is missing"
# define ERROR_NO_COMMENT_COMMAND   "Champion comment command is missing"
# define ERROR_NAME_LENGTH          "Champion name too long"
# define ERROR_COMMENT_LENGTH       "Champion comment too long"
# define ERROR_NO_EXEC_CODE			"Champion exec code is missing"
# define ERROR_READ_FILE            "Can't read source file"
# define ERROR_NO_NEWLINE           "No newline at the end of input"

typedef enum		e_type
{
	ENDLINE,
	COMMAND_COMMENT,
	COMMAND_NAME,
	STRING,
	SEPARATOR,
	INSTRUCTION,
	LABEL,
	REGISTER,
	DIRECT_LABEL,
	INDIRECT_LABEL,
	DIRECT_NUM,
	INDIRECT_NUM,
	ARGS_TYPES,
}					t_type;

typedef struct		s_token
{
	char			*content;
	int				value;
	t_type			type;
	int				size;
	int				pos;
	int				row;
	int				col;
	struct s_token	*next;
}					t_token;

typedef struct		s_data
{
	int				fd;
	unsigned int	row;
	unsigned int	col;
	unsigned int	champion_code_size;
	char			*filename;
	char			*line;
	char			*buff_line;
	char			*content;
	char			*champion_name;
	char			*champion_comment;
	char			*champion_code;
	t_token			*tokens;
	t_token			*curr_token;
	t_token			*labels;
	t_token			*start_code_token;
}					t_data;

t_data				*ft_init_data(char *filename);
t_token				*ft_init_token(t_data *data, char *content, int start,
															t_type type);
t_token				*ft_init_label(t_data *data, char *content, int pos);
void				ft_clean_data(t_data *data);

int					ft_read_next_line(t_data *data, const int fd, char **line);
void				ft_read_till_quote(t_data *data);
void				ft_write_to_file(t_data *data);
void				ft_dump_to_stdout(t_data *data);

void				ft_parse_file(t_data *data);
void				ft_parse_command(t_data *data, char *line);
void				ft_parse_string(t_data *data);
void				ft_parse_alpha(t_data *data, char *line);
void				ft_parse_direct(t_data *data, char *line);
void				ft_parse_num(t_data *data, char *line);

void				ft_handle_ignorable_label(t_data *data);
void				ft_handle_replaceable_label(t_data *data, t_op *op);
void				ft_set_label_values(t_data *data);
void				ft_handle_args_types_code(t_data *data, t_op *op);
void				ft_handle_args(t_data *data, t_op *op);
void				ft_set_commands(t_data *data);
void				ft_set_code(t_data *data);

int					ft_has_extension(const char *filename,
											const char *extension);
char				*ft_remove_extension(t_data *data,
						const char *filename, const char *extension);
int					ft_is_register(const char *str);
int					ft_is_whitespace(int c);
unsigned int		ft_get_insruction_line_size(t_token *token);
t_op				*ft_get_op(const char *name);
char				*ft_get_instruction_content(t_data *data, t_op *op);
int					ft_get_arg_type(t_type type);
unsigned int		ft_atoui_max(char *str);
void				ft_add_token(t_token **tokens, t_token *new_token);

void				ft_exit_with_error(t_data *data, char *error_msg);
void				ft_exit_with_lexical_error(t_data *data, int col);
void				ft_exit_with_syntax_error(t_data *data);
void				ft_exit_with_invalid_instruction_error(t_data *data);
void				ft_exit_with_arg_type_error(t_data *data, int arg_num,
									int arg_type, const char *instruction);
void				ft_exit_with_no_such_label_error(t_data *data,
															t_token *token);
void				ft_exit_with_io_error(t_data *data, const char *error_msg,
														const char *filename);
void				ft_exit_with_max_length_error(t_data *data,
											const char *error_msg, int length);

#endif
