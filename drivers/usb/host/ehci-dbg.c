multiline_comment|/*&n; * Copyright (c) 2001-2002 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* this file is part of ehci-hcd.c */
DECL|macro|ehci_dbg
mdefine_line|#define ehci_dbg(ehci, fmt, args...) &bslash;&n;&t;dev_dbg (*(ehci)-&gt;hcd.controller, fmt, ## args )
macro_line|#ifdef EHCI_VERBOSE_DEBUG
DECL|macro|ehci_vdbg
mdefine_line|#define ehci_vdbg(ehci, fmt, args...) &bslash;&n;&t;dev_dbg (*(ehci)-&gt;hcd.controller, fmt, ## args )
macro_line|#else
DECL|macro|ehci_vdbg
mdefine_line|#define ehci_vdbg(ehci, fmt, args...) do { } while (0)
macro_line|#endif
macro_line|#ifdef EHCI_VERBOSE_DEBUG
DECL|macro|vdbg
macro_line|#&t;define vdbg dbg
macro_line|#else
DECL|function|vdbg
r_static
r_inline
r_void
id|vdbg
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifdef&t;DEBUG
multiline_comment|/* check the values in the HCSPARAMS register&n; * (host controller _Structural_ parameters)&n; * see EHCI spec, Table 2-4 for each value&n; */
DECL|function|dbg_hcs_params
r_static
r_void
id|dbg_hcs_params
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_char
op_star
id|label
)paren
(brace
id|u32
id|params
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcs_params
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;%s hcs_params 0x%x dbg=%d%s cc=%d pcc=%d%s%s ports=%d&quot;
comma
id|label
comma
id|params
comma
id|HCS_DEBUG_PORT
(paren
id|params
)paren
comma
id|HCS_INDICATOR
(paren
id|params
)paren
ques
c_cond
l_string|&quot; ind&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|HCS_N_CC
(paren
id|params
)paren
comma
id|HCS_N_PCC
(paren
id|params
)paren
comma
id|HCS_PORTROUTED
(paren
id|params
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; ordered&quot;
comma
id|HCS_PPC
(paren
id|params
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; !ppc&quot;
comma
id|HCS_N_PORTS
(paren
id|params
)paren
)paren
suffix:semicolon
multiline_comment|/* Port routing, per EHCI 0.95 Spec, Section 2.2.5 */
r_if
c_cond
(paren
id|HCS_PORTROUTED
(paren
id|params
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
id|buf
(braket
l_int|46
)braket
comma
id|tmp
(braket
l_int|7
)braket
comma
id|byte
suffix:semicolon
id|buf
(braket
l_int|0
)braket
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
id|HCS_N_PORTS
(paren
id|params
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|byte
op_assign
id|readb
(paren
op_amp
id|ehci-&gt;caps-&gt;portroute
(braket
(paren
id|i
op_rshift
l_int|1
)paren
)braket
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|tmp
comma
l_string|&quot;%d &quot;
comma
(paren
(paren
id|i
op_amp
l_int|0x1
)paren
ques
c_cond
(paren
(paren
id|byte
)paren
op_amp
l_int|0xf
)paren
suffix:colon
(paren
(paren
id|byte
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
)paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
id|tmp
)paren
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;%s: %s portroute %s&quot;
comma
id|hcd_to_bus
(paren
op_amp
id|ehci-&gt;hcd
)paren
op_member_access_from_pointer
id|bus_name
comma
id|label
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|function|dbg_hcs_params
r_static
r_inline
r_void
id|dbg_hcs_params
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_char
op_star
id|label
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifdef&t;DEBUG
multiline_comment|/* check the values in the HCCPARAMS register&n; * (host controller _Capability_ parameters)&n; * see EHCI Spec, Table 2-5 for each value&n; * */
DECL|function|dbg_hcc_params
r_static
r_void
id|dbg_hcc_params
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_char
op_star
id|label
)paren
(brace
id|u32
id|params
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcc_params
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HCC_EXT_CAPS
(paren
id|params
)paren
)paren
(brace
singleline_comment|// EHCI 0.96 ... could interpret these (legacy?)
id|dbg
(paren
l_string|&quot;%s extended capabilities at pci %2x&quot;
comma
id|label
comma
id|HCC_EXT_CAPS
(paren
id|params
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|HCC_ISOC_CACHE
(paren
id|params
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;%s hcc_params %04x caching frame %s%s%s&quot;
comma
id|label
comma
id|params
comma
id|HCC_PGM_FRAMELISTLEN
(paren
id|params
)paren
ques
c_cond
l_string|&quot;256/512/1024&quot;
suffix:colon
l_string|&quot;1024&quot;
comma
id|HCC_CANPARK
(paren
id|params
)paren
ques
c_cond
l_string|&quot; park&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|HCC_64BIT_ADDR
(paren
id|params
)paren
ques
c_cond
l_string|&quot; 64 bit addr&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dbg
(paren
l_string|&quot;%s hcc_params %04x caching %d uframes %s%s%s&quot;
comma
id|label
comma
id|params
comma
id|HCC_ISOC_THRES
(paren
id|params
)paren
comma
id|HCC_PGM_FRAMELISTLEN
(paren
id|params
)paren
ques
c_cond
l_string|&quot;256/512/1024&quot;
suffix:colon
l_string|&quot;1024&quot;
comma
id|HCC_CANPARK
(paren
id|params
)paren
ques
c_cond
l_string|&quot; park&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|HCC_64BIT_ADDR
(paren
id|params
)paren
ques
c_cond
l_string|&quot; 64 bit addr&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|function|dbg_hcc_params
r_static
r_inline
r_void
id|dbg_hcc_params
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_char
op_star
id|label
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifdef&t;DEBUG
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_qh
id|dbg_qh
(paren
r_char
op_star
id|label
comma
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_struct
id|ehci_qh
op_star
id|qh
)paren
(brace
id|dbg
(paren
l_string|&quot;%s %p info1 %x info2 %x hw_curr %x qtd_next %x&quot;
comma
id|label
comma
id|qh
comma
id|qh-&gt;hw_info1
comma
id|qh-&gt;hw_info2
comma
id|qh-&gt;hw_current
comma
id|qh-&gt;hw_qtd_next
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;  alt+errs= %x, token= %x, page0= %x, page1= %x&quot;
comma
id|qh-&gt;hw_alt_next
comma
id|qh-&gt;hw_token
comma
id|qh-&gt;hw_buf
(braket
l_int|0
)braket
comma
id|qh-&gt;hw_buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qh-&gt;hw_buf
(braket
l_int|2
)braket
)paren
(brace
id|dbg
(paren
l_string|&quot;  page2= %x, page3= %x, page4= %x&quot;
comma
id|qh-&gt;hw_buf
(braket
l_int|2
)braket
comma
id|qh-&gt;hw_buf
(braket
l_int|3
)braket
comma
id|qh-&gt;hw_buf
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_status_buf
id|dbg_status_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
id|u32
id|status
)paren
(brace
r_return
id|snprintf
(paren
id|buf
comma
id|len
comma
l_string|&quot;%s%sstatus %04x%s%s%s%s%s%s%s%s%s%s&quot;
comma
id|label
comma
id|label
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot; &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|status
comma
(paren
id|status
op_amp
id|STS_ASS
)paren
ques
c_cond
l_string|&quot; Async&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_PSS
)paren
ques
c_cond
l_string|&quot; Periodic&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_RECL
)paren
ques
c_cond
l_string|&quot; Recl&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_HALT
)paren
ques
c_cond
l_string|&quot; Halt&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_IAA
)paren
ques
c_cond
l_string|&quot; IAA&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_FATAL
)paren
ques
c_cond
l_string|&quot; FATAL&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_FLR
)paren
ques
c_cond
l_string|&quot; FLR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_PCD
)paren
ques
c_cond
l_string|&quot; PCD&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_ERR
)paren
ques
c_cond
l_string|&quot; ERR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|STS_INT
)paren
ques
c_cond
l_string|&quot; INT&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_intr_buf
id|dbg_intr_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
id|u32
id|enable
)paren
(brace
r_return
id|snprintf
(paren
id|buf
comma
id|len
comma
l_string|&quot;%s%sintrenable %02x%s%s%s%s%s%s&quot;
comma
id|label
comma
id|label
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot; &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|enable
comma
(paren
id|enable
op_amp
id|STS_IAA
)paren
ques
c_cond
l_string|&quot; IAA&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|enable
op_amp
id|STS_FATAL
)paren
ques
c_cond
l_string|&quot; FATAL&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|enable
op_amp
id|STS_FLR
)paren
ques
c_cond
l_string|&quot; FLR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|enable
op_amp
id|STS_PCD
)paren
ques
c_cond
l_string|&quot; PCD&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|enable
op_amp
id|STS_ERR
)paren
ques
c_cond
l_string|&quot; ERR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|enable
op_amp
id|STS_INT
)paren
ques
c_cond
l_string|&quot; INT&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|variable|fls_strings
r_static
r_const
r_char
op_star
r_const
id|fls_strings
(braket
)braket
op_assign
(brace
l_string|&quot;1024&quot;
comma
l_string|&quot;512&quot;
comma
l_string|&quot;256&quot;
comma
l_string|&quot;??&quot;
)brace
suffix:semicolon
DECL|function|dbg_command_buf
r_static
r_int
id|dbg_command_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
id|u32
id|command
)paren
(brace
r_return
id|snprintf
(paren
id|buf
comma
id|len
comma
l_string|&quot;%s%scommand %06x %s=%d ithresh=%d%s%s%s%s period=%s%s %s&quot;
comma
id|label
comma
id|label
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot; &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|command
comma
(paren
id|command
op_amp
id|CMD_PARK
)paren
ques
c_cond
l_string|&quot;park&quot;
suffix:colon
l_string|&quot;(park)&quot;
comma
id|CMD_PARK_CNT
(paren
id|command
)paren
comma
(paren
id|command
op_rshift
l_int|16
)paren
op_amp
l_int|0x3f
comma
(paren
id|command
op_amp
id|CMD_LRESET
)paren
ques
c_cond
l_string|&quot; LReset&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|command
op_amp
id|CMD_IAAD
)paren
ques
c_cond
l_string|&quot; IAAD&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|command
op_amp
id|CMD_ASE
)paren
ques
c_cond
l_string|&quot; Async&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|command
op_amp
id|CMD_PSE
)paren
ques
c_cond
l_string|&quot; Periodic&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|fls_strings
(braket
(paren
id|command
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)braket
comma
(paren
id|command
op_amp
id|CMD_RESET
)paren
ques
c_cond
l_string|&quot; Reset&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|command
op_amp
id|CMD_RUN
)paren
ques
c_cond
l_string|&quot;RUN&quot;
suffix:colon
l_string|&quot;HALT&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|dbg_port_buf
id|dbg_port_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
r_int
id|port
comma
id|u32
id|status
)paren
(brace
r_char
op_star
id|sig
suffix:semicolon
multiline_comment|/* signaling state */
r_switch
c_cond
(paren
id|status
op_amp
(paren
l_int|3
op_lshift
l_int|10
)paren
)paren
(brace
r_case
l_int|0
op_lshift
l_int|10
suffix:colon
id|sig
op_assign
l_string|&quot;se0&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
op_lshift
l_int|10
suffix:colon
id|sig
op_assign
l_string|&quot;k&quot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* low speed */
r_case
l_int|2
op_lshift
l_int|10
suffix:colon
id|sig
op_assign
l_string|&quot;j&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sig
op_assign
l_string|&quot;?&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|snprintf
(paren
id|buf
comma
id|len
comma
l_string|&quot;%s%sport %d status %06x%s%s sig=%s %s%s%s%s%s%s%s%s%s&quot;
comma
id|label
comma
id|label
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot; &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|port
comma
id|status
comma
(paren
id|status
op_amp
id|PORT_POWER
)paren
ques
c_cond
l_string|&quot; POWER&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_OWNER
)paren
ques
c_cond
l_string|&quot; OWNER&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|sig
comma
(paren
id|status
op_amp
id|PORT_RESET
)paren
ques
c_cond
l_string|&quot; RESET&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_SUSPEND
)paren
ques
c_cond
l_string|&quot; SUSPEND&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_RESUME
)paren
ques
c_cond
l_string|&quot; RESUME&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_OCC
)paren
ques
c_cond
l_string|&quot; OCC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_OC
)paren
ques
c_cond
l_string|&quot; OC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_PEC
)paren
ques
c_cond
l_string|&quot; PEC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_PE
)paren
ques
c_cond
l_string|&quot; PE&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_CSC
)paren
ques
c_cond
l_string|&quot; CSC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|status
op_amp
id|PORT_CONNECT
)paren
ques
c_cond
l_string|&quot; CONNECT&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
r_static
r_inline
r_void
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_qh
id|dbg_qh
(paren
r_char
op_star
id|label
comma
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_struct
id|ehci_qh
op_star
id|qh
)paren
(brace
)brace
r_static
r_inline
r_int
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_status_buf
id|dbg_status_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
id|u32
id|status
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_command_buf
id|dbg_command_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
id|u32
id|command
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_intr_buf
id|dbg_intr_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
id|u32
id|enable
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
id|__attribute__
c_func
(paren
(paren
id|__unused__
)paren
)paren
DECL|function|dbg_port_buf
id|dbg_port_buf
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_char
op_star
id|label
comma
r_int
id|port
comma
id|u32
id|status
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* DEBUG */
multiline_comment|/* functions have the &quot;wrong&quot; filename when they&squot;re output... */
DECL|macro|dbg_status
mdefine_line|#define dbg_status(ehci, label, status) { &bslash;&n;&t;char _buf [80]; &bslash;&n;&t;dbg_status_buf (_buf, sizeof _buf, label, status); &bslash;&n;&t;dbg (&quot;%s&quot;, _buf); &bslash;&n;}
DECL|macro|dbg_cmd
mdefine_line|#define dbg_cmd(ehci, label, command) { &bslash;&n;&t;char _buf [80]; &bslash;&n;&t;dbg_command_buf (_buf, sizeof _buf, label, command); &bslash;&n;&t;dbg (&quot;%s&quot;, _buf); &bslash;&n;}
DECL|macro|dbg_port
mdefine_line|#define dbg_port(hcd, label, port, status) { &bslash;&n;&t;char _buf [80]; &bslash;&n;&t;dbg_port_buf (_buf, sizeof _buf, label, port, status); &bslash;&n;&t;dbg (&quot;%s&quot;, _buf); &bslash;&n;}
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef STUB_DEBUG_FILES
DECL|function|create_debug_files
r_static
r_inline
r_void
id|create_debug_files
(paren
r_struct
id|ehci_hcd
op_star
id|bus
)paren
(brace
)brace
DECL|function|remove_debug_files
r_static
r_inline
r_void
id|remove_debug_files
(paren
r_struct
id|ehci_hcd
op_star
id|bus
)paren
(brace
)brace
macro_line|#else
multiline_comment|/* troubleshooting help: expose state in driverfs */
DECL|macro|speed_char
mdefine_line|#define speed_char(info1) ({ char tmp; &bslash;&n;&t;&t;switch (info1 &amp; (3 &lt;&lt; 12)) { &bslash;&n;&t;&t;case 0 &lt;&lt; 12: tmp = &squot;f&squot;; break; &bslash;&n;&t;&t;case 1 &lt;&lt; 12: tmp = &squot;l&squot;; break; &bslash;&n;&t;&t;case 2 &lt;&lt; 12: tmp = &squot;h&squot;; break; &bslash;&n;&t;&t;default: tmp = &squot;?&squot;; break; &bslash;&n;&t;&t;}; tmp; })
DECL|function|qh_lines
r_static
r_void
id|qh_lines
(paren
r_struct
id|ehci_qh
op_star
id|qh
comma
r_char
op_star
op_star
id|nextp
comma
r_int
op_star
id|sizep
)paren
(brace
id|u32
id|scratch
suffix:semicolon
id|u32
id|hw_curr
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|ehci_qtd
op_star
id|td
suffix:semicolon
r_int
id|temp
suffix:semicolon
r_int
id|size
op_assign
op_star
id|sizep
suffix:semicolon
r_char
op_star
id|next
op_assign
op_star
id|nextp
suffix:semicolon
id|scratch
op_assign
id|cpu_to_le32p
(paren
op_amp
id|qh-&gt;hw_info1
)paren
suffix:semicolon
id|hw_curr
op_assign
id|cpu_to_le32p
(paren
op_amp
id|qh-&gt;hw_current
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;qh/%p dev%d %cs ep%d %08x %08x (%08x %08x)&quot;
comma
id|qh
comma
id|scratch
op_amp
l_int|0x007f
comma
id|speed_char
(paren
id|scratch
)paren
comma
(paren
id|scratch
op_rshift
l_int|8
)paren
op_amp
l_int|0x000f
comma
id|scratch
comma
id|cpu_to_le32p
(paren
op_amp
id|qh-&gt;hw_info2
)paren
comma
id|hw_curr
comma
id|cpu_to_le32p
(paren
op_amp
id|qh-&gt;hw_token
)paren
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|list_for_each
(paren
id|entry
comma
op_amp
id|qh-&gt;qtd_list
)paren
(brace
id|td
op_assign
id|list_entry
(paren
id|entry
comma
r_struct
id|ehci_qtd
comma
id|qtd_list
)paren
suffix:semicolon
id|scratch
op_assign
id|cpu_to_le32p
(paren
op_amp
id|td-&gt;hw_token
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;&bslash;n&bslash;t%std/%p %s len=%d %08x urb %p&quot;
comma
(paren
id|hw_curr
op_eq
id|td-&gt;qtd_dma
)paren
ques
c_cond
l_string|&quot;*&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|td
comma
(paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
r_switch
(paren
(paren
id|scratch
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
(brace
r_case
l_int|0
suffix:colon
id|tmp
op_assign
l_string|&quot;out&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tmp
op_assign
l_string|&quot;in&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tmp
op_assign
l_string|&quot;setup&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|tmp
op_assign
l_string|&quot;?&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tmp
suffix:semicolon
)brace
)paren
comma
(paren
id|scratch
op_rshift
l_int|16
)paren
op_amp
l_int|0x7fff
comma
id|scratch
comma
id|td-&gt;urb
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
)brace
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|sizep
op_assign
id|size
op_minus
id|temp
suffix:semicolon
op_star
id|nextp
op_assign
id|next
op_plus
id|temp
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|show_async
id|show_async
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|ehci_hcd
op_star
id|ehci
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
comma
id|size
suffix:semicolon
r_char
op_star
id|next
suffix:semicolon
r_struct
id|ehci_qh
op_star
id|qh
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|pdev
op_assign
id|container_of
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
id|ehci
op_assign
id|container_of
(paren
id|pci_get_drvdata
(paren
id|pdev
)paren
comma
r_struct
id|ehci_hcd
comma
id|hcd
)paren
suffix:semicolon
id|next
op_assign
id|buf
suffix:semicolon
id|size
op_assign
id|count
suffix:semicolon
multiline_comment|/* dumps a snapshot of the async schedule.&n;&t; * usually empty except for long-term bulk reads, or head.&n;&t; * one QH per line, and TDs we know about&n;&t; */
id|spin_lock_irqsave
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|qh
op_assign
id|ehci-&gt;async-&gt;qh_next.qh
suffix:semicolon
id|qh
suffix:semicolon
id|qh
op_assign
id|qh-&gt;qh_next.qh
)paren
id|qh_lines
(paren
id|qh
comma
op_amp
id|next
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ehci-&gt;reclaim
)paren
(brace
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;&bslash;nreclaim =&bslash;n&quot;
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|qh_lines
(paren
id|ehci-&gt;reclaim
comma
op_amp
id|next
comma
op_amp
id|size
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|count
op_minus
id|size
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
(paren
id|async
comma
id|S_IRUGO
comma
id|show_async
comma
l_int|NULL
)paren
suffix:semicolon
DECL|macro|DBG_SCHED_LIMIT
mdefine_line|#define DBG_SCHED_LIMIT 64
r_static
id|ssize_t
DECL|function|show_periodic
id|show_periodic
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|ehci_hcd
op_star
id|ehci
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_union
id|ehci_shadow
id|p
comma
op_star
id|seen
suffix:semicolon
r_int
id|temp
comma
id|size
comma
id|seen_count
suffix:semicolon
r_char
op_star
id|next
suffix:semicolon
r_int
id|i
comma
id|tag
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|seen
op_assign
id|kmalloc
(paren
id|DBG_SCHED_LIMIT
op_star
r_sizeof
op_star
id|seen
comma
id|SLAB_ATOMIC
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|seen_count
op_assign
l_int|0
suffix:semicolon
id|pdev
op_assign
id|container_of
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
id|ehci
op_assign
id|container_of
(paren
id|pci_get_drvdata
(paren
id|pdev
)paren
comma
r_struct
id|ehci_hcd
comma
id|hcd
)paren
suffix:semicolon
id|next
op_assign
id|buf
suffix:semicolon
id|size
op_assign
id|count
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;size = %d&bslash;n&quot;
comma
id|ehci-&gt;periodic_size
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
multiline_comment|/* dump a snapshot of the periodic schedule.&n;&t; * iso changes, interrupt usually doesn&squot;t.&n;&t; */
id|spin_lock_irqsave
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
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
id|ehci-&gt;periodic_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
id|ehci-&gt;pshadow
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p.ptr
)paren
r_continue
suffix:semicolon
id|tag
op_assign
id|Q_NEXT_TYPE
(paren
id|ehci-&gt;periodic
(braket
id|i
)braket
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;%4d: &quot;
comma
id|i
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
r_do
(brace
r_switch
c_cond
(paren
id|tag
)paren
(brace
r_case
id|Q_TYPE_QH
suffix:colon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot; qh%d/%p&quot;
comma
id|p.qh-&gt;period
comma
id|p.qh
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
r_for
c_loop
(paren
id|temp
op_assign
l_int|0
suffix:semicolon
id|temp
OL
id|seen_count
suffix:semicolon
id|temp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|seen
(braket
id|temp
)braket
dot
id|ptr
op_eq
id|p.ptr
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* show more info the first time around */
r_if
c_cond
(paren
id|temp
op_eq
id|seen_count
)paren
(brace
id|u32
id|scratch
op_assign
id|cpu_to_le32p
(paren
op_amp
id|p.qh-&gt;hw_info1
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot; (%cs dev%d ep%d [%d/%d] %d)&quot;
comma
id|speed_char
(paren
id|scratch
)paren
comma
id|scratch
op_amp
l_int|0x007f
comma
(paren
id|scratch
op_rshift
l_int|8
)paren
op_amp
l_int|0x000f
comma
id|p.qh-&gt;usecs
comma
id|p.qh-&gt;c_usecs
comma
id|scratch
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* FIXME TD info too */
r_if
c_cond
(paren
id|seen_count
OL
id|DBG_SCHED_LIMIT
)paren
id|seen
(braket
id|seen_count
op_increment
)braket
dot
id|qh
op_assign
id|p.qh
suffix:semicolon
)brace
r_else
id|temp
op_assign
l_int|0
suffix:semicolon
id|tag
op_assign
id|Q_NEXT_TYPE
(paren
id|p.qh-&gt;hw_next
)paren
suffix:semicolon
id|p
op_assign
id|p.qh-&gt;qh_next
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_TYPE_FSTN
suffix:colon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot; fstn-%8x/%p&quot;
comma
id|p.fstn-&gt;hw_prev
comma
id|p.fstn
)paren
suffix:semicolon
id|tag
op_assign
id|Q_NEXT_TYPE
(paren
id|p.fstn-&gt;hw_next
)paren
suffix:semicolon
id|p
op_assign
id|p.fstn-&gt;fstn_next
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_TYPE_ITD
suffix:colon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot; itd/%p&quot;
comma
id|p.itd
)paren
suffix:semicolon
id|tag
op_assign
id|Q_NEXT_TYPE
(paren
id|p.itd-&gt;hw_next
)paren
suffix:semicolon
id|p
op_assign
id|p.itd-&gt;itd_next
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Q_TYPE_SITD
suffix:colon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot; sitd/%p&quot;
comma
id|p.sitd
)paren
suffix:semicolon
id|tag
op_assign
id|Q_NEXT_TYPE
(paren
id|p.sitd-&gt;hw_next
)paren
suffix:semicolon
id|p
op_assign
id|p.sitd-&gt;sitd_next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p.ptr
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
(paren
id|seen
)paren
suffix:semicolon
r_return
id|count
op_minus
id|size
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
(paren
id|periodic
comma
id|S_IRUGO
comma
id|show_periodic
comma
l_int|NULL
)paren
suffix:semicolon
DECL|macro|DBG_SCHED_LIMIT
macro_line|#undef DBG_SCHED_LIMIT
r_static
id|ssize_t
DECL|function|show_registers
id|show_registers
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|ehci_hcd
op_star
id|ehci
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
comma
id|size
comma
id|i
suffix:semicolon
r_char
op_star
id|next
comma
id|scratch
(braket
l_int|80
)braket
suffix:semicolon
r_static
r_char
id|fmt
(braket
)braket
op_assign
l_string|&quot;%*s&bslash;n&quot;
suffix:semicolon
r_static
r_char
id|label
(braket
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|pdev
op_assign
id|container_of
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
id|ehci
op_assign
id|container_of
(paren
id|pci_get_drvdata
(paren
id|pdev
)paren
comma
r_struct
id|ehci_hcd
comma
id|hcd
)paren
suffix:semicolon
id|next
op_assign
id|buf
suffix:semicolon
id|size
op_assign
id|count
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Capability Registers */
id|i
op_assign
id|readw
(paren
op_amp
id|ehci-&gt;caps-&gt;hci_version
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;EHCI %x.%02x, hcd state %d&bslash;n&quot;
comma
id|i
op_rshift
l_int|8
comma
id|i
op_amp
l_int|0x0ff
comma
id|ehci-&gt;hcd.state
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
singleline_comment|// FIXME interpret both types of params
id|i
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcs_params
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;structural params 0x%08x&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|i
op_assign
id|readl
(paren
op_amp
id|ehci-&gt;caps-&gt;hcc_params
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;capability params 0x%08x&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
multiline_comment|/* Operational Registers */
id|temp
op_assign
id|dbg_status_buf
(paren
id|scratch
comma
r_sizeof
id|scratch
comma
id|label
comma
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;status
)paren
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
id|fmt
comma
id|temp
comma
id|scratch
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|temp
op_assign
id|dbg_command_buf
(paren
id|scratch
comma
r_sizeof
id|scratch
comma
id|label
comma
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;command
)paren
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
id|fmt
comma
id|temp
comma
id|scratch
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|temp
op_assign
id|dbg_intr_buf
(paren
id|scratch
comma
r_sizeof
id|scratch
comma
id|label
comma
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;intr_enable
)paren
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
id|fmt
comma
id|temp
comma
id|scratch
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;uframe %04x&bslash;n&quot;
comma
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;frame_index
)paren
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
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
id|HCS_N_PORTS
(paren
id|ehci-&gt;hcs_params
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
op_assign
id|dbg_port_buf
(paren
id|scratch
comma
r_sizeof
id|scratch
comma
id|label
comma
id|i
comma
id|readl
(paren
op_amp
id|ehci-&gt;regs-&gt;port_status
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
id|fmt
comma
id|temp
comma
id|scratch
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ehci-&gt;reclaim
)paren
(brace
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;reclaim qh %p%s&bslash;n&quot;
comma
id|ehci-&gt;reclaim
comma
id|ehci-&gt;reclaim_ready
ques
c_cond
l_string|&quot; ready&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
)brace
macro_line|#ifdef EHCI_STATS
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;irq normal %ld err %ld reclaim %ld&bslash;n&quot;
comma
id|ehci-&gt;stats.normal
comma
id|ehci-&gt;stats.error
comma
id|ehci-&gt;stats.reclaim
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;complete %ld unlink %ld&bslash;n&quot;
comma
id|ehci-&gt;stats.complete
comma
id|ehci-&gt;stats.unlink
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
macro_line|#endif
id|spin_unlock_irqrestore
(paren
op_amp
id|ehci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|count
op_minus
id|size
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
(paren
id|registers
comma
id|S_IRUGO
comma
id|show_registers
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|create_debug_files
r_static
r_inline
r_void
id|create_debug_files
(paren
r_struct
id|ehci_hcd
op_star
id|bus
)paren
(brace
id|device_create_file
(paren
op_amp
id|bus-&gt;hcd.pdev-&gt;dev
comma
op_amp
id|dev_attr_async
)paren
suffix:semicolon
id|device_create_file
(paren
op_amp
id|bus-&gt;hcd.pdev-&gt;dev
comma
op_amp
id|dev_attr_periodic
)paren
suffix:semicolon
id|device_create_file
(paren
op_amp
id|bus-&gt;hcd.pdev-&gt;dev
comma
op_amp
id|dev_attr_registers
)paren
suffix:semicolon
)brace
DECL|function|remove_debug_files
r_static
r_inline
r_void
id|remove_debug_files
(paren
r_struct
id|ehci_hcd
op_star
id|bus
)paren
(brace
id|device_remove_file
(paren
op_amp
id|bus-&gt;hcd.pdev-&gt;dev
comma
op_amp
id|dev_attr_async
)paren
suffix:semicolon
id|device_remove_file
(paren
op_amp
id|bus-&gt;hcd.pdev-&gt;dev
comma
op_amp
id|dev_attr_periodic
)paren
suffix:semicolon
id|device_remove_file
(paren
op_amp
id|bus-&gt;hcd.pdev-&gt;dev
comma
op_amp
id|dev_attr_registers
)paren
suffix:semicolon
)brace
macro_line|#endif /* STUB_DEBUG_FILES */
eof
