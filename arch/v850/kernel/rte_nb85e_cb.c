multiline_comment|/*&n; * arch/v850/kernel/rte_nb85e_cb.c -- Midas labs RTE-V850E/NB85E-CB board&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/nb85e.h&gt;
macro_line|#include &lt;asm/rte_nb85e_cb.h&gt;
macro_line|#include &quot;mach.h&quot;
DECL|function|mach_get_physical_ram
r_void
id|__init
id|mach_get_physical_ram
(paren
r_int
r_int
op_star
id|ram_start
comma
r_int
r_int
op_star
id|ram_len
)paren
(brace
multiline_comment|/* We just use SDRAM here; the kernel itself is in SRAM.  */
op_star
id|ram_start
op_assign
id|SDRAM_ADDR
suffix:semicolon
op_star
id|ram_len
op_assign
id|SDRAM_SIZE
suffix:semicolon
)brace
DECL|function|mach_reserve_bootmem
r_void
id|__init
id|mach_reserve_bootmem
(paren
)paren
(brace
r_extern
r_char
id|_root_fs_image_start
comma
id|_root_fs_image_end
suffix:semicolon
id|u32
id|root_fs_image_start
op_assign
(paren
id|u32
)paren
op_amp
id|_root_fs_image_start
suffix:semicolon
id|u32
id|root_fs_image_end
op_assign
(paren
id|u32
)paren
op_amp
id|_root_fs_image_end
suffix:semicolon
multiline_comment|/* Reserve the memory used by the root filesystem image if it&squot;s&n;&t;   in RAM.  */
r_if
c_cond
(paren
id|root_fs_image_start
op_ge
id|RAM_START
op_logical_and
id|root_fs_image_start
OL
id|RAM_END
)paren
id|reserve_bootmem
(paren
id|root_fs_image_start
comma
id|root_fs_image_end
op_minus
id|root_fs_image_start
)paren
suffix:semicolon
)brace
DECL|function|mach_gettimeofday
r_void
id|mach_gettimeofday
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
id|tv-&gt;tv_sec
op_assign
l_int|0
suffix:semicolon
id|tv-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
eof
