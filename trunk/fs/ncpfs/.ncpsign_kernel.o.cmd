cmd_fs/ncpfs/ncpsign_kernel.o := gcc -Wp,-MD,fs/ncpfs/.ncpsign_kernel.o.d  -nostdinc -isystem /usr/lib/gcc/i686-redhat-linux/4.4.4/include -I/home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -m32 -msoft-float -mregparm=3 -freg-struct-return -mpreferred-stack-boundary=2 -march=i686 -mtune=generic -Wa,-mtune=generic32 -ffreestanding -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=1024 -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-dwarf2-cfi-asm -fconserve-stack  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ncpsign_kernel)"  -D"KBUILD_MODNAME=KBUILD_STR(ncpfs)" -D"DEBUG_HASH=1" -D"DEBUG_HASH2=31" -c -o fs/ncpfs/ncpsign_kernel.o fs/ncpfs/ncpsign_kernel.c

deps_fs/ncpfs/ncpsign_kernel.o := \
  fs/ncpfs/ncpsign_kernel.c \
    $(wildcard include/config/ncpfs/packet/signing.h) \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/types.h \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/highmem64g.h) \
  include/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/x86/32.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/posix_types_32.h \
  /usr/lib/gcc/i686-redhat-linux/4.4.4/include/stdarg.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/string.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/string_32.h \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/kmemcheck.h) \
  include/linux/ncp.h \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/cmov.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/paravirt.h) \
  include/linux/stringify.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/asm.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cpufeature.h \
    $(wildcard include/config/x86/invlpg.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/minix.h \
  fs/ncpfs/ncpsign_kernel.h \
  include/linux/ncp_fs.h \
    $(wildcard include/config/ncpfs/extras.h) \
    $(wildcard include/config/ncpfs/nfs/ns.h) \
    $(wildcard include/config/ncpfs/smalldos.h) \
    $(wildcard include/config/ncpfs/os2/ns.h) \
  include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/linkage.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  include/linux/wait.h \
    $(wildcard include/config/lockdep.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/prefetch.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/processor.h \
    $(wildcard include/config/x86/vsmp.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/m386.h) \
    $(wildcard include/config/m486.h) \
    $(wildcard include/config/x86/debugctlmsr.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/vm86.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/vm86.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ptrace.h \
    $(wildcard include/config/x86/ptrace/bts.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ptrace-abi.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/segment.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page_types.h \
  include/linux/const.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page_32_types.h \
    $(wildcard include/config/highmem4g.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/4kstacks.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/math_emu.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/sigcontext.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/current.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/percpu.h \
    $(wildcard include/config/x86/64/smp.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
  include/linux/dynamic_debug.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/div64.h \
  include/asm-generic/percpu.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/system.h \
    $(wildcard include/config/ia32/emulation.h) \
    $(wildcard include/config/x86/32/lazy/gs.h) \
    $(wildcard include/config/x86/ppro/fence.h) \
    $(wildcard include/config/x86/oostore.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cmpxchg.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cmpxchg_32.h \
    $(wildcard include/config/x86/cmpxchg.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/nops.h \
    $(wildcard include/config/mk7.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/irqflags.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/paravirt.h \
    $(wildcard include/config/highpte.h) \
    $(wildcard include/config/paravirt/spinlocks.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/compat/vdso.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable_32_types.h \
    $(wildcard include/config/highmem.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable-2level_types.h \
  include/asm-generic/pgtable-nopud.h \
  include/asm-generic/pgtable-nopmd.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/paravirt_types.h \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/paravirt/debug.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/desc_defs.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/kmap_types.h \
    $(wildcard include/config/debug/highmem.h) \
  include/asm-generic/kmap_types.h \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/bitmap.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page_32.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/x86/3dnow.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  include/asm-generic/getorder.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/msr.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/msr-index.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cpumask.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ds.h \
    $(wildcard include/config/x86/ds.h) \
  include/linux/err.h \
  include/linux/personality.h \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
    $(wildcard include/config/x86/internode/cache/shift.h) \
  include/linux/math64.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  include/linux/preempt.h \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ftrace.h \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/atomic.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/atomic_32.h \
  include/asm-generic/atomic-long.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/generic/hardirqs.h) \
  include/linux/rwlock_types.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/spinlock.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/rwlock.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/inline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
  include/linux/seqlock.h \
  include/linux/completion.h \
  include/linux/rcutree.h \
    $(wildcard include/config/no/hz.h) \
  include/linux/path.h \
  include/linux/stat.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/stat.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/kobject.h \
  include/linux/sysfs.h \
  include/linux/errno.h \
  include/linux/kref.h \
  include/linux/radix-tree.h \
  include/linux/prio_tree.h \
  include/linux/pid.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  include/linux/capability.h \
  include/linux/semaphore.h \
  include/linux/fiemap.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/rwsem.h \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/inet.h \
  include/linux/fcntl.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
  include/linux/in.h \
  include/linux/socket.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/socket.h \
  include/asm-generic/socket.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/sockios.h \
  include/asm-generic/sockios.h \
  include/linux/sockios.h \
  include/linux/uio.h \
  include/linux/magic.h \
  include/linux/ipx.h \
  include/linux/ncp_no.h \
  include/linux/ncp_fs_i.h \
  include/linux/ncp_fs_sb.h \
  include/linux/ncp_mount.h \
  include/linux/net.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/random.h \
  include/linux/irqnr.h \
  include/linux/kmemcheck.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/mmu/notifier.h) \
  include/linux/auxvec.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/auxvec.h \
  include/linux/rbtree.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/mmu.h \
  include/linux/sysctl.h \
  include/linux/ratelimit.h \
  include/linux/param.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/jiffies.h \
  include/linux/timex.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/timex.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/tsc.h \
    $(wildcard include/config/x86/tsc.h) \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \

fs/ncpfs/ncpsign_kernel.o: $(deps_fs/ncpfs/ncpsign_kernel.o)

$(deps_fs/ncpfs/ncpsign_kernel.o):
