multiline_comment|/*&n; * 53c710 driver.  Modified from Drew Eckhardts driver&n; * for 53c810 by Richard Hirst [richard@sleepie.demon.co.uk]&n; *&n; * I have left the code for the 53c8xx family in here, because it didn&squot;t&n; * seem worth removing it.  The possibility of IO_MAPPED chips rather&n; * than MEMORY_MAPPED remains, in case someone wants to add support for&n; * 53c710 chips on Intel PCs (some older machines have them on the&n; * motherboard).&n; *&n; * NOTE THERE MAY BE PROBLEMS WITH CASTS IN read8 AND Co.&n; */
multiline_comment|/*&n; * NCR 53c{7,8}0x0 driver, header file&n; *&n; * Sponsored by&n; *      iX Multiuser Multitasking Magazine&n; *&t;Hannover, Germany&n; *&t;hm@ix.de&t;&n; *&n; * Copyright 1993, 1994, 1995 Drew Eckhardt&n; *      Visionary Computing &n; *      (Unix and Linux consulting and custom programming)&n; *      drew@PoohSticks.ORG&n; *&t;+1 (303) 786-7975&n; *&n; * TolerANT and SCSI SCRIPTS are registered trademarks of NCR Corporation.&n; * &n; * PRE-ALPHA&n; *&n; * For more information, please consult &n; *&n; * NCR 53C700/53C700-66&n; * SCSI I/O Processor&n; * Data Manual&n; *&n; * NCR 53C810&n; * PCI-SCSI I/O Processor &n; * Data Manual&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * +1 (719) 578-3400&n; *&n; * Toll free literature number&n; * +1 (800) 334-5454&n; *&n; */
macro_line|#ifndef NCR53c710_H
DECL|macro|NCR53c710_H
mdefine_line|#define NCR53c710_H
macro_line|#ifndef HOSTS_C
multiline_comment|/* SCSI control 0 rw, default = 0xc0 */
DECL|macro|SCNTL0_REG
mdefine_line|#define SCNTL0_REG &t;&t;0x00&t;
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
mdefine_line|#define SCNTL1_REG &t;&t;0x01&t;
DECL|macro|SCNTL1_EXC
mdefine_line|#define SCNTL1_EXC&t;&t;0x80&t;/* Extra Clock Cycle of Data setup */
DECL|macro|SCNTL1_ADB
mdefine_line|#define SCNTL1_ADB&t;&t;0x40&t;/*  contents of SODL on bus */
DECL|macro|SCNTL1_ESR_700
mdefine_line|#define SCNTL1_ESR_700&t;&t;0x20&t;/* Enable SIOP response to selection &n;&t;&t;&t;&t;&t;   and reselection */
DECL|macro|SCNTL1_DHP_800
mdefine_line|#define SCNTL1_DHP_800&t;&t;0x20&t;/* Disable halt on parity error or ATN&n;&t;&t;&t;&t;&t;   target mode only */
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
mdefine_line|#define SCNTL2_REG_800&t;&t;0x02&t;
DECL|macro|SCNTL2_800_SDU
mdefine_line|#define SCNTL2_800_SDU&t;&t;0x80&t;/* SCSI disconnect unexpected */
multiline_comment|/* SCSI control 3 rw */
DECL|macro|SCNTL3_REG_800
mdefine_line|#define SCNTL3_REG_800 &t;&t;0x03&t;
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
multiline_comment|/* 0x20 = SCLK/1.5 &n;&t;&t;&t;&t;&t;   0x30 = SCLK/2 &n;&t;&t;&t;&t;&t;   0x40 = SCLK/3 */
DECL|macro|SCNTL3_800_CCF_SHIFT
mdefine_line|#define SCNTL3_800_CCF_SHIFT&t;0
DECL|macro|SCNTL3_800_CCF_MASK
mdefine_line|#define SCNTL3_800_CCF_MASK&t;0x07
DECL|macro|SCNTL3_800_CCF2
mdefine_line|#define SCNTL3_800_CCF2&t;&t;0x04&t;/* 0x00 50.01 to 66 */
DECL|macro|SCNTL3_800_CCF1
mdefine_line|#define SCNTL3_800_CCF1&t;&t;0x02&t;/* 0x01 16.67 to 25 */
DECL|macro|SCNTL3_800_CCF0
mdefine_line|#define SCNTL3_800_CCF0&t;&t;0x01&t;/* 0x02&t;25.01 - 37.5 &n;&t;&t;&t;&t;&t;   0x03&t;37.51 - 50 &n;&t;&t;&t;&t;&t;   0x04 50.01 - 66 */
multiline_comment|/*  &n; * SCSI destination ID rw - the appropriate bit is set for the selected&n; * target ID.  This is written by the SCSI SCRIPTS processor.&n; * default = 0x00&n; */
DECL|macro|SDID_REG_700
mdefine_line|#define SDID_REG_700  &t;&t;0x02&t;
DECL|macro|SDID_REG_800
mdefine_line|#define SDID_REG_800&t;&t;0x06
DECL|macro|GP_REG_800
mdefine_line|#define GP_REG_800&t;&t;0x07&t;/* General purpose IO */
DECL|macro|GP_800_IO1
mdefine_line|#define GP_800_IO1&t;&t;0x02
DECL|macro|GP_800_IO2
mdefine_line|#define GP_800_IO2&t;&t;0x01
multiline_comment|/* SCSI interrupt enable rw, default = 0x00 */
DECL|macro|SIEN_REG_700
mdefine_line|#define SIEN_REG_700&t;&t;0x03&t;
DECL|macro|SIEN0_REG_800
mdefine_line|#define SIEN0_REG_800&t;&t;0x40
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
multiline_comment|/* &n; * SCSI chip ID rw&n; * NCR53c700 : &n; * &t;When arbitrating, the highest bit is used, when reselection or selection&n; * &t;occurs, the chip responds to all IDs for which a bit is set.&n; * &t;default = 0x00 &n; * NCR53c810 : &n; *&t;Uses bit mapping&n; */
DECL|macro|SCID_REG
mdefine_line|#define SCID_REG&t;&t;0x04&t;
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
mdefine_line|#define SXFER_REG&t;&t;0x05
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
multiline_comment|/* &n; * SCSI output data latch rw&n; * The contents of this register are driven onto the SCSI bus when &n; * the Assert Data Bus bit of the SCNTL1 register is set and &n; * the CD, IO, and MSG bits of the SOCL register match the SCSI phase&n; */
DECL|macro|SODL_REG_700
mdefine_line|#define SODL_REG_700&t;&t;0x06&t;
DECL|macro|SODL_REG_800
mdefine_line|#define SODL_REG_800&t;&t;0x54
multiline_comment|/* &n; * SCSI output control latch rw, default = 0 &n; * Note that when the chip is being manually programmed as an initiator,&n; * the MSG, CD, and IO bits must be set correctly for the phase the target&n; * is driving the bus in.  Otherwise no data transfer will occur due to &n; * phase mismatch.&n; */
DECL|macro|SOCL_REG
mdefine_line|#define SOCL_REG&t;&t;0x07
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
multiline_comment|/* &n; * SCSI first byte received latch ro &n; * This register contains the first byte received during a block MOVE &n; * SCSI SCRIPTS instruction, including&n; * &n; * Initiator mode&t;Target mode&n; * Message in&t;&t;Command&n; * Status&t;&t;Message out&n; * Data in&t;&t;Data out&n; *&n; * It also contains the selecting or reselecting device&squot;s ID and our &n; * ID.&n; *&n; * Note that this is the register the various IF conditionals can &n; * operate on.&n; */
DECL|macro|SFBR_REG
mdefine_line|#define SFBR_REG&t;&t;0x08&t;
multiline_comment|/* &n; * SCSI input data latch ro&n; * In initiator mode, data is latched into this register on the rising&n; * edge of REQ/. In target mode, data is latched on the rising edge of &n; * ACK/&n; */
DECL|macro|SIDL_REG_700
mdefine_line|#define SIDL_REG_700&t;&t;0x09
DECL|macro|SIDL_REG_800
mdefine_line|#define SIDL_REG_800&t;&t;0x50
multiline_comment|/* &n; * SCSI bus data lines ro &n; * This register reflects the instantaneous status of the SCSI data &n; * lines.  Note that SCNTL0 must be set to disable parity checking, &n; * otherwise reading this register will latch new parity.&n; */
DECL|macro|SBDL_REG_700
mdefine_line|#define SBDL_REG_700&t;&t;0x0a
DECL|macro|SBDL_REG_800
mdefine_line|#define SBDL_REG_800&t;&t;0x58
DECL|macro|SSID_REG_800
mdefine_line|#define SSID_REG_800&t;&t;0x0a
DECL|macro|SSID_800_VAL
mdefine_line|#define SSID_800_VAL&t;&t;0x80&t;/* Exactly two bits asserted at sel */
DECL|macro|SSID_800_ENCID_MASK
mdefine_line|#define SSID_800_ENCID_MASK&t;0x07&t;/* Device which performed operation */
multiline_comment|/* &n; * SCSI bus control lines rw, &n; * instantaneous readout of control lines &n; */
DECL|macro|SBCL_REG
mdefine_line|#define SBCL_REG&t;&t;0x0b &t;
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
multiline_comment|/* &n; * Synchronous SCSI Clock Control bits &n; * 0 - set by DCNTL &n; * 1 - SCLK / 1.0&n; * 2 - SCLK / 1.5&n; * 3 - SCLK / 2.0 &n; */
DECL|macro|SBCL_SSCF1
mdefine_line|#define SBCL_SSCF1&t;&t;0x02&t;/* wo, -66 only */
DECL|macro|SBCL_SSCF0
mdefine_line|#define SBCL_SSCF0&t;&t;0x01&t;/* wo, -66 only */
DECL|macro|SBCL_SSCF_MASK
mdefine_line|#define SBCL_SSCF_MASK&t;&t;0x03
multiline_comment|/* &n; * XXX note : when reading the DSTAT and STAT registers to clear interrupts,&n; * insure that 10 clocks elapse between the two  &n; */
multiline_comment|/* DMA status ro */
DECL|macro|DSTAT_REG
mdefine_line|#define DSTAT_REG&t;&t;0x0c&t;
DECL|macro|DSTAT_DFE
mdefine_line|#define DSTAT_DFE&t;&t;0x80&t;/* DMA FIFO empty */
DECL|macro|DSTAT_800_MDPE
mdefine_line|#define DSTAT_800_MDPE&t;&t;0x40&t;/* Master Data Parity Error */
DECL|macro|DSTAT_800_BF
mdefine_line|#define DSTAT_800_BF&t;&t;0x20&t;/* Bus Fault */
DECL|macro|DSTAT_ABRT
mdefine_line|#define DSTAT_ABRT&t;&t;0x10&t;/* Aborted - set on error */
DECL|macro|DSTAT_SSI
mdefine_line|#define DSTAT_SSI&t;&t;0x08&t;/* SCRIPTS single step interrupt */
DECL|macro|DSTAT_SIR
mdefine_line|#define DSTAT_SIR&t;&t;0x04&t;/* SCRIPTS interrupt received - &n;&t;&t;&t;&t;&t;   set when INT instruction is &n;&t;&t;&t;&t;&t;   executed */
DECL|macro|DSTAT_WTD
mdefine_line|#define DSTAT_WTD&t;&t;0x02&t;/* Watchdog timeout detected */
DECL|macro|DSTAT_OPC
mdefine_line|#define DSTAT_OPC&t;&t;0x01&t;/* Illegal instruction */
DECL|macro|DSTAT_800_IID
mdefine_line|#define DSTAT_800_IID&t;&t;0x01&t;/* Same thing, different name */
multiline_comment|/* NCR53c800 moves this stuff into SIST0 */
DECL|macro|SSTAT0_REG
mdefine_line|#define SSTAT0_REG&t;&t;0x0d&t;/* SCSI status 0 ro */
DECL|macro|SIST0_REG_800
mdefine_line|#define SIST0_REG_800&t;&t;0x42&t;
DECL|macro|SSTAT0_MA
mdefine_line|#define SSTAT0_MA&t;&t;0x80&t;/* ini : phase mismatch,&n;&t;&t;&t;&t;&t; * tgt : ATN/ asserted &n;&t;&t;&t;&t;&t; */
DECL|macro|SSTAT0_CMP
mdefine_line|#define SSTAT0_CMP&t;&t;0x40&t;/* function complete */
DECL|macro|SSTAT0_700_STO
mdefine_line|#define SSTAT0_700_STO&t;&t;0x20&t;/* Selection or reselection timeout */
DECL|macro|SIST0_800_SEL
mdefine_line|#define SIST0_800_SEL&t;&t;0x20&t;/* Selected */
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
multiline_comment|/* And uses SSTAT0 for what was SSTAT1 */
DECL|macro|SSTAT1_REG
mdefine_line|#define SSTAT1_REG&t;&t;0x0e&t;/* SCSI status 1 ro */
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
mdefine_line|#define SSTAT2_REG&t;&t;0x0f&t;/* SCSI status 2 ro */
DECL|macro|SSTAT2_FF3
mdefine_line|#define SSTAT2_FF3&t;&t;0x80 &t;/* number of bytes in synchronous */
DECL|macro|SSTAT2_FF2
mdefine_line|#define SSTAT2_FF2&t;&t;0x40&t;/* data FIFO */
DECL|macro|SSTAT2_FF1
mdefine_line|#define SSTAT2_FF1&t;&t;0x20&t;
DECL|macro|SSTAT2_FF0
mdefine_line|#define SSTAT2_FF0&t;&t;0x10
DECL|macro|SSTAT2_FF_MASK
mdefine_line|#define SSTAT2_FF_MASK&t;&t;0xf0
DECL|macro|SSTAT2_FF_SHIFT
mdefine_line|#define SSTAT2_FF_SHIFT&t;&t;4
multiline_comment|/* &n; * Latched signals, latched on the leading edge of REQ/ for initiators,&n; * ACK/ for targets.&n; */
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
multiline_comment|/* NCR53c700-66 only */
DECL|macro|SCRATCHA_REG_00
mdefine_line|#define SCRATCHA_REG_00&t;&t;0x10    /* through  0x13 Scratch A rw */
multiline_comment|/* NCR53c710 and higher */
DECL|macro|DSA_REG
mdefine_line|#define DSA_REG&t;&t;&t;0x10&t;/* DATA structure address */
DECL|macro|CTEST0_REG_700
mdefine_line|#define CTEST0_REG_700&t;&t;0x14&t;/* Chip test 0 ro */
DECL|macro|CTEST0_REG_800
mdefine_line|#define CTEST0_REG_800&t;&t;0x18&t;/* Chip test 0 rw, general purpose */
multiline_comment|/* 0x80 - 0x04 are reserved */
DECL|macro|CTEST0_700_RTRG
mdefine_line|#define CTEST0_700_RTRG&t;&t;0x02&t;/* Real target mode */
DECL|macro|CTEST0_700_DDIR
mdefine_line|#define CTEST0_700_DDIR&t;&t;0x01&t;/* Data direction, 1 = &n;&t;&t;&t;&t;&t; * SCSI bus to host, 0  =&n;&t;&t;&t;&t;&t; * host to SCSI.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST1_REG_700
mdefine_line|#define CTEST1_REG_700&t;&t;0x15&t;/* Chip test 1 ro */
DECL|macro|CTEST1_REG_800
mdefine_line|#define CTEST1_REG_800&t;&t;0x19&t;/* Chip test 1 ro */
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
mdefine_line|#define CTEST2_REG_700&t;&t;0x16&t;/* Chip test 2 ro */
DECL|macro|CTEST2_REG_800
mdefine_line|#define CTEST2_REG_800&t;&t;0x1a&t;/* Chip test 2 ro */
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
mdefine_line|#define CTEST2_700_SOFF&t;&t;0x20&t;/* SCSI Offset Compare,&n;&t;&t;&t;&t;&t; * As an initiator, this bit is &n;&t;&t;&t;&t;&t; * one when the synchronous offset&n;&t;&t;&t;&t;&t; * is zero, as a target this bit &n;&t;&t;&t;&t;&t; * is one when the synchronous &n;&t;&t;&t;&t;&t; * offset is at the maximum&n;&t;&t;&t;&t;&t; * defined in SXFER&n;&t;&t;&t;&t;&t; */
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
mdefine_line|#define CTEST2_800_DACK&t;&t;0x01&t;
multiline_comment|/* &n; * Chip test 3 ro &n; * Unloads the bottom byte of the eight deep SCSI synchronous FIFO,&n; * check SSTAT2 FIFO full bits to determine size.  Note that a GROSS&n; * error results if a read is attempted on this register.  Also note &n; * that 16 and 32 bit reads of this register will cause corruption.&n; */
DECL|macro|CTEST3_REG_700
mdefine_line|#define CTEST3_REG_700&t;&t;0x17&t;
multiline_comment|/*  Chip test 3 rw */
DECL|macro|CTEST3_REG_800
mdefine_line|#define CTEST3_REG_800&t;&t;0x1b
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
DECL|macro|CTEST4_REG_700
mdefine_line|#define CTEST4_REG_700&t;&t;0x18&t;/* Chip test 4 rw */
DECL|macro|CTEST4_REG_800
mdefine_line|#define CTEST4_REG_800&t;&t;0x21&t;/* Chip test 4 rw */
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
mdefine_line|#define CTEST4_700_SFWR&t;&t;0x08&t;/* SCSI FIFO write enable, &n;&t;&t;&t;&t;&t; * redirects writes from SODL&n;&t;&t;&t;&t;&t; * to the SCSI FIFO.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST4_800_MPEE
mdefine_line|#define CTEST4_800_MPEE&t;&t;0x08&t;/* Enable parity checking&n;&t;&t;&t;&t;&t;   during master cycles on PCI&n;&t;&t;&t;&t;&t;   bus */
multiline_comment|/* &n; * These bits send the contents of the CTEST6 register to the appropriate&n; * byte lane of the 32 bit DMA FIFO.  Normal operation is zero, otherwise &n; * the high bit means the low two bits select the byte lane.&n; */
DECL|macro|CTEST4_FBL2
mdefine_line|#define CTEST4_FBL2&t;&t;0x04&t;
DECL|macro|CTEST4_FBL1
mdefine_line|#define CTEST4_FBL1&t;&t;0x02
DECL|macro|CTEST4_FBL0
mdefine_line|#define CTEST4_FBL0&t;&t;0x01&t;
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
mdefine_line|#define CTEST5_REG_700&t;&t;0x19&t;/* Chip test 5 rw */
DECL|macro|CTEST5_REG_800
mdefine_line|#define CTEST5_REG_800&t;&t;0x22&t;/* Chip test 5 rw */
multiline_comment|/* &n; * Clock Address Incrementor.  When set, it increments the &n; * DNAD register to the next bus size boundary.  It automatically &n; * resets itself when the operation is complete.&n; */
DECL|macro|CTEST5_ADCK
mdefine_line|#define CTEST5_ADCK&t;&t;0x80
multiline_comment|/*&n; * Clock Byte Counter.  When set, it decrements the DBC register to&n; * the next bus size boundary.&n; */
DECL|macro|CTEST5_BBCK
mdefine_line|#define CTEST5_BBCK&t;&t;0x40
multiline_comment|/*&n; * Reset SCSI Offset.  Setting this bit to 1 clears the current offset&n; * pointer in the SCSI synchronous offset counter (SSTAT).  This bit&n; * is set to 1 if a SCSI Gross Error Condition occurs.  The offset should&n; * be cleared when a synchronous transfer fails.  When written, it is &n; * automatically cleared after the SCSI synchronous offset counter is &n; * reset.&n; */
multiline_comment|/* Bit 5 is reserved on 800 series chips */
DECL|macro|CTEST5_700_ROFF
mdefine_line|#define CTEST5_700_ROFF&t;&t;0x20
multiline_comment|/* &n; * Master Control for Set or Reset pulses. When 1, causes the low &n; * four bits of register to set when set, 0 causes the low bits to&n; * clear when set.&n; */
DECL|macro|CTEST5_MASR
mdefine_line|#define CTEST5_MASR &t;&t;0x10&t;
DECL|macro|CTEST5_DDIR
mdefine_line|#define CTEST5_DDIR&t;&t;0x08&t;/* DMA direction */
multiline_comment|/*&n; * Bits 2-0 are reserved on 800 series chips&n; */
DECL|macro|CTEST5_700_EOP
mdefine_line|#define CTEST5_700_EOP&t;&t;0x04&t;/* End of process */
DECL|macro|CTEST5_700_DREQ
mdefine_line|#define CTEST5_700_DREQ&t;&t;0x02&t;/* Data request */
DECL|macro|CTEST5_700_DACK
mdefine_line|#define CTEST5_700_DACK&t;&t;0x01&t;/* Data acknowledge */
multiline_comment|/* &n; * Chip test 6 rw - writing to this register writes to the byte &n; * lane in the DMA FIFO as determined by the FBL bits in the CTEST4&n; * register.&n; */
DECL|macro|CTEST6_REG_700
mdefine_line|#define CTEST6_REG_700&t;&t;0x1a
DECL|macro|CTEST6_REG_800
mdefine_line|#define CTEST6_REG_800&t;&t;0x23
DECL|macro|CTEST7_REG
mdefine_line|#define CTEST7_REG&t;&t;0x1b&t;/* Chip test 7 rw */
multiline_comment|/* 0x80 - 0x40 are reserved on NCR53c700 and NCR53c700-66 chips */
DECL|macro|CTEST7_10_CDIS
mdefine_line|#define CTEST7_10_CDIS&t;&t;0x80&t;/* Cache burst disable */
DECL|macro|CTEST7_10_SC1
mdefine_line|#define CTEST7_10_SC1&t;&t;0x40&t;/* Snoop control bits */
DECL|macro|CTEST7_10_SC0
mdefine_line|#define CTEST7_10_SC0&t;&t;0x20&t;
DECL|macro|CTEST7_10_SC_MASK
mdefine_line|#define CTEST7_10_SC_MASK&t;0x60
multiline_comment|/* 0x20 is reserved on the NCR53c700 */
DECL|macro|CTEST7_0060_FM
mdefine_line|#define CTEST7_0060_FM&t;&t;0x20&t;/* Fetch mode */
DECL|macro|CTEST7_STD
mdefine_line|#define CTEST7_STD&t;&t;0x10&t;/* Selection timeout disable */
DECL|macro|CTEST7_DFP
mdefine_line|#define CTEST7_DFP&t;&t;0x08&t;/* DMA FIFO parity bit for CTEST6 */
DECL|macro|CTEST7_EVP
mdefine_line|#define CTEST7_EVP&t;&t;0x04&t;/* 1 = host bus even parity, 0 = odd */
DECL|macro|CTEST7_10_TT1
mdefine_line|#define CTEST7_10_TT1&t;&t;0x02&t;/* Transfer type */
DECL|macro|CTEST7_00_DC
mdefine_line|#define CTEST7_00_DC&t;&t;0x02&t;/* Set to drive DC low during instruction &n;&t;&t;&t;&t;&t;   fetch */
DECL|macro|CTEST7_DIFF
mdefine_line|#define CTEST7_DIFF&t;&t;0x01&t;/* Differential mode */
DECL|macro|CTEST7_SAVE
mdefine_line|#define CTEST7_SAVE ( CTEST7_EVP | CTEST7_DIFF )
DECL|macro|TEMP_REG
mdefine_line|#define TEMP_REG&t;&t;0x1c&t;/* through 0x1f Temporary stack rw */
DECL|macro|DFIFO_REG
mdefine_line|#define DFIFO_REG&t;&t;0x20&t;/* DMA FIFO rw */
multiline_comment|/* &n; * 0x80 is reserved on the NCR53c710, the CLF and FLF bits have been&n; * moved into the CTEST8 register.&n; */
DECL|macro|DFIFO_00_FLF
mdefine_line|#define DFIFO_00_FLF&t;&t;0x80&t;/* Flush DMA FIFO to memory */
DECL|macro|DFIFO_00_CLF
mdefine_line|#define DFIFO_00_CLF&t;&t;0x40&t;/* Clear DMA and SCSI FIFOs */
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
DECL|macro|DFIFO_00_BO_MASK
mdefine_line|#define DFIFO_00_BO_MASK&t;0x3f&t;/* 6 bit counter */
multiline_comment|/* &n; * Interrupt status rw &n; * Note that this is the only register which can be read while SCSI&n; * SCRIPTS are being executed.&n; */
DECL|macro|ISTAT_REG_700
mdefine_line|#define ISTAT_REG_700&t;&t;0x21
DECL|macro|ISTAT_REG_800
mdefine_line|#define ISTAT_REG_800&t;&t;0x14
DECL|macro|ISTAT_ABRT
mdefine_line|#define ISTAT_ABRT&t;&t;0x80&t;/* Software abort, write &n;&t;&t;&t;&t;&t; *1 to abort, wait for interrupt. */
multiline_comment|/* 0x40 and 0x20 are reserved on NCR53c700 and NCR53c700-66 chips */
DECL|macro|ISTAT_10_SRST
mdefine_line|#define ISTAT_10_SRST&t;&t;0x40&t;/* software reset */
DECL|macro|ISTAT_10_SIGP
mdefine_line|#define ISTAT_10_SIGP&t;&t;0x20&t;/* signal script */
multiline_comment|/* 0x10 is reserved on NCR53c700 series chips */
DECL|macro|ISTAT_800_SEM
mdefine_line|#define ISTAT_800_SEM&t;&t;0x10&t;/* semaphore */
DECL|macro|ISTAT_CON
mdefine_line|#define ISTAT_CON&t;&t;0x08&t;/* 1 when connected */
DECL|macro|ISTAT_800_INTF
mdefine_line|#define ISTAT_800_INTF&t;&t;0x04&t;/* Interrupt on the fly */
DECL|macro|ISTAT_700_PRE
mdefine_line|#define ISTAT_700_PRE&t;&t;0x04&t;/* Pointer register empty.&n;&t;&t;&t;&t;&t; * Set to 1 when DSPS and DSP&n;&t;&t;&t;&t;&t; * registers are empty in pipeline&n;&t;&t;&t;&t;&t; * mode, always set otherwise.&n;&t;&t;&t;&t;&t; */
DECL|macro|ISTAT_SIP
mdefine_line|#define ISTAT_SIP&t;&t;0x02&t;/* SCSI interrupt pending from&n;&t;&t;&t;&t;&t; * SCSI portion of SIOP see&n;&t;&t;&t;&t;&t; * SSTAT0&n;&t;&t;&t;&t;&t; */
DECL|macro|ISTAT_DIP
mdefine_line|#define ISTAT_DIP&t;&t;0x01&t;/* DMA interrupt pending &n;&t;&t;&t;&t;&t; * see DSTAT&n;&t;&t;&t;&t;&t; */
multiline_comment|/* NCR53c700-66 and NCR53c710 only */
DECL|macro|CTEST8_REG
mdefine_line|#define CTEST8_REG&t;&t;0x22&t;/* Chip test 8 rw */
DECL|macro|CTEST8_0066_EAS
mdefine_line|#define CTEST8_0066_EAS&t;&t;0x80&t;/* Enable alternate SCSI clock,&n;&t;&t;&t;&t;&t; * ie read from SCLK/ rather than CLK/&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_0066_EFM
mdefine_line|#define CTEST8_0066_EFM&t;&t;0x40&t;/* Enable fetch and master outputs */
DECL|macro|CTEST8_0066_GRP
mdefine_line|#define CTEST8_0066_GRP&t;&t;0x20&t;/* Generate Receive Parity for &n;&t;&t;&t;&t;&t; * pass through.  This insures that &n;&t;&t;&t;&t;&t; * bad parity won&squot;t reach the host &n;&t;&t;&t;&t;&t; * bus.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_0066_TE
mdefine_line|#define CTEST8_0066_TE&t;&t;0x10&t;/* TolerANT enable.  Enable &n;&t;&t;&t;&t;&t; * active negation, should only&n;&t;&t;&t;&t;&t; * be used for slow SCSI &n;&t;&t;&t;&t;&t; * non-differential.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_0066_HSC
mdefine_line|#define CTEST8_0066_HSC&t;&t;0x08&t;/* Halt SCSI clock */
DECL|macro|CTEST8_0066_SRA
mdefine_line|#define CTEST8_0066_SRA&t;&t;0x04&t;/* Shorten REQ/ACK filtering,&n;&t;&t;&t;&t;&t; * must be set for fast SCSI-II&n;&t;&t;&t;&t;&t; * speeds.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_0066_DAS
mdefine_line|#define CTEST8_0066_DAS&t;&t;0x02&t;/* Disable automatic target/initiator&n;&t;&t;&t;&t;&t; * switching.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_0066_LDE
mdefine_line|#define CTEST8_0066_LDE&t;&t;0x01&t;/* Last disconnect enable.&n;&t;&t;&t;&t;&t; * The status of pending &n;&t;&t;&t;&t;&t; * disconnect is maintained by&n;&t;&t;&t;&t;&t; * the core, eliminating&n;&t;&t;&t;&t;&t; * the possibility of missing a &n;&t;&t;&t;&t;&t; * selection or reselection&n;&t;&t;&t;&t;&t; * while waiting to fetch a &n;&t;&t;&t;&t;&t; * WAIT DISCONNECT opcode.&n;&t;&t;&t;&t;&t; */
DECL|macro|CTEST8_10_V3
mdefine_line|#define CTEST8_10_V3&t;&t;0x80&t;/* Chip revision */
DECL|macro|CTEST8_10_V2
mdefine_line|#define CTEST8_10_V2&t;&t;0x40
DECL|macro|CTEST8_10_V1
mdefine_line|#define CTEST8_10_V1&t;&t;0x20&t;
DECL|macro|CTEST8_10_V0
mdefine_line|#define CTEST8_10_V0&t;&t;0x10
DECL|macro|CTEST8_10_V_MASK
mdefine_line|#define CTEST8_10_V_MASK&t;0xf0&t;
DECL|macro|CTEST8_10_FLF
mdefine_line|#define CTEST8_10_FLF&t;&t;0x08&t;/* Flush FIFOs */
DECL|macro|CTEST8_10_CLF
mdefine_line|#define CTEST8_10_CLF&t;&t;0x04&t;/* Clear FIFOs */
DECL|macro|CTEST8_10_FM
mdefine_line|#define CTEST8_10_FM&t;&t;0x02&t;/* Fetch pin mode */
DECL|macro|CTEST8_10_SM
mdefine_line|#define CTEST8_10_SM&t;&t;0x01&t;/* Snoop pin mode */
multiline_comment|/* &n; * The CTEST9 register may be used to differentiate between a&n; * NCR53c700 and a NCR53c710.  &n; *&n; * Write 0xff to this register.&n; * Read it.&n; * If the contents are 0xff, it is a NCR53c700&n; * If the contents are 0x00, it is a NCR53c700-66 first revision&n; * If the contents are some other value, it is some other NCR53c700-66&n; */
DECL|macro|CTEST9_REG_00
mdefine_line|#define CTEST9_REG_00&t;&t;0x23&t;/* Chip test 9 ro */
DECL|macro|LCRC_REG_10
mdefine_line|#define LCRC_REG_10&t;&t;0x23&t;
multiline_comment|/*&n; * 0x24 through 0x27 are the DMA byte counter register.  Instructions&n; * write their high 8 bits into the DCMD register, the low 24 bits into&n; * the DBC register.&n; *&n; * Function is dependent on the command type being executed.&n; */
DECL|macro|DBC_REG
mdefine_line|#define DBC_REG&t;&t;&t;0x24
multiline_comment|/* &n; * For Block Move Instructions, DBC is a 24 bit quantity representing &n; *     the number of bytes to transfer.&n; * For Transfer Control Instructions, DBC is bit fielded as follows : &n; */
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
mdefine_line|#define DCMD_REG&t;&t;0x27&t;
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
mdefine_line|#define DCMD_TYPE_TCI&t;&t;0x80&t;/* Indicates a Transfer Control &n;&t;&t;&t;&t;&t;   instruction */
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
mdefine_line|#define DCMD_TYPE_MMI&t;&t;0xc0&t;/* Indicates a Memory Move instruction &n;&t;&t;&t;&t;&t;   (three words) */
DECL|macro|DNAD_REG
mdefine_line|#define DNAD_REG&t;&t;0x28&t;/* through 0x2b DMA next address for &n;&t;&t;&t;&t;&t;   data */
DECL|macro|DSP_REG
mdefine_line|#define DSP_REG&t;&t;&t;0x2c&t;/* through 0x2f DMA SCRIPTS pointer rw */
DECL|macro|DSPS_REG
mdefine_line|#define DSPS_REG&t;&t;0x30&t;/* through 0x33 DMA SCRIPTS pointer &n;&t;&t;&t;&t;&t;   save rw */
DECL|macro|DMODE_REG_00
mdefine_line|#define DMODE_REG_00&t;&t;0x34 &t;/* DMA mode rw */
DECL|macro|DMODE_00_BL1
mdefine_line|#define DMODE_00_BL1&t;0x80&t;/* Burst length bits */
DECL|macro|DMODE_00_BL0
mdefine_line|#define DMODE_00_BL0&t;0x40
DECL|macro|DMODE_BL_MASK
mdefine_line|#define DMODE_BL_MASK&t;0xc0
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
DECL|macro|DMODE_700_BW16
mdefine_line|#define DMODE_700_BW16&t;0x20&t;/* Host buswidth = 16 */
DECL|macro|DMODE_700_286
mdefine_line|#define DMODE_700_286&t;0x10&t;/* 286 mode */
DECL|macro|DMODE_700_IOM
mdefine_line|#define DMODE_700_IOM&t;0x08&t;/* Transfer to IO port */
DECL|macro|DMODE_700_FAM
mdefine_line|#define DMODE_700_FAM&t;0x04&t;/* Fixed address mode */
DECL|macro|DMODE_700_PIPE
mdefine_line|#define DMODE_700_PIPE&t;0x02&t;/* Pipeline mode disables &n;&t;&t;&t;&t;&t; * automatic fetch / exec &n;&t;&t;&t;&t;&t; */
DECL|macro|DMODE_MAN
mdefine_line|#define DMODE_MAN&t;0x01&t;&t;/* Manual start mode, &n;&t;&t;&t;&t;&t; * requires a 1 to be written&n;&t;&t;&t;&t;&t; * to the start DMA bit in the DCNTL&n;&t;&t;&t;&t;&t; * register to run scripts &n;&t;&t;&t;&t;&t; */
DECL|macro|DMODE_700_SAVE
mdefine_line|#define DMODE_700_SAVE ( DMODE_00_BL_MASK | DMODE_00_BW16 | DMODE_00_286 )
multiline_comment|/* NCR53c800 series only */
DECL|macro|SCRATCHA_REG_800
mdefine_line|#define SCRATCHA_REG_800&t;0x34&t;/* through 0x37 Scratch A rw */
multiline_comment|/* NCR53c710 only */
DECL|macro|SCRATCHB_REG_10
mdefine_line|#define SCRATCHB_REG_10&t;&t;0x34&t;/* through 0x37 scratch B rw */
DECL|macro|DMODE_REG_10
mdefine_line|#define DMODE_REG_10    &t;0x38&t;/* DMA mode rw, NCR53c710 and newer */
DECL|macro|DMODE_800_SIOM
mdefine_line|#define DMODE_800_SIOM&t;&t;0x20&t;/* Source IO = 1 */
DECL|macro|DMODE_800_DIOM
mdefine_line|#define DMODE_800_DIOM&t;&t;0x10&t;/* Destination IO = 1 */
DECL|macro|DMODE_800_ERL
mdefine_line|#define DMODE_800_ERL&t;&t;0x08&t;/* Enable Read Line */
multiline_comment|/* 35-38 are reserved on 700 and 700-66 series chips */
DECL|macro|DIEN_REG
mdefine_line|#define DIEN_REG&t;&t;0x39&t;/* DMA interrupt enable rw */
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
mdefine_line|#define DIEN_SIR&t;&t;0x04&t;/* Enable SCRIPTS INT command &n;&t;&t;&t;&t;&t; * interrupt&n;&t;&t;&t;&t;&t; */
multiline_comment|/* 0x02 is reserved on 800 series chips */
DECL|macro|DIEN_700_WTD
mdefine_line|#define DIEN_700_WTD&t;&t;0x02&t;/* Enable watchdog timeout interrupt */
DECL|macro|DIEN_700_OPC
mdefine_line|#define DIEN_700_OPC&t;&t;0x01&t;/* Enable illegal instruction &n;&t;&t;&t;&t;&t; * interrupt &n;&t;&t;&t;&t;&t; */
DECL|macro|DIEN_800_IID
mdefine_line|#define DIEN_800_IID&t;&t;0x01&t;/*  Same meaning, different name */ 
multiline_comment|/*&n; * DMA watchdog timer rw&n; * set in 16 CLK input periods.&n; */
DECL|macro|DWT_REG
mdefine_line|#define DWT_REG&t;&t;&t;0x3a
multiline_comment|/* DMA control rw */
DECL|macro|DCNTL_REG
mdefine_line|#define DCNTL_REG&t;&t;0x3b
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
mdefine_line|#define DCNTL_700_LLM&t;&t;0x08&t;/* Low level mode, can only be set &n;&t;&t;&t;&t;&t; * after selection */
DECL|macro|DCNTL_800_IRQM
mdefine_line|#define DCNTL_800_IRQM&t;&t;0x08&t;/* Totem pole IRQ pin */
DECL|macro|DCNTL_STD
mdefine_line|#define DCNTL_STD&t;&t;0x04&t;/* Start DMA / SCRIPTS */
multiline_comment|/* 0x02 is reserved */
DECL|macro|DCNTL_00_RST
mdefine_line|#define DCNTL_00_RST&t;&t;0x01&t;/* Software reset, resets everything&n;&t;&t;&t;&t;&t; * but 286 mode bit  in DMODE. On the&n;&t;&t;&t;&t;&t; * NCR53c710, this bit moved to CTEST8&n;&t;&t;&t;&t;&t; */
DECL|macro|DCNTL_10_COM
mdefine_line|#define DCNTL_10_COM&t;&t;0x01&t;/* 700 software compatibility mode */
DECL|macro|DCNTL_10_EA
mdefine_line|#define DCNTL_10_EA&t;&t;0x20&t;/* Enable Ack - needed for MVME16x */
DECL|macro|DCNTL_700_SAVE
mdefine_line|#define DCNTL_700_SAVE ( DCNTL_CF_MASK | DCNTL_S16)
multiline_comment|/* NCR53c700-66 only */
DECL|macro|SCRATCHB_REG_00
mdefine_line|#define SCRATCHB_REG_00&t;&t;0x3c&t;/* through 0x3f scratch b rw */
DECL|macro|SCRATCHB_REG_800
mdefine_line|#define SCRATCHB_REG_800&t;0x5c&t;/* through 0x5f scratch b rw */
multiline_comment|/* NCR53c710 only */
DECL|macro|ADDER_REG_10
mdefine_line|#define ADDER_REG_10&t;&t;0x3c&t;/* Adder, NCR53c710 only */
DECL|macro|SIEN1_REG_800
mdefine_line|#define SIEN1_REG_800&t;&t;0x41
DECL|macro|SIEN1_800_STO
mdefine_line|#define SIEN1_800_STO&t;&t;0x04&t;/* selection/reselection timeout */
DECL|macro|SIEN1_800_GEN
mdefine_line|#define SIEN1_800_GEN&t;&t;0x02&t;/* general purpose timer */
DECL|macro|SIEN1_800_HTH
mdefine_line|#define SIEN1_800_HTH&t;&t;0x01&t;/* handshake to handshake */
DECL|macro|SIST1_REG_800
mdefine_line|#define SIST1_REG_800&t;&t;0x43
DECL|macro|SIST1_800_STO
mdefine_line|#define SIST1_800_STO&t;&t;0x04&t;/* selection/reselection timeout */
DECL|macro|SIST1_800_GEN
mdefine_line|#define SIST1_800_GEN&t;&t;0x02&t;/* general purpose timer */
DECL|macro|SIST1_800_HTH
mdefine_line|#define SIST1_800_HTH&t;&t;0x01&t;/* handshake to handshake */
DECL|macro|SLPAR_REG_800
mdefine_line|#define SLPAR_REG_800&t;&t;0x44&t;/* Parity */
DECL|macro|MACNTL_REG_800
mdefine_line|#define MACNTL_REG_800&t;&t;0x46&t;/* Memory access control */
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
mdefine_line|#define GPCNTL_REG_800&t;&t;0x47&t;/* General Purpose Pin Control */
multiline_comment|/* Timeouts are expressed such that 0=off, 1=100us, doubling after that */
DECL|macro|STIME0_REG_800
mdefine_line|#define STIME0_REG_800&t;&t;0x48&t;/* SCSI Timer Register 0 */
DECL|macro|STIME0_800_HTH_MASK
mdefine_line|#define STIME0_800_HTH_MASK&t;0xf0&t;/* Handshake to Handshake timeout */
DECL|macro|STIME0_800_HTH_SHIFT
mdefine_line|#define STIME0_800_HTH_SHIFT&t;4
DECL|macro|STIME0_800_SEL_MASK
mdefine_line|#define STIME0_800_SEL_MASK&t;0x0f&t;/* Selection timeout */
DECL|macro|STIME0_800_SEL_SHIFT
mdefine_line|#define STIME0_800_SEL_SHIFT&t;0
DECL|macro|STIME1_REG_800
mdefine_line|#define STIME1_REG_800&t;&t;0x49
DECL|macro|STIME1_800_GEN_MASK
mdefine_line|#define STIME1_800_GEN_MASK&t;0x0f&t;/* General purpose timer */
DECL|macro|RESPID_REG_800
mdefine_line|#define RESPID_REG_800&t;&t;0x4a&t;/* Response ID, bit fielded.  8&n;&t;&t;&t;&t;&t;   bits on narrow chips, 16 on WIDE */
DECL|macro|STEST0_REG_800
mdefine_line|#define STEST0_REG_800&t;&t;0x4c&t;
DECL|macro|STEST0_800_SLT
mdefine_line|#define STEST0_800_SLT&t;&t;0x08&t;/* Selection response logic test */
DECL|macro|STEST0_800_ART
mdefine_line|#define STEST0_800_ART&t;&t;0x04&t;/* Arbitration priority encoder test */
DECL|macro|STEST0_800_SOZ
mdefine_line|#define STEST0_800_SOZ&t;&t;0x02&t;/* Synchronous offset zero */
DECL|macro|STEST0_800_SOM
mdefine_line|#define STEST0_800_SOM&t;&t;0x01&t;/* Synchronous offset maximum */
DECL|macro|STEST1_REG_800
mdefine_line|#define STEST1_REG_800&t;&t;0x4d
DECL|macro|STEST1_800_SCLK
mdefine_line|#define STEST1_800_SCLK&t;&t;0x80&t;/* Disable SCSI clock */
DECL|macro|STEST2_REG_800
mdefine_line|#define STEST2_REG_800&t;&t;0x4e&t;
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
mdefine_line|#define STEST3_REG_800&t;&t;0x4f&t; 
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
DECL|macro|OPTION_PARITY
mdefine_line|#define OPTION_PARITY &t;&t;0x1&t;/* Enable parity checking */
DECL|macro|OPTION_TAGGED_QUEUE
mdefine_line|#define OPTION_TAGGED_QUEUE&t;0x2&t;/* Enable SCSI-II tagged queuing */
DECL|macro|OPTION_700
mdefine_line|#define OPTION_700&t;&t;0x8&t;/* Always run NCR53c700 scripts */
DECL|macro|OPTION_INTFLY
mdefine_line|#define OPTION_INTFLY&t;&t;0x10&t;/* Use INTFLY interrupts */
DECL|macro|OPTION_DEBUG_INTR
mdefine_line|#define OPTION_DEBUG_INTR&t;0x20&t;/* Debug interrupts */
DECL|macro|OPTION_DEBUG_INIT_ONLY
mdefine_line|#define OPTION_DEBUG_INIT_ONLY&t;0x40&t;/* Run initialization code and &n;&t;&t;&t;&t;&t;   simple test code, return&n;&t;&t;&t;&t;&t;   DID_NO_CONNECT if any SCSI&n;&t;&t;&t;&t;&t;   commands are attempted. */
DECL|macro|OPTION_DEBUG_READ_ONLY
mdefine_line|#define OPTION_DEBUG_READ_ONLY&t;0x80&t;/* Return DID_ERROR if any &n;&t;&t;&t;&t;&t;   SCSI write is attempted */
DECL|macro|OPTION_DEBUG_TRACE
mdefine_line|#define OPTION_DEBUG_TRACE&t;0x100&t;/* Animated trace mode, print &n;&t;&t;&t;&t;&t;   each address and instruction &n;&t;&t;&t;&t;&t;   executed to debug buffer. */
DECL|macro|OPTION_DEBUG_SINGLE
mdefine_line|#define OPTION_DEBUG_SINGLE&t;0x200&t;/* stop after executing one &n;&t;&t;&t;&t;&t;   instruction */
DECL|macro|OPTION_SYNCHRONOUS
mdefine_line|#define OPTION_SYNCHRONOUS&t;0x400&t;/* Enable sync SCSI.  */
DECL|macro|OPTION_MEMORY_MAPPED
mdefine_line|#define OPTION_MEMORY_MAPPED&t;0x800&t;/* NCR registers have valid &n;&t;&t;&t;&t;&t;   memory mapping */
DECL|macro|OPTION_IO_MAPPED
mdefine_line|#define OPTION_IO_MAPPED&t;0x1000  /* NCR registers have valid&n;&t;&t;&t;&t;&t;     I/O mapping */
DECL|macro|OPTION_DEBUG_PROBE_ONLY
mdefine_line|#define OPTION_DEBUG_PROBE_ONLY&t;0x2000  /* Probe only, don&squot;t even init */
DECL|macro|OPTION_DEBUG_TESTS_ONLY
mdefine_line|#define OPTION_DEBUG_TESTS_ONLY&t;0x4000  /* Probe, init, run selected tests */
DECL|macro|OPTION_DEBUG_TEST0
mdefine_line|#define OPTION_DEBUG_TEST0&t;0x08000 /* Run test 0 */
DECL|macro|OPTION_DEBUG_TEST1
mdefine_line|#define OPTION_DEBUG_TEST1&t;0x10000 /* Run test 1 */
DECL|macro|OPTION_DEBUG_TEST2
mdefine_line|#define OPTION_DEBUG_TEST2&t;0x20000 /* Run test 2 */
DECL|macro|OPTION_DEBUG_DUMP
mdefine_line|#define OPTION_DEBUG_DUMP&t;0x40000 /* Dump commands */
DECL|macro|OPTION_DEBUG_TARGET_LIMIT
mdefine_line|#define OPTION_DEBUG_TARGET_LIMIT 0x80000 /* Only talk to target+luns specified */
DECL|macro|OPTION_DEBUG_NCOMMANDS_LIMIT
mdefine_line|#define OPTION_DEBUG_NCOMMANDS_LIMIT 0x100000 /* Limit the number of commands */
DECL|macro|OPTION_DEBUG_SCRIPT
mdefine_line|#define OPTION_DEBUG_SCRIPT 0x200000 /* Print when checkpoints are passed */
DECL|macro|OPTION_DEBUG_FIXUP
mdefine_line|#define OPTION_DEBUG_FIXUP 0x400000 /* print fixup values */
DECL|macro|OPTION_DEBUG_DSA
mdefine_line|#define OPTION_DEBUG_DSA 0x800000
DECL|macro|OPTION_DEBUG_CORRUPTION
mdefine_line|#define OPTION_DEBUG_CORRUPTION&t;0x1000000&t;/* Detect script corruption */
DECL|macro|OPTION_DEBUG_SDTR
mdefine_line|#define OPTION_DEBUG_SDTR       0x2000000&t;/* Debug SDTR problem */
DECL|macro|OPTION_DEBUG_MISMATCH
mdefine_line|#define OPTION_DEBUG_MISMATCH &t;0x4000000 &t;/* Debug phase mismatches */
DECL|macro|OPTION_DISCONNECT
mdefine_line|#define OPTION_DISCONNECT&t;0x8000000&t;/* Allow disconnect */
DECL|macro|OPTION_DEBUG_DISCONNECT
mdefine_line|#define OPTION_DEBUG_DISCONNECT 0x10000000&t;
DECL|macro|OPTION_ALWAYS_SYNCHRONOUS
mdefine_line|#define OPTION_ALWAYS_SYNCHRONOUS 0x20000000&t;/* Negotiate sync. transfers&n;&t;&t;&t;&t;&t;&t;   on power up */
DECL|macro|OPTION_DEBUG_QUEUES
mdefine_line|#define OPTION_DEBUG_QUEUES&t;0x80000000&t;
DECL|macro|OPTION_DEBUG_ALLOCATION
mdefine_line|#define OPTION_DEBUG_ALLOCATION 0x100000000LL
DECL|macro|OPTION_DEBUG_SYNCHRONOUS
mdefine_line|#define OPTION_DEBUG_SYNCHRONOUS 0x200000000LL&t;/* Sanity check SXFER and &n;&t;&t;&t;&t;&t;&t;   SCNTL3 registers */
DECL|macro|OPTION_NO_ASYNC
mdefine_line|#define OPTION_NO_ASYNC&t;0x400000000LL&t;&t;/* Don&squot;t automagically send&n;&t;&t;&t;&t;&t;&t;   SDTR for async transfers when&n;&t;&t;&t;&t;&t;&t;   we haven&squot;t been told to do&n;&t;&t;&t;&t;&t;&t;   a synchronous transfer. */
DECL|macro|OPTION_NO_PRINT_RACE
mdefine_line|#define OPTION_NO_PRINT_RACE 0x800000000LL&t;/* Don&squot;t print message when&n;&t;&t;&t;&t;&t;&t;   the reselect/WAIT DISCONNECT&n;&t;&t;&t;&t;&t;&t;   race condition hits */
macro_line|#if !defined(PERM_OPTIONS)
DECL|macro|PERM_OPTIONS
mdefine_line|#define PERM_OPTIONS 0
macro_line|#endif
multiline_comment|/*&n; * Some data which is accessed by the NCR chip must be 4-byte aligned.&n; * For some hosts the default is less than that (eg. 68K uses 2-byte).&n; * Alignment has only been forced where it is important; also if one&n; * 32 bit structure field is aligned then it is assumed that following&n; * 32 bit fields are also aligned.  Take care when adding fields&n; * which are other than 32 bit.&n; */
DECL|struct|NCR53c7x0_synchronous
r_struct
id|NCR53c7x0_synchronous
(brace
DECL|member|select_indirect
id|u32
id|select_indirect
multiline_comment|/* Value used for indirect selection */
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|member|sscf_710
id|u32
id|sscf_710
suffix:semicolon
multiline_comment|/* Used to set SSCF bits for 710 */
DECL|member|script
id|u32
id|script
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Size ?? Script used when target is &n;&t;&t;&t;&t;&t;&t;reselected */
DECL|member|synchronous_want
r_int
r_char
id|synchronous_want
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Per target desired SDTR */
multiline_comment|/* &n; * Set_synchronous programs these, select_indirect and current settings after&n; * int_debug_should show a match.&n; */
DECL|member|sxfer_sanity
DECL|member|scntl3_sanity
r_int
r_char
id|sxfer_sanity
comma
id|scntl3_sanity
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CMD_FLAG_SDTR
mdefine_line|#define CMD_FLAG_SDTR &t;&t;1&t;/* Initiating synchronous &n;&t;&t;&t;&t;&t;   transfer negotiation */
DECL|macro|CMD_FLAG_WDTR
mdefine_line|#define CMD_FLAG_WDTR&t;&t;2&t;/* Initiating wide transfer&n;&t;&t;&t;&t;&t;   negotiation */
DECL|macro|CMD_FLAG_DID_SDTR
mdefine_line|#define CMD_FLAG_DID_SDTR&t;4&t;/* did SDTR */
DECL|macro|CMD_FLAG_DID_WDTR
mdefine_line|#define CMD_FLAG_DID_WDTR&t;8&t;/* did WDTR */
DECL|struct|NCR53c7x0_table_indirect
r_struct
id|NCR53c7x0_table_indirect
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|ncr_event
r_enum
id|ncr_event
(brace
DECL|enumerator|EVENT_NONE
id|EVENT_NONE
op_assign
l_int|0
comma
multiline_comment|/* &n; * Order is IMPORTANT, since these must correspond to the event interrupts&n; * in 53c7,8xx.scr &n; */
DECL|enumerator|EVENT_ISSUE_QUEUE
id|EVENT_ISSUE_QUEUE
op_assign
l_int|0x5000000
comma
multiline_comment|/* 0 Command was added to issue queue */
DECL|enumerator|EVENT_START_QUEUE
id|EVENT_START_QUEUE
comma
multiline_comment|/* 1 Command moved to start queue */
DECL|enumerator|EVENT_SELECT
id|EVENT_SELECT
comma
multiline_comment|/* 2 Command completed selection */
DECL|enumerator|EVENT_DISCONNECT
id|EVENT_DISCONNECT
comma
multiline_comment|/* 3 Command disconnected */
DECL|enumerator|EVENT_RESELECT
id|EVENT_RESELECT
comma
multiline_comment|/* 4 Command reselected */
DECL|enumerator|EVENT_COMPLETE
id|EVENT_COMPLETE
comma
multiline_comment|/* 5 Command completed */
DECL|enumerator|EVENT_IDLE
id|EVENT_IDLE
comma
multiline_comment|/* 6 */
DECL|enumerator|EVENT_SELECT_FAILED
id|EVENT_SELECT_FAILED
comma
multiline_comment|/* 7 */
DECL|enumerator|EVENT_BEFORE_SELECT
id|EVENT_BEFORE_SELECT
comma
multiline_comment|/* 8 */
DECL|enumerator|EVENT_RESELECT_FAILED
id|EVENT_RESELECT_FAILED
multiline_comment|/* 9 */
)brace
suffix:semicolon
DECL|struct|NCR53c7x0_event
r_struct
id|NCR53c7x0_event
(brace
DECL|member|event
r_enum
id|ncr_event
id|event
suffix:semicolon
multiline_comment|/* What type of event */
DECL|member|target
r_int
r_char
id|target
suffix:semicolon
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
DECL|member|dsa
id|u32
op_star
id|dsa
suffix:semicolon
multiline_comment|/* What&squot;s in the DSA register now (virt) */
multiline_comment|/* &n; * A few things from that SCSI pid so we know what happened after &n; * the Scsi_Cmnd structure in question may have disappeared.&n; */
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
multiline_comment|/* The SCSI PID which caused this &n;&t;&t;&t;&t;   event */
DECL|member|cmnd
r_int
r_char
id|cmnd
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Things in the NCR53c7x0_cmd structure are split into two parts :&n; *&n; * 1.  A fixed portion, for things which are not accessed directly by static NCR&n; *&t;code (ie, are referenced only by the Linux side of the driver,&n; *&t;or only by dynamically generated code).  &n; *&n; * 2.  The DSA portion, for things which are accessed directly by static NCR&n; *&t;code.&n; *&n; * This is a little ugly, but it &n; * 1.  Avoids conflicts between the NCR code&squot;s picture of the structure, and &n; * &t;Linux code&squot;s idea of what it looks like.&n; *&n; * 2.  Minimizes the pain in the Linux side of the code needed &n; * &t;to calculate real dsa locations for things, etc.&n; * &n; */
DECL|struct|NCR53c7x0_cmd
r_struct
id|NCR53c7x0_cmd
(brace
DECL|member|real
r_void
op_star
id|real
suffix:semicolon
multiline_comment|/* Real, unaligned address for&n;&t;&t;&t;&t;&t;   free function */
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Command to deallocate; NULL&n;&t;&t;&t;&t;&t;   for structures allocated with&n;&t;&t;&t;&t;&t;   scsi_register, etc. */
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* Associated Scsi_Cmnd &n;&t;&t;&t;&t;&t;   structure, Scsi_Cmnd points&n;&t;&t;&t;&t;&t;   at NCR53c7x0_cmd using &n;&t;&t;&t;&t;&t;   host_scribble structure */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* scsi_malloc&squot;d size of this &n;&t;&t;&t;&t;&t;   structure */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* CMD_* flags */
DECL|member|cmnd
r_int
r_char
id|cmnd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* CDB, copied from Scsi_Cmnd */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* Copy to Scsi_Cmnd when done */
r_struct
(brace
multiline_comment|/* Private non-cached bounce buffer */
DECL|member|buf
r_int
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|bounce
)brace
id|bounce
suffix:semicolon
multiline_comment|/*&n; * SDTR and WIDE messages are an either/or affair&n; * in this message, since we will go into message out and send&n; * _the whole mess_ without dropping out of message out to &n; * let the target go into message in after sending the first &n; * message.&n; */
DECL|member|select
r_int
r_char
id|select
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* Select message, includes&n;&t;&t;&t;&t;&t;   IDENTIFY&n;&t;&t;&t;&t;&t;   (optional) QUEUE TAG&n; &t;&t;&t;&t; &t;   (optional) SDTR or WDTR&n;&t;&t;&t;&t;&t; */
DECL|member|next
r_volatile
r_struct
id|NCR53c7x0_cmd
op_star
id|next
suffix:semicolon
multiline_comment|/* Linux maintained lists (free,&n;&t;&t;&t;&t;&t;    running, eventually finished */
DECL|member|data_transfer_start
id|u32
op_star
id|data_transfer_start
suffix:semicolon
multiline_comment|/* Start of data transfer routines */
DECL|member|data_transfer_end
id|u32
op_star
id|data_transfer_end
suffix:semicolon
multiline_comment|/* Address after end of data transfer o&n;    &t;    &t;    &t;    &t;    &t;   routines */
multiline_comment|/* &n; * The following three fields were moved from the DSA proper to here&n; * since only dynamically generated NCR code refers to them, meaning&n; * we don&squot;t need dsa_* absolutes, and it is simpler to let the &n; * host code refer to them directly.&n; */
multiline_comment|/* &n; * HARD CODED : residual and saved_residual need to agree with the sizes&n; * used in NCR53c7,8xx.scr.  &n; * &n; * FIXME: we want to consider the case where we have odd-length &n; *&t;scatter/gather buffers and a WIDE transfer, in which case &n; *&t;we&squot;ll need to use the CHAIN MOVE instruction.  Ick.&n; */
DECL|member|residual
id|u32
id|residual
(braket
l_int|6
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Residual data transfer which&n;&t;&t;&t;&t;&t;   allows pointer code to work&n;&t;&t;&t;&t;&t;   right.&n;&n;    &t;    &t;    &t;    &t;    &t;    [0-1] : Conditional call to &n;    &t;    &t;    &t;    &t;    &t;    &t;appropriate other transfer &n;    &t;    &t;    &t;    &t;    &t;    &t;routine.&n;    &t;    &t;    &t;    &t;    &t;    [2-3] : Residual block transfer&n;    &t;    &t;    &t;    &t;    &t;    &t;instruction.&n;    &t;    &t;    &t;    &t;    &t;    [4-5] : Jump to instruction&n;    &t;    &t;    &t;    &t;    &t;    &t;after splice.&n;&t;&t;&t;&t;&t; */
DECL|member|saved_residual
id|u32
id|saved_residual
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Copy of old residual, so we &n;&t;&t;&t;&t;&t;   can get another partial &n;&t;&t;&t;&t;&t;   transfer and still recover &n;    &t;    &t;    &t;    &t;    &t; */
DECL|member|saved_data_pointer
id|u32
id|saved_data_pointer
suffix:semicolon
multiline_comment|/* Saved data pointer */
DECL|member|dsa_next_addr
id|u32
id|dsa_next_addr
suffix:semicolon
multiline_comment|/* _Address_ of dsa_next field  &n;&t;&t;&t;&t;&t;   in this dsa for RISCy &n;&t;&t;&t;&t;&t;   style constant. */
DECL|member|dsa_addr
id|u32
id|dsa_addr
suffix:semicolon
multiline_comment|/* Address of dsa; RISCy style&n;&t;&t;&t;&t;&t;   constant */
DECL|member|dsa
id|u32
id|dsa
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Variable length (depending&n;&t;&t;&t;&t;&t;   on host type, number of scatter /&n;&t;&t;&t;&t;&t;   gather buffers, etc).  */
)brace
suffix:semicolon
DECL|struct|NCR53c7x0_break
r_struct
id|NCR53c7x0_break
(brace
DECL|member|address
DECL|member|old_instruction
id|u32
op_star
id|address
comma
id|old_instruction
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|next
r_struct
id|NCR53c7x0_break
op_star
id|next
suffix:semicolon
DECL|member|old_size
r_int
r_char
id|old_size
suffix:semicolon
multiline_comment|/* Size of old instruction */
)brace
suffix:semicolon
multiline_comment|/* Indicates that the NCR is not executing code */
DECL|macro|STATE_HALTED
mdefine_line|#define STATE_HALTED&t;0&t;&t;
multiline_comment|/* &n; * Indicates that the NCR is executing the wait for select / reselect &n; * script.  Only used when running NCR53c700 compatible scripts, only &n; * state during which an ABORT is _not_ considered an error condition.&n; */
DECL|macro|STATE_WAITING
mdefine_line|#define STATE_WAITING&t;1&t;&t;
multiline_comment|/* Indicates that the NCR is executing other code. */
DECL|macro|STATE_RUNNING
mdefine_line|#define STATE_RUNNING&t;2&t;&t;
multiline_comment|/* &n; * Indicates that the NCR was being aborted.&n; */
DECL|macro|STATE_ABORTING
mdefine_line|#define STATE_ABORTING&t;3
multiline_comment|/* Indicates that the NCR was successfully aborted. */
DECL|macro|STATE_ABORTED
mdefine_line|#define STATE_ABORTED 4
multiline_comment|/* Indicates that the NCR has been disabled due to a fatal error */
DECL|macro|STATE_DISABLED
mdefine_line|#define STATE_DISABLED 5
multiline_comment|/* &n; * Where knowledge of SCSI SCRIPT(tm) specified values are needed &n; * in an interrupt handler, an interrupt handler exists for each &n; * different SCSI script so we don&squot;t have name space problems.&n; * &n; * Return values of these handlers are as follows : &n; */
DECL|macro|SPECIFIC_INT_NOTHING
mdefine_line|#define SPECIFIC_INT_NOTHING &t;0&t;/* don&squot;t even restart */
DECL|macro|SPECIFIC_INT_RESTART
mdefine_line|#define SPECIFIC_INT_RESTART&t;1&t;/* restart at the next instruction */
DECL|macro|SPECIFIC_INT_ABORT
mdefine_line|#define SPECIFIC_INT_ABORT&t;2&t;/* recoverable error, abort cmd */
DECL|macro|SPECIFIC_INT_PANIC
mdefine_line|#define SPECIFIC_INT_PANIC&t;3&t;/* unrecoverable error, panic */
DECL|macro|SPECIFIC_INT_DONE
mdefine_line|#define SPECIFIC_INT_DONE&t;4&t;/* normal command completion */
DECL|macro|SPECIFIC_INT_BREAK
mdefine_line|#define SPECIFIC_INT_BREAK&t;5&t;/* break point encountered */
DECL|struct|NCR53c7x0_hostdata
r_struct
id|NCR53c7x0_hostdata
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Size of entire Scsi_Host&n;&t;&t;&t;&t;&t;   structure */
DECL|member|board
r_int
id|board
suffix:semicolon
multiline_comment|/* set to board type, useful if &n;&t;&t;&t;&t;&t;   we have host specific things,&n;&t;&t;&t;&t;&t;   ie, a general purpose I/O &n;&t;&t;&t;&t;&t;   bit is being used to enable&n;&t;&t;&t;&t;&t;   termination, etc. */
DECL|member|chip
r_int
id|chip
suffix:semicolon
multiline_comment|/* set to chip type; 700-66 is&n;&t;&t;&t;&t;&t;   700-66, rest are last three&n;&t;&t;&t;&t;&t;   digits of part number */
DECL|member|valid_ids
r_char
id|valid_ids
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Valid SCSI ID&squot;s for adapter */
DECL|member|dsp
id|u32
op_star
id|dsp
suffix:semicolon
multiline_comment|/* dsp to restart with after&n;&t;&t;&t;&t;&t;   all stacked interrupts are&n;&t;&t;&t;&t;&t;   handled. */
DECL|member|dsp_changed
r_int
id|dsp_changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Has dsp changed within this&n;&t;&t;&t;&t;&t;   set of stacked interrupts ? */
DECL|member|dstat
r_int
r_char
id|dstat
suffix:semicolon
multiline_comment|/* Most recent value of dstat */
DECL|member|dstat_valid
r_int
id|dstat_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|expecting_iid
r_int
id|expecting_iid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Expect IID interrupt */
DECL|member|expecting_sto
r_int
id|expecting_sto
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Expect STO interrupt */
multiline_comment|/* &n;     * The code stays cleaner if we use variables with function&n;     * pointers and offsets that are unique for the different&n;     * scripts rather than having a slew of switch(hostdata-&gt;chip) &n;     * statements.&n;     * &n;     * It also means that the #defines from the SCSI SCRIPTS(tm)&n;     * don&squot;t have to be visible outside of the script-specific&n;     * instructions, preventing name space pollution.&n;     */
DECL|member|init_fixup
r_void
(paren
op_star
id|init_fixup
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
DECL|member|init_save_regs
r_void
(paren
op_star
id|init_save_regs
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
DECL|member|dsa_fixup
r_void
(paren
op_star
id|dsa_fixup
)paren
(paren
r_struct
id|NCR53c7x0_cmd
op_star
id|cmd
)paren
suffix:semicolon
DECL|member|soft_reset
r_void
(paren
op_star
id|soft_reset
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
DECL|member|run_tests
r_int
(paren
op_star
id|run_tests
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/*&n;     * Called when DSTAT_SIR is set, indicating an interrupt generated&n;     * by the INT instruction, where values are unique for each SCSI&n;     * script.  Should return one of the SPEC_* values.&n;     */
DECL|member|dstat_sir_intr
r_int
(paren
op_star
id|dstat_sir_intr
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
r_struct
id|NCR53c7x0_cmd
op_star
id|cmd
)paren
suffix:semicolon
DECL|member|dsa_len
r_int
id|dsa_len
suffix:semicolon
multiline_comment|/* Size of DSA structure */
multiline_comment|/*&n;     * Location of DSA fields for the SCSI SCRIPT corresponding to this &n;     * chip.  &n;     */
DECL|member|dsa_start
id|s32
id|dsa_start
suffix:semicolon
DECL|member|dsa_end
id|s32
id|dsa_end
suffix:semicolon
DECL|member|dsa_next
id|s32
id|dsa_next
suffix:semicolon
DECL|member|dsa_prev
id|s32
id|dsa_prev
suffix:semicolon
DECL|member|dsa_cmnd
id|s32
id|dsa_cmnd
suffix:semicolon
DECL|member|dsa_select
id|s32
id|dsa_select
suffix:semicolon
DECL|member|dsa_msgout
id|s32
id|dsa_msgout
suffix:semicolon
DECL|member|dsa_cmdout
id|s32
id|dsa_cmdout
suffix:semicolon
DECL|member|dsa_dataout
id|s32
id|dsa_dataout
suffix:semicolon
DECL|member|dsa_datain
id|s32
id|dsa_datain
suffix:semicolon
DECL|member|dsa_msgin
id|s32
id|dsa_msgin
suffix:semicolon
DECL|member|dsa_msgout_other
id|s32
id|dsa_msgout_other
suffix:semicolon
DECL|member|dsa_write_sync
id|s32
id|dsa_write_sync
suffix:semicolon
DECL|member|dsa_write_resume
id|s32
id|dsa_write_resume
suffix:semicolon
DECL|member|dsa_check_reselect
id|s32
id|dsa_check_reselect
suffix:semicolon
DECL|member|dsa_status
id|s32
id|dsa_status
suffix:semicolon
DECL|member|dsa_saved_pointer
id|s32
id|dsa_saved_pointer
suffix:semicolon
DECL|member|dsa_jump_dest
id|s32
id|dsa_jump_dest
suffix:semicolon
multiline_comment|/* &n;     * Important entry points that generic fixup code needs&n;     * to know about, fixed up.&n;     */
DECL|member|E_accept_message
id|s32
id|E_accept_message
suffix:semicolon
DECL|member|E_command_complete
id|s32
id|E_command_complete
suffix:semicolon
DECL|member|E_data_transfer
id|s32
id|E_data_transfer
suffix:semicolon
DECL|member|E_dsa_code_template
id|s32
id|E_dsa_code_template
suffix:semicolon
DECL|member|E_dsa_code_template_end
id|s32
id|E_dsa_code_template_end
suffix:semicolon
DECL|member|E_end_data_transfer
id|s32
id|E_end_data_transfer
suffix:semicolon
DECL|member|E_msg_in
id|s32
id|E_msg_in
suffix:semicolon
DECL|member|E_initiator_abort
id|s32
id|E_initiator_abort
suffix:semicolon
DECL|member|E_other_transfer
id|s32
id|E_other_transfer
suffix:semicolon
DECL|member|E_other_in
id|s32
id|E_other_in
suffix:semicolon
DECL|member|E_other_out
id|s32
id|E_other_out
suffix:semicolon
DECL|member|E_target_abort
id|s32
id|E_target_abort
suffix:semicolon
DECL|member|E_debug_break
id|s32
id|E_debug_break
suffix:semicolon
DECL|member|E_reject_message
id|s32
id|E_reject_message
suffix:semicolon
DECL|member|E_respond_message
id|s32
id|E_respond_message
suffix:semicolon
DECL|member|E_select
id|s32
id|E_select
suffix:semicolon
DECL|member|E_select_msgout
id|s32
id|E_select_msgout
suffix:semicolon
DECL|member|E_test_0
id|s32
id|E_test_0
suffix:semicolon
DECL|member|E_test_1
id|s32
id|E_test_1
suffix:semicolon
DECL|member|E_test_2
id|s32
id|E_test_2
suffix:semicolon
DECL|member|E_test_3
id|s32
id|E_test_3
suffix:semicolon
DECL|member|E_dsa_zero
id|s32
id|E_dsa_zero
suffix:semicolon
DECL|member|E_cmdout_cmdout
id|s32
id|E_cmdout_cmdout
suffix:semicolon
DECL|member|E_wait_reselect
id|s32
id|E_wait_reselect
suffix:semicolon
DECL|member|E_dsa_code_begin
id|s32
id|E_dsa_code_begin
suffix:semicolon
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
multiline_comment|/* Bitfielded set of options enabled */
DECL|member|test_completed
r_volatile
id|u32
id|test_completed
suffix:semicolon
multiline_comment|/* Test completed */
DECL|member|test_running
r_int
id|test_running
suffix:semicolon
multiline_comment|/* Test currently running */
DECL|member|test_source
id|s32
id|test_source
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|member|test_dest
r_volatile
id|s32
id|test_dest
suffix:semicolon
DECL|member|state
r_volatile
r_int
id|state
suffix:semicolon
multiline_comment|/* state of driver, only used for &n;&t;&t;&t;&t;&t;   OPTION_700 */
DECL|member|dmode
r_int
r_char
id|dmode
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t;&t;&t; * set to the address of the DMODE &n;&t;&t;&t;&t;&t; * register for this chip.&n;&t;&t;&t;&t;&t; */
DECL|member|istat
r_int
r_char
id|istat
suffix:semicolon
multiline_comment|/* &n;    &t;    &t;    &t;    &t;    &t; * set to the address of the ISTAT &n;    &t;    &t;    &t;    &t;    &t; * register for this chip.&n;    &t;    &t;    &t;    &t;    &t; */
DECL|member|scsi_clock
r_int
id|scsi_clock
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t;&t;&t; * SCSI clock in HZ. 0 may be used &n;&t;&t;&t;&t;&t; * for unknown, although this will&n;&t;&t;&t;&t;&t; * disable synchronous negotiation.&n;&t;&t;&t;&t;&t; */
DECL|member|intrs
r_volatile
r_int
id|intrs
suffix:semicolon
multiline_comment|/* Number of interrupts */
DECL|member|resets
r_volatile
r_int
id|resets
suffix:semicolon
multiline_comment|/* Number of SCSI resets */
DECL|member|saved_dmode
r_int
r_char
id|saved_dmode
suffix:semicolon
DECL|member|saved_ctest4
r_int
r_char
id|saved_ctest4
suffix:semicolon
DECL|member|saved_ctest7
r_int
r_char
id|saved_ctest7
suffix:semicolon
DECL|member|saved_dcntl
r_int
r_char
id|saved_dcntl
suffix:semicolon
DECL|member|saved_scntl3
r_int
r_char
id|saved_scntl3
suffix:semicolon
DECL|member|this_id_mask
r_int
r_char
id|this_id_mask
suffix:semicolon
multiline_comment|/* Debugger information */
DECL|member|breakpoints
r_struct
id|NCR53c7x0_break
op_star
id|breakpoints
comma
multiline_comment|/* Linked list of all break points */
DECL|member|breakpoint_current
op_star
id|breakpoint_current
suffix:semicolon
multiline_comment|/* Current breakpoint being stepped &n;&t;&t;&t;&t;&t;   through, NULL if we are running &n;&t;&t;&t;&t;&t;   normally. */
macro_line|#ifdef NCR_DEBUG
DECL|member|debug_size
r_int
id|debug_size
suffix:semicolon
multiline_comment|/* Size of debug buffer */
DECL|member|debug_count
r_volatile
r_int
id|debug_count
suffix:semicolon
multiline_comment|/* Current data count */
DECL|member|debug_buf
r_volatile
r_char
op_star
id|debug_buf
suffix:semicolon
multiline_comment|/* Output ring buffer */
DECL|member|debug_write
r_volatile
r_char
op_star
id|debug_write
suffix:semicolon
multiline_comment|/* Current write pointer */
DECL|member|debug_read
r_volatile
r_char
op_star
id|debug_read
suffix:semicolon
multiline_comment|/* Current read pointer */
macro_line|#endif /* def NCR_DEBUG */
multiline_comment|/* XXX - primitive debugging junk, remove when working ? */
DECL|member|debug_print_limit
r_int
id|debug_print_limit
suffix:semicolon
multiline_comment|/* Number of commands to print&n;&t;&t;&t;&t;&t;   out exhaustive debugging&n;&t;&t;&t;&t;&t;   information for if &n;&t;&t;&t;&t;&t;   OPTION_DEBUG_DUMP is set */
DECL|member|debug_lun_limit
r_int
r_char
id|debug_lun_limit
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* If OPTION_DEBUG_TARGET_LIMIT&n;&t;&t;&t;&t;&t;   set, puke if commands are sent&n;&t;&t;&t;&t;&t;   to other target/lun combinations */
DECL|member|debug_count_limit
r_int
id|debug_count_limit
suffix:semicolon
multiline_comment|/* Number of commands to execute&n;&t;&t;&t;&t;&t;   before puking to limit debugging &n;&t;&t;&t;&t;&t;   output */
DECL|member|idle
r_volatile
r_int
id|idle
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set to 1 if idle */
multiline_comment|/* &n;     * Table of synchronous+wide transfer parameters set on a per-target&n;     * basis.&n;     */
DECL|member|sync
r_volatile
r_struct
id|NCR53c7x0_synchronous
id|sync
(braket
l_int|16
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|member|issue_queue
r_volatile
id|Scsi_Cmnd
op_star
id|issue_queue
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* waiting to be issued by&n;&t;&t;&t;&t;&t;&t;   Linux driver */
DECL|member|running_list
r_volatile
r_struct
id|NCR53c7x0_cmd
op_star
id|running_list
suffix:semicolon
multiline_comment|/* commands running, maintained&n;&t;&t;&t;&t;&t;&t;   by Linux driver */
DECL|member|ncrcurrent
r_volatile
r_struct
id|NCR53c7x0_cmd
op_star
id|ncrcurrent
suffix:semicolon
multiline_comment|/* currently connected &n;&t;&t;&t;&t;&t;&t;   nexus, ONLY valid for&n;&t;&t;&t;&t;&t;&t;   NCR53c700/NCR53c700-66&n;&t;&t;&t;&t;&t;&t; */
DECL|member|spare
r_volatile
r_struct
id|NCR53c7x0_cmd
op_star
id|spare
suffix:semicolon
multiline_comment|/* pointer to spare,&n;    &t;    &t;    &t;    &t;    &t;    &t;   allocated at probe time,&n;    &t;    &t;    &t;    &t;    &t;    &t;   which we can use for &n;&t;&t;&t;&t;&t;&t;   initialization */
DECL|member|free
r_volatile
r_struct
id|NCR53c7x0_cmd
op_star
id|free
suffix:semicolon
DECL|member|max_cmd_size
r_int
id|max_cmd_size
suffix:semicolon
multiline_comment|/* Maximum size of NCR53c7x0_cmd&n;&t;&t;&t;&t;&t;    &t;   based on number of &n;&t;&t;&t;&t;&t;&t;   scatter/gather segments, etc.&n;&t;&t;&t;&t;&t;&t;   */
DECL|member|num_cmds
r_volatile
r_int
id|num_cmds
suffix:semicolon
multiline_comment|/* Number of commands &n;&t;&t;&t;&t;&t;&t;   allocated */
DECL|member|extra_allocate
r_volatile
r_int
id|extra_allocate
suffix:semicolon
DECL|member|cmd_allocated
r_volatile
r_int
r_char
id|cmd_allocated
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Have we allocated commands&n;&t;&t;&t;&t;&t;&t;   for this target yet?  If not,&n;&t;&t;&t;&t;&t;&t;   do so ASAP */
DECL|member|busy
r_volatile
r_int
r_char
id|busy
(braket
l_int|16
)braket
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* number of commands &n;&t;&t;&t;&t;&t;&t;   executing on each target&n;    &t;    &t;    &t;    &t;    &t;    &t; */
multiline_comment|/* &n;     * Eventually, I&squot;ll switch to a coroutine for calling &n;     * cmd-&gt;done(cmd), etc. so that we can overlap interrupt&n;     * processing with this code for maximum performance.&n;     */
DECL|member|finished_queue
r_volatile
r_struct
id|NCR53c7x0_cmd
op_star
id|finished_queue
suffix:semicolon
multiline_comment|/* Shared variables between SCRIPT and host driver */
DECL|member|schedule
r_volatile
id|u32
op_star
id|schedule
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Array of JUMPs to dsa_begin&n;&t;&t;&t;&t;&t;&t;   routines of various DSAs.  &n;&t;&t;&t;&t;&t;&t;   When not in use, replace&n;&t;&t;&t;&t;&t;&t;   with jump to next slot */
DECL|member|msg_buf
r_volatile
r_int
r_char
id|msg_buf
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* buffer for messages&n;&t;&t;&t;&t;&t;&t;   other than the command&n;&t;&t;&t;&t;&t;&t;   complete message */
multiline_comment|/* Per-target default synchronous and WIDE messages */
DECL|member|synchronous_want
r_volatile
r_int
r_char
id|synchronous_want
(braket
l_int|16
)braket
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|wide_want
r_volatile
r_int
r_char
id|wide_want
(braket
l_int|16
)braket
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Bit fielded set of targets we want to speak synchronously with */
DECL|member|initiate_sdtr
r_volatile
id|u16
id|initiate_sdtr
suffix:semicolon
multiline_comment|/* Bit fielded set of targets we want to speak wide with */
DECL|member|initiate_wdtr
r_volatile
id|u16
id|initiate_wdtr
suffix:semicolon
multiline_comment|/* Bit fielded list of targets we&squot;ve talked to. */
DECL|member|talked_to
r_volatile
id|u16
id|talked_to
suffix:semicolon
multiline_comment|/* Array of bit-fielded lun lists that we need to request_sense */
DECL|member|request_sense
r_volatile
r_int
r_char
id|request_sense
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|addr_reconnect_dsa_head
id|u32
id|addr_reconnect_dsa_head
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* RISCy style constant,&n;&t;&t;&t;&t;&t;&t;   address of following */
DECL|member|reconnect_dsa_head
r_volatile
id|u32
id|reconnect_dsa_head
suffix:semicolon
multiline_comment|/* Data identifying nexus we are trying to match during reselection */
DECL|member|reselected_identify
r_volatile
r_int
r_char
id|reselected_identify
suffix:semicolon
multiline_comment|/* IDENTIFY message */
DECL|member|reselected_tag
r_volatile
r_int
r_char
id|reselected_tag
suffix:semicolon
multiline_comment|/* second byte of queue tag &n;&t;&t;&t;&t;&t;&t;   message or 0 */
multiline_comment|/* These were static variables before we moved them */
DECL|member|NCR53c7xx_zero
id|s32
id|NCR53c7xx_zero
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|member|NCR53c7xx_sink
id|s32
id|NCR53c7xx_sink
suffix:semicolon
DECL|member|NOP_insn
id|u32
id|NOP_insn
suffix:semicolon
DECL|member|NCR53c7xx_msg_reject
r_char
id|NCR53c7xx_msg_reject
suffix:semicolon
DECL|member|NCR53c7xx_msg_abort
r_char
id|NCR53c7xx_msg_abort
suffix:semicolon
DECL|member|NCR53c7xx_msg_nop
r_char
id|NCR53c7xx_msg_nop
suffix:semicolon
multiline_comment|/*&n;     * Following item introduced by RGH to support NCRc710, which is&n;     * VERY brain-dead when it come to memory moves&n;     */
multiline_comment|/* DSA save area used only by the NCR chip */
DECL|member|saved2_dsa
r_volatile
r_int
r_int
id|saved2_dsa
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|member|emulated_intfly
r_volatile
r_int
r_int
id|emulated_intfly
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|member|event_size
DECL|member|event_index
r_volatile
r_int
id|event_size
comma
id|event_index
suffix:semicolon
DECL|member|events
r_volatile
r_struct
id|NCR53c7x0_event
op_star
id|events
suffix:semicolon
multiline_comment|/* If we need to generate code to kill off the currently connected &n;       command, this is where we do it. Should have a BMI instruction&n;       to source or sink the current data, followed by a JUMP&n;       to abort_connected */
DECL|member|abort_script
id|u32
op_star
id|abort_script
suffix:semicolon
DECL|member|script_count
r_int
id|script_count
suffix:semicolon
multiline_comment|/* Size of script in words */
DECL|member|script
id|u32
id|script
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Relocated SCSI script */
)brace
suffix:semicolon
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE&t;255
DECL|macro|DMA_NONE
mdefine_line|#define DMA_NONE&t;255
DECL|macro|IRQ_AUTO
mdefine_line|#define IRQ_AUTO&t;254
DECL|macro|DMA_AUTO
mdefine_line|#define DMA_AUTO&t;254
DECL|macro|BOARD_GENERIC
mdefine_line|#define BOARD_GENERIC&t;0
DECL|macro|NCR53c7x0_insn_size
mdefine_line|#define NCR53c7x0_insn_size(insn)&t;&t;&t;&t;&t;&bslash;&n;    (((insn) &amp; DCMD_TYPE_MASK) == DCMD_TYPE_MMI ? 3 : 2)
DECL|macro|NCR53c7x0_local_declare
mdefine_line|#define NCR53c7x0_local_declare()&t;&t;&t;&t;&t;&bslash;&n;    volatile unsigned char *NCR53c7x0_address_memory;&t;&t;&t;&bslash;&n;    unsigned int NCR53c7x0_address_io;&t;&t;&t;&t;&t;&bslash;&n;    int NCR53c7x0_memory_mapped
DECL|macro|NCR53c7x0_local_setup
mdefine_line|#define NCR53c7x0_local_setup(host)&t;&t;&t;&t;&t;&bslash;&n;    NCR53c7x0_address_memory = (void *) (host)-&gt;base;&t;&t;&t;&bslash;&n;    NCR53c7x0_address_io = (unsigned int) (host)-&gt;io_port;&t;&t;&bslash;&n;    NCR53c7x0_memory_mapped = ((struct NCR53c7x0_hostdata *) &t;&t;&bslash;&n;&t;host-&gt;hostdata[0])-&gt; options &amp; OPTION_MEMORY_MAPPED 
macro_line|#ifdef BIG_ENDIAN
multiline_comment|/* These could be more efficient, given that we are always memory mapped,&n; * but they don&squot;t give the same problems as the write macros, so leave&n; * them. */
macro_line|#ifdef __mc68000__
DECL|macro|NCR53c7x0_read8
mdefine_line|#define NCR53c7x0_read8(address) &t;&t;&t;&t;&t;&bslash;&n;    ((unsigned int)raw_inb((u32)NCR53c7x0_address_memory + ((u32)(address)^3)) )
DECL|macro|NCR53c7x0_read16
mdefine_line|#define NCR53c7x0_read16(address) &t;&t;&t;&t;&t;&bslash;&n;    ((unsigned int)raw_inw((u32)NCR53c7x0_address_memory + ((u32)(address)^2)))
macro_line|#else
DECL|macro|NCR53c7x0_read8
mdefine_line|#define NCR53c7x0_read8(address) &t;&t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int)readb((u32)NCR53c7x0_address_memory + ((u32)(address)^3)) :&t;&bslash;&n;&t;inb(NCR53c7x0_address_io + (address)))
DECL|macro|NCR53c7x0_read16
mdefine_line|#define NCR53c7x0_read16(address) &t;&t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int)readw((u32)NCR53c7x0_address_memory + ((u32)(address)^2)) :&t;&bslash;&n;&t;inw(NCR53c7x0_address_io + (address)))
macro_line|#endif /* mc68000 */
macro_line|#else
DECL|macro|NCR53c7x0_read8
mdefine_line|#define NCR53c7x0_read8(address) &t;&t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int)readb((u32)NCR53c7x0_address_memory + (u32)(address)) :&t;&bslash;&n;&t;inb(NCR53c7x0_address_io + (address)))
DECL|macro|NCR53c7x0_read16
mdefine_line|#define NCR53c7x0_read16(address) &t;&t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int)readw((u32)NCR53c7x0_address_memory + (u32)(address)) :&t;&bslash;&n;&t;inw(NCR53c7x0_address_io + (address)))
macro_line|#endif
macro_line|#ifdef __mc68000__
DECL|macro|NCR53c7x0_read32
mdefine_line|#define NCR53c7x0_read32(address) &t;&t;&t;&t;&t;&bslash;&n;    ((unsigned int) raw_inl((u32)NCR53c7x0_address_memory + (u32)(address)))
macro_line|#else
DECL|macro|NCR53c7x0_read32
mdefine_line|#define NCR53c7x0_read32(address) &t;&t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned int) readl((u32)NCR53c7x0_address_memory + (u32)(address)) : &t;&bslash;&n;&t;inl(NCR53c7x0_address_io + (address)))
macro_line|#endif /* mc68000*/
macro_line|#ifdef BIG_ENDIAN
multiline_comment|/* If we are big-endian, then we are not Intel, so probably don&squot;t have&n; * an i/o map as well as a memory map.  So, let&squot;s assume memory mapped.&n; * Also, I am having terrible problems trying to persuade the compiler&n; * not to lay down code which does a read after write for these macros.&n; * If you remove &squot;volatile&squot; from writeb() and friends it is ok....&n; */
DECL|macro|NCR53c7x0_write8
mdefine_line|#define NCR53c7x0_write8(address,value) &t;&t;&t;&t;&bslash;&n;&t;*(volatile unsigned char *)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;((u32)NCR53c7x0_address_memory + ((u32)(address)^3)) = (value)
DECL|macro|NCR53c7x0_write16
mdefine_line|#define NCR53c7x0_write16(address,value) &t;&t;&t;&t;&bslash;&n;&t;*(volatile unsigned short *)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;((u32)NCR53c7x0_address_memory + ((u32)(address)^2)) = (value)
DECL|macro|NCR53c7x0_write32
mdefine_line|#define NCR53c7x0_write32(address,value) &t;&t;&t;&t;&bslash;&n;&t;*(volatile unsigned long *)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;((u32)NCR53c7x0_address_memory + ((u32)(address))) = (value)
macro_line|#else
DECL|macro|NCR53c7x0_write8
mdefine_line|#define NCR53c7x0_write8(address,value) &t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;     ({writeb((value), (u32)NCR53c7x0_address_memory + (u32)(address)); mb();}) :&t;&bslash;&n;&t;outb((value), NCR53c7x0_address_io + (address)))
DECL|macro|NCR53c7x0_write16
mdefine_line|#define NCR53c7x0_write16(address,value) &t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;     ({writew((value), (u32)NCR53c7x0_address_memory + (u32)(address)); mb();}) :&t;&bslash;&n;&t;outw((value), NCR53c7x0_address_io + (address)))
DECL|macro|NCR53c7x0_write32
mdefine_line|#define NCR53c7x0_write32(address,value) &t;&t;&t;&t;&bslash;&n;    (NCR53c7x0_memory_mapped ? &t;&t;&t;&t;&t;&t;&bslash;&n;     ({writel((value), (u32)NCR53c7x0_address_memory + (u32)(address)); mb();}) :&t;&bslash;&n;&t;outl((value), NCR53c7x0_address_io + (address)))
macro_line|#endif
multiline_comment|/* Patch arbitrary 32 bit words in the script */
DECL|macro|patch_abs_32
mdefine_line|#define patch_abs_32(script, offset, symbol, value)&t;&t;&t;&bslash;&n;    &t;for (i = 0; i &lt; (sizeof (A_##symbol##_used) / sizeof &t;&t;&bslash;&n;    &t;    (u32)); ++i) {&t;&t;&t;&t;&t;&bslash;&n;&t;    (script)[A_##symbol##_used[i] - (offset)] += (value);&t;&bslash;&n;&t;    if (hostdata-&gt;options &amp; OPTION_DEBUG_FIXUP) &t;&t;&bslash;&n;&t;      printk(&quot;scsi%d : %s reference %d at 0x%x in %s is now 0x%x&bslash;n&quot;,&bslash;&n;&t;&t;host-&gt;host_no, #symbol, i, A_##symbol##_used[i] - &t;&bslash;&n;&t;&t;(int)(offset), #script, (script)[A_##symbol##_used[i] -&t;&bslash;&n;&t;&t;(offset)]);&t;&t;&t;&t;&t;&t;&bslash;&n;    &t;}
multiline_comment|/* Patch read/write instruction immediate field */
DECL|macro|patch_abs_rwri_data
mdefine_line|#define patch_abs_rwri_data(script, offset, symbol, value)&t;&t;&bslash;&n;    &t;for (i = 0; i &lt; (sizeof (A_##symbol##_used) / sizeof &t;&t;&bslash;&n;    &t;    (u32)); ++i)&t;&t;&t;&t;&t;&bslash;&n;    &t;    (script)[A_##symbol##_used[i] - (offset)] =&t;&t;&t;&bslash;&n;&t;    &t;((script)[A_##symbol##_used[i] - (offset)] &amp; &t;&t;&bslash;&n;&t;    &t;~DBC_RWRI_IMMEDIATE_MASK) | &t;&t;&t;&t;&bslash;&n;    &t;    &t;(((value) &lt;&lt; DBC_RWRI_IMMEDIATE_SHIFT) &amp;&t;&t;&bslash;&n;&t;&t; DBC_RWRI_IMMEDIATE_MASK)
multiline_comment|/* Patch transfer control instruction data field */
DECL|macro|patch_abs_tci_data
mdefine_line|#define patch_abs_tci_data(script, offset, symbol, value)&t;        &bslash;&n;    &t;for (i = 0; i &lt; (sizeof (A_##symbol##_used) / sizeof &t;&t;&bslash;&n;    &t;    (u32)); ++i)&t;&t;&t;&t;&t;&bslash;&n;    &t;    (script)[A_##symbol##_used[i] - (offset)] =&t;&t;&t;&bslash;&n;&t;    &t;((script)[A_##symbol##_used[i] - (offset)] &amp; &t;&t;&bslash;&n;&t;    &t;~DBC_TCI_DATA_MASK) | &t;&t;&t;&t;&t;&bslash;&n;    &t;    &t;(((value) &lt;&lt; DBC_TCI_DATA_SHIFT) &amp;&t;&t;&t;&bslash;&n;&t;&t; DBC_TCI_DATA_MASK)
multiline_comment|/* Patch field in dsa structure (assignment should be +=?) */
DECL|macro|patch_dsa_32
mdefine_line|#define patch_dsa_32(dsa, symbol, word, value)&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(dsa)[(hostdata-&gt;##symbol - hostdata-&gt;dsa_start) / sizeof(u32)&t;&bslash;&n;&t;    + (word)] = (value);&t;&t;&t;&t;&t;&bslash;&n;&t;if (hostdata-&gt;options &amp; OPTION_DEBUG_DSA)&t;&t;&t;&bslash;&n;&t;    printk(&quot;scsi : dsa %s symbol %s(%d) word %d now 0x%x&bslash;n&quot;,&t;&bslash;&n;&t;&t;#dsa, #symbol, hostdata-&gt;##symbol, &t;&t;&t;&bslash;&n;&t;&t;(word), (u32) (value));&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* Paranoid people could use panic() here. */
DECL|macro|FATAL
mdefine_line|#define FATAL(host) shutdown((host));
macro_line|#endif /* NCR53c710_C */
macro_line|#endif /* NCR53c710_H */
eof
