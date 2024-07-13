.PHONY: build runs cleans ignore

build:
	gcc -Wall -o file_processor_singlethreaded file_processor_singlethreaded.c
	@echo "\nTo run the file_processor_singlethreaded program, USE: make runs <input_file> \n"

	gcc -Wall -o file_processor_multithreaded file_processor_multithreaded.c -lpthread
	@echo "\nTo run the file_processor_multithreaded program, USE: make runm <input_file> <num_threads> \n"
	
runs:
	./file_processor_singlethreaded $(filter-out $@,$(MAKECMDGOALS))

runm:
	./file_processor_multithreaded $(filter-out $@,$(MAKECMDGOALS))

clean:
	rm -f file_processor_singlethreaded file_processor_multithreaded

ignore:
	@:

%: ignore
	@:

