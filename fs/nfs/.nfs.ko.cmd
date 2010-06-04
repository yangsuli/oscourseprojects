cmd_fs/nfs/nfs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/nfs/nfs.ko fs/nfs/nfs.o fs/nfs/nfs.mod.o
