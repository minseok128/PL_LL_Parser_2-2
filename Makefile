CC      = c++ -std=c++14
CFLAGS  = -Wall -Wextra -Werror

DIR     = ./src
BASE    = main Parser ContextManager Lexer SymbolTable Var
HBASE	= Parser ContextManager Lexer SymbolTable Var TokenType
SRCS    = $(addprefix $(DIR)/, $(addsuffix .cpp, $(BASE)))
OBJS    = $(addprefix $(DIR)/, $(addsuffix .o, $(BASE)))
HEADERS = $(addprefix $(DIR)/, $(addsuffix .h, $(HBASE)))
NAME    = CPP_Parser

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -I$(DIR) $^ -o $@

%.o : %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I$(DIR) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

test : all
	./$(NAME) ./test_case/test0.txt

.PHONY : all clean fclean re