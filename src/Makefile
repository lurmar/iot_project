CXX      = g++
CXXFLAGS = -std=c++17 -Wall
UNAME    := $(shell uname)

ifeq ($(UNAME), Darwin)
    CXXFLAGS += -I/opt/homebrew/include
    LDFLAGS   = -L/opt/homebrew/lib -lmosquittopp -lmosquitto
else ifeq ($(UNAME), Linux)
    CXXFLAGS += -I/usr/include
    LDFLAGS   = -L/usr/lib -lmosquittopp -lmosquitto
endif

all: subscriber publisher

subscriber: subscriber.cpp
	$(CXX) subscriber.cpp -o subscriber $(CXXFLAGS) $(LDFLAGS)

publisher: publisher.cpp
	$(CXX) publisher.cpp -o publisher $(CXXFLAGS) $(LDFLAGS)

menu: menu.cpp
	$(CXX) menu.cpp -o menu


# Docker
broker:
	docker start mosquitto

stop:
	docker stop mosquitto

logs:
	docker logs mosquitto

restart:
	docker restart mosquitto

status:
	docker ps | grep mosquitto

# Limpieza
rebuild: clean all

clean:
	rm -f subscriber publisher menu