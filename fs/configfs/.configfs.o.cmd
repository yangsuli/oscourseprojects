cmd_fs/configfs/configfs.o := ld -m elf_i386   -r -o fs/configfs/configfs.o fs/configfs/inode.o fs/configfs/file.o fs/configfs/dir.o fs/configfs/symlink.o fs/configfs/mount.o fs/configfs/item.o 
