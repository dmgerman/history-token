multiline_comment|/*&n; * Copyright 2002 Momentum Computer Inc.&n; * Author: Matthew Dharm &lt;mdharm@momenco.com&gt;&n; *&n; * Louis Hamilton, Red Hat, Inc.&n; * hamilton@redhat.com  [MIPS64 modifications]&n; *&n; * Based on Ocelot Linux port, which is&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * Added changes for SMP - Manish Lachwani (lachwani@pmc-sierra.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mv64340.h&gt;
macro_line|#include &lt;asm/pmon.h&gt;
macro_line|#include &quot;jaguar_atx_fpga.h&quot;
r_extern
r_void
id|ja_setup_console
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|debug_vectors
r_struct
id|callvectors
op_star
id|debug_vectors
suffix:semicolon
r_extern
r_int
r_int
id|cpu_clock
suffix:semicolon
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
r_return
l_string|&quot;Momentum Jaguar-ATX&quot;
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MV643XX_ETH
r_extern
r_int
r_char
id|prom_mac_addr_base
(braket
l_int|6
)braket
suffix:semicolon
DECL|function|burn_clocks
r_static
r_void
id|burn_clocks
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* this loop should burn at least 1us -- this should be plenty */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x10000
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
)brace
DECL|function|exchange_bit
r_static
id|u8
id|exchange_bit
c_func
(paren
id|u8
id|val
comma
id|u8
id|cs
)paren
(brace
multiline_comment|/* place the data */
id|JAGUAR_FPGA_WRITE
c_func
(paren
(paren
id|val
op_lshift
l_int|2
)paren
op_or
id|cs
comma
id|EEPROM_MODE
)paren
suffix:semicolon
id|burn_clocks
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* turn the clock on */
id|JAGUAR_FPGA_WRITE
c_func
(paren
(paren
id|val
op_lshift
l_int|2
)paren
op_or
id|cs
op_or
l_int|0x2
comma
id|EEPROM_MODE
)paren
suffix:semicolon
id|burn_clocks
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* turn the clock off and read-strobe */
id|JAGUAR_FPGA_WRITE
c_func
(paren
(paren
id|val
op_lshift
l_int|2
)paren
op_or
id|cs
op_or
l_int|0x10
comma
id|EEPROM_MODE
)paren
suffix:semicolon
multiline_comment|/* return the data */
r_return
(paren
(paren
id|JAGUAR_FPGA_READ
c_func
(paren
id|EEPROM_MODE
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x1
)paren
suffix:semicolon
)brace
DECL|function|get_mac
r_void
id|get_mac
c_func
(paren
r_char
id|dest
(braket
l_int|6
)braket
)paren
(brace
id|u8
id|read_opcode
(braket
l_int|12
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|i
comma
id|j
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
l_int|12
suffix:semicolon
id|i
op_increment
)paren
id|exchange_bit
c_func
(paren
id|read_opcode
(braket
id|i
)braket
comma
l_int|1
)paren
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
l_int|6
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dest
(braket
id|j
)braket
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
id|dest
(braket
id|j
)braket
op_lshift_assign
l_int|1
suffix:semicolon
id|dest
(braket
id|j
)braket
op_or_assign
id|exchange_bit
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* turn off CS */
id|exchange_bit
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|function|signext
r_int
r_int
id|signext
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_and_assign
l_int|0xffffffff
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
(paren
(paren
r_int
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|get_arg
r_void
op_star
id|get_arg
c_func
(paren
r_int
r_int
id|args
comma
r_int
id|arc
)paren
(brace
r_int
r_int
id|ul
suffix:semicolon
r_int
r_char
op_star
id|puc
comma
id|uc
suffix:semicolon
id|args
op_add_assign
(paren
id|arc
op_star
l_int|4
)paren
suffix:semicolon
id|ul
op_assign
(paren
r_int
r_int
)paren
id|signext
c_func
(paren
id|args
)paren
suffix:semicolon
id|puc
op_assign
(paren
r_int
r_char
op_star
)paren
id|ul
suffix:semicolon
r_if
c_cond
(paren
id|puc
op_eq
l_int|0
)paren
r_return
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_LITTLE_ENDIAN
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|l
op_assign
(paren
r_int
r_int
)paren
id|uc
suffix:semicolon
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_lshift
l_int|24
)paren
suffix:semicolon
macro_line|#else
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_assign
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_lshift
l_int|24
suffix:semicolon
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|uc
op_assign
op_star
id|puc
op_increment
suffix:semicolon
id|ul
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
suffix:semicolon
macro_line|#endif
id|ul
op_assign
id|signext
c_func
(paren
id|ul
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ul
suffix:semicolon
)brace
DECL|function|arg64
r_char
op_star
id|arg64
c_func
(paren
r_int
r_int
id|addrin
comma
r_int
id|arg_index
)paren
(brace
r_int
r_int
id|args
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|args
op_assign
id|signext
c_func
(paren
id|addrin
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
id|get_arg
c_func
(paren
id|args
comma
id|arg_index
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
macro_line|#endif  /* CONFIG_MIPS64 */
multiline_comment|/* PMON passes arguments in C main() style */
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
r_char
op_star
op_star
id|env
op_assign
(paren
r_char
op_star
op_star
)paren
id|fw_arg2
suffix:semicolon
r_struct
id|callvectors
op_star
id|cv
op_assign
(paren
r_struct
id|callvectors
op_star
)paren
id|fw_arg3
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
singleline_comment|//&t;ja_setup_console();&t;/* The very first thing.  */
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
r_char
op_star
id|ptr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mips64 Jaguar-ATX&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* save the PROM vectors for debugging use */
id|debug_vectors
op_assign
(paren
r_struct
id|callvectors
op_star
)paren
id|signext
c_func
(paren
(paren
r_int
r_int
)paren
id|cv
)paren
suffix:semicolon
multiline_comment|/* arg[0] is &quot;g&quot;, the rest is boot parameters */
id|arcs_cmdline
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
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
id|ptr
op_assign
(paren
r_char
op_star
)paren
id|arg64
c_func
(paren
(paren
r_int
r_int
)paren
id|arg
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|ptr
)paren
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
id|ptr
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
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|ptr
op_assign
(paren
r_char
op_star
)paren
id|arg64
c_func
(paren
(paren
r_int
r_int
)paren
id|env
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;gtbase&quot;
comma
id|ptr
comma
id|strlen
c_func
(paren
l_string|&quot;gtbase&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|marvell_base
op_assign
id|simple_strtol
c_func
(paren
id|ptr
op_plus
id|strlen
c_func
(paren
l_string|&quot;gtbase=&quot;
)paren
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|marvell_base
op_amp
l_int|0xffffffff00000000
)paren
op_eq
l_int|0
)paren
id|marvell_base
op_or_assign
l_int|0xffffffff00000000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;marvell_base set to 0x%016lx&bslash;n&quot;
comma
id|marvell_base
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;cpuclock&quot;
comma
id|ptr
comma
id|strlen
c_func
(paren
l_string|&quot;cpuclock&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|cpu_clock
op_assign
id|simple_strtol
c_func
(paren
id|ptr
op_plus
id|strlen
c_func
(paren
l_string|&quot;cpuclock=&quot;
)paren
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cpu_clock set to %d&bslash;n&quot;
comma
id|cpu_clock
)paren
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;arcs_cmdline: %s&bslash;n&quot;
comma
id|arcs_cmdline
)paren
suffix:semicolon
macro_line|#else   /* CONFIG_MIPS64 */
multiline_comment|/* save the PROM vectors for debugging use */
id|debug_vectors
op_assign
id|cv
suffix:semicolon
multiline_comment|/* arg[0] is &quot;g&quot;, the rest is boot parameters */
id|arcs_cmdline
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
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
r_while
c_loop
(paren
op_star
id|env
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;gtbase&quot;
comma
op_star
id|env
comma
id|strlen
c_func
(paren
l_string|&quot;gtbase&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|marvell_base
op_assign
id|simple_strtol
c_func
(paren
op_star
id|env
op_plus
id|strlen
c_func
(paren
l_string|&quot;gtbase=&quot;
)paren
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;cpuclock&quot;
comma
op_star
id|env
comma
id|strlen
c_func
(paren
l_string|&quot;cpuclock&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|cpu_clock
op_assign
id|simple_strtol
c_func
(paren
op_star
id|env
op_plus
id|strlen
c_func
(paren
l_string|&quot;cpuclock=&quot;
)paren
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
)brace
id|env
op_increment
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MIPS64 */
id|mips_machgroup
op_assign
id|MACH_GROUP_MOMENCO
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_MOMENCO_JAGUAR_ATX
suffix:semicolon
macro_line|#ifdef CONFIG_MV643XX_ETH
multiline_comment|/* get the base MAC address for on-board ethernet ports */
id|get_mac
c_func
(paren
id|prom_mac_addr_base
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|prom_free_prom_memory
r_void
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|prom_fixup_mem_map
r_void
id|__init
id|prom_fixup_mem_map
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
)brace
DECL|function|prom_boot_secondary
r_int
id|prom_boot_secondary
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|sp
comma
r_int
r_int
id|gp
)paren
(brace
multiline_comment|/* Clear the semaphore */
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
l_int|0xbb000a68
)paren
op_assign
l_int|0x80000000
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|prom_init_secondary
r_void
id|prom_init_secondary
c_func
(paren
r_void
)paren
(brace
id|clear_c0_config
c_func
(paren
id|CONF_CM_CMASK
)paren
suffix:semicolon
id|set_c0_config
c_func
(paren
l_int|0x2
)paren
suffix:semicolon
id|clear_c0_status
c_func
(paren
id|ST0_IM
)paren
suffix:semicolon
id|set_c0_status
c_func
(paren
l_int|0x1ffff
)paren
suffix:semicolon
)brace
DECL|function|prom_smp_finish
r_void
id|prom_smp_finish
c_func
(paren
r_void
)paren
(brace
)brace
eof
