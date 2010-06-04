cmd_fs/quota/built-in.o :=  ld -m elf_i386   -r -o fs/quota/built-in.o fs/quota/dquot.o fs/quota/quota_v2.o fs/quota/quota_tree.o fs/quota/quota.o 
