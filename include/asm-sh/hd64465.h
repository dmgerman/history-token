macro_line|#ifndef _ASM_SH_HD64465_
DECL|macro|_ASM_SH_HD64465_
mdefine_line|#define _ASM_SH_HD64465_ 1
multiline_comment|/*&n; * $Id: hd64465.h,v 1.3 2001/02/07 18:31:20 stuart_menefy Exp $&n; *&n; * Hitachi HD64465 companion chip support&n; *&n; * by Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * (c) 2000 PocketPenguins Inc.&n; *&n; * Derived from &lt;asm/hd64461.h&gt; which bore the message:&n; * Copyright (C) 2000 YAEGASHI Takeshi&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Note that registers are defined here as virtual port numbers,&n; * which have no meaning except to get translated by hd64465_isa_port2addr()&n; * to an address in the range 0xb0000000-0xb3ffffff.  Note that&n; * this translation happens to consist of adding the lower 16 bits&n; * of the virtual port number to 0xb0000000.  Note also that the manual&n; * shows addresses as absolute physical addresses starting at 0x10000000,&n; * so e.g. the NIRR register is listed as 0x15000 here, 0x10005000 in the&n; * manual, and accessed using address 0xb0005000 - Greg.&n; */
multiline_comment|/* System registers */
DECL|macro|HD64465_REG_SRR
mdefine_line|#define HD64465_REG_SRR     0x1000c &t;/* System Revision Register */
DECL|macro|HD64465_REG_SDID
mdefine_line|#define HD64465_REG_SDID    0x10010 &t;/* System Device ID Reg */
DECL|macro|HD64465_SDID
mdefine_line|#define     HD64465_SDID            0x8122  /* 64465 device ID */
multiline_comment|/* Power Management registers */
DECL|macro|HD64465_REG_SMSCR
mdefine_line|#define HD64465_REG_SMSCR   0x10000 &t;/* System Module Standby Control Reg */
DECL|macro|HD64465_SMSCR_PS2ST
mdefine_line|#define&t;    HD64465_SMSCR_PS2ST     0x4000  /* PS/2 Standby */
DECL|macro|HD64465_SMSCR_ADCST
mdefine_line|#define&t;    HD64465_SMSCR_ADCST     0x1000  /* ADC Standby */
DECL|macro|HD64465_SMSCR_UARTST
mdefine_line|#define&t;    HD64465_SMSCR_UARTST    0x0800  /* UART Standby */
DECL|macro|HD64465_SMSCR_SCDIST
mdefine_line|#define&t;    HD64465_SMSCR_SCDIST    0x0200  /* Serial Codec Standby */
DECL|macro|HD64465_SMSCR_PPST
mdefine_line|#define&t;    HD64465_SMSCR_PPST&t;    0x0100  /* Parallel Port Standby */
DECL|macro|HD64465_SMSCR_PC0ST
mdefine_line|#define&t;    HD64465_SMSCR_PC0ST     0x0040  /* PCMCIA0 Standby */
DECL|macro|HD64465_SMSCR_PC1ST
mdefine_line|#define&t;    HD64465_SMSCR_PC1ST     0x0020  /* PCMCIA1 Standby */
DECL|macro|HD64465_SMSCR_AFEST
mdefine_line|#define&t;    HD64465_SMSCR_AFEST     0x0010  /* AFE Standby */
DECL|macro|HD64465_SMSCR_TM0ST
mdefine_line|#define&t;    HD64465_SMSCR_TM0ST     0x0008  /* Timer0 Standby */
DECL|macro|HD64465_SMSCR_TM1ST
mdefine_line|#define&t;    HD64465_SMSCR_TM1ST     0x0004  /* Timer1 Standby */
DECL|macro|HD64465_SMSCR_IRDAST
mdefine_line|#define&t;    HD64465_SMSCR_IRDAST    0x0002  /* IRDA Standby */
DECL|macro|HD64465_SMSCR_KBCST
mdefine_line|#define&t;    HD64465_SMSCR_KBCST     0x0001  /* Keyboard Controller Standby */
multiline_comment|/* Interrupt Controller registers */
DECL|macro|HD64465_REG_NIRR
mdefine_line|#define HD64465_REG_NIRR    0x15000  &t;/* Interrupt Request Register */
DECL|macro|HD64465_REG_NIMR
mdefine_line|#define HD64465_REG_NIMR    0x15002  &t;/* Interrupt Mask Register */
DECL|macro|HD64465_REG_NITR
mdefine_line|#define HD64465_REG_NITR    0x15004  &t;/* Interrupt Trigger Mode Register */
multiline_comment|/* Timer registers */
DECL|macro|HD64465_REG_TCVR1
mdefine_line|#define HD64465_REG_TCVR1   0x16000  &t;/* Timer 1 constant value register  */
DECL|macro|HD64465_REG_TCVR0
mdefine_line|#define HD64465_REG_TCVR0   0x16002&t;/* Timer 0 constant value register  */
DECL|macro|HD64465_REG_TRVR1
mdefine_line|#define HD64465_REG_TRVR1   0x16004&t;/* Timer 1 read value register  */
DECL|macro|HD64465_REG_TRVR0
mdefine_line|#define HD64465_REG_TRVR0   0x16006&t;/* Timer 0 read value register  */
DECL|macro|HD64465_REG_TCR1
mdefine_line|#define HD64465_REG_TCR1    0x16008&t;/* Timer 1 control register  */
DECL|macro|HD64465_REG_TCR0
mdefine_line|#define HD64465_REG_TCR0    0x1600A&t;/* Timer 0 control register  */
DECL|macro|HD64465_TCR_EADT
mdefine_line|#define&t;    HD64465_TCR_EADT &t;0x10&t;    /* Enable ADTRIG# signal */
DECL|macro|HD64465_TCR_ETMO
mdefine_line|#define&t;    HD64465_TCR_ETMO &t;0x08&t;    /* Enable TMO signal */
DECL|macro|HD64465_TCR_PST_MASK
mdefine_line|#define&t;    HD64465_TCR_PST_MASK 0x06&t;    /* Clock Prescale */
DECL|macro|HD64465_TCR_PST_1
mdefine_line|#define&t;    HD64465_TCR_PST_1 &t;0x06&t;    /* 1:1 */
DECL|macro|HD64465_TCR_PST_4
mdefine_line|#define&t;    HD64465_TCR_PST_4 &t;0x04&t;    /* 1:4 */
DECL|macro|HD64465_TCR_PST_8
mdefine_line|#define&t;    HD64465_TCR_PST_8 &t;0x02&t;    /* 1:8 */
DECL|macro|HD64465_TCR_PST_16
mdefine_line|#define&t;    HD64465_TCR_PST_16 &t;0x00&t;    /* 1:16 */
DECL|macro|HD64465_TCR_TSTP
mdefine_line|#define&t;    HD64465_TCR_TSTP &t;0x01&t;    /* Start/Stop timer */
DECL|macro|HD64465_REG_TIRR
mdefine_line|#define HD64465_REG_TIRR    0x1600C&t;/* Timer interrupt request register  */
DECL|macro|HD64465_REG_TIDR
mdefine_line|#define HD64465_REG_TIDR    0x1600E&t;/* Timer interrupt disable register  */
DECL|macro|HD64465_REG_PWM1CS
mdefine_line|#define HD64465_REG_PWM1CS  0x16010&t;/* PWM 1 clock scale register  */
DECL|macro|HD64465_REG_PWM1LPC
mdefine_line|#define HD64465_REG_PWM1LPC 0x16012&t;/* PWM 1 low pulse width counter register  */
DECL|macro|HD64465_REG_PWM1HPC
mdefine_line|#define HD64465_REG_PWM1HPC 0x16014&t;/* PWM 1 high pulse width counter register  */
DECL|macro|HD64465_REG_PWM0CS
mdefine_line|#define HD64465_REG_PWM0CS  0x16018&t;/* PWM 0 clock scale register  */
DECL|macro|HD64465_REG_PWM0LPC
mdefine_line|#define HD64465_REG_PWM0LPC 0x1601A&t;/* PWM 0 low pulse width counter register  */
DECL|macro|HD64465_REG_PWM0HPC
mdefine_line|#define HD64465_REG_PWM0HPC 0x1601C&t;/* PWM 0 high pulse width counter register  */
multiline_comment|/* Analog/Digital Converter registers */
DECL|macro|HD64465_REG_ADDRA
mdefine_line|#define HD64465_REG_ADDRA   0x1E000&t;/* A/D data register A */
DECL|macro|HD64465_REG_ADDRB
mdefine_line|#define HD64465_REG_ADDRB   0x1E002&t;/* A/D data register B */
DECL|macro|HD64465_REG_ADDRC
mdefine_line|#define HD64465_REG_ADDRC   0x1E004&t;/* A/D data register C */
DECL|macro|HD64465_REG_ADDRD
mdefine_line|#define HD64465_REG_ADDRD   0x1E006&t;/* A/D data register D */
DECL|macro|HD64465_REG_ADCSR
mdefine_line|#define HD64465_REG_ADCSR   0x1E008&t;/* A/D control/status register */
DECL|macro|HD64465_ADCSR_ADF
mdefine_line|#define     HD64465_ADCSR_ADF&t;    0x80    /* A/D End Flag */
DECL|macro|HD64465_ADCSR_ADST
mdefine_line|#define     HD64465_ADCSR_ADST&t;    0x40    /* A/D Start Flag */
DECL|macro|HD64465_ADCSR_ADIS
mdefine_line|#define     HD64465_ADCSR_ADIS&t;    0x20    /* A/D Interrupt Status */
DECL|macro|HD64465_ADCSR_TRGE
mdefine_line|#define     HD64465_ADCSR_TRGE&t;    0x10    /* A/D Trigger Enable */
DECL|macro|HD64465_ADCSR_ADIE
mdefine_line|#define     HD64465_ADCSR_ADIE&t;    0x08    /* A/D Interrupt Enable */
DECL|macro|HD64465_ADCSR_SCAN
mdefine_line|#define     HD64465_ADCSR_SCAN&t;    0x04    /* A/D Scan Mode */
DECL|macro|HD64465_ADCSR_CH_MASK
mdefine_line|#define     HD64465_ADCSR_CH_MASK   0x03    /* A/D Channel */
DECL|macro|HD64465_REG_ADCALCR
mdefine_line|#define HD64465_REG_ADCALCR 0x1E00A  &t;/* A/D calibration sample control */
DECL|macro|HD64465_REG_ADCAL
mdefine_line|#define HD64465_REG_ADCAL   0x1E00C  &t;/* A/D calibration data register */
multiline_comment|/* General Purpose I/O ports registers */
DECL|macro|HD64465_REG_GPACR
mdefine_line|#define HD64465_REG_GPACR   0x14000  &t;/* Port A Control Register */
DECL|macro|HD64465_REG_GPBCR
mdefine_line|#define HD64465_REG_GPBCR   0x14002  &t;/* Port B Control Register */
DECL|macro|HD64465_REG_GPCCR
mdefine_line|#define HD64465_REG_GPCCR   0x14004  &t;/* Port C Control Register */
DECL|macro|HD64465_REG_GPDCR
mdefine_line|#define HD64465_REG_GPDCR   0x14006  &t;/* Port D Control Register */
DECL|macro|HD64465_REG_GPECR
mdefine_line|#define HD64465_REG_GPECR   0x14008  &t;/* Port E Control Register */
DECL|macro|HD64465_REG_GPADR
mdefine_line|#define HD64465_REG_GPADR   0x14010  &t;/* Port A Data Register */
DECL|macro|HD64465_REG_GPBDR
mdefine_line|#define HD64465_REG_GPBDR   0x14012  &t;/* Port B Data Register */
DECL|macro|HD64465_REG_GPCDR
mdefine_line|#define HD64465_REG_GPCDR   0x14014  &t;/* Port C Data Register */
DECL|macro|HD64465_REG_GPDDR
mdefine_line|#define HD64465_REG_GPDDR   0x14016  &t;/* Port D Data Register */
DECL|macro|HD64465_REG_GPEDR
mdefine_line|#define HD64465_REG_GPEDR   0x14018  &t;/* Port E Data Register */
DECL|macro|HD64465_REG_GPAICR
mdefine_line|#define HD64465_REG_GPAICR  0x14020  &t;/* Port A Interrupt Control Register */
DECL|macro|HD64465_REG_GPBICR
mdefine_line|#define HD64465_REG_GPBICR  0x14022  &t;/* Port B Interrupt Control Register */
DECL|macro|HD64465_REG_GPCICR
mdefine_line|#define HD64465_REG_GPCICR  0x14024  &t;/* Port C Interrupt Control Register */
DECL|macro|HD64465_REG_GPDICR
mdefine_line|#define HD64465_REG_GPDICR  0x14026  &t;/* Port D Interrupt Control Register */
DECL|macro|HD64465_REG_GPEICR
mdefine_line|#define HD64465_REG_GPEICR  0x14028  &t;/* Port E Interrupt Control Register */
DECL|macro|HD64465_REG_GPAISR
mdefine_line|#define HD64465_REG_GPAISR  0x14040  &t;/* Port A Interrupt Status Register */
DECL|macro|HD64465_REG_GPBISR
mdefine_line|#define HD64465_REG_GPBISR  0x14042  &t;/* Port B Interrupt Status Register */
DECL|macro|HD64465_REG_GPCISR
mdefine_line|#define HD64465_REG_GPCISR  0x14044  &t;/* Port C Interrupt Status Register */
DECL|macro|HD64465_REG_GPDISR
mdefine_line|#define HD64465_REG_GPDISR  0x14046  &t;/* Port D Interrupt Status Register */
DECL|macro|HD64465_REG_GPEISR
mdefine_line|#define HD64465_REG_GPEISR  0x14048  &t;/* Port E Interrupt Status Register */
multiline_comment|/* PCMCIA bridge interface */
DECL|macro|HD64465_REG_PCC0ISR
mdefine_line|#define HD64465_REG_PCC0ISR&t;0x12000&t;/* socket 0 interface status */ 
DECL|macro|HD64465_PCCISR_PREADY
mdefine_line|#define     HD64465_PCCISR_PREADY   &t; 0x80    /* mem card ready / io card IREQ */
DECL|macro|HD64465_PCCISR_PIREQ
mdefine_line|#define     HD64465_PCCISR_PIREQ    &t; 0x80
DECL|macro|HD64465_PCCISR_PMWP
mdefine_line|#define     HD64465_PCCISR_PMWP     &t; 0x40    /* mem card write-protected */
DECL|macro|HD64465_PCCISR_PVS2
mdefine_line|#define     HD64465_PCCISR_PVS2 &t; 0x20    /* voltage select pin 2 */
DECL|macro|HD64465_PCCISR_PVS1
mdefine_line|#define     HD64465_PCCISR_PVS1 &t; 0x10    /* voltage select pin 1 */
DECL|macro|HD64465_PCCISR_PCD_MASK
mdefine_line|#define     HD64465_PCCISR_PCD_MASK &t; 0x0c    /* card detect */
DECL|macro|HD64465_PCCISR_PBVD_MASK
mdefine_line|#define     HD64465_PCCISR_PBVD_MASK     0x03    /* battery voltage */
DECL|macro|HD64465_PCCISR_PBVD_BATGOOD
mdefine_line|#define     HD64465_PCCISR_PBVD_BATGOOD  0x03    /* battery good */
DECL|macro|HD64465_PCCISR_PBVD_BATWARN
mdefine_line|#define     HD64465_PCCISR_PBVD_BATWARN  0x01    /* battery low warning */
DECL|macro|HD64465_PCCISR_PBVD_BATDEAD1
mdefine_line|#define     HD64465_PCCISR_PBVD_BATDEAD1 0x02    /* battery dead */
DECL|macro|HD64465_PCCISR_PBVD_BATDEAD2
mdefine_line|#define     HD64465_PCCISR_PBVD_BATDEAD2 0x00    /* battery dead */
DECL|macro|HD64465_REG_PCC0GCR
mdefine_line|#define HD64465_REG_PCC0GCR&t;0x12002&t;/* socket 0 general control */ 
DECL|macro|HD64465_PCCGCR_PDRV
mdefine_line|#define     HD64465_PCCGCR_PDRV   &t; 0x80    /* output drive */
DECL|macro|HD64465_PCCGCR_PCCR
mdefine_line|#define     HD64465_PCCGCR_PCCR   &t; 0x40    /* PC card reset */
DECL|macro|HD64465_PCCGCR_PCCT
mdefine_line|#define     HD64465_PCCGCR_PCCT   &t; 0x20    /* PC card type, 1=IO&amp;mem, 0=mem */
DECL|macro|HD64465_PCCGCR_PVCC0
mdefine_line|#define     HD64465_PCCGCR_PVCC0   &t; 0x10    /* voltage control pin VCC0SEL0 */
DECL|macro|HD64465_PCCGCR_PMMOD
mdefine_line|#define     HD64465_PCCGCR_PMMOD   &t; 0x08    /* memory mode */
DECL|macro|HD64465_PCCGCR_PPA25
mdefine_line|#define     HD64465_PCCGCR_PPA25   &t; 0x04    /* pin A25 */
DECL|macro|HD64465_PCCGCR_PPA24
mdefine_line|#define     HD64465_PCCGCR_PPA24   &t; 0x02    /* pin A24 */
DECL|macro|HD64465_PCCGCR_PREG
mdefine_line|#define     HD64465_PCCGCR_PREG   &t; 0x01    /* ping PCC0REG# */
DECL|macro|HD64465_REG_PCC0CSCR
mdefine_line|#define HD64465_REG_PCC0CSCR&t;0x12004&t;/* socket 0 card status change */ 
DECL|macro|HD64465_PCCCSCR_PSCDI
mdefine_line|#define     HD64465_PCCCSCR_PSCDI   &t; 0x80    /* sw card detect intr */
DECL|macro|HD64465_PCCCSCR_PSWSEL
mdefine_line|#define     HD64465_PCCCSCR_PSWSEL   &t; 0x40    /* power select */
DECL|macro|HD64465_PCCCSCR_PIREQ
mdefine_line|#define     HD64465_PCCCSCR_PIREQ   &t; 0x20    /* IREQ intr req */
DECL|macro|HD64465_PCCCSCR_PSC
mdefine_line|#define     HD64465_PCCCSCR_PSC   &t; 0x10    /* STSCHG (status change) pin */
DECL|macro|HD64465_PCCCSCR_PCDC
mdefine_line|#define     HD64465_PCCCSCR_PCDC   &t; 0x08    /* CD (card detect) change */
DECL|macro|HD64465_PCCCSCR_PRC
mdefine_line|#define     HD64465_PCCCSCR_PRC   &t; 0x04    /* ready change */
DECL|macro|HD64465_PCCCSCR_PBW
mdefine_line|#define     HD64465_PCCCSCR_PBW   &t; 0x02    /* battery warning change */
DECL|macro|HD64465_PCCCSCR_PBD
mdefine_line|#define     HD64465_PCCCSCR_PBD   &t; 0x01    /* battery dead change */
DECL|macro|HD64465_REG_PCC0CSCIER
mdefine_line|#define HD64465_REG_PCC0CSCIER&t;0x12006&t;/* socket 0 card status change interrupt enable */ 
DECL|macro|HD64465_PCCCSCIER_PCRE
mdefine_line|#define     HD64465_PCCCSCIER_PCRE   &t; 0x80    /* change reset enable */
DECL|macro|HD64465_PCCCSCIER_PIREQE_MASK
mdefine_line|#define     HD64465_PCCCSCIER_PIREQE_MASK   &t;0x60   /* IREQ enable */
DECL|macro|HD64465_PCCCSCIER_PIREQE_DISABLED
mdefine_line|#define     HD64465_PCCCSCIER_PIREQE_DISABLED&t;0x00   /* IREQ disabled */
DECL|macro|HD64465_PCCCSCIER_PIREQE_LEVEL
mdefine_line|#define     HD64465_PCCCSCIER_PIREQE_LEVEL  &t;0x20   /* IREQ level-triggered */
DECL|macro|HD64465_PCCCSCIER_PIREQE_FALLING
mdefine_line|#define     HD64465_PCCCSCIER_PIREQE_FALLING&t;0x40   /* IREQ falling-edge-trig */
DECL|macro|HD64465_PCCCSCIER_PIREQE_RISING
mdefine_line|#define     HD64465_PCCCSCIER_PIREQE_RISING &t;0x60   /* IREQ rising-edge-trig */
DECL|macro|HD64465_PCCCSCIER_PSCE
mdefine_line|#define     HD64465_PCCCSCIER_PSCE   &t; 0x10    /* status change enable */
DECL|macro|HD64465_PCCCSCIER_PCDE
mdefine_line|#define     HD64465_PCCCSCIER_PCDE   &t; 0x08    /* card detect change enable */
DECL|macro|HD64465_PCCCSCIER_PRE
mdefine_line|#define     HD64465_PCCCSCIER_PRE   &t; 0x04    /* ready change enable */
DECL|macro|HD64465_PCCCSCIER_PBWE
mdefine_line|#define     HD64465_PCCCSCIER_PBWE   &t; 0x02    /* battery warn change enable */
DECL|macro|HD64465_PCCCSCIER_PBDE
mdefine_line|#define     HD64465_PCCCSCIER_PBDE   &t; 0x01    /* battery dead change enable*/
DECL|macro|HD64465_REG_PCC0SCR
mdefine_line|#define HD64465_REG_PCC0SCR&t;0x12008&t;/* socket 0 software control */ 
DECL|macro|HD64465_PCCSCR_SHDN
mdefine_line|#define     HD64465_PCCSCR_SHDN   &t; 0x10    /* TPS2206 SHutDowN pin */
DECL|macro|HD64465_PCCSCR_SWP
mdefine_line|#define     HD64465_PCCSCR_SWP   &t; 0x01    /* write protect */
DECL|macro|HD64465_REG_PCCPSR
mdefine_line|#define HD64465_REG_PCCPSR&t;0x1200A&t;/* serial power switch control */ 
DECL|macro|HD64465_REG_PCC1ISR
mdefine_line|#define HD64465_REG_PCC1ISR&t;0x12010&t;/* socket 1 interface status */ 
DECL|macro|HD64465_REG_PCC1GCR
mdefine_line|#define HD64465_REG_PCC1GCR&t;0x12012&t;/* socket 1 general control */ 
DECL|macro|HD64465_REG_PCC1CSCR
mdefine_line|#define HD64465_REG_PCC1CSCR&t;0x12014&t;/* socket 1 card status change */ 
DECL|macro|HD64465_REG_PCC1CSCIER
mdefine_line|#define HD64465_REG_PCC1CSCIER&t;0x12016&t;/* socket 1 card status change interrupt enable */ 
DECL|macro|HD64465_REG_PCC1SCR
mdefine_line|#define HD64465_REG_PCC1SCR&t;0x12018&t;/* socket 1 software control */ 
multiline_comment|/* PS/2 Keyboard and mouse controller -- *not* register compatible */
DECL|macro|HD64465_REG_KBCSR
mdefine_line|#define HD64465_REG_KBCSR   &t;0x1dc00 /* Keyboard Control/Status reg */
DECL|macro|HD64465_KBCSR_KBCIE
mdefine_line|#define     HD64465_KBCSR_KBCIE   &t; 0x8000    /* KBCK Input Enable */
DECL|macro|HD64465_KBCSR_KBCOE
mdefine_line|#define     HD64465_KBCSR_KBCOE   &t; 0x4000    /* KBCK Output Enable */
DECL|macro|HD64465_KBCSR_KBDOE
mdefine_line|#define     HD64465_KBCSR_KBDOE   &t; 0x2000    /* KB DATA Output Enable */
DECL|macro|HD64465_KBCSR_KBCD
mdefine_line|#define     HD64465_KBCSR_KBCD   &t; 0x1000    /* KBCK Driven */
DECL|macro|HD64465_KBCSR_KBDD
mdefine_line|#define     HD64465_KBCSR_KBDD   &t; 0x0800    /* KB DATA Driven */
DECL|macro|HD64465_KBCSR_KBCS
mdefine_line|#define     HD64465_KBCSR_KBCS   &t; 0x0400    /* KBCK pin Status */
DECL|macro|HD64465_KBCSR_KBDS
mdefine_line|#define     HD64465_KBCSR_KBDS   &t; 0x0200    /* KB DATA pin Status */
DECL|macro|HD64465_KBCSR_KBDP
mdefine_line|#define     HD64465_KBCSR_KBDP   &t; 0x0100    /* KB DATA Parity bit */
DECL|macro|HD64465_KBCSR_KBD_MASK
mdefine_line|#define     HD64465_KBCSR_KBD_MASK   &t; 0x00ff    /* KD DATA shift reg */
DECL|macro|HD64465_REG_KBISR
mdefine_line|#define HD64465_REG_KBISR   &t;0x1dc04 /* Keyboard Interrupt Status reg */
DECL|macro|HD64465_KBISR_KBRDF
mdefine_line|#define     HD64465_KBISR_KBRDF   &t; 0x0001    /* KB Received Data Full */
DECL|macro|HD64465_REG_MSCSR
mdefine_line|#define HD64465_REG_MSCSR   &t;0x1dc10 /* Mouse Control/Status reg */
DECL|macro|HD64465_REG_MSISR
mdefine_line|#define HD64465_REG_MSISR   &t;0x1dc14 /* Mouse Interrupt Status reg */
multiline_comment|/*&n; * Logical address at which the HD64465 is mapped.  Note that this&n; * should always be in the P2 segment (uncached and untranslated).&n; */
macro_line|#ifndef CONFIG_HD64465_IOBASE
DECL|macro|CONFIG_HD64465_IOBASE
mdefine_line|#define CONFIG_HD64465_IOBASE&t;0xb0000000
macro_line|#endif
multiline_comment|/*&n; * The HD64465 multiplexes all its modules&squot; interrupts onto&n; * this single interrupt.&n; */
macro_line|#ifndef CONFIG_HD64465_IRQ
DECL|macro|CONFIG_HD64465_IRQ
mdefine_line|#define CONFIG_HD64465_IRQ&t;5
macro_line|#endif
DECL|macro|_HD64465_IO_MASK
mdefine_line|#define _HD64465_IO_MASK&t;0xf8000000
DECL|macro|is_hd64465_addr
mdefine_line|#define is_hd64465_addr(addr) &bslash;&n;&t;((addr &amp; _HD64465_IO_MASK) == (CONFIG_HD64465_IOBASE &amp; _HD64465_IO_MASK))
multiline_comment|/*&n; * A range of 16 virtual interrupts generated by&n; * demuxing the HD64465 muxed interrupt.&n; */
DECL|macro|HD64465_IRQ_BASE
mdefine_line|#define HD64465_IRQ_BASE&t;OFFCHIP_IRQ_BASE
DECL|macro|HD64465_IRQ_NUM
mdefine_line|#define HD64465_IRQ_NUM &t;16
DECL|macro|HD64465_IRQ_ADC
mdefine_line|#define HD64465_IRQ_ADC     &t;(HD64465_IRQ_BASE+0)
DECL|macro|HD64465_IRQ_USB
mdefine_line|#define HD64465_IRQ_USB     &t;(HD64465_IRQ_BASE+1)
DECL|macro|HD64465_IRQ_SCDI
mdefine_line|#define HD64465_IRQ_SCDI    &t;(HD64465_IRQ_BASE+2)
DECL|macro|HD64465_IRQ_PARALLEL
mdefine_line|#define HD64465_IRQ_PARALLEL&t;(HD64465_IRQ_BASE+3)
multiline_comment|/* bit 4 is reserved */
DECL|macro|HD64465_IRQ_UART
mdefine_line|#define HD64465_IRQ_UART    &t;(HD64465_IRQ_BASE+5)
DECL|macro|HD64465_IRQ_IRDA
mdefine_line|#define HD64465_IRQ_IRDA    &t;(HD64465_IRQ_BASE+6)
DECL|macro|HD64465_IRQ_PS2MOUSE
mdefine_line|#define HD64465_IRQ_PS2MOUSE&t;(HD64465_IRQ_BASE+7)
DECL|macro|HD64465_IRQ_KBC
mdefine_line|#define HD64465_IRQ_KBC     &t;(HD64465_IRQ_BASE+8)
DECL|macro|HD64465_IRQ_TIMER1
mdefine_line|#define HD64465_IRQ_TIMER1   &t;(HD64465_IRQ_BASE+9)
DECL|macro|HD64465_IRQ_TIMER0
mdefine_line|#define HD64465_IRQ_TIMER0  &t;(HD64465_IRQ_BASE+10)
DECL|macro|HD64465_IRQ_GPIO
mdefine_line|#define HD64465_IRQ_GPIO    &t;(HD64465_IRQ_BASE+11)
DECL|macro|HD64465_IRQ_AFE
mdefine_line|#define HD64465_IRQ_AFE     &t;(HD64465_IRQ_BASE+12)
DECL|macro|HD64465_IRQ_PCMCIA1
mdefine_line|#define HD64465_IRQ_PCMCIA1 &t;(HD64465_IRQ_BASE+13)
DECL|macro|HD64465_IRQ_PCMCIA0
mdefine_line|#define HD64465_IRQ_PCMCIA0 &t;(HD64465_IRQ_BASE+14)
DECL|macro|HD64465_IRQ_PS2KBD
mdefine_line|#define HD64465_IRQ_PS2KBD     &t;(HD64465_IRQ_BASE+15)
multiline_comment|/* Constants for PCMCIA mappings */
DECL|macro|HD64465_PCC_WINDOW
mdefine_line|#define HD64465_PCC_WINDOW&t;0x01000000
DECL|macro|HD64465_PCC0_BASE
mdefine_line|#define HD64465_PCC0_BASE&t;0xb8000000&t;/* area 6 */
DECL|macro|HD64465_PCC0_ATTR
mdefine_line|#define HD64465_PCC0_ATTR&t;(HD64465_PCC0_BASE)
DECL|macro|HD64465_PCC0_COMM
mdefine_line|#define HD64465_PCC0_COMM&t;(HD64465_PCC0_BASE+HD64465_PCC_WINDOW)
DECL|macro|HD64465_PCC0_IO
mdefine_line|#define HD64465_PCC0_IO&t;&t;(HD64465_PCC0_BASE+2*HD64465_PCC_WINDOW)
DECL|macro|HD64465_PCC1_BASE
mdefine_line|#define HD64465_PCC1_BASE&t;0xb4000000&t;/* area 5 */
DECL|macro|HD64465_PCC1_ATTR
mdefine_line|#define HD64465_PCC1_ATTR&t;(HD64465_PCC1_BASE)
DECL|macro|HD64465_PCC1_COMM
mdefine_line|#define HD64465_PCC1_COMM&t;(HD64465_PCC1_BASE+HD64465_PCC_WINDOW)
DECL|macro|HD64465_PCC1_IO
mdefine_line|#define HD64465_PCC1_IO&t;&t;(HD64465_PCC1_BASE+2*HD64465_PCC_WINDOW)
multiline_comment|/*&n; * Base of USB controller interface (as memory)&n; */
DECL|macro|HD64465_USB_BASE
mdefine_line|#define HD64465_USB_BASE    &t;(CONFIG_HD64465_IOBASE+0xb000)
DECL|macro|HD64465_USB_LEN
mdefine_line|#define HD64465_USB_LEN    &t;0x1000
multiline_comment|/*&n; * Base of embedded SRAM, used for USB controller.&n; */
DECL|macro|HD64465_SRAM_BASE
mdefine_line|#define HD64465_SRAM_BASE    &t;(CONFIG_HD64465_IOBASE+0x9000)
DECL|macro|HD64465_SRAM_LEN
mdefine_line|#define HD64465_SRAM_LEN    &t;0x1000
macro_line|#endif /* _ASM_SH_HD64465_  */
eof
