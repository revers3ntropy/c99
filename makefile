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
	valgrind -s --leak-check=full --track-origins=yes ./bin/c99
clean: 
	rm -r bin/
format:
	    git ls-files | grep -E '\.(cpp|hpp|c|h|cc|cxx|hxx|ixx)$$' | xargs clang-format -i -style=file
