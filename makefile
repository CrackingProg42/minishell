all:
	gcc -Wextra -Werror -Wall -ltermcap *.c  -I .&& ./a.out
	
