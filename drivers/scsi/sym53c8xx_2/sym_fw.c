multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifdef __FreeBSD__
macro_line|#include &lt;dev/sym/sym_glue.h&gt;
macro_line|#else
macro_line|#include &quot;sym_glue.h&quot;
macro_line|#endif
multiline_comment|/*&n; *  Macros used for all firmwares.&n; */
DECL|macro|SYM_GEN_A
mdefine_line|#define&t;SYM_GEN_A(s, label)&t;((short) offsetof(s, label)),
DECL|macro|SYM_GEN_B
mdefine_line|#define&t;SYM_GEN_B(s, label)&t;((short) offsetof(s, label)),
DECL|macro|SYM_GEN_Z
mdefine_line|#define&t;SYM_GEN_Z(s, label)&t;((short) offsetof(s, label)),
DECL|macro|PADDR_A
mdefine_line|#define&t;PADDR_A(label)&t;&t;SYM_GEN_PADDR_A(struct SYM_FWA_SCR, label)
DECL|macro|PADDR_B
mdefine_line|#define&t;PADDR_B(label)&t;&t;SYM_GEN_PADDR_B(struct SYM_FWB_SCR, label)
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
multiline_comment|/*&n; *  Allocate firmware #1 script area.&n; */
DECL|macro|SYM_FWA_SCR
mdefine_line|#define&t;SYM_FWA_SCR&t;&t;sym_fw1a_scr
DECL|macro|SYM_FWB_SCR
mdefine_line|#define&t;SYM_FWB_SCR&t;&t;sym_fw1b_scr
DECL|macro|SYM_FWZ_SCR
mdefine_line|#define&t;SYM_FWZ_SCR&t;&t;sym_fw1z_scr
macro_line|#ifdef __FreeBSD__
macro_line|#include &lt;dev/sym/sym_fw1.h&gt;
macro_line|#else
macro_line|#include &quot;sym_fw1.h&quot;
macro_line|#endif
DECL|variable|sym_fw1a_ofs
r_static
r_struct
id|sym_fwa_ofs
id|sym_fw1a_ofs
op_assign
(brace
id|SYM_GEN_FW_A
c_func
(paren
r_struct
id|SYM_FWA_SCR
)paren
)brace
suffix:semicolon
DECL|variable|sym_fw1b_ofs
r_static
r_struct
id|sym_fwb_ofs
id|sym_fw1b_ofs
op_assign
(brace
id|SYM_GEN_FW_B
c_func
(paren
r_struct
id|SYM_FWB_SCR
)paren
macro_line|#ifdef SYM_OPT_HANDLE_DIR_UNKNOWN
id|SYM_GEN_B
c_func
(paren
r_struct
id|SYM_FWB_SCR
comma
id|data_io
)paren
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|sym_fw1z_ofs
r_static
r_struct
id|sym_fwz_ofs
id|sym_fw1z_ofs
op_assign
(brace
id|SYM_GEN_FW_Z
c_func
(paren
r_struct
id|SYM_FWZ_SCR
)paren
)brace
suffix:semicolon
DECL|macro|SYM_FWA_SCR
macro_line|#undef&t;SYM_FWA_SCR
DECL|macro|SYM_FWB_SCR
macro_line|#undef&t;SYM_FWB_SCR
DECL|macro|SYM_FWZ_SCR
macro_line|#undef&t;SYM_FWZ_SCR
macro_line|#endif&t;/* SYM_CONF_GENERIC_SUPPORT */
multiline_comment|/*&n; *  Allocate firmware #2 script area.&n; */
DECL|macro|SYM_FWA_SCR
mdefine_line|#define&t;SYM_FWA_SCR&t;&t;sym_fw2a_scr
DECL|macro|SYM_FWB_SCR
mdefine_line|#define&t;SYM_FWB_SCR&t;&t;sym_fw2b_scr
DECL|macro|SYM_FWZ_SCR
mdefine_line|#define&t;SYM_FWZ_SCR&t;&t;sym_fw2z_scr
macro_line|#ifdef __FreeBSD__
macro_line|#include &lt;dev/sym/sym_fw2.h&gt;
macro_line|#else
macro_line|#include &quot;sym_fw2.h&quot;
macro_line|#endif
DECL|variable|sym_fw2a_ofs
r_static
r_struct
id|sym_fwa_ofs
id|sym_fw2a_ofs
op_assign
(brace
id|SYM_GEN_FW_A
c_func
(paren
r_struct
id|SYM_FWA_SCR
)paren
)brace
suffix:semicolon
DECL|variable|sym_fw2b_ofs
r_static
r_struct
id|sym_fwb_ofs
id|sym_fw2b_ofs
op_assign
(brace
id|SYM_GEN_FW_B
c_func
(paren
r_struct
id|SYM_FWB_SCR
)paren
macro_line|#ifdef SYM_OPT_HANDLE_DIR_UNKNOWN
id|SYM_GEN_B
c_func
(paren
r_struct
id|SYM_FWB_SCR
comma
id|data_io
)paren
macro_line|#endif
id|SYM_GEN_B
c_func
(paren
r_struct
id|SYM_FWB_SCR
comma
id|start64
)paren
id|SYM_GEN_B
c_func
(paren
r_struct
id|SYM_FWB_SCR
comma
id|pm_handle
)paren
)brace
suffix:semicolon
DECL|variable|sym_fw2z_ofs
r_static
r_struct
id|sym_fwz_ofs
id|sym_fw2z_ofs
op_assign
(brace
id|SYM_GEN_FW_Z
c_func
(paren
r_struct
id|SYM_FWZ_SCR
)paren
)brace
suffix:semicolon
DECL|macro|SYM_FWA_SCR
macro_line|#undef&t;SYM_FWA_SCR
DECL|macro|SYM_FWB_SCR
macro_line|#undef&t;SYM_FWB_SCR
DECL|macro|SYM_FWZ_SCR
macro_line|#undef&t;SYM_FWZ_SCR
DECL|macro|SYM_GEN_A
macro_line|#undef&t;SYM_GEN_A
DECL|macro|SYM_GEN_B
macro_line|#undef&t;SYM_GEN_B
DECL|macro|SYM_GEN_Z
macro_line|#undef&t;SYM_GEN_Z
DECL|macro|PADDR_A
macro_line|#undef&t;PADDR_A
DECL|macro|PADDR_B
macro_line|#undef&t;PADDR_B
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
multiline_comment|/*&n; *  Patch routine for firmware #1.&n; */
r_static
r_void
DECL|function|sym_fw1_patch
id|sym_fw1_patch
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
)paren
(brace
r_struct
id|sym_fw1a_scr
op_star
id|scripta0
suffix:semicolon
r_struct
id|sym_fw1b_scr
op_star
id|scriptb0
suffix:semicolon
id|scripta0
op_assign
(paren
r_struct
id|sym_fw1a_scr
op_star
)paren
id|np-&gt;scripta0
suffix:semicolon
id|scriptb0
op_assign
(paren
r_struct
id|sym_fw1b_scr
op_star
)paren
id|np-&gt;scriptb0
suffix:semicolon
multiline_comment|/*&n;&t; *  Remove LED support if not needed.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_LED0
)paren
)paren
(brace
id|scripta0-&gt;idle
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;reselected
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;start
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
)brace
macro_line|#ifdef SYM_CONF_IARB_SUPPORT
multiline_comment|/*&n;&t; *    If user does not want to use IMMEDIATE ARBITRATION&n;&t; *    when we are reselected while attempting to arbitrate,&n;&t; *    patch the SCRIPTS accordingly with a SCRIPT NO_OP.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|SYM_CONF_SET_IARB_ON_ARB_LOST
)paren
id|scripta0-&gt;ungetjob
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Patch some data in SCRIPTS.&n;&t; *  - start and done queue initial bus address.&n;&t; *  - target bus address table bus address.&n;&t; */
id|scriptb0-&gt;startpos
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;squeue_ba
)paren
suffix:semicolon
id|scriptb0-&gt;done_pos
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;dqueue_ba
)paren
suffix:semicolon
id|scriptb0-&gt;targtbl
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;targtbl_ba
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* SYM_CONF_GENERIC_SUPPORT */
multiline_comment|/*&n; *  Patch routine for firmware #2.&n; */
r_static
r_void
DECL|function|sym_fw2_patch
id|sym_fw2_patch
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
)paren
(brace
r_struct
id|sym_fw2a_scr
op_star
id|scripta0
suffix:semicolon
r_struct
id|sym_fw2b_scr
op_star
id|scriptb0
suffix:semicolon
id|scripta0
op_assign
(paren
r_struct
id|sym_fw2a_scr
op_star
)paren
id|np-&gt;scripta0
suffix:semicolon
id|scriptb0
op_assign
(paren
r_struct
id|sym_fw2b_scr
op_star
)paren
id|np-&gt;scriptb0
suffix:semicolon
multiline_comment|/*&n;&t; *  Remove LED support if not needed.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_LED0
)paren
)paren
(brace
id|scripta0-&gt;idle
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;reselected
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;start
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
)brace
macro_line|#if   SYM_CONF_DMA_ADDRESSING_MODE == 2
multiline_comment|/*&n;&t; *  Remove useless 64 bit DMA specific SCRIPTS, &n;&t; *  when this feature is not available.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|np-&gt;use_dac
)paren
(brace
id|scripta0-&gt;is_dmap_dirty
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;is_dmap_dirty
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|scripta0-&gt;is_dmap_dirty
(braket
l_int|2
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;is_dmap_dirty
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SYM_CONF_IARB_SUPPORT
multiline_comment|/*&n;&t; *    If user does not want to use IMMEDIATE ARBITRATION&n;&t; *    when we are reselected while attempting to arbitrate,&n;&t; *    patch the SCRIPTS accordingly with a SCRIPT NO_OP.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|SYM_CONF_SET_IARB_ON_ARB_LOST
)paren
id|scripta0-&gt;ungetjob
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Patch some variable in SCRIPTS.&n;&t; *  - start and done queue initial bus address.&n;&t; *  - target bus address table bus address.&n;&t; */
id|scriptb0-&gt;startpos
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;squeue_ba
)paren
suffix:semicolon
id|scriptb0-&gt;done_pos
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;dqueue_ba
)paren
suffix:semicolon
id|scriptb0-&gt;targtbl
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;targtbl_ba
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Remove the load of SCNTL4 on reselection if not a C10.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_C10
)paren
)paren
(brace
id|scripta0-&gt;resel_scntl4
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;resel_scntl4
(braket
l_int|1
)braket
op_assign
id|cpu_to_scr
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Remove a couple of work-arounds specific to C1010 if &n;&t; *  they are not desirable. See `sym_fw2.h&squot; for more details.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;device_id
op_eq
id|PCI_ID_LSI53C1010_66
op_logical_and
id|np-&gt;revision_id
OL
l_int|0x1
op_logical_and
id|np-&gt;pciclk_khz
OL
l_int|60000
)paren
)paren
(brace
id|scripta0-&gt;datao_phase
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;datao_phase
(braket
l_int|1
)braket
op_assign
id|cpu_to_scr
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;device_id
op_eq
id|PCI_ID_LSI53C1010_33
op_logical_and
multiline_comment|/* np-&gt;revision_id &lt; 0xff */
l_int|1
)paren
)paren
(brace
id|scripta0-&gt;sel_done
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|SCR_NO_OP
)paren
suffix:semicolon
id|scripta0-&gt;sel_done
(braket
l_int|1
)braket
op_assign
id|cpu_to_scr
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Patch some other variables in SCRIPTS.&n;&t; *  These ones are loaded by the SCRIPTS processor.&n;&t; */
id|scriptb0-&gt;pm0_data_addr
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;scripta_ba
op_plus
m_offsetof
(paren
r_struct
id|sym_fw2a_scr
comma
id|pm0_data
)paren
)paren
suffix:semicolon
id|scriptb0-&gt;pm1_data_addr
(braket
l_int|0
)braket
op_assign
id|cpu_to_scr
c_func
(paren
id|np-&gt;scripta_ba
op_plus
m_offsetof
(paren
r_struct
id|sym_fw2a_scr
comma
id|pm1_data
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Fill the data area in scripts.&n; *  To be done for all firmwares.&n; */
r_static
r_void
DECL|function|sym_fw_fill_data
id|sym_fw_fill_data
(paren
id|u32
op_star
id|in
comma
id|u32
op_star
id|out
)paren
(brace
r_int
id|i
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
id|SYM_CONF_MAX_SG
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|in
op_increment
op_assign
id|SCR_CHMOV_TBL
op_xor
id|SCR_DATA_IN
suffix:semicolon
op_star
id|in
op_increment
op_assign
m_offsetof
(paren
r_struct
id|sym_dsb
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|SCR_CHMOV_TBL
op_xor
id|SCR_DATA_OUT
suffix:semicolon
op_star
id|out
op_increment
op_assign
m_offsetof
(paren
r_struct
id|sym_dsb
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Setup useful script bus addresses.&n; *  To be done for all firmwares.&n; */
r_static
r_void
DECL|function|sym_fw_setup_bus_addresses
id|sym_fw_setup_bus_addresses
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_fw
op_star
id|fw
)paren
(brace
id|u32
op_star
id|pa
suffix:semicolon
id|u_short
op_star
id|po
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *  Build the bus address table for script A &n;&t; *  from the script A offset table.&n;&t; */
id|po
op_assign
(paren
id|u_short
op_star
)paren
id|fw-&gt;a_ofs
suffix:semicolon
id|pa
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|np-&gt;fwa_bas
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
id|np-&gt;fwa_bas
)paren
op_div
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
id|i
op_increment
)paren
id|pa
(braket
id|i
)braket
op_assign
id|np-&gt;scripta_ba
op_plus
id|po
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *  Same for script B.&n;&t; */
id|po
op_assign
(paren
id|u_short
op_star
)paren
id|fw-&gt;b_ofs
suffix:semicolon
id|pa
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|np-&gt;fwb_bas
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
id|np-&gt;fwb_bas
)paren
op_div
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
id|i
op_increment
)paren
id|pa
(braket
id|i
)braket
op_assign
id|np-&gt;scriptb_ba
op_plus
id|po
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *  Same for script Z.&n;&t; */
id|po
op_assign
(paren
id|u_short
op_star
)paren
id|fw-&gt;z_ofs
suffix:semicolon
id|pa
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|np-&gt;fwz_bas
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
id|np-&gt;fwz_bas
)paren
op_div
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
id|i
op_increment
)paren
id|pa
(braket
id|i
)braket
op_assign
id|np-&gt;scriptz_ba
op_plus
id|po
(braket
id|i
)braket
suffix:semicolon
)brace
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
multiline_comment|/*&n; *  Setup routine for firmware #1.&n; */
r_static
r_void
DECL|function|sym_fw1_setup
id|sym_fw1_setup
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_fw
op_star
id|fw
)paren
(brace
r_struct
id|sym_fw1a_scr
op_star
id|scripta0
suffix:semicolon
r_struct
id|sym_fw1b_scr
op_star
id|scriptb0
suffix:semicolon
id|scripta0
op_assign
(paren
r_struct
id|sym_fw1a_scr
op_star
)paren
id|np-&gt;scripta0
suffix:semicolon
id|scriptb0
op_assign
(paren
r_struct
id|sym_fw1b_scr
op_star
)paren
id|np-&gt;scriptb0
suffix:semicolon
multiline_comment|/*&n;&t; *  Fill variable parts in scripts.&n;&t; */
id|sym_fw_fill_data
c_func
(paren
id|scripta0-&gt;data_in
comma
id|scripta0-&gt;data_out
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Setup bus addresses used from the C code..&n;&t; */
id|sym_fw_setup_bus_addresses
c_func
(paren
id|np
comma
id|fw
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* SYM_CONF_GENERIC_SUPPORT */
multiline_comment|/*&n; *  Setup routine for firmware #2.&n; */
r_static
r_void
DECL|function|sym_fw2_setup
id|sym_fw2_setup
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_fw
op_star
id|fw
)paren
(brace
r_struct
id|sym_fw2a_scr
op_star
id|scripta0
suffix:semicolon
r_struct
id|sym_fw2b_scr
op_star
id|scriptb0
suffix:semicolon
id|scripta0
op_assign
(paren
r_struct
id|sym_fw2a_scr
op_star
)paren
id|np-&gt;scripta0
suffix:semicolon
id|scriptb0
op_assign
(paren
r_struct
id|sym_fw2b_scr
op_star
)paren
id|np-&gt;scriptb0
suffix:semicolon
multiline_comment|/*&n;&t; *  Fill variable parts in scripts.&n;&t; */
id|sym_fw_fill_data
c_func
(paren
id|scripta0-&gt;data_in
comma
id|scripta0-&gt;data_out
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Setup bus addresses used from the C code..&n;&t; */
id|sym_fw_setup_bus_addresses
c_func
(paren
id|np
comma
id|fw
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Allocate firmware descriptors.&n; */
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
DECL|variable|sym_fw1
r_static
r_struct
id|sym_fw
id|sym_fw1
op_assign
id|SYM_FW_ENTRY
c_func
(paren
id|sym_fw1
comma
l_string|&quot;NCR-generic&quot;
)paren
suffix:semicolon
macro_line|#endif&t;/* SYM_CONF_GENERIC_SUPPORT */
DECL|variable|sym_fw2
r_static
r_struct
id|sym_fw
id|sym_fw2
op_assign
id|SYM_FW_ENTRY
c_func
(paren
id|sym_fw2
comma
l_string|&quot;LOAD/STORE-based&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *  Find the most appropriate firmware for a chip.&n; */
r_struct
id|sym_fw
op_star
DECL|function|sym_find_firmware
id|sym_find_firmware
c_func
(paren
r_struct
id|sym_pci_chip
op_star
id|chip
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;features
op_amp
id|FE_LDSTR
)paren
r_return
op_amp
id|sym_fw2
suffix:semicolon
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|chip-&gt;features
op_amp
(paren
id|FE_PFEN
op_or
id|FE_NOPM
op_or
id|FE_DAC
)paren
)paren
)paren
r_return
op_amp
id|sym_fw1
suffix:semicolon
macro_line|#endif
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *  Bind a script to physical addresses.&n; */
DECL|function|sym_fw_bind_script
r_void
id|sym_fw_bind_script
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
id|u32
op_star
id|start
comma
r_int
id|len
)paren
(brace
id|u32
id|opcode
comma
r_new
comma
id|old
comma
id|tmp1
comma
id|tmp2
suffix:semicolon
id|u32
op_star
id|end
comma
op_star
id|cur
suffix:semicolon
r_int
id|relocs
suffix:semicolon
id|cur
op_assign
id|start
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
op_div
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|cur
OL
id|end
)paren
(brace
id|opcode
op_assign
op_star
id|cur
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  If we forget to change the length&n;&t;&t; *  in scripts, a field will be&n;&t;&t; *  padded with 0. This is an illegal&n;&t;&t; *  command.&n;&t;&t; */
r_if
c_cond
(paren
id|opcode
op_eq
l_int|0
)paren
(brace
id|printf
(paren
l_string|&quot;%s: ERROR0 IN SCRIPT at %d.&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
(paren
r_int
)paren
(paren
id|cur
op_minus
id|start
)paren
)paren
suffix:semicolon
id|MDELAY
(paren
l_int|10000
)paren
suffix:semicolon
op_increment
id|cur
suffix:semicolon
r_continue
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  We use the bogus value 0xf00ff00f ;-)&n;&t;&t; *  to reserve data area in SCRIPTS.&n;&t;&t; */
r_if
c_cond
(paren
id|opcode
op_eq
id|SCR_DATA_ZERO
)paren
(brace
op_star
id|cur
op_increment
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DEBUG_FLAGS
op_amp
id|DEBUG_SCRIPT
)paren
id|printf
(paren
l_string|&quot;%d:  &lt;%x&gt;&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|cur
op_minus
id|start
)paren
comma
(paren
r_int
)paren
id|opcode
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  We don&squot;t have to decode ALL commands&n;&t;&t; */
r_switch
c_cond
(paren
id|opcode
op_rshift
l_int|28
)paren
(brace
r_case
l_int|0xf
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  LOAD / STORE DSA relative, don&squot;t relocate.&n;&t;&t;&t; */
id|relocs
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  LOAD / STORE absolute.&n;&t;&t;&t; */
id|relocs
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xc
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  COPY has TWO arguments.&n;&t;&t;&t; */
id|relocs
op_assign
l_int|2
suffix:semicolon
id|tmp1
op_assign
id|cur
(braket
l_int|1
)braket
suffix:semicolon
id|tmp2
op_assign
id|cur
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp1
op_xor
id|tmp2
)paren
op_amp
l_int|3
)paren
(brace
id|printf
(paren
l_string|&quot;%s: ERROR1 IN SCRIPT at %d.&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
(paren
r_int
)paren
(paren
id|cur
op_minus
id|start
)paren
)paren
suffix:semicolon
id|MDELAY
(paren
l_int|10000
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *  If PREFETCH feature not enabled, remove &n;&t;&t;&t; *  the NO FLUSH bit if present.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|opcode
op_amp
id|SCR_NO_FLUSH
)paren
op_logical_and
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_PFEN
)paren
)paren
(brace
id|opcode
op_assign
(paren
id|opcode
op_amp
op_complement
id|SCR_NO_FLUSH
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x0
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  MOVE/CHMOV (absolute address)&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_WIDE
)paren
)paren
id|opcode
op_assign
(paren
id|opcode
op_or
id|OPC_MOVE
)paren
suffix:semicolon
id|relocs
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  MOVE/CHMOV (table indirect)&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_WIDE
)paren
)paren
id|opcode
op_assign
(paren
id|opcode
op_or
id|OPC_MOVE
)paren
suffix:semicolon
id|relocs
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef SYM_CONF_TARGET_ROLE_SUPPORT
r_case
l_int|0x2
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  MOVE/CHMOV in target role (absolute address)&n;&t;&t;&t; */
id|opcode
op_and_assign
op_complement
l_int|0x20000000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_WIDE
)paren
)paren
id|opcode
op_assign
(paren
id|opcode
op_amp
op_complement
id|OPC_TCHMOVE
)paren
suffix:semicolon
id|relocs
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  MOVE/CHMOV in target role (table indirect)&n;&t;&t;&t; */
id|opcode
op_and_assign
op_complement
l_int|0x20000000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;features
op_amp
id|FE_WIDE
)paren
)paren
id|opcode
op_assign
(paren
id|opcode
op_amp
op_complement
id|OPC_TCHMOVE
)paren
suffix:semicolon
id|relocs
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|0x8
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  JUMP / CALL&n;&t;&t;&t; *  don&squot;t relocate if relative :-)&n;&t;&t;&t; */
r_if
c_cond
(paren
id|opcode
op_amp
l_int|0x00800000
)paren
id|relocs
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|opcode
op_amp
l_int|0xf8400000
)paren
op_eq
l_int|0x80400000
)paren
multiline_comment|/*JUMP64*/
id|relocs
op_assign
l_int|2
suffix:semicolon
r_else
id|relocs
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
r_case
l_int|0x5
suffix:colon
r_case
l_int|0x6
suffix:colon
r_case
l_int|0x7
suffix:colon
id|relocs
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|relocs
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Scriptify:) the opcode.&n;&t;&t; */
op_star
id|cur
op_increment
op_assign
id|cpu_to_scr
c_func
(paren
id|opcode
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  If no relocation, assume 1 argument &n;&t;&t; *  and just scriptize:) it.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|relocs
)paren
(brace
op_star
id|cur
op_assign
id|cpu_to_scr
c_func
(paren
op_star
id|cur
)paren
suffix:semicolon
op_increment
id|cur
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *  Otherwise performs all needed relocations.&n;&t;&t; */
r_while
c_loop
(paren
id|relocs
op_decrement
)paren
(brace
id|old
op_assign
op_star
id|cur
suffix:semicolon
r_switch
c_cond
(paren
id|old
op_amp
id|RELOC_MASK
)paren
(brace
r_case
id|RELOC_REGISTER
suffix:colon
r_new
op_assign
(paren
id|old
op_amp
op_complement
id|RELOC_MASK
)paren
op_plus
id|np-&gt;mmio_ba
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RELOC_LABEL_A
suffix:colon
r_new
op_assign
(paren
id|old
op_amp
op_complement
id|RELOC_MASK
)paren
op_plus
id|np-&gt;scripta_ba
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RELOC_LABEL_B
suffix:colon
r_new
op_assign
(paren
id|old
op_amp
op_complement
id|RELOC_MASK
)paren
op_plus
id|np-&gt;scriptb_ba
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RELOC_SOFTC
suffix:colon
r_new
op_assign
(paren
id|old
op_amp
op_complement
id|RELOC_MASK
)paren
op_plus
id|np-&gt;hcb_ba
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; *  Don&squot;t relocate a 0 address.&n;&t;&t;&t;&t; *  They are mostly used for patched or &n;&t;&t;&t;&t; *  script self-modified areas.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|old
op_eq
l_int|0
)paren
(brace
r_new
op_assign
id|old
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fall through */
r_default
suffix:colon
r_new
op_assign
l_int|0
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;sym_fw_bind_script: &quot;
l_string|&quot;weird relocation %x&bslash;n&quot;
comma
id|old
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|cur
op_increment
op_assign
id|cpu_to_scr
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
)brace
eof
