cmd_fs/jfs/jfs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/jfs/jfs.ko fs/jfs/jfs.o fs/jfs/jfs.mod.o
