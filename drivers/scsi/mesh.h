multiline_comment|/*&n; * mesh.h: definitions for the driver for the MESH SCSI bus adaptor&n; * (Macintosh Enhanced SCSI Hardware) found on Power Macintosh computers.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#ifndef _MESH_H
DECL|macro|_MESH_H
mdefine_line|#define _MESH_H
r_int
id|mesh_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|mesh_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|mesh_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|mesh_queue
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
id|mesh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|mesh_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|SCSI_MESH
mdefine_line|#define SCSI_MESH {&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name:&t;&quot;mesh&quot;,&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&quot;MESH&quot;,&t;&t;&t;&t;&bslash;&n;&t;detect:&t;&t;mesh_detect,&t;&t;&t;&bslash;&n;&t;release:&t;mesh_release,&t;&t;&t;&bslash;&n;&t;command:&t;mesh_command,&t;&t;&t;&bslash;&n;&t;queuecommand:&t;mesh_queue,&t;&t;&t;&bslash;&n;&t;abort:&t;&t;mesh_abort,&t;&t;&t;&bslash;&n;&t;reset:&t;&t;mesh_reset,&t;&t;&t;&bslash;&n;&t;can_queue:&t;20,&t;&t;&t;&t;&bslash;&n;&t;this_id:&t;7,&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;2,&t;&t;&t;&t;&bslash;&n;&t;use_clustering:&t;DISABLE_CLUSTERING,&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Registers in the MESH controller.&n; */
DECL|struct|mesh_regs
r_struct
id|mesh_regs
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
DECL|member|count_hi
r_int
r_char
id|count_hi
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
DECL|member|sequence
r_int
r_char
id|sequence
suffix:semicolon
DECL|member|pad3
r_char
id|pad3
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|bus_status0
r_int
r_char
id|bus_status0
suffix:semicolon
DECL|member|pad4
r_char
id|pad4
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|bus_status1
r_int
r_char
id|bus_status1
suffix:semicolon
DECL|member|pad5
r_char
id|pad5
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|fifo_count
r_int
r_char
id|fifo_count
suffix:semicolon
DECL|member|pad6
r_char
id|pad6
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|exception
r_int
r_char
id|exception
suffix:semicolon
DECL|member|pad7
r_char
id|pad7
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|error
r_int
r_char
id|error
suffix:semicolon
DECL|member|pad8
r_char
id|pad8
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|intr_mask
r_int
r_char
id|intr_mask
suffix:semicolon
DECL|member|pad9
r_char
id|pad9
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|interrupt
r_int
r_char
id|interrupt
suffix:semicolon
DECL|member|pad10
r_char
id|pad10
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|source_id
r_int
r_char
id|source_id
suffix:semicolon
DECL|member|pad11
r_char
id|pad11
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|dest_id
r_int
r_char
id|dest_id
suffix:semicolon
DECL|member|pad12
r_char
id|pad12
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|sync_params
r_int
r_char
id|sync_params
suffix:semicolon
DECL|member|pad13
r_char
id|pad13
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|mesh_id
r_int
r_char
id|mesh_id
suffix:semicolon
DECL|member|pad14
r_char
id|pad14
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|sel_timeout
r_int
r_char
id|sel_timeout
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
multiline_comment|/* Bits in the sequence register. */
DECL|macro|SEQ_DMA_MODE
mdefine_line|#define SEQ_DMA_MODE&t;0x80&t;/* use DMA for data transfer */
DECL|macro|SEQ_TARGET
mdefine_line|#define SEQ_TARGET&t;0x40&t;/* put the controller into target mode */
DECL|macro|SEQ_ATN
mdefine_line|#define SEQ_ATN&t;&t;0x20&t;/* assert ATN signal */
DECL|macro|SEQ_ACTIVE_NEG
mdefine_line|#define SEQ_ACTIVE_NEG&t;0x10&t;/* use active negation on REQ/ACK */
DECL|macro|SEQ_CMD
mdefine_line|#define SEQ_CMD&t;&t;0x0f&t;/* command bits: */
DECL|macro|SEQ_ARBITRATE
mdefine_line|#define SEQ_ARBITRATE&t;1&t;/*  get the bus */
DECL|macro|SEQ_SELECT
mdefine_line|#define SEQ_SELECT&t;2&t;/*  select a target */
DECL|macro|SEQ_COMMAND
mdefine_line|#define SEQ_COMMAND&t;3&t;/*  send a command */
DECL|macro|SEQ_STATUS
mdefine_line|#define SEQ_STATUS&t;4&t;/*  receive status */
DECL|macro|SEQ_DATAOUT
mdefine_line|#define SEQ_DATAOUT&t;5&t;/*  send data */
DECL|macro|SEQ_DATAIN
mdefine_line|#define SEQ_DATAIN&t;6&t;/*  receive data */
DECL|macro|SEQ_MSGOUT
mdefine_line|#define SEQ_MSGOUT&t;7&t;/*  send a message */
DECL|macro|SEQ_MSGIN
mdefine_line|#define SEQ_MSGIN&t;8&t;/*  receive a message */
DECL|macro|SEQ_BUSFREE
mdefine_line|#define SEQ_BUSFREE&t;9&t;/*  look for bus free */
DECL|macro|SEQ_ENBPARITY
mdefine_line|#define SEQ_ENBPARITY&t;0x0a&t;/*  enable parity checking */
DECL|macro|SEQ_DISPARITY
mdefine_line|#define SEQ_DISPARITY&t;0x0b&t;/*  disable parity checking */
DECL|macro|SEQ_ENBRESEL
mdefine_line|#define SEQ_ENBRESEL&t;0x0c&t;/*  enable reselection */
DECL|macro|SEQ_DISRESEL
mdefine_line|#define SEQ_DISRESEL&t;0x0d&t;/*  disable reselection */
DECL|macro|SEQ_RESETMESH
mdefine_line|#define SEQ_RESETMESH&t;0x0e&t;/*  reset the controller */
DECL|macro|SEQ_FLUSHFIFO
mdefine_line|#define SEQ_FLUSHFIFO&t;0x0f&t;/*  clear out the FIFO */
multiline_comment|/* Bits in the bus_status0 and bus_status1 registers:&n;   these correspond directly to the SCSI bus control signals. */
DECL|macro|BS0_REQ
mdefine_line|#define BS0_REQ&t;&t;0x20
DECL|macro|BS0_ACK
mdefine_line|#define BS0_ACK&t;&t;0x10
DECL|macro|BS0_ATN
mdefine_line|#define BS0_ATN&t;&t;0x08
DECL|macro|BS0_MSG
mdefine_line|#define BS0_MSG&t;&t;0x04
DECL|macro|BS0_CD
mdefine_line|#define BS0_CD&t;&t;0x02
DECL|macro|BS0_IO
mdefine_line|#define BS0_IO&t;&t;0x01
DECL|macro|BS1_RST
mdefine_line|#define BS1_RST&t;&t;0x80
DECL|macro|BS1_BSY
mdefine_line|#define BS1_BSY&t;&t;0x40
DECL|macro|BS1_SEL
mdefine_line|#define BS1_SEL&t;&t;0x20
multiline_comment|/* Bus phases defined by the bits in bus_status0 */
DECL|macro|BS0_PHASE
mdefine_line|#define BS0_PHASE&t;(BS0_MSG+BS0_CD+BS0_IO)
DECL|macro|BP_DATAOUT
mdefine_line|#define BP_DATAOUT&t;0
DECL|macro|BP_DATAIN
mdefine_line|#define BP_DATAIN&t;BS0_IO
DECL|macro|BP_COMMAND
mdefine_line|#define BP_COMMAND&t;BS0_CD
DECL|macro|BP_STATUS
mdefine_line|#define BP_STATUS&t;(BS0_CD+BS0_IO)
DECL|macro|BP_MSGOUT
mdefine_line|#define BP_MSGOUT&t;(BS0_MSG+BS0_CD)
DECL|macro|BP_MSGIN
mdefine_line|#define BP_MSGIN&t;(BS0_MSG+BS0_CD+BS0_IO)
multiline_comment|/* Bits in the exception register. */
DECL|macro|EXC_SELWATN
mdefine_line|#define EXC_SELWATN&t;0x20&t;/* (as target) we were selected with ATN */
DECL|macro|EXC_SELECTED
mdefine_line|#define EXC_SELECTED&t;0x10&t;/* (as target) we were selected w/o ATN */
DECL|macro|EXC_RESELECTED
mdefine_line|#define EXC_RESELECTED&t;0x08&t;/* (as initiator) we were reselected */
DECL|macro|EXC_ARBLOST
mdefine_line|#define EXC_ARBLOST&t;0x04&t;/* we lost arbitration */
DECL|macro|EXC_PHASEMM
mdefine_line|#define EXC_PHASEMM&t;0x02&t;/* SCSI phase mismatch */
DECL|macro|EXC_SELTO
mdefine_line|#define EXC_SELTO&t;0x01&t;/* selection timeout */
multiline_comment|/* Bits in the error register */
DECL|macro|ERR_UNEXPDISC
mdefine_line|#define ERR_UNEXPDISC&t;0x40&t;/* target unexpectedly disconnected */
DECL|macro|ERR_SCSIRESET
mdefine_line|#define ERR_SCSIRESET&t;0x20&t;/* SCSI bus got reset on us */
DECL|macro|ERR_SEQERR
mdefine_line|#define ERR_SEQERR&t;0x10&t;/* we did something the chip didn&squot;t like */
DECL|macro|ERR_PARITY
mdefine_line|#define ERR_PARITY&t;0x01&t;/* parity error was detected */
multiline_comment|/* Bits in the interrupt and intr_mask registers */
DECL|macro|INT_ERROR
mdefine_line|#define INT_ERROR&t;0x04&t;/* error interrupt */
DECL|macro|INT_EXCEPTION
mdefine_line|#define INT_EXCEPTION&t;0x02&t;/* exception interrupt */
DECL|macro|INT_CMDDONE
mdefine_line|#define INT_CMDDONE&t;0x01&t;/* command done interrupt */
multiline_comment|/* Fields in the sync_params register */
DECL|macro|SYNC_OFF
mdefine_line|#define SYNC_OFF(x)&t;((x) &gt;&gt; 4)&t;/* offset field */
DECL|macro|SYNC_PER
mdefine_line|#define SYNC_PER(x)&t;((x) &amp; 0xf)&t;/* period field */
DECL|macro|SYNC_PARAMS
mdefine_line|#define SYNC_PARAMS(o, p)&t;(((o) &lt;&lt; 4) | (p))
DECL|macro|ASYNC_PARAMS
mdefine_line|#define ASYNC_PARAMS&t;2&t;/* sync_params value for async xfers */
multiline_comment|/*&n; * Assuming a clock frequency of 50MHz:&n; *&n; * The transfer period with SYNC_PER(sync_params) == x&n; * is (x + 2) * 40ns, except that x == 0 gives 100ns.&n; *&n; * The units of the sel_timeout register are 10ms.&n; */
macro_line|#endif /* _MESH_H */
eof
