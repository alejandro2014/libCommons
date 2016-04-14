##############################################
# Makefile used to compile various libraries #
# Alejandro Rupérez                          #
# Version 0.2 - April 2011                   #
##############################################

#Different paths
MAINPATH=/home/alejandro/programs/lib
BINPATH=${MAINPATH}/bin
INCPATH=${MAINPATH}/include
OBJPATH=${MAINPATH}/obj
SRCPATH=${MAINPATH}/src

#Names of the sources
LIB1=utilities
LIB2=bufferFiles
LIB3=pstrings

OBJ1=bufferedFiles
OBJ2=commonTasks
OBJ3=pstrings

#Options
CC=gcc
COMPOPT=-c -Wall -Werror -ansi -pedantic -I${INCPATH} -g -O0
LIBS=${LIBPATH}/lib${LIB1}.a ${LIBPATH}/lib${LIB2}.a ${LIBPATH}/lib${LIB3}.a
OBJLIB1=${OBJPATH}/${OBJ1}.o ${OBJPATH}/${OBJ2}.o ${OBJPATH}/${OBJ3}.o
OBJLIB2=${OBJPATH}/${OBJ1}.o ${OBJPATH}/${OBJ3}.o
OBJLIB3=${OBJPATH}/${OBJ2}.o ${OBJPATH}/${OBJ3}.o

#Libraries
all: ${LIBS}

${LIBPATH}/lib${LIB1}.a: ${OBJLIB1}
	ar rcs ${BINPATH}/lib${LIB1}.a ${OBJLIB1}

${LIBPATH}/lib${LIB2}.a: ${OBJLIB2}
	ar rcs ${BINPATH}/lib${LIB2}.a ${OBJLIB2}
	
${LIBPATH}/lib${LIB3}.a: ${OBJLIB3}
	ar rcs ${BINPATH}/lib${LIB3}.a ${OBJLIB3}

#Object code
${OBJPATH}/${OBJ1}.o: ${SRCPATH}/${OBJ1}.c
	${CC} ${COMPOPT} ${SRCPATH}/${OBJ1}.c -o ${OBJPATH}/${OBJ1}.o

${OBJPATH}/${OBJ2}.o: ${SRCPATH}/${OBJ2}.c
	${CC} ${COMPOPT} ${SRCPATH}/${OBJ2}.c -o ${OBJPATH}/${OBJ2}.o

${OBJPATH}/${OBJ3}.o: ${SRCPATH}/${OBJ3}.c
	${CC} ${COMPOPT} ${SRCPATH}/${OBJ3}.c -o ${OBJPATH}/${OBJ3}.o

clean:
	rm -f ${OBJLIB1} ${LIBS}
