cmd_fs/efs/efs.o := ld -m elf_i386   -r -o fs/efs/efs.o fs/efs/super.o fs/efs/inode.o fs/efs/namei.o fs/efs/dir.o fs/efs/file.o fs/efs/symlink.o 
