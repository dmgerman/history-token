multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SYM_NVRAM_H
DECL|macro|SYM_NVRAM_H
mdefine_line|#define SYM_NVRAM_H
macro_line|#include &quot;sym_conf.h&quot;
multiline_comment|/*&n; *&t;Symbios NVRAM data format&n; */
DECL|macro|SYMBIOS_NVRAM_SIZE
mdefine_line|#define SYMBIOS_NVRAM_SIZE 368
DECL|macro|SYMBIOS_NVRAM_ADDRESS
mdefine_line|#define SYMBIOS_NVRAM_ADDRESS 0x100
DECL|struct|Symbios_nvram
r_struct
id|Symbios_nvram
(brace
multiline_comment|/* Header 6 bytes */
DECL|member|type
id|u_short
id|type
suffix:semicolon
multiline_comment|/* 0x0000 */
DECL|member|byte_count
id|u_short
id|byte_count
suffix:semicolon
multiline_comment|/* excluding header/trailer */
DECL|member|checksum
id|u_short
id|checksum
suffix:semicolon
multiline_comment|/* Controller set up 20 bytes */
DECL|member|v_major
id|u_char
id|v_major
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|v_minor
id|u_char
id|v_minor
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|boot_crc
id|u32
id|boot_crc
suffix:semicolon
DECL|member|flags
id|u_short
id|flags
suffix:semicolon
DECL|macro|SYMBIOS_SCAM_ENABLE
mdefine_line|#define SYMBIOS_SCAM_ENABLE&t;(1)
DECL|macro|SYMBIOS_PARITY_ENABLE
mdefine_line|#define SYMBIOS_PARITY_ENABLE&t;(1&lt;&lt;1)
DECL|macro|SYMBIOS_VERBOSE_MSGS
mdefine_line|#define SYMBIOS_VERBOSE_MSGS&t;(1&lt;&lt;2)
DECL|macro|SYMBIOS_CHS_MAPPING
mdefine_line|#define SYMBIOS_CHS_MAPPING&t;(1&lt;&lt;3)
DECL|macro|SYMBIOS_NO_NVRAM
mdefine_line|#define SYMBIOS_NO_NVRAM&t;(1&lt;&lt;3)&t;/* ??? */
DECL|member|flags1
id|u_short
id|flags1
suffix:semicolon
DECL|macro|SYMBIOS_SCAN_HI_LO
mdefine_line|#define SYMBIOS_SCAN_HI_LO&t;(1)
DECL|member|term_state
id|u_short
id|term_state
suffix:semicolon
DECL|macro|SYMBIOS_TERM_CANT_PROGRAM
mdefine_line|#define SYMBIOS_TERM_CANT_PROGRAM&t;(0)
DECL|macro|SYMBIOS_TERM_ENABLED
mdefine_line|#define SYMBIOS_TERM_ENABLED&t;&t;(1)
DECL|macro|SYMBIOS_TERM_DISABLED
mdefine_line|#define SYMBIOS_TERM_DISABLED&t;&t;(2)
DECL|member|rmvbl_flags
id|u_short
id|rmvbl_flags
suffix:semicolon
DECL|macro|SYMBIOS_RMVBL_NO_SUPPORT
mdefine_line|#define SYMBIOS_RMVBL_NO_SUPPORT&t;(0)
DECL|macro|SYMBIOS_RMVBL_BOOT_DEVICE
mdefine_line|#define SYMBIOS_RMVBL_BOOT_DEVICE&t;(1)
DECL|macro|SYMBIOS_RMVBL_MEDIA_INSTALLED
mdefine_line|#define SYMBIOS_RMVBL_MEDIA_INSTALLED&t;(2)
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|num_hba
id|u_char
id|num_hba
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|num_devices
id|u_char
id|num_devices
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|max_scam_devices
id|u_char
id|max_scam_devices
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|num_valid_scam_devices
id|u_char
id|num_valid_scam_devices
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|flags2
id|u_char
id|flags2
suffix:semicolon
DECL|macro|SYMBIOS_AVOID_BUS_RESET
mdefine_line|#define SYMBIOS_AVOID_BUS_RESET&t;&t;(1&lt;&lt;2)
multiline_comment|/* Boot order 14 bytes * 4 */
DECL|struct|Symbios_host
r_struct
id|Symbios_host
(brace
DECL|member|type
id|u_short
id|type
suffix:semicolon
multiline_comment|/* 4:8xx / 0:nok */
DECL|member|device_id
id|u_short
id|device_id
suffix:semicolon
multiline_comment|/* PCI device id */
DECL|member|vendor_id
id|u_short
id|vendor_id
suffix:semicolon
multiline_comment|/* PCI vendor id */
DECL|member|bus_nr
id|u_char
id|bus_nr
suffix:semicolon
multiline_comment|/* PCI bus number */
DECL|member|device_fn
id|u_char
id|device_fn
suffix:semicolon
multiline_comment|/* PCI device/function number &lt;&lt; 3*/
DECL|member|word8
id|u_short
id|word8
suffix:semicolon
DECL|member|flags
id|u_short
id|flags
suffix:semicolon
DECL|macro|SYMBIOS_INIT_SCAN_AT_BOOT
mdefine_line|#define&t;SYMBIOS_INIT_SCAN_AT_BOOT&t;(1)
DECL|member|io_port
id|u_short
id|io_port
suffix:semicolon
multiline_comment|/* PCI io_port address */
DECL|member|host
)brace
id|host
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Targets 8 bytes * 16 */
DECL|struct|Symbios_target
r_struct
id|Symbios_target
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|macro|SYMBIOS_DISCONNECT_ENABLE
mdefine_line|#define SYMBIOS_DISCONNECT_ENABLE&t;(1)
DECL|macro|SYMBIOS_SCAN_AT_BOOT_TIME
mdefine_line|#define SYMBIOS_SCAN_AT_BOOT_TIME&t;(1&lt;&lt;1)
DECL|macro|SYMBIOS_SCAN_LUNS
mdefine_line|#define SYMBIOS_SCAN_LUNS&t;&t;(1&lt;&lt;2)
DECL|macro|SYMBIOS_QUEUE_TAGS_ENABLED
mdefine_line|#define SYMBIOS_QUEUE_TAGS_ENABLED&t;(1&lt;&lt;3)
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
DECL|member|bus_width
id|u_char
id|bus_width
suffix:semicolon
multiline_comment|/* 0x08/0x10 */
DECL|member|sync_offset
id|u_char
id|sync_offset
suffix:semicolon
DECL|member|sync_period
id|u_short
id|sync_period
suffix:semicolon
multiline_comment|/* 4*period factor */
DECL|member|timeout
id|u_short
id|timeout
suffix:semicolon
DECL|member|target
)brace
id|target
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Scam table 8 bytes * 4 */
DECL|struct|Symbios_scam
r_struct
id|Symbios_scam
(brace
DECL|member|id
id|u_short
id|id
suffix:semicolon
DECL|member|method
id|u_short
id|method
suffix:semicolon
DECL|macro|SYMBIOS_SCAM_DEFAULT_METHOD
mdefine_line|#define SYMBIOS_SCAM_DEFAULT_METHOD&t;(0)
DECL|macro|SYMBIOS_SCAM_DONT_ASSIGN
mdefine_line|#define SYMBIOS_SCAM_DONT_ASSIGN&t;(1)
DECL|macro|SYMBIOS_SCAM_SET_SPECIFIC_ID
mdefine_line|#define SYMBIOS_SCAM_SET_SPECIFIC_ID&t;(2)
DECL|macro|SYMBIOS_SCAM_USE_ORDER_GIVEN
mdefine_line|#define SYMBIOS_SCAM_USE_ORDER_GIVEN&t;(3)
DECL|member|status
id|u_short
id|status
suffix:semicolon
DECL|macro|SYMBIOS_SCAM_UNKNOWN
mdefine_line|#define SYMBIOS_SCAM_UNKNOWN&t;&t;(0)
DECL|macro|SYMBIOS_SCAM_DEVICE_NOT_FOUND
mdefine_line|#define SYMBIOS_SCAM_DEVICE_NOT_FOUND&t;(1)
DECL|macro|SYMBIOS_SCAM_ID_NOT_SET
mdefine_line|#define SYMBIOS_SCAM_ID_NOT_SET&t;&t;(2)
DECL|macro|SYMBIOS_SCAM_ID_VALID
mdefine_line|#define SYMBIOS_SCAM_ID_VALID&t;&t;(3)
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
DECL|member|scam
)brace
id|scam
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|spare_devices
id|u_char
id|spare_devices
(braket
l_int|15
op_star
l_int|8
)braket
suffix:semicolon
DECL|member|trailer
id|u_char
id|trailer
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0xfe 0xfe 0x00 0x00 0x00 0x00 */
)brace
suffix:semicolon
DECL|typedef|Symbios_nvram
r_typedef
r_struct
id|Symbios_nvram
id|Symbios_nvram
suffix:semicolon
DECL|typedef|Symbios_host
r_typedef
r_struct
id|Symbios_host
id|Symbios_host
suffix:semicolon
DECL|typedef|Symbios_target
r_typedef
r_struct
id|Symbios_target
id|Symbios_target
suffix:semicolon
DECL|typedef|Symbios_scam
r_typedef
r_struct
id|Symbios_scam
id|Symbios_scam
suffix:semicolon
multiline_comment|/*&n; *&t;Tekram NvRAM data format.&n; */
DECL|macro|TEKRAM_NVRAM_SIZE
mdefine_line|#define TEKRAM_NVRAM_SIZE 64
DECL|macro|TEKRAM_93C46_NVRAM_ADDRESS
mdefine_line|#define TEKRAM_93C46_NVRAM_ADDRESS 0
DECL|macro|TEKRAM_24C16_NVRAM_ADDRESS
mdefine_line|#define TEKRAM_24C16_NVRAM_ADDRESS 0x40
DECL|struct|Tekram_nvram
r_struct
id|Tekram_nvram
(brace
DECL|struct|Tekram_target
r_struct
id|Tekram_target
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|macro|TEKRAM_PARITY_CHECK
mdefine_line|#define&t;TEKRAM_PARITY_CHECK&t;&t;(1)
DECL|macro|TEKRAM_SYNC_NEGO
mdefine_line|#define TEKRAM_SYNC_NEGO&t;&t;(1&lt;&lt;1)
DECL|macro|TEKRAM_DISCONNECT_ENABLE
mdefine_line|#define TEKRAM_DISCONNECT_ENABLE&t;(1&lt;&lt;2)
DECL|macro|TEKRAM_START_CMD
mdefine_line|#define&t;TEKRAM_START_CMD&t;&t;(1&lt;&lt;3)
DECL|macro|TEKRAM_TAGGED_COMMANDS
mdefine_line|#define TEKRAM_TAGGED_COMMANDS&t;&t;(1&lt;&lt;4)
DECL|macro|TEKRAM_WIDE_NEGO
mdefine_line|#define TEKRAM_WIDE_NEGO&t;&t;(1&lt;&lt;5)
DECL|member|sync_index
id|u_char
id|sync_index
suffix:semicolon
DECL|member|word2
id|u_short
id|word2
suffix:semicolon
DECL|member|target
)brace
id|target
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|macro|TEKRAM_MORE_THAN_2_DRIVES
mdefine_line|#define TEKRAM_MORE_THAN_2_DRIVES&t;(1)
DECL|macro|TEKRAM_DRIVES_SUP_1GB
mdefine_line|#define TEKRAM_DRIVES_SUP_1GB&t;&t;(1&lt;&lt;1)
DECL|macro|TEKRAM_RESET_ON_POWER_ON
mdefine_line|#define&t;TEKRAM_RESET_ON_POWER_ON&t;(1&lt;&lt;2)
DECL|macro|TEKRAM_ACTIVE_NEGATION
mdefine_line|#define TEKRAM_ACTIVE_NEGATION&t;&t;(1&lt;&lt;3)
DECL|macro|TEKRAM_IMMEDIATE_SEEK
mdefine_line|#define TEKRAM_IMMEDIATE_SEEK&t;&t;(1&lt;&lt;4)
DECL|macro|TEKRAM_SCAN_LUNS
mdefine_line|#define&t;TEKRAM_SCAN_LUNS&t;&t;(1&lt;&lt;5)
DECL|macro|TEKRAM_REMOVABLE_FLAGS
mdefine_line|#define&t;TEKRAM_REMOVABLE_FLAGS&t;&t;(3&lt;&lt;6)&t;/* 0: disable; */
multiline_comment|/* 1: boot device; 2:all */
DECL|member|boot_delay_index
id|u_char
id|boot_delay_index
suffix:semicolon
DECL|member|max_tags_index
id|u_char
id|max_tags_index
suffix:semicolon
DECL|member|flags1
id|u_short
id|flags1
suffix:semicolon
DECL|macro|TEKRAM_F2_F6_ENABLED
mdefine_line|#define TEKRAM_F2_F6_ENABLED&t;&t;(1)
DECL|member|spare
id|u_short
id|spare
(braket
l_int|29
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|Tekram_nvram
r_typedef
r_struct
id|Tekram_nvram
id|Tekram_nvram
suffix:semicolon
DECL|typedef|Tekram_target
r_typedef
r_struct
id|Tekram_target
id|Tekram_target
suffix:semicolon
macro_line|#ifndef CONFIG_PARISC
DECL|struct|pdc_initiator
DECL|member|dummy
r_struct
id|pdc_initiator
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Union of supported NVRAM formats.&n; */
DECL|struct|sym_nvram
r_struct
id|sym_nvram
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|macro|SYM_SYMBIOS_NVRAM
mdefine_line|#define&t;SYM_SYMBIOS_NVRAM&t;(1)
DECL|macro|SYM_TEKRAM_NVRAM
mdefine_line|#define&t;SYM_TEKRAM_NVRAM&t;(2)
DECL|macro|SYM_PARISC_PDC
mdefine_line|#define SYM_PARISC_PDC&t;&t;(3)
macro_line|#if SYM_CONF_NVRAM_SUPPORT
r_union
(brace
DECL|member|Symbios
id|Symbios_nvram
id|Symbios
suffix:semicolon
DECL|member|Tekram
id|Tekram_nvram
id|Tekram
suffix:semicolon
DECL|member|parisc
r_struct
id|pdc_initiator
id|parisc
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#if SYM_CONF_NVRAM_SUPPORT
r_void
id|sym_nvram_setup_host
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvram
)paren
suffix:semicolon
r_void
id|sym_nvram_setup_target
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_int
id|target
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
suffix:semicolon
r_int
id|sym_read_nvram
(paren
r_struct
id|sym_device
op_star
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
suffix:semicolon
macro_line|#else
DECL|function|sym_nvram_setup_host
r_static
r_inline
r_void
id|sym_nvram_setup_host
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvram
)paren
(brace
)brace
DECL|function|sym_nvram_setup_target
r_static
r_inline
r_void
id|sym_nvram_setup_target
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvram
)paren
(brace
)brace
DECL|function|sym_read_nvram
r_static
r_inline
r_int
id|sym_read_nvram
c_func
(paren
r_struct
id|sym_device
op_star
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
(brace
id|nvp-&gt;type
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* SYM_NVRAM_H */
eof
