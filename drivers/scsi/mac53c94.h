multiline_comment|/*&n; * mac53c94.h: definitions for the driver for the 53c94 SCSI bus adaptor&n; * found on Power Macintosh computers, controlling the external SCSI chain.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#ifndef _MAC53C94_H
DECL|macro|_MAC53C94_H
mdefine_line|#define _MAC53C94_H
r_int
id|mac53c94_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|mac53c94_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|mac53c94_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|mac53c94_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|mac53c94_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|mac53c94_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|SCSI_MAC53C94
mdefine_line|#define SCSI_MAC53C94 {&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name:&t;&quot;53c94&quot;,&t;&t;&t;&bslash;&n;&t;name:&t;&t;&quot;53C94&quot;,&t;&t;&t;&bslash;&n;&t;detect:&t;&t;mac53c94_detect,&t;&t;&bslash;&n;&t;release:&t;mac53c94_release,&t;&t;&bslash;&n;&t;command:&t;mac53c94_command,&t;&t;&bslash;&n;&t;queuecommand:&t;mac53c94_queue,&t;&t;&t;&bslash;&n;&t;abort:&t;&t;mac53c94_abort,&t;&t;&t;&bslash;&n;&t;reset:&t;&t;mac53c94_reset,&t;&t;&t;&bslash;&n;&t;can_queue:&t;1,&t;&t;&t;&t;&bslash;&n;&t;this_id:&t;7,&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;1,&t;&t;&t;&t;&bslash;&n;&t;use_clustering:&t;DISABLE_CLUSTERING,&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Registers in the 53C94 controller.&n; */
DECL|struct|mac53c94_regs
r_struct
id|mac53c94_regs
(brace
DECL|member|count_lo
r_int
r_char
id|count_lo
suffix:semicolon
DECL|member|pad0
r_char
id|pad0
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|count_mid
r_int
r_char
id|count_mid
suffix:semicolon
DECL|member|pad1
r_char
id|pad1
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|fifo
r_int
r_char
id|fifo
suffix:semicolon
DECL|member|pad2
r_char
id|pad2
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|pad3
r_char
id|pad3
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|pad4
r_char
id|pad4
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|interrupt
r_int
r_char
id|interrupt
suffix:semicolon
DECL|member|pad5
r_char
id|pad5
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|seqstep
r_int
r_char
id|seqstep
suffix:semicolon
DECL|member|pad6
r_char
id|pad6
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|pad7
r_char
id|pad7
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|config1
r_int
r_char
id|config1
suffix:semicolon
DECL|member|pad8
r_char
id|pad8
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|clk_factor
r_int
r_char
id|clk_factor
suffix:semicolon
DECL|member|pad9
r_char
id|pad9
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|test
r_int
r_char
id|test
suffix:semicolon
DECL|member|pad10
r_char
id|pad10
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|config2
r_int
r_char
id|config2
suffix:semicolon
DECL|member|pad11
r_char
id|pad11
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|config3
r_int
r_char
id|config3
suffix:semicolon
DECL|member|pad12
r_char
id|pad12
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|config4
r_int
r_char
id|config4
suffix:semicolon
DECL|member|pad13
r_char
id|pad13
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|count_hi
r_int
r_char
id|count_hi
suffix:semicolon
DECL|member|pad14
r_char
id|pad14
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|fifo_res
r_int
r_char
id|fifo_res
suffix:semicolon
DECL|member|pad15
r_char
id|pad15
(braket
l_int|15
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Alternate functions for some registers.&n; */
DECL|macro|dest_id
mdefine_line|#define dest_id&t;&t;status
DECL|macro|sel_timeout
mdefine_line|#define sel_timeout&t;interrupt
DECL|macro|sync_period
mdefine_line|#define sync_period&t;seqstep
DECL|macro|sync_offset
mdefine_line|#define sync_offset&t;flags
multiline_comment|/*&n; * Bits in command register.&n; */
DECL|macro|CMD_DMA_MODE
mdefine_line|#define CMD_DMA_MODE&t;0x80
DECL|macro|CMD_MODE_MASK
mdefine_line|#define CMD_MODE_MASK&t;0x70
DECL|macro|CMD_MODE_INIT
mdefine_line|#define CMD_MODE_INIT&t;0x10
DECL|macro|CMD_MODE_TARG
mdefine_line|#define CMD_MODE_TARG&t;0x20
DECL|macro|CMD_MODE_DISC
mdefine_line|#define CMD_MODE_DISC&t;0x40
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;0
DECL|macro|CMD_FLUSH
mdefine_line|#define CMD_FLUSH&t;1
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET&t;2
DECL|macro|CMD_SCSI_RESET
mdefine_line|#define CMD_SCSI_RESET&t;3
DECL|macro|CMD_XFER_DATA
mdefine_line|#define CMD_XFER_DATA&t;0x10
DECL|macro|CMD_I_COMPLETE
mdefine_line|#define CMD_I_COMPLETE&t;0x11
DECL|macro|CMD_ACCEPT_MSG
mdefine_line|#define CMD_ACCEPT_MSG&t;0x12
DECL|macro|CMD_XFER_PAD
mdefine_line|#define CMD_XFER_PAD&t;0x18
DECL|macro|CMD_SET_ATN
mdefine_line|#define CMD_SET_ATN&t;0x1a
DECL|macro|CMD_CLR_ATN
mdefine_line|#define CMD_CLR_ATN&t;0x1b
DECL|macro|CMD_SEND_MSG
mdefine_line|#define CMD_SEND_MSG&t;0x20
DECL|macro|CMD_SEND_STATUS
mdefine_line|#define CMD_SEND_STATUS&t;0x21
DECL|macro|CMD_SEND_DATA
mdefine_line|#define CMD_SEND_DATA&t;0x22
DECL|macro|CMD_DISC_SEQ
mdefine_line|#define CMD_DISC_SEQ&t;0x23
DECL|macro|CMD_TERMINATE
mdefine_line|#define CMD_TERMINATE&t;0x24
DECL|macro|CMD_T_COMPLETE
mdefine_line|#define CMD_T_COMPLETE&t;0x25
DECL|macro|CMD_DISCONNECT
mdefine_line|#define CMD_DISCONNECT&t;0x27
DECL|macro|CMD_RECV_MSG
mdefine_line|#define CMD_RECV_MSG&t;0x28
DECL|macro|CMD_RECV_CDB
mdefine_line|#define CMD_RECV_CDB&t;0x29
DECL|macro|CMD_RECV_DATA
mdefine_line|#define CMD_RECV_DATA&t;0x2a
DECL|macro|CMD_RECV_CMD
mdefine_line|#define CMD_RECV_CMD&t;0x2b
DECL|macro|CMD_ABORT_DMA
mdefine_line|#define CMD_ABORT_DMA&t;0x04
DECL|macro|CMD_RESELECT
mdefine_line|#define CMD_RESELECT&t;0x40
DECL|macro|CMD_SELECT
mdefine_line|#define CMD_SELECT&t;0x41
DECL|macro|CMD_SELECT_ATN
mdefine_line|#define CMD_SELECT_ATN&t;0x42
DECL|macro|CMD_SELATN_STOP
mdefine_line|#define CMD_SELATN_STOP&t;0x43
DECL|macro|CMD_ENABLE_SEL
mdefine_line|#define CMD_ENABLE_SEL&t;0x44
DECL|macro|CMD_DISABLE_SEL
mdefine_line|#define CMD_DISABLE_SEL&t;0x45
DECL|macro|CMD_SEL_ATN3
mdefine_line|#define CMD_SEL_ATN3&t;0x46
DECL|macro|CMD_RESEL_ATN3
mdefine_line|#define CMD_RESEL_ATN3&t;0x47
multiline_comment|/*&n; * Bits in status register.&n; */
DECL|macro|STAT_IRQ
mdefine_line|#define STAT_IRQ&t;0x80
DECL|macro|STAT_ERROR
mdefine_line|#define STAT_ERROR&t;0x40
DECL|macro|STAT_PARITY
mdefine_line|#define STAT_PARITY&t;0x20
DECL|macro|STAT_TC_ZERO
mdefine_line|#define STAT_TC_ZERO&t;0x10
DECL|macro|STAT_DONE
mdefine_line|#define STAT_DONE&t;0x08
DECL|macro|STAT_PHASE
mdefine_line|#define STAT_PHASE&t;0x07
DECL|macro|STAT_MSG
mdefine_line|#define STAT_MSG&t;0x04
DECL|macro|STAT_CD
mdefine_line|#define STAT_CD&t;&t;0x02
DECL|macro|STAT_IO
mdefine_line|#define STAT_IO&t;&t;0x01
multiline_comment|/*&n; * Bits in interrupt register.&n; */
DECL|macro|INTR_RESET
mdefine_line|#define INTR_RESET&t;0x80&t;/* SCSI bus was reset */
DECL|macro|INTR_ILL_CMD
mdefine_line|#define INTR_ILL_CMD&t;0x40&t;/* illegal command */
DECL|macro|INTR_DISCONNECT
mdefine_line|#define INTR_DISCONNECT&t;0x20&t;/* we got disconnected */
DECL|macro|INTR_BUS_SERV
mdefine_line|#define INTR_BUS_SERV&t;0x10&t;/* bus service requested */
DECL|macro|INTR_DONE
mdefine_line|#define INTR_DONE&t;0x08&t;/* function completed */
DECL|macro|INTR_RESELECTED
mdefine_line|#define INTR_RESELECTED&t;0x04&t;/* we were reselected */
DECL|macro|INTR_SEL_ATN
mdefine_line|#define INTR_SEL_ATN&t;0x02&t;/* we were selected, ATN asserted */
DECL|macro|INTR_SELECT
mdefine_line|#define INTR_SELECT&t;0x01&t;/* we were selected, ATN negated */
multiline_comment|/*&n; * Encoding for the select timeout.&n; */
DECL|macro|TIMO_VAL
mdefine_line|#define TIMO_VAL(x)&t;((x) * 5000 / 7682)
multiline_comment|/*&n; * Bits in sequence step register.&n; */
DECL|macro|SS_MASK
mdefine_line|#define SS_MASK&t;&t;7
DECL|macro|SS_ARB_SEL
mdefine_line|#define SS_ARB_SEL&t;0&t;/* Selection &amp; arbitration complete */
DECL|macro|SS_MSG_SENT
mdefine_line|#define SS_MSG_SENT&t;1&t;/* One message byte sent */
DECL|macro|SS_NOT_CMD
mdefine_line|#define SS_NOT_CMD&t;2&t;/* Not in command phase */
DECL|macro|SS_PHASE_CHG
mdefine_line|#define SS_PHASE_CHG&t;3&t;/* Early phase change, cmd bytes lost */
DECL|macro|SS_DONE
mdefine_line|#define SS_DONE&t;&t;4&t;/* Command was sent OK */
multiline_comment|/*&n; * Encoding for sync transfer period.&n; */
DECL|macro|SYNCP_MASK
mdefine_line|#define SYNCP_MASK&t;0x1f
DECL|macro|SYNCP_MIN
mdefine_line|#define SYNCP_MIN&t;4
DECL|macro|SYNCP_MAX
mdefine_line|#define SYNCP_MAX&t;31
multiline_comment|/*&n; * Bits in flags register.&n; */
DECL|macro|FLAGS_FIFO_LEV
mdefine_line|#define FLAGS_FIFO_LEV&t;0x1f
DECL|macro|FLAGS_SEQ_STEP
mdefine_line|#define FLAGS_SEQ_STEP&t;0xe0
multiline_comment|/*&n; * Encoding for sync offset.&n; */
DECL|macro|SYNCO_MASK
mdefine_line|#define SYNCO_MASK&t;0x0f
DECL|macro|SYNCO_ASS_CTRL
mdefine_line|#define SYNCO_ASS_CTRL&t;0x30&t;/* REQ/ACK assertion control */
DECL|macro|SYNCO_NEG_CTRL
mdefine_line|#define SYNCO_NEG_CTRL&t;0xc0&t;/* REQ/ACK negation control */
multiline_comment|/*&n; * Bits in config1 register.&n; */
DECL|macro|CF1_SLOW_CABLE
mdefine_line|#define CF1_SLOW_CABLE&t;0x80&t;/* Slow cable mode */
DECL|macro|CF1_NO_RES_REP
mdefine_line|#define CF1_NO_RES_REP&t;0x40&t;/* Disable SCSI reset reports */
DECL|macro|CF1_PAR_TEST
mdefine_line|#define CF1_PAR_TEST&t;0x20&t;/* Parity test mode enable */
DECL|macro|CF1_PAR_ENABLE
mdefine_line|#define CF1_PAR_ENABLE&t;0x10&t;/* Enable parity checks */
DECL|macro|CF1_TEST
mdefine_line|#define CF1_TEST&t;0x08&t;/* Chip tests */
DECL|macro|CF1_MY_ID
mdefine_line|#define CF1_MY_ID&t;0x07&t;/* Controller&squot;s address on bus */
multiline_comment|/*&n; * Encoding for clk_factor register.&n; */
DECL|macro|CLKF_MASK
mdefine_line|#define CLKF_MASK&t;7
DECL|macro|CLKF_VAL
mdefine_line|#define CLKF_VAL(freq)&t;((((freq) + 4999999) / 5000000) &amp; CLKF_MASK)
multiline_comment|/*&n; * Bits in test mode register.&n; */
DECL|macro|TEST_TARGET
mdefine_line|#define TEST_TARGET&t;1&t;/* target test mode */
DECL|macro|TEST_INITIATOR
mdefine_line|#define TEST_INITIATOR&t;2&t;/* initiator test mode */
DECL|macro|TEST_TRISTATE
mdefine_line|#define TEST_TRISTATE&t;4&t;/* tristate (hi-z) test mode */
multiline_comment|/*&n; * Bits in config2 register.&n; */
DECL|macro|CF2_RFB
mdefine_line|#define CF2_RFB&t;&t;0x80
DECL|macro|CF2_FEATURE_EN
mdefine_line|#define CF2_FEATURE_EN&t;0x40&t;/* enable features / phase latch */
DECL|macro|CF2_BYTECTRL
mdefine_line|#define CF2_BYTECTRL&t;0x20
DECL|macro|CF2_DREQ_HIZ
mdefine_line|#define CF2_DREQ_HIZ&t;0x10
DECL|macro|CF2_SCSI2
mdefine_line|#define CF2_SCSI2&t;0x08
DECL|macro|CF2_PAR_ABORT
mdefine_line|#define CF2_PAR_ABORT&t;0x04&t;/* bad parity target abort */
DECL|macro|CF2_REG_PARERR
mdefine_line|#define CF2_REG_PARERR&t;0x02&t;/* register parity error */
DECL|macro|CF2_DMA_PARERR
mdefine_line|#define CF2_DMA_PARERR&t;0x01&t;/* DMA parity error */
multiline_comment|/*&n; * Bits in the config3 register.&n; */
DECL|macro|CF3_ID_MSG_CHK
mdefine_line|#define CF3_ID_MSG_CHK&t;0x80
DECL|macro|CF3_3B_MSGS
mdefine_line|#define CF3_3B_MSGS&t;0x40
DECL|macro|CF3_CDB10
mdefine_line|#define CF3_CDB10&t;0x20
DECL|macro|CF3_FASTSCSI
mdefine_line|#define CF3_FASTSCSI&t;0x10&t;/* enable fast SCSI support */
DECL|macro|CF3_FASTCLOCK
mdefine_line|#define CF3_FASTCLOCK&t;0x08
DECL|macro|CF3_SAVERESID
mdefine_line|#define CF3_SAVERESID&t;0x04
DECL|macro|CF3_ALT_DMA
mdefine_line|#define CF3_ALT_DMA&t;0x02
DECL|macro|CF3_THRESH_8
mdefine_line|#define CF3_THRESH_8&t;0x01
multiline_comment|/*&n; * Bits in the config4 register.&n; */
DECL|macro|CF4_EAN
mdefine_line|#define CF4_EAN&t;&t;0x04
DECL|macro|CF4_TEST
mdefine_line|#define CF4_TEST&t;0x02
DECL|macro|CF4_BBTE
mdefine_line|#define CF4_BBTE&t;0x01
macro_line|#endif /* _MAC53C94_H */
eof
