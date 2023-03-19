#
TOPDIR = ../../..
#
include $(TOPDIR)/make.inc

#
INCS = -I"$(TOPDIR)/inc" -I"."
LIBS = -L"$(TOPDIR)/lib" -lws2_32
CFLAGS +=
CXXFLAGS += -DBUILD_EXE
#
OBJ = rawping.o ip_checksum.o rawping_driver.o
BIN = rawping.exe
RC  = rawping.rc
RES = ${RC:.rc=.res}
#
HEADER = rawping.h ip_checksum.h
#
all: $(BIN) 

#
$(BIN) : $(OBJ) $(RES)
	$(CXX) -o $@ $^ $(LIBS)
	cp -vf $@ $(BINDIR)/$@

.PHONY : test
test :
	$(WINE) $(BINDIR)/$(BIN) 127.0.0.1

#
clean :
	$(RM) ${OBJ} ${RES} ${BIN}
