multiline_comment|/* $Id: applicom.h,v 1.2 1999/08/28 15:09:49 dwmw2 Exp $ */
macro_line|#ifndef __LINUX_APPLICOM_H__
DECL|macro|__LINUX_APPLICOM_H__
mdefine_line|#define __LINUX_APPLICOM_H__
DECL|macro|DATA_TO_PC_READY
mdefine_line|#define DATA_TO_PC_READY      0x00
DECL|macro|TIC_OWNER_TO_PC
mdefine_line|#define TIC_OWNER_TO_PC       0x01
DECL|macro|NUMCARD_OWNER_TO_PC
mdefine_line|#define NUMCARD_OWNER_TO_PC   0x02
DECL|macro|TIC_DES_TO_PC
mdefine_line|#define TIC_DES_TO_PC         0x03
DECL|macro|NUMCARD_DES_TO_PC
mdefine_line|#define NUMCARD_DES_TO_PC     0x04
DECL|macro|DATA_FROM_PC_READY
mdefine_line|#define DATA_FROM_PC_READY    0x05
DECL|macro|TIC_OWNER_FROM_PC
mdefine_line|#define TIC_OWNER_FROM_PC     0x06
DECL|macro|NUMCARD_OWNER_FROM_PC
mdefine_line|#define NUMCARD_OWNER_FROM_PC 0x07
DECL|macro|TIC_DES_FROM_PC
mdefine_line|#define TIC_DES_FROM_PC       0x08
DECL|macro|NUMCARD_DES_FROM_PC
mdefine_line|#define NUMCARD_DES_FROM_PC   0x09
DECL|macro|ACK_FROM_PC_READY
mdefine_line|#define ACK_FROM_PC_READY     0x0E
DECL|macro|TIC_ACK_FROM_PC
mdefine_line|#define TIC_ACK_FROM_PC       0x0F
DECL|macro|NUMCARD_ACK_FROM_PC
mdefine_line|#define NUMCARD_ACK_FROM_PC   0x010
DECL|macro|TYP_ACK_FROM_PC
mdefine_line|#define TYP_ACK_FROM_PC       0x011
DECL|macro|CONF_END_TEST
mdefine_line|#define CONF_END_TEST         0x012
DECL|macro|ERROR_CODE
mdefine_line|#define ERROR_CODE            0x016 
DECL|macro|PARAMETER_ERROR
mdefine_line|#define PARAMETER_ERROR       0x018 
DECL|macro|VERS
mdefine_line|#define VERS                  0x01E 
DECL|macro|RAM_TO_PC
mdefine_line|#define RAM_TO_PC             0x040
DECL|macro|RAM_FROM_PC
mdefine_line|#define RAM_FROM_PC           0x0170
DECL|macro|TYPE_CARD
mdefine_line|#define TYPE_CARD             0x03C0
DECL|macro|SERIAL_NUMBER
mdefine_line|#define SERIAL_NUMBER         0x03DA
DECL|macro|RAM_IT_FROM_PC
mdefine_line|#define RAM_IT_FROM_PC        0x03FE
DECL|macro|RAM_IT_TO_PC
mdefine_line|#define RAM_IT_TO_PC          0x03FF
DECL|struct|mailbox
r_struct
id|mailbox
(brace
DECL|member|stjb_codef
id|u16
id|stjb_codef
suffix:semicolon
multiline_comment|/* offset 00 */
DECL|member|stjb_status
id|s16
id|stjb_status
suffix:semicolon
multiline_comment|/* offset 02 */
DECL|member|stjb_ticuser_root
id|u16
id|stjb_ticuser_root
suffix:semicolon
multiline_comment|/* offset 04 */
DECL|member|stjb_piduser
id|u8
id|stjb_piduser
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* offset 06 */
DECL|member|stjb_mode
id|u16
id|stjb_mode
suffix:semicolon
multiline_comment|/* offset 0A */
DECL|member|stjb_time
id|u16
id|stjb_time
suffix:semicolon
multiline_comment|/* offset 0C */
DECL|member|stjb_stop
id|u16
id|stjb_stop
suffix:semicolon
multiline_comment|/* offset 0E */
DECL|member|stjb_nfonc
id|u16
id|stjb_nfonc
suffix:semicolon
multiline_comment|/* offset 10 */
DECL|member|stjb_ncard
id|u16
id|stjb_ncard
suffix:semicolon
multiline_comment|/* offset 12 */
DECL|member|stjb_nchan
id|u16
id|stjb_nchan
suffix:semicolon
multiline_comment|/* offset 14 */
DECL|member|stjb_nes
id|u16
id|stjb_nes
suffix:semicolon
multiline_comment|/* offset 16 */
DECL|member|stjb_nb
id|u16
id|stjb_nb
suffix:semicolon
multiline_comment|/* offset 18 */
DECL|member|stjb_typvar
id|u16
id|stjb_typvar
suffix:semicolon
multiline_comment|/* offset 1A */
DECL|member|stjb_adr
id|u32
id|stjb_adr
suffix:semicolon
multiline_comment|/* offset 1C */
DECL|member|stjb_ticuser_dispcyc
id|u16
id|stjb_ticuser_dispcyc
suffix:semicolon
multiline_comment|/* offset 20 */
DECL|member|stjb_ticuser_protocol
id|u16
id|stjb_ticuser_protocol
suffix:semicolon
multiline_comment|/* offset 22 */
DECL|member|stjb_filler
id|u8
id|stjb_filler
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* offset 24 */
DECL|member|stjb_data
id|u8
id|stjb_data
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* offset 30 */
)brace
suffix:semicolon
DECL|struct|st_ram_io
r_struct
id|st_ram_io
(brace
DECL|member|data_to_pc_ready
r_int
r_char
id|data_to_pc_ready
suffix:semicolon
DECL|member|tic_owner_to_pc
r_int
r_char
id|tic_owner_to_pc
suffix:semicolon
DECL|member|numcard_owner_to_pc
r_int
r_char
id|numcard_owner_to_pc
suffix:semicolon
DECL|member|tic_des_to_pc
r_int
r_char
id|tic_des_to_pc
suffix:semicolon
DECL|member|numcard_des_to_pc
r_int
r_char
id|numcard_des_to_pc
suffix:semicolon
DECL|member|data_from_pc_ready
r_int
r_char
id|data_from_pc_ready
suffix:semicolon
DECL|member|tic_owner_from_pc
r_int
r_char
id|tic_owner_from_pc
suffix:semicolon
DECL|member|numcard_owner_from_pc
r_int
r_char
id|numcard_owner_from_pc
suffix:semicolon
DECL|member|tic_des_from_pc
r_int
r_char
id|tic_des_from_pc
suffix:semicolon
DECL|member|numcard_des_from_pc
r_int
r_char
id|numcard_des_from_pc
suffix:semicolon
DECL|member|ack_to_pc_ready
r_int
r_char
id|ack_to_pc_ready
suffix:semicolon
DECL|member|tic_ack_to_pc
r_int
r_char
id|tic_ack_to_pc
suffix:semicolon
DECL|member|numcard_ack_to_pc
r_int
r_char
id|numcard_ack_to_pc
suffix:semicolon
DECL|member|typ_ack_to_pc
r_int
r_char
id|typ_ack_to_pc
suffix:semicolon
DECL|member|ack_from_pc_ready
r_int
r_char
id|ack_from_pc_ready
suffix:semicolon
DECL|member|tic_ack_from_pc
r_int
r_char
id|tic_ack_from_pc
suffix:semicolon
DECL|member|numcard_ack_from_pc
r_int
r_char
id|numcard_ack_from_pc
suffix:semicolon
DECL|member|typ_ack_from_pc
r_int
r_char
id|typ_ack_from_pc
suffix:semicolon
DECL|member|conf_end_test
r_int
r_char
id|conf_end_test
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|error_code
r_int
r_char
id|error_code
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|parameter_error
r_int
r_char
id|parameter_error
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|time_base
r_int
r_char
id|time_base
suffix:semicolon
DECL|member|nul_inc
r_int
r_char
id|nul_inc
suffix:semicolon
DECL|member|vers
r_int
r_char
id|vers
suffix:semicolon
DECL|member|num_card
r_int
r_char
id|num_card
suffix:semicolon
DECL|member|reserv1
r_int
r_char
id|reserv1
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_APPLICOM_H__ */
eof
