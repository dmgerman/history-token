multiline_comment|/*&n; * include/asm-sh/snapgear/io.h&n; *&n; * Modified version of io_se.h for the snapgear-specific functions.&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * IO functions for a SnapGear&n; */
macro_line|#ifndef _ASM_SH_IO_SNAPGEAR_H
DECL|macro|_ASM_SH_IO_SNAPGEAR_H
mdefine_line|#define _ASM_SH_IO_SNAPGEAR_H
macro_line|#if defined(CONFIG_CPU_SH4)
multiline_comment|/*&n; * The external interrupt lines, these take up ints 0 - 15 inclusive&n; * depending on the priority for the interrupt.  In fact the priority&n; * is the interrupt :-)&n; */
DECL|macro|IRL0_IRQ
mdefine_line|#define IRL0_IRQ&t;&t;2
DECL|macro|IRL0_IPR_ADDR
mdefine_line|#define IRL0_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL0_IPR_POS
mdefine_line|#define IRL0_IPR_POS&t;3
DECL|macro|IRL0_PRIORITY
mdefine_line|#define IRL0_PRIORITY&t;13
DECL|macro|IRL1_IRQ
mdefine_line|#define IRL1_IRQ&t;&t;5
DECL|macro|IRL1_IPR_ADDR
mdefine_line|#define IRL1_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL1_IPR_POS
mdefine_line|#define IRL1_IPR_POS&t;2
DECL|macro|IRL1_PRIORITY
mdefine_line|#define IRL1_PRIORITY&t;10
DECL|macro|IRL2_IRQ
mdefine_line|#define IRL2_IRQ&t;&t;8
DECL|macro|IRL2_IPR_ADDR
mdefine_line|#define IRL2_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL2_IPR_POS
mdefine_line|#define IRL2_IPR_POS&t;1
DECL|macro|IRL2_PRIORITY
mdefine_line|#define IRL2_PRIORITY&t;7
DECL|macro|IRL3_IRQ
mdefine_line|#define IRL3_IRQ&t;&t;11
DECL|macro|IRL3_IPR_ADDR
mdefine_line|#define IRL3_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRL3_IPR_POS
mdefine_line|#define IRL3_IPR_POS&t;0
DECL|macro|IRL3_PRIORITY
mdefine_line|#define IRL3_PRIORITY&t;4
macro_line|#endif
r_extern
r_int
r_char
id|snapgear_inb
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
id|snapgear_inw
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
id|snapgear_inl
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|snapgear_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|snapgear_outw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|snapgear_outl
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_char
id|snapgear_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|snapgear_outb_p
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|snapgear_insl
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
suffix:semicolon
r_extern
r_void
id|snapgear_outsl
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
suffix:semicolon
r_extern
r_int
r_int
id|snapgear_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SH_SECUREEDGE5410
multiline_comment|/*&n; * We need to remember what was written to the ioport as some bits&n; * are shared with other functions and you cannot read back what was&n; * written :-|&n; *&n; * Bit        Read                   Write&n; * -----------------------------------------------&n; * D0         DCD on ttySC1          power&n; * D1         Reset Switch           heatbeat&n; * D2         ttySC0 CTS (7100)      LAN&n; * D3         -                      WAN&n; * D4         ttySC0 DCD (7100)      CONSOLE&n; * D5         -                      ONLINE&n; * D6         -                      VPN&n; * D7         -                      DTR on ttySC1&n; * D8         -                      ttySC0 RTS (7100)&n; * D9         -                      ttySC0 DTR (7100)&n; * D10        -                      RTC SCLK&n; * D11        RTC DATA               RTC DATA&n; * D12        -                      RTS RESET&n; */
DECL|macro|SECUREEDGE_IOPORT_ADDR
mdefine_line|#define SECUREEDGE_IOPORT_ADDR ((volatile short *) 0xb0000000)
r_extern
r_int
r_int
id|secureedge5410_ioport
suffix:semicolon
DECL|macro|SECUREEDGE_WRITE_IOPORT
mdefine_line|#define SECUREEDGE_WRITE_IOPORT(val, mask) (*SECUREEDGE_IOPORT_ADDR = &bslash;&n;&t;&t; (secureedge5410_ioport = &bslash;&n;&t;&t; &t;&t;((secureedge5410_ioport &amp; ~(mask)) | ((val) &amp; (mask)))))
DECL|macro|SECUREEDGE_READ_IOPORT
mdefine_line|#define SECUREEDGE_READ_IOPORT() &bslash;&n; &t;&t; ((*SECUREEDGE_IOPORT_ADDR&amp;0x0817) | (secureedge5410_ioport&amp;~0x0817))
macro_line|#endif
macro_line|#endif /* _ASM_SH_IO_SNAPGEAR_H */
eof
