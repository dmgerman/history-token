multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 Waldorf GmbH&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 FSMLabs, Inc.&n; */
macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * Slowdown I/O port space accesses for antique hardware.&n; */
DECL|macro|CONF_SLOWDOWN_IO
macro_line|#undef CONF_SLOWDOWN_IO
multiline_comment|/*&n; * Sane hardware offers swapping of I/O space accesses in hardware; less&n; * sane hardware forces software to fiddle with this ...&n; */
macro_line|#if defined(CONFIG_SWAP_IO_SPACE) &amp;&amp; defined(__MIPSEB__)
DECL|macro|__ioswab8
mdefine_line|#define __ioswab8(x) (x)
DECL|macro|__ioswab16
mdefine_line|#define __ioswab16(x) swab16(x)
DECL|macro|__ioswab32
mdefine_line|#define __ioswab32(x) swab32(x)
macro_line|#else
DECL|macro|__ioswab8
mdefine_line|#define __ioswab8(x) (x)
DECL|macro|__ioswab16
mdefine_line|#define __ioswab16(x) (x)
DECL|macro|__ioswab32
mdefine_line|#define __ioswab32(x) (x)
macro_line|#endif
multiline_comment|/*&n; * This file contains the definitions for the MIPS counterpart of the&n; * x86 in/out instructions. This heap of macros and C results in much&n; * better code than the approach of doing it in plain C.  The macros&n; * result in code that is to fast for certain hardware.  On the other&n; * side the performance of the string functions should be improved for&n; * sake of certain devices like EIDE disks that do highspeed polled I/O.&n; *&n; *   Ralf&n; *&n; * This file contains the definitions for the x86 IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated&n; * to (a) handle it all in a way that makes gcc able to optimize it&n; * as well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; */
multiline_comment|/*&n; * On MIPS I/O ports are memory mapped, so we access them using normal&n; * load/store instructions. mips_io_port_base is the virtual address to&n; * which all ports are being mapped.  For sake of efficiency some code&n; * assumes that this is an address that can be loaded with a single lui&n; * instruction, so the lower 16 bits must be zero.  Should be true on&n; * on any sane architecture; generic code does not use this assumption.&n; */
r_extern
r_int
r_int
id|mips_io_port_base
suffix:semicolon
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; *&n; */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;sb&bslash;t$0,0x80(%0)&quot; &bslash;&n;&t;&t;: : &quot;r&quot; (mips_io_port_base));
macro_line|#ifdef CONF_SLOWDOWN_IO
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are trivial on the 1:1 Linux/MIPS mapping&n; */
DECL|function|virt_to_phys
r_extern
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|PHYSADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_extern
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|KSEG0ADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IO bus memory addresses are also 1:1 with the physical address&n; */
DECL|function|virt_to_bus
r_extern
r_inline
r_int
r_int
id|virt_to_bus
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|PHYSADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|bus_to_virt
r_extern
r_inline
r_void
op_star
id|bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|KSEG0ADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is mapped&n; * for the processor.&n; */
r_extern
r_int
r_int
id|isa_slot_offset
suffix:semicolon
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|function|ioremap
r_extern
r_inline
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|offset
comma
id|size
comma
id|_CACHE_UNCACHED
)paren
suffix:semicolon
)brace
DECL|function|ioremap_nocache
r_extern
r_inline
r_void
op_star
id|ioremap_nocache
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|offset
comma
id|size
comma
id|_CACHE_UNCACHED
)paren
suffix:semicolon
)brace
r_extern
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * XXX We need system specific versions of these to handle EISA address bits&n; * 24-31 on SNI.&n; * XXX more SNI hacks.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *)(addr))
DECL|macro|readw
mdefine_line|#define readw(addr) __ioswab16((*(volatile unsigned short *)(addr)))
DECL|macro|readl
mdefine_line|#define readl(addr) __ioswab32((*(volatile unsigned int *)(addr)))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb readb
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw readw
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl readl
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) (*(volatile unsigned char *)(addr)) = (b)
DECL|macro|writew
mdefine_line|#define writew(b,addr) (*(volatile unsigned short *)(addr)) = (__ioswab16(b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) (*(volatile unsigned int *)(addr)) = (__ioswab32(b))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew writew
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel writel
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
multiline_comment|/* END SNI HACKS ... */
multiline_comment|/*&n; * ISA space is &squot;always mapped&squot; on currently supported MIPS systems, no need&n; * to explicitly ioremap() it. The fact that the ISA IO space is mapped&n; * to PAGE_OFFSET is pure coincidence - it does not mean ISA values&n; * are physical addresses. The following constant pointer can be&n; * used as the IO-area pointer (it can be iounmapped as well, so the&n; * analogy with PCI is quite large):&n; */
DECL|macro|__ISA_IO_base
mdefine_line|#define __ISA_IO_base ((char *)(PAGE_OFFSET))
DECL|macro|isa_readb
mdefine_line|#define isa_readb(a) readb(a)
DECL|macro|isa_readw
mdefine_line|#define isa_readw(a) readw(a)
DECL|macro|isa_readl
mdefine_line|#define isa_readl(a) readl(a)
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(b,a) writeb(b,a)
DECL|macro|isa_writew
mdefine_line|#define isa_writew(w,a) writew(w,a)
DECL|macro|isa_writel
mdefine_line|#define isa_writel(l,a) writel(l,a)
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c)     memset_io((a),(b),(c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c) memcpy_fromio((a),(b),(c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c)   memcpy_toio((a),(b),(c))
multiline_comment|/*&n; * We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and&n; * just copy it. The net code will then do the checksum later.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused) memcpy_fromio((skb)-&gt;data,(src),(len))
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(a,b,c,d) eth_copy_and_sum((a),(b),(c),(d))
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_int
r_int
id|io_addr
comma
r_const
r_int
r_char
op_star
id|signature
comma
r_int
id|length
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|io_addr
)paren
op_ne
op_star
id|signature
)paren
r_goto
id|out
suffix:semicolon
id|io_addr
op_increment
suffix:semicolon
id|signature
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|isa_check_signature
mdefine_line|#define isa_check_signature(io, s, l) check_signature(i,s,l)
multiline_comment|/*&n; * Talk about misusing macros..&n; */
DECL|macro|__OUT1
mdefine_line|#define __OUT1(s) &bslash;&n;extern inline void __out##s(unsigned int value, unsigned int port) {
DECL|macro|__OUT2
mdefine_line|#define __OUT2(m) &bslash;&n;__asm__ __volatile__ (&quot;s&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__OUT
mdefine_line|#define __OUT(m,s,w) &bslash;&n;__OUT1(s) __OUT2(m) : : &quot;r&quot; (__ioswab##w(value)), &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); } &bslash;&n;__OUT1(s##c) __OUT2(m) : : &quot;r&quot; (__ioswab##w(value)), &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); } &bslash;&n;__OUT1(s##_p) __OUT2(m) : : &quot;r&quot; (__ioswab##w(value)), &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); &bslash;&n;&t;SLOW_DOWN_IO; } &bslash;&n;__OUT1(s##c_p) __OUT2(m) : : &quot;r&quot; (__ioswab##w(value)), &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); &bslash;&n;&t;SLOW_DOWN_IO; }
DECL|macro|__IN1
mdefine_line|#define __IN1(t,s) &bslash;&n;extern __inline__ t __in##s(unsigned int port) { t _v;
multiline_comment|/*&n; * Required nops will be inserted by the assembler&n; */
DECL|macro|__IN2
mdefine_line|#define __IN2(m) &bslash;&n;__asm__ __volatile__ (&quot;l&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__IN
mdefine_line|#define __IN(t,m,s,w) &bslash;&n;__IN1(t,s) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); return __ioswab##w(_v); } &bslash;&n;__IN1(t,s##c) __IN2(m) : &quot;=r&quot; (_v) : &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); return __ioswab##w(_v); } &bslash;&n;__IN1(t,s##_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); SLOW_DOWN_IO; return __ioswab##w(_v); } &bslash;&n;__IN1(t,s##c_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); SLOW_DOWN_IO; return __ioswab##w(_v); }
DECL|macro|__INS1
mdefine_line|#define __INS1(s) &bslash;&n;extern inline void __ins##s(unsigned int port, void * addr, unsigned long count) {
DECL|macro|__INS2
mdefine_line|#define __INS2(m) &bslash;&n;if (count) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tl&quot; #m &quot;&bslash;t$1,%4(%5)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;s&quot; #m &quot;&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t%0,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot;
DECL|macro|__INS
mdefine_line|#define __INS(m,s,i) &bslash;&n;__INS1(s) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &bslash;&n;&t;  &quot;r&quot; (mips_io_port_base+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__INS1(s##c) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;ir&quot; (port), &bslash;&n;&t;  &quot;r&quot; (mips_io_port_base), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
DECL|macro|__OUTS1
mdefine_line|#define __OUTS1(s) &bslash;&n;extern inline void __outs##s(unsigned int port, const void * addr, unsigned long count) {
DECL|macro|__OUTS2
mdefine_line|#define __OUTS2(m) &bslash;&n;if (count) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;        &quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;        &quot;1:&bslash;tl&quot; #m &quot;&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;        &quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot; &bslash;&n;        &quot;s&quot; #m &quot;&bslash;t$1,%4(%5)&bslash;n&bslash;t&quot; &bslash;&n;        &quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;        &quot;addiu&bslash;t%0,%6&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;treorder&quot;
DECL|macro|__OUTS
mdefine_line|#define __OUTS(m,s,i) &bslash;&n;__OUTS1(s) __OUTS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__OUTS1(s##c) __OUTS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
id|__IN
c_func
(paren
r_int
r_char
comma
id|b
comma
id|b
comma
l_int|8
)paren
id|__IN
c_func
(paren
r_int
r_int
comma
id|h
comma
id|w
comma
l_int|16
)paren
id|__IN
c_func
(paren
r_int
r_int
comma
id|w
comma
id|l
comma
l_int|32
)paren
id|__OUT
c_func
(paren
id|b
comma
id|b
comma
l_int|8
)paren
id|__OUT
c_func
(paren
id|h
comma
id|w
comma
l_int|16
)paren
id|__OUT
c_func
(paren
id|w
comma
id|l
comma
l_int|32
)paren
id|__INS
c_func
(paren
id|b
comma
id|b
comma
l_int|1
)paren
id|__INS
c_func
(paren
id|h
comma
id|w
comma
l_int|2
)paren
id|__INS
c_func
(paren
id|w
comma
id|l
comma
l_int|4
)paren
id|__OUTS
c_func
(paren
id|b
comma
id|b
comma
l_int|1
)paren
id|__OUTS
c_func
(paren
id|h
comma
id|w
comma
l_int|2
)paren
id|__OUTS
c_func
(paren
id|w
comma
id|l
comma
l_int|4
)paren
multiline_comment|/*&n; * Note that due to the way __builtin_constant_p() works, you&n; *  - can&squot;t use it inside an inline function (it will never be true)&n; *  - you don&squot;t have to worry about side effects within the __builtin..&n; */
DECL|macro|outb
mdefine_line|#define outb(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outbc((val),(port)) : &bslash;&n;&t;__outb((val),(port)))
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inbc(port) : &bslash;&n;&t;__inb(port))
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outbc_p((val),(port)) : &bslash;&n;&t;__outb_p((val),(port)))
DECL|macro|inb_p
mdefine_line|#define inb_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inbc_p(port) : &bslash;&n;&t;__inb_p(port))
DECL|macro|outw
mdefine_line|#define outw(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outwc((val),(port)) : &bslash;&n;&t;__outw((val),(port)))
DECL|macro|inw
mdefine_line|#define inw(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inwc(port) : &bslash;&n;&t;__inw(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outwc_p((val),(port)) : &bslash;&n;&t;__outw_p((val),(port)))
DECL|macro|inw_p
mdefine_line|#define inw_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inwc_p(port) : &bslash;&n;&t;__inw_p(port))
DECL|macro|outl
mdefine_line|#define outl(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outlc((val),(port)) : &bslash;&n;&t;__outl((val),(port)))
DECL|macro|inl
mdefine_line|#define inl(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inlc(port) : &bslash;&n;&t;__inl(port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outlc_p((val),(port)) : &bslash;&n;&t;__outl_p((val),(port)))
DECL|macro|inl_p
mdefine_line|#define inl_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inlc_p(port) : &bslash;&n;&t;__inl_p(port))
DECL|macro|outsb
mdefine_line|#define outsb(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outsbc((port),(addr),(count)) : &bslash;&n;&t;__outsb ((port),(addr),(count)))
DECL|macro|insb
mdefine_line|#define insb(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__insbc((port),(addr),(count)) : &bslash;&n;&t;__insb((port),(addr),(count)))
DECL|macro|outsw
mdefine_line|#define outsw(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outswc((port),(addr),(count)) : &bslash;&n;&t;__outsw ((port),(addr),(count)))
DECL|macro|insw
mdefine_line|#define insw(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inswc((port),(addr),(count)) : &bslash;&n;&t;__insw((port),(addr),(count)))
DECL|macro|outsl
mdefine_line|#define outsl(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outslc((port),(addr),(count)) : &bslash;&n;&t;__outsl ((port),(addr),(count)))
DECL|macro|insl
mdefine_line|#define insl(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inslc((port),(addr),(count)) : &bslash;&n;&t;__insl((port),(addr),(count)))
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/*&n; * The caches on some architectures aren&squot;t dma-coherent and have need to&n; * handle this in software.  There are three types of operations that&n; * can be applied to dma buffers.&n; *&n; *  - dma_cache_wback_inv(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_wback(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_inv(start, size) invalidates the affected parts of the&n; *    caches.  Dirty lines of the caches may be written back or simply&n; *    be discarded.  This operation is necessary before dma operations&n; *    to the memory.&n; */
r_extern
r_void
(paren
op_star
id|_dma_cache_wback_inv
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_dma_cache_wback
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_dma_cache_inv
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(start,size)&t;_dma_cache_wback_inv(start,size)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(start,size)&t;_dma_cache_wback(start,size)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(start,size)&t;_dma_cache_inv(start,size)
macro_line|#endif /* _ASM_IO_H */
eof
