multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-m68knommu/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; *&t;Copyright (C) 2001       Lineo Inc., davidm@uclinux.org&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef _M68KNOMMU_IDE_H
DECL|macro|_M68KNOMMU_IDE_H
mdefine_line|#define _M68KNOMMU_IDE_H
macro_line|#ifdef __KERNEL__
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;some coldfire specifics&n; */
macro_line|#ifdef CONFIG_COLDFIRE
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
multiline_comment|/*&n; *&t;Save some space,  only have 1 interface&n; */
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;&t;  1&t;/* we only have one interface for now */
macro_line|#ifdef CONFIG_SECUREEDGEMP3
DECL|macro|MCFSIM_LOCALCS
mdefine_line|#define&t;MCFSIM_LOCALCS&t;  MCFSIM_CSCR4
macro_line|#else
DECL|macro|MCFSIM_LOCALCS
mdefine_line|#define&t;MCFSIM_LOCALCS&t;  MCFSIM_CSCR6
macro_line|#endif
macro_line|#endif /* CONFIG_COLDFIRE */
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;Fix up things that may not have been provided&n; */
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4&t;/* same as the other archs */
macro_line|#endif
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
multiline_comment|/*&n; *&t;our list of ports/irq&squot;s for different boards&n; */
DECL|struct|m68k_ide_defaults
r_static
r_struct
id|m68k_ide_defaults
(brace
DECL|member|base
id|ide_ioreg_t
id|base
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|variable|m68k_ide_defaults
)brace
id|m68k_ide_defaults
(braket
id|MAX_HWIFS
)braket
op_assign
(brace
macro_line|#if defined(CONFIG_SECUREEDGEMP3)
(brace
(paren
(paren
id|ide_ioreg_t
)paren
l_int|0x30800000
)paren
comma
l_int|29
)brace
comma
macro_line|#elif defined(CONFIG_eLIA)
(brace
(paren
(paren
id|ide_ioreg_t
)paren
l_int|0x30c00000
)paren
comma
l_int|29
)brace
comma
macro_line|#else
(brace
(paren
(paren
id|ide_ioreg_t
)paren
l_int|0x0
)paren
comma
l_int|0
)brace
macro_line|#endif
)brace
suffix:semicolon
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
r_int
id|i
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
id|MAX_HWIFS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|m68k_ide_defaults
(braket
id|i
)braket
dot
id|base
op_eq
id|base
)paren
r_return
id|m68k_ide_defaults
(braket
id|i
)braket
dot
id|irq
suffix:semicolon
r_return
l_int|0
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
r_if
c_cond
(paren
id|index
op_ge
l_int|0
op_logical_and
id|index
OL
id|MAX_HWIFS
)paren
r_return
id|m68k_ide_defaults
(braket
id|index
)braket
dot
id|base
suffix:semicolon
r_return
l_int|0
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
l_int|1
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
id|data_port
op_plus
l_int|0xe
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
r_static
id|IDE_INLINE
r_int
DECL|function|ide_request_irq
id|ide_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|device
comma
r_void
op_star
id|dev_id
)paren
(brace
macro_line|#ifdef CONFIG_COLDFIRE
id|mcf_autovector
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#endif
r_return
id|request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|flags
comma
id|device
comma
id|dev_id
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_free_irq
id|ide_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_int
DECL|function|ide_check_region
id|ide_check_region
c_func
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_request_region
id|ide_request_region
c_func
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
comma
r_const
r_char
op_star
id|name
)paren
(brace
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_release_region
id|ide_release_region
c_func
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_fix_driveid
id|ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
macro_line|#ifdef CONFIG_COLDFIRE
r_int
id|i
comma
id|n
suffix:semicolon
r_int
r_int
op_star
id|wp
op_assign
(paren
r_int
r_int
op_star
)paren
id|id
suffix:semicolon
r_int
id|avoid
(braket
)braket
op_assign
(brace
l_int|49
comma
l_int|51
comma
l_int|52
comma
l_int|59
comma
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* do not swap these words */
multiline_comment|/* Need to byte swap shorts,  but not char fields */
r_for
c_loop
(paren
id|i
op_assign
id|n
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
op_star
id|id
)paren
op_div
r_sizeof
(paren
op_star
id|wp
)paren
suffix:semicolon
id|i
op_increment
comma
id|wp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|avoid
(braket
id|n
)braket
op_eq
id|i
)paren
(brace
id|n
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|wp
op_assign
(paren
(paren
op_star
id|wp
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
op_star
id|wp
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/* have to word swap the one 32 bit field */
id|id-&gt;lba_capacity
op_assign
(paren
(paren
id|id-&gt;lba_capacity
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|id-&gt;lba_capacity
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_release_lock
id|ide_release_lock
(paren
r_int
op_star
id|ide_lock
)paren
(brace
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_get_lock
id|ide_get_lock
c_func
(paren
r_int
op_star
id|ide_lock
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
)brace
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif) &bslash;&n;&t;((hwif)-&gt;hw.ack_intr ? (hwif)-&gt;hw.ack_intr(hwif) : 1)
DECL|macro|ide__sti
mdefine_line|#define&t;ide__sti()&t;__sti()
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;System specific IO requirements&n; */
macro_line|#ifdef CONFIG_COLDFIRE
macro_line|#ifdef CONFIG_SECUREEDGEMP3
multiline_comment|/* Replace standard IO functions for funky mapping of MP3 board */
DECL|macro|outb
macro_line|#undef outb
DECL|macro|outb_p
macro_line|#undef outb_p
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inb_p
macro_line|#undef inb_p
DECL|macro|outb
mdefine_line|#define outb(v, a)          ide_outb(v, (unsigned long) (a))
DECL|macro|outb_p
mdefine_line|#define outb_p(v, a)        ide_outb(v, (unsigned long) (a))
DECL|macro|inb
mdefine_line|#define inb(a)              ide_inb((unsigned long) (a))
DECL|macro|inb_p
mdefine_line|#define inb_p(a)            ide_inb((unsigned long) (a))
DECL|macro|ADDR8_PTR
mdefine_line|#define ADDR8_PTR(addr)&t;&t;(((addr) &amp; 0x1) ? (0x8000 + (addr) - 1) : (addr))
DECL|macro|ADDR16_PTR
mdefine_line|#define ADDR16_PTR(addr)&t;(addr)
DECL|macro|ADDR32_PTR
mdefine_line|#define ADDR32_PTR(addr)&t;(addr)
DECL|macro|SWAP8
mdefine_line|#define SWAP8(w)&t;&t;&t;((((w) &amp; 0xffff) &lt;&lt; 8) | (((w) &amp; 0xffff) &gt;&gt; 8))
DECL|macro|SWAP16
mdefine_line|#define SWAP16(w)&t;&t;&t;(w)
DECL|macro|SWAP32
mdefine_line|#define SWAP32(w)&t;&t;&t;(w)
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outb
id|ide_outb
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(val=%x,addr=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|val
comma
id|addr
)paren
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR8_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
op_star
id|rp
op_assign
id|SWAP8
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_int
DECL|function|ide_inb
id|ide_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
comma
id|val
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(addr=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
)paren
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR8_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|val
op_assign
op_star
id|rp
suffix:semicolon
r_return
id|SWAP8
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outw
id|ide_outw
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(val=%x,addr=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|val
comma
id|addr
)paren
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR16_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
op_star
id|rp
op_assign
id|SWAP16
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outsw
id|ide_outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
comma
id|val
suffix:semicolon
r_int
r_int
op_star
id|buf
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(addr=%x,vbuf=%p,len=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR16_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|val
op_assign
op_star
id|buf
op_increment
suffix:semicolon
op_star
id|rp
op_assign
id|SWAP16
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
)brace
r_static
id|IDE_INLINE
r_int
DECL|function|ide_inw
id|ide_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
comma
id|val
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(addr=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
)paren
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR16_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|val
op_assign
op_star
id|rp
suffix:semicolon
r_return
id|SWAP16
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_insw
id|ide_insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
suffix:semicolon
r_int
r_int
id|w
comma
op_star
id|buf
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(addr=%x,vbuf=%p,len=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR16_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|w
op_assign
op_star
id|rp
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|SWAP16
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_insl
id|ide_insl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
suffix:semicolon
r_int
r_int
id|w
comma
op_star
id|buf
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(addr=%x,vbuf=%p,len=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR32_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|w
op_assign
op_star
id|rp
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|SWAP32
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outsl
id|ide_outsl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
comma
id|val
suffix:semicolon
r_int
r_int
op_star
id|buf
suffix:semicolon
id|DBGIDE
c_func
(paren
l_string|&quot;%s(addr=%x,vbuf=%p,len=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADDR32_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|val
op_assign
op_star
id|buf
op_increment
suffix:semicolon
op_star
id|rp
op_assign
id|SWAP32
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
)brace
macro_line|#elif CONFIG_eLIA
multiline_comment|/* 8/16 bit acesses are controlled by flicking bits in the CS register */
DECL|macro|ACCESS_MODE_16BIT
mdefine_line|#define&t;ACCESS_MODE_16BIT()&t;&bslash;&n;&t;*((volatile unsigned short *) (MCF_MBAR + MCFSIM_LOCALCS)) = 0x0080
DECL|macro|ACCESS_MODE_8BIT
mdefine_line|#define&t;ACCESS_MODE_8BIT()&t;&bslash;&n;&t;*((volatile unsigned short *) (MCF_MBAR + MCFSIM_LOCALCS)) = 0x0040
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outw
id|ide_outw
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|ACCESS_MODE_16BIT
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|ACCESS_MODE_8BIT
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outsw
id|ide_outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
id|ACCESS_MODE_16BIT
c_func
(paren
)paren
suffix:semicolon
id|outsw
c_func
(paren
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|ACCESS_MODE_8BIT
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_int
DECL|function|ide_inw
id|ide_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ACCESS_MODE_16BIT
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|inw
c_func
(paren
id|addr
)paren
suffix:semicolon
id|ACCESS_MODE_8BIT
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_insw
id|ide_insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
id|ACCESS_MODE_16BIT
c_func
(paren
)paren
suffix:semicolon
id|insw
c_func
(paren
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|ACCESS_MODE_8BIT
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_insl
id|ide_insl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
id|ACCESS_MODE_16BIT
c_func
(paren
)paren
suffix:semicolon
id|insl
c_func
(paren
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|ACCESS_MODE_8BIT
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
id|IDE_INLINE
r_void
DECL|function|ide_outsl
id|ide_outsl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
id|ACCESS_MODE_16BIT
c_func
(paren
)paren
suffix:semicolon
id|outsl
c_func
(paren
id|addr
comma
id|vbuf
comma
id|len
)paren
suffix:semicolon
id|ACCESS_MODE_8BIT
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SECUREEDGEMP3 */
DECL|macro|outw
macro_line|#undef outw
DECL|macro|outw_p
macro_line|#undef outw_p
DECL|macro|outsw
macro_line|#undef outsw
DECL|macro|inw
macro_line|#undef inw
DECL|macro|inw_p
macro_line|#undef inw_p
DECL|macro|insw
macro_line|#undef insw
DECL|macro|insl
macro_line|#undef insl
DECL|macro|outsl
macro_line|#undef outsl
DECL|macro|outw
mdefine_line|#define&t;outw(v, a)&t;     ide_outw(v, (unsigned long) (a))
DECL|macro|outw_p
mdefine_line|#define&t;outw_p(v, a)     ide_outw(v, (unsigned long) (a))
DECL|macro|outsw
mdefine_line|#define outsw(a, b, n)   ide_outsw((unsigned long) (a), b, n)
DECL|macro|inw
mdefine_line|#define&t;inw(a)&t;         ide_inw((unsigned long) (a))
DECL|macro|inw_p
mdefine_line|#define&t;inw_p(a)&t;     ide_inw((unsigned long) (a))
DECL|macro|insw
mdefine_line|#define insw(a, b, n)    ide_insw((unsigned long) (a), b, n)
DECL|macro|insl
mdefine_line|#define insl(a, b, n)    ide_insl((unsigned long) (a), b, n)
DECL|macro|outsl
mdefine_line|#define outsl(a, b, n)   ide_outsl((unsigned long) (a), b, n)
macro_line|#endif CONFIG_COLDFIRE
multiline_comment|/****************************************************************************/
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68KNOMMU_IDE_H */
multiline_comment|/****************************************************************************/
eof
