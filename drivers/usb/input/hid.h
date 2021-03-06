macro_line|#ifndef __HID_H
DECL|macro|__HID_H
mdefine_line|#define __HID_H
multiline_comment|/*&n; * $Id: hid.h,v 1.24 2001/12/27 10:37:41 vojtech Exp $&n; *&n; *  Copyright (c) 1999 Andreas Gal&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * USB HID (Human Interface Device) interface class code&n; */
DECL|macro|USB_INTERFACE_CLASS_HID
mdefine_line|#define USB_INTERFACE_CLASS_HID&t;&t;3
multiline_comment|/*&n; * HID class requests&n; */
DECL|macro|HID_REQ_GET_REPORT
mdefine_line|#define HID_REQ_GET_REPORT&t;&t;0x01
DECL|macro|HID_REQ_GET_IDLE
mdefine_line|#define HID_REQ_GET_IDLE&t;&t;0x02
DECL|macro|HID_REQ_GET_PROTOCOL
mdefine_line|#define HID_REQ_GET_PROTOCOL&t;&t;0x03
DECL|macro|HID_REQ_SET_REPORT
mdefine_line|#define HID_REQ_SET_REPORT&t;&t;0x09
DECL|macro|HID_REQ_SET_IDLE
mdefine_line|#define HID_REQ_SET_IDLE&t;&t;0x0A
DECL|macro|HID_REQ_SET_PROTOCOL
mdefine_line|#define HID_REQ_SET_PROTOCOL&t;&t;0x0B
multiline_comment|/*&n; * HID class descriptor types&n; */
DECL|macro|HID_DT_HID
mdefine_line|#define HID_DT_HID&t;&t;&t;(USB_TYPE_CLASS | 0x01)
DECL|macro|HID_DT_REPORT
mdefine_line|#define HID_DT_REPORT&t;&t;&t;(USB_TYPE_CLASS | 0x02)
DECL|macro|HID_DT_PHYSICAL
mdefine_line|#define HID_DT_PHYSICAL&t;&t;&t;(USB_TYPE_CLASS | 0x03)
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
DECL|macro|HID_UP_UNDEFINED
mdefine_line|#define HID_UP_UNDEFINED&t;0x00000000
DECL|macro|HID_UP_GENDESK
mdefine_line|#define HID_UP_GENDESK &t;&t;0x00010000
DECL|macro|HID_UP_KEYBOARD
mdefine_line|#define HID_UP_KEYBOARD &t;0x00070000
DECL|macro|HID_UP_LED
mdefine_line|#define HID_UP_LED &t;&t;0x00080000
DECL|macro|HID_UP_BUTTON
mdefine_line|#define HID_UP_BUTTON &t;&t;0x00090000
DECL|macro|HID_UP_ORDINAL
mdefine_line|#define HID_UP_ORDINAL &t;&t;0x000a0000
DECL|macro|HID_UP_CONSUMER
mdefine_line|#define HID_UP_CONSUMER&t;&t;0x000c0000
DECL|macro|HID_UP_DIGITIZER
mdefine_line|#define HID_UP_DIGITIZER &t;0x000d0000
DECL|macro|HID_UP_PID
mdefine_line|#define HID_UP_PID &t;&t;0x000f0000
DECL|macro|HID_UP_HPVENDOR
mdefine_line|#define HID_UP_HPVENDOR         0xff7f0000
DECL|macro|HID_UP_MSVENDOR
mdefine_line|#define HID_UP_MSVENDOR&t;&t;0xff000000
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
DECL|macro|HID_GD_KEYBOARD
mdefine_line|#define HID_GD_KEYBOARD&t;&t;0x00010006
DECL|macro|HID_GD_KEYPAD
mdefine_line|#define HID_GD_KEYPAD&t;&t;0x00010007
DECL|macro|HID_GD_MULTIAXIS
mdefine_line|#define HID_GD_MULTIAXIS&t;0x00010008
DECL|macro|HID_GD_X
mdefine_line|#define HID_GD_X&t;&t;0x00010030
DECL|macro|HID_GD_Y
mdefine_line|#define HID_GD_Y&t;&t;0x00010031
DECL|macro|HID_GD_Z
mdefine_line|#define HID_GD_Z&t;&t;0x00010032
DECL|macro|HID_GD_RX
mdefine_line|#define HID_GD_RX&t;&t;0x00010033
DECL|macro|HID_GD_RY
mdefine_line|#define HID_GD_RY&t;&t;0x00010034
DECL|macro|HID_GD_RZ
mdefine_line|#define HID_GD_RZ&t;&t;0x00010035
DECL|macro|HID_GD_SLIDER
mdefine_line|#define HID_GD_SLIDER&t;&t;0x00010036
DECL|macro|HID_GD_DIAL
mdefine_line|#define HID_GD_DIAL&t;&t;0x00010037
DECL|macro|HID_GD_WHEEL
mdefine_line|#define HID_GD_WHEEL&t;&t;0x00010038
DECL|macro|HID_GD_HATSWITCH
mdefine_line|#define HID_GD_HATSWITCH&t;0x00010039
DECL|macro|HID_GD_BUFFER
mdefine_line|#define HID_GD_BUFFER&t;&t;0x0001003a
DECL|macro|HID_GD_BYTECOUNT
mdefine_line|#define HID_GD_BYTECOUNT&t;0x0001003b
DECL|macro|HID_GD_MOTION
mdefine_line|#define HID_GD_MOTION&t;&t;0x0001003c
DECL|macro|HID_GD_START
mdefine_line|#define HID_GD_START&t;&t;0x0001003d
DECL|macro|HID_GD_SELECT
mdefine_line|#define HID_GD_SELECT&t;&t;0x0001003e
DECL|macro|HID_GD_VX
mdefine_line|#define HID_GD_VX&t;&t;0x00010040
DECL|macro|HID_GD_VY
mdefine_line|#define HID_GD_VY&t;&t;0x00010041
DECL|macro|HID_GD_VZ
mdefine_line|#define HID_GD_VZ&t;&t;0x00010042
DECL|macro|HID_GD_VBRX
mdefine_line|#define HID_GD_VBRX&t;&t;0x00010043
DECL|macro|HID_GD_VBRY
mdefine_line|#define HID_GD_VBRY&t;&t;0x00010044
DECL|macro|HID_GD_VBRZ
mdefine_line|#define HID_GD_VBRZ&t;&t;0x00010045
DECL|macro|HID_GD_VNO
mdefine_line|#define HID_GD_VNO&t;&t;0x00010046
DECL|macro|HID_GD_FEATURE
mdefine_line|#define HID_GD_FEATURE&t;&t;0x00010047
DECL|macro|HID_GD_UP
mdefine_line|#define HID_GD_UP&t;&t;0x00010090
DECL|macro|HID_GD_DOWN
mdefine_line|#define HID_GD_DOWN&t;&t;0x00010091
DECL|macro|HID_GD_RIGHT
mdefine_line|#define HID_GD_RIGHT&t;&t;0x00010092
DECL|macro|HID_GD_LEFT
mdefine_line|#define HID_GD_LEFT&t;&t;0x00010093
multiline_comment|/*&n; * HID report types --- Ouch! HID spec says 1 2 3!&n; */
DECL|macro|HID_INPUT_REPORT
mdefine_line|#define HID_INPUT_REPORT&t;0
DECL|macro|HID_OUTPUT_REPORT
mdefine_line|#define HID_OUTPUT_REPORT&t;1
DECL|macro|HID_FEATURE_REPORT
mdefine_line|#define HID_FEATURE_REPORT&t;2
multiline_comment|/*&n; * HID device quirks.&n; */
DECL|macro|HID_QUIRK_INVERT
mdefine_line|#define HID_QUIRK_INVERT&t;&t;&t;0x001
DECL|macro|HID_QUIRK_NOTOUCH
mdefine_line|#define HID_QUIRK_NOTOUCH&t;&t;&t;0x002
DECL|macro|HID_QUIRK_IGNORE
mdefine_line|#define HID_QUIRK_IGNORE&t;&t;&t;0x004
DECL|macro|HID_QUIRK_NOGET
mdefine_line|#define HID_QUIRK_NOGET&t;&t;&t;&t;0x008
DECL|macro|HID_QUIRK_HIDDEV
mdefine_line|#define HID_QUIRK_HIDDEV&t;&t;&t;0x010
DECL|macro|HID_QUIRK_BADPAD
mdefine_line|#define HID_QUIRK_BADPAD&t;&t;&t;0x020
DECL|macro|HID_QUIRK_MULTI_INPUT
mdefine_line|#define HID_QUIRK_MULTI_INPUT&t;&t;&t;0x040
DECL|macro|HID_QUIRK_2WHEEL_MOUSE_HACK_7
mdefine_line|#define HID_QUIRK_2WHEEL_MOUSE_HACK_7&t;&t;0x080
DECL|macro|HID_QUIRK_2WHEEL_MOUSE_HACK_5
mdefine_line|#define HID_QUIRK_2WHEEL_MOUSE_HACK_5&t;&t;0x100
DECL|macro|HID_QUIRK_2WHEEL_MOUSE_HACK_ON
mdefine_line|#define HID_QUIRK_2WHEEL_MOUSE_HACK_ON&t;&t;0x200
multiline_comment|/*&n; * This is the global environment of the parser. This information is&n; * persistent for main-items. The global environment can be saved and&n; * restored with PUSH/POP statements.&n; */
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
id|__s32
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
multiline_comment|/*&n; * This is the local environment. It is persistent up the next main-item.&n; */
DECL|macro|HID_MAX_DESCRIPTOR_SIZE
mdefine_line|#define HID_MAX_DESCRIPTOR_SIZE&t;&t;4096
DECL|macro|HID_MAX_USAGES
mdefine_line|#define HID_MAX_USAGES&t;&t;&t;1024
DECL|macro|HID_DEFAULT_NUM_COLLECTIONS
mdefine_line|#define HID_DEFAULT_NUM_COLLECTIONS&t;16
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
DECL|member|collection_index
r_int
id|collection_index
(braket
id|HID_MAX_USAGES
)braket
suffix:semicolon
multiline_comment|/* collection index array */
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
DECL|member|level
r_int
id|level
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
DECL|member|collection_index
r_int
id|collection_index
suffix:semicolon
multiline_comment|/* index into collection array */
multiline_comment|/* hidinput data */
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
DECL|member|hat_min
id|__s8
id|hat_min
suffix:semicolon
multiline_comment|/* hat switch fun */
DECL|member|hat_max
id|__s8
id|hat_max
suffix:semicolon
multiline_comment|/* ditto */
DECL|member|hat_dir
id|__s8
id|hat_dir
suffix:semicolon
multiline_comment|/* ditto */
)brace
suffix:semicolon
r_struct
id|hid_input
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
DECL|member|application
r_int
id|application
suffix:semicolon
multiline_comment|/* application usage for this field */
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
id|__s32
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
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* index into report-&gt;field[] */
multiline_comment|/* hidinput data */
DECL|member|hidinput
r_struct
id|hid_input
op_star
id|hidinput
suffix:semicolon
multiline_comment|/* associated input structure */
DECL|member|dpad
id|__u16
id|dpad
suffix:semicolon
multiline_comment|/* dpad input code */
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
mdefine_line|#define HID_BUFFER_SIZE&t;&t;64&t;&t;/* use 64 for compatibility with all possible packetlen */
DECL|macro|HID_CONTROL_FIFO_SIZE
mdefine_line|#define HID_CONTROL_FIFO_SIZE&t;256&t;&t;/* to init devices with &gt;100 reports */
DECL|macro|HID_OUTPUT_FIFO_SIZE
mdefine_line|#define HID_OUTPUT_FIFO_SIZE&t;64
DECL|struct|hid_control_fifo
r_struct
id|hid_control_fifo
(brace
DECL|member|dir
r_int
r_char
id|dir
suffix:semicolon
DECL|member|report
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HID_CLAIMED_INPUT
mdefine_line|#define HID_CLAIMED_INPUT&t;1
DECL|macro|HID_CLAIMED_HIDDEV
mdefine_line|#define HID_CLAIMED_HIDDEV&t;2
DECL|macro|HID_CTRL_RUNNING
mdefine_line|#define HID_CTRL_RUNNING&t;1
DECL|macro|HID_OUT_RUNNING
mdefine_line|#define HID_OUT_RUNNING&t;&t;2
DECL|struct|hid_input
r_struct
id|hid_input
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|report
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
DECL|member|input
r_struct
id|input_dev
id|input
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
DECL|member|collection
r_struct
id|hid_collection
op_star
id|collection
suffix:semicolon
multiline_comment|/* List of HID collections */
DECL|member|collection_size
r_int
id|collection_size
suffix:semicolon
multiline_comment|/* Number of allocated hid_collections */
DECL|member|maxcollection
r_int
id|maxcollection
suffix:semicolon
multiline_comment|/* Number of parsed collections */
DECL|member|maxapplication
r_int
id|maxapplication
suffix:semicolon
multiline_comment|/* Number of applications */
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
DECL|member|intf
r_struct
id|usb_interface
op_star
id|intf
suffix:semicolon
multiline_comment|/* USB interface */
DECL|member|ifnum
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* USB interface number */
DECL|member|iofl
r_int
r_int
id|iofl
suffix:semicolon
multiline_comment|/* I/O flags (CTRL_RUNNING, OUT_RUNNING) */
DECL|member|urbin
r_struct
id|urb
op_star
id|urbin
suffix:semicolon
multiline_comment|/* Input URB */
DECL|member|inbuf
r_char
op_star
id|inbuf
suffix:semicolon
multiline_comment|/* Input buffer */
DECL|member|inbuf_dma
id|dma_addr_t
id|inbuf_dma
suffix:semicolon
multiline_comment|/* Input buffer dma */
DECL|member|urbctrl
r_struct
id|urb
op_star
id|urbctrl
suffix:semicolon
multiline_comment|/* Control URB */
DECL|member|cr
r_struct
id|usb_ctrlrequest
op_star
id|cr
suffix:semicolon
multiline_comment|/* Control request struct */
DECL|member|cr_dma
id|dma_addr_t
id|cr_dma
suffix:semicolon
multiline_comment|/* Control request struct dma */
DECL|member|ctrl
r_struct
id|hid_control_fifo
id|ctrl
(braket
id|HID_CONTROL_FIFO_SIZE
)braket
suffix:semicolon
multiline_comment|/* Control fifo */
DECL|member|ctrlhead
DECL|member|ctrltail
r_int
r_char
id|ctrlhead
comma
id|ctrltail
suffix:semicolon
multiline_comment|/* Control fifo head &amp; tail */
DECL|member|ctrlbuf
r_char
op_star
id|ctrlbuf
suffix:semicolon
multiline_comment|/* Control buffer */
DECL|member|ctrlbuf_dma
id|dma_addr_t
id|ctrlbuf_dma
suffix:semicolon
multiline_comment|/* Control buffer dma */
DECL|member|ctrllock
id|spinlock_t
id|ctrllock
suffix:semicolon
multiline_comment|/* Control fifo spinlock */
DECL|member|urbout
r_struct
id|urb
op_star
id|urbout
suffix:semicolon
multiline_comment|/* Output URB */
DECL|member|out
r_struct
id|hid_report
op_star
id|out
(braket
id|HID_CONTROL_FIFO_SIZE
)braket
suffix:semicolon
multiline_comment|/* Output pipe fifo */
DECL|member|outhead
DECL|member|outtail
r_int
r_char
id|outhead
comma
id|outtail
suffix:semicolon
multiline_comment|/* Output pipe fifo head &amp; tail */
DECL|member|outbuf
r_char
op_star
id|outbuf
suffix:semicolon
multiline_comment|/* Output buffer */
DECL|member|outbuf_dma
id|dma_addr_t
id|outbuf_dma
suffix:semicolon
multiline_comment|/* Output buffer dma */
DECL|member|outlock
id|spinlock_t
id|outlock
suffix:semicolon
multiline_comment|/* Output fifo spinlock */
DECL|member|claimed
r_int
id|claimed
suffix:semicolon
multiline_comment|/* Claimed by hidinput, hiddev? */
DECL|member|quirks
r_int
id|quirks
suffix:semicolon
multiline_comment|/* Various quirks the device can pull on us */
DECL|member|inputs
r_struct
id|list_head
id|inputs
suffix:semicolon
multiline_comment|/* The list of inputs */
DECL|member|hiddev
r_void
op_star
id|hiddev
suffix:semicolon
multiline_comment|/* The hiddev structure */
DECL|member|minor
r_int
id|minor
suffix:semicolon
multiline_comment|/* Hiddev minor number */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* For sleeping */
DECL|member|open
r_int
id|open
suffix:semicolon
multiline_comment|/* is the device open by anyone? */
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Device name */
DECL|member|phys
r_char
id|phys
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Device physical location */
DECL|member|uniq
r_char
id|uniq
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Device unique identifier (serial #) */
DECL|member|ff_private
r_void
op_star
id|ff_private
suffix:semicolon
multiline_comment|/* Private data for the force-feedback driver */
DECL|member|ff_exit
r_void
(paren
op_star
id|ff_exit
)paren
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Called by hid_exit_ff(hid) */
DECL|member|ff_event
r_int
(paren
op_star
id|ff_event
)paren
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|input_dev
op_star
id|input
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
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
r_int
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
macro_line|#ifdef DEBUG
macro_line|#include &quot;hid-debug.h&quot;
macro_line|#else
DECL|macro|hid_dump_input
mdefine_line|#define hid_dump_input(a,b)&t;do { } while (0)
DECL|macro|hid_dump_device
mdefine_line|#define hid_dump_device(c)&t;do { } while (0)
DECL|macro|hid_dump_field
mdefine_line|#define hid_dump_field(a,b)&t;do { } while (0)
DECL|macro|resolv_usage
mdefine_line|#define resolv_usage(a)&t;&t;do { } while (0)
DECL|macro|resolv_event
mdefine_line|#define resolv_event(a,b)&t;do { } while (0)
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_USB_HIDINPUT
multiline_comment|/* Applications from HID Usage Tables 4/8/99 Version 1.1 */
multiline_comment|/* We ignore a few input applications that are not widely used */
DECL|macro|IS_INPUT_APPLICATION
mdefine_line|#define IS_INPUT_APPLICATION(a) (((a &gt;= 0x00010000) &amp;&amp; (a &lt;= 0x00010008)) || (a == 0x00010080) || (a == 0x000c0001))
r_extern
r_void
id|hidinput_hid_event
c_func
(paren
r_struct
id|hid_device
op_star
comma
r_struct
id|hid_field
op_star
comma
r_struct
id|hid_usage
op_star
comma
id|__s32
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|hidinput_report_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|hid_report
op_star
id|report
)paren
suffix:semicolon
r_extern
r_int
id|hidinput_connect
c_func
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hidinput_disconnect
c_func
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|IS_INPUT_APPLICATION
mdefine_line|#define IS_INPUT_APPLICATION(a) (0)
DECL|function|hidinput_hid_event
r_static
r_inline
r_void
id|hidinput_hid_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|hid_field
op_star
id|field
comma
r_struct
id|hid_usage
op_star
id|usage
comma
id|__s32
id|value
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
)brace
DECL|function|hidinput_report_event
r_static
r_inline
r_void
id|hidinput_report_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|hid_report
op_star
id|report
)paren
(brace
)brace
DECL|function|hidinput_connect
r_static
r_inline
r_int
id|hidinput_connect
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|hidinput_disconnect
r_static
r_inline
r_void
id|hidinput_disconnect
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
)brace
macro_line|#endif
r_int
id|hid_open
c_func
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
r_void
id|hid_close
c_func
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
r_int
id|hid_set_field
c_func
(paren
r_struct
id|hid_field
op_star
comma
r_int
comma
id|__s32
)paren
suffix:semicolon
r_void
id|hid_submit_report
c_func
(paren
r_struct
id|hid_device
op_star
comma
r_struct
id|hid_report
op_star
comma
r_int
r_char
id|dir
)paren
suffix:semicolon
r_void
id|hid_init_reports
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
r_struct
id|hid_field
op_star
id|hid_find_field_by_usage
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
id|__u32
id|wanted_usage
comma
r_int
id|type
)paren
suffix:semicolon
r_int
id|hid_wait_io
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HID_FF
r_int
id|hid_ff_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
macro_line|#else
DECL|function|hid_ff_init
r_static
r_inline
r_int
id|hid_ff_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|hid_ff_exit
r_static
r_inline
r_void
id|hid_ff_exit
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_if
c_cond
(paren
id|hid-&gt;ff_exit
)paren
id|hid
op_member_access_from_pointer
id|ff_exit
c_func
(paren
id|hid
)paren
suffix:semicolon
)brace
DECL|function|hid_ff_event
r_static
r_inline
r_int
id|hid_ff_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|input_dev
op_star
id|input
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|hid-&gt;ff_event
)paren
r_return
id|hid
op_member_access_from_pointer
id|ff_event
c_func
(paren
id|hid
comma
id|input
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
