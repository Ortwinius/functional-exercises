all: exercise

.outputFolder:
	mkdir -p out

exercise: .outputFolder
	clang -std=c++20 -lstdc++ -lm exercise.cpp -Wall -Wextra -Werror -o out/exercise
	./out/exercise