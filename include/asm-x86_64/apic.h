macro_line|#ifndef __ASM_APIC_H
DECL|macro|__ASM_APIC_H
mdefine_line|#define __ASM_APIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
DECL|macro|APIC_DEBUG
mdefine_line|#define APIC_DEBUG 0
macro_line|#if APIC_DEBUG
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...) printk(x)
macro_line|#else
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...)
macro_line|#endif
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/*&n; * Basic functions accessing APICs.&n; */
DECL|function|apic_write
r_static
id|__inline
r_void
id|apic_write
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|v
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|reg
)paren
)paren
op_assign
id|v
suffix:semicolon
)brace
DECL|function|apic_write_atomic
r_static
id|__inline
r_void
id|apic_write_atomic
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|v
)paren
(brace
id|xchg
c_func
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|reg
)paren
comma
id|v
)paren
suffix:semicolon
)brace
DECL|function|apic_read
r_static
id|__inline
r_int
r_int
id|apic_read
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|reg
)paren
)paren
suffix:semicolon
)brace
DECL|function|apic_wait_icr_idle
r_static
id|__inline__
r_void
id|apic_wait_icr_idle
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|apic_read
c_func
(paren
id|APIC_ICR
)paren
op_amp
id|APIC_ICR_BUSY
)paren
suffix:semicolon
)brace
DECL|macro|FORCE_READ_AROUND_WRITE
mdefine_line|#define FORCE_READ_AROUND_WRITE 0
DECL|macro|apic_read_around
mdefine_line|#define apic_read_around(x)
DECL|macro|apic_write_around
mdefine_line|#define apic_write_around(x,y) apic_write((x),(y))
DECL|function|ack_APIC_irq
r_static
r_inline
r_void
id|ack_APIC_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * ack_APIC_irq() actually gets compiled as a single instruction:&n;&t; * - a single rmw on Pentium/82489DX&n;&t; * - a single write on P6+ cores (CONFIG_X86_GOOD_APIC)&n;&t; * ... yummie.&n;&t; */
multiline_comment|/* Docs say use 0 for future compatibility */
id|apic_write_around
c_func
(paren
id|APIC_EOI
comma
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_int
id|get_maxlvt
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|clear_local_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|connect_bsp_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disconnect_bsp_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_local_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|verify_local_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cache_APIC_registers
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sync_Arb_IDs
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_bsp_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_local_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_apic_mappings
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_local_timer_interrupt
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|setup_boot_APIC_clock
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_secondary_APIC_clock
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_apic_nmi_watchdog
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_lapic_nmi_watchdog
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_lapic_nmi_watchdog
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_timer_nmi_watchdog
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_timer_nmi_watchdog
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|nmi_watchdog_tick
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|reason
)paren
suffix:semicolon
r_extern
r_int
id|APIC_init_uniprocessor
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_APIC_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_APIC_timer
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_extern
r_struct
id|sys_device
id|device_lapic
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|check_nmi_watchdog
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nmi_watchdog
suffix:semicolon
DECL|macro|NMI_NONE
mdefine_line|#define NMI_NONE&t;0
DECL|macro|NMI_IO_APIC
mdefine_line|#define NMI_IO_APIC&t;1
DECL|macro|NMI_LOCAL_APIC
mdefine_line|#define NMI_LOCAL_APIC&t;2
DECL|macro|NMI_INVALID
mdefine_line|#define NMI_INVALID&t;3
macro_line|#endif /* CONFIG_X86_LOCAL_APIC */
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode 0
DECL|macro|esr_disable
mdefine_line|#define esr_disable 0
r_extern
r_int
id|boot_cpu_id
suffix:semicolon
macro_line|#endif /* __ASM_APIC_H */
eof
