#
TOPDIR = ../..
#
include $(TOPDIR)/make.inc

#
INCS = -I"$(TOPDIR)/inc"
LIBS = -L"$(TOPDIR)/lib" -mwindows -luwin
CFLAGS +=
CXXFLAGS += -DBUILD_EXE

#
OBJ = test_progressbar.o

BIN = test_progressbar.exe
RC  = progressbar.rc
RES = ${RC:.rc=.res}
#
HEADER = $(INCDIR)/udialogx.h \
		 $(INCDIR)/ucontrol.h \
		 $(INCDIR)/uprogressbar.h \
		 $(INCDIR)/ubutton.h \
         mac_progressbar.h  \
#
all: $(BIN)

#
$(BIN) : $(OBJ) $(RES)
	$(CXX) -o $(BIN) $^ $(LIBS)
	cp -v $@ $(BINDIR)/$@
    
#
.PHONY : test
test :
	$(WINE) $(BINDIR)/$(BIN)
#
.PHONY : clean
clean :
	$(RM) ${OBJ} ${RES} ${BIN}

