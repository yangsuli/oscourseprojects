cmd_fs/ufs/ufs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/ufs/ufs.ko fs/ufs/ufs.o fs/ufs/ufs.mod.o
