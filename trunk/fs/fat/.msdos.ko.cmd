cmd_fs/fat/msdos.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/fat/msdos.ko fs/fat/msdos.o fs/fat/msdos.mod.o
