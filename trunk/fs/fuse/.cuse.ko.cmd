cmd_fs/fuse/cuse.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/fuse/cuse.ko fs/fuse/cuse.o fs/fuse/cuse.mod.o
