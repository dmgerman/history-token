multiline_comment|/*&n; * drivers/ide/ide-h8300.c&n; * H8/300 generic IDE interface&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|bswap
mdefine_line|#define bswap(d) &bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;u16 r;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;mov.b %w1,r1h&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;mov.b %x1,r1l&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;mov.w r1,%0&quot;&t;&t;&bslash;&n;&t;&t;:&quot;=r&quot;(r)&t;&t;&bslash;&n;&t;&t;:&quot;r&quot;(d)&t;&t;&t;&bslash;&n;&t;&t;:&quot;er1&quot;);&t;&t;&bslash;&n;&t;(r);&t;&t;&t;&t;&bslash;&n;})
DECL|function|mm_outw
r_static
r_void
id|mm_outw
c_func
(paren
id|u16
id|d
comma
r_int
r_int
id|a
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;mov.b %w0,r2h&bslash;n&bslash;t&quot;
l_string|&quot;mov.b %x0,r2l&bslash;n&bslash;t&quot;
l_string|&quot;mov.w r2,@%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|d
)paren
comma
l_string|&quot;r&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;er2&quot;
)paren
suffix:semicolon
)brace
DECL|function|mm_inw
r_static
id|u16
id|mm_inw
c_func
(paren
r_int
r_int
id|a
)paren
(brace
r_register
id|u16
id|r
id|__asm__
c_func
(paren
l_string|&quot;er0&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov.w @%1,r2&bslash;n&bslash;t&quot;
l_string|&quot;mov.b r2l,%x0&bslash;n&bslash;t&quot;
l_string|&quot;mov.b r2h,%w0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;er2&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|mm_outsw
r_static
r_void
id|mm_outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
id|u32
id|len
)paren
(brace
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
comma
id|bp
op_increment
)paren
op_star
(paren
r_volatile
id|u16
op_star
)paren
id|addr
op_assign
id|bswap
c_func
(paren
op_star
id|bp
)paren
suffix:semicolon
)brace
DECL|function|mm_insw
r_static
r_void
id|mm_insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
id|u32
id|len
)paren
(brace
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
comma
id|bp
op_increment
)paren
op_star
id|bp
op_assign
id|bswap
c_func
(paren
op_star
(paren
r_volatile
id|u16
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|H8300_IDE_GAP
mdefine_line|#define H8300_IDE_GAP (2)
DECL|function|hw_setup
r_static
r_inline
r_void
id|hw_setup
c_func
(paren
id|hw_regs_t
op_star
id|hw
)paren
(brace
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|hw
comma
l_int|0
comma
r_sizeof
(paren
id|hw_regs_t
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|CONFIG_H8300_IDE_BASE
op_plus
id|H8300_IDE_GAP
op_star
id|i
suffix:semicolon
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|CONFIG_H8300_IDE_ALT
suffix:semicolon
id|hw-&gt;irq
op_assign
id|EXT_IRQ0
op_plus
id|CONFIG_H8300_IDE_IRQ
suffix:semicolon
id|hw-&gt;dma
op_assign
id|NO_DMA
suffix:semicolon
id|hw-&gt;chipset
op_assign
id|ide_generic
suffix:semicolon
)brace
DECL|function|hwif_setup
r_static
r_inline
r_void
id|hwif_setup
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|default_hwif_iops
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|hwif-&gt;mmio
op_assign
l_int|2
suffix:semicolon
id|hwif-&gt;OUTW
op_assign
id|mm_outw
suffix:semicolon
id|hwif-&gt;OUTSW
op_assign
id|mm_outsw
suffix:semicolon
id|hwif-&gt;INW
op_assign
id|mm_inw
suffix:semicolon
id|hwif-&gt;INSW
op_assign
id|mm_insw
suffix:semicolon
id|hwif-&gt;OUTL
op_assign
l_int|NULL
suffix:semicolon
id|hwif-&gt;INL
op_assign
l_int|NULL
suffix:semicolon
id|hwif-&gt;OUTSL
op_assign
l_int|NULL
suffix:semicolon
id|hwif-&gt;INSL
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|h8300_ide_init
r_void
id|__init
id|h8300_ide_init
c_func
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
id|ide_hwif_t
op_star
id|hwif
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|CONFIG_H8300_IDE_BASE
comma
id|H8300_IDE_GAP
op_star
l_int|8
comma
l_string|&quot;ide-h8300&quot;
)paren
)paren
r_goto
id|out_busy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|CONFIG_H8300_IDE_ALT
comma
id|H8300_IDE_GAP
comma
l_string|&quot;ide-h8300&quot;
)paren
)paren
(brace
id|release_region
c_func
(paren
id|CONFIG_H8300_IDE_BASE
comma
id|H8300_IDE_GAP
op_star
l_int|8
)paren
suffix:semicolon
r_goto
id|out_busy
suffix:semicolon
)brace
id|hw_setup
c_func
(paren
op_amp
id|hw
)paren
suffix:semicolon
multiline_comment|/* register if */
id|idx
op_assign
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
op_amp
id|hwif
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ide-h8300: IDE I/F register failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hwif_setup
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ide%d: H8/300 generic IDE interface&bslash;n&quot;
comma
id|idx
)paren
suffix:semicolon
r_return
suffix:semicolon
id|out_busy
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ide-h8300: IDE I/F resource already used.&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
