NAME            =   dynamic_array

CC              =   cc
HEADERS         =   ./includes
CFLAGS          =   -Wall -Werror -Wextra -MMD -MP $(addprefix -I,$(HEADERS)) \
					-fsanitize=address -g3
LDFLAGS         =   

BUILD_DIR       =   __build__
SRC_DIR         =   srcs

SRC             =   $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ             =   $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP             =   $(OBJ:.o=.d)

RM              =   rm -rf
MAKE            =   make

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

-include $(DEP)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
