macro_line|#ifndef DASD_ECKD_H
DECL|macro|DASD_ECKD_H
mdefine_line|#define DASD_ECKD_H
multiline_comment|/*******************************************************************************&n; * SECTION: CCW Definitions&n; ******************************************************************************/
DECL|macro|DASD_ECKD_CCW_WRITE
mdefine_line|#define DASD_ECKD_CCW_WRITE&t;&t; 0x05
DECL|macro|DASD_ECKD_CCW_READ
mdefine_line|#define DASD_ECKD_CCW_READ&t;&t; 0x06
DECL|macro|DASD_ECKD_CCW_WRITE_HOME_ADDRESS
mdefine_line|#define DASD_ECKD_CCW_WRITE_HOME_ADDRESS 0x09
DECL|macro|DASD_ECKD_CCW_READ_HOME_ADDRESS
mdefine_line|#define DASD_ECKD_CCW_READ_HOME_ADDRESS&t; 0x0a
DECL|macro|DASD_ECKD_CCW_WRITE_KD
mdefine_line|#define DASD_ECKD_CCW_WRITE_KD&t;&t; 0x0d
DECL|macro|DASD_ECKD_CCW_READ_KD
mdefine_line|#define DASD_ECKD_CCW_READ_KD&t;&t; 0x0e
DECL|macro|DASD_ECKD_CCW_ERASE
mdefine_line|#define DASD_ECKD_CCW_ERASE&t;&t; 0x11
DECL|macro|DASD_ECKD_CCW_READ_COUNT
mdefine_line|#define DASD_ECKD_CCW_READ_COUNT&t; 0x12
DECL|macro|DASD_ECKD_CCW_SLCK
mdefine_line|#define DASD_ECKD_CCW_SLCK&t;&t; 0x14
DECL|macro|DASD_ECKD_CCW_WRITE_RECORD_ZERO
mdefine_line|#define DASD_ECKD_CCW_WRITE_RECORD_ZERO&t; 0x15
DECL|macro|DASD_ECKD_CCW_READ_RECORD_ZERO
mdefine_line|#define DASD_ECKD_CCW_READ_RECORD_ZERO&t; 0x16
DECL|macro|DASD_ECKD_CCW_WRITE_CKD
mdefine_line|#define DASD_ECKD_CCW_WRITE_CKD&t;&t; 0x1d
DECL|macro|DASD_ECKD_CCW_READ_CKD
mdefine_line|#define DASD_ECKD_CCW_READ_CKD&t;&t; 0x1e
DECL|macro|DASD_ECKD_CCW_PSF
mdefine_line|#define DASD_ECKD_CCW_PSF&t;&t; 0x27
DECL|macro|DASD_ECKD_CCW_RSSD
mdefine_line|#define DASD_ECKD_CCW_RSSD&t;&t; 0x3e
DECL|macro|DASD_ECKD_CCW_LOCATE_RECORD
mdefine_line|#define DASD_ECKD_CCW_LOCATE_RECORD&t; 0x47
DECL|macro|DASD_ECKD_CCW_DEFINE_EXTENT
mdefine_line|#define DASD_ECKD_CCW_DEFINE_EXTENT&t; 0x63
DECL|macro|DASD_ECKD_CCW_WRITE_MT
mdefine_line|#define DASD_ECKD_CCW_WRITE_MT&t;&t; 0x85
DECL|macro|DASD_ECKD_CCW_READ_MT
mdefine_line|#define DASD_ECKD_CCW_READ_MT&t;&t; 0x86
DECL|macro|DASD_ECKD_CCW_WRITE_KD_MT
mdefine_line|#define DASD_ECKD_CCW_WRITE_KD_MT&t; 0x8d
DECL|macro|DASD_ECKD_CCW_READ_KD_MT
mdefine_line|#define DASD_ECKD_CCW_READ_KD_MT&t; 0x8e
DECL|macro|DASD_ECKD_CCW_RELEASE
mdefine_line|#define DASD_ECKD_CCW_RELEASE&t;&t; 0x94
DECL|macro|DASD_ECKD_CCW_READ_CKD_MT
mdefine_line|#define DASD_ECKD_CCW_READ_CKD_MT&t; 0x9e
DECL|macro|DASD_ECKD_CCW_WRITE_CKD_MT
mdefine_line|#define DASD_ECKD_CCW_WRITE_CKD_MT&t; 0x9d
DECL|macro|DASD_ECKD_CCW_RESERVE
mdefine_line|#define DASD_ECKD_CCW_RESERVE&t;&t; 0xB4
multiline_comment|/*&n; *Perform Subsystem Function / Sub-Orders&n; */
DECL|macro|PSF_ORDER_PRSSD
mdefine_line|#define PSF_ORDER_PRSSD&t;&t;&t; 0x18
multiline_comment|/*******************************************************************************&n; * SECTION: Type Definitions&n; ******************************************************************************/
DECL|struct|eckd_count_t
r_typedef
r_struct
id|eckd_count_t
(brace
DECL|member|cyl
id|__u16
id|cyl
suffix:semicolon
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|member|record
id|__u8
id|record
suffix:semicolon
DECL|member|kl
id|__u8
id|kl
suffix:semicolon
DECL|member|dl
id|__u16
id|dl
suffix:semicolon
DECL|typedef|eckd_count_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|eckd_count_t
suffix:semicolon
DECL|struct|ch_t
r_typedef
r_struct
id|ch_t
(brace
DECL|member|cyl
id|__u16
id|cyl
suffix:semicolon
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|typedef|ch_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ch_t
suffix:semicolon
DECL|struct|chs_t
r_typedef
r_struct
id|chs_t
(brace
DECL|member|cyl
id|__u16
id|cyl
suffix:semicolon
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|member|sector
id|__u32
id|sector
suffix:semicolon
DECL|typedef|chs_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|chs_t
suffix:semicolon
DECL|struct|chr_t
r_typedef
r_struct
id|chr_t
(brace
DECL|member|cyl
id|__u16
id|cyl
suffix:semicolon
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|member|record
id|__u8
id|record
suffix:semicolon
DECL|typedef|chr_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|chr_t
suffix:semicolon
DECL|struct|geom_t
r_typedef
r_struct
id|geom_t
(brace
DECL|member|cyl
id|__u16
id|cyl
suffix:semicolon
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|member|sector
id|__u32
id|sector
suffix:semicolon
DECL|typedef|geom_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|geom_t
suffix:semicolon
DECL|struct|eckd_home_t
r_typedef
r_struct
id|eckd_home_t
(brace
DECL|member|skip_control
id|__u8
id|skip_control
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|cell_number
id|__u16
id|cell_number
suffix:semicolon
DECL|member|physical_addr
id|__u8
id|physical_addr
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|flag
id|__u8
id|flag
suffix:semicolon
DECL|member|track_addr
id|ch_t
id|track_addr
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
DECL|member|key_length
id|__u8
id|key_length
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|eckd_home_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|eckd_home_t
suffix:semicolon
DECL|struct|DE_eckd_data_t
r_typedef
r_struct
id|DE_eckd_data_t
(brace
r_struct
(brace
DECL|member|perm
r_int
r_char
id|perm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Permissions on this extent */
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|seek
r_int
r_char
id|seek
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Seek control */
DECL|member|auth
r_int
r_char
id|auth
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Access authorization */
DECL|member|pci
r_int
r_char
id|pci
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PCI Fetch mode */
DECL|member|mask
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mask
suffix:semicolon
r_struct
(brace
DECL|member|mode
r_int
r_char
id|mode
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Architecture mode */
DECL|member|ckd
r_int
r_char
id|ckd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* CKD Conversion */
DECL|member|operation
r_int
r_char
id|operation
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Operation mode */
DECL|member|cfw
r_int
r_char
id|cfw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache fast write */
DECL|member|dfw
r_int
r_char
id|dfw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* DASD fast write */
DECL|member|attributes
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|attributes
suffix:semicolon
DECL|member|blk_size
id|__u16
r_int
id|blk_size
suffix:semicolon
multiline_comment|/* Blocksize */
DECL|member|fast_write_id
id|__u16
id|fast_write_id
suffix:semicolon
DECL|member|ga_additional
id|__u8
id|ga_additional
suffix:semicolon
multiline_comment|/* Global Attributes Additional */
DECL|member|ga_extended
id|__u8
id|ga_extended
suffix:semicolon
multiline_comment|/* Global Attributes Extended&t;*/
DECL|member|beg_ext
id|ch_t
id|beg_ext
suffix:semicolon
DECL|member|end_ext
id|ch_t
id|end_ext
suffix:semicolon
DECL|typedef|DE_eckd_data_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|DE_eckd_data_t
suffix:semicolon
DECL|struct|LO_eckd_data_t
r_typedef
r_struct
id|LO_eckd_data_t
(brace
r_struct
(brace
DECL|member|orientation
r_int
r_char
id|orientation
suffix:colon
l_int|2
suffix:semicolon
DECL|member|operation
r_int
r_char
id|operation
suffix:colon
l_int|6
suffix:semicolon
DECL|member|operation
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|operation
suffix:semicolon
r_struct
(brace
DECL|member|last_bytes_used
r_int
r_char
id|last_bytes_used
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|6
suffix:semicolon
DECL|member|read_count_suffix
r_int
r_char
id|read_count_suffix
suffix:colon
l_int|1
suffix:semicolon
DECL|member|auxiliary
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|auxiliary
suffix:semicolon
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
DECL|member|count
id|__u8
id|count
suffix:semicolon
DECL|member|seek_addr
id|ch_t
id|seek_addr
suffix:semicolon
DECL|member|search_arg
id|chr_t
id|search_arg
suffix:semicolon
DECL|member|sector
id|__u8
id|sector
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|typedef|LO_eckd_data_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|LO_eckd_data_t
suffix:semicolon
DECL|struct|dasd_eckd_characteristics_t
r_typedef
r_struct
id|dasd_eckd_characteristics_t
(brace
DECL|member|cu_type
id|__u16
id|cu_type
suffix:semicolon
r_struct
(brace
DECL|member|support
r_int
r_char
id|support
suffix:colon
l_int|2
suffix:semicolon
DECL|member|async
r_int
r_char
id|async
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cache_info
r_int
r_char
id|cache_info
suffix:colon
l_int|1
suffix:semicolon
DECL|member|model
r_int
r_char
id|model
suffix:colon
l_int|3
suffix:semicolon
DECL|member|cu_model
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|cu_model
suffix:semicolon
DECL|member|dev_type
id|__u16
id|dev_type
suffix:semicolon
DECL|member|dev_model
id|__u8
id|dev_model
suffix:semicolon
r_struct
(brace
DECL|member|mult_burst
r_int
r_char
id|mult_burst
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RT_in_LR
r_int
r_char
id|RT_in_LR
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RD_IN_LR
r_int
r_char
id|RD_IN_LR
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved3
r_int
r_char
id|reserved3
suffix:colon
l_int|8
suffix:semicolon
DECL|member|defect_wr
r_int
r_char
id|defect_wr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved4
r_int
r_char
id|reserved4
suffix:colon
l_int|2
suffix:semicolon
DECL|member|striping
r_int
r_char
id|striping
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved5
r_int
r_char
id|reserved5
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cfw
r_int
r_char
id|cfw
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved6
r_int
r_char
id|reserved6
suffix:colon
l_int|2
suffix:semicolon
DECL|member|cache
r_int
r_char
id|cache
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dual_copy
r_int
r_char
id|dual_copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dfw
r_int
r_char
id|dfw
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reset_alleg
r_int
r_char
id|reset_alleg
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sense_down
r_int
r_char
id|sense_down
suffix:colon
l_int|1
suffix:semicolon
DECL|member|facilities
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|facilities
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
suffix:semicolon
DECL|member|unit_type
id|__u8
id|unit_type
suffix:semicolon
DECL|member|no_cyl
id|__u16
id|no_cyl
suffix:semicolon
DECL|member|trk_per_cyl
id|__u16
id|trk_per_cyl
suffix:semicolon
DECL|member|sec_per_trk
id|__u8
id|sec_per_trk
suffix:semicolon
DECL|member|byte_per_track
id|__u8
id|byte_per_track
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|home_bytes
id|__u16
id|home_bytes
suffix:semicolon
DECL|member|formula
id|__u8
id|formula
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|f1
id|__u8
id|f1
suffix:semicolon
DECL|member|f2
id|__u16
id|f2
suffix:semicolon
DECL|member|f3
id|__u16
id|f3
suffix:semicolon
DECL|member|f_0x01
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|f_0x01
suffix:semicolon
r_struct
(brace
DECL|member|f1
id|__u8
id|f1
suffix:semicolon
DECL|member|f2
id|__u8
id|f2
suffix:semicolon
DECL|member|f3
id|__u8
id|f3
suffix:semicolon
DECL|member|f4
id|__u8
id|f4
suffix:semicolon
DECL|member|f5
id|__u8
id|f5
suffix:semicolon
DECL|member|f_0x02
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|f_0x02
suffix:semicolon
DECL|member|factors
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|factors
suffix:semicolon
DECL|member|first_alt_trk
id|__u16
id|first_alt_trk
suffix:semicolon
DECL|member|no_alt_trk
id|__u16
id|no_alt_trk
suffix:semicolon
DECL|member|first_dia_trk
id|__u16
id|first_dia_trk
suffix:semicolon
DECL|member|no_dia_trk
id|__u16
id|no_dia_trk
suffix:semicolon
DECL|member|first_sup_trk
id|__u16
id|first_sup_trk
suffix:semicolon
DECL|member|no_sup_trk
id|__u16
id|no_sup_trk
suffix:semicolon
DECL|member|MDR_ID
id|__u8
id|MDR_ID
suffix:semicolon
DECL|member|OBR_ID
id|__u8
id|OBR_ID
suffix:semicolon
DECL|member|director
id|__u8
id|director
suffix:semicolon
DECL|member|rd_trk_set
id|__u8
id|rd_trk_set
suffix:semicolon
DECL|member|max_rec_zero
id|__u16
id|max_rec_zero
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|RWANY_in_LR
id|__u8
id|RWANY_in_LR
suffix:semicolon
DECL|member|factor6
id|__u8
id|factor6
suffix:semicolon
DECL|member|factor7
id|__u8
id|factor7
suffix:semicolon
DECL|member|factor8
id|__u8
id|factor8
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|dasd_eckd_characteristics_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|dasd_eckd_characteristics_t
suffix:semicolon
DECL|struct|dasd_eckd_confdata_t
r_typedef
r_struct
id|dasd_eckd_confdata_t
(brace
r_struct
(brace
r_struct
(brace
DECL|member|identifier
r_int
r_char
id|identifier
suffix:colon
l_int|2
suffix:semicolon
DECL|member|token_id
r_int
r_char
id|token_id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sno_valid
r_int
r_char
id|sno_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|subst_sno
r_int
r_char
id|subst_sno
suffix:colon
l_int|1
suffix:semicolon
DECL|member|recNED
r_int
r_char
id|recNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|emuNED
r_int
r_char
id|emuNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|descriptor
id|__u8
id|descriptor
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
DECL|member|dev_type
r_int
r_char
id|dev_type
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|dev_model
r_int
r_char
id|dev_model
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|HDA_manufacturer
r_int
r_char
id|HDA_manufacturer
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|HDA_location
r_int
r_char
id|HDA_location
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|HDA_seqno
r_int
r_char
id|HDA_seqno
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|ID
id|__u16
id|ID
suffix:semicolon
DECL|member|ned1
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ned1
suffix:semicolon
r_struct
(brace
r_struct
(brace
DECL|member|identifier
r_int
r_char
id|identifier
suffix:colon
l_int|2
suffix:semicolon
DECL|member|token_id
r_int
r_char
id|token_id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sno_valid
r_int
r_char
id|sno_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|subst_sno
r_int
r_char
id|subst_sno
suffix:colon
l_int|1
suffix:semicolon
DECL|member|recNED
r_int
r_char
id|recNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|emuNED
r_int
r_char
id|emuNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|descriptor
id|__u8
id|descriptor
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dev_type
r_int
r_char
id|dev_type
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|dev_model
r_int
r_char
id|dev_model
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|DASD_manufacturer
r_int
r_char
id|DASD_manufacturer
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|DASD_location
r_int
r_char
id|DASD_location
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|DASD_seqno
r_int
r_char
id|DASD_seqno
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|ID
id|__u16
id|ID
suffix:semicolon
DECL|member|ned2
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ned2
suffix:semicolon
r_struct
(brace
r_struct
(brace
DECL|member|identifier
r_int
r_char
id|identifier
suffix:colon
l_int|2
suffix:semicolon
DECL|member|token_id
r_int
r_char
id|token_id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sno_valid
r_int
r_char
id|sno_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|subst_sno
r_int
r_char
id|subst_sno
suffix:colon
l_int|1
suffix:semicolon
DECL|member|recNED
r_int
r_char
id|recNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|emuNED
r_int
r_char
id|emuNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|descriptor
id|__u8
id|descriptor
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cont_type
r_int
r_char
id|cont_type
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|cont_model
r_int
r_char
id|cont_model
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cont_manufacturer
r_int
r_char
id|cont_manufacturer
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cont_location
r_int
r_char
id|cont_location
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cont_seqno
r_int
r_char
id|cont_seqno
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|ID
id|__u16
id|ID
suffix:semicolon
DECL|member|ned3
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ned3
suffix:semicolon
r_struct
(brace
r_struct
(brace
DECL|member|identifier
r_int
r_char
id|identifier
suffix:colon
l_int|2
suffix:semicolon
DECL|member|token_id
r_int
r_char
id|token_id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sno_valid
r_int
r_char
id|sno_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|subst_sno
r_int
r_char
id|subst_sno
suffix:colon
l_int|1
suffix:semicolon
DECL|member|recNED
r_int
r_char
id|recNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|emuNED
r_int
r_char
id|emuNED
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|descriptor
id|__u8
id|descriptor
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cont_type
r_int
r_char
id|cont_type
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|empty
r_int
r_char
id|empty
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cont_manufacturer
r_int
r_char
id|cont_manufacturer
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cont_location
r_int
r_char
id|cont_location
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cont_seqno
r_int
r_char
id|cont_seqno
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|ID
id|__u16
id|ID
suffix:semicolon
DECL|member|ned4
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ned4
suffix:semicolon
DECL|member|ned5
r_int
r_char
id|ned5
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|ned6
r_int
r_char
id|ned6
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|ned7
r_int
r_char
id|ned7
(braket
l_int|32
)braket
suffix:semicolon
r_struct
(brace
r_struct
(brace
DECL|member|identifier
r_int
r_char
id|identifier
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|6
suffix:semicolon
DECL|member|flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|selector
id|__u8
id|selector
suffix:semicolon
DECL|member|interfaceID
id|__u16
id|interfaceID
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
suffix:semicolon
DECL|member|subsystemID
id|__u16
id|subsystemID
suffix:semicolon
r_struct
(brace
DECL|member|sp0
r_int
r_char
id|sp0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sp1
r_int
r_char
id|sp1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|5
suffix:semicolon
DECL|member|scluster
r_int
r_char
id|scluster
suffix:colon
l_int|1
suffix:semicolon
DECL|member|spathID
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|spathID
suffix:semicolon
DECL|member|unit_address
id|__u8
id|unit_address
suffix:semicolon
DECL|member|dev_ID
id|__u8
id|dev_ID
suffix:semicolon
DECL|member|dev_address
id|__u8
id|dev_address
suffix:semicolon
DECL|member|adapterID
id|__u8
id|adapterID
suffix:semicolon
DECL|member|link_address
id|__u16
id|link_address
suffix:semicolon
r_struct
(brace
DECL|member|parallel
r_int
r_char
id|parallel
suffix:colon
l_int|1
suffix:semicolon
DECL|member|escon
r_int
r_char
id|escon
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ficon
r_int
r_char
id|ficon
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|protocol_type
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|protocol_type
suffix:semicolon
r_struct
(brace
DECL|member|PID_in_236
r_int
r_char
id|PID_in_236
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|7
suffix:semicolon
DECL|member|format_flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|format_flags
suffix:semicolon
DECL|member|log_dev_address
id|__u8
id|log_dev_address
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|neq
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|neq
suffix:semicolon
DECL|typedef|dasd_eckd_confdata_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|dasd_eckd_confdata_t
suffix:semicolon
multiline_comment|/*&n; * Perform Subsystem Function - Prepare for Read Subsystem Data&t; &n; */
DECL|struct|dasd_psf_prssd_data_t
r_typedef
r_struct
id|dasd_psf_prssd_data_t
(brace
DECL|member|order
r_int
r_char
id|order
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|suborder
r_int
r_char
id|suborder
suffix:semicolon
DECL|member|varies
r_int
r_char
id|varies
(braket
l_int|9
)braket
suffix:semicolon
DECL|typedef|dasd_psf_prssd_data_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|dasd_psf_prssd_data_t
suffix:semicolon
r_int
id|dasd_eckd_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dasd_eckd_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* DASD_ECKD_H */
eof
