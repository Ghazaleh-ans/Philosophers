# Colors
RESET			= "\033[0m"
BLACK    		= "\033[30m"    # Black
RED      		= "\033[31m"    # Red
GREEN    		= "\033[32m"    # Green
YELLOW   		= "\033[33m"    # Yellow
BLUE     		= "\033[34m"    # Blue
MAGENTA  		= "\033[35m"    # Magenta
CYAN     		= "\033[36m"    # Cyan
WHITE    		= "\033[37m"    # White

# Emojis
SUCCESS		= "✅"
BUILD		= "🔨"
CLEAN		= "🧹"

# Compiler
NAME			= philo
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -pthread
MAKE			= make -sC
MKDIR			= mkdir -p
RM				= rm -rf

# Includes
INCLUDES_DIR 	= includes
INCLUDES_FLAG 	= -I$(INCLUDES_DIR)
INCLUDES		= $(INCLUDES_DIR)/philo.h

# Sources
SRCS_DIR		= srcs/
SRCS			= $(SRCS_DIR)main.c $(SRCS_DIR)init.c $(SRCS_DIR)utils.c $(SRCS_DIR)philo.c $(SRCS_DIR)monitor.c $(SRCS_DIR)time.c

# Objects
OBJS_DIR		= objs/
OBJS 			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# OBJS			= $(OBJS_DIR)main.o $(OBJS_DIR)init.o $(OBJS_DIR)utils.o $(OBJS_DIR)philo.o $(OBJS_DIR)monitor.o $(OBJS_DIR)time.o

all : $(OBJS_DIR) $(NAME) $(INCLUDES)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(NAME) : $(OBJS) Makefile
	@echo $(BUILD) $(GREEN) "Compiling $(NAME)..." $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME)
	@echo $(SUCCESS) $(YELLOW) "Compiling $(NAME) FINISHED" $(RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@

clean :
	@$(RM) $(OBJS_DIR)
	@echo $(CLEAN) $(RED) "Cleaned!" $(RESET)

fclean : clean
	@$(RM) $(NAME)
	@echo $(CLEAN) $(RED) "Full Cleaned!" $(RESET)

re: fclean all

.PHONY: all clean fclean re
