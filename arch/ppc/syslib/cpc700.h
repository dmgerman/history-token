multiline_comment|/*&n; * arch/ppc/syslib/cpc700.h&n; * &n; * Header file for IBM CPC700 Host Bridge, et. al.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2000-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * This file contains the defines and macros for the IBM CPC700 host bridge,&n; * memory controller, PIC, UARTs, IIC, and Timers.&n; */
macro_line|#ifndef&t;_ASMPPC_CPC700_H
DECL|macro|_ASMPPC_CPC700_H
mdefine_line|#define&t;_ASMPPC_CPC700_H
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|CPC700_OUT_32
mdefine_line|#define CPC700_OUT_32(a,d)  (*(u_int *)a = d)
DECL|macro|CPC700_IN_32
mdefine_line|#define CPC700_IN_32(a)     (*(u_int *)a)
multiline_comment|/*&n; * PCI Section&n; */
DECL|macro|CPC700_PCI_CONFIG_ADDR
mdefine_line|#define CPC700_PCI_CONFIG_ADDR          0xfec00000
DECL|macro|CPC700_PCI_CONFIG_DATA
mdefine_line|#define CPC700_PCI_CONFIG_DATA          0xfec00004
DECL|macro|CPC700_PMM0_LOCAL
mdefine_line|#define CPC700_PMM0_LOCAL&t;&t;0xff400000
DECL|macro|CPC700_PMM0_MASK_ATTR
mdefine_line|#define CPC700_PMM0_MASK_ATTR&t;&t;0xff400004
DECL|macro|CPC700_PMM0_PCI_LOW
mdefine_line|#define CPC700_PMM0_PCI_LOW&t;&t;0xff400008
DECL|macro|CPC700_PMM0_PCI_HIGH
mdefine_line|#define CPC700_PMM0_PCI_HIGH&t;&t;0xff40000c
DECL|macro|CPC700_PMM1_LOCAL
mdefine_line|#define CPC700_PMM1_LOCAL&t;&t;0xff400010
DECL|macro|CPC700_PMM1_MASK_ATTR
mdefine_line|#define CPC700_PMM1_MASK_ATTR&t;&t;0xff400014
DECL|macro|CPC700_PMM1_PCI_LOW
mdefine_line|#define CPC700_PMM1_PCI_LOW&t;&t;0xff400018
DECL|macro|CPC700_PMM1_PCI_HIGH
mdefine_line|#define CPC700_PMM1_PCI_HIGH&t;&t;0xff40001c
DECL|macro|CPC700_PMM2_LOCAL
mdefine_line|#define CPC700_PMM2_LOCAL&t;&t;0xff400020
DECL|macro|CPC700_PMM2_MASK_ATTR
mdefine_line|#define CPC700_PMM2_MASK_ATTR&t;&t;0xff400024
DECL|macro|CPC700_PMM2_PCI_LOW
mdefine_line|#define CPC700_PMM2_PCI_LOW&t;&t;0xff400028
DECL|macro|CPC700_PMM2_PCI_HIGH
mdefine_line|#define CPC700_PMM2_PCI_HIGH&t;&t;0xff40002c
DECL|macro|CPC700_PTM1_MEMSIZE
mdefine_line|#define CPC700_PTM1_MEMSIZE&t;&t;0xff400030
DECL|macro|CPC700_PTM1_LOCAL
mdefine_line|#define CPC700_PTM1_LOCAL&t;&t;0xff400034
DECL|macro|CPC700_PTM2_MEMSIZE
mdefine_line|#define CPC700_PTM2_MEMSIZE&t;&t;0xff400038
DECL|macro|CPC700_PTM2_LOCAL
mdefine_line|#define CPC700_PTM2_LOCAL&t;&t;0xff40003c
multiline_comment|/*&n; * PIC Section&n; *&n; * IBM calls the CPC700&squot;s programmable interrupt controller the Universal&n; * Interrupt Controller or UIC.&n; */
multiline_comment|/*&n; * UIC Register Addresses.&n; */
DECL|macro|CPC700_UIC_UICSR
mdefine_line|#define&t;CPC700_UIC_UICSR&t;&t;0xff500880&t;/* Status Reg (Rd/Clr)*/
DECL|macro|CPC700_UIC_UICSRS
mdefine_line|#define&t;CPC700_UIC_UICSRS&t;&t;0xff500884&t;/* Status Reg (Set) */
DECL|macro|CPC700_UIC_UICER
mdefine_line|#define&t;CPC700_UIC_UICER&t;&t;0xff500888&t;/* Enable Reg */
DECL|macro|CPC700_UIC_UICCR
mdefine_line|#define&t;CPC700_UIC_UICCR&t;&t;0xff50088c&t;/* Critical Reg */
DECL|macro|CPC700_UIC_UICPR
mdefine_line|#define&t;CPC700_UIC_UICPR&t;&t;0xff500890&t;/* Polarity Reg */
DECL|macro|CPC700_UIC_UICTR
mdefine_line|#define&t;CPC700_UIC_UICTR&t;&t;0xff500894&t;/* Trigger Reg */
DECL|macro|CPC700_UIC_UICMSR
mdefine_line|#define&t;CPC700_UIC_UICMSR&t;&t;0xff500898&t;/* Masked Status Reg */
DECL|macro|CPC700_UIC_UICVR
mdefine_line|#define&t;CPC700_UIC_UICVR&t;&t;0xff50089c&t;/* Vector Reg */
DECL|macro|CPC700_UIC_UICVCR
mdefine_line|#define&t;CPC700_UIC_UICVCR&t;&t;0xff5008a0&t;/* Vector Config Reg */
DECL|macro|CPC700_UIC_UICER_ENABLE
mdefine_line|#define&t;CPC700_UIC_UICER_ENABLE&t;&t;0x00000001&t;/* Enable an IRQ */
DECL|macro|CPC700_UIC_UICVCR_31_HI
mdefine_line|#define&t;CPC700_UIC_UICVCR_31_HI&t;&t;0x00000000&t;/* IRQ 31 hi priority */
DECL|macro|CPC700_UIC_UICVCR_0_HI
mdefine_line|#define&t;CPC700_UIC_UICVCR_0_HI&t;&t;0x00000001&t;/* IRQ 0 hi priority */
DECL|macro|CPC700_UIC_UICVCR_BASE_MASK
mdefine_line|#define CPC700_UIC_UICVCR_BASE_MASK&t;0xfffffffc
DECL|macro|CPC700_UIC_UICVCR_ORDER_MASK
mdefine_line|#define CPC700_UIC_UICVCR_ORDER_MASK&t;0x00000001
multiline_comment|/* Specify value of a bit for an IRQ. */
DECL|macro|CPC700_UIC_IRQ_BIT
mdefine_line|#define&t;CPC700_UIC_IRQ_BIT(i)&t;&t;((0x00000001) &lt;&lt; (31 - (i)))
multiline_comment|/*&n; * UIC Exports...&n; */
r_extern
r_struct
id|hw_interrupt_type
id|cpc700_pic
suffix:semicolon
r_extern
r_int
r_int
id|cpc700_irq_assigns
(braket
l_int|32
)braket
(braket
l_int|2
)braket
suffix:semicolon
r_extern
r_void
id|__init
id|cpc700_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpc700_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* _ASMPPC_CPC700_H */
eof
