multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
r_case
id|MACH_NEC_DDB5074
suffix:colon
r_return
l_string|&quot;NEC DDB Vrc-5074&quot;
suffix:semicolon
r_case
id|MACH_NEC_DDB5476
suffix:colon
r_return
l_string|&quot;NEC DDB Vrc-5476&quot;
suffix:semicolon
r_case
id|MACH_NEC_DDB5477
suffix:colon
r_return
l_string|&quot;NEC DDB Vrc-5477&quot;
suffix:semicolon
r_case
id|MACH_NEC_ROCKHOPPER
suffix:colon
r_return
l_string|&quot;NEC Rockhopper&quot;
suffix:semicolon
r_case
id|MACH_NEC_ROCKHOPPERII
suffix:colon
r_return
l_string|&quot;NEC RockhopperII&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;Unknown NEC board&quot;
suffix:semicolon
)brace
)brace
macro_line|#if defined(CONFIG_DDB5477)
r_void
id|ddb5477_runtime_detection
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* [jsun@junsun.net] PMON passes arguments in C main() style */
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_void
)paren
(brace
r_int
id|argc
op_assign
id|fw_arg0
suffix:semicolon
r_char
op_star
op_star
id|arg
op_assign
(paren
r_char
op_star
op_star
)paren
id|fw_arg1
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* if user passes kernel args, ignore the default one */
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|arcs_cmdline
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* arg[0] is &quot;g&quot;, the rest is boot parameters */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|arcs_cmdline
)paren
op_plus
id|strlen
c_func
(paren
id|arg
(braket
id|i
)braket
op_plus
l_int|1
)paren
op_ge
r_sizeof
(paren
id|arcs_cmdline
)paren
)paren
r_break
suffix:semicolon
id|strcat
c_func
(paren
id|arcs_cmdline
comma
id|arg
(braket
id|i
)braket
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|arcs_cmdline
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|mips_machgroup
op_assign
id|MACH_GROUP_NEC_DDB
suffix:semicolon
macro_line|#if defined(CONFIG_DDB5074)
id|mips_machtype
op_assign
id|MACH_NEC_DDB5074
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
id|DDB_SDRAM_SIZE
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_DDB5476)
id|mips_machtype
op_assign
id|MACH_NEC_DDB5476
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
id|DDB_SDRAM_SIZE
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_DDB5477)
id|ddb5477_runtime_detection
c_func
(paren
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
id|board_ram_size
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|prom_free_prom_memory
r_int
r_int
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_DDB5477)
DECL|macro|DEFAULT_LCS1_BASE
mdefine_line|#define DEFAULT_LCS1_BASE 0x19000000
DECL|macro|TESTVAL1
mdefine_line|#define TESTVAL1 &squot;K&squot;
DECL|macro|TESTVAL2
mdefine_line|#define TESTVAL2 &squot;S&squot;
DECL|variable|board_ram_size
r_int
id|board_ram_size
suffix:semicolon
DECL|function|ddb5477_runtime_detection
r_void
id|ddb5477_runtime_detection
c_func
(paren
r_void
)paren
(brace
r_volatile
r_char
op_star
id|test_offset
suffix:semicolon
r_char
id|saved_test_byte
suffix:semicolon
multiline_comment|/* Determine if this is a DDB5477 board, or a BSB-VR0300&n;           base board.  We can tell by checking for the location of&n;           the NVRAM.  It lives at the beginning of LCS1 on the DDB5477,&n;           and the beginning of LCS1 on the BSB-VR0300 is flash memory.&n;           The first 2K of the NVRAM are reserved, so don&squot;t we&squot;ll poke&n;           around just after that.&n;         */
multiline_comment|/* We can only use the PCI bus to distinquish between&n;&t;   the Rockhopper and RockhopperII backplanes and this must&n;&t;   wait until ddb5477_board_init() in setup.c after the 5477&n;&t;   is initialized.  So, until then handle&n;&t;   both Rockhopper and RockhopperII backplanes as Rockhopper 1&n;&t; */
id|test_offset
op_assign
(paren
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|DEFAULT_LCS1_BASE
op_plus
l_int|0x800
)paren
suffix:semicolon
id|saved_test_byte
op_assign
op_star
id|test_offset
suffix:semicolon
op_star
id|test_offset
op_assign
id|TESTVAL1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|test_offset
op_ne
id|TESTVAL1
)paren
(brace
multiline_comment|/* We couldn&squot;t set our test value, so it must not be NVRAM,&n;                   so it&squot;s a BSB_VR0300 */
id|mips_machtype
op_assign
id|MACH_NEC_ROCKHOPPER
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We may have gotten lucky, and the TESTVAL1 was already&n;                   stored at the test location, so we must check a second&n;                   test value */
op_star
id|test_offset
op_assign
id|TESTVAL2
suffix:semicolon
r_if
c_cond
(paren
op_star
id|test_offset
op_ne
id|TESTVAL2
)paren
(brace
multiline_comment|/* OK, we couldn&squot;t set this value either, so it must&n;                           definately be a BSB_VR0300 */
id|mips_machtype
op_assign
id|MACH_NEC_ROCKHOPPER
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We could change the value twice, so it must be&n;                        NVRAM, so it&squot;s a DDB_VRC5477 */
id|mips_machtype
op_assign
id|MACH_NEC_DDB5477
suffix:semicolon
)brace
)brace
multiline_comment|/* Restore the original byte */
op_star
id|test_offset
op_assign
id|saved_test_byte
suffix:semicolon
multiline_comment|/* before we know a better way, we will trust PMON for getting&n;&t; * RAM size&n;&t; */
id|board_ram_size
op_assign
l_int|1
op_lshift
(paren
l_int|36
op_minus
(paren
id|ddb_in32
c_func
(paren
id|DDB_SDRAM0
)paren
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
id|db_run
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;DDB run-time detection : %s, %d MB RAM&bslash;n&quot;
comma
id|mips_machtype
op_eq
id|MACH_NEC_DDB5477
ques
c_cond
l_string|&quot;DDB5477&quot;
suffix:colon
l_string|&quot;Rockhopper&quot;
comma
id|board_ram_size
op_rshift
l_int|20
)paren
)paren
suffix:semicolon
multiline_comment|/* we can&squot;t handle ram size &gt; 128 MB */
id|db_assert
c_func
(paren
id|board_ram_size
op_le
(paren
l_int|128
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
