macro_line|#ifndef _DWARF2_H
DECL|macro|_DWARF2_H
mdefine_line|#define _DWARF2_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#warning &quot;asm/dwarf2.h should be only included in pure assembly files&quot;
macro_line|#endif
multiline_comment|/* &n;   Macros for dwarf2 CFI unwind table entries.&n;   See &quot;as.info&quot; for details on these pseudo ops. Unfortunately &n;   they are only supported in very new binutils, so define them &n;   away for older version. &n; */
macro_line|#ifdef CONFIG_DEBUG_INFO
DECL|macro|CFI_STARTPROC
mdefine_line|#define CFI_STARTPROC .cfi_startproc
DECL|macro|CFI_ENDPROC
mdefine_line|#define CFI_ENDPROC .cfi_endproc
DECL|macro|CFI_DEF_CFA
mdefine_line|#define CFI_DEF_CFA .cfi_def_cfa
DECL|macro|CFI_DEF_CFA_REGISTER
mdefine_line|#define CFI_DEF_CFA_REGISTER .cfi_def_cfa_register
DECL|macro|CFI_DEF_CFA_OFFSET
mdefine_line|#define CFI_DEF_CFA_OFFSET .cfi_def_cfa_offset
DECL|macro|CFI_ADJUST_CFA_OFFSET
mdefine_line|#define CFI_ADJUST_CFA_OFFSET .cfi_adjust_cfa_offset
DECL|macro|CFI_OFFSET
mdefine_line|#define CFI_OFFSET .cfi_offset
DECL|macro|CFI_REL_OFFSET
mdefine_line|#define CFI_REL_OFFSET .cfi_rel_offset
macro_line|#else
multiline_comment|/* use assembler line comment character # to ignore the arguments. */
DECL|macro|CFI_STARTPROC
mdefine_line|#define CFI_STARTPROC&t;#
DECL|macro|CFI_ENDPROC
mdefine_line|#define CFI_ENDPROC&t;#
DECL|macro|CFI_DEF_CFA
mdefine_line|#define CFI_DEF_CFA&t;#
DECL|macro|CFI_DEF_CFA_REGISTER
mdefine_line|#define CFI_DEF_CFA_REGISTER&t;#
DECL|macro|CFI_DEF_CFA_OFFSET
mdefine_line|#define CFI_DEF_CFA_OFFSET&t;#
DECL|macro|CFI_ADJUST_CFA_OFFSET
mdefine_line|#define CFI_ADJUST_CFA_OFFSET&t;#
DECL|macro|CFI_OFFSET
mdefine_line|#define CFI_OFFSET&t;#
DECL|macro|CFI_REL_OFFSET
mdefine_line|#define CFI_REL_OFFSET&t;#
macro_line|#endif
macro_line|#endif
eof
