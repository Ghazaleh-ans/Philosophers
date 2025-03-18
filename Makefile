# Colors
RESET            = "\033[0m"
BLACK            = "\033[30m"    # Black
RED              = "\033[31m"    # Red
GREEN            = "\033[32m"    # Green
YELLOW           = "\033[33m"    # Yellow
BLUE             = "\033[34m"    # Blue
MAGENTA          = "\033[35m"    # Magenta
CYAN             = "\033[36m"    # Cyan
WHITE            = "\033[37m"    # White

# Emojis
SUCCESS         = "✅"
BUILD           = "🔨"
CLEAN           = "🧹"

# Compiler
NAME            = philo
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -pthread
MAKE            = make -sC
MKDIR           = mkdir -p
RM              = rm -rf

# Includes
INCLUDES_DIR    = includes
INCLUDES_FLAG   = -I$(INCLUDES_DIR)
INCLUDES        = $(INCLUDES_DIR)/philo.h

# Sources
SRCS_DIR        = srcs/
SRCS            = $(SRCS_DIR)main.c $(SRCS_DIR)init.c $(SRCS_DIR)utils.c $(SRCS_DIR)philo.c \
					$(SRCS_DIR)monitor.c $(SRCS_DIR)time.c $(SRCS_DIR)input.c $(SRCS_DIR)utils_libft.c \
					$(SRCS_DIR)utils_threads.c $(SRCS_DIR)philo_eat.c

# Objects
OBJS_DIR        = objs/
OBJS            = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(NAME): $(OBJS) Makefile
	@echo $(BUILD) $(RED) "Compiling $(NAME)..." $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(SUCCESS) $(GREEN) "Compiling $(NAME) FINISHED" $(RESET)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)
	@echo $(CLEAN) $(YELLOW) "Cleaned!" $(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(CLEAN) $(YELLOW) "Full Cleaned!" $(RESET)

re: fclean all

.PHONY: all clean fclean re
