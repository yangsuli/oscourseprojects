cmd_fs/ext2/ext2.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/ext2/ext2.ko fs/ext2/ext2.o fs/ext2/ext2.mod.o
