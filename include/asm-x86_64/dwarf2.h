macro_line|#ifndef _DWARF2_H
DECL|macro|_DWARF2_H
mdefine_line|#define _DWARF2_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#warning &quot;asm/dwarf2.h should be only included in pure assembly files&quot;
macro_line|#endif
multiline_comment|/* &n;   Macros for dwarf2 CFI unwind table entries.&n;   See &quot;as.info&quot; for details on these pseudo ops. Unfortunately &n;   they are only supported in very new binutils, so define them &n;   away for older version. &n; */
macro_line|#ifdef CONFIG_CFI_BINUTILS
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
macro_line|#ifdef __ASSEMBLY__
dot
id|macro
id|nothing
dot
id|endm
dot
id|macro
id|nothing1
id|a
dot
id|endm
dot
id|macro
id|nothing2
id|a
comma
id|b
dot
id|endm
macro_line|#endif
DECL|macro|CFI_STARTPROC
mdefine_line|#define CFI_STARTPROC nothing
DECL|macro|CFI_ENDPROC
mdefine_line|#define CFI_ENDPROC nothing
DECL|macro|CFI_DEF_CFA
mdefine_line|#define CFI_DEF_CFA nothing2
DECL|macro|CFI_DEF_CFA_REGISTER
mdefine_line|#define CFI_DEF_CFA_REGISTER nothing1
DECL|macro|CFI_DEF_CFA_OFFSET
mdefine_line|#define CFI_DEF_CFA_OFFSET nothing1
DECL|macro|CFI_ADJUST_CFA_OFFSET
mdefine_line|#define CFI_ADJUST_CFA_OFFSET nothing1
DECL|macro|CFI_OFFSET
mdefine_line|#define CFI_OFFSET nothing2
DECL|macro|CFI_REL_OFFSET
mdefine_line|#define CFI_REL_OFFSET nothing2
macro_line|#endif
macro_line|#endif
eof
