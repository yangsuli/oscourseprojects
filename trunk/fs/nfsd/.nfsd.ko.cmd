cmd_fs/nfsd/nfsd.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/nfsd/nfsd.ko fs/nfsd/nfsd.o fs/nfsd/nfsd.mod.o
