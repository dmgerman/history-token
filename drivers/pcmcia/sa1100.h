multiline_comment|/*======================================================================&n;&n;    Device driver for the PCMCIA control functionality of StrongARM&n;    SA-1100 microprocessors.&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is John G. Dorsey&n;    &lt;john+@cs.cmu.edu&gt;.  Portions created by John G. Dorsey are&n;    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
macro_line|#if !defined(_PCMCIA_SA1100_H)
DECL|macro|_PCMCIA_SA1100_H
macro_line|# define _PCMCIA_SA1100_H
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
macro_line|#include &lt;asm/arch/pcmcia.h&gt;
multiline_comment|/* MECR: Expansion Memory Configuration Register&n; * (SA-1100 Developers Manual, p.10-13; SA-1110 Developers Manual, p.10-24)&n; *&n; * MECR layout is:  &n; *&n; *   FAST1 BSM1&lt;4:0&gt; BSA1&lt;4:0&gt; BSIO1&lt;4:0&gt; FAST0 BSM0&lt;4:0&gt; BSA0&lt;4:0&gt; BSIO0&lt;4:0&gt;&n; *&n; * (This layout is actually true only for the SA-1110; the FASTn bits are&n; * reserved on the SA-1100.)&n; */
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
multiline_comment|/* This function returns the (approxmiate) command assertion period, in&n; * nanoseconds, for a given CPU clock frequency and MECR BS value:&n; */
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
multiline_comment|/* SA-1100 PCMCIA Memory and I/O timing&n; * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^&n; * The SA-1110 Developer&squot;s Manual, section 10.2.5, says the following:&n; *&n; *  &quot;To calculate the recommended BS_xx value for each address space:&n; *   divide the command width time (the greater of twIOWR and twIORD,&n; *   or the greater of twWE and twOE) by processor cycle time; divide&n; *   by 2; divide again by 3 (number of BCLK&squot;s per command assertion);&n; *   round up to the next whole number; and subtract 1.&quot;&n; *&n; * The PC Card Standard, Release 7, section 4.13.4, says that twIORD&n; * has a minimum value of 165ns. Section 4.13.5 says that twIOWR has&n; * a minimum value of 165ns, as well. Section 4.7.2 (describing&n; * common and attribute memory write timing) says that twWE has a&n; * minimum value of 150ns for a 250ns cycle time (for 5V operation;&n; * see section 4.7.4), or 300ns for a 600ns cycle time (for 3.3V&n; * operation, also section 4.7.4). Section 4.7.3 says that taOE&n; * has a maximum value of 150ns for a 300ns cycle time (for 5V&n; * operation), or 300ns for a 600ns cycle time (for 3.3V operation).&n; *&n; * When configuring memory maps, Card Services appears to adopt the policy&n; * that a memory access time of &quot;0&quot; means &quot;use the default.&quot; The default&n; * PCMCIA I/O command width time is 165ns. The default PCMCIA 5V attribute&n; * and memory command width time is 150ns; the PCMCIA 3.3V attribute and&n; * memory command width time is 300ns.&n; */
DECL|macro|SA1100_PCMCIA_IO_ACCESS
mdefine_line|#define SA1100_PCMCIA_IO_ACCESS      (165)
DECL|macro|SA1100_PCMCIA_5V_MEM_ACCESS
mdefine_line|#define SA1100_PCMCIA_5V_MEM_ACCESS  (150)
DECL|macro|SA1100_PCMCIA_3V_MEM_ACCESS
mdefine_line|#define SA1100_PCMCIA_3V_MEM_ACCESS  (300)
multiline_comment|/* The socket driver actually works nicely in interrupt-driven form,&n; * so the (relatively infrequent) polling is &quot;just to be sure.&quot;&n; */
DECL|macro|SA1100_PCMCIA_POLL_PERIOD
mdefine_line|#define SA1100_PCMCIA_POLL_PERIOD    (2*HZ)
multiline_comment|/* This structure encapsulates per-socket state which we might need to&n; * use when responding to a Card Services query of some kind.&n; */
DECL|struct|sa1100_pcmcia_socket
r_struct
id|sa1100_pcmcia_socket
(brace
DECL|member|cs_state
id|socket_state_t
id|cs_state
suffix:semicolon
DECL|member|k_state
r_struct
id|pcmcia_state
id|k_state
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|handler_info
r_void
op_star
id|handler_info
suffix:semicolon
DECL|member|io_map
id|pccard_io_map
id|io_map
(braket
id|MAX_IO_WIN
)braket
suffix:semicolon
DECL|member|mem_map
id|pccard_mem_map
id|mem_map
(braket
id|MAX_WIN
)braket
suffix:semicolon
DECL|member|virt_io
DECL|member|phys_attr
DECL|member|phys_mem
id|ioaddr_t
id|virt_io
comma
id|phys_attr
comma
id|phys_mem
suffix:semicolon
DECL|member|speed_io
DECL|member|speed_attr
DECL|member|speed_mem
r_int
r_int
id|speed_io
comma
id|speed_attr
comma
id|speed_mem
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I/O pins replacing memory pins&n; * (PCMCIA System Architecture, 2nd ed., by Don Anderson, p.75)&n; *&n; * These signals change meaning when going from memory-only to &n; * memory-or-I/O interface:&n; */
DECL|macro|iostschg
mdefine_line|#define iostschg bvd1
DECL|macro|iospkr
mdefine_line|#define iospkr   bvd2
multiline_comment|/*&n; * Declaration for all implementation specific low_level operations.&n; */
r_extern
r_struct
id|pcmcia_low_level
id|assabet_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|neponset_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|h3600_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|cerf_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|gcplus_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|xp860_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|yopy_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|pangolin_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|freebird_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|pfs168_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|jornada720_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|flexanet_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|simpad_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|graphicsmaster_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|adsbitsy_pcmcia_ops
suffix:semicolon
r_extern
r_struct
id|pcmcia_low_level
id|stork_pcmcia_ops
suffix:semicolon
macro_line|#endif  /* !defined(_PCMCIA_SA1100_H) */
eof
