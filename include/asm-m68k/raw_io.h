multiline_comment|/*&n; * linux/include/asm-m68k/raw_io.h &n; *&n; * 10/20/00 RZ: - created from bits of io.h and ide.h to cleanup namespace&n; *&n; */
macro_line|#ifndef _RAW_IO_H
DECL|macro|_RAW_IO_H
mdefine_line|#define _RAW_IO_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* Values for nocacheflag and cmode */
DECL|macro|IOMAP_FULL_CACHING
mdefine_line|#define IOMAP_FULL_CACHING&t;&t;0
DECL|macro|IOMAP_NOCACHE_SER
mdefine_line|#define IOMAP_NOCACHE_SER&t;&t;1
DECL|macro|IOMAP_NOCACHE_NONSER
mdefine_line|#define IOMAP_NOCACHE_NONSER&t;&t;2
DECL|macro|IOMAP_WRITETHROUGH
mdefine_line|#define IOMAP_WRITETHROUGH&t;&t;3
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
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
comma
r_int
id|cacheflag
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
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* ++roman: The assignments to temp. vars avoid that gcc sometimes generates&n; * two accesses to memory, which may be undesirable for some devices.&n; */
DECL|macro|in_8
mdefine_line|#define in_8(addr) &bslash;&n;    ({ unsigned char __v = (*(volatile unsigned char *) (addr)); __v; })
DECL|macro|in_be16
mdefine_line|#define in_be16(addr) &bslash;&n;    ({ unsigned short __v = (*(volatile unsigned short *) (addr)); __v; })
DECL|macro|in_be32
mdefine_line|#define in_be32(addr) &bslash;&n;    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); __v; })
DECL|macro|in_le16
mdefine_line|#define in_le16(addr) &bslash;&n;    ({ unsigned short __v = le16_to_cpu(*(volatile unsigned short *) (addr)); __v; })
DECL|macro|in_le32
mdefine_line|#define in_le32(addr) &bslash;&n;    ({ unsigned int __v = le32_to_cpu(*(volatile unsigned int *) (addr)); __v; })
DECL|macro|out_8
mdefine_line|#define out_8(addr,b) (void)((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|out_be16
mdefine_line|#define out_be16(addr,w) (void)((*(volatile unsigned short *) (addr)) = (w))
DECL|macro|out_be32
mdefine_line|#define out_be32(addr,l) (void)((*(volatile unsigned int *) (addr)) = (l))
DECL|macro|out_le16
mdefine_line|#define out_le16(addr,w) (void)((*(volatile unsigned short *) (addr)) = cpu_to_le16(w))
DECL|macro|out_le32
mdefine_line|#define out_le32(addr,l) (void)((*(volatile unsigned int *) (addr)) = cpu_to_le32(l))
DECL|macro|raw_inb
mdefine_line|#define raw_inb in_8
DECL|macro|raw_inw
mdefine_line|#define raw_inw in_be16
DECL|macro|raw_inl
mdefine_line|#define raw_inl in_be32
DECL|macro|raw_outb
mdefine_line|#define raw_outb(val,port) out_8((port),(val))
DECL|macro|raw_outw
mdefine_line|#define raw_outw(val,port) out_be16((port),(val))
DECL|macro|raw_outl
mdefine_line|#define raw_outl(val,port) out_be32((port),(val))
DECL|function|raw_insb
r_static
r_inline
r_void
id|raw_insb
c_func
(paren
r_volatile
r_int
r_char
op_star
id|port
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
op_star
id|buf
op_increment
op_assign
id|in_8
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|raw_outsb
r_static
r_inline
r_void
id|raw_outsb
c_func
(paren
r_volatile
r_int
r_char
op_star
id|port
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
id|out_8
c_func
(paren
id|port
comma
op_star
id|buf
op_increment
)paren
suffix:semicolon
)brace
DECL|function|raw_insw
r_static
r_inline
r_void
id|raw_insw
c_func
(paren
r_volatile
r_int
r_int
op_star
id|port
comma
r_int
r_int
op_star
id|buf
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_amp
l_int|15
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_amp
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: movew %2@,%0@+; dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_rshift
l_int|4
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_rshift
l_int|4
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;movew %2@,%0@+; &quot;
l_string|&quot;dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|raw_outsw
r_static
r_inline
r_void
id|raw_outsw
c_func
(paren
r_volatile
r_int
r_int
op_star
id|port
comma
r_const
r_int
r_int
op_star
id|buf
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_amp
l_int|15
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_amp
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: movew %0@+,%2@; dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_rshift
l_int|4
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_rshift
l_int|4
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;movew %0@+,%2@; &quot;
l_string|&quot;dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|raw_insl
r_static
r_inline
r_void
id|raw_insl
c_func
(paren
r_volatile
r_int
r_int
op_star
id|port
comma
r_int
r_int
op_star
id|buf
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_amp
l_int|15
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_amp
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: movel %2@,%0@+; dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_rshift
l_int|4
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_rshift
l_int|4
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;movel %2@,%0@+; &quot;
l_string|&quot;dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|raw_outsl
r_static
r_inline
r_void
id|raw_outsl
c_func
(paren
r_volatile
r_int
r_int
op_star
id|port
comma
r_const
r_int
r_int
op_star
id|buf
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_amp
l_int|15
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_amp
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: movel %0@+,%2@; dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_rshift
l_int|4
)paren
(brace
id|tmp
op_assign
(paren
id|nr
op_rshift
l_int|4
)paren
op_minus
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;movel %0@+,%2@; &quot;
l_string|&quot;dbra %1,1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|buf
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
id|buf
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|raw_insw_swapw
r_static
r_inline
r_void
id|raw_insw_swapw
c_func
(paren
r_volatile
r_int
r_int
op_star
id|port
comma
r_int
r_int
op_star
id|buf
comma
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
(paren
id|nr
)paren
op_mod
l_int|8
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;tmovel %0,%/a0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,%/a1&bslash;n&bslash;t&quot;
l_string|&quot;movel %2,%/d6&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%/d6&bslash;n&quot;
l_string|&quot;1:&bslash;tmovew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %/d6,1b&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|port
)paren
comma
l_string|&quot;g&quot;
(paren
id|buf
)paren
comma
l_string|&quot;g&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;d6&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel %0,%/a0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,%/a1&bslash;n&bslash;t&quot;
l_string|&quot;movel %2,%/d6&bslash;n&bslash;t&quot;
l_string|&quot;lsrl  #3,%/d6&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%/d6&bslash;n&quot;
l_string|&quot;1:&bslash;tmovew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a0@,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a1@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %/d6,1b&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|port
)paren
comma
l_string|&quot;g&quot;
(paren
id|buf
)paren
comma
l_string|&quot;g&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;d6&quot;
)paren
suffix:semicolon
)brace
DECL|function|raw_outsw_swapw
r_static
r_inline
r_void
id|raw_outsw_swapw
c_func
(paren
r_volatile
r_int
r_int
op_star
id|port
comma
r_const
r_int
r_int
op_star
id|buf
comma
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
(paren
id|nr
)paren
op_mod
l_int|8
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel %0,%/a0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,%/a1&bslash;n&bslash;t&quot;
l_string|&quot;movel %2,%/d6&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%/d6&bslash;n&quot;
l_string|&quot;1:&bslash;tmovew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;dbra %/d6,1b&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|port
)paren
comma
l_string|&quot;g&quot;
(paren
id|buf
)paren
comma
l_string|&quot;g&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;d6&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel %0,%/a0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,%/a1&bslash;n&bslash;t&quot;
l_string|&quot;movel %2,%/d6&bslash;n&bslash;t&quot;
l_string|&quot;lsrl  #3,%/d6&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%/d6&bslash;n&quot;
l_string|&quot;1:&bslash;tmovew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;movew %/a1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;rolw  #8,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movew %/d0,%/a0@&bslash;n&bslash;t&quot;
l_string|&quot;dbra %/d6,1b&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|port
)paren
comma
l_string|&quot;g&quot;
(paren
id|buf
)paren
comma
l_string|&quot;g&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;d6&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _RAW_IO_H */
eof
