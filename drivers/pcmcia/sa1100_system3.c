multiline_comment|/*&n; * drivers/pcmcia/sa1100_system3.c&n; *&n; * PT Diagital Board PCMCIA specific routines&n; *&n; * Copyright (C) 2001 Stefan Eletzhofer &lt;stefan.eletzhofer@eletztrick.de&gt;&n; *&n; * $Id: sa1100_system3.c,v 1.1.4.2 2002/02/25 13:56:45 seletz Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * $Log: sa1100_system3.c,v $&n; * Revision 1.1.4.2  2002/02/25 13:56:45  seletz&n; * - more cleanups&n; * - setup interrupts for CF card only ATM&n; *&n; * Revision 1.1.4.1  2002/02/14 02:23:27  seletz&n; * - 2.5.2-rmk6 PCMCIA changes&n; *&n; * Revision 1.1.2.1  2002/02/13 23:49:33  seletz&n; * - added from 2.4.16-rmk2&n; * - cleanups&n; *&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
macro_line|#include &quot;sa1111_generic.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
macro_line|#&t;define DPRINTK( x, args... )&t;printk( &quot;%s: line %d: &quot;x, __FUNCTION__, __LINE__, ## args  );
macro_line|#else
DECL|macro|DPRINTK
macro_line|#&t;define DPRINTK( x, args... )&t;/* nix */
macro_line|#endif
DECL|function|system3_pcmcia_init
r_int
id|system3_pcmcia_init
c_func
(paren
r_struct
id|pcmcia_init
op_star
id|init
)paren
(brace
id|init-&gt;socket_irq
(braket
l_int|0
)braket
op_assign
id|IRQ_S0_READY_NINT
suffix:semicolon
id|init-&gt;socket_irq
(braket
l_int|1
)braket
op_assign
id|IRQ_S1_READY_NINT
suffix:semicolon
multiline_comment|/* Don&squot;t need no CD and BVD* interrupts */
r_return
l_int|2
suffix:semicolon
)brace
DECL|function|system3_pcmcia_shutdown
r_int
id|system3_pcmcia_shutdown
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|system3_pcmcia_configure_socket
r_int
id|system3_pcmcia_configure_socket
c_func
(paren
r_int
id|sock
comma
r_const
r_struct
id|pcmcia_configure
op_star
id|conf
)paren
(brace
multiline_comment|/* only CF ATM */
r_if
c_cond
(paren
id|sock
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|sa1111_pcmcia_configure_socket
c_func
(paren
id|sock
comma
id|conf
)paren
suffix:semicolon
)brace
DECL|function|system3_pcmcia_socket_state
r_static
r_void
id|system3_pcmcia_socket_state
c_func
(paren
r_int
id|sock
comma
r_struct
id|pcmcia_state
op_star
id|state
)paren
(brace
r_int
r_int
id|status
op_assign
id|PCSR
suffix:semicolon
r_switch
c_cond
(paren
id|sock
)paren
(brace
macro_line|#if 0 /* PCMCIA socket not yet connected */
r_case
l_int|0
suffix:colon
id|state-&gt;detect
op_assign
id|status
op_amp
id|PCSR_S0_DETECT
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;ready
op_assign
id|status
op_amp
id|PCSR_S0_READY
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
id|status
op_amp
id|PCSR_S0_BVD1
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
l_int|1
suffix:semicolon
id|state-&gt;wrprot
op_assign
id|status
op_amp
id|PCSR_S0_WP
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
l_int|1
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|1
suffix:colon
id|state-&gt;detect
op_assign
id|status
op_amp
id|PCSR_S1_DETECT
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;ready
op_assign
id|status
op_amp
id|PCSR_S1_READY
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
id|status
op_amp
id|PCSR_S1_BVD1
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
l_int|1
suffix:semicolon
id|state-&gt;wrprot
op_assign
id|status
op_amp
id|PCSR_S1_WP
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
l_int|1
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;Sock %d PCSR=0x%08lx, Sx_RDY_nIREQ=%d&bslash;n&quot;
comma
id|sock
comma
id|status
comma
id|state-&gt;ready
)paren
suffix:semicolon
)brace
DECL|variable|system3_pcmcia_ops
r_struct
id|pcmcia_low_level
id|system3_pcmcia_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|init
op_assign
id|system3_pcmcia_init
comma
dot
id|shutdown
op_assign
id|system3_pcmcia_shutdown
comma
dot
id|socket_state
op_assign
id|system3_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|system3_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|sa1111_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|sa1111_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_system3_init
r_int
id|__init
id|pcmcia_system3_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_pt_system3
c_func
(paren
)paren
)paren
id|ret
op_assign
id|sa1100_register_pcmcia
c_func
(paren
op_amp
id|system3_pcmcia_ops
comma
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_system3_exit
r_void
id|__exit
id|pcmcia_system3_exit
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|system3_pcmcia_ops
comma
id|dev
)paren
suffix:semicolon
)brace
eof
