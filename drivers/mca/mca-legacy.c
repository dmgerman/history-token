multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/*&n; * MCA bus support functions for legacy (2.4) API.&n; *&n; * Legacy API means the API that operates in terms of MCA slot number&n; *&n; * (C) 2002 James Bottomley &lt;James.Bottomley@HansenPartnership.com&gt;&n; *&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* NOTE: This structure is stack allocated */
DECL|struct|mca_find_adapter_info
r_struct
id|mca_find_adapter_info
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|slot
r_int
id|slot
suffix:semicolon
DECL|member|mca_dev
r_struct
id|mca_device
op_star
id|mca_dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The purpose of this iterator is to loop over all the devices and&n; * find the one with the smallest slot number that&squot;s just greater than&n; * or equal to the required slot with a matching id */
DECL|function|mca_find_adapter_callback
r_static
r_int
id|mca_find_adapter_callback
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|mca_find_adapter_info
op_star
id|info
op_assign
id|data
suffix:semicolon
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mca_dev-&gt;pos_id
op_ne
id|info-&gt;id
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mca_dev-&gt;slot
OL
id|info-&gt;slot
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;mca_dev
op_logical_or
id|info-&gt;mca_dev-&gt;slot
op_ge
id|mca_dev-&gt;slot
)paren
(brace
id|info-&gt;mca_dev
op_assign
id|mca_dev
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mca_find_adapter - scan for adapters&n; *&t;@id:&t;MCA identification to search for&n; *&t;@start:&t;starting slot&n; *&n; *&t;Search the MCA configuration for adapters matching the 16bit&n; *&t;ID given. The first time it should be called with start as zero&n; *&t;and then further calls made passing the return value of the&n; *&t;previous call until %MCA_NOTFOUND is returned.&n; *&n; *&t;Disabled adapters are not reported.&n; */
DECL|function|mca_find_adapter
r_int
id|mca_find_adapter
c_func
(paren
r_int
id|id
comma
r_int
id|start
)paren
(brace
r_struct
id|mca_find_adapter_info
id|info
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|0xffff
)paren
(brace
r_return
id|MCA_NOTFOUND
suffix:semicolon
)brace
id|info.slot
op_assign
id|start
suffix:semicolon
id|info.id
op_assign
id|id
suffix:semicolon
id|info.mca_dev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|bus_for_each_dev
c_func
(paren
op_amp
id|mca_bus_type
comma
op_amp
id|info
comma
id|mca_find_adapter_callback
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info.mca_dev
op_eq
l_int|NULL
)paren
(brace
r_return
id|MCA_NOTFOUND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info.mca_dev-&gt;status
op_ne
id|MCA_ADAPTER_DISABLED
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* OK, found adapter but it was disabled.  Go around&n;&t;&t; * again, excluding the slot we just found */
id|info.slot
op_assign
id|info.mca_dev-&gt;slot
op_plus
l_int|1
suffix:semicolon
id|info.mca_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|info.mca_dev-&gt;slot
suffix:semicolon
)brace
DECL|variable|mca_find_adapter
id|EXPORT_SYMBOL
c_func
(paren
id|mca_find_adapter
)paren
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------------*/
multiline_comment|/**&n; *&t;mca_find_unused_adapter - scan for unused adapters&n; *&t;@id:&t;MCA identification to search for&n; *&t;@start:&t;starting slot&n; *&n; *&t;Search the MCA configuration for adapters matching the 16bit&n; *&t;ID given. The first time it should be called with start as zero&n; *&t;and then further calls made passing the return value of the&n; *&t;previous call until %MCA_NOTFOUND is returned.&n; *&n; *&t;Adapters that have been claimed by drivers and those that&n; *&t;are disabled are not reported. This function thus allows a driver&n; *&t;to scan for further cards when some may already be driven.&n; */
DECL|function|mca_find_unused_adapter
r_int
id|mca_find_unused_adapter
c_func
(paren
r_int
id|id
comma
r_int
id|start
)paren
(brace
r_struct
id|mca_find_adapter_info
id|info
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|0xffff
)paren
(brace
r_return
id|MCA_NOTFOUND
suffix:semicolon
)brace
id|info.slot
op_assign
id|start
suffix:semicolon
id|info.id
op_assign
id|id
suffix:semicolon
id|info.mca_dev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|bus_for_each_dev
c_func
(paren
op_amp
id|mca_bus_type
comma
op_amp
id|info
comma
id|mca_find_adapter_callback
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info.mca_dev
op_eq
l_int|NULL
)paren
(brace
r_return
id|MCA_NOTFOUND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info.mca_dev-&gt;status
op_ne
id|MCA_ADAPTER_DISABLED
op_logical_and
op_logical_neg
id|info.mca_dev-&gt;driver_loaded
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* OK, found adapter but it was disabled or already in&n;&t;&t; * use.  Go around again, excluding the slot we just&n;&t;&t; * found */
id|info.slot
op_assign
id|info.mca_dev-&gt;slot
op_plus
l_int|1
suffix:semicolon
id|info.mca_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|info.mca_dev-&gt;slot
suffix:semicolon
)brace
DECL|variable|mca_find_unused_adapter
id|EXPORT_SYMBOL
c_func
(paren
id|mca_find_unused_adapter
)paren
suffix:semicolon
multiline_comment|/* NOTE: stack allocated structure */
DECL|struct|mca_find_device_by_slot_info
r_struct
id|mca_find_device_by_slot_info
(brace
DECL|member|slot
r_int
id|slot
suffix:semicolon
DECL|member|mca_dev
r_struct
id|mca_device
op_star
id|mca_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|function|mca_find_device_by_slot_callback
r_static
r_int
id|mca_find_device_by_slot_callback
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|mca_find_device_by_slot_info
op_star
id|info
op_assign
id|data
suffix:semicolon
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mca_dev-&gt;slot
op_eq
id|info-&gt;slot
)paren
(brace
id|info-&gt;mca_dev
op_assign
id|mca_dev
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mca_find_device_by_slot
r_struct
id|mca_device
op_star
id|mca_find_device_by_slot
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_find_device_by_slot_info
id|info
suffix:semicolon
id|info.slot
op_assign
id|slot
suffix:semicolon
id|info.mca_dev
op_assign
l_int|NULL
suffix:semicolon
id|bus_for_each_dev
c_func
(paren
op_amp
id|mca_bus_type
comma
op_amp
id|info
comma
id|mca_find_device_by_slot_callback
)paren
suffix:semicolon
r_return
id|info.mca_dev
suffix:semicolon
)brace
DECL|variable|mca_find_device_by_slot
id|EXPORT_SYMBOL
c_func
(paren
id|mca_find_device_by_slot
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_read_stored_pos - read POS register from boot data&n; *&t;@slot: slot number to read from&n; *&t;@reg:  register to read from&n; *&n; *&t;Fetch a POS value that was stored at boot time by the kernel&n; *&t;when it scanned the MCA space. The register value is returned.&n; *&t;Missing or invalid registers report 0.&n; */
DECL|function|mca_read_stored_pos
r_int
r_char
id|mca_read_stored_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg
OL
l_int|0
op_logical_or
id|reg
op_ge
l_int|8
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|mca_dev-&gt;pos
(braket
id|reg
)braket
suffix:semicolon
)brace
DECL|variable|mca_read_stored_pos
id|EXPORT_SYMBOL
c_func
(paren
id|mca_read_stored_pos
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_read_pos - read POS register from card&n; *&t;@slot: slot number to read from&n; *&t;@reg:  register to read from&n; *&n; *&t;Fetch a POS value directly from the hardware to obtain the&n; *&t;current value. This is much slower than mca_read_stored_pos and&n; *&t;may not be invoked from interrupt context. It handles the&n; *&t;deep magic required for onboard devices transparently.&n; */
DECL|function|mca_read_pos
r_int
r_char
id|mca_read_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_char
id|byte
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg
OL
l_int|0
op_logical_or
id|reg
op_ge
l_int|8
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mca_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mca_dev-&gt;pos_register
)paren
(brace
multiline_comment|/* Disable adapter setup, enable motherboard setup */
id|outb_p
c_func
(paren
l_int|0
comma
id|MCA_ADAPTER_SETUP_REG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|mca_dev-&gt;pos_register
comma
id|MCA_MOTHERBOARD_SETUP_REG
)paren
suffix:semicolon
id|byte
op_assign
id|inb_p
c_func
(paren
id|MCA_POS_REG
c_func
(paren
id|reg
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
comma
id|MCA_MOTHERBOARD_SETUP_REG
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Make sure motherboard setup is off */
id|outb_p
c_func
(paren
l_int|0xff
comma
id|MCA_MOTHERBOARD_SETUP_REG
)paren
suffix:semicolon
multiline_comment|/* Read the appropriate register */
id|outb_p
c_func
(paren
l_int|0x8
op_or
(paren
id|mca_dev-&gt;slot
op_amp
l_int|0xf
)paren
comma
id|MCA_ADAPTER_SETUP_REG
)paren
suffix:semicolon
id|byte
op_assign
id|inb_p
c_func
(paren
id|MCA_POS_REG
c_func
(paren
id|reg
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|MCA_ADAPTER_SETUP_REG
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mca_lock
comma
id|flags
)paren
suffix:semicolon
id|mca_dev-&gt;pos
(braket
id|reg
)braket
op_assign
id|byte
suffix:semicolon
r_return
id|byte
suffix:semicolon
)brace
DECL|variable|mca_read_pos
id|EXPORT_SYMBOL
c_func
(paren
id|mca_read_pos
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_write_pos - read POS register from card&n; *&t;@slot: slot number to read from&n; *&t;@reg:  register to read from&n; *&t;@byte: byte to write to the POS registers&n; *&n; *&t;Store a POS value directly from the hardware. You should not&n; *&t;normally need to use this function and should have a very good&n; *&t;knowledge of MCA bus before you do so. Doing this wrongly can&n; *&t;damage the hardware.&n; *&n; *&t;This function may not be used from interrupt context.&n; *&n; *&t;Note that this a technically a Bad Thing, as IBM tech stuff says&n; *&t;you should only set POS values through their utilities.&n; *&t;However, some devices such as the 3c523 recommend that you write&n; *&t;back some data to make sure the configuration is consistent.&n; *&t;I&squot;d say that IBM is right, but I like my drivers to work.&n; *&n; *&t;This function can&squot;t do checks to see if multiple devices end up&n; *&t;with the same resources, so you might see magic smoke if someone&n; *&t;screws up.&n; */
DECL|function|mca_write_pos
r_void
id|mca_write_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
comma
r_int
r_char
id|byte
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg
OL
l_int|0
op_logical_or
id|reg
op_ge
l_int|8
)paren
(brace
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mca_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Make sure motherboard setup is off */
id|outb_p
c_func
(paren
l_int|0xff
comma
id|MCA_MOTHERBOARD_SETUP_REG
)paren
suffix:semicolon
multiline_comment|/* Read in the appropriate register */
id|outb_p
c_func
(paren
l_int|0x8
op_or
(paren
id|slot
op_amp
l_int|0xf
)paren
comma
id|MCA_ADAPTER_SETUP_REG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|byte
comma
id|MCA_POS_REG
c_func
(paren
id|reg
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|MCA_ADAPTER_SETUP_REG
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mca_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Update the global register list, while we have the byte */
id|mca_dev-&gt;pos
(braket
id|reg
)braket
op_assign
id|byte
suffix:semicolon
)brace
DECL|variable|mca_write_pos
id|EXPORT_SYMBOL
c_func
(paren
id|mca_write_pos
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_set_adapter_name - Set the description of the card&n; *&t;@slot: slot to name&n; *&t;@name: text string for the namen&n; *&n; *&t;This function sets the name reported via /proc for this&n; *&t;adapter slot. This is for user information only. Setting a&n; *&t;name deletes any previous name.&n; */
DECL|function|mca_set_adapter_name
r_void
id|mca_set_adapter_name
c_func
(paren
r_int
id|slot
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|mca_dev-&gt;dev.name
comma
id|name
comma
r_sizeof
(paren
id|mca_dev-&gt;dev.name
)paren
)paren
suffix:semicolon
id|mca_dev-&gt;dev.name
(braket
r_sizeof
(paren
id|mca_dev-&gt;dev.name
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|variable|mca_set_adapter_name
id|EXPORT_SYMBOL
c_func
(paren
id|mca_set_adapter_name
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_get_adapter_name - get the adapter description&n; *&t;@slot:&t;slot to query&n; *&n; *&t;Return the adapter description if set. If it has not been&n; *&t;set or the slot is out range then return NULL.&n; */
DECL|function|mca_get_adapter_name
r_char
op_star
id|mca_get_adapter_name
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|mca_dev-&gt;dev.name
suffix:semicolon
)brace
DECL|variable|mca_get_adapter_name
id|EXPORT_SYMBOL
c_func
(paren
id|mca_get_adapter_name
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_is_adapter_used - check if claimed by driver&n; *&t;@slot:&t;slot to check&n; *&n; *&t;Returns 1 if the slot has been claimed by a driver&n; */
DECL|function|mca_is_adapter_used
r_int
id|mca_is_adapter_used
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|mca_dev-&gt;driver_loaded
suffix:semicolon
)brace
DECL|variable|mca_is_adapter_used
id|EXPORT_SYMBOL
c_func
(paren
id|mca_is_adapter_used
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_mark_as_used - claim an MCA device&n; *&t;@slot:&t;slot to claim&n; *&t;FIXME:  should we make this threadsafe&n; *&n; *&t;Claim an MCA slot for a device driver. If the&n; *&t;slot is already taken the function returns 1,&n; *&t;if it is not taken it is claimed and 0 is&n; *&t;returned.&n; */
DECL|function|mca_mark_as_used
r_int
id|mca_mark_as_used
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
multiline_comment|/* FIXME: this is actually a severe error */
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mca_dev-&gt;driver_loaded
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|mca_dev-&gt;driver_loaded
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mca_mark_as_used
id|EXPORT_SYMBOL
c_func
(paren
id|mca_mark_as_used
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_mark_as_unused - release an MCA device&n; *&t;@slot:&t;slot to claim&n; *&n; *&t;Release the slot for other drives to use.&n; */
DECL|function|mca_mark_as_unused
r_void
id|mca_mark_as_unused
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
suffix:semicolon
)brace
id|mca_dev-&gt;driver_loaded
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|mca_mark_as_unused
id|EXPORT_SYMBOL
c_func
(paren
id|mca_mark_as_unused
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_isadapter - check if the slot holds an adapter&n; *&t;@slot:&t;slot to query&n; *&n; *&t;Returns zero if the slot does not hold an adapter, non zero if&n; *&t;it does.&n; */
DECL|function|mca_isadapter
r_int
id|mca_isadapter
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|mca_dev-&gt;status
op_eq
id|MCA_ADAPTER_NORMAL
op_logical_or
id|mca_dev-&gt;status
op_eq
id|MCA_ADAPTER_DISABLED
suffix:semicolon
)brace
DECL|variable|mca_isadapter
id|EXPORT_SYMBOL
c_func
(paren
id|mca_isadapter
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;mca_isenabled - check if the slot holds an enabled adapter&n; *&t;@slot:&t;slot to query&n; *&n; *&t;Returns a non zero value if the slot holds an enabled adapter&n; *&t;and zero for any other case.&n; */
DECL|function|mca_isenabled
r_int
id|mca_isenabled
c_func
(paren
r_int
id|slot
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|mca_dev-&gt;status
op_eq
id|MCA_ADAPTER_NORMAL
suffix:semicolon
)brace
eof
