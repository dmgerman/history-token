multiline_comment|/*&n; * NS16550 Serial Port (uart) debugging stuff.&n; *&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdarg.h&gt;
DECL|macro|WANT_PPCDBG_TAB
mdefine_line|#define WANT_PPCDBG_TAB /* Only defined here */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
r_extern
id|u8
id|real_readb
c_func
(paren
r_volatile
id|u8
id|__iomem
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|real_writeb
c_func
(paren
id|u8
id|data
comma
r_volatile
id|u8
id|__iomem
op_star
id|addr
)paren
suffix:semicolon
DECL|struct|NS16550
r_struct
id|NS16550
(brace
multiline_comment|/* this struct must be packed */
DECL|member|rbr
r_int
r_char
id|rbr
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|ier
r_int
r_char
id|ier
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|fcr
r_int
r_char
id|fcr
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|lcr
r_int
r_char
id|lcr
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|mcr
r_int
r_char
id|mcr
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|lsr
r_int
r_char
id|lsr
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|msr
r_int
r_char
id|msr
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|scr
r_int
r_char
id|scr
suffix:semicolon
multiline_comment|/* 7 */
)brace
suffix:semicolon
DECL|macro|thr
mdefine_line|#define thr rbr
DECL|macro|iir
mdefine_line|#define iir fcr
DECL|macro|dll
mdefine_line|#define dll rbr
DECL|macro|dlm
mdefine_line|#define dlm ier
DECL|macro|dlab
mdefine_line|#define dlab lcr
DECL|macro|LSR_DR
mdefine_line|#define LSR_DR   0x01  /* Data ready */
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE   0x02  /* Overrun */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE   0x04  /* Parity error */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE   0x08  /* Framing error */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI   0x10  /* Break */
DECL|macro|LSR_THRE
mdefine_line|#define LSR_THRE 0x20  /* Xmit holding register empty */
DECL|macro|LSR_TEMT
mdefine_line|#define LSR_TEMT 0x40  /* Xmitter empty */
DECL|macro|LSR_ERR
mdefine_line|#define LSR_ERR  0x80  /* Error */
DECL|variable|udbg_comport
r_static
r_volatile
r_struct
id|NS16550
id|__iomem
op_star
id|udbg_comport
suffix:semicolon
DECL|function|udbg_init_uart
r_void
id|udbg_init_uart
c_func
(paren
r_void
id|__iomem
op_star
id|comport
comma
r_int
r_int
id|speed
)paren
(brace
id|u16
id|dll
op_assign
id|speed
ques
c_cond
(paren
l_int|115200
op_div
id|speed
)paren
suffix:colon
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|comport
)paren
(brace
id|udbg_comport
op_assign
(paren
r_struct
id|NS16550
id|__iomem
op_star
)paren
id|comport
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lcr
comma
l_int|0x00
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;ier
comma
l_int|0xff
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;ier
comma
l_int|0x00
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lcr
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Access baud rate */
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;dll
comma
id|dll
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* 1 = 115200,  2 = 57600,&n;&t;&t;&t;&t;&t;&t;&t;   3 = 38400, 12 = 9600 baud */
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;dlm
comma
id|dll
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* dll &gt;&gt; 8 which should be zero&n;&t;&t;&t;&t;&t;&t;&t;   for fast rates; */
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lcr
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* 8 data, 1 stop, no parity */
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;mcr
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* RTS/DTR */
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;fcr
comma
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* Clear &amp; enable FIFOs */
)brace
)brace
macro_line|#ifdef CONFIG_PPC_PMAC
DECL|macro|SCC_TXRDY
mdefine_line|#define&t;SCC_TXRDY&t;4
DECL|macro|SCC_RXRDY
mdefine_line|#define SCC_RXRDY&t;1
DECL|variable|sccc
r_static
r_volatile
id|u8
id|__iomem
op_star
id|sccc
suffix:semicolon
DECL|variable|sccd
r_static
r_volatile
id|u8
id|__iomem
op_star
id|sccd
suffix:semicolon
DECL|variable|scc_inittab
r_static
r_int
r_char
id|scc_inittab
(braket
)braket
op_assign
(brace
l_int|13
comma
l_int|0
comma
multiline_comment|/* set baud rate divisor */
l_int|12
comma
l_int|0
comma
l_int|14
comma
l_int|1
comma
multiline_comment|/* baud rate gen enable, src=rtxc */
l_int|11
comma
l_int|0x50
comma
multiline_comment|/* clocks = br gen */
l_int|5
comma
l_int|0xea
comma
multiline_comment|/* tx 8 bits, assert DTR &amp; RTS */
l_int|4
comma
l_int|0x46
comma
multiline_comment|/* x16 clock, 1 stop */
l_int|3
comma
l_int|0xc1
comma
multiline_comment|/* rx enable, 8 bits */
)brace
suffix:semicolon
DECL|function|udbg_init_scc
r_void
id|udbg_init_scc
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
(brace
id|u32
op_star
id|reg
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|i
comma
id|x
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;escc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
op_logical_or
id|np-&gt;parent
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;found SCC...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Get address within mac-io ASIC */
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|addr
op_assign
id|reg
(braket
l_int|0
)braket
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;local addr: %lx&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
multiline_comment|/* Get address of mac-io PCI itself */
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np-&gt;parent
comma
l_string|&quot;assigned-addresses&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|addr
op_add_assign
id|reg
(braket
l_int|2
)braket
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;final addr: %lx&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
multiline_comment|/* Setup for 57600 8N1 */
id|addr
op_add_assign
l_int|0x20
suffix:semicolon
id|sccc
op_assign
(paren
r_volatile
id|u8
op_star
id|__iomem
)paren
id|ioremap
c_func
(paren
id|addr
op_amp
id|PAGE_MASK
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|sccc
op_add_assign
id|addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|sccd
op_assign
id|sccc
op_plus
l_int|0x10
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;ioremap result sccc: %p&bslash;n&quot;
comma
id|sccc
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|20000
suffix:semicolon
id|i
op_ne
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
id|x
op_assign
id|in_8
c_func
(paren
id|sccc
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|sccc
comma
l_int|0x09
)paren
suffix:semicolon
multiline_comment|/* reset A or B side */
id|out_8
c_func
(paren
id|sccc
comma
l_int|0xc0
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
OL
r_sizeof
(paren
id|scc_inittab
)paren
suffix:semicolon
op_increment
id|i
)paren
id|out_8
c_func
(paren
id|sccc
comma
id|scc_inittab
(braket
id|i
)braket
)paren
suffix:semicolon
id|ppc_md.udbg_putc
op_assign
id|udbg_putc
suffix:semicolon
id|ppc_md.udbg_getc
op_assign
id|udbg_getc
suffix:semicolon
id|ppc_md.udbg_getc_poll
op_assign
id|udbg_getc_poll
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;Hello World !&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
macro_line|#if CONFIG_PPC_PMAC
DECL|function|udbg_real_putc
r_static
r_void
id|udbg_real_putc
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
(paren
id|real_readb
c_func
(paren
id|sccc
)paren
op_amp
id|SCC_TXRDY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|real_writeb
c_func
(paren
id|c
comma
id|sccd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|udbg_real_putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
DECL|function|udbg_init_pmac_realmode
r_void
id|udbg_init_pmac_realmode
c_func
(paren
r_void
)paren
(brace
id|sccc
op_assign
(paren
r_volatile
id|u8
id|__iomem
op_star
)paren
l_int|0x80013020ul
suffix:semicolon
id|sccd
op_assign
(paren
r_volatile
id|u8
id|__iomem
op_star
)paren
l_int|0x80013030ul
suffix:semicolon
id|ppc_md.udbg_putc
op_assign
id|udbg_real_putc
suffix:semicolon
id|ppc_md.udbg_getc
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.udbg_getc_poll
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
macro_line|#ifdef CONFIG_PPC_MAPLE
DECL|function|udbg_maple_real_putc
r_void
id|udbg_maple_real_putc
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|udbg_comport
)paren
(brace
r_while
c_loop
(paren
(paren
id|real_readb
c_func
(paren
op_amp
id|udbg_comport-&gt;lsr
)paren
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for idle */
suffix:semicolon
id|real_writeb
c_func
(paren
id|c
comma
op_amp
id|udbg_comport-&gt;thr
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* Also put a CR.  This is for convenience. */
r_while
c_loop
(paren
(paren
id|real_readb
c_func
(paren
op_amp
id|udbg_comport-&gt;lsr
)paren
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for idle */
suffix:semicolon
id|real_writeb
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
op_amp
id|udbg_comport-&gt;thr
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|udbg_init_maple_realmode
r_void
id|udbg_init_maple_realmode
c_func
(paren
r_void
)paren
(brace
id|udbg_comport
op_assign
(paren
r_volatile
r_struct
id|NS16550
id|__iomem
op_star
)paren
l_int|0xf40003f8
suffix:semicolon
id|ppc_md.udbg_putc
op_assign
id|udbg_maple_real_putc
suffix:semicolon
id|ppc_md.udbg_getc
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.udbg_getc_poll
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_MAPLE */
DECL|function|udbg_putc
r_void
id|udbg_putc
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|udbg_comport
)paren
(brace
r_while
c_loop
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lsr
)paren
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for idle */
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;thr
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* Also put a CR.  This is for convenience. */
r_while
c_loop
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lsr
)paren
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for idle */
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|udbg_comport-&gt;thr
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PPC_PMAC
r_else
r_if
c_cond
(paren
id|sccc
)paren
(brace
r_while
c_loop
(paren
(paren
id|in_8
c_func
(paren
id|sccc
)paren
op_amp
id|SCC_TXRDY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|sccd
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
)brace
DECL|function|udbg_getc_poll
r_int
id|udbg_getc_poll
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|udbg_comport
)paren
(brace
r_if
c_cond
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lsr
)paren
op_amp
id|LSR_DR
)paren
op_ne
l_int|0
)paren
r_return
id|in_8
c_func
(paren
op_amp
id|udbg_comport-&gt;rbr
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PMAC
r_else
r_if
c_cond
(paren
id|sccc
)paren
(brace
r_if
c_cond
(paren
(paren
id|in_8
c_func
(paren
id|sccc
)paren
op_amp
id|SCC_RXRDY
)paren
op_ne
l_int|0
)paren
r_return
id|in_8
c_func
(paren
id|sccd
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|udbg_getc
r_int
r_char
id|udbg_getc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|udbg_comport
)paren
(brace
r_while
c_loop
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|udbg_comport-&gt;lsr
)paren
op_amp
id|LSR_DR
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for char */
suffix:semicolon
r_return
id|in_8
c_func
(paren
op_amp
id|udbg_comport-&gt;rbr
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PMAC
r_else
r_if
c_cond
(paren
id|sccc
)paren
(brace
r_while
c_loop
(paren
(paren
id|in_8
c_func
(paren
id|sccc
)paren
op_amp
id|SCC_RXRDY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_return
id|in_8
c_func
(paren
id|sccd
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|udbg_puts
r_void
id|udbg_puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.udbg_putc
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|s
op_logical_and
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|ppc_md
dot
id|udbg_putc
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|s
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|udbg_write
r_int
id|udbg_write
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_int
id|remain
op_assign
id|n
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.udbg_putc
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s
op_logical_and
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_while
c_loop
(paren
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_and
(paren
id|remain
op_decrement
OG
l_int|0
)paren
)paren
(brace
id|ppc_md
dot
id|udbg_putc
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
r_return
id|n
op_minus
id|remain
suffix:semicolon
)brace
DECL|function|udbg_read
r_int
id|udbg_read
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
(brace
r_char
id|c
comma
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.udbg_getc
)paren
r_return
l_int|0
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
id|buflen
suffix:semicolon
op_increment
id|i
)paren
(brace
r_do
(brace
id|c
op_assign
id|ppc_md
dot
id|udbg_getc
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
op_eq
l_int|0x11
op_logical_or
id|c
op_eq
l_int|0x13
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_int|0
)paren
r_break
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|udbg_console_write
r_void
id|udbg_console_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|n
)paren
(brace
id|udbg_write
c_func
(paren
id|s
comma
id|n
)paren
suffix:semicolon
)brace
DECL|macro|UDBG_BUFSIZE
mdefine_line|#define UDBG_BUFSIZE 256
DECL|function|udbg_printf
r_void
id|udbg_printf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_int
r_char
id|buf
(braket
id|UDBG_BUFSIZE
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|buf
comma
id|UDBG_BUFSIZE
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/* Special print used by PPCDBG() macro */
DECL|function|udbg_ppcdbg
r_void
id|udbg_ppcdbg
c_func
(paren
r_int
r_int
id|debug_flags
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_int
r_int
id|active_debugs
op_assign
id|debug_flags
op_amp
id|ppc64_debug_switch
suffix:semicolon
r_if
c_cond
(paren
id|active_debugs
)paren
(brace
id|va_list
id|ap
suffix:semicolon
r_int
r_char
id|buf
(braket
id|UDBG_BUFSIZE
)braket
suffix:semicolon
r_int
r_int
id|i
comma
id|len
op_assign
l_int|0
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
id|PPCDBG_NUM_FLAGS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
l_int|1U
op_lshift
id|i
)paren
op_amp
id|active_debugs
)paren
op_logical_and
id|trace_names
(braket
id|i
)braket
)paren
(brace
id|len
op_add_assign
id|strlen
c_func
(paren
id|trace_names
(braket
id|i
)braket
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|trace_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|snprintf
c_func
(paren
id|buf
comma
id|UDBG_BUFSIZE
comma
l_string|&quot; [%s]: &quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|len
op_add_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
l_int|18
)paren
(brace
id|udbg_puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|len
op_increment
suffix:semicolon
)brace
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|buf
comma
id|UDBG_BUFSIZE
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
)brace
DECL|function|udbg_ifdebug
r_int
r_int
id|udbg_ifdebug
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_return
(paren
id|flags
op_amp
id|ppc64_debug_switch
)paren
suffix:semicolon
)brace
eof
