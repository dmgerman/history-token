multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; * &n; *  File: &n; *      @(#)&t;pa/fp/fpu.h&t;&t;$Revision: 1.1 $&n; * &n; *  Purpose:&n; *      &lt;&lt;please update with a synopis of the functionality provided by this file&gt;&gt;&n; * &n; * &n; * END_DESC  &n;*/
macro_line|#ifdef __NO_PA_HDRS
id|PA
id|header
id|file
op_decrement
r_do
op_logical_neg
id|include
id|this
id|header
id|file
r_for
c_loop
id|non
op_minus
id|PA
id|builds
dot
macro_line|#endif
macro_line|#ifndef _MACHINE_FPU_INCLUDED /* allows multiple inclusion */
DECL|macro|_MACHINE_FPU_INCLUDED
mdefine_line|#define _MACHINE_FPU_INCLUDED
macro_line|#if 0
macro_line|#ifndef _SYS_STDSYMS_INCLUDED
macro_line|#    include &lt;sys/stdsyms.h&gt;
macro_line|#endif   /* _SYS_STDSYMS_INCLUDED  */
macro_line|#include  &lt;machine/pdc/pdc_rqsts.h&gt;
macro_line|#endif
DECL|macro|PA83_FPU_FLAG
mdefine_line|#define PA83_FPU_FLAG    0x00000001
DECL|macro|PA89_FPU_FLAG
mdefine_line|#define PA89_FPU_FLAG    0x00000002
DECL|macro|PA2_0_FPU_FLAG
mdefine_line|#define PA2_0_FPU_FLAG   0x00000010
DECL|macro|TIMEX_EXTEN_FLAG
mdefine_line|#define TIMEX_EXTEN_FLAG 0x00000004
DECL|macro|ROLEX_EXTEN_FLAG
mdefine_line|#define ROLEX_EXTEN_FLAG 0x00000008
DECL|macro|COPR_FP
mdefine_line|#define COPR_FP &t;0x00000080&t;/* Floating point -- Coprocessor 0 */
DECL|macro|SFU_MPY_DIVIDE
mdefine_line|#define SFU_MPY_DIVIDE&t;0x00008000&t;/* Multiply/Divide __ SFU 0 */
DECL|macro|EM_FPU_TYPE_OFFSET
mdefine_line|#define EM_FPU_TYPE_OFFSET 272
multiline_comment|/* version of EMULATION software for COPR,0,0 instruction */
DECL|macro|EMULATION_VERSION
mdefine_line|#define EMULATION_VERSION 4
multiline_comment|/*&n; * The only was to differeniate between TIMEX and ROLEX (or PCX-S and PCX-T)&n; * is thorough the potential type field from the PDC_MODEL call.  The &n; * following flags are used at assist this differeniation.&n; */
DECL|macro|ROLEX_POTENTIAL_KEY_FLAGS
mdefine_line|#define ROLEX_POTENTIAL_KEY_FLAGS&t;PDC_MODEL_CPU_KEY_WORD_TO_IO
DECL|macro|TIMEX_POTENTIAL_KEY_FLAGS
mdefine_line|#define TIMEX_POTENTIAL_KEY_FLAGS&t;(PDC_MODEL_CPU_KEY_QUAD_STORE | &bslash;&n;&t;&t;&t;&t;&t; PDC_MODEL_CPU_KEY_RECIP_SQRT)
macro_line|#endif /* ! _MACHINE_FPU_INCLUDED */
eof
