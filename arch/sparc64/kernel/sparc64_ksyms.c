multiline_comment|/* $Id: sparc64_ksyms.c,v 1.121 2002/02/09 19:49:31 davem Exp $&n; * arch/sparc64/kernel/sparc64_ksyms.c: Sparc64 specific ksyms support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)&n; * Copyright (C) 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; */
multiline_comment|/* Tell string.h we don&squot;t want memcpy etc. as cpp defines */
DECL|macro|EXPORT_SYMTAB_STROPS
mdefine_line|#define EXPORT_SYMTAB_STROPS
DECL|macro|PROMLIB_INTERNAL
mdefine_line|#define PROMLIB_INTERNAL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs_struct.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/compat.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/svr4.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mostek.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/fpumacro.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#ifdef CONFIG_SBUS
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/isa.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/ns87303.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/cpudata.h&gt;
macro_line|#include &lt;asm/rwsem.h&gt;
DECL|struct|poll
r_struct
id|poll
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|events
r_int
id|events
suffix:semicolon
DECL|member|revents
r_int
id|revents
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
id|pid_t
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_void
id|_sigpause_common
(paren
r_int
r_int
id|set
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__bzero
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memscan_zero
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memscan_generic
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__memcmp
c_func
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
id|__kernel_size_t
id|strlen
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|linux_sparc_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtrap
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|solaris_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u32
id|sunos_sys_table
(braket
)braket
comma
id|sys_call_table32
(braket
)braket
suffix:semicolon
r_extern
r_void
id|tl0_solaris
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sys_sigsuspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|svr4_getcontext
c_func
(paren
id|svr4_ucontext_t
op_star
id|uc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|svr4_setcontext
c_func
(paren
id|svr4_ucontext_t
op_star
id|uc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|compat_sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
id|u32
id|arg
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|handle_mathemu
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|fpustate
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sparc32_open
c_func
(paren
r_const
r_char
id|__user
op_star
id|filename
comma
r_int
id|flags
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|io_remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
suffix:semicolon
r_extern
r_int
id|io_remap_pfn_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|pfn
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|prom_palette
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__ashrdi3
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SMP) &amp;&amp; defined(CONFIG_DEBUG_SPINLOCK)
r_extern
r_void
id|_do_spin_lock
(paren
id|spinlock_t
op_star
id|lock
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_spin_unlock
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|_spin_trylock
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_do_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_int
id|_do_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|phys_base
suffix:semicolon
r_extern
r_int
r_int
id|pfn_base
suffix:semicolon
r_extern
r_int
r_int
id|sys_call_table
(braket
)braket
suffix:semicolon
r_extern
r_void
id|xor_vis_2
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xor_vis_3
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xor_vis_4
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xor_vis_5
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* Per-CPU information table */
DECL|variable|__cpu_data
id|EXPORT_PER_CPU_SYMBOL
c_func
(paren
id|__cpu_data
)paren
suffix:semicolon
multiline_comment|/* used by various drivers */
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef CONFIG_DEBUG_SPINLOCK
multiline_comment|/* Out of line rw-locking implementation. */
DECL|variable|__read_lock
id|EXPORT_SYMBOL
c_func
(paren
id|__read_lock
)paren
suffix:semicolon
DECL|variable|__read_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|__read_unlock
)paren
suffix:semicolon
DECL|variable|__write_lock
id|EXPORT_SYMBOL
c_func
(paren
id|__write_lock
)paren
suffix:semicolon
DECL|variable|__write_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|__write_unlock
)paren
suffix:semicolon
DECL|variable|__write_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__write_trylock
)paren
suffix:semicolon
multiline_comment|/* Out of line spin-locking implementation. */
DECL|variable|_raw_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_spin_lock
)paren
suffix:semicolon
DECL|variable|_raw_spin_lock_flags
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_spin_lock_flags
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Hard IRQ locking */
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_MCOUNT)
r_extern
r_void
id|_mcount
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|_mcount
id|EXPORT_SYMBOL
c_func
(paren
id|_mcount
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* CPU online map and active count.  */
DECL|variable|cpu_online_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
DECL|variable|phys_cpu_present_map
id|EXPORT_SYMBOL
c_func
(paren
id|phys_cpu_present_map
)paren
suffix:semicolon
multiline_comment|/* Spinlock debugging library, optional. */
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
DECL|variable|_do_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_spin_lock
)paren
suffix:semicolon
DECL|variable|_do_spin_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_spin_unlock
)paren
suffix:semicolon
DECL|variable|_spin_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_trylock
)paren
suffix:semicolon
DECL|variable|_do_read_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_read_lock
)paren
suffix:semicolon
DECL|variable|_do_read_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_read_unlock
)paren
suffix:semicolon
DECL|variable|_do_write_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_write_lock
)paren
suffix:semicolon
DECL|variable|_do_write_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_write_unlock
)paren
suffix:semicolon
DECL|variable|_do_write_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|_do_write_trylock
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|variable|sparc64_get_clock_tick
id|EXPORT_SYMBOL
c_func
(paren
id|sparc64_get_clock_tick
)paren
suffix:semicolon
multiline_comment|/* semaphores */
DECL|variable|down
id|EXPORT_SYMBOL
c_func
(paren
id|down
)paren
suffix:semicolon
DECL|variable|down_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|down_trylock
)paren
suffix:semicolon
DECL|variable|down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|down_interruptible
)paren
suffix:semicolon
DECL|variable|up
id|EXPORT_SYMBOL
c_func
(paren
id|up
)paren
suffix:semicolon
multiline_comment|/* RW semaphores */
DECL|variable|__down_read
id|EXPORT_SYMBOL
c_func
(paren
id|__down_read
)paren
suffix:semicolon
DECL|variable|__down_read_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_read_trylock
)paren
suffix:semicolon
DECL|variable|__down_write
id|EXPORT_SYMBOL
c_func
(paren
id|__down_write
)paren
suffix:semicolon
DECL|variable|__down_write_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_write_trylock
)paren
suffix:semicolon
DECL|variable|__up_read
id|EXPORT_SYMBOL
c_func
(paren
id|__up_read
)paren
suffix:semicolon
DECL|variable|__up_write
id|EXPORT_SYMBOL
c_func
(paren
id|__up_write
)paren
suffix:semicolon
DECL|variable|__downgrade_write
id|EXPORT_SYMBOL
c_func
(paren
id|__downgrade_write
)paren
suffix:semicolon
multiline_comment|/* Atomic counter implementation. */
DECL|variable|atomic_add
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_add
)paren
suffix:semicolon
DECL|variable|atomic_add_ret
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_add_ret
)paren
suffix:semicolon
DECL|variable|atomic_sub
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_sub
)paren
suffix:semicolon
DECL|variable|atomic_sub_ret
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_sub_ret
)paren
suffix:semicolon
DECL|variable|atomic64_add
id|EXPORT_SYMBOL
c_func
(paren
id|atomic64_add
)paren
suffix:semicolon
DECL|variable|atomic64_add_ret
id|EXPORT_SYMBOL
c_func
(paren
id|atomic64_add_ret
)paren
suffix:semicolon
DECL|variable|atomic64_sub
id|EXPORT_SYMBOL
c_func
(paren
id|atomic64_sub
)paren
suffix:semicolon
DECL|variable|atomic64_sub_ret
id|EXPORT_SYMBOL
c_func
(paren
id|atomic64_sub_ret
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|_atomic_dec_and_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_atomic_dec_and_lock
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Atomic bit operations. */
DECL|variable|test_and_set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_set_bit
)paren
suffix:semicolon
DECL|variable|test_and_clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_clear_bit
)paren
suffix:semicolon
DECL|variable|test_and_change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_change_bit
)paren
suffix:semicolon
DECL|variable|set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|set_bit
)paren
suffix:semicolon
DECL|variable|clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|clear_bit
)paren
suffix:semicolon
DECL|variable|change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|change_bit
)paren
suffix:semicolon
multiline_comment|/* Bit searching */
DECL|variable|find_next_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_bit
)paren
suffix:semicolon
DECL|variable|find_next_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_bit
)paren
suffix:semicolon
DECL|variable|find_next_zero_le_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_le_bit
)paren
suffix:semicolon
DECL|variable|ivector_table
id|EXPORT_SYMBOL
c_func
(paren
id|ivector_table
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|__flushw_user
id|EXPORT_SYMBOL
c_func
(paren
id|__flushw_user
)paren
suffix:semicolon
DECL|variable|tlb_type
id|EXPORT_SYMBOL
c_func
(paren
id|tlb_type
)paren
suffix:semicolon
DECL|variable|get_fb_unmapped_area
id|EXPORT_SYMBOL
c_func
(paren
id|get_fb_unmapped_area
)paren
suffix:semicolon
DECL|variable|flush_icache_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_icache_range
)paren
suffix:semicolon
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
macro_line|#ifdef DCACHE_ALIASING_POSSIBLE
DECL|variable|__flush_dcache_range
id|EXPORT_SYMBOL
c_func
(paren
id|__flush_dcache_range
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|mostek_lock
id|EXPORT_SYMBOL
c_func
(paren
id|mostek_lock
)paren
suffix:semicolon
DECL|variable|mstk48t02_regs
id|EXPORT_SYMBOL
c_func
(paren
id|mstk48t02_regs
)paren
suffix:semicolon
DECL|variable|request_fast_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_fast_irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_AUXIO
DECL|variable|auxio_set_led
id|EXPORT_SYMBOL
c_func
(paren
id|auxio_set_led
)paren
suffix:semicolon
DECL|variable|auxio_set_lte
id|EXPORT_SYMBOL
c_func
(paren
id|auxio_set_lte
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SBUS
DECL|variable|sbus_root
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_root
)paren
suffix:semicolon
DECL|variable|dma_chain
id|EXPORT_SYMBOL
c_func
(paren
id|dma_chain
)paren
suffix:semicolon
DECL|variable|sbus_set_sbus64
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_set_sbus64
)paren
suffix:semicolon
DECL|variable|sbus_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_alloc_consistent
)paren
suffix:semicolon
DECL|variable|sbus_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_free_consistent
)paren
suffix:semicolon
DECL|variable|sbus_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_map_single
)paren
suffix:semicolon
DECL|variable|sbus_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_unmap_single
)paren
suffix:semicolon
DECL|variable|sbus_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_map_sg
)paren
suffix:semicolon
DECL|variable|sbus_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_unmap_sg
)paren
suffix:semicolon
DECL|variable|sbus_dma_sync_single_for_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_dma_sync_single_for_cpu
)paren
suffix:semicolon
DECL|variable|sbus_dma_sync_single_for_device
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_dma_sync_single_for_device
)paren
suffix:semicolon
DECL|variable|sbus_dma_sync_sg_for_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_dma_sync_sg_for_cpu
)paren
suffix:semicolon
DECL|variable|sbus_dma_sync_sg_for_device
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_dma_sync_sg_for_device
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|outsb
id|EXPORT_SYMBOL
c_func
(paren
id|outsb
)paren
suffix:semicolon
DECL|variable|outsw
id|EXPORT_SYMBOL
c_func
(paren
id|outsw
)paren
suffix:semicolon
DECL|variable|outsl
id|EXPORT_SYMBOL
c_func
(paren
id|outsl
)paren
suffix:semicolon
DECL|variable|insb
id|EXPORT_SYMBOL
c_func
(paren
id|insb
)paren
suffix:semicolon
DECL|variable|insw
id|EXPORT_SYMBOL
c_func
(paren
id|insw
)paren
suffix:semicolon
DECL|variable|insl
id|EXPORT_SYMBOL
c_func
(paren
id|insl
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|variable|ebus_chain
id|EXPORT_SYMBOL
c_func
(paren
id|ebus_chain
)paren
suffix:semicolon
DECL|variable|isa_chain
id|EXPORT_SYMBOL
c_func
(paren
id|isa_chain
)paren
suffix:semicolon
DECL|variable|pci_memspace_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_memspace_mask
)paren
suffix:semicolon
DECL|variable|pci_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|pci_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_free_consistent
)paren
suffix:semicolon
DECL|variable|pci_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_map_single
)paren
suffix:semicolon
DECL|variable|pci_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_single
)paren
suffix:semicolon
DECL|variable|pci_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|pci_map_sg
)paren
suffix:semicolon
DECL|variable|pci_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_sg
)paren
suffix:semicolon
DECL|variable|pci_dma_sync_single_for_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dma_sync_single_for_cpu
)paren
suffix:semicolon
DECL|variable|pci_dma_sync_sg_for_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dma_sync_sg_for_cpu
)paren
suffix:semicolon
DECL|variable|pci_dma_supported
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dma_supported
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* I/O device mmaping on Sparc64. */
DECL|variable|io_remap_page_range
id|EXPORT_SYMBOL
c_func
(paren
id|io_remap_page_range
)paren
suffix:semicolon
DECL|variable|io_remap_pfn_range
id|EXPORT_SYMBOL
c_func
(paren
id|io_remap_pfn_range
)paren
suffix:semicolon
multiline_comment|/* Solaris/SunOS binary compatibility */
DECL|variable|_sigpause_common
id|EXPORT_SYMBOL
c_func
(paren
id|_sigpause_common
)paren
suffix:semicolon
DECL|variable|verify_compat_iovec
id|EXPORT_SYMBOL
c_func
(paren
id|verify_compat_iovec
)paren
suffix:semicolon
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|dump_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_fpu
)paren
suffix:semicolon
DECL|variable|__pte_alloc_one_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|__pte_alloc_one_kernel
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|variable|pgt_quicklists
id|EXPORT_SYMBOL
c_func
(paren
id|pgt_quicklists
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|put_fs_struct
id|EXPORT_SYMBOL
c_func
(paren
id|put_fs_struct
)paren
suffix:semicolon
multiline_comment|/* math-emu wants this */
DECL|variable|die_if_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|die_if_kernel
)paren
suffix:semicolon
multiline_comment|/* Kernel thread creation. */
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
multiline_comment|/* prom symbols */
DECL|variable|idprom
id|EXPORT_SYMBOL
c_func
(paren
id|idprom
)paren
suffix:semicolon
DECL|variable|prom_root_node
id|EXPORT_SYMBOL
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
DECL|variable|prom_getchild
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getchild
)paren
suffix:semicolon
DECL|variable|prom_getsibling
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getsibling
)paren
suffix:semicolon
DECL|variable|prom_searchsiblings
id|EXPORT_SYMBOL
c_func
(paren
id|prom_searchsiblings
)paren
suffix:semicolon
DECL|variable|prom_firstprop
id|EXPORT_SYMBOL
c_func
(paren
id|prom_firstprop
)paren
suffix:semicolon
DECL|variable|prom_nextprop
id|EXPORT_SYMBOL
c_func
(paren
id|prom_nextprop
)paren
suffix:semicolon
DECL|variable|prom_getproplen
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getproplen
)paren
suffix:semicolon
DECL|variable|prom_getproperty
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getproperty
)paren
suffix:semicolon
DECL|variable|prom_node_has_property
id|EXPORT_SYMBOL
c_func
(paren
id|prom_node_has_property
)paren
suffix:semicolon
DECL|variable|prom_setprop
id|EXPORT_SYMBOL
c_func
(paren
id|prom_setprop
)paren
suffix:semicolon
DECL|variable|saved_command_line
id|EXPORT_SYMBOL
c_func
(paren
id|saved_command_line
)paren
suffix:semicolon
DECL|variable|prom_getname
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getname
)paren
suffix:semicolon
DECL|variable|prom_finddevice
id|EXPORT_SYMBOL
c_func
(paren
id|prom_finddevice
)paren
suffix:semicolon
DECL|variable|prom_feval
id|EXPORT_SYMBOL
c_func
(paren
id|prom_feval
)paren
suffix:semicolon
DECL|variable|prom_getbool
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getbool
)paren
suffix:semicolon
DECL|variable|prom_getstring
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getstring
)paren
suffix:semicolon
DECL|variable|prom_getint
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getint
)paren
suffix:semicolon
DECL|variable|prom_getintdefault
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getintdefault
)paren
suffix:semicolon
DECL|variable|__prom_getchild
id|EXPORT_SYMBOL
c_func
(paren
id|__prom_getchild
)paren
suffix:semicolon
DECL|variable|__prom_getsibling
id|EXPORT_SYMBOL
c_func
(paren
id|__prom_getsibling
)paren
suffix:semicolon
multiline_comment|/* sparc library symbols */
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|__strlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strlen_user
)paren
suffix:semicolon
DECL|variable|__strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strnlen_user
)paren
suffix:semicolon
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SOLARIS_EMUL_MODULE
DECL|variable|linux_sparc_syscall
id|EXPORT_SYMBOL
c_func
(paren
id|linux_sparc_syscall
)paren
suffix:semicolon
DECL|variable|rtrap
id|EXPORT_SYMBOL
c_func
(paren
id|rtrap
)paren
suffix:semicolon
DECL|variable|show_regs
id|EXPORT_SYMBOL
c_func
(paren
id|show_regs
)paren
suffix:semicolon
DECL|variable|solaris_syscall
id|EXPORT_SYMBOL
c_func
(paren
id|solaris_syscall
)paren
suffix:semicolon
DECL|variable|syscall_trace
id|EXPORT_SYMBOL
c_func
(paren
id|syscall_trace
)paren
suffix:semicolon
DECL|variable|sunos_sys_table
id|EXPORT_SYMBOL
c_func
(paren
id|sunos_sys_table
)paren
suffix:semicolon
DECL|variable|sys_call_table32
id|EXPORT_SYMBOL
c_func
(paren
id|sys_call_table32
)paren
suffix:semicolon
DECL|variable|tl0_solaris
id|EXPORT_SYMBOL
c_func
(paren
id|tl0_solaris
)paren
suffix:semicolon
DECL|variable|sys_sigsuspend
id|EXPORT_SYMBOL
c_func
(paren
id|sys_sigsuspend
)paren
suffix:semicolon
DECL|variable|sys_getppid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_getppid
)paren
suffix:semicolon
DECL|variable|sys_getpid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_getpid
)paren
suffix:semicolon
DECL|variable|sys_geteuid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_geteuid
)paren
suffix:semicolon
DECL|variable|sys_getuid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_getuid
)paren
suffix:semicolon
DECL|variable|sys_getegid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_getegid
)paren
suffix:semicolon
DECL|variable|sys_getgid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_getgid
)paren
suffix:semicolon
DECL|variable|svr4_getcontext
id|EXPORT_SYMBOL
c_func
(paren
id|svr4_getcontext
)paren
suffix:semicolon
DECL|variable|svr4_setcontext
id|EXPORT_SYMBOL
c_func
(paren
id|svr4_setcontext
)paren
suffix:semicolon
DECL|variable|compat_sys_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|compat_sys_ioctl
)paren
suffix:semicolon
DECL|variable|sparc32_open
id|EXPORT_SYMBOL
c_func
(paren
id|sparc32_open
)paren
suffix:semicolon
DECL|variable|sys_close
id|EXPORT_SYMBOL
c_func
(paren
id|sys_close
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Special internal versions of library functions. */
DECL|variable|_clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|_clear_page
)paren
suffix:semicolon
DECL|variable|clear_user_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_user_page
)paren
suffix:semicolon
DECL|variable|copy_user_page
id|EXPORT_SYMBOL
c_func
(paren
id|copy_user_page
)paren
suffix:semicolon
DECL|variable|__bzero
id|EXPORT_SYMBOL
c_func
(paren
id|__bzero
)paren
suffix:semicolon
DECL|variable|__memscan_zero
id|EXPORT_SYMBOL
c_func
(paren
id|__memscan_zero
)paren
suffix:semicolon
DECL|variable|__memscan_generic
id|EXPORT_SYMBOL
c_func
(paren
id|__memscan_generic
)paren
suffix:semicolon
DECL|variable|__memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|__memcmp
)paren
suffix:semicolon
DECL|variable|__memset
id|EXPORT_SYMBOL
c_func
(paren
id|__memset
)paren
suffix:semicolon
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_nocheck
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_nocheck
)paren
suffix:semicolon
DECL|variable|__csum_partial_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__csum_partial_copy_from_user
)paren
suffix:semicolon
DECL|variable|__csum_partial_copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|__csum_partial_copy_to_user
)paren
suffix:semicolon
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
multiline_comment|/* Moving data to/from/in userspace. */
DECL|variable|___copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|___copy_to_user
)paren
suffix:semicolon
DECL|variable|___copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|___copy_from_user
)paren
suffix:semicolon
DECL|variable|___copy_in_user
id|EXPORT_SYMBOL
c_func
(paren
id|___copy_in_user
)paren
suffix:semicolon
DECL|variable|copy_to_user_fixup
id|EXPORT_SYMBOL
c_func
(paren
id|copy_to_user_fixup
)paren
suffix:semicolon
DECL|variable|copy_from_user_fixup
id|EXPORT_SYMBOL
c_func
(paren
id|copy_from_user_fixup
)paren
suffix:semicolon
DECL|variable|copy_in_user_fixup
id|EXPORT_SYMBOL
c_func
(paren
id|copy_in_user_fixup
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user
)paren
suffix:semicolon
DECL|variable|__bzero_noasi
id|EXPORT_SYMBOL
c_func
(paren
id|__bzero_noasi
)paren
suffix:semicolon
multiline_comment|/* Various address conversion macros use this. */
DECL|variable|phys_base
id|EXPORT_SYMBOL
c_func
(paren
id|phys_base
)paren
suffix:semicolon
DECL|variable|pfn_base
id|EXPORT_SYMBOL
c_func
(paren
id|pfn_base
)paren
suffix:semicolon
DECL|variable|sparc64_valid_addr_bitmap
id|EXPORT_SYMBOL
c_func
(paren
id|sparc64_valid_addr_bitmap
)paren
suffix:semicolon
DECL|variable|page_to_pfn
id|EXPORT_SYMBOL
c_func
(paren
id|page_to_pfn
)paren
suffix:semicolon
DECL|variable|pfn_to_page
id|EXPORT_SYMBOL
c_func
(paren
id|pfn_to_page
)paren
suffix:semicolon
multiline_comment|/* No version information on this, heavily used in inline asm,&n; * and will always be &squot;void __ret_efault(void)&squot;.&n; */
DECL|variable|__ret_efault
id|EXPORT_SYMBOL
c_func
(paren
id|__ret_efault
)paren
suffix:semicolon
multiline_comment|/* No version information on these, as gcc produces such symbols. */
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
multiline_comment|/* Delay routines. */
DECL|variable|__udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__udelay
)paren
suffix:semicolon
DECL|variable|__ndelay
id|EXPORT_SYMBOL
c_func
(paren
id|__ndelay
)paren
suffix:semicolon
DECL|variable|__const_udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__const_udelay
)paren
suffix:semicolon
DECL|variable|__delay
id|EXPORT_SYMBOL
c_func
(paren
id|__delay
)paren
suffix:semicolon
r_void
id|VISenter
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* RAID code needs this */
DECL|variable|VISenter
id|EXPORT_SYMBOL
c_func
(paren
id|VISenter
)paren
suffix:semicolon
multiline_comment|/* for input/keybdev */
DECL|variable|sun_do_break
id|EXPORT_SYMBOL
c_func
(paren
id|sun_do_break
)paren
suffix:semicolon
DECL|variable|serial_console
id|EXPORT_SYMBOL
c_func
(paren
id|serial_console
)paren
suffix:semicolon
DECL|variable|stop_a_enabled
id|EXPORT_SYMBOL
c_func
(paren
id|stop_a_enabled
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
DECL|variable|do_BUG
id|EXPORT_SYMBOL
c_func
(paren
id|do_BUG
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* for ns8703 */
DECL|variable|ns87303_lock
id|EXPORT_SYMBOL
c_func
(paren
id|ns87303_lock
)paren
suffix:semicolon
multiline_comment|/* for solaris compat module */
DECL|variable|sys_call_table
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sys_call_table
)paren
suffix:semicolon
DECL|variable|tick_ops
id|EXPORT_SYMBOL
c_func
(paren
id|tick_ops
)paren
suffix:semicolon
DECL|variable|xor_vis_2
id|EXPORT_SYMBOL
c_func
(paren
id|xor_vis_2
)paren
suffix:semicolon
DECL|variable|xor_vis_3
id|EXPORT_SYMBOL
c_func
(paren
id|xor_vis_3
)paren
suffix:semicolon
DECL|variable|xor_vis_4
id|EXPORT_SYMBOL
c_func
(paren
id|xor_vis_4
)paren
suffix:semicolon
DECL|variable|xor_vis_5
id|EXPORT_SYMBOL
c_func
(paren
id|xor_vis_5
)paren
suffix:semicolon
DECL|variable|prom_palette
id|EXPORT_SYMBOL
c_func
(paren
id|prom_palette
)paren
suffix:semicolon
eof
