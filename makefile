main: main.cpp simulation.cpp train_tracks.cpp debug_utils.cpp
	g++ main.cpp simulation.cpp train_tracks.cpp debug_utils.cpp -o main -g -std=c++17 -Wall -lpthread
# DEBUG:
#	g++ main.cpp simulation.cpp train_tracks.cpp debug_utils.cpp -o simulation -DDEBUG -g -std=c++17 -Wall -lpthread
# DISPLAY:
#	g++ main.cpp simulation.cpp train_tracks.cpp debug_utils.cpp -o simulation -DDEBUG -DDISPLAY -g -std=c++17 -Wall -lpthread
# DEBUG & DISPLAY
#	g++ main.cpp simulation.cpp train_tracks.cpp debug_utils.cpp -o simulation -DDEBUG -DDISPLAY -g -std=c++17 -Wall -lpthread

clean:
	rm main
