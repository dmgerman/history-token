macro_line|#ifndef __I386_SGI_COBALT_H
DECL|macro|__I386_SGI_COBALT_H
mdefine_line|#define __I386_SGI_COBALT_H
macro_line|#include &lt;asm/fixmap.h&gt;
multiline_comment|/*&n; * Cobalt SGI Visual Workstation system ASIC&n; */
DECL|macro|CO_CPU_NUM_PHYS
mdefine_line|#define CO_CPU_NUM_PHYS 0x1e00
DECL|macro|CO_CPU_TAB_PHYS
mdefine_line|#define CO_CPU_TAB_PHYS (CO_CPU_NUM_PHYS + 2)
DECL|macro|CO_CPU_MAX
mdefine_line|#define CO_CPU_MAX 4
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
mdefine_line|#define&t;CO_CTRL_TIMERUN&t;&t;0x04&t;&t;/* 0 == disabled */
DECL|macro|CO_CTRL_TIMEMASK
mdefine_line|#define&t;CO_CTRL_TIMEMASK&t;0x08&t;&t;/* 0 == unmasked */
multiline_comment|/* CO_CPU_STATUS bits */
DECL|macro|CO_STAT_TIMEINTR
mdefine_line|#define&t;CO_STAT_TIMEINTR&t;0x02&t;/* (r) 1 == int pend, (w) 0 == clear */
multiline_comment|/* CO_CPU_TIMEVAL value */
DECL|macro|CO_TIME_HZ
mdefine_line|#define&t;CO_TIME_HZ&t;&t;100000000&t;/* Cobalt core rate */
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
DECL|macro|CO_APIC_MASK
mdefine_line|#define&t;CO_APIC_MASK&t;&t;0x00010000&t;/* 0 = enabled */
DECL|macro|CO_APIC_LEVEL
mdefine_line|#define&t;CO_APIC_LEVEL&t;&t;0x00008000&t;/* 0 = edge */
multiline_comment|/*&n; * Where things are physically wired to Cobalt&n; * #defines with no board _&lt;type&gt;_&lt;rev&gt;_ are common to all (thus far)&n; */
DECL|macro|CO_APIC_IDE0
mdefine_line|#define&t;CO_APIC_IDE0&t;&t;4
DECL|macro|CO_APIC_IDE1
mdefine_line|#define CO_APIC_IDE1&t;&t;2&t;&t;/* Only on 320 */
DECL|macro|CO_APIC_8259
mdefine_line|#define&t;CO_APIC_8259&t;&t;12&t;&t;/* serial, floppy, par-l-l */
multiline_comment|/* Lithium PCI Bridge A -- &quot;the one with 82557 Ethernet&quot; */
DECL|macro|CO_APIC_PCIA_BASE0
mdefine_line|#define&t;CO_APIC_PCIA_BASE0&t;0 /* and 1 */&t;/* slot 0, line 0 */
DECL|macro|CO_APIC_PCIA_BASE123
mdefine_line|#define&t;CO_APIC_PCIA_BASE123&t;5 /* and 6 */&t;/* slot 0, line 1 */
DECL|macro|CO_APIC_PIIX4_USB
mdefine_line|#define&t;CO_APIC_PIIX4_USB&t;7&t;&t;/* this one is weird */
multiline_comment|/* Lithium PCI Bridge B -- &quot;the one with PIIX4&quot; */
DECL|macro|CO_APIC_PCIB_BASE0
mdefine_line|#define&t;CO_APIC_PCIB_BASE0&t;8 /* and 9-12 *//* slot 0, line 0 */
DECL|macro|CO_APIC_PCIB_BASE123
mdefine_line|#define&t;CO_APIC_PCIB_BASE123&t;13 /* 14.15 */&t;/* slot 0, line 1 */
DECL|macro|CO_APIC_VIDOUT0
mdefine_line|#define&t;CO_APIC_VIDOUT0&t;&t;16
DECL|macro|CO_APIC_VIDOUT1
mdefine_line|#define&t;CO_APIC_VIDOUT1&t;&t;17
DECL|macro|CO_APIC_VIDIN0
mdefine_line|#define&t;CO_APIC_VIDIN0&t;&t;18
DECL|macro|CO_APIC_VIDIN1
mdefine_line|#define&t;CO_APIC_VIDIN1&t;&t;19
DECL|macro|CO_APIC_LI_AUDIO
mdefine_line|#define&t;CO_APIC_LI_AUDIO&t;22
DECL|macro|CO_APIC_AS
mdefine_line|#define&t;CO_APIC_AS&t;&t;24
DECL|macro|CO_APIC_RE
mdefine_line|#define&t;CO_APIC_RE&t;&t;25
DECL|macro|CO_APIC_CPU
mdefine_line|#define CO_APIC_CPU&t;&t;28&t;&t;/* Timer and Cache interrupt */
DECL|macro|CO_APIC_NMI
mdefine_line|#define&t;CO_APIC_NMI&t;&t;29
DECL|macro|CO_APIC_LAST
mdefine_line|#define&t;CO_APIC_LAST&t;&t;CO_APIC_NMI
multiline_comment|/*&n; * This is how irqs are assigned on the Visual Workstation.&n; * Legacy devices get irq&squot;s 1-15 (system clock is 0 and is CO_APIC_CPU).&n; * All other devices (including PCI) go to Cobalt and are irq&squot;s 16 on up.&n; */
DECL|macro|CO_IRQ_APIC0
mdefine_line|#define&t;CO_IRQ_APIC0&t;16&t;&t;&t;/* irq of apic entry 0 */
DECL|macro|IS_CO_APIC
mdefine_line|#define&t;IS_CO_APIC(irq)&t;((irq) &gt;= CO_IRQ_APIC0)
DECL|macro|CO_IRQ
mdefine_line|#define&t;CO_IRQ(apic)&t;(CO_IRQ_APIC0 + (apic))&t;/* apic ent to irq */
DECL|macro|CO_APIC
mdefine_line|#define&t;CO_APIC(irq)&t;((irq) - CO_IRQ_APIC0)&t;/* irq to apic ent */
DECL|macro|CO_IRQ_IDE0
mdefine_line|#define CO_IRQ_IDE0&t;14&t;&t;&t;/* knowledge of... */
DECL|macro|CO_IRQ_IDE1
mdefine_line|#define CO_IRQ_IDE1&t;15&t;&t;&t;/* ... ide driver defaults! */
DECL|macro|CO_IRQ_8259
mdefine_line|#define&t;CO_IRQ_8259&t;CO_IRQ(CO_APIC_8259)
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
macro_line|#endif /* __I386_SGI_COBALT_H */
eof
