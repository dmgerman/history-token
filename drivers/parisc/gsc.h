multiline_comment|/*&n; * drivers/parisc/gsc.h&n; * Declarations for functions in gsc.c&n; * Copyright (c) 2000-2002 Helge Deller, Matthew Wilcox&n; *&n; * Distributed under the terms of the GPL, version 2&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/parisc-device.h&gt;
DECL|macro|OFFSET_IRR
mdefine_line|#define OFFSET_IRR 0x0000   /* Interrupt request register */
DECL|macro|OFFSET_IMR
mdefine_line|#define OFFSET_IMR 0x0004   /* Interrupt mask register */
DECL|macro|OFFSET_IPR
mdefine_line|#define OFFSET_IPR 0x0008   /* Interrupt pending register */
DECL|macro|OFFSET_ICR
mdefine_line|#define OFFSET_ICR 0x000C   /* Interrupt control register */
DECL|macro|OFFSET_IAR
mdefine_line|#define OFFSET_IAR 0x0010   /* Interrupt address register */
multiline_comment|/* PA I/O Architected devices support at least 5 bits in the EIM register. */
DECL|macro|GSC_EIM_WIDTH
mdefine_line|#define GSC_EIM_WIDTH 5
DECL|struct|gsc_irq
r_struct
id|gsc_irq
(brace
DECL|member|txn_addr
r_int
r_int
id|txn_addr
suffix:semicolon
multiline_comment|/* IRQ &quot;target&quot; */
DECL|member|txn_data
r_int
id|txn_data
suffix:semicolon
multiline_comment|/* HW &quot;IRQ&quot; */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* virtual IRQ */
)brace
suffix:semicolon
DECL|struct|busdevice
r_struct
id|busdevice
(brace
DECL|member|gsc
r_struct
id|parisc_device
op_star
id|gsc
suffix:semicolon
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|parent_irq
r_int
id|parent_irq
suffix:semicolon
DECL|member|eim
r_int
id|eim
suffix:semicolon
DECL|member|busdev_region
r_struct
id|irq_region
op_star
id|busdev_region
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* short cut to keep the compiler happy */
DECL|macro|BUSDEV_DEV
mdefine_line|#define BUSDEV_DEV(x)&t;((struct busdevice *) (x))
r_int
id|gsc_common_irqsetup
c_func
(paren
r_struct
id|parisc_device
op_star
id|parent
comma
r_struct
id|busdevice
op_star
id|busdev
)paren
suffix:semicolon
r_extern
r_int
id|gsc_alloc_irq
c_func
(paren
r_struct
id|gsc_irq
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* dev needs an irq */
r_extern
r_int
id|gsc_claim_irq
c_func
(paren
r_struct
id|gsc_irq
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* dev needs this irq */
id|irqreturn_t
id|busdev_barked
c_func
(paren
r_int
id|busdev_irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
eof
