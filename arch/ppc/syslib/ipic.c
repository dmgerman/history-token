multiline_comment|/*&n; * include/asm-ppc/ipic.c&n; *&n; * IPIC routines implementations.&n; *&n; * Copyright 2005 Freescale Semiconductor, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ipic.h&gt;
macro_line|#include &lt;asm/mpc83xx.h&gt;
macro_line|#include &quot;ipic.h&quot;
DECL|variable|p_ipic
r_static
r_struct
id|ipic
id|p_ipic
suffix:semicolon
DECL|variable|primary_ipic
r_static
r_struct
id|ipic
op_star
id|primary_ipic
suffix:semicolon
DECL|variable|ipic_info
r_static
r_struct
id|ipic_info
id|ipic_info
(braket
)braket
op_assign
(brace
(braket
l_int|9
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_D
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|24
comma
dot
id|prio_mask
op_assign
l_int|0
comma
)brace
comma
(braket
l_int|10
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_D
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|25
comma
dot
id|prio_mask
op_assign
l_int|1
comma
)brace
comma
(braket
l_int|11
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_D
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|26
comma
dot
id|prio_mask
op_assign
l_int|2
comma
)brace
comma
(braket
l_int|14
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_D
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|29
comma
dot
id|prio_mask
op_assign
l_int|5
comma
)brace
comma
(braket
l_int|15
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_D
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|30
comma
dot
id|prio_mask
op_assign
l_int|6
comma
)brace
comma
(braket
l_int|16
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_D
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|31
comma
dot
id|prio_mask
op_assign
l_int|7
comma
)brace
comma
(braket
l_int|17
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|1
comma
dot
id|prio_mask
op_assign
l_int|5
comma
)brace
comma
(braket
l_int|18
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|2
comma
dot
id|prio_mask
op_assign
l_int|6
comma
)brace
comma
(braket
l_int|19
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|3
comma
dot
id|prio_mask
op_assign
l_int|7
comma
)brace
comma
(braket
l_int|20
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|4
comma
dot
id|prio_mask
op_assign
l_int|4
comma
)brace
comma
(braket
l_int|21
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|5
comma
dot
id|prio_mask
op_assign
l_int|5
comma
)brace
comma
(braket
l_int|22
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|6
comma
dot
id|prio_mask
op_assign
l_int|6
comma
)brace
comma
(braket
l_int|23
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|7
comma
dot
id|prio_mask
op_assign
l_int|7
comma
)brace
comma
(braket
l_int|32
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|0
comma
dot
id|prio_mask
op_assign
l_int|0
comma
)brace
comma
(braket
l_int|33
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|1
comma
dot
id|prio_mask
op_assign
l_int|1
comma
)brace
comma
(braket
l_int|34
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|2
comma
dot
id|prio_mask
op_assign
l_int|2
comma
)brace
comma
(braket
l_int|35
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|3
comma
dot
id|prio_mask
op_assign
l_int|3
comma
)brace
comma
(braket
l_int|36
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|4
comma
dot
id|prio_mask
op_assign
l_int|4
comma
)brace
comma
(braket
l_int|37
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|5
comma
dot
id|prio_mask
op_assign
l_int|5
comma
)brace
comma
(braket
l_int|38
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|6
comma
dot
id|prio_mask
op_assign
l_int|6
comma
)brace
comma
(braket
l_int|39
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_H
comma
dot
id|prio
op_assign
id|IPIC_SIPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_H
comma
dot
id|bit
op_assign
l_int|7
comma
dot
id|prio_mask
op_assign
l_int|7
comma
)brace
comma
(braket
l_int|48
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SEPNR
comma
dot
id|mask
op_assign
id|IPIC_SEMSR
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SEFCR
comma
dot
id|bit
op_assign
l_int|0
comma
dot
id|prio_mask
op_assign
l_int|4
comma
)brace
comma
(braket
l_int|64
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|0
comma
dot
id|prio_mask
op_assign
l_int|0
comma
)brace
comma
(braket
l_int|65
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|1
comma
dot
id|prio_mask
op_assign
l_int|1
comma
)brace
comma
(braket
l_int|66
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|2
comma
dot
id|prio_mask
op_assign
l_int|2
comma
)brace
comma
(braket
l_int|67
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_A
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|3
comma
dot
id|prio_mask
op_assign
l_int|3
comma
)brace
comma
(braket
l_int|68
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|4
comma
dot
id|prio_mask
op_assign
l_int|0
comma
)brace
comma
(braket
l_int|69
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|5
comma
dot
id|prio_mask
op_assign
l_int|1
comma
)brace
comma
(braket
l_int|70
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|6
comma
dot
id|prio_mask
op_assign
l_int|2
comma
)brace
comma
(braket
l_int|71
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
id|IPIC_SMPRR_B
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|7
comma
dot
id|prio_mask
op_assign
l_int|3
comma
)brace
comma
(braket
l_int|72
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|8
comma
)brace
comma
(braket
l_int|73
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|9
comma
)brace
comma
(braket
l_int|74
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|10
comma
)brace
comma
(braket
l_int|75
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|11
comma
)brace
comma
(braket
l_int|76
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|12
comma
)brace
comma
(braket
l_int|77
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|13
comma
)brace
comma
(braket
l_int|78
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|14
comma
)brace
comma
(braket
l_int|79
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|15
comma
)brace
comma
(braket
l_int|80
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|16
comma
)brace
comma
(braket
l_int|84
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|20
comma
)brace
comma
(braket
l_int|85
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|21
comma
)brace
comma
(braket
l_int|90
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|26
comma
)brace
comma
(braket
l_int|91
)braket
op_assign
(brace
dot
id|pend
op_assign
id|IPIC_SIPNR_H
comma
dot
id|mask
op_assign
id|IPIC_SIMSR_L
comma
dot
id|prio
op_assign
l_int|0
comma
dot
id|force
op_assign
id|IPIC_SIFCR_L
comma
dot
id|bit
op_assign
l_int|27
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|ipic_read
r_static
r_inline
id|u32
id|ipic_read
c_func
(paren
r_volatile
id|u32
id|__iomem
op_star
id|base
comma
r_int
r_int
id|reg
)paren
(brace
r_return
id|in_be32
c_func
(paren
id|base
op_plus
(paren
id|reg
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipic_write
r_static
r_inline
r_void
id|ipic_write
c_func
(paren
r_volatile
id|u32
id|__iomem
op_star
id|base
comma
r_int
r_int
id|reg
comma
id|u32
id|value
)paren
(brace
id|out_be32
c_func
(paren
id|base
op_plus
(paren
id|reg
op_rshift
l_int|2
)paren
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|ipic_from_irq
r_static
r_inline
r_struct
id|ipic
op_star
id|ipic_from_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
id|primary_ipic
suffix:semicolon
)brace
DECL|function|ipic_enable_irq
r_static
r_void
id|ipic_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|ipic_from_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
r_int
id|src
op_assign
id|irq
op_minus
id|ipic-&gt;irq_offset
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|mask
)paren
suffix:semicolon
id|temp
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|ipic_info
(braket
id|src
)braket
dot
id|bit
)paren
)paren
suffix:semicolon
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|mask
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|ipic_disable_irq
r_static
r_void
id|ipic_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|ipic_from_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
r_int
id|src
op_assign
id|irq
op_minus
id|ipic-&gt;irq_offset
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|mask
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|ipic_info
(braket
id|src
)braket
dot
id|bit
)paren
)paren
suffix:semicolon
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|mask
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|ipic_disable_irq_and_ack
r_static
r_void
id|ipic_disable_irq_and_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|ipic_from_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
r_int
id|src
op_assign
id|irq
op_minus
id|ipic-&gt;irq_offset
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|ipic_disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|pend
)paren
suffix:semicolon
id|temp
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|ipic_info
(braket
id|src
)braket
dot
id|bit
)paren
)paren
suffix:semicolon
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|pend
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|ipic_end_irq
r_static
r_void
id|ipic_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|ipic_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ipic
r_struct
id|hw_interrupt_type
id|ipic
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot; IPIC  &quot;
comma
dot
id|enable
op_assign
id|ipic_enable_irq
comma
dot
id|disable
op_assign
id|ipic_disable_irq
comma
dot
id|ack
op_assign
id|ipic_disable_irq_and_ack
comma
dot
id|end
op_assign
id|ipic_end_irq
comma
)brace
suffix:semicolon
DECL|function|ipic_init
r_void
id|__init
id|ipic_init
c_func
(paren
id|phys_addr_t
id|phys_addr
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|irq_offset
comma
r_int
r_char
op_star
id|senses
comma
r_int
r_int
id|senses_count
)paren
(brace
id|u32
id|i
comma
id|temp
op_assign
l_int|0
suffix:semicolon
id|primary_ipic
op_assign
op_amp
id|p_ipic
suffix:semicolon
id|primary_ipic-&gt;regs
op_assign
id|ioremap
c_func
(paren
id|phys_addr
comma
id|MPC83xx_IPIC_SIZE
)paren
suffix:semicolon
id|primary_ipic-&gt;irq_offset
op_assign
id|irq_offset
suffix:semicolon
id|ipic_write
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SICNR
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* default priority scheme is grouped. If spread mode is required&n;&t; * configure SICFR accordingly */
r_if
c_cond
(paren
id|flags
op_amp
id|IPIC_SPREADMODE_GRP_A
)paren
id|temp
op_or_assign
id|SICFR_IPSA
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IPIC_SPREADMODE_GRP_D
)paren
id|temp
op_or_assign
id|SICFR_IPSD
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IPIC_SPREADMODE_MIX_A
)paren
id|temp
op_or_assign
id|SICFR_MPSA
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IPIC_SPREADMODE_MIX_B
)paren
id|temp
op_or_assign
id|SICFR_MPSB
suffix:semicolon
id|ipic_write
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SICNR
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* handle MCP route */
id|temp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IPIC_DISABLE_MCP_OUT
)paren
id|temp
op_assign
id|SERCR_MCPR
suffix:semicolon
id|ipic_write
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SERCR
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* handle routing of IRQ0 to MCP */
id|temp
op_assign
id|ipic_read
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SEMSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IPIC_IRQ0_MCP
)paren
id|temp
op_or_assign
id|SEMSR_SIRQ0
suffix:semicolon
r_else
id|temp
op_and_assign
op_complement
id|SEMSR_SIRQ0
suffix:semicolon
id|ipic_write
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SEMSR
comma
id|temp
)paren
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
id|NR_IPIC_INTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
op_plus
id|irq_offset
)braket
dot
id|handler
op_assign
op_amp
id|ipic
suffix:semicolon
id|irq_desc
(braket
id|i
op_plus
id|irq_offset
)braket
dot
id|status
op_assign
id|IRQ_LEVEL
suffix:semicolon
)brace
id|temp
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
id|senses_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|senses
(braket
id|i
)braket
op_amp
id|IRQ_SENSE_MASK
)paren
op_eq
id|IRQ_SENSE_EDGE
)paren
(brace
id|temp
op_or_assign
l_int|1
op_lshift
(paren
l_int|16
op_minus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
id|irq_desc
(braket
id|i
op_plus
id|irq_offset
op_plus
id|MPC83xx_IRQ_EXT1
op_minus
l_int|1
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
r_else
id|irq_desc
(braket
id|irq_offset
op_plus
id|MPC83xx_IRQ_EXT0
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|ipic_write
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SECNR
comma
id|temp
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;IPIC (%d IRQ sources, %d External IRQs) at %p&bslash;n&quot;
comma
id|NR_IPIC_INTS
comma
id|senses_count
comma
id|primary_ipic-&gt;regs
)paren
suffix:semicolon
)brace
DECL|function|ipic_set_priority
r_int
id|ipic_set_priority
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|priority
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|ipic_from_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
r_int
id|src
op_assign
id|irq
op_minus
id|ipic-&gt;irq_offset
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|priority
OG
l_int|7
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|src
OG
l_int|127
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ipic_info
(braket
id|src
)braket
dot
id|prio
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|prio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priority
OL
l_int|4
)paren
(brace
id|temp
op_and_assign
op_complement
(paren
l_int|0x7
op_lshift
(paren
l_int|20
op_plus
(paren
l_int|3
op_minus
id|priority
)paren
op_star
l_int|3
)paren
)paren
suffix:semicolon
id|temp
op_or_assign
id|ipic_info
(braket
id|src
)braket
dot
id|prio_mask
op_lshift
(paren
l_int|20
op_plus
(paren
l_int|3
op_minus
id|priority
)paren
op_star
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp
op_and_assign
op_complement
(paren
l_int|0x7
op_lshift
(paren
l_int|4
op_plus
(paren
l_int|7
op_minus
id|priority
)paren
op_star
l_int|3
)paren
)paren
suffix:semicolon
id|temp
op_or_assign
id|ipic_info
(braket
id|src
)braket
dot
id|prio_mask
op_lshift
(paren
l_int|4
op_plus
(paren
l_int|7
op_minus
id|priority
)paren
op_star
l_int|3
)paren
suffix:semicolon
)brace
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|ipic_info
(braket
id|src
)braket
dot
id|prio
comma
id|temp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipic_set_highest_priority
r_void
id|ipic_set_highest_priority
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|ipic_from_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
r_int
id|src
op_assign
id|irq
op_minus
id|ipic-&gt;irq_offset
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|IPIC_SICFR
)paren
suffix:semicolon
multiline_comment|/* clear and set HPI */
id|temp
op_and_assign
l_int|0x7f000000
suffix:semicolon
id|temp
op_or_assign
(paren
id|src
op_amp
l_int|0x7f
)paren
op_lshift
l_int|24
suffix:semicolon
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|IPIC_SICFR
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|ipic_set_default_priority
r_void
id|ipic_set_default_priority
c_func
(paren
r_void
)paren
(brace
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_TSEC1_TX
comma
l_int|0
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_TSEC1_RX
comma
l_int|1
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_TSEC1_ERROR
comma
l_int|2
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_TSEC2_TX
comma
l_int|3
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_TSEC2_RX
comma
l_int|4
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_TSEC2_ERROR
comma
l_int|5
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_USB2_DR
comma
l_int|6
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_USB2_MPH
comma
l_int|7
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_UART1
comma
l_int|0
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_UART2
comma
l_int|1
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_SEC2
comma
l_int|2
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_IIC1
comma
l_int|5
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_IIC2
comma
l_int|6
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_SPI
comma
l_int|7
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_RTC_SEC
comma
l_int|0
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_PIT
comma
l_int|1
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_PCI1
comma
l_int|2
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_PCI2
comma
l_int|3
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT0
comma
l_int|4
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT1
comma
l_int|5
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT2
comma
l_int|6
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT3
comma
l_int|7
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_RTC_ALR
comma
l_int|0
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_MU
comma
l_int|1
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_SBA
comma
l_int|2
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_DMA
comma
l_int|3
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT4
comma
l_int|4
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT5
comma
l_int|5
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT6
comma
l_int|6
)paren
suffix:semicolon
id|ipic_set_priority
c_func
(paren
id|MPC83xx_IRQ_EXT7
comma
l_int|7
)paren
suffix:semicolon
)brace
DECL|function|ipic_enable_mcp
r_void
id|ipic_enable_mcp
c_func
(paren
r_enum
id|ipic_mcp_irq
id|mcp_irq
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|primary_ipic
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|IPIC_SERMR
)paren
suffix:semicolon
id|temp
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|mcp_irq
)paren
)paren
suffix:semicolon
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|IPIC_SERMR
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|ipic_disable_mcp
r_void
id|ipic_disable_mcp
c_func
(paren
r_enum
id|ipic_mcp_irq
id|mcp_irq
)paren
(brace
r_struct
id|ipic
op_star
id|ipic
op_assign
id|primary_ipic
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|temp
op_assign
id|ipic_read
c_func
(paren
id|ipic-&gt;regs
comma
id|IPIC_SERMR
)paren
suffix:semicolon
id|temp
op_and_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|mcp_irq
)paren
)paren
suffix:semicolon
id|ipic_write
c_func
(paren
id|ipic-&gt;regs
comma
id|IPIC_SERMR
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|ipic_get_mcp_status
id|u32
id|ipic_get_mcp_status
c_func
(paren
r_void
)paren
(brace
r_return
id|ipic_read
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SERMR
)paren
suffix:semicolon
)brace
DECL|function|ipic_clear_mcp_status
r_void
id|ipic_clear_mcp_status
c_func
(paren
id|u32
id|mask
)paren
(brace
id|ipic_write
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SERMR
comma
id|mask
)paren
suffix:semicolon
)brace
multiline_comment|/* Return an interrupt vector or -1 if no interrupt is pending. */
DECL|function|ipic_get_irq
r_int
id|ipic_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
id|irq
op_assign
id|ipic_read
c_func
(paren
id|primary_ipic-&gt;regs
comma
id|IPIC_SIVCR
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
multiline_comment|/* 0 --&gt; no irq is pending */
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
DECL|variable|ipic_sysclass
r_static
r_struct
id|sysdev_class
id|ipic_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;ipic&quot;
)paren
comma
)brace
suffix:semicolon
DECL|variable|device_ipic
r_static
r_struct
id|sys_device
id|device_ipic
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|ipic_sysclass
comma
)brace
suffix:semicolon
DECL|function|init_ipic_sysfs
r_static
r_int
id|__init
id|init_ipic_sysfs
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|primary_ipic-&gt;regs
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Registering ipic with sysfs...&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|ipic_sysclass
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed registering ipic sys class&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|rc
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|device_ipic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed registering ipic sys device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_ipic_sysfs
id|subsys_initcall
c_func
(paren
id|init_ipic_sysfs
)paren
suffix:semicolon
eof
