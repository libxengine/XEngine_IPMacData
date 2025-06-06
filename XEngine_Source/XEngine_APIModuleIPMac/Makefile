CC = g++ -Wall -std=c++20 -fPIC
CC_C = gcc -Wall -std=c17 -fPIC
PLATFORM = linux
PLATVER = 
FILEEXT = 
LIBFLAG = 
LOADHDR = -I ./ 
LOADSO = 
LIB = 
LIBEX = 
OBJECTS_C = data-pool.o maxminddb.o
OBJECTS_CPP = APIModule_IPAddr.o APIModule_MACInfo.o pch.o
OBJECTS = $(OBJECTS_C) $(OBJECTS_CPP)

ifeq ($(RELEASE),1)
FLAGS = -c -D _RELEASE
DEBUG = -O2
else
	ifeq ($(PLATFORM),mac)
		FLAGS = -c
		DEBUG = -g -D _DEBUG
	else
		FLAGS = -c -lc_p
		DEBUG = -g -pg -D _DEBUG
	endif
endif

ifeq ($(UNICODE),1)
override UNICODE := -D __UNICODE__
else
override UNICODE := -D __ANSI__
endif


ifeq ($(PLATFORM),linux)
	ifeq (/etc/redhat-release,$(wildcard /etc/redhat-release))
		PLATVER = -D __CENTOS__
	else
		PLATVER = -D __UBUNTU__
	endif
	FILEEXT = so
	LIBFLAG = -shared
	LIBEX = -lpthread -lrt -ldl
	LOADBIN = -Wl,-rpath=./,--disable-new-dtags
else ifeq ($(PLATFORM),mac)
	CC += -Wno-deprecated-declarations
	PLATVER = -D __MACOS__
	FILEEXT = dylib
	LIBFLAG = -dynamiclib
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
endif


all:$(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o libXEngine_APIModuleIPMac.$(FILEEXT) $(LIBFLAG) $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)

data-pool.o:./APIModule_IPAddr/data-pool.c             
	$(CC_C) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./APIModule_IPAddr/data-pool.c
maxminddb.o:./APIModule_IPAddr/maxminddb.c       
	$(CC_C) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./APIModule_IPAddr/maxminddb.c
APIModule_IPAddr.o:./APIModule_IPAddr/APIModule_IPAddr.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./APIModule_IPAddr/APIModule_IPAddr.cpp 
xdb_searcher.o:./APIModule_IPAddr/xdb_searcher.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./APIModule_IPAddr/xdb_searcher.cpp 
APIModule_MACInfo.o:./APIModule_MACInfo/APIModule_MACInfo.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./APIModule_MACInfo/APIModule_MACInfo.cpp 

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./pch.cpp


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(FILEEXT)                        
