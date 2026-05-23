# C flags
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -lm

# SDL flags
SDLFLAGS += -lSDL2

build:
	clang++ $(CFLAGS) $(SDLFLAGS) ./src/**.cpp ./ui/**.cpp ./utils/**.cpp -o $(BUILD)

run:
	./$(BUILD)
