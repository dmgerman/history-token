multiline_comment|/*&n; * linux/include/asm-arm/arch-s3c2410/io.h&n; *  from linux/include/asm-arm/arch-rpc/io.h&n; *&n; * Copyright (C) 1997 Russell King&n; *&t;     (C) 2003 Simtec Electronics&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; *  02-Sep-2003 BJD&t;Modified for S3C2410&n; *&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * We use two different types of addressing - PC style addresses, and ARM&n; * addresses.  PC style accesses the PC hardware with the normal PC IO&n; * addresses, eg 0x3f8 for serial#1.  ARM addresses are above A28&n; * and are translated to the start of IO.  Note that all addresses are&n; * not shifted left!&n; */
DECL|macro|__PORT_PCIO
mdefine_line|#define __PORT_PCIO(x)&t;((x) &lt; (1&lt;&lt;28))
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t; (S3C2410_VA_ISA_WORD)
DECL|macro|PCIO_BASE_b
mdefine_line|#define PCIO_BASE_b&t; (S3C2410_VA_ISA_BYTE)
DECL|macro|PCIO_BASE_w
mdefine_line|#define PCIO_BASE_w&t; (S3C2410_VA_ISA_WORD)
DECL|macro|PCIO_BASE_l
mdefine_line|#define PCIO_BASE_l&t; (S3C2410_VA_ISA_WORD)
multiline_comment|/*&n; * Dynamic IO functions - let the compiler&n; * optimize the expressions&n; */
DECL|macro|DECLARE_DYN_OUT
mdefine_line|#define DECLARE_DYN_OUT(sz,fnsuffix,instr) &bslash;&n;static inline void __out##fnsuffix (unsigned int val, unsigned int port) &bslash;&n;{ &bslash;&n;&t;unsigned long temp;&t;&t;&t;&t;      &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;      &bslash;&n;&t;&quot;cmp&t;%2, #(1&lt;&lt;28)&bslash;n&bslash;t&quot;&t;&t;&t;      &bslash;&n;&t;&quot;mov&t;%0, %2&bslash;n&bslash;t&quot;&t;&t;&t;&t;      &bslash;&n;&t;&quot;addcc&t;%0, %0, %3&bslash;n&bslash;t&quot;&t;&t;&t;&t;      &bslash;&n;&t;&quot;str&quot; instr &quot; %1, [%0, #0 ]&t;@ out&quot; #fnsuffix      &bslash;&n;&t;: &quot;=&amp;r&quot; (temp)&t;&t;&t;&t;&t;      &bslash;&n;&t;: &quot;r&quot; (val), &quot;r&quot; (port), &quot;Ir&quot; (PCIO_BASE_##fnsuffix)  &bslash;&n;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|DECLARE_DYN_IN
mdefine_line|#define DECLARE_DYN_IN(sz,fnsuffix,instr)&t;&t;&t;&t;&bslash;&n;static inline unsigned sz __in##fnsuffix (unsigned int port)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long temp, value;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp&t;%2, #(1&lt;&lt;28)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%0, %2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;addcc&t;%0, %0, %3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr&quot; instr &quot;&t;%1, [%0, #0 ]&t;@ in&quot; #fnsuffix&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (temp), &quot;=r&quot; (value)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (port), &quot;Ir&quot; (PCIO_BASE_##fnsuffix)&t;&bslash;&n;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (unsigned sz)value;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|function|__ioaddr
r_static
r_inline
r_void
id|__iomem
op_star
id|__ioaddr
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|__PORT_PCIO
c_func
(paren
id|port
)paren
ques
c_cond
id|PCIO_BASE
op_plus
id|port
suffix:colon
id|port
)paren
suffix:semicolon
)brace
DECL|macro|DECLARE_IO
mdefine_line|#define DECLARE_IO(sz,fnsuffix,instr)&t;&bslash;&n;&t;DECLARE_DYN_IN(sz,fnsuffix,instr) &bslash;&n;&t;DECLARE_DYN_OUT(sz,fnsuffix,instr)
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
l_string|&quot;h&quot;
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
mdefine_line|#define __outbc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strb&t;%0, [%1, %2]&t;@ outbc&quot;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port)));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strb&t;%0, [%1, #0]&t;@ outbc&quot;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; ((port)));&t;&t;&bslash;&n;})
DECL|macro|__inbc
mdefine_line|#define __inbc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrb&t;%0, [%1, %2]&t;@ inbc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port)));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrb&t;%0, [%1, #0]&t;@ inbc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; ((port)));&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outwc
mdefine_line|#define __outwc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long v = value;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strh&t;%0, [%1, %2]&t;@ outwc&quot;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port)));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strh&t;%0, [%1, #0]&t;@ outwc&quot;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; ((port)));&t;&bslash;&n;})
DECL|macro|__inwc
mdefine_line|#define __inwc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrh&t;%0, [%1, %2]&t;@ inwc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port)));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrh&t;%0, [%1, #0]&t;@ inwc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; ((port)));&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outlc
mdefine_line|#define __outlc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long v = value;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&t;@ outlc&quot;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port)));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, #0]&t;@ outlc&quot;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; ((port)));&t;&t;&bslash;&n;})
DECL|macro|__inlc
mdefine_line|#define __inlc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&t;@ inlc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port)));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, #0]&t;@ inlc&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; ((port)));&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ioaddrc
mdefine_line|#define __ioaddrc(port)&t;((void __iomem *)(__PORT_PCIO(port) ? PCIO_BASE + (port) : (port)))
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;(__builtin_constant_p((p)) ? __inbc(p)&t;   : __inb(p))
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;(__builtin_constant_p((p)) ? __inwc(p)&t;   : __inw(p))
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;(__builtin_constant_p((p)) ? __inlc(p)&t;   : __inl(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;(__builtin_constant_p((p)) ? __outbc(v,p) : __outb(v,p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;(__builtin_constant_p((p)) ? __outwc(v,p) : __outw(v,p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;(__builtin_constant_p((p)) ? __outlc(v,p) : __outl(v,p))
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)&t;(__builtin_constant_p((p)) ? __ioaddr(p)  : __ioaddrc(p))
multiline_comment|/* the following macro is deprecated */
DECL|macro|ioaddr
mdefine_line|#define ioaddr(port)&t;&t;&t;__ioaddr((port))
DECL|macro|insb
mdefine_line|#define insb(p,d,l)&t;__raw_readsb(__ioaddr(p),d,l)
DECL|macro|insw
mdefine_line|#define insw(p,d,l)&t;__raw_readsw(__ioaddr(p),d,l)
DECL|macro|insl
mdefine_line|#define insl(p,d,l)&t;__raw_readsl(__ioaddr(p),d,l)
DECL|macro|outsb
mdefine_line|#define outsb(p,d,l)&t;__raw_writesb(__ioaddr(p),d,l)
DECL|macro|outsw
mdefine_line|#define outsw(p,d,l)&t;__raw_writesw(__ioaddr(p),d,l)
DECL|macro|outsl
mdefine_line|#define outsl(p,d,l)&t;__raw_writesl(__ioaddr(p),d,l)
multiline_comment|/*&n; * 1:1 mapping for ioremapped regions.&n; */
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(x)&t;(x)
macro_line|#endif
eof
