multiline_comment|/*&n; *  linux/include/asm-arm/arch-rpc/io.h&n; *&n; *  Copyright (C) 1997 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * We use two different types of addressing - PC style addresses, and ARM&n; * addresses.  PC style accesses the PC hardware with the normal PC IO&n; * addresses, eg 0x3f8 for serial#1.  ARM addresses are 0x80000000+&n; * and are translated to the start of IO.  Note that all addresses are&n; * shifted left!&n; */
DECL|macro|__PORT_PCIO
mdefine_line|#define __PORT_PCIO(x)&t;(!((x) &amp; 0x80000000))
multiline_comment|/*&n; * Dynamic IO functions.&n; */
DECL|function|__outb
r_extern
id|__inline__
r_void
id|__outb
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;tst&t;%2, #0x80000000&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%0, %4&bslash;n&bslash;t&quot;
l_string|&quot;addeq&t;%0, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;strb&t;%1, [%0, %2, lsl #2]&t;@ outb&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|port
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|PCIO_BASE
op_minus
id|IO_BASE
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|IO_BASE
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|__outw
r_extern
id|__inline__
r_void
id|__outw
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;tst&t;%2, #0x80000000&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%0, %4&bslash;n&bslash;t&quot;
l_string|&quot;addeq&t;%0, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;str&t;%1, [%0, %2, lsl #2]&t;@ outw&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
op_or
id|value
op_lshift
l_int|16
)paren
comma
l_string|&quot;r&quot;
(paren
id|port
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|PCIO_BASE
op_minus
id|IO_BASE
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|IO_BASE
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|__outl
r_extern
id|__inline__
r_void
id|__outl
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;tst&t;%2, #0x80000000&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%0, %4&bslash;n&bslash;t&quot;
l_string|&quot;addeq&t;%0, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;str&t;%1, [%0, %2, lsl #2]&t;@ outl&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|port
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|PCIO_BASE
op_minus
id|IO_BASE
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|IO_BASE
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|DECLARE_DYN_IN
mdefine_line|#define DECLARE_DYN_IN(sz,fnsuffix,instr)&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned sz __in##fnsuffix (unsigned int port)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long temp, value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;tst&t;%2, #0x80000000&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%0, %4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;addeq&t;%0, %0, %3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr&quot; ##instr## &quot;&t;%1, [%0, %2, lsl #2]&t;@ in&quot;###fnsuffix&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (temp), &quot;=r&quot; (value)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (port), &quot;Ir&quot; (PCIO_BASE - IO_BASE), &quot;Ir&quot; (IO_BASE)&t;&t;&bslash;&n;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (unsigned sz)value;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|function|__ioaddr
r_extern
id|__inline__
r_int
r_int
id|__ioaddr
(paren
r_int
r_int
id|port
)paren
"&bslash;"
(brace
"&bslash;"
r_if
c_cond
(paren
id|__PORT_PCIO
c_func
(paren
id|port
)paren
)paren
"&bslash;"
r_return
(paren
r_int
r_int
)paren
(paren
id|PCIO_BASE
op_plus
(paren
id|port
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
"&bslash;"
r_else
"&bslash;"
r_return
(paren
r_int
r_int
)paren
(paren
id|IO_BASE
op_plus
(paren
id|port
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
"&bslash;"
)brace
DECL|macro|DECLARE_IO
mdefine_line|#define DECLARE_IO(sz,fnsuffix,instr)&t;&bslash;&n;&t;DECLARE_DYN_IN(sz,fnsuffix,instr)
id|DECLARE_IO
c_func
(paren
r_char
comma
id|b
comma
l_string|&quot;b&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|w
comma
l_string|&quot;&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|l
comma
l_string|&quot;&quot;
)paren
DECL|macro|DECLARE_IO
macro_line|#undef DECLARE_IO
DECL|macro|DECLARE_DYN_IN
macro_line|#undef DECLARE_DYN_IN
multiline_comment|/*&n; * Constant address IO functions&n; *&n; * These have to be macros for the &squot;J&squot; constraint to work -&n; * +/-4096 immediate operand.&n; */
DECL|macro|__outbc
mdefine_line|#define __outbc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strb&t;%0, [%1, %2]&t;@ outbc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strb&t;%0, [%1, %2]&t;@ outbc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;})
DECL|macro|__inbc
mdefine_line|#define __inbc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrb&t;%0, [%1, %2]&t;@ inbc&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrb&t;%0, [%1, %2]&t;@ inbc&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outwc
mdefine_line|#define __outwc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long v = value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&t;@ outwc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v|v&lt;&lt;16), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&t;@ outwc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v|v&lt;&lt;16), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;})
DECL|macro|__inwc
mdefine_line|#define __inwc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&t;@ inwc&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&t;@ inwc&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;result &amp; 0xffff;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outlc
mdefine_line|#define __outlc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long v = value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&t;@ outlc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&t;@ outlc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&t;&bslash;&n;})
DECL|macro|__inlc
mdefine_line|#define __inlc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&t;@ inlc&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&t;@ inlc&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ioaddrc
mdefine_line|#define __ioaddrc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__PORT_PCIO((port)) ? PCIO_BASE + ((port) &lt;&lt; 2) : IO_BASE + ((port) &lt;&lt; 2))
DECL|macro|inb
mdefine_line|#define inb(p)&t; &t;(__builtin_constant_p((p)) ? __inbc(p)    : __inb(p))
DECL|macro|inw
mdefine_line|#define inw(p)&t; &t;(__builtin_constant_p((p)) ? __inwc(p)    : __inw(p))
DECL|macro|inl
mdefine_line|#define inl(p)&t; &t;(__builtin_constant_p((p)) ? __inlc(p)    : __inl(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;(__builtin_constant_p((p)) ? __outbc(v,p) : __outb(v,p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;(__builtin_constant_p((p)) ? __outwc(v,p) : __outw(v,p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;(__builtin_constant_p((p)) ? __outlc(v,p) : __outl(v,p))
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)&t;(__builtin_constant_p((p)) ? __ioaddr(p)  : __ioaddrc(p))
multiline_comment|/*&n; * Translated address IO functions&n; *&n; * IO address has already been translated to a virtual address&n; */
DECL|macro|outb_t
mdefine_line|#define outb_t(v,p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned char *)(p) = (v))
DECL|macro|inb_t
mdefine_line|#define inb_t(p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned char *)(p))
DECL|macro|outl_t
mdefine_line|#define outl_t(v,p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned long *)(p) = (v))
DECL|macro|inl_t
mdefine_line|#define inl_t(p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned long *)(p))
macro_line|#endif
eof
