multiline_comment|/* &n; *   arch/ppc/kernel/mol.h&n; *   &n; *&t;&lt;mol.h&gt;&n; *&t;&n; *&t;Mac-on-Linux hook macros&n; *&t;&lt;http://www.maconlinux.org&gt;&n; *   &n; *   Copyright (C) 2000 Samuel Rydh (samuel@ibrium.se)&n; *   &n; *   This program is free software; you can redistribute it and/or&n; *   modify it under the terms of the GNU General Public License&n; *   as published by the Free Software Foundation&n; *   &n; */
macro_line|#ifndef _PPC_KERNEL_MOL
DECL|macro|_PPC_KERNEL_MOL
mdefine_line|#define _PPC_KERNEL_MOL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MOL
DECL|macro|MOL_INTERFACE_VERSION
mdefine_line|#define MOL_INTERFACE_VERSION&t;&t;3
DECL|macro|MOL_HOOK
mdefine_line|#define MOL_HOOK(hook_num)&t;&t;&t;&t;&t;&bslash;&n;&t;lwz&t;r0,(mol_interface + 4 * hook_num + 4)@l(0); &t;&bslash;&n;&t;cmpwi&t;cr1,r0,0; &t;&t;&t;&t;&t;&bslash;&n;&t;beq+&t;cr1,777f; &t;&t;&t;&t;&t;&bslash;&n;&t;mtctr&t;r0; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;bctrl; &t;&t;&t;&t;&t;&t;&t;&bslash;&n;777:&t;lwz&t;r0,GPR0(r21)
DECL|macro|MOL_HOOK_RESTORE
mdefine_line|#define MOL_HOOK_RESTORE(hook_num)&t;&t;&t;&t;&bslash;&n;&t;mfcr&t;r2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MOL_HOOK(hook_num);&t;&t;&t;&t;&t;&bslash;&n;&t;mtcrf&t;0x80,r2;&t;&t;&t;&t;&t;&bslash;&n;&t;lwz&t;r2,_CTR(r21);&t;&t;&t;&t;&t;&bslash;&n;&t;mtctr&t;r2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;lwz&t;r2,GPR2(r21)
DECL|macro|MOL_HOOK_MMU
mdefine_line|#define MOL_HOOK_MMU(hook_num, scr)&t;&t;&t;&t;&bslash;&n;&t;lis&t;scr,(mol_interface + 4 * hook_num + 4)@ha;&t;&bslash;&n;&t;lwz&t;scr,(mol_interface + 4 * hook_num + 4)@l(scr);&t;&bslash;&n;&t;cmpwi&t;cr1,scr,0;&t;&t;&t;&t;&t;&bslash;&n;&t;beq+&t;cr1,778f;&t;&t;&t;&t;&t;&bslash;&n;&t;mtctr&t;scr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bctrl;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;778:
DECL|macro|MOL_HOOK_TLBMISS
mdefine_line|#define MOL_HOOK_TLBMISS(hook_num)&t;&t;&t;&t;&bslash;&n;&t;lwz&t;r0,(mol_interface + 4 * hook_num + 4)@l(0);&t;&bslash;&n;&t;cmpwi&t;r0,0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;beq+&t;779f;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mflr&t;r3;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mtlr&t;r0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;blrl;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mtlr&t;r3;&t;&t;&t;&t;&t;&t;&bslash;&n;779:
macro_line|#else
DECL|macro|MOL_HOOK
mdefine_line|#define MOL_HOOK(num)
DECL|macro|MOL_HOOK_RESTORE
mdefine_line|#define MOL_HOOK_RESTORE(num)
DECL|macro|MOL_HOOK_MMU
mdefine_line|#define MOL_HOOK_MMU(num, scr)
DECL|macro|MOL_HOOK_TLBMISS
mdefine_line|#define MOL_HOOK_TLBMISS(num)
macro_line|#endif
macro_line|#endif   /* _PPC_KERNEL_MOL */
eof
