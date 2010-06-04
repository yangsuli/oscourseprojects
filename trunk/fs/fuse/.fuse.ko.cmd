cmd_fs/fuse/fuse.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/fuse/fuse.ko fs/fuse/fuse.o fs/fuse/fuse.mod.o
