multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM_DEFS_H
DECL|macro|SYM_DEFS_H
mdefine_line|#define SYM_DEFS_H
multiline_comment|/*&n; *  Vendor.&n; */
DECL|macro|PCI_VENDOR_NCR
mdefine_line|#define PCI_VENDOR_NCR&t;&t;0x1000
multiline_comment|/*&n; *  PCI device identifier of SYMBIOS chips.&n; */
DECL|macro|PCI_ID_SYM53C810
mdefine_line|#define PCI_ID_SYM53C810&t;1
DECL|macro|PCI_ID_SYM53C810AP
mdefine_line|#define PCI_ID_SYM53C810AP&t;5
DECL|macro|PCI_ID_SYM53C815
mdefine_line|#define PCI_ID_SYM53C815&t;4
DECL|macro|PCI_ID_SYM53C820
mdefine_line|#define PCI_ID_SYM53C820&t;2
DECL|macro|PCI_ID_SYM53C825
mdefine_line|#define PCI_ID_SYM53C825&t;3
DECL|macro|PCI_ID_SYM53C860
mdefine_line|#define PCI_ID_SYM53C860&t;6
DECL|macro|PCI_ID_SYM53C875
mdefine_line|#define PCI_ID_SYM53C875&t;0xf
DECL|macro|PCI_ID_SYM53C875_2
mdefine_line|#define PCI_ID_SYM53C875_2&t;0x8f
DECL|macro|PCI_ID_SYM53C885
mdefine_line|#define PCI_ID_SYM53C885&t;0xd
DECL|macro|PCI_ID_SYM53C895
mdefine_line|#define PCI_ID_SYM53C895&t;0xc
DECL|macro|PCI_ID_SYM53C896
mdefine_line|#define PCI_ID_SYM53C896&t;0xb
DECL|macro|PCI_ID_SYM53C895A
mdefine_line|#define PCI_ID_SYM53C895A&t;0x12
DECL|macro|PCI_ID_SYM53C875A
mdefine_line|#define PCI_ID_SYM53C875A&t;0x13
DECL|macro|PCI_ID_LSI53C1010
mdefine_line|#define PCI_ID_LSI53C1010&t;0x20
DECL|macro|PCI_ID_LSI53C1010_2
mdefine_line|#define PCI_ID_LSI53C1010_2&t;0x21
DECL|macro|PCI_ID_LSI53C1510D
mdefine_line|#define PCI_ID_LSI53C1510D&t;0xa
multiline_comment|/*&n; *&t;SYM53C8XX device features descriptor.&n; */
DECL|struct|sym_pci_chip
r_struct
id|sym_pci_chip
(brace
DECL|member|device_id
id|u_short
id|device_id
suffix:semicolon
DECL|member|revision_id
id|u_short
id|revision_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|burst_max
id|u_char
id|burst_max
suffix:semicolon
multiline_comment|/* log-base-2 of max burst */
DECL|member|offset_max
id|u_char
id|offset_max
suffix:semicolon
DECL|member|nr_divisor
id|u_char
id|nr_divisor
suffix:semicolon
DECL|member|lp_probe_bit
id|u_char
id|lp_probe_bit
suffix:semicolon
DECL|member|features
id|u_int
id|features
suffix:semicolon
DECL|macro|FE_LED0
mdefine_line|#define FE_LED0&t;&t;(1&lt;&lt;0)
DECL|macro|FE_WIDE
mdefine_line|#define FE_WIDE&t;&t;(1&lt;&lt;1)    /* Wide data transfers */
DECL|macro|FE_ULTRA
mdefine_line|#define FE_ULTRA&t;(1&lt;&lt;2)&t;  /* Ultra speed 20Mtrans/sec */
DECL|macro|FE_ULTRA2
mdefine_line|#define FE_ULTRA2&t;(1&lt;&lt;3)&t;  /* Ultra 2 - 40 Mtrans/sec */
DECL|macro|FE_DBLR
mdefine_line|#define FE_DBLR&t;&t;(1&lt;&lt;4)&t;  /* Clock doubler present */
DECL|macro|FE_QUAD
mdefine_line|#define FE_QUAD&t;&t;(1&lt;&lt;5)&t;  /* Clock quadrupler present */
DECL|macro|FE_ERL
mdefine_line|#define FE_ERL&t;&t;(1&lt;&lt;6)    /* Enable read line */
DECL|macro|FE_CLSE
mdefine_line|#define FE_CLSE&t;&t;(1&lt;&lt;7)    /* Cache line size enable */
DECL|macro|FE_WRIE
mdefine_line|#define FE_WRIE&t;&t;(1&lt;&lt;8)    /* Write &amp; Invalidate enable */
DECL|macro|FE_ERMP
mdefine_line|#define FE_ERMP&t;&t;(1&lt;&lt;9)    /* Enable read multiple */
DECL|macro|FE_BOF
mdefine_line|#define FE_BOF&t;&t;(1&lt;&lt;10)   /* Burst opcode fetch */
DECL|macro|FE_DFS
mdefine_line|#define FE_DFS&t;&t;(1&lt;&lt;11)   /* DMA fifo size */
DECL|macro|FE_PFEN
mdefine_line|#define FE_PFEN&t;&t;(1&lt;&lt;12)   /* Prefetch enable */
DECL|macro|FE_LDSTR
mdefine_line|#define FE_LDSTR&t;(1&lt;&lt;13)   /* Load/Store supported */
DECL|macro|FE_RAM
mdefine_line|#define FE_RAM&t;&t;(1&lt;&lt;14)   /* On chip RAM present */
DECL|macro|FE_VARCLK
mdefine_line|#define FE_VARCLK&t;(1&lt;&lt;15)   /* Clock frequency may vary */
DECL|macro|FE_RAM8K
mdefine_line|#define FE_RAM8K&t;(1&lt;&lt;16)   /* On chip RAM sized 8Kb */
DECL|macro|FE_64BIT
mdefine_line|#define FE_64BIT&t;(1&lt;&lt;17)   /* 64-bit PCI BUS interface */
DECL|macro|FE_IO256
mdefine_line|#define FE_IO256&t;(1&lt;&lt;18)   /* Requires full 256 bytes in PCI space */
DECL|macro|FE_NOPM
mdefine_line|#define FE_NOPM&t;&t;(1&lt;&lt;19)   /* Scripts handles phase mismatch */
DECL|macro|FE_LEDC
mdefine_line|#define FE_LEDC&t;&t;(1&lt;&lt;20)   /* Hardware control of LED */
DECL|macro|FE_ULTRA3
mdefine_line|#define FE_ULTRA3&t;(1&lt;&lt;21)&t;  /* Ultra 3 - 80 Mtrans/sec DT */
DECL|macro|FE_66MHZ
mdefine_line|#define FE_66MHZ&t;(1&lt;&lt;22)&t;  /* 66MHz PCI support */
DECL|macro|FE_CRC
mdefine_line|#define FE_CRC&t;&t;(1&lt;&lt;23)&t;  /* CRC support */
DECL|macro|FE_DIFF
mdefine_line|#define FE_DIFF&t;&t;(1&lt;&lt;24)&t;  /* SCSI HVD support */
DECL|macro|FE_DFBC
mdefine_line|#define FE_DFBC&t;&t;(1&lt;&lt;25)&t;  /* Have DFBC register */
DECL|macro|FE_LCKFRQ
mdefine_line|#define FE_LCKFRQ&t;(1&lt;&lt;26)&t;  /* Have LCKFRQ */
DECL|macro|FE_C10
mdefine_line|#define FE_C10&t;&t;(1&lt;&lt;27)&t;  /* Various C10 core (mis)features */
DECL|macro|FE_U3EN
mdefine_line|#define FE_U3EN&t;&t;(1&lt;&lt;28)&t;  /* U3EN bit usable */
DECL|macro|FE_DAC
mdefine_line|#define FE_DAC&t;&t;(1&lt;&lt;29)&t;  /* Support PCI DAC (64 bit addressing) */
DECL|macro|FE_ISTAT1
mdefine_line|#define FE_ISTAT1 &t;(1&lt;&lt;30)   /* Have ISTAT1, MBOX0, MBOX1 registers */
DECL|macro|FE_CACHE_SET
mdefine_line|#define FE_CACHE_SET&t;(FE_ERL|FE_CLSE|FE_WRIE|FE_ERMP)
DECL|macro|FE_CACHE0_SET
mdefine_line|#define FE_CACHE0_SET&t;(FE_CACHE_SET &amp; ~FE_ERL)
)brace
suffix:semicolon
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
multiline_comment|/*&n; *&t;SYM53C8XX IO register data structure.&n; */
DECL|struct|sym_reg
r_struct
id|sym_reg
(brace
DECL|member|nc_scntl0
multiline_comment|/*00*/
id|u8
id|nc_scntl0
suffix:semicolon
multiline_comment|/* full arb., ena parity, par-&gt;ATN  */
DECL|member|nc_scntl1
multiline_comment|/*01*/
id|u8
id|nc_scntl1
suffix:semicolon
multiline_comment|/* no reset                         */
DECL|macro|ISCON
mdefine_line|#define   ISCON   0x10  /* connected to scsi&t;&t;    */
DECL|macro|CRST
mdefine_line|#define   CRST    0x08  /* force reset                      */
DECL|macro|IARB
mdefine_line|#define   IARB    0x02  /* immediate arbitration            */
DECL|member|nc_scntl2
multiline_comment|/*02*/
id|u8
id|nc_scntl2
suffix:semicolon
multiline_comment|/* no disconnect expected           */
DECL|macro|SDU
mdefine_line|#define   SDU     0x80  /* cmd: disconnect will raise error */
DECL|macro|CHM
mdefine_line|#define   CHM     0x40  /* sta: chained mode                */
DECL|macro|WSS
mdefine_line|#define   WSS     0x08  /* sta: wide scsi send           [W]*/
DECL|macro|WSR
mdefine_line|#define   WSR     0x01  /* sta: wide scsi received       [W]*/
DECL|member|nc_scntl3
multiline_comment|/*03*/
id|u8
id|nc_scntl3
suffix:semicolon
multiline_comment|/* cnf system clock dependent       */
DECL|macro|EWS
mdefine_line|#define   EWS     0x08  /* cmd: enable wide scsi         [W]*/
DECL|macro|ULTRA
mdefine_line|#define   ULTRA   0x80  /* cmd: ULTRA enable                */
multiline_comment|/* bits 0-2, 7 rsvd for C1010       */
DECL|member|nc_scid
multiline_comment|/*04*/
id|u8
id|nc_scid
suffix:semicolon
multiline_comment|/* cnf host adapter scsi address    */
DECL|macro|RRE
mdefine_line|#define   RRE     0x40  /* r/w:e enable response to resel.  */
DECL|macro|SRE
mdefine_line|#define   SRE     0x20  /* r/w:e enable response to select  */
DECL|member|nc_sxfer
multiline_comment|/*05*/
id|u8
id|nc_sxfer
suffix:semicolon
multiline_comment|/* ### Sync speed and count         */
multiline_comment|/* bits 6-7 rsvd for C1010          */
DECL|member|nc_sdid
multiline_comment|/*06*/
id|u8
id|nc_sdid
suffix:semicolon
multiline_comment|/* ### Destination-ID               */
DECL|member|nc_gpreg
multiline_comment|/*07*/
id|u8
id|nc_gpreg
suffix:semicolon
multiline_comment|/* ??? IO-Pins                      */
DECL|member|nc_sfbr
multiline_comment|/*08*/
id|u8
id|nc_sfbr
suffix:semicolon
multiline_comment|/* ### First byte received          */
DECL|member|nc_socl
multiline_comment|/*09*/
id|u8
id|nc_socl
suffix:semicolon
DECL|macro|CREQ
mdefine_line|#define   CREQ&t;  0x80&t;/* r/w: SCSI-REQ                    */
DECL|macro|CACK
mdefine_line|#define   CACK&t;  0x40&t;/* r/w: SCSI-ACK                    */
DECL|macro|CBSY
mdefine_line|#define   CBSY&t;  0x20&t;/* r/w: SCSI-BSY                    */
DECL|macro|CSEL
mdefine_line|#define   CSEL&t;  0x10&t;/* r/w: SCSI-SEL                    */
DECL|macro|CATN
mdefine_line|#define   CATN&t;  0x08&t;/* r/w: SCSI-ATN                    */
DECL|macro|CMSG
mdefine_line|#define   CMSG&t;  0x04&t;/* r/w: SCSI-MSG                    */
DECL|macro|CC_D
mdefine_line|#define   CC_D&t;  0x02&t;/* r/w: SCSI-C_D                    */
DECL|macro|CI_O
mdefine_line|#define   CI_O&t;  0x01&t;/* r/w: SCSI-I_O                    */
DECL|member|nc_ssid
multiline_comment|/*0a*/
id|u8
id|nc_ssid
suffix:semicolon
DECL|member|nc_sbcl
multiline_comment|/*0b*/
id|u8
id|nc_sbcl
suffix:semicolon
DECL|member|nc_dstat
multiline_comment|/*0c*/
id|u8
id|nc_dstat
suffix:semicolon
DECL|macro|DFE
mdefine_line|#define   DFE     0x80  /* sta: dma fifo empty              */
DECL|macro|MDPE
mdefine_line|#define   MDPE    0x40  /* int: master data parity error    */
DECL|macro|BF
mdefine_line|#define   BF      0x20  /* int: script: bus fault           */
DECL|macro|ABRT
mdefine_line|#define   ABRT    0x10  /* int: script: command aborted     */
DECL|macro|SSI
mdefine_line|#define   SSI     0x08  /* int: script: single step         */
DECL|macro|SIR
mdefine_line|#define   SIR     0x04  /* int: script: interrupt instruct. */
DECL|macro|IID
mdefine_line|#define   IID     0x01  /* int: script: illegal instruct.   */
DECL|member|nc_sstat0
multiline_comment|/*0d*/
id|u8
id|nc_sstat0
suffix:semicolon
DECL|macro|ILF
mdefine_line|#define   ILF     0x80  /* sta: data in SIDL register lsb   */
DECL|macro|ORF
mdefine_line|#define   ORF     0x40  /* sta: data in SODR register lsb   */
DECL|macro|OLF
mdefine_line|#define   OLF     0x20  /* sta: data in SODL register lsb   */
DECL|macro|AIP
mdefine_line|#define   AIP     0x10  /* sta: arbitration in progress     */
DECL|macro|LOA
mdefine_line|#define   LOA     0x08  /* sta: arbitration lost            */
DECL|macro|WOA
mdefine_line|#define   WOA     0x04  /* sta: arbitration won             */
DECL|macro|IRST
mdefine_line|#define   IRST    0x02  /* sta: scsi reset signal           */
DECL|macro|SDP
mdefine_line|#define   SDP     0x01  /* sta: scsi parity signal          */
DECL|member|nc_sstat1
multiline_comment|/*0e*/
id|u8
id|nc_sstat1
suffix:semicolon
DECL|macro|FF3210
mdefine_line|#define   FF3210  0xf0&t;/* sta: bytes in the scsi fifo      */
DECL|member|nc_sstat2
multiline_comment|/*0f*/
id|u8
id|nc_sstat2
suffix:semicolon
DECL|macro|ILF1
mdefine_line|#define   ILF1    0x80  /* sta: data in SIDL register msb[W]*/
DECL|macro|ORF1
mdefine_line|#define   ORF1    0x40  /* sta: data in SODR register msb[W]*/
DECL|macro|OLF1
mdefine_line|#define   OLF1    0x20  /* sta: data in SODL register msb[W]*/
DECL|macro|DM
mdefine_line|#define   DM      0x04  /* sta: DIFFSENS mismatch (895/6 only) */
DECL|macro|LDSC
mdefine_line|#define   LDSC    0x02  /* sta: disconnect &amp; reconnect      */
DECL|member|nc_dsa
multiline_comment|/*10*/
id|u8
id|nc_dsa
suffix:semicolon
multiline_comment|/* --&gt; Base page                    */
DECL|member|nc_dsa1
multiline_comment|/*11*/
id|u8
id|nc_dsa1
suffix:semicolon
DECL|member|nc_dsa2
multiline_comment|/*12*/
id|u8
id|nc_dsa2
suffix:semicolon
DECL|member|nc_dsa3
multiline_comment|/*13*/
id|u8
id|nc_dsa3
suffix:semicolon
DECL|member|nc_istat
multiline_comment|/*14*/
id|u8
id|nc_istat
suffix:semicolon
multiline_comment|/* --&gt; Main Command and status      */
DECL|macro|CABRT
mdefine_line|#define   CABRT   0x80  /* cmd: abort current operation     */
DECL|macro|SRST
mdefine_line|#define   SRST    0x40  /* mod: reset chip                  */
DECL|macro|SIGP
mdefine_line|#define   SIGP    0x20  /* r/w: message from host to script */
DECL|macro|SEM
mdefine_line|#define   SEM     0x10  /* r/w: message between host + script  */
DECL|macro|CON
mdefine_line|#define   CON     0x08  /* sta: connected to scsi           */
DECL|macro|INTF
mdefine_line|#define   INTF    0x04  /* sta: int on the fly (reset by wr)*/
DECL|macro|SIP
mdefine_line|#define   SIP     0x02  /* sta: scsi-interrupt              */
DECL|macro|DIP
mdefine_line|#define   DIP     0x01  /* sta: host/script interrupt       */
DECL|member|nc_istat1
multiline_comment|/*15*/
id|u8
id|nc_istat1
suffix:semicolon
multiline_comment|/* 896 only */
DECL|macro|FLSH
mdefine_line|#define   FLSH    0x04  /* sta: chip is flushing            */
DECL|macro|SCRUN
mdefine_line|#define   SCRUN   0x02  /* sta: scripts are running         */
DECL|macro|SIRQD
mdefine_line|#define   SIRQD   0x01  /* r/w: disable INT pin             */
DECL|member|nc_mbox0
multiline_comment|/*16*/
id|u8
id|nc_mbox0
suffix:semicolon
multiline_comment|/* 896 only */
DECL|member|nc_mbox1
multiline_comment|/*17*/
id|u8
id|nc_mbox1
suffix:semicolon
multiline_comment|/* 896 only */
DECL|member|nc_ctest0
multiline_comment|/*18*/
id|u8
id|nc_ctest0
suffix:semicolon
DECL|member|nc_ctest1
multiline_comment|/*19*/
id|u8
id|nc_ctest1
suffix:semicolon
DECL|member|nc_ctest2
multiline_comment|/*1a*/
id|u8
id|nc_ctest2
suffix:semicolon
DECL|macro|CSIGP
mdefine_line|#define   CSIGP   0x40
multiline_comment|/* bits 0-2,7 rsvd for C1010        */
DECL|member|nc_ctest3
multiline_comment|/*1b*/
id|u8
id|nc_ctest3
suffix:semicolon
DECL|macro|FLF
mdefine_line|#define   FLF     0x08  /* cmd: flush dma fifo              */
DECL|macro|CLF
mdefine_line|#define   CLF&t;  0x04&t;/* cmd: clear dma fifo&t;&t;    */
DECL|macro|FM
mdefine_line|#define   FM      0x02  /* mod: fetch pin mode              */
DECL|macro|WRIE
mdefine_line|#define   WRIE    0x01  /* mod: write and invalidate enable */
multiline_comment|/* bits 4-7 rsvd for C1010          */
DECL|member|nc_temp
multiline_comment|/*1c*/
id|u32
id|nc_temp
suffix:semicolon
multiline_comment|/* ### Temporary stack              */
DECL|member|nc_dfifo
multiline_comment|/*20*/
id|u8
id|nc_dfifo
suffix:semicolon
DECL|member|nc_ctest4
multiline_comment|/*21*/
id|u8
id|nc_ctest4
suffix:semicolon
DECL|macro|BDIS
mdefine_line|#define   BDIS    0x80  /* mod: burst disable               */
DECL|macro|MPEE
mdefine_line|#define   MPEE    0x08  /* mod: master parity error enable  */
DECL|member|nc_ctest5
multiline_comment|/*22*/
id|u8
id|nc_ctest5
suffix:semicolon
DECL|macro|DFS
mdefine_line|#define   DFS     0x20  /* mod: dma fifo size               */
multiline_comment|/* bits 0-1, 3-7 rsvd for C1010     */
DECL|member|nc_ctest6
multiline_comment|/*23*/
id|u8
id|nc_ctest6
suffix:semicolon
DECL|member|nc_dbc
multiline_comment|/*24*/
id|u32
id|nc_dbc
suffix:semicolon
multiline_comment|/* ### Byte count and command       */
DECL|member|nc_dnad
multiline_comment|/*28*/
id|u32
id|nc_dnad
suffix:semicolon
multiline_comment|/* ### Next command register        */
DECL|member|nc_dsp
multiline_comment|/*2c*/
id|u32
id|nc_dsp
suffix:semicolon
multiline_comment|/* --&gt; Script Pointer               */
DECL|member|nc_dsps
multiline_comment|/*30*/
id|u32
id|nc_dsps
suffix:semicolon
multiline_comment|/* --&gt; Script pointer save/opcode#2 */
DECL|member|nc_scratcha
multiline_comment|/*34*/
id|u8
id|nc_scratcha
suffix:semicolon
multiline_comment|/* Temporary register a            */
DECL|member|nc_scratcha1
multiline_comment|/*35*/
id|u8
id|nc_scratcha1
suffix:semicolon
DECL|member|nc_scratcha2
multiline_comment|/*36*/
id|u8
id|nc_scratcha2
suffix:semicolon
DECL|member|nc_scratcha3
multiline_comment|/*37*/
id|u8
id|nc_scratcha3
suffix:semicolon
DECL|member|nc_dmode
multiline_comment|/*38*/
id|u8
id|nc_dmode
suffix:semicolon
DECL|macro|BL_2
mdefine_line|#define   BL_2    0x80  /* mod: burst length shift value +2 */
DECL|macro|BL_1
mdefine_line|#define   BL_1    0x40  /* mod: burst length shift value +1 */
DECL|macro|ERL
mdefine_line|#define   ERL     0x08  /* mod: enable read line            */
DECL|macro|ERMP
mdefine_line|#define   ERMP    0x04  /* mod: enable read multiple        */
DECL|macro|BOF
mdefine_line|#define   BOF     0x02  /* mod: burst op code fetch         */
DECL|member|nc_dien
multiline_comment|/*39*/
id|u8
id|nc_dien
suffix:semicolon
DECL|member|nc_sbr
multiline_comment|/*3a*/
id|u8
id|nc_sbr
suffix:semicolon
DECL|member|nc_dcntl
multiline_comment|/*3b*/
id|u8
id|nc_dcntl
suffix:semicolon
multiline_comment|/* --&gt; Script execution control     */
DECL|macro|CLSE
mdefine_line|#define   CLSE    0x80  /* mod: cache line size enable      */
DECL|macro|PFF
mdefine_line|#define   PFF     0x40  /* cmd: pre-fetch flush             */
DECL|macro|PFEN
mdefine_line|#define   PFEN    0x20  /* mod: pre-fetch enable            */
DECL|macro|SSM
mdefine_line|#define   SSM     0x10  /* mod: single step mode            */
DECL|macro|IRQM
mdefine_line|#define   IRQM    0x08  /* mod: irq mode (1 = totem pole !) */
DECL|macro|STD
mdefine_line|#define   STD     0x04  /* cmd: start dma mode              */
DECL|macro|IRQD
mdefine_line|#define   IRQD    0x02  /* mod: irq disable                 */
DECL|macro|NOCOM
mdefine_line|#define&t;  NOCOM   0x01&t;/* cmd: protect sfbr while reselect */
multiline_comment|/* bits 0-1 rsvd for C1010          */
DECL|member|nc_adder
multiline_comment|/*3c*/
id|u32
id|nc_adder
suffix:semicolon
DECL|member|nc_sien
multiline_comment|/*40*/
id|u16
id|nc_sien
suffix:semicolon
multiline_comment|/* --&gt;: interrupt enable            */
DECL|member|nc_sist
multiline_comment|/*42*/
id|u16
id|nc_sist
suffix:semicolon
multiline_comment|/* &lt;--: interrupt status            */
DECL|macro|SBMC
mdefine_line|#define   SBMC    0x1000/* sta: SCSI Bus Mode Change (895/6 only) */
DECL|macro|STO
mdefine_line|#define   STO     0x0400/* sta: timeout (select)            */
DECL|macro|GEN
mdefine_line|#define   GEN     0x0200/* sta: timeout (general)           */
DECL|macro|HTH
mdefine_line|#define   HTH     0x0100/* sta: timeout (handshake)         */
DECL|macro|MA
mdefine_line|#define   MA      0x80  /* sta: phase mismatch              */
DECL|macro|CMP
mdefine_line|#define   CMP     0x40  /* sta: arbitration complete        */
DECL|macro|SEL
mdefine_line|#define   SEL     0x20  /* sta: selected by another device  */
DECL|macro|RSL
mdefine_line|#define   RSL     0x10  /* sta: reselected by another device*/
DECL|macro|SGE
mdefine_line|#define   SGE     0x08  /* sta: gross error (over/underflow)*/
DECL|macro|UDC
mdefine_line|#define   UDC     0x04  /* sta: unexpected disconnect       */
DECL|macro|RST
mdefine_line|#define   RST     0x02  /* sta: scsi bus reset detected     */
DECL|macro|PAR
mdefine_line|#define   PAR     0x01  /* sta: scsi parity error           */
DECL|member|nc_slpar
multiline_comment|/*44*/
id|u8
id|nc_slpar
suffix:semicolon
DECL|member|nc_swide
multiline_comment|/*45*/
id|u8
id|nc_swide
suffix:semicolon
DECL|member|nc_macntl
multiline_comment|/*46*/
id|u8
id|nc_macntl
suffix:semicolon
DECL|member|nc_gpcntl
multiline_comment|/*47*/
id|u8
id|nc_gpcntl
suffix:semicolon
DECL|member|nc_stime0
multiline_comment|/*48*/
id|u8
id|nc_stime0
suffix:semicolon
multiline_comment|/* cmd: timeout for select&amp;handshake*/
DECL|member|nc_stime1
multiline_comment|/*49*/
id|u8
id|nc_stime1
suffix:semicolon
multiline_comment|/* cmd: timeout user defined        */
DECL|member|nc_respid
multiline_comment|/*4a*/
id|u16
id|nc_respid
suffix:semicolon
multiline_comment|/* sta: Reselect-IDs                */
DECL|member|nc_stest0
multiline_comment|/*4c*/
id|u8
id|nc_stest0
suffix:semicolon
DECL|member|nc_stest1
multiline_comment|/*4d*/
id|u8
id|nc_stest1
suffix:semicolon
DECL|macro|SCLK
mdefine_line|#define   SCLK    0x80&t;/* Use the PCI clock as SCSI clock&t;*/
DECL|macro|DBLEN
mdefine_line|#define   DBLEN   0x08&t;/* clock doubler running&t;&t;*/
DECL|macro|DBLSEL
mdefine_line|#define   DBLSEL  0x04&t;/* clock doubler selected&t;&t;*/
DECL|member|nc_stest2
multiline_comment|/*4e*/
id|u8
id|nc_stest2
suffix:semicolon
DECL|macro|ROF
mdefine_line|#define   ROF     0x40&t;/* reset scsi offset (after gross error!) */
DECL|macro|EXT
mdefine_line|#define   EXT     0x02  /* extended filtering                     */
DECL|member|nc_stest3
multiline_comment|/*4f*/
id|u8
id|nc_stest3
suffix:semicolon
DECL|macro|TE
mdefine_line|#define   TE     0x80&t;/* c: tolerAnt enable */
DECL|macro|HSC
mdefine_line|#define   HSC    0x20&t;/* c: Halt SCSI Clock */
DECL|macro|CSF
mdefine_line|#define   CSF    0x02&t;/* c: clear scsi fifo */
DECL|member|nc_sidl
multiline_comment|/*50*/
id|u16
id|nc_sidl
suffix:semicolon
multiline_comment|/* Lowlevel: latched from scsi data */
DECL|member|nc_stest4
multiline_comment|/*52*/
id|u8
id|nc_stest4
suffix:semicolon
DECL|macro|SMODE
mdefine_line|#define   SMODE  0xc0&t;/* SCSI bus mode      (895/6 only) */
DECL|macro|SMODE_HVD
mdefine_line|#define    SMODE_HVD 0x40&t;/* High Voltage Differential       */
DECL|macro|SMODE_SE
mdefine_line|#define    SMODE_SE  0x80&t;/* Single Ended                    */
DECL|macro|SMODE_LVD
mdefine_line|#define    SMODE_LVD 0xc0&t;/* Low Voltage Differential        */
DECL|macro|LCKFRQ
mdefine_line|#define   LCKFRQ 0x20&t;/* Frequency Lock (895/6 only)     */
multiline_comment|/* bits 0-5 rsvd for C1010         */
DECL|member|nc_53_
multiline_comment|/*53*/
id|u8
id|nc_53_
suffix:semicolon
DECL|member|nc_sodl
multiline_comment|/*54*/
id|u16
id|nc_sodl
suffix:semicolon
multiline_comment|/* Lowlevel: data out to scsi data  */
DECL|member|nc_ccntl0
multiline_comment|/*56*/
id|u8
id|nc_ccntl0
suffix:semicolon
multiline_comment|/* Chip Control 0 (896)             */
DECL|macro|ENPMJ
mdefine_line|#define   ENPMJ  0x80&t;/* Enable Phase Mismatch Jump       */
DECL|macro|PMJCTL
mdefine_line|#define   PMJCTL 0x40&t;/* Phase Mismatch Jump Control      */
DECL|macro|ENNDJ
mdefine_line|#define   ENNDJ  0x20&t;/* Enable Non Data PM Jump          */
DECL|macro|DISFC
mdefine_line|#define   DISFC  0x10&t;/* Disable Auto FIFO Clear          */
DECL|macro|DILS
mdefine_line|#define   DILS   0x02&t;/* Disable Internal Load/Store      */
DECL|macro|DPR
mdefine_line|#define   DPR    0x01&t;/* Disable Pipe Req                 */
DECL|member|nc_ccntl1
multiline_comment|/*57*/
id|u8
id|nc_ccntl1
suffix:semicolon
multiline_comment|/* Chip Control 1 (896)             */
DECL|macro|ZMOD
mdefine_line|#define   ZMOD   0x80&t;/* High Impedance Mode              */
DECL|macro|DDAC
mdefine_line|#define   DDAC   0x08&t;/* Disable Dual Address Cycle       */
DECL|macro|XTIMOD
mdefine_line|#define   XTIMOD 0x04&t;/* 64-bit Table Ind. Indexing Mode  */
DECL|macro|EXTIBMV
mdefine_line|#define   EXTIBMV 0x02&t;/* Enable 64-bit Table Ind. BMOV    */
DECL|macro|EXDBMV
mdefine_line|#define   EXDBMV 0x01&t;/* Enable 64-bit Direct BMOV        */
DECL|member|nc_sbdl
multiline_comment|/*58*/
id|u16
id|nc_sbdl
suffix:semicolon
multiline_comment|/* Lowlevel: data from scsi data    */
DECL|member|nc_5a_
multiline_comment|/*5a*/
id|u16
id|nc_5a_
suffix:semicolon
DECL|member|nc_scr0
multiline_comment|/*5c*/
id|u8
id|nc_scr0
suffix:semicolon
multiline_comment|/* Working register B               */
DECL|member|nc_scr1
multiline_comment|/*5d*/
id|u8
id|nc_scr1
suffix:semicolon
DECL|member|nc_scr2
multiline_comment|/*5e*/
id|u8
id|nc_scr2
suffix:semicolon
DECL|member|nc_scr3
multiline_comment|/*5f*/
id|u8
id|nc_scr3
suffix:semicolon
DECL|member|nc_scrx
multiline_comment|/*60*/
id|u8
id|nc_scrx
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Working register C-R             */
DECL|member|nc_mmrs
multiline_comment|/*a0*/
id|u32
id|nc_mmrs
suffix:semicolon
multiline_comment|/* Memory Move Read Selector        */
DECL|member|nc_mmws
multiline_comment|/*a4*/
id|u32
id|nc_mmws
suffix:semicolon
multiline_comment|/* Memory Move Write Selector       */
DECL|member|nc_sfs
multiline_comment|/*a8*/
id|u32
id|nc_sfs
suffix:semicolon
multiline_comment|/* Script Fetch Selector            */
DECL|member|nc_drs
multiline_comment|/*ac*/
id|u32
id|nc_drs
suffix:semicolon
multiline_comment|/* DSA Relative Selector            */
DECL|member|nc_sbms
multiline_comment|/*b0*/
id|u32
id|nc_sbms
suffix:semicolon
multiline_comment|/* Static Block Move Selector       */
DECL|member|nc_dbms
multiline_comment|/*b4*/
id|u32
id|nc_dbms
suffix:semicolon
multiline_comment|/* Dynamic Block Move Selector      */
DECL|member|nc_dnad64
multiline_comment|/*b8*/
id|u32
id|nc_dnad64
suffix:semicolon
multiline_comment|/* DMA Next Address 64              */
DECL|member|nc_scntl4
multiline_comment|/*bc*/
id|u16
id|nc_scntl4
suffix:semicolon
multiline_comment|/* C1010 only                       */
DECL|macro|U3EN
mdefine_line|#define   U3EN    0x80&t;/* Enable Ultra 3                   */
DECL|macro|AIPCKEN
mdefine_line|#define   AIPCKEN 0x40  /* AIP checking enable              */
multiline_comment|/* Also enable AIP generation on C10-33*/
DECL|macro|XCLKH_DT
mdefine_line|#define   XCLKH_DT 0x08 /* Extra clock of data hold on DT edge */
DECL|macro|XCLKH_ST
mdefine_line|#define   XCLKH_ST 0x04 /* Extra clock of data hold on ST edge */
DECL|macro|XCLKS_DT
mdefine_line|#define   XCLKS_DT 0x02 /* Extra clock of data set  on DT edge */
DECL|macro|XCLKS_ST
mdefine_line|#define   XCLKS_ST 0x01 /* Extra clock of data set  on ST edge */
DECL|member|nc_aipcntl0
multiline_comment|/*be*/
id|u8
id|nc_aipcntl0
suffix:semicolon
multiline_comment|/* AIP Control 0 C1010 only         */
DECL|member|nc_aipcntl1
multiline_comment|/*bf*/
id|u8
id|nc_aipcntl1
suffix:semicolon
multiline_comment|/* AIP Control 1 C1010 only         */
DECL|macro|DISAIP
mdefine_line|#define DISAIP  0x08&t;/* Disable AIP generation C10-66 only  */
DECL|member|nc_pmjad1
multiline_comment|/*c0*/
id|u32
id|nc_pmjad1
suffix:semicolon
multiline_comment|/* Phase Mismatch Jump Address 1    */
DECL|member|nc_pmjad2
multiline_comment|/*c4*/
id|u32
id|nc_pmjad2
suffix:semicolon
multiline_comment|/* Phase Mismatch Jump Address 2    */
DECL|member|nc_rbc
multiline_comment|/*c8*/
id|u8
id|nc_rbc
suffix:semicolon
multiline_comment|/* Remaining Byte Count             */
DECL|member|nc_rbc1
multiline_comment|/*c9*/
id|u8
id|nc_rbc1
suffix:semicolon
DECL|member|nc_rbc2
multiline_comment|/*ca*/
id|u8
id|nc_rbc2
suffix:semicolon
DECL|member|nc_rbc3
multiline_comment|/*cb*/
id|u8
id|nc_rbc3
suffix:semicolon
DECL|member|nc_ua
multiline_comment|/*cc*/
id|u8
id|nc_ua
suffix:semicolon
multiline_comment|/* Updated Address                  */
DECL|member|nc_ua1
multiline_comment|/*cd*/
id|u8
id|nc_ua1
suffix:semicolon
DECL|member|nc_ua2
multiline_comment|/*ce*/
id|u8
id|nc_ua2
suffix:semicolon
DECL|member|nc_ua3
multiline_comment|/*cf*/
id|u8
id|nc_ua3
suffix:semicolon
DECL|member|nc_esa
multiline_comment|/*d0*/
id|u32
id|nc_esa
suffix:semicolon
multiline_comment|/* Entry Storage Address            */
DECL|member|nc_ia
multiline_comment|/*d4*/
id|u8
id|nc_ia
suffix:semicolon
multiline_comment|/* Instruction Address              */
DECL|member|nc_ia1
multiline_comment|/*d5*/
id|u8
id|nc_ia1
suffix:semicolon
DECL|member|nc_ia2
multiline_comment|/*d6*/
id|u8
id|nc_ia2
suffix:semicolon
DECL|member|nc_ia3
multiline_comment|/*d7*/
id|u8
id|nc_ia3
suffix:semicolon
DECL|member|nc_sbc
multiline_comment|/*d8*/
id|u32
id|nc_sbc
suffix:semicolon
multiline_comment|/* SCSI Byte Count (3 bytes only)   */
DECL|member|nc_csbc
multiline_comment|/*dc*/
id|u32
id|nc_csbc
suffix:semicolon
multiline_comment|/* Cumulative SCSI Byte Count       */
multiline_comment|/* Following for C1010 only         */
DECL|member|nc_crcpad
multiline_comment|/*e0*/
id|u16
id|nc_crcpad
suffix:semicolon
multiline_comment|/* CRC Value                        */
DECL|member|nc_crccntl0
multiline_comment|/*e2*/
id|u8
id|nc_crccntl0
suffix:semicolon
multiline_comment|/* CRC control register             */
DECL|macro|SNDCRC
mdefine_line|#define   SNDCRC  0x10&t;/* Send CRC Request                 */
DECL|member|nc_crccntl1
multiline_comment|/*e3*/
id|u8
id|nc_crccntl1
suffix:semicolon
multiline_comment|/* CRC control register             */
DECL|member|nc_crcdata
multiline_comment|/*e4*/
id|u32
id|nc_crcdata
suffix:semicolon
multiline_comment|/* CRC data register                */
DECL|member|nc_e8_
multiline_comment|/*e8*/
id|u32
id|nc_e8_
suffix:semicolon
DECL|member|nc_ec_
multiline_comment|/*ec*/
id|u32
id|nc_ec_
suffix:semicolon
DECL|member|nc_dfbc
multiline_comment|/*f0*/
id|u16
id|nc_dfbc
suffix:semicolon
multiline_comment|/* DMA FIFO byte count              */
)brace
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Utility macros for the script.&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|REGJ
mdefine_line|#define REGJ(p,r) (offsetof(struct sym_reg, p ## r))
DECL|macro|REG
mdefine_line|#define REG(r) REGJ (nc_, r)
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;SCSI phases&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_DATA_OUT
mdefine_line|#define&t;SCR_DATA_OUT&t;0x00000000
DECL|macro|SCR_DATA_IN
mdefine_line|#define&t;SCR_DATA_IN&t;0x01000000
DECL|macro|SCR_COMMAND
mdefine_line|#define&t;SCR_COMMAND&t;0x02000000
DECL|macro|SCR_STATUS
mdefine_line|#define&t;SCR_STATUS&t;0x03000000
DECL|macro|SCR_DT_DATA_OUT
mdefine_line|#define&t;SCR_DT_DATA_OUT&t;0x04000000
DECL|macro|SCR_DT_DATA_IN
mdefine_line|#define&t;SCR_DT_DATA_IN&t;0x05000000
DECL|macro|SCR_MSG_OUT
mdefine_line|#define SCR_MSG_OUT&t;0x06000000
DECL|macro|SCR_MSG_IN
mdefine_line|#define SCR_MSG_IN      0x07000000
multiline_comment|/* DT phases are illegal for non Ultra3 mode */
DECL|macro|SCR_ILG_OUT
mdefine_line|#define SCR_ILG_OUT&t;0x04000000
DECL|macro|SCR_ILG_IN
mdefine_line|#define SCR_ILG_IN&t;0x05000000
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Data transfer via SCSI.&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;MOVE_ABS (LEN)&n; *&t;&lt;&lt;start address&gt;&gt;&n; *&n; *&t;MOVE_IND (LEN)&n; *&t;&lt;&lt;dnad_offset&gt;&gt;&n; *&n; *&t;MOVE_TBL&n; *&t;&lt;&lt;dnad_offset&gt;&gt;&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|OPC_MOVE
mdefine_line|#define OPC_MOVE          0x08000000
DECL|macro|SCR_MOVE_ABS
mdefine_line|#define SCR_MOVE_ABS(l) ((0x00000000 | OPC_MOVE) | (l))
multiline_comment|/* #define SCR_MOVE_IND(l) ((0x20000000 | OPC_MOVE) | (l)) */
DECL|macro|SCR_MOVE_TBL
mdefine_line|#define SCR_MOVE_TBL     (0x10000000 | OPC_MOVE)
DECL|macro|SCR_CHMOV_ABS
mdefine_line|#define SCR_CHMOV_ABS(l) ((0x00000000) | (l))
multiline_comment|/* #define SCR_CHMOV_IND(l) ((0x20000000) | (l)) */
DECL|macro|SCR_CHMOV_TBL
mdefine_line|#define SCR_CHMOV_TBL     (0x10000000)
macro_line|#ifdef SYM_CONF_TARGET_ROLE_SUPPORT
multiline_comment|/* We steal the `indirect addressing&squot; flag for target mode MOVE in scripts */
DECL|macro|OPC_TCHMOVE
mdefine_line|#define OPC_TCHMOVE        0x08000000
DECL|macro|SCR_TCHMOVE_ABS
mdefine_line|#define SCR_TCHMOVE_ABS(l) ((0x20000000 | OPC_TCHMOVE) | (l))
DECL|macro|SCR_TCHMOVE_TBL
mdefine_line|#define SCR_TCHMOVE_TBL     (0x30000000 | OPC_TCHMOVE)
DECL|macro|SCR_TMOV_ABS
mdefine_line|#define SCR_TMOV_ABS(l)    ((0x20000000) | (l))
DECL|macro|SCR_TMOV_TBL
mdefine_line|#define SCR_TMOV_TBL        (0x30000000)
macro_line|#endif
DECL|struct|sym_tblmove
r_struct
id|sym_tblmove
(brace
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|addr
id|u32
id|addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Selection&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;SEL_ABS | SCR_ID (0..15)    [ | REL_JMP]&n; *&t;&lt;&lt;alternate_address&gt;&gt;&n; *&n; *&t;SEL_TBL | &lt;&lt; dnad_offset&gt;&gt;  [ | REL_JMP]&n; *&t;&lt;&lt;alternate_address&gt;&gt;&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_SEL_ABS
mdefine_line|#define&t;SCR_SEL_ABS&t;0x40000000
DECL|macro|SCR_SEL_ABS_ATN
mdefine_line|#define&t;SCR_SEL_ABS_ATN&t;0x41000000
DECL|macro|SCR_SEL_TBL
mdefine_line|#define&t;SCR_SEL_TBL&t;0x42000000
DECL|macro|SCR_SEL_TBL_ATN
mdefine_line|#define&t;SCR_SEL_TBL_ATN&t;0x43000000
macro_line|#ifdef SYM_CONF_TARGET_ROLE_SUPPORT
DECL|macro|SCR_RESEL_ABS
mdefine_line|#define&t;SCR_RESEL_ABS     0x40000000
DECL|macro|SCR_RESEL_ABS_ATN
mdefine_line|#define&t;SCR_RESEL_ABS_ATN 0x41000000
DECL|macro|SCR_RESEL_TBL
mdefine_line|#define&t;SCR_RESEL_TBL     0x42000000
DECL|macro|SCR_RESEL_TBL_ATN
mdefine_line|#define&t;SCR_RESEL_TBL_ATN 0x43000000
macro_line|#endif
DECL|struct|sym_tblsel
r_struct
id|sym_tblsel
(brace
DECL|member|sel_scntl4
id|u_char
id|sel_scntl4
suffix:semicolon
multiline_comment|/* C1010 only */
DECL|member|sel_sxfer
id|u_char
id|sel_sxfer
suffix:semicolon
DECL|member|sel_id
id|u_char
id|sel_id
suffix:semicolon
DECL|member|sel_scntl3
id|u_char
id|sel_scntl3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCR_JMP_REL
mdefine_line|#define SCR_JMP_REL     0x04000000
DECL|macro|SCR_ID
mdefine_line|#define SCR_ID(id)&t;(((u32)(id)) &lt;&lt; 16)
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Waiting for Disconnect or Reselect&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;WAIT_DISC&n; *&t;dummy: &lt;&lt;alternate_address&gt;&gt;&n; *&n; *&t;WAIT_RESEL&n; *&t;&lt;&lt;alternate_address&gt;&gt;&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_WAIT_DISC
mdefine_line|#define&t;SCR_WAIT_DISC&t;0x48000000
DECL|macro|SCR_WAIT_RESEL
mdefine_line|#define SCR_WAIT_RESEL  0x50000000
macro_line|#ifdef SYM_CONF_TARGET_ROLE_SUPPORT
DECL|macro|SCR_DISCONNECT
mdefine_line|#define&t;SCR_DISCONNECT&t;0x48000000
macro_line|#endif
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Bit Set / Reset&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;SET (flags {|.. })&n; *&n; *&t;CLR (flags {|.. })&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_SET
mdefine_line|#define SCR_SET(f)     (0x58000000 | (f))
DECL|macro|SCR_CLR
mdefine_line|#define SCR_CLR(f)     (0x60000000 | (f))
DECL|macro|SCR_CARRY
mdefine_line|#define&t;SCR_CARRY&t;0x00000400
DECL|macro|SCR_TRG
mdefine_line|#define&t;SCR_TRG&t;&t;0x00000200
DECL|macro|SCR_ACK
mdefine_line|#define&t;SCR_ACK&t;&t;0x00000040
DECL|macro|SCR_ATN
mdefine_line|#define&t;SCR_ATN&t;&t;0x00000008
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Memory to memory move&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;COPY (bytecount)&n; *&t;&lt;&lt; source_address &gt;&gt;&n; *&t;&lt;&lt; destination_address &gt;&gt;&n; *&n; *&t;SCR_COPY   sets the NO FLUSH option by default.&n; *&t;SCR_COPY_F does not set this option.&n; *&n; *&t;For chips which do not support this option,&n; *&t;sym_fw_bind_script() will remove this bit.&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_NO_FLUSH
mdefine_line|#define SCR_NO_FLUSH 0x01000000
DECL|macro|SCR_COPY
mdefine_line|#define SCR_COPY(n) (0xc0000000 | SCR_NO_FLUSH | (n))
DECL|macro|SCR_COPY_F
mdefine_line|#define SCR_COPY_F(n) (0xc0000000 | (n))
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Register move and binary operations&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;SFBR_REG (reg, op, data)        reg  = SFBR op data&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *&t;REG_SFBR (reg, op, data)        SFBR = reg op data&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *&t;REG_REG  (reg, op, data)        reg  = reg op data&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;On 825A, 875, 895 and 896 chips the content &n; *&t;of SFBR register can be used as data (SCR_SFBR_DATA).&n; *&t;The 896 has additionnal IO registers starting at &n; *&t;offset 0x80. Bit 7 of register offset is stored in &n; *&t;bit 7 of the SCRIPTS instruction first DWORD.&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_REG_OFS
mdefine_line|#define SCR_REG_OFS(ofs) ((((ofs) &amp; 0x7f) &lt;&lt; 16ul) + ((ofs) &amp; 0x80)) 
DECL|macro|SCR_SFBR_REG
mdefine_line|#define SCR_SFBR_REG(reg,op,data) &bslash;&n;        (0x68000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&amp;0xff)&lt;&lt;8ul))
DECL|macro|SCR_REG_SFBR
mdefine_line|#define SCR_REG_SFBR(reg,op,data) &bslash;&n;        (0x70000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&amp;0xff)&lt;&lt;8ul))
DECL|macro|SCR_REG_REG
mdefine_line|#define SCR_REG_REG(reg,op,data) &bslash;&n;        (0x78000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&amp;0xff)&lt;&lt;8ul))
DECL|macro|SCR_LOAD
mdefine_line|#define      SCR_LOAD   0x00000000
DECL|macro|SCR_SHL
mdefine_line|#define      SCR_SHL    0x01000000
DECL|macro|SCR_OR
mdefine_line|#define      SCR_OR     0x02000000
DECL|macro|SCR_XOR
mdefine_line|#define      SCR_XOR    0x03000000
DECL|macro|SCR_AND
mdefine_line|#define      SCR_AND    0x04000000
DECL|macro|SCR_SHR
mdefine_line|#define      SCR_SHR    0x05000000
DECL|macro|SCR_ADD
mdefine_line|#define      SCR_ADD    0x06000000
DECL|macro|SCR_ADDC
mdefine_line|#define      SCR_ADDC   0x07000000
DECL|macro|SCR_SFBR_DATA
mdefine_line|#define      SCR_SFBR_DATA   (0x00800000&gt;&gt;8ul)&t;/* Use SFBR as data */
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;FROM_REG (reg)&t;&t;  SFBR = reg&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *&t;TO_REG&t; (reg)&t;&t;  reg  = SFBR&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *&t;LOAD_REG (reg, data)&t;  reg  = &lt;data&gt;&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *&t;LOAD_SFBR(data) &t;  SFBR = &lt;data&gt;&n; *&t;&lt;&lt; 0 &gt;&gt;&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_FROM_REG
mdefine_line|#define&t;SCR_FROM_REG(reg) &bslash;&n;&t;SCR_REG_SFBR(reg,SCR_OR,0)
DECL|macro|SCR_TO_REG
mdefine_line|#define&t;SCR_TO_REG(reg) &bslash;&n;&t;SCR_SFBR_REG(reg,SCR_OR,0)
DECL|macro|SCR_LOAD_REG
mdefine_line|#define&t;SCR_LOAD_REG(reg,data) &bslash;&n;&t;SCR_REG_REG(reg,SCR_LOAD,data)
DECL|macro|SCR_LOAD_SFBR
mdefine_line|#define SCR_LOAD_SFBR(data) &bslash;&n;        (SCR_REG_SFBR (gpreg, SCR_LOAD, data))
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;LOAD  from memory   to register.&n; *&t;STORE from register to memory.&n; *&n; *&t;Only supported by 810A, 860, 825A, 875, 895 and 896.&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;LOAD_ABS (LEN)&n; *&t;&lt;&lt;start address&gt;&gt;&n; *&n; *&t;LOAD_REL (LEN)        (DSA relative)&n; *&t;&lt;&lt;dsa_offset&gt;&gt;&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_REG_OFS2
mdefine_line|#define SCR_REG_OFS2(ofs) (((ofs) &amp; 0xff) &lt;&lt; 16ul)
DECL|macro|SCR_NO_FLUSH2
mdefine_line|#define SCR_NO_FLUSH2&t;0x02000000
DECL|macro|SCR_DSA_REL2
mdefine_line|#define SCR_DSA_REL2&t;0x10000000
DECL|macro|SCR_LOAD_R
mdefine_line|#define SCR_LOAD_R(reg, how, n) &bslash;&n;        (0xe1000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))
DECL|macro|SCR_STORE_R
mdefine_line|#define SCR_STORE_R(reg, how, n) &bslash;&n;        (0xe0000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))
DECL|macro|SCR_LOAD_ABS
mdefine_line|#define SCR_LOAD_ABS(reg, n)&t;SCR_LOAD_R(reg, SCR_NO_FLUSH2, n)
DECL|macro|SCR_LOAD_REL
mdefine_line|#define SCR_LOAD_REL(reg, n)&t;SCR_LOAD_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2, n)
DECL|macro|SCR_LOAD_ABS_F
mdefine_line|#define SCR_LOAD_ABS_F(reg, n)&t;SCR_LOAD_R(reg, 0, n)
DECL|macro|SCR_LOAD_REL_F
mdefine_line|#define SCR_LOAD_REL_F(reg, n)&t;SCR_LOAD_R(reg, SCR_DSA_REL2, n)
DECL|macro|SCR_STORE_ABS
mdefine_line|#define SCR_STORE_ABS(reg, n)&t;SCR_STORE_R(reg, SCR_NO_FLUSH2, n)
DECL|macro|SCR_STORE_REL
mdefine_line|#define SCR_STORE_REL(reg, n)&t;SCR_STORE_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2,n)
DECL|macro|SCR_STORE_ABS_F
mdefine_line|#define SCR_STORE_ABS_F(reg, n)&t;SCR_STORE_R(reg, 0, n)
DECL|macro|SCR_STORE_REL_F
mdefine_line|#define SCR_STORE_REL_F(reg, n)&t;SCR_STORE_R(reg, SCR_DSA_REL2, n)
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;Waiting for Disconnect or Reselect&n; *&n; *-----------------------------------------------------------&n; *&n; *&t;JUMP            [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;address&gt;&gt;&n; *&n; *&t;JUMPR           [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;distance&gt;&gt;&n; *&n; *&t;CALL            [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;address&gt;&gt;&n; *&n; *&t;CALLR           [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;distance&gt;&gt;&n; *&n; *&t;RETURN          [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;dummy&gt;&gt;&n; *&n; *&t;INT             [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;ident&gt;&gt;&n; *&n; *&t;INT_FLY         [ | IFTRUE/IFFALSE ( ... ) ]&n; *&t;&lt;&lt;ident&gt;&gt;&n; *&n; *&t;Conditions:&n; *&t;     WHEN (phase)&n; *&t;     IF   (phase)&n; *&t;     CARRYSET&n; *&t;     DATA (data, mask)&n; *&n; *-----------------------------------------------------------&n; */
DECL|macro|SCR_NO_OP
mdefine_line|#define SCR_NO_OP       0x80000000
DECL|macro|SCR_JUMP
mdefine_line|#define SCR_JUMP        0x80080000
DECL|macro|SCR_JUMP64
mdefine_line|#define SCR_JUMP64      0x80480000
DECL|macro|SCR_JUMPR
mdefine_line|#define SCR_JUMPR       0x80880000
DECL|macro|SCR_CALL
mdefine_line|#define SCR_CALL        0x88080000
DECL|macro|SCR_CALLR
mdefine_line|#define SCR_CALLR       0x88880000
DECL|macro|SCR_RETURN
mdefine_line|#define SCR_RETURN      0x90080000
DECL|macro|SCR_INT
mdefine_line|#define SCR_INT         0x98080000
DECL|macro|SCR_INT_FLY
mdefine_line|#define SCR_INT_FLY     0x98180000
DECL|macro|IFFALSE
mdefine_line|#define IFFALSE(arg)   (0x00080000 | (arg))
DECL|macro|IFTRUE
mdefine_line|#define IFTRUE(arg)    (0x00000000 | (arg))
DECL|macro|WHEN
mdefine_line|#define WHEN(phase)    (0x00030000 | (phase))
DECL|macro|IF
mdefine_line|#define IF(phase)      (0x00020000 | (phase))
DECL|macro|DATA
mdefine_line|#define DATA(D)        (0x00040000 | ((D) &amp; 0xff))
DECL|macro|MASK
mdefine_line|#define MASK(D,M)      (0x00040000 | (((M ^ 0xff) &amp; 0xff) &lt;&lt; 8ul)|((D) &amp; 0xff))
DECL|macro|CARRYSET
mdefine_line|#define CARRYSET       (0x00200000)
multiline_comment|/*-----------------------------------------------------------&n; *&n; *&t;SCSI  constants.&n; *&n; *-----------------------------------------------------------&n; */
multiline_comment|/*&n; *&t;Messages&n; */
DECL|macro|M_COMPLETE
mdefine_line|#define&t;M_COMPLETE&t;(0x00)
DECL|macro|M_EXTENDED
mdefine_line|#define&t;M_EXTENDED&t;(0x01)
DECL|macro|M_SAVE_DP
mdefine_line|#define&t;M_SAVE_DP&t;(0x02)
DECL|macro|M_RESTORE_DP
mdefine_line|#define&t;M_RESTORE_DP&t;(0x03)
DECL|macro|M_DISCONNECT
mdefine_line|#define&t;M_DISCONNECT&t;(0x04)
DECL|macro|M_ID_ERROR
mdefine_line|#define&t;M_ID_ERROR&t;(0x05)
DECL|macro|M_ABORT
mdefine_line|#define&t;M_ABORT&t;&t;(0x06)
DECL|macro|M_REJECT
mdefine_line|#define&t;M_REJECT&t;(0x07)
DECL|macro|M_NOOP
mdefine_line|#define&t;M_NOOP&t;&t;(0x08)
DECL|macro|M_PARITY
mdefine_line|#define&t;M_PARITY&t;(0x09)
DECL|macro|M_LCOMPLETE
mdefine_line|#define&t;M_LCOMPLETE&t;(0x0a)
DECL|macro|M_FCOMPLETE
mdefine_line|#define&t;M_FCOMPLETE&t;(0x0b)
DECL|macro|M_RESET
mdefine_line|#define&t;M_RESET&t;&t;(0x0c)
DECL|macro|M_ABORT_TAG
mdefine_line|#define&t;M_ABORT_TAG&t;(0x0d)
DECL|macro|M_CLEAR_QUEUE
mdefine_line|#define&t;M_CLEAR_QUEUE&t;(0x0e)
DECL|macro|M_INIT_REC
mdefine_line|#define&t;M_INIT_REC&t;(0x0f)
DECL|macro|M_REL_REC
mdefine_line|#define&t;M_REL_REC&t;(0x10)
DECL|macro|M_TERMINATE
mdefine_line|#define&t;M_TERMINATE&t;(0x11)
DECL|macro|M_SIMPLE_TAG
mdefine_line|#define&t;M_SIMPLE_TAG&t;(0x20)
DECL|macro|M_HEAD_TAG
mdefine_line|#define&t;M_HEAD_TAG&t;(0x21)
DECL|macro|M_ORDERED_TAG
mdefine_line|#define&t;M_ORDERED_TAG&t;(0x22)
DECL|macro|M_IGN_RESIDUE
mdefine_line|#define&t;M_IGN_RESIDUE&t;(0x23)
DECL|macro|M_IDENTIFY
mdefine_line|#define&t;M_IDENTIFY   &t;(0x80)
DECL|macro|M_X_MODIFY_DP
mdefine_line|#define&t;M_X_MODIFY_DP&t;(0x00)
DECL|macro|M_X_SYNC_REQ
mdefine_line|#define&t;M_X_SYNC_REQ&t;(0x01)
DECL|macro|M_X_WIDE_REQ
mdefine_line|#define&t;M_X_WIDE_REQ&t;(0x03)
DECL|macro|M_X_PPR_REQ
mdefine_line|#define&t;M_X_PPR_REQ&t;(0x04)
multiline_comment|/*&n; *&t;PPR protocol options&n; */
DECL|macro|PPR_OPT_IU
mdefine_line|#define&t;PPR_OPT_IU&t;(0x01)
DECL|macro|PPR_OPT_DT
mdefine_line|#define&t;PPR_OPT_DT&t;(0x02)
DECL|macro|PPR_OPT_QAS
mdefine_line|#define&t;PPR_OPT_QAS&t;(0x04)
DECL|macro|PPR_OPT_MASK
mdefine_line|#define PPR_OPT_MASK&t;(0x07)
multiline_comment|/*&n; *&t;Status&n; */
DECL|macro|S_GOOD
mdefine_line|#define&t;S_GOOD&t;&t;(0x00)
DECL|macro|S_CHECK_COND
mdefine_line|#define&t;S_CHECK_COND&t;(0x02)
DECL|macro|S_COND_MET
mdefine_line|#define&t;S_COND_MET&t;(0x04)
DECL|macro|S_BUSY
mdefine_line|#define&t;S_BUSY&t;&t;(0x08)
DECL|macro|S_INT
mdefine_line|#define&t;S_INT&t;&t;(0x10)
DECL|macro|S_INT_COND_MET
mdefine_line|#define&t;S_INT_COND_MET&t;(0x14)
DECL|macro|S_CONFLICT
mdefine_line|#define&t;S_CONFLICT&t;(0x18)
DECL|macro|S_TERMINATED
mdefine_line|#define&t;S_TERMINATED&t;(0x20)
DECL|macro|S_QUEUE_FULL
mdefine_line|#define&t;S_QUEUE_FULL&t;(0x28)
DECL|macro|S_ILLEGAL
mdefine_line|#define&t;S_ILLEGAL&t;(0xff)
macro_line|#endif /* defined SYM_DEFS_H */
eof
