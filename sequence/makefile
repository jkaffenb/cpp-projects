testseq: testseq.o sequence.o
	g++ -o testseq testseq.o sequence.o

testseq.o: testseq.cc sequence.h
	g++ -c testseq.cc

sequence.o: sequence.cc sequence.h
	g++ -c sequence.cc

clean:
	rm -f *.o testseq
