multiline_comment|/*&n; * ACPI PCI Hot Plug IBM Extension&n; *&n; * Copyright (C) 2004 Vernon Mauery &lt;vernux@us.ibm.com&gt;&n; * Copyright (C) 2004 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;vernux@us.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &quot;acpiphp.h&quot;
macro_line|#include &quot;pci_hotplug.h&quot;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;1.0.1&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Irene Zubarev &lt;zubarev@us.ibm.com&gt;, Vernon Mauery &lt;vernux@us.ibm.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;ACPI Hot Plug PCI Controller Driver IBM extension&quot;
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|DRIVER_VERSION
id|MODULE_VERSION
c_func
(paren
id|DRIVER_VERSION
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_bool
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot; Debugging mode enabled or not&quot;
)paren
suffix:semicolon
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;acpiphp_ibm&quot;
DECL|macro|dbg
macro_line|#undef dbg
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (debug)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(KERN_DEBUG &quot;%s: &quot; format,&t;&bslash;&n;&t;&t;&t;&t;MY_NAME , ## arg);&t;&bslash;&n;} while (0)
DECL|macro|FOUND_APCI
mdefine_line|#define FOUND_APCI 0x61504349
multiline_comment|/* these are the names for the IBM ACPI pseudo-device */
DECL|macro|IBM_HARDWARE_ID1
mdefine_line|#define IBM_HARDWARE_ID1 &quot;IBM37D0&quot;
DECL|macro|IBM_HARDWARE_ID2
mdefine_line|#define IBM_HARDWARE_ID2 &quot;IBM37D4&quot;
DECL|macro|hpslot_to_sun
mdefine_line|#define hpslot_to_sun(A) (((struct slot *)((A)-&gt;private))-&gt;acpi_slot-&gt;sun)
multiline_comment|/* union apci_descriptor - allows access to the&n; * various device descriptors that are embedded in the&n; * aPCI table&n; */
DECL|union|apci_descriptor
r_union
id|apci_descriptor
(brace
r_struct
(brace
DECL|member|sig
r_char
id|sig
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|header
)brace
id|header
suffix:semicolon
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|slot_id
id|u16
id|slot_id
suffix:semicolon
DECL|member|bus_id
id|u8
id|bus_id
suffix:semicolon
DECL|member|dev_num
id|u8
id|dev_num
suffix:semicolon
DECL|member|slot_num
id|u8
id|slot_num
suffix:semicolon
DECL|member|slot_attr
id|u8
id|slot_attr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|attn
id|u8
id|attn
suffix:semicolon
DECL|member|status
id|u8
id|status
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sun
id|u8
id|sun
suffix:semicolon
DECL|member|res
id|u8
id|res
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|slot
)brace
id|slot
suffix:semicolon
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|generic
)brace
id|generic
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* struct notification - keeps info about the device&n; * that cause the ACPI notification event&n; */
DECL|struct|notification
r_struct
id|notification
(brace
DECL|member|device
r_struct
id|acpi_device
op_star
id|device
suffix:semicolon
DECL|member|event
id|u8
id|event
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|ibm_set_attention_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
id|status
)paren
suffix:semicolon
r_static
r_int
id|ibm_get_attention_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
op_star
id|status
)paren
suffix:semicolon
r_static
r_void
id|ibm_handle_events
c_func
(paren
id|acpi_handle
id|handle
comma
id|u32
id|event
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_static
r_int
id|ibm_get_table_from_acpi
c_func
(paren
r_char
op_star
op_star
id|bufp
)paren
suffix:semicolon
r_static
id|ssize_t
id|ibm_read_apci_table
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|pos
comma
r_int
id|size
)paren
suffix:semicolon
r_static
id|acpi_status
id|__init
id|ibm_find_acpi_device
c_func
(paren
id|acpi_handle
id|handle
comma
id|u32
id|lvl
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|rv
)paren
suffix:semicolon
r_static
r_int
id|__init
id|ibm_acpiphp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|ibm_acpiphp_exit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|ibm_acpi_handle
r_static
id|acpi_handle
id|ibm_acpi_handle
suffix:semicolon
DECL|variable|ibm_note
r_static
r_struct
id|notification
id|ibm_note
suffix:semicolon
DECL|variable|ibm_apci_table_attr
r_static
r_struct
id|bin_attribute
id|ibm_apci_table_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;apci_table&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|mode
op_assign
id|S_IRUGO
comma
)brace
comma
dot
id|read
op_assign
id|ibm_read_apci_table
comma
dot
id|write
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|ibm_attention_info
r_static
r_struct
id|acpiphp_attention_info
id|ibm_attention_info
op_assign
(brace
dot
id|set_attn
op_assign
id|ibm_set_attention_status
comma
dot
id|get_attn
op_assign
id|ibm_get_attention_status
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * ibm_slot_from_id - workaround for bad ibm hardware&n; * @id: the slot number that linux refers to the slot by&n; *&n; * Description: this method returns the aCPI slot descriptor&n; * corresponding to the Linux slot number.  This descriptor&n; * has info about the aPCI slot id and attention status.&n; * This descriptor must be freed using kfree when done.&n; **/
DECL|function|ibm_slot_from_id
r_static
r_union
id|apci_descriptor
op_star
id|ibm_slot_from_id
c_func
(paren
r_int
id|id
)paren
(brace
r_int
id|ind
op_assign
l_int|0
comma
id|size
suffix:semicolon
r_union
id|apci_descriptor
op_star
id|ret
op_assign
l_int|NULL
comma
op_star
id|des
suffix:semicolon
r_char
op_star
id|table
suffix:semicolon
id|size
op_assign
id|ibm_get_table_from_acpi
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
id|des
op_assign
(paren
r_union
id|apci_descriptor
op_star
)paren
id|table
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|des-&gt;header.sig
comma
l_string|&quot;aPCI&quot;
comma
l_int|4
)paren
op_ne
l_int|0
)paren
r_goto
id|ibm_slot_done
suffix:semicolon
id|des
op_assign
(paren
r_union
id|apci_descriptor
op_star
)paren
op_amp
id|table
(braket
id|ind
op_add_assign
id|des-&gt;header.len
)braket
suffix:semicolon
r_while
c_loop
(paren
id|ind
OL
id|size
op_logical_and
(paren
id|des-&gt;generic.type
op_ne
l_int|0x82
op_logical_or
id|des-&gt;slot.slot_num
op_ne
id|id
)paren
)paren
(brace
id|des
op_assign
(paren
r_union
id|apci_descriptor
op_star
)paren
op_amp
id|table
(braket
id|ind
op_add_assign
id|des-&gt;generic.len
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ind
OL
id|size
op_logical_and
id|des-&gt;slot.slot_num
op_eq
id|id
)paren
id|ret
op_assign
id|des
suffix:semicolon
id|ibm_slot_done
suffix:colon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ret
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_union
id|apci_descriptor
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ret
comma
id|des
comma
r_sizeof
(paren
r_union
id|apci_descriptor
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|table
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * ibm_set_attention_status - callback method to set the attention LED&n; * @slot: the hotplug_slot to work with&n; * @status: what to set the LED to (0 or 1)&n; *&n; * Description: this method is registered with the acpiphp module as a&n; * callback to do the device specific task of setting the LED status&n; **/
DECL|function|ibm_set_attention_status
r_static
r_int
id|ibm_set_attention_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
id|status
)paren
(brace
r_union
id|acpi_object
id|args
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|acpi_object_list
id|params
op_assign
(brace
dot
id|pointer
op_assign
id|args
comma
dot
id|count
op_assign
l_int|2
)brace
suffix:semicolon
id|acpi_status
id|stat
suffix:semicolon
r_int
r_int
id|rc
suffix:semicolon
r_union
id|apci_descriptor
op_star
id|ibm_slot
suffix:semicolon
id|ibm_slot
op_assign
id|ibm_slot_from_id
c_func
(paren
id|hpslot_to_sun
c_func
(paren
id|slot
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: set slot %d (%d) attention status to %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ibm_slot-&gt;slot.slot_num
comma
id|ibm_slot-&gt;slot.slot_id
comma
(paren
id|status
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|args
(braket
l_int|0
)braket
dot
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|args
(braket
l_int|0
)braket
dot
id|integer.value
op_assign
id|ibm_slot-&gt;slot.slot_id
suffix:semicolon
id|args
(braket
l_int|1
)braket
dot
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|args
(braket
l_int|1
)braket
dot
id|integer.value
op_assign
(paren
id|status
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|ibm_slot
)paren
suffix:semicolon
id|stat
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|ibm_acpi_handle
comma
l_string|&quot;APLS&quot;
comma
op_amp
id|params
comma
op_amp
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|stat
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;APLS evaluation failed:  0x%08x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|err
c_func
(paren
l_string|&quot;APLS method failed:  0x%08lx&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
op_minus
id|ERANGE
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * ibm_get_attention_status - callback method to get attention LED status&n; * @slot: the hotplug_slot to work with&n; * @status: returns what the LED is set to (0 or 1)&n; *&n; * Description: this method is registered with the acpiphp module as a&n; * callback to do the device specific task of getting the LED status&n; * &n; * Because there is no direct method of getting the LED status directly&n; * from an ACPI call, we read the aPCI table and parse out our&n; * slot descriptor to read the status from that.&n; **/
DECL|function|ibm_get_attention_status
r_static
r_int
id|ibm_get_attention_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
op_star
id|status
)paren
(brace
r_union
id|apci_descriptor
op_star
id|ibm_slot
suffix:semicolon
id|ibm_slot
op_assign
id|ibm_slot_from_id
c_func
(paren
id|hpslot_to_sun
c_func
(paren
id|slot
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ibm_slot-&gt;slot.attn
op_amp
l_int|0xa0
op_logical_or
id|ibm_slot-&gt;slot.status
(braket
l_int|1
)braket
op_amp
l_int|0x08
)paren
op_star
id|status
op_assign
l_int|1
suffix:semicolon
r_else
op_star
id|status
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: get slot %d (%d) attention status is %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ibm_slot-&gt;slot.slot_num
comma
id|ibm_slot-&gt;slot.slot_id
comma
op_star
id|status
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ibm_slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * ibm_handle_events - listens for ACPI events for the IBM37D0 device&n; * @handle: an ACPI handle to the device that caused the event&n; * @event: the event info (device specific)&n; * @context: passed context (our notification struct)&n; *&n; * Description: this method is registered as a callback with the ACPI&n; * subsystem it is called when this device has an event to notify the OS of&n; *&n; * The events actually come from the device as two events that get&n; * synthesized into one event with data by this function.  The event&n; * ID comes first and then the slot number that caused it.  We report&n; * this as one event to the OS.&n; *&n; * From section 5.6.2.2 of the ACPI 2.0 spec, I understand that the OSPM will&n; * only re-enable the interrupt that causes this event AFTER this method&n; * has returned, thereby enforcing serial access for the notification struct.&n; **/
DECL|function|ibm_handle_events
r_static
r_void
id|ibm_handle_events
c_func
(paren
id|acpi_handle
id|handle
comma
id|u32
id|event
comma
r_void
op_star
id|context
)paren
(brace
id|u8
id|detail
op_assign
id|event
op_amp
l_int|0x0f
suffix:semicolon
id|u8
id|subevent
op_assign
id|event
op_amp
l_int|0xf0
suffix:semicolon
r_struct
id|notification
op_star
id|note
op_assign
id|context
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: Received notification %02x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subevent
op_eq
l_int|0x80
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: generationg bus event&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|acpi_bus_generate_event
c_func
(paren
id|note-&gt;device
comma
id|note-&gt;event
comma
id|detail
)paren
suffix:semicolon
)brace
r_else
id|note-&gt;event
op_assign
id|event
suffix:semicolon
)brace
multiline_comment|/**&n; * ibm_get_table_from_acpi - reads the APLS buffer from ACPI&n; * @bufp: address to pointer to allocate for the table&n; *&n; * Description: this method reads the APLS buffer in from ACPI and&n; * stores the &quot;stripped&quot; table into a single buffer&n; * it allocates and passes the address back in bufp&n; *&n; * If NULL is passed in as buffer, this method only calculates&n; * the size of the table and returns that without filling&n; * in the buffer&n; *&n; * returns &lt; 0 on error or the size of the table on success&n; **/
DECL|function|ibm_get_table_from_acpi
r_static
r_int
id|ibm_get_table_from_acpi
c_func
(paren
r_char
op_star
op_star
id|bufp
)paren
(brace
r_union
id|acpi_object
op_star
id|package
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_char
op_star
id|lbuf
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|size
op_assign
op_minus
id|EIO
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|ibm_acpi_handle
comma
l_string|&quot;APCI&quot;
comma
l_int|NULL
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s:  APCI evaluation failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|package
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|package
)paren
op_logical_or
(paren
id|package-&gt;type
op_ne
id|ACPI_TYPE_PACKAGE
)paren
op_logical_or
op_logical_neg
(paren
id|package-&gt;package.elements
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s:  Invalid APCI object&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|read_table_done
suffix:semicolon
)brace
r_for
c_loop
(paren
id|size
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|package-&gt;package.count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|package-&gt;package.elements
(braket
id|i
)braket
dot
id|type
op_ne
id|ACPI_TYPE_BUFFER
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s:  Invalid APCI element %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|i
)paren
suffix:semicolon
r_goto
id|read_table_done
suffix:semicolon
)brace
id|size
op_add_assign
id|package-&gt;package.elements
(braket
id|i
)braket
dot
id|buffer.length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bufp
op_eq
l_int|NULL
)paren
r_goto
id|read_table_done
suffix:semicolon
id|lbuf
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: element count: %i, ASL table size: %i, &amp;table = 0x%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|package-&gt;package.count
comma
id|size
comma
id|lbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lbuf
)paren
(brace
op_star
id|bufp
op_assign
id|lbuf
suffix:semicolon
id|memset
c_func
(paren
id|lbuf
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|size
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|read_table_done
suffix:semicolon
)brace
id|size
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
id|package-&gt;package.count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|lbuf
(braket
id|size
)braket
comma
id|package-&gt;package.elements
(braket
id|i
)braket
dot
id|buffer.pointer
comma
id|package-&gt;package.elements
(braket
id|i
)braket
dot
id|buffer.length
)paren
suffix:semicolon
id|size
op_add_assign
id|package-&gt;package.elements
(braket
id|i
)braket
dot
id|buffer.length
suffix:semicolon
)brace
id|read_table_done
suffix:colon
id|kfree
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/**&n; * ibm_read_apci_table - callback for the sysfs apci_table file&n; * @kobj: the kobject this binary attribute is a part of&n; * @buffer: the kernel space buffer to fill&n; * @pos: the offset into the file&n; * @size: the number of bytes requested&n; *&n; * Description: gets registered with sysfs as the reader callback&n; * to be executed when /sys/bus/pci/slots/apci_table gets read&n; *&n; * Since we don&squot;t get notified on open and close for this file,&n; * things get really tricky here...&n; * our solution is to only allow reading the table in all at once&n; **/
DECL|function|ibm_read_apci_table
r_static
id|ssize_t
id|ibm_read_apci_table
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|pos
comma
r_int
id|size
)paren
(brace
r_int
id|bytes_read
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_char
op_star
id|table
op_assign
l_int|NULL
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: pos = %d, size = %zd&bslash;n&quot;
comma
id|__FUNCTION__
comma
(paren
r_int
)paren
id|pos
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_eq
l_int|0
)paren
(brace
id|bytes_read
op_assign
id|ibm_get_table_from_acpi
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bytes_read
OG
l_int|0
op_logical_and
id|bytes_read
op_le
id|size
)paren
id|memcpy
c_func
(paren
id|buffer
comma
id|table
comma
id|bytes_read
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|table
)paren
suffix:semicolon
)brace
r_return
id|bytes_read
suffix:semicolon
)brace
multiline_comment|/**&n; * ibm_find_acpi_device - callback to find our ACPI device&n; * @handle: the ACPI handle of the device we are inspecting&n; * @lvl: depth into the namespace tree&n; * @context: a pointer to our handle to fill when we find the device&n; * @rv: a return value to fill if desired&n; *&n; * Description: used as a callback when calling acpi_walk_namespace&n; * to find our device.  When this method returns non-zero&n; * acpi_walk_namespace quits its search and returns our value&n; **/
DECL|function|ibm_find_acpi_device
r_static
id|acpi_status
id|__init
id|ibm_find_acpi_device
c_func
(paren
id|acpi_handle
id|handle
comma
id|u32
id|lvl
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|rv
)paren
(brace
id|acpi_handle
op_star
id|phandle
op_assign
(paren
id|acpi_handle
op_star
)paren
id|context
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_device_info
id|info
suffix:semicolon
r_struct
id|acpi_buffer
id|info_buffer
op_assign
(brace
dot
id|length
op_assign
r_sizeof
(paren
r_struct
id|acpi_device_info
)paren
comma
dot
id|pointer
op_assign
op_amp
id|info
comma
)brace
suffix:semicolon
id|status
op_assign
id|acpi_get_object_info
c_func
(paren
id|handle
comma
op_amp
id|info_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s:  Failed to get device information&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|info.hardware_id.value
(braket
r_sizeof
(paren
id|info.hardware_id.value
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|info.current_status
op_logical_and
(paren
id|info.valid
op_amp
id|ACPI_VALID_HID
)paren
op_logical_and
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|info.hardware_id.value
comma
id|IBM_HARDWARE_ID1
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|info.hardware_id.value
comma
id|IBM_HARDWARE_ID2
)paren
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;found hardware: %s, handle: %p&bslash;n&quot;
comma
id|info.hardware_id.value
comma
id|handle
)paren
suffix:semicolon
op_star
id|phandle
op_assign
id|handle
suffix:semicolon
multiline_comment|/* returning non-zero causes the search to stop&n;&t;&t; * and returns this value to the caller of &n;&t;&t; * acpi_walk_namespace, but it also causes some warnings&n;&t;&t; * in the acpi debug code to print...&n;&t;&t; */
r_return
id|FOUND_APCI
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ibm_acpiphp_init
r_static
r_int
id|__init
id|ibm_acpiphp_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
suffix:semicolon
r_struct
id|kobject
op_star
id|sysdir
op_assign
op_amp
id|pci_hotplug_slots_subsys.kset.kobj
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_walk_namespace
c_func
(paren
id|ACPI_TYPE_DEVICE
comma
id|ACPI_ROOT_OBJECT
comma
id|ACPI_UINT32_MAX
comma
id|ibm_find_acpi_device
comma
op_amp
id|ibm_acpi_handle
comma
l_int|NULL
)paren
op_ne
id|FOUND_APCI
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: acpi_walk_namespace failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|init_return
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s: found IBM aPCI device&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bus_get_device
c_func
(paren
id|ibm_acpi_handle
comma
op_amp
id|device
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: acpi_bus_get_device failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|init_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpiphp_register_attention
c_func
(paren
op_amp
id|ibm_attention_info
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|init_return
suffix:semicolon
)brace
id|ibm_note.device
op_assign
id|device
suffix:semicolon
id|status
op_assign
id|acpi_install_notify_handler
c_func
(paren
id|ibm_acpi_handle
comma
id|ACPI_DEVICE_NOTIFY
comma
id|ibm_handle_events
comma
op_amp
id|ibm_note
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s:  Failed to register notification handler&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|init_cleanup
suffix:semicolon
)brace
id|ibm_apci_table_attr.size
op_assign
id|ibm_get_table_from_acpi
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|retval
op_assign
id|sysfs_create_bin_file
c_func
(paren
id|sysdir
comma
op_amp
id|ibm_apci_table_attr
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|init_cleanup
suffix:colon
id|acpiphp_unregister_attention
c_func
(paren
op_amp
id|ibm_attention_info
)paren
suffix:semicolon
id|init_return
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ibm_acpiphp_exit
r_static
r_void
id|__exit
id|ibm_acpiphp_exit
c_func
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|kobject
op_star
id|sysdir
op_assign
op_amp
id|pci_hotplug_slots_subsys.kset.kobj
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpiphp_unregister_attention
c_func
(paren
op_amp
id|ibm_attention_info
)paren
)paren
id|err
c_func
(paren
l_string|&quot;%s: attention info deregistration failed&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|status
op_assign
id|acpi_remove_notify_handler
c_func
(paren
id|ibm_acpi_handle
comma
id|ACPI_DEVICE_NOTIFY
comma
id|ibm_handle_events
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|err
c_func
(paren
l_string|&quot;%s:  Notification handler removal failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
singleline_comment|// remove the /sys entries
r_if
c_cond
(paren
id|sysfs_remove_bin_file
c_func
(paren
id|sysdir
comma
op_amp
id|ibm_apci_table_attr
)paren
)paren
id|err
c_func
(paren
l_string|&quot;%s: removal of sysfs file apci_table failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
DECL|variable|ibm_acpiphp_init
id|module_init
c_func
(paren
id|ibm_acpiphp_init
)paren
suffix:semicolon
DECL|variable|ibm_acpiphp_exit
id|module_exit
c_func
(paren
id|ibm_acpiphp_exit
)paren
suffix:semicolon
eof
