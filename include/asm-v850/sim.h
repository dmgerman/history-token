multiline_comment|/*&n; * include/asm-v850/sim.h -- Machine-dependent defs for GDB v850e simulator&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SIM_H__
DECL|macro|__V850_SIM_H__
mdefine_line|#define __V850_SIM_H__
DECL|macro|CPU_ARCH
mdefine_line|#define CPU_ARCH&t;&t;&quot;v850e&quot;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&t;&quot;v850e&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&t;&quot;NEC V850E&quot;
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&t;&quot;gdb/v850e&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&t;&quot;GDB V850E simulator&quot;
multiline_comment|/* We use a weird value for RAM, not just 0, for testing purposes.&n;   These must match the values used in the linker script.  */
DECL|macro|RAM_ADDR
mdefine_line|#define RAM_ADDR&t;&t;0x8F000000
DECL|macro|RAM_SIZE
mdefine_line|#define RAM_SIZE&t;&t;0x01000000
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET &t;&t;RAM_ADDR
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* `R0 RAM&squot;, used for a few miscellaneous variables that must be&n;   accessible using a load instruction relative to R0.  On real&n;   processors, this usually is on-chip RAM, but here we just&n;   choose an arbitrary address that meets the above constraint.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;0xFFFFF000
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;&t;&t;24&t;/* Minimum supported frequency.  */
macro_line|#endif
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;&t;6
macro_line|#endif /* __V850_SIM_H__ */
eof
