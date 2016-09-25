CXX     =   g++

RM      =   rm -f

NAME    =   301danone

SRC     =   main.cpp

OBJ     =   $(SRC:.cpp=.o)

all:        $(NAME)

$(NAME):    $(OBJ)
            $(CXX) -o $(NAME) $(OBJ)

clean:
            $(RM) $(OBJ)

fclean:     clean
            $(RM) $(NAME)

re:         fclean all