all:
	gcc -Wextra -Werror -Wall *.c */*.c -I .&& ./a.out
	
