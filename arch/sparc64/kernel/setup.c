multiline_comment|/*  $Id: setup.c,v 1.72 2002/02/09 19:49:30 davem Exp $&n; *  linux/arch/sparc64/kernel/setup.c&n; *&n; *  Copyright (C) 1995,1996  David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1997       Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/starfire.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#ifdef CONFIG_IP_PNP
macro_line|#include &lt;net/ipconfig.h&gt;
macro_line|#endif
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|128
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* unused, ega_bx, unused */
l_int|54
comma
multiline_comment|/* orig-video-lines */
l_int|0
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
)brace
suffix:semicolon
multiline_comment|/* Typing sync at the prom prompt calls the function pointed to by&n; * the sync callback which I set to the following function.&n; * This should sync all filesystems and return, for now it just&n; * prints out pretty messages and returns.&n; */
DECL|variable|prom_palette
r_void
(paren
op_star
id|prom_palette
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|variable|prom_keyboard
r_void
(paren
op_star
id|prom_keyboard
)paren
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* it&squot;s really int */
r_static
r_void
DECL|function|prom_console_write
id|prom_console_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
id|prom_write
c_func
(paren
id|s
comma
id|n
)paren
suffix:semicolon
)brace
DECL|variable|prom_console
r_static
r_struct
id|console
id|prom_console
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;prom&quot;
comma
dot
id|write
op_assign
id|prom_console_write
comma
dot
id|flags
op_assign
id|CON_CONSDEV
op_or
id|CON_ENABLED
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|macro|PROM_TRUE
mdefine_line|#define PROM_TRUE&t;-1
DECL|macro|PROM_FALSE
mdefine_line|#define PROM_FALSE&t;0
multiline_comment|/* Pretty sick eh? */
DECL|function|prom_callback
r_int
id|prom_callback
c_func
(paren
r_int
op_star
id|args
)paren
(brace
r_struct
id|console
op_star
id|cons
comma
op_star
id|saved_console
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|cmd
suffix:semicolon
r_extern
id|spinlock_t
id|prom_entry_lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|args
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmd
op_assign
(paren
r_char
op_star
)paren
id|args
(braket
l_int|0
)braket
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * The callback can be invoked on the cpu that first dropped &n;&t; * into prom_cmdline after taking the serial interrupt, or on &n;&t; * a slave processor that was smp_captured() if the &n;&t; * administrator has done a switch-cpu inside obp. In either &n;&t; * case, the cpu is marked as in-interrupt. Drop IRQ locks.&n;&t; */
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX Revisit the locking here someday.  This is a debugging&n;&t; * XXX feature so it isnt all that critical.  -DaveM&n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|prom_entry_lock
)paren
suffix:semicolon
id|cons
op_assign
id|console_drivers
suffix:semicolon
r_while
c_loop
(paren
id|cons
)paren
(brace
id|unregister_console
c_func
(paren
id|cons
)paren
suffix:semicolon
id|cons-&gt;flags
op_and_assign
op_complement
(paren
id|CON_PRINTBUFFER
)paren
suffix:semicolon
id|cons-&gt;next
op_assign
id|saved_console
suffix:semicolon
id|saved_console
op_assign
id|cons
suffix:semicolon
id|cons
op_assign
id|console_drivers
suffix:semicolon
)brace
id|register_console
c_func
(paren
op_amp
id|prom_console
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;sync&quot;
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;PROM `%s&squot; command...&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|0
)paren
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
)brace
id|args
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|3
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Returning to PROM&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;va&gt;tte-data&quot;
)paren
)paren
(brace
r_int
r_int
id|ctx
comma
id|va
suffix:semicolon
r_int
r_int
id|tte
op_assign
l_int|0
suffix:semicolon
r_int
id|res
op_assign
id|PROM_FALSE
suffix:semicolon
id|ctx
op_assign
id|args
(braket
l_int|3
)braket
suffix:semicolon
id|va
op_assign
id|args
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ctx
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Find process owning ctx, lookup mapping.&n;&t;&t;&t; */
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
l_int|NULL
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|for_each_process
c_func
(paren
id|p
)paren
(brace
id|mm
op_assign
id|p-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|CTX_HWBITS
c_func
(paren
id|mm-&gt;context
)paren
op_eq
id|ctx
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mm
op_logical_or
id|CTX_HWBITS
c_func
(paren
id|mm-&gt;context
)paren
op_ne
id|ctx
)paren
r_goto
id|done
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgdp
)paren
)paren
r_goto
id|done
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmdp
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* Preemption implicitly disabled by virtue of&n;&t;&t;&t; * being called from inside OBP.&n;&t;&t;&t; */
id|ptep
op_assign
id|pte_offset_map
c_func
(paren
id|pmdp
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|ptep
)paren
)paren
(brace
id|tte
op_assign
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
id|res
op_assign
id|PROM_TRUE
suffix:semicolon
)brace
id|pte_unmap
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|va
op_ge
id|KERNBASE
)paren
op_logical_and
(paren
id|va
OL
(paren
id|KERNBASE
op_plus
(paren
l_int|4
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
)paren
)paren
(brace
multiline_comment|/* Spitfire Errata #32 workaround */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&t;%0, [%1] %2&bslash;n&bslash;t&quot;
l_string|&quot;flush&t;%%g6&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|PRIMARY_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_DMMU
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Locked down tlb entry.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|tlb_type
op_eq
id|spitfire
)paren
id|tte
op_assign
id|spitfire_get_dtlb_data
c_func
(paren
id|SPITFIRE_HIGHEST_LOCKED_TLBENT
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tlb_type
op_eq
id|cheetah
op_logical_or
id|tlb_type
op_eq
id|cheetah_plus
)paren
id|tte
op_assign
id|cheetah_get_ldtlb_data
c_func
(paren
id|CHEETAH_HIGHEST_LOCKED_TLBENT
)paren
suffix:semicolon
id|res
op_assign
id|PROM_TRUE
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|va
OL
id|PGDIR_SIZE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * vmalloc or prom_inherited mapping.&n;&t;&t;&t; */
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|va
op_ge
id|LOW_OBP_ADDRESS
)paren
op_logical_and
(paren
id|va
OL
id|HI_OBP_ADDRESS
)paren
)paren
(brace
id|tte
op_assign
id|prom_virt_to_phys
c_func
(paren
id|va
comma
op_amp
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|res
op_assign
id|PROM_TRUE
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|pgdp
op_assign
id|pgd_offset_k
c_func
(paren
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgdp
)paren
)paren
r_goto
id|done
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmdp
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* Preemption implicitly disabled by virtue of&n;&t;&t;&t; * being called from inside OBP.&n;&t;&t;&t; */
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmdp
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|ptep
)paren
)paren
(brace
id|tte
op_assign
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
id|res
op_assign
id|PROM_TRUE
suffix:semicolon
)brace
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|va
OL
id|PAGE_OFFSET
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * No mappings here.&n;&t;&t;&t; */
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|va
op_amp
(paren
l_int|1UL
op_lshift
l_int|40
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * I/O page.&n;&t;&t;&t; */
id|tte
op_assign
(paren
id|__pa
c_func
(paren
id|va
)paren
op_amp
id|_PAGE_PADDR
)paren
op_or
id|_PAGE_VALID
op_or
id|_PAGE_SZ4MB
op_or
id|_PAGE_E
op_or
id|_PAGE_P
op_or
id|_PAGE_W
suffix:semicolon
id|res
op_assign
id|PROM_TRUE
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Normal page.&n;&t;&t; */
id|tte
op_assign
(paren
id|__pa
c_func
(paren
id|va
)paren
op_amp
id|_PAGE_PADDR
)paren
op_or
id|_PAGE_VALID
op_or
id|_PAGE_SZ4MB
op_or
id|_PAGE_CP
op_or
id|_PAGE_CV
op_or
id|_PAGE_P
op_or
id|_PAGE_W
suffix:semicolon
id|res
op_assign
id|PROM_TRUE
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|res
op_eq
id|PROM_TRUE
)paren
(brace
id|args
(braket
l_int|2
)braket
op_assign
l_int|3
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|4
)braket
op_assign
id|res
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|5
)braket
op_assign
id|tte
suffix:semicolon
)brace
r_else
(brace
id|args
(braket
l_int|2
)braket
op_assign
l_int|2
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|4
)braket
op_assign
id|res
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;.soft1&quot;
)paren
)paren
(brace
r_int
r_int
id|tte
suffix:semicolon
id|tte
op_assign
id|args
(braket
l_int|3
)braket
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;%lx:&bslash;&quot;%s%s%s%s%s&bslash;&quot; &quot;
comma
(paren
id|tte
op_amp
id|_PAGE_SOFT
)paren
op_rshift
l_int|7
comma
id|tte
op_amp
id|_PAGE_MODIFIED
ques
c_cond
l_string|&quot;M&quot;
suffix:colon
l_string|&quot;-&quot;
comma
id|tte
op_amp
id|_PAGE_ACCESSED
ques
c_cond
l_string|&quot;A&quot;
suffix:colon
l_string|&quot;-&quot;
comma
id|tte
op_amp
id|_PAGE_READ
ques
c_cond
l_string|&quot;W&quot;
suffix:colon
l_string|&quot;-&quot;
comma
id|tte
op_amp
id|_PAGE_WRITE
ques
c_cond
l_string|&quot;R&quot;
suffix:colon
l_string|&quot;-&quot;
comma
id|tte
op_amp
id|_PAGE_PRESENT
ques
c_cond
l_string|&quot;P&quot;
suffix:colon
l_string|&quot;-&quot;
)paren
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|2
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|4
)braket
op_assign
id|PROM_TRUE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;.soft2&quot;
)paren
)paren
(brace
r_int
r_int
id|tte
suffix:semicolon
id|tte
op_assign
id|args
(braket
l_int|3
)braket
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;%lx &quot;
comma
(paren
id|tte
op_amp
l_int|0x07FC000000000000
)paren
op_rshift
l_int|50
)paren
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|2
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|args
(braket
l_int|1
)braket
op_plus
l_int|4
)braket
op_assign
id|PROM_TRUE
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;unknown PROM `%s&squot; command...&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
)brace
id|unregister_console
c_func
(paren
op_amp
id|prom_console
)paren
suffix:semicolon
r_while
c_loop
(paren
id|saved_console
)paren
(brace
id|cons
op_assign
id|saved_console
suffix:semicolon
id|saved_console
op_assign
id|cons-&gt;next
suffix:semicolon
id|register_console
c_func
(paren
id|cons
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|prom_entry_lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Restore in-interrupt status for a resume from obp.&n;&t; */
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|boot_flags
r_int
r_int
id|boot_flags
op_assign
l_int|0
suffix:semicolon
DECL|macro|BOOTME_DEBUG
mdefine_line|#define BOOTME_DEBUG  0x1
DECL|macro|BOOTME_SINGLE
mdefine_line|#define BOOTME_SINGLE 0x2
multiline_comment|/* Exported for mm/init.c:paging_init. */
DECL|variable|cmdline_memory_size
r_int
r_int
id|cmdline_memory_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|prom_debug_console
r_static
r_struct
id|console
id|prom_debug_console
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;debug&quot;
comma
dot
id|write
op_assign
id|prom_console_write
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* XXX Implement this at some point... */
DECL|function|kernel_enter_debugger
r_void
id|kernel_enter_debugger
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|obp_system_intr
r_int
id|obp_system_intr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OBP: system interrupted&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Process kernel command line switches that are specific to the&n; * SPARC or that require special low-level processing.&n; */
DECL|function|process_switch
r_static
r_void
id|__init
id|process_switch
c_func
(paren
r_char
id|c
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_DEBUG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_SINGLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;boot_flags_init: Halt!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
multiline_comment|/* Use PROM debug console. */
id|register_console
c_func
(paren
op_amp
id|prom_debug_console
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown boot switch (-%c)&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|process_console
r_static
r_void
id|__init
id|process_console
c_func
(paren
r_char
op_star
id|commands
)paren
(brace
id|serial_console
op_assign
l_int|0
suffix:semicolon
id|commands
op_add_assign
l_int|8
suffix:semicolon
multiline_comment|/* Linux-style serial */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;ttyS&quot;
comma
l_int|4
)paren
)paren
id|serial_console
op_assign
id|simple_strtoul
c_func
(paren
id|commands
op_plus
l_int|4
comma
l_int|NULL
comma
l_int|10
)paren
op_plus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;tty&quot;
comma
l_int|3
)paren
)paren
(brace
r_char
id|c
op_assign
op_star
(paren
id|commands
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Solaris-style serial */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;a&squot;
op_logical_or
id|c
op_eq
l_char|&squot;b&squot;
)paren
(brace
id|serial_console
op_assign
id|c
op_minus
l_char|&squot;a&squot;
op_plus
l_int|1
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Using /dev/tty%c as console.&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/* else Linux-style fbcon, not serial */
)brace
macro_line|#if defined(CONFIG_PROM_CONSOLE)
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;prom&quot;
comma
l_int|4
)paren
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|commands
op_minus
l_int|8
suffix:semicolon
op_star
id|p
op_logical_and
op_star
id|p
op_ne
l_char|&squot; &squot;
suffix:semicolon
id|p
op_increment
)paren
op_star
id|p
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|conswitchp
op_assign
op_amp
id|prom_con
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|boot_flags_init
r_static
r_void
id|__init
id|boot_flags_init
c_func
(paren
r_char
op_star
id|commands
)paren
(brace
r_while
c_loop
(paren
op_star
id|commands
)paren
(brace
multiline_comment|/* Move to the start of the next &quot;argument&quot;. */
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_eq
l_char|&squot; &squot;
)paren
id|commands
op_increment
suffix:semicolon
multiline_comment|/* Process any command switches, otherwise skip it. */
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|commands
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_ne
l_char|&squot; &squot;
)paren
id|process_switch
c_func
(paren
op_star
id|commands
op_increment
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;console=&quot;
comma
l_int|8
)paren
)paren
(brace
id|process_console
c_func
(paren
id|commands
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;mem=&quot;
comma
l_int|4
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * &quot;mem=XXX[kKmM]&quot; overrides the PROM-reported&n;&t;&t;&t; * memory size.&n;&t;&t;&t; */
id|cmdline_memory_size
op_assign
id|simple_strtoul
c_func
(paren
id|commands
op_plus
l_int|4
comma
op_amp
id|commands
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;K&squot;
op_logical_or
op_star
id|commands
op_eq
l_char|&squot;k&squot;
)paren
(brace
id|cmdline_memory_size
op_lshift_assign
l_int|10
suffix:semicolon
id|commands
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;M&squot;
op_logical_or
op_star
id|commands
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|cmdline_memory_size
op_lshift_assign
l_int|20
suffix:semicolon
id|commands
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_ne
l_char|&squot; &squot;
)paren
id|commands
op_increment
suffix:semicolon
)brace
)brace
r_extern
r_int
id|prom_probe_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_extern
r_void
id|panic_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|root_flags
suffix:semicolon
r_extern
r_int
r_int
id|root_dev
suffix:semicolon
r_extern
r_int
r_int
id|ram_flags
suffix:semicolon
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK&t;0x07FF
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG&t;&t;0x8000
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG&t;&t;0x4000
r_extern
r_int
id|root_mountflags
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|reboot_command
r_char
id|reboot_command
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|fake_swapper_regs
r_static
r_struct
id|pt_regs
id|fake_swapper_regs
op_assign
(brace
(brace
l_int|0
comma
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|register_prom_callbacks
r_void
id|register_prom_callbacks
c_func
(paren
r_void
)paren
(brace
id|prom_setcallback
c_func
(paren
id|prom_callback
)paren
suffix:semicolon
id|prom_feval
c_func
(paren
l_string|&quot;: linux-va&gt;tte-data 2 &bslash;&quot; va&gt;tte-data&bslash;&quot; $callback drop ; &quot;
l_string|&quot;&squot; linux-va&gt;tte-data to va&gt;tte-data&quot;
)paren
suffix:semicolon
id|prom_feval
c_func
(paren
l_string|&quot;: linux-.soft1 1 &bslash;&quot; .soft1&bslash;&quot; $callback 2drop ; &quot;
l_string|&quot;&squot; linux-.soft1 to .soft1&quot;
)paren
suffix:semicolon
id|prom_feval
c_func
(paren
l_string|&quot;: linux-.soft2 1 &bslash;&quot; .soft2&bslash;&quot; $callback 2drop ; &quot;
l_string|&quot;&squot; linux-.soft2 to .soft2&quot;
)paren
suffix:semicolon
)brace
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_int
r_int
id|highest_paddr
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Initialize PROM console and command line. */
op_star
id|cmdline_p
op_assign
id|prom_getbootargs
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ARCH: SUN4U&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#elif defined(CONFIG_PROM_CONSOLE)
id|conswitchp
op_assign
op_amp
id|prom_con
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|i
op_assign
(paren
r_int
r_int
)paren
op_amp
id|irq_stat
(braket
l_int|1
)braket
op_minus
(paren
r_int
r_int
)paren
op_amp
id|irq_stat
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_eq
id|SMP_CACHE_BYTES
)paren
op_logical_or
(paren
id|i
op_eq
(paren
l_int|2
op_star
id|SMP_CACHE_BYTES
)paren
)paren
)paren
(brace
r_extern
r_int
r_int
id|irqsz_patchme
(braket
l_int|1
)braket
suffix:semicolon
id|irqsz_patchme
(braket
l_int|0
)braket
op_or_assign
(paren
(paren
id|i
op_eq
id|SMP_CACHE_BYTES
)paren
ques
c_cond
id|SMP_CACHE_BYTES_SHIFT
suffix:colon
"&bslash;"
id|SMP_CACHE_BYTES_SHIFT
op_plus
l_int|1
)paren
suffix:semicolon
id|flushi
c_func
(paren
(paren
r_int
)paren
op_amp
id|irqsz_patchme
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Unexpected size of irq_stat[] elements&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Work out if we are starfire early on */
id|check_if_starfire
c_func
(paren
)paren
suffix:semicolon
id|boot_flags_init
c_func
(paren
op_star
id|cmdline_p
)paren
suffix:semicolon
id|idprom_init
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|prom_probe_memory
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* In paging_init() we tip off this value to see if we need&n;&t; * to change init_mm.pgd to point to the real alias mapping.&n;&t; */
id|phys_base
op_assign
l_int|0xffffffffffffffffUL
suffix:semicolon
id|highest_paddr
op_assign
l_int|0UL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|top
suffix:semicolon
r_if
c_cond
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
OL
id|phys_base
)paren
id|phys_base
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
suffix:semicolon
id|top
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
r_if
c_cond
(paren
id|highest_paddr
OL
id|top
)paren
id|highest_paddr
op_assign
id|top
suffix:semicolon
)brace
id|pfn_base
op_assign
id|phys_base
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_flags
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
id|ROOT_DEV
op_assign
id|old_decode_dev
c_func
(paren
id|root_dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|rd_image_start
op_assign
id|ram_flags
op_amp
id|RAMDISK_IMAGE_START_MASK
suffix:semicolon
id|rd_prompt
op_assign
(paren
(paren
id|ram_flags
op_amp
id|RAMDISK_PROMPT_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|rd_doload
op_assign
(paren
(paren
id|ram_flags
op_amp
id|RAMDISK_LOAD_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|init_task.thread_info-&gt;kregs
op_assign
op_amp
id|fake_swapper_regs
suffix:semicolon
macro_line|#ifdef CONFIG_IP_PNP
r_if
c_cond
(paren
op_logical_neg
id|ic_set_manually
)paren
(brace
r_int
id|chosen
op_assign
id|prom_finddevice
(paren
l_string|&quot;/chosen&quot;
)paren
suffix:semicolon
id|u32
id|cl
comma
id|sv
comma
id|gw
suffix:semicolon
id|cl
op_assign
id|prom_getintdefault
(paren
id|chosen
comma
l_string|&quot;client-ip&quot;
comma
l_int|0
)paren
suffix:semicolon
id|sv
op_assign
id|prom_getintdefault
(paren
id|chosen
comma
l_string|&quot;server-ip&quot;
comma
l_int|0
)paren
suffix:semicolon
id|gw
op_assign
id|prom_getintdefault
(paren
id|chosen
comma
l_string|&quot;gateway-ip&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
op_logical_and
id|sv
)paren
(brace
id|ic_myaddr
op_assign
id|cl
suffix:semicolon
id|ic_servaddr
op_assign
id|sv
suffix:semicolon
r_if
c_cond
(paren
id|gw
)paren
id|ic_gateway
op_assign
id|gw
suffix:semicolon
macro_line|#if defined(CONFIG_IP_PNP_BOOTP) || defined(CONFIG_IP_PNP_RARP)
id|ic_proto_enabled
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#endif
id|paging_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|set_preferred_console
r_static
r_int
id|__init
id|set_preferred_console
c_func
(paren
r_void
)paren
(brace
r_int
id|idev
comma
id|odev
suffix:semicolon
multiline_comment|/* The user has requested a console so this is already set up. */
r_if
c_cond
(paren
id|serial_console
op_ge
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|idev
op_assign
id|prom_query_input_device
c_func
(paren
)paren
suffix:semicolon
id|odev
op_assign
id|prom_query_output_device
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_IKBD
op_logical_and
id|odev
op_eq
id|PROMDEV_OSCREEN
)paren
(brace
id|serial_console
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_ITTYA
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYA
)paren
(brace
id|serial_console
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_ITTYB
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYB
)paren
(brace
id|serial_console
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Inconsistent console: &quot;
l_string|&quot;input %d, output %d&bslash;n&quot;
comma
id|idev
comma
id|odev
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial_console
)paren
r_return
id|add_preferred_console
c_func
(paren
l_string|&quot;ttyS&quot;
comma
id|serial_console
op_minus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|set_preferred_console
id|console_initcall
c_func
(paren
id|set_preferred_console
)paren
suffix:semicolon
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* BUFFER is PAGE_SIZE bytes long. */
r_extern
r_char
op_star
id|sparc_cpu_type
suffix:semicolon
r_extern
r_char
op_star
id|sparc_fpu_type
suffix:semicolon
r_extern
r_void
id|smp_info
c_func
(paren
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
r_extern
r_void
id|smp_bogo
c_func
(paren
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mmu_info
c_func
(paren
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
DECL|function|show_cpuinfo
r_static
r_int
id|show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|__unused
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;promlib&bslash;t&bslash;t: Version 3 Revision %d&bslash;n&quot;
l_string|&quot;prom&bslash;t&bslash;t: %d.%d.%d&bslash;n&quot;
l_string|&quot;type&bslash;t&bslash;t: sun4u&bslash;n&quot;
l_string|&quot;ncpus probed&bslash;t: %ld&bslash;n&quot;
l_string|&quot;ncpus active&bslash;t: %ld&bslash;n&quot;
macro_line|#ifndef CONFIG_SMP
l_string|&quot;Cpu0Bogo&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;Cpu0ClkTck&bslash;t: %016lx&bslash;n&quot;
macro_line|#endif
comma
id|sparc_cpu_type
comma
id|sparc_fpu_type
comma
id|prom_rev
comma
id|prom_prev
op_rshift
l_int|16
comma
(paren
id|prom_prev
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|prom_prev
op_amp
l_int|0xff
comma
(paren
r_int
)paren
id|num_possible_cpus
c_func
(paren
)paren
comma
(paren
r_int
)paren
id|num_online_cpus
c_func
(paren
)paren
macro_line|#ifndef CONFIG_SMP
comma
id|cpu_data
c_func
(paren
l_int|0
)paren
dot
id|udelay_val
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|cpu_data
c_func
(paren
l_int|0
)paren
dot
id|udelay_val
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
comma
id|cpu_data
c_func
(paren
l_int|0
)paren
dot
id|clock_tick
macro_line|#endif
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_bogo
c_func
(paren
id|m
)paren
suffix:semicolon
macro_line|#endif
id|mmu_info
c_func
(paren
id|m
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_info
c_func
(paren
id|m
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
multiline_comment|/* The pointer we are returning is arbitrary,&n;&t; * it just has to be non-NULL and not IS_ERR&n;&t; * in the success case.&n;&t; */
r_return
op_star
id|pos
op_eq
l_int|0
ques
c_cond
op_amp
id|c_start
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|show_cpuinfo
comma
)brace
suffix:semicolon
r_extern
r_int
id|stop_a_enabled
suffix:semicolon
DECL|function|sun_do_break
r_void
id|sun_do_break
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|stop_a_enabled
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|flush_user_windows
c_func
(paren
)paren
suffix:semicolon
id|prom_cmdline
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|serial_console
r_int
id|serial_console
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|stop_a_enabled
r_int
id|stop_a_enabled
op_assign
l_int|1
suffix:semicolon
DECL|function|topology_init
r_static
r_int
id|__init
id|topology_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
(brace
r_struct
id|cpu
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|register_cpu
c_func
(paren
id|p
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|topology_init
id|subsys_initcall
c_func
(paren
id|topology_init
)paren
suffix:semicolon
eof
