macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __I386_COBALT_H
DECL|macro|__I386_COBALT_H
mdefine_line|#define __I386_COBALT_H
multiline_comment|/*&n; * Cobalt is the system ASIC on the SGI 320 and 540 Visual Workstations&n; */
DECL|macro|CO_CPU_PHYS
mdefine_line|#define&t;CO_CPU_PHYS&t;&t;0xc2000000
DECL|macro|CO_APIC_PHYS
mdefine_line|#define&t;CO_APIC_PHYS&t;&t;0xc4000000
multiline_comment|/* see set_fixmap() and asm/fixmap.h */
DECL|macro|CO_CPU_VADDR
mdefine_line|#define&t;CO_CPU_VADDR&t;&t;(fix_to_virt(FIX_CO_CPU))
DECL|macro|CO_APIC_VADDR
mdefine_line|#define&t;CO_APIC_VADDR&t;&t;(fix_to_virt(FIX_CO_APIC))
multiline_comment|/* Cobalt CPU registers -- relative to CO_CPU_VADDR, use co_cpu_*() */
DECL|macro|CO_CPU_REV
mdefine_line|#define&t;CO_CPU_REV&t;&t;0x08
DECL|macro|CO_CPU_CTRL
mdefine_line|#define&t;CO_CPU_CTRL&t;&t;0x10
DECL|macro|CO_CPU_STAT
mdefine_line|#define&t;CO_CPU_STAT&t;&t;0x20
DECL|macro|CO_CPU_TIMEVAL
mdefine_line|#define&t;CO_CPU_TIMEVAL&t;&t;0x30
multiline_comment|/* CO_CPU_CTRL bits */
DECL|macro|CO_CTRL_TIMERUN
mdefine_line|#define&t;CO_CTRL_TIMERUN&t;&t;0x04&t;/* 0 == disabled */
DECL|macro|CO_CTRL_TIMEMASK
mdefine_line|#define&t;CO_CTRL_TIMEMASK&t;0x08&t;/* 0 == unmasked */
multiline_comment|/* CO_CPU_STATUS bits */
DECL|macro|CO_STAT_TIMEINTR
mdefine_line|#define&t;CO_STAT_TIMEINTR&t;0x02&t;/* (r) 1 == int pend, (w) 0 == clear */
multiline_comment|/* CO_CPU_TIMEVAL value */
DECL|macro|CO_TIME_HZ
mdefine_line|#define&t;CO_TIME_HZ&t;&t;100000000 /* Cobalt core rate */
multiline_comment|/* Cobalt APIC registers -- relative to CO_APIC_VADDR, use co_apic_*() */
DECL|macro|CO_APIC_HI
mdefine_line|#define&t;CO_APIC_HI(n)&t;&t;(((n) * 0x10) + 4)
DECL|macro|CO_APIC_LO
mdefine_line|#define&t;CO_APIC_LO(n)&t;&t;((n) * 0x10)
DECL|macro|CO_APIC_ID
mdefine_line|#define&t;CO_APIC_ID&t;&t;0x0ffc
multiline_comment|/* CO_APIC_ID bits */
DECL|macro|CO_APIC_ENABLE
mdefine_line|#define&t;CO_APIC_ENABLE&t;&t;0x00000100
multiline_comment|/* CO_APIC_LO bits */
DECL|macro|CO_APIC_LEVEL
mdefine_line|#define&t;CO_APIC_LEVEL&t;&t;0x08000&t;&t;/* 0 = edge */
multiline_comment|/*&n; * Where things are physically wired to Cobalt&n; * #defines with no board _&lt;type&gt;_&lt;rev&gt;_ are common to all (thus far)&n; */
DECL|macro|CO_APIC_0_5_IDE0
mdefine_line|#define CO_APIC_0_5_IDE0&t;5
DECL|macro|CO_APIC_0_5_SERIAL
mdefine_line|#define&t;CO_APIC_0_5_SERIAL&t;13&t; /* XXX not really...h/w bug! */
DECL|macro|CO_APIC_0_5_PARLL
mdefine_line|#define CO_APIC_0_5_PARLL&t;4
DECL|macro|CO_APIC_0_5_FLOPPY
mdefine_line|#define CO_APIC_0_5_FLOPPY&t;6
DECL|macro|CO_APIC_0_6_IDE0
mdefine_line|#define&t;CO_APIC_0_6_IDE0&t;4
DECL|macro|CO_APIC_0_6_USB
mdefine_line|#define&t;CO_APIC_0_6_USB&t;7&t;/* PIIX4 USB */
DECL|macro|CO_APIC_1_2_IDE0
mdefine_line|#define&t;CO_APIC_1_2_IDE0&t;4
DECL|macro|CO_APIC_0_5_IDE1
mdefine_line|#define CO_APIC_0_5_IDE1&t;2
DECL|macro|CO_APIC_0_6_IDE1
mdefine_line|#define CO_APIC_0_6_IDE1&t;2
multiline_comment|/* XXX */
DECL|macro|CO_APIC_IDE0
mdefine_line|#define&t;CO_APIC_IDE0&t;CO_APIC_0_5_IDE0
DECL|macro|CO_APIC_IDE1
mdefine_line|#define&t;CO_APIC_IDE1&t;CO_APIC_0_5_IDE1
DECL|macro|CO_APIC_SERIAL
mdefine_line|#define&t;CO_APIC_SERIAL&t;CO_APIC_0_5_SERIAL
multiline_comment|/* XXX */
DECL|macro|CO_APIC_ENET
mdefine_line|#define CO_APIC_ENET&t;3&t;/* Lithium PCI Bridge A, Device 3 */
DECL|macro|CO_APIC_8259
mdefine_line|#define&t;CO_APIC_8259&t;12&t;/* serial, floppy, par-l-l, audio */
DECL|macro|CO_APIC_VIDOUT0
mdefine_line|#define&t;CO_APIC_VIDOUT0&t;16
DECL|macro|CO_APIC_VIDOUT1
mdefine_line|#define&t;CO_APIC_VIDOUT1&t;17
DECL|macro|CO_APIC_VIDIN0
mdefine_line|#define&t;CO_APIC_VIDIN0&t;18
DECL|macro|CO_APIC_VIDIN1
mdefine_line|#define&t;CO_APIC_VIDIN1&t;19
DECL|macro|CO_APIC_CPU
mdefine_line|#define CO_APIC_CPU&t;28&t;/* Timer and Cache interrupt */
multiline_comment|/*&n; * This is the &quot;irq&quot; arg to request_irq(), just a unique cookie.&n; */
DECL|macro|CO_IRQ_TIMER
mdefine_line|#define&t;CO_IRQ_TIMER&t;0
DECL|macro|CO_IRQ_ENET
mdefine_line|#define CO_IRQ_ENET&t;3
DECL|macro|CO_IRQ_SERIAL
mdefine_line|#define CO_IRQ_SERIAL&t;4
DECL|macro|CO_IRQ_FLOPPY
mdefine_line|#define CO_IRQ_FLOPPY&t;6&t;/* Same as drivers/block/floppy.c:FLOPPY_IRQ */
DECL|macro|CO_IRQ_PARLL
mdefine_line|#define&t;CO_IRQ_PARLL&t;7
DECL|macro|CO_IRQ_POWER
mdefine_line|#define&t;CO_IRQ_POWER&t;9
DECL|macro|CO_IRQ_IDE
mdefine_line|#define CO_IRQ_IDE&t;14
DECL|macro|CO_IRQ_8259
mdefine_line|#define&t;CO_IRQ_8259&t;12
macro_line|#ifdef CONFIG_X86_VISWS_APIC
DECL|function|co_cpu_write
r_extern
id|__inline
r_void
id|co_cpu_write
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
id|CO_CPU_VADDR
op_plus
id|reg
)paren
)paren
op_assign
id|v
suffix:semicolon
)brace
DECL|function|co_cpu_read
r_extern
id|__inline
r_int
r_int
id|co_cpu_read
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
id|CO_CPU_VADDR
op_plus
id|reg
)paren
)paren
suffix:semicolon
)brace
DECL|function|co_apic_write
r_extern
id|__inline
r_void
id|co_apic_write
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
id|CO_APIC_VADDR
op_plus
id|reg
)paren
)paren
op_assign
id|v
suffix:semicolon
)brace
DECL|function|co_apic_read
r_extern
id|__inline
r_int
r_int
id|co_apic_read
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
id|CO_APIC_VADDR
op_plus
id|reg
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_char
id|visws_board_type
suffix:semicolon
DECL|macro|VISWS_320
mdefine_line|#define&t;VISWS_320&t;0
DECL|macro|VISWS_540
mdefine_line|#define&t;VISWS_540&t;1
r_extern
r_char
id|visws_board_rev
suffix:semicolon
macro_line|#endif
eof
