multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains the MIPS architecture specific IDE code.&n; *&n; * Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the MIPS architecture specific IDE code.&n; */
macro_line|#ifndef __ASM_IDE_H
DECL|macro|__ASM_IDE_H
mdefine_line|#define __ASM_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef MAX_HWIFS
macro_line|# ifdef CONFIG_PCI
DECL|macro|MAX_HWIFS
macro_line|#  define MAX_HWIFS&t;10
macro_line|# else
DECL|macro|MAX_HWIFS
macro_line|#  define MAX_HWIFS&t;6
macro_line|# endif
macro_line|#endif
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
macro_line|#ifndef CONFIG_PCI
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
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_IDE_H */
eof
