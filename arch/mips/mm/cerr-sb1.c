multiline_comment|/*&n; * Copyright (C) 2001,2002,2003 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#ifndef CONFIG_SIBYTE_BUS_WATCHER
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_scd.h&gt;
macro_line|#endif
multiline_comment|/* SB1 definitions */
multiline_comment|/* XXX should come from config1 XXX */
DECL|macro|SB1_CACHE_INDEX_MASK
mdefine_line|#define SB1_CACHE_INDEX_MASK   0x1fe0
DECL|macro|CP0_ERRCTL_RECOVERABLE
mdefine_line|#define CP0_ERRCTL_RECOVERABLE (1 &lt;&lt; 31)
DECL|macro|CP0_ERRCTL_DCACHE
mdefine_line|#define CP0_ERRCTL_DCACHE      (1 &lt;&lt; 30)
DECL|macro|CP0_ERRCTL_ICACHE
mdefine_line|#define CP0_ERRCTL_ICACHE      (1 &lt;&lt; 29)
DECL|macro|CP0_ERRCTL_MULTIBUS
mdefine_line|#define CP0_ERRCTL_MULTIBUS    (1 &lt;&lt; 23)
DECL|macro|CP0_ERRCTL_MC_TLB
mdefine_line|#define CP0_ERRCTL_MC_TLB      (1 &lt;&lt; 15)
DECL|macro|CP0_ERRCTL_MC_TIMEOUT
mdefine_line|#define CP0_ERRCTL_MC_TIMEOUT  (1 &lt;&lt; 14)
DECL|macro|CP0_CERRI_TAG_PARITY
mdefine_line|#define CP0_CERRI_TAG_PARITY   (1 &lt;&lt; 29)
DECL|macro|CP0_CERRI_DATA_PARITY
mdefine_line|#define CP0_CERRI_DATA_PARITY  (1 &lt;&lt; 28)
DECL|macro|CP0_CERRI_EXTERNAL
mdefine_line|#define CP0_CERRI_EXTERNAL     (1 &lt;&lt; 26)
DECL|macro|CP0_CERRI_IDX_VALID
mdefine_line|#define CP0_CERRI_IDX_VALID(c) (!((c) &amp; CP0_CERRI_EXTERNAL))
DECL|macro|CP0_CERRI_DATA
mdefine_line|#define CP0_CERRI_DATA         (CP0_CERRI_DATA_PARITY)
DECL|macro|CP0_CERRD_MULTIPLE
mdefine_line|#define CP0_CERRD_MULTIPLE     (1 &lt;&lt; 31)
DECL|macro|CP0_CERRD_TAG_STATE
mdefine_line|#define CP0_CERRD_TAG_STATE    (1 &lt;&lt; 30)
DECL|macro|CP0_CERRD_TAG_ADDRESS
mdefine_line|#define CP0_CERRD_TAG_ADDRESS  (1 &lt;&lt; 29)
DECL|macro|CP0_CERRD_DATA_SBE
mdefine_line|#define CP0_CERRD_DATA_SBE     (1 &lt;&lt; 28)
DECL|macro|CP0_CERRD_DATA_DBE
mdefine_line|#define CP0_CERRD_DATA_DBE     (1 &lt;&lt; 27)
DECL|macro|CP0_CERRD_EXTERNAL
mdefine_line|#define CP0_CERRD_EXTERNAL     (1 &lt;&lt; 26)
DECL|macro|CP0_CERRD_LOAD
mdefine_line|#define CP0_CERRD_LOAD         (1 &lt;&lt; 25)
DECL|macro|CP0_CERRD_STORE
mdefine_line|#define CP0_CERRD_STORE        (1 &lt;&lt; 24)
DECL|macro|CP0_CERRD_FILLWB
mdefine_line|#define CP0_CERRD_FILLWB       (1 &lt;&lt; 23)
DECL|macro|CP0_CERRD_COHERENCY
mdefine_line|#define CP0_CERRD_COHERENCY    (1 &lt;&lt; 22)
DECL|macro|CP0_CERRD_DUPTAG
mdefine_line|#define CP0_CERRD_DUPTAG       (1 &lt;&lt; 21)
DECL|macro|CP0_CERRD_DPA_VALID
mdefine_line|#define CP0_CERRD_DPA_VALID(c) (!((c) &amp; CP0_CERRD_EXTERNAL))
DECL|macro|CP0_CERRD_IDX_VALID
mdefine_line|#define CP0_CERRD_IDX_VALID(c) &bslash;&n;   (((c) &amp; (CP0_CERRD_LOAD | CP0_CERRD_STORE)) ? (!((c) &amp; CP0_CERRD_EXTERNAL)) : 0)
DECL|macro|CP0_CERRD_CAUSES
mdefine_line|#define CP0_CERRD_CAUSES &bslash;&n;   (CP0_CERRD_LOAD | CP0_CERRD_STORE | CP0_CERRD_FILLWB | CP0_CERRD_COHERENCY | CP0_CERRD_DUPTAG)
DECL|macro|CP0_CERRD_TYPES
mdefine_line|#define CP0_CERRD_TYPES &bslash;&n;   (CP0_CERRD_TAG_STATE | CP0_CERRD_TAG_ADDRESS | CP0_CERRD_DATA_SBE | CP0_CERRD_DATA_DBE | CP0_CERRD_EXTERNAL)
DECL|macro|CP0_CERRD_DATA
mdefine_line|#define CP0_CERRD_DATA         (CP0_CERRD_DATA_SBE | CP0_CERRD_DATA_DBE)
r_static
r_uint32
id|extract_ic
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|data
)paren
suffix:semicolon
r_static
r_uint32
id|extract_dc
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|data
)paren
suffix:semicolon
DECL|function|breakout_errctl
r_static
r_inline
r_void
id|breakout_errctl
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
id|CP0_ERRCTL_RECOVERABLE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; recoverable&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_ERRCTL_DCACHE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; dcache&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_ERRCTL_ICACHE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; icache&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_ERRCTL_MULTIBUS
)paren
id|prom_printf
c_func
(paren
l_string|&quot; multiple-buserr&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|breakout_cerri
r_static
r_inline
r_void
id|breakout_cerri
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRI_TAG_PARITY
)paren
id|prom_printf
c_func
(paren
l_string|&quot; tag-parity&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRI_DATA_PARITY
)paren
id|prom_printf
c_func
(paren
l_string|&quot; data-parity&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRI_EXTERNAL
)paren
id|prom_printf
c_func
(paren
l_string|&quot; external&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|breakout_cerrd
r_static
r_inline
r_void
id|breakout_cerrd
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_switch
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_CAUSES
)paren
(brace
r_case
id|CP0_CERRD_LOAD
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot; load,&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CP0_CERRD_STORE
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot; store,&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CP0_CERRD_FILLWB
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot; fill/wb,&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CP0_CERRD_COHERENCY
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot; coherency,&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CP0_CERRD_DUPTAG
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot; duptags,&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot; NO CAUSE,&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|val
op_amp
id|CP0_CERRD_TYPES
)paren
)paren
id|prom_printf
c_func
(paren
l_string|&quot; NO TYPE&quot;
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_MULTIPLE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; multi-err&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_TAG_STATE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; tag-state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_TAG_ADDRESS
)paren
id|prom_printf
c_func
(paren
l_string|&quot; tag-address&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_DATA_SBE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; data-SBE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_DATA_DBE
)paren
id|prom_printf
c_func
(paren
l_string|&quot; data-DBE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|CP0_CERRD_EXTERNAL
)paren
id|prom_printf
c_func
(paren
l_string|&quot; external&quot;
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_SIBYTE_BUS_WATCHER
DECL|function|check_bus_watcher
r_static
r_void
id|check_bus_watcher
c_func
(paren
r_void
)paren
(brace
r_uint32
id|status
comma
id|l2_err
comma
id|memio_err
suffix:semicolon
multiline_comment|/* Destructive read, clears register and interrupt */
id|status
op_assign
id|csr_in32
c_func
(paren
id|IOADDR
c_func
(paren
id|A_SCD_BUS_ERR_STATUS
)paren
)paren
suffix:semicolon
multiline_comment|/* Bit 31 is always on, but there&squot;s no #define for that */
r_if
c_cond
(paren
id|status
op_amp
op_complement
(paren
l_int|1UL
op_lshift
l_int|31
)paren
)paren
(brace
id|l2_err
op_assign
id|csr_in32
c_func
(paren
id|IOADDR
c_func
(paren
id|A_BUS_L2_ERRORS
)paren
)paren
suffix:semicolon
id|memio_err
op_assign
id|csr_in32
c_func
(paren
id|IOADDR
c_func
(paren
id|A_BUS_MEM_IO_ERRORS
)paren
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Bus watcher error counters: %08x %08x&bslash;n&quot;
comma
id|l2_err
comma
id|memio_err
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;nLast recorded signature:&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Request %02x from %d, answered by %d with Dcode %d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
(paren
id|G_SCD_BERR_TID
c_func
(paren
id|status
)paren
op_amp
l_int|0x3f
)paren
comma
(paren
r_int
)paren
(paren
id|G_SCD_BERR_TID
c_func
(paren
id|status
)paren
op_rshift
l_int|6
)paren
comma
(paren
r_int
)paren
id|G_SCD_BERR_RID
c_func
(paren
id|status
)paren
comma
(paren
r_int
)paren
id|G_SCD_BERR_DCODE
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Bus watcher indicates no error&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#else                                                    
r_extern
r_void
id|check_bus_watcher
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif                                          
DECL|function|sb1_cache_error
id|asmlinkage
r_void
id|sb1_cache_error
c_func
(paren
r_void
)paren
(brace
r_uint64
id|cerr_dpa
suffix:semicolon
r_uint32
id|errctl
comma
id|cerr_i
comma
id|cerr_d
comma
id|dpalo
comma
id|dpahi
comma
id|eepc
comma
id|res
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Cache error exception on CPU %x:&bslash;n&quot;
comma
(paren
id|read_c0_prid
c_func
(paren
)paren
op_rshift
l_int|25
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;push&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;mips64&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noat&bslash;n&bslash;t&quot;
l_string|&quot;&t;mfc0&t;%0, $26&bslash;n&bslash;t&quot;
l_string|&quot;&t;mfc0&t;%1, $27&bslash;n&bslash;t&quot;
l_string|&quot;&t;mfc0&t;%2, $27, 1&bslash;n&bslash;t&quot;
l_string|&quot;&t;dmfc0&t;$1, $27, 3&bslash;n&bslash;t&quot;
l_string|&quot;&t;dsrl32&t;%3, $1, 0 &bslash;n&bslash;t&quot;
l_string|&quot;&t;sll&t;%4, $1, 0 &bslash;n&bslash;t&quot;
l_string|&quot;&t;mfc0&t;%5, $30&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|errctl
)paren
comma
l_string|&quot;=r&quot;
(paren
id|cerr_i
)paren
comma
l_string|&quot;=r&quot;
(paren
id|cerr_d
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dpahi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dpalo
)paren
comma
l_string|&quot;=r&quot;
(paren
id|eepc
)paren
)paren
suffix:semicolon
id|cerr_dpa
op_assign
(paren
(paren
(paren
r_uint64
)paren
id|dpahi
)paren
op_lshift
l_int|32
)paren
op_or
id|dpalo
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot; c0_errorepc ==   %08x&bslash;n&quot;
comma
id|eepc
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot; c0_errctl   ==   %08x&quot;
comma
id|errctl
)paren
suffix:semicolon
id|breakout_errctl
c_func
(paren
id|errctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errctl
op_amp
id|CP0_ERRCTL_ICACHE
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot; c0_cerr_i   ==   %08x&quot;
comma
id|cerr_i
)paren
suffix:semicolon
id|breakout_cerri
c_func
(paren
id|cerr_i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CP0_CERRI_IDX_VALID
c_func
(paren
id|cerr_i
)paren
)paren
(brace
multiline_comment|/* Check index of EPC, allowing for delay slot */
r_if
c_cond
(paren
(paren
(paren
id|eepc
op_amp
id|SB1_CACHE_INDEX_MASK
)paren
op_ne
(paren
id|cerr_i
op_amp
id|SB1_CACHE_INDEX_MASK
)paren
)paren
op_logical_and
(paren
(paren
id|eepc
op_amp
id|SB1_CACHE_INDEX_MASK
)paren
op_ne
(paren
(paren
id|cerr_i
op_amp
id|SB1_CACHE_INDEX_MASK
)paren
op_minus
l_int|4
)paren
)paren
)paren
id|prom_printf
c_func
(paren
l_string|&quot; cerr_i idx doesn&squot;t match eepc&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|res
op_assign
id|extract_ic
c_func
(paren
id|cerr_i
op_amp
id|SB1_CACHE_INDEX_MASK
comma
(paren
id|cerr_i
op_amp
id|CP0_CERRI_DATA
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|res
op_amp
id|cerr_i
)paren
)paren
id|prom_printf
c_func
(paren
l_string|&quot;...didn&squot;t see indicated icache problem&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|errctl
op_amp
id|CP0_ERRCTL_DCACHE
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot; c0_cerr_d   ==   %08x&quot;
comma
id|cerr_d
)paren
suffix:semicolon
id|breakout_cerrd
c_func
(paren
id|cerr_d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CP0_CERRD_DPA_VALID
c_func
(paren
id|cerr_d
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot; c0_cerr_dpa == %010llx&bslash;n&quot;
comma
id|cerr_dpa
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CP0_CERRD_IDX_VALID
c_func
(paren
id|cerr_d
)paren
)paren
(brace
id|res
op_assign
id|extract_dc
c_func
(paren
id|cerr_dpa
op_amp
id|SB1_CACHE_INDEX_MASK
comma
(paren
id|cerr_d
op_amp
id|CP0_CERRD_DATA
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|res
op_amp
id|cerr_d
)paren
)paren
id|prom_printf
c_func
(paren
l_string|&quot;...didn&squot;t see indicated dcache problem&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|cerr_dpa
op_amp
id|SB1_CACHE_INDEX_MASK
)paren
op_ne
(paren
id|cerr_d
op_amp
id|SB1_CACHE_INDEX_MASK
)paren
)paren
id|prom_printf
c_func
(paren
l_string|&quot; cerr_d idx doesn&squot;t match cerr_dpa&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|res
op_assign
id|extract_dc
c_func
(paren
id|cerr_d
op_amp
id|SB1_CACHE_INDEX_MASK
comma
(paren
id|cerr_d
op_amp
id|CP0_CERRD_DATA
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|res
op_amp
id|cerr_d
)paren
)paren
id|prom_printf
c_func
(paren
l_string|&quot;...didn&squot;t see indicated problem&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
id|check_bus_watcher
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This tends to make things get really ugly; let&squot;s just stall instead.&n;&t; *    panic(&quot;Can&squot;t handle the cache error!&quot;);&n;&t; */
)brace
multiline_comment|/* Parity lookup table. */
DECL|variable|parity
r_static
r_const
r_uint8
id|parity
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Masks to select bits for Hamming parity, mask_72_64[i] for bit[i] */
DECL|variable|mask_72_64
r_static
r_const
r_uint64
id|mask_72_64
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x0738C808099264FFULL
comma
l_int|0x38C808099264FF07ULL
comma
l_int|0xC808099264FF0738ULL
comma
l_int|0x08099264FF0738C8ULL
comma
l_int|0x099264FF0738C808ULL
comma
l_int|0x9264FF0738C80809ULL
comma
l_int|0x64FF0738C8080992ULL
comma
l_int|0xFF0738C808099264ULL
)brace
suffix:semicolon
multiline_comment|/* Calculate the parity on a range of bits */
DECL|function|range_parity
r_static
r_char
id|range_parity
c_func
(paren
r_uint64
id|dword
comma
r_int
id|max
comma
r_int
id|min
)paren
(brace
r_char
id|parity
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dword
op_rshift_assign
id|min
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|max
op_minus
id|min
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|dword
op_amp
l_int|0x1
)paren
id|parity
op_assign
op_logical_neg
id|parity
suffix:semicolon
id|dword
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|parity
suffix:semicolon
)brace
multiline_comment|/* Calculate the 4-bit even byte-parity for an instruction */
DECL|function|inst_parity
r_static
r_int
r_char
id|inst_parity
c_func
(paren
r_uint32
id|word
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_char
id|parity
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
suffix:semicolon
id|j
op_increment
)paren
(brace
r_char
id|byte_parity
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|word
op_amp
l_int|0x80000000
)paren
id|byte_parity
op_assign
op_logical_neg
id|byte_parity
suffix:semicolon
id|word
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|parity
op_lshift_assign
l_int|1
suffix:semicolon
id|parity
op_or_assign
id|byte_parity
suffix:semicolon
)brace
r_return
id|parity
suffix:semicolon
)brace
DECL|function|extract_ic
r_static
r_uint32
id|extract_ic
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
r_int
id|way
suffix:semicolon
r_int
id|valid
suffix:semicolon
r_uint64
id|taglo
comma
id|va
comma
id|tlo_tmp
suffix:semicolon
r_uint32
id|taghi
comma
id|taglolo
comma
id|taglohi
suffix:semicolon
r_uint8
id|lru
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Icache index 0x%04x  &quot;
comma
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|way
op_assign
l_int|0
suffix:semicolon
id|way
OL
l_int|4
suffix:semicolon
id|way
op_increment
)paren
(brace
multiline_comment|/* Index-load-tag-I */
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;push&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noreorder&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;mips64&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noat&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;cache&t;4, 0(%3)&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;mfc0&t;%0, $29&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;dmfc0&t;$1, $28&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;dsrl32&t;%1, $1, 0&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;sll&t;%2, $1, 0&t;&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|taghi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|taglohi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|taglolo
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|way
op_lshift
l_int|13
)paren
op_or
id|addr
)paren
)paren
suffix:semicolon
id|taglo
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|taglohi
op_lshift
l_int|32
)paren
op_or
id|taglolo
suffix:semicolon
r_if
c_cond
(paren
id|way
op_eq
l_int|0
)paren
(brace
id|lru
op_assign
(paren
id|taghi
op_rshift
l_int|14
)paren
op_amp
l_int|0xff
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;[Bank %d Set 0x%02x]  LRU &gt; %d %d %d %d &gt; MRU&bslash;n&quot;
comma
(paren
(paren
id|addr
op_rshift
l_int|5
)paren
op_amp
l_int|0x3
)paren
comma
multiline_comment|/* bank */
(paren
(paren
id|addr
op_rshift
l_int|7
)paren
op_amp
l_int|0x3f
)paren
comma
multiline_comment|/* index */
(paren
id|lru
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|lru
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|lru
op_rshift
l_int|4
)paren
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|lru
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
)paren
)paren
suffix:semicolon
)brace
id|va
op_assign
(paren
id|taglo
op_amp
l_int|0xC0000FFFFFFFE000ULL
)paren
op_or
id|addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|taglo
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
op_logical_and
(paren
(paren
(paren
id|taglo
op_rshift
l_int|62
)paren
op_amp
l_int|0x3
)paren
op_eq
l_int|3
)paren
)paren
id|va
op_or_assign
l_int|0x3FFFF00000000000ULL
suffix:semicolon
id|valid
op_assign
(paren
(paren
id|taghi
op_rshift
l_int|29
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|valid
)paren
(brace
id|tlo_tmp
op_assign
id|taglo
op_amp
l_int|0xfff3ff
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|taglo
op_rshift
l_int|10
)paren
op_amp
l_int|1
)paren
op_xor
id|range_parity
c_func
(paren
id|tlo_tmp
comma
l_int|23
comma
l_int|0
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in VTag0/G/ASID&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRI_TAG_PARITY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|taglo
op_rshift
l_int|11
)paren
op_amp
l_int|1
)paren
op_xor
id|range_parity
c_func
(paren
id|taglo
comma
l_int|63
comma
l_int|24
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in R/VTag1&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRI_TAG_PARITY
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|valid
op_xor
(paren
(paren
id|taghi
op_rshift
l_int|27
)paren
op_amp
l_int|1
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity for valid bit&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRI_TAG_PARITY
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot; %d  [VA %016llx]  [Vld? %d]  raw tags: %08X-%016llX&bslash;n&quot;
comma
id|way
comma
id|va
comma
id|valid
comma
id|taghi
comma
id|taglo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
r_uint32
id|datahi
comma
id|insta
comma
id|instb
suffix:semicolon
r_uint8
id|predecode
suffix:semicolon
r_int
id|offset
suffix:semicolon
multiline_comment|/* (hit all banks and ways) */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
l_int|4
suffix:semicolon
id|offset
op_increment
)paren
(brace
multiline_comment|/* Index-load-data-I */
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;push&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noreorder&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;mips64&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noat&bslash;n&bslash;t&quot;
l_string|&quot;&t;cache&t;6, 0(%3)  &bslash;n&bslash;t&quot;
l_string|&quot;&t;mfc0&t;%0, $29, 1&bslash;n&bslash;t&quot;
l_string|&quot;&t;dmfc0  $1, $28, 1&bslash;n&bslash;t&quot;
l_string|&quot;&t;dsrl32 %1, $1, 0 &bslash;n&bslash;t&quot;
l_string|&quot;&t;sll    %2, $1, 0 &bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;pop         &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|datahi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|insta
)paren
comma
l_string|&quot;=r&quot;
(paren
id|instb
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|way
op_lshift
l_int|13
)paren
op_or
id|addr
op_or
(paren
id|offset
op_lshift
l_int|3
)paren
)paren
)paren
suffix:semicolon
id|predecode
op_assign
(paren
id|datahi
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|datahi
op_rshift
l_int|16
)paren
op_amp
l_int|1
)paren
op_ne
(paren
r_uint32
)paren
id|range_parity
c_func
(paren
id|predecode
comma
l_int|7
comma
l_int|0
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in predecode&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRI_DATA_PARITY
suffix:semicolon
)brace
multiline_comment|/* XXXKW should/could check predecode bits themselves */
r_if
c_cond
(paren
(paren
(paren
id|datahi
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
op_xor
id|inst_parity
c_func
(paren
id|insta
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in instruction a&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRI_DATA_PARITY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|datahi
op_amp
l_int|0xf
)paren
op_xor
id|inst_parity
c_func
(paren
id|instb
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in instruction b&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRI_DATA_PARITY
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;  %05X-%08X%08X&quot;
comma
id|datahi
comma
id|insta
comma
id|instb
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Compute the ECC for a data doubleword */
DECL|function|dc_ecc
r_static
r_uint8
id|dc_ecc
c_func
(paren
r_uint64
id|dword
)paren
(brace
r_uint64
id|t
suffix:semicolon
r_uint32
id|w
suffix:semicolon
r_uint8
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|p
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|p
op_lshift_assign
l_int|1
suffix:semicolon
id|t
op_assign
id|dword
op_amp
id|mask_72_64
(braket
id|i
)braket
suffix:semicolon
id|w
op_assign
(paren
r_uint32
)paren
(paren
id|t
op_rshift
l_int|32
)paren
suffix:semicolon
id|p
op_xor_assign
(paren
id|parity
(braket
id|w
op_rshift
l_int|24
)braket
op_xor
id|parity
(braket
(paren
id|w
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)braket
op_xor
id|parity
(braket
(paren
id|w
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
)braket
op_xor
id|parity
(braket
id|w
op_amp
l_int|0xFF
)braket
)paren
suffix:semicolon
id|w
op_assign
(paren
r_uint32
)paren
(paren
id|t
op_amp
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|p
op_xor_assign
(paren
id|parity
(braket
id|w
op_rshift
l_int|24
)braket
op_xor
id|parity
(braket
(paren
id|w
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)braket
op_xor
id|parity
(braket
(paren
id|w
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
)braket
op_xor
id|parity
(braket
id|w
op_amp
l_int|0xFF
)braket
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|struct|dc_state
r_struct
id|dc_state
(brace
DECL|member|val
r_int
r_char
id|val
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dc_states
r_static
r_struct
id|dc_state
id|dc_states
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
l_string|&quot;INVALID&quot;
)brace
comma
(brace
l_int|0x0f
comma
l_string|&quot;COH-SHD&quot;
)brace
comma
(brace
l_int|0x13
comma
l_string|&quot;NCO-E-C&quot;
)brace
comma
(brace
l_int|0x19
comma
l_string|&quot;NCO-E-D&quot;
)brace
comma
(brace
l_int|0x16
comma
l_string|&quot;COH-E-C&quot;
)brace
comma
(brace
l_int|0x1c
comma
l_string|&quot;COH-E-D&quot;
)brace
comma
(brace
l_int|0xff
comma
l_string|&quot;*ERROR*&quot;
)brace
)brace
suffix:semicolon
DECL|macro|DC_TAG_VALID
mdefine_line|#define DC_TAG_VALID(state) &bslash;&n;    (((state) == 0xf) || ((state) == 0x13) || ((state) == 0x19) || ((state == 0x16)) || ((state) == 0x1c))
DECL|function|dc_state_str
r_static
r_char
op_star
id|dc_state_str
c_func
(paren
r_int
r_char
id|state
)paren
(brace
r_struct
id|dc_state
op_star
id|dsc
op_assign
id|dc_states
suffix:semicolon
r_while
c_loop
(paren
id|dsc-&gt;val
op_ne
l_int|0xff
)paren
(brace
r_if
c_cond
(paren
id|dsc-&gt;val
op_eq
id|state
)paren
r_break
suffix:semicolon
id|dsc
op_increment
suffix:semicolon
)brace
r_return
id|dsc-&gt;name
suffix:semicolon
)brace
DECL|function|extract_dc
r_static
r_uint32
id|extract_dc
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
id|valid
comma
id|way
suffix:semicolon
r_int
r_char
id|state
suffix:semicolon
r_uint64
id|taglo
comma
id|pa
suffix:semicolon
r_uint32
id|taghi
comma
id|taglolo
comma
id|taglohi
suffix:semicolon
r_uint8
id|ecc
comma
id|lru
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Dcache index 0x%04x  &quot;
comma
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|way
op_assign
l_int|0
suffix:semicolon
id|way
OL
l_int|4
suffix:semicolon
id|way
op_increment
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;push&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noreorder&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;mips64&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noat&bslash;n&bslash;t&quot;
l_string|&quot;&t;cache&t;5, 0(%3)&bslash;n&bslash;t&quot;
multiline_comment|/* Index-load-tag-D */
l_string|&quot;&t;mfc0&t;%0, $29, 2&bslash;n&bslash;t&quot;
l_string|&quot;&t;dmfc0&t;$1, $28, 2&bslash;n&bslash;t&quot;
l_string|&quot;&t;dsrl32&t;%1, $1, 0&bslash;n&bslash;t&quot;
l_string|&quot;&t;sll&t;%2, $1, 0&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|taghi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|taglohi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|taglolo
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|way
op_lshift
l_int|13
)paren
op_or
id|addr
)paren
)paren
suffix:semicolon
id|taglo
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|taglohi
op_lshift
l_int|32
)paren
op_or
id|taglolo
suffix:semicolon
id|pa
op_assign
(paren
id|taglo
op_amp
l_int|0xFFFFFFE000ULL
)paren
op_or
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|way
op_eq
l_int|0
)paren
(brace
id|lru
op_assign
(paren
id|taghi
op_rshift
l_int|14
)paren
op_amp
l_int|0xff
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;[Bank %d Set 0x%02x]  LRU &gt; %d %d %d %d &gt; MRU&bslash;n&quot;
comma
(paren
(paren
id|addr
op_rshift
l_int|11
)paren
op_amp
l_int|0x2
)paren
op_or
(paren
(paren
id|addr
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
comma
multiline_comment|/* bank */
(paren
(paren
id|addr
op_rshift
l_int|6
)paren
op_amp
l_int|0x3f
)paren
comma
multiline_comment|/* index */
(paren
id|lru
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|lru
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|lru
op_rshift
l_int|4
)paren
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|lru
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
)paren
)paren
suffix:semicolon
)brace
id|state
op_assign
(paren
id|taghi
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|valid
op_assign
id|DC_TAG_VALID
c_func
(paren
id|state
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot; %d  [PA %010llx]  [state %s (%02x)]  raw tags: %08X-%016llX&bslash;n&quot;
comma
id|way
comma
id|pa
comma
id|dc_state_str
c_func
(paren
id|state
)paren
comma
id|state
comma
id|taghi
comma
id|taglo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|valid
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|taglo
op_rshift
l_int|11
)paren
op_amp
l_int|1
)paren
op_xor
id|range_parity
c_func
(paren
id|taglo
comma
l_int|39
comma
l_int|26
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in PTag1&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRD_TAG_ADDRESS
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|taglo
op_rshift
l_int|10
)paren
op_amp
l_int|1
)paren
op_xor
id|range_parity
c_func
(paren
id|taglo
comma
l_int|25
comma
l_int|13
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;   ** bad parity in PTag0&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_or_assign
id|CP0_CERRD_TAG_ADDRESS
suffix:semicolon
)brace
)brace
r_else
(brace
id|res
op_or_assign
id|CP0_CERRD_TAG_STATE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
)paren
(brace
r_uint64
id|datalo
suffix:semicolon
r_uint32
id|datalohi
comma
id|datalolo
comma
id|datahi
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
l_int|4
suffix:semicolon
id|offset
op_increment
)paren
(brace
multiline_comment|/* Index-load-data-D */
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;push&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noreorder&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;mips64&bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;noat&bslash;n&bslash;t&quot;
l_string|&quot;&t;cache&t;7, 0(%3)&bslash;n&bslash;t&quot;
multiline_comment|/* Index-load-data-D */
l_string|&quot;&t;mfc0&t;%0, $29, 3&bslash;n&bslash;t&quot;
l_string|&quot;&t;dmfc0&t;$1, $28, 3&bslash;n&bslash;t&quot;
l_string|&quot;&t;dsrl32&t;%1, $1, 0 &bslash;n&bslash;t&quot;
l_string|&quot;&t;sll&t;%2, $1, 0 &bslash;n&bslash;t&quot;
l_string|&quot;&t;.set&t;pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|datahi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|datalohi
)paren
comma
l_string|&quot;=r&quot;
(paren
id|datalolo
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|way
op_lshift
l_int|13
)paren
op_or
id|addr
op_or
(paren
id|offset
op_lshift
l_int|3
)paren
)paren
)paren
suffix:semicolon
id|datalo
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|datalohi
op_lshift
l_int|32
)paren
op_or
id|datalolo
suffix:semicolon
id|ecc
op_assign
id|dc_ecc
c_func
(paren
id|datalo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ecc
op_ne
id|datahi
)paren
(brace
r_int
id|bits
op_assign
l_int|0
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;  ** bad ECC (%02x %02x) -&gt;&quot;
comma
id|datahi
comma
id|ecc
)paren
suffix:semicolon
id|ecc
op_xor_assign
id|datahi
suffix:semicolon
r_while
c_loop
(paren
id|ecc
)paren
(brace
r_if
c_cond
(paren
id|ecc
op_amp
l_int|1
)paren
id|bits
op_increment
suffix:semicolon
id|ecc
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|res
op_or_assign
(paren
id|bits
op_eq
l_int|1
)paren
ques
c_cond
id|CP0_CERRD_DATA_SBE
suffix:colon
id|CP0_CERRD_DATA_DBE
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;  %02X-%016llX&quot;
comma
id|datahi
comma
id|datalo
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|res
suffix:semicolon
)brace
eof
