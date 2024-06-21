run:
	@cp ${file}/${file}.* ./
	@gcc ${file}/${file}.c -o bin/${file}
	@./bin/${file}
	@cat ./${file}.out
	@rm ${file}.*

