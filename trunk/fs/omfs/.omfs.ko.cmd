cmd_fs/omfs/omfs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/omfs/omfs.ko fs/omfs/omfs.o fs/omfs/omfs.mod.o
