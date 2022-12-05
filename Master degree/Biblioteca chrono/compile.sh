#!/bin/bash
#Run this in terminal
#+ Command to compile c++ program. here i used common one
g++ -std=c++11 -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/1b.cpp' -o 1b -lcryptopp
g++ -std=c++11 -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/2b.cpp' -o 2b -lcryptopp
g++ -std=c++11 -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/4b.cpp' -o 4b -lcryptopp
g++ -std=c++11  -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/8b.cpp' -o 8b -lcryptopp
g++ -std=c++11  -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/16b.cpp' -o 16b -lcryptopp
g++ -std=c++11  -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/32b.cpp' -o 32b -lcryptopp
g++ -std=c++11  -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/64b.cpp' -o 64b -lcryptopp
g++ -std=c++11  -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/128b.cpp' -o 128b -lcryptopp
g++ -std=c++11  -g3 -ggdb -O0 -Wall -Wextra -Wno-unused '/home/haruka/Desktop/atual/256b.cpp' -o 256b -lcryptopp
exit 0

