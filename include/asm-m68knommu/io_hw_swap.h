macro_line|#ifndef _M68K_IO_HW_SWAP_H
DECL|macro|_M68K_IO_HW_SWAP_H
mdefine_line|#define _M68K_IO_HW_SWAP_H
multiline_comment|/*&n; * swap functions are sometimes needed to interface little-endian hardware&n; */
DECL|function|_swapw
r_static
r_inline
r_int
r_int
id|_swapw
c_func
(paren
r_volatile
r_int
r_int
id|v
)paren
(brace
r_return
(paren
(paren
id|v
op_lshift
l_int|8
)paren
op_or
(paren
id|v
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
DECL|function|_swapl
r_static
r_inline
r_int
r_int
id|_swapl
c_func
(paren
r_volatile
r_int
r_int
id|v
)paren
(brace
r_return
(paren
(paren
id|v
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|v
op_amp
l_int|0xff00
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|v
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|8
)paren
op_or
(paren
id|v
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the m68k architecture, we just read/write the&n; * memory location directly.&n; */
multiline_comment|/* ++roman: The assignments to temp. vars avoid that gcc sometimes generates&n; * two accesses to memory, which may be undesireable for some devices.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) &bslash;&n;    ({ unsigned char __v = (*(volatile unsigned char *) (addr)); __v; })
DECL|macro|readw
mdefine_line|#define readw(addr) &bslash;&n;    ({ unsigned short __v = (*(volatile unsigned short *) (addr)); __v; })
DECL|macro|readl
mdefine_line|#define readl(addr) &bslash;&n;    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); __v; })
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) ((*(volatile unsigned short *) (addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) ((*(volatile unsigned int *) (addr)) = (b))
multiline_comment|/* There is no difference between I/O and memory on 68k, these are the same */
DECL|macro|inb
mdefine_line|#define inb(addr) &bslash;&n;    ({ unsigned char __v = (*(volatile unsigned char *) (addr)); __v; })
DECL|macro|inw
mdefine_line|#define inw(addr) &bslash;&n;    ({ unsigned short __v = (*(volatile unsigned short *) (addr)); &bslash;&n;       _swapw(__v); })
DECL|macro|inl
mdefine_line|#define inl(addr) &bslash;&n;    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); _swapl(__v); })
DECL|macro|outb
mdefine_line|#define outb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|outw
mdefine_line|#define outw(b,addr) ((*(volatile unsigned short *) (addr)) = (_swapw(b)))
DECL|macro|outl
mdefine_line|#define outl(b,addr) ((*(volatile unsigned int *) (addr)) = (_swapl(b)))
multiline_comment|/* FIXME: these need to be optimized.  Watch out for byte swapping, they&n; * are used mostly for Intel devices... */
DECL|macro|outsw
mdefine_line|#define outsw(addr,buf,len) &bslash;&n;    ({ unsigned short * __p = (unsigned short *)(buf); &bslash;&n;       unsigned short * __e = (unsigned short *)(__p) + (len); &bslash;&n;       while (__p &lt; __e) { &bslash;&n;&t;  *(volatile unsigned short *)(addr) = *__p++;&bslash;&n;       } &bslash;&n;     })
DECL|macro|insw
mdefine_line|#define insw(addr,buf,len) &bslash;&n;    ({ unsigned short * __p = (unsigned short *)(buf); &bslash;&n;       unsigned short * __e = (unsigned short *)(__p) + (len); &bslash;&n;       while (__p &lt; __e) { &bslash;&n;          *(__p++) = *(volatile unsigned short *)(addr); &bslash;&n;       } &bslash;&n;     })
DECL|function|get_user_byte_io
r_static
r_inline
r_int
r_char
id|get_user_byte_io
c_func
(paren
r_const
r_char
op_star
id|addr
)paren
(brace
r_register
r_int
r_char
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %1,%0&quot;
suffix:colon
l_string|&quot;=dm&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
DECL|macro|inb_p
mdefine_line|#define inb_p(addr) get_user_byte_io((char *)(addr))
DECL|function|put_user_byte_io
r_static
r_inline
r_void
id|put_user_byte_io
c_func
(paren
r_char
id|val
comma
r_char
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %0,%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;idm&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|outb_p
mdefine_line|#define outb_p(x,addr) put_user_byte_io((x),(char *)(addr))
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are trivial on the 1:1 Linux/i386 mapping (but if we ever&n; * make the kernel segment mapped at 0, we need to do translation&n; * on the i386 as well)&n; */
r_extern
r_int
r_int
id|mm_vtop
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mm_ptov
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
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
id|mm_vtop
c_func
(paren
(paren
r_int
r_int
)paren
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
id|mm_ptov
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IO bus memory addresses are also 1:1 with the physical address&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
macro_line|#endif /* _M68K_IO_HW_SWAP_H */
eof
