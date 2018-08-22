##
## EPITECH PROJECT, 2018
## Project navy
## File description:
## Build navy binary.
##

MAIN_SRC	=	src/main.c

SRC	=		src/my_getnbr.c		\
			src/load_file.c		\
			src/init_boat.c		\
			src/change_map.c	\
			src/get_next_line.c	\
			src/create_map.c	\
			src/my_printf.c		\
			src/players.c		\
			src/sigs.c		\
			src/check_end.c		\
			src/hdl.c		\
			src/error.c		\
			src/turns.c

UT_SRC	=	tests/main_test.c

OBJ	=	$(MAIN_SRC:.c=.o) $(SRC:.c=.o)

UT_OBJ	=	$(SRC:.c=.o) $(UT_SRC:.c=.o)

CFLAGS	=	-Wextra -W -Wall -I ./include/ -lncurses

LDFLAGS	=

NAME	=	navy

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(UT_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f units
	rm -f *.html
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcno" -type f -delete

re: fclean all

test_run:	CFLAGS += --coverage

test_run:	$(UT_OBJ)
		$(CC) -o units $(UT_OBJ) $(LDFLAGS) -lcriterion --coverage
		./units

cov:	test_run
	gcovr -r . --html -o coverage.html --html-details -e ".*tests/.*"
