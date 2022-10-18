NAME = computor
CPP = c++ -fsanitize=address -g3
INCS = inc
CPP_FLAGS = -I${INCS} -lreadline
SRCS = srcs/*.cpp

# Style constants
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m # No Color


all : ${NAME}
	@echo "${GREEN}✔️  Done compiling..${NC}"

bonus : ${NAME}

${NAME}:
	@echo "${GREEN}📇  Compiling All sources..${NC}"
	@${CPP} ${CPP_FLAGS} ${SRCS} -o ${NAME}

clean : 
	@echo "${YELLOW}🗑️  Removing Objects..${NC}"
	@rm -rf *.o

fclean : clean
	@echo "${YELLOW}🗑️  Removing ${NAME}..${NC}"
	@rm -rf ${NAME}

re : fclean all

.PHONY : re clean fclean all