macro_line|#ifndef __HID_H
DECL|macro|__HID_H
mdefine_line|#define __HID_H
multiline_comment|/*&n; * $Id: hid.h,v 1.7 2000/05/31 22:57:48 vojtech Exp $&n; *&n; *  Copyright (c) 1999 Andreas Gal&n; *  Copyright (c) 2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * USB HID (Human Interface Device) interface class code&n; */
DECL|macro|USB_INTERFACE_CLASS_HID
mdefine_line|#define USB_INTERFACE_CLASS_HID&t;&t;3
multiline_comment|/*&n; * We parse each description item into this structure. Short items data&n; * values are expanded to 32-bit signed int, long items contain a pointer&n; * into the data area.&n; */
DECL|struct|hid_item
r_struct
id|hid_item
(brace
DECL|member|format
r_int
id|format
suffix:semicolon
DECL|member|size
id|__u8
id|size
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|tag
id|__u8
id|tag
suffix:semicolon
r_union
(brace
DECL|member|u8
id|__u8
id|u8
suffix:semicolon
DECL|member|s8
id|__s8
id|s8
suffix:semicolon
DECL|member|u16
id|__u16
id|u16
suffix:semicolon
DECL|member|s16
id|__s16
id|s16
suffix:semicolon
DECL|member|u32
id|__u32
id|u32
suffix:semicolon
DECL|member|s32
id|__s32
id|s32
suffix:semicolon
DECL|member|longdata
id|__u8
op_star
id|longdata
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * HID report item format&n; */
DECL|macro|HID_ITEM_FORMAT_SHORT
mdefine_line|#define HID_ITEM_FORMAT_SHORT&t;0
DECL|macro|HID_ITEM_FORMAT_LONG
mdefine_line|#define HID_ITEM_FORMAT_LONG&t;1
multiline_comment|/*&n; * Special tag indicating long items&n; */
DECL|macro|HID_ITEM_TAG_LONG
mdefine_line|#define HID_ITEM_TAG_LONG&t;15
multiline_comment|/*&n; * HID report descriptor item type (prefix bit 2,3)&n; */
DECL|macro|HID_ITEM_TYPE_MAIN
mdefine_line|#define HID_ITEM_TYPE_MAIN&t;&t;0
DECL|macro|HID_ITEM_TYPE_GLOBAL
mdefine_line|#define HID_ITEM_TYPE_GLOBAL&t;&t;1
DECL|macro|HID_ITEM_TYPE_LOCAL
mdefine_line|#define HID_ITEM_TYPE_LOCAL&t;&t;2
DECL|macro|HID_ITEM_TYPE_RESERVED
mdefine_line|#define HID_ITEM_TYPE_RESERVED&t;&t;3
multiline_comment|/*&n; * HID report descriptor main item tags&n; */
DECL|macro|HID_MAIN_ITEM_TAG_INPUT
mdefine_line|#define HID_MAIN_ITEM_TAG_INPUT&t;&t;&t;8
DECL|macro|HID_MAIN_ITEM_TAG_OUTPUT
mdefine_line|#define HID_MAIN_ITEM_TAG_OUTPUT&t;&t;9
DECL|macro|HID_MAIN_ITEM_TAG_FEATURE
mdefine_line|#define HID_MAIN_ITEM_TAG_FEATURE&t;&t;11
DECL|macro|HID_MAIN_ITEM_TAG_BEGIN_COLLECTION
mdefine_line|#define HID_MAIN_ITEM_TAG_BEGIN_COLLECTION&t;10
DECL|macro|HID_MAIN_ITEM_TAG_END_COLLECTION
mdefine_line|#define HID_MAIN_ITEM_TAG_END_COLLECTION&t;12
multiline_comment|/*&n; * HID report descriptor main item contents&n; */
DECL|macro|HID_MAIN_ITEM_CONSTANT
mdefine_line|#define HID_MAIN_ITEM_CONSTANT&t;&t;0x001
DECL|macro|HID_MAIN_ITEM_VARIABLE
mdefine_line|#define HID_MAIN_ITEM_VARIABLE&t;&t;0x002
DECL|macro|HID_MAIN_ITEM_RELATIVE
mdefine_line|#define HID_MAIN_ITEM_RELATIVE&t;&t;0x004
DECL|macro|HID_MAIN_ITEM_WRAP
mdefine_line|#define HID_MAIN_ITEM_WRAP&t;&t;0x008&t;
DECL|macro|HID_MAIN_ITEM_NONLINEAR
mdefine_line|#define HID_MAIN_ITEM_NONLINEAR&t;&t;0x010
DECL|macro|HID_MAIN_ITEM_NO_PREFERRED
mdefine_line|#define HID_MAIN_ITEM_NO_PREFERRED&t;0x020
DECL|macro|HID_MAIN_ITEM_NULL_STATE
mdefine_line|#define HID_MAIN_ITEM_NULL_STATE&t;0x040
DECL|macro|HID_MAIN_ITEM_VOLATILE
mdefine_line|#define HID_MAIN_ITEM_VOLATILE&t;&t;0x080
DECL|macro|HID_MAIN_ITEM_BUFFERED_BYTE
mdefine_line|#define HID_MAIN_ITEM_BUFFERED_BYTE&t;0x100
multiline_comment|/*&n; * HID report descriptor collection item types&n; */
DECL|macro|HID_COLLECTION_PHYSICAL
mdefine_line|#define HID_COLLECTION_PHYSICAL&t;&t;0
DECL|macro|HID_COLLECTION_APPLICATION
mdefine_line|#define HID_COLLECTION_APPLICATION&t;1
DECL|macro|HID_COLLECTION_LOGICAL
mdefine_line|#define HID_COLLECTION_LOGICAL&t;&t;2
multiline_comment|/*&n; * HID report descriptor global item tags&n; */
DECL|macro|HID_GLOBAL_ITEM_TAG_USAGE_PAGE
mdefine_line|#define HID_GLOBAL_ITEM_TAG_USAGE_PAGE&t;&t;0
DECL|macro|HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM
mdefine_line|#define HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM&t;1
DECL|macro|HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM
mdefine_line|#define HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM&t;2
DECL|macro|HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM
mdefine_line|#define HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM&t;3
DECL|macro|HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM
mdefine_line|#define HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM&t;4
DECL|macro|HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT
mdefine_line|#define HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT&t;5
DECL|macro|HID_GLOBAL_ITEM_TAG_UNIT
mdefine_line|#define HID_GLOBAL_ITEM_TAG_UNIT&t;&t;6
DECL|macro|HID_GLOBAL_ITEM_TAG_REPORT_SIZE
mdefine_line|#define HID_GLOBAL_ITEM_TAG_REPORT_SIZE&t;&t;7
DECL|macro|HID_GLOBAL_ITEM_TAG_REPORT_ID
mdefine_line|#define HID_GLOBAL_ITEM_TAG_REPORT_ID&t;&t;8
DECL|macro|HID_GLOBAL_ITEM_TAG_REPORT_COUNT
mdefine_line|#define HID_GLOBAL_ITEM_TAG_REPORT_COUNT&t;9
DECL|macro|HID_GLOBAL_ITEM_TAG_PUSH
mdefine_line|#define HID_GLOBAL_ITEM_TAG_PUSH&t;&t;10
DECL|macro|HID_GLOBAL_ITEM_TAG_POP
mdefine_line|#define HID_GLOBAL_ITEM_TAG_POP&t;&t;&t;11
multiline_comment|/*&n; * HID report descriptor local item tags&n; */
DECL|macro|HID_LOCAL_ITEM_TAG_USAGE
mdefine_line|#define HID_LOCAL_ITEM_TAG_USAGE&t;&t;0
DECL|macro|HID_LOCAL_ITEM_TAG_USAGE_MINIMUM
mdefine_line|#define HID_LOCAL_ITEM_TAG_USAGE_MINIMUM&t;1
DECL|macro|HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM
mdefine_line|#define HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM&t;2
DECL|macro|HID_LOCAL_ITEM_TAG_DESIGNATOR_INDEX
mdefine_line|#define HID_LOCAL_ITEM_TAG_DESIGNATOR_INDEX&t;3
DECL|macro|HID_LOCAL_ITEM_TAG_DESIGNATOR_MINIMUM
mdefine_line|#define HID_LOCAL_ITEM_TAG_DESIGNATOR_MINIMUM&t;4
DECL|macro|HID_LOCAL_ITEM_TAG_DESIGNATOR_MAXIMUM
mdefine_line|#define HID_LOCAL_ITEM_TAG_DESIGNATOR_MAXIMUM&t;5
DECL|macro|HID_LOCAL_ITEM_TAG_STRING_INDEX
mdefine_line|#define HID_LOCAL_ITEM_TAG_STRING_INDEX&t;&t;7
DECL|macro|HID_LOCAL_ITEM_TAG_STRING_MINIMUM
mdefine_line|#define HID_LOCAL_ITEM_TAG_STRING_MINIMUM&t;8
DECL|macro|HID_LOCAL_ITEM_TAG_STRING_MAXIMUM
mdefine_line|#define HID_LOCAL_ITEM_TAG_STRING_MAXIMUM&t;9
DECL|macro|HID_LOCAL_ITEM_TAG_DELIMITER
mdefine_line|#define HID_LOCAL_ITEM_TAG_DELIMITER&t;&t;10
multiline_comment|/*&n; * HID usage tables&n; */
DECL|macro|HID_USAGE_PAGE
mdefine_line|#define HID_USAGE_PAGE&t;&t;0xffff0000
DECL|macro|HID_UP_GENDESK
mdefine_line|#define HID_UP_GENDESK &t;&t;0x00010000
DECL|macro|HID_UP_KEYBOARD
mdefine_line|#define HID_UP_KEYBOARD &t;0x00070000
DECL|macro|HID_UP_LED
mdefine_line|#define HID_UP_LED &t;&t;0x00080000
DECL|macro|HID_UP_BUTTON
mdefine_line|#define HID_UP_BUTTON &t;&t;0x00090000
DECL|macro|HID_UP_CONSUMER
mdefine_line|#define HID_UP_CONSUMER&t;&t;0x000c0000
DECL|macro|HID_UP_DIGITIZER
mdefine_line|#define HID_UP_DIGITIZER &t;0x000d0000
DECL|macro|HID_UP_PID
mdefine_line|#define HID_UP_PID &t;&t;0x000f0000
DECL|macro|HID_USAGE
mdefine_line|#define HID_USAGE&t;&t;0x0000ffff
DECL|macro|HID_GD_POINTER
mdefine_line|#define HID_GD_POINTER&t;&t;0x00010001
DECL|macro|HID_GD_MOUSE
mdefine_line|#define HID_GD_MOUSE&t;&t;0x00010002
DECL|macro|HID_GD_JOYSTICK
mdefine_line|#define HID_GD_JOYSTICK&t;&t;0x00010004
DECL|macro|HID_GD_GAMEPAD
mdefine_line|#define HID_GD_GAMEPAD&t;&t;0x00010005
DECL|macro|HID_GD_HATSWITCH
mdefine_line|#define HID_GD_HATSWITCH&t;0x00010039
multiline_comment|/*&n; * HID report types --- Ouch! HID spec says 1 2 3!&n; */
DECL|macro|HID_INPUT_REPORT
mdefine_line|#define HID_INPUT_REPORT&t;0
DECL|macro|HID_OUTPUT_REPORT
mdefine_line|#define HID_OUTPUT_REPORT&t;1
DECL|macro|HID_FEATURE_REPORT
mdefine_line|#define HID_FEATURE_REPORT&t;2
multiline_comment|/*&n; * HID device quirks.&n; */
DECL|macro|HID_QUIRK_INVERT
mdefine_line|#define HID_QUIRK_INVERT&t;0x01
DECL|macro|HID_QUIRK_NOTOUCH
mdefine_line|#define HID_QUIRK_NOTOUCH&t;0x02
multiline_comment|/*&n; * This is the global enviroment of the parser. This information is&n; * persistent for main-items. The global enviroment can be saved and&n; * restored with PUSH/POP statements.&n; */
DECL|struct|hid_global
r_struct
id|hid_global
(brace
DECL|member|usage_page
r_int
id|usage_page
suffix:semicolon
DECL|member|logical_minimum
id|__s32
id|logical_minimum
suffix:semicolon
DECL|member|logical_maximum
id|__s32
id|logical_maximum
suffix:semicolon
DECL|member|physical_minimum
id|__s32
id|physical_minimum
suffix:semicolon
DECL|member|physical_maximum
id|__s32
id|physical_maximum
suffix:semicolon
DECL|member|unit_exponent
r_int
id|unit_exponent
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|report_id
r_int
id|report_id
suffix:semicolon
DECL|member|report_size
r_int
id|report_size
suffix:semicolon
DECL|member|report_count
r_int
id|report_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the local enviroment. It is resistent up the next main-item.&n; */
DECL|macro|HID_MAX_DESCRIPTOR_SIZE
mdefine_line|#define HID_MAX_DESCRIPTOR_SIZE&t;&t;4096
DECL|macro|HID_MAX_USAGES
mdefine_line|#define HID_MAX_USAGES&t;&t;&t;1024
DECL|struct|hid_local
r_struct
id|hid_local
(brace
DECL|member|usage
r_int
id|usage
(braket
id|HID_MAX_USAGES
)braket
suffix:semicolon
multiline_comment|/* usage array */
DECL|member|usage_index
r_int
id|usage_index
suffix:semicolon
DECL|member|usage_minimum
r_int
id|usage_minimum
suffix:semicolon
DECL|member|delimiter_depth
r_int
id|delimiter_depth
suffix:semicolon
DECL|member|delimiter_branch
r_int
id|delimiter_branch
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the collection stack. We climb up the stack to determine&n; * application and function of each field.&n; */
DECL|struct|hid_collection
r_struct
id|hid_collection
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|usage
r_int
id|usage
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hid_usage
r_struct
id|hid_usage
(brace
DECL|member|hid
r_int
id|hid
suffix:semicolon
multiline_comment|/* hid usage code */
DECL|member|code
id|__u16
id|code
suffix:semicolon
multiline_comment|/* input driver code */
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* input driver type */
DECL|member|hat
id|__u8
id|hat
suffix:semicolon
multiline_comment|/* hat switch fun */
)brace
suffix:semicolon
DECL|struct|hid_field
r_struct
id|hid_field
(brace
DECL|member|physical
r_int
id|physical
suffix:semicolon
multiline_comment|/* physical usage for this field */
DECL|member|logical
r_int
id|logical
suffix:semicolon
multiline_comment|/* logical usage for this field */
DECL|member|usage
r_struct
id|hid_usage
op_star
id|usage
suffix:semicolon
multiline_comment|/* usage table for this function */
DECL|member|maxusage
r_int
id|maxusage
suffix:semicolon
multiline_comment|/* maximum usage index */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* main-item flags (i.e. volatile,array,constant) */
DECL|member|report_offset
r_int
id|report_offset
suffix:semicolon
multiline_comment|/* bit offset in the report */
DECL|member|report_size
r_int
id|report_size
suffix:semicolon
multiline_comment|/* size of this field in the report */
DECL|member|report_count
r_int
id|report_count
suffix:semicolon
multiline_comment|/* number of this field in the report */
DECL|member|report_type
r_int
id|report_type
suffix:semicolon
multiline_comment|/* (input,output,feature) */
DECL|member|value
id|__s32
op_star
id|value
suffix:semicolon
multiline_comment|/* last known value(s) */
DECL|member|logical_minimum
id|__s32
id|logical_minimum
suffix:semicolon
DECL|member|logical_maximum
id|__s32
id|logical_maximum
suffix:semicolon
DECL|member|physical_minimum
id|__s32
id|physical_minimum
suffix:semicolon
DECL|member|physical_maximum
id|__s32
id|physical_maximum
suffix:semicolon
DECL|member|unit_exponent
r_int
id|unit_exponent
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|report
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
multiline_comment|/* associated report */
)brace
suffix:semicolon
DECL|macro|HID_MAX_FIELDS
mdefine_line|#define HID_MAX_FIELDS 64
DECL|struct|hid_report
r_struct
id|hid_report
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* id of this report */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* report type */
DECL|member|field
r_struct
id|hid_field
op_star
id|field
(braket
id|HID_MAX_FIELDS
)braket
suffix:semicolon
multiline_comment|/* fields of the report */
DECL|member|maxfield
r_int
id|maxfield
suffix:semicolon
multiline_comment|/* maximum valid field index */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of the report (bits) */
DECL|member|device
r_struct
id|hid_device
op_star
id|device
suffix:semicolon
multiline_comment|/* associated device */
)brace
suffix:semicolon
DECL|struct|hid_report_enum
r_struct
id|hid_report_enum
(brace
DECL|member|numbered
r_int
id|numbered
suffix:semicolon
DECL|member|report_list
r_struct
id|list_head
id|report_list
suffix:semicolon
DECL|member|report_id_hash
r_struct
id|hid_report
op_star
id|report_id_hash
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HID_REPORT_TYPES
mdefine_line|#define HID_REPORT_TYPES 3
DECL|macro|HID_BUFFER_SIZE
mdefine_line|#define HID_BUFFER_SIZE&t;&t;32
DECL|macro|HID_CONTROL_FIFO_SIZE
mdefine_line|#define HID_CONTROL_FIFO_SIZE&t;8
DECL|struct|hid_control_fifo
r_struct
id|hid_control_fifo
(brace
DECL|member|dr
id|devrequest
id|dr
suffix:semicolon
DECL|member|buffer
r_char
id|buffer
(braket
id|HID_BUFFER_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hid_device
r_struct
id|hid_device
(brace
multiline_comment|/* device report descriptor */
DECL|member|rdesc
id|__u8
op_star
id|rdesc
suffix:semicolon
DECL|member|rsize
r_int
id|rsize
suffix:semicolon
DECL|member|application
r_int
id|application
suffix:semicolon
multiline_comment|/* HID application, i.e. Digitizer */
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* HID version */
DECL|member|country
r_int
id|country
suffix:semicolon
multiline_comment|/* HID country */
DECL|member|report_enum
r_struct
id|hid_report_enum
id|report_enum
(braket
id|HID_REPORT_TYPES
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* USB device */
DECL|member|ifnum
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* USB interface number */
DECL|member|urb
r_struct
id|urb
id|urb
suffix:semicolon
multiline_comment|/* USB URB structure */
DECL|member|buffer
r_char
id|buffer
(braket
id|HID_BUFFER_SIZE
)braket
suffix:semicolon
multiline_comment|/* Rx buffer */
DECL|member|urbout
r_struct
id|urb
id|urbout
suffix:semicolon
multiline_comment|/* Output URB */
DECL|member|out
r_struct
id|hid_control_fifo
id|out
(braket
id|HID_CONTROL_FIFO_SIZE
)braket
suffix:semicolon
multiline_comment|/* Transmit buffer */
DECL|member|outhead
DECL|member|outtail
r_int
r_char
id|outhead
comma
id|outtail
suffix:semicolon
multiline_comment|/* Tx buffer head &amp; tail */
DECL|member|input
r_struct
id|input_dev
id|input
suffix:semicolon
multiline_comment|/* input device structure */
DECL|member|open
r_int
id|open
suffix:semicolon
multiline_comment|/* is the device open by input? */
DECL|member|quirks
r_int
id|quirks
suffix:semicolon
multiline_comment|/* Various nasty tricks the device can pull on us */
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Device name */
)brace
suffix:semicolon
DECL|macro|HID_GLOBAL_STACK_SIZE
mdefine_line|#define HID_GLOBAL_STACK_SIZE 4
DECL|macro|HID_COLLECTION_STACK_SIZE
mdefine_line|#define HID_COLLECTION_STACK_SIZE 4
DECL|struct|hid_parser
r_struct
id|hid_parser
(brace
DECL|member|global
r_struct
id|hid_global
id|global
suffix:semicolon
DECL|member|global_stack
r_struct
id|hid_global
id|global_stack
(braket
id|HID_GLOBAL_STACK_SIZE
)braket
suffix:semicolon
DECL|member|global_stack_ptr
r_int
id|global_stack_ptr
suffix:semicolon
DECL|member|local
r_struct
id|hid_local
id|local
suffix:semicolon
DECL|member|collection_stack
r_struct
id|hid_collection
id|collection_stack
(braket
id|HID_COLLECTION_STACK_SIZE
)braket
suffix:semicolon
DECL|member|collection_stack_ptr
r_int
id|collection_stack_ptr
suffix:semicolon
DECL|member|device
r_struct
id|hid_device
op_star
id|device
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hid_class_descriptor
r_struct
id|hid_class_descriptor
(brace
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|wDescriptorLength
id|__u16
id|wDescriptorLength
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|hid_descriptor
r_struct
id|hid_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bcdHID
id|__u16
id|bcdHID
suffix:semicolon
DECL|member|bCountryCode
id|__u8
id|bCountryCode
suffix:semicolon
DECL|member|bNumDescriptors
id|__u8
id|bNumDescriptors
suffix:semicolon
DECL|member|desc
r_struct
id|hid_class_descriptor
id|desc
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif
eof
