NAME_ASM = asm
NAME_DIS = disasm
LIBFT_A = ./libft/libft.a
FLAGS = -g -Wall -Wextra -Werror
COMP = gcc -c -o

HEADERS_DIR = ./inc
HEADERS_LIST =	op.h \
				asm_op.h \
				asm.h \
				dis_asm.h

# ASM_H = -I ./inc/

OBJ_DIR =	./obj/
OBJ_DIS =	./obj_dis/

SRC_DIR =	./src/asm/
SRC_DIS =	./src/disassembler/

C_FILE =		cleaning.c \
				file_extension_utils.c \
				initialization.c asm.c \
				parsing_tokens.c \
				setting_code.c utils.c \
				exiting_with_positional_error.c \
				exiting_with_non_positional_error.c \
				handling_labels.c \
				instruction_args_utils.c \
				parsing.c \
				parsing_utils.c \
				setting_commands.c \
				writing.c \
				reading.c \
				dumping_to_stdout.c \
				handling_args.c

C_DIS_FILE =	ft_dis_command.c \
				ft_dis_header.c \
				ft_error.c \
				ft_init_data.c \
				main_disasm.c

C_FIND =		$(addprefix $(SRC_DIR), $(C_FILE))
C_DIS_FIND =	$(addprefix $(SRC_DIS), $(C_DIS_FILE))

O_FILE =		$(C_FILE:%.c=%.o)
O_DIS_FILE =	$(C_DIS_FILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(O_FILE))
OBJ_D =		$(addprefix $(OBJ_DIS), $(O_DIS_FILE))

HEADERS = $(addprefix $(HEADERS_DIR)/,$(HEADERS_LIST))

all: $(NAME_ASM) $(NAME_DIS)

$(NAME_ASM): $(OBJ_DIR) $(OBJ) $(HEADERS)
	@make -C ./libft
	@gcc $(LIBFT_A) $(OBJ) -I$(HEADERS_DIR) -o $(NAME_ASM)
	@echo $(NAME_ASM) create

$(NAME_DIS): $(OBJ_DIS) $(OBJ_D) $(HEADERS)
			@gcc $(LIBFT_A) $(OBJ_D) -I$(HEADERS_DIR) -o $(NAME_DIS)
			@echo $(NAME_DIS) create

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@echo Create: $(@:obj/%=%)
			@gcc $(FLAGS) -I $(HEADERS_DIR) -c $< -o $@

$(OBJ_DIS):
			@mkdir -p $(OBJ_DIS)

$(OBJ_DIS)%.o: $(SRC_DIS)%.c
			@echo Create: $(@:obj_dis/%=%)
			@gcc $(FLAGS)  -I $(HEADERS_DIR) -c $< -o $@

clean:
		@rm -rf obj*
		@make -C libft/ clean

fclean: clean
		@rm -rf ./$(NAME_ASM) ./$(NAME_DIS)
		@make -C libft/ fclean

re: fclean all

.PHONY: all clean flcean re