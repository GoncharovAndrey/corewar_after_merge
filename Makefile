NAME_ASM = asm
NAME_DIS = disasm
NAME_CWS = corewar
LIBFT_A = ./libft/libft.a
FLAGS = -g -Wall -Wextra -Werror
COMP = gcc -c -o

HEADERS_DIR = ./inc/
HEADERS_LIST =	op.h \
				asm_op.h \
				asm.h \
				dis_asm.h \
				corewar.h

OBJ_DIR =	./obj/
OBJ_DIS =	./obj_dis/
OBJ_CWS = 	./obj_cws/

SRC_DIR =	./src/asm/
SRC_DIS =	./src/disassembler/
SRC_CWS =	./src/corewar/

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

C_CWS_FILE =	adder.c\
				vis_window.c \
				vis_process.c \
				vis_map.c \
				check_arguments_cycles.c \
				check_cycles_to_die.c \
				create_cars_and_sort.c \
				create_champions_check_flags.c \
				functions_to_put_take_from_memory.c \
				init_map_car_champ.c \
				list_operations.c \
				main.c \
				parse_champions_info.c \
				print_map_and_intro_end.c \
				put_code_and_indexes_to_map.c \
				add.c \
				aff.c \
				and.c \
				fork.c \
				ld.c \
				ldi.c \
				lfork.c \
				live.c \
				lld.c \
				lldi.c \
				or.c \
				st.c \
				sti.c \
				sub.c \
				xor.c \
				zjmp.c \
				trap.c \
				fastfork.c \
				check_flag_and_set_right_id.c \
				extra_func_for_sort.c \
				vis_extra_func.c

C_FIND =		$(addprefix $(SRC_DIR), $(C_FILE))
C_DIS_FIND =	$(addprefix $(SRC_DIS), $(C_DIS_FILE))
C_CWS_FIND =	$(addprefix $(SRC_CWS), $(C_CWS_FILE))

O_FILE =		$(C_FILE:%.c=%.o)
O_DIS_FILE =	$(C_DIS_FILE:%.c=%.o)
O_CWS_FILE =	$(C_CWS_FILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(O_FILE))
OBJ_D =		$(addprefix $(OBJ_DIS), $(O_DIS_FILE))
OBJ_C =		$(addprefix $(OBJ_CWS), $(O_CWS_FILE))

HEADERS = $(addprefix $(HEADERS_DIR)/,$(HEADERS_LIST))

all: $(NAME_ASM) $(NAME_DIS) $(NAME_CWS)

$(NAME_ASM): $(OBJ_DIR) $(OBJ) $(HEADERS)
	@make -C ./libft
	@gcc $(LIBFT_A) $(OBJ) -I$(HEADERS_DIR) -o $(NAME_ASM)
	@echo $(NAME_ASM) create

$(NAME_DIS): $(OBJ_DIS) $(OBJ_D) $(HEADERS)
			@gcc $(LIBFT_A) $(OBJ_D) -I$(HEADERS_DIR) -o $(NAME_DIS)
			@echo $(NAME_DIS) create

$(NAME_CWS): $(OBJ_CWS) $(OBJ_C) $(HEADERS)
			@gcc $(LIBFT_A) $(OBJ_C) -lncurses -I$(HEADERS_DIR) -o $(NAME_CWS)
			@echo $(NAME_CWS) create

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

$(OBJ_CWS):
			@mkdir -p $(OBJ_CWS)

$(OBJ_CWS)%.o: $(SRC_CWS)%.c
			@echo Create: $(@:obj_cws/%=%)
			@gcc $(FLAGS)  -I $(HEADERS_DIR) -c $< -o $@

clean:
		@rm -rf obj*
		@make -C libft/ clean

fclean: clean
		@rm -rf ./$(NAME_ASM) ./$(NAME_DIS) ./$(NAME_CWS)
		@make -C libft/ fclean

re: fclean all

.PHONY: all clean flcean re
