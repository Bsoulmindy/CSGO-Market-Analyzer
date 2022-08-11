objects_src = $(filter-out src/main.o, $(patsubst src/%.cpp,src/%.o,$(shell find src -name '*.cpp')))
object_main = src/main.o
objects_test = $(patsubst test/%.cpp,test/%.o,$(shell find test -name '*.cpp'))
sources_test = $(shell find test -name '*.cpp')
sources_src = $(shell find src -name '*.cpp')
# CPPFLAGS = -fprofile-arcs -ftest-coverage
# CXXFLAGS = -g

build/analyzer: $(objects_src) $(object_main)
	g++ $(objects_src) $(object_main) -o build/analyzer -L/usr/lib/ -lboost_system -lboost_thread -lpthread -lcrypto -lssl -lsqlite3 -lgcov --coverage -lbass

build/test: $(objects_test) $(objects_src)
	g++ $(objects_test) -o build/test $(objects_src) -fprofile-arcs -ftest-coverage -L/usr/lib/ -lboost_system -lboost_thread -lpthread -lcrypto -lssl -lsqlite3 -lboost_unit_test_framework -lbass

coverage:
	gcov $(sources_test) $(sources_src)
	lcov --capture --directory . --output-file main_coverage.info
	lcov -r main_coverage.info "/usr/*" -o main_2.info
	genhtml main_2.info --output-directory coverage
	firefox coverage/index.html
	rm *.gcov
	rm main_coverage.info
	rm main_2.info

.PHONY: clean
clean:
	rm $(shell find . -name '*.o')
	rm $(shell find . -name '*.gcda')
	rm $(shell find . -name '*.gcno')