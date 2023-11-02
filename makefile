all: 
	make compile
	make run
compile:
	mkdir -p bin
	cd bin/ && cmake .. && make 
	cd .. 
run:
	./bin/c99
valgrind:
	mkdir -p bin
	cd bin/ && cmake .. && make 
	cd ..
	valgrind -s --leak-check=full ./bin/c99
clean: 
	rm -r bin/
