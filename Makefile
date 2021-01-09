game: source/*.cpp
	g++ ./source/*.cpp -o ./build/game -std=c++11

clean: game
	rm build/game
