macro_line|#ifndef _ASM_IA64_SN_SIMULATOR_H
DECL|macro|_ASM_IA64_SN_SIMULATOR_H
mdefine_line|#define _ASM_IA64_SN_SIMULATOR_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; * Copyright (C) 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN_SIM
DECL|macro|SNMAGIC
mdefine_line|#define SNMAGIC 0xaeeeeeee8badbeefL
DECL|macro|IS_RUNNING_ON_SIMULATOR
mdefine_line|#define IS_RUNNING_ON_SIMULATOR() ({long sn; asm(&quot;mov %0=cpuid[%1]&quot; : &quot;=r&quot;(sn) : &quot;r&quot;(2)); sn == SNMAGIC;})
DECL|macro|SIMULATOR_SLEEP
mdefine_line|#define SIMULATOR_SLEEP()&t;asm(&quot;nop.i 0x8beef&quot;)
macro_line|#else
DECL|macro|IS_RUNNING_ON_SIMULATOR
mdefine_line|#define IS_RUNNING_ON_SIMULATOR()&t;(0)
DECL|macro|SIMULATOR_SLEEP
mdefine_line|#define SIMULATOR_SLEEP()
macro_line|#endif
macro_line|#endif /* _ASM_IA64_SN_SIMULATOR_H */
eof
