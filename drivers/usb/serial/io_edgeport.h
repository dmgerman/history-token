multiline_comment|/************************************************************************&n; *&n; *&t;io_edgeport.h&t;Edgeport Linux Interface definitions&n; *&n; *&t;Copyright (c) 2000 Inside Out Networks, Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&n; ************************************************************************/
macro_line|#if !defined(_IO_EDGEPORT_H_)
DECL|macro|_IO_EDGEPORT_H_
mdefine_line|#define&t;_IO_EDGEPORT_H_
DECL|macro|MAX_RS232_PORTS
mdefine_line|#define MAX_RS232_PORTS&t;&t;8&t;/* Max # of RS-232 ports per device */
multiline_comment|/* typedefs that the insideout headers need */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE&t;&t;(1)
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE&t;&t;(0)
macro_line|#endif
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;(((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef MAX
DECL|macro|MAX
mdefine_line|#define MAX(a,b)&t;(((a)&gt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef max
DECL|macro|max
mdefine_line|#define max&t;&t;MAX
macro_line|#endif
macro_line|#ifndef LOW8
DECL|macro|LOW8
mdefine_line|#define LOW8(a)&t;&t;((unsigned char)(a &amp; 0xff))
macro_line|#endif
macro_line|#ifndef HIGH8
DECL|macro|HIGH8
mdefine_line|#define HIGH8(a)&t;((unsigned char)((a &amp; 0xff00) &gt;&gt; 8))
macro_line|#endif
macro_line|#ifndef NUM_ENTRIES
DECL|macro|NUM_ENTRIES
mdefine_line|#define NUM_ENTRIES(x)&t;(sizeof(x)/sizeof((x)[0]))
macro_line|#endif
macro_line|#ifndef __KERNEL__
DECL|macro|__KERNEL__
mdefine_line|#define __KERNEL__
macro_line|#endif
macro_line|#include &quot;io_usbvend.h&quot;
multiline_comment|/* The following table is used to map the USBx port number to &n; * the device serial number (or physical USB path), */
DECL|macro|MAX_EDGEPORTS
mdefine_line|#define MAX_EDGEPORTS&t;64
DECL|struct|comMapper
r_struct
id|comMapper
(brace
DECL|member|SerialNumber
r_char
id|SerialNumber
(braket
id|MAX_SERIALNUMBER_LEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Serial number/usb path */
DECL|member|numPorts
r_int
id|numPorts
suffix:semicolon
multiline_comment|/* Number of ports */
DECL|member|Original
r_int
id|Original
(braket
id|MAX_RS232_PORTS
)braket
suffix:semicolon
multiline_comment|/* Port numbers set by IOCTL */
DECL|member|Port
r_int
id|Port
(braket
id|MAX_RS232_PORTS
)braket
suffix:semicolon
multiline_comment|/* Actual used port numbers */
)brace
suffix:semicolon
DECL|macro|EDGEPORT_CONFIG_DEVICE
mdefine_line|#define EDGEPORT_CONFIG_DEVICE &quot;/proc/edgeport&quot;
multiline_comment|/* /proc/edgeport Interface&n; * This interface uses read/write/lseek interface to talk to the edgeport driver&n; * the following read functions are supported: */
DECL|macro|PROC_GET_MAPPING_TO_PATH
mdefine_line|#define PROC_GET_MAPPING_TO_PATH &t;1
DECL|macro|PROC_GET_COM_ENTRY
mdefine_line|#define PROC_GET_COM_ENTRY&t;&t;2
DECL|macro|PROC_GET_EDGE_MANUF_DESCRIPTOR
mdefine_line|#define PROC_GET_EDGE_MANUF_DESCRIPTOR&t;3
DECL|macro|PROC_GET_BOOT_DESCRIPTOR
mdefine_line|#define PROC_GET_BOOT_DESCRIPTOR&t;4
DECL|macro|PROC_GET_PRODUCT_INFO
mdefine_line|#define PROC_GET_PRODUCT_INFO&t;&t;5
DECL|macro|PROC_GET_STRINGS
mdefine_line|#define PROC_GET_STRINGS&t;&t;6
DECL|macro|PROC_GET_CURRENT_COM_MAPPING
mdefine_line|#define PROC_GET_CURRENT_COM_MAPPING&t;7
multiline_comment|/* The parameters to the lseek() for the read is: */
DECL|macro|PROC_READ_SETUP
mdefine_line|#define PROC_READ_SETUP(Command, Argument)&t;((Command) + ((Argument)&lt;&lt;8))
multiline_comment|/* the following write functions are supported: */
DECL|macro|PROC_SET_COM_MAPPING
mdefine_line|#define PROC_SET_COM_MAPPING &t;&t;1
DECL|macro|PROC_SET_COM_ENTRY
mdefine_line|#define PROC_SET_COM_ENTRY&t;&t;2
multiline_comment|/* The following sturcture is passed to the write */
DECL|struct|procWrite
r_struct
id|procWrite
(brace
DECL|member|Command
r_int
id|Command
suffix:semicolon
r_union
(brace
DECL|member|Entry
r_struct
id|comMapper
id|Entry
suffix:semicolon
DECL|member|ComMappingBasedOnUSBPort
r_int
id|ComMappingBasedOnUSBPort
suffix:semicolon
multiline_comment|/* Boolean value */
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Product information read from the Edgeport&n; */
DECL|struct|edgeport_product_info
r_struct
id|edgeport_product_info
(brace
DECL|member|ProductId
id|__u16
id|ProductId
suffix:semicolon
multiline_comment|/* Product Identifier */
DECL|member|NumPorts
id|__u8
id|NumPorts
suffix:semicolon
multiline_comment|/* Number of ports on edgeport */
DECL|member|ProdInfoVer
id|__u8
id|ProdInfoVer
suffix:semicolon
multiline_comment|/* What version of structure is this? */
DECL|member|IsServer
id|__u32
id|IsServer
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Set if Server */
DECL|member|IsRS232
id|__u32
id|IsRS232
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Set if RS-232 ports exist */
DECL|member|IsRS422
id|__u32
id|IsRS422
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Set if RS-422 ports exist */
DECL|member|IsRS485
id|__u32
id|IsRS485
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Set if RS-485 ports exist */
DECL|member|IsReserved
id|__u32
id|IsReserved
suffix:colon
l_int|28
suffix:semicolon
multiline_comment|/* Reserved for later expansion */
DECL|member|RomSize
id|__u8
id|RomSize
suffix:semicolon
multiline_comment|/* Size of ROM/E2PROM in K */
DECL|member|RamSize
id|__u8
id|RamSize
suffix:semicolon
multiline_comment|/* Size of external RAM in K */
DECL|member|CpuRev
id|__u8
id|CpuRev
suffix:semicolon
multiline_comment|/* CPU revision level (chg only if s/w visible) */
DECL|member|BoardRev
id|__u8
id|BoardRev
suffix:semicolon
multiline_comment|/* PCB revision level (chg only if s/w visible) */
DECL|member|BootMajorVersion
id|__u8
id|BootMajorVersion
suffix:semicolon
multiline_comment|/* Boot Firmware version: xx. */
DECL|member|BootMinorVersion
id|__u8
id|BootMinorVersion
suffix:semicolon
multiline_comment|/*&t;   &t;&t;  yy. */
DECL|member|BootBuildNumber
id|__u16
id|BootBuildNumber
suffix:semicolon
multiline_comment|/*&t;&t;      &t;  zzzz (LE format) */
DECL|member|FirmwareMajorVersion
id|__u8
id|FirmwareMajorVersion
suffix:semicolon
multiline_comment|/* Operational Firmware version:xx. */
DECL|member|FirmwareMinorVersion
id|__u8
id|FirmwareMinorVersion
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;yy. */
DECL|member|FirmwareBuildNumber
id|__u16
id|FirmwareBuildNumber
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;zzzz (LE format) */
DECL|member|ManufactureDescDate
id|__u8
id|ManufactureDescDate
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* MM/DD/YY when descriptor template was compiled */
DECL|member|Unused1
id|__u8
id|Unused1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Available */
DECL|member|iDownloadFile
id|__u8
id|iDownloadFile
suffix:semicolon
multiline_comment|/* What to download to EPiC device */
DECL|member|Unused2
id|__u8
id|Unused2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Available */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Edgeport Stringblock String locations&n; */
DECL|macro|EDGESTRING_MANUFNAME
mdefine_line|#define EDGESTRING_MANUFNAME&t;&t;1&t;/* Manufacture Name */
DECL|macro|EDGESTRING_PRODNAME
mdefine_line|#define EDGESTRING_PRODNAME&t;&t;2&t;/* Product Name */
DECL|macro|EDGESTRING_SERIALNUM
mdefine_line|#define EDGESTRING_SERIALNUM&t;&t;3&t;/* Serial Number */
DECL|macro|EDGESTRING_ASSEMNUM
mdefine_line|#define EDGESTRING_ASSEMNUM&t;&t;4&t;/* Assembly Number */
DECL|macro|EDGESTRING_OEMASSEMNUM
mdefine_line|#define EDGESTRING_OEMASSEMNUM&t;&t;5&t;/* OEM Assembly Number */
DECL|macro|EDGESTRING_MANUFDATE
mdefine_line|#define EDGESTRING_MANUFDATE&t;&t;6&t;/* Manufacture Date */
DECL|macro|EDGESTRING_ORIGSERIALNUM
mdefine_line|#define EDGESTRING_ORIGSERIALNUM&t;7&t;/* Serial Number */
DECL|struct|string_block
r_struct
id|string_block
(brace
DECL|member|NumStrings
id|__u16
id|NumStrings
suffix:semicolon
multiline_comment|/* Number of strings in block */
DECL|member|Strings
id|__u16
id|Strings
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Start of string block */
)brace
suffix:semicolon
DECL|typedef|STRING_BLOCK
DECL|typedef|PSTRING_BLOCK
r_typedef
r_struct
id|string_block
id|STRING_BLOCK
comma
op_star
id|PSTRING_BLOCK
suffix:semicolon
macro_line|#endif
eof
