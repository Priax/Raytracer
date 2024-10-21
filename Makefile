##
## EPITECH PROJECT, 2024
## B-PDG-300-MAR-3-1-PDGRUSH3-vincent.montero-fontaine
## File description:
## Makefile
##

EXEC = raytracer

LIB = -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

UNIT_TEST =		tests/unit_tests

SRC = 	src/main.cpp 				\
		src/primitives/quad.cpp 	\
		src/primitives/sphere.cpp 	\
		src/primitives/cylinder.cpp \
		src/primitives/cone.cpp 	\
		src/primitives/triangle.cpp \
		src/primitives/pyramide.cpp \
		src/boxes.cpp 				\
		src/camera.cpp 				\
		src/color.cpp 				\
		src/error_parser.cpp 		\
		src/graphical.cpp			\
		src/hittable_list.cpp 		\
		src/hittable.cpp 			\
		src/interval.cpp 			\
		src/material.cpp 			\
		src/new_parser.cpp 			\
		src/ortho.cpp 				\
		src/pdf.cpp 				\
		src/perlin.cpp 				\
		src/ray.cpp 				\
		src/texture.cpp 			\
		src/utility.cpp 			\
		src/vec3.cpp 				\
		src/vecN.cpp 				\

TEST_SRC =	src/primitives/quad.cpp 	\
			src/primitives/sphere.cpp 	\
			src/primitives/cylinder.cpp \
			src/primitives/cone.cpp 	\
			src/primitives/triangle.cpp \
			src/primitives/pyramide.cpp \
			src/boxes.cpp 				\
			src/camera.cpp 				\
			src/color.cpp 				\
			src/error_parser.cpp 		\
			src/graphical.cpp			\
			src/hittable_list.cpp 		\
			src/hittable.cpp 			\
			src/interval.cpp 			\
			src/material.cpp 			\
			src/new_parser.cpp 			\
			src/ortho.cpp 				\
			src/pdf.cpp 				\
			src/perlin.cpp 				\
			src/ray.cpp 				\
			src/texture.cpp 			\
			src/utility.cpp 			\
			src/vec3.cpp 				\
			src/vecN.cpp 				\
			tests/tests.cpp

GCC_PARAM = -W -Wall -Wextra -g3

LAST_FLAG = -ansi -pedantic -Werror

FLAG_VAL = --tool=memcheck --leak-check=yes --show-reachable=yes

FLAG_VAL2 = --leak-check=full --show-leak-kinds=all -s

all:	$(EXEC)

$(EXEC): $(SRC)
	g++ $(GCC_PARAM) $(LIB) -o $@ $^

spe: $(SRC)
	g++ $(GCC_PARAM) $(LAST_FLAG) -o $(EXEC) $^

clean:
	rm -f $(EXEC)

fclean: clean
	@find . -type f \( -name "*~" -o \( -name "*#" -a -name "#*" \) \) -delete
	@find . -type f \( -name "#*#" -o -name "*~" \) -delete
	@find . -type f \( -name "*.gcno" -o -name "*.gcda" \) -delete
	@find . -type f \( -name "*.o" -o -name "vgcore.*" \) -delete
	rm -f coding-style-reports.log

tests_run:
	@g++ $(TEST_SRC) -o $(UNIT_TEST) $(GCC_PARAMS) $(LIB) -lcriterion -std=c++17
	@./$(UNIT_TEST)

style: fclean
	coding-style . .
	cat coding-style-reports.log

exec:  $(EXEC)
	clear
	@./$(EXEC)

valgrind: all
	valgrind $(FLAG_VAL) $(FLAG_VAL2) ./$(EXEC)

re:	fclean all

.PHONY: clean fclean spe style valgrind re
