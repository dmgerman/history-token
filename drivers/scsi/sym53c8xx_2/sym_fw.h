multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef&t;SYM_FW_H
DECL|macro|SYM_FW_H
mdefine_line|#define&t;SYM_FW_H
multiline_comment|/*&n; *  Macro used to generate interfaces for script A.&n; */
DECL|macro|SYM_GEN_FW_A
mdefine_line|#define SYM_GEN_FW_A(s)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_A(s, start)&t;&t;SYM_GEN_A(s, getjob_begin)&t;&bslash;&n;&t;SYM_GEN_A(s, getjob_end)&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_A(s, select)&t;&t;SYM_GEN_A(s, wf_sel_done)&t;&bslash;&n;&t;SYM_GEN_A(s, send_ident)&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_A(s, dispatch)&t;&t;SYM_GEN_A(s, init)&t;&t;&bslash;&n;&t;SYM_GEN_A(s, clrack)&t;&t;SYM_GEN_A(s, complete_error)&t;&bslash;&n;&t;SYM_GEN_A(s, done)&t;&t;SYM_GEN_A(s, done_end)&t;&t;&bslash;&n;&t;SYM_GEN_A(s, idle)&t;&t;SYM_GEN_A(s, ungetjob)&t;&t;&bslash;&n;&t;SYM_GEN_A(s, reselect)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_A(s, resel_tag)&t;&t;SYM_GEN_A(s, resel_dsa)&t;&t;&bslash;&n;&t;SYM_GEN_A(s, resel_no_tag)&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_A(s, data_in)&t;&t;SYM_GEN_A(s, data_in2)&t;&t;&bslash;&n;&t;SYM_GEN_A(s, data_out)&t;&t;SYM_GEN_A(s, data_out2)&t;&t;&bslash;&n;&t;SYM_GEN_A(s, pm0_data)&t;&t;SYM_GEN_A(s, pm1_data)
multiline_comment|/*&n; *  Macro used to generate interfaces for script B.&n; */
DECL|macro|SYM_GEN_FW_B
mdefine_line|#define SYM_GEN_FW_B(s)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_B(s, no_data)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_B(s, sel_for_abort)&t;SYM_GEN_B(s, sel_for_abort_1)&t;&bslash;&n;&t;SYM_GEN_B(s, msg_bad)&t;&t;SYM_GEN_B(s, msg_weird)&t;&t;&bslash;&n;&t;SYM_GEN_B(s, wdtr_resp)&t;&t;SYM_GEN_B(s, send_wdtr)&t;&t;&bslash;&n;&t;SYM_GEN_B(s, sdtr_resp)&t;&t;SYM_GEN_B(s, send_sdtr)&t;&t;&bslash;&n;&t;SYM_GEN_B(s, ppr_resp)&t;&t;SYM_GEN_B(s, send_ppr)&t;&t;&bslash;&n;&t;SYM_GEN_B(s, nego_bad_phase)&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_B(s, ident_break) &t;SYM_GEN_B(s, ident_break_atn)&t;&bslash;&n;&t;SYM_GEN_B(s, sdata_in)&t;&t;SYM_GEN_B(s, resel_bad_lun)&t;&bslash;&n;&t;SYM_GEN_B(s, bad_i_t_l)&t;&t;SYM_GEN_B(s, bad_i_t_l_q)&t;&bslash;&n;&t;SYM_GEN_B(s, wsr_ma_helper)
multiline_comment|/*&n; *  Macro used to generate interfaces for script Z.&n; */
DECL|macro|SYM_GEN_FW_Z
mdefine_line|#define SYM_GEN_FW_Z(s)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SYM_GEN_Z(s, snooptest)&t;&t;SYM_GEN_Z(s, snoopend)
multiline_comment|/*&n; *  Generates structure interface that contains &n; *  offsets within script A, B and Z.&n; */
DECL|macro|SYM_GEN_A
mdefine_line|#define&t;SYM_GEN_A(s, label)&t;s label;
DECL|macro|SYM_GEN_B
mdefine_line|#define&t;SYM_GEN_B(s, label)&t;s label;
DECL|macro|SYM_GEN_Z
mdefine_line|#define&t;SYM_GEN_Z(s, label)&t;s label;
DECL|struct|sym_fwa_ofs
r_struct
id|sym_fwa_ofs
(brace
id|SYM_GEN_FW_A
c_func
(paren
id|u_short
)paren
)brace
suffix:semicolon
DECL|struct|sym_fwb_ofs
r_struct
id|sym_fwb_ofs
(brace
id|SYM_GEN_FW_B
c_func
(paren
id|u_short
)paren
macro_line|#ifdef SYM_OPT_HANDLE_DIR_UNKNOWN
id|SYM_GEN_B
c_func
(paren
id|u_short
comma
id|data_io
)paren
macro_line|#endif
id|SYM_GEN_B
c_func
(paren
id|u_short
comma
id|start64
)paren
id|SYM_GEN_B
c_func
(paren
id|u_short
comma
id|pm_handle
)paren
)brace
suffix:semicolon
DECL|struct|sym_fwz_ofs
r_struct
id|sym_fwz_ofs
(brace
id|SYM_GEN_FW_Z
c_func
(paren
id|u_short
)paren
macro_line|#ifdef SYM_OPT_NO_BUS_MEMORY_MAPPING
id|SYM_GEN_Z
c_func
(paren
id|u_short
comma
id|start_ram
)paren
id|SYM_GEN_Z
c_func
(paren
id|u_short
comma
id|start_ram64
)paren
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *  Generates structure interface that contains &n; *  bus addresses within script A, B and Z.&n; */
DECL|struct|sym_fwa_ba
r_struct
id|sym_fwa_ba
(brace
id|SYM_GEN_FW_A
c_func
(paren
id|u32
)paren
)brace
suffix:semicolon
DECL|struct|sym_fwb_ba
r_struct
id|sym_fwb_ba
(brace
id|SYM_GEN_FW_B
c_func
(paren
id|u32
)paren
macro_line|#ifdef SYM_OPT_HANDLE_DIR_UNKNOWN
id|SYM_GEN_B
c_func
(paren
id|u32
comma
id|data_io
)paren
macro_line|#endif
id|SYM_GEN_B
c_func
(paren
id|u32
comma
id|start64
)paren
suffix:semicolon
DECL|member|SYM_GEN_B
id|SYM_GEN_B
c_func
(paren
id|u32
comma
id|pm_handle
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sym_fwz_ba
r_struct
id|sym_fwz_ba
(brace
id|SYM_GEN_FW_Z
c_func
(paren
id|u32
)paren
macro_line|#ifdef SYM_OPT_NO_BUS_MEMORY_MAPPING
id|SYM_GEN_Z
c_func
(paren
id|u32
comma
id|start_ram
)paren
id|SYM_GEN_Z
c_func
(paren
id|u32
comma
id|start_ram64
)paren
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|SYM_GEN_A
macro_line|#undef&t;SYM_GEN_A
DECL|macro|SYM_GEN_B
macro_line|#undef&t;SYM_GEN_B
DECL|macro|SYM_GEN_Z
macro_line|#undef&t;SYM_GEN_Z
multiline_comment|/*&n; *  Let cc know about the name of the controller data structure.&n; *  We need this for function prototype declarations just below.&n; */
r_struct
id|sym_hcb
suffix:semicolon
multiline_comment|/*&n; *  Generic structure that defines a firmware.&n; */
DECL|struct|sym_fw
r_struct
id|sym_fw
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Name we want to print out&t;*/
DECL|member|a_base
id|u32
op_star
id|a_base
suffix:semicolon
multiline_comment|/* Pointer to script A template&t;*/
DECL|member|a_size
r_int
id|a_size
suffix:semicolon
multiline_comment|/* Size of script A&t;&t;*/
r_struct
id|sym_fwa_ofs
DECL|member|a_ofs
op_star
id|a_ofs
suffix:semicolon
multiline_comment|/* Useful offsets in script A&t;*/
DECL|member|b_base
id|u32
op_star
id|b_base
suffix:semicolon
multiline_comment|/* Pointer to script B template&t;*/
DECL|member|b_size
r_int
id|b_size
suffix:semicolon
multiline_comment|/* Size of script B&t;&t;*/
r_struct
id|sym_fwb_ofs
DECL|member|b_ofs
op_star
id|b_ofs
suffix:semicolon
multiline_comment|/* Useful offsets in script B&t;*/
DECL|member|z_base
id|u32
op_star
id|z_base
suffix:semicolon
multiline_comment|/* Pointer to script Z template&t;*/
DECL|member|z_size
r_int
id|z_size
suffix:semicolon
multiline_comment|/* Size of script Z&t;&t;*/
r_struct
id|sym_fwz_ofs
DECL|member|z_ofs
op_star
id|z_ofs
suffix:semicolon
multiline_comment|/* Useful offsets in script Z&t;*/
multiline_comment|/* Setup and patch methods for this firmware */
DECL|member|setup
r_void
(paren
op_star
id|setup
)paren
(paren
r_struct
id|sym_hcb
op_star
comma
r_struct
id|sym_fw
op_star
)paren
suffix:semicolon
DECL|member|patch
r_void
(paren
op_star
id|patch
)paren
(paren
r_struct
id|sym_hcb
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Macro used to declare a firmware.&n; */
DECL|macro|SYM_FW_ENTRY
mdefine_line|#define SYM_FW_ENTRY(fw, name)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;name,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(u32 *) &amp;fw##a_scr, sizeof(fw##a_scr), &amp;fw##a_ofs,&t;&bslash;&n;&t;(u32 *) &amp;fw##b_scr, sizeof(fw##b_scr), &amp;fw##b_ofs,&t;&bslash;&n;&t;(u32 *) &amp;fw##z_scr, sizeof(fw##z_scr), &amp;fw##z_ofs,&t;&bslash;&n;&t;fw##_setup, fw##_patch&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; *  Macros used from the C code to get useful&n; *  SCRIPTS bus addresses.&n; */
DECL|macro|SCRIPTA_BA
mdefine_line|#define SCRIPTA_BA(np, label)&t;(np-&gt;fwa_bas.label)
DECL|macro|SCRIPTB_BA
mdefine_line|#define SCRIPTB_BA(np, label)&t;(np-&gt;fwb_bas.label)
DECL|macro|SCRIPTZ_BA
mdefine_line|#define SCRIPTZ_BA(np, label)&t;(np-&gt;fwz_bas.label)
multiline_comment|/*&n; *  Macros used by scripts definitions.&n; *&n; *  HADDR_1 generates a reference to a field of the controller data.&n; *  HADDR_2 generates a reference to a field of the controller data&n; *          with offset.&n; *  RADDR_1 generates a reference to a script processor register.&n; *  RADDR_2 generates a reference to a script processor register&n; *          with offset.&n; *  PADDR_A generates a reference to another part of script A.&n; *  PADDR_B generates a reference to another part of script B.&n; *&n; *  SYM_GEN_PADDR_A and SYM_GEN_PADDR_B are used to define respectively &n; *  the PADDR_A and PADDR_B macros for each firmware by setting argument &n; *  `s&squot; to the name of the corresponding structure.&n; *&n; *  SCR_DATA_ZERO is used to allocate a DWORD of data in scripts areas.&n; */
DECL|macro|RELOC_SOFTC
mdefine_line|#define&t;RELOC_SOFTC&t;0x40000000
DECL|macro|RELOC_LABEL_A
mdefine_line|#define&t;RELOC_LABEL_A&t;0x50000000
DECL|macro|RELOC_REGISTER
mdefine_line|#define&t;RELOC_REGISTER&t;0x60000000
DECL|macro|RELOC_LABEL_B
mdefine_line|#define&t;RELOC_LABEL_B&t;0x80000000
DECL|macro|RELOC_MASK
mdefine_line|#define&t;RELOC_MASK&t;0xf0000000
DECL|macro|HADDR_1
mdefine_line|#define&t;HADDR_1(label)&t;   (RELOC_SOFTC    | offsetof(struct sym_hcb, label))
DECL|macro|HADDR_2
mdefine_line|#define&t;HADDR_2(label,ofs) (RELOC_SOFTC    | &bslash;&n;&t;&t;&t;&t;(offsetof(struct sym_hcb, label)+(ofs)))
DECL|macro|RADDR_1
mdefine_line|#define&t;RADDR_1(label)&t;   (RELOC_REGISTER | REG(label))
DECL|macro|RADDR_2
mdefine_line|#define&t;RADDR_2(label,ofs) (RELOC_REGISTER | ((REG(label))+(ofs)))
DECL|macro|SYM_GEN_PADDR_A
mdefine_line|#define SYM_GEN_PADDR_A(s, label) (RELOC_LABEL_A  | offsetof(s, label))
DECL|macro|SYM_GEN_PADDR_B
mdefine_line|#define SYM_GEN_PADDR_B(s, label) (RELOC_LABEL_B  | offsetof(s, label))
DECL|macro|SCR_DATA_ZERO
mdefine_line|#define SCR_DATA_ZERO&t;0xf00ff00f
macro_line|#endif&t;/* SYM_FW_H */
eof
