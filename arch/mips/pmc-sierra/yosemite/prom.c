multiline_comment|/*&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * Copyright (C) 2003 PMC-Sierra Inc.&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;setup.h&quot;
multiline_comment|/* Call Vectors */
DECL|struct|callvectors
r_struct
id|callvectors
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|lseek
id|off_t
(paren
op_star
id|lseek
)paren
(paren
r_int
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|member|printf
r_int
(paren
op_star
id|printf
)paren
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|member|cacheflush
r_void
(paren
op_star
id|cacheflush
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|gets
r_char
op_star
(paren
op_star
id|gets
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
)brace
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
id|yosemite_base
suffix:semicolon
r_extern
r_int
r_int
id|cpu_clock
suffix:semicolon
DECL|variable|titan_ge_mac_addr_base
r_int
r_char
id|titan_ge_mac_addr_base
(braket
l_int|6
)braket
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
l_string|&quot;PMC-Sierra Yosemite&quot;
suffix:semicolon
)brace
DECL|function|prom_cpu0_exit
r_static
r_void
id|prom_cpu0_exit
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|nvram
op_assign
id|YOSEMITE_NVRAM_BASE_ADDR
suffix:semicolon
multiline_comment|/* Ask the NVRAM/RTC/watchdog chip to assert reset in 1/16 second */
id|writeb
c_func
(paren
l_int|0x84
comma
id|nvram
op_plus
l_int|0xff7
)paren
suffix:semicolon
multiline_comment|/* wait for the watchdog to go off */
id|mdelay
c_func
(paren
l_int|100
op_plus
(paren
l_int|1000
op_div
l_int|16
)paren
)paren
suffix:semicolon
multiline_comment|/* if the watchdog fails for some reason, let people know */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Watchdog reset failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reset the NVRAM over the local bus&n; */
DECL|function|prom_exit
r_static
r_void
id|prom_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
multiline_comment|/* CPU 1 */
id|smp_call_function
c_func
(paren
id|prom_cpu0_exit
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|prom_cpu0_exit
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the MAC address from the EEPROM using the I2C protocol&n; */
DECL|function|get_mac_address
r_void
id|get_mac_address
c_func
(paren
r_char
id|dest
(braket
l_int|6
)braket
)paren
(brace
multiline_comment|/* Use the I2C command code in the i2c-yosemite */
)brace
multiline_comment|/*&n; * Halt the system &n; */
DECL|function|prom_halt
r_static
r_void
id|prom_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;&bslash;n** You can safely turn off the power&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Init routine which accepts the variables from PMON&n; */
DECL|function|prom_init
id|__init
id|prom_init
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|arg
comma
r_char
op_star
op_star
id|env
comma
r_struct
id|callvectors
op_star
id|cv
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Callbacks for halt, restart */
id|_machine_restart
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_char
op_star
)paren
)paren
id|prom_exit
suffix:semicolon
id|_machine_halt
op_assign
id|prom_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|prom_halt
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/* Do nothing for the 64-bit for now. Just implement for the 32-bit */
macro_line|#else /* CONFIG_MIPS64 */
id|debug_vectors
op_assign
id|cv
suffix:semicolon
id|arcs_cmdline
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Get the boot parameters */
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
l_string|&quot;ocd_base&quot;
comma
op_star
id|env
comma
id|strlen
c_func
(paren
l_string|&quot;ocd_base&quot;
)paren
)paren
op_eq
l_int|0
)paren
id|yosemite_base
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
l_string|&quot;ocd_base=&quot;
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
id|env
op_increment
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MIPS64 */
id|mips_machgroup
op_assign
id|MACH_GROUP_TITAN
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_TITAN_YOSEMITE
suffix:semicolon
id|get_mac_address
c_func
(paren
id|titan_ge_mac_addr_base
)paren
suffix:semicolon
id|debug_vectors
op_member_access_from_pointer
id|printf
c_func
(paren
l_string|&quot;Booting Linux kernel...&bslash;n&quot;
)paren
suffix:semicolon
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
r_extern
r_void
id|asmlinkage
id|smp_bootstrap
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * SMP support&n; */
DECL|function|prom_setup_smp
r_int
id|prom_setup_smp
c_func
(paren
r_void
)paren
(brace
r_int
id|num_cpus
op_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;         * We know that the RM9000 on the Jaguar ATX board has 2 cores. Hence, this&n;         * can be hardcoded for now.&n;         */
r_return
id|num_cpus
suffix:semicolon
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
id|u_int32_t
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
