multiline_comment|/*&n; * linux/drivers/pcmcia/sa1100_badge4.c&n; *&n; * BadgePAD 4 PCMCIA specific routines&n; *&n; *   Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; *&n; * Copyright (C) 2002 Hewlett-Packard Company&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/badge4.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1111_generic.h&quot;
multiline_comment|/*&n; * BadgePAD 4 Details&n; *&n; * PCM Vcc:&n; *&n; *  PCM Vcc on BadgePAD 4 can be jumpered for 3v3 (short pins 1 and 3&n; *  on JP6) or 5v0 (short pins 3 and 5 on JP6).&n; *&n; * PCM Vpp:&n; *&n; *  PCM Vpp on BadgePAD 4 can be jumpered for 12v0 (short pins 4 and 6&n; *  on JP6) or tied to PCM Vcc (short pins 2 and 4 on JP6).  N.B.,&n; *  12v0 operation requires that the power supply actually supply 12v0&n; *  via pin 7 of JP7.&n; *&n; * CF Vcc:&n; *&n; *  CF Vcc on BadgePAD 4 can be jumpered either for 3v3 (short pins 1&n; *  and 2 on JP10) or 5v0 (short pins 2 and 3 on JP10).&n; *&n; * Unfortunately there&squot;s no way programmatically to determine how a&n; * given board is jumpered.  This code assumes a default jumpering&n; * as described below.&n; *&n; * If the defaults aren&squot;t correct, you may override them with a pcmv&n; * setup argument: pcmv=&lt;pcm vcc&gt;,&lt;pcm vpp&gt;,&lt;cf vcc&gt;.  The units are&n; * tenths of volts; e.g. pcmv=33,120,50 indicates 3v3 PCM Vcc, 12v0&n; * PCM Vpp, and 5v0 CF Vcc.&n; *&n; */
DECL|variable|badge4_pcmvcc
r_static
r_int
id|badge4_pcmvcc
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* pins 3 and 5 jumpered on JP6 */
DECL|variable|badge4_pcmvpp
r_static
r_int
id|badge4_pcmvpp
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* pins 2 and 4 jumpered on JP6 */
DECL|variable|badge4_cfvcc
r_static
r_int
id|badge4_cfvcc
op_assign
l_int|33
suffix:semicolon
multiline_comment|/* pins 1 and 2 jumpered on JP10 */
DECL|function|complain_about_jumpering
r_static
r_void
id|complain_about_jumpering
c_func
(paren
r_const
r_char
op_star
id|whom
comma
r_const
r_char
op_star
id|supply
comma
r_int
id|given
comma
r_int
id|wanted
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: %s %d.%dV wanted but board is jumpered for %s %d.%dV operation&quot;
l_string|&quot;; re-jumper the board and/or use pcmv=xx,xx,xx&bslash;n&quot;
comma
id|whom
comma
id|supply
comma
id|wanted
op_div
l_int|10
comma
id|wanted
op_mod
l_int|10
comma
id|supply
comma
id|given
op_div
l_int|10
comma
id|given
op_mod
l_int|10
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|badge4_pcmcia_configure_socket
id|badge4_pcmcia_configure_socket
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
comma
r_const
id|socket_state_t
op_star
id|state
)paren
(brace
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|skt-&gt;nr
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
(paren
id|state-&gt;Vcc
op_ne
l_int|0
)paren
op_logical_and
(paren
id|state-&gt;Vcc
op_ne
id|badge4_pcmvcc
)paren
)paren
(brace
id|complain_about_jumpering
c_func
(paren
id|__FUNCTION__
comma
l_string|&quot;pcmvcc&quot;
comma
id|badge4_pcmvcc
comma
id|state-&gt;Vcc
)paren
suffix:semicolon
singleline_comment|// Apply power regardless of the jumpering.
singleline_comment|// return -1;
)brace
r_if
c_cond
(paren
(paren
id|state-&gt;Vpp
op_ne
l_int|0
)paren
op_logical_and
(paren
id|state-&gt;Vpp
op_ne
id|badge4_pcmvpp
)paren
)paren
(brace
id|complain_about_jumpering
c_func
(paren
id|__FUNCTION__
comma
l_string|&quot;pcmvpp&quot;
comma
id|badge4_pcmvpp
comma
id|state-&gt;Vpp
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
(paren
id|state-&gt;Vcc
op_ne
l_int|0
)paren
op_logical_and
(paren
id|state-&gt;Vcc
op_ne
id|badge4_cfvcc
)paren
)paren
(brace
id|complain_about_jumpering
c_func
(paren
id|__FUNCTION__
comma
l_string|&quot;cfvcc&quot;
comma
id|badge4_cfvcc
comma
id|state-&gt;Vcc
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|sa1111_pcmcia_configure_socket
c_func
(paren
id|skt
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|need5V
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|need5V
op_assign
(paren
(paren
id|state-&gt;Vcc
op_eq
l_int|50
)paren
op_logical_or
(paren
id|state-&gt;Vpp
op_eq
l_int|50
)paren
)paren
suffix:semicolon
id|badge4_set_5V
c_func
(paren
id|BADGE4_5V_PCMCIA_SOCK
c_func
(paren
id|skt-&gt;nr
)paren
comma
id|need5V
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|badge4_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|badge4_pcmcia_ops
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
id|sa1111_pcmcia_hw_init
comma
dot
id|shutdown
op_assign
id|sa1111_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|sa1111_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|badge4_pcmcia_configure_socket
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
DECL|function|pcmcia_badge4_init
r_int
id|pcmcia_badge4_init
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
id|machine_is_badge4
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: badge4_pcmvcc=%d, badge4_pcmvpp=%d, badge4_cfvcc=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|badge4_pcmvcc
comma
id|badge4_pcmvpp
comma
id|badge4_cfvcc
)paren
suffix:semicolon
id|ret
op_assign
id|sa11xx_drv_pcmcia_probe
c_func
(paren
id|dev
comma
op_amp
id|badge4_pcmcia_ops
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmv_setup
r_static
r_int
id|__init
id|pcmv_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_int
id|v
(braket
l_int|4
)braket
suffix:semicolon
id|s
op_assign
id|get_options
c_func
(paren
id|s
comma
id|ARRAY_SIZE
c_func
(paren
id|v
)paren
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
(braket
l_int|0
)braket
op_ge
l_int|1
)paren
id|badge4_pcmvcc
op_assign
id|v
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|v
(braket
l_int|0
)braket
op_ge
l_int|2
)paren
id|badge4_pcmvpp
op_assign
id|v
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|v
(braket
l_int|0
)braket
op_ge
l_int|3
)paren
id|badge4_cfvcc
op_assign
id|v
(braket
l_int|3
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pcmv=&quot;
comma
id|pcmv_setup
)paren
suffix:semicolon
eof
