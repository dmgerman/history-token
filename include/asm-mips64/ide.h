multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains the MIPS architecture specific IDE code.&n; *&n; * Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the MIPS architecture specific IDE code.&n; */
macro_line|#ifndef __ASM_IDE_H
DECL|macro|__ASM_IDE_H
mdefine_line|#define __ASM_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef MAX_HWIFS
macro_line|# ifdef CONFIG_BLK_DEV_IDEPCI
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;10
macro_line|# else
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;6
macro_line|# endif
macro_line|#endif
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;__sti()
DECL|struct|ide_ops
r_struct
id|ide_ops
(brace
DECL|member|ide_default_irq
r_int
(paren
op_star
id|ide_default_irq
)paren
(paren
id|ide_ioreg_t
id|base
)paren
suffix:semicolon
DECL|member|ide_default_io_base
id|ide_ioreg_t
(paren
op_star
id|ide_default_io_base
)paren
(paren
r_int
id|index
)paren
suffix:semicolon
DECL|member|ide_init_hwif_ports
r_void
(paren
op_star
id|ide_init_hwif_ports
)paren
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
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ide_ops
op_star
id|ide_ops
suffix:semicolon
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
id|ide_ops
op_member_access_from_pointer
id|ide_default_irq
c_func
(paren
id|base
)paren
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
id|ide_ops
op_member_access_from_pointer
id|ide_default_io_base
c_func
(paren
id|index
)paren
suffix:semicolon
)brace
DECL|function|ide_init_hwif_ports
r_static
r_inline
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
id|ide_ops
op_member_access_from_pointer
id|ide_init_hwif_ports
c_func
(paren
id|hw
comma
id|data_port
comma
id|ctrl_port
comma
id|irq
)paren
suffix:semicolon
)brace
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
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|bit5
r_int
id|bit5
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
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
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
DECL|member|bit0
r_int
id|bit0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nIEN
r_int
id|nIEN
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device INTRQ to host */
DECL|member|SRST
r_int
id|SRST
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* host soft reset bit */
DECL|member|bit3
r_int
id|bit3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ATA-2 thingy */
DECL|member|reserved456
r_int
id|reserved456
suffix:colon
l_int|3
suffix:semicolon
DECL|member|HOB
r_int
id|HOB
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 48-bit address ordering */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|control_t
)brace
id|control_t
suffix:semicolon
macro_line|#if defined(CONFIG_SWAP_IO_SPACE) &amp;&amp; defined(__MIPSEB__)
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
DECL|macro|insw
mdefine_line|#define insw(p,a,c)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short *ptr = (unsigned short *)(a);&t;&t;&t;&bslash;&n;&t;unsigned int i = (c);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (i--)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*ptr++ = inw(p);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|insl
mdefine_line|#define insl(p,a,c)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long *ptr = (unsigned long *)(a);&t;&t;&t;&bslash;&n;&t;unsigned int i = (c);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (i--)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*ptr++ = inl(p);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|outsw
mdefine_line|#define outsw(p,a,c)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short *ptr = (unsigned short *)(a);&t;&t;&t;&bslash;&n;&t;unsigned int i = (c);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (i--)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;outw(*ptr++, (p));&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|outsl
mdefine_line|#define outsl(p,a,c) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long *ptr = (unsigned long *)(a);&t;&t;&t;&bslash;&n;&t;unsigned int i = (c);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (i--)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;outl(*ptr++, (p));&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* defined(CONFIG_SWAP_IO_SPACE) &amp;&amp; defined(__MIPSEB__)  */
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_fix_driveid
mdefine_line|#define ide_fix_driveid(id)&t;&t;do {} while (0)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_IDE_H */
eof
