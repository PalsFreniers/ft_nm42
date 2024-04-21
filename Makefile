CC=cc
CFLAGS=-Wall -Wextra
CFILES= src/main.c
HEADER= 
LD=cc
LIBS=-Llibft -lft
LDFLAGS=$(LIBS) #-fsanitize=address
LDFILES=$(CFILES:.c=.o)

NAME=ft_nm
LIBFT=libft/libft.a

$(NAME): $(LIBFT) $(LDFILES)
	$(LD) -o $(NAME) $(LDFILES) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -o $@ -c $< $(CFLAGS) 

$(LIBFT):
	@make --no-print-directory -j 4 -C libft

all: $(NAME)

clean:
	rm -rf $(LDFILES)
	@make clean --no-print-directory -C libft

fclean: clean
	rm -rf $(NAME)
	@make fclean --no-print-directory -C libft

re: fclean all

.PHONY: all clean fclean re
