multiline_comment|/*&n; *&t;Serial Device Initialisation for Lasi/Asp/Wax/Dino&n; *&n; *&t;(c) Copyright Matthew Wilcox &lt;willy@debian.org&gt; 2001-2002&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/parisc-device.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/serial.h&gt; /* for LASI_BASE_BAUD */
macro_line|#include &quot;8250.h&quot;
r_static
r_int
id|__init
DECL|function|serial_init_chip
id|serial_init_chip
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_static
r_int
id|serial_line_nr
suffix:semicolon
r_struct
id|uart_port
id|port
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
multiline_comment|/* We find some unattached serial ports by walking native&n;&t;&t; * busses.  These should be silently ignored.  Otherwise,&n;&t;&t; * what we have here is a missing parent device, so tell&n;&t;&t; * the user what they&squot;re missing.&n;&t;&t; */
r_if
c_cond
(paren
id|parisc_parent
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|id.hw_type
op_ne
id|HPHW_IOA
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Serial: device 0x%lx not configured.&bslash;n&quot;
l_string|&quot;Enable support for Wax, Lasi, Asp or Dino.&bslash;n&quot;
comma
id|dev-&gt;hpa
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|address
op_assign
id|dev-&gt;hpa
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;id.sversion
op_ne
l_int|0x8d
)paren
(brace
id|address
op_add_assign
l_int|0x800
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|uart_port
)paren
)paren
suffix:semicolon
id|port.mapbase
op_assign
id|address
suffix:semicolon
id|port.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|port.iotype
op_assign
id|UPIO_MEM
suffix:semicolon
id|port.flags
op_assign
id|UPF_IOREMAP
op_or
id|UPF_BOOT_AUTOCONF
suffix:semicolon
id|port.uartclk
op_assign
id|LASI_BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|port.dev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|err
op_assign
id|serial8250_register_port
c_func
(paren
op_amp
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;serial8250_register_port returned error %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|serial_tbl
r_static
r_struct
id|parisc_device_id
id|serial_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00075
)brace
comma
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x0008c
)brace
comma
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x0008d
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Hack.  Some machines have SERIAL_0 attached to Lasi and SERIAL_1&n; * attached to Dino.  Unfortunately, Dino appears before Lasi in the device&n; * tree.  To ensure that ttyS0 == SERIAL_0, we register two drivers; one&n; * which only knows about Lasi and then a second which will find all the&n; * other serial ports.  HPUX ignores this problem.&n; */
DECL|variable|lasi_tbl
r_static
r_struct
id|parisc_device_id
id|lasi_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x03B
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* C1xx/C1xxL */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x03C
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* B132L */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x03D
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* B160L */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x03E
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* B132L+ */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x03F
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* B180L+ */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x046
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* Rocky2 120 */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x047
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* Rocky2 150 */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x04E
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* Kiji L2 132 */
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
l_int|0x056
comma
l_int|0x0008C
)brace
comma
multiline_comment|/* Raven+ */
(brace
l_int|0
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|parisc
comma
id|serial_tbl
)paren
suffix:semicolon
DECL|variable|lasi_driver
r_static
r_struct
id|parisc_driver
id|lasi_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial_1&quot;
comma
dot
id|id_table
op_assign
id|lasi_tbl
comma
dot
id|probe
op_assign
id|serial_init_chip
comma
)brace
suffix:semicolon
DECL|variable|serial_driver
r_static
r_struct
id|parisc_driver
id|serial_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial&quot;
comma
dot
id|id_table
op_assign
id|serial_tbl
comma
dot
id|probe
op_assign
id|serial_init_chip
comma
)brace
suffix:semicolon
DECL|function|probe_serial_gsc
r_int
id|__init
id|probe_serial_gsc
c_func
(paren
r_void
)paren
(brace
id|register_parisc_driver
c_func
(paren
op_amp
id|lasi_driver
)paren
suffix:semicolon
id|register_parisc_driver
c_func
(paren
op_amp
id|serial_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|probe_serial_gsc
id|module_init
c_func
(paren
id|probe_serial_gsc
)paren
suffix:semicolon
eof
