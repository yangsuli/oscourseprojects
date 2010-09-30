all: context tlb disk

context:context.c hw1.h
	gcc -O0 -lrt -D_GNU_SOURCE -o context context.c

tlb:tlb.c hw1.h
	gcc -O0 -lrt -D_GNU_SOURCE -o tlb tlb.c

tlb2:tlb2.c hw1.h
	gcc -O0 -lrt -D_GNU_SOURCE -o tlb2 tlb2.c

disk:disk.c hw1.h
	gcc -O0 -lrt -D_GNU_SOURCE -o disk disk.c

clean:
	rm -rf context tlb


