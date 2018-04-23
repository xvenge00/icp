# ICP project 2018
# Author: Matej Kastak <xkasta02>
# Author: Adam Venger  <xvenge00>
AUTHOR_MATO=xkasta02
AUTHOR_ADAM=xvenge00

AUTHOR=$(AUTHOR_MATO)
ifeq ($(AUTHOR), $(AUTHOR_MATO))
    AUTHOR2=$(AUTHOR_ADAM)
else ifeq ($(AUTHOR), $(AUTHOR_ADAM))
    AUTHOR2=$(AUTHOR_MATO)
else
    $(error Wrong author name)
endif

#TODO(mato): migrate to cmake compilaion

ICP_BIN=icp
SHELL=/bin/sh

FINAL_ARCHIVE=$(AUTHOR)-$(AUTHOR2)#-100-0
REMOTE_SOURCE_DIR=~/dev/icp/

# variables for remote compilation
REMOTE_MERLIN=$(AUTHOR)@merlin.fit.vutbr.cz
REMOTE_EVA=$(AUTHOR)@eva.fit.vutbr.cz
REMOTE_TRANSFER_FILES=*.cc *.h Makefile

ARCHIVE_FILES=src/ examples/ doc/ README.txt Makefile

EXECUTABLE=blockeditor

# flags used for compilation
CFLAGS=-Wall -Wextra --pedantic -std=c99
CXXFLAGS=-Wall -Wextra --pedantic -std=c++11
LDFLAGS=-Wall -Wextra --pedantic

all : debug
# all : $(EXECUTABLE)

$(EXECUTABLE) : $(O_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

.PHONY : run clean dist-clean pack format merlin eva debug

debug: CXXFLAGS+=-g -DDEBUG
debug: $(EXECUTABLE)

# run the program, for testing purposes
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# clear the repository
clean :
	rm -rf $(EXECUTABLE) *.o $(FINAL_ARCHIVE).*

dist-clean : clean
	rm -rf *~ *.orig test/*.orig $(GTEST)
#-git clean -dn

# create final archive
pack : clean
	tar -vczf $(FINAL_ARCHIVE).tar.gz $(ARCHIVE_FILES)
	zip $(FINAL_ARCHIVE).zip $(ARCHIVE_FILES)

merlin :
	scp -C $(REMOTE_TRANSFER_FILES) $(REMOTE_MERLIN):$(REMOTE_SOURCE_DIR)
	-ssh -X -t $(REMOTE_MERLIN) "cd $(REMOTE_SOURCE_DIR) && make; bash"

eva :
	scp -C $(REMOTE_TRANSFER_FILES) $(REMOTE_EVA):$(REMOTE_SOURCE_DIR)
	-ssh -X -t $(REMOTE_EVA) "cd $(REMOTE_SOURCE_DIR) && gmake; bash" # gmake for GNU make on eva

# format source files
# astyle --indent=spaces --style=java --break-blocks --pad-oper --align-pointer=middle --align-reference=middle --max-code-length=120 *.cc *.h
format :
	cd src && clang-format -i *.cpp *.h
