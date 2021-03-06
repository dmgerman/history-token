multiline_comment|/*&n;    $Id: bttv-if.c,v 1.4 2004/11/17 18:47:47 kraxel Exp $&n;&n;    bttv-if.c  --  old gpio interface to other kernel modules&n;                   don&squot;t use in new code, will go away in 2.7&n;&t;&t;   have a look at bttv-gpio.c instead.&n;&n;    bttv - Bt848 frame grabber driver&n;&n;    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)&n;                           &amp; Marcus Metzler (mocm@thp.uni-koeln.de)&n;    (c) 1999-2003 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;bttvp.h&quot;
DECL|variable|bttv_get_cardinfo
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_cardinfo
)paren
suffix:semicolon
DECL|variable|bttv_get_pcidev
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_pcidev
)paren
suffix:semicolon
DECL|variable|bttv_get_id
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_id
)paren
suffix:semicolon
DECL|variable|bttv_gpio_enable
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_gpio_enable
)paren
suffix:semicolon
DECL|variable|bttv_read_gpio
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_read_gpio
)paren
suffix:semicolon
DECL|variable|bttv_write_gpio
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_write_gpio
)paren
suffix:semicolon
DECL|variable|bttv_get_gpio_queue
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_gpio_queue
)paren
suffix:semicolon
DECL|variable|bttv_i2c_call
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_i2c_call
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* Exported functions - for other modules which want to access the         */
multiline_comment|/*                      gpio ports (IR for example)                        */
multiline_comment|/*                      see bttv.h for comments                            */
DECL|function|bttv_get_cardinfo
r_int
id|bttv_get_cardinfo
c_func
(paren
r_int
r_int
id|card
comma
r_int
op_star
id|type
comma
r_int
op_star
id|cardid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;The bttv_* interface is obsolete and will go away,&bslash;n&quot;
l_string|&quot;please use the new, sysfs based interface instead.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|type
op_assign
id|bttvs
(braket
id|card
)braket
dot
id|c.type
suffix:semicolon
op_star
id|cardid
op_assign
id|bttvs
(braket
id|card
)braket
dot
id|cardid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_get_pcidev
r_struct
id|pci_dev
op_star
id|bttv_get_pcidev
c_func
(paren
r_int
r_int
id|card
)paren
(brace
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|bttvs
(braket
id|card
)braket
dot
id|c.pci
suffix:semicolon
)brace
DECL|function|bttv_get_id
r_int
id|bttv_get_id
c_func
(paren
r_int
r_int
id|card
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;The bttv_* interface is obsolete and will go away,&bslash;n&quot;
l_string|&quot;please use the new, sysfs based interface instead.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|bttvs
(braket
id|card
)braket
dot
id|c.type
suffix:semicolon
)brace
DECL|function|bttv_gpio_enable
r_int
id|bttv_gpio_enable
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
id|gpio_inout
c_func
(paren
id|mask
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bttv_gpio
)paren
id|bttv_gpio_tracking
c_func
(paren
id|btv
comma
l_string|&quot;extern enable&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_read_gpio
r_int
id|bttv_read_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
r_if
c_cond
(paren
id|btv-&gt;shutdown
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* prior setting BT848_GPIO_REG_INP is (probably) not needed&n;   because we set direct input on init */
op_star
id|data
op_assign
id|gpio_read
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_write_gpio
r_int
id|bttv_write_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
multiline_comment|/* prior setting BT848_GPIO_REG_INP is (probably) not needed&n;   because direct input is set on init */
id|gpio_bits
c_func
(paren
id|mask
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bttv_gpio
)paren
id|bttv_gpio_tracking
c_func
(paren
id|btv
comma
l_string|&quot;extern write&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_get_gpio_queue
id|wait_queue_head_t
op_star
id|bttv_get_gpio_queue
c_func
(paren
r_int
r_int
id|card
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bttvs
(braket
id|card
)braket
dot
id|shutdown
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
op_amp
id|btv-&gt;gpioq
suffix:semicolon
)brace
DECL|function|bttv_i2c_call
r_void
id|bttv_i2c_call
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
r_return
suffix:semicolon
id|bttv_call_i2c_clients
c_func
(paren
op_amp
id|bttvs
(braket
id|card
)braket
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
