macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
multiline_comment|/* USE_HPPA_IOREMAP IS THE MAGIC FLAG TO ENABLE OR DISABLE REAL IOREMAP() FUNCTIONALITY */
multiline_comment|/* FOR 712 or 715 MACHINES THIS SHOULD BE ENABLED, &n;   NEWER MACHINES STILL HAVE SOME ISSUES IN THE SCSI AND/OR NETWORK DRIVERS AND &n;   BECAUSE OF THAT I WILL LEAVE IT DISABLED FOR NOW &lt;deller@gmx.de&gt; */
multiline_comment|/* WHEN THOSE ISSUES ARE SOLVED, USE_HPPA_IOREMAP WILL GO AWAY */
DECL|macro|USE_HPPA_IOREMAP
mdefine_line|#define USE_HPPA_IOREMAP 0
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_int
r_int
id|parisc_vmerge_boundary
suffix:semicolon
r_extern
r_int
r_int
id|parisc_vmerge_max_size
suffix:semicolon
DECL|macro|BIO_VMERGE_BOUNDARY
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;parisc_vmerge_boundary
DECL|macro|BIO_VMERGE_MAX_SIZE
mdefine_line|#define BIO_VMERGE_MAX_SIZE&t;parisc_vmerge_max_size
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(a) ((unsigned long)__pa(a))
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(a) __va(a)
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/* Memory mapped IO */
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
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This one maps high address device memory and turns off caching for that area.&n; * it&squot;s useful if some control registers are in such an area and write combining&n; * or read caching is not desirable:&n; */
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
id|_PAGE_NO_CACHE
multiline_comment|/* _PAGE_PCD */
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
multiline_comment|/*&n; * __raw_ variants have no defined meaning.  on hppa, it means `i was&n; * too lazy to ioremap first&squot;.  kind of like isa_, except that there&squot;s&n; * no additional base address to add on.&n; */
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a) ___raw_readb((unsigned long)(a))
DECL|function|___raw_readb
r_extern
id|__inline__
r_int
r_char
id|___raw_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
r_char
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;rsm&t;2,%0&bslash;n&quot;
l_string|&quot;&t;ldbx&t;0(%2),%1&bslash;n&quot;
l_string|&quot;&t;mtsm&t;%0&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|flags
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a) ___raw_readw((unsigned long)(a))
DECL|function|___raw_readw
r_extern
id|__inline__
r_int
r_int
id|___raw_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;rsm&t;2,%0&bslash;n&quot;
l_string|&quot;&t;ldhx&t;0(%2),%1&bslash;n&quot;
l_string|&quot;&t;mtsm&t;%0&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|flags
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a) ___raw_readl((unsigned long)(a))
DECL|function|___raw_readl
r_extern
id|__inline__
r_int
r_int
id|___raw_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;ldwax&t;0(%1),%0&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a) ___raw_readq((unsigned long)(a))
DECL|function|___raw_readq
r_extern
id|__inline__
r_int
r_int
r_int
id|___raw_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
r_int
id|ret
suffix:semicolon
macro_line|#ifdef __LP64__
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;ldda&t;0(%1),%0&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* two reads may have side effects.. */
id|ret
op_assign
(paren
(paren
id|u64
)paren
id|__raw_readl
c_func
(paren
id|addr
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
id|ret
op_or_assign
id|__raw_readl
c_func
(paren
id|addr
op_plus
l_int|4
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(a,b) ___raw_writeb(a, (unsigned long)(b))
DECL|function|___raw_writeb
r_extern
id|__inline__
r_void
id|___raw_writeb
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|flags
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;rsm&t;2,%0&bslash;n&quot;
l_string|&quot;&t;stbs&t;%1,0(%2)&bslash;n&quot;
l_string|&quot;&t;mtsm&t;%0&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|flags
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(a,b) ___raw_writew(a, (unsigned long)(b))
DECL|function|___raw_writew
r_extern
id|__inline__
r_void
id|___raw_writew
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|flags
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;rsm&t;2,%0&bslash;n&quot;
l_string|&quot;&t;sths&t;%1,0(%2)&bslash;n&quot;
l_string|&quot;&t;mtsm&t;%0&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|flags
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(a,b) ___raw_writel(a, (unsigned long)(b))
DECL|function|___raw_writel
r_extern
id|__inline__
r_void
id|___raw_writel
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;stwas&t;%0,0(%1)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(a,b) ___raw_writeq(a, (unsigned long)(b))
DECL|function|___raw_writeq
r_extern
id|__inline__
r_void
id|___raw_writeq
c_func
(paren
r_int
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
macro_line|#ifdef __LP64__
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;stda&t;%0,0(%1)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* two writes may have side effects.. */
id|__raw_writel
c_func
(paren
id|val
op_rshift
l_int|32
comma
id|addr
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|addr
op_plus
l_int|4
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if USE_HPPA_IOREMAP
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) (addr))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) (addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) (addr))
DECL|macro|readq
mdefine_line|#define readq(addr) (*(volatile u64 *) (addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) (*(volatile unsigned char *) (addr) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) (*(volatile unsigned short *) (addr) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) (*(volatile unsigned int *) (addr) = (b))
DECL|macro|writeq
mdefine_line|#define writeq(b,addr) (*(volatile u64 *) (addr) = (b))
macro_line|#else /* !USE_HPPA_IOREMAP */
DECL|macro|readb
mdefine_line|#define readb(addr) __raw_readb(addr)
DECL|macro|readw
mdefine_line|#define readw(addr) le16_to_cpu(__raw_readw(addr))
DECL|macro|readl
mdefine_line|#define readl(addr) le32_to_cpu(__raw_readl(addr))
DECL|macro|readq
mdefine_line|#define readq(addr) le64_to_cpu(__raw_readq(addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) __raw_writeb(b,addr)
DECL|macro|writew
mdefine_line|#define writew(b,addr) __raw_writew(cpu_to_le16(b),addr)
DECL|macro|writel
mdefine_line|#define writel(b,addr) __raw_writel(cpu_to_le32(b),addr)
DECL|macro|writeq
mdefine_line|#define writeq(b,addr) __raw_writeq(cpu_to_le64(b),addr)
macro_line|#endif /* !USE_HPPA_IOREMAP */
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(addr) readb(addr)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(addr) readw(addr)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(addr) readl(addr)
DECL|macro|readq_relaxed
mdefine_line|#define readq_relaxed(addr) readq(addr)
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
r_extern
r_void
id|__memcpy_fromio
c_func
(paren
r_int
r_int
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
r_extern
r_void
id|__memcpy_toio
c_func
(paren
r_int
r_int
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
r_extern
r_void
id|__memset_io
c_func
(paren
r_int
r_int
id|dest
comma
r_char
id|fill
comma
r_int
id|count
)paren
suffix:semicolon
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c) __memcpy_fromio((unsigned long)(a), (unsigned long)(b), (c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)   __memcpy_toio((unsigned long)(a), (unsigned long)(b), (c))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)     __memset_io((unsigned long)(a), (b), (c))
multiline_comment|/* Support old drivers which don&squot;t ioremap.&n; * NB this interface is scheduled to disappear in 2.5&n; */
DECL|macro|EISA_BASE
mdefine_line|#define EISA_BASE 0xfffffffffc000000UL
DECL|macro|isa_readb
mdefine_line|#define isa_readb(a) readb(EISA_BASE | (a))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(a) readw(EISA_BASE | (a))
DECL|macro|isa_readl
mdefine_line|#define isa_readl(a) readl(EISA_BASE | (a))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(b,a) writeb((b), EISA_BASE | (a))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(b,a) writew((b), EISA_BASE | (a))
DECL|macro|isa_writel
mdefine_line|#define isa_writel(b,a) writel((b), EISA_BASE | (a))
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c) memset_io(EISA_BASE | (a), (b), (c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c) memcpy_fromio((a), EISA_BASE | (b), (c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c) memcpy_toio(EISA_BASE | (a), (b), (c))
multiline_comment|/* &n; * These functions support PA-RISC drivers which don&squot;t yet call ioremap().&n; * They will disappear once the last of these drivers is gone.&n; */
DECL|macro|gsc_readb
mdefine_line|#define gsc_readb(x) __raw_readb(x)
DECL|macro|gsc_readw
mdefine_line|#define gsc_readw(x) __raw_readw(x)
DECL|macro|gsc_readl
mdefine_line|#define gsc_readl(x) __raw_readl(x)
DECL|macro|gsc_writeb
mdefine_line|#define gsc_writeb(x, y) __raw_writeb(x, y)
DECL|macro|gsc_writew
mdefine_line|#define gsc_writew(x, y) __raw_writew(x, y)
DECL|macro|gsc_writel
mdefine_line|#define gsc_writel(x, y) __raw_writel(x, y)
multiline_comment|/*&n; * XXX - We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and &n; * just copy it. The net code will then do the checksum later. Presently &n; * only used by some shared memory 8390 Ethernet cards anyway.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused) &bslash;&n;  memcpy_fromio((skb)-&gt;data,(src),(len))
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(skb,src,len,unused) &bslash;&n;  isa_memcpy_fromio((skb)-&gt;data,(src),(len))
multiline_comment|/* Port-space IO */
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|inw_p
mdefine_line|#define inw_p inw
DECL|macro|inl_p
mdefine_line|#define inl_p inl
DECL|macro|outb_p
mdefine_line|#define outb_p outb
DECL|macro|outw_p
mdefine_line|#define outw_p outw
DECL|macro|outl_p
mdefine_line|#define outl_p outl
r_extern
r_int
r_char
id|eisa_in8
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|eisa_in16
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|eisa_in32
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|eisa_out8
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|eisa_out16
c_func
(paren
r_int
r_int
id|data
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|eisa_out32
c_func
(paren
r_int
r_int
id|data
comma
r_int
r_int
id|port
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PCI)
r_extern
r_int
r_char
id|inb
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|inw
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|inl
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
id|addr
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_EISA)
DECL|macro|inb
mdefine_line|#define inb eisa_in8
DECL|macro|inw
mdefine_line|#define inw eisa_in16
DECL|macro|inl
mdefine_line|#define inl eisa_in32
DECL|macro|outb
mdefine_line|#define outb eisa_out8
DECL|macro|outw
mdefine_line|#define outw eisa_out16
DECL|macro|outl
mdefine_line|#define outl eisa_out32
macro_line|#else
DECL|function|inb
r_static
r_inline
r_char
id|inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|inw
r_static
r_inline
r_int
id|inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|inl
r_static
r_inline
r_int
id|inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|macro|outb
mdefine_line|#define outb(x, y)&t;BUG()
DECL|macro|outw
mdefine_line|#define outw(x, y)&t;BUG()
DECL|macro|outl
mdefine_line|#define outl(x, y)&t;BUG()
macro_line|#endif
multiline_comment|/*&n; * String versions of in/out ops:&n; */
r_extern
r_void
id|insb
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insw
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insl
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsb
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsw
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsl
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* IO Port space is :      BBiiii   where BB is HBA number. */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0x00ffffff
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { flush_kernel_dcache_range(_start,_size); } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { flush_kernel_dcache_range(_start,_size); } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { flush_kernel_dcache_range(_start,_size); } while (0)
multiline_comment|/* PA machines have an MM I/O space from 0xf0000000-0xffffffff in 32&n; * bit mode and from 0xfffffffff0000000-0xfffffffffffffff in 64 bit&n; * mode (essentially just sign extending.  This macro takes in a 32&n; * bit I/O address (still with the leading f) and outputs the correct&n; * value for either 32 or 64 bit mode */
DECL|macro|F_EXTEND
mdefine_line|#define F_EXTEND(x) ((unsigned long)((x) | (0xffffffff00000000ULL)))
macro_line|#include &lt;asm-generic/iomap.h&gt;
macro_line|#endif
eof
