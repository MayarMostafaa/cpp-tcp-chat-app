CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -pthread -g

SERVER := server
CLIENT := client

all: $(SERVER) $(CLIENT)

$(SERVER): server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o $(SERVER)

$(CLIENT): client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)

run-server: $(SERVER)
	./$(SERVER)

run-client: $(CLIENT)
	./$(CLIENT)

.PHONY: all clean run-server run-client
