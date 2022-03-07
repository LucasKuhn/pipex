NAME	=	pipex
CC		=	gcc
SRCS	=	main.c ft_exec.c pipex.c ft_split.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_strlen.c
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
CFLAGS	=	-Wall -Wextra -Werror
VPATH	=	src utils

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@ -I ./

$(OBJ_DIR):
	mkdir -p obj

clean:
	@rm -rf obj
	@echo "removed obj folder"

fclean: clean
	@rm -rf $(NAME)
	@echo "removed executable"

re: fclean all

go: all
	./$(NAME) infile "tr o A" "tr A H" outfile
	@cat outfile

.phony: all clean go