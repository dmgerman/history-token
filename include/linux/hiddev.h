macro_line|#ifndef _HIDDEV_H
DECL|macro|_HIDDEV_H
mdefine_line|#define _HIDDEV_H
multiline_comment|/*&n; * $Id: hiddev.h,v 1.2 2001/04/26 11:26:09 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
multiline_comment|/*&n; * The event structure itself&n; */
DECL|struct|hiddev_event
r_struct
id|hiddev_event
(brace
DECL|member|hid
r_int
id|hid
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hiddev_devinfo
r_struct
id|hiddev_devinfo
(brace
DECL|member|bustype
id|__u32
id|bustype
suffix:semicolon
DECL|member|busnum
id|__u32
id|busnum
suffix:semicolon
DECL|member|devnum
id|__u32
id|devnum
suffix:semicolon
DECL|member|ifnum
id|__u32
id|ifnum
suffix:semicolon
DECL|member|vendor
id|__s16
id|vendor
suffix:semicolon
DECL|member|product
id|__s16
id|product
suffix:semicolon
DECL|member|version
id|__s16
id|version
suffix:semicolon
DECL|member|num_applications
id|__u32
id|num_applications
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hiddev_collection_info
r_struct
id|hiddev_collection_info
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|type
id|__u32
id|type
suffix:semicolon
DECL|member|usage
id|__u32
id|usage
suffix:semicolon
DECL|member|level
id|__u32
id|level
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HID_STRING_SIZE
mdefine_line|#define HID_STRING_SIZE 256
DECL|struct|hiddev_string_descriptor
r_struct
id|hiddev_string_descriptor
(brace
DECL|member|index
id|__s32
id|index
suffix:semicolon
DECL|member|value
r_char
id|value
(braket
id|HID_STRING_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hiddev_report_info
r_struct
id|hiddev_report_info
(brace
DECL|member|report_type
id|__u32
id|report_type
suffix:semicolon
DECL|member|report_id
id|__u32
id|report_id
suffix:semicolon
DECL|member|num_fields
id|__u32
id|num_fields
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* To do a GUSAGE/SUSAGE, fill in at least usage_code,  report_type and &n; * report_id.  Set report_id to REPORT_ID_UNKNOWN if the rest of the fields &n; * are unknown.  Otherwise use a usage_ref struct filled in from a previous &n; * successful GUSAGE call to save time.  To actually send a value to the&n; * device, perform a SUSAGE first, followed by a SREPORT.  An INITREPORT or a&n; * GREPORT isn&squot;t necessary for a GUSAGE to return valid data.&n; */
DECL|macro|HID_REPORT_ID_UNKNOWN
mdefine_line|#define HID_REPORT_ID_UNKNOWN 0xffffffff
DECL|macro|HID_REPORT_ID_FIRST
mdefine_line|#define HID_REPORT_ID_FIRST   0x00000100
DECL|macro|HID_REPORT_ID_NEXT
mdefine_line|#define HID_REPORT_ID_NEXT    0x00000200
DECL|macro|HID_REPORT_ID_MASK
mdefine_line|#define HID_REPORT_ID_MASK    0x000000ff
DECL|macro|HID_REPORT_ID_MAX
mdefine_line|#define HID_REPORT_ID_MAX     0x000000ff
DECL|macro|HID_REPORT_TYPE_INPUT
mdefine_line|#define HID_REPORT_TYPE_INPUT&t;1
DECL|macro|HID_REPORT_TYPE_OUTPUT
mdefine_line|#define HID_REPORT_TYPE_OUTPUT&t;2
DECL|macro|HID_REPORT_TYPE_FEATURE
mdefine_line|#define HID_REPORT_TYPE_FEATURE&t;3
DECL|macro|HID_REPORT_TYPE_MIN
mdefine_line|#define HID_REPORT_TYPE_MIN     1
DECL|macro|HID_REPORT_TYPE_MAX
mdefine_line|#define HID_REPORT_TYPE_MAX     3
DECL|struct|hiddev_field_info
r_struct
id|hiddev_field_info
(brace
DECL|member|report_type
id|__u32
id|report_type
suffix:semicolon
DECL|member|report_id
id|__u32
id|report_id
suffix:semicolon
DECL|member|field_index
id|__u32
id|field_index
suffix:semicolon
DECL|member|maxusage
id|__u32
id|maxusage
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|physical
id|__u32
id|physical
suffix:semicolon
multiline_comment|/* physical usage for this field */
DECL|member|logical
id|__u32
id|logical
suffix:semicolon
multiline_comment|/* logical usage for this field */
DECL|member|application
id|__u32
id|application
suffix:semicolon
multiline_comment|/* application usage for this field */
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
id|__u32
id|unit_exponent
suffix:semicolon
DECL|member|unit
id|__u32
id|unit
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Fill in report_type, report_id and field_index to get the information on a&n; * field.&n; */
DECL|macro|HID_FIELD_CONSTANT
mdefine_line|#define HID_FIELD_CONSTANT&t;&t;0x001
DECL|macro|HID_FIELD_VARIABLE
mdefine_line|#define HID_FIELD_VARIABLE&t;&t;0x002
DECL|macro|HID_FIELD_RELATIVE
mdefine_line|#define HID_FIELD_RELATIVE&t;&t;0x004
DECL|macro|HID_FIELD_WRAP
mdefine_line|#define HID_FIELD_WRAP&t;&t;&t;0x008&t;
DECL|macro|HID_FIELD_NONLINEAR
mdefine_line|#define HID_FIELD_NONLINEAR&t;&t;0x010
DECL|macro|HID_FIELD_NO_PREFERRED
mdefine_line|#define HID_FIELD_NO_PREFERRED&t;&t;0x020
DECL|macro|HID_FIELD_NULL_STATE
mdefine_line|#define HID_FIELD_NULL_STATE&t;&t;0x040
DECL|macro|HID_FIELD_VOLATILE
mdefine_line|#define HID_FIELD_VOLATILE&t;&t;0x080
DECL|macro|HID_FIELD_BUFFERED_BYTE
mdefine_line|#define HID_FIELD_BUFFERED_BYTE&t;&t;0x100
DECL|struct|hiddev_usage_ref
r_struct
id|hiddev_usage_ref
(brace
DECL|member|report_type
id|__u32
id|report_type
suffix:semicolon
DECL|member|report_id
id|__u32
id|report_id
suffix:semicolon
DECL|member|field_index
id|__u32
id|field_index
suffix:semicolon
DECL|member|usage_index
id|__u32
id|usage_index
suffix:semicolon
DECL|member|usage_code
id|__u32
id|usage_code
suffix:semicolon
DECL|member|value
id|__s32
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hiddev_usage_ref_multi is used for sending multiple bytes to a control.&n; * It really manifests itself as setting the value of consecutive usages */
DECL|macro|HID_MAX_MULTI_USAGES
mdefine_line|#define HID_MAX_MULTI_USAGES 1024
DECL|struct|hiddev_usage_ref_multi
r_struct
id|hiddev_usage_ref_multi
(brace
DECL|member|uref
r_struct
id|hiddev_usage_ref
id|uref
suffix:semicolon
DECL|member|num_values
id|__u32
id|num_values
suffix:semicolon
DECL|member|values
id|__s32
id|values
(braket
id|HID_MAX_MULTI_USAGES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FIELD_INDEX_NONE is returned in read() data from the kernel when flags&n; * is set to (HIDDEV_FLAG_UREF | HIDDEV_FLAG_REPORT) and a new report has&n; * been sent by the device &n; */
DECL|macro|HID_FIELD_INDEX_NONE
mdefine_line|#define HID_FIELD_INDEX_NONE 0xffffffff
multiline_comment|/*&n; * Protocol version.&n; */
DECL|macro|HID_VERSION
mdefine_line|#define HID_VERSION&t;&t;0x010004
multiline_comment|/*&n; * IOCTLs (0x00 - 0x7f)&n; */
DECL|macro|HIDIOCGVERSION
mdefine_line|#define HIDIOCGVERSION&t;&t;_IOR(&squot;H&squot;, 0x01, int)
DECL|macro|HIDIOCAPPLICATION
mdefine_line|#define HIDIOCAPPLICATION&t;_IO(&squot;H&squot;, 0x02)
DECL|macro|HIDIOCGDEVINFO
mdefine_line|#define HIDIOCGDEVINFO&t;&t;_IOR(&squot;H&squot;, 0x03, struct hiddev_devinfo)
DECL|macro|HIDIOCGSTRING
mdefine_line|#define HIDIOCGSTRING&t;&t;_IOR(&squot;H&squot;, 0x04, struct hiddev_string_descriptor)
DECL|macro|HIDIOCINITREPORT
mdefine_line|#define HIDIOCINITREPORT&t;_IO(&squot;H&squot;, 0x05)
DECL|macro|HIDIOCGNAME
mdefine_line|#define HIDIOCGNAME(len)&t;_IOC(_IOC_READ, &squot;H&squot;, 0x06, len)
DECL|macro|HIDIOCGREPORT
mdefine_line|#define HIDIOCGREPORT&t;&t;_IOW(&squot;H&squot;, 0x07, struct hiddev_report_info)
DECL|macro|HIDIOCSREPORT
mdefine_line|#define HIDIOCSREPORT&t;&t;_IOW(&squot;H&squot;, 0x08, struct hiddev_report_info)
DECL|macro|HIDIOCGREPORTINFO
mdefine_line|#define HIDIOCGREPORTINFO&t;_IOWR(&squot;H&squot;, 0x09, struct hiddev_report_info)
DECL|macro|HIDIOCGFIELDINFO
mdefine_line|#define HIDIOCGFIELDINFO&t;_IOWR(&squot;H&squot;, 0x0A, struct hiddev_field_info)
DECL|macro|HIDIOCGUSAGE
mdefine_line|#define HIDIOCGUSAGE&t;&t;_IOWR(&squot;H&squot;, 0x0B, struct hiddev_usage_ref)
DECL|macro|HIDIOCSUSAGE
mdefine_line|#define HIDIOCSUSAGE&t;&t;_IOW(&squot;H&squot;, 0x0C, struct hiddev_usage_ref)
DECL|macro|HIDIOCGUCODE
mdefine_line|#define HIDIOCGUCODE&t;&t;_IOWR(&squot;H&squot;, 0x0D, struct hiddev_usage_ref)
DECL|macro|HIDIOCGFLAG
mdefine_line|#define HIDIOCGFLAG&t;&t;_IOR(&squot;H&squot;, 0x0E, int)
DECL|macro|HIDIOCSFLAG
mdefine_line|#define HIDIOCSFLAG&t;&t;_IOW(&squot;H&squot;, 0x0F, int)
DECL|macro|HIDIOCGCOLLECTIONINDEX
mdefine_line|#define HIDIOCGCOLLECTIONINDEX&t;_IOW(&squot;H&squot;, 0x10, struct hiddev_usage_ref)
DECL|macro|HIDIOCGCOLLECTIONINFO
mdefine_line|#define HIDIOCGCOLLECTIONINFO&t;_IOWR(&squot;H&squot;, 0x11, struct hiddev_collection_info)
DECL|macro|HIDIOCGPHYS
mdefine_line|#define HIDIOCGPHYS(len)&t;_IOC(_IOC_READ, &squot;H&squot;, 0x12, len)
multiline_comment|/* For writing/reading to multiple/consecutive usages */
DECL|macro|HIDIOCGUSAGES
mdefine_line|#define HIDIOCGUSAGES&t;&t;_IOWR(&squot;H&squot;, 0x13, struct hiddev_usage_ref_multi)
DECL|macro|HIDIOCSUSAGES
mdefine_line|#define HIDIOCSUSAGES&t;&t;_IOW(&squot;H&squot;, 0x14, struct hiddev_usage_ref_multi)
multiline_comment|/* &n; * Flags to be used in HIDIOCSFLAG&n; */
DECL|macro|HIDDEV_FLAG_UREF
mdefine_line|#define HIDDEV_FLAG_UREF&t;0x1
DECL|macro|HIDDEV_FLAG_REPORT
mdefine_line|#define HIDDEV_FLAG_REPORT&t;0x2
DECL|macro|HIDDEV_FLAGS
mdefine_line|#define HIDDEV_FLAGS&t;&t;0x3
multiline_comment|/* To traverse the input report descriptor info for a HID device, perform the &n; * following:&n; *&n; *  rinfo.report_type = HID_REPORT_TYPE_INPUT;&n; *  rinfo.report_id = HID_REPORT_ID_FIRST;&n; *  ret = ioctl(fd, HIDIOCGREPORTINFO, &amp;rinfo);&n; *&n; *  while (ret &gt;= 0) {&n; *      for (i = 0; i &lt; rinfo.num_fields; i++) { &n; *&t;    finfo.report_type = rinfo.report_type;&n; *          finfo.report_id = rinfo.report_id;&n; *          finfo.field_index = i;&n; *          ioctl(fd, HIDIOCGFIELDINFO, &amp;finfo);&n; *          for (j = 0; j &lt; finfo.maxusage; j++) {&n; *              uref.field_index = i;&n; *&t;&t;uref.usage_index = j;&n; *&t;&t;ioctl(fd, HIDIOCGUCODE, &amp;uref);&n; *&t;&t;ioctl(fd, HIDIOCGUSAGE, &amp;uref);&n; *          }&n; *&t;}&n; *&t;uref.report_id |= HID_REPORT_ID_NEXT;&n; *&t;ret = ioctl(fd, HIDIOCGREPORTINFO, &amp;uref);&n; *  }&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-kernel definitions.&n; */
macro_line|#ifdef CONFIG_USB_HIDDEV
r_struct
id|hid_device
suffix:semicolon
r_struct
id|hid_usage
suffix:semicolon
r_struct
id|hid_field
suffix:semicolon
r_struct
id|hid_report
suffix:semicolon
r_int
id|hiddev_connect
c_func
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
r_void
id|hiddev_disconnect
c_func
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
r_void
id|hiddev_hid_event
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
suffix:semicolon
r_void
id|hiddev_report_event
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
r_int
id|__init
id|hiddev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|hiddev_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|hiddev_connect
r_static
r_inline
r_int
id|hiddev_connect
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
DECL|function|hiddev_disconnect
r_static
r_inline
r_void
id|hiddev_disconnect
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
)brace
DECL|function|hiddev_hid_event
r_static
r_inline
r_void
id|hiddev_hid_event
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
DECL|function|hiddev_report_event
r_static
r_inline
r_void
id|hiddev_report_event
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
DECL|function|hiddev_init
r_static
r_inline
r_int
id|hiddev_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hiddev_exit
r_static
r_inline
r_void
id|hiddev_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
