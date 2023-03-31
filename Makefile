NAME = computor
CPP = c++ -std=c++11 -fsanitize=address -g3
INCS_ROOT = inc
INCS_CORE = inc/core_types
INCS_MISC = inc/misc_types
INCS_OPS = inc/mixed_operators
INCS_READLINE = /usr/local/opt/readline/include
CPP_FLAGS = -I${INCS_ROOT} -I${INCS_CORE} -I${INCS_MISC} -I${INCS_OPS} -I${INCS_READLINE} -lreadline -L/usr/local/opt/readline/lib -c 
SRCS = srcs/*.cpp srcs/parse/*.cpp srcs/os/*.cpp srcs/evaluate/*.cpp srcs/misc/*.cpp srcs/builtins/*.cpp srcs/mixed_operators/*.cpp srcs/core_types/*.cpp srcs/polynomial/*.cpp
OBJS= ${SRCS:.cpp=.o}

# Style constants
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m # No Color

# @${CPP} ${SRCS} ${CPP_FLAGS} -o ${NAME}
all : ${NAME}
	@echo "${GREEN}✔️  Done compiling..${NC}"

bonus : ${NAME}

${NAME}: ${OBJS}
	@echo "${GREEN}📇  Compiling All sources..${NC}"
	@echo "Linking..."

.cpp.o : 
	@echo "${GREEN}📇  Compiling $<..${NC}"
	${CPP} ${CPP_FLAGS} $< -o ${<:.cpp=.o}

clean : 
	@echo "${YELLOW}🗑️  Removing Objects..${NC}"
	@rm -rf *.o

fclean : clean
	@echo "${YELLOW}🗑️  Removing ${NAME}..${NC}"
	@rm -rf ${NAME}

re : fclean all

.PHONY : re clean fclean all