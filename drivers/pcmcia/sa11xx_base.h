multiline_comment|/*======================================================================&n;&n;    Device driver for the PCMCIA control functionality of StrongARM&n;    SA-1100 microprocessors.&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is John G. Dorsey&n;    &lt;john+@cs.cmu.edu&gt;.  Portions created by John G. Dorsey are&n;    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;&n;======================================================================*/
macro_line|#if !defined(_PCMCIA_SA1100_H)
DECL|macro|_PCMCIA_SA1100_H
macro_line|# define _PCMCIA_SA1100_H
multiline_comment|/* SA-1100 PCMCIA Memory and I/O timing&n; * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^&n; * The SA-1110 Developer&squot;s Manual, section 10.2.5, says the following:&n; *&n; *  &quot;To calculate the recommended BS_xx value for each address space:&n; *   divide the command width time (the greater of twIOWR and twIORD,&n; *   or the greater of twWE and twOE) by processor cycle time; divide&n; *   by 2; divide again by 3 (number of BCLK&squot;s per command assertion);&n; *   round up to the next whole number; and subtract 1.&quot;&n; */
multiline_comment|/* MECR: Expansion Memory Configuration Register&n; * (SA-1100 Developers Manual, p.10-13; SA-1110 Developers Manual, p.10-24)&n; *&n; * MECR layout is:&n; *&n; *   FAST1 BSM1&lt;4:0&gt; BSA1&lt;4:0&gt; BSIO1&lt;4:0&gt; FAST0 BSM0&lt;4:0&gt; BSA0&lt;4:0&gt; BSIO0&lt;4:0&gt;&n; *&n; * (This layout is actually true only for the SA-1110; the FASTn bits are&n; * reserved on the SA-1100.)&n; */
DECL|macro|MECR_SOCKET_0_SHIFT
mdefine_line|#define MECR_SOCKET_0_SHIFT (0)
DECL|macro|MECR_SOCKET_1_SHIFT
mdefine_line|#define MECR_SOCKET_1_SHIFT (16)
DECL|macro|MECR_BS_MASK
mdefine_line|#define MECR_BS_MASK        (0x1f)
DECL|macro|MECR_FAST_MODE_MASK
mdefine_line|#define MECR_FAST_MODE_MASK (0x01)
DECL|macro|MECR_BSIO_SHIFT
mdefine_line|#define MECR_BSIO_SHIFT (0)
DECL|macro|MECR_BSA_SHIFT
mdefine_line|#define MECR_BSA_SHIFT  (5)
DECL|macro|MECR_BSM_SHIFT
mdefine_line|#define MECR_BSM_SHIFT  (10)
DECL|macro|MECR_FAST_SHIFT
mdefine_line|#define MECR_FAST_SHIFT (15)
DECL|macro|MECR_SET
mdefine_line|#define MECR_SET(mecr, sock, shift, mask, bs) &bslash;&n;((mecr)=((mecr)&amp;~(((mask)&lt;&lt;(shift))&lt;&lt;&bslash;&n;                  ((sock)==0?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT)))|&bslash;&n;        (((bs)&lt;&lt;(shift))&lt;&lt;((sock)==0?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT)))
DECL|macro|MECR_GET
mdefine_line|#define MECR_GET(mecr, sock, shift, mask) &bslash;&n;((((mecr)&gt;&gt;(((sock)==0)?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT))&gt;&gt;&bslash;&n; (shift))&amp;(mask))
DECL|macro|MECR_BSIO_SET
mdefine_line|#define MECR_BSIO_SET(mecr, sock, bs) &bslash;&n;MECR_SET((mecr), (sock), MECR_BSIO_SHIFT, MECR_BS_MASK, (bs))
DECL|macro|MECR_BSIO_GET
mdefine_line|#define MECR_BSIO_GET(mecr, sock) &bslash;&n;MECR_GET((mecr), (sock), MECR_BSIO_SHIFT, MECR_BS_MASK)
DECL|macro|MECR_BSA_SET
mdefine_line|#define MECR_BSA_SET(mecr, sock, bs) &bslash;&n;MECR_SET((mecr), (sock), MECR_BSA_SHIFT, MECR_BS_MASK, (bs))
DECL|macro|MECR_BSA_GET
mdefine_line|#define MECR_BSA_GET(mecr, sock) &bslash;&n;MECR_GET((mecr), (sock), MECR_BSA_SHIFT, MECR_BS_MASK)
DECL|macro|MECR_BSM_SET
mdefine_line|#define MECR_BSM_SET(mecr, sock, bs) &bslash;&n;MECR_SET((mecr), (sock), MECR_BSM_SHIFT, MECR_BS_MASK, (bs))
DECL|macro|MECR_BSM_GET
mdefine_line|#define MECR_BSM_GET(mecr, sock) &bslash;&n;MECR_GET((mecr), (sock), MECR_BSM_SHIFT, MECR_BS_MASK)
DECL|macro|MECR_FAST_SET
mdefine_line|#define MECR_FAST_SET(mecr, sock, fast) &bslash;&n;MECR_SET((mecr), (sock), MECR_FAST_SHIFT, MECR_FAST_MODE_MASK, (fast))
DECL|macro|MECR_FAST_GET
mdefine_line|#define MECR_FAST_GET(mecr, sock) &bslash;&n;MECR_GET((mecr), (sock), MECR_FAST_SHIFT, MECR_FAST_MODE_MASK)
multiline_comment|/* This function implements the BS value calculation for setting the MECR&n; * using integer arithmetic:&n; */
DECL|function|sa1100_pcmcia_mecr_bs
r_static
r_inline
r_int
r_int
(def_block
id|sa1100_pcmcia_mecr_bs
c_func
(paren
r_int
r_int
id|pcmcia_cycle_ns
comma
r_int
r_int
id|cpu_clock_khz
)paren
(brace
r_int
r_int
id|t
op_assign
(paren
(paren
id|pcmcia_cycle_ns
op_star
id|cpu_clock_khz
)paren
op_div
l_int|6
)paren
op_minus
l_int|1000000
suffix:semicolon
r_return
(paren
id|t
op_div
l_int|1000000
)paren
op_plus
(paren
(paren
(paren
id|t
op_mod
l_int|1000000
)paren
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
)def_block
multiline_comment|/* This function returns the (approximate) command assertion period, in&n; * nanoseconds, for a given CPU clock frequency and MECR BS value:&n; */
DECL|function|sa1100_pcmcia_cmd_time
r_static
r_inline
r_int
r_int
(def_block
id|sa1100_pcmcia_cmd_time
c_func
(paren
r_int
r_int
id|cpu_clock_khz
comma
r_int
r_int
id|pcmcia_mecr_bs
)paren
(brace
r_return
(paren
(paren
(paren
l_int|10000000
op_star
l_int|2
)paren
op_div
id|cpu_clock_khz
)paren
op_star
(paren
l_int|3
op_star
(paren
id|pcmcia_mecr_bs
op_plus
l_int|1
)paren
)paren
)paren
op_div
l_int|10
suffix:semicolon
)brace
)def_block
r_extern
r_int
id|sa11xx_drv_pcmcia_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|pcmcia_low_level
op_star
id|ops
comma
r_int
id|first
comma
r_int
id|nr
)paren
suffix:semicolon
macro_line|#endif  /* !defined(_PCMCIA_SA1100_H) */
eof
