multiline_comment|/*&n; *  arch/i386/mach-pc9800/mach_reboot.h&n; *&n; *  Machine specific reboot functions for PC-9800.&n; *  Written by Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; */
macro_line|#ifndef _MACH_REBOOT_H
DECL|macro|_MACH_REBOOT_H
mdefine_line|#define _MACH_REBOOT_H
macro_line|#ifdef CMOS_WRITE
DECL|macro|CMOS_WRITE
macro_line|#undef CMOS_WRITE
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(a,b)&t;do{}while(0)
macro_line|#endif
DECL|function|mach_reboot
r_static
r_inline
r_void
id|mach_reboot
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
l_int|0xf0
)paren
suffix:semicolon
multiline_comment|/* signal CPU reset */
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif /* !_MACH_REBOOT_H */
eof
