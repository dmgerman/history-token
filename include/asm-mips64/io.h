multiline_comment|/* $Id: io.h,v 1.9 2000/02/04 07:40:53 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 Waldorf GmbH&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifdef CONFIG_SGI_IP22
macro_line|#include &lt;asm/sgi/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP27
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#endif
r_extern
r_int
r_int
id|bus_to_baddr
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/*&n; * Slowdown I/O port space accesses for antique hardware.&n; */
DECL|macro|CONF_SLOWDOWN_IO
macro_line|#undef CONF_SLOWDOWN_IO
multiline_comment|/*&n; * On MIPS, we have the whole physical address space mapped at all&n; * times, so &quot;ioremap()&quot; and &quot;iounmap()&quot; do not need to do anything.&n; *&n; * We cheat a bit and always return uncachable areas until we&squot;ve fixed&n; * the drivers to handle caching properly.&n; */
r_extern
r_inline
r_void
op_star
DECL|function|ioremap
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
(paren
r_void
op_star
)paren
(paren
id|IO_SPACE_BASE
op_or
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/* This one maps high address device memory and turns off caching for that&n; *  area.  It&squot;s useful if some control registers are in such an area and write&n; * combining or read caching is not desirable.&n; */
r_extern
r_inline
r_void
op_star
DECL|function|ioremap_nocache
id|ioremap_nocache
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
(paren
r_void
op_star
)paren
(paren
id|IO_SPACE_BASE
op_or
id|offset
)paren
suffix:semicolon
)brace
DECL|function|iounmap
r_extern
r_inline
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
)brace
multiline_comment|/*&n; * This assumes sane hardware.  The Origin is.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;(*(volatile unsigned char *) (addr))
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;(*(volatile unsigned short *) (addr))
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;(*(volatile unsigned int *) (addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr)&t;&t;(*(volatile unsigned char *) (addr) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr)&t;&t;(*(volatile unsigned short *) (addr) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr)&t;&t;(*(volatile unsigned int *) (addr) = (b))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *) a,(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
multiline_comment|/* The ISA versions are supplied by system specific code */
multiline_comment|/*&n; * On MIPS I/O ports are memory mapped, so we access them using normal&n; * load/store instructions. mips_io_port_base is the virtual address to&n; * which all ports are being mapped.  For sake of efficiency some code&n; * assumes that this is an address that can be loaded with a single lui&n; * instruction, so the lower 16 bits must be zero.  Should be true on&n; * on any sane architecture; generic code does not use this assumption.&n; */
r_extern
r_int
r_int
id|mips_io_port_base
suffix:semicolon
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
(paren
r_int
r_int
)paren
id|address
op_minus
id|PAGE_OFFSET
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
(paren
id|address
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is is mapped&n; * for the processor.  This implies the assumption that there is only&n; * one of these busses.&n; */
r_extern
r_int
r_int
id|isa_slot_offset
suffix:semicolon
multiline_comment|/*&n; * We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and&n; * just copy it. The net code will then do the checksum later.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused) memcpy_fromio((skb)-&gt;data,(src),(len))
r_static
r_inline
r_int
DECL|function|check_signature
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
multiline_comment|/*&n; * Talk about misusing macros..&n; */
DECL|macro|__OUT1
mdefine_line|#define __OUT1(s) &bslash;&n;extern inline void __out##s(unsigned int value, unsigned long port) {
DECL|macro|__OUT2
mdefine_line|#define __OUT2(m) &bslash;&n;__asm__ __volatile__ (&quot;s&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__OUT
mdefine_line|#define __OUT(m,s) &bslash;&n;__OUT1(s) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); } &bslash;&n;__OUT1(s##c) __OUT2(m) : : &quot;r&quot; (value), &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); } &bslash;&n;__OUT1(s##_p) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); &bslash;&n;&t;SLOW_DOWN_IO; } &bslash;&n;__OUT1(s##c_p) __OUT2(m) : : &quot;r&quot; (value), &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); &bslash;&n;&t;SLOW_DOWN_IO; }
DECL|macro|__IN1
mdefine_line|#define __IN1(t,s) &bslash;&n;extern __inline__ t __in##s(unsigned long port) { t _v;
multiline_comment|/*&n; * Required nops will be inserted by the assembler&n; */
DECL|macro|__IN2
mdefine_line|#define __IN2(m) &bslash;&n;__asm__ __volatile__ (&quot;l&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__IN
mdefine_line|#define __IN(t,m,s) &bslash;&n;__IN1(t,s) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); return _v; } &bslash;&n;__IN1(t,s##c) __IN2(m) : &quot;=r&quot; (_v) : &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); return _v; } &bslash;&n;__IN1(t,s##_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port)); SLOW_DOWN_IO; return _v; } &bslash;&n;__IN1(t,s##c_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base)); SLOW_DOWN_IO; return _v; }
DECL|macro|__INS1
mdefine_line|#define __INS1(s) &bslash;&n;extern inline void __ins##s(unsigned long port, void * addr, unsigned long count) {
DECL|macro|__INS2
mdefine_line|#define __INS2(m) &bslash;&n;if (count) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tl&quot; #m &quot;&bslash;t$1, %4(%5)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;dsubu&bslash;t%1, 1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;s&quot; #m &quot;&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bnez&bslash;t%1, 1b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;daddiu&bslash;t%0, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot;
DECL|macro|__INS
mdefine_line|#define __INS(m,s,i) &bslash;&n;__INS1(s) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &quot;r&quot; (mips_io_port_base+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__INS1(s##c) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;ir&quot; (port), &quot;r&quot; (mips_io_port_base), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
DECL|macro|__OUTS1
mdefine_line|#define __OUTS1(s) &bslash;&n;extern inline void __outs##s(unsigned long port, const void * addr, unsigned long count) {
DECL|macro|__OUTS2
mdefine_line|#define __OUTS2(m) &bslash;&n;if (count) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tl&quot; #m &quot;&bslash;t$1, (%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;dsubu&bslash;t%1, 1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;s&quot; #m &quot;&bslash;t$1, %4(%5)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bnez&bslash;t%1, 1b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;daddiu&bslash;t%0, %6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot;
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
)paren
id|__OUT
c_func
(paren
id|b
comma
id|b
)paren
id|__OUT
c_func
(paren
id|h
comma
id|w
)paren
id|__OUT
c_func
(paren
id|w
comma
id|l
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
mdefine_line|#define outb(val,port) &bslash;&n;((__builtin_constant_p((port)^(3)) &amp;&amp; ((port)^(3)) &lt; 32768) ? &bslash;&n;&t;__outbc((val),(port)^(3)) : &bslash;&n;&t;__outb((val),(port)^(3)))
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;((__builtin_constant_p((port)^(3)) &amp;&amp; ((port)^(3)) &lt; 32768) ? &bslash;&n;&t;__inbc((port)^(3)) : &bslash;&n;&t;__inb((port)^(3)))
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port) &bslash;&n;((__builtin_constant_p((port)^(3)) &amp;&amp; ((port)^(3)) &lt; 32768) ? &bslash;&n;&t;__outbc_p((val),(port)^(3)) : &bslash;&n;&t;__outb_p((val),(port)^(3)))
DECL|macro|inb_p
mdefine_line|#define inb_p(port) &bslash;&n;((__builtin_constant_p((port)^(3)) &amp;&amp; ((port)^(3)) &lt; 32768) ? &bslash;&n;&t;__inbc_p((port)^(3)) : &bslash;&n;&t;__inb_p((port)^(3)))
DECL|macro|outw
mdefine_line|#define outw(val,port) &bslash;&n;((__builtin_constant_p(((port)^(2))) &amp;&amp; ((port)^(2)) &lt; 32768) ? &bslash;&n;&t;__outwc((val),((port)^(2))) : &bslash;&n;&t;__outw((val),((port)^(2))))
DECL|macro|inw
mdefine_line|#define inw(port) &bslash;&n;((__builtin_constant_p(((port)^(2))) &amp;&amp; ((port)^(2)) &lt; 32768) ? &bslash;&n;&t;__inwc((port)^(2)) : &bslash;&n;&t;__inw((port)^(2)))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port) &bslash;&n;((__builtin_constant_p((port)^(2)) &amp;&amp; ((port)^(2)) &lt; 32768) ? &bslash;&n;&t;__outwc_p((val),(port)^(2)) : &bslash;&n;&t;__outw_p((val),(port)^(2)))
DECL|macro|inw_p
mdefine_line|#define inw_p(port) &bslash;&n;((__builtin_constant_p((port)^(2)) &amp;&amp; ((port)^(2)) &lt; 32768) ? &bslash;&n;&t;__inwc_p((port)^(2)) : &bslash;&n;&t;__inw_p((port)^(2)))
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
multiline_comment|/*&n; * The caches on some architectures aren&squot;t dma-coherent and have need to&n; * handle this in software.  There are three types of operations that&n; * can be applied to dma buffers.&n; *&n; *  - dma_cache_wback_inv(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_wback(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_inv(start, size) invalidates the affected parts of the&n; *    caches.  Dirty lines of the caches may be written back or simply&n; *    be discarded.  This operation is necessary before dma operations&n; *    to the memory.&n; */
macro_line|#ifdef CONFIG_COHERENT_IO
multiline_comment|/* This is for example for IP27.  */
DECL|function|dma_cache_wback_inv
r_extern
r_inline
r_void
id|dma_cache_wback_inv
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
)brace
DECL|function|dma_cache_wback
r_extern
r_inline
r_void
id|dma_cache_wback
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
)brace
DECL|function|dma_cache_inv
r_extern
r_inline
r_void
id|dma_cache_inv
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
)brace
macro_line|#else
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
mdefine_line|#define dma_cache_wback_inv(start,size)&t;_dma_cache_wback_inv(start,size)
mdefine_line|#define dma_cache_wback(start,size)&t;_dma_cache_wback(start,size)
mdefine_line|#define dma_cache_inv(start,size)&t;_dma_cache_inv(start,size)
macro_line|#endif
macro_line|#endif /* _ASM_IO_H */
eof
