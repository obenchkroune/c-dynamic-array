NAME            =   libdynarray.a
TEST_NAME       =   test_runner

CC              =   cc
CFLAGS          =   -Wall -Werror -Wextra -pedantic -MMD -MP -I.

BUILD_DIR       =   __build__
SRC_DIR         =   srcs
TEST_DIR        =   tests

SRC             =   srcs/dynamic_string.c \
					srcs/dynamic_array.c
					
OBJ             =   $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP             =   $(OBJ:.o=.d)

TEST_SRC        =   tests/test_dynamic_array.c \
					tests/test_string.c \
					tests/test_main.c

TEST_OBJ        =   $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%.o)
TEST_DEP        =   $(TEST_OBJ:.o=.d)

RM              =   rm -rf
AR				=	ar rcs

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(TEST_NAME): $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -ldynarray -o $(TEST_NAME)

test: $(TEST_NAME)
	./$(TEST_NAME) -v

-include $(DEP)
-include $(TEST_DEP)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
.SECONDARY: $(OBJ)
