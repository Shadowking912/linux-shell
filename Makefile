all: main

main:
	@echo "Building Program"
	@gcc -o ls ls.c
	@gcc -o shell shell.c
	@gcc -o cat cat.c
	@gcc -o date date.c
	@gcc -o mkdir mkdir.c
	@gcc -o rm rm.c
	@./shell
	@echo "running program"
clean: 
	@echo "Removing executables"
	@rm -f ls shell shell.o cat date mkdir rm