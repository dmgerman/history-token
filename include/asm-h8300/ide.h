multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-h8300/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; *  Copyright (C) 2001       Lineo Inc., davidm@snapgear.com&n; *  Copyright (C) 2002       Greg Ungerer (gerg@snapgear.com)&n; *  Copyright (C) 2002       Yoshinori Sato (ysato@users.sourceforge.jp)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef _H8300_IDE_H
DECL|macro|_H8300_IDE_H
mdefine_line|#define _H8300_IDE_H
multiline_comment|/****************************************************************************/
macro_line|#ifdef __KERNEL__
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; *&t;Some coldfire specifics.&n; */
multiline_comment|/*&n; *&t;Save some space, only have 1 interface.&n; */
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;1
multiline_comment|/*&n; *&t;Fix up things that may not have been provided.&n; */
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS 0
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC 0
multiline_comment|/* this definition is used only on startup .. */
DECL|macro|HD_DATA
macro_line|#undef HD_DATA
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA NULL
DECL|macro|DBGIDE
mdefine_line|#define&t;DBGIDE(fmt,a...)
singleline_comment|// #define&t;DBGIDE(fmt,a...) printk(fmt, ##a)
DECL|macro|IDE_INLINE
mdefine_line|#define IDE_INLINE __inline__
singleline_comment|// #define IDE_INLINE
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;__sti()
multiline_comment|/****************************************************************************/
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
multiline_comment|/*&n; *&t;Our list of ports/irq&squot;s for different boards.&n; */
multiline_comment|/* machine depend header include */
DECL|macro|H8300_IDE_DEFINE
mdefine_line|#define H8300_IDE_DEFINE
macro_line|#include &lt;asm/machine-depend.h&gt;
DECL|macro|H8300_IDE_DEFINE
macro_line|#undef  H8300_IDE_DEFINE
multiline_comment|/****************************************************************************/
DECL|function|ide_default_irq
r_static
id|IDE_INLINE
r_int
id|ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_return
id|H8300_IDE_IRQ
op_plus
l_int|12
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|IDE_INLINE
id|ide_ioreg_t
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_return
(paren
id|ide_ioreg_t
)paren
id|H8300_IDE_BASE
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a hw structure for a specified data port, control port and IRQ.&n; * This should follow whatever the default interface uses.&n; */
DECL|function|ide_init_hwif_ports
r_static
id|IDE_INLINE
r_void
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
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
id|H8300_IDE_REG_OFFSET
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_port
)paren
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
)brace
r_else
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
(paren
id|ide_ioreg_t
)paren
id|H8300_IDE_CTRL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This registers the standard ports for this architecture with the IDE&n; * driver.&n; */
DECL|function|ide_init_default_hwifs
r_static
id|IDE_INLINE
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
id|ide_ioreg_t
id|base
suffix:semicolon
r_int
id|index
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_HWIFS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|base
op_assign
id|ide_default_io_base
c_func
(paren
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
r_continue
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
id|base
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|ide_default_irq
c_func
(paren
id|base
)paren
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
DECL|macro|ide_request_irq
mdefine_line|#define ide_request_irq(irq,hand,flg,dev,id)&t;request_irq((irq),(hand),(flg),(dev),(id))
DECL|macro|ide_free_irq
mdefine_line|#define ide_free_irq(irq,dev_id)&t;&t;free_irq((irq), (dev_id))
DECL|macro|ide_check_region
mdefine_line|#define ide_check_region(from,extent)&t;&t;(0)
DECL|macro|ide_request_region
mdefine_line|#define ide_request_region(from,extent,name)&t;do {} while(0)
DECL|macro|ide_release_region
mdefine_line|#define ide_release_region(from,extent)&t;&t;do {} while(0)
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_fix_driveid
mdefine_line|#define ide_fix_driveid(id)&t;&t;target_ide_fix_driveid(id)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
DECL|function|ide_print_resource
r_static
id|IDE_INLINE
r_void
id|ide_print_resource
c_func
(paren
r_char
op_star
id|name
comma
id|hw_regs_t
op_star
id|hw
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s at 0x%08x-0x%08x,0x%08x on irq %d&quot;
comma
id|name
comma
(paren
r_int
r_int
)paren
id|hw-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
comma
(paren
r_int
r_int
)paren
id|hw-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_plus
(paren
l_int|8
op_star
id|H8300_IDE_REG_OFFSET
)paren
op_minus
l_int|1
comma
(paren
r_int
r_int
)paren
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
comma
id|hw-&gt;irq
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************/
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _H8300_IDE_H */
multiline_comment|/****************************************************************************/
eof
