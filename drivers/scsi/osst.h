multiline_comment|/*&n; *&t;$Header: /home/cvsroot/Driver/osst.h,v 1.11 2001/01/26 01:54:49 riede Exp $&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif
multiline_comment|/*&t;FIXME - rename and use the following two types or delete them!&n; *              and the types really should go to st.h anyway...&n; *&t;INQUIRY packet command - Data Format (From Table 6-8 of QIC-157C)&n; */
r_typedef
r_struct
(brace
DECL|member|device_type
r_int
id|device_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Peripheral Device Type */
DECL|member|reserved0_765
r_int
id|reserved0_765
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Peripheral Qualifier - Reserved */
DECL|member|reserved1_6t0
r_int
id|reserved1_6t0
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|rmb
r_int
id|rmb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Removable Medium Bit */
DECL|member|ansi_version
r_int
id|ansi_version
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* ANSI Version */
DECL|member|ecma_version
r_int
id|ecma_version
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* ECMA Version */
DECL|member|iso_version
r_int
id|iso_version
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* ISO Version */
DECL|member|response_format
r_int
id|response_format
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Response Data Format */
DECL|member|reserved3_45
r_int
id|reserved3_45
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|reserved3_6
r_int
id|reserved3_6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TrmIOP - Reserved */
DECL|member|reserved3_7
r_int
id|reserved3_7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* AENC - Reserved */
DECL|member|additional_length
id|u8
id|additional_length
suffix:semicolon
multiline_comment|/* Additional Length (total_length-4) */
DECL|member|rsv5
DECL|member|rsv6
DECL|member|rsv7
id|u8
id|rsv5
comma
id|rsv6
comma
id|rsv7
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|vendor_id
id|u8
id|vendor_id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Vendor Identification */
DECL|member|product_id
id|u8
id|product_id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Product Identification */
DECL|member|revision_level
id|u8
id|revision_level
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Revision Level */
DECL|member|vendor_specific
id|u8
id|vendor_specific
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Vendor Specific - Optional */
DECL|member|reserved56t95
id|u8
id|reserved56t95
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* Reserved - Optional */
multiline_comment|/* Additional information may be returned */
DECL|typedef|idetape_inquiry_result_t
)brace
id|idetape_inquiry_result_t
suffix:semicolon
multiline_comment|/*&n; *&t;READ POSITION packet command - Data Format (From Table 6-57)&n; */
r_typedef
r_struct
(brace
DECL|member|reserved0_10
r_int
id|reserved0_10
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|bpu
r_int
id|bpu
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Block Position Unknown */
DECL|member|reserved0_543
r_int
id|reserved0_543
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|eop
r_int
id|eop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* End Of Partition */
DECL|member|bop
r_int
id|bop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Beginning Of Partition */
DECL|member|partition
id|u8
id|partition
suffix:semicolon
multiline_comment|/* Partition Number */
DECL|member|reserved2
DECL|member|reserved3
id|u8
id|reserved2
comma
id|reserved3
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|first_block
id|u32
id|first_block
suffix:semicolon
multiline_comment|/* First Block Location */
DECL|member|last_block
id|u32
id|last_block
suffix:semicolon
multiline_comment|/* Last Block Location (Optional) */
DECL|member|reserved12
id|u8
id|reserved12
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|blocks_in_buffer
id|u8
id|blocks_in_buffer
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Blocks In Buffer - (Optional) */
DECL|member|bytes_in_buffer
id|u32
id|bytes_in_buffer
suffix:semicolon
multiline_comment|/* Bytes In Buffer (Optional) */
DECL|typedef|idetape_read_position_result_t
)brace
id|idetape_read_position_result_t
suffix:semicolon
multiline_comment|/*&n; *      Follows structures which are related to the SELECT SENSE / MODE SENSE&n; *      packet commands. &n; */
DECL|macro|COMPRESSION_PAGE
mdefine_line|#define COMPRESSION_PAGE           0x0f
DECL|macro|COMPRESSION_PAGE_LENGTH
mdefine_line|#define COMPRESSION_PAGE_LENGTH    16
DECL|macro|CAPABILITIES_PAGE
mdefine_line|#define CAPABILITIES_PAGE          0x2a
DECL|macro|CAPABILITIES_PAGE_LENGTH
mdefine_line|#define CAPABILITIES_PAGE_LENGTH   20
DECL|macro|TAPE_PARAMTR_PAGE
mdefine_line|#define TAPE_PARAMTR_PAGE          0x2b
DECL|macro|TAPE_PARAMTR_PAGE_LENGTH
mdefine_line|#define TAPE_PARAMTR_PAGE_LENGTH   16
DECL|macro|NUMBER_RETRIES_PAGE
mdefine_line|#define NUMBER_RETRIES_PAGE        0x2f
DECL|macro|NUMBER_RETRIES_PAGE_LENGTH
mdefine_line|#define NUMBER_RETRIES_PAGE_LENGTH 4
DECL|macro|BLOCK_SIZE_PAGE
mdefine_line|#define BLOCK_SIZE_PAGE            0x30
DECL|macro|BLOCK_SIZE_PAGE_LENGTH
mdefine_line|#define BLOCK_SIZE_PAGE_LENGTH     4
DECL|macro|BUFFER_FILLING_PAGE
mdefine_line|#define BUFFER_FILLING_PAGE        0x33
DECL|macro|BUFFER_FILLING_PAGE_LENGTH
mdefine_line|#define BUFFER_FILLING_PAGE_LENGTH 
DECL|macro|VENDOR_IDENT_PAGE
mdefine_line|#define VENDOR_IDENT_PAGE          0x36
DECL|macro|VENDOR_IDENT_PAGE_LENGTH
mdefine_line|#define VENDOR_IDENT_PAGE_LENGTH   8
DECL|macro|LOCATE_STATUS_PAGE
mdefine_line|#define LOCATE_STATUS_PAGE         0x37
DECL|macro|LOCATE_STATUS_PAGE_LENGTH
mdefine_line|#define LOCATE_STATUS_PAGE_LENGTH  0
DECL|macro|MODE_HEADER_LENGTH
mdefine_line|#define MODE_HEADER_LENGTH         4
multiline_comment|/*&n; *&t;REQUEST SENSE packet command result - Data Format.&n; */
r_typedef
r_struct
(brace
DECL|member|error_code
r_int
id|error_code
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Current of deferred errors */
DECL|member|valid
r_int
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The information field conforms to QIC-157C */
DECL|member|reserved1
id|u8
id|reserved1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Segment Number - Reserved */
DECL|member|sense_key
r_int
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Sense Key */
DECL|member|reserved2_4
r_int
id|reserved2_4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ili
r_int
id|ili
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Incorrect Length Indicator */
DECL|member|eom
r_int
id|eom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* End Of Medium */
DECL|member|filemark
r_int
id|filemark
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Filemark */
DECL|member|information
id|u32
id|information
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|asl
id|u8
id|asl
suffix:semicolon
multiline_comment|/* Additional sense length (n-7) */
DECL|member|command_specific
id|u32
id|command_specific
suffix:semicolon
multiline_comment|/* Additional command specific information */
DECL|member|asc
id|u8
id|asc
suffix:semicolon
multiline_comment|/* Additional Sense Code */
DECL|member|ascq
id|u8
id|ascq
suffix:semicolon
multiline_comment|/* Additional Sense Code Qualifier */
DECL|member|replaceable_unit_code
id|u8
id|replaceable_unit_code
suffix:semicolon
multiline_comment|/* Field Replaceable Unit Code */
DECL|member|sk_specific1
r_int
id|sk_specific1
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Sense Key Specific */
DECL|member|sksv
r_int
id|sksv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sense Key Specific information is valid */
DECL|member|sk_specific2
id|u8
id|sk_specific2
suffix:semicolon
multiline_comment|/* Sense Key Specific */
DECL|member|sk_specific3
id|u8
id|sk_specific3
suffix:semicolon
multiline_comment|/* Sense Key Specific */
DECL|member|pad
id|u8
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Padding to 20 bytes */
DECL|typedef|idetape_request_sense_result_t
)brace
id|idetape_request_sense_result_t
suffix:semicolon
multiline_comment|/*&n; *      Mode Parameter Header for the MODE SENSE packet command&n; */
r_typedef
r_struct
(brace
DECL|member|mode_data_length
id|u8
id|mode_data_length
suffix:semicolon
multiline_comment|/* Length of the following data transfer */
DECL|member|medium_type
id|u8
id|medium_type
suffix:semicolon
multiline_comment|/* Medium Type */
DECL|member|dsp
id|u8
id|dsp
suffix:semicolon
multiline_comment|/* Device Specific Parameter */
DECL|member|bdl
id|u8
id|bdl
suffix:semicolon
multiline_comment|/* Block Descriptor Length */
DECL|typedef|osst_mode_parameter_header_t
)brace
id|osst_mode_parameter_header_t
suffix:semicolon
multiline_comment|/*&n; *      Mode Parameter Block Descriptor the MODE SENSE packet command&n; *&n; *      Support for block descriptors is optional.&n; */
r_typedef
r_struct
(brace
DECL|member|density_code
id|u8
id|density_code
suffix:semicolon
multiline_comment|/* Medium density code */
DECL|member|blocks
id|u8
id|blocks
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Number of blocks */
DECL|member|reserved4
id|u8
id|reserved4
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|length
id|u8
id|length
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Block Length */
DECL|typedef|osst_parameter_block_descriptor_t
)brace
id|osst_parameter_block_descriptor_t
suffix:semicolon
multiline_comment|/*&n; *      The Data Compression Page, as returned by the MODE SENSE packet command.&n; */
r_typedef
r_struct
(brace
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|ps
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved0
r_int
id|reserved0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|page_code
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code - Should be 0xf */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code - Should be 0xf */
r_int
id|reserved0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|page_length
id|u8
id|page_length
suffix:semicolon
multiline_comment|/* Page Length - Should be 14 */
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|dce
r_int
id|dce
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data Compression Enable */
DECL|member|dcc
r_int
id|dcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data Compression Capable */
DECL|member|reserved2
r_int
id|reserved2
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Reserved */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved2
r_int
id|reserved2
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|dcc
r_int
id|dcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data Compression Capable */
DECL|member|dce
r_int
id|dce
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data Compression Enable */
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|dde
r_int
id|dde
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data Decompression Enable */
DECL|member|red
r_int
id|red
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Report Exception on Decompression */
DECL|member|reserved3
r_int
id|reserved3
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Reserved */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved3
r_int
id|reserved3
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|red
r_int
id|red
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Report Exception on Decompression */
DECL|member|dde
r_int
id|dde
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data Decompression Enable */
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|ca
id|u32
id|ca
suffix:semicolon
multiline_comment|/* Compression Algorithm */
DECL|member|da
id|u32
id|da
suffix:semicolon
multiline_comment|/* Decompression Algorithm */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Reserved */
DECL|typedef|osst_data_compression_page_t
)brace
id|osst_data_compression_page_t
suffix:semicolon
multiline_comment|/*&n; *      The Medium Partition Page, as returned by the MODE SENSE packet command.&n; */
r_typedef
r_struct
(brace
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|ps
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1_6
r_int
id|reserved1_6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|page_code
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code - Should be 0x11 */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code - Should be 0x11 */
r_int
id|reserved1_6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|page_length
id|u8
id|page_length
suffix:semicolon
multiline_comment|/* Page Length - Should be 6 */
DECL|member|map
id|u8
id|map
suffix:semicolon
multiline_comment|/* Maximum Additional Partitions - Should be 0 */
DECL|member|apd
id|u8
id|apd
suffix:semicolon
multiline_comment|/* Additional Partitions Defined - Should be 0 */
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|fdp
r_int
id|fdp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Fixed Data Partitions */
DECL|member|sdp
r_int
id|sdp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be 0 */
DECL|member|idp
r_int
id|idp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be 0 */
DECL|member|psum
r_int
id|psum
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Should be 0 */
DECL|member|reserved4_012
r_int
id|reserved4_012
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Reserved */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved4_012
r_int
id|reserved4_012
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|psum
r_int
id|psum
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Should be 0 */
DECL|member|idp
r_int
id|idp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be 0 */
DECL|member|sdp
r_int
id|sdp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should be 0 */
DECL|member|fdp
r_int
id|fdp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Fixed Data Partitions */
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|mfr
id|u8
id|mfr
suffix:semicolon
multiline_comment|/* Medium Format Recognition */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved */
DECL|typedef|osst_medium_partition_page_t
)brace
id|osst_medium_partition_page_t
suffix:semicolon
multiline_comment|/*&n; *      Capabilities and Mechanical Status Page&n; */
r_typedef
r_struct
(brace
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved1_67
r_int
id|reserved1_67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|page_code
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x2a */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x2a */
r_int
id|reserved1_67
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|page_length
id|u8
id|page_length
suffix:semicolon
multiline_comment|/* Page Length - Should be 0x12 */
DECL|member|reserved2
DECL|member|reserved3
id|u8
id|reserved2
comma
id|reserved3
suffix:semicolon
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved4_67
r_int
id|reserved4_67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|sprev
r_int
id|sprev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports SPACE in the reverse direction */
DECL|member|reserved4_1234
r_int
id|reserved4_1234
suffix:colon
l_int|4
suffix:semicolon
DECL|member|ro
r_int
id|ro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Read Only Mode */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|ro
r_int
id|ro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Read Only Mode */
DECL|member|reserved4_1234
r_int
id|reserved4_1234
suffix:colon
l_int|4
suffix:semicolon
DECL|member|sprev
r_int
id|sprev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports SPACE in the reverse direction */
DECL|member|reserved4_67
r_int
id|reserved4_67
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved5_67
r_int
id|reserved5_67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|qfa
r_int
id|qfa
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports the QFA two partition formats */
DECL|member|reserved5_4
r_int
id|reserved5_4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|efmt
r_int
id|efmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports ERASE command initiated formatting */
DECL|member|reserved5_012
r_int
id|reserved5_012
suffix:colon
l_int|3
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved5_012
r_int
id|reserved5_012
suffix:colon
l_int|3
suffix:semicolon
DECL|member|efmt
r_int
id|efmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports ERASE command initiated formatting */
DECL|member|reserved5_4
r_int
id|reserved5_4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|qfa
r_int
id|qfa
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports the QFA two partition formats */
DECL|member|reserved5_67
r_int
id|reserved5_67
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|cmprs
r_int
id|cmprs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports data compression */
DECL|member|ecc
r_int
id|ecc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports error correction */
DECL|member|reserved6_45
r_int
id|reserved6_45
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|eject
r_int
id|eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device can eject the volume */
DECL|member|prevent
r_int
id|prevent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device defaults in the prevent state after power up */
DECL|member|locked
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The volume is locked */
DECL|member|lock
r_int
id|lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports locking the volume */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|lock
r_int
id|lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports locking the volume */
DECL|member|locked
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The volume is locked */
DECL|member|prevent
r_int
id|prevent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device defaults in the prevent state after power up */
DECL|member|eject
r_int
id|eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device can eject the volume */
DECL|member|reserved6_45
r_int
id|reserved6_45
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ecc
r_int
id|ecc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports error correction */
DECL|member|cmprs
r_int
id|cmprs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports data compression */
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|blk32768
r_int
id|blk32768
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* slowb - the device restricts the byte count for PIO */
multiline_comment|/* transfers for slow buffer memory ??? */
multiline_comment|/* Also 32768 block size in some cases */
DECL|member|reserved7_3_6
r_int
id|reserved7_3_6
suffix:colon
l_int|4
suffix:semicolon
DECL|member|blk1024
r_int
id|blk1024
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports 1024 bytes block size */
DECL|member|blk512
r_int
id|blk512
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports 512 bytes block size */
DECL|member|reserved7_0
r_int
id|reserved7_0
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved7_0
r_int
id|reserved7_0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|blk512
r_int
id|blk512
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports 512 bytes block size */
DECL|member|blk1024
r_int
id|blk1024
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports 1024 bytes block size */
DECL|member|reserved7_3_6
r_int
id|reserved7_3_6
suffix:colon
l_int|4
suffix:semicolon
DECL|member|blk32768
r_int
id|blk32768
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* slowb - the device restricts the byte count for PIO */
multiline_comment|/* transfers for slow buffer memory ??? */
multiline_comment|/* Also 32768 block size in some cases */
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|max_speed
id|u16
id|max_speed
suffix:semicolon
multiline_comment|/* Maximum speed supported in KBps */
DECL|member|reserved10
DECL|member|reserved11
id|u8
id|reserved10
comma
id|reserved11
suffix:semicolon
DECL|member|ctl
id|u16
id|ctl
suffix:semicolon
multiline_comment|/* Continuous Transfer Limit in blocks */
DECL|member|speed
id|u16
id|speed
suffix:semicolon
multiline_comment|/* Current Speed, in KBps */
DECL|member|buffer_size
id|u16
id|buffer_size
suffix:semicolon
multiline_comment|/* Buffer Size, in 512 bytes */
DECL|member|reserved18
DECL|member|reserved19
id|u8
id|reserved18
comma
id|reserved19
suffix:semicolon
DECL|typedef|osst_capabilities_page_t
)brace
id|osst_capabilities_page_t
suffix:semicolon
multiline_comment|/*&n; *      Block Size Page&n; */
r_typedef
r_struct
(brace
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|ps
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1_6
r_int
id|reserved1_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_code
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x30 */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x30 */
r_int
id|reserved1_6
suffix:colon
l_int|1
suffix:semicolon
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|page_length
id|u8
id|page_length
suffix:semicolon
multiline_comment|/* Page Length - Should be 2 */
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|one
r_int
id|one
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2_6
r_int
id|reserved2_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|record32_5
r_int
id|record32_5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|record32
r_int
id|record32
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2_23
r_int
id|reserved2_23
suffix:colon
l_int|2
suffix:semicolon
DECL|member|play32_5
r_int
id|play32_5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|play32
r_int
id|play32
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|play32
r_int
id|play32
suffix:colon
l_int|1
suffix:semicolon
DECL|member|play32_5
r_int
id|play32_5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2_23
r_int
id|reserved2_23
suffix:colon
l_int|2
suffix:semicolon
DECL|member|record32
r_int
id|record32
suffix:colon
l_int|1
suffix:semicolon
DECL|member|record32_5
r_int
id|record32_5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2_6
r_int
id|reserved2_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|one
r_int
id|one
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|typedef|osst_block_size_page_t
)brace
id|osst_block_size_page_t
suffix:semicolon
multiline_comment|/*&n; *&t;Tape Parameters Page&n; */
r_typedef
r_struct
(brace
macro_line|#if   defined(__BIG_ENDIAN_BITFIELD)
DECL|member|ps
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1_6
r_int
id|reserved1_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_code
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x2b */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x2b */
r_int
id|reserved1_6
suffix:colon
l_int|1
suffix:semicolon
r_int
id|ps
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|density
id|u8
id|density
suffix:semicolon
DECL|member|reserved3
DECL|member|reserved4
id|u8
id|reserved3
comma
id|reserved4
suffix:semicolon
DECL|member|segtrk
id|u16
id|segtrk
suffix:semicolon
DECL|member|trks
id|u16
id|trks
suffix:semicolon
DECL|member|reserved5
DECL|member|reserved6
DECL|member|reserved7
DECL|member|reserved8
DECL|member|reserved9
DECL|member|reserved10
id|u8
id|reserved5
comma
id|reserved6
comma
id|reserved7
comma
id|reserved8
comma
id|reserved9
comma
id|reserved10
suffix:semicolon
DECL|typedef|osst_tape_paramtr_page_t
)brace
id|osst_tape_paramtr_page_t
suffix:semicolon
multiline_comment|/* OnStream definitions */
DECL|macro|OS_CONFIG_PARTITION
mdefine_line|#define OS_CONFIG_PARTITION     (0xff)
DECL|macro|OS_DATA_PARTITION
mdefine_line|#define OS_DATA_PARTITION       (0)
DECL|macro|OS_PARTITION_VERSION
mdefine_line|#define OS_PARTITION_VERSION    (1)
multiline_comment|/*&n; * partition&n; */
DECL|struct|os_partition_s
r_typedef
r_struct
id|os_partition_s
(brace
DECL|member|partition_num
id|__u8
id|partition_num
suffix:semicolon
DECL|member|par_desc_ver
id|__u8
id|par_desc_ver
suffix:semicolon
DECL|member|wrt_pass_cntr
id|__u16
id|wrt_pass_cntr
suffix:semicolon
DECL|member|first_frame_ppos
id|__u32
id|first_frame_ppos
suffix:semicolon
DECL|member|last_frame_ppos
id|__u32
id|last_frame_ppos
suffix:semicolon
DECL|member|eod_frame_ppos
id|__u32
id|eod_frame_ppos
suffix:semicolon
DECL|typedef|os_partition_t
)brace
id|os_partition_t
suffix:semicolon
multiline_comment|/*&n; * DAT entry&n; */
DECL|struct|os_dat_entry_s
r_typedef
r_struct
id|os_dat_entry_s
(brace
DECL|member|blk_sz
id|__u32
id|blk_sz
suffix:semicolon
DECL|member|blk_cnt
id|__u16
id|blk_cnt
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
DECL|typedef|os_dat_entry_t
)brace
id|os_dat_entry_t
suffix:semicolon
multiline_comment|/*&n; * DAT&n; */
DECL|macro|OS_DAT_FLAGS_DATA
mdefine_line|#define OS_DAT_FLAGS_DATA       (0xc)
DECL|macro|OS_DAT_FLAGS_MARK
mdefine_line|#define OS_DAT_FLAGS_MARK       (0x1)
DECL|struct|os_dat_s
r_typedef
r_struct
id|os_dat_s
(brace
DECL|member|dat_sz
id|__u8
id|dat_sz
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|entry_cnt
id|__u8
id|entry_cnt
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|member|dat_list
id|os_dat_entry_t
id|dat_list
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|os_dat_t
)brace
id|os_dat_t
suffix:semicolon
multiline_comment|/*&n; * Frame types&n; */
DECL|macro|OS_FRAME_TYPE_FILL
mdefine_line|#define OS_FRAME_TYPE_FILL      (0)
DECL|macro|OS_FRAME_TYPE_EOD
mdefine_line|#define OS_FRAME_TYPE_EOD       (1 &lt;&lt; 0)
DECL|macro|OS_FRAME_TYPE_MARKER
mdefine_line|#define OS_FRAME_TYPE_MARKER    (1 &lt;&lt; 1)
DECL|macro|OS_FRAME_TYPE_HEADER
mdefine_line|#define OS_FRAME_TYPE_HEADER    (1 &lt;&lt; 3)
DECL|macro|OS_FRAME_TYPE_DATA
mdefine_line|#define OS_FRAME_TYPE_DATA      (1 &lt;&lt; 7)
multiline_comment|/*&n; * AUX&n; */
DECL|struct|os_aux_s
r_typedef
r_struct
id|os_aux_s
(brace
DECL|member|format_id
id|__u32
id|format_id
suffix:semicolon
multiline_comment|/* hardware compability AUX is based on */
DECL|member|application_sig
r_char
id|application_sig
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* driver used to write this media */
DECL|member|hdwr
id|__u32
id|hdwr
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|update_frame_cntr
id|__u32
id|update_frame_cntr
suffix:semicolon
multiline_comment|/* for configuration frame */
DECL|member|frame_type
id|__u8
id|frame_type
suffix:semicolon
DECL|member|frame_type_reserved
id|__u8
id|frame_type_reserved
suffix:semicolon
DECL|member|reserved_18_19
id|__u8
id|reserved_18_19
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|partition
id|os_partition_t
id|partition
suffix:semicolon
DECL|member|reserved_36_43
id|__u8
id|reserved_36_43
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|frame_seq_num
id|__u32
id|frame_seq_num
suffix:semicolon
DECL|member|logical_blk_num_high
id|__u32
id|logical_blk_num_high
suffix:semicolon
DECL|member|logical_blk_num
id|__u32
id|logical_blk_num
suffix:semicolon
DECL|member|dat
id|os_dat_t
id|dat
suffix:semicolon
DECL|member|reserved188_191
id|__u8
id|reserved188_191
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|filemark_cnt
id|__u32
id|filemark_cnt
suffix:semicolon
DECL|member|phys_fm
id|__u32
id|phys_fm
suffix:semicolon
DECL|member|last_mark_ppos
id|__u32
id|last_mark_ppos
suffix:semicolon
DECL|member|reserved204_223
id|__u8
id|reserved204_223
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/*&n;         * __u8         app_specific[32];&n;         *&n;         * Linux specific fields:&n;         */
DECL|member|next_mark_ppos
id|__u32
id|next_mark_ppos
suffix:semicolon
multiline_comment|/* when known, points to next marker */
DECL|member|last_mark_lbn
id|__u32
id|last_mark_lbn
suffix:semicolon
multiline_comment|/* storing log_blk_num of last mark is extends ADR spec */
DECL|member|linux_specific
id|__u8
id|linux_specific
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|reserved_256_511
id|__u8
id|reserved_256_511
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|os_aux_t
)brace
id|os_aux_t
suffix:semicolon
DECL|macro|OS_FM_TAB_MAX
mdefine_line|#define OS_FM_TAB_MAX 1024
DECL|struct|os_fm_tab_s
r_typedef
r_struct
id|os_fm_tab_s
(brace
DECL|member|fm_part_num
id|__u8
id|fm_part_num
suffix:semicolon
DECL|member|reserved_1
id|__u8
id|reserved_1
suffix:semicolon
DECL|member|fm_tab_ent_sz
id|__u8
id|fm_tab_ent_sz
suffix:semicolon
DECL|member|reserved_3
id|__u8
id|reserved_3
suffix:semicolon
DECL|member|fm_tab_ent_cnt
id|__u16
id|fm_tab_ent_cnt
suffix:semicolon
DECL|member|reserved6_15
id|__u8
id|reserved6_15
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|fm_tab_ent
id|__u32
id|fm_tab_ent
(braket
id|OS_FM_TAB_MAX
)braket
suffix:semicolon
DECL|typedef|os_fm_tab_t
)brace
id|os_fm_tab_t
suffix:semicolon
DECL|struct|os_ext_trk_ey_s
r_typedef
r_struct
id|os_ext_trk_ey_s
(brace
DECL|member|et_part_num
id|__u8
id|et_part_num
suffix:semicolon
DECL|member|fmt
id|__u8
id|fmt
suffix:semicolon
DECL|member|fm_tab_off
id|__u16
id|fm_tab_off
suffix:semicolon
DECL|member|reserved4_7
id|__u8
id|reserved4_7
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|last_hlb_hi
id|__u32
id|last_hlb_hi
suffix:semicolon
DECL|member|last_hlb
id|__u32
id|last_hlb
suffix:semicolon
DECL|member|last_pp
id|__u32
id|last_pp
suffix:semicolon
DECL|member|reserved20_31
id|__u8
id|reserved20_31
(braket
l_int|12
)braket
suffix:semicolon
DECL|typedef|os_ext_trk_ey_t
)brace
id|os_ext_trk_ey_t
suffix:semicolon
DECL|struct|os_ext_trk_tb_s
r_typedef
r_struct
id|os_ext_trk_tb_s
(brace
DECL|member|nr_stream_part
id|__u8
id|nr_stream_part
suffix:semicolon
DECL|member|reserved_1
id|__u8
id|reserved_1
suffix:semicolon
DECL|member|et_ent_sz
id|__u8
id|et_ent_sz
suffix:semicolon
DECL|member|reserved3_15
id|__u8
id|reserved3_15
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|dat_ext_trk_ey
id|os_ext_trk_ey_t
id|dat_ext_trk_ey
suffix:semicolon
DECL|member|qfa_ext_trk_ey
id|os_ext_trk_ey_t
id|qfa_ext_trk_ey
suffix:semicolon
DECL|typedef|os_ext_trk_tb_t
)brace
id|os_ext_trk_tb_t
suffix:semicolon
DECL|struct|os_header_s
r_typedef
r_struct
id|os_header_s
(brace
DECL|member|ident_str
r_char
id|ident_str
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|major_rev
id|__u8
id|major_rev
suffix:semicolon
DECL|member|minor_rev
id|__u8
id|minor_rev
suffix:semicolon
DECL|member|ext_trk_tb_off
id|__u16
id|ext_trk_tb_off
suffix:semicolon
DECL|member|reserved12_15
id|__u8
id|reserved12_15
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pt_par_num
id|__u8
id|pt_par_num
suffix:semicolon
DECL|member|pt_reserved1_3
id|__u8
id|pt_reserved1_3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|partition
id|os_partition_t
id|partition
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cfg_col_width
id|__u32
id|cfg_col_width
suffix:semicolon
DECL|member|dat_col_width
id|__u32
id|dat_col_width
suffix:semicolon
DECL|member|qfa_col_width
id|__u32
id|qfa_col_width
suffix:semicolon
DECL|member|cartridge
id|__u8
id|cartridge
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|reserved304_511
id|__u8
id|reserved304_511
(braket
l_int|208
)braket
suffix:semicolon
DECL|member|old_filemark_list
id|__u32
id|old_filemark_list
(braket
l_int|16680
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* in ADR 1.4 __u8 track_table[16680] */
DECL|member|ext_track_tb
id|os_ext_trk_tb_t
id|ext_track_tb
suffix:semicolon
DECL|member|reserved17272_17735
id|__u8
id|reserved17272_17735
(braket
l_int|464
)braket
suffix:semicolon
DECL|member|dat_fm_tab
id|os_fm_tab_t
id|dat_fm_tab
suffix:semicolon
DECL|member|qfa_fm_tab
id|os_fm_tab_t
id|qfa_fm_tab
suffix:semicolon
DECL|member|reserved25960_32767
id|__u8
id|reserved25960_32767
(braket
l_int|6808
)braket
suffix:semicolon
DECL|typedef|os_header_t
)brace
id|os_header_t
suffix:semicolon
multiline_comment|/*&n; * OnStream ADRL frame&n; */
DECL|macro|OS_FRAME_SIZE
mdefine_line|#define OS_FRAME_SIZE   (32 * 1024 + 512)
DECL|macro|OS_DATA_SIZE
mdefine_line|#define OS_DATA_SIZE    (32 * 1024)
DECL|macro|OS_AUX_SIZE
mdefine_line|#define OS_AUX_SIZE     (512)
singleline_comment|//#define OSST_MAX_SG      2
multiline_comment|/* The tape buffer descriptor. */
r_typedef
r_struct
(brace
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
DECL|member|dma
r_int
r_char
id|dma
suffix:semicolon
multiline_comment|/* DMA-able buffer */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
DECL|member|buffer_blocks
r_int
id|buffer_blocks
suffix:semicolon
DECL|member|buffer_bytes
r_int
id|buffer_bytes
suffix:semicolon
DECL|member|read_pointer
r_int
id|read_pointer
suffix:semicolon
DECL|member|writing
r_int
id|writing
suffix:semicolon
DECL|member|midlevel_result
r_int
id|midlevel_result
suffix:semicolon
DECL|member|syscall_result
r_int
id|syscall_result
suffix:semicolon
DECL|member|last_SRpnt
id|Scsi_Request
op_star
id|last_SRpnt
suffix:semicolon
DECL|member|b_data
r_int
r_char
op_star
id|b_data
suffix:semicolon
DECL|member|aux
id|os_aux_t
op_star
id|aux
suffix:semicolon
multiline_comment|/* onstream AUX structure at end of each block */
DECL|member|use_sg
r_int
r_int
id|use_sg
suffix:semicolon
multiline_comment|/* zero or number of segments for this adapter */
DECL|member|sg_segs
r_int
r_int
id|sg_segs
suffix:semicolon
multiline_comment|/* total number of allocated segments */
DECL|member|orig_sg_segs
r_int
r_int
id|orig_sg_segs
suffix:semicolon
multiline_comment|/* number of segments allocated at first try */
DECL|member|sg
r_struct
id|scatterlist
id|sg
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* MUST BE last item */
DECL|typedef|OSST_buffer
)brace
id|OSST_buffer
suffix:semicolon
multiline_comment|/* The tape drive descriptor */
r_typedef
r_struct
(brace
DECL|member|devt
id|kdev_t
id|devt
suffix:semicolon
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* for serialization */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* for SCSI commands */
DECL|member|buffer
id|OSST_buffer
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Drive characteristics */
DECL|member|omit_blklims
r_int
r_char
id|omit_blklims
suffix:semicolon
DECL|member|do_auto_lock
r_int
r_char
id|do_auto_lock
suffix:semicolon
DECL|member|can_bsr
r_int
r_char
id|can_bsr
suffix:semicolon
DECL|member|can_partitions
r_int
r_char
id|can_partitions
suffix:semicolon
DECL|member|two_fm
r_int
r_char
id|two_fm
suffix:semicolon
DECL|member|fast_mteom
r_int
r_char
id|fast_mteom
suffix:semicolon
DECL|member|restr_dma
r_int
r_char
id|restr_dma
suffix:semicolon
DECL|member|scsi2_logical
r_int
r_char
id|scsi2_logical
suffix:semicolon
DECL|member|default_drvbuffer
r_int
r_char
id|default_drvbuffer
suffix:semicolon
multiline_comment|/* 0xff = don&squot;t touch, value 3 bits */
DECL|member|write_threshold
r_int
id|write_threshold
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout for normal commands */
DECL|member|long_timeout
r_int
id|long_timeout
suffix:semicolon
multiline_comment|/* timeout for commands known to take long time*/
multiline_comment|/* Mode characteristics */
DECL|member|modes
id|ST_mode
id|modes
(braket
id|ST_NBR_MODES
)braket
suffix:semicolon
DECL|member|current_mode
r_int
id|current_mode
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|member|de_r
id|devfs_handle_t
id|de_r
(braket
id|ST_NBR_MODES
)braket
suffix:semicolon
multiline_comment|/*  Rewind entries     */
DECL|member|de_n
id|devfs_handle_t
id|de_n
(braket
id|ST_NBR_MODES
)braket
suffix:semicolon
multiline_comment|/*  No-rewind entries  */
macro_line|#endif
multiline_comment|/* Status variables */
DECL|member|partition
r_int
id|partition
suffix:semicolon
DECL|member|new_partition
r_int
id|new_partition
suffix:semicolon
DECL|member|nbr_partitions
r_int
id|nbr_partitions
suffix:semicolon
multiline_comment|/* zero until partition support enabled */
DECL|member|ps
id|ST_partstat
id|ps
(braket
id|ST_NBR_PARTITIONS
)braket
suffix:semicolon
DECL|member|dirty
r_int
r_char
id|dirty
suffix:semicolon
DECL|member|ready
r_int
r_char
id|ready
suffix:semicolon
DECL|member|write_prot
r_int
r_char
id|write_prot
suffix:semicolon
DECL|member|drv_write_prot
r_int
r_char
id|drv_write_prot
suffix:semicolon
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
DECL|member|blksize_changed
r_int
r_char
id|blksize_changed
suffix:semicolon
DECL|member|density_changed
r_int
r_char
id|density_changed
suffix:semicolon
DECL|member|compression_changed
r_int
r_char
id|compression_changed
suffix:semicolon
DECL|member|drv_buffer
r_int
r_char
id|drv_buffer
suffix:semicolon
DECL|member|density
r_int
r_char
id|density
suffix:semicolon
DECL|member|door_locked
r_int
r_char
id|door_locked
suffix:semicolon
DECL|member|rew_at_close
r_int
r_char
id|rew_at_close
suffix:semicolon
DECL|member|inited
r_int
r_char
id|inited
suffix:semicolon
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
DECL|member|min_block
r_int
id|min_block
suffix:semicolon
DECL|member|max_block
r_int
id|max_block
suffix:semicolon
DECL|member|recover_count
r_int
id|recover_count
suffix:semicolon
multiline_comment|/* from tape opening */
DECL|member|write_count
r_int
id|write_count
suffix:semicolon
DECL|member|read_count
r_int
id|read_count
suffix:semicolon
DECL|member|recover_erreg
r_int
id|recover_erreg
suffix:semicolon
multiline_comment|/* from last status call */
multiline_comment|/*&n;   * OnStream specific data&n;   */
DECL|member|os_fw_rev
r_int
id|os_fw_rev
suffix:semicolon
multiline_comment|/* the firmware revision * 10000 */
DECL|member|raw
r_int
r_char
id|raw
suffix:semicolon
multiline_comment|/* flag OnStream raw access (32.5KB block size) */
DECL|member|poll
r_int
r_char
id|poll
suffix:semicolon
multiline_comment|/* flag that this drive needs polling (IDE|firmware) */
DECL|member|frame_in_buffer
r_int
r_char
id|frame_in_buffer
suffix:semicolon
multiline_comment|/* flag that the frame as per frame_seq_number&n;&t;&t;&t;&t;&t;&t;* has been read into STp-&gt;buffer and is valid */
DECL|member|frame_seq_number
r_int
id|frame_seq_number
suffix:semicolon
multiline_comment|/* logical frame number */
DECL|member|logical_blk_num
r_int
id|logical_blk_num
suffix:semicolon
multiline_comment|/* logical block number */
DECL|member|first_frame_position
r_int
id|first_frame_position
suffix:semicolon
multiline_comment|/* physical frame to be transfered to/from host */
DECL|member|last_frame_position
r_int
id|last_frame_position
suffix:semicolon
multiline_comment|/* physical frame to be transferd to/from tape */
DECL|member|cur_frames
r_int
id|cur_frames
suffix:semicolon
multiline_comment|/* current number of frames in internal buffer */
DECL|member|max_frames
r_int
id|max_frames
suffix:semicolon
multiline_comment|/* max number of frames in internal buffer */
DECL|member|application_sig
r_char
id|application_sig
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* application signature */
DECL|member|fast_open
r_int
r_char
id|fast_open
suffix:semicolon
multiline_comment|/* flag that reminds us we didn&squot;t check headers at open */
DECL|member|wrt_pass_cntr
r_int
r_int
id|wrt_pass_cntr
suffix:semicolon
multiline_comment|/* write pass counter */
DECL|member|update_frame_cntr
r_int
id|update_frame_cntr
suffix:semicolon
multiline_comment|/* update frame counter */
DECL|member|onstream_write_error
r_int
id|onstream_write_error
suffix:semicolon
multiline_comment|/* write error recovery active */
DECL|member|header_ok
r_int
id|header_ok
suffix:semicolon
multiline_comment|/* header frame verified ok */
DECL|member|linux_media
r_int
id|linux_media
suffix:semicolon
multiline_comment|/* reading linux-specifc media */
DECL|member|linux_media_version
r_int
id|linux_media_version
suffix:semicolon
DECL|member|header_cache
id|os_header_t
op_star
id|header_cache
suffix:semicolon
multiline_comment|/* cache is kept for filemark positions */
DECL|member|filemark_cnt
r_int
id|filemark_cnt
suffix:semicolon
DECL|member|first_mark_ppos
r_int
id|first_mark_ppos
suffix:semicolon
DECL|member|last_mark_ppos
r_int
id|last_mark_ppos
suffix:semicolon
DECL|member|last_mark_lbn
r_int
id|last_mark_lbn
suffix:semicolon
multiline_comment|/* storing log_blk_num of last mark is extends ADR spec */
DECL|member|first_data_ppos
r_int
id|first_data_ppos
suffix:semicolon
DECL|member|eod_frame_ppos
r_int
id|eod_frame_ppos
suffix:semicolon
DECL|member|eod_frame_lfa
r_int
id|eod_frame_lfa
suffix:semicolon
DECL|member|write_type
r_int
id|write_type
suffix:semicolon
multiline_comment|/* used in write error recovery */
DECL|member|read_error_frame
r_int
id|read_error_frame
suffix:semicolon
multiline_comment|/* used in read error recovery */
DECL|member|cmd_start_time
r_int
r_int
id|cmd_start_time
suffix:semicolon
DECL|member|max_cmd_time
r_int
r_int
id|max_cmd_time
suffix:semicolon
macro_line|#if DEBUG
DECL|member|write_pending
r_int
r_char
id|write_pending
suffix:semicolon
DECL|member|nbr_finished
r_int
id|nbr_finished
suffix:semicolon
DECL|member|nbr_waits
r_int
id|nbr_waits
suffix:semicolon
DECL|member|last_cmnd
r_int
r_char
id|last_cmnd
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|last_sense
r_int
r_char
id|last_sense
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|OS_Scsi_Tape
)brace
id|OS_Scsi_Tape
suffix:semicolon
multiline_comment|/* Values of write_type */
DECL|macro|OS_WRITE_DATA
mdefine_line|#define OS_WRITE_DATA      0
DECL|macro|OS_WRITE_EOD
mdefine_line|#define OS_WRITE_EOD       1
DECL|macro|OS_WRITE_NEW_MARK
mdefine_line|#define OS_WRITE_NEW_MARK  2
DECL|macro|OS_WRITE_LAST_MARK
mdefine_line|#define OS_WRITE_LAST_MARK 3
DECL|macro|OS_WRITE_HEADER
mdefine_line|#define OS_WRITE_HEADER    4
DECL|macro|OS_WRITE_FILLER
mdefine_line|#define OS_WRITE_FILLER    5
eof
