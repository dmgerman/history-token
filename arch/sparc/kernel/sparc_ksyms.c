multiline_comment|/* $Id: sparc_ksyms.c,v 1.107 2001/07/17 16:17:33 anton Exp $&n; * arch/sparc/kernel/ksyms.c: Sparc specific ksyms support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)&n; */
multiline_comment|/* Tell string.h we don&squot;t want memcpy etc. as cpp defines */
DECL|macro|EXPORT_SYMTAB_STROPS
mdefine_line|#define EXPORT_SYMTAB_STROPS
DECL|macro|PROMLIB_INTERNAL
mdefine_line|#define PROMLIB_INTERNAL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#ifdef CONFIG_HIGHMEM
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/svr4.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mostek.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#ifdef CONFIG_SBUS
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/io-unit.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
r_extern
id|spinlock_t
id|rtc_lock
suffix:semicolon
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
r_int
id|svr4_getcontext
(paren
id|svr4_ucontext_t
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|svr4_setcontext
(paren
id|svr4_ucontext_t
op_star
comma
r_struct
id|pt_regs
op_star
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
(paren
op_star
id|__copy_1page
)paren
(paren
r_void
op_star
comma
r_const
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__memmove
c_func
(paren
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
r_void
(paren
op_star
id|bzero_1page
)paren
(paren
r_void
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
r_int
id|__strncmp
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
r_extern
r_void
id|bcopy
(paren
r_const
r_char
op_star
comma
r_char
op_star
comma
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
r_int
id|__ashldi3
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__lshrdi3
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__muldi3
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__divdi3
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
multiline_comment|/* Private functions with odd calling conventions. */
r_extern
r_void
id|___atomic24_add
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|___atomic24_sub
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|___set_bit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|___clear_bit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|___change_bit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* One thing to note is that the way the symbols of the mul/div&n; * support routines are named is a mess, they all start with&n; * a &squot;.&squot; which makes it a bitch to export, here is the trick:&n; */
multiline_comment|/* If the interface of any of these special functions does ever&n; * change in an incompatible way, you must modify this.&n; */
DECL|macro|DOT_PROTO
mdefine_line|#define DOT_PROTO(sym) extern int __dot_##sym(int, int)
macro_line|#ifdef __GENKSYMS__
DECL|macro|EXPORT_SYMBOL_DOT
mdefine_line|#define EXPORT_SYMBOL_DOT(sym)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DOT_PROTO(sym);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;EXPORT_SYMBOL(__dot_ ## sym)
macro_line|#else /* !__GENKSYMS__ */
DECL|macro|EXPORT_SYMBOL_DOT
mdefine_line|#define EXPORT_SYMBOL_DOT(sym)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DOT_PROTO(sym) __asm__(&quot;.&quot; # sym);&t;&t;&t;&t;&bslash;&n;&t;__CRC_SYMBOL(__dot_##sym, &quot;&quot;)&t;&t;&t;&t;&t;&bslash;&n;&t;static const char __kstrtab___dot_##sym[]&t;&t;&t;&bslash;&n;&t;__attribute__((section(&quot;__ksymtab_strings&quot;)))&t;&t;&t;&bslash;&n;&t;= &quot;.&quot; #sym;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static const struct kernel_symbol __ksymtab___dot_##sym&t;&t;&bslash;&n;&t;__attribute__((section(&quot;__ksymtab&quot;)))&t;&t;&t;&t;&bslash;&n;&t;= { (unsigned long)&amp;__dot_##sym, __kstrtab___dot_##sym }
macro_line|#endif
multiline_comment|/* used by various drivers */
DECL|variable|sparc_cpu_model
id|EXPORT_SYMBOL
c_func
(paren
id|sparc_cpu_model
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
macro_line|#ifdef CONFIG_SMP
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
macro_line|#endif
macro_line|#else
singleline_comment|// XXX find what uses (or used) these.
singleline_comment|// EXPORT_SYMBOL_PRIVATE(_rw_read_enter);
singleline_comment|// EXPORT_SYMBOL_PRIVATE(_rw_read_exit);
singleline_comment|// EXPORT_SYMBOL_PRIVATE(_rw_write_enter);
macro_line|#endif
multiline_comment|/* semaphores */
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
)paren
suffix:semicolon
DECL|variable|__down_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_trylock
)paren
suffix:semicolon
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|sparc_valid_addr_bitmap
id|EXPORT_SYMBOL
c_func
(paren
id|sparc_valid_addr_bitmap
)paren
suffix:semicolon
DECL|variable|phys_base
id|EXPORT_SYMBOL
c_func
(paren
id|phys_base
)paren
suffix:semicolon
multiline_comment|/* Atomic operations. */
DECL|variable|___atomic24_add
id|EXPORT_SYMBOL
c_func
(paren
id|___atomic24_add
)paren
suffix:semicolon
DECL|variable|___atomic24_sub
id|EXPORT_SYMBOL
c_func
(paren
id|___atomic24_sub
)paren
suffix:semicolon
multiline_comment|/* Bit operations. */
DECL|variable|___set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|___set_bit
)paren
suffix:semicolon
DECL|variable|___clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|___clear_bit
)paren
suffix:semicolon
DECL|variable|___change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|___change_bit
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* IRQ implementation. */
DECL|variable|global_irq_holder
id|EXPORT_SYMBOL
c_func
(paren
id|global_irq_holder
)paren
suffix:semicolon
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
multiline_comment|/* Misc SMP information */
DECL|variable|__cpu_number_map
id|EXPORT_SYMBOL
c_func
(paren
id|__cpu_number_map
)paren
suffix:semicolon
DECL|variable|__cpu_logical_map
id|EXPORT_SYMBOL
c_func
(paren
id|__cpu_logical_map
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|udelay
id|EXPORT_SYMBOL
c_func
(paren
id|udelay
)paren
suffix:semicolon
DECL|variable|ndelay
id|EXPORT_SYMBOL
c_func
(paren
id|ndelay
)paren
suffix:semicolon
DECL|variable|rtc_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_lock
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_SUN_AUXIO
DECL|variable|set_auxio
id|EXPORT_SYMBOL
c_func
(paren
id|set_auxio
)paren
suffix:semicolon
DECL|variable|get_auxio
id|EXPORT_SYMBOL
c_func
(paren
id|get_auxio
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|request_fast_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_fast_irq
)paren
suffix:semicolon
DECL|variable|io_remap_page_range
id|EXPORT_SYMBOL
c_func
(paren
id|io_remap_page_range
)paren
suffix:semicolon
multiline_comment|/* P3: iounit_xxx may be needed, sun4d users */
multiline_comment|/* EXPORT_SYMBOL(iounit_map_dma_init); */
multiline_comment|/* EXPORT_SYMBOL(iounit_map_dma_page); */
multiline_comment|/* Btfixup stuff cannot have versions, it would be complicated too much */
macro_line|#ifndef CONFIG_SMP
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|___xchg32
)paren
)paren
suffix:semicolon
macro_line|#else
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|__smp_processor_id
)paren
)paren
suffix:semicolon
macro_line|#endif
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|enable_irq
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|disable_irq
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|__irq_itoa
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|mmu_unlockarea
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|mmu_lockarea
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|mmu_get_scsi_sgl
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|mmu_get_scsi_one
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|mmu_release_scsi_sgl
)paren
)paren
suffix:semicolon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|BTFIXUP_CALL
c_func
(paren
id|mmu_release_scsi_one
)paren
)paren
suffix:semicolon
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
DECL|variable|sbus_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_dma_sync_single
)paren
suffix:semicolon
DECL|variable|sbus_dma_sync_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_dma_sync_sg
)paren
suffix:semicolon
DECL|variable|sbus_iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_iounmap
)paren
suffix:semicolon
DECL|variable|sbus_ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|sbus_ioremap
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
DECL|variable|ebus_chain
id|EXPORT_SYMBOL
c_func
(paren
id|ebus_chain
)paren
suffix:semicolon
DECL|variable|insl
id|EXPORT_SYMBOL
c_func
(paren
id|insl
)paren
suffix:semicolon
DECL|variable|outsl
id|EXPORT_SYMBOL
c_func
(paren
id|outsl
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
DECL|variable|pci_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dma_sync_single
)paren
suffix:semicolon
multiline_comment|/* Actually, ioremap/iounmap are not PCI specific. But it is ok for drivers. */
DECL|variable|ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|ioremap
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* in arch/sparc/mm/highmem.c */
macro_line|#ifdef CONFIG_HIGHMEM
DECL|variable|kmap_atomic
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_atomic
)paren
suffix:semicolon
DECL|variable|kunmap_atomic
id|EXPORT_SYMBOL
c_func
(paren
id|kunmap_atomic
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Solaris/SunOS binary compatibility */
DECL|variable|svr4_setcontext
id|EXPORT_SYMBOL
c_func
(paren
id|svr4_setcontext
)paren
suffix:semicolon
DECL|variable|svr4_getcontext
id|EXPORT_SYMBOL
c_func
(paren
id|svr4_getcontext
)paren
suffix:semicolon
DECL|variable|_sigpause_common
id|EXPORT_SYMBOL
c_func
(paren
id|_sigpause_common
)paren
suffix:semicolon
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
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
DECL|variable|prom_apply_obio_ranges
id|EXPORT_SYMBOL
c_func
(paren
id|prom_apply_obio_ranges
)paren
suffix:semicolon
DECL|variable|prom_getname
id|EXPORT_SYMBOL
c_func
(paren
id|prom_getname
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
DECL|variable|prom_finddevice
id|EXPORT_SYMBOL
c_func
(paren
id|prom_finddevice
)paren
suffix:semicolon
DECL|variable|romvec
id|EXPORT_SYMBOL
c_func
(paren
id|romvec
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
DECL|variable|bcopy
id|EXPORT_SYMBOL
c_func
(paren
id|bcopy
)paren
suffix:semicolon
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
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
DECL|variable|strncmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncmp
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
DECL|variable|page_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|page_kernel
)paren
suffix:semicolon
multiline_comment|/* Special internal versions of library functions. */
DECL|variable|__copy_1page
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_1page
)paren
suffix:semicolon
DECL|variable|__memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy
)paren
suffix:semicolon
DECL|variable|__memset
id|EXPORT_SYMBOL
c_func
(paren
id|__memset
)paren
suffix:semicolon
DECL|variable|bzero_1page
id|EXPORT_SYMBOL
c_func
(paren
id|bzero_1page
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
DECL|variable|__strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|__strncmp
)paren
suffix:semicolon
DECL|variable|__memmove
id|EXPORT_SYMBOL
c_func
(paren
id|__memmove
)paren
suffix:semicolon
multiline_comment|/* Moving data to/from userspace. */
DECL|variable|__copy_user
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
multiline_comment|/* XXX This is NOVERS because C_LABEL_STR doesn&squot;t get the version number. -DaveM */
DECL|variable|__csum_partial_copy_sparc_generic
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__csum_partial_copy_sparc_generic
)paren
suffix:semicolon
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
multiline_comment|/* Cache flushing.  */
DECL|variable|sparc_flush_page_to_ram
id|EXPORT_SYMBOL
c_func
(paren
id|sparc_flush_page_to_ram
)paren
suffix:semicolon
multiline_comment|/* No version information on this, heavily used in inline asm,&n; * and will always be &squot;void __ret_efault(void)&squot;.&n; */
DECL|variable|__ret_efault
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ret_efault
)paren
suffix:semicolon
multiline_comment|/* No version information on these, as gcc produces such symbols. */
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__divdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divdi3
)paren
suffix:semicolon
DECL|variable|rem
id|EXPORT_SYMBOL_DOT
c_func
(paren
id|rem
)paren
suffix:semicolon
DECL|variable|urem
id|EXPORT_SYMBOL_DOT
c_func
(paren
id|urem
)paren
suffix:semicolon
DECL|variable|mul
id|EXPORT_SYMBOL_DOT
c_func
(paren
id|mul
)paren
suffix:semicolon
DECL|variable|umul
id|EXPORT_SYMBOL_DOT
c_func
(paren
id|umul
)paren
suffix:semicolon
DECL|variable|div
id|EXPORT_SYMBOL_DOT
c_func
(paren
id|div
)paren
suffix:semicolon
DECL|variable|udiv
id|EXPORT_SYMBOL_DOT
c_func
(paren
id|udiv
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
multiline_comment|/* Sun Power Management Idle Handler */
DECL|variable|pm_idle
id|EXPORT_SYMBOL
c_func
(paren
id|pm_idle
)paren
suffix:semicolon
eof
