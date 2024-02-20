SRCS = 	src/print_base.c \
	src/printf.c \

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
	$(CC) -lcriterion -o ut.out $(ABJS) libstu.a

.PHONY : all clean fclean re

