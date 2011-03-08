BINDIR= $(DESTDIR)/usr/bin
MANDIR= $(DESTDIR)/usr/share/man/man1
CFLAGS= -Wall -std=c99 -pedantic -O3 -fomit-frame-pointer -g
CC= mpicc ${CFLAGS} 
SNAME= mnetbench
SRC= mnetbench.c linked_list.c netbench_master.c netbench_client.c netbench_algorithm.c netbench_task.c netbench_test.c netbench_test_bandwidth.c netbench_test_latency.c netbench_result.c netbench_result_bandwidth.c netbench_result_latency.c netbench_list_task.c netbench_algorithm_matrix.c netbench_communication.c netbench_list_result.c netbench_time.c netbench_printer_tool.c netbench_test_type.c netbench_printer.c options.c
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
	@tar czvf ${SNAME}.tar.gz Makefile AUTHORS COPYING README TODO *.c *.h
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
