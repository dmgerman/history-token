multiline_comment|/* $Id: ide.h,v 1.21 2001/09/25 20:21:48 kanoj Exp $&n; * ide.h: Ultra/PCI specific IDE glue.&n; *&n; * Copyright (C) 1997  David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998  Eddie C. Dost   (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC64_IDE_H
DECL|macro|_SPARC64_IDE_H
mdefine_line|#define _SPARC64_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hdreg.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
DECL|macro|MAX_HWIFS
macro_line|#undef  MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;2
DECL|macro|ide__sti
mdefine_line|#define&t;ide__sti()&t;__sti()
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
id|ide_ioreg_t
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_init_hwif_ports
r_static
id|__inline__
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
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
id|hw-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
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
macro_line|#ifndef CONFIG_BLK_DEV_IDEPCI
id|hw_regs_t
id|hw
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
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hw
comma
id|ide_default_io_base
c_func
(paren
id|index
)paren
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
id|ide_default_io_base
c_func
(paren
id|index
)paren
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
macro_line|#endif /* CONFIG_BLK_DEV_IDEPCI */
)brace
r_typedef
r_union
(brace
r_int
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
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lba
r_int
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bit5
r_int
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unit
r_int
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
DECL|function|ide_request_irq
r_static
id|__inline__
r_int
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
id|name
comma
r_void
op_star
id|devid
)paren
(brace
r_return
id|request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|SA_SHIRQ
comma
id|name
comma
id|devid
)paren
suffix:semicolon
)brace
DECL|function|ide_free_irq
r_static
id|__inline__
r_void
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
DECL|function|ide_check_region
r_static
id|__inline__
r_int
id|ide_check_region
c_func
(paren
id|ide_ioreg_t
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|check_region
c_func
(paren
id|base
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|ide_request_region
r_static
id|__inline__
r_void
id|ide_request_region
c_func
(paren
id|ide_ioreg_t
id|base
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|request_region
c_func
(paren
id|base
comma
id|size
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|ide_release_region
r_static
id|__inline__
r_void
id|ide_release_region
c_func
(paren
id|ide_ioreg_t
id|base
comma
r_int
r_int
id|size
)paren
(brace
id|release_region
c_func
(paren
id|base
comma
id|size
)paren
suffix:semicolon
)brace
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef  SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS 0
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef  SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC 0
DECL|macro|HD_DATA
macro_line|#undef  HD_DATA
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA ((ide_ioreg_t)0)
multiline_comment|/* From m68k code... */
macro_line|#ifdef insl
DECL|macro|insl
macro_line|#undef insl
macro_line|#endif
macro_line|#ifdef outsl
DECL|macro|outsl
macro_line|#undef outsl
macro_line|#endif
macro_line|#ifdef insw
DECL|macro|insw
macro_line|#undef insw
macro_line|#endif
macro_line|#ifdef outsw
DECL|macro|outsw
macro_line|#undef outsw
macro_line|#endif
DECL|macro|insl
mdefine_line|#define insl(data_reg, buffer, wcount) insw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|outsl
mdefine_line|#define outsl(data_reg, buffer, wcount) outsw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|insw
mdefine_line|#define insw(port, buf, nr) ide_insw((port), (buf), (nr))
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, nr) ide_outsw((port), (buf), (nr))
DECL|function|inw_be
r_static
id|__inline__
r_int
r_int
id|inw_be
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ide_insw
r_static
id|__inline__
r_void
id|ide_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
r_int
r_int
id|end
op_assign
(paren
r_int
r_int
)paren
id|dst
op_plus
(paren
id|count
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|u16
op_star
id|ps
op_assign
id|dst
suffix:semicolon
id|u32
op_star
id|pi
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u64
)paren
id|ps
)paren
op_amp
l_int|0x2
)paren
(brace
op_star
id|ps
op_increment
op_assign
id|inw_be
c_func
(paren
id|port
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|pi
op_assign
(paren
id|u32
op_star
)paren
id|ps
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
l_int|2
)paren
(brace
id|u32
id|w
suffix:semicolon
id|w
op_assign
id|inw_be
c_func
(paren
id|port
)paren
op_lshift
l_int|16
suffix:semicolon
id|w
op_or_assign
id|inw_be
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|pi
op_increment
op_assign
id|w
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|ps
op_assign
(paren
id|u16
op_star
)paren
id|pi
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
op_star
id|ps
op_increment
op_assign
id|inw_be
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
id|__flush_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|dst
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|outw_be
r_static
id|__inline__
r_void
id|outw_be
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha %0, [%1] %2&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|ide_outsw
r_static
id|__inline__
r_void
id|ide_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
(brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
r_int
r_int
id|end
op_assign
(paren
r_int
r_int
)paren
id|src
op_plus
(paren
id|count
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_const
id|u16
op_star
id|ps
op_assign
id|src
suffix:semicolon
r_const
id|u32
op_star
id|pi
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u64
)paren
id|src
)paren
op_amp
l_int|0x2
)paren
(brace
id|outw_be
c_func
(paren
op_star
id|ps
op_increment
comma
id|port
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|pi
op_assign
(paren
r_const
id|u32
op_star
)paren
id|ps
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
l_int|2
)paren
(brace
id|u32
id|w
suffix:semicolon
id|w
op_assign
op_star
id|pi
op_increment
suffix:semicolon
id|outw_be
c_func
(paren
(paren
id|w
op_rshift
l_int|16
)paren
comma
id|port
)paren
suffix:semicolon
id|outw_be
c_func
(paren
id|w
comma
id|port
)paren
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|ps
op_assign
(paren
r_const
id|u16
op_star
)paren
id|pi
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|outw_be
c_func
(paren
op_star
id|ps
comma
id|port
)paren
suffix:semicolon
)brace
macro_line|#if (L1DCACHE_SIZE &gt; PAGE_SIZE)&t;&t;/* is there D$ aliasing problem */
id|__flush_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|src
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|T_CHAR
mdefine_line|#define T_CHAR          (0x0000)        /* char:  don&squot;t touch  */
DECL|macro|T_SHORT
mdefine_line|#define T_SHORT         (0x4000)        /* short: 12 -&gt; 21     */
DECL|macro|T_INT
mdefine_line|#define T_INT           (0x8000)        /* int:   1234 -&gt; 4321 */
DECL|macro|T_TEXT
mdefine_line|#define T_TEXT          (0xc000)        /* text:  12 -&gt; 21     */
DECL|macro|T_MASK_TYPE
mdefine_line|#define T_MASK_TYPE     (0xc000)
DECL|macro|T_MASK_COUNT
mdefine_line|#define T_MASK_COUNT    (0x3fff)
DECL|macro|D_CHAR
mdefine_line|#define D_CHAR(cnt)     (T_CHAR  | (cnt))
DECL|macro|D_SHORT
mdefine_line|#define D_SHORT(cnt)    (T_SHORT | (cnt))
DECL|macro|D_INT
mdefine_line|#define D_INT(cnt)      (T_INT   | (cnt))
DECL|macro|D_TEXT
mdefine_line|#define D_TEXT(cnt)     (T_TEXT  | (cnt))
DECL|variable|driveid_types
r_static
id|u_short
id|driveid_types
(braket
)braket
op_assign
(brace
id|D_SHORT
c_func
(paren
l_int|10
)paren
comma
multiline_comment|/* config - vendor2 */
id|D_TEXT
c_func
(paren
l_int|20
)paren
comma
multiline_comment|/* serial_no */
id|D_SHORT
c_func
(paren
l_int|3
)paren
comma
multiline_comment|/* buf_type - ecc_bytes */
id|D_TEXT
c_func
(paren
l_int|48
)paren
comma
multiline_comment|/* fw_rev - model */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* max_multsect - vendor3 */
id|D_SHORT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* dword_io */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* vendor4 - capability */
id|D_SHORT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* reserved50 */
id|D_CHAR
c_func
(paren
l_int|4
)paren
comma
multiline_comment|/* vendor5 - tDMA */
id|D_SHORT
c_func
(paren
l_int|4
)paren
comma
multiline_comment|/* field_valid - cur_sectors */
id|D_INT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* cur_capacity */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* multsect - multsect_valid */
id|D_INT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* lba_capacity */
id|D_SHORT
c_func
(paren
l_int|194
)paren
multiline_comment|/* dma_1word - reservedyy */
)brace
suffix:semicolon
DECL|macro|num_driveid_types
mdefine_line|#define num_driveid_types       (sizeof(driveid_types)/sizeof(*driveid_types))
DECL|function|ide_fix_driveid
r_static
id|__inline__
r_void
id|ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
id|id
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|cnt
suffix:semicolon
id|u_char
id|t
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
id|num_driveid_types
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cnt
op_assign
id|driveid_types
(braket
id|i
)braket
op_amp
id|T_MASK_COUNT
suffix:semicolon
r_switch
c_cond
(paren
id|driveid_types
(braket
id|i
)braket
op_amp
id|T_MASK_TYPE
)paren
(brace
r_case
id|T_CHAR
suffix:colon
id|p
op_add_assign
id|cnt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|T_SHORT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|T_INT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|3
)braket
suffix:semicolon
id|p
(braket
l_int|3
)braket
op_assign
id|t
suffix:semicolon
id|t
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
id|p
(braket
l_int|2
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|T_TEXT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC64_IDE_H */
eof
