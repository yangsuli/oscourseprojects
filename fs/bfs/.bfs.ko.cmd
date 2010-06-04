cmd_fs/bfs/bfs.ko := ld -r -m elf_i386 -T /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/scripts/module-common.lds --build-id -o fs/bfs/bfs.ko fs/bfs/bfs.o fs/bfs/bfs.mod.o
