multiline_comment|/* DO NOT EDIT - Generated automatically by script_asm.pl */
DECL|variable|SCRIPT
r_static
id|u32
id|SCRIPT
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&n;&n;&n;&n;&n;&n;ABSOLUTE dsa_select  = 0&n;ABSOLUTE dsa_msgout  = 8&n;ABSOLUTE dsa_cmnd    = 16&n;ABSOLUTE dsa_status  = 24&n;ABSOLUTE dsa_msgin   = 32&n;ABSOLUTE dsa_datain  = 40&t;&n;ABSOLUTE dsa_dataout = 1064&t;&n;ABSOLUTE dsa_size     = 2088&n;&n;ABSOLUTE reselected_identify = 0&n;ABSOLUTE msgin_buf = 0&n;&n;&n;&n;ABSOLUTE int_bad_extmsg1a&t;= 0xab930000&n;ABSOLUTE int_bad_extmsg1b&t;= 0xab930001&n;ABSOLUTE int_bad_extmsg2a&t;= 0xab930002&n;ABSOLUTE int_bad_extmsg2b&t;= 0xab930003&n;ABSOLUTE int_bad_extmsg3a&t;= 0xab930004&n;ABSOLUTE int_bad_extmsg3b&t;= 0xab930005&n;ABSOLUTE int_bad_msg1&t;&t;= 0xab930006&n;ABSOLUTE int_bad_msg2&t;&t;= 0xab930007&n;ABSOLUTE int_bad_msg3&t;&t;= 0xab930008&n;ABSOLUTE int_cmd_bad_phase&t;= 0xab930009&n;ABSOLUTE int_cmd_complete&t;= 0xab93000a&n;ABSOLUTE int_data_bad_phase&t;= 0xab93000b&n;ABSOLUTE int_msg_sdtr1&t;&t;= 0xab93000c&n;ABSOLUTE int_msg_sdtr2&t;&t;= 0xab93000d&n;ABSOLUTE int_msg_sdtr3&t;&t;= 0xab93000e&n;ABSOLUTE int_no_msgout1&t;&t;= 0xab93000f&n;ABSOLUTE int_no_msgout2&t;&t;= 0xab930010&n;ABSOLUTE int_no_msgout3&t;&t;= 0xab930011&n;ABSOLUTE int_not_cmd_complete&t;= 0xab930012&n;ABSOLUTE int_sel_no_ident&t;= 0xab930013&n;ABSOLUTE int_sel_not_cmd&t;= 0xab930014&n;ABSOLUTE int_status_not_msgin&t;= 0xab930015&n;ABSOLUTE int_resel_not_msgin&t;= 0xab930016&n;ABSOLUTE int_reselected&t;&t;= 0xab930017&n;ABSOLUTE int_selected&t;&t;= 0xab930018&n;ABSOLUTE int_disc1&t;&t;= 0xab930019&n;ABSOLUTE int_disc2&t;&t;= 0xab93001a&n;ABSOLUTE int_disc3&t;&t;= 0xab93001b&n;ABSOLUTE int_not_rej&t;&t;= 0xab93001c&n;&n;&n;&n;&n;ABSOLUTE had_select&t;= 0x01&n;ABSOLUTE had_msgout&t;= 0x02&n;ABSOLUTE had_cmdout&t;= 0x04&n;ABSOLUTE had_datain&t;= 0x08&n;ABSOLUTE had_dataout&t;= 0x10&n;ABSOLUTE had_status&t;= 0x20&n;ABSOLUTE had_msgin&t;= 0x40&n;ABSOLUTE had_extmsg&t;= 0x80&n;&n;&n;&n;&n;&n;&n;ENTRY do_select&n;do_select:&n;&t;CLEAR TARGET&n;&n;at 0x00000000 : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 &amp; 0 TO SCRATCH0&n;&n;at 0x00000002 : */
l_int|0x7c340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;; Enable selection timer&n;&t;MOVE CTEST7 &amp; 0xef TO CTEST7&n;&n;at 0x00000004 : */
l_int|0x7c1bef00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;SELECT ATN FROM dsa_select, reselect&n;&n;at 0x00000006 : */
l_int|0x43000000
comma
l_int|0x00000c48
comma
multiline_comment|/*&n;&t;JUMP get_status, WHEN STATUS&n;&n;at 0x00000008 : */
l_int|0x830b0000
comma
l_int|0x000000a0
comma
multiline_comment|/*&n;&t;; Disable selection timer&n;&t;MOVE CTEST7 | 0x10 TO CTEST7&n;&n;at 0x0000000a : */
l_int|0x7a1b1000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 | had_select TO SCRATCH0&n;&n;at 0x0000000c : */
l_int|0x7a340100
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_sel_no_ident, IF NOT MSG_OUT&n;&n;at 0x0000000e : */
l_int|0x9e020000
comma
l_int|0xab930013
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 | had_msgout TO SCRATCH0&n;&n;at 0x00000010 : */
l_int|0x7a340200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_msgout, when MSG_OUT&n;&n;at 0x00000012 : */
l_int|0x1e000000
comma
l_int|0x00000008
comma
multiline_comment|/*&n;ENTRY done_ident&n;done_ident:&n;&t;JUMP get_status, IF STATUS&n;&n;at 0x00000014 : */
l_int|0x830a0000
comma
l_int|0x000000a0
comma
multiline_comment|/*&n;redo_msgin1:&n;&t;JUMP get_msgin1, WHEN MSG_IN&n;&n;at 0x00000016 : */
l_int|0x870b0000
comma
l_int|0x00000920
comma
multiline_comment|/*&n;&t;INT int_sel_not_cmd, IF NOT CMD&n;&n;at 0x00000018 : */
l_int|0x9a020000
comma
l_int|0xab930014
comma
multiline_comment|/*&n;ENTRY resume_cmd&n;resume_cmd:&n;&t;MOVE SCRATCH0 | had_cmdout TO SCRATCH0&n;&n;at 0x0000001a : */
l_int|0x7a340400
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_cmnd, WHEN CMD&n;&n;at 0x0000001c : */
l_int|0x1a000000
comma
l_int|0x00000010
comma
multiline_comment|/*&n;ENTRY resume_pmm&n;resume_pmm:&n;redo_msgin2:&n;&t;JUMP get_msgin2, WHEN MSG_IN&n;&n;at 0x0000001e : */
l_int|0x870b0000
comma
l_int|0x00000a20
comma
multiline_comment|/*&n;&t;JUMP get_status, IF STATUS&n;&n;at 0x00000020 : */
l_int|0x830a0000
comma
l_int|0x000000a0
comma
multiline_comment|/*&n;&t;JUMP input_data, IF DATA_IN&n;&n;at 0x00000022 : */
l_int|0x810a0000
comma
l_int|0x000000e0
comma
multiline_comment|/*&n;&t;JUMP output_data, IF DATA_OUT&n;&n;at 0x00000024 : */
l_int|0x800a0000
comma
l_int|0x000004f8
comma
multiline_comment|/*&n;&t;INT int_cmd_bad_phase&n;&n;at 0x00000026 : */
l_int|0x98080000
comma
l_int|0xab930009
comma
multiline_comment|/*&n;&n;get_status:&n;&t;; Disable selection timer&n;&t;MOVE CTEST7 | 0x10 TO CTEST7&n;&n;at 0x00000028 : */
l_int|0x7a1b1000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_status, WHEN STATUS&n;&n;at 0x0000002a : */
l_int|0x1b000000
comma
l_int|0x00000018
comma
multiline_comment|/*&n;&t;INT int_status_not_msgin, WHEN NOT MSG_IN&n;&n;at 0x0000002c : */
l_int|0x9f030000
comma
l_int|0xab930015
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_msgin, WHEN MSG_IN&n;&n;at 0x0000002e : */
l_int|0x1f000000
comma
l_int|0x00000020
comma
multiline_comment|/*&n;&t;INT int_not_cmd_complete, IF NOT 0x00&n;&n;at 0x00000030 : */
l_int|0x98040000
comma
l_int|0xab930012
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x00000032 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY wait_disc_complete&n;wait_disc_complete:&n;&t;WAIT DISCONNECT&n;&n;at 0x00000034 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_cmd_complete&n;&n;at 0x00000036 : */
l_int|0x98080000
comma
l_int|0xab93000a
comma
multiline_comment|/*&n;&n;input_data:&n;&t;MOVE SCRATCH0 | had_datain TO SCRATCH0&n;&n;at 0x00000038 : */
l_int|0x7a340800
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY patch_input_data&n;patch_input_data:&n;&t;JUMP 0&n;&n;at 0x0000003a : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0000, WHEN DATA_IN&n;&n;at 0x0000003c : */
l_int|0x19000000
comma
l_int|0x00000028
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0008, WHEN DATA_IN&n;&n;at 0x0000003e : */
l_int|0x19000000
comma
l_int|0x00000030
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0010, WHEN DATA_IN&n;&n;at 0x00000040 : */
l_int|0x19000000
comma
l_int|0x00000038
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0018, WHEN DATA_IN&n;&n;at 0x00000042 : */
l_int|0x19000000
comma
l_int|0x00000040
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0020, WHEN DATA_IN&n;&n;at 0x00000044 : */
l_int|0x19000000
comma
l_int|0x00000048
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0028, WHEN DATA_IN&n;&n;at 0x00000046 : */
l_int|0x19000000
comma
l_int|0x00000050
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0030, WHEN DATA_IN&n;&n;at 0x00000048 : */
l_int|0x19000000
comma
l_int|0x00000058
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0038, WHEN DATA_IN&n;&n;at 0x0000004a : */
l_int|0x19000000
comma
l_int|0x00000060
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0040, WHEN DATA_IN&n;&n;at 0x0000004c : */
l_int|0x19000000
comma
l_int|0x00000068
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0048, WHEN DATA_IN&n;&n;at 0x0000004e : */
l_int|0x19000000
comma
l_int|0x00000070
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0050, WHEN DATA_IN&n;&n;at 0x00000050 : */
l_int|0x19000000
comma
l_int|0x00000078
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0058, WHEN DATA_IN&n;&n;at 0x00000052 : */
l_int|0x19000000
comma
l_int|0x00000080
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0060, WHEN DATA_IN&n;&n;at 0x00000054 : */
l_int|0x19000000
comma
l_int|0x00000088
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0068, WHEN DATA_IN&n;&n;at 0x00000056 : */
l_int|0x19000000
comma
l_int|0x00000090
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0070, WHEN DATA_IN&n;&n;at 0x00000058 : */
l_int|0x19000000
comma
l_int|0x00000098
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0078, WHEN DATA_IN&n;&n;at 0x0000005a : */
l_int|0x19000000
comma
l_int|0x000000a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0080, WHEN DATA_IN&n;&n;at 0x0000005c : */
l_int|0x19000000
comma
l_int|0x000000a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0088, WHEN DATA_IN&n;&n;at 0x0000005e : */
l_int|0x19000000
comma
l_int|0x000000b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0090, WHEN DATA_IN&n;&n;at 0x00000060 : */
l_int|0x19000000
comma
l_int|0x000000b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0098, WHEN DATA_IN&n;&n;at 0x00000062 : */
l_int|0x19000000
comma
l_int|0x000000c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00a0, WHEN DATA_IN&n;&n;at 0x00000064 : */
l_int|0x19000000
comma
l_int|0x000000c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00a8, WHEN DATA_IN&n;&n;at 0x00000066 : */
l_int|0x19000000
comma
l_int|0x000000d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00b0, WHEN DATA_IN&n;&n;at 0x00000068 : */
l_int|0x19000000
comma
l_int|0x000000d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00b8, WHEN DATA_IN&n;&n;at 0x0000006a : */
l_int|0x19000000
comma
l_int|0x000000e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00c0, WHEN DATA_IN&n;&n;at 0x0000006c : */
l_int|0x19000000
comma
l_int|0x000000e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00c8, WHEN DATA_IN&n;&n;at 0x0000006e : */
l_int|0x19000000
comma
l_int|0x000000f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00d0, WHEN DATA_IN&n;&n;at 0x00000070 : */
l_int|0x19000000
comma
l_int|0x000000f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00d8, WHEN DATA_IN&n;&n;at 0x00000072 : */
l_int|0x19000000
comma
l_int|0x00000100
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00e0, WHEN DATA_IN&n;&n;at 0x00000074 : */
l_int|0x19000000
comma
l_int|0x00000108
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00e8, WHEN DATA_IN&n;&n;at 0x00000076 : */
l_int|0x19000000
comma
l_int|0x00000110
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00f0, WHEN DATA_IN&n;&n;at 0x00000078 : */
l_int|0x19000000
comma
l_int|0x00000118
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x00f8, WHEN DATA_IN&n;&n;at 0x0000007a : */
l_int|0x19000000
comma
l_int|0x00000120
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0100, WHEN DATA_IN&n;&n;at 0x0000007c : */
l_int|0x19000000
comma
l_int|0x00000128
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0108, WHEN DATA_IN&n;&n;at 0x0000007e : */
l_int|0x19000000
comma
l_int|0x00000130
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0110, WHEN DATA_IN&n;&n;at 0x00000080 : */
l_int|0x19000000
comma
l_int|0x00000138
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0118, WHEN DATA_IN&n;&n;at 0x00000082 : */
l_int|0x19000000
comma
l_int|0x00000140
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0120, WHEN DATA_IN&n;&n;at 0x00000084 : */
l_int|0x19000000
comma
l_int|0x00000148
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0128, WHEN DATA_IN&n;&n;at 0x00000086 : */
l_int|0x19000000
comma
l_int|0x00000150
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0130, WHEN DATA_IN&n;&n;at 0x00000088 : */
l_int|0x19000000
comma
l_int|0x00000158
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0138, WHEN DATA_IN&n;&n;at 0x0000008a : */
l_int|0x19000000
comma
l_int|0x00000160
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0140, WHEN DATA_IN&n;&n;at 0x0000008c : */
l_int|0x19000000
comma
l_int|0x00000168
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0148, WHEN DATA_IN&n;&n;at 0x0000008e : */
l_int|0x19000000
comma
l_int|0x00000170
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0150, WHEN DATA_IN&n;&n;at 0x00000090 : */
l_int|0x19000000
comma
l_int|0x00000178
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0158, WHEN DATA_IN&n;&n;at 0x00000092 : */
l_int|0x19000000
comma
l_int|0x00000180
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0160, WHEN DATA_IN&n;&n;at 0x00000094 : */
l_int|0x19000000
comma
l_int|0x00000188
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0168, WHEN DATA_IN&n;&n;at 0x00000096 : */
l_int|0x19000000
comma
l_int|0x00000190
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0170, WHEN DATA_IN&n;&n;at 0x00000098 : */
l_int|0x19000000
comma
l_int|0x00000198
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0178, WHEN DATA_IN&n;&n;at 0x0000009a : */
l_int|0x19000000
comma
l_int|0x000001a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0180, WHEN DATA_IN&n;&n;at 0x0000009c : */
l_int|0x19000000
comma
l_int|0x000001a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0188, WHEN DATA_IN&n;&n;at 0x0000009e : */
l_int|0x19000000
comma
l_int|0x000001b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0190, WHEN DATA_IN&n;&n;at 0x000000a0 : */
l_int|0x19000000
comma
l_int|0x000001b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0198, WHEN DATA_IN&n;&n;at 0x000000a2 : */
l_int|0x19000000
comma
l_int|0x000001c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01a0, WHEN DATA_IN&n;&n;at 0x000000a4 : */
l_int|0x19000000
comma
l_int|0x000001c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01a8, WHEN DATA_IN&n;&n;at 0x000000a6 : */
l_int|0x19000000
comma
l_int|0x000001d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01b0, WHEN DATA_IN&n;&n;at 0x000000a8 : */
l_int|0x19000000
comma
l_int|0x000001d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01b8, WHEN DATA_IN&n;&n;at 0x000000aa : */
l_int|0x19000000
comma
l_int|0x000001e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01c0, WHEN DATA_IN&n;&n;at 0x000000ac : */
l_int|0x19000000
comma
l_int|0x000001e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01c8, WHEN DATA_IN&n;&n;at 0x000000ae : */
l_int|0x19000000
comma
l_int|0x000001f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01d0, WHEN DATA_IN&n;&n;at 0x000000b0 : */
l_int|0x19000000
comma
l_int|0x000001f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01d8, WHEN DATA_IN&n;&n;at 0x000000b2 : */
l_int|0x19000000
comma
l_int|0x00000200
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01e0, WHEN DATA_IN&n;&n;at 0x000000b4 : */
l_int|0x19000000
comma
l_int|0x00000208
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01e8, WHEN DATA_IN&n;&n;at 0x000000b6 : */
l_int|0x19000000
comma
l_int|0x00000210
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01f0, WHEN DATA_IN&n;&n;at 0x000000b8 : */
l_int|0x19000000
comma
l_int|0x00000218
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x01f8, WHEN DATA_IN&n;&n;at 0x000000ba : */
l_int|0x19000000
comma
l_int|0x00000220
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0200, WHEN DATA_IN&n;&n;at 0x000000bc : */
l_int|0x19000000
comma
l_int|0x00000228
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0208, WHEN DATA_IN&n;&n;at 0x000000be : */
l_int|0x19000000
comma
l_int|0x00000230
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0210, WHEN DATA_IN&n;&n;at 0x000000c0 : */
l_int|0x19000000
comma
l_int|0x00000238
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0218, WHEN DATA_IN&n;&n;at 0x000000c2 : */
l_int|0x19000000
comma
l_int|0x00000240
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0220, WHEN DATA_IN&n;&n;at 0x000000c4 : */
l_int|0x19000000
comma
l_int|0x00000248
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0228, WHEN DATA_IN&n;&n;at 0x000000c6 : */
l_int|0x19000000
comma
l_int|0x00000250
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0230, WHEN DATA_IN&n;&n;at 0x000000c8 : */
l_int|0x19000000
comma
l_int|0x00000258
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0238, WHEN DATA_IN&n;&n;at 0x000000ca : */
l_int|0x19000000
comma
l_int|0x00000260
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0240, WHEN DATA_IN&n;&n;at 0x000000cc : */
l_int|0x19000000
comma
l_int|0x00000268
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0248, WHEN DATA_IN&n;&n;at 0x000000ce : */
l_int|0x19000000
comma
l_int|0x00000270
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0250, WHEN DATA_IN&n;&n;at 0x000000d0 : */
l_int|0x19000000
comma
l_int|0x00000278
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0258, WHEN DATA_IN&n;&n;at 0x000000d2 : */
l_int|0x19000000
comma
l_int|0x00000280
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0260, WHEN DATA_IN&n;&n;at 0x000000d4 : */
l_int|0x19000000
comma
l_int|0x00000288
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0268, WHEN DATA_IN&n;&n;at 0x000000d6 : */
l_int|0x19000000
comma
l_int|0x00000290
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0270, WHEN DATA_IN&n;&n;at 0x000000d8 : */
l_int|0x19000000
comma
l_int|0x00000298
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0278, WHEN DATA_IN&n;&n;at 0x000000da : */
l_int|0x19000000
comma
l_int|0x000002a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0280, WHEN DATA_IN&n;&n;at 0x000000dc : */
l_int|0x19000000
comma
l_int|0x000002a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0288, WHEN DATA_IN&n;&n;at 0x000000de : */
l_int|0x19000000
comma
l_int|0x000002b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0290, WHEN DATA_IN&n;&n;at 0x000000e0 : */
l_int|0x19000000
comma
l_int|0x000002b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0298, WHEN DATA_IN&n;&n;at 0x000000e2 : */
l_int|0x19000000
comma
l_int|0x000002c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02a0, WHEN DATA_IN&n;&n;at 0x000000e4 : */
l_int|0x19000000
comma
l_int|0x000002c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02a8, WHEN DATA_IN&n;&n;at 0x000000e6 : */
l_int|0x19000000
comma
l_int|0x000002d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02b0, WHEN DATA_IN&n;&n;at 0x000000e8 : */
l_int|0x19000000
comma
l_int|0x000002d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02b8, WHEN DATA_IN&n;&n;at 0x000000ea : */
l_int|0x19000000
comma
l_int|0x000002e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02c0, WHEN DATA_IN&n;&n;at 0x000000ec : */
l_int|0x19000000
comma
l_int|0x000002e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02c8, WHEN DATA_IN&n;&n;at 0x000000ee : */
l_int|0x19000000
comma
l_int|0x000002f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02d0, WHEN DATA_IN&n;&n;at 0x000000f0 : */
l_int|0x19000000
comma
l_int|0x000002f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02d8, WHEN DATA_IN&n;&n;at 0x000000f2 : */
l_int|0x19000000
comma
l_int|0x00000300
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02e0, WHEN DATA_IN&n;&n;at 0x000000f4 : */
l_int|0x19000000
comma
l_int|0x00000308
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02e8, WHEN DATA_IN&n;&n;at 0x000000f6 : */
l_int|0x19000000
comma
l_int|0x00000310
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02f0, WHEN DATA_IN&n;&n;at 0x000000f8 : */
l_int|0x19000000
comma
l_int|0x00000318
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x02f8, WHEN DATA_IN&n;&n;at 0x000000fa : */
l_int|0x19000000
comma
l_int|0x00000320
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0300, WHEN DATA_IN&n;&n;at 0x000000fc : */
l_int|0x19000000
comma
l_int|0x00000328
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0308, WHEN DATA_IN&n;&n;at 0x000000fe : */
l_int|0x19000000
comma
l_int|0x00000330
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0310, WHEN DATA_IN&n;&n;at 0x00000100 : */
l_int|0x19000000
comma
l_int|0x00000338
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0318, WHEN DATA_IN&n;&n;at 0x00000102 : */
l_int|0x19000000
comma
l_int|0x00000340
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0320, WHEN DATA_IN&n;&n;at 0x00000104 : */
l_int|0x19000000
comma
l_int|0x00000348
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0328, WHEN DATA_IN&n;&n;at 0x00000106 : */
l_int|0x19000000
comma
l_int|0x00000350
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0330, WHEN DATA_IN&n;&n;at 0x00000108 : */
l_int|0x19000000
comma
l_int|0x00000358
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0338, WHEN DATA_IN&n;&n;at 0x0000010a : */
l_int|0x19000000
comma
l_int|0x00000360
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0340, WHEN DATA_IN&n;&n;at 0x0000010c : */
l_int|0x19000000
comma
l_int|0x00000368
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0348, WHEN DATA_IN&n;&n;at 0x0000010e : */
l_int|0x19000000
comma
l_int|0x00000370
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0350, WHEN DATA_IN&n;&n;at 0x00000110 : */
l_int|0x19000000
comma
l_int|0x00000378
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0358, WHEN DATA_IN&n;&n;at 0x00000112 : */
l_int|0x19000000
comma
l_int|0x00000380
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0360, WHEN DATA_IN&n;&n;at 0x00000114 : */
l_int|0x19000000
comma
l_int|0x00000388
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0368, WHEN DATA_IN&n;&n;at 0x00000116 : */
l_int|0x19000000
comma
l_int|0x00000390
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0370, WHEN DATA_IN&n;&n;at 0x00000118 : */
l_int|0x19000000
comma
l_int|0x00000398
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0378, WHEN DATA_IN&n;&n;at 0x0000011a : */
l_int|0x19000000
comma
l_int|0x000003a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0380, WHEN DATA_IN&n;&n;at 0x0000011c : */
l_int|0x19000000
comma
l_int|0x000003a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0388, WHEN DATA_IN&n;&n;at 0x0000011e : */
l_int|0x19000000
comma
l_int|0x000003b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0390, WHEN DATA_IN&n;&n;at 0x00000120 : */
l_int|0x19000000
comma
l_int|0x000003b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x0398, WHEN DATA_IN&n;&n;at 0x00000122 : */
l_int|0x19000000
comma
l_int|0x000003c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03a0, WHEN DATA_IN&n;&n;at 0x00000124 : */
l_int|0x19000000
comma
l_int|0x000003c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03a8, WHEN DATA_IN&n;&n;at 0x00000126 : */
l_int|0x19000000
comma
l_int|0x000003d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03b0, WHEN DATA_IN&n;&n;at 0x00000128 : */
l_int|0x19000000
comma
l_int|0x000003d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03b8, WHEN DATA_IN&n;&n;at 0x0000012a : */
l_int|0x19000000
comma
l_int|0x000003e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03c0, WHEN DATA_IN&n;&n;at 0x0000012c : */
l_int|0x19000000
comma
l_int|0x000003e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03c8, WHEN DATA_IN&n;&n;at 0x0000012e : */
l_int|0x19000000
comma
l_int|0x000003f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03d0, WHEN DATA_IN&n;&n;at 0x00000130 : */
l_int|0x19000000
comma
l_int|0x000003f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03d8, WHEN DATA_IN&n;&n;at 0x00000132 : */
l_int|0x19000000
comma
l_int|0x00000400
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03e0, WHEN DATA_IN&n;&n;at 0x00000134 : */
l_int|0x19000000
comma
l_int|0x00000408
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03e8, WHEN DATA_IN&n;&n;at 0x00000136 : */
l_int|0x19000000
comma
l_int|0x00000410
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03f0, WHEN DATA_IN&n;&n;at 0x00000138 : */
l_int|0x19000000
comma
l_int|0x00000418
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_datain+0x03f8, WHEN DATA_IN&n;&n;at 0x0000013a : */
l_int|0x19000000
comma
l_int|0x00000420
comma
multiline_comment|/*&n;&t;JUMP end_data_trans&n;&n;at 0x0000013c : */
l_int|0x80080000
comma
l_int|0x00000908
comma
multiline_comment|/*&n;&n;output_data:&n;&t;MOVE SCRATCH0 | had_dataout TO SCRATCH0&n;&n;at 0x0000013e : */
l_int|0x7a341000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY patch_output_data&n;patch_output_data:&n;&t;JUMP 0&n;&n;at 0x00000140 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0000, WHEN DATA_OUT&n;&n;at 0x00000142 : */
l_int|0x18000000
comma
l_int|0x00000428
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0008, WHEN DATA_OUT&n;&n;at 0x00000144 : */
l_int|0x18000000
comma
l_int|0x00000430
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0010, WHEN DATA_OUT&n;&n;at 0x00000146 : */
l_int|0x18000000
comma
l_int|0x00000438
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0018, WHEN DATA_OUT&n;&n;at 0x00000148 : */
l_int|0x18000000
comma
l_int|0x00000440
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0020, WHEN DATA_OUT&n;&n;at 0x0000014a : */
l_int|0x18000000
comma
l_int|0x00000448
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0028, WHEN DATA_OUT&n;&n;at 0x0000014c : */
l_int|0x18000000
comma
l_int|0x00000450
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0030, WHEN DATA_OUT&n;&n;at 0x0000014e : */
l_int|0x18000000
comma
l_int|0x00000458
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0038, WHEN DATA_OUT&n;&n;at 0x00000150 : */
l_int|0x18000000
comma
l_int|0x00000460
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0040, WHEN DATA_OUT&n;&n;at 0x00000152 : */
l_int|0x18000000
comma
l_int|0x00000468
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0048, WHEN DATA_OUT&n;&n;at 0x00000154 : */
l_int|0x18000000
comma
l_int|0x00000470
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0050, WHEN DATA_OUT&n;&n;at 0x00000156 : */
l_int|0x18000000
comma
l_int|0x00000478
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0058, WHEN DATA_OUT&n;&n;at 0x00000158 : */
l_int|0x18000000
comma
l_int|0x00000480
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0060, WHEN DATA_OUT&n;&n;at 0x0000015a : */
l_int|0x18000000
comma
l_int|0x00000488
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0068, WHEN DATA_OUT&n;&n;at 0x0000015c : */
l_int|0x18000000
comma
l_int|0x00000490
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0070, WHEN DATA_OUT&n;&n;at 0x0000015e : */
l_int|0x18000000
comma
l_int|0x00000498
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0078, WHEN DATA_OUT&n;&n;at 0x00000160 : */
l_int|0x18000000
comma
l_int|0x000004a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0080, WHEN DATA_OUT&n;&n;at 0x00000162 : */
l_int|0x18000000
comma
l_int|0x000004a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0088, WHEN DATA_OUT&n;&n;at 0x00000164 : */
l_int|0x18000000
comma
l_int|0x000004b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0090, WHEN DATA_OUT&n;&n;at 0x00000166 : */
l_int|0x18000000
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0098, WHEN DATA_OUT&n;&n;at 0x00000168 : */
l_int|0x18000000
comma
l_int|0x000004c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00a0, WHEN DATA_OUT&n;&n;at 0x0000016a : */
l_int|0x18000000
comma
l_int|0x000004c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00a8, WHEN DATA_OUT&n;&n;at 0x0000016c : */
l_int|0x18000000
comma
l_int|0x000004d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00b0, WHEN DATA_OUT&n;&n;at 0x0000016e : */
l_int|0x18000000
comma
l_int|0x000004d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00b8, WHEN DATA_OUT&n;&n;at 0x00000170 : */
l_int|0x18000000
comma
l_int|0x000004e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00c0, WHEN DATA_OUT&n;&n;at 0x00000172 : */
l_int|0x18000000
comma
l_int|0x000004e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00c8, WHEN DATA_OUT&n;&n;at 0x00000174 : */
l_int|0x18000000
comma
l_int|0x000004f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00d0, WHEN DATA_OUT&n;&n;at 0x00000176 : */
l_int|0x18000000
comma
l_int|0x000004f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00d8, WHEN DATA_OUT&n;&n;at 0x00000178 : */
l_int|0x18000000
comma
l_int|0x00000500
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00e0, WHEN DATA_OUT&n;&n;at 0x0000017a : */
l_int|0x18000000
comma
l_int|0x00000508
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00e8, WHEN DATA_OUT&n;&n;at 0x0000017c : */
l_int|0x18000000
comma
l_int|0x00000510
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00f0, WHEN DATA_OUT&n;&n;at 0x0000017e : */
l_int|0x18000000
comma
l_int|0x00000518
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x00f8, WHEN DATA_OUT&n;&n;at 0x00000180 : */
l_int|0x18000000
comma
l_int|0x00000520
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0100, WHEN DATA_OUT&n;&n;at 0x00000182 : */
l_int|0x18000000
comma
l_int|0x00000528
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0108, WHEN DATA_OUT&n;&n;at 0x00000184 : */
l_int|0x18000000
comma
l_int|0x00000530
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0110, WHEN DATA_OUT&n;&n;at 0x00000186 : */
l_int|0x18000000
comma
l_int|0x00000538
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0118, WHEN DATA_OUT&n;&n;at 0x00000188 : */
l_int|0x18000000
comma
l_int|0x00000540
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0120, WHEN DATA_OUT&n;&n;at 0x0000018a : */
l_int|0x18000000
comma
l_int|0x00000548
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0128, WHEN DATA_OUT&n;&n;at 0x0000018c : */
l_int|0x18000000
comma
l_int|0x00000550
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0130, WHEN DATA_OUT&n;&n;at 0x0000018e : */
l_int|0x18000000
comma
l_int|0x00000558
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0138, WHEN DATA_OUT&n;&n;at 0x00000190 : */
l_int|0x18000000
comma
l_int|0x00000560
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0140, WHEN DATA_OUT&n;&n;at 0x00000192 : */
l_int|0x18000000
comma
l_int|0x00000568
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0148, WHEN DATA_OUT&n;&n;at 0x00000194 : */
l_int|0x18000000
comma
l_int|0x00000570
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0150, WHEN DATA_OUT&n;&n;at 0x00000196 : */
l_int|0x18000000
comma
l_int|0x00000578
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0158, WHEN DATA_OUT&n;&n;at 0x00000198 : */
l_int|0x18000000
comma
l_int|0x00000580
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0160, WHEN DATA_OUT&n;&n;at 0x0000019a : */
l_int|0x18000000
comma
l_int|0x00000588
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0168, WHEN DATA_OUT&n;&n;at 0x0000019c : */
l_int|0x18000000
comma
l_int|0x00000590
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0170, WHEN DATA_OUT&n;&n;at 0x0000019e : */
l_int|0x18000000
comma
l_int|0x00000598
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0178, WHEN DATA_OUT&n;&n;at 0x000001a0 : */
l_int|0x18000000
comma
l_int|0x000005a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0180, WHEN DATA_OUT&n;&n;at 0x000001a2 : */
l_int|0x18000000
comma
l_int|0x000005a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0188, WHEN DATA_OUT&n;&n;at 0x000001a4 : */
l_int|0x18000000
comma
l_int|0x000005b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0190, WHEN DATA_OUT&n;&n;at 0x000001a6 : */
l_int|0x18000000
comma
l_int|0x000005b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0198, WHEN DATA_OUT&n;&n;at 0x000001a8 : */
l_int|0x18000000
comma
l_int|0x000005c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01a0, WHEN DATA_OUT&n;&n;at 0x000001aa : */
l_int|0x18000000
comma
l_int|0x000005c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01a8, WHEN DATA_OUT&n;&n;at 0x000001ac : */
l_int|0x18000000
comma
l_int|0x000005d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01b0, WHEN DATA_OUT&n;&n;at 0x000001ae : */
l_int|0x18000000
comma
l_int|0x000005d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01b8, WHEN DATA_OUT&n;&n;at 0x000001b0 : */
l_int|0x18000000
comma
l_int|0x000005e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01c0, WHEN DATA_OUT&n;&n;at 0x000001b2 : */
l_int|0x18000000
comma
l_int|0x000005e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01c8, WHEN DATA_OUT&n;&n;at 0x000001b4 : */
l_int|0x18000000
comma
l_int|0x000005f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01d0, WHEN DATA_OUT&n;&n;at 0x000001b6 : */
l_int|0x18000000
comma
l_int|0x000005f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01d8, WHEN DATA_OUT&n;&n;at 0x000001b8 : */
l_int|0x18000000
comma
l_int|0x00000600
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01e0, WHEN DATA_OUT&n;&n;at 0x000001ba : */
l_int|0x18000000
comma
l_int|0x00000608
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01e8, WHEN DATA_OUT&n;&n;at 0x000001bc : */
l_int|0x18000000
comma
l_int|0x00000610
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01f0, WHEN DATA_OUT&n;&n;at 0x000001be : */
l_int|0x18000000
comma
l_int|0x00000618
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x01f8, WHEN DATA_OUT&n;&n;at 0x000001c0 : */
l_int|0x18000000
comma
l_int|0x00000620
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0200, WHEN DATA_OUT&n;&n;at 0x000001c2 : */
l_int|0x18000000
comma
l_int|0x00000628
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0208, WHEN DATA_OUT&n;&n;at 0x000001c4 : */
l_int|0x18000000
comma
l_int|0x00000630
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0210, WHEN DATA_OUT&n;&n;at 0x000001c6 : */
l_int|0x18000000
comma
l_int|0x00000638
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0218, WHEN DATA_OUT&n;&n;at 0x000001c8 : */
l_int|0x18000000
comma
l_int|0x00000640
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0220, WHEN DATA_OUT&n;&n;at 0x000001ca : */
l_int|0x18000000
comma
l_int|0x00000648
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0228, WHEN DATA_OUT&n;&n;at 0x000001cc : */
l_int|0x18000000
comma
l_int|0x00000650
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0230, WHEN DATA_OUT&n;&n;at 0x000001ce : */
l_int|0x18000000
comma
l_int|0x00000658
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0238, WHEN DATA_OUT&n;&n;at 0x000001d0 : */
l_int|0x18000000
comma
l_int|0x00000660
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0240, WHEN DATA_OUT&n;&n;at 0x000001d2 : */
l_int|0x18000000
comma
l_int|0x00000668
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0248, WHEN DATA_OUT&n;&n;at 0x000001d4 : */
l_int|0x18000000
comma
l_int|0x00000670
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0250, WHEN DATA_OUT&n;&n;at 0x000001d6 : */
l_int|0x18000000
comma
l_int|0x00000678
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0258, WHEN DATA_OUT&n;&n;at 0x000001d8 : */
l_int|0x18000000
comma
l_int|0x00000680
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0260, WHEN DATA_OUT&n;&n;at 0x000001da : */
l_int|0x18000000
comma
l_int|0x00000688
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0268, WHEN DATA_OUT&n;&n;at 0x000001dc : */
l_int|0x18000000
comma
l_int|0x00000690
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0270, WHEN DATA_OUT&n;&n;at 0x000001de : */
l_int|0x18000000
comma
l_int|0x00000698
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0278, WHEN DATA_OUT&n;&n;at 0x000001e0 : */
l_int|0x18000000
comma
l_int|0x000006a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0280, WHEN DATA_OUT&n;&n;at 0x000001e2 : */
l_int|0x18000000
comma
l_int|0x000006a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0288, WHEN DATA_OUT&n;&n;at 0x000001e4 : */
l_int|0x18000000
comma
l_int|0x000006b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0290, WHEN DATA_OUT&n;&n;at 0x000001e6 : */
l_int|0x18000000
comma
l_int|0x000006b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0298, WHEN DATA_OUT&n;&n;at 0x000001e8 : */
l_int|0x18000000
comma
l_int|0x000006c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02a0, WHEN DATA_OUT&n;&n;at 0x000001ea : */
l_int|0x18000000
comma
l_int|0x000006c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02a8, WHEN DATA_OUT&n;&n;at 0x000001ec : */
l_int|0x18000000
comma
l_int|0x000006d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02b0, WHEN DATA_OUT&n;&n;at 0x000001ee : */
l_int|0x18000000
comma
l_int|0x000006d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02b8, WHEN DATA_OUT&n;&n;at 0x000001f0 : */
l_int|0x18000000
comma
l_int|0x000006e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02c0, WHEN DATA_OUT&n;&n;at 0x000001f2 : */
l_int|0x18000000
comma
l_int|0x000006e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02c8, WHEN DATA_OUT&n;&n;at 0x000001f4 : */
l_int|0x18000000
comma
l_int|0x000006f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02d0, WHEN DATA_OUT&n;&n;at 0x000001f6 : */
l_int|0x18000000
comma
l_int|0x000006f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02d8, WHEN DATA_OUT&n;&n;at 0x000001f8 : */
l_int|0x18000000
comma
l_int|0x00000700
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02e0, WHEN DATA_OUT&n;&n;at 0x000001fa : */
l_int|0x18000000
comma
l_int|0x00000708
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02e8, WHEN DATA_OUT&n;&n;at 0x000001fc : */
l_int|0x18000000
comma
l_int|0x00000710
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02f0, WHEN DATA_OUT&n;&n;at 0x000001fe : */
l_int|0x18000000
comma
l_int|0x00000718
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x02f8, WHEN DATA_OUT&n;&n;at 0x00000200 : */
l_int|0x18000000
comma
l_int|0x00000720
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0300, WHEN DATA_OUT&n;&n;at 0x00000202 : */
l_int|0x18000000
comma
l_int|0x00000728
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0308, WHEN DATA_OUT&n;&n;at 0x00000204 : */
l_int|0x18000000
comma
l_int|0x00000730
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0310, WHEN DATA_OUT&n;&n;at 0x00000206 : */
l_int|0x18000000
comma
l_int|0x00000738
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0318, WHEN DATA_OUT&n;&n;at 0x00000208 : */
l_int|0x18000000
comma
l_int|0x00000740
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0320, WHEN DATA_OUT&n;&n;at 0x0000020a : */
l_int|0x18000000
comma
l_int|0x00000748
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0328, WHEN DATA_OUT&n;&n;at 0x0000020c : */
l_int|0x18000000
comma
l_int|0x00000750
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0330, WHEN DATA_OUT&n;&n;at 0x0000020e : */
l_int|0x18000000
comma
l_int|0x00000758
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0338, WHEN DATA_OUT&n;&n;at 0x00000210 : */
l_int|0x18000000
comma
l_int|0x00000760
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0340, WHEN DATA_OUT&n;&n;at 0x00000212 : */
l_int|0x18000000
comma
l_int|0x00000768
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0348, WHEN DATA_OUT&n;&n;at 0x00000214 : */
l_int|0x18000000
comma
l_int|0x00000770
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0350, WHEN DATA_OUT&n;&n;at 0x00000216 : */
l_int|0x18000000
comma
l_int|0x00000778
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0358, WHEN DATA_OUT&n;&n;at 0x00000218 : */
l_int|0x18000000
comma
l_int|0x00000780
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0360, WHEN DATA_OUT&n;&n;at 0x0000021a : */
l_int|0x18000000
comma
l_int|0x00000788
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0368, WHEN DATA_OUT&n;&n;at 0x0000021c : */
l_int|0x18000000
comma
l_int|0x00000790
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0370, WHEN DATA_OUT&n;&n;at 0x0000021e : */
l_int|0x18000000
comma
l_int|0x00000798
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0378, WHEN DATA_OUT&n;&n;at 0x00000220 : */
l_int|0x18000000
comma
l_int|0x000007a0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0380, WHEN DATA_OUT&n;&n;at 0x00000222 : */
l_int|0x18000000
comma
l_int|0x000007a8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0388, WHEN DATA_OUT&n;&n;at 0x00000224 : */
l_int|0x18000000
comma
l_int|0x000007b0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0390, WHEN DATA_OUT&n;&n;at 0x00000226 : */
l_int|0x18000000
comma
l_int|0x000007b8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x0398, WHEN DATA_OUT&n;&n;at 0x00000228 : */
l_int|0x18000000
comma
l_int|0x000007c0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03a0, WHEN DATA_OUT&n;&n;at 0x0000022a : */
l_int|0x18000000
comma
l_int|0x000007c8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03a8, WHEN DATA_OUT&n;&n;at 0x0000022c : */
l_int|0x18000000
comma
l_int|0x000007d0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03b0, WHEN DATA_OUT&n;&n;at 0x0000022e : */
l_int|0x18000000
comma
l_int|0x000007d8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03b8, WHEN DATA_OUT&n;&n;at 0x00000230 : */
l_int|0x18000000
comma
l_int|0x000007e0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03c0, WHEN DATA_OUT&n;&n;at 0x00000232 : */
l_int|0x18000000
comma
l_int|0x000007e8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03c8, WHEN DATA_OUT&n;&n;at 0x00000234 : */
l_int|0x18000000
comma
l_int|0x000007f0
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03d0, WHEN DATA_OUT&n;&n;at 0x00000236 : */
l_int|0x18000000
comma
l_int|0x000007f8
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03d8, WHEN DATA_OUT&n;&n;at 0x00000238 : */
l_int|0x18000000
comma
l_int|0x00000800
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03e0, WHEN DATA_OUT&n;&n;at 0x0000023a : */
l_int|0x18000000
comma
l_int|0x00000808
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03e8, WHEN DATA_OUT&n;&n;at 0x0000023c : */
l_int|0x18000000
comma
l_int|0x00000810
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03f0, WHEN DATA_OUT&n;&n;at 0x0000023e : */
l_int|0x18000000
comma
l_int|0x00000818
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_dataout+0x03f8, WHEN DATA_OUT&n;&n;at 0x00000240 : */
l_int|0x18000000
comma
l_int|0x00000820
comma
multiline_comment|/*&n;ENTRY end_data_trans&n;end_data_trans:&n;redo_msgin3:&n;&t;JUMP get_status, WHEN STATUS&n;&n;at 0x00000242 : */
l_int|0x830b0000
comma
l_int|0x000000a0
comma
multiline_comment|/*&n;&t;JUMP get_msgin3, WHEN MSG_IN&n;&n;at 0x00000244 : */
l_int|0x870b0000
comma
l_int|0x00000b20
comma
multiline_comment|/*&n;&t;INT int_data_bad_phase&n;&n;at 0x00000246 : */
l_int|0x98080000
comma
l_int|0xab93000b
comma
multiline_comment|/*&n;&n;get_msgin1:&n;&t;MOVE SCRATCH0 | had_msgin TO SCRATCH0&n;&n;at 0x00000248 : */
l_int|0x7a344000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf, WHEN MSG_IN&n;&n;at 0x0000024a : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP ext_msg1, IF 0x01&t;&t;; Extended Message&n;&n;at 0x0000024c : */
l_int|0x800c0001
comma
l_int|0x00000968
comma
multiline_comment|/*&n;&t;JUMP ignore_msg1, IF 0x02&t;; Save Data Pointers&n;&n;at 0x0000024e : */
l_int|0x800c0002
comma
l_int|0x00000958
comma
multiline_comment|/*&n;&t;JUMP ignore_msg1, IF 0x03&t;; Save Restore Pointers&n;&n;at 0x00000250 : */
l_int|0x800c0003
comma
l_int|0x00000958
comma
multiline_comment|/*&n;&t;JUMP disc1, IF 0x04&t;&t;; Disconnect&n;&n;at 0x00000252 : */
l_int|0x800c0004
comma
l_int|0x000009c8
comma
multiline_comment|/*&n;&t;INT int_bad_msg1&n;&n;at 0x00000254 : */
l_int|0x98080000
comma
l_int|0xab930006
comma
multiline_comment|/*&n;ignore_msg1:&n;&t;CLEAR ACK&n;&n;at 0x00000256 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP redo_msgin1&n;&n;at 0x00000258 : */
l_int|0x80080000
comma
l_int|0x00000058
comma
multiline_comment|/*&n;ext_msg1:&n;&t;MOVE SCRATCH0 | had_extmsg TO SCRATCH0&n;&n;at 0x0000025a : */
l_int|0x7a348000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x0000025c : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf + 1, WHEN MSG_IN&n;&n;at 0x0000025e : */
l_int|0x0f000001
comma
l_int|0x00000001
comma
multiline_comment|/*&n;&t;JUMP ext_msg1a, IF 0x03&n;&n;at 0x00000260 : */
l_int|0x800c0003
comma
l_int|0x00000990
comma
multiline_comment|/*&n;&t;INT int_bad_extmsg1a&n;&n;at 0x00000262 : */
l_int|0x98080000
comma
l_int|0xab930000
comma
multiline_comment|/*&n;ext_msg1a:&n;&t;CLEAR ACK&n;&n;at 0x00000264 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf + 2, WHEN MSG_IN&n;&n;at 0x00000266 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;&t;JUMP ext_msg1b, IF 0x01&t;&t;; Must be SDTR&n;&n;at 0x00000268 : */
l_int|0x800c0001
comma
l_int|0x000009b0
comma
multiline_comment|/*&n;&t;INT int_bad_extmsg1b&n;&n;at 0x0000026a : */
l_int|0x98080000
comma
l_int|0xab930001
comma
multiline_comment|/*&n;ext_msg1b:&n;&t;CLEAR ACK&n;&n;at 0x0000026c : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 2, msgin_buf + 3, WHEN MSG_IN&n;&n;at 0x0000026e : */
l_int|0x0f000002
comma
l_int|0x00000003
comma
multiline_comment|/*&n;&t;INT int_msg_sdtr1&n;&n;at 0x00000270 : */
l_int|0x98080000
comma
l_int|0xab93000c
comma
multiline_comment|/*&n;disc1:&n;&t;CLEAR ACK&n;&n;at 0x00000272 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY wait_disc1&n;wait_disc1:&n;&t;WAIT DISCONNECT&n;&n;at 0x00000274 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_disc1&n;&n;at 0x00000276 : */
l_int|0x98080000
comma
l_int|0xab930019
comma
multiline_comment|/*&n;ENTRY resume_msgin1a&n;resume_msgin1a:&n;&t;CLEAR ACK&n;&n;at 0x00000278 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP redo_msgin1&n;&n;at 0x0000027a : */
l_int|0x80080000
comma
l_int|0x00000058
comma
multiline_comment|/*&n;ENTRY resume_msgin1b&n;resume_msgin1b:&n;&t;SET ATN&n;&n;at 0x0000027c : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x0000027e : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_no_msgout1, WHEN NOT MSG_OUT&n;&n;at 0x00000280 : */
l_int|0x9e030000
comma
l_int|0xab93000f
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 | had_msgout TO SCRATCH0&n;&n;at 0x00000282 : */
l_int|0x7a340200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_msgout, when MSG_OUT&n;&n;at 0x00000284 : */
l_int|0x1e000000
comma
l_int|0x00000008
comma
multiline_comment|/*&n;&t;JUMP redo_msgin1&n;&n;at 0x00000286 : */
l_int|0x80080000
comma
l_int|0x00000058
comma
multiline_comment|/*&n;&n;get_msgin2:&n;&t;MOVE SCRATCH0 | had_msgin TO SCRATCH0&n;&n;at 0x00000288 : */
l_int|0x7a344000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf, WHEN MSG_IN&n;&n;at 0x0000028a : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP ext_msg2, IF 0x01&t;&t;; Extended Message&n;&n;at 0x0000028c : */
l_int|0x800c0001
comma
l_int|0x00000a68
comma
multiline_comment|/*&n;&t;JUMP ignore_msg2, IF 0x02&t;; Save Data Pointers&n;&n;at 0x0000028e : */
l_int|0x800c0002
comma
l_int|0x00000a58
comma
multiline_comment|/*&n;&t;JUMP ignore_msg2, IF 0x03&t;; Save Restore Pointers&n;&n;at 0x00000290 : */
l_int|0x800c0003
comma
l_int|0x00000a58
comma
multiline_comment|/*&n;&t;JUMP disc2, IF 0x04&t;&t;; Disconnect&n;&n;at 0x00000292 : */
l_int|0x800c0004
comma
l_int|0x00000ac8
comma
multiline_comment|/*&n;&t;INT int_bad_msg2&n;&n;at 0x00000294 : */
l_int|0x98080000
comma
l_int|0xab930007
comma
multiline_comment|/*&n;ignore_msg2:&n;&t;CLEAR ACK&n;&n;at 0x00000296 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP redo_msgin2&n;&n;at 0x00000298 : */
l_int|0x80080000
comma
l_int|0x00000078
comma
multiline_comment|/*&n;ext_msg2:&n;&t;MOVE SCRATCH0 | had_extmsg TO SCRATCH0&n;&n;at 0x0000029a : */
l_int|0x7a348000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x0000029c : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf + 1, WHEN MSG_IN&n;&n;at 0x0000029e : */
l_int|0x0f000001
comma
l_int|0x00000001
comma
multiline_comment|/*&n;&t;JUMP ext_msg2a, IF 0x03&n;&n;at 0x000002a0 : */
l_int|0x800c0003
comma
l_int|0x00000a90
comma
multiline_comment|/*&n;&t;INT int_bad_extmsg2a&n;&n;at 0x000002a2 : */
l_int|0x98080000
comma
l_int|0xab930002
comma
multiline_comment|/*&n;ext_msg2a:&n;&t;CLEAR ACK&n;&n;at 0x000002a4 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf + 2, WHEN MSG_IN&n;&n;at 0x000002a6 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;&t;JUMP ext_msg2b, IF 0x01&t;&t;; Must be SDTR&n;&n;at 0x000002a8 : */
l_int|0x800c0001
comma
l_int|0x00000ab0
comma
multiline_comment|/*&n;&t;INT int_bad_extmsg2b&n;&n;at 0x000002aa : */
l_int|0x98080000
comma
l_int|0xab930003
comma
multiline_comment|/*&n;ext_msg2b:&n;&t;CLEAR ACK&n;&n;at 0x000002ac : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 2, msgin_buf + 3, WHEN MSG_IN&n;&n;at 0x000002ae : */
l_int|0x0f000002
comma
l_int|0x00000003
comma
multiline_comment|/*&n;&t;INT int_msg_sdtr2&n;&n;at 0x000002b0 : */
l_int|0x98080000
comma
l_int|0xab93000d
comma
multiline_comment|/*&n;disc2:&n;&t;CLEAR ACK&n;&n;at 0x000002b2 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY wait_disc2&n;wait_disc2:&n;&t;WAIT DISCONNECT&n;&n;at 0x000002b4 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_disc2&n;&n;at 0x000002b6 : */
l_int|0x98080000
comma
l_int|0xab93001a
comma
multiline_comment|/*&n;ENTRY resume_msgin2a&n;resume_msgin2a:&n;&t;CLEAR ACK&n;&n;at 0x000002b8 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP redo_msgin2&n;&n;at 0x000002ba : */
l_int|0x80080000
comma
l_int|0x00000078
comma
multiline_comment|/*&n;ENTRY resume_msgin2b&n;resume_msgin2b:&n;&t;SET ATN&n;&n;at 0x000002bc : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x000002be : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_no_msgout2, WHEN NOT MSG_OUT&n;&n;at 0x000002c0 : */
l_int|0x9e030000
comma
l_int|0xab930010
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 | had_msgout TO SCRATCH0&n;&n;at 0x000002c2 : */
l_int|0x7a340200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_msgout, when MSG_OUT&n;&n;at 0x000002c4 : */
l_int|0x1e000000
comma
l_int|0x00000008
comma
multiline_comment|/*&n;&t;JUMP redo_msgin2&n;&n;at 0x000002c6 : */
l_int|0x80080000
comma
l_int|0x00000078
comma
multiline_comment|/*&n;&n;get_msgin3:&n;&t;MOVE SCRATCH0 | had_msgin TO SCRATCH0&n;&n;at 0x000002c8 : */
l_int|0x7a344000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf, WHEN MSG_IN&n;&n;at 0x000002ca : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP ext_msg3, IF 0x01&t;&t;; Extended Message&n;&n;at 0x000002cc : */
l_int|0x800c0001
comma
l_int|0x00000b68
comma
multiline_comment|/*&n;&t;JUMP ignore_msg3, IF 0x02&t;; Save Data Pointers&n;&n;at 0x000002ce : */
l_int|0x800c0002
comma
l_int|0x00000b58
comma
multiline_comment|/*&n;&t;JUMP ignore_msg3, IF 0x03&t;; Save Restore Pointers&n;&n;at 0x000002d0 : */
l_int|0x800c0003
comma
l_int|0x00000b58
comma
multiline_comment|/*&n;&t;JUMP disc3, IF 0x04&t;&t;; Disconnect&n;&n;at 0x000002d2 : */
l_int|0x800c0004
comma
l_int|0x00000bc8
comma
multiline_comment|/*&n;&t;INT int_bad_msg3&n;&n;at 0x000002d4 : */
l_int|0x98080000
comma
l_int|0xab930008
comma
multiline_comment|/*&n;ignore_msg3:&n;&t;CLEAR ACK&n;&n;at 0x000002d6 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP redo_msgin3&n;&n;at 0x000002d8 : */
l_int|0x80080000
comma
l_int|0x00000908
comma
multiline_comment|/*&n;ext_msg3:&n;&t;MOVE SCRATCH0 | had_extmsg TO SCRATCH0&n;&n;at 0x000002da : */
l_int|0x7a348000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x000002dc : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf + 1, WHEN MSG_IN&n;&n;at 0x000002de : */
l_int|0x0f000001
comma
l_int|0x00000001
comma
multiline_comment|/*&n;&t;JUMP ext_msg3a, IF 0x03&n;&n;at 0x000002e0 : */
l_int|0x800c0003
comma
l_int|0x00000b90
comma
multiline_comment|/*&n;&t;INT int_bad_extmsg3a&n;&n;at 0x000002e2 : */
l_int|0x98080000
comma
l_int|0xab930004
comma
multiline_comment|/*&n;ext_msg3a:&n;&t;CLEAR ACK&n;&n;at 0x000002e4 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf + 2, WHEN MSG_IN&n;&n;at 0x000002e6 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;&t;JUMP ext_msg3b, IF 0x01&t;&t;; Must be SDTR&n;&n;at 0x000002e8 : */
l_int|0x800c0001
comma
l_int|0x00000bb0
comma
multiline_comment|/*&n;&t;INT int_bad_extmsg3b&n;&n;at 0x000002ea : */
l_int|0x98080000
comma
l_int|0xab930005
comma
multiline_comment|/*&n;ext_msg3b:&n;&t;CLEAR ACK&n;&n;at 0x000002ec : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 2, msgin_buf + 3, WHEN MSG_IN&n;&n;at 0x000002ee : */
l_int|0x0f000002
comma
l_int|0x00000003
comma
multiline_comment|/*&n;&t;INT int_msg_sdtr3&n;&n;at 0x000002f0 : */
l_int|0x98080000
comma
l_int|0xab93000e
comma
multiline_comment|/*&n;disc3:&n;&t;CLEAR ACK&n;&n;at 0x000002f2 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY wait_disc3&n;wait_disc3:&n;&t;WAIT DISCONNECT&n;&n;at 0x000002f4 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_disc3&n;&n;at 0x000002f6 : */
l_int|0x98080000
comma
l_int|0xab93001b
comma
multiline_comment|/*&n;ENTRY resume_msgin3a&n;resume_msgin3a:&n;&t;CLEAR ACK&n;&n;at 0x000002f8 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP redo_msgin3&n;&n;at 0x000002fa : */
l_int|0x80080000
comma
l_int|0x00000908
comma
multiline_comment|/*&n;ENTRY resume_msgin3b&n;resume_msgin3b:&n;&t;SET ATN&n;&n;at 0x000002fc : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x000002fe : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_no_msgout3, WHEN NOT MSG_OUT&n;&n;at 0x00000300 : */
l_int|0x9e030000
comma
l_int|0xab930011
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 | had_msgout TO SCRATCH0&n;&n;at 0x00000302 : */
l_int|0x7a340200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE FROM dsa_msgout, when MSG_OUT&n;&n;at 0x00000304 : */
l_int|0x1e000000
comma
l_int|0x00000008
comma
multiline_comment|/*&n;&t;JUMP redo_msgin3&n;&n;at 0x00000306 : */
l_int|0x80080000
comma
l_int|0x00000908
comma
multiline_comment|/*&n;&n;ENTRY resume_rej_ident&n;resume_rej_ident:&n;&t;CLEAR ATN&n;&n;at 0x00000308 : */
l_int|0x60000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE 1, msgin_buf, WHEN MSG_IN&n;&n;at 0x0000030a : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_not_rej, IF NOT 0x07&t;&t;; Reject&n;&n;at 0x0000030c : */
l_int|0x98040007
comma
l_int|0xab93001c
comma
multiline_comment|/*&n;&t;CLEAR ACK&n;&n;at 0x0000030e : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP done_ident&n;&n;at 0x00000310 : */
l_int|0x80080000
comma
l_int|0x00000050
comma
multiline_comment|/*&n;&n;ENTRY reselect&n;reselect:&n;&t;; Disable selection timer&n;&t;MOVE CTEST7 | 0x10 TO CTEST7&n;&n;at 0x00000312 : */
l_int|0x7a1b1000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;WAIT RESELECT resel_err&n;&n;at 0x00000314 : */
l_int|0x50000000
comma
l_int|0x00000c70
comma
multiline_comment|/*&n;&t;INT int_resel_not_msgin, WHEN NOT MSG_IN&n;&n;at 0x00000316 : */
l_int|0x9f030000
comma
l_int|0xab930016
comma
multiline_comment|/*&n;&t;MOVE 1, reselected_identify, WHEN MSG_IN&n;&n;at 0x00000318 : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;INT int_reselected&n;&n;at 0x0000031a : */
l_int|0x98080000
comma
l_int|0xab930017
comma
multiline_comment|/*&n;resel_err:&n;&t;MOVE CTEST2 &amp; 0x40 TO SFBR&n;&n;at 0x0000031c : */
l_int|0x74164000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP selected, IF 0x00&n;&n;at 0x0000031e : */
l_int|0x800c0000
comma
l_int|0x00000cb0
comma
multiline_comment|/*&n;&t;MOVE SFBR &amp; 0 TO SFBR&n;&n;at 0x00000320 : */
l_int|0x7c080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY patch_new_dsa&n;patch_new_dsa:&n;&t;MOVE SFBR | 0x11 TO DSA0&n;&n;at 0x00000322 : */
l_int|0x6a101100
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE SFBR | 0x22 TO DSA1&n;&n;at 0x00000324 : */
l_int|0x6a112200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE SFBR | 0x33 TO DSA2&n;&n;at 0x00000326 : */
l_int|0x6a123300
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE SFBR | 0x44 TO DSA3&n;&n;at 0x00000328 : */
l_int|0x6a134400
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP do_select&n;&n;at 0x0000032a : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;selected:&n;&t;INT int_selected&n;&n;at 0x0000032c : */
l_int|0x98080000
comma
l_int|0xab930018
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_cmnd
mdefine_line|#define A_dsa_cmnd&t;0x00000010
r_static
id|u32
id|A_dsa_cmnd_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000001d
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_datain
mdefine_line|#define A_dsa_datain&t;0x00000028
r_static
id|u32
id|A_dsa_datain_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000003d
comma
l_int|0x0000003f
comma
l_int|0x00000041
comma
l_int|0x00000043
comma
l_int|0x00000045
comma
l_int|0x00000047
comma
l_int|0x00000049
comma
l_int|0x0000004b
comma
l_int|0x0000004d
comma
l_int|0x0000004f
comma
l_int|0x00000051
comma
l_int|0x00000053
comma
l_int|0x00000055
comma
l_int|0x00000057
comma
l_int|0x00000059
comma
l_int|0x0000005b
comma
l_int|0x0000005d
comma
l_int|0x0000005f
comma
l_int|0x00000061
comma
l_int|0x00000063
comma
l_int|0x00000065
comma
l_int|0x00000067
comma
l_int|0x00000069
comma
l_int|0x0000006b
comma
l_int|0x0000006d
comma
l_int|0x0000006f
comma
l_int|0x00000071
comma
l_int|0x00000073
comma
l_int|0x00000075
comma
l_int|0x00000077
comma
l_int|0x00000079
comma
l_int|0x0000007b
comma
l_int|0x0000007d
comma
l_int|0x0000007f
comma
l_int|0x00000081
comma
l_int|0x00000083
comma
l_int|0x00000085
comma
l_int|0x00000087
comma
l_int|0x00000089
comma
l_int|0x0000008b
comma
l_int|0x0000008d
comma
l_int|0x0000008f
comma
l_int|0x00000091
comma
l_int|0x00000093
comma
l_int|0x00000095
comma
l_int|0x00000097
comma
l_int|0x00000099
comma
l_int|0x0000009b
comma
l_int|0x0000009d
comma
l_int|0x0000009f
comma
l_int|0x000000a1
comma
l_int|0x000000a3
comma
l_int|0x000000a5
comma
l_int|0x000000a7
comma
l_int|0x000000a9
comma
l_int|0x000000ab
comma
l_int|0x000000ad
comma
l_int|0x000000af
comma
l_int|0x000000b1
comma
l_int|0x000000b3
comma
l_int|0x000000b5
comma
l_int|0x000000b7
comma
l_int|0x000000b9
comma
l_int|0x000000bb
comma
l_int|0x000000bd
comma
l_int|0x000000bf
comma
l_int|0x000000c1
comma
l_int|0x000000c3
comma
l_int|0x000000c5
comma
l_int|0x000000c7
comma
l_int|0x000000c9
comma
l_int|0x000000cb
comma
l_int|0x000000cd
comma
l_int|0x000000cf
comma
l_int|0x000000d1
comma
l_int|0x000000d3
comma
l_int|0x000000d5
comma
l_int|0x000000d7
comma
l_int|0x000000d9
comma
l_int|0x000000db
comma
l_int|0x000000dd
comma
l_int|0x000000df
comma
l_int|0x000000e1
comma
l_int|0x000000e3
comma
l_int|0x000000e5
comma
l_int|0x000000e7
comma
l_int|0x000000e9
comma
l_int|0x000000eb
comma
l_int|0x000000ed
comma
l_int|0x000000ef
comma
l_int|0x000000f1
comma
l_int|0x000000f3
comma
l_int|0x000000f5
comma
l_int|0x000000f7
comma
l_int|0x000000f9
comma
l_int|0x000000fb
comma
l_int|0x000000fd
comma
l_int|0x000000ff
comma
l_int|0x00000101
comma
l_int|0x00000103
comma
l_int|0x00000105
comma
l_int|0x00000107
comma
l_int|0x00000109
comma
l_int|0x0000010b
comma
l_int|0x0000010d
comma
l_int|0x0000010f
comma
l_int|0x00000111
comma
l_int|0x00000113
comma
l_int|0x00000115
comma
l_int|0x00000117
comma
l_int|0x00000119
comma
l_int|0x0000011b
comma
l_int|0x0000011d
comma
l_int|0x0000011f
comma
l_int|0x00000121
comma
l_int|0x00000123
comma
l_int|0x00000125
comma
l_int|0x00000127
comma
l_int|0x00000129
comma
l_int|0x0000012b
comma
l_int|0x0000012d
comma
l_int|0x0000012f
comma
l_int|0x00000131
comma
l_int|0x00000133
comma
l_int|0x00000135
comma
l_int|0x00000137
comma
l_int|0x00000139
comma
l_int|0x0000013b
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_dataout
mdefine_line|#define A_dsa_dataout&t;0x00000428
r_static
id|u32
id|A_dsa_dataout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000143
comma
l_int|0x00000145
comma
l_int|0x00000147
comma
l_int|0x00000149
comma
l_int|0x0000014b
comma
l_int|0x0000014d
comma
l_int|0x0000014f
comma
l_int|0x00000151
comma
l_int|0x00000153
comma
l_int|0x00000155
comma
l_int|0x00000157
comma
l_int|0x00000159
comma
l_int|0x0000015b
comma
l_int|0x0000015d
comma
l_int|0x0000015f
comma
l_int|0x00000161
comma
l_int|0x00000163
comma
l_int|0x00000165
comma
l_int|0x00000167
comma
l_int|0x00000169
comma
l_int|0x0000016b
comma
l_int|0x0000016d
comma
l_int|0x0000016f
comma
l_int|0x00000171
comma
l_int|0x00000173
comma
l_int|0x00000175
comma
l_int|0x00000177
comma
l_int|0x00000179
comma
l_int|0x0000017b
comma
l_int|0x0000017d
comma
l_int|0x0000017f
comma
l_int|0x00000181
comma
l_int|0x00000183
comma
l_int|0x00000185
comma
l_int|0x00000187
comma
l_int|0x00000189
comma
l_int|0x0000018b
comma
l_int|0x0000018d
comma
l_int|0x0000018f
comma
l_int|0x00000191
comma
l_int|0x00000193
comma
l_int|0x00000195
comma
l_int|0x00000197
comma
l_int|0x00000199
comma
l_int|0x0000019b
comma
l_int|0x0000019d
comma
l_int|0x0000019f
comma
l_int|0x000001a1
comma
l_int|0x000001a3
comma
l_int|0x000001a5
comma
l_int|0x000001a7
comma
l_int|0x000001a9
comma
l_int|0x000001ab
comma
l_int|0x000001ad
comma
l_int|0x000001af
comma
l_int|0x000001b1
comma
l_int|0x000001b3
comma
l_int|0x000001b5
comma
l_int|0x000001b7
comma
l_int|0x000001b9
comma
l_int|0x000001bb
comma
l_int|0x000001bd
comma
l_int|0x000001bf
comma
l_int|0x000001c1
comma
l_int|0x000001c3
comma
l_int|0x000001c5
comma
l_int|0x000001c7
comma
l_int|0x000001c9
comma
l_int|0x000001cb
comma
l_int|0x000001cd
comma
l_int|0x000001cf
comma
l_int|0x000001d1
comma
l_int|0x000001d3
comma
l_int|0x000001d5
comma
l_int|0x000001d7
comma
l_int|0x000001d9
comma
l_int|0x000001db
comma
l_int|0x000001dd
comma
l_int|0x000001df
comma
l_int|0x000001e1
comma
l_int|0x000001e3
comma
l_int|0x000001e5
comma
l_int|0x000001e7
comma
l_int|0x000001e9
comma
l_int|0x000001eb
comma
l_int|0x000001ed
comma
l_int|0x000001ef
comma
l_int|0x000001f1
comma
l_int|0x000001f3
comma
l_int|0x000001f5
comma
l_int|0x000001f7
comma
l_int|0x000001f9
comma
l_int|0x000001fb
comma
l_int|0x000001fd
comma
l_int|0x000001ff
comma
l_int|0x00000201
comma
l_int|0x00000203
comma
l_int|0x00000205
comma
l_int|0x00000207
comma
l_int|0x00000209
comma
l_int|0x0000020b
comma
l_int|0x0000020d
comma
l_int|0x0000020f
comma
l_int|0x00000211
comma
l_int|0x00000213
comma
l_int|0x00000215
comma
l_int|0x00000217
comma
l_int|0x00000219
comma
l_int|0x0000021b
comma
l_int|0x0000021d
comma
l_int|0x0000021f
comma
l_int|0x00000221
comma
l_int|0x00000223
comma
l_int|0x00000225
comma
l_int|0x00000227
comma
l_int|0x00000229
comma
l_int|0x0000022b
comma
l_int|0x0000022d
comma
l_int|0x0000022f
comma
l_int|0x00000231
comma
l_int|0x00000233
comma
l_int|0x00000235
comma
l_int|0x00000237
comma
l_int|0x00000239
comma
l_int|0x0000023b
comma
l_int|0x0000023d
comma
l_int|0x0000023f
comma
l_int|0x00000241
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_msgin
mdefine_line|#define A_dsa_msgin&t;0x00000020
r_static
id|u32
id|A_dsa_msgin_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000002f
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_msgout
mdefine_line|#define A_dsa_msgout&t;0x00000008
r_static
id|u32
id|A_dsa_msgout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000013
comma
l_int|0x00000285
comma
l_int|0x000002c5
comma
l_int|0x00000305
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_select
mdefine_line|#define A_dsa_select&t;0x00000000
r_static
id|u32
id|A_dsa_select_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000006
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_size
mdefine_line|#define A_dsa_size&t;0x00000828
r_static
id|u32
id|A_dsa_size_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_status
mdefine_line|#define A_dsa_status&t;0x00000018
r_static
id|u32
id|A_dsa_status_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000002b
comma
)brace
suffix:semicolon
DECL|macro|A_had_cmdout
mdefine_line|#define A_had_cmdout&t;0x00000004
r_static
id|u32
id|A_had_cmdout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000001a
comma
)brace
suffix:semicolon
DECL|macro|A_had_datain
mdefine_line|#define A_had_datain&t;0x00000008
r_static
id|u32
id|A_had_datain_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000038
comma
)brace
suffix:semicolon
DECL|macro|A_had_dataout
mdefine_line|#define A_had_dataout&t;0x00000010
r_static
id|u32
id|A_had_dataout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000013e
comma
)brace
suffix:semicolon
DECL|macro|A_had_extmsg
mdefine_line|#define A_had_extmsg&t;0x00000080
r_static
id|u32
id|A_had_extmsg_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000025a
comma
l_int|0x0000029a
comma
l_int|0x000002da
comma
)brace
suffix:semicolon
DECL|macro|A_had_msgin
mdefine_line|#define A_had_msgin&t;0x00000040
r_static
id|u32
id|A_had_msgin_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000248
comma
l_int|0x00000288
comma
l_int|0x000002c8
comma
)brace
suffix:semicolon
DECL|macro|A_had_msgout
mdefine_line|#define A_had_msgout&t;0x00000002
r_static
id|u32
id|A_had_msgout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000010
comma
l_int|0x00000282
comma
l_int|0x000002c2
comma
l_int|0x00000302
comma
)brace
suffix:semicolon
DECL|macro|A_had_select
mdefine_line|#define A_had_select&t;0x00000001
r_static
id|u32
id|A_had_select_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000000c
comma
)brace
suffix:semicolon
DECL|macro|A_had_status
mdefine_line|#define A_had_status&t;0x00000020
r_static
id|u32
id|A_had_status_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_bad_extmsg1a
mdefine_line|#define A_int_bad_extmsg1a&t;0xab930000
r_static
id|u32
id|A_int_bad_extmsg1a_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000263
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_extmsg1b
mdefine_line|#define A_int_bad_extmsg1b&t;0xab930001
r_static
id|u32
id|A_int_bad_extmsg1b_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000026b
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_extmsg2a
mdefine_line|#define A_int_bad_extmsg2a&t;0xab930002
r_static
id|u32
id|A_int_bad_extmsg2a_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002a3
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_extmsg2b
mdefine_line|#define A_int_bad_extmsg2b&t;0xab930003
r_static
id|u32
id|A_int_bad_extmsg2b_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002ab
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_extmsg3a
mdefine_line|#define A_int_bad_extmsg3a&t;0xab930004
r_static
id|u32
id|A_int_bad_extmsg3a_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002e3
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_extmsg3b
mdefine_line|#define A_int_bad_extmsg3b&t;0xab930005
r_static
id|u32
id|A_int_bad_extmsg3b_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002eb
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_msg1
mdefine_line|#define A_int_bad_msg1&t;0xab930006
r_static
id|u32
id|A_int_bad_msg1_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000255
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_msg2
mdefine_line|#define A_int_bad_msg2&t;0xab930007
r_static
id|u32
id|A_int_bad_msg2_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000295
comma
)brace
suffix:semicolon
DECL|macro|A_int_bad_msg3
mdefine_line|#define A_int_bad_msg3&t;0xab930008
r_static
id|u32
id|A_int_bad_msg3_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002d5
comma
)brace
suffix:semicolon
DECL|macro|A_int_cmd_bad_phase
mdefine_line|#define A_int_cmd_bad_phase&t;0xab930009
r_static
id|u32
id|A_int_cmd_bad_phase_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000027
comma
)brace
suffix:semicolon
DECL|macro|A_int_cmd_complete
mdefine_line|#define A_int_cmd_complete&t;0xab93000a
r_static
id|u32
id|A_int_cmd_complete_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000037
comma
)brace
suffix:semicolon
DECL|macro|A_int_data_bad_phase
mdefine_line|#define A_int_data_bad_phase&t;0xab93000b
r_static
id|u32
id|A_int_data_bad_phase_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000247
comma
)brace
suffix:semicolon
DECL|macro|A_int_disc1
mdefine_line|#define A_int_disc1&t;0xab930019
r_static
id|u32
id|A_int_disc1_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000277
comma
)brace
suffix:semicolon
DECL|macro|A_int_disc2
mdefine_line|#define A_int_disc2&t;0xab93001a
r_static
id|u32
id|A_int_disc2_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002b7
comma
)brace
suffix:semicolon
DECL|macro|A_int_disc3
mdefine_line|#define A_int_disc3&t;0xab93001b
r_static
id|u32
id|A_int_disc3_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002f7
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_sdtr1
mdefine_line|#define A_int_msg_sdtr1&t;0xab93000c
r_static
id|u32
id|A_int_msg_sdtr1_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000271
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_sdtr2
mdefine_line|#define A_int_msg_sdtr2&t;0xab93000d
r_static
id|u32
id|A_int_msg_sdtr2_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002b1
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_sdtr3
mdefine_line|#define A_int_msg_sdtr3&t;0xab93000e
r_static
id|u32
id|A_int_msg_sdtr3_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002f1
comma
)brace
suffix:semicolon
DECL|macro|A_int_no_msgout1
mdefine_line|#define A_int_no_msgout1&t;0xab93000f
r_static
id|u32
id|A_int_no_msgout1_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000281
comma
)brace
suffix:semicolon
DECL|macro|A_int_no_msgout2
mdefine_line|#define A_int_no_msgout2&t;0xab930010
r_static
id|u32
id|A_int_no_msgout2_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000002c1
comma
)brace
suffix:semicolon
DECL|macro|A_int_no_msgout3
mdefine_line|#define A_int_no_msgout3&t;0xab930011
r_static
id|u32
id|A_int_no_msgout3_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000301
comma
)brace
suffix:semicolon
DECL|macro|A_int_not_cmd_complete
mdefine_line|#define A_int_not_cmd_complete&t;0xab930012
r_static
id|u32
id|A_int_not_cmd_complete_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000031
comma
)brace
suffix:semicolon
DECL|macro|A_int_not_rej
mdefine_line|#define A_int_not_rej&t;0xab93001c
r_static
id|u32
id|A_int_not_rej_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000030d
comma
)brace
suffix:semicolon
DECL|macro|A_int_resel_not_msgin
mdefine_line|#define A_int_resel_not_msgin&t;0xab930016
r_static
id|u32
id|A_int_resel_not_msgin_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000317
comma
)brace
suffix:semicolon
DECL|macro|A_int_reselected
mdefine_line|#define A_int_reselected&t;0xab930017
r_static
id|u32
id|A_int_reselected_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000031b
comma
)brace
suffix:semicolon
DECL|macro|A_int_sel_no_ident
mdefine_line|#define A_int_sel_no_ident&t;0xab930013
r_static
id|u32
id|A_int_sel_no_ident_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000000f
comma
)brace
suffix:semicolon
DECL|macro|A_int_sel_not_cmd
mdefine_line|#define A_int_sel_not_cmd&t;0xab930014
r_static
id|u32
id|A_int_sel_not_cmd_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000019
comma
)brace
suffix:semicolon
DECL|macro|A_int_selected
mdefine_line|#define A_int_selected&t;0xab930018
r_static
id|u32
id|A_int_selected_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000032d
comma
)brace
suffix:semicolon
DECL|macro|A_int_status_not_msgin
mdefine_line|#define A_int_status_not_msgin&t;0xab930015
r_static
id|u32
id|A_int_status_not_msgin_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000002d
comma
)brace
suffix:semicolon
DECL|macro|A_msgin_buf
mdefine_line|#define A_msgin_buf&t;0x00000000
r_static
id|u32
id|A_msgin_buf_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000024b
comma
l_int|0x0000025f
comma
l_int|0x00000267
comma
l_int|0x0000026f
comma
l_int|0x0000028b
comma
l_int|0x0000029f
comma
l_int|0x000002a7
comma
l_int|0x000002af
comma
l_int|0x000002cb
comma
l_int|0x000002df
comma
l_int|0x000002e7
comma
l_int|0x000002ef
comma
l_int|0x0000030b
comma
)brace
suffix:semicolon
DECL|macro|A_reselected_identify
mdefine_line|#define A_reselected_identify&t;0x00000000
r_static
id|u32
id|A_reselected_identify_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000319
comma
)brace
suffix:semicolon
DECL|macro|Ent_do_select
mdefine_line|#define Ent_do_select&t;0x00000000
DECL|macro|Ent_done_ident
mdefine_line|#define Ent_done_ident&t;0x00000050
DECL|macro|Ent_end_data_trans
mdefine_line|#define Ent_end_data_trans&t;0x00000908
DECL|macro|Ent_patch_input_data
mdefine_line|#define Ent_patch_input_data&t;0x000000e8
DECL|macro|Ent_patch_new_dsa
mdefine_line|#define Ent_patch_new_dsa&t;0x00000c88
DECL|macro|Ent_patch_output_data
mdefine_line|#define Ent_patch_output_data&t;0x00000500
DECL|macro|Ent_reselect
mdefine_line|#define Ent_reselect&t;0x00000c48
DECL|macro|Ent_resume_cmd
mdefine_line|#define Ent_resume_cmd&t;0x00000068
DECL|macro|Ent_resume_msgin1a
mdefine_line|#define Ent_resume_msgin1a&t;0x000009e0
DECL|macro|Ent_resume_msgin1b
mdefine_line|#define Ent_resume_msgin1b&t;0x000009f0
DECL|macro|Ent_resume_msgin2a
mdefine_line|#define Ent_resume_msgin2a&t;0x00000ae0
DECL|macro|Ent_resume_msgin2b
mdefine_line|#define Ent_resume_msgin2b&t;0x00000af0
DECL|macro|Ent_resume_msgin3a
mdefine_line|#define Ent_resume_msgin3a&t;0x00000be0
DECL|macro|Ent_resume_msgin3b
mdefine_line|#define Ent_resume_msgin3b&t;0x00000bf0
DECL|macro|Ent_resume_pmm
mdefine_line|#define Ent_resume_pmm&t;0x00000078
DECL|macro|Ent_resume_rej_ident
mdefine_line|#define Ent_resume_rej_ident&t;0x00000c20
DECL|macro|Ent_wait_disc1
mdefine_line|#define Ent_wait_disc1&t;0x000009d0
DECL|macro|Ent_wait_disc2
mdefine_line|#define Ent_wait_disc2&t;0x00000ad0
DECL|macro|Ent_wait_disc3
mdefine_line|#define Ent_wait_disc3&t;0x00000bd0
DECL|macro|Ent_wait_disc_complete
mdefine_line|#define Ent_wait_disc_complete&t;0x000000d0
r_static
id|u32
id|LABELPATCHES
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000007
comma
l_int|0x00000009
comma
l_int|0x00000015
comma
l_int|0x00000017
comma
l_int|0x0000001f
comma
l_int|0x00000021
comma
l_int|0x00000023
comma
l_int|0x00000025
comma
l_int|0x0000013d
comma
l_int|0x00000243
comma
l_int|0x00000245
comma
l_int|0x0000024d
comma
l_int|0x0000024f
comma
l_int|0x00000251
comma
l_int|0x00000253
comma
l_int|0x00000259
comma
l_int|0x00000261
comma
l_int|0x00000269
comma
l_int|0x0000027b
comma
l_int|0x00000287
comma
l_int|0x0000028d
comma
l_int|0x0000028f
comma
l_int|0x00000291
comma
l_int|0x00000293
comma
l_int|0x00000299
comma
l_int|0x000002a1
comma
l_int|0x000002a9
comma
l_int|0x000002bb
comma
l_int|0x000002c7
comma
l_int|0x000002cd
comma
l_int|0x000002cf
comma
l_int|0x000002d1
comma
l_int|0x000002d3
comma
l_int|0x000002d9
comma
l_int|0x000002e1
comma
l_int|0x000002e9
comma
l_int|0x000002fb
comma
l_int|0x00000307
comma
l_int|0x00000311
comma
l_int|0x00000315
comma
l_int|0x0000031f
comma
l_int|0x0000032b
comma
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
)brace
id|EXTERNAL_PATCHES
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
r_static
id|u32
id|INSTRUCTIONS
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
l_int|407
suffix:semicolon
r_static
id|u32
id|PATCHES
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
l_int|42
suffix:semicolon
r_static
id|u32
id|EXTERNAL_PATCHES_LEN
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
l_int|0
suffix:semicolon
eof
