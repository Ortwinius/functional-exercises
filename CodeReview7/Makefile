all: main

.outputFolder:
	mkdir -p out

main: .outputFolder
	clang -std=c++23 -lstdc++ -lm main.cpp -Wall -Wextra -Werror -o out/exercise
	./out/exercise
