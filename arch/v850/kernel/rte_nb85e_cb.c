multiline_comment|/*&n; * arch/v850/kernel/rte_nb85e_cb.c -- Midas labs RTE-V850E/NB85E-CB board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/v850e.h&gt;
macro_line|#include &lt;asm/rte_nb85e_cb.h&gt;
macro_line|#include &quot;mach.h&quot;
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
multiline_comment|/* Configure caching; some possible settings:&n;&n;&t;     BHC = 0x0000, DCC = 0x0000&t; -- all caching disabled&n;&t;     BHC = 0x0040, DCC = 0x0000&t; -- SDRAM: icache only&n;&t;     BHC = 0x0080, DCC = 0x0C00&t; -- SDRAM: write-back dcache only&n;&t;     BHC = 0x00C0, DCC = 0x0C00&t; -- SDRAM: icache + write-back dcache&n;&t;     BHC = 0x00C0, DCC = 0x0800&t; -- SDRAM: icache + write-thru dcache&n;&n;&t;   We can only cache SDRAM (we can&squot;t use cache SRAM because it&squot;s in&n;&t;   the same memory region as the on-chip RAM and I/O space).&n;&n;&t;   Unfortunately, the dcache seems to be buggy, so we only use the&n;&t;   icache for now.  */
id|v850e_cache_enable
(paren
l_int|0x0040
multiline_comment|/*BHC*/
comma
l_int|0x0003
multiline_comment|/*ICC*/
comma
l_int|0x0000
multiline_comment|/*DCC*/
)paren
suffix:semicolon
id|rte_cb_early_init
(paren
)paren
suffix:semicolon
)brace
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
multiline_comment|/* We just use SDRAM here.  */
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
multiline_comment|/* Reserve the memory used by the root filesystem image if it&squot;s&n;&t;   in SDRAM.  */
r_if
c_cond
(paren
id|root_fs_image_end
OG
id|root_fs_image_start
op_logical_and
id|root_fs_image_start
op_ge
id|SDRAM_ADDR
op_logical_and
id|root_fs_image_start
OL
(paren
id|SDRAM_ADDR
op_plus
id|SDRAM_SIZE
)paren
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
multiline_comment|/* Called before configuring an on-chip UART.  */
DECL|function|rte_nb85e_cb_uart_pre_configure
r_void
id|rte_nb85e_cb_uart_pre_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
(brace
multiline_comment|/* The RTE-NB85E-CB connects some general-purpose I/O pins on the&n;&t;   CPU to the RTS/CTS lines the UART&squot;s serial connection, as follows:&n;&t;   P00 = CTS (in), P01 = DSR (in), P02 = RTS (out), P03 = DTR (out). */
id|TEG_PORT0_PM
op_assign
l_int|0x03
suffix:semicolon
multiline_comment|/* P00 and P01 inputs, P02 and P03 outputs */
id|TEG_PORT0_IO
op_assign
l_int|0x03
suffix:semicolon
multiline_comment|/* Accept input */
multiline_comment|/* Do pre-configuration for the actual UART.  */
id|teg_uart_pre_configure
(paren
id|chan
comma
id|cflags
comma
id|baud
)paren
suffix:semicolon
)brace
DECL|function|mach_init_irqs
r_void
id|__init
id|mach_init_irqs
(paren
r_void
)paren
(brace
id|teg_init_irqs
(paren
)paren
suffix:semicolon
id|rte_cb_init_irqs
(paren
)paren
suffix:semicolon
)brace
eof
