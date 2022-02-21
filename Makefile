NAME	=	pipex
CC		=	gcc
SRCS	=	main.c pipex.c ft_split.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c
OBJS	=	$(SRCS:%.c=%.o)
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	./$(NAME) infile "tr o A" "tr A H" outfile

re: clean all

clean:
	rm -f $(OBJS) $(NAME)

.phony: all clean