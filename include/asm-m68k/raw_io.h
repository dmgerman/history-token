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
DECL|macro|raw_insb
mdefine_line|#define raw_insb(port, buf, len) ({&t;   &bslash;&n;&t;volatile unsigned char *_port = (volatile unsigned char *) (port);   &bslash;&n;        unsigned char *_buf =(unsigned char *)(buf);&t;   &bslash;&n;        unsigned int  _i,_len=(unsigned int)(len);&t;   &bslash;&n;        for(_i=0; _i&lt; _len; _i++)  &bslash;&n;           *_buf++=in_8(_port);      &bslash;&n;  })
DECL|macro|raw_outsb
mdefine_line|#define raw_outsb(port, buf, len) ({&t;   &bslash;&n;&t;volatile unsigned char *_port = (volatile unsigned char *) (port);   &bslash;&n;        unsigned char *_buf =(unsigned char *)(buf);&t;   &bslash;&n;        unsigned int  _i,_len=(unsigned int)(len);&t;   &bslash;&n;        for( _i=0; _i&lt; _len; _i++)  &bslash;&n;           out_8(_port,*_buf++);      &bslash;&n;  })
DECL|macro|raw_insw
mdefine_line|#define raw_insw(port, buf, nr) ({&t;&t;&t;&t;&bslash;&n;&t;volatile unsigned char *_port = (volatile unsigned char *) (port);&t;&bslash;&n;&t;unsigned char *_buf = (unsigned char *)(buf);&t;&t;&t;&bslash;&n;&t;unsigned int _nr = (unsigned int)(nr);&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _tmp;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_nr &amp; 15) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = (_nr &amp; 15) - 1;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1: movew %2@,%0@+; dbra %1,1b&quot;&t;&bslash;&n;&t;&t;&t;: &quot;=a&quot; (_buf), &quot;=d&quot; (_tmp)&t;&bslash;&n;&t;&t;&t;: &quot;a&quot; (_port), &quot;0&quot; (_buf),&t;&bslash;&n;&t;&t;&t;  &quot;1&quot; (_tmp));&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_nr &gt;&gt; 4) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = (_nr &gt;&gt; 4) - 1;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1: &quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %2@,%0@+; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;dbra %1,1b&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=a&quot; (_buf), &quot;=d&quot; (_tmp)&t;&bslash;&n;&t;&t;&t;: &quot;a&quot; (_port), &quot;0&quot; (_buf),&t;&bslash;&n;&t;&t;&t;  &quot;1&quot; (_tmp));&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|raw_outsw
mdefine_line|#define raw_outsw(port, buf, nr) ({&t;&t;&t;&t;&bslash;&n;&t;volatile unsigned char *_port = (volatile unsigned char *) (port);&t;&bslash;&n;&t;unsigned char *_buf = (unsigned char *)(buf);&t;&t;&t;&bslash;&n;&t;unsigned int _nr = (unsigned int)(nr);&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _tmp;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_nr &amp; 15) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = (_nr &amp; 15) - 1;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1: movew %0@+,%2@; dbra %1,1b&quot;&t;&bslash;&n;&t;&t;&t;: &quot;=a&quot; (_buf), &quot;=d&quot; (_tmp)&t;&bslash;&n;&t;&t;&t;: &quot;a&quot; (_port), &quot;0&quot; (_buf),&t;&bslash;&n;&t;&t;&t;  &quot;1&quot; (_tmp));&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_nr &gt;&gt; 4) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = (_nr &gt;&gt; 4) - 1;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1: &quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;movew %0@+,%2@; &quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;dbra %1,1b&quot;&t;   &t;&t;&bslash;&n;&t;&t;&t;: &quot;=a&quot; (_buf), &quot;=d&quot; (_tmp)&t;&bslash;&n;&t;&t;&t;: &quot;a&quot; (_port), &quot;0&quot; (_buf),&t;&bslash;&n;&t;&t;&t;  &quot;1&quot; (_tmp));&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|raw_insw_swapw
mdefine_line|#define raw_insw_swapw(port, buf, nr) &bslash;&n;({  if ((nr) % 8) &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; dbra %/d6,1b&quot;  &bslash;&n;&t;&t;:               &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;d0&quot;, &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;); &bslash;&n;    else &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; lsrl  #3,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a1@+; &bslash;&n;&t;&t; dbra %/d6,1b&quot;  &bslash;&n;                :               &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;d0&quot;, &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;); &bslash;&n;})
DECL|macro|raw_outsw_swapw
mdefine_line|#define raw_outsw_swapw(port, buf, nr) &bslash;&n;({  if ((nr) % 8) &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; dbra %/d6,1b&quot;  &bslash;&n;                :               &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;d0&quot;, &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;); &bslash;&n;    else &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; lsrl  #3,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/d0; &bslash;&n;&t;&t; rolw  #8,%/d0; &bslash;&n;&t;&t; movew %/d0,%/a0@; &bslash;&n;&t;&t; dbra %/d6,1b&quot;  &bslash;&n;                :               &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;d0&quot;, &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;); &bslash;&n;})
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _RAW_IO_H */
eof
