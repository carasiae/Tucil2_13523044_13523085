CC = gcc
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
FLAG = -fopenmp

build:
	@$(CC) $(FLAG) $(SOURCE_FOLDER)/*.c -o $(OUTPUT_FOLDER)/app -lm

clean:
	@rm -f $(OUTPUT_FOLDER)/app

run:
	@$(OUTPUT_FOLDER)/app	

all: clean build run

dep:
	@curl -L https://github.com/nothings/stb/blob/master/stb_image.h?raw=true -o ./src/stb_image.h
	@curl -L https://github.com/nothings/stb/blob/master/stb_image_write.h?raw=true -o ./src/stb_image_write.h

# i think this is correct? maybe? just configure it 
