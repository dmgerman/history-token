multiline_comment|/*&n; * some sbus structures and macros to make usage of sbus drivers possible&n; */
macro_line|#ifndef __M68K_SBUS_H
DECL|macro|__M68K_SBUS_H
mdefine_line|#define __M68K_SBUS_H
DECL|struct|linux_sbus_device
r_struct
id|linux_sbus_device
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
macro_line|#endif
eof
