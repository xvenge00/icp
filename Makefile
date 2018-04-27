# ICP project 2018
# Author: Matej Kastak <xkasta02>
# Author: Adam Venger  <xvenge00>
AUTHOR_MATO=xkasta02
AUTHOR_ADAM=xvenge00

SHELL=/bin/sh

AUTHOR=$(AUTHOR_MATO)
ifeq ($(AUTHOR), $(AUTHOR_MATO))
    AUTHOR2=$(AUTHOR_ADAM)
else ifeq ($(AUTHOR), $(AUTHOR_ADAM))
    AUTHOR2=$(AUTHOR_MATO)
else
    $(error Wrong author name)
endif

EXECUTABLE=src/blockeditor
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	EXECUTABLE=src/blockeditor.app/Contents/MacOS/blockeditor
endif

FINAL_ARCHIVE=$(AUTHOR)-$(AUTHOR2)
REMOTE_SOURCE_DIR=~/dev/icp/

# variables for remote compilation
REMOTE_MERLIN=$(AUTHOR)@merlin.fit.vutbr.cz
REMOTE_EVA=$(AUTHOR)@eva.fit.vutbr.cz
REMOTE_TRANSFER_FILES=*.cc *.h Makefile
REMOTE_TRANSFER_FILES=$(FINAL_ARCHIVE).zip

ARCHIVE_FILES=src/* examples/* doc/* README.txt Makefile

# TODO(mato): change to release
all : debug

.PHONY : run clean dist-clean pack format merlin eva debug compile

compile : 
	cd src && qmake -Wall && make

debug: 
	cd src && qmake -Wall CONFIG+=icp_debug && make

# run the program, for testing purposes
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# clear the repository
clean :
	rm -rf $(EXECUTABLE) src/*.o $(FINAL_ARCHIVE).*
	cd ./src && qmake -Wall && make clean

dist-clean : clean
	rm -rf *~ *.orig test/*.orig $(GTEST)
#-git clean -dn

# create final archive
pack : clean
	tar -vczf $(FINAL_ARCHIVE).tar.gz $(ARCHIVE_FILES)
	zip $(FINAL_ARCHIVE).zip $(ARCHIVE_FILES)

merlin : pack
	scp -C $(REMOTE_TRANSFER_FILES) $(REMOTE_MERLIN):$(REMOTE_SOURCE_DIR)
	-ssh -X -t $(REMOTE_MERLIN) "cd $(REMOTE_SOURCE_DIR) && unzip $(REMOTE_TRANSFER_FILES) && make; bash"

eva : pack
	scp -C $(REMOTE_TRANSFER_FILES) $(REMOTE_EVA):$(REMOTE_SOURCE_DIR)
	-ssh -X -t $(REMOTE_EVA) "cd $(REMOTE_SOURCE_DIR) && unzip $(REMOTE_TRANSFER_FILES) && gmake; bash" # gmake for GNU make on eva

# format source files
# astyle --indent=spaces --style=java --break-blocks --pad-oper --align-pointer=middle --align-reference=middle --max-code-length=120 *.cc *.h
format :
	cd src && clang-format -i *.cpp *.h
