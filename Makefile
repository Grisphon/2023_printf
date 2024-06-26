SRCS = 	src/print_base.c \
	src/printf.c \
	src/print_char.c \
	src/print_int.c \
	src/print_str.c \
	src/print_perc.c \
	src/print_x.c \
	src/print_b.c \
	src/print_o.c \
	src/print_p.c \
	src/flag_create.c\

TEST = test/test_printf.c \

OBJS = $(SRCS:.c=.o)

TOBJS = $(TEST:.c=.o)

ABJS = $(OBJS) $(TOBJS)

CFLAGS = -Wall -Wextra -Werror -Iinclude -I../libstu/include

CC = gcc

all: ut.out

libstu.a:
	$(MAKE) -C ../libstu libstu.a
	cp ../libstu/libstu.a libstu.a

clean:
	@rm -vf $(ABJS)
	$(MAKE) -C ../libstu fclean

fclean: clean
	@rm -vf libstu.a
	@rm -vf ut.out
	$(MAKE) -C ../libstu fclean


re: fclean all

ut.out: $(ABJS) libstu.a
	$(CC) -lcriterion -g -o ut.out $(ABJS) libstu.a

.PHONY : all clean fclean re

