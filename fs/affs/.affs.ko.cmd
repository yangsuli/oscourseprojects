cmd_fs/affs/affs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/affs/affs.ko fs/affs/affs.o fs/affs/affs.mod.o
