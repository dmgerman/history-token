multiline_comment|/*&n; *  linux/arch/m32r/kernel/io_mappi.c&n; *&n; *  Typical I/O routines for OPSPUT board.&n; *&n; *  Copyright (c) 2001, 2002  Hiroyuki Kondo, Hirokazu Takata,&n; *                            Hitoshi Yamamoto, Takeo Takahashi&n; *&n; *  This file is subject to the terms and conditions of the GNU General&n; *  Public License.  See the file &quot;COPYING&quot; in the main directory of this&n; *  archive for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|M32R_PCC_IOMAP_SIZE
mdefine_line|#define M32R_PCC_IOMAP_SIZE 0x1000
DECL|macro|M32R_PCC_IOSTART0
mdefine_line|#define M32R_PCC_IOSTART0 0x1000
DECL|macro|M32R_PCC_IOEND0
mdefine_line|#define M32R_PCC_IOEND0   (M32R_PCC_IOSTART0 + M32R_PCC_IOMAP_SIZE - 1)
r_extern
r_void
id|pcc_ioread_byte
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcc_ioread_word
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcc_iowrite_byte
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcc_iowrite_word
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PCMCIA &amp;&amp; CONFIG_M32R_CFC */
DECL|macro|PORT2ADDR
mdefine_line|#define PORT2ADDR(port)  _port2addr(port)
DECL|macro|PORT2ADDR_USB
mdefine_line|#define PORT2ADDR_USB(port) _port2addr_usb(port)
DECL|function|_port2addr
r_static
r_inline
r_void
op_star
id|_port2addr
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|port
op_plus
id|NONCACHE_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * OPSPUT-LAN is located in the extended bus space&n; * from 0x10000000 to 0x13ffffff on physical address.&n; * The base address of LAN controller(LAN91C111) is 0x300.&n; */
DECL|macro|LAN_IOSTART
mdefine_line|#define LAN_IOSTART&t;0x300
DECL|macro|LAN_IOEND
mdefine_line|#define LAN_IOEND&t;0x320
DECL|function|_port2addr_ne
r_static
r_inline
r_void
op_star
id|_port2addr_ne
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|port
op_plus
id|NONCACHE_OFFSET
op_plus
l_int|0x10000000
)paren
suffix:semicolon
)brace
DECL|function|_port2addr_usb
r_static
r_inline
r_void
op_star
id|_port2addr_usb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
id|port
op_amp
l_int|0x0f
)paren
op_plus
id|NONCACHE_OFFSET
op_plus
l_int|0x10303000
)paren
suffix:semicolon
)brace
DECL|function|delay
r_static
r_inline
r_void
id|delay
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;push r0; &bslash;n&bslash;t pop r0;&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NIC I/O function&n; */
DECL|macro|PORT2ADDR_NE
mdefine_line|#define PORT2ADDR_NE(port)  _port2addr_ne(port)
DECL|function|_ne_inb
r_static
r_inline
r_int
r_char
id|_ne_inb
c_func
(paren
r_void
op_star
id|portp
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|portp
suffix:semicolon
)brace
DECL|function|_ne_inw
r_static
r_inline
r_int
r_int
id|_ne_inw
c_func
(paren
r_void
op_star
id|portp
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|le16_to_cpu
c_func
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
)paren
suffix:semicolon
)brace
DECL|function|_ne_insb
r_static
r_inline
r_void
id|_ne_insb
c_func
(paren
r_void
op_star
id|portp
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_char
op_star
id|buf
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
id|_ne_inb
c_func
(paren
id|portp
)paren
suffix:semicolon
)brace
DECL|function|_ne_outb
r_static
r_inline
r_void
id|_ne_outb
c_func
(paren
r_int
r_char
id|b
comma
r_void
op_star
id|portp
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|portp
op_assign
id|b
suffix:semicolon
)brace
DECL|function|_ne_outw
r_static
r_inline
r_void
id|_ne_outw
c_func
(paren
r_int
r_int
id|w
comma
r_void
op_star
id|portp
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
op_assign
id|cpu_to_le16
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
DECL|function|_inb
r_int
r_char
id|_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
r_return
id|_ne_inb
c_func
(paren
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_else
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
r_int
r_char
id|b
suffix:semicolon
id|pcc_ioread_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
r_else
macro_line|#endif
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|_inw
r_int
r_int
id|_inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
r_return
id|_ne_inw
c_func
(paren
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_USB)
r_else
r_if
c_cond
(paren
id|port
op_ge
l_int|0x340
op_logical_and
id|port
OL
l_int|0x3a0
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR_USB
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_else
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
r_else
macro_line|#endif
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|_inl
r_int
r_int
id|_inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|l
comma
r_sizeof
(paren
id|l
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|l
suffix:semicolon
)brace
r_else
macro_line|#endif
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|_inb_p
r_int
r_char
id|_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|v
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|v
op_assign
id|_ne_inb
c_func
(paren
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_else
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
r_int
r_char
id|b
suffix:semicolon
id|pcc_ioread_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
r_else
macro_line|#endif
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|v
)paren
suffix:semicolon
)brace
DECL|function|_inw_p
r_int
r_int
id|_inw_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|v
op_assign
id|_ne_inw
c_func
(paren
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_else
macro_line|#if defined(CONFIG_USB)
r_if
c_cond
(paren
id|port
op_ge
l_int|0x340
op_logical_and
id|port
OL
l_int|0x3a0
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR_USB
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
r_else
macro_line|#endif
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|v
)paren
suffix:semicolon
)brace
DECL|function|_inl_p
r_int
r_int
id|_inl_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|v
)paren
suffix:semicolon
)brace
DECL|function|_outb
r_void
id|_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|_ne_outb
c_func
(paren
id|b
comma
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_else
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|function|_outw
r_void
id|_outw
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|_ne_outw
c_func
(paren
id|w
comma
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_else
macro_line|#if defined(CONFIG_USB)
r_if
c_cond
(paren
id|port
op_ge
l_int|0x340
op_logical_and
id|port
OL
l_int|0x3a0
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR_USB
c_func
(paren
id|port
)paren
op_assign
id|w
suffix:semicolon
)brace
r_else
macro_line|#endif
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|_outl
r_void
id|_outl
c_func
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
(brace
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|l
comma
r_sizeof
(paren
id|l
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|l
suffix:semicolon
)brace
DECL|function|_outb_p
r_void
id|_outb_p
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|_ne_outb
c_func
(paren
id|b
comma
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_else
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_outw_p
r_void
id|_outw_p
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|_ne_outw
c_func
(paren
id|w
comma
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_else
macro_line|#if defined(CONFIG_USB)
r_if
c_cond
(paren
id|port
op_ge
l_int|0x340
op_logical_and
id|port
OL
l_int|0x3a0
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR_USB
c_func
(paren
id|port
)paren
op_assign
id|w
suffix:semicolon
)brace
r_else
macro_line|#endif
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|w
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_outl_p
r_void
id|_outl_p
c_func
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|l
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_insb
r_void
id|_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
id|_ne_insb
c_func
(paren
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
comma
id|addr
comma
id|count
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
r_else
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_ioread_byte
c_func
(paren
l_int|0
comma
id|port
comma
(paren
r_void
op_star
)paren
id|addr
comma
r_sizeof
(paren
r_int
r_char
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
r_else
(brace
r_int
r_char
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_char
op_star
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|portp
suffix:semicolon
)brace
)brace
DECL|function|_insw
r_void
id|_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_int
op_star
id|portp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
(brace
multiline_comment|/*&n;&t;&t; * This portion is only used by smc91111.c to read data&n;&t;&t; * from the DATA_REG. Do not swap the data.&n;&t;&t; */
id|portp
op_assign
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
suffix:semicolon
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
)brace
r_else
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_ioread_word
c_func
(paren
l_int|9
comma
id|port
comma
(paren
r_void
op_star
)paren
id|addr
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
suffix:semicolon
)brace
)brace
DECL|function|_insl
r_void
id|_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_int
op_star
id|portp
suffix:semicolon
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
suffix:semicolon
)brace
DECL|function|_outsb
r_void
id|_outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_char
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_char
op_star
id|portp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
(brace
id|portp
op_assign
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|_ne_outb
c_func
(paren
op_star
id|buf
op_increment
comma
id|portp
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
)brace
r_else
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_byte
c_func
(paren
l_int|0
comma
id|port
comma
(paren
r_void
op_star
)paren
id|addr
comma
r_sizeof
(paren
r_int
r_char
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|_outsw
r_void
id|_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_int
op_star
id|portp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|LAN_IOSTART
op_logical_and
id|port
OL
id|LAN_IOEND
)paren
(brace
multiline_comment|/*&n;&t;&t; * This portion is only used by smc91111.c to write data&n;&t;&t; * into the DATA_REG. Do not swap the data.&n;&t;&t; */
id|portp
op_assign
id|PORT2ADDR_NE
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
macro_line|#if defined(CONFIG_PCMCIA) &amp;&amp; defined(CONFIG_M32R_CFC)
)brace
r_else
r_if
c_cond
(paren
id|port
op_ge
id|M32R_PCC_IOSTART0
op_logical_and
id|port
op_le
id|M32R_PCC_IOEND0
)paren
(brace
id|pcc_iowrite_word
c_func
(paren
l_int|9
comma
id|port
comma
(paren
r_void
op_star
)paren
id|addr
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|_outsl
r_void
id|_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_char
op_star
id|portp
suffix:semicolon
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
)brace
eof
