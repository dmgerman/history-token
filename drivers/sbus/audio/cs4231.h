multiline_comment|/* $Id: cs4231.h,v 1.13 1999/09/21 14:37:27 davem Exp $&n; * drivers/sbus/audio/cs4231.h&n; *&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; * Copyright (C) 1997 Derrick J. Brashear (shadow@dementia.org)&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _CS4231_H_
DECL|macro|_CS4231_H_
mdefine_line|#define _CS4231_H_
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* According to the CS4231A data provided on CS web site and sun&squot;s includes */
DECL|macro|IAR
mdefine_line|#define IAR&t;0x00UL&t;/* Index Address Register */
DECL|macro|IDR
mdefine_line|#define IDR&t;0x04UL&t;/* Index Data Register */
DECL|macro|STAT
mdefine_line|#define STAT&t;0x08UL&t;/* Status Register */
DECL|macro|PIOD
mdefine_line|#define PIOD&t;0x0cUL&t;/* PIO Data Register */
DECL|macro|APCCSR
mdefine_line|#define APCCSR&t;0x10UL&t;/* APC DMA CSR */
DECL|macro|APCCVA
mdefine_line|#define APCCVA&t;0x20UL&t;/* APC Capture DMA Address */
DECL|macro|APCCC
mdefine_line|#define APCCC&t;0x24UL&t;/* APC Capture Count */
DECL|macro|APCCNVA
mdefine_line|#define APCCNVA&t;0x28UL&t;/* APC Capture DMA Next Address */
DECL|macro|APCCNC
mdefine_line|#define APCCNC&t;0x2cUL&t;/* APC Capture Next Count */
DECL|macro|APCPVA
mdefine_line|#define APCPVA&t;0x30UL&t;/* APC Play DMA Address */
DECL|macro|APCPC
mdefine_line|#define APCPC&t;0x34UL&t;/* APC Play Count */
DECL|macro|APCPNVA
mdefine_line|#define APCPNVA&t;0x38UL&t;/* APC Play DMA Next Address */
DECL|macro|APCPNC
mdefine_line|#define APCPNC&t;0x3cUL&t;/* APC Play Next Count */
multiline_comment|/* EBUS DMA Registers */
DECL|macro|EBDMA_CSR
mdefine_line|#define EBDMA_CSR&t;0x00UL&t;/* Control/Status */
DECL|macro|EBDMA_ADDR
mdefine_line|#define EBDMA_ADDR&t;0x04UL&t;/* DMA Address */
DECL|macro|EBDMA_COUNT
mdefine_line|#define EBDMA_COUNT&t;0x08UL&t;/* DMA Count */
multiline_comment|/* Our structure for each chip */
DECL|struct|cs4231_chip
r_struct
id|cs4231_chip
(brace
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
DECL|member|eb2c
r_int
r_int
id|eb2c
suffix:semicolon
DECL|member|eb2p
r_int
r_int
id|eb2p
suffix:semicolon
DECL|member|perchip_info
r_struct
id|audio_info
id|perchip_info
suffix:semicolon
DECL|member|playlen
DECL|member|reclen
r_int
r_int
id|playlen
comma
id|reclen
suffix:semicolon
DECL|member|irq
DECL|member|irq2
DECL|member|nirqs
r_int
id|irq
comma
id|irq2
comma
id|nirqs
suffix:semicolon
DECL|member|regs_size
r_int
r_int
id|regs_size
suffix:semicolon
multiline_comment|/* Keep track of various info */
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* Current buffer that the driver is playing. */
DECL|member|output_ptr
r_volatile
id|__u8
op_star
id|output_ptr
suffix:semicolon
DECL|member|output_size
r_volatile
id|__u32
id|output_size
suffix:semicolon
DECL|member|output_dma_handle
DECL|member|output_next_dma_handle
r_volatile
id|__u32
id|output_dma_handle
comma
id|output_next_dma_handle
suffix:semicolon
DECL|member|output_dma_size
DECL|member|output_next_dma_size
r_volatile
id|__u32
id|output_dma_size
comma
id|output_next_dma_size
suffix:semicolon
multiline_comment|/* Current record buffer. */
DECL|member|input_ptr
r_volatile
id|__u8
op_star
id|input_ptr
suffix:semicolon
DECL|member|input_size
r_volatile
id|__u32
id|input_size
suffix:semicolon
DECL|member|input_dma_handle
DECL|member|input_next_dma_handle
r_volatile
id|__u32
id|input_dma_handle
comma
id|input_next_dma_handle
suffix:semicolon
DECL|member|input_dma_size
DECL|member|input_next_dma_size
r_volatile
id|__u32
id|input_dma_size
comma
id|input_next_dma_size
suffix:semicolon
multiline_comment|/* Number of buffers in the pipe. */
DECL|member|playing_count
r_volatile
id|__u32
id|playing_count
suffix:semicolon
DECL|member|recording_count
r_volatile
id|__u32
id|recording_count
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef EB4231_SUPPORT
DECL|macro|CS4231_READ32
mdefine_line|#define CS4231_READ32(__C, __REG)&t;&t;&bslash;&n;&t;(((__C)-&gt;status &amp; CS_STATUS_IS_EBUS) ?&t;&bslash;&n;&t;readl((__REG)) :&t;&t;&t;&bslash;&n;&t;sbus_readl((__REG)))
DECL|macro|CS4231_READ8
mdefine_line|#define CS4231_READ8(__C, __REG) &bslash;&n;&t;(((__C)-&gt;status &amp; CS_STATUS_IS_EBUS) ?&t;&bslash;&n;&t;readb((__REG)) :&t;&t;&t;&bslash;&n;&t;sbus_readb((__REG)))
DECL|macro|CS4231_WRITE32
mdefine_line|#define CS4231_WRITE32(__C, __REG, __VAL)&t;&bslash;&n;&t;(((__C)-&gt;status &amp; CS_STATUS_IS_EBUS) ?&t;&bslash;&n;         writel((__VAL), (__REG)) :&t;&t;&bslash;&n;         sbus_writel((__VAL), (__REG)))
DECL|macro|CS4231_WRITE8
mdefine_line|#define CS4231_WRITE8(__C, __REG, __VAL)&t;&bslash;&n;&t;(((__C)-&gt;status &amp; CS_STATUS_IS_EBUS) ?&t;&bslash;&n;         writeb((__VAL), (__REG)) :&t;&t;&bslash;&n;         sbus_writeb((__VAL), (__REG)))
macro_line|#else
multiline_comment|/* We can assume all is SBUS in this case. */
DECL|macro|CS4231_READ32
mdefine_line|#define CS4231_READ32(__C, __REG) sbus_readl((__REG))
DECL|macro|CS4231_READ8
mdefine_line|#define CS4231_READ8(__C, __REG) sbus_readb((__REG))
DECL|macro|CS4231_WRITE32
mdefine_line|#define CS4231_WRITE32(__C, __REG, __VAL) sbus_writel((__VAL), (__REG))
DECL|macro|CS4231_WRITE8
mdefine_line|#define CS4231_WRITE8(__C, __REG, __VAL) sbus_writeb((__VAL), (__REG))
macro_line|#endif
multiline_comment|/* Local status bits */
DECL|macro|CS_STATUS_NEED_INIT
mdefine_line|#define CS_STATUS_NEED_INIT 0x01
DECL|macro|CS_STATUS_INIT_ON_CLOSE
mdefine_line|#define CS_STATUS_INIT_ON_CLOSE 0x02
DECL|macro|CS_STATUS_REV_A
mdefine_line|#define CS_STATUS_REV_A 0x04
DECL|macro|CS_STATUS_INTS_ON
mdefine_line|#define CS_STATUS_INTS_ON 0x08
DECL|macro|CS_STATUS_IS_ULTRA
mdefine_line|#define CS_STATUS_IS_ULTRA 0x10
DECL|macro|CS_STATUS_IS_EBUS
mdefine_line|#define CS_STATUS_IS_EBUS 0x20
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT      9000000
DECL|macro|GAIN_SET
mdefine_line|#define GAIN_SET(var, gain)     ((var &amp; ~(0x3f)) | gain)
DECL|macro|RECGAIN_SET
mdefine_line|#define RECGAIN_SET(var, gain)  ((var &amp; ~(0x1f)) | gain)
multiline_comment|/* bits 0-3 set address of register accessed by idr register */
multiline_comment|/* bit 4 allows access to idr registers 16-31 in mode 2 only */
multiline_comment|/* bit 5 if set causes dma transfers to cease if the int bit of status set */
DECL|macro|IAR_AUTOCAL_BEGIN
mdefine_line|#define IAR_AUTOCAL_BEGIN       0x40    /* MCE */
DECL|macro|IAR_NOT_READY
mdefine_line|#define IAR_NOT_READY           0x80    /* INIT */
DECL|macro|IAR_AUTOCAL_END
mdefine_line|#define IAR_AUTOCAL_END         ~(IAR_AUTOCAL_BEGIN) /* MCD */
multiline_comment|/* Registers 1-15 modes 1 and 2. Registers 16-31 mode 2 only */
multiline_comment|/* Registers assumed to be same in both modes unless noted */
multiline_comment|/* 0 - Left Input Control */
multiline_comment|/* 1 - Right Input Control */
DECL|macro|MIC_ENABLE
mdefine_line|#define MIC_ENABLE(var)         ((var &amp; 0x2f) | 0x80)
DECL|macro|LINE_ENABLE
mdefine_line|#define LINE_ENABLE(var)        (var &amp; 0x2f)
DECL|macro|CDROM_ENABLE
mdefine_line|#define CDROM_ENABLE(var)       ((var &amp; 0x2f) | 0x40)
DECL|macro|OUTPUTLOOP_ENABLE
mdefine_line|#define OUTPUTLOOP_ENABLE(var)  ((var &amp; 0x2f) | 0xC0)
DECL|macro|INPUTCR_AUX1
mdefine_line|#define INPUTCR_AUX1            0x40
multiline_comment|/* 2 - Left Aux 1 Input Control */
multiline_comment|/* 3 - Right Aux 1 Input Control */
multiline_comment|/* 4 - Left Aux 2 Input Control */
multiline_comment|/* 5 - Right Aux 2 Input Control */
multiline_comment|/* 6 - Left Output Control */
multiline_comment|/* 7 - Right Output Control */
DECL|macro|OUTCR_MUTE
mdefine_line|#define OUTCR_MUTE              0x80
DECL|macro|OUTCR_UNMUTE
mdefine_line|#define OUTCR_UNMUTE            ~0x80
multiline_comment|/* 8 - Playback Data Format (Mode 2) */
DECL|macro|CHANGE_DFR
mdefine_line|#define CHANGE_DFR(var, val)            ((var &amp; ~(0xF)) | val)
DECL|macro|CHANGE_ENCODING
mdefine_line|#define CHANGE_ENCODING(var, val)       ((var &amp; ~(0xe0)) | val)
DECL|macro|DEFAULT_DATA_FMAT
mdefine_line|#define DEFAULT_DATA_FMAT               CS4231_DFR_ULAW
DECL|macro|CS4231_DFR_5512
mdefine_line|#define CS4231_DFR_5512                 0x01
DECL|macro|CS4231_DFR_6615
mdefine_line|#define CS4231_DFR_6615                 0x0f
DECL|macro|CS4231_DFR_8000
mdefine_line|#define CS4231_DFR_8000                 0x00
DECL|macro|CS4231_DFR_9600
mdefine_line|#define CS4231_DFR_9600                 0x0e
DECL|macro|CS4231_DFR_11025
mdefine_line|#define CS4231_DFR_11025                0x03
DECL|macro|CS4231_DFR_16000
mdefine_line|#define CS4231_DFR_16000                0x02
DECL|macro|CS4231_DFR_18900
mdefine_line|#define CS4231_DFR_18900                0x05
DECL|macro|CS4231_DFR_22050
mdefine_line|#define CS4231_DFR_22050                0x07
DECL|macro|CS4231_DFR_27429
mdefine_line|#define CS4231_DFR_27429                0x04
DECL|macro|CS4231_DFR_32000
mdefine_line|#define CS4231_DFR_32000                0x06
DECL|macro|CS4231_DFR_33075
mdefine_line|#define CS4231_DFR_33075                0x0d
DECL|macro|CS4231_DFR_37800
mdefine_line|#define CS4231_DFR_37800                0x09
DECL|macro|CS4231_DFR_44100
mdefine_line|#define CS4231_DFR_44100                0x0b
DECL|macro|CS4231_DFR_48000
mdefine_line|#define CS4231_DFR_48000                0x0c
DECL|macro|CS4231_DFR_LINEAR8
mdefine_line|#define CS4231_DFR_LINEAR8              0x00
DECL|macro|CS4231_DFR_ULAW
mdefine_line|#define CS4231_DFR_ULAW                 0x20
DECL|macro|CS4231_DFR_LINEARLE
mdefine_line|#define CS4231_DFR_LINEARLE             0x40
DECL|macro|CS4231_DFR_ALAW
mdefine_line|#define CS4231_DFR_ALAW                 0x60
DECL|macro|CS4231_DFR_ADPCM
mdefine_line|#define CS4231_DFR_ADPCM                0xa0 /* N/A in mode 1 */
DECL|macro|CS4231_DFR_LINEARBE
mdefine_line|#define CS4231_DFR_LINEARBE             0xc0 /* N/A in mode 1 */
DECL|macro|CS4231_STEREO_ON
mdefine_line|#define CS4231_STEREO_ON(val)           (val | 0x10)
DECL|macro|CS4231_MONO_ON
mdefine_line|#define CS4231_MONO_ON(val)             (val &amp; ~0x10)
multiline_comment|/* 9 - Interface Config. Register */
DECL|macro|PEN_ENABLE
mdefine_line|#define PEN_ENABLE              (0x01) /* Playback Enable */
DECL|macro|PEN_DISABLE
mdefine_line|#define PEN_DISABLE             (~0x01)
DECL|macro|CEN_ENABLE
mdefine_line|#define CEN_ENABLE              (0x02) /* Capture Enable */
DECL|macro|CEN_DISABLE
mdefine_line|#define CEN_DISABLE             (~0x02)
DECL|macro|SDC_ENABLE
mdefine_line|#define SDC_ENABLE              (0x04) /* Turn on single DMA Channel mode */
DECL|macro|ACAL_CONV
mdefine_line|#define ACAL_CONV               0x08   /* Turn on converter autocal */
DECL|macro|ACAL_DISABLE
mdefine_line|#define ACAL_DISABLE            (~0x08) 
DECL|macro|ACAL_DAC
mdefine_line|#define ACAL_DAC                0x10  /* Turn on DAC autocal */
DECL|macro|ACAL_FULL
mdefine_line|#define ACAL_FULL               (ACAL_DAC|ACAL_CONV) /* Turn on full autocal */
DECL|macro|PPIO
mdefine_line|#define PPIO                    0x20 /* do playback via PIO rather than DMA */
DECL|macro|CPIO
mdefine_line|#define CPIO                    0x40 /* do capture via PIO rather than DMA */
DECL|macro|ICR_AUTOCAL_INIT
mdefine_line|#define ICR_AUTOCAL_INIT        0x01
multiline_comment|/* 10 - Pin Control Register */
DECL|macro|INTR_ON
mdefine_line|#define INTR_ON                 0x82
DECL|macro|INTR_OFF
mdefine_line|#define INTR_OFF                0x80
DECL|macro|PINCR_LINE_MUTE
mdefine_line|#define PINCR_LINE_MUTE         0x40
DECL|macro|PINCR_HDPH_MUTE
mdefine_line|#define PINCR_HDPH_MUTE         0x80
multiline_comment|/* 11 - Test/Initialization */
DECL|macro|DRQ_STAT
mdefine_line|#define DRQ_STAT                0x10
DECL|macro|AUTOCAL_IN_PROGRESS
mdefine_line|#define AUTOCAL_IN_PROGRESS      0x20
multiline_comment|/* 12 - Misc Information */
DECL|macro|MISC_IR_MODE2
mdefine_line|#define MISC_IR_MODE2           0x40
multiline_comment|/* 13 - Loopback Control */
DECL|macro|LOOPB_ON
mdefine_line|#define LOOPB_ON                0x01
DECL|macro|LOOPB_OFF
mdefine_line|#define LOOPB_OFF               0x00
multiline_comment|/* 14 - shared play/capture upper (mode 1) */
multiline_comment|/* 15 - shared play/capture lower (mode 1) */
multiline_comment|/* 14 - Playback Upper (mode 2) */
multiline_comment|/* 15 - Playback Lower (mode 2) */
multiline_comment|/* The rest are mode 2 only */
multiline_comment|/* 16 - Alternate Feature 1 Enable */
DECL|macro|DAC_ZERO
mdefine_line|#define DAC_ZERO                0x01
DECL|macro|PLAY_MCE
mdefine_line|#define PLAY_MCE                0x10
DECL|macro|CAPTURE_MCE
mdefine_line|#define CAPTURE_MCE             0x20
DECL|macro|TIMER_ENABLE
mdefine_line|#define TIMER_ENABLE            0x40
DECL|macro|OLB_ENABLE
mdefine_line|#define OLB_ENABLE              0x80 /* go to 2.88 vpp analog output */
multiline_comment|/* 17 - Alternate Feature 2 Enable */
DECL|macro|HPF_ON
mdefine_line|#define HPF_ON                  0x01 /* High Pass Filter */
DECL|macro|XTALE_ON
mdefine_line|#define XTALE_ON                0x02 /* Enable both crystals */
DECL|macro|APAR_OFF
mdefine_line|#define APAR_OFF                0x04 /* ADPCM playback accum reset */
multiline_comment|/* 18 - Left Line Input Gain */
multiline_comment|/* 19 - Right Line Input Gain */
multiline_comment|/* 20 - Timer High */
multiline_comment|/* 21 - Timer Low */
multiline_comment|/* 22 - unused */
multiline_comment|/* 23 - Alt. Fea. Ena 3 */
DECL|macro|ACF
mdefine_line|#define ACF 0x01
multiline_comment|/* 24 - Alternate Feature Status */
DECL|macro|CS_PU
mdefine_line|#define CS_PU                   0x01 /* Underrun */
DECL|macro|CS_PO
mdefine_line|#define CS_PO                   0x02 /* Overrun */
DECL|macro|CS_CU
mdefine_line|#define CS_CU                   0x04 /* Underrun */
DECL|macro|CS_CO
mdefine_line|#define CS_CO                   0x08 /* Overrun */
DECL|macro|CS_PI
mdefine_line|#define CS_PI                   0x10 
DECL|macro|CS_CI
mdefine_line|#define CS_CI                   0x20 
DECL|macro|CS_TI
mdefine_line|#define CS_TI                   0x40 
multiline_comment|/* 25 - Version */
DECL|macro|CS4231A
mdefine_line|#define CS4231A         0x20
DECL|macro|CS4231CDE
mdefine_line|#define CS4231CDE       0x80
multiline_comment|/* 26 - Mono I/O Control */
DECL|macro|CHANGE_MONO_GAIN
mdefine_line|#define CHANGE_MONO_GAIN(val)   ((val &amp; ~(0xFF)) | val)
DECL|macro|MONO_IOCR_BYPASS
mdefine_line|#define MONO_IOCR_BYPASS     0x20 
DECL|macro|MONO_IOCR_MUTE
mdefine_line|#define MONO_IOCR_MUTE       0x40
DECL|macro|MONO_IOCR_INMUTE
mdefine_line|#define MONO_IOCR_INMUTE     0x80
multiline_comment|/* 27 - Unused */
multiline_comment|/* 28 - Capture Data Format */
multiline_comment|/* see register 8 */
multiline_comment|/* 29 - Unused */
multiline_comment|/* 30 - Capture Upper */
multiline_comment|/* 31 - Capture Lower */
multiline_comment|/* Following are APC CSR register definitions for the Sparc */
DECL|macro|APC_INT_PENDING
mdefine_line|#define APC_INT_PENDING 0x800000 /* Interrupt Pending */
DECL|macro|APC_PLAY_INT
mdefine_line|#define APC_PLAY_INT    0x400000 /* Playback interrupt */
DECL|macro|APC_CAPT_INT
mdefine_line|#define APC_CAPT_INT    0x200000 /* Capture interrupt */
DECL|macro|APC_GENL_INT
mdefine_line|#define APC_GENL_INT    0x100000 /* General interrupt */
DECL|macro|APC_XINT_ENA
mdefine_line|#define APC_XINT_ENA    0x80000  /* General ext int. enable */
DECL|macro|APC_XINT_PLAY
mdefine_line|#define APC_XINT_PLAY   0x40000  /* Playback ext intr */
DECL|macro|APC_XINT_CAPT
mdefine_line|#define APC_XINT_CAPT   0x20000  /* Capture ext intr */
DECL|macro|APC_XINT_GENL
mdefine_line|#define APC_XINT_GENL   0x10000  /* Error ext intr */
DECL|macro|APC_XINT_EMPT
mdefine_line|#define APC_XINT_EMPT   0x8000   /* Pipe empty interrupt (0 write to pva) */
DECL|macro|APC_XINT_PEMP
mdefine_line|#define APC_XINT_PEMP   0x4000   /* Play pipe empty (pva and pnva not set) */
DECL|macro|APC_XINT_PNVA
mdefine_line|#define APC_XINT_PNVA   0x2000   /* Playback NVA dirty */
DECL|macro|APC_XINT_PENA
mdefine_line|#define APC_XINT_PENA   0x1000   /* play pipe empty Int enable */
DECL|macro|APC_XINT_COVF
mdefine_line|#define APC_XINT_COVF   0x800    /* Cap data dropped on floor */
DECL|macro|APC_XINT_CNVA
mdefine_line|#define APC_XINT_CNVA   0x400    /* Capture NVA dirty */
DECL|macro|APC_XINT_CEMP
mdefine_line|#define APC_XINT_CEMP   0x200    /* Capture pipe empty (cva and cnva not set) */
DECL|macro|APC_XINT_CENA
mdefine_line|#define APC_XINT_CENA   0x100    /* Cap. pipe empty int enable */
DECL|macro|APC_PPAUSE
mdefine_line|#define APC_PPAUSE      0x80     /* Pause the play DMA */
DECL|macro|APC_CPAUSE
mdefine_line|#define APC_CPAUSE      0x40     /* Pause the capture DMA */
DECL|macro|APC_CDC_RESET
mdefine_line|#define APC_CDC_RESET   0x20     /* CODEC RESET */
DECL|macro|APC_PDMA_READY
mdefine_line|#define APC_PDMA_READY  0x08     /* Play DMA Go */
DECL|macro|APC_CDMA_READY
mdefine_line|#define APC_CDMA_READY  0x04     /* Capture DMA Go */
DECL|macro|APC_CHIP_RESET
mdefine_line|#define APC_CHIP_RESET  0x01     /* Reset the chip */
DECL|macro|APC_INIT_SETUP
mdefine_line|#define APC_INIT_SETUP  (APC_CDMA_READY | APC_PDMA_READY | APC_XINT_ENA | &bslash;&n;&t;&t;&t; APC_XINT_PLAY | APC_XINT_GENL | APC_INT_PENDING | &bslash;&n;&t;&t;&t; APC_PLAY_INT | APC_CAPT_INT | APC_GENL_INT) 
DECL|macro|APC_PLAY_SETUP
mdefine_line|#define APC_PLAY_SETUP  (APC_GENL_INT | APC_PLAY_INT | APC_XINT_ENA | &bslash;&n;&t;&t;&t; APC_XINT_PLAY | APC_XINT_EMPT | APC_XINT_GENL | &bslash;&n;&t;&t;&t; APC_XINT_PENA | APC_PDMA_READY)
DECL|macro|APC_CAPT_SETUP
mdefine_line|#define APC_CAPT_SETUP  (APC_GENL_INT | APC_CAPT_INT | APC_XINT_ENA | &bslash;&n;&t;&t;&t; APC_XINT_CAPT | APC_XINT_CEMP | APC_XINT_GENL | &bslash;&n;&t;&t;&t; APC_CDMA_READY)
multiline_comment|/* Following are EB2 CSR register definitions for the Sparc */
multiline_comment|/* asm/ebus.h has the base settings */
DECL|macro|EB2_PLAY_SETUP
mdefine_line|#define EB2_PLAY_SETUP (EBUS_DCSR_BURST_SZ_8 | EBUS_DCSR_INT_EN | EBUS_DCSR_EN_DMA | &bslash;&n;&t;&t;&t;EBUS_DCSR_EN_CNT | EBUS_DCSR_TC)
DECL|macro|EB2_CAPT_SETUP
mdefine_line|#define EB2_CAPT_SETUP (EBUS_DCSR_BURST_SZ_8 | EBUS_DCSR_INT_EN | EBUS_DCSR_EN_DMA| &bslash;&n;&t;&t;&t;EBUS_DCSR_EN_CNT | EBUS_DCSR_TC | EBUS_DCSR_WRITE)
DECL|macro|CS4231_MIN_ATEN
mdefine_line|#define CS4231_MIN_ATEN     (0)
DECL|macro|CS4231_MAX_ATEN
mdefine_line|#define CS4231_MAX_ATEN     (31)
DECL|macro|CS4231_MAX_DEV_ATEN
mdefine_line|#define CS4231_MAX_DEV_ATEN (63)
DECL|macro|CS4231_MON_MIN_ATEN
mdefine_line|#define CS4231_MON_MIN_ATEN         (0)
DECL|macro|CS4231_MON_MAX_ATEN
mdefine_line|#define CS4231_MON_MAX_ATEN         (63)
DECL|macro|CS4231_DEFAULT_PLAYGAIN
mdefine_line|#define CS4231_DEFAULT_PLAYGAIN     (132)
DECL|macro|CS4231_DEFAULT_RECGAIN
mdefine_line|#define CS4231_DEFAULT_RECGAIN      (126)
DECL|macro|CS4231_MIN_GAIN
mdefine_line|#define CS4231_MIN_GAIN     (0)
DECL|macro|CS4231_MAX_GAIN
mdefine_line|#define CS4231_MAX_GAIN     (15)
DECL|macro|CS4231_PRECISION
mdefine_line|#define CS4231_PRECISION    (8)             /* # of bits/sample */
DECL|macro|CS4231_CHANNELS
mdefine_line|#define CS4231_CHANNELS     (1)             /* channels/sample */
DECL|macro|CS4231_RATE
mdefine_line|#define CS4231_RATE   (8000)                /* default sample rate */
macro_line|#endif /* _CS4231_H_ */
eof
