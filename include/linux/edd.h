multiline_comment|/*&n; * linux/include/linux/edd.h&n; *  Copyright (C) 2002, 2003, 2004 Dell Inc.&n; *  by Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *&n; * structures and definitions for the int 13h, ax={41,48}h&n; * BIOS Enhanced Disk Drive Services&n; * This is based on the T13 group document D1572 Revision 0 (August 14 2002)&n; * available at http://www.t13.org/docs2002/d1572r0.pdf.  It is&n; * very similar to D1484 Revision 3 http://www.t13.org/docs2002/d1484r3.pdf&n; *&n; * In a nutshell, arch/{i386,x86_64}/boot/setup.S populates a scratch&n; * table in the boot_params that contains a list of BIOS-enumerated&n; * boot devices.&n; * In arch/{i386,x86_64}/kernel/setup.c, this information is&n; * transferred into the edd structure, and in drivers/firmware/edd.c, that&n; * information is used to identify BIOS boot disk.  The code in setup.S&n; * is very sensitive to the size of these structures.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License v2.0 as published by&n; * the Free Software Foundation&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; */
macro_line|#ifndef _LINUX_EDD_H
DECL|macro|_LINUX_EDD_H
mdefine_line|#define _LINUX_EDD_H
DECL|macro|EDDNR
mdefine_line|#define EDDNR 0x1e9&t;&t;/* addr of number of edd_info structs at EDDBUF&n;&t;&t;&t;&t;   in boot_params - treat this as 1 byte  */
DECL|macro|EDDBUF
mdefine_line|#define EDDBUF&t;0x600&t;&t;/* addr of edd_info structs in boot_params */
DECL|macro|EDDMAXNR
mdefine_line|#define EDDMAXNR 6&t;&t;/* number of edd_info structs starting at EDDBUF  */
DECL|macro|EDDEXTSIZE
mdefine_line|#define EDDEXTSIZE 8&t;&t;/* change these if you muck with the structures */
DECL|macro|EDDPARMSIZE
mdefine_line|#define EDDPARMSIZE 74
DECL|macro|CHECKEXTENSIONSPRESENT
mdefine_line|#define CHECKEXTENSIONSPRESENT 0x41
DECL|macro|EXTENDEDREAD
mdefine_line|#define EXTENDEDREAD 0x42
DECL|macro|GETDEVICEPARAMETERS
mdefine_line|#define GETDEVICEPARAMETERS 0x48
DECL|macro|LEGACYGETDEVICEPARAMETERS
mdefine_line|#define LEGACYGETDEVICEPARAMETERS 0x08
DECL|macro|EDDMAGIC1
mdefine_line|#define EDDMAGIC1 0x55AA
DECL|macro|EDDMAGIC2
mdefine_line|#define EDDMAGIC2 0xAA55
DECL|macro|FIXEDDISKSUBSET
mdefine_line|#define FIXEDDISKSUBSET 0x0001
DECL|macro|GET_DEVICE_PARAMETERS_SUPPORTED
mdefine_line|#define GET_DEVICE_PARAMETERS_SUPPORTED 0x0007
DECL|macro|READ_SECTORS
mdefine_line|#define READ_SECTORS 0x02         /* int13 AH=0x02 is READ_SECTORS command */
DECL|macro|EDD_MBR_SIG_OFFSET
mdefine_line|#define EDD_MBR_SIG_OFFSET 0x1B8  /* offset of signature in the MBR */
DECL|macro|EDD_DEV_ADDR_PACKET_LEN
mdefine_line|#define EDD_DEV_ADDR_PACKET_LEN 0x10  /* for int13 fn42 */
DECL|macro|EDD_MBR_SIG_BUF
mdefine_line|#define EDD_MBR_SIG_BUF    0x290  /* addr in boot params */
DECL|macro|EDD_MBR_SIG_MAX
mdefine_line|#define EDD_MBR_SIG_MAX 16        /* max number of signatures to store */
DECL|macro|EDD_MBR_SIG_NR_BUF
mdefine_line|#define EDD_MBR_SIG_NR_BUF 0x1ea  /* addr of number of MBR signtaures at EDD_MBR_SIG_BUF&n;&t;&t;&t;&t;     in boot_params - treat this as 1 byte  */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|EDD_EXT_FIXED_DISK_ACCESS
mdefine_line|#define EDD_EXT_FIXED_DISK_ACCESS           (1 &lt;&lt; 0)
DECL|macro|EDD_EXT_DEVICE_LOCKING_AND_EJECTING
mdefine_line|#define EDD_EXT_DEVICE_LOCKING_AND_EJECTING (1 &lt;&lt; 1)
DECL|macro|EDD_EXT_ENHANCED_DISK_DRIVE_SUPPORT
mdefine_line|#define EDD_EXT_ENHANCED_DISK_DRIVE_SUPPORT (1 &lt;&lt; 2)
DECL|macro|EDD_EXT_64BIT_EXTENSIONS
mdefine_line|#define EDD_EXT_64BIT_EXTENSIONS            (1 &lt;&lt; 3)
DECL|macro|EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT
mdefine_line|#define EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT (1 &lt;&lt; 0)
DECL|macro|EDD_INFO_GEOMETRY_VALID
mdefine_line|#define EDD_INFO_GEOMETRY_VALID                (1 &lt;&lt; 1)
DECL|macro|EDD_INFO_REMOVABLE
mdefine_line|#define EDD_INFO_REMOVABLE                     (1 &lt;&lt; 2)
DECL|macro|EDD_INFO_WRITE_VERIFY
mdefine_line|#define EDD_INFO_WRITE_VERIFY                  (1 &lt;&lt; 3)
DECL|macro|EDD_INFO_MEDIA_CHANGE_NOTIFICATION
mdefine_line|#define EDD_INFO_MEDIA_CHANGE_NOTIFICATION     (1 &lt;&lt; 4)
DECL|macro|EDD_INFO_LOCKABLE
mdefine_line|#define EDD_INFO_LOCKABLE                      (1 &lt;&lt; 5)
DECL|macro|EDD_INFO_NO_MEDIA_PRESENT
mdefine_line|#define EDD_INFO_NO_MEDIA_PRESENT              (1 &lt;&lt; 6)
DECL|macro|EDD_INFO_USE_INT13_FN50
mdefine_line|#define EDD_INFO_USE_INT13_FN50                (1 &lt;&lt; 7)
DECL|struct|edd_device_params
r_struct
id|edd_device_params
(brace
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|info_flags
id|u16
id|info_flags
suffix:semicolon
DECL|member|num_default_cylinders
id|u32
id|num_default_cylinders
suffix:semicolon
DECL|member|num_default_heads
id|u32
id|num_default_heads
suffix:semicolon
DECL|member|sectors_per_track
id|u32
id|sectors_per_track
suffix:semicolon
DECL|member|number_of_sectors
id|u64
id|number_of_sectors
suffix:semicolon
DECL|member|bytes_per_sector
id|u16
id|bytes_per_sector
suffix:semicolon
DECL|member|dpte_ptr
id|u32
id|dpte_ptr
suffix:semicolon
multiline_comment|/* 0xFFFFFFFF for our purposes */
DECL|member|key
id|u16
id|key
suffix:semicolon
multiline_comment|/* = 0xBEDD */
DECL|member|device_path_info_length
id|u8
id|device_path_info_length
suffix:semicolon
multiline_comment|/* = 44 */
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u16
id|reserved3
suffix:semicolon
DECL|member|host_bus_type
id|u8
id|host_bus_type
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|interface_type
id|u8
id|interface_type
(braket
l_int|8
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|base_address
id|u16
id|base_address
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|isa
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|isa
suffix:semicolon
r_struct
(brace
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|slot
id|u8
id|slot
suffix:semicolon
DECL|member|function
id|u8
id|function
suffix:semicolon
DECL|member|channel
id|u8
id|channel
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|pci
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|pci
suffix:semicolon
multiline_comment|/* pcix is same as pci */
r_struct
(brace
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|ibnd
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ibnd
suffix:semicolon
r_struct
(brace
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|xprs
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|xprs
suffix:semicolon
r_struct
(brace
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|htpt
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|htpt
suffix:semicolon
r_struct
(brace
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|unknown
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|unknown
suffix:semicolon
DECL|member|interface_path
)brace
id|interface_path
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u64
id|reserved4
suffix:semicolon
DECL|member|ata
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ata
suffix:semicolon
r_struct
(brace
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|lun
id|u8
id|lun
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u64
id|reserved4
suffix:semicolon
DECL|member|atapi
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|atapi
suffix:semicolon
r_struct
(brace
DECL|member|id
id|u16
id|id
suffix:semicolon
DECL|member|lun
id|u64
id|lun
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|scsi
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|scsi
suffix:semicolon
r_struct
(brace
DECL|member|serial_number
id|u64
id|serial_number
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|usb
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|usb
suffix:semicolon
r_struct
(brace
DECL|member|eui
id|u64
id|eui
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|i1394
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|i1394
suffix:semicolon
r_struct
(brace
DECL|member|wwid
id|u64
id|wwid
suffix:semicolon
DECL|member|lun
id|u64
id|lun
suffix:semicolon
DECL|member|fibre
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|fibre
suffix:semicolon
r_struct
(brace
DECL|member|identity_tag
id|u64
id|identity_tag
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|i2o
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|i2o
suffix:semicolon
r_struct
(brace
DECL|member|array_number
id|u32
id|array_number
suffix:semicolon
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u64
id|reserved2
suffix:semicolon
DECL|member|raid
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|raid
suffix:semicolon
r_struct
(brace
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u64
id|reserved4
suffix:semicolon
DECL|member|sata
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sata
suffix:semicolon
r_struct
(brace
DECL|member|reserved1
id|u64
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u64
id|reserved2
suffix:semicolon
DECL|member|unknown
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|unknown
suffix:semicolon
DECL|member|device_path
)brace
id|device_path
suffix:semicolon
DECL|member|reserved4
id|u8
id|reserved4
suffix:semicolon
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|edd_info
r_struct
id|edd_info
(brace
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|version
id|u8
id|version
suffix:semicolon
DECL|member|interface_support
id|u16
id|interface_support
suffix:semicolon
DECL|member|legacy_max_cylinder
id|u16
id|legacy_max_cylinder
suffix:semicolon
DECL|member|legacy_max_head
id|u8
id|legacy_max_head
suffix:semicolon
DECL|member|legacy_sectors_per_track
id|u8
id|legacy_sectors_per_track
suffix:semicolon
DECL|member|params
r_struct
id|edd_device_params
id|params
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|edd
r_struct
id|edd
(brace
DECL|member|mbr_signature
r_int
r_int
id|mbr_signature
(braket
id|EDD_MBR_SIG_MAX
)braket
suffix:semicolon
DECL|member|edd_info
r_struct
id|edd_info
id|edd_info
(braket
id|EDDMAXNR
)braket
suffix:semicolon
DECL|member|mbr_signature_nr
r_int
r_char
id|mbr_signature_nr
suffix:semicolon
DECL|member|edd_info_nr
r_int
r_char
id|edd_info_nr
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|edd
id|edd
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/*!__ASSEMBLY__ */
macro_line|#endif&t;&t;&t;&t;/* _LINUX_EDD_H */
eof
