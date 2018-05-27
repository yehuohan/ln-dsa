

#-------------------------------------------------
#
# Project created by Vim 2018-05-27 17:04:51
#
#-------------------------------------------------

#===============================================================================
# path 
#===============================================================================
DIR_INC = ./
DIR_SRC = ./
DIR_OBJ = ./obj
DIR_BIN = ./
DIR_3RD = ./3party
DIR_LIB = ./lib

#===============================================================================
# setting 
#===============================================================================
CC = g++
TARGET = usestl

ifeq ($(CC), g++)
CC_SUF = cpp
endif
ifeq ($(CC), gcc)
CC_SUF = c
endif

SRC = $(wildcard ${DIR_SRC}/*.${CC_SUF})
OBJ = $(patsubst %.${CC_SUF},${DIR_OBJ}/%.o,$(notdir ${SRC}))

BIN_TARGET = ${DIR_BIN}/${TARGET}
LDFLAGS = -L${DIR_LIB}
LIBS =
#-lopencv_core -lpthread
PKGFLAGS =
#`pkg-config opencv --cflagspkg-config opencv --libs`
CXXFLAGS = -g -Wall -I${DIR_INC} -I${DIR_SRC} -I${DIR_3RD} ${PKGFLAGS}


${BIN_TARGET} : ${OBJ}
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

${DIR_OBJ}/%.o:${DIR_SRC}/%.${CC_SUF}
	@[ -d ${DIR_OBJ} ] || mkdir -p ${DIR_OBJ}
	$(CC) $(CXXFLAGS) -c $< -o $@

.phony:clean
clean:
	rm ${OBJ}

