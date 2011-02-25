BINDIR= $(DESTDIR)/usr/bin
MANDIR= $(DESTDIR)/usr/share/man/man1
CFLAGS= -Wall -ansi -pedantic -O3 -fomit-frame-pointer -g
CC= mpicc ${CFLAGS} 
SNAME= gridnetbench
SRC= gridnetbench.c netbench_master.c netbench_client.c
OBJ= $(SRC:.c=.o)

all : ${SNAME} clean
	@echo success making ${SNAME}
dev : ${SNAME}
	@echo success making ${SNAME}
${SNAME} : ${OBJ}
	@echo making ${SNAME}
	@${CC} -o $@ ${OBJ}
%.o : %.c
	@echo -n 'compiling $< ... '
	@${CC} -o $@ -c $<
	@echo done
archive :
	@echo 'creating archive file'
	@tar czvf ${SNAME}.tar.gz Makefile *.c *.h
	@echo 'success creating ${SNAME}.tar.gz'
install :
	#cp -f ${SNAME} ${BINDIR}
	#chmod 755 ${BINDIR}/${SNAME}
	#cp -f ${SNAME}.1 ${MANDIR}
	#gzip -9 -f ${MANDIR}/${SNAME}.1
clean :
	@echo cleaning object files
	@rm -f ${OBJ}
cleanall : clean
	@echo cleaning executable file
	@rm -f ${SNAME}
