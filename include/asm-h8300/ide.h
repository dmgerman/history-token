multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-h8300/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; *  Copyright (C) 2001       Lineo Inc., davidm@snapgear.com&n; *  Copyright (C) 2002       Greg Ungerer (gerg@snapgear.com)&n; *  Copyright (C) 2002       Yoshinori Sato (ysato@users.sourceforge.jp)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef _H8300_IDE_H
DECL|macro|_H8300_IDE_H
mdefine_line|#define _H8300_IDE_H
multiline_comment|/****************************************************************************/
macro_line|#ifdef __KERNEL__
multiline_comment|/****************************************************************************/
r_void
id|h8300_ide_print_resource
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
suffix:semicolon
DECL|function|ide_default_irq
r_static
r_inline
r_int
id|ide_default_irq
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ide_default_io_base
r_static
r_inline
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
suffix:semicolon
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
r_int
r_int
id|data_port
comma
r_int
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
)brace
DECL|function|ide_init_default_hwifs
r_static
r_inline
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
)brace
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;1
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw(port,addr,count)  do { } while(0)
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl(port,addr,count)  do { } while(0)
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw(port,addr,count) do { } while(0)
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl(port,addr,count) do { } while(0)
multiline_comment|/****************************************************************************/
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _H8300_IDE_H */
multiline_comment|/****************************************************************************/
eof
