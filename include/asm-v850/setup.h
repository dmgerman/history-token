multiline_comment|/*&n; * include/asm-v850/setup.h&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SETUP_H__
DECL|macro|__V850_SETUP_H__
mdefine_line|#define __V850_SETUP_H__
multiline_comment|/* Linux/v850 platforms.  This corresponds roughly to what the outside&n;   the CPU looks like.  */
DECL|macro|MACH_SIM
mdefine_line|#define MACH_SIM&t;1&t;/* GDB architectural simulator */
multiline_comment|/* v850 cpu architectures.  This is what a user-program would be&n;   concerned with.  */
DECL|macro|CPU_ARCH_V850E
mdefine_line|#define CPU_ARCH_V850E&t;1
DECL|macro|CPU_ARCH_V850E2
mdefine_line|#define CPU_ARCH_V850E2&t;2
multiline_comment|/* v850 cpu `cores&squot;.  These are system-level extensions to the basic CPU,&n;   defining such things as interrupt-handling.  */
DECL|macro|CPU_CORE_NB85E
mdefine_line|#define CPU_CORE_NB85E&t;1
DECL|macro|CPU_CORE_NB85ET
mdefine_line|#define CPU_CORE_NB85ET&t;2
DECL|macro|CPU_CORE_NU85E
mdefine_line|#define CPU_CORE_NU85E&t;3
DECL|macro|CPU_CORE_NU85ET
mdefine_line|#define CPU_CORE_NU85ET&t;4
multiline_comment|/* Specific v850 cpu chips.  These each incorporate a `core&squot;, and add&n;   varions peripheral services.  */
DECL|macro|CPU_CHIP_MA1
mdefine_line|#define CPU_CHIP_MA1&t;1
macro_line|#endif /* __V850_SETUP_H__ */
eof
