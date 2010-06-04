cmd_fs/efs/efs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/efs/efs.ko fs/efs/efs.o fs/efs/efs.mod.o
