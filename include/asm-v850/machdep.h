multiline_comment|/*&n; * include/asm-v850/machdep.h -- Machine-dependent definitions&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_MACHDEP_H__
DECL|macro|__V850_MACHDEP_H__
mdefine_line|#define __V850_MACHDEP_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* chips */
macro_line|#ifdef CONFIG_V850E_MA1
macro_line|#include &lt;asm/ma1.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E_ME2
macro_line|#include &lt;asm/me2.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E_TEG
macro_line|#include &lt;asm/teg.h&gt;
macro_line|#endif
multiline_comment|/* These are both chips _and_ platforms, so put them in the middle... */
macro_line|#ifdef CONFIG_V850E2_ANNA
macro_line|#include &lt;asm/anna.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E_AS85EP1
macro_line|#include &lt;asm/as85ep1.h&gt;
macro_line|#endif
multiline_comment|/* platforms */
macro_line|#ifdef CONFIG_RTE_CB_MA1
macro_line|#include &lt;asm/rte_ma1_cb.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RTE_CB_ME2
macro_line|#include &lt;asm/rte_me2_cb.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RTE_CB_NB85E
macro_line|#include &lt;asm/rte_nb85e_cb.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E_SIM
macro_line|#include &lt;asm/sim.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E2_SIM85E2C
macro_line|#include &lt;asm/sim85e2c.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E2_SIM85E2S
macro_line|#include &lt;asm/sim85e2s.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_V850E2_FPGA85E2C
macro_line|#include &lt;asm/fpga85e2c.h&gt;
macro_line|#endif
macro_line|#endif /* __V850_MACHDEP_H__ */
eof
