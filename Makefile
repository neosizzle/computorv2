NAME = computor
CPP = c++ -std=c++11 -fsanitize=address -g3
INCS_ROOT = inc
INCS_CORE = inc/core_types
INCS_MISC = inc/misc_types
INCS_OPS = inc/mixed_operators
INCS_READLINE = /usr/local/opt/readline/include
BUILDDIR=build/
CPP_INCS= -I${INCS_ROOT} -I${INCS_CORE} -I${INCS_MISC} -I${INCS_OPS} -I${INCS_READLINE}
CPP_FLAGS = -lreadline -L/usr/local/opt/readline/lib -lm -Wall -Wextra
SRCS = ${wildcard srcs/*.cpp srcs/parse/*.cpp srcs/os/*.cpp srcs/evaluate/*.cpp srcs/misc/*.cpp srcs/builtins/*.cpp srcs/mixed_operators/*.cpp srcs/core_types/*.cpp srcs/polynomial/*.cpp}
OBJS= ${SRCS:.cpp=.o}
OBJS_TARGET=${addprefix ${BUILDDIR},${subst /,_,${OBJS}}}

# Style constants
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m # No Color

all : ${NAME}
	@echo "${GREEN}✔️  Done building..${NC}"

bonus : ${NAME}

${NAME}: ${OBJS_TARGET}
	@echo "${GREEN}😏  Linking..${NC}"
	@${CPP} ${BUILDDIR}*.o ${CPP_FLAGS} -o ${NAME}

build/%.o : ${OBJS}
	@echo "${GREEN}📇  Compile finish..${NC}"

.cpp.o :
	@echo "${GREEN}📇  Compiling $<..${NC}"
	@${CPP} -c ${CPP_INCS} $< -o ${BUILDDIR}${subst /,_,$@}

clean : 
	@echo "${YELLOW}🗑️  Removing Objects..${NC}"
	@rm -rf ${BUILDDIR}*.o

fclean : clean
	@echo "${YELLOW}🗑️  Removing ${NAME}..${NC}"
	@rm -rf ${NAME}

re : fclean all

.PHONY : re clean fclean all