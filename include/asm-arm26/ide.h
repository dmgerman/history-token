multiline_comment|/*&n; *  linux/include/asm-arm/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the i386 architecture specific IDE code.&n; */
macro_line|#ifndef __ASMARM_IDE_H
DECL|macro|__ASMARM_IDE_H
mdefine_line|#define __ASMARM_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/* JMA 18.05.03 these will never be needed, but the kernel needs them to compile */
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw(port,addr,len)    readsw(port,addr,len)
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl(port,addr,len)    readsl(port,addr,len)
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw(port,addr,len)   writesw(port,addr,len)
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl(port,addr,len)   writesl(port,addr,len)
multiline_comment|/*&n; * Set up a hw structure for a specified data port, control port and IRQ.&n; * This should follow whatever the default interface uses.&n; */
r_static
id|__inline__
r_void
DECL|function|ide_init_hwif_ports
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_int
id|data_port
comma
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
(paren
id|ide_ioreg_t
)paren
id|data_port
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
suffix:semicolon
id|reg
op_add_assign
l_int|1
suffix:semicolon
)brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
(paren
id|ide_ioreg_t
)paren
id|ctrl_port
suffix:semicolon
r_if
c_cond
(paren
id|irq
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This registers the standard ports for this architecture with the IDE&n; * driver.&n; */
DECL|function|ide_init_default_hwifs
r_static
id|__inline__
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_a5k
c_func
(paren
)paren
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hw
comma
l_int|0
comma
r_sizeof
(paren
id|hw
)paren
)paren
suffix:semicolon
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hw
comma
l_int|0x1f0
comma
l_int|0x3f6
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|IRQ_HARDDISK
suffix:semicolon
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We always use the new IDE port registering,&n; * so these are fixed here.&n; */
DECL|macro|ide_default_io_base
mdefine_line|#define ide_default_io_base(i)&t;&t;((ide_ioreg_t)0)
DECL|macro|ide_default_irq
mdefine_line|#define ide_default_irq(b)&t;&t;(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMARM_IDE_H */
eof
