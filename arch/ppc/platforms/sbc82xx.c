multiline_comment|/*&n; * arch/ppc/platforms/sbc82xx.c&n; *&n; * SBC82XX platform support&n; *&n; * Author: Guy Streeter &lt;streeter@redhat.com&gt;&n; *&n; * Derived from: est8260_setup.c by Allen Curtis, ONZ&n; *&n; * Copyright 2004 Red Hat, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
DECL|variable|callback_setup_arch
r_static
r_void
(paren
op_star
id|callback_setup_arch
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|__res
(braket
r_sizeof
(paren
id|bd_t
)paren
)braket
suffix:semicolon
r_extern
r_void
id|m8260_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|late_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
DECL|function|sbc82xx_show_cpuinfo
id|sbc82xx_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Wind River&bslash;n&quot;
l_string|&quot;machine&bslash;t&bslash;t: SBC PowerQUICC II&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;mem size&bslash;t&bslash;t: 0x%08x&bslash;n&quot;
l_string|&quot;console baud&bslash;t&bslash;t: %d&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
comma
id|binfo-&gt;bi_memsize
comma
id|binfo-&gt;bi_baudrate
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sbc82xx_setup_arch
id|sbc82xx_setup_arch
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SBC PowerQUICC II Port&bslash;n&quot;
)paren
suffix:semicolon
id|callback_setup_arch
c_func
(paren
)paren
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Timer init happens before mem_init but after paging init, so we cannot&n; * directly use ioremap() at that time.&n; * late_time_init() is call after paging init.&n; */
macro_line|#ifdef CONFIG_GEN_RTC
DECL|function|sbc82xx_time_init
r_static
r_void
id|sbc82xx_time_init
c_func
(paren
r_void
)paren
(brace
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T59
comma
l_int|0
comma
l_int|0
comma
id|SBC82xx_TODC_NVRAM_ADDR
comma
l_int|0
)paren
suffix:semicolon
id|todc_info-&gt;nvram_data
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|todc_info-&gt;nvram_data
comma
l_int|0x2000
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|todc_info-&gt;nvram_data
)paren
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
id|todc_time_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_GEN_RTC */
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
multiline_comment|/* Generic 8260 platform initialization */
id|m8260_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
multiline_comment|/* Anything special for this platform */
id|ppc_md.show_cpuinfo
op_assign
id|sbc82xx_show_cpuinfo
suffix:semicolon
id|callback_setup_arch
op_assign
id|ppc_md.setup_arch
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|sbc82xx_setup_arch
suffix:semicolon
macro_line|#ifdef CONFIG_GEN_RTC
id|ppc_md.time_init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
l_int|NULL
suffix:semicolon
id|late_time_init
op_assign
id|sbc82xx_time_init
suffix:semicolon
macro_line|#endif /* CONFIG_GEN_RTC */
)brace
eof
