multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Public interface for reading Atmel EEPROMs via L1 system controllers&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_EEPROM_H
DECL|macro|_ASM_SN_EEPROM_H
mdefine_line|#define _ASM_SN_EEPROM_H
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/vector.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/nic.h&gt;
multiline_comment|/*&n; * The following structures are an implementation of the EEPROM info&n; * areas described in the SN1 EEPROM spec and the IPMI FRU Information&n; * Storage definition&n; */
multiline_comment|/* Maximum lengths for EEPROM fields&n; */
DECL|macro|EEPROM_PARTNUM_LEN
mdefine_line|#define EEPROM_PARTNUM_LEN&t;20
DECL|macro|EEPROM_SERNUM_LEN
mdefine_line|#define EEPROM_SERNUM_LEN&t;10
DECL|macro|EEPROM_MANUF_NAME_LEN
mdefine_line|#define&t;EEPROM_MANUF_NAME_LEN&t;10
DECL|macro|EEPROM_PROD_NAME_LEN
mdefine_line|#define EEPROM_PROD_NAME_LEN&t;14
multiline_comment|/* The EEPROM &quot;common header&quot;, which contains offsets to the other&n; * info areas in the EEPROM&n; */
DECL|struct|eeprom_common_hdr_t
r_typedef
r_struct
id|eeprom_common_hdr_t
(brace
DECL|member|format
id|uchar_t
id|format
suffix:semicolon
multiline_comment|/* common header format byte */
DECL|member|internal_use
id|uchar_t
id|internal_use
suffix:semicolon
multiline_comment|/* offsets to various info areas */
DECL|member|chassis
id|uchar_t
id|chassis
suffix:semicolon
multiline_comment|/*  (in doubleword units)        */
DECL|member|board
id|uchar_t
id|board
suffix:semicolon
DECL|member|product
id|uchar_t
id|product
suffix:semicolon
DECL|member|multi_record
id|uchar_t
id|multi_record
suffix:semicolon
DECL|member|pad
id|uchar_t
id|pad
suffix:semicolon
DECL|member|checksum
id|uchar_t
id|checksum
suffix:semicolon
DECL|typedef|eeprom_common_hdr_t
)brace
id|eeprom_common_hdr_t
suffix:semicolon
multiline_comment|/* The chassis (brick) info area &n; */
DECL|struct|eeprom_chassis_ia_t
r_typedef
r_struct
id|eeprom_chassis_ia_t
(brace
DECL|member|format
id|uchar_t
id|format
suffix:semicolon
multiline_comment|/* format byte */
DECL|member|length
id|uchar_t
id|length
suffix:semicolon
multiline_comment|/* info area length in doublewords */
DECL|member|type
id|uchar_t
id|type
suffix:semicolon
multiline_comment|/* chassis type (always 0x17 &quot;rack mount&quot;) */
DECL|member|part_num_tl
id|uchar_t
id|part_num_tl
suffix:semicolon
multiline_comment|/* type/length of part number field */
DECL|member|part_num
r_char
id|part_num
(braket
id|EEPROM_PARTNUM_LEN
)braket
suffix:semicolon
multiline_comment|/* ASCII part number */
DECL|member|serial_num_tl
id|uchar_t
id|serial_num_tl
suffix:semicolon
multiline_comment|/* type/length of serial number field */
DECL|member|serial_num
r_char
id|serial_num
(braket
id|EEPROM_SERNUM_LEN
)braket
suffix:semicolon
multiline_comment|/* ASCII serial number */
DECL|member|checksum
id|uchar_t
id|checksum
suffix:semicolon
DECL|typedef|eeprom_chassis_ia_t
)brace
id|eeprom_chassis_ia_t
suffix:semicolon
multiline_comment|/* The board info area&n; */
DECL|struct|eeprom_board_ia_t
r_typedef
r_struct
id|eeprom_board_ia_t
(brace
DECL|member|format
id|uchar_t
id|format
suffix:semicolon
multiline_comment|/* format byte */
DECL|member|length
id|uchar_t
id|length
suffix:semicolon
multiline_comment|/* info area length in doublewords */
DECL|member|language
id|uchar_t
id|language
suffix:semicolon
multiline_comment|/* language code, always 0x00 &quot;English&quot; */
DECL|member|mfg_date
r_int
id|mfg_date
suffix:semicolon
multiline_comment|/* date &amp; time of manufacture, in minutes&n;&t;&t;&t;&t;    since 0:00 1/1/96 */
DECL|member|manuf_tl
id|uchar_t
id|manuf_tl
suffix:semicolon
multiline_comment|/* type/length of manufacturer name field */
DECL|member|manuf
r_char
id|manuf
(braket
id|EEPROM_MANUF_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* ASCII manufacturer name */
DECL|member|product_tl
id|uchar_t
id|product_tl
suffix:semicolon
multiline_comment|/* type/length of product name field */
DECL|member|product
r_char
id|product
(braket
id|EEPROM_PROD_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* ASCII product name */
DECL|member|serial_num_tl
id|uchar_t
id|serial_num_tl
suffix:semicolon
multiline_comment|/* type/length of board serial number */
DECL|member|serial_num
r_char
id|serial_num
(braket
id|EEPROM_SERNUM_LEN
)braket
suffix:semicolon
multiline_comment|/* ASCII serial number */
DECL|member|part_num_tl
id|uchar_t
id|part_num_tl
suffix:semicolon
multiline_comment|/* type/length of board part number */
DECL|member|part_num
r_char
id|part_num
(braket
id|EEPROM_PARTNUM_LEN
)braket
suffix:semicolon
multiline_comment|/* ASCII part number */
multiline_comment|/*&n;     * &quot;custom&quot; fields -- see SN1 EEPROM Spec&n;     */
DECL|member|board_rev_tl
id|uchar_t
id|board_rev_tl
suffix:semicolon
multiline_comment|/* type/length of board rev (always 0xC2) */
DECL|member|board_rev
r_char
id|board_rev
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ASCII board revision */
DECL|member|eeprom_size_tl
id|uchar_t
id|eeprom_size_tl
suffix:semicolon
multiline_comment|/* type/length of eeprom size field */
DECL|member|eeprom_size
id|uchar_t
id|eeprom_size
suffix:semicolon
multiline_comment|/* size code for eeprom */
DECL|member|temp_waiver_tl
id|uchar_t
id|temp_waiver_tl
suffix:semicolon
multiline_comment|/* type/length of temp waiver field (0xC2) */
DECL|member|temp_waiver
r_char
id|temp_waiver
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* temp waiver */
multiline_comment|/*&n;     * these fields only appear in main boards&squot; EEPROMs&n;     */
DECL|member|ekey_G_tl
id|uchar_t
id|ekey_G_tl
suffix:semicolon
multiline_comment|/* type/length of encryption key &quot;G&quot; */
DECL|member|ekey_G
r_uint32
id|ekey_G
suffix:semicolon
multiline_comment|/* encryption key &quot;G&quot; */
DECL|member|ekey_P_tl
id|uchar_t
id|ekey_P_tl
suffix:semicolon
multiline_comment|/* type/length of encryption key &quot;P&quot; */
DECL|member|ekey_P
r_uint32
id|ekey_P
suffix:semicolon
multiline_comment|/* encryption key &quot;P&quot; */
DECL|member|ekey_Y_tl
id|uchar_t
id|ekey_Y_tl
suffix:semicolon
multiline_comment|/* type/length of encryption key &quot;Y&quot; */
DECL|member|ekey_Y
r_uint32
id|ekey_Y
suffix:semicolon
multiline_comment|/* encryption key &quot;Y&quot; */
multiline_comment|/*&n;     * these fields are used for I bricks only&n;     */
DECL|member|mac_addr_tl
id|uchar_t
id|mac_addr_tl
suffix:semicolon
multiline_comment|/* type/length of MAC address */
DECL|member|mac_addr
r_char
id|mac_addr
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* MAC address */
DECL|member|ieee1394_cfg_tl
id|uchar_t
id|ieee1394_cfg_tl
suffix:semicolon
multiline_comment|/* type/length of IEEE 1394 info */
DECL|member|ieee1394_cfg
id|uchar_t
id|ieee1394_cfg
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* IEEE 1394 config info */
multiline_comment|/*&n;     * all boards have a checksum&n;     */
DECL|member|checksum
id|uchar_t
id|checksum
suffix:semicolon
DECL|typedef|eeprom_board_ia_t
)brace
id|eeprom_board_ia_t
suffix:semicolon
multiline_comment|/* given a pointer to the three-byte little-endian EEPROM representation&n; * of date-of-manufacture, this function translates to a big-endian&n; * integer format&n; */
r_int
id|eeprom_xlate_board_mfr_date
c_func
(paren
id|uchar_t
op_star
id|src
)paren
suffix:semicolon
multiline_comment|/* EEPROM Serial Presence Detect record (used for DIMMs in IP35)&n; */
DECL|struct|eeprom_spd_t
r_typedef
r_struct
id|eeprom_spd_t
(brace
DECL|member|spd_used
multiline_comment|/* 0*/
id|uchar_t
id|spd_used
suffix:semicolon
multiline_comment|/* # of bytes written to serial memory by manufacturer */
DECL|member|spd_size
multiline_comment|/* 1*/
id|uchar_t
id|spd_size
suffix:semicolon
multiline_comment|/* Total # of bytes of SPD memory device */
DECL|member|mem_type
multiline_comment|/* 2*/
id|uchar_t
id|mem_type
suffix:semicolon
multiline_comment|/* Fundamental memory type (FPM, EDO, SDRAM..) */
DECL|member|num_rows
multiline_comment|/* 3*/
id|uchar_t
id|num_rows
suffix:semicolon
multiline_comment|/* # of row addresses on this assembly */
DECL|member|num_cols
multiline_comment|/* 4*/
id|uchar_t
id|num_cols
suffix:semicolon
multiline_comment|/* # Column Addresses on this assembly */
DECL|member|mod_rows
multiline_comment|/* 5*/
id|uchar_t
id|mod_rows
suffix:semicolon
multiline_comment|/* # Module Rows on this assembly */
DECL|member|data_width
multiline_comment|/* 6*/
id|uchar_t
id|data_width
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data Width of this assembly (16b little-endian) */
DECL|member|volt_if
multiline_comment|/* 8*/
id|uchar_t
id|volt_if
suffix:semicolon
multiline_comment|/* Voltage interface standard of this assembly */
DECL|member|cyc_time
multiline_comment|/* 9*/
id|uchar_t
id|cyc_time
suffix:semicolon
multiline_comment|/* SDRAM Cycle time, CL=X (highest CAS latency) */
DECL|member|acc_time
multiline_comment|/* A*/
id|uchar_t
id|acc_time
suffix:semicolon
multiline_comment|/* SDRAM Access from Clock (highest CAS latency) */
DECL|member|dimm_cfg
multiline_comment|/* B*/
id|uchar_t
id|dimm_cfg
suffix:semicolon
multiline_comment|/* DIMM Configuration type (non-parity, ECC) */
DECL|member|refresh_rt
multiline_comment|/* C*/
id|uchar_t
id|refresh_rt
suffix:semicolon
multiline_comment|/* Refresh Rate/Type */
DECL|member|prim_width
multiline_comment|/* D*/
id|uchar_t
id|prim_width
suffix:semicolon
multiline_comment|/* Primary SDRAM Width */
DECL|member|ec_width
multiline_comment|/* E*/
id|uchar_t
id|ec_width
suffix:semicolon
multiline_comment|/* Error Checking SDRAM width */
DECL|member|min_delay
multiline_comment|/* F*/
id|uchar_t
id|min_delay
suffix:semicolon
multiline_comment|/* Min Clock Delay Back to Back Random Col Address */
DECL|member|burst_len
multiline_comment|/*10*/
id|uchar_t
id|burst_len
suffix:semicolon
multiline_comment|/* Burst Lengths Supported */
DECL|member|num_banks
multiline_comment|/*11*/
id|uchar_t
id|num_banks
suffix:semicolon
multiline_comment|/* # of Banks on Each SDRAM Device */
DECL|member|cas_latencies
multiline_comment|/*12*/
id|uchar_t
id|cas_latencies
suffix:semicolon
multiline_comment|/* CAS# Latencies Supported */
DECL|member|cs_latencies
multiline_comment|/*13*/
id|uchar_t
id|cs_latencies
suffix:semicolon
multiline_comment|/* CS# Latencies Supported */
DECL|member|we_latencies
multiline_comment|/*14*/
id|uchar_t
id|we_latencies
suffix:semicolon
multiline_comment|/* Write Latencies Supported */
DECL|member|mod_attrib
multiline_comment|/*15*/
id|uchar_t
id|mod_attrib
suffix:semicolon
multiline_comment|/* SDRAM Module Attributes */
DECL|member|dev_attrib
multiline_comment|/*16*/
id|uchar_t
id|dev_attrib
suffix:semicolon
multiline_comment|/* SDRAM Device Attributes: General */
DECL|member|cyc_time2
multiline_comment|/*17*/
id|uchar_t
id|cyc_time2
suffix:semicolon
multiline_comment|/* Min SDRAM Cycle time at CL X-1 (2nd highest CAS latency) */
DECL|member|acc_time2
multiline_comment|/*18*/
id|uchar_t
id|acc_time2
suffix:semicolon
multiline_comment|/* SDRAM Access from Clock at CL X-1 (2nd highest CAS latency) */
DECL|member|cyc_time3
multiline_comment|/*19*/
id|uchar_t
id|cyc_time3
suffix:semicolon
multiline_comment|/* Min SDRAM Cycle time at CL X-2 (3rd highest CAS latency) */
DECL|member|acc_time3
multiline_comment|/*1A*/
id|uchar_t
id|acc_time3
suffix:semicolon
multiline_comment|/* Max SDRAM Access from Clock at CL X-2 (3nd highest CAS latency) */
DECL|member|min_row_prechg
multiline_comment|/*1B*/
id|uchar_t
id|min_row_prechg
suffix:semicolon
multiline_comment|/* Min Row Precharge Time (Trp) */
DECL|member|min_ra_to_ra
multiline_comment|/*1C*/
id|uchar_t
id|min_ra_to_ra
suffix:semicolon
multiline_comment|/* Min Row Active to Row Active (Trrd) */
DECL|member|min_ras_to_cas
multiline_comment|/*1D*/
id|uchar_t
id|min_ras_to_cas
suffix:semicolon
multiline_comment|/* Min RAS to CAS Delay (Trcd) */
DECL|member|min_ras_pulse
multiline_comment|/*1E*/
id|uchar_t
id|min_ras_pulse
suffix:semicolon
multiline_comment|/* Minimum RAS Pulse Width (Tras) */
DECL|member|row_density
multiline_comment|/*1F*/
id|uchar_t
id|row_density
suffix:semicolon
multiline_comment|/* Density of each row on module */
DECL|member|ca_setup
multiline_comment|/*20*/
id|uchar_t
id|ca_setup
suffix:semicolon
multiline_comment|/* Command and Address signal input setup time */
DECL|member|ca_hold
multiline_comment|/*21*/
id|uchar_t
id|ca_hold
suffix:semicolon
multiline_comment|/* Command and Address signal input hold time */
DECL|member|d_setup
multiline_comment|/*22*/
id|uchar_t
id|d_setup
suffix:semicolon
multiline_comment|/* Data signal input setup time */
DECL|member|d_hold
multiline_comment|/*23*/
id|uchar_t
id|d_hold
suffix:semicolon
multiline_comment|/* Data signal input hold time */
DECL|member|pad0
multiline_comment|/*24*/
id|uchar_t
id|pad0
(braket
l_int|26
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|data_rev
multiline_comment|/*3E*/
id|uchar_t
id|data_rev
suffix:semicolon
multiline_comment|/* SPD Data Revision Code */
DECL|member|checksum
multiline_comment|/*3F*/
id|uchar_t
id|checksum
suffix:semicolon
multiline_comment|/* Checksum for bytes 0-62 */
DECL|member|jedec_id
multiline_comment|/*40*/
id|uchar_t
id|jedec_id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Manufacturer&squot;s JEDEC ID code */
DECL|member|mfg_loc
multiline_comment|/*48*/
id|uchar_t
id|mfg_loc
suffix:semicolon
multiline_comment|/* Manufacturing Location */
DECL|member|part_num
multiline_comment|/*49*/
id|uchar_t
id|part_num
(braket
l_int|18
)braket
suffix:semicolon
multiline_comment|/* Manufacturer&squot;s Part Number */
DECL|member|rev_code
multiline_comment|/*5B*/
id|uchar_t
id|rev_code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Revision Code */
DECL|member|mfg_date
multiline_comment|/*5D*/
id|uchar_t
id|mfg_date
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Manufacturing Date */
DECL|member|ser_num
multiline_comment|/*5F*/
id|uchar_t
id|ser_num
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Assembly Serial Number */
DECL|member|manuf_data
multiline_comment|/*63*/
id|uchar_t
id|manuf_data
(braket
l_int|27
)braket
suffix:semicolon
multiline_comment|/* Manufacturer Specific Data */
DECL|member|intel_freq
multiline_comment|/*7E*/
id|uchar_t
id|intel_freq
suffix:semicolon
multiline_comment|/* Intel specification frequency */
DECL|member|intel_100MHz
multiline_comment|/*7F*/
id|uchar_t
id|intel_100MHz
suffix:semicolon
multiline_comment|/* Intel spec details for 100MHz support */
DECL|typedef|eeprom_spd_t
)brace
id|eeprom_spd_t
suffix:semicolon
DECL|macro|EEPROM_SPD_RECORD_MAXLEN
mdefine_line|#define EEPROM_SPD_RECORD_MAXLEN&t;256
DECL|union|eeprom_spd_u
r_typedef
r_union
id|eeprom_spd_u
(brace
DECL|member|fields
id|eeprom_spd_t
id|fields
suffix:semicolon
DECL|member|bytes
r_char
id|bytes
(braket
id|EEPROM_SPD_RECORD_MAXLEN
)braket
suffix:semicolon
DECL|typedef|eeprom_spd_u
)brace
id|eeprom_spd_u
suffix:semicolon
multiline_comment|/* EEPROM board record&n; */
DECL|struct|eeprom_brd_record_t
r_typedef
r_struct
id|eeprom_brd_record_t
(brace
DECL|member|chassis_ia
id|eeprom_chassis_ia_t
op_star
id|chassis_ia
suffix:semicolon
DECL|member|board_ia
id|eeprom_board_ia_t
op_star
id|board_ia
suffix:semicolon
DECL|member|spd
id|eeprom_spd_u
op_star
id|spd
suffix:semicolon
DECL|typedef|eeprom_brd_record_t
)brace
id|eeprom_brd_record_t
suffix:semicolon
multiline_comment|/* End-of-fields marker&n; */
DECL|macro|EEPROM_EOF
mdefine_line|#define EEPROM_EOF&t;        0xc1
multiline_comment|/* masks for dissecting the type/length bytes&n; */
DECL|macro|FIELD_FORMAT_MASK
mdefine_line|#define FIELD_FORMAT_MASK       0xc0
DECL|macro|FIELD_LENGTH_MASK
mdefine_line|#define FIELD_LENGTH_MASK       0x3f
multiline_comment|/* field format codes (used in type/length bytes)&n; */
DECL|macro|FIELD_FORMAT_BINARY
mdefine_line|#define FIELD_FORMAT_BINARY     0x00 /* binary format */
DECL|macro|FIELD_FORMAT_BCD
mdefine_line|#define FIELD_FORMAT_BCD        0x40 /* BCD */
DECL|macro|FIELD_FORMAT_PACKED
mdefine_line|#define FIELD_FORMAT_PACKED     0x80 /* packed 6-bit ASCII */
DECL|macro|FIELD_FORMAT_ASCII
mdefine_line|#define FIELD_FORMAT_ASCII      0xC0 /* 8-bit ASCII */
multiline_comment|/* codes specifying brick and board type&n; */
DECL|macro|C_BRICK
mdefine_line|#define C_BRICK&t;&t;0x100
DECL|macro|C_PIMM
mdefine_line|#define C_PIMM&t;&t;(C_BRICK | 0x10)
DECL|macro|C_PIMM_0
mdefine_line|#define C_PIMM_0&t;(C_PIMM) /* | 0x0 */
DECL|macro|C_PIMM_1
mdefine_line|#define C_PIMM_1&t;(C_PIMM | 0x1)
DECL|macro|C_DIMM
mdefine_line|#define C_DIMM&t;&t;(C_BRICK | 0x20)
DECL|macro|C_DIMM_0
mdefine_line|#define C_DIMM_0&t;(C_DIMM) /* | 0x0 */
DECL|macro|C_DIMM_1
mdefine_line|#define C_DIMM_1&t;(C_DIMM | 0x1)
DECL|macro|C_DIMM_2
mdefine_line|#define C_DIMM_2&t;(C_DIMM | 0x2)
DECL|macro|C_DIMM_3
mdefine_line|#define C_DIMM_3&t;(C_DIMM | 0x3)
DECL|macro|C_DIMM_4
mdefine_line|#define C_DIMM_4&t;(C_DIMM | 0x4)
DECL|macro|C_DIMM_5
mdefine_line|#define C_DIMM_5&t;(C_DIMM | 0x5)
DECL|macro|C_DIMM_6
mdefine_line|#define C_DIMM_6&t;(C_DIMM | 0x6)
DECL|macro|C_DIMM_7
mdefine_line|#define C_DIMM_7&t;(C_DIMM | 0x7)
DECL|macro|R_BRICK
mdefine_line|#define R_BRICK&t;&t;0x200
DECL|macro|R_POWER
mdefine_line|#define R_POWER&t;&t;(R_BRICK | 0x10)
DECL|macro|VECTOR
mdefine_line|#define VECTOR&t;&t;0x300 /* used in vector ops when the destination&n;&t;&t;&t;       * could be a cbrick or an rbrick */
DECL|macro|IO_BRICK
mdefine_line|#define IO_BRICK&t;0x400
DECL|macro|IO_POWER
mdefine_line|#define IO_POWER&t;(IO_BRICK | 0x10)
DECL|macro|BRICK_MASK
mdefine_line|#define BRICK_MASK&t;0xf00
DECL|macro|SUBORD_MASK
mdefine_line|#define SUBORD_MASK&t;0xf0  /* AND with component specification; if the&n;&t;&t;&t;         the result is non-zero, then the component&n;&t;&t;&t;         is a subordinate board of some kind */
DECL|macro|COMPT_MASK
mdefine_line|#define COMPT_MASK&t;0xf   /* if there&squot;s more than one instance of a&n;&t;&t;&t;&t; particular type of subordinate board, this &n;&t;&t;&t;&t; masks out which one we&squot;re talking about */
multiline_comment|/* functions &amp; macros for obtaining &quot;NIC-like&quot; strings from EEPROMs&n; */
r_int
id|eeprom_str
c_func
(paren
r_char
op_star
id|nic_str
comma
id|nasid_t
id|nasid
comma
r_int
id|component
)paren
suffix:semicolon
r_int
id|vector_eeprom_str
c_func
(paren
r_char
op_star
id|nic_str
comma
id|nasid_t
id|nasid
comma
r_int
id|component
comma
id|net_vec_t
id|path
)paren
suffix:semicolon
DECL|macro|CBRICK_EEPROM_STR
mdefine_line|#define CBRICK_EEPROM_STR(s,n)&t;eeprom_str((s),(n),C_BRICK)
DECL|macro|IOBRICK_EEPROM_STR
mdefine_line|#define IOBRICK_EEPROM_STR(s,n)&t;eeprom_str((s),(n),IO_BRICK)
DECL|macro|RBRICK_EEPROM_STR
mdefine_line|#define RBRICK_EEPROM_STR(s,n,p)  vector_eeprom_str((s),(n),R_BRICK,p)
DECL|macro|VECTOR_EEPROM_STR
mdefine_line|#define VECTOR_EEPROM_STR(s,n,p)  vector_eeprom_str((s),(n),VECTOR,p)
multiline_comment|/* functions for obtaining formatted records from EEPROMs&n; */
r_int
id|cbrick_eeprom_read
c_func
(paren
id|eeprom_brd_record_t
op_star
id|buf
comma
id|nasid_t
id|nasid
comma
r_int
id|component
)paren
suffix:semicolon
r_int
id|iobrick_eeprom_read
c_func
(paren
id|eeprom_brd_record_t
op_star
id|buf
comma
id|nasid_t
id|nasid
comma
r_int
id|component
)paren
suffix:semicolon
r_int
id|vector_eeprom_read
c_func
(paren
id|eeprom_brd_record_t
op_star
id|buf
comma
id|nasid_t
id|nasid
comma
id|net_vec_t
id|path
comma
r_int
id|component
)paren
suffix:semicolon
multiline_comment|/* functions providing unique id&squot;s for duplonet and i/o discovery&n; */
r_int
id|cbrick_uid_get
c_func
(paren
id|nasid_t
id|nasid
comma
r_uint64
op_star
id|uid
)paren
suffix:semicolon
r_int
id|rbrick_uid_get
c_func
(paren
id|nasid_t
id|nasid
comma
id|net_vec_t
id|path
comma
r_uint64
op_star
id|uid
)paren
suffix:semicolon
r_int
id|iobrick_uid_get
c_func
(paren
id|nasid_t
id|nasid
comma
r_uint64
op_star
id|uid
)paren
suffix:semicolon
multiline_comment|/* retrieve the ethernet MAC address for an I-brick&n; */
r_int
id|ibrick_mac_addr_get
c_func
(paren
id|nasid_t
id|nasid
comma
r_char
op_star
id|eaddr
)paren
suffix:semicolon
multiline_comment|/* error codes&n; */
DECL|macro|EEP_OK
mdefine_line|#define EEP_OK&t;&t;&t;0
DECL|macro|EEP_L1
mdefine_line|#define EEP_L1&t;&t;&t;1
DECL|macro|EEP_FAIL
mdefine_line|#define EEP_FAIL&t;&t;2
DECL|macro|EEP_BAD_CHECKSUM
mdefine_line|#define EEP_BAD_CHECKSUM&t;3
DECL|macro|EEP_NICIFY
mdefine_line|#define EEP_NICIFY&t;&t;4
DECL|macro|EEP_PARAM
mdefine_line|#define EEP_PARAM&t;&t;6
DECL|macro|EEP_NOMEM
mdefine_line|#define EEP_NOMEM&t;&t;7
multiline_comment|/* given a hardware graph vertex and an indication of the brick type,&n; * brick and board to be read, this functions reads the eeprom and&n; * attaches a &quot;NIC&quot;-format string of manufacturing information to the &n; * vertex.  If the vertex already has the string, just returns the&n; * string.  If component is not VECTOR or R_BRICK, the path parameter&n; * is ignored.&n; */
macro_line|#ifdef LATER
r_char
op_star
id|eeprom_vertex_info_set
c_func
(paren
r_int
id|component
comma
r_int
id|nasid
comma
id|devfs_handle_t
id|v
comma
id|net_vec_t
id|path
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* We may need to differentiate between an XBridge and other types of&n; * bridges during discovery to tell whether the bridge in question&n; * is part of an IO brick.  The following function reads the WIDGET_ID&n; * register of the bridge under examination and returns a positive value&n; * if the part and mfg numbers stored there indicate that this widget&n; * is an XBridge (and so must be part of a brick).&n; */
macro_line|#ifdef LATER
r_int
id|is_iobrick
c_func
(paren
r_int
id|nasid
comma
r_int
id|widget_num
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* the following macro derives the widget number from the register&n; * address passed to it and uses is_iobrick to determine whether&n; * the widget in question is part of an SN1 IO brick.&n; */
DECL|macro|IS_IOBRICK
mdefine_line|#define IS_IOBRICK(rg)&t;is_iobrick( NASID_GET((rg)), SWIN_WIDGETNUM((rg)) )
multiline_comment|/* macros for NIC compatability */
multiline_comment|/* always invoked on &quot;this&quot; cbrick */
DECL|macro|HUB_VERTEX_MFG_INFO
mdefine_line|#define HUB_VERTEX_MFG_INFO(v) &bslash;&n;    eeprom_vertex_info_set( C_BRICK, get_nasid(), (v), 0 )
DECL|macro|BRIDGE_VERTEX_MFG_INFO
mdefine_line|#define BRIDGE_VERTEX_MFG_INFO(v, r) &bslash;&n;    ( IS_IOBRICK((r)) ? eeprom_vertex_info_set &bslash;&n;&t;&t;          ( IO_BRICK, NASID_GET((r)), (v), 0 ) &bslash;&n;&t;&t;      : nic_bridge_vertex_info((v), (r)) )
macro_line|#ifdef BRINGUP /* will we read mfg info from IOC3&squot;s that aren&squot;t&n;&t;&t;* part of IO7 cards, or aren&squot;t in I/O bricks? */
DECL|macro|IOC3_VERTEX_MFG_INFO
mdefine_line|#define IOC3_VERTEX_MFG_INFO(v, r, e) &bslash;&n;    eeprom_vertex_info_set( IO_IO7, NASID_GET((r)), (v), 0 )
macro_line|#endif /* BRINGUP */
DECL|macro|HUB_UID_GET
mdefine_line|#define HUB_UID_GET(n,v,p)&t;cbrick_uid_get((n),(p))
DECL|macro|ROUTER_UID_GET
mdefine_line|#define ROUTER_UID_GET(d,p)&t;rbrick_uid_get(get_nasid(),(d),(p))
DECL|macro|XBOW_UID_GET
mdefine_line|#define XBOW_UID_GET(n,p)&t;iobrick_uid_get((n),(p))
macro_line|#endif /* _ASM_SN_EEPROM_H */
eof
