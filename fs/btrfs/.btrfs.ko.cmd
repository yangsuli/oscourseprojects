cmd_fs/btrfs/btrfs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/btrfs/btrfs.ko fs/btrfs/btrfs.o fs/btrfs/btrfs.mod.o
