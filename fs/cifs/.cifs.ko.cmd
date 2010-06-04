cmd_fs/cifs/cifs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/cifs/cifs.ko fs/cifs/cifs.o fs/cifs/cifs.mod.o
