macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Copy data from IO memory space to &quot;real&quot; memory space.&n; * This needs to be optimized.&n; */
r_void
DECL|function|__ia64_memcpy_fromio
id|__ia64_memcpy_fromio
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|to
op_assign
id|readb
c_func
(paren
id|from
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|to
)paren
op_increment
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
)brace
DECL|variable|__ia64_memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_memcpy_fromio
)paren
suffix:semicolon
multiline_comment|/*&n; * Copy data from &quot;real&quot; memory space to IO memory space.&n; * This needs to be optimized.&n; */
r_void
DECL|function|__ia64_memcpy_toio
id|__ia64_memcpy_toio
(paren
r_int
r_int
id|to
comma
r_void
op_star
id|from
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|writeb
c_func
(paren
op_star
(paren
r_char
op_star
)paren
id|from
comma
id|to
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|from
)paren
op_increment
suffix:semicolon
id|to
op_increment
suffix:semicolon
)brace
)brace
DECL|variable|__ia64_memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_memcpy_toio
)paren
suffix:semicolon
multiline_comment|/*&n; * &quot;memset&quot; on IO memory space.&n; * This needs to be optimized.&n; */
r_void
DECL|function|__ia64_memset_c_io
id|__ia64_memset_c_io
(paren
r_int
r_int
id|dst
comma
r_int
r_int
id|c
comma
r_int
id|count
)paren
(brace
r_int
r_char
id|ch
op_assign
(paren
r_char
)paren
(paren
id|c
op_amp
l_int|0xff
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|writeb
c_func
(paren
id|ch
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
)brace
DECL|variable|__ia64_memset_c_io
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_memset_c_io
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_GENERIC
DECL|macro|__ia64_inb
macro_line|#undef __ia64_inb
DECL|macro|__ia64_inw
macro_line|#undef __ia64_inw
DECL|macro|__ia64_inl
macro_line|#undef __ia64_inl
DECL|macro|__ia64_outb
macro_line|#undef __ia64_outb
DECL|macro|__ia64_outw
macro_line|#undef __ia64_outw
DECL|macro|__ia64_outl
macro_line|#undef __ia64_outl
DECL|macro|__ia64_readb
macro_line|#undef __ia64_readb
DECL|macro|__ia64_readw
macro_line|#undef __ia64_readw
DECL|macro|__ia64_readl
macro_line|#undef __ia64_readl
DECL|macro|__ia64_readq
macro_line|#undef __ia64_readq
DECL|macro|__ia64_readb_relaxed
macro_line|#undef __ia64_readb_relaxed
DECL|macro|__ia64_readw_relaxed
macro_line|#undef __ia64_readw_relaxed
DECL|macro|__ia64_readl_relaxed
macro_line|#undef __ia64_readl_relaxed
DECL|macro|__ia64_readq_relaxed
macro_line|#undef __ia64_readq_relaxed
DECL|macro|__ia64_writeb
macro_line|#undef __ia64_writeb
DECL|macro|__ia64_writew
macro_line|#undef __ia64_writew
DECL|macro|__ia64_writel
macro_line|#undef __ia64_writel
DECL|macro|__ia64_writeq
macro_line|#undef __ia64_writeq
r_int
r_int
DECL|function|__ia64_inb
id|__ia64_inb
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|___ia64_inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_inw
id|__ia64_inw
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|___ia64_inw
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_inl
id|__ia64_inl
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|___ia64_inl
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_void
DECL|function|__ia64_outb
id|__ia64_outb
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|___ia64_outb
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
r_void
DECL|function|__ia64_outw
id|__ia64_outw
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|___ia64_outw
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
r_void
DECL|function|__ia64_outl
id|__ia64_outl
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|___ia64_outl
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
r_int
r_char
DECL|function|__ia64_readb
id|__ia64_readb
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readb
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_readw
id|__ia64_readw
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readw
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_readl
id|__ia64_readl
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readl
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_readq
id|__ia64_readq
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readq
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_char
DECL|function|__ia64_readb_relaxed
id|__ia64_readb_relaxed
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readb
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_readw_relaxed
id|__ia64_readw_relaxed
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readw
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_readl_relaxed
id|__ia64_readl_relaxed
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readl
(paren
id|addr
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|__ia64_readq_relaxed
id|__ia64_readq_relaxed
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|___ia64_readq
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_IA64_GENERIC */
eof
