multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|macro|PLD_BASE
mdefine_line|#define PLD_BASE&t;0xbc000000
DECL|macro|REV
mdefine_line|#define REV             0x0     /* Board Assembly Revision */
DECL|macro|PLD1ID
mdefine_line|#define PLD1ID          0x1     /* PLD 1 ID */
DECL|macro|PLD2ID
mdefine_line|#define PLD2ID          0x2     /* PLD 2 ID */
DECL|macro|RESET_STAT
mdefine_line|#define RESET_STAT      0x3     /* Reset Status Register */
DECL|macro|BOARD_STAT
mdefine_line|#define BOARD_STAT      0x4     /* Board Status Register */
DECL|macro|CPCI_ID
mdefine_line|#define CPCI_ID         0x5     /* Compact PCI ID Register */
DECL|macro|CONTROL
mdefine_line|#define CONTROL         0x8     /* Control Register */
DECL|macro|CPU_EEPROM
mdefine_line|#define CPU_EEPROM      0x9     /* CPU Configuration EEPROM Register */
DECL|macro|INTMASK
mdefine_line|#define INTMASK         0xA     /* Interrupt Mask Register */
DECL|macro|INTSTAT
mdefine_line|#define INTSTAT         0xB     /* Interrupt Status Register */
DECL|macro|INTSET
mdefine_line|#define INTSET          0xC     /* Interrupt Set Register */
DECL|macro|INTCLR
mdefine_line|#define INTCLR          0xD     /* Interrupt Clear Register */
DECL|macro|PLD_REG
mdefine_line|#define PLD_REG(x)&t;((uint8_t*)(PLD_BASE+(x)))
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/* [jsun@junsun.net] PMON passes arguments in C main() style */
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|arg
)paren
(brace
r_int
id|i
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
id|mips_machgroup
op_assign
id|MACH_GROUP_MOMENCO
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_MOMENCO_OCELOT
suffix:semicolon
multiline_comment|/* turn off the Bit Error LED, which comes on automatically&n;&t; * at power-up reset */
op_star
id|PLD_REG
c_func
(paren
id|INTCLR
)paren
op_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* All the boards have at least 64MiB. If there&squot;s more, we&n;&t;   detect and register it later */
id|add_memory_region
c_func
(paren
l_int|0
comma
l_int|64
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
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
eof
