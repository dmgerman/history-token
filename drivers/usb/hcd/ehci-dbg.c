multiline_comment|/*&n; * Copyright (c) 2001 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* this file is part of ehci-hcd.c */
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
multiline_comment|/* check the values in the HCSPARAMS register - host controller structural parameters */
multiline_comment|/* see EHCI 0.95 Spec, Table 2-4 for each value */
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
id|ehci-&gt;hcd.bus_name
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
multiline_comment|/* check the values in the HCCPARAMS register - host controller capability parameters */
multiline_comment|/* see EHCI 0.95 Spec, Table 2-5 for each value */
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
l_string|&quot;%s extended capabilities at pci %d&quot;
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
l_string|&quot;%s hcc_params 0x%04x caching frame %s%s%s&quot;
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
l_string|&quot;%s hcc_params 0x%04x caching %d uframes %s%s%s&quot;
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
macro_line|#if 0
r_static
r_void
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
macro_line|#endif
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
macro_line|#else
macro_line|#if 0
r_static
r_inline
r_void
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
macro_line|#endif
macro_line|#endif&t;/* DEBUG */
multiline_comment|/* functions have the &quot;wrong&quot; filename when they&squot;re output... */
DECL|macro|dbg_status
mdefine_line|#define dbg_status(ehci, label, status) &bslash;&n;&t;dbg (&quot;%s status 0x%x%s%s%s%s%s%s%s%s%s%s&quot;, &bslash;&n;&t;&t;label, status, &bslash;&n;&t;&t;(status &amp; STS_ASS) ? &quot; Async&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_PSS) ? &quot; Periodic&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_RECL) ? &quot; Recl&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_HALT) ? &quot; Halt&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_IAA) ? &quot; IAA&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_FATAL) ? &quot; FATAL&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_FLR) ? &quot; FLR&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_PCD) ? &quot; PCD&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_ERR) ? &quot; ERR&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; STS_INT) ? &quot; INT&quot; : &quot;&quot; &bslash;&n;&t;&t;)
DECL|macro|dbg_cmd
mdefine_line|#define dbg_cmd(ehci, label, command) &bslash;&n;&t;dbg (&quot;%s %x cmd %s=%d ithresh=%d%s%s%s%s period=%s%s %s&quot;, &bslash;&n;&t;&t;label, command, &bslash;&n;&t;&t;(command &amp; CMD_PARK) ? &quot;park&quot; : &quot;(park)&quot;, &bslash;&n;&t;&t;CMD_PARK_CNT (command), &bslash;&n;&t;&t;(command &gt;&gt; 16) &amp; 0x3f, &bslash;&n;&t;&t;(command &amp; CMD_LRESET) ? &quot; LReset&quot; : &quot;&quot;, &bslash;&n;&t;&t;(command &amp; CMD_IAAD) ? &quot; IAAD&quot; : &quot;&quot;, &bslash;&n;&t;&t;(command &amp; CMD_ASE) ? &quot; Async&quot; : &quot;&quot;, &bslash;&n;&t;&t;(command &amp; CMD_PSE) ? &quot; Periodic&quot; : &quot;&quot;, &bslash;&n;&t;&t;fls_strings [(command &gt;&gt; 2) &amp; 0x3], &bslash;&n;&t;&t;(command &amp; CMD_RESET) ? &quot; Reset&quot; : &quot;&quot;, &bslash;&n;&t;&t;(command &amp; CMD_RUN) ? &quot;RUN&quot; : &quot;HALT&quot; &bslash;&n;&t;&t;)
DECL|macro|dbg_port
mdefine_line|#define dbg_port(hcd, label, port, status) &bslash;&n;&t;dbg (&quot;%s port %d status 0x%x%s%s speed=%d%s%s%s%s%s%s%s%s%s&quot;, &bslash;&n;&t;&t;label, port, status, &bslash;&n;&t;&t;(status &amp; PORT_OWNER) ? &quot; OWNER&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_POWER) ? &quot; POWER&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &gt;&gt; 10) &amp; 3, &bslash;&n;&t;&t;(status &amp; PORT_RESET) ? &quot; RESET&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_SUSPEND) ? &quot; SUSPEND&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_RESUME) ? &quot; RESUME&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_OCC) ? &quot; OCC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_OC) ? &quot; OC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_PEC) ? &quot; PEC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_PE) ? &quot; PE&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_CSC) ? &quot; CSC&quot; : &quot;&quot;, &bslash;&n;&t;&t;(status &amp; PORT_CONNECT) ? &quot; CONNECT&quot; : &quot;&quot; &bslash;&n;&t;    )
eof
