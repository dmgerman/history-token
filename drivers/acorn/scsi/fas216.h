multiline_comment|/*&n; *  linux/drivers/acorn/scsi/fas216.h&n; *&n; *  Copyright (C) 1997-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  FAS216 generic driver&n; */
macro_line|#ifndef FAS216_H
DECL|macro|FAS216_H
mdefine_line|#define FAS216_H
macro_line|#ifndef NO_IRQ
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ 255
macro_line|#endif
macro_line|#include &quot;queue.h&quot;
macro_line|#include &quot;msgqueue.h&quot;
multiline_comment|/* FAS register definitions */
multiline_comment|/* transfer count low */
DECL|macro|REG_CTCL
mdefine_line|#define REG_CTCL(x)&t;&t;((x)-&gt;scsi.io_port)
DECL|macro|REG_STCL
mdefine_line|#define REG_STCL(x)&t;&t;((x)-&gt;scsi.io_port)
multiline_comment|/* transfer count medium */
DECL|macro|REG_CTCM
mdefine_line|#define REG_CTCM(x)&t;&t;((x)-&gt;scsi.io_port + (1 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|REG_STCM
mdefine_line|#define REG_STCM(x)&t;&t;((x)-&gt;scsi.io_port + (1 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* fifo data */
DECL|macro|REG_FF
mdefine_line|#define REG_FF(x)&t;&t;((x)-&gt;scsi.io_port + (2 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* command */
DECL|macro|REG_CMD
mdefine_line|#define REG_CMD(x)&t;&t;((x)-&gt;scsi.io_port + (3 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;&t;0x00
DECL|macro|CMD_FLUSHFIFO
mdefine_line|#define CMD_FLUSHFIFO&t;&t;0x01
DECL|macro|CMD_RESETCHIP
mdefine_line|#define CMD_RESETCHIP&t;&t;0x02
DECL|macro|CMD_RESETSCSI
mdefine_line|#define CMD_RESETSCSI&t;&t;0x03
DECL|macro|CMD_TRANSFERINFO
mdefine_line|#define CMD_TRANSFERINFO&t;0x10
DECL|macro|CMD_INITCMDCOMPLETE
mdefine_line|#define CMD_INITCMDCOMPLETE&t;0x11
DECL|macro|CMD_MSGACCEPTED
mdefine_line|#define CMD_MSGACCEPTED&t;&t;0x12
DECL|macro|CMD_PADBYTES
mdefine_line|#define CMD_PADBYTES&t;&t;0x18
DECL|macro|CMD_SETATN
mdefine_line|#define CMD_SETATN&t;&t;0x1a
DECL|macro|CMD_RSETATN
mdefine_line|#define CMD_RSETATN&t;&t;0x1b
DECL|macro|CMD_SELECTWOATN
mdefine_line|#define CMD_SELECTWOATN&t;&t;0x41
DECL|macro|CMD_SELECTATN
mdefine_line|#define CMD_SELECTATN&t;&t;0x42
DECL|macro|CMD_SELECTATNSTOP
mdefine_line|#define CMD_SELECTATNSTOP&t;0x43
DECL|macro|CMD_ENABLESEL
mdefine_line|#define CMD_ENABLESEL&t;&t;0x44
DECL|macro|CMD_DISABLESEL
mdefine_line|#define CMD_DISABLESEL&t;&t;0x45
DECL|macro|CMD_SELECTATN3
mdefine_line|#define CMD_SELECTATN3&t;&t;0x46
DECL|macro|CMD_RESEL3
mdefine_line|#define CMD_RESEL3&t;&t;0x47
DECL|macro|CMD_WITHDMA
mdefine_line|#define CMD_WITHDMA&t;&t;0x80
multiline_comment|/* status register (read) */
DECL|macro|REG_STAT
mdefine_line|#define REG_STAT(x)&t;&t;((x)-&gt;scsi.io_port + (4 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|STAT_IO
mdefine_line|#define STAT_IO&t;&t;&t;(1 &lt;&lt; 0)&t;&t;&t;/* IO phase&t;&t;*/
DECL|macro|STAT_CD
mdefine_line|#define STAT_CD&t;&t;&t;(1 &lt;&lt; 1)&t;&t;&t;/* CD phase&t;&t;*/
DECL|macro|STAT_MSG
mdefine_line|#define STAT_MSG&t;&t;(1 &lt;&lt; 2)&t;&t;&t;/* MSG phase&t;&t;*/
DECL|macro|STAT_TRANSFERDONE
mdefine_line|#define STAT_TRANSFERDONE&t;(1 &lt;&lt; 3)&t;&t;&t;/* Transfer completed&t;*/
DECL|macro|STAT_TRANSFERCNTZ
mdefine_line|#define STAT_TRANSFERCNTZ&t;(1 &lt;&lt; 4)&t;&t;&t;/* Transfer counter is zero */
DECL|macro|STAT_PARITYERROR
mdefine_line|#define STAT_PARITYERROR&t;(1 &lt;&lt; 5)&t;&t;&t;/* Parity error&t;&t;*/
DECL|macro|STAT_REALBAD
mdefine_line|#define STAT_REALBAD&t;&t;(1 &lt;&lt; 6)&t;&t;&t;/* Something bad&t;*/
DECL|macro|STAT_INT
mdefine_line|#define STAT_INT&t;&t;(1 &lt;&lt; 7)&t;&t;&t;/* Interrupt&t;&t;*/
DECL|macro|STAT_BUSMASK
mdefine_line|#define STAT_BUSMASK&t;&t;(STAT_MSG|STAT_CD|STAT_IO)
DECL|macro|STAT_DATAOUT
mdefine_line|#define STAT_DATAOUT&t;&t;(0)&t;&t;&t;&t;/* Data out&t;&t;*/
DECL|macro|STAT_DATAIN
mdefine_line|#define STAT_DATAIN&t;&t;(STAT_IO)&t;&t;&t;/* Data in&t;&t;*/
DECL|macro|STAT_COMMAND
mdefine_line|#define STAT_COMMAND&t;&t;(STAT_CD)&t;&t;&t;/* Command out&t;&t;*/
DECL|macro|STAT_STATUS
mdefine_line|#define STAT_STATUS&t;&t;(STAT_CD|STAT_IO)&t;&t;/* Status In&t;&t;*/
DECL|macro|STAT_MESGOUT
mdefine_line|#define STAT_MESGOUT&t;&t;(STAT_MSG|STAT_CD)&t;&t;/* Message out&t;&t;*/
DECL|macro|STAT_MESGIN
mdefine_line|#define STAT_MESGIN&t;&t;(STAT_MSG|STAT_CD|STAT_IO)&t;/* Message In&t;&t;*/
multiline_comment|/* bus ID for select / reselect */
DECL|macro|REG_SDID
mdefine_line|#define REG_SDID(x)&t;&t;((x)-&gt;scsi.io_port + (4 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|BUSID
mdefine_line|#define BUSID(target)&t;&t;((target) &amp; 7)
multiline_comment|/* Interrupt status register (read) */
DECL|macro|REG_INST
mdefine_line|#define REG_INST(x)&t;&t;((x)-&gt;scsi.io_port + (5 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|INST_SELWOATN
mdefine_line|#define INST_SELWOATN&t;&t;(1 &lt;&lt; 0)&t;&t;&t;/* Select w/o ATN&t;*/
DECL|macro|INST_SELATN
mdefine_line|#define INST_SELATN&t;&t;(1 &lt;&lt; 1)&t;&t;&t;/* Select w/ATN&t;&t;*/
DECL|macro|INST_RESELECTED
mdefine_line|#define INST_RESELECTED&t;&t;(1 &lt;&lt; 2)&t;&t;&t;/* Reselected&t;&t;*/
DECL|macro|INST_FUNCDONE
mdefine_line|#define INST_FUNCDONE&t;&t;(1 &lt;&lt; 3)&t;&t;&t;/* Function done&t;*/
DECL|macro|INST_BUSSERVICE
mdefine_line|#define INST_BUSSERVICE&t;&t;(1 &lt;&lt; 4)&t;&t;&t;/* Bus service&t;&t;*/
DECL|macro|INST_DISCONNECT
mdefine_line|#define INST_DISCONNECT&t;&t;(1 &lt;&lt; 5)&t;&t;&t;/* Disconnect&t;&t;*/
DECL|macro|INST_ILLEGALCMD
mdefine_line|#define INST_ILLEGALCMD&t;&t;(1 &lt;&lt; 6)&t;&t;&t;/* Illegal command&t;*/
DECL|macro|INST_BUSRESET
mdefine_line|#define INST_BUSRESET&t;&t;(1 &lt;&lt; 7)&t;&t;&t;/* SCSI Bus reset&t;*/
multiline_comment|/* Timeout register (write) */
DECL|macro|REG_STIM
mdefine_line|#define REG_STIM(x)&t;&t;((x)-&gt;scsi.io_port + (5 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* Sequence step register (read) */
DECL|macro|REG_IS
mdefine_line|#define REG_IS(x)&t;&t;((x)-&gt;scsi.io_port + (6 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|IS_BITS
mdefine_line|#define IS_BITS&t;&t;&t;0x07
DECL|macro|IS_SELARB
mdefine_line|#define IS_SELARB&t;&t;0x00&t;&t;&t;&t;/* Select &amp; Arb ok&t;*/
DECL|macro|IS_MSGBYTESENT
mdefine_line|#define IS_MSGBYTESENT&t;&t;0x01&t;&t;&t;&t;/* One byte message sent*/
DECL|macro|IS_NOTCOMMAND
mdefine_line|#define IS_NOTCOMMAND&t;&t;0x02&t;&t;&t;&t;/* Not in command state&t;*/
DECL|macro|IS_EARLYPHASE
mdefine_line|#define IS_EARLYPHASE&t;&t;0x03&t;&t;&t;&t;/* Early phase change&t;*/
DECL|macro|IS_COMPLETE
mdefine_line|#define IS_COMPLETE&t;&t;0x04&t;&t;&t;&t;/* Command ok&t;&t;*/
DECL|macro|IS_SOF
mdefine_line|#define IS_SOF&t;&t;&t;0x08&t;&t;&t;&t;/* Sync off flag&t;*/
multiline_comment|/* Transfer period step (write) */
DECL|macro|REG_STP
mdefine_line|#define REG_STP(x)&t;&t;((x)-&gt;scsi.io_port + (6 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* Synchronous Offset (write) */
DECL|macro|REG_SOF
mdefine_line|#define REG_SOF(x)&t;&t;((x)-&gt;scsi.io_port + (7 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* Fifo state register (read) */
DECL|macro|REG_CFIS
mdefine_line|#define REG_CFIS(x)&t;&t;((x)-&gt;scsi.io_port + (7 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|CFIS_CF
mdefine_line|#define CFIS_CF&t;&t;&t;0x1f&t;&t;&t;&t;/* Num bytes in FIFO&t;*/
DECL|macro|CFIS_IS
mdefine_line|#define CFIS_IS&t;&t;&t;0xe0&t;&t;&t;&t;/* Step&t;&t;&t;*/
multiline_comment|/* config register 1 */
DECL|macro|REG_CNTL1
mdefine_line|#define REG_CNTL1(x)&t;&t;((x)-&gt;scsi.io_port + (8 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|CNTL1_CID
mdefine_line|#define CNTL1_CID&t;&t;(7 &lt;&lt; 0)&t;&t;&t;/* Chip ID&t;&t;&t;*/
DECL|macro|CNTL1_STE
mdefine_line|#define CNTL1_STE&t;&t;(1 &lt;&lt; 3)&t;&t;&t;/* Self test enable&t;&t;*/
DECL|macro|CNTL1_PERE
mdefine_line|#define CNTL1_PERE&t;&t;(1 &lt;&lt; 4)&t;&t;&t;/* Parity enable reporting en.&t;*/
DECL|macro|CNTL1_PTE
mdefine_line|#define CNTL1_PTE&t;&t;(1 &lt;&lt; 5)&t;&t;&t;/* Parity test enable&t;&t;*/
DECL|macro|CNTL1_DISR
mdefine_line|#define CNTL1_DISR&t;&t;(1 &lt;&lt; 6)&t;&t;&t;/* Disable Irq on SCSI reset&t;*/
DECL|macro|CNTL1_ETM
mdefine_line|#define CNTL1_ETM&t;&t;(1 &lt;&lt; 7)&t;&t;&t;/* Extended Timing Mode&t;&t;*/
multiline_comment|/* Clock conversion factor (read) */
DECL|macro|REG_CLKF
mdefine_line|#define REG_CLKF(x)&t;&t;((x)-&gt;scsi.io_port + (9 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|CLKF_F37MHZ
mdefine_line|#define CLKF_F37MHZ&t;&t;0x00&t;&t;&t;&t;/* 35.01 - 40 MHz&t;&t;*/
DECL|macro|CLKF_F10MHZ
mdefine_line|#define CLKF_F10MHZ&t;&t;0x02&t;&t;&t;&t;/* 10 MHz&t;&t;&t;*/
DECL|macro|CLKF_F12MHZ
mdefine_line|#define CLKF_F12MHZ&t;&t;0x03&t;&t;&t;&t;/* 10.01 - 15 MHz&t;&t;*/
DECL|macro|CLKF_F17MHZ
mdefine_line|#define CLKF_F17MHZ&t;&t;0x04&t;&t;&t;&t;/* 15.01 - 20 MHz&t;&t;*/
DECL|macro|CLKF_F22MHZ
mdefine_line|#define CLKF_F22MHZ&t;&t;0x05&t;&t;&t;&t;/* 20.01 - 25 MHz&t;&t;*/
DECL|macro|CLKF_F27MHZ
mdefine_line|#define CLKF_F27MHZ&t;&t;0x06&t;&t;&t;&t;/* 25.01 - 30 MHz&t;&t;*/
DECL|macro|CLKF_F32MHZ
mdefine_line|#define CLKF_F32MHZ&t;&t;0x07&t;&t;&t;&t;/* 30.01 - 35 MHz&t;&t;*/
multiline_comment|/* Chip test register (write) */
DECL|macro|REG0_FTM
mdefine_line|#define REG0_FTM(x)&t;&t;((x)-&gt;scsi.io_port + (10 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|TEST_FTM
mdefine_line|#define TEST_FTM&t;&t;0x01&t;&t;&t;&t;/* Force target mode&t;&t;*/
DECL|macro|TEST_FIM
mdefine_line|#define TEST_FIM&t;&t;0x02&t;&t;&t;&t;/* Force initiator mode&t;&t;*/
DECL|macro|TEST_FHI
mdefine_line|#define TEST_FHI&t;&t;0x04&t;&t;&t;&t;/* Force high impedance mode&t;*/
multiline_comment|/* Configuration register 2 (read/write) */
DECL|macro|REG_CNTL2
mdefine_line|#define REG_CNTL2(x)&t;&t;((x)-&gt;scsi.io_port + (11 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|CNTL2_PGDP
mdefine_line|#define CNTL2_PGDP&t;&t;(1 &lt;&lt; 0)&t;&t;&t;/* Pass Th/Generate Data Parity&t;*/
DECL|macro|CNTL2_PGRP
mdefine_line|#define CNTL2_PGRP&t;&t;(1 &lt;&lt; 1)&t;&t;&t;/* Pass Th/Generate Reg Parity&t;*/
DECL|macro|CNTL2_ACDPE
mdefine_line|#define CNTL2_ACDPE&t;&t;(1 &lt;&lt; 2)&t;&t;&t;/* Abort on Cmd/Data Parity Err&t;*/
DECL|macro|CNTL2_S2FE
mdefine_line|#define CNTL2_S2FE&t;&t;(1 &lt;&lt; 3)&t;&t;&t;/* SCSI2 Features Enable&t;*/
DECL|macro|CNTL2_TSDR
mdefine_line|#define CNTL2_TSDR&t;&t;(1 &lt;&lt; 4)&t;&t;&t;/* Tristate DREQ&t;&t;*/
DECL|macro|CNTL2_SBO
mdefine_line|#define CNTL2_SBO&t;&t;(1 &lt;&lt; 5)&t;&t;&t;/* Select Byte Order&t;&t;*/
DECL|macro|CNTL2_ENF
mdefine_line|#define CNTL2_ENF&t;&t;(1 &lt;&lt; 6)&t;&t;&t;/* Enable features&t;&t;*/
DECL|macro|CNTL2_DAE
mdefine_line|#define CNTL2_DAE&t;&t;(1 &lt;&lt; 7)&t;&t;&t;/* Data Alignment Enable&t;*/
multiline_comment|/* Configuration register 3 (read/write) */
DECL|macro|REG_CNTL3
mdefine_line|#define REG_CNTL3(x)&t;&t;((x)-&gt;scsi.io_port + (12 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|CNTL3_BS8
mdefine_line|#define CNTL3_BS8&t;&t;(1 &lt;&lt; 0)&t;&t;&t;/* Burst size 8&t;&t;&t;*/
DECL|macro|CNTL3_MDM
mdefine_line|#define CNTL3_MDM&t;&t;(1 &lt;&lt; 1)&t;&t;&t;/* Modify DMA mode&t;&t;*/
DECL|macro|CNTL3_LBTM
mdefine_line|#define CNTL3_LBTM&t;&t;(1 &lt;&lt; 2)&t;&t;&t;/* Last Byte Transfer mode&t;*/
DECL|macro|CNTL3_FASTCLK
mdefine_line|#define CNTL3_FASTCLK&t;&t;(1 &lt;&lt; 3)&t;&t;&t;/* Fast SCSI clocking&t;&t;*/
DECL|macro|CNTL3_FASTSCSI
mdefine_line|#define CNTL3_FASTSCSI&t;&t;(1 &lt;&lt; 4)&t;&t;&t;/* Fast SCSI&t;&t;&t;*/
DECL|macro|CNTL3_G2CB
mdefine_line|#define CNTL3_G2CB&t;&t;(1 &lt;&lt; 5)&t;&t;&t;/* Group2 SCSI support&t;&t;*/
DECL|macro|CNTL3_QTAG
mdefine_line|#define CNTL3_QTAG&t;&t;(1 &lt;&lt; 6)&t;&t;&t;/* Enable 3 byte msgs&t;&t;*/
DECL|macro|CNTL3_ADIDCHK
mdefine_line|#define CNTL3_ADIDCHK&t;&t;(1 &lt;&lt; 7)&t;&t;&t;/* Additional ID check&t;&t;*/
multiline_comment|/* High transfer count (read/write) */
DECL|macro|REG_CTCH
mdefine_line|#define REG_CTCH(x)&t;&t;((x)-&gt;scsi.io_port + (14 &lt;&lt; (x)-&gt;scsi.io_shift))
DECL|macro|REG_STCH
mdefine_line|#define REG_STCH(x)&t;&t;((x)-&gt;scsi.io_port + (14 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* ID reigster (read only) */
DECL|macro|REG1_ID
mdefine_line|#define REG1_ID(x)&t;&t;((x)-&gt;scsi.io_port + (14 &lt;&lt; (x)-&gt;scsi.io_shift))
multiline_comment|/* Data alignment */
DECL|macro|REG0_DAL
mdefine_line|#define REG0_DAL(x)&t;&t;((x)-&gt;scsi.io_port + (15 &lt;&lt; (x)-&gt;scsi.io_shift))
r_typedef
r_enum
(brace
DECL|enumerator|PHASE_IDLE
id|PHASE_IDLE
comma
multiline_comment|/* we&squot;re not planning on doing anything&t;*/
DECL|enumerator|PHASE_SELECTION
id|PHASE_SELECTION
comma
multiline_comment|/* selecting a device&t;&t;&t;*/
DECL|enumerator|PHASE_SELSTEPS
id|PHASE_SELSTEPS
comma
multiline_comment|/* selection with command steps&t;&t;*/
DECL|enumerator|PHASE_COMMAND
id|PHASE_COMMAND
comma
multiline_comment|/* command sent&t;&t;&t;&t;*/
DECL|enumerator|PHASE_MESSAGESENT
id|PHASE_MESSAGESENT
comma
multiline_comment|/* selected, and we&squot;re sending cmd&t;*/
DECL|enumerator|PHASE_RECONNECTED
id|PHASE_RECONNECTED
comma
multiline_comment|/* reconnected&t;&t;&t;&t;*/
DECL|enumerator|PHASE_DATAOUT
id|PHASE_DATAOUT
comma
multiline_comment|/* data out to device&t;&t;&t;*/
DECL|enumerator|PHASE_DATAIN
id|PHASE_DATAIN
comma
multiline_comment|/* data in from device&t;&t;&t;*/
DECL|enumerator|PHASE_MSGIN
id|PHASE_MSGIN
comma
multiline_comment|/* message in from device&t;&t;*/
DECL|enumerator|PHASE_MSGIN_DISCONNECT
id|PHASE_MSGIN_DISCONNECT
comma
multiline_comment|/* disconnecting from bus&t;&t;*/
DECL|enumerator|PHASE_MSGOUT
id|PHASE_MSGOUT
comma
multiline_comment|/* after message out phase&t;&t;*/
DECL|enumerator|PHASE_MSGOUT_EXPECT
id|PHASE_MSGOUT_EXPECT
comma
multiline_comment|/* expecting message out&t;&t;*/
DECL|enumerator|PHASE_STATUS
id|PHASE_STATUS
comma
multiline_comment|/* status from device&t;&t;&t;*/
DECL|enumerator|PHASE_DONE
id|PHASE_DONE
multiline_comment|/* Command complete&t;&t;&t;*/
DECL|typedef|phase_t
)brace
id|phase_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DMA_OUT
id|DMA_OUT
comma
multiline_comment|/* DMA from memory to chip&t;&t;*/
DECL|enumerator|DMA_IN
id|DMA_IN
multiline_comment|/* DMA from chip to memory&t;&t;*/
DECL|typedef|fasdmadir_t
)brace
id|fasdmadir_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|fasdma_none
id|fasdma_none
comma
multiline_comment|/* No dma&t;&t;&t;&t;*/
DECL|enumerator|fasdma_pio
id|fasdma_pio
comma
multiline_comment|/* PIO mode&t;&t;&t;&t;*/
DECL|enumerator|fasdma_pseudo
id|fasdma_pseudo
comma
multiline_comment|/* Pseudo DMA&t;&t;&t;&t;*/
DECL|enumerator|fasdma_real_block
id|fasdma_real_block
comma
multiline_comment|/* Real DMA, on block by block basis&t;*/
DECL|enumerator|fasdma_real_all
id|fasdma_real_all
multiline_comment|/* Real DMA, on request by request&t;*/
DECL|typedef|fasdmatype_t
)brace
id|fasdmatype_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|neg_wait
id|neg_wait
comma
multiline_comment|/* Negociate with device&t;&t;*/
DECL|enumerator|neg_inprogress
id|neg_inprogress
comma
multiline_comment|/* Negociation sent&t;&t;&t;*/
DECL|enumerator|neg_complete
id|neg_complete
comma
multiline_comment|/* Negociation complete&t;&t;&t;*/
DECL|enumerator|neg_targcomplete
id|neg_targcomplete
comma
multiline_comment|/* Target completed negociation&t;&t;*/
DECL|enumerator|neg_invalid
id|neg_invalid
multiline_comment|/* Negociation not supported&t;&t;*/
DECL|typedef|neg_t
)brace
id|neg_t
suffix:semicolon
DECL|macro|MAGIC
mdefine_line|#define MAGIC&t;0x441296bdUL
DECL|macro|NR_MSGS
mdefine_line|#define NR_MSGS&t;8
r_typedef
r_struct
(brace
DECL|member|magic_start
r_int
r_int
id|magic_start
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* host&t;&t;&t;&t;&t;*/
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
multiline_comment|/* currently processing command&t;&t;*/
DECL|member|origSCpnt
id|Scsi_Cmnd
op_star
id|origSCpnt
suffix:semicolon
multiline_comment|/* original connecting command&t;&t;*/
DECL|member|reqSCpnt
id|Scsi_Cmnd
op_star
id|reqSCpnt
suffix:semicolon
multiline_comment|/* request sense command&t;&t;*/
multiline_comment|/* driver information */
r_struct
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
multiline_comment|/* base address of FAS216&t;&t;*/
DECL|member|io_shift
r_int
r_int
id|io_shift
suffix:semicolon
multiline_comment|/* shift to adjust reg offsets by&t;*/
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt&t;&t;&t;&t;*/
DECL|member|cfg
r_int
r_char
id|cfg
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* configuration registers&t;&t;*/
DECL|member|type
r_const
r_char
op_star
id|type
suffix:semicolon
multiline_comment|/* chip type&t;&t;&t;&t;*/
DECL|member|phase
id|phase_t
id|phase
suffix:semicolon
multiline_comment|/* current phase&t;&t;&t;*/
r_struct
(brace
DECL|member|target
r_int
r_char
id|target
suffix:semicolon
multiline_comment|/* reconnected target&t;&t;&t;*/
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
multiline_comment|/* reconnected lun&t;&t;&t;*/
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
multiline_comment|/* reconnected tag&t;&t;&t;*/
DECL|member|reconnected
)brace
id|reconnected
suffix:semicolon
DECL|member|SCp
id|Scsi_Pointer
id|SCp
suffix:semicolon
multiline_comment|/* current commands data pointer&t;*/
DECL|member|msgs
id|MsgQueue_t
id|msgs
suffix:semicolon
multiline_comment|/* message queue for connected device&t;*/
DECL|member|async_stp
r_int
r_int
id|async_stp
suffix:semicolon
multiline_comment|/* Async transfer STP value&t;&t;*/
DECL|member|msgin_fifo
r_int
r_char
id|msgin_fifo
suffix:semicolon
multiline_comment|/* bytes in fifo at time of message in&t;*/
DECL|member|message
r_int
r_char
id|message
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* last message received from device&t;*/
DECL|member|msglen
r_int
r_int
id|msglen
suffix:semicolon
multiline_comment|/* length of last message received&t;*/
DECL|member|disconnectable
r_int
r_char
id|disconnectable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* this command can be disconnected&t;*/
DECL|member|aborting
r_int
r_char
id|aborting
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* aborting command&t;&t;&t;*/
DECL|member|scsi
)brace
id|scsi
suffix:semicolon
multiline_comment|/* statistics information */
r_struct
(brace
DECL|member|queues
r_int
r_int
id|queues
suffix:semicolon
DECL|member|removes
r_int
r_int
id|removes
suffix:semicolon
DECL|member|fins
r_int
r_int
id|fins
suffix:semicolon
DECL|member|reads
r_int
r_int
id|reads
suffix:semicolon
DECL|member|writes
r_int
r_int
id|writes
suffix:semicolon
DECL|member|miscs
r_int
r_int
id|miscs
suffix:semicolon
DECL|member|disconnects
r_int
r_int
id|disconnects
suffix:semicolon
DECL|member|aborts
r_int
r_int
id|aborts
suffix:semicolon
DECL|member|bus_resets
r_int
r_int
id|bus_resets
suffix:semicolon
DECL|member|host_resets
r_int
r_int
id|host_resets
suffix:semicolon
DECL|member|stats
)brace
id|stats
suffix:semicolon
multiline_comment|/* configuration information */
r_struct
(brace
DECL|member|clockrate
r_int
r_char
id|clockrate
suffix:semicolon
multiline_comment|/* clock rate of FAS device (MHz)&t;*/
DECL|member|select_timeout
r_int
r_char
id|select_timeout
suffix:semicolon
multiline_comment|/* timeout (R5)&t;&t;&t;&t;*/
DECL|member|sync_max_depth
r_int
r_char
id|sync_max_depth
suffix:semicolon
multiline_comment|/* Synchronous xfer max fifo depth&t;*/
DECL|member|wide_max_size
r_int
r_char
id|wide_max_size
suffix:semicolon
multiline_comment|/* Maximum wide transfer size&t;&t;*/
DECL|member|cntl3
r_int
r_char
id|cntl3
suffix:semicolon
multiline_comment|/* Control Reg 3&t;&t;&t;*/
DECL|member|asyncperiod
r_int
r_int
id|asyncperiod
suffix:semicolon
multiline_comment|/* Async transfer period (ns)&t;&t;*/
DECL|member|disconnect_ok
r_int
r_int
id|disconnect_ok
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Disconnects allowed?&t;&t;&t;*/
DECL|member|ifcfg
)brace
id|ifcfg
suffix:semicolon
multiline_comment|/* queue handling */
r_struct
(brace
DECL|member|issue
id|Queue_t
id|issue
suffix:semicolon
multiline_comment|/* issue queue&t;&t;&t;&t;*/
DECL|member|disconnected
id|Queue_t
id|disconnected
suffix:semicolon
multiline_comment|/* disconnected command queue&t;&t;*/
DECL|member|queues
)brace
id|queues
suffix:semicolon
multiline_comment|/* per-device info */
DECL|struct|fas216_device
r_struct
id|fas216_device
(brace
DECL|member|disconnect_ok
r_int
r_char
id|disconnect_ok
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device can disconnect&t;&t;*/
DECL|member|period
r_int
r_char
id|period
suffix:semicolon
multiline_comment|/* sync xfer period in (*4ns)&t;&t;*/
DECL|member|stp
r_int
r_char
id|stp
suffix:semicolon
multiline_comment|/* synchronous transfer period&t;&t;*/
DECL|member|sof
r_int
r_char
id|sof
suffix:semicolon
multiline_comment|/* synchronous offset register&t;&t;*/
DECL|member|wide_xfer
r_int
r_char
id|wide_xfer
suffix:semicolon
multiline_comment|/* currently negociated wide transfer&t;*/
DECL|member|sync_state
id|neg_t
id|sync_state
suffix:semicolon
multiline_comment|/* synchronous transfer mode&t;&t;*/
DECL|member|wide_state
id|neg_t
id|wide_state
suffix:semicolon
multiline_comment|/* wide transfer mode&t;&t;&t;*/
DECL|member|device
)brace
id|device
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|busyluns
r_int
r_char
id|busyluns
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* array of bits indicating LUNs busy&t;*/
multiline_comment|/* dma */
r_struct
(brace
DECL|member|transfer_type
id|fasdmatype_t
id|transfer_type
suffix:semicolon
multiline_comment|/* current type of DMA transfer&t;&t;*/
DECL|member|setup
id|fasdmatype_t
(paren
op_star
id|setup
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Pointer
op_star
id|SCp
comma
id|fasdmadir_t
id|direction
comma
id|fasdmatype_t
id|min_dma
)paren
suffix:semicolon
DECL|member|pseudo
r_void
(paren
op_star
id|pseudo
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Pointer
op_star
id|SCp
comma
id|fasdmadir_t
id|direction
comma
r_int
id|transfer
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Pointer
op_star
id|SCp
)paren
suffix:semicolon
DECL|member|dma
)brace
id|dma
suffix:semicolon
multiline_comment|/* miscellaneous */
DECL|member|internal_done
r_int
id|internal_done
suffix:semicolon
multiline_comment|/* flag to indicate request done */
DECL|member|magic_end
r_int
r_int
id|magic_end
suffix:semicolon
DECL|typedef|FAS216_Info
)brace
id|FAS216_Info
suffix:semicolon
multiline_comment|/* Function: int fas216_init (struct Scsi_Host *instance)&n; * Purpose : initialise FAS/NCR/AMD SCSI ic.&n; * Params  : instance - a driver-specific filled-out structure&n; * Returns : 0 on success&n; */
r_extern
r_int
id|fas216_init
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_abort (Scsi_Cmnd *SCpnt)&n; * Purpose : abort a command if something horrible happens.&n; * Params  : SCpnt - Command that is believed to be causing a problem.&n; * Returns : one of SCSI_ABORT_ macros.&n; */
r_extern
r_int
id|fas216_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_reset (Scsi_Cmnd *SCpnt, unsigned int reset_flags)&n; * Purpose : resets the adapter if something horrible happens.&n; * Params  : SCpnt - Command that is believed to be causing a problem.&n; *&t;     reset_flags - flags indicating reset type that is believed to be required.&n; * Returns : one of SCSI_RESET_ macros, or&squot;d with the SCSI_RESET_*_RESET macros.&n; */
r_extern
r_int
id|fas216_reset
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_queue_command (Scsi_Cmnd *SCpnt, void (*done)(Scsi_Cmnd *))&n; * Purpose : queue a command for adapter to process.&n; * Params  : SCpnt - Command to queue&n; *&t;     done  - done function to call once command is complete&n; * Returns : 0 - success, else error&n; */
r_extern
r_int
id|fas216_queue_command
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
multiline_comment|/* Function: int fas216_command (Scsi_Cmnd *SCpnt)&n; * Purpose : queue a command for adapter to process.&n; * Params  : SCpnt - Command to queue&n; * Returns : scsi result code&n; */
r_extern
r_int
id|fas216_command
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Function: void fas216_intr (struct Scsi_Host *instance)&n; * Purpose : handle interrupts from the interface to progress a command&n; * Params  : instance - interface to service&n; */
r_extern
r_void
id|fas216_intr
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_release (struct Scsi_Host *instance)&n; * Purpose : release all resources and put everything to bed for FAS/NCR/AMD SCSI ic.&n; * Params  : instance - a driver-specific filled-out structure&n; * Returns : 0 on success&n; */
r_extern
r_int
id|fas216_release
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
r_extern
r_int
id|fas216_info
c_func
(paren
id|FAS216_Info
op_star
id|info
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|fas216_print_host
c_func
(paren
id|FAS216_Info
op_star
id|info
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|fas216_print_stats
c_func
(paren
id|FAS216_Info
op_star
id|info
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|fas216_print_device
c_func
(paren
id|FAS216_Info
op_star
id|info
comma
id|Scsi_Device
op_star
id|scd
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_eh_abort(Scsi_Cmnd *SCpnt)&n; * Purpose : abort this command&n; * Params  : SCpnt - command to abort&n; * Returns : FAILED if unable to abort&n; */
r_extern
r_int
id|fas216_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_eh_device_reset(Scsi_Cmnd *SCpnt)&n; * Purpose : Reset the device associated with this command&n; * Params  : SCpnt - command specifing device to reset&n; * Returns : FAILED if unable to reset&n; */
r_extern
r_int
id|fas216_eh_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_eh_bus_reset(Scsi_Cmnd *SCpnt)&n; * Purpose : Reset the complete bus associated with this command&n; * Params  : SCpnt - command specifing bus to reset&n; * Returns : FAILED if unable to reset&n; */
r_extern
r_int
id|fas216_eh_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/* Function: int fas216_eh_host_reset(Scsi_Cmnd *SCpnt)&n; * Purpose : Reset the host associated with this command&n; * Params  : SCpnt - command specifing host to reset&n; * Returns : FAILED if unable to reset&n; */
r_extern
r_int
id|fas216_eh_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
macro_line|#endif /* FAS216_H */
eof
