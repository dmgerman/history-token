multiline_comment|/*&n; * arch/ppc/syslib/mpc52xx_setup.c&n; *&n; * Common code for the boards based on Freescale MPC52xx embedded CPU.&n; *&n; * &n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Support for other bootloaders than UBoot by Dale Farnsworth &n; * &lt;dfarnsworth@mvista.com&gt;&n; * &n; * Copyright (C) 2004 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; * Copyright (C) 2003 Montavista Software, Inc&n; * &n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/mpc52xx.h&gt;
macro_line|#include &lt;asm/mpc52xx_psc.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
r_extern
id|bd_t
id|__res
suffix:semicolon
DECL|variable|core_mult
r_static
r_int
id|core_mult
(braket
)braket
op_assign
(brace
multiline_comment|/* CPU Frequency multiplier, taken    */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|10
comma
l_int|20
comma
l_int|20
comma
l_int|25
comma
l_int|45
comma
multiline_comment|/* from the datasheet used to compute */
l_int|30
comma
l_int|55
comma
l_int|40
comma
l_int|50
comma
l_int|0
comma
l_int|60
comma
l_int|35
comma
l_int|0
comma
multiline_comment|/* CPU frequency from XLB freq and    */
l_int|30
comma
l_int|25
comma
l_int|65
comma
l_int|10
comma
l_int|70
comma
l_int|20
comma
l_int|75
comma
l_int|45
comma
multiline_comment|/* external jumper config             */
l_int|0
comma
l_int|55
comma
l_int|40
comma
l_int|50
comma
l_int|80
comma
l_int|60
comma
l_int|35
comma
l_int|0
)brace
suffix:semicolon
r_void
DECL|function|mpc52xx_restart
id|mpc52xx_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_struct
id|mpc52xx_gpt
id|__iomem
op_star
id|gpt0
op_assign
(paren
r_struct
id|mpc52xx_gpt
id|__iomem
op_star
)paren
id|MPC52xx_GPTx
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn on the watchdog and wait for it to expire. It effectively&n;&t;  does a reset */
r_if
c_cond
(paren
id|gpt0
op_ne
l_int|NULL
)paren
(brace
id|out_be32
c_func
(paren
op_amp
id|gpt0-&gt;count
comma
l_int|0x000000ff
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|gpt0-&gt;mode
comma
l_int|0x00009004
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mpc52xx_restart: Unable to ioremap GPT0 registers, -&gt; looping ...&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|mpc52xx_halt
id|mpc52xx_halt
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
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
)brace
r_void
DECL|function|mpc52xx_power_off
id|mpc52xx_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* By default we don&squot;t have any way of shut down.&n;&t;   If a specific board wants to, it can set the power down&n;&t;   code to any hardware implementation dependent code */
id|mpc52xx_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|mpc52xx_set_bat
id|mpc52xx_set_bat
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Set BAT 2 to map the 0xf0000000 area */
multiline_comment|/* This mapping is used during mpc52xx_progress,&n;&t; * mpc52xx_find_end_of_memory, and UARTs/GPIO access for debug&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT2U
comma
l_int|0xf0001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT2L
comma
l_int|0xf000002a
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|mpc52xx_map_io
id|mpc52xx_map_io
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Here we only map the MBAR */
id|io_block_mapping
c_func
(paren
id|MPC52xx_MBAR_VIRT
comma
id|MPC52xx_MBAR
comma
id|MPC52xx_MBAR_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
macro_line|#ifdef MPC52xx_PF_CONSOLE_PORT
DECL|macro|MPC52xx_CONSOLE
mdefine_line|#define MPC52xx_CONSOLE MPC52xx_PSCx(MPC52xx_PF_CONSOLE_PORT)
macro_line|#else
macro_line|#error &quot;mpc52xx PSC for console not selected&quot;
macro_line|#endif
r_static
r_void
DECL|function|mpc52xx_psc_putc
id|mpc52xx_psc_putc
c_func
(paren
r_struct
id|mpc52xx_psc
id|__iomem
op_star
id|psc
comma
r_int
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|in_be16
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_status
)paren
op_amp
id|MPC52xx_PSC_SR_TXRDY
)paren
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_buffer_8
comma
id|c
)paren
suffix:semicolon
)brace
r_void
DECL|function|mpc52xx_progress
id|mpc52xx_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_char
id|c
suffix:semicolon
r_struct
id|mpc52xx_psc
id|__iomem
op_star
id|psc
op_assign
(paren
r_struct
id|mpc52xx_psc
id|__iomem
op_star
)paren
id|MPC52xx_CONSOLE
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|mpc52xx_psc_putc
c_func
(paren
id|psc
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|mpc52xx_psc_putc
c_func
(paren
id|psc
comma
id|c
)paren
suffix:semicolon
)brace
id|mpc52xx_psc_putc
c_func
(paren
id|psc
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|mpc52xx_psc_putc
c_func
(paren
id|psc
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
macro_line|#endif  /* CONFIG_SERIAL_TEXT_DEBUG */
r_int
r_int
id|__init
DECL|function|mpc52xx_find_end_of_memory
id|mpc52xx_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|u32
id|ramsize
op_assign
id|__res.bi_memsize
suffix:semicolon
multiline_comment|/*&n;&t; * if bootloader passed a memsize, just use it&n;&t; * else get size from sdram config registers&n;&t; */
r_if
c_cond
(paren
id|ramsize
op_eq
l_int|0
)paren
(brace
r_struct
id|mpc52xx_mmap_ctl
id|__iomem
op_star
id|mmap_ctl
suffix:semicolon
id|u32
id|sdram_config_0
comma
id|sdram_config_1
suffix:semicolon
multiline_comment|/* Temp BAT2 mapping active when this is called ! */
id|mmap_ctl
op_assign
(paren
r_struct
id|mpc52xx_mmap_ctl
id|__iomem
op_star
)paren
id|MPC52xx_MMAP_CTL
suffix:semicolon
id|sdram_config_0
op_assign
id|in_be32
c_func
(paren
op_amp
id|mmap_ctl-&gt;sdram0
)paren
suffix:semicolon
id|sdram_config_1
op_assign
id|in_be32
c_func
(paren
op_amp
id|mmap_ctl-&gt;sdram1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sdram_config_0
op_amp
l_int|0x1f
)paren
op_ge
l_int|0x13
)paren
id|ramsize
op_assign
l_int|1
op_lshift
(paren
(paren
id|sdram_config_0
op_amp
l_int|0xf
)paren
op_plus
l_int|17
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|sdram_config_1
op_amp
l_int|0x1f
)paren
op_ge
l_int|0x13
)paren
op_logical_and
(paren
(paren
id|sdram_config_1
op_amp
l_int|0xfff00000
)paren
op_eq
id|ramsize
)paren
)paren
id|ramsize
op_add_assign
l_int|1
op_lshift
(paren
(paren
id|sdram_config_1
op_amp
l_int|0xf
)paren
op_plus
l_int|17
)paren
suffix:semicolon
)brace
r_return
id|ramsize
suffix:semicolon
)brace
r_void
id|__init
DECL|function|mpc52xx_calibrate_decr
id|mpc52xx_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
id|current_time
comma
id|previous_time
suffix:semicolon
r_int
id|tbl_start
comma
id|tbl_end
suffix:semicolon
r_int
r_int
id|xlbfreq
comma
id|cpufreq
comma
id|ipbfreq
comma
id|pcifreq
comma
id|divisor
suffix:semicolon
id|xlbfreq
op_assign
id|__res.bi_busfreq
suffix:semicolon
multiline_comment|/* if bootloader didn&squot;t pass bus frequencies, calculate them */
r_if
c_cond
(paren
id|xlbfreq
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Get RTC &amp; Clock manager modules */
r_struct
id|mpc52xx_rtc
id|__iomem
op_star
id|rtc
suffix:semicolon
r_struct
id|mpc52xx_cdm
id|__iomem
op_star
id|cdm
suffix:semicolon
id|rtc
op_assign
id|ioremap
c_func
(paren
id|MPC52xx_RTC
comma
r_sizeof
(paren
r_struct
id|mpc52xx_rtc
)paren
)paren
suffix:semicolon
id|cdm
op_assign
id|ioremap
c_func
(paren
id|MPC52xx_CDM
comma
r_sizeof
(paren
r_struct
id|mpc52xx_cdm
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rtc
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|cdm
op_eq
l_int|NULL
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Can&squot;t ioremap RTC/CDM while computing bus freq&quot;
)paren
suffix:semicolon
multiline_comment|/* Count bus clock during 1/64 sec */
id|out_be32
c_func
(paren
op_amp
id|rtc-&gt;dividers
comma
l_int|0x8f1f0000
)paren
suffix:semicolon
multiline_comment|/* Set RTC 64x faster */
id|previous_time
op_assign
id|in_be32
c_func
(paren
op_amp
id|rtc-&gt;time
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|current_time
op_assign
id|in_be32
c_func
(paren
op_amp
id|rtc-&gt;time
)paren
)paren
op_eq
id|previous_time
)paren
suffix:semicolon
id|tbl_start
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
id|previous_time
op_assign
id|current_time
suffix:semicolon
r_while
c_loop
(paren
(paren
id|current_time
op_assign
id|in_be32
c_func
(paren
op_amp
id|rtc-&gt;time
)paren
)paren
op_eq
id|previous_time
)paren
suffix:semicolon
id|tbl_end
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|rtc-&gt;dividers
comma
l_int|0xffff0000
)paren
suffix:semicolon
multiline_comment|/* Restore RTC */
multiline_comment|/* Compute all frequency from that &amp; CDM settings */
id|xlbfreq
op_assign
(paren
id|tbl_end
op_minus
id|tbl_start
)paren
op_lshift
l_int|8
suffix:semicolon
id|cpufreq
op_assign
(paren
id|xlbfreq
op_star
id|core_mult
(braket
id|in_be32
c_func
(paren
op_amp
id|cdm-&gt;rstcfg
)paren
op_amp
l_int|0x1f
)braket
)paren
op_div
l_int|10
suffix:semicolon
id|ipbfreq
op_assign
(paren
id|in_8
c_func
(paren
op_amp
id|cdm-&gt;ipb_clk_sel
)paren
op_amp
l_int|1
)paren
ques
c_cond
id|xlbfreq
op_div
l_int|2
suffix:colon
id|xlbfreq
suffix:semicolon
r_switch
c_cond
(paren
id|in_8
c_func
(paren
op_amp
id|cdm-&gt;pci_clk_sel
)paren
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|pcifreq
op_assign
id|ipbfreq
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|pcifreq
op_assign
id|ipbfreq
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pcifreq
op_assign
id|xlbfreq
op_div
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
id|__res.bi_busfreq
op_assign
id|xlbfreq
suffix:semicolon
id|__res.bi_intfreq
op_assign
id|cpufreq
suffix:semicolon
id|__res.bi_ipbfreq
op_assign
id|ipbfreq
suffix:semicolon
id|__res.bi_pcifreq
op_assign
id|pcifreq
suffix:semicolon
multiline_comment|/* Release mapping */
id|iounmap
c_func
(paren
id|rtc
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|cdm
)paren
suffix:semicolon
)brace
id|divisor
op_assign
l_int|4
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|xlbfreq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|xlbfreq
op_div
id|divisor
comma
l_int|1000000
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|mpc52xx_add_board_devices
id|mpc52xx_add_board_devices
c_func
(paren
r_struct
id|ocp_def
id|board_ocp
(braket
)braket
)paren
(brace
r_while
c_loop
(paren
id|board_ocp-&gt;vendor
op_ne
id|OCP_VENDOR_INVALID
)paren
r_if
c_cond
(paren
id|ocp_add_one_device
c_func
(paren
id|board_ocp
op_increment
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mpc5200-ocp: Failed to add board device !&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
