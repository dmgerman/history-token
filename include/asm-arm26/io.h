multiline_comment|/*&n; *  linux/include/asm-arm/io.h&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *  16-Sep-1996&t;RMK&t;Inlined the inx/outx functions &amp; optimised for both&n; *&t;&t;&t;constant addresses and variable addresses.&n; *  04-Dec-1997&t;RMK&t;Moved a lot of this stuff to the new architecture&n; *&t;&t;&t;specific IO header files.&n; *  27-Mar-1999&t;PJB&t;Second parameter of memcpy_toio is const..&n; *  04-Apr-1999&t;PJB&t;Added check_signature.&n; *  12-Dec-1999&t;RMK&t;More cleanups&n; *  18-Jun-2000 RMK&t;Removed virt_to_* and friends definitions&n; */
macro_line|#ifndef __ASM_ARM_IO_H
DECL|macro|__ASM_ARM_IO_H
mdefine_line|#define __ASM_ARM_IO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
multiline_comment|/*&n; * Generic IO read/write.  These perform native-endian accesses.  Note&n; * that some architectures will want to re-define __raw_{read,write}w.&n; */
r_extern
r_void
id|__raw_writesb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|bytelen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_writesw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|wordlen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_writesl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|longlen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_readsb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|data
comma
r_int
id|bytelen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_readsw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|data
comma
r_int
id|wordlen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_readsl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|data
comma
r_int
id|longlen
)paren
suffix:semicolon
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)       (*(volatile unsigned char  *)(a) = (v))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)       (*(volatile unsigned short *)(a) = (v))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)       (*(volatile unsigned int   *)(a) = (v))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)          (*(volatile unsigned char  *)(a))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)          (*(volatile unsigned short *)(a))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)          (*(volatile unsigned int   *)(a))
multiline_comment|/*&n; * Bad read/write accesses...&n; */
r_extern
r_void
id|__readwrite_bug
c_func
(paren
r_const
r_char
op_star
id|fn
)paren
suffix:semicolon
multiline_comment|/*&n; * Now, pick up the machine-defined IO definitions&n; */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * GCC is totally crap at loading/storing data.  We try to persuade it&n; * to do the right thing by using these whereever possible instead of&n; * the above.&n; */
DECL|macro|__arch_base_getb
mdefine_line|#define __arch_base_getb(b,o)                   &bslash;&n; ({                                             &bslash;&n;        unsigned int v, r = (b);                &bslash;&n;        __asm__ __volatile__(                   &bslash;&n;                &quot;ldrb   %0, [%1, %2]&quot;           &bslash;&n;                : &quot;=r&quot; (v)                      &bslash;&n;                : &quot;r&quot; (r), &quot;Ir&quot; (o));           &bslash;&n;        v;                                      &bslash;&n; })
DECL|macro|__arch_base_getl
mdefine_line|#define __arch_base_getl(b,o)                   &bslash;&n; ({                                             &bslash;&n;        unsigned int v, r = (b);                &bslash;&n;        __asm__ __volatile__(                   &bslash;&n;                &quot;ldr    %0, [%1, %2]&quot;           &bslash;&n;                : &quot;=r&quot; (v)                      &bslash;&n;                : &quot;r&quot; (r), &quot;Ir&quot; (o));           &bslash;&n;        v;                                      &bslash;&n; })
DECL|macro|__arch_base_putb
mdefine_line|#define __arch_base_putb(v,b,o)                 &bslash;&n; ({                                             &bslash;&n;        unsigned int r = (b);                   &bslash;&n;        __asm__ __volatile__(                   &bslash;&n;                &quot;strb   %0, [%1, %2]&quot;           &bslash;&n;                :                               &bslash;&n;                : &quot;r&quot; (v), &quot;r&quot; (r), &quot;Ir&quot; (o));  &bslash;&n; })
DECL|macro|__arch_base_putl
mdefine_line|#define __arch_base_putl(v,b,o)                 &bslash;&n; ({                                             &bslash;&n;        unsigned int r = (b);                   &bslash;&n;        __asm__ __volatile__(                   &bslash;&n;                &quot;str    %0, [%1, %2]&quot;           &bslash;&n;                :                               &bslash;&n;                : &quot;r&quot; (v), &quot;r&quot; (r), &quot;Ir&quot; (o));  &bslash;&n; })
multiline_comment|/*&n; * We use two different types of addressing - PC style addresses, and ARM&n; * addresses.  PC style accesses the PC hardware with the normal PC IO&n; * addresses, eg 0x3f8 for serial#1.  ARM addresses are 0x80000000+&n; * and are translated to the start of IO.  Note that all addresses are&n; * shifted left!&n; */
DECL|macro|__PORT_PCIO
mdefine_line|#define __PORT_PCIO(x)  (!((x) &amp; 0x80000000))
multiline_comment|/*&n; * Dynamic IO functions - let the compiler&n; * optimize the expressions&n; */
DECL|function|__outb
r_static
r_inline
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
l_string|&quot;tst    %2, #0x80000000&bslash;n&bslash;t&quot;
l_string|&quot;mov    %0, %4&bslash;n&bslash;t&quot;
l_string|&quot;addeq  %0, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;strb   %1, [%0, %2, lsl #2]    @ outb&quot;
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
r_static
r_inline
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
l_string|&quot;tst    %2, #0x80000000&bslash;n&bslash;t&quot;
l_string|&quot;mov    %0, %4&bslash;n&bslash;t&quot;
l_string|&quot;addeq  %0, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;str    %1, [%0, %2, lsl #2]    @ outw&quot;
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
r_static
r_inline
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
l_string|&quot;tst    %2, #0x80000000&bslash;n&bslash;t&quot;
l_string|&quot;mov    %0, %4&bslash;n&bslash;t&quot;
l_string|&quot;addeq  %0, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;str    %1, [%0, %2, lsl #2]    @ outl&quot;
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
mdefine_line|#define DECLARE_DYN_IN(sz,fnsuffix,instr)                                       &bslash;&n;static inline unsigned sz __in##fnsuffix (unsigned int port)            &bslash;&n;{                                                                               &bslash;&n;        unsigned long temp, value;                                              &bslash;&n;        __asm__ __volatile__(                                                   &bslash;&n;        &quot;tst    %2, #0x80000000&bslash;n&bslash;t&quot;                                            &bslash;&n;        &quot;mov    %0, %4&bslash;n&bslash;t&quot;                                                     &bslash;&n;        &quot;addeq  %0, %0, %3&bslash;n&bslash;t&quot;                                                 &bslash;&n;        &quot;ldr&quot; instr &quot;   %1, [%0, %2, lsl #2]    @ in&quot; #fnsuffix                 &bslash;&n;        : &quot;=&amp;r&quot; (temp), &quot;=r&quot; (value)                                            &bslash;&n;        : &quot;r&quot; (port), &quot;Ir&quot; (PCIO_BASE - IO_BASE), &quot;Ir&quot; (IO_BASE)                &bslash;&n;        : &quot;cc&quot;);                                                                &bslash;&n;        return (unsigned sz)value;                                              &bslash;&n;}
DECL|function|__ioaddr
r_static
r_inline
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
mdefine_line|#define DECLARE_IO(sz,fnsuffix,instr)   &bslash;&n;        DECLARE_DYN_IN(sz,fnsuffix,instr)
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
mdefine_line|#define __outbc(value,port)                                                     &bslash;&n;({                                                                              &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;strb   %0, [%1, %2]    @ outbc&quot;                                &bslash;&n;                : : &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));          &bslash;&n;        else                                                                    &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;strb   %0, [%1, %2]    @ outbc&quot;                                &bslash;&n;                : : &quot;r&quot; (value), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));             &bslash;&n;})
DECL|macro|__inbc
mdefine_line|#define __inbc(port)                                                            &bslash;&n;({                                                                              &bslash;&n;        unsigned char result;                                                   &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;ldrb   %0, [%1, %2]    @ inbc&quot;                                 &bslash;&n;                : &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));         &bslash;&n;        else                                                                    &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;ldrb   %0, [%1, %2]    @ inbc&quot;                                 &bslash;&n;                : &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));            &bslash;&n;        result;                                                                 &bslash;&n;})
DECL|macro|__outwc
mdefine_line|#define __outwc(value,port)                                                     &bslash;&n;({                                                                              &bslash;&n;        unsigned long v = value;                                                &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;str    %0, [%1, %2]    @ outwc&quot;                                &bslash;&n;                : : &quot;r&quot; (v|v&lt;&lt;16), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));        &bslash;&n;        else                                                                    &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;str    %0, [%1, %2]    @ outwc&quot;                                &bslash;&n;                : : &quot;r&quot; (v|v&lt;&lt;16), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));           &bslash;&n;})
DECL|macro|__inwc
mdefine_line|#define __inwc(port)                                                            &bslash;&n;({                                                                              &bslash;&n;        unsigned short result;                                                  &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;ldr    %0, [%1, %2]    @ inwc&quot;                                 &bslash;&n;                : &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));         &bslash;&n;        else                                                                    &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;ldr    %0, [%1, %2]    @ inwc&quot;                                 &bslash;&n;                : &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));            &bslash;&n;        result &amp; 0xffff;                                                        &bslash;&n;})
DECL|macro|__outlc
mdefine_line|#define __outlc(value,port)                                                     &bslash;&n;({                                                                              &bslash;&n;        unsigned long v = value;                                                &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;str    %0, [%1, %2]    @ outlc&quot;                                &bslash;&n;                : : &quot;r&quot; (v), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));              &bslash;&n;        else                                                                    &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;str    %0, [%1, %2]    @ outlc&quot;                                &bslash;&n;                : : &quot;r&quot; (v), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));                 &bslash;&n;})
DECL|macro|__inlc
mdefine_line|#define __inlc(port)                                                            &bslash;&n;({                                                                              &bslash;&n;        unsigned long result;                                                   &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;ldr    %0, [%1, %2]    @ inlc&quot;                                 &bslash;&n;                : &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));         &bslash;&n;        else                                                                    &bslash;&n;                __asm__ __volatile__(                                           &bslash;&n;                &quot;ldr    %0, [%1, %2]    @ inlc&quot;                                 &bslash;&n;                : &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));            &bslash;&n;        result;                                                                 &bslash;&n;})
DECL|macro|__ioaddrc
mdefine_line|#define __ioaddrc(port)                                                         &bslash;&n;({                                                                              &bslash;&n;        unsigned long addr;                                                     &bslash;&n;        if (__PORT_PCIO((port)))                                                &bslash;&n;                addr = PCIO_BASE + ((port) &lt;&lt; 2);                               &bslash;&n;        else                                                                    &bslash;&n;                addr = IO_BASE + ((port) &lt;&lt; 2);                                 &bslash;&n;        addr;                                                                   &bslash;&n;})
DECL|macro|inb
mdefine_line|#define inb(p)          (__builtin_constant_p((p)) ? __inbc(p)    : __inb(p))
DECL|macro|inw
mdefine_line|#define inw(p)          (__builtin_constant_p((p)) ? __inwc(p)    : __inw(p))
DECL|macro|inl
mdefine_line|#define inl(p)          (__builtin_constant_p((p)) ? __inlc(p)    : __inl(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)       (__builtin_constant_p((p)) ? __outbc(v,p) : __outb(v,p))
DECL|macro|outw
mdefine_line|#define outw(v,p)       (__builtin_constant_p((p)) ? __outwc(v,p) : __outw(v,p))
DECL|macro|outl
mdefine_line|#define outl(v,p)       (__builtin_constant_p((p)) ? __outlc(v,p) : __outl(v,p))
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)     (__builtin_constant_p((p)) ? __ioaddr(p)  : __ioaddrc(p))
multiline_comment|/* JMA 18.02.03 added sb,sl from arm/io.h, changing io to ioaddr */
DECL|macro|outsb
mdefine_line|#define outsb(p,d,l)            __raw_writesb(__ioaddr(p),d,l)
DECL|macro|outsw
mdefine_line|#define outsw(p,d,l)            __raw_writesw(__ioaddr(p),d,l)
DECL|macro|outsl
mdefine_line|#define outsl(p,d,l)            __raw_writesl(__ioaddr(p),d,l)
DECL|macro|insb
mdefine_line|#define insb(p,d,l)             __raw_readsb(__ioaddr(p),d,l)
DECL|macro|insw
mdefine_line|#define insw(p,d,l)             __raw_readsw(__ioaddr(p),d,l)
DECL|macro|insl
mdefine_line|#define insl(p,d,l)             __raw_readsl(__ioaddr(p),d,l)
DECL|macro|insw
mdefine_line|#define insw(p,d,l)     __raw_readsw(__ioaddr(p),d,l)
DECL|macro|outsw
mdefine_line|#define outsw(p,d,l)    __raw_writesw(__ioaddr(p),d,l)
DECL|macro|readb
mdefine_line|#define readb(c)                        (__readwrite_bug(&quot;readb&quot;),0)
DECL|macro|readw
mdefine_line|#define readw(c)                        (__readwrite_bug(&quot;readw&quot;),0)
DECL|macro|readl
mdefine_line|#define readl(c)                        (__readwrite_bug(&quot;readl&quot;),0)
DECL|macro|writeb
mdefine_line|#define writeb(v,c)                     __readwrite_bug(&quot;writeb&quot;)
DECL|macro|writew
mdefine_line|#define writew(v,c)                     __readwrite_bug(&quot;writew&quot;)
DECL|macro|writel
mdefine_line|#define writel(v,c)                     __readwrite_bug(&quot;writel&quot;)
DECL|macro|readsw
mdefine_line|#define readsw(p,d,l)                 (__readwrite_bug(&quot;readsw&quot;),0)
DECL|macro|readsl
mdefine_line|#define readsl(p,d,l)                 (__readwrite_bug(&quot;readsl&quot;),0)
DECL|macro|writesw
mdefine_line|#define writesw(p,d,l)                        __readwrite_bug(&quot;writesw&quot;)
DECL|macro|writesl
mdefine_line|#define writesl(p,d,l)                        __readwrite_bug(&quot;writesl&quot;)
multiline_comment|/* the following macro is depreciated */
DECL|macro|ioaddr
mdefine_line|#define ioaddr(port)                    __ioaddr((port))
multiline_comment|/*&n; * No ioremap support here.&n; */
DECL|macro|__arch_ioremap
mdefine_line|#define __arch_ioremap(c,s,f,a)   ((void *)(c))
DECL|macro|__arch_iounmap
mdefine_line|#define __arch_iounmap(c)       do { }  while (0)
macro_line|#if defined(__arch_putb) || defined(__arch_putw) || defined(__arch_putl) || &bslash;&n;    defined(__arch_getb) || defined(__arch_getw) || defined(__arch_getl)
macro_line|#warning machine class uses old __arch_putw or __arch_getw
macro_line|#endif
multiline_comment|/*&n; *  IO port access primitives&n; *  -------------------------&n; *&n; * The ARM doesn&squot;t have special IO access instructions; all IO is memory&n; * mapped.  Note that these are defined to perform little endian accesses&n; * only.  Their primary purpose is to access PCI and ISA peripherals.&n; *&n; * Note that for a big endian machine, this implies that the following&n; * big endian mode connectivity is in place, as described by numerious&n; * ARM documents:&n; *&n; *    PCI:  D0-D7   D8-D15 D16-D23 D24-D31&n; *    ARM: D24-D31 D16-D23  D8-D15  D0-D7&n; *&n; * The machine specific io.h include defines __io to translate an &quot;IO&quot;&n; * address to a memory address.&n; *&n; * Note that we prevent GCC re-ordering or caching values in expressions&n; * by introducing sequence points into the in*() definitions.  Note that&n; * __raw_* do not guarantee this behaviour.&n; */
multiline_comment|/*&n;#define outsb(p,d,l)&t;&t;__raw_writesb(__io(p),d,l)&n;#define outsw(p,d,l)&t;&t;__raw_writesw(__io(p),d,l)&n;&n;#define insb(p,d,l)&t;&t;__raw_readsb(__io(p),d,l)&n;#define insw(p,d,l)&t;&t;__raw_readsw(__io(p),d,l)&n;*/
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port)&t;outb((val),(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port)&t;outw((val),(port))
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;inb((port))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;inw((port))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;inl((port))
DECL|macro|outsb_p
mdefine_line|#define outsb_p(port,from,len)&t;outsb(port,from,len)
DECL|macro|outsw_p
mdefine_line|#define outsw_p(port,from,len)&t;outsw(port,from,len)
DECL|macro|insb_p
mdefine_line|#define insb_p(port,to,len)&t;insb(port,to,len)
DECL|macro|insw_p
mdefine_line|#define insw_p(port,to,len)&t;insw(port,to,len)
multiline_comment|/*&n; * String version of IO memory access ops:&n; */
r_extern
r_void
id|_memcpy_fromio
c_func
(paren
r_void
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_memcpy_toio
c_func
(paren
r_int
r_int
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_memset_io
c_func
(paren
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * ioremap and friends.&n; *&n; * ioremap takes a PCI memory address, as specified in&n; * linux/Documentation/IO-mapping.txt.&n; */
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
macro_line|#ifndef __arch_ioremap
DECL|macro|ioremap
mdefine_line|#define ioremap(cookie,size)&t;&t;__ioremap(cookie,size,0,1)
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(cookie,size)&t;__ioremap(cookie,size,0,1)
DECL|macro|iounmap
mdefine_line|#define iounmap(cookie)&t;&t;&t;__iounmap(cookie)
macro_line|#else
DECL|macro|ioremap
mdefine_line|#define ioremap(cookie,size)&t;&t;__arch_ioremap((cookie),(size),0,1)
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(cookie,size)&t;__arch_ioremap((cookie),(size),0,1)
DECL|macro|iounmap
mdefine_line|#define iounmap(cookie)&t;&t;&t;__arch_iounmap(cookie)
macro_line|#endif
multiline_comment|/*&n; * DMA-consistent mapping functions.  These allocate/free a region of&n; * uncached, unwrite-buffered mapped memory space for use with DMA&n; * devices.  This is the &quot;generic&quot; version.  The PCI specific version&n; * is in pci.h&n; */
r_extern
r_void
op_star
id|consistent_alloc
c_func
(paren
r_int
id|gfp
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|handle
)paren
suffix:semicolon
r_extern
r_void
id|consistent_free
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
id|dma_addr_t
id|handle
)paren
suffix:semicolon
r_extern
r_void
id|consistent_sync
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|rw
)paren
suffix:semicolon
multiline_comment|/*&n; * can the hardware map this into one segment or not, given no other&n; * constraints.&n; */
DECL|macro|BIOVEC_MERGEABLE
mdefine_line|#define BIOVEC_MERGEABLE(vec1, vec2)&t;&bslash;&n;&t;((bvec_to_phys((vec1)) + (vec1)-&gt;bv_len) == bvec_to_phys((vec2)))
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __ASM_ARM_IO_H */
eof
