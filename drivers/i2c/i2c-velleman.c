multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-velleman.c i2c-hw access for Velleman K9000 adapters&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-96, 2000 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* $Id: i2c-velleman.c,v 1.19 2000/01/24 02:06:33 mds Exp $ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;  /* for 2.0 kernels to get NULL   */
macro_line|#include &lt;asm/errno.h&gt;     /* for 2.0 kernels to get ENODEV */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
multiline_comment|/* ----- global defines -----------------------------------------------&t;*/
DECL|macro|DEB
mdefine_line|#define DEB(x)&t;&t;/* should be reasonable open, close &amp;c. &t;*/
DECL|macro|DEB2
mdefine_line|#define DEB2(x) &t;/* low level debugging - very slow &t;&t;*/
DECL|macro|DEBE
mdefine_line|#define DEBE(x)&t;x&t;/* error messages &t;&t;&t;&t;*/
multiline_comment|/* Pin Port  Inverted&t;name&t;*/
DECL|macro|I2C_SDA
mdefine_line|#define I2C_SDA&t;&t;0x02&t;&t;/*  ctrl bit 1 &t;(inv)&t;*/
DECL|macro|I2C_SCL
mdefine_line|#define I2C_SCL&t;&t;0x08&t;&t;/*  ctrl bit 3 &t;(inv)&t;*/
DECL|macro|I2C_SDAIN
mdefine_line|#define I2C_SDAIN&t;0x10&t;&t;/* stat bit 4&t;&t;*/
DECL|macro|I2C_SCLIN
mdefine_line|#define I2C_SCLIN&t;0x08&t;&t;/* ctrl bit 3 (inv)(reads own output)*/
DECL|macro|I2C_DMASK
mdefine_line|#define I2C_DMASK&t;0xfd
DECL|macro|I2C_CMASK
mdefine_line|#define I2C_CMASK&t;0xf7
multiline_comment|/* --- Convenience defines for the parallel port:&t;&t;&t;*/
DECL|macro|BASE
mdefine_line|#define BASE&t;(unsigned int)(data)
DECL|macro|DATA
mdefine_line|#define DATA&t;BASE&t;&t;&t;/* Centronics data port&t;&t;*/
DECL|macro|STAT
mdefine_line|#define STAT&t;(BASE+1)&t;&t;/* Centronics status port&t;*/
DECL|macro|CTRL
mdefine_line|#define CTRL&t;(BASE+2)&t;&t;/* Centronics control port&t;*/
DECL|macro|DEFAULT_BASE
mdefine_line|#define DEFAULT_BASE 0x378
DECL|variable|base
r_static
r_int
id|base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ----- local functions --------------------------------------------------- */
DECL|function|bit_velle_setscl
r_static
r_void
id|bit_velle_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|CTRL
)paren
op_amp
id|I2C_CMASK
comma
id|CTRL
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|CTRL
)paren
op_or
id|I2C_SCL
comma
id|CTRL
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_velle_setsda
r_static
r_void
id|bit_velle_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|CTRL
)paren
op_amp
id|I2C_DMASK
comma
id|CTRL
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|CTRL
)paren
op_or
id|I2C_SDA
comma
id|CTRL
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_velle_getscl
r_static
r_int
id|bit_velle_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
l_int|0
op_eq
(paren
(paren
id|inb
c_func
(paren
id|CTRL
)paren
)paren
op_amp
id|I2C_SCLIN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_velle_getsda
r_static
r_int
id|bit_velle_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
l_int|0
op_ne
(paren
(paren
id|inb
c_func
(paren
id|STAT
)paren
)paren
op_amp
id|I2C_SDAIN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_velle_init
r_static
r_int
id|bit_velle_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|base
comma
(paren
id|base
op_eq
l_int|0x3bc
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|8
)paren
OL
l_int|0
)paren
(brace
id|DEBE
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c-velleman.o: Port %#x already in use.&bslash;n&quot;
comma
id|base
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
id|request_region
c_func
(paren
id|base
comma
(paren
id|base
op_eq
l_int|0x3bc
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|8
comma
l_string|&quot;i2c (Vellemann adapter)&quot;
)paren
suffix:semicolon
id|bit_velle_setsda
c_func
(paren
(paren
r_void
op_star
)paren
id|base
comma
l_int|1
)paren
suffix:semicolon
id|bit_velle_setscl
c_func
(paren
(paren
r_void
op_star
)paren
id|base
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_velle_exit
r_static
r_void
id|__exit
id|bit_velle_exit
c_func
(paren
r_void
)paren
(brace
id|release_region
c_func
(paren
id|base
comma
(paren
id|base
op_eq
l_int|0x3bc
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|bit_velle_reg
r_static
r_int
id|bit_velle_reg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_velle_unreg
r_static
r_int
id|bit_velle_unreg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_velle_inc_use
r_static
r_void
id|bit_velle_inc_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|bit_velle_dec_use
r_static
r_void
id|bit_velle_dec_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* ------------------------------------------------------------------------&n; * Encapsulate the above functions in the correct operations structure.&n; * This is only done when more than one hardware adapter is supported.&n; */
DECL|variable|bit_velle_data
r_static
r_struct
id|i2c_algo_bit_data
id|bit_velle_data
op_assign
(brace
l_int|NULL
comma
id|bit_velle_setsda
comma
id|bit_velle_setscl
comma
id|bit_velle_getsda
comma
id|bit_velle_getscl
comma
l_int|10
comma
l_int|10
comma
l_int|100
comma
multiline_comment|/*&t;waits, timeout */
)brace
suffix:semicolon
DECL|variable|bit_velle_ops
r_static
r_struct
id|i2c_adapter
id|bit_velle_ops
op_assign
(brace
l_string|&quot;Velleman K8000&quot;
comma
id|I2C_HW_B_VELLE
comma
l_int|NULL
comma
op_amp
id|bit_velle_data
comma
id|bit_velle_inc_use
comma
id|bit_velle_dec_use
comma
id|bit_velle_reg
comma
id|bit_velle_unreg
comma
)brace
suffix:semicolon
DECL|function|i2c_bitvelle_init
r_int
id|__init
id|i2c_bitvelle_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-velleman.o: i2c Velleman K8000 adapter module&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
(brace
multiline_comment|/* probe some values */
id|base
op_assign
id|DEFAULT_BASE
suffix:semicolon
id|bit_velle_data.data
op_assign
(paren
r_void
op_star
)paren
id|DEFAULT_BASE
suffix:semicolon
r_if
c_cond
(paren
id|bit_velle_init
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|bit_velle_ops
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
id|bit_velle_data.data
op_assign
(paren
r_void
op_star
)paren
id|base
suffix:semicolon
r_if
c_cond
(paren
id|bit_velle_init
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|bit_velle_ops
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;i2c-velleman.o: found device at %#x.&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Simon G. Vogl &lt;simon@tk.uni-linz.ac.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus adapter routines for Velleman K8000 adapter&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|base
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_bitvelle_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|bit_velle_ops
)paren
suffix:semicolon
id|bit_velle_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
