cmd_fs/9p/9p.o := ld -m elf_i386   -r -o fs/9p/9p.o fs/9p/vfs_super.o fs/9p/vfs_inode.o fs/9p/vfs_addr.o fs/9p/vfs_file.o fs/9p/vfs_dir.o fs/9p/vfs_dentry.o fs/9p/v9fs.o fs/9p/fid.o fs/9p/cache.o 
