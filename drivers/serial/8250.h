multiline_comment|/*&n; *  linux/drivers/char/8250.h&n; *&n; *  Driver for 8250/16550-type serial ports&n; *&n; *  Based on drivers/char/serial.c, by Linus Torvalds, Theodore Ts&squot;o.&n; *&n; *  Copyright (C) 2001 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; *  $Id: 8250.h,v 1.8 2002/07/21 21:32:30 rmk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|struct|serial8250_probe
r_struct
id|serial8250_probe
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|pci_init_one
r_int
(paren
op_star
id|pci_init_one
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|pci_remove_one
r_void
(paren
op_star
id|pci_remove_one
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|pnp_init
r_void
(paren
op_star
id|pnp_init
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|serial8250_register_probe
c_func
(paren
r_struct
id|serial8250_probe
op_star
id|probe
)paren
suffix:semicolon
r_void
id|serial8250_unregister_probe
c_func
(paren
r_struct
id|serial8250_probe
op_star
id|probe
)paren
suffix:semicolon
r_void
id|serial8250_get_irq_map
c_func
(paren
r_int
r_int
op_star
id|map
)paren
suffix:semicolon
DECL|struct|old_serial_port
r_struct
id|old_serial_port
(brace
DECL|member|uart
r_int
r_int
id|uart
suffix:semicolon
DECL|member|base_baud
r_int
r_int
id|base_baud
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SERIAL_DEBUG_PCI
macro_line|#undef SERIAL_DEBUG_PCI
macro_line|#if defined(__i386__) &amp;&amp; (defined(CONFIG_M386) || defined(CONFIG_M486))
DECL|macro|SERIAL_INLINE
mdefine_line|#define SERIAL_INLINE
macro_line|#endif
macro_line|#ifdef SERIAL_INLINE
DECL|macro|_INLINE_
mdefine_line|#define _INLINE_ inline
macro_line|#else
DECL|macro|_INLINE_
mdefine_line|#define _INLINE_
macro_line|#endif
DECL|macro|PROBE_RSA
mdefine_line|#define PROBE_RSA&t;(1 &lt;&lt; 0)
DECL|macro|PROBE_ANY
mdefine_line|#define PROBE_ANY&t;(~0)
DECL|macro|HIGH_BITS_OFFSET
mdefine_line|#define HIGH_BITS_OFFSET ((sizeof(long)-sizeof(int))*8)
macro_line|#ifdef CONFIG_SERIAL_8250_SHARE_IRQ
DECL|macro|SERIAL8250_SHARE_IRQS
mdefine_line|#define SERIAL8250_SHARE_IRQS 1
macro_line|#else
DECL|macro|SERIAL8250_SHARE_IRQS
mdefine_line|#define SERIAL8250_SHARE_IRQS 0
macro_line|#endif
eof
