multiline_comment|/*&n; * some sbus structures and macros to make usage of sbus drivers possible&n; */
macro_line|#ifndef __M68K_SBUS_H
DECL|macro|__M68K_SBUS_H
mdefine_line|#define __M68K_SBUS_H
DECL|struct|sbus_dev
r_struct
id|sbus_dev
(brace
r_struct
(brace
DECL|member|which_io
r_int
r_int
id|which_io
suffix:semicolon
DECL|member|phys_addr
r_int
r_int
id|phys_addr
suffix:semicolon
DECL|member|reg_addrs
)brace
id|reg_addrs
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
op_star
id|sparc_alloc_io
(paren
id|u32
comma
r_void
op_star
comma
r_int
comma
r_char
op_star
comma
id|u32
comma
r_int
)paren
suffix:semicolon
DECL|macro|sparc_alloc_io
mdefine_line|#define sparc_alloc_io(a,b,c,d,e,f)&t;(a)
DECL|macro|ARCH_SUN4
mdefine_line|#define ARCH_SUN4  0
multiline_comment|/* sbus IO functions stolen from include/asm-sparc/io.h for the serial driver */
multiline_comment|/* No SBUS on the Sun3, kludge -- sam */
DECL|function|_sbus_writeb
r_static
r_inline
r_void
id|_sbus_writeb
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|function|_sbus_readb
r_static
r_inline
r_int
r_char
id|_sbus_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|_sbus_writel
r_static
r_inline
r_void
id|_sbus_writel
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
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|sbus_readb
mdefine_line|#define sbus_readb(a) _sbus_readb((unsigned long)a)
DECL|macro|sbus_writeb
mdefine_line|#define sbus_writeb(v, a) _sbus_writeb(v, (unsigned long)a)
DECL|macro|sbus_writel
mdefine_line|#define sbus_writel(v, a) _sbus_writel(v, (unsigned long)a)
macro_line|#endif
eof
