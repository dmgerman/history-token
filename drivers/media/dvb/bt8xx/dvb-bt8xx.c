multiline_comment|/*&n; * Bt8xx based DVB adapter driver &n; *&n; * Copyright (C) 2002,2003 Florian Schirmer &lt;jolt@tuxbox.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb-bt8xx.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
macro_line|#include &quot;bt878.h&quot;
multiline_comment|/* ID THAT MUST GO INTO i2c ids */
macro_line|#ifndef  I2C_DRIVERID_DVB_BT878A
DECL|macro|I2C_DRIVERID_DVB_BT878A
macro_line|# define I2C_DRIVERID_DVB_BT878A I2C_DRIVERID_EXP0+10
macro_line|#endif
DECL|macro|dprintk
mdefine_line|#define dprintk if (debug) printk
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|card_list
)paren
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|function|dvb_bt8xx_task
r_static
r_void
id|dvb_bt8xx_task
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
op_assign
(paren
r_struct
id|dvb_bt8xx_card
op_star
)paren
id|data
suffix:semicolon
singleline_comment|//printk(&quot;%d &quot;, finished_block);
r_while
c_loop
(paren
id|card-&gt;bt-&gt;last_block
op_ne
id|card-&gt;bt-&gt;finished_block
)paren
(brace
(paren
id|card-&gt;bt-&gt;TS_Size
ques
c_cond
id|dvb_dmx_swfilter_204
suffix:colon
id|dvb_dmx_swfilter
)paren
(paren
op_amp
id|card-&gt;demux
comma
op_amp
id|card-&gt;bt-&gt;buf_cpu
(braket
id|card-&gt;bt-&gt;last_block
op_star
id|card-&gt;bt-&gt;block_bytes
)braket
comma
id|card-&gt;bt-&gt;block_bytes
)paren
suffix:semicolon
id|card-&gt;bt-&gt;last_block
op_assign
(paren
id|card-&gt;bt-&gt;last_block
op_plus
l_int|1
)paren
op_mod
id|card-&gt;bt-&gt;block_count
suffix:semicolon
)brace
)brace
DECL|function|dvb_bt8xx_start_feed
r_static
r_int
id|dvb_bt8xx_start_feed
c_func
(paren
r_struct
id|dvb_demux_feed
op_star
id|dvbdmxfeed
)paren
(brace
r_struct
id|dvb_demux
op_star
id|dvbdmx
op_assign
id|dvbdmxfeed-&gt;demux
suffix:semicolon
r_struct
id|dvb_bt8xx_card
op_star
id|card
op_assign
id|dvbdmx-&gt;priv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;dvb_bt8xx: start_feed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdmx-&gt;dmx.frontend
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;active
)paren
r_return
l_int|0
suffix:semicolon
id|card-&gt;active
op_assign
l_int|1
suffix:semicolon
singleline_comment|//&t;bt878_start(card-&gt;bt, card-&gt;gpio_mode);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_stop_feed
r_static
r_int
id|dvb_bt8xx_stop_feed
c_func
(paren
r_struct
id|dvb_demux_feed
op_star
id|dvbdmxfeed
)paren
(brace
r_struct
id|dvb_demux
op_star
id|dvbdmx
op_assign
id|dvbdmxfeed-&gt;demux
suffix:semicolon
r_struct
id|dvb_bt8xx_card
op_star
id|card
op_assign
id|dvbdmx-&gt;priv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;dvb_bt8xx: stop_feed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdmx-&gt;dmx.frontend
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;active
)paren
r_return
l_int|0
suffix:semicolon
singleline_comment|//&t;bt878_stop(card-&gt;bt);
id|card-&gt;active
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|master_xfer
r_static
r_int
id|master_xfer
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
op_assign
id|i2c-&gt;data
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|card-&gt;bt-&gt;gpio_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|retval
op_assign
id|i2c_transfer
c_func
(paren
id|card-&gt;i2c_adapter
comma
(paren
r_struct
id|i2c_msg
op_star
)paren
id|msgs
comma
id|num
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|card-&gt;bt-&gt;gpio_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|is_pci_slot_eq
r_static
r_int
id|is_pci_slot_eq
c_func
(paren
r_struct
id|pci_dev
op_star
id|adev
comma
r_struct
id|pci_dev
op_star
id|bdev
)paren
(brace
r_if
c_cond
(paren
(paren
id|adev-&gt;subsystem_vendor
op_eq
id|bdev-&gt;subsystem_vendor
)paren
op_logical_and
(paren
id|adev-&gt;subsystem_device
op_eq
id|bdev-&gt;subsystem_device
)paren
op_logical_and
(paren
id|adev-&gt;bus-&gt;number
op_eq
id|bdev-&gt;bus-&gt;number
)paren
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|adev-&gt;devfn
)paren
op_eq
id|PCI_SLOT
c_func
(paren
id|bdev-&gt;devfn
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_878_match
r_static
r_struct
id|bt878
id|__init
op_star
id|dvb_bt8xx_878_match
c_func
(paren
r_int
r_int
id|bttv_nr
comma
r_struct
id|pci_dev
op_star
id|bttv_pci_dev
)paren
(brace
r_int
r_int
id|card_nr
suffix:semicolon
multiline_comment|/* Hmm, n squared. Hope n is small */
r_for
c_loop
(paren
id|card_nr
op_assign
l_int|0
suffix:semicolon
id|card_nr
OL
id|bt878_num
suffix:semicolon
id|card_nr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|is_pci_slot_eq
c_func
(paren
id|bt878
(braket
id|card_nr
)braket
dot
id|dev
comma
id|bttv_pci_dev
)paren
)paren
r_return
op_amp
id|bt878
(braket
id|card_nr
)braket
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_card_match
r_static
r_int
id|__init
id|dvb_bt8xx_card_match
c_func
(paren
r_int
r_int
id|bttv_nr
comma
r_char
op_star
id|card_name
comma
id|u32
id|gpio_mode
comma
id|u32
id|op_sync_orin
comma
id|u32
id|irq_err_ignore
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
r_struct
id|pci_dev
op_star
id|bttv_pci_dev
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;dvb_bt8xx: identified card%d as %s&bslash;n&quot;
comma
id|bttv_nr
comma
id|card_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|card
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_bt8xx_card
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|card
)paren
)paren
suffix:semicolon
id|card-&gt;bttv_nr
op_assign
id|bttv_nr
suffix:semicolon
id|strncpy
c_func
(paren
id|card-&gt;card_name
comma
id|card_name
comma
r_sizeof
(paren
id|card_name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bttv_pci_dev
op_assign
id|bttv_get_pcidev
c_func
(paren
id|bttv_nr
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: no pci device for card %d&bslash;n&quot;
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|card-&gt;bt
op_assign
id|dvb_bt8xx_878_match
c_func
(paren
id|card-&gt;bttv_nr
comma
id|bttv_pci_dev
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: unable to determine DMA core of card %d&bslash;n&quot;
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|init_MUTEX
c_func
(paren
op_amp
id|card-&gt;bt-&gt;gpio_lock
)paren
suffix:semicolon
id|card-&gt;bt-&gt;bttv_nr
op_assign
id|bttv_nr
suffix:semicolon
id|card-&gt;gpio_mode
op_assign
id|gpio_mode
suffix:semicolon
id|card-&gt;op_sync_orin
op_assign
id|op_sync_orin
suffix:semicolon
id|card-&gt;irq_err_ignore
op_assign
id|irq_err_ignore
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|card-&gt;list
comma
op_amp
id|card_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_find_by_i2c_adap
r_static
r_struct
id|dvb_bt8xx_card
op_star
id|dvb_bt8xx_find_by_i2c_adap
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
r_struct
id|list_head
op_star
id|item
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;find by i2c adap: checking &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|adap-&gt;name
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|item
comma
op_amp
id|card_list
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|item
comma
r_struct
id|dvb_bt8xx_card
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;i2c_adapter
op_eq
id|adap
)paren
r_return
id|card
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_find_by_pci
r_static
r_struct
id|dvb_bt8xx_card
op_star
id|dvb_bt8xx_find_by_pci
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
r_struct
id|list_head
op_star
id|item
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;find by pci: checking &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|adap-&gt;name
)paren
suffix:semicolon
id|dev
op_assign
id|adap-&gt;dev.parent
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev
)paren
(brace
multiline_comment|/* shoudn&squot;t happen with 2.6.0-test7 + newer */
id|printk
c_func
(paren
l_string|&quot;attach: Huh? i2c adapter not in sysfs tree?&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|pci
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|item
comma
op_amp
id|card_list
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|item
comma
r_struct
id|dvb_bt8xx_card
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_pci_slot_eq
c_func
(paren
id|pci
comma
id|card-&gt;bt-&gt;dev
)paren
)paren
(brace
r_return
id|card
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_attach
r_static
r_int
id|dvb_bt8xx_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;attach: checking &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|adap-&gt;name
)paren
suffix:semicolon
multiline_comment|/* looking for bt878 cards ... */
r_if
c_cond
(paren
id|adap-&gt;id
op_ne
(paren
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|card
op_assign
id|dvb_bt8xx_find_by_pci
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
r_return
l_int|0
suffix:semicolon
id|card-&gt;i2c_adapter
op_assign
id|adap
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;attach: &bslash;&quot;%s&bslash;&quot;, to card %d&bslash;n&quot;
comma
id|adap-&gt;name
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
id|try_module_get
c_func
(paren
id|adap-&gt;owner
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_i2c_adap_free
r_static
r_void
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
id|module_put
c_func
(paren
id|adap-&gt;owner
)paren
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_detach
r_static
r_int
id|dvb_bt8xx_detach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
id|card
op_assign
id|dvb_bt8xx_find_by_i2c_adap
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* This should not happen. We have locked the module! */
id|printk
c_func
(paren
l_string|&quot;detach: &bslash;&quot;%s&bslash;&quot;, for card %d removed&bslash;n&quot;
comma
id|adap-&gt;name
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dvb_bt8xx_driver
r_static
r_struct
id|i2c_driver
id|dvb_bt8xx_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;dvb_bt8xx&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_DVB_BT878A
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|dvb_bt8xx_attach
comma
dot
id|detach_adapter
op_assign
id|dvb_bt8xx_detach
comma
)brace
suffix:semicolon
DECL|function|dvb_bt8xx_get_adaps
r_static
r_void
id|__init
id|dvb_bt8xx_get_adaps
c_func
(paren
r_void
)paren
(brace
id|i2c_add_driver
c_func
(paren
op_amp
id|dvb_bt8xx_driver
)paren
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_exit_adaps
r_static
r_void
id|__exit
id|dvb_bt8xx_exit_adaps
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|dvb_bt8xx_driver
)paren
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_load_card
r_static
r_int
id|__init
id|dvb_bt8xx_load_card
c_func
(paren
r_struct
id|dvb_bt8xx_card
op_star
id|card
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;i2c_adapter
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: unable to determine i2c adaptor of card %d, deleting&bslash;n&quot;
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|result
op_assign
id|dvb_register_adapter
c_func
(paren
op_amp
id|card-&gt;dvb_adapter
comma
id|card-&gt;card_name
comma
id|THIS_MODULE
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_register_adapter failed (errno = %d)&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|card-&gt;bt-&gt;adap_ptr
op_assign
id|card-&gt;dvb_adapter
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dvb_register_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_register_i2c_bus of card%d failed&bslash;n&quot;
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|card-&gt;demux
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dvb_demux
)paren
)paren
suffix:semicolon
id|card-&gt;demux.dmx.capabilities
op_assign
id|DMX_TS_FILTERING
op_or
id|DMX_SECTION_FILTERING
op_or
id|DMX_MEMORY_BASED_FILTERING
suffix:semicolon
id|card-&gt;demux.priv
op_assign
id|card
suffix:semicolon
id|card-&gt;demux.filternum
op_assign
l_int|256
suffix:semicolon
id|card-&gt;demux.feednum
op_assign
l_int|256
suffix:semicolon
id|card-&gt;demux.start_feed
op_assign
id|dvb_bt8xx_start_feed
suffix:semicolon
id|card-&gt;demux.stop_feed
op_assign
id|dvb_bt8xx_stop_feed
suffix:semicolon
id|card-&gt;demux.write_to_decoder
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|dvb_dmx_init
c_func
(paren
op_amp
id|card-&gt;demux
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_dmx_init failed (errno = %d)&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|dvb_unregister_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|card-&gt;dmxdev.filternum
op_assign
l_int|256
suffix:semicolon
id|card-&gt;dmxdev.demux
op_assign
op_amp
id|card-&gt;demux.dmx
suffix:semicolon
id|card-&gt;dmxdev.capabilities
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|dvb_dmxdev_init
c_func
(paren
op_amp
id|card-&gt;dmxdev
comma
id|card-&gt;dvb_adapter
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_dmxdev_init failed (errno = %d)&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|dvb_dmx_release
c_func
(paren
op_amp
id|card-&gt;demux
)paren
suffix:semicolon
id|dvb_unregister_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|card-&gt;fe_hw.source
op_assign
id|DMX_FRONTEND_0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|card-&gt;demux.dmx
dot
id|add_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_hw
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_dmx_init failed (errno = %d)&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|dvb_dmxdev_release
c_func
(paren
op_amp
id|card-&gt;dmxdev
)paren
suffix:semicolon
id|dvb_dmx_release
c_func
(paren
op_amp
id|card-&gt;demux
)paren
suffix:semicolon
id|dvb_unregister_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|card-&gt;fe_mem.source
op_assign
id|DMX_MEMORY_FE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|card-&gt;demux.dmx
dot
id|add_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_mem
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_dmx_init failed (errno = %d)&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|card-&gt;demux.dmx
dot
id|remove_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_hw
)paren
suffix:semicolon
id|dvb_dmxdev_release
c_func
(paren
op_amp
id|card-&gt;dmxdev
)paren
suffix:semicolon
id|dvb_dmx_release
c_func
(paren
op_amp
id|card-&gt;demux
)paren
suffix:semicolon
id|dvb_unregister_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|result
op_assign
id|card-&gt;demux.dmx
dot
id|connect_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_hw
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dvb_bt8xx: dvb_dmx_init failed (errno = %d)&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|card-&gt;demux.dmx
dot
id|remove_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_mem
)paren
suffix:semicolon
id|card-&gt;demux.dmx
dot
id|remove_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_hw
)paren
suffix:semicolon
id|dvb_dmxdev_release
c_func
(paren
op_amp
id|card-&gt;dmxdev
)paren
suffix:semicolon
id|dvb_dmx_release
c_func
(paren
op_amp
id|card-&gt;demux
)paren
suffix:semicolon
id|dvb_unregister_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|dvb_net_init
c_func
(paren
id|card-&gt;dvb_adapter
comma
op_amp
id|card-&gt;dvbnet
comma
op_amp
id|card-&gt;demux.dmx
)paren
suffix:semicolon
id|tasklet_init
c_func
(paren
op_amp
id|card-&gt;bt-&gt;tasklet
comma
id|dvb_bt8xx_task
comma
(paren
r_int
r_int
)paren
id|card
)paren
suffix:semicolon
id|bt878_start
c_func
(paren
id|card-&gt;bt
comma
id|card-&gt;gpio_mode
comma
id|card-&gt;op_sync_orin
comma
id|card-&gt;irq_err_ignore
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_load_all
r_static
r_int
id|__init
id|dvb_bt8xx_load_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|entry_safe
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|entry
comma
id|entry_safe
comma
op_amp
id|card_list
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|dvb_bt8xx_card
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dvb_bt8xx_load_card
c_func
(paren
id|card
)paren
OL
l_int|0
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|card-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|BT878_NEBULA
mdefine_line|#define BT878_NEBULA&t;0x68
DECL|macro|BT878_TWINHAN_DST
mdefine_line|#define BT878_TWINHAN_DST 0x71
DECL|function|dvb_bt8xx_init
r_static
r_int
id|__init
id|dvb_bt8xx_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|card_nr
op_assign
l_int|0
suffix:semicolon
r_int
id|card_id
suffix:semicolon
r_int
id|card_type
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;dvb_bt8xx: enumerating available bttv cards...&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bttv_get_cardinfo
c_func
(paren
id|card_nr
comma
op_amp
id|card_type
comma
op_amp
id|card_id
)paren
op_eq
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|card_id
)paren
(brace
r_case
l_int|0x001C11BD
suffix:colon
id|dvb_bt8xx_card_match
c_func
(paren
id|card_nr
comma
l_string|&quot;Pinnacle PCTV DVB-S&quot;
comma
l_int|0x0400C060
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 26, 15, 14, 6, 5 &n;&t;&t;&t;&t; * A_G2X  DA_DPM DA_SBR DA_IOM_DA &n;&t;&t;&t;&t; * DA_APP(parallel) */
r_break
suffix:semicolon
r_case
l_int|0x01010071
suffix:colon
id|nebula
suffix:colon
id|dvb_bt8xx_card_match
c_func
(paren
id|card_nr
comma
l_string|&quot;Nebula DigiTV DVB-T&quot;
comma
(paren
l_int|1
op_lshift
l_int|26
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* A_PWRDN DA_SBR DA_APP (high speed serial) */
r_break
suffix:semicolon
r_case
l_int|0x07611461
suffix:colon
id|dvb_bt8xx_card_match
c_func
(paren
id|card_nr
comma
l_string|&quot;Avermedia DVB-T&quot;
comma
(paren
l_int|1
op_lshift
l_int|26
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* A_PWRDN DA_SBR DA_APP (high speed serial) */
r_break
suffix:semicolon
r_case
l_int|0x0
suffix:colon
r_if
c_cond
(paren
id|card_type
op_eq
id|BT878_NEBULA
op_logical_or
id|card_type
op_eq
id|BT878_TWINHAN_DST
)paren
r_goto
id|dst
suffix:semicolon
r_goto
id|unknown_card
suffix:semicolon
r_case
l_int|0x2611BD
suffix:colon
r_case
l_int|0x11822
suffix:colon
id|dst
suffix:colon
id|dvb_bt8xx_card_match
c_func
(paren
id|card_nr
comma
l_string|&quot;DST DVB-S&quot;
comma
l_int|0x2204f2c
comma
id|BT878_RISC_SYNC_MASK
comma
id|BT878_APABORT
op_or
id|BT878_ARIPERR
op_or
id|BT878_APPERR
op_or
id|BT878_AFBUS
)paren
suffix:semicolon
multiline_comment|/* 25,21,14,11,10,9,8,3,2 then&n;&t;&t;&t;&t; * 0x33 = 5,4,1,0&n;&t;&t;&t;&t; * A_SEL=SML, DA_MLB, DA_SBR, &n;&t;&t;&t;&t; * DA_SDR=f, fifo trigger = 32 DWORDS&n;&t;&t;&t;&t; * IOM = 0 == audio A/D&n;&t;&t;&t;&t; * DPM = 0 == digital audio mode&n;&t;&t;&t;&t; * == async data parallel port&n;&t;&t;&t;&t; * then 0x33 (13 is set by start_capture)&n;&t;&t;&t;&t; * DA_APP = async data parallel port, &n;&t;&t;&t;&t; * ACAP_EN = 1,&n;&t;&t;&t;&t; * RISC+FIFO ENABLE */
r_break
suffix:semicolon
r_default
suffix:colon
id|unknown_card
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: unknown card_id found %0X&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card_type
op_eq
id|BT878_NEBULA
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: bttv type set to nebula&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|nebula
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card_type
op_eq
id|BT878_TWINHAN_DST
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: bttv type set to Twinhan DST&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|dst
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: unknown card_type found %0X, NOT LOADED&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|card_type
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: unknown card_nr found %0X&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|card_nr
)paren
suffix:semicolon
)brace
id|card_nr
op_increment
suffix:semicolon
)brace
id|dvb_bt8xx_get_adaps
c_func
(paren
)paren
suffix:semicolon
id|dvb_bt8xx_load_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_bt8xx_exit
r_static
r_void
id|__exit
id|dvb_bt8xx_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|dvb_bt8xx_card
op_star
id|card
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|entry_safe
suffix:semicolon
id|dvb_bt8xx_exit_adaps
c_func
(paren
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|entry
comma
id|entry_safe
comma
op_amp
id|card_list
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|dvb_bt8xx_card
comma
id|list
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;dvb_bt8xx: unloading card%d&bslash;n&quot;
comma
id|card-&gt;bttv_nr
)paren
suffix:semicolon
id|bt878_stop
c_func
(paren
id|card-&gt;bt
)paren
suffix:semicolon
id|tasklet_kill
c_func
(paren
op_amp
id|card-&gt;bt-&gt;tasklet
)paren
suffix:semicolon
id|dvb_net_release
c_func
(paren
op_amp
id|card-&gt;dvbnet
)paren
suffix:semicolon
id|card-&gt;demux.dmx
dot
id|remove_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_mem
)paren
suffix:semicolon
id|card-&gt;demux.dmx
dot
id|remove_frontend
c_func
(paren
op_amp
id|card-&gt;demux.dmx
comma
op_amp
id|card-&gt;fe_hw
)paren
suffix:semicolon
id|dvb_dmxdev_release
c_func
(paren
op_amp
id|card-&gt;dmxdev
)paren
suffix:semicolon
id|dvb_dmx_release
c_func
(paren
op_amp
id|card-&gt;demux
)paren
suffix:semicolon
id|dvb_unregister_i2c_bus
c_func
(paren
id|master_xfer
comma
id|card-&gt;dvb_adapter
comma
l_int|0
)paren
suffix:semicolon
id|dvb_bt8xx_i2c_adap_free
c_func
(paren
id|card-&gt;i2c_adapter
)paren
suffix:semicolon
id|dvb_unregister_adapter
c_func
(paren
id|card-&gt;dvb_adapter
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|card-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
)brace
DECL|variable|dvb_bt8xx_init
id|module_init
c_func
(paren
id|dvb_bt8xx_init
)paren
suffix:semicolon
DECL|variable|dvb_bt8xx_exit
id|module_exit
c_func
(paren
id|dvb_bt8xx_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bt8xx based DVB adapter driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Florian Schirmer &lt;jolt@tuxbox.org&gt;&quot;
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
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
eof
