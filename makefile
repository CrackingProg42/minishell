all:
	gcc -Wextra -Werror -Wall -ltermcap *.c */*.c -I .&& ./a.out
	
