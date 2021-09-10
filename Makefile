##
## EPITECH PROJECT, 2021
## makefile
## File description:
## cpp-makefile by Erudyx
##

MAKEFLAGS += --no-print-directory -j

END=\e[0m
GREEN=\e[92m
RED=\x1b[31;01m
YELLOW=\x1b[33;

CXX 	= g++

define rich_echo
[ -t 1 ] && echo -e "\e[1m$(1)\e[0m\t$(2)" || echo -e "$(0)\t$(2)"
endef

SOURCE_DIR		= src
BUILD_DIR		= build

SOURCE			=  $(shell find $(SOURCE_DIR) -name "*.cpp")

TEST_SOURCE			= $(shell find $(SOURCE_DIR) -name "*.cpp")

OBJ		=	$(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCE))
TEST_OBJ		=	$(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCE))

NAME	=	plazza

CPPFLAGS	+=	-I./include
CXXFLAGS 	+= -O2 -W -Wall -Wextra -std=c++17
LDLIBS 		+= -lpthread -lrt

ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	CPPFLAGS += -g -D__DEBUG
endif

ifneq (,$(findstring tests,$(MAKECMDGOALS)))
	CPPFLAGS += -D__TESTS -lgtest -lgtest_main --coverage
endif

all::	$(NAME)
all::	message

message:
	@echo -e "\e[38;5;33m"
	@figlet $(NAME); exit 0
	@echo -e "\e[0m"
	@echo -e "\e[1m[INFO]\t$(GREEN)Compilation successful ✔$(END)"

$(NAME): $(OBJ)
	@$(CXX) -o $@ $^ $(LDLIBS)

.SECONDEXPANSION:
$(BUILD_DIR)/%.o: override CPPFLAGS += -MT $@ -MMD -MP -MF $(@:.o=.d)
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $$(@D)/.
	@$(call rich_echo,"CXX","$@")
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/.:
		@mkdir -p $@

$(BUILD_DIR)%/.:
		@mkdir -p $@

.PRECIOUS:			$(BUILD_DIR)/. $(BUILD_DIR)%/.

clean:
	@rm -rfv $(shell find $(BUILD_DIR) -name "*.gc*")
	@rm -rfv $(shell find $(BUILD_DIR) -name "*.o")
	@rm -rfv $(shell find $(BUILD_DIR) -name "*.d")
	@rm -rfv $(shell find -name "vgcore.*")

debug:: clean
debug:: all
	@$(call rich_echo,"🔨","Debug biniary set")


fclean:	clean
	@rm -fv $(NAME) $(NAME).debug $(NAME).gtest

tests_run: $(OBJ)
	@$(CXX) -o $(NAME).gtest $(TEST_OBJ) $(CPPFLAGS) -std=c++17 -lgtest_main -lgtest -pthread $(LDLIBS) tests/*.cpp
	@$(call rich_echo,"🔨","Unit tests building done")
	./$(NAME).gtest
	$(CLEAR)

re::	fclean
re::	all

.PHONY: all clean fclean re debug test DOLIB

-include $(OBJ:.o=.d)

# CC: 	compilateur C 					(gcc, clang)
# CPP: 	compilateur préprocesseur C/C++ (gcc, clang, g++, clang++)
# CXX: 	compilateur C++ 				(g++, clang++)
# LD: 	linker 							(ld, gcc, ...)

# CFLAGS: 	flag compilo C 						(-W, -Wall, --coverage, -g)
# CPPFLAGS 	flag compilo C/C++ PREPROCESSOR 	(-Include)
# CXXFLAGS 	flag compilo C++ 					(-W ..., -std=c++14)
# LDLIBS: 	lib pour le linker 					(-lmy, -lcriterion)
# LDFLAGS: 	flag pour le linker 				(-Llib)
#
#
