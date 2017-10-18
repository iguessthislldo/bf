NAME=bf

all: $(NAME).c
	gcc $< -o $(NAME)

clean:
	rm -fr $(NAME)
