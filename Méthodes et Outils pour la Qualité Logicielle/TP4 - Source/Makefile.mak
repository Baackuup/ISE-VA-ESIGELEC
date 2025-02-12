# Windows makefile
BOOST:="C:\MOQL\boost_1_78_0"
OUT := cashregister.exe
SRCS := Cashregister.c Productdatabase.c Specialoffer.c Userinterface.c Main.c
OBJS := $(SRCS:%.c=%.o)
DEPS := $(SRCS:%.c=%.d)
GCOVR_DIR := gcovr_out

TEST_SRCS := Cashregister.c Productdatabase.c Specialoffer.c Userinterface.c Test.cpp
TEST_OUT := test_cash.exe

CFLAGS := -O0 -g3 -W -I. -MMD -MP

all: $(OUT)

$(OUT): $(SRCS)
	gcc $(CFLAGS) $^ -o $@

clean:
	-del $(OUT)
	-del $(TEST_OUT)
	-rmdir /S /Q $(GCOVR_DIR)
	-del *.gcda
	-del *.gcno

run: $(OUT)
	-./$(OUT)

gcov: $(OUT)
	gcov $(SRCS)
	
gcov_full: $(OUT)
	gcov --branch-probabilities --branch-counts --function-summaries --demangled-names $(SRCS)

gcovr: $(GCOVR_DIR) $(OUT)
	python -m gcovr --output $(GCOVR_DIR)/gcovr.html --html-details

$(GCOVR_DIR):
	mkdir $@

install_gcovr:
	python -m pip install gcovr

$(TEST_OUT): $(TEST_SRCS)
	g++ $(CFLAGS) -w -fpermissive -I$(BOOST) $(TEST_SRCS) -o $@

unit_test: $(TEST_OUT)
	$(TEST_OUT)

