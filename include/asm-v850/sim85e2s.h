multiline_comment|/*&n; * include/asm-v850/sim85e2s.h -- Machine-dependent defs for&n; *&t;V850E2 RTL simulator&n; *&n; *  Copyright (C) 2003  NEC Electronics Corporation&n; *  Copyright (C) 2003  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SIM85E2S_H__
DECL|macro|__V850_SIM85E2S_H__
mdefine_line|#define __V850_SIM85E2S_H__
macro_line|#include &lt;asm/sim85e2.h&gt;&t;/* Use generic sim85e2 settings.  */
macro_line|#if 0
macro_line|#include &lt;asm/v850e2_cache.h&gt;&t;/* + cache */
macro_line|#endif
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;v850e2&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E2&quot;
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&quot;sim85e2s&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&quot;SIM85E2S V850E2 simulator&quot;
macro_line|#endif /* __V850_SIM85E2S_H__ */
eof
