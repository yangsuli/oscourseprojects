cmd_fs/xfs/xfs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/xfs/xfs.ko fs/xfs/xfs.o fs/xfs/xfs.mod.o
