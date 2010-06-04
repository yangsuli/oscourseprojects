cmd_fs/xfs/xfs_dir2.o := gcc -Wp,-MD,fs/xfs/.xfs_dir2.o.d  -nostdinc -isystem /usr/lib/gcc/i686-redhat-linux/4.4.4/include -I/home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -m32 -msoft-float -mregparm=3 -freg-struct-return -mpreferred-stack-boundary=2 -march=i686 -mtune=generic -Wa,-mtune=generic32 -ffreestanding -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=1024 -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-dwarf2-cfi-asm -fconserve-stack -Ifs/xfs -Ifs/xfs/linux-2.6 -funsigned-char  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(xfs_dir2)"  -D"KBUILD_MODNAME=KBUILD_STR(xfs)" -D"DEBUG_HASH=15" -D"DEBUG_HASH2=47" -c -o fs/xfs/xfs_dir2.o fs/xfs/xfs_dir2.c

deps_fs/xfs/xfs_dir2.o := \
  fs/xfs/xfs_dir2.c \
  fs/xfs/xfs.h \
    $(wildcard include/config/xfs/debug.h) \
  fs/xfs/linux-2.6/xfs_linux.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/smp.h) \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
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
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/x86/32.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/posix_types_32.h \
  fs/xfs/xfs_types.h \
  fs/xfs/xfs_arch.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \
  include/linux/byteorder/generic.h \
  fs/xfs/linux-2.6/kmem.h \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/debug/slab.h) \
  include/linux/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/debug/vm.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/typecheck.h \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/cmov.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/alternative.h \
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
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  include/asm-generic/bitops/minix.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page_types.h \
  include/linux/const.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page_32_types.h \
    $(wildcard include/config/highmem4g.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/4kstacks.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/page_32.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/x86/3dnow.h) \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /usr/lib/gcc/i686-redhat-linux/4.4.4/include/stdarg.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/string.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/string_32.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/asm-generic/getorder.h \
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
    $(wildcard include/config/ftrace/mcount/record.h) \
  include/linux/linkage.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/dynamic_debug.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/div64.h \
  include/asm-generic/percpu.h \
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
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/irqflags.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/paravirt.h \
    $(wildcard include/config/highpte.h) \
    $(wildcard include/config/paravirt/spinlocks.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/compat/vdso.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable_32_types.h \
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
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/msr.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/msr-index.h \
  include/linux/ioctl.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
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
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ftrace.h \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/atomic.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/atomic_32.h \
  include/asm-generic/atomic-long.h \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/prefetch.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
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
  include/linux/wait.h \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/seqlock.h \
  include/linux/nodemask.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/memory/hotremove.h) \
  include/linux/notifier.h \
  include/linux/errno.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/rwsem.h \
  include/linux/srcu.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/smp.h \
    $(wildcard include/config/x86/io/apic.h) \
    $(wildcard include/config/x86/32/smp.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/mpspec.h \
    $(wildcard include/config/x86/numaq.h) \
    $(wildcard include/config/mca.h) \
    $(wildcard include/config/eisa.h) \
    $(wildcard include/config/x86/mpparse.h) \
    $(wildcard include/config/acpi.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/mpspec_def.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/x86_init.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/bootparam.h \
  include/linux/screen_info.h \
  include/linux/apm_bios.h \
  include/linux/edd.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/e820.h \
    $(wildcard include/config/efi.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/memtest.h) \
  include/linux/ioport.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ist.h \
  include/video/edid.h \
    $(wildcard include/config/x86.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/apic.h \
    $(wildcard include/config/x86/x2apic.h) \
  include/linux/delay.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/delay.h \
  include/linux/pm.h \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/linux/param.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/timex.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/tsc.h \
    $(wildcard include/config/x86/tsc.h) \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects/free.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/apicdef.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/fixmap.h \
    $(wildcard include/config/provide/ohci1394/dma/init.h) \
    $(wildcard include/config/x86/visws/apic.h) \
    $(wildcard include/config/x86/f00f/bug.h) \
    $(wildcard include/config/x86/cyclone/timer.h) \
    $(wildcard include/config/pci/mmconfig.h) \
    $(wildcard include/config/intel/txt.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/acpi.h \
    $(wildcard include/config/acpi/numa.h) \
  include/acpi/pdc_intel.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/numa.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/numa_32.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/mmu.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/io_apic.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/irq_vectors.h \
    $(wildcard include/config/sparse/irq.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/topology.h \
    $(wildcard include/config/x86/ht.h) \
    $(wildcard include/config/x86/64/acpi/numa.h) \
  include/asm-generic/topology.h \
  include/linux/mmdebug.h \
  include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
  include/linux/kobject.h \
  include/linux/sysfs.h \
    $(wildcard include/config/sysfs.h) \
  include/linux/kref.h \
  include/linux/kmemtrace.h \
    $(wildcard include/config/kmemtrace.h) \
  include/trace/events/kmem.h \
  include/linux/tracepoint.h \
    $(wildcard include/config/tracepoints.h) \
  include/linux/rcupdate.h \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
  include/linux/completion.h \
  include/linux/rcutree.h \
    $(wildcard include/config/no/hz.h) \
  include/trace/define_trace.h \
    $(wildcard include/config/event/tracing.h) \
  include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/detect/softlockup.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/user/sched.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/utrace.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/group/sched.h) \
    $(wildcard include/config/mm/owner.h) \
  include/linux/capability.h \
  include/linux/rbtree.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
  include/linux/auxvec.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/auxvec.h \
  include/linux/prio_tree.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ipcbuf.h \
  include/asm-generic/ipcbuf.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/sembuf.h \
  include/linux/signal.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/signal.h \
  include/asm-generic/signal-defs.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/path.h \
  include/linux/pid.h \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  include/linux/pfn.h \
  include/linux/proportions.h \
  include/linux/percpu_counter.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/seccomp.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/seccomp_32.h \
  include/linux/unistd.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/unistd.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/unistd_32.h \
  include/linux/rculist.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
  include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/sysctl.h \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/aio.h \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/linux/mm.h \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/debug/pagealloc.h) \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable_32.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable_32_types.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/pgtable-2level.h \
  include/asm-generic/pgtable.h \
  include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/s390.h) \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  fs/xfs/linux-2.6/mrlock.h \
  fs/xfs/linux-2.6/sv.h \
  fs/xfs/linux-2.6/time.h \
  fs/xfs/support/debug.h \
  fs/xfs/support/uuid.h \
  include/linux/semaphore.h \
  include/linux/blkdev.h \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/blk/dev/bsg.h) \
    $(wildcard include/config/bounce.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/linux/major.h \
  include/linux/genhd.h \
    $(wildcard include/config/fail/make/request.h) \
    $(wildcard include/config/solaris/x86/partition.h) \
    $(wildcard include/config/bsd/disklabel.h) \
    $(wildcard include/config/unixware/disklabel.h) \
    $(wildcard include/config/minix/subpartition.h) \
  include/linux/kdev_t.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
  include/linux/klist.h \
  include/linux/module.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
  include/linux/stat.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/stat.h \
  include/linux/kmod.h \
  include/linux/elf.h \
  include/linux/elf-em.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/elf.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/user.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/user_32.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/vdso.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/desc.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/ldt.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/local.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/module.h \
    $(wildcard include/config/m586.h) \
    $(wildcard include/config/m586tsc.h) \
    $(wildcard include/config/m586mmx.h) \
    $(wildcard include/config/mcore2.h) \
    $(wildcard include/config/matom.h) \
    $(wildcard include/config/m686.h) \
    $(wildcard include/config/mpentiumii.h) \
    $(wildcard include/config/mpentiumiii.h) \
    $(wildcard include/config/mpentiumm.h) \
    $(wildcard include/config/mpentium4.h) \
    $(wildcard include/config/mk6.h) \
    $(wildcard include/config/mk8.h) \
    $(wildcard include/config/x86/elan.h) \
    $(wildcard include/config/mcrusoe.h) \
    $(wildcard include/config/mefficeon.h) \
    $(wildcard include/config/mwinchipc6.h) \
    $(wildcard include/config/mwinchip3d.h) \
    $(wildcard include/config/mcyrixiii.h) \
    $(wildcard include/config/mviac3/2.h) \
    $(wildcard include/config/mviac7.h) \
    $(wildcard include/config/mgeodegx1.h) \
    $(wildcard include/config/mgeode/lx.h) \
  include/asm-generic/module.h \
  include/trace/events/module.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/device.h \
    $(wildcard include/config/dmar.h) \
    $(wildcard include/config/amd/iommu.h) \
  include/linux/pm_wakeup.h \
    $(wildcard include/config/pm.h) \
  include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/dcache.h \
  include/linux/radix-tree.h \
  include/linux/fiemap.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
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
  include/linux/pagemap.h \
  include/linux/highmem.h \
  include/linux/uaccess.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/uaccess.h \
    $(wildcard include/config/x86/wp/works/ok.h) \
    $(wildcard include/config/x86/intel/usercopy.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/uaccess_32.h \
    $(wildcard include/config/debug/strict/user/copy/checks.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/cacheflush.h \
    $(wildcard include/config/x86/pat.h) \
    $(wildcard include/config/debug/rodata.h) \
    $(wildcard include/config/debug/rodata/test.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/highmem.h \
  include/linux/interrupt.h \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/irqreturn.h \
  include/linux/irqnr.h \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/hardirq.h \
    $(wildcard include/config/x86/thermal/vector.h) \
    $(wildcard include/config/x86/mce/threshold.h) \
  include/linux/irq.h \
    $(wildcard include/config/irq/per/cpu.h) \
    $(wildcard include/config/irq/release/method.h) \
    $(wildcard include/config/intr/remap.h) \
    $(wildcard include/config/generic/pending/irq.h) \
    $(wildcard include/config/numa/irq/desc.h) \
    $(wildcard include/config/generic/hardirqs/no//do/irq.h) \
    $(wildcard include/config/cpumasks/offstack.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/irq.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/irq_regs.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/hw_irq.h \
  include/linux/profile.h \
    $(wildcard include/config/profiling.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/sections.h \
  include/asm-generic/sections.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/tlbflush.h \
  include/linux/backing-dev.h \
    $(wildcard include/config/debug/fs.h) \
  include/linux/writeback.h \
  include/linux/mempool.h \
  include/linux/bio.h \
  include/linux/ioprio.h \
  include/linux/iocontext.h \
    $(wildcard include/config/blk/cgroup.h) \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/io.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/io_32.h \
  include/asm-generic/iomap.h \
  include/linux/vmalloc.h \
  include/linux/bsg.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/scatterlist.h \
  include/asm-generic/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
  include/linux/elevator.h \
  include/linux/file.h \
  include/linux/swap.h \
    $(wildcard include/config/cgroup/mem/res/ctlr/swap.h) \
  include/linux/memcontrol.h \
    $(wildcard include/config/cgroup/mem/cont.h) \
  include/linux/cgroup.h \
  include/linux/cgroupstats.h \
  include/linux/taskstats.h \
  include/linux/prio_heap.h \
  include/linux/idr.h \
  include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/ns.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/net/cls/cgroup.h) \
  include/linux/node.h \
    $(wildcard include/config/memory/hotplug/sparse.h) \
    $(wildcard include/config/hugetlbfs.h) \
  include/linux/sysdev.h \
  include/linux/vfs.h \
  include/linux/statfs.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/statfs.h \
  include/asm-generic/statfs.h \
  include/linux/seq_file.h \
  include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  include/linux/magic.h \
  include/linux/sort.h \
  include/linux/cpu.h \
    $(wildcard include/config/arch/cpu/probe/release.h) \
    $(wildcard include/config/pm/sleep/smp.h) \
  include/linux/random.h \
  include/linux/ctype.h \
  /home/yangsuli/rpmbuild/BUILD/kernel-2.6.33/linux-2.6.33.i686/arch/x86/include/asm/unaligned.h \
  include/linux/unaligned/access_ok.h \
  include/linux/unaligned/generic.h \
  fs/xfs/linux-2.6/xfs_cred.h \
  fs/xfs/linux-2.6/xfs_vnode.h \
  fs/xfs/xfs_fs.h \
  fs/xfs/linux-2.6/xfs_stats.h \
  fs/xfs/linux-2.6/xfs_sysctl.h \
  fs/xfs/linux-2.6/xfs_iops.h \
  fs/xfs/linux-2.6/xfs_aops.h \
  fs/xfs/linux-2.6/xfs_super.h \
    $(wildcard include/config/xfs/quota.h) \
    $(wildcard include/config/xfs/posix/acl.h) \
    $(wildcard include/config/xfs/rt.h) \
    $(wildcard include/config/xfs/dmapi.h) \
  include/linux/exportfs.h \
  fs/xfs/linux-2.6/xfs_globals.h \
  fs/xfs/linux-2.6/xfs_fs_subr.h \
  fs/xfs/linux-2.6/xfs_lrw.h \
  fs/xfs/linux-2.6/xfs_buf.h \
    $(wildcard include/config/kdb/modules.h) \
  include/linux/buffer_head.h \
  fs/xfs/xfs_fs.h \
  fs/xfs/xfs_types.h \
  fs/xfs/xfs_bit.h \
  fs/xfs/xfs_log.h \
  fs/xfs/xfs_inum.h \
  fs/xfs/xfs_trans.h \
  fs/xfs/xfs_sb.h \
  fs/xfs/xfs_ag.h \
  fs/xfs/xfs_dir2.h \
  fs/xfs/xfs_dmapi.h \
  fs/xfs/linux-2.6/xfs_dmapi_priv.h \
  fs/xfs/xfs_mount.h \
  fs/xfs/linux-2.6/xfs_sync.h \
  fs/xfs/xfs_da_btree.h \
  fs/xfs/xfs_bmap_btree.h \
  fs/xfs/xfs_alloc_btree.h \
  fs/xfs/xfs_dir2_sf.h \
  fs/xfs/xfs_attr_sf.h \
  fs/xfs/xfs_dinode.h \
  fs/xfs/xfs_inode.h \
  fs/xfs/xfs_inode_item.h \
  fs/xfs/xfs_bmap.h \
  fs/xfs/xfs_dir2_data.h \
  fs/xfs/xfs_dir2_leaf.h \
  fs/xfs/xfs_dir2_block.h \
  fs/xfs/xfs_dir2_node.h \
  fs/xfs/xfs_error.h \
  fs/xfs/xfs_vnodeops.h \
  fs/xfs/linux-2.6/xfs_trace.h \

fs/xfs/xfs_dir2.o: $(deps_fs/xfs/xfs_dir2.o)

$(deps_fs/xfs/xfs_dir2.o):
