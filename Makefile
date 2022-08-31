# Project name
PROJ_NAME=gsic

# .c files
C_SOURCE=$(wildcard ./src/*.c)

# .h files
H_SOURCE=$(wildcard ./src/*.h)

# .o files
OBJS=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

# C compiler
CC=gcc

# Compiler flags
CC_FLAGS=-c             \
         -W             \
         -Wall          \
         -ansi          \
         -pedantic      \
         -std=c11

# Comand used at clean target
RM=rm -rf


# Compilation and linking
all: objects_dir $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo ' '
	@ echo 'Finished building binary: $@'
	@ echo ' '
	@ echo '\o/'

./objects/%.o: ./src/%.c ./src/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./src/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objects_dir:
	@ mkdir -p objects

clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects

# Alvos falsos, para evitar conflitos.
# Por exemplo, se existisse um arquivo chamado clean.c, ou all.c
.PHONY: all clean