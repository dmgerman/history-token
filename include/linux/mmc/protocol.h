multiline_comment|/*&n; * Header for MultiMediaCard (MMC)&n; *&n; * Copyright 2002 Hewlett-Packard Company&n; *&n; * Use consistent with the GNU GPL is permitted,&n; * provided that this copyright notice is&n; * preserved in its entirety in all copies and derived works.&n; *&n; * HEWLETT-PACKARD COMPANY MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n; * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n; * FITNESS FOR ANY PARTICULAR PURPOSE.&n; *&n; * Many thanks to Alessandro Rubini and Jonathan Corbet!&n; *&n; * Based strongly on code by:&n; *&n; * Author: Yong-iL Joh &lt;tolkien@mizi.com&gt;&n; * Date  : $Date: 2002/06/18 12:37:30 $&n; *&n; * Author:  Andrew Christian&n; *          15 May 2002&n; */
macro_line|#ifndef MMC_MMC_PROTOCOL_H
DECL|macro|MMC_MMC_PROTOCOL_H
mdefine_line|#define MMC_MMC_PROTOCOL_H
multiline_comment|/* Standard MMC commands (3.1)           type  argument     response */
multiline_comment|/* class 1 */
DECL|macro|MMC_GO_IDLE_STATE
mdefine_line|#define&t;MMC_GO_IDLE_STATE         0   /* bc                          */
DECL|macro|MMC_SEND_OP_COND
mdefine_line|#define MMC_SEND_OP_COND          1   /* bcr  [31:0] OCR         R3  */
DECL|macro|MMC_ALL_SEND_CID
mdefine_line|#define MMC_ALL_SEND_CID          2   /* bcr                     R2  */
DECL|macro|MMC_SET_RELATIVE_ADDR
mdefine_line|#define MMC_SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1  */
DECL|macro|MMC_SET_DSR
mdefine_line|#define MMC_SET_DSR               4   /* bc   [31:16] RCA            */
DECL|macro|MMC_SELECT_CARD
mdefine_line|#define MMC_SELECT_CARD           7   /* ac   [31:16] RCA        R1  */
DECL|macro|MMC_SEND_CSD
mdefine_line|#define MMC_SEND_CSD              9   /* ac   [31:16] RCA        R2  */
DECL|macro|MMC_SEND_CID
mdefine_line|#define MMC_SEND_CID             10   /* ac   [31:16] RCA        R2  */
DECL|macro|MMC_READ_DAT_UNTIL_STOP
mdefine_line|#define MMC_READ_DAT_UNTIL_STOP  11   /* adtc [31:0] dadr        R1  */
DECL|macro|MMC_STOP_TRANSMISSION
mdefine_line|#define MMC_STOP_TRANSMISSION    12   /* ac                      R1b */
DECL|macro|MMC_SEND_STATUS
mdefine_line|#define MMC_SEND_STATUS&t;         13   /* ac   [31:16] RCA        R1  */
DECL|macro|MMC_GO_INACTIVE_STATE
mdefine_line|#define MMC_GO_INACTIVE_STATE    15   /* ac   [31:16] RCA            */
multiline_comment|/* class 2 */
DECL|macro|MMC_SET_BLOCKLEN
mdefine_line|#define MMC_SET_BLOCKLEN         16   /* ac   [31:0] block len   R1  */
DECL|macro|MMC_READ_SINGLE_BLOCK
mdefine_line|#define MMC_READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
DECL|macro|MMC_READ_MULTIPLE_BLOCK
mdefine_line|#define MMC_READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */
multiline_comment|/* class 3 */
DECL|macro|MMC_WRITE_DAT_UNTIL_STOP
mdefine_line|#define MMC_WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */
multiline_comment|/* class 4 */
DECL|macro|MMC_SET_BLOCK_COUNT
mdefine_line|#define MMC_SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
DECL|macro|MMC_WRITE_BLOCK
mdefine_line|#define MMC_WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
DECL|macro|MMC_WRITE_MULTIPLE_BLOCK
mdefine_line|#define MMC_WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1  */
DECL|macro|MMC_PROGRAM_CID
mdefine_line|#define MMC_PROGRAM_CID          26   /* adtc                    R1  */
DECL|macro|MMC_PROGRAM_CSD
mdefine_line|#define MMC_PROGRAM_CSD          27   /* adtc                    R1  */
multiline_comment|/* class 6 */
DECL|macro|MMC_SET_WRITE_PROT
mdefine_line|#define MMC_SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
DECL|macro|MMC_CLR_WRITE_PROT
mdefine_line|#define MMC_CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
DECL|macro|MMC_SEND_WRITE_PROT
mdefine_line|#define MMC_SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1  */
multiline_comment|/* class 5 */
DECL|macro|MMC_ERASE_GROUP_START
mdefine_line|#define MMC_ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
DECL|macro|MMC_ERASE_GROUP_END
mdefine_line|#define MMC_ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
DECL|macro|MMC_ERASE
mdefine_line|#define MMC_ERASE                37   /* ac                      R1b */
multiline_comment|/* class 9 */
DECL|macro|MMC_FAST_IO
mdefine_line|#define MMC_FAST_IO              39   /* ac   &lt;Complex&gt;          R4  */
DECL|macro|MMC_GO_IRQ_STATE
mdefine_line|#define MMC_GO_IRQ_STATE         40   /* bcr                     R5  */
multiline_comment|/* class 7 */
DECL|macro|MMC_LOCK_UNLOCK
mdefine_line|#define MMC_LOCK_UNLOCK          42   /* adtc                    R1b */
multiline_comment|/* class 8 */
DECL|macro|MMC_APP_CMD
mdefine_line|#define MMC_APP_CMD              55   /* ac   [31:16] RCA        R1  */
DECL|macro|MMC_GEN_CMD
mdefine_line|#define MMC_GEN_CMD              56   /* adtc [0] RD/WR          R1b */
multiline_comment|/* SD commands                           type  argument     response */
multiline_comment|/* class 8 */
multiline_comment|/* This is basically the same command as for MMC with some quirks. */
DECL|macro|SD_SEND_RELATIVE_ADDR
mdefine_line|#define SD_SEND_RELATIVE_ADDR     3   /* ac                      R6  */
multiline_comment|/* Application commands */
DECL|macro|SD_APP_SET_BUS_WIDTH
mdefine_line|#define SD_APP_SET_BUS_WIDTH      6   /* ac   [1:0] bus width    R1  */
DECL|macro|SD_APP_OP_COND
mdefine_line|#define SD_APP_OP_COND           41   /* bcr  [31:0] OCR         R3  */
DECL|macro|SD_APP_SEND_SCR
mdefine_line|#define SD_APP_SEND_SCR          51   /* adtc                    R1  */
multiline_comment|/*&n;  MMC status in R1&n;  Type&n;  &t;e : error bit&n;&t;s : status bit&n;&t;r : detected and set for the actual command response&n;&t;x : detected and set during command execution. the host must poll&n;            the card by sending status command in order to read these bits.&n;  Clear condition&n;  &t;a : according to the card state&n;&t;b : always related to the previous command. Reception of&n;            a valid command will clear it (with a delay of one command)&n;&t;c : clear by read&n; */
DECL|macro|R1_OUT_OF_RANGE
mdefine_line|#define R1_OUT_OF_RANGE&t;&t;(1 &lt;&lt; 31)&t;/* er, c */
DECL|macro|R1_ADDRESS_ERROR
mdefine_line|#define R1_ADDRESS_ERROR&t;(1 &lt;&lt; 30)&t;/* erx, c */
DECL|macro|R1_BLOCK_LEN_ERROR
mdefine_line|#define R1_BLOCK_LEN_ERROR&t;(1 &lt;&lt; 29)&t;/* er, c */
DECL|macro|R1_ERASE_SEQ_ERROR
mdefine_line|#define R1_ERASE_SEQ_ERROR      (1 &lt;&lt; 28)&t;/* er, c */
DECL|macro|R1_ERASE_PARAM
mdefine_line|#define R1_ERASE_PARAM&t;&t;(1 &lt;&lt; 27)&t;/* ex, c */
DECL|macro|R1_WP_VIOLATION
mdefine_line|#define R1_WP_VIOLATION&t;&t;(1 &lt;&lt; 26)&t;/* erx, c */
DECL|macro|R1_CARD_IS_LOCKED
mdefine_line|#define R1_CARD_IS_LOCKED&t;(1 &lt;&lt; 25)&t;/* sx, a */
DECL|macro|R1_LOCK_UNLOCK_FAILED
mdefine_line|#define R1_LOCK_UNLOCK_FAILED&t;(1 &lt;&lt; 24)&t;/* erx, c */
DECL|macro|R1_COM_CRC_ERROR
mdefine_line|#define R1_COM_CRC_ERROR&t;(1 &lt;&lt; 23)&t;/* er, b */
DECL|macro|R1_ILLEGAL_COMMAND
mdefine_line|#define R1_ILLEGAL_COMMAND&t;(1 &lt;&lt; 22)&t;/* er, b */
DECL|macro|R1_CARD_ECC_FAILED
mdefine_line|#define R1_CARD_ECC_FAILED&t;(1 &lt;&lt; 21)&t;/* ex, c */
DECL|macro|R1_CC_ERROR
mdefine_line|#define R1_CC_ERROR&t;&t;(1 &lt;&lt; 20)&t;/* erx, c */
DECL|macro|R1_ERROR
mdefine_line|#define R1_ERROR&t;&t;(1 &lt;&lt; 19)&t;/* erx, c */
DECL|macro|R1_UNDERRUN
mdefine_line|#define R1_UNDERRUN&t;&t;(1 &lt;&lt; 18)&t;/* ex, c */
DECL|macro|R1_OVERRUN
mdefine_line|#define R1_OVERRUN&t;&t;(1 &lt;&lt; 17)&t;/* ex, c */
DECL|macro|R1_CID_CSD_OVERWRITE
mdefine_line|#define R1_CID_CSD_OVERWRITE&t;(1 &lt;&lt; 16)&t;/* erx, c, CID/CSD overwrite */
DECL|macro|R1_WP_ERASE_SKIP
mdefine_line|#define R1_WP_ERASE_SKIP&t;(1 &lt;&lt; 15)&t;/* sx, c */
DECL|macro|R1_CARD_ECC_DISABLED
mdefine_line|#define R1_CARD_ECC_DISABLED&t;(1 &lt;&lt; 14)&t;/* sx, a */
DECL|macro|R1_ERASE_RESET
mdefine_line|#define R1_ERASE_RESET&t;&t;(1 &lt;&lt; 13)&t;/* sr, c */
DECL|macro|R1_STATUS
mdefine_line|#define R1_STATUS(x)            (x &amp; 0xFFFFE000)
DECL|macro|R1_CURRENT_STATE
mdefine_line|#define R1_CURRENT_STATE(x)    &t;((x &amp; 0x00001E00) &gt;&gt; 9)&t;/* sx, b (4 bits) */
DECL|macro|R1_READY_FOR_DATA
mdefine_line|#define R1_READY_FOR_DATA&t;(1 &lt;&lt; 8)&t;/* sx, a */
DECL|macro|R1_APP_CMD
mdefine_line|#define R1_APP_CMD&t;&t;(1 &lt;&lt; 5)&t;/* sr, c */
multiline_comment|/* These are unpacked versions of the actual responses */
DECL|struct|_mmc_csd
r_struct
id|_mmc_csd
(brace
DECL|member|csd_structure
id|u8
id|csd_structure
suffix:semicolon
DECL|member|spec_vers
id|u8
id|spec_vers
suffix:semicolon
DECL|member|taac
id|u8
id|taac
suffix:semicolon
DECL|member|nsac
id|u8
id|nsac
suffix:semicolon
DECL|member|tran_speed
id|u8
id|tran_speed
suffix:semicolon
DECL|member|ccc
id|u16
id|ccc
suffix:semicolon
DECL|member|read_bl_len
id|u8
id|read_bl_len
suffix:semicolon
DECL|member|read_bl_partial
id|u8
id|read_bl_partial
suffix:semicolon
DECL|member|write_blk_misalign
id|u8
id|write_blk_misalign
suffix:semicolon
DECL|member|read_blk_misalign
id|u8
id|read_blk_misalign
suffix:semicolon
DECL|member|dsr_imp
id|u8
id|dsr_imp
suffix:semicolon
DECL|member|c_size
id|u16
id|c_size
suffix:semicolon
DECL|member|vdd_r_curr_min
id|u8
id|vdd_r_curr_min
suffix:semicolon
DECL|member|vdd_r_curr_max
id|u8
id|vdd_r_curr_max
suffix:semicolon
DECL|member|vdd_w_curr_min
id|u8
id|vdd_w_curr_min
suffix:semicolon
DECL|member|vdd_w_curr_max
id|u8
id|vdd_w_curr_max
suffix:semicolon
DECL|member|c_size_mult
id|u8
id|c_size_mult
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/* MMC system specification version 3.1 */
DECL|member|erase_grp_size
id|u8
id|erase_grp_size
suffix:semicolon
DECL|member|erase_grp_mult
id|u8
id|erase_grp_mult
suffix:semicolon
DECL|member|v31
)brace
id|v31
suffix:semicolon
r_struct
(brace
multiline_comment|/* MMC system specification version 2.2 */
DECL|member|sector_size
id|u8
id|sector_size
suffix:semicolon
DECL|member|erase_grp_size
id|u8
id|erase_grp_size
suffix:semicolon
DECL|member|v22
)brace
id|v22
suffix:semicolon
DECL|member|erase
)brace
id|erase
suffix:semicolon
DECL|member|wp_grp_size
id|u8
id|wp_grp_size
suffix:semicolon
DECL|member|wp_grp_enable
id|u8
id|wp_grp_enable
suffix:semicolon
DECL|member|default_ecc
id|u8
id|default_ecc
suffix:semicolon
DECL|member|r2w_factor
id|u8
id|r2w_factor
suffix:semicolon
DECL|member|write_bl_len
id|u8
id|write_bl_len
suffix:semicolon
DECL|member|write_bl_partial
id|u8
id|write_bl_partial
suffix:semicolon
DECL|member|file_format_grp
id|u8
id|file_format_grp
suffix:semicolon
DECL|member|copy
id|u8
id|copy
suffix:semicolon
DECL|member|perm_write_protect
id|u8
id|perm_write_protect
suffix:semicolon
DECL|member|tmp_write_protect
id|u8
id|tmp_write_protect
suffix:semicolon
DECL|member|file_format
id|u8
id|file_format
suffix:semicolon
DECL|member|ecc
id|u8
id|ecc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MMC_VDD_145_150
mdefine_line|#define MMC_VDD_145_150&t;0x00000001&t;/* VDD voltage 1.45 - 1.50 */
DECL|macro|MMC_VDD_150_155
mdefine_line|#define MMC_VDD_150_155&t;0x00000002&t;/* VDD voltage 1.50 - 1.55 */
DECL|macro|MMC_VDD_155_160
mdefine_line|#define MMC_VDD_155_160&t;0x00000004&t;/* VDD voltage 1.55 - 1.60 */
DECL|macro|MMC_VDD_160_165
mdefine_line|#define MMC_VDD_160_165&t;0x00000008&t;/* VDD voltage 1.60 - 1.65 */
DECL|macro|MMC_VDD_165_170
mdefine_line|#define MMC_VDD_165_170&t;0x00000010&t;/* VDD voltage 1.65 - 1.70 */
DECL|macro|MMC_VDD_17_18
mdefine_line|#define MMC_VDD_17_18&t;0x00000020&t;/* VDD voltage 1.7 - 1.8 */
DECL|macro|MMC_VDD_18_19
mdefine_line|#define MMC_VDD_18_19&t;0x00000040&t;/* VDD voltage 1.8 - 1.9 */
DECL|macro|MMC_VDD_19_20
mdefine_line|#define MMC_VDD_19_20&t;0x00000080&t;/* VDD voltage 1.9 - 2.0 */
DECL|macro|MMC_VDD_20_21
mdefine_line|#define MMC_VDD_20_21&t;0x00000100&t;/* VDD voltage 2.0 ~ 2.1 */
DECL|macro|MMC_VDD_21_22
mdefine_line|#define MMC_VDD_21_22&t;0x00000200&t;/* VDD voltage 2.1 ~ 2.2 */
DECL|macro|MMC_VDD_22_23
mdefine_line|#define MMC_VDD_22_23&t;0x00000400&t;/* VDD voltage 2.2 ~ 2.3 */
DECL|macro|MMC_VDD_23_24
mdefine_line|#define MMC_VDD_23_24&t;0x00000800&t;/* VDD voltage 2.3 ~ 2.4 */
DECL|macro|MMC_VDD_24_25
mdefine_line|#define MMC_VDD_24_25&t;0x00001000&t;/* VDD voltage 2.4 ~ 2.5 */
DECL|macro|MMC_VDD_25_26
mdefine_line|#define MMC_VDD_25_26&t;0x00002000&t;/* VDD voltage 2.5 ~ 2.6 */
DECL|macro|MMC_VDD_26_27
mdefine_line|#define MMC_VDD_26_27&t;0x00004000&t;/* VDD voltage 2.6 ~ 2.7 */
DECL|macro|MMC_VDD_27_28
mdefine_line|#define MMC_VDD_27_28&t;0x00008000&t;/* VDD voltage 2.7 ~ 2.8 */
DECL|macro|MMC_VDD_28_29
mdefine_line|#define MMC_VDD_28_29&t;0x00010000&t;/* VDD voltage 2.8 ~ 2.9 */
DECL|macro|MMC_VDD_29_30
mdefine_line|#define MMC_VDD_29_30&t;0x00020000&t;/* VDD voltage 2.9 ~ 3.0 */
DECL|macro|MMC_VDD_30_31
mdefine_line|#define MMC_VDD_30_31&t;0x00040000&t;/* VDD voltage 3.0 ~ 3.1 */
DECL|macro|MMC_VDD_31_32
mdefine_line|#define MMC_VDD_31_32&t;0x00080000&t;/* VDD voltage 3.1 ~ 3.2 */
DECL|macro|MMC_VDD_32_33
mdefine_line|#define MMC_VDD_32_33&t;0x00100000&t;/* VDD voltage 3.2 ~ 3.3 */
DECL|macro|MMC_VDD_33_34
mdefine_line|#define MMC_VDD_33_34&t;0x00200000&t;/* VDD voltage 3.3 ~ 3.4 */
DECL|macro|MMC_VDD_34_35
mdefine_line|#define MMC_VDD_34_35&t;0x00400000&t;/* VDD voltage 3.4 ~ 3.5 */
DECL|macro|MMC_VDD_35_36
mdefine_line|#define MMC_VDD_35_36&t;0x00800000&t;/* VDD voltage 3.5 ~ 3.6 */
DECL|macro|MMC_CARD_BUSY
mdefine_line|#define MMC_CARD_BUSY&t;0x80000000&t;/* Card Power up status bit */
multiline_comment|/*&n; * CSD field definitions&n; */
DECL|macro|CSD_STRUCT_VER_1_0
mdefine_line|#define CSD_STRUCT_VER_1_0  0           /* Valid for system specification 1.0 - 1.2 */
DECL|macro|CSD_STRUCT_VER_1_1
mdefine_line|#define CSD_STRUCT_VER_1_1  1           /* Valid for system specification 1.4 - 2.2 */
DECL|macro|CSD_STRUCT_VER_1_2
mdefine_line|#define CSD_STRUCT_VER_1_2  2           /* Valid for system specification 3.1       */
DECL|macro|CSD_SPEC_VER_0
mdefine_line|#define CSD_SPEC_VER_0      0           /* Implements system specification 1.0 - 1.2 */
DECL|macro|CSD_SPEC_VER_1
mdefine_line|#define CSD_SPEC_VER_1      1           /* Implements system specification 1.4 */
DECL|macro|CSD_SPEC_VER_2
mdefine_line|#define CSD_SPEC_VER_2      2           /* Implements system specification 2.0 - 2.2 */
DECL|macro|CSD_SPEC_VER_3
mdefine_line|#define CSD_SPEC_VER_3      3           /* Implements system specification 3.1 */
macro_line|#endif  /* MMC_MMC_PROTOCOL_H */
eof
