macro_line|#ifndef _SIM710_H
DECL|macro|_SIM710_H
mdefine_line|#define _SIM710_H
multiline_comment|/*&n; * sim710.h - Copyright (C) 1999 Richard Hirst&n; */
macro_line|#include &lt;linux/types.h&gt;
r_int
id|sim710_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|sim710_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|sim710_queuecommand
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
id|sim710_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|sim710_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|sim710_dev_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|sim710_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|sim710_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|sim710_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|sim710_release
mdefine_line|#define sim710_release&t;NULL
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|macro|SIM710_SCSI
mdefine_line|#define SIM710_SCSI { proc_name:&t;&t;&quot;sim710&quot;,&t;&bslash;&n;&t;&t;      name:&t;&t;&t;&quot;Simple 53c710&quot;, &t;&bslash;&n;&t;&t;      detect:&t;&t;&t;sim710_detect,&t;&t;&bslash;&n;&t;&t;      release:&t;&t;&t;sim710_release,&t;&t;&bslash;&n;&t;&t;      queuecommand:&t;&t;sim710_queuecommand,&t;&bslash;&n;&t;&t;      eh_abort_handler:&t;&t;sim710_abort,&t;&t;&bslash;&n;&t;&t;      eh_device_reset_handler:&t;sim710_dev_reset,&t;&bslash;&n;&t;&t;      eh_bus_reset_handler:&t;sim710_bus_reset,&t;&bslash;&n;&t;&t;      eh_host_reset_handler:&t;sim710_host_reset,&t;&bslash;&n;&t;&t;      bios_param:&t;&t;scsicam_bios_param,&t;&bslash;&n;&t;&t;      can_queue:&t;&t;8,&t;&t; &t;&bslash;&n;&t;&t;      this_id:&t;&t;&t;7, &t;&t;&t;&bslash;&n;&t;&t;      sg_tablesize:&t;&t;128,&t;&t; &t;&bslash;&n;&t;&t;      cmd_per_lun:&t;&t;1,&t;&t; &t;&bslash;&n;&t;&t;      use_clustering:&t;&t;DISABLE_CLUSTERING,&t;&bslash;&n;&t;&t;      use_new_eh_code:&t;&t;1}
macro_line|#ifndef HOSTS_C
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|bE
mdefine_line|#define&t;bE&t;3&t;/* 0 for little endian, 3 for big endian */
macro_line|#else
DECL|macro|bE
mdefine_line|#define bE&t;0
macro_line|#endif
multiline_comment|/* SCSI control 0 rw, default = 0xc0 */
DECL|macro|SCNTL0_REG
mdefine_line|#define SCNTL0_REG &t;&t;(0x00^bE)
DECL|macro|SCNTL0_ARB1
mdefine_line|#define SCNTL0_ARB1&t;&t;0x80&t;/* 0 0 = simple arbitration */
DECL|macro|SCNTL0_ARB2
mdefine_line|#define SCNTL0_ARB2&t;&t;0x40&t;/* 1 1 = full arbitration */
DECL|macro|SCNTL0_STRT
mdefine_line|#define SCNTL0_STRT&t;&t;0x20&t;/* Start Sequence */
DECL|macro|SCNTL0_WATN
mdefine_line|#define SCNTL0_WATN&t;&t;0x10&t;/* Select with ATN */
DECL|macro|SCNTL0_EPC
mdefine_line|#define SCNTL0_EPC&t;&t;0x08&t;/* Enable parity checking */
multiline_comment|/* Bit 2 is reserved on 800 series chips */
DECL|macro|SCNTL0_EPG_700
mdefine_line|#define SCNTL0_EPG_700&t;&t;0x04&t;/* Enable parity generation */
DECL|macro|SCNTL0_AAP
mdefine_line|#define SCNTL0_AAP&t;&t;0x02&t;/*  ATN/ on parity error */
DECL|macro|SCNTL0_TRG
mdefine_line|#define SCNTL0_TRG&t;&t;0x01&t;/* Target mode */
multiline_comment|/* SCSI control 1 rw, default = 0x00 */
DECL|macro|SCNTL1_REG
mdefine_line|#define SCNTL1_REG &t;&t;(0x01^bE)
DECL|macro|SCNTL1_EXC
mdefine_line|#define SCNTL1_EXC&t;&t;0x80&t;/* Extra Clock Cycle of Data setup */
DECL|macro|SCNTL1_ADB
mdefine_line|#define SCNTL1_ADB&t;&t;0x40&t;/*  contents of SODL on bus */
DECL|macro|SCNTL1_ESR_700
mdefine_line|#define SCNTL1_ESR_700&t;&t;0x20&t;/* Enable SIOP response to selection&n;&t;&t;&t;&t;&t;   and reselection */
DECL|macro|SCNTL1_CON
mdefine_line|#define SCNTL1_CON&t;&t;0x10&t;/* Connected */
DECL|macro|SCNTL1_RST
mdefine_line|#define SCNTL1_RST&t;&t;0x08&t;/* SCSI RST/ */
DECL|macro|SCNTL1_AESP
mdefine_line|#define SCNTL1_AESP&t;&t;0x04&t;/* Force bad parity */
DECL|macro|SCNTL1_SND_700
mdefine_line|#define SCNTL1_SND_700&t;&t;0x02&t;/* Start SCSI send */
DECL|macro|SCNTL1_IARB_800
mdefine_line|#define SCNTL1_IARB_800&t;&t;0x02&t;/* Immediate Arbitration, start&n;&t;&t;&t;&t;&t;   arbitration immediately after&n;&t;&t;&t;&t;&t;   busfree is detected */
DECL|macro|SCNTL1_RCV_700
mdefine_line|#define SCNTL1_RCV_700&t;&t;0x01&t;/* Start SCSI receive */
DECL|macro|SCNTL1_SST_800
mdefine_line|#define SCNTL1_SST_800&t;&t;0x01&t;/* Start SCSI transfer */
multiline_comment|/* SCSI control 2 rw, */
DECL|macro|SCNTL2_REG_800
mdefine_line|#define SCNTL2_REG_800&t;&t;(0x02^bE)
DECL|macro|SCNTL2_800_SDU
mdefine_line|#define SCNTL2_800_SDU&t;&t;0x80&t;/* SCSI disconnect unexpected */
multiline_comment|/* SCSI control 3 rw */
DECL|macro|SCNTL3_REG_800
mdefine_line|#define SCNTL3_REG_800 &t;&t;(0x03^bE)
DECL|macro|SCNTL3_800_SCF_SHIFT
mdefine_line|#define SCNTL3_800_SCF_SHIFT&t;4
DECL|macro|SCNTL3_800_SCF_MASK
mdefine_line|#define SCNTL3_800_SCF_MASK&t;0x70
DECL|macro|SCNTL3_800_SCF2
mdefine_line|#define SCNTL3_800_SCF2&t;&t;0x40&t;/* Synchronous divisor */
DECL|macro|SCNTL3_800_SCF1
mdefine_line|#define SCNTL3_800_SCF1&t;&t;0x20&t;/* 0x00 = SCLK/3 */
DECL|macro|SCNTL3_800_SCF0
mdefine_line|#define SCNTL3_800_SCF0&t;&t;0x10&t;/* 0x10 = SCLK/1 */
multiline_comment|/* 0x20 = SCLK/1.5&n;&t;&t;&t;&t;&t;   0x30 = SCLK/2&n;&t;&t;&t;&t;&t;   0x40 = SCLK/3 */
DECL|macro|SCNTL3_800_CCF_SHIFT
mdefine_line|#define SCNTL3_800_CCF_SHIFT&t;0
DECL|macro|SCNTL3_800_CCF_MASK
mdefine_line|#define SCNTL3_800_CCF_MASK&t;0x07
DECL|macro|SCNTL3_800_CCF2
mdefine_line|#define SCNTL3_800_CCF2&t;&t;0x04&t;/* 0x00 50.01 to 66 */
DECL|macro|SCNTL3_800_CCF1
mdefine_line|#define SCNTL3_800_CCF1&t;&t;0x02&t;/* 0x01 16.67 to 25 */
DECL|macro|SCNTL3_800_CCF0
mdefine_line|#define SCNTL3_800_CCF0&t;&t;0x01&t;/* 0x02&t;25.01 - 37.5&n;&t;&t;&t;&t;&t;   0x03&t;37.51 - 50&n;&t;&t;&t;&t;&t;   0x04 50.01 - 66 */
multiline_comment|/*&n; * SCSI destination ID rw - the appropriate bit is set for the selected&n; * target ID.  This is written by the SCSI SCRIPTS processor.&n; * default = 0x00&n; */
DECL|macro|SDID_REG_700
mdefine_line|#define SDID_REG_700  &t;&t;(0x02^bE)
DECL|macro|SDID_REG_800
mdefine_line|#define SDID_REG_800  &t;&t;(0x06^bE)
DECL|macro|GP_REG_800
mdefine_line|#define GP_REG_800&t;&t;(0x07^bE) /* General purpose IO */
DECL|macro|GP_800_IO1
mdefine_line|#define GP_800_IO1&t;&t;0x02
DECL|macro|GP_800_IO2
mdefine_line|#define GP_800_IO2&t;&t;0x01
multiline_comment|/* SCSI interrupt enable rw, default = 0x00 */
DECL|macro|SIEN_REG_700
mdefine_line|#define SIEN_REG_700&t;&t;(0x03^bE)
DECL|macro|SIEN0_REG_800
mdefine_line|#define SIEN0_REG_800&t;&t;(0x40^bE)
DECL|macro|SIEN_MA
mdefine_line|#define SIEN_MA&t;&t;&t;0x80&t;/* Phase mismatch (ini) or ATN (tgt) */
DECL|macro|SIEN_FC
mdefine_line|#define SIEN_FC&t;&t;&t;0x40&t;/* Function complete */
DECL|macro|SIEN_700_STO
mdefine_line|#define SIEN_700_STO&t;&t;0x20&t;/* Selection or reselection timeout */
DECL|macro|SIEN_800_SEL
mdefine_line|#define SIEN_800_SEL&t;&t;0x20&t;/* Selected */
DECL|macro|SIEN_700_SEL
mdefine_line|#define SIEN_700_SEL&t;&t;0x10&t;/* Selected or reselected */
DECL|macro|SIEN_800_RESEL
mdefine_line|#define SIEN_800_RESEL&t;&t;0x10&t;/* Reselected */
DECL|macro|SIEN_SGE
mdefine_line|#define SIEN_SGE&t;&t;0x08&t;/* SCSI gross error */
DECL|macro|SIEN_UDC
mdefine_line|#define SIEN_UDC&t;&t;0x04&t;/* Unexpected disconnect */
DECL|macro|SIEN_RST
mdefine_line|#define SIEN_RST&t;&t;0x02&t;/* SCSI RST/ received */
DECL|macro|SIEN_PAR
mdefine_line|#define SIEN_PAR&t;&t;0x01&t;/* Parity error */
multiline_comment|/*&n; * SCSI chip ID rw&n; * NCR53c700 :&n; * &t;When arbitrating, the highest bit is used, when reselection or selection&n; * &t;occurs, the chip responds to all IDs for which a bit is set.&n; * &t;default = 0x00&n; */
DECL|macro|SCID_REG
mdefine_line|#define SCID_REG&t;&t;(0x04^bE)
multiline_comment|/* Bit 7 is reserved on 800 series chips */
DECL|macro|SCID_800_RRE
mdefine_line|#define SCID_800_RRE&t;&t;0x40&t;/* Enable response to reselection */
DECL|macro|SCID_800_SRE
mdefine_line|#define SCID_800_SRE&t;&t;0x20&t;/* Enable response to selection */
multiline_comment|/* Bits four and three are reserved on 800 series chips */
DECL|macro|SCID_800_ENC_MASK
mdefine_line|#define SCID_800_ENC_MASK&t;0x07&t;/* Encoded SCSI ID */
multiline_comment|/* SCSI transfer rw, default = 0x00 */
DECL|macro|SXFER_REG
mdefine_line|#define SXFER_REG&t;&t;(0x05^bE)
DECL|macro|SXFER_DHP
mdefine_line|#define SXFER_DHP&t;&t;0x80&t;/* Disable halt on parity */
DECL|macro|SXFER_TP2
mdefine_line|#define SXFER_TP2&t;&t;0x40&t;/* Transfer period msb */
DECL|macro|SXFER_TP1
mdefine_line|#define SXFER_TP1&t;&t;0x20
DECL|macro|SXFER_TP0
mdefine_line|#define SXFER_TP0&t;&t;0x10&t;/* lsb */
DECL|macro|SXFER_TP_MASK
mdefine_line|#define SXFER_TP_MASK&t;&t;0x70
multiline_comment|/* FIXME : SXFER_TP_SHIFT == 5 is right for &squot;8xx chips */
DECL|macro|SXFER_TP_SHIFT
mdefine_line|#define SXFER_TP_SHIFT&t;&t;5
DECL|macro|SXFER_TP_4
mdefine_line|#define SXFER_TP_4&t;&t;0x00&t;/* Divisors */
DECL|macro|SXFER_TP_5
mdefine_line|#define SXFER_TP_5&t;&t;0x10&lt;&lt;1
DECL|macro|SXFER_TP_6
mdefine_line|#define SXFER_TP_6&t;&t;0x20&lt;&lt;1
DECL|macro|SXFER_TP_7
mdefine_line|#define SXFER_TP_7&t;&t;0x30&lt;&lt;1
DECL|macro|SXFER_TP_8
mdefine_line|#define SXFER_TP_8&t;&t;0x40&lt;&lt;1
DECL|macro|SXFER_TP_9
mdefine_line|#define SXFER_TP_9&t;&t;0x50&lt;&lt;1
DECL|macro|SXFER_TP_10
mdefine_line|#define SXFER_TP_10&t;&t;0x60&lt;&lt;1
DECL|macro|SXFER_TP_11
mdefine_line|#define SXFER_TP_11&t;&t;0x70&lt;&lt;1
DECL|macro|SXFER_MO3
mdefine_line|#define SXFER_MO3&t;&t;0x08&t;/* Max offset msb */
DECL|macro|SXFER_MO2
mdefine_line|#define SXFER_MO2&t;&t;0x04
DECL|macro|SXFER_MO1
mdefine_line|#define SXFER_MO1&t;&t;0x02
DECL|macro|SXFER_MO0
mdefine_line|#define SXFER_MO0&t;&t;0x01&t;/* lsb */
DECL|macro|SXFER_MO_MASK
mdefine_line|#define SXFER_MO_MASK&t;&t;0x0f
DECL|macro|SXFER_MO_SHIFT
mdefine_line|#define SXFER_MO_SHIFT&t;&t;0
multiline_comment|/*&n; * SCSI output data latch rw&n; * The contents of this register are driven onto the SCSI bus when&n; * the Assert Data Bus bit of the SCNTL1 register is set and&n; * the CD, IO, and MSG bits of the SOCL register match the SCSI phase&n; */
DECL|macro|SODL_REG_700
mdefine_line|#define SODL_REG_700&t;&t;(0x06^bE)
DECL|macro|SODL_REG_800
mdefine_line|#define SODL_REG_800&t;&t;(0x54^bE)
multiline_comment|/*&n; * SCSI output control latch rw, default = 0&n; * Note that when the chip is being manually programmed as an initiator,&n; * the MSG, CD, and IO bits must be set correctly for the phase the target&n; * is driving the bus in.  Otherwise no data transfer will occur due to&n; * phase mismatch.&n; */
DECL|macro|SOCL_REG
mdefine_line|#define SOCL_REG&t;&t;(0x07^bE)
DECL|macro|SOCL_REQ
mdefine_line|#define SOCL_REQ&t;&t;0x80&t;/*  REQ */
DECL|macro|SOCL_ACK
mdefine_line|#define SOCL_ACK&t;&t;0x40&t;/*  ACK */
DECL|macro|SOCL_BSY
mdefine_line|#define SOCL_BSY&t;&t;0x20&t;/*  BSY */
DECL|macro|SOCL_SEL
mdefine_line|#define SOCL_SEL&t;&t;0x10&t;/*  SEL */
DECL|macro|SOCL_ATN
mdefine_line|#define SOCL_ATN&t;&t;0x08&t;/*  ATN */
DECL|macro|SOCL_MSG
mdefine_line|#define SOCL_MSG&t;&t;0x04&t;/*  MSG */
DECL|macro|SOCL_CD
mdefine_line|#define SOCL_CD&t;&t;&t;0x02&t;/*  C/D */
DECL|macro|SOCL_IO
mdefine_line|#define SOCL_IO&t;&t;&t;0x01&t;/*  I/O */
multiline_comment|/*&n; * SCSI first byte received latch ro&n; * This register contains the first byte received during a block MOVE&n; * SCSI SCRIPTS instruction, including&n; *&n; * Initiator mode&t;Target mode&n; * Message in&t;&t;Command&n; * Status&t;&t;Message out&n; * Data in&t;&t;Data out&n; *&n; * It also contains the selecting or reselecting device&squot;s ID and our&n; * ID.&n; *&n; * Note that this is the register the various IF conditionals can&n; * operate on.&n; */
DECL|macro|SFBR_REG
mdefine_line|#define SFBR_REG&t;&t;(0x08^bE)
multiline_comment|/*&n; * SCSI input data latch ro&n; * In initiator mode, data is latched into this register on the rising&n; * edge of REQ/. In target mode, data is latched on the rising edge of&n; * ACK/&n; */
DECL|macro|SIDL_REG_700
mdefine_line|#define SIDL_REG_700&t;&t;(0x09^bE)
DECL|macro|SIDL_REG_800
mdefine_line|#define SIDL_REG_800&t;&t;(0x50^bE)
multiline_comment|/*&n; * SCSI bus data lines ro&n; * This register reflects the instantaneous status of the SCSI data&n; * lines.  Note that SCNTL0 must be set to disable parity checking,&n; * otherwise reading this register will latch new parity.&n; */
DECL|macro|SBDL_REG_700
mdefine_line|#define SBDL_REG_700&t;&t;(0x0a^bE)
DECL|macro|SBDL_REG_800
mdefine_line|#define SBDL_REG_800&t;&t;(0x58^bE)
DECL|macro|SSID_REG_800
mdefine_line|#define SSID_REG_800&t;&t;(0x0a^bE)
DECL|macro|SSID_800_VAL
mdefine_line|#define SSID_800_VAL&t;&t;0x80&t;/* Exactly two bits asserted at sel */
DECL|macro|SSID_800_ENCID_MASK
mdefine_line|#define SSID_800_ENCID_MASK&t;0x07&t;/* Device which performed operation */
multiline_comment|/*&n; * SCSI bus control lines rw,&n; * instantaneous readout of control lines&n; */
DECL|macro|SBCL_REG
mdefine_line|#define SBCL_REG&t;&t;(0x0b^bE)
DECL|macro|SBCL_REQ
mdefine_line|#define SBCL_REQ&t;&t;0x80&t;/*  REQ ro */
DECL|macro|SBCL_ACK
mdefine_line|#define SBCL_ACK&t;&t;0x40&t;/*  ACK ro */
DECL|macro|SBCL_BSY
mdefine_line|#define SBCL_BSY&t;&t;0x20&t;/*  BSY ro */
DECL|macro|SBCL_SEL
mdefine_line|#define SBCL_SEL&t;&t;0x10&t;/*  SEL ro */
DECL|macro|SBCL_ATN
mdefine_line|#define SBCL_ATN&t;&t;0x08&t;/*  ATN ro */
DECL|macro|SBCL_MSG
mdefine_line|#define SBCL_MSG&t;&t;0x04&t;/*  MSG ro */
DECL|macro|SBCL_CD
mdefine_line|#define SBCL_CD&t;&t;&t;0x02&t;/*  C/D ro */
DECL|macro|SBCL_IO
mdefine_line|#define SBCL_IO&t;&t;&t;0x01&t;/*  I/O ro */
DECL|macro|SBCL_PHASE_CMDOUT
mdefine_line|#define SBCL_PHASE_CMDOUT&t;SBCL_CD
DECL|macro|SBCL_PHASE_DATAIN
mdefine_line|#define SBCL_PHASE_DATAIN&t;SBCL_IO
DECL|macro|SBCL_PHASE_DATAOUT
mdefine_line|#define SBCL_PHASE_DATAOUT&t;0
DECL|macro|SBCL_PHASE_MSGIN
mdefine_line|#define SBCL_PHASE_MSGIN&t;(SBCL_CD|SBCL_IO|SBCL_MSG)
DECL|macro|SBCL_PHASE_MSGOUT
mdefine_line|#define SBCL_PHASE_MSGOUT&t;(SBCL_CD|SBCL_MSG)
DECL|macro|SBCL_PHASE_STATIN
mdefine_line|#define SBCL_PHASE_STATIN&t;(SBCL_CD|SBCL_IO)
DECL|macro|SBCL_PHASE_MASK
mdefine_line|#define SBCL_PHASE_MASK&t;&t;(SBCL_CD|SBCL_IO|SBCL_MSG)
multiline_comment|/*&n; * Synchronous SCSI Clock Control bits&n; * 0 - set by DCNTL&n; * 1 - SCLK / 1.0&n; * 2 - SCLK / 1.5&n; * 3 - SCLK / 2.0&n; */
DECL|macro|SBCL_SSCF1
mdefine_line|#define SBCL_SSCF1&t;&t;0x02&t;/* wo, -66 only */
DECL|macro|SBCL_SSCF0
mdefine_line|#define SBCL_SSCF0&t;&t;0x01&t;/* wo, -66 only */
DECL|macro|SBCL_SSCF_MASK
mdefine_line|#define SBCL_SSCF_MASK&t;&t;0x03
multiline_comment|/*&n; * XXX note : when reading the DSTAT and STAT registers to clear interrupts,&n; * insure that 10 clocks elapse between the two&n; */
multiline_comment|/* DMA status ro */
DECL|macro|DSTAT_REG
mdefine_line|#define DSTAT_REG&t;&t;(0x0c^bE)
DECL|macro|DSTAT_DFE
mdefine_line|#define DSTAT_DFE&t;&t;0x80&t;/* DMA FIFO empty */
DECL|macro|DSTAT_800_MDPE
mdefine_line|#define DSTAT_800_MDPE&t;&t;0x40&t;/* Master Data Parity Error */
DECL|macro|DSTAT_BF
mdefine_line|#define DSTAT_BF&t;&t;0x20&t;/* Bus Fault */
DECL|macro|DSTAT_ABRT
mdefine_line|#define DSTAT_ABRT&t;&t;0x10&t;/* Aborted - set on error */
DECL|macro|DSTAT_SSI
mdefine_line|#define DSTAT_SSI&t;&t;0x08&t;/* SCRIPTS single step interrupt */
DECL|macro|DSTAT_SIR
mdefine_line|#define DSTAT_SIR&t;&t;0x04&t;/* SCRIPTS interrupt received -&n;&t;&t;&t;&t;&t;   set when INT instruction is&n;&t;&t;&t;&t;&t;   executed */
DECL|macro|DSTAT_WTD
mdefine_line|#define DSTAT_WTD&t;&t;0x02&t;/* Watchdog timeout detected */
DECL|macro|DSTAT_OPC
mdefine_line|#define DSTAT_OPC&t;&t;0x01&t;/* Illegal instruction */
DECL|macro|DSTAT_IID
mdefine_line|#define DSTAT_IID&t;&t;0x01&t;/* Same thing, different name */
DECL|macro|SSTAT0_REG
mdefine_line|#define SSTAT0_REG&t;&t;(0x0d^bE)&t;/* SCSI status 0 ro */
DECL|macro|SIST0_REG_800
mdefine_line|#define SIST0_REG_800&t;&t;(0x42^bE)&t;/* SCSI status 0 ro */
DECL|macro|SSTAT0_MA
mdefine_line|#define SSTAT0_MA&t;&t;0x80&t;/* ini : phase mismatch,&n;&t;&t;&t;&t;&t; * tgt : ATN/ asserted&n;&t;&t;&t;&t;&t; */
DECL|macro|SSTAT0_CMP
mdefine_line|#define SSTAT0_CMP&t;&t;0x40&t;/* function complete */
DECL|macro|SSTAT0_700_STO
mdefine_line|#define SSTAT0_700_STO&t;&t;0x20&t;/* Selection or reselection timeout */
DECL|macro|SSTAT0_800_SEL
mdefine_line|#define SSTAT0_800_SEL&t;&t;0x20&t;/* Selected */
DECL|macro|SSTAT0_700_SEL
mdefine_line|#define SSTAT0_700_SEL&t;&t;0x10&t;/* Selected or reselected */
DECL|macro|SIST0_800_RSL
mdefine_line|#define SIST0_800_RSL&t;&t;0x10&t;/* Reselected */
DECL|macro|SSTAT0_SGE
mdefine_line|#define SSTAT0_SGE&t;&t;0x08&t;/* SCSI gross error */
DECL|macro|SSTAT0_UDC
mdefine_line|#define SSTAT0_UDC&t;&t;0x04&t;/* Unexpected disconnect */
DECL|macro|SSTAT0_RST
mdefine_line|#define SSTAT0_RST&t;&t;0x02&t;/* SCSI RST/ received */
DECL|macro|SSTAT0_PAR
mdefine_line|#define SSTAT0_PAR&t;&t;0x01&t;/* Parity error */
DECL|macro|SSTAT1_REG
mdefine_line|#define SSTAT1_REG&t;&t;(0x0e^bE)&t;/* SCSI status 1 ro */
DECL|macro|SSTAT1_ILF
mdefine_line|#define SSTAT1_ILF&t;&t;0x80&t;/* SIDL full */
DECL|macro|SSTAT1_ORF
mdefine_line|#define SSTAT1_ORF&t;&t;0x40&t;/* SODR full */
DECL|macro|SSTAT1_OLF
mdefine_line|#define SSTAT1_OLF&t;&t;0x20&t;/* SODL full */
DECL|macro|SSTAT1_AIP
mdefine_line|#define SSTAT1_AIP&t;&t;0x10&t;/* Arbitration in progress */
DECL|macro|SSTAT1_LOA
mdefine_line|#define SSTAT1_LOA&t;&t;0x08&t;/* Lost arbitration */
DECL|macro|SSTAT1_WOA
mdefine_line|#define SSTAT1_WOA&t;&t;0x04&t;/* Won arbitration */
DECL|macro|SSTAT1_RST
mdefine_line|#define SSTAT1_RST&t;&t;0x02&t;/* Instant readout of RST/ */
DECL|macro|SSTAT1_SDP
mdefine_line|#define SSTAT1_SDP&t;&t;0x01&t;/* Instant readout of SDP/ */
DECL|macro|SSTAT2_REG
mdefine_line|#define SSTAT2_REG&t;&t;(0x0f^bE)&t;/* SCSI status 2 ro */
DECL|macro|SSTAT2_FF3
mdefine_line|#define SSTAT2_FF3&t;&t;0x80 &t;/* number of bytes in synchronous */
DECL|macro|SSTAT2_FF2
mdefine_line|#define SSTAT2_FF2&t;&t;0x40&t;/* data FIFO */
DECL|macro|SSTAT2_FF1
mdefine_line|#define SSTAT2_FF1&t;&t;0x20
DECL|macro|SSTAT2_FF0
mdefine_line|#define SSTAT2_FF0&t;&t;0x10
DECL|macro|SSTAT2_FF_MASK
mdefine_line|#define SSTAT2_FF_MASK&t;&t;0xf0
DECL|macro|SSTAT2_FF_SHIFT
mdefine_line|#define SSTAT2_FF_SHIFT&t;&t;4
multiline_comment|/*&n; * Latched signals, latched on the leading edge of REQ/ for initiators,&n; * ACK/ for targets.&n; */
DECL|macro|SSTAT2_SDP
mdefine_line|#define SSTAT2_SDP&t;&t;0x08&t;/* SDP */
DECL|macro|SSTAT2_MSG
mdefine_line|#define SSTAT2_MSG&t;&t;0x04&t;/* MSG */
DECL|macro|SSTAT2_CD
mdefine_line|#define SSTAT2_CD&t;&t;0x02&t;/* C/D */
DECL|macro|SSTAT2_IO
mdefine_line|#define SSTAT2_IO&t;&t;0x01&t;/* I/O */
DECL|macro|SSTAT2_PHASE_CMDOUT
mdefine_line|#define SSTAT2_PHASE_CMDOUT&t;SSTAT2_CD
DECL|macro|SSTAT2_PHASE_DATAIN
mdefine_line|#define SSTAT2_PHASE_DATAIN&t;SSTAT2_IO
DECL|macro|SSTAT2_PHASE_DATAOUT
mdefine_line|#define SSTAT2_PHASE_DATAOUT&t;0
DECL|macro|SSTAT2_PHASE_MSGIN
mdefine_line|#define SSTAT2_PHASE_MSGIN&t;(SSTAT2_CD|SSTAT2_IO|SSTAT2_MSG)
DECL|macro|SSTAT2_PHASE_MSGOUT
mdefine_line|#define SSTAT2_PHASE_MSGOUT&t;(SSTAT2_CD|SSTAT2_MSG)
DECL|macro|SSTAT2_PHASE_STATIN
mdefine_line|#define SSTAT2_PHASE_STATIN&t;(SSTAT2_CD|SSTAT2_IO)
DECL|macro|SSTAT2_PHASE_MASK
mdefine_line|#define SSTAT2_PHASE_MASK&t;(SSTAT2_CD|SSTAT2_IO|SSTAT2_MSG)
DECL|macro|DSA_REG
mdefine_line|#define DSA_REG&t;&t;&t;0x10&t;/* DATA structure address */
DECL|macro|CTEST0_REG_700
mdefine_line|#define CTEST0_REG_700&t;&t;(0x14^bE)&t;/* Chip test 0 ro */
DECL|macro|CTEST0_REG_800
mdefine_line|#define CTEST0_REG_800&t;&t;(0x18^bE)&t;/* Chip test 0 ro */
multiline_comment|/* 0x80 - 0x04 are reserved */
DECL|macro|CTEST0_700_RTRG
mdefine_line|#define CTEST0_700_RTRG&t;&t;0x02&t;/* Real target mode */
DECL|macro|CTEST0_700_DDIR
mdefine_line|#define CTEST0_700_DDIR&t;&t;0x01&t;/* Data direction, 1 =&n;&t;&t;&t;&t;&t; * SCSI bus to host, 0  =&n;&t;&t;&t;&t;&t; * host to SCSI.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST1_REG_700
mdefine_line|#define CTEST1_REG_700&t;&t;(0x15^bE)&t;/* Chip test 1 ro */
DECL|macro|CTEST1_REG_800
mdefine_line|#define CTEST1_REG_800&t;&t;(0x19^bE)&t;/* Chip test 1 ro */
DECL|macro|CTEST1_FMT3
mdefine_line|#define CTEST1_FMT3&t;&t;0x80&t;/* Identify which byte lanes are empty */
DECL|macro|CTEST1_FMT2
mdefine_line|#define CTEST1_FMT2&t;&t;0x40 &t;/* in the DMA FIFO */
DECL|macro|CTEST1_FMT1
mdefine_line|#define CTEST1_FMT1&t;&t;0x20
DECL|macro|CTEST1_FMT0
mdefine_line|#define CTEST1_FMT0&t;&t;0x10
DECL|macro|CTEST1_FFL3
mdefine_line|#define CTEST1_FFL3&t;&t;0x08&t;/* Identify which bytes lanes are full */
DECL|macro|CTEST1_FFL2
mdefine_line|#define CTEST1_FFL2&t;&t;0x04&t;/* in the DMA FIFO */
DECL|macro|CTEST1_FFL1
mdefine_line|#define CTEST1_FFL1&t;&t;0x02
DECL|macro|CTEST1_FFL0
mdefine_line|#define CTEST1_FFL0&t;&t;0x01
DECL|macro|CTEST2_REG_700
mdefine_line|#define CTEST2_REG_700&t;&t;(0x16^bE)&t;/* Chip test 2 ro */
DECL|macro|CTEST2_REG_800
mdefine_line|#define CTEST2_REG_800&t;&t;(0x1a^bE)&t;/* Chip test 2 ro */
DECL|macro|CTEST2_800_DDIR
mdefine_line|#define CTEST2_800_DDIR&t;&t;0x80&t;/* 1 = SCSI-&gt;host */
DECL|macro|CTEST2_800_SIGP
mdefine_line|#define CTEST2_800_SIGP&t;&t;0x40&t;/* A copy of SIGP in ISTAT.&n;&t;&t;&t;&t;&t;   Reading this register clears */
DECL|macro|CTEST2_800_CIO
mdefine_line|#define CTEST2_800_CIO&t;&t;0x20&t;/* Configured as IO */.
DECL|macro|CTEST2_800_CM
mdefine_line|#define CTEST2_800_CM&t;&t;0x10&t;/* Configured as memory */
multiline_comment|/* 0x80 - 0x40 are reserved on 700 series chips */
DECL|macro|CTEST2_700_SOFF
mdefine_line|#define CTEST2_700_SOFF&t;&t;0x20&t;/* SCSI Offset Compare,&n;&t;&t;&t;&t;&t; * As an initiator, this bit is&n;&t;&t;&t;&t;&t; * one when the synchronous offset&n;&t;&t;&t;&t;&t; * is zero, as a target this bit&n;&t;&t;&t;&t;&t; * is one when the synchronous&n;&t;&t;&t;&t;&t; * offset is at the maximum&n;&t;&t;&t;&t;&t; * defined in SXFER&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST2_700_SFP
mdefine_line|#define CTEST2_700_SFP&t;&t;0x10&t;/* SCSI FIFO parity bit,&n;&t;&t;&t;&t;&t; * reading CTEST3 unloads a byte&n;&t;&t;&t;&t;&t; * from the FIFO and sets this&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST2_700_DFP
mdefine_line|#define CTEST2_700_DFP&t;&t;0x08&t;/* DMA FIFO parity bit,&n;&t;&t;&t;&t;&t; * reading CTEST6 unloads a byte&n;&t;&t;&t;&t;&t; * from the FIFO and sets this&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST2_TEOP
mdefine_line|#define CTEST2_TEOP&t;&t;0x04&t;/* SCSI true end of process,&n;&t;&t;&t;&t;&t; * indicates a totally finished&n;&t;&t;&t;&t;&t; * transfer&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST2_DREQ
mdefine_line|#define CTEST2_DREQ&t;&t;0x02&t;/* Data request signal */
multiline_comment|/* 0x01 is reserved on 700 series chips */
DECL|macro|CTEST2_800_DACK
mdefine_line|#define CTEST2_800_DACK&t;&t;0x01
multiline_comment|/*&n; * Chip test 3 ro&n; * Unloads the bottom byte of the eight deep SCSI synchronous FIFO,&n; * check SSTAT2 FIFO full bits to determine size.  Note that a GROSS&n; * error results if a read is attempted on this register.  Also note&n; * that 16 and 32 bit reads of this register will cause corruption.&n; */
DECL|macro|CTEST3_REG_700
mdefine_line|#define CTEST3_REG_700&t;&t;(0x17^bE)
multiline_comment|/*  Chip test 3 rw */
DECL|macro|CTEST3_REG_800
mdefine_line|#define CTEST3_REG_800&t;&t;(0x1b^bE)
DECL|macro|CTEST3_800_V3
mdefine_line|#define CTEST3_800_V3&t;&t;0x80&t;/* Chip revision */
DECL|macro|CTEST3_800_V2
mdefine_line|#define CTEST3_800_V2&t;&t;0x40
DECL|macro|CTEST3_800_V1
mdefine_line|#define CTEST3_800_V1&t;&t;0x20
DECL|macro|CTEST3_800_V0
mdefine_line|#define CTEST3_800_V0&t;&t;0x10
DECL|macro|CTEST3_800_FLF
mdefine_line|#define CTEST3_800_FLF&t;&t;0x08&t;/* Flush DMA FIFO */
DECL|macro|CTEST3_800_CLF
mdefine_line|#define CTEST3_800_CLF&t;&t;0x04&t;/* Clear DMA FIFO */
DECL|macro|CTEST3_800_FM
mdefine_line|#define CTEST3_800_FM&t;&t;0x02&t;/* Fetch mode pin */
multiline_comment|/* bit 0 is reserved on 800 series chips */
DECL|macro|CTEST4_REG_400
mdefine_line|#define CTEST4_REG_400&t;&t;(0x18^bE)&t;/* Chip test 4 rw */
DECL|macro|CTEST4_REG_800
mdefine_line|#define CTEST4_REG_800&t;&t;(0x21^bE)&t;/* Chip test 4 rw */
multiline_comment|/* 0x80 is reserved on 700 series chips */
DECL|macro|CTEST4_800_BDIS
mdefine_line|#define CTEST4_800_BDIS&t;&t;0x80&t;/* Burst mode disable */
DECL|macro|CTEST4_ZMOD
mdefine_line|#define CTEST4_ZMOD&t;&t;0x40&t;/* High impedance mode */
DECL|macro|CTEST4_SZM
mdefine_line|#define CTEST4_SZM&t;&t;0x20&t;/* SCSI bus high impedance */
DECL|macro|CTEST4_700_SLBE
mdefine_line|#define CTEST4_700_SLBE&t;&t;0x10&t;/* SCSI loopback enabled */
DECL|macro|CTEST4_800_SRTM
mdefine_line|#define CTEST4_800_SRTM&t;&t;0x10&t;/* Shadow Register Test Mode */
DECL|macro|CTEST4_700_SFWR
mdefine_line|#define CTEST4_700_SFWR&t;&t;0x08&t;/* SCSI FIFO write enable,&n;&t;&t;&t;&t;&t; * redirects writes from SODL&n;&t;&t;&t;&t;&t; * to the SCSI FIFO.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST4_800_MPEE
mdefine_line|#define CTEST4_800_MPEE&t;&t;0x08&t;/* Enable parity checking&n;&t;&t;&t;&t;&t;   during master cycles on PCI&n;&t;&t;&t;&t;&t;   bus */
multiline_comment|/*&n; * These bits send the contents of the CTEST6 register to the appropriate&n; * byte lane of the 32 bit DMA FIFO.  Normal operation is zero, otherwise&n; * the high bit means the low two bits select the byte lane.&n; */
DECL|macro|CTEST4_FBL2
mdefine_line|#define CTEST4_FBL2&t;&t;0x04
DECL|macro|CTEST4_FBL1
mdefine_line|#define CTEST4_FBL1&t;&t;0x02
DECL|macro|CTEST4_FBL0
mdefine_line|#define CTEST4_FBL0&t;&t;0x01
DECL|macro|CTEST4_FBL_MASK
mdefine_line|#define CTEST4_FBL_MASK&t;&t;0x07
DECL|macro|CTEST4_FBL_0
mdefine_line|#define CTEST4_FBL_0&t;&t;0x04&t;/* Select DMA FIFO byte lane 0 */
DECL|macro|CTEST4_FBL_1
mdefine_line|#define CTEST4_FBL_1&t;&t;0x05&t;/* Select DMA FIFO byte lane 1 */
DECL|macro|CTEST4_FBL_2
mdefine_line|#define CTEST4_FBL_2&t;&t;0x06&t;/* Select DMA FIFO byte lane 2 */
DECL|macro|CTEST4_FBL_3
mdefine_line|#define CTEST4_FBL_3&t;&t;0x07&t;/* Select DMA FIFO byte lane 3 */
DECL|macro|CTEST4_800_SAVE
mdefine_line|#define CTEST4_800_SAVE&t;&t;(CTEST4_800_BDIS)
DECL|macro|CTEST5_REG_700
mdefine_line|#define CTEST5_REG_700&t;&t;(0x19^bE)&t;/* Chip test 5 rw */
DECL|macro|CTEST5_REG_800
mdefine_line|#define CTEST5_REG_800&t;&t;(0x22^bE)&t;/* Chip test 5 rw */
multiline_comment|/*&n; * Clock Address Incrementor.  When set, it increments the&n; * DNAD register to the next bus size boundary.  It automatically&n; * resets itself when the operation is complete.&n; */
DECL|macro|CTEST5_ADCK
mdefine_line|#define CTEST5_ADCK&t;&t;0x80
multiline_comment|/*&n; * Clock Byte Counter.  When set, it decrements the DBC register to&n; * the next bus size boundary.&n; */
DECL|macro|CTEST5_BBCK
mdefine_line|#define CTEST5_BBCK&t;&t;0x40
multiline_comment|/*&n; * Reset SCSI Offset.  Setting this bit to 1 clears the current offset&n; * pointer in the SCSI synchronous offset counter (SSTAT).  This bit&n; * is set to 1 if a SCSI Gross Error Condition occurs.  The offset should&n; * be cleared when a synchronous transfer fails.  When written, it is&n; * automatically cleared after the SCSI synchronous offset counter is&n; * reset.&n; */
multiline_comment|/* Bit 5 is reserved on 800 series chips */
DECL|macro|CTEST5_700_ROFF
mdefine_line|#define CTEST5_700_ROFF&t;&t;0x20
multiline_comment|/*&n; * Master Control for Set or Reset pulses. When 1, causes the low&n; * four bits of register to set when set, 0 causes the low bits to&n; * clear when set.&n; */
DECL|macro|CTEST5_MASR
mdefine_line|#define CTEST5_MASR &t;&t;0x10
DECL|macro|CTEST5_DDIR
mdefine_line|#define CTEST5_DDIR&t;&t;0x08&t;/* DMA direction */
multiline_comment|/*&n; * Bits 2-0 are reserved on 800 series chips&n; */
DECL|macro|CTEST5_700_EOP
mdefine_line|#define CTEST5_700_EOP&t;&t;0x04&t;/* End of process */
DECL|macro|CTEST5_700_DREQ
mdefine_line|#define CTEST5_700_DREQ&t;&t;0x02&t;/* Data request */
DECL|macro|CTEST5_700_DACK
mdefine_line|#define CTEST5_700_DACK&t;&t;0x01&t;/* Data acknowledge */
multiline_comment|/*&n; * Chip test 6 rw - writing to this register writes to the byte&n; * lane in the DMA FIFO as determined by the FBL bits in the CTEST4&n; * register.&n; */
DECL|macro|CTEST6_REG_700
mdefine_line|#define CTEST6_REG_700&t;&t;(0x1a^bE)
DECL|macro|CTEST6_REG_800
mdefine_line|#define CTEST6_REG_800&t;&t;(0x23^bE)
DECL|macro|CTEST7_REG
mdefine_line|#define CTEST7_REG&t;&t;(0x1b^bE)&t;/* Chip test 7 rw */
DECL|macro|CTEST7_10_CDIS
mdefine_line|#define CTEST7_10_CDIS&t;&t;0x80&t;/* Cache burst disable */
DECL|macro|CTEST7_10_SC1
mdefine_line|#define CTEST7_10_SC1&t;&t;0x40&t;/* Snoop control bits */
DECL|macro|CTEST7_10_SC0
mdefine_line|#define CTEST7_10_SC0&t;&t;0x20
DECL|macro|CTEST7_10_SC_MASK
mdefine_line|#define CTEST7_10_SC_MASK&t;0x60
DECL|macro|CTEST7_STD
mdefine_line|#define CTEST7_STD&t;&t;0x10&t;/* Selection timeout disable */
DECL|macro|CTEST7_DFP
mdefine_line|#define CTEST7_DFP&t;&t;0x08&t;/* DMA FIFO parity bit for CTEST6 */
DECL|macro|CTEST7_EVP
mdefine_line|#define CTEST7_EVP&t;&t;0x04&t;/* 1 = host bus even parity, 0 = odd */
DECL|macro|CTEST7_10_TT1
mdefine_line|#define CTEST7_10_TT1&t;&t;0x02&t;/* Transfer type */
DECL|macro|CTEST7_DIFF
mdefine_line|#define CTEST7_DIFF&t;&t;0x01&t;/* Differential mode */
DECL|macro|CTEST7_SAVE
mdefine_line|#define CTEST7_SAVE ( CTEST7_EVP | CTEST7_DIFF )
DECL|macro|TEMP_REG
mdefine_line|#define TEMP_REG&t;&t;0x1c&t;/* through 0x1f Temporary stack rw */
DECL|macro|DFIFO_REG
mdefine_line|#define DFIFO_REG&t;&t;(0x20^bE)&t;/* DMA FIFO rw */
multiline_comment|/*&n; * 0x80 is reserved on the NCR53c710, the CLF and FLF bits have been&n; * moved into the CTEST8 register.&n; */
DECL|macro|DFIFO_BO6
mdefine_line|#define DFIFO_BO6&t;&t;0x40
DECL|macro|DFIFO_BO5
mdefine_line|#define DFIFO_BO5&t;&t;0x20
DECL|macro|DFIFO_BO4
mdefine_line|#define DFIFO_BO4&t;&t;0x10
DECL|macro|DFIFO_BO3
mdefine_line|#define DFIFO_BO3&t;&t;0x08
DECL|macro|DFIFO_BO2
mdefine_line|#define DFIFO_BO2&t;&t;0x04
DECL|macro|DFIFO_BO1
mdefine_line|#define DFIFO_BO1&t;&t;0x02
DECL|macro|DFIFO_BO0
mdefine_line|#define DFIFO_BO0&t;&t;0x01
DECL|macro|DFIFO_10_BO_MASK
mdefine_line|#define DFIFO_10_BO_MASK&t;0x7f&t;/* 7 bit counter */
multiline_comment|/*&n; * Interrupt status rw&n; * Note that this is the only register which can be read while SCSI&n; * SCRIPTS are being executed.&n; */
DECL|macro|ISTAT_REG_700
mdefine_line|#define ISTAT_REG_700&t;&t;(0x21^bE)
DECL|macro|ISTAT_REG_800
mdefine_line|#define ISTAT_REG_800&t;&t;(0x14^bE)
DECL|macro|ISTAT_ABRT
mdefine_line|#define ISTAT_ABRT&t;&t;0x80&t;/* Software abort, write&n;&t;&t;&t;&t;&t; *1 to abort, wait for interrupt. */
DECL|macro|ISTAT_10_SRST
mdefine_line|#define ISTAT_10_SRST&t;&t;0x40&t;/* software reset */
DECL|macro|ISTAT_10_SIGP
mdefine_line|#define ISTAT_10_SIGP&t;&t;0x20&t;/* signal script */
DECL|macro|ISTAT_CON
mdefine_line|#define ISTAT_CON&t;&t;0x08&t;/* 1 when connected */
DECL|macro|ISTAT_800_INTF
mdefine_line|#define ISTAT_800_INTF&t;&t;0x04&t;/* Interrupt on the fly */
DECL|macro|ISTAT_700_PRE
mdefine_line|#define ISTAT_700_PRE&t;&t;0x04&t;/* Pointer register empty.&n;&t;&t;&t;&t;&t; * Set to 1 when DSPS and DSP&n;&t;&t;&t;&t;&t; * registers are empty in pipeline&n;&t;&t;&t;&t;&t; * mode, always set otherwise.&n;&t;&t;&t;&t;&t; */
DECL|macro|ISTAT_SIP
mdefine_line|#define ISTAT_SIP&t;&t;0x02&t;/* SCSI interrupt pending from&n;&t;&t;&t;&t;&t; * SCSI portion of SIOP see&n;&t;&t;&t;&t;&t; * SSTAT0&n;&t;&t;&t;&t;&t; */
DECL|macro|ISTAT_DIP
mdefine_line|#define ISTAT_DIP&t;&t;0x01&t;/* DMA interrupt pending&n;&t;&t;&t;&t;&t; * see DSTAT&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_REG
mdefine_line|#define CTEST8_REG&t;&t;(0x22^bE)&t;/* Chip test 8 rw */
DECL|macro|CTEST8_10_V3
mdefine_line|#define CTEST8_10_V3&t;&t;0x80&t;/* Chip revision */
DECL|macro|CTEST8_10_V2
mdefine_line|#define CTEST8_10_V2&t;&t;0x40
DECL|macro|CTEST8_10_V1
mdefine_line|#define CTEST8_10_V1&t;&t;0x20
DECL|macro|CTEST8_10_V0
mdefine_line|#define CTEST8_10_V0&t;&t;0x10
DECL|macro|CTEST8_10_V_MASK
mdefine_line|#define CTEST8_10_V_MASK&t;0xf0
DECL|macro|CTEST8_10_FLF
mdefine_line|#define CTEST8_10_FLF&t;&t;0x08&t;/* Flush FIFOs */
DECL|macro|CTEST8_10_CLF
mdefine_line|#define CTEST8_10_CLF&t;&t;0x04&t;/* Clear FIFOs */
DECL|macro|CTEST8_10_FM
mdefine_line|#define CTEST8_10_FM&t;&t;0x02&t;/* Fetch pin mode */
DECL|macro|CTEST8_10_SM
mdefine_line|#define CTEST8_10_SM&t;&t;0x01&t;/* Snoop pin mode */
DECL|macro|LCRC_REG_10
mdefine_line|#define LCRC_REG_10&t;&t;(0x23^bE)
multiline_comment|/*&n; * 0x24 through 0x27 are the DMA byte counter register.  Instructions&n; * write their high 8 bits into the DCMD register, the low 24 bits into&n; * the DBC register.&n; *&n; * Function is dependent on the command type being executed.&n; */
DECL|macro|DBC_REG
mdefine_line|#define DBC_REG&t;&t;&t;0x24
multiline_comment|/*&n; * For Block Move Instructions, DBC is a 24 bit quantity representing&n; *     the number of bytes to transfer.&n; * For Transfer Control Instructions, DBC is bit fielded as follows :&n; */
multiline_comment|/* Bits 20 - 23 should be clear */
DECL|macro|DBC_TCI_TRUE
mdefine_line|#define DBC_TCI_TRUE&t;&t;(1 &lt;&lt; 19) &t;/* Jump when true */
DECL|macro|DBC_TCI_COMPARE_DATA
mdefine_line|#define DBC_TCI_COMPARE_DATA&t;(1 &lt;&lt; 18)&t;/* Compare data */
DECL|macro|DBC_TCI_COMPARE_PHASE
mdefine_line|#define DBC_TCI_COMPARE_PHASE&t;(1 &lt;&lt; 17)&t;/* Compare phase with DCMD field */
DECL|macro|DBC_TCI_WAIT_FOR_VALID
mdefine_line|#define DBC_TCI_WAIT_FOR_VALID&t;(1 &lt;&lt; 16)&t;/* Wait for REQ */
multiline_comment|/* Bits 8 - 15 are reserved on some implementations ? */
DECL|macro|DBC_TCI_MASK_MASK
mdefine_line|#define DBC_TCI_MASK_MASK&t;0xff00 &t;&t;/* Mask for data compare */
DECL|macro|DBC_TCI_MASK_SHIFT
mdefine_line|#define DBC_TCI_MASK_SHIFT&t;8
DECL|macro|DBC_TCI_DATA_MASK
mdefine_line|#define DBC_TCI_DATA_MASK&t;0xff&t;&t;/* Data to be compared */
DECL|macro|DBC_TCI_DATA_SHIFT
mdefine_line|#define DBC_TCI_DATA_SHIFT&t;0
DECL|macro|DBC_RWRI_IMMEDIATE_MASK
mdefine_line|#define DBC_RWRI_IMMEDIATE_MASK&t;0xff00&t;&t;/* Immediate data */
DECL|macro|DBC_RWRI_IMMEDIATE_SHIFT
mdefine_line|#define DBC_RWRI_IMMEDIATE_SHIFT 8&t;&t;/* Amount to shift */
DECL|macro|DBC_RWRI_ADDRESS_MASK
mdefine_line|#define DBC_RWRI_ADDRESS_MASK&t;0x3f0000&t;/* Register address */
DECL|macro|DBC_RWRI_ADDRESS_SHIFT
mdefine_line|#define DBC_RWRI_ADDRESS_SHIFT &t;16
multiline_comment|/*&n; * DMA command r/w&n; */
DECL|macro|DCMD_REG
mdefine_line|#define DCMD_REG&t;&t;(0x27^bE)
DECL|macro|DCMD_TYPE_MASK
mdefine_line|#define DCMD_TYPE_MASK&t;&t;0xc0&t;/* Masks off type */
DECL|macro|DCMD_TYPE_BMI
mdefine_line|#define DCMD_TYPE_BMI&t;&t;0x00&t;/* Indicates a Block Move instruction */
DECL|macro|DCMD_BMI_IO
mdefine_line|#define DCMD_BMI_IO&t;&t;0x01&t;/* I/O, CD, and MSG bits selecting   */
DECL|macro|DCMD_BMI_CD
mdefine_line|#define DCMD_BMI_CD&t;&t;0x02&t;/* the phase for the block MOVE      */
DECL|macro|DCMD_BMI_MSG
mdefine_line|#define DCMD_BMI_MSG&t;&t;0x04&t;/* instruction &t;&t;&t;     */
DECL|macro|DCMD_BMI_OP_MASK
mdefine_line|#define DCMD_BMI_OP_MASK&t;0x18&t;/* mask for opcode */
DECL|macro|DCMD_BMI_OP_MOVE_T
mdefine_line|#define DCMD_BMI_OP_MOVE_T&t;0x00&t;/* MOVE */
DECL|macro|DCMD_BMI_OP_MOVE_I
mdefine_line|#define DCMD_BMI_OP_MOVE_I&t;0x08&t;/* MOVE Initiator */
DECL|macro|DCMD_BMI_INDIRECT
mdefine_line|#define DCMD_BMI_INDIRECT&t;0x20&t;/*  Indirect addressing */
DECL|macro|DCMD_TYPE_TCI
mdefine_line|#define DCMD_TYPE_TCI&t;&t;0x80&t;/* Indicates a Transfer Control&n;&t;&t;&t;&t;&t;   instruction */
DECL|macro|DCMD_TCI_IO
mdefine_line|#define DCMD_TCI_IO&t;&t;0x01&t;/* I/O, CD, and MSG bits selecting   */
DECL|macro|DCMD_TCI_CD
mdefine_line|#define DCMD_TCI_CD&t;&t;0x02&t;/* the phase for the block MOVE      */
DECL|macro|DCMD_TCI_MSG
mdefine_line|#define DCMD_TCI_MSG&t;&t;0x04&t;/* instruction &t;&t;&t;     */
DECL|macro|DCMD_TCI_OP_MASK
mdefine_line|#define DCMD_TCI_OP_MASK&t;0x38&t;/* mask for opcode */
DECL|macro|DCMD_TCI_OP_JUMP
mdefine_line|#define DCMD_TCI_OP_JUMP&t;0x00&t;/* JUMP */
DECL|macro|DCMD_TCI_OP_CALL
mdefine_line|#define DCMD_TCI_OP_CALL&t;0x08&t;/* CALL */
DECL|macro|DCMD_TCI_OP_RETURN
mdefine_line|#define DCMD_TCI_OP_RETURN&t;0x10&t;/* RETURN */
DECL|macro|DCMD_TCI_OP_INT
mdefine_line|#define DCMD_TCI_OP_INT&t;&t;0x18&t;/* INT */
DECL|macro|DCMD_TYPE_RWRI
mdefine_line|#define DCMD_TYPE_RWRI&t;&t;0x40&t;/* Indicates I/O or register Read/Write&n;&t;&t;&t;&t;&t;   instruction */
DECL|macro|DCMD_RWRI_OPC_MASK
mdefine_line|#define DCMD_RWRI_OPC_MASK&t;0x38&t;/* Opcode mask */
DECL|macro|DCMD_RWRI_OPC_WRITE
mdefine_line|#define DCMD_RWRI_OPC_WRITE&t;0x28&t;/* Write SFBR to register */
DECL|macro|DCMD_RWRI_OPC_READ
mdefine_line|#define DCMD_RWRI_OPC_READ&t;0x30&t;/* Read register to SFBR */
DECL|macro|DCMD_RWRI_OPC_MODIFY
mdefine_line|#define DCMD_RWRI_OPC_MODIFY&t;0x38&t;/* Modify in place */
DECL|macro|DCMD_RWRI_OP_MASK
mdefine_line|#define DCMD_RWRI_OP_MASK&t;0x07
DECL|macro|DCMD_RWRI_OP_MOVE
mdefine_line|#define DCMD_RWRI_OP_MOVE&t;0x00
DECL|macro|DCMD_RWRI_OP_SHL
mdefine_line|#define DCMD_RWRI_OP_SHL&t;0x01
DECL|macro|DCMD_RWRI_OP_OR
mdefine_line|#define DCMD_RWRI_OP_OR&t;&t;0x02
DECL|macro|DCMD_RWRI_OP_XOR
mdefine_line|#define DCMD_RWRI_OP_XOR&t;0x03
DECL|macro|DCMD_RWRI_OP_AND
mdefine_line|#define DCMD_RWRI_OP_AND&t;0x04
DECL|macro|DCMD_RWRI_OP_SHR
mdefine_line|#define DCMD_RWRI_OP_SHR&t;0x05
DECL|macro|DCMD_RWRI_OP_ADD
mdefine_line|#define DCMD_RWRI_OP_ADD&t;0x06
DECL|macro|DCMD_RWRI_OP_ADDC
mdefine_line|#define DCMD_RWRI_OP_ADDC&t;0x07
DECL|macro|DCMD_TYPE_MMI
mdefine_line|#define DCMD_TYPE_MMI&t;&t;0xc0&t;/* Indicates a Memory Move instruction&n;&t;&t;&t;&t;&t;   (three words) */
DECL|macro|DNAD_REG
mdefine_line|#define DNAD_REG&t;&t;0x28&t;/* through 0x2b DMA next address for&n;&t;&t;&t;&t;&t;   data */
DECL|macro|DSP_REG
mdefine_line|#define DSP_REG&t;&t;&t;0x2c&t;/* through 0x2f DMA SCRIPTS pointer rw */
DECL|macro|DSPS_REG
mdefine_line|#define DSPS_REG&t;&t;0x30&t;/* through 0x33 DMA SCRIPTS pointer&n;&t;&t;&t;&t;&t;   save rw */
DECL|macro|DMODE_BL1
mdefine_line|#define DMODE_BL1&t;&t;0x80&t;/* Burst length bits */
DECL|macro|DMODE_BL0
mdefine_line|#define DMODE_BL0&t;&t;0x40
DECL|macro|DMODE_BL_MASK
mdefine_line|#define DMODE_BL_MASK&t;&t;0xc0
multiline_comment|/* Burst lengths (800) */
DECL|macro|DMODE_BL_2
mdefine_line|#define DMODE_BL_2&t;0x00&t;/* 2 transfer */
DECL|macro|DMODE_BL_4
mdefine_line|#define DMODE_BL_4&t;0x40&t;/* 4 transfers */
DECL|macro|DMODE_BL_8
mdefine_line|#define DMODE_BL_8&t;0x80&t;/* 8 transfers */
DECL|macro|DMODE_BL_16
mdefine_line|#define DMODE_BL_16&t;0xc0&t;/* 16 transfers */
DECL|macro|DMODE_10_BL_1
mdefine_line|#define DMODE_10_BL_1&t;0x00&t;/* 1 transfer */
DECL|macro|DMODE_10_BL_2
mdefine_line|#define DMODE_10_BL_2&t;0x40&t;/* 2 transfers */
DECL|macro|DMODE_10_BL_4
mdefine_line|#define DMODE_10_BL_4&t;0x80&t;/* 4 transfers */
DECL|macro|DMODE_10_BL_8
mdefine_line|#define DMODE_10_BL_8&t;0xc0&t;/* 8 transfers */
DECL|macro|DMODE_10_FC2
mdefine_line|#define DMODE_10_FC2&t;0x20&t;/* Driven to FC2 pin */
DECL|macro|DMODE_10_FC1
mdefine_line|#define DMODE_10_FC1&t;0x10&t;/* Driven to FC1 pin */
DECL|macro|DMODE_710_PD
mdefine_line|#define DMODE_710_PD&t;0x08&t;/* Program/data on FC0 pin */
DECL|macro|DMODE_710_UO
mdefine_line|#define DMODE_710_UO&t;0x02&t;/* User prog. output */
DECL|macro|DMODE_MAN
mdefine_line|#define DMODE_MAN&t;&t;0x01&t;/* Manual start mode,&n;&t;&t;&t;&t;&t; * requires a 1 to be written&n;&t;&t;&t;&t;&t; * to the start DMA bit in the DCNTL&n;&t;&t;&t;&t;&t; * register to run scripts&n;&t;&t;&t;&t;&t; */
multiline_comment|/* NCR53c800 series only */
DECL|macro|SCRATCHA_REG_800
mdefine_line|#define SCRATCHA_REG_800&t;0x34&t;/* through 0x37 Scratch A rw */
multiline_comment|/* NCR53c710 only */
DECL|macro|SCRATCHB_REG_10
mdefine_line|#define SCRATCHB_REG_10&t;&t;0x34&t;/* through 0x37 scratch rw */
DECL|macro|DMODE_REG
mdefine_line|#define DMODE_REG&t;    &t;(0x38^bE)&t;/* DMA mode rw, NCR53c710 and newer */
DECL|macro|DMODE_800_SIOM
mdefine_line|#define DMODE_800_SIOM&t;&t;0x20&t;/* Source IO = 1 */
DECL|macro|DMODE_800_DIOM
mdefine_line|#define DMODE_800_DIOM&t;&t;0x10&t;/* Destination IO = 1 */
DECL|macro|DMODE_800_ERL
mdefine_line|#define DMODE_800_ERL&t;&t;0x08&t;/* Enable Read Line */
DECL|macro|DIEN_REG
mdefine_line|#define DIEN_REG&t;&t;(0x39^bE)&t;/* DMA interrupt enable rw */
multiline_comment|/* 0x80, 0x40, and 0x20 are reserved on 700-series chips */
DECL|macro|DIEN_800_MDPE
mdefine_line|#define DIEN_800_MDPE&t;&t;0x40&t;/* Master data parity error */
DECL|macro|DIEN_800_BF
mdefine_line|#define DIEN_800_BF&t;&t;0x20&t;/* BUS fault */
DECL|macro|DIEN_700_BF
mdefine_line|#define DIEN_700_BF&t;&t;0x20&t;/* BUS fault */
DECL|macro|DIEN_ABRT
mdefine_line|#define DIEN_ABRT&t;&t;0x10&t;/* Enable aborted interrupt */
DECL|macro|DIEN_SSI
mdefine_line|#define DIEN_SSI&t;&t;0x08&t;/* Enable single step interrupt */
DECL|macro|DIEN_SIR
mdefine_line|#define DIEN_SIR&t;&t;0x04&t;/* Enable SCRIPTS INT command&n;&t;&t;&t;&t;&t; * interrupt&n;&t;&t;&t;&t;&t; */
DECL|macro|DIEN_700_WTD
mdefine_line|#define DIEN_700_WTD&t;&t;0x02&t;/* Enable watchdog timeout interrupt */
DECL|macro|DIEN_700_OPC
mdefine_line|#define DIEN_700_OPC&t;&t;0x01&t;/* Enable illegal instruction&n;&t;&t;&t;&t;&t; * interrupt&n;&t;&t;&t;&t;&t; */
DECL|macro|DIEN_800_IID
mdefine_line|#define DIEN_800_IID&t;&t;0x01&t;/*  Same meaning, different name */
multiline_comment|/*&n; * DMA watchdog timer rw&n; * set in 16 CLK input periods.&n; */
DECL|macro|DWT_REG
mdefine_line|#define DWT_REG&t;&t;&t;(0x3a^bE)
multiline_comment|/* DMA control rw */
DECL|macro|DCNTL_REG
mdefine_line|#define DCNTL_REG&t;&t;(0x3b^bE)
DECL|macro|DCNTL_700_CF1
mdefine_line|#define DCNTL_700_CF1&t;&t;0x80&t;/* Clock divisor bits */
DECL|macro|DCNTL_700_CF0
mdefine_line|#define DCNTL_700_CF0&t;&t;0x40
DECL|macro|DCNTL_700_CF_MASK
mdefine_line|#define DCNTL_700_CF_MASK&t;0xc0
multiline_comment|/* Clock divisors &t;&t;&t;   Divisor SCLK range (MHZ) */
DECL|macro|DCNTL_700_CF_2
mdefine_line|#define DCNTL_700_CF_2&t;&t;0x00    /* 2.0&t;   37.51-50.00 */
DECL|macro|DCNTL_700_CF_1_5
mdefine_line|#define DCNTL_700_CF_1_5&t;0x40&t;/* 1.5&t;   25.01-37.50 */
DECL|macro|DCNTL_700_CF_1
mdefine_line|#define DCNTL_700_CF_1&t;&t;0x80&t;/* 1.0     16.67-25.00 */
DECL|macro|DCNTL_700_CF_3
mdefine_line|#define DCNTL_700_CF_3&t;&t;0xc0&t;/* 3.0&t;   50.01-66.67 (53c700-66) */
DECL|macro|DCNTL_700_S16
mdefine_line|#define DCNTL_700_S16&t;&t;0x20&t;/* Load scripts 16 bits at a time */
DECL|macro|DCNTL_SSM
mdefine_line|#define DCNTL_SSM&t;&t;0x10&t;/* Single step mode */
DECL|macro|DCNTL_700_LLM
mdefine_line|#define DCNTL_700_LLM&t;&t;0x08&t;/* Low level mode, can only be set&n;&t;&t;&t;&t;&t; * after selection */
DECL|macro|DCNTL_800_IRQM
mdefine_line|#define DCNTL_800_IRQM&t;&t;0x08&t;/* Totem pole IRQ pin */
DECL|macro|DCNTL_STD
mdefine_line|#define DCNTL_STD&t;&t;0x04&t;/* Start DMA / SCRIPTS */
multiline_comment|/* 0x02 is reserved */
DECL|macro|DCNTL_10_COM
mdefine_line|#define DCNTL_10_COM&t;&t;0x01&t;/* 700 software compatibility mode */
DECL|macro|DCNTL_10_EA
mdefine_line|#define DCNTL_10_EA&t;&t;0x20&t;/* Enable Ack - needed for MVME16x */
DECL|macro|SCRATCHB_REG_800
mdefine_line|#define SCRATCHB_REG_800&t;0x5c&t;/* through 0x5f scratch b rw */
multiline_comment|/* NCR53c710 only */
DECL|macro|ADDER_REG_10
mdefine_line|#define ADDER_REG_10&t;&t;0x3c&t;/* Adder, NCR53c710 only */
DECL|macro|SIEN1_REG_800
mdefine_line|#define SIEN1_REG_800&t;&t;(0x41^bE)
DECL|macro|SIEN1_800_STO
mdefine_line|#define SIEN1_800_STO&t;&t;0x04&t;/* selection/reselection timeout */
DECL|macro|SIEN1_800_GEN
mdefine_line|#define SIEN1_800_GEN&t;&t;0x02&t;/* general purpose timer */
DECL|macro|SIEN1_800_HTH
mdefine_line|#define SIEN1_800_HTH&t;&t;0x01&t;/* handshake to handshake */
DECL|macro|SIST1_REG_800
mdefine_line|#define SIST1_REG_800&t;&t;(0x43^bE)
DECL|macro|SIST1_800_STO
mdefine_line|#define SIST1_800_STO&t;&t;0x04&t;/* selection/reselection timeout */
DECL|macro|SIST1_800_GEN
mdefine_line|#define SIST1_800_GEN&t;&t;0x02&t;/* general purpose timer */
DECL|macro|SIST1_800_HTH
mdefine_line|#define SIST1_800_HTH&t;&t;0x01&t;/* handshake to handshake */
DECL|macro|SLPAR_REG_800
mdefine_line|#define SLPAR_REG_800&t;&t;(0x44^bE)&t;/* Parity */
DECL|macro|MACNTL_REG_800
mdefine_line|#define MACNTL_REG_800&t;&t;(0x46^bE)&t;/* Memory access control */
DECL|macro|MACNTL_800_TYP3
mdefine_line|#define MACNTL_800_TYP3&t;&t;0x80
DECL|macro|MACNTL_800_TYP2
mdefine_line|#define MACNTL_800_TYP2&t;&t;0x40
DECL|macro|MACNTL_800_TYP1
mdefine_line|#define MACNTL_800_TYP1&t;&t;0x20
DECL|macro|MACNTL_800_TYP0
mdefine_line|#define MACNTL_800_TYP0&t;&t;0x10
DECL|macro|MACNTL_800_DWR
mdefine_line|#define MACNTL_800_DWR&t;&t;0x08
DECL|macro|MACNTL_800_DRD
mdefine_line|#define MACNTL_800_DRD&t;&t;0x04
DECL|macro|MACNTL_800_PSCPT
mdefine_line|#define MACNTL_800_PSCPT&t;0x02
DECL|macro|MACNTL_800_SCPTS
mdefine_line|#define MACNTL_800_SCPTS&t;0x01
DECL|macro|GPCNTL_REG_800
mdefine_line|#define GPCNTL_REG_800&t;&t;(0x47^bE)&t;/* General Purpose Pin Control */
multiline_comment|/* Timeouts are expressed such that 0=off, 1=100us, doubling after that */
DECL|macro|STIME0_REG_800
mdefine_line|#define STIME0_REG_800&t;&t;(0x48^bE)&t;/* SCSI Timer Register 0 */
DECL|macro|STIME0_800_HTH_MASK
mdefine_line|#define STIME0_800_HTH_MASK&t;0xf0&t;/* Handshake to Handshake timeout */
DECL|macro|STIME0_800_HTH_SHIFT
mdefine_line|#define STIME0_800_HTH_SHIFT&t;4
DECL|macro|STIME0_800_SEL_MASK
mdefine_line|#define STIME0_800_SEL_MASK&t;0x0f&t;/* Selection timeout */
DECL|macro|STIME0_800_SEL_SHIFT
mdefine_line|#define STIME0_800_SEL_SHIFT&t;0
DECL|macro|STIME1_REG_800
mdefine_line|#define STIME1_REG_800&t;&t;(0x49^bE)
DECL|macro|STIME1_800_GEN_MASK
mdefine_line|#define STIME1_800_GEN_MASK&t;0x0f&t;/* General purpose timer */
DECL|macro|RESPID_REG_800
mdefine_line|#define RESPID_REG_800&t;&t;(0x4a^bE)&t;/* Response ID, bit fielded.  8&n;&t;&t;&t;&t;&t;   bits on narrow chips, 16 on WIDE */
DECL|macro|STEST0_REG_800
mdefine_line|#define STEST0_REG_800&t;&t;(0x4c^bE)
DECL|macro|STEST0_800_SLT
mdefine_line|#define STEST0_800_SLT&t;&t;0x08&t;/* Selection response logic test */
DECL|macro|STEST0_800_ART
mdefine_line|#define STEST0_800_ART&t;&t;0x04&t;/* Arbitration priority encoder test */
DECL|macro|STEST0_800_SOZ
mdefine_line|#define STEST0_800_SOZ&t;&t;0x02&t;/* Synchronous offset zero */
DECL|macro|STEST0_800_SOM
mdefine_line|#define STEST0_800_SOM&t;&t;0x01&t;/* Synchronous offset maximum */
DECL|macro|STEST1_REG_800
mdefine_line|#define STEST1_REG_800&t;&t;(0x4d^bE)
DECL|macro|STEST1_800_SCLK
mdefine_line|#define STEST1_800_SCLK&t;&t;0x80&t;/* Disable SCSI clock */
DECL|macro|STEST2_REG_800
mdefine_line|#define STEST2_REG_800&t;&t;(0x4e^bE)
DECL|macro|STEST2_800_SCE
mdefine_line|#define STEST2_800_SCE&t;&t;0x80&t;/* Enable SOCL/SODL */
DECL|macro|STEST2_800_ROF
mdefine_line|#define STEST2_800_ROF&t;&t;0x40&t;/* Reset SCSI sync offset */
DECL|macro|STEST2_800_SLB
mdefine_line|#define STEST2_800_SLB&t;&t;0x10&t;/* Enable SCSI loopback mode */
DECL|macro|STEST2_800_SZM
mdefine_line|#define STEST2_800_SZM&t;&t;0x08&t;/* SCSI high impedance mode */
DECL|macro|STEST2_800_EXT
mdefine_line|#define STEST2_800_EXT&t;&t;0x02&t;/* Extend REQ/ACK filter 30 to 60ns */
DECL|macro|STEST2_800_LOW
mdefine_line|#define STEST2_800_LOW&t;&t;0x01&t;/* SCSI low level mode */
DECL|macro|STEST3_REG_800
mdefine_line|#define STEST3_REG_800&t;&t;(0x4f^bE)
DECL|macro|STEST3_800_TE
mdefine_line|#define STEST3_800_TE&t;&t;0x80&t;/* Enable active negation */
DECL|macro|STEST3_800_STR
mdefine_line|#define STEST3_800_STR&t;&t;0x40&t;/* SCSI FIFO test read */
DECL|macro|STEST3_800_HSC
mdefine_line|#define STEST3_800_HSC&t;&t;0x20&t;/* Halt SCSI clock */
DECL|macro|STEST3_800_DSI
mdefine_line|#define STEST3_800_DSI&t;&t;0x10&t;/* Disable single initiator response */
DECL|macro|STEST3_800_TTM
mdefine_line|#define STEST3_800_TTM&t;&t;0x04&t;/* Time test mode */
DECL|macro|STEST3_800_CSF
mdefine_line|#define STEST3_800_CSF&t;&t;0x02&t;/* Clear SCSI FIFO */
DECL|macro|STEST3_800_STW
mdefine_line|#define STEST3_800_STW&t;&t;0x01&t;/* SCSI FIFO test write */
DECL|macro|ISTAT_REG
mdefine_line|#define ISTAT_REG&t;ISTAT_REG_700
DECL|macro|SCRATCH_REG
mdefine_line|#define SCRATCH_REG&t;SCRATCHB_REG_10
macro_line|#ifdef MEM_MAPPED
DECL|macro|NCR_read8
mdefine_line|#define NCR_read8(address) &t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int)readb((u32)(host-&gt;base) + ((u32)(address)))
DECL|macro|NCR_read32
mdefine_line|#define NCR_read32(address) &t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int) readl((u32)(host-&gt;base) + (u32)(address))
DECL|macro|NCR_write8
mdefine_line|#define NCR_write8(address,value) &t;&t;&t;&t;&bslash;&n;&t;{ DEB(DEB_REGS, printk(&quot;NCR: %02x =&gt; %08x&bslash;n&quot;, (u32)(value), ((u32)(host-&gt;base) + (u32)(address)))); &bslash;&n;&t;*(volatile unsigned char *)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;((u32)(host-&gt;base) + (u32)(address)) = (value); }
DECL|macro|NCR_write32
mdefine_line|#define NCR_write32(address,value) &t;&t;&t;&t;&bslash;&n;&t;{ DEB(DEB_REGS, printk(&quot;NCR: %08x =&gt; %08x&bslash;n&quot;, (u32)(value), ((u32)(host-&gt;base) + (u32)(address)))); &bslash;&n;&t;*(volatile unsigned long *)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;((u32)(host-&gt;base) + (u32)(address)) = (value); }
macro_line|#else
DECL|macro|NCR_read8
mdefine_line|#define NCR_read8(address) &t;&t;&t;&t;&t;&bslash;&n;&t;inb((u32)(host-&gt;base) + (address))
DECL|macro|NCR_read32
mdefine_line|#define NCR_read32(address) &t;&t;&t;&t;&t;&bslash;&n;&t;inl((u32)(host-&gt;base) + (address))
DECL|macro|NCR_write8
mdefine_line|#define NCR_write8(address,value) &t;&t;&t;&t;&bslash;&n;&t;{ DEB(DEB_REGS, printk(&quot;NCR: %02x =&gt; %08x&bslash;n&quot;, (u32)(value), ((u32)(host-&gt;base) + (u32)(address)))); &bslash;&n;&t;outb((value), (u32)(host-&gt;base) + (u32)(address)); }
DECL|macro|NCR_write32
mdefine_line|#define NCR_write32(address,value) &t;&t;&t;&t;&bslash;&n;&t;{ DEB(DEB_REGS, printk(&quot;NCR: %08x =&gt; %08x&bslash;n&quot;, (u32)(value), ((u32)(host-&gt;base) + (u32)(address)))); &bslash;&n;&t;outl((value), (u32)(host-&gt;base) + (u32)(address)); }
macro_line|#endif
multiline_comment|/* Patch arbitrary 32 bit words in the script */
DECL|macro|patch_abs_32
mdefine_line|#define patch_abs_32(script, offset, symbol, value)&t;&t;&t;&bslash;&n;    &t;for (i = 0; i &lt; (sizeof (A_##symbol##_used) / sizeof &t;&t;&bslash;&n;    &t;    (u32)); ++i) {&t;&t;&t;&t;&t;&bslash;&n;&t;    (script)[A_##symbol##_used[i] - (offset)] += (value);&t;&bslash;&n;&t;      DEB(DEB_FIXUP, printk(&quot;scsi%d: %s reference %d at 0x%x in %s is now 0x%x&bslash;n&quot;,&bslash;&n;&t;&t;host-&gt;host_no, #symbol, i, A_##symbol##_used[i] - &t;&bslash;&n;&t;&t;(int)(offset), #script, (script)[A_##symbol##_used[i] -&t;&bslash;&n;&t;&t;(offset)]));&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;}
macro_line|#endif
macro_line|#endif
eof
