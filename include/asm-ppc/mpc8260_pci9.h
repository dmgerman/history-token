multiline_comment|/* include/asm-ppc/mpc8260_pci9.h&n; *&n; * Undefine the PCI read* and in* macros so we can define them as functions&n; * that implement the workaround for the MPC8260 device erratum PCI 9.&n; *&n; * This header file should only be included at the end of include/asm-ppc/io.h&n; * and never included directly anywhere else.&n; *&n; * Author:  andy_lowe@mvista.com&n; *&n; * 2003 (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef _PPC_IO_H
macro_line|#error &quot;Do not include mpc8260_pci9.h directly.&quot;
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __CONFIG_8260_PCI9_DEFS
DECL|macro|__CONFIG_8260_PCI9_DEFS
mdefine_line|#define __CONFIG_8260_PCI9_DEFS
DECL|macro|readb
macro_line|#undef readb
DECL|macro|readw
macro_line|#undef readw
DECL|macro|readl
macro_line|#undef readl
DECL|macro|insb
macro_line|#undef insb
DECL|macro|insw
macro_line|#undef insw
DECL|macro|insl
macro_line|#undef insl
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inw
macro_line|#undef inw
DECL|macro|inl
macro_line|#undef inl
DECL|macro|insw_ns
macro_line|#undef insw_ns
DECL|macro|insl_ns
macro_line|#undef insl_ns
DECL|macro|memcpy_fromio
macro_line|#undef memcpy_fromio
r_extern
r_int
id|readb
c_func
(paren
r_volatile
r_int
r_char
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|readw
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|readl
c_func
(paren
r_volatile
r_int
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|insb
c_func
(paren
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|insw
c_func
(paren
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|insl
c_func
(paren
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_int
id|inb
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
id|inw
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
id|inl
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|insw_ns
c_func
(paren
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|insl_ns
c_func
(paren
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy_fromio
c_func
(paren
r_void
op_star
id|dest
comma
r_int
r_int
id|src
comma
r_int
id|count
)paren
suffix:semicolon
macro_line|#endif /* !__CONFIG_8260_PCI9_DEFS */
macro_line|#endif /* __KERNEL__ */
eof
