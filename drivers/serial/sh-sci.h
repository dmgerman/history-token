multiline_comment|/* $Id: sh-sci.h,v 1.4 2004/02/19 16:43:56 lethal Exp $&n; *&n; *  linux/drivers/serial/sh-sci.h&n; *&n; *  SuperH on-chip serial module support.  (SCI with no FIFO / with FIFO)&n; *  Copyright (C) 1999, 2000  Niibe Yutaka&n; *  Copyright (C) 2000  Greg Banks&n; *  Copyright (C) 2002, 2003  Paul Mundt&n; *  Modified to support multiple serial ports. Stuart Menefy (May 2000).&n; *  Modified to support SH7300(SH-Mobile) SCIF. Takashi Kusuda (Jun 2003).&n; *  Modified to support H8/300 Series Yoshinori Sato (Feb 2004).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#if defined(__H8300H__) || defined(__H8300S__)
macro_line|#include &lt;asm/gpio.h&gt;
macro_line|#if defined(CONFIG_H83007) || defined(CONFIG_H83068)
macro_line|#include &lt;asm/regs306x.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_H8S2678)
macro_line|#include &lt;asm/regs267x.h&gt;
macro_line|#endif
macro_line|#endif
multiline_comment|/* Offsets into the sci_port-&gt;irqs array */
DECL|macro|SCIx_ERI_IRQ
mdefine_line|#define SCIx_ERI_IRQ 0
DECL|macro|SCIx_RXI_IRQ
mdefine_line|#define SCIx_RXI_IRQ 1
DECL|macro|SCIx_TXI_IRQ
mdefine_line|#define SCIx_TXI_IRQ 2
multiline_comment|/*                     ERI, RXI, TXI, BRI */
DECL|macro|SCI_IRQS
mdefine_line|#define SCI_IRQS      { 23,  24,  25,   0 }
DECL|macro|SH3_SCIF_IRQS
mdefine_line|#define SH3_SCIF_IRQS { 56,  57,  59,  58 }
DECL|macro|SH3_IRDA_IRQS
mdefine_line|#define SH3_IRDA_IRQS { 52,  53,  55,  54 }
DECL|macro|SH4_SCIF_IRQS
mdefine_line|#define SH4_SCIF_IRQS { 40,  41,  43,  42 }
DECL|macro|STB1_SCIF1_IRQS
mdefine_line|#define STB1_SCIF1_IRQS {23, 24,  26,  25 }
DECL|macro|SH7760_SCIF0_IRQS
mdefine_line|#define SH7760_SCIF0_IRQS { 52, 53, 55, 54 }
DECL|macro|SH7760_SCIF1_IRQS
mdefine_line|#define SH7760_SCIF1_IRQS { 72, 73, 75, 74 }
DECL|macro|SH7760_SCIF2_IRQS
mdefine_line|#define SH7760_SCIF2_IRQS { 76, 77, 79, 78 }
DECL|macro|SH7300_SCIF0_IRQS
mdefine_line|#define SH7300_SCIF0_IRQS {80,  80,  80,  80 }
DECL|macro|SH73180_SCIF_IRQS
mdefine_line|#define SH73180_SCIF_IRQS {80,  81,  83,  82 }
DECL|macro|H8300H_SCI_IRQS0
mdefine_line|#define H8300H_SCI_IRQS0 {52, 53, 54,   0 }
DECL|macro|H8300H_SCI_IRQS1
mdefine_line|#define H8300H_SCI_IRQS1 {56, 57, 58,   0 }
DECL|macro|H8300H_SCI_IRQS2
mdefine_line|#define H8300H_SCI_IRQS2 {60, 61, 62,   0 }
DECL|macro|H8S_SCI_IRQS0
mdefine_line|#define H8S_SCI_IRQS0 {88, 89, 90,   0 }
DECL|macro|H8S_SCI_IRQS1
mdefine_line|#define H8S_SCI_IRQS1 {92, 93, 94,   0 }
DECL|macro|H8S_SCI_IRQS2
mdefine_line|#define H8S_SCI_IRQS2 {96, 97, 98,   0 }
DECL|macro|SH5_SCIF_IRQS
mdefine_line|#define SH5_SCIF_IRQS {39, 40, 42,   0 }
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7708)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCSPTR
macro_line|# define SCSPTR 0xffffff7c /* 8 bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x30 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCI_ONLY
macro_line|# define SCI_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7707) || defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 3
DECL|macro|SCPCR
macro_line|# define SCPCR  0xA4000116 /* 16 bit SCI and SCIF */
DECL|macro|SCPDR
macro_line|# define SCPDR  0xA4000136 /* 8  bit SCI and SCIF */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x30 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCI_AND_SCIF
macro_line|# define SCI_AND_SCIF
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|SCIF0
macro_line|# define SCIF0&t;&t;0xA4400000
DECL|macro|SCIF2
macro_line|# define SCIF2&t;&t;0xA4410000
DECL|macro|SCSMR_Ir
macro_line|# define SCSMR_Ir &t;0xA44A0000
DECL|macro|IRDA_SCIF
macro_line|# define IRDA_SCIF &t;SCIF0
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 2
DECL|macro|SCPCR
macro_line|# define SCPCR 0xA4000116
DECL|macro|SCPDR
macro_line|# define SCPDR 0xA4000136
multiline_comment|/* Set the clock source,&n; * SCIF2 (0xA4410000) -&gt; External clock, SCK pin used as clock input&n; * SCIF0 (0xA4400000) -&gt; Internal clock, SCK pin as serial clock output&n; */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port) (port-&gt;mapbase == SCIF2) ? 0xF3 : 0xF0
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_SH_RTS7751R2D)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCSPTR1
macro_line|# define SCSPTR1 0xffe0001c /* 8  bit SCI */
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2 0xFFE80020 /* 16 bit SCIF */
DECL|macro|SCIF_ORER
macro_line|# define SCIF_ORER 0x0001   /* overrun error bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port) 0x3a /* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 2
DECL|macro|SCSPTR1
macro_line|# define SCSPTR1 0xffe0001c /* 8  bit SCI */
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2 0xFFE80020 /* 16 bit SCIF */
DECL|macro|SCIF_ORER
macro_line|# define SCIF_ORER 0x0001   /* overrun error bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port) (((port)-&gt;type == PORT_SCI) ? &bslash;&n;&t;0x30 /* TIE=0,RIE=0,TE=1,RE=1 */ : &bslash;&n;&t;0x38 /* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */ )
DECL|macro|SCI_AND_SCIF
macro_line|# define SCI_AND_SCIF
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7760)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 3
DECL|macro|SCSPTR0
macro_line|# define SCSPTR0 0xfe600000 /* 16 bit SCIF */
DECL|macro|SCSPTR1
macro_line|# define SCSPTR1 0xfe610000 /* 16 bit SCIF */
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2 0xfe620000 /* 16 bit SCIF */
DECL|macro|SCIF_ORER
macro_line|# define SCIF_ORER 0x0001  /* overrun error bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x38 /* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7300)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCPCR
macro_line|# define SCPCR  0xA4050116        /* 16 bit SCIF */
DECL|macro|SCPDR
macro_line|# define SCPDR  0xA4050136        /* 16 bit SCIF */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)  0x0030 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH73180)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCPDR
macro_line|# define SCPDR  0xA4050138        /* 16 bit SCIF */
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2 SCPDR
DECL|macro|SCIF_ORER
macro_line|# define SCIF_ORER 0x0001   /* overrun error bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)  0x0038 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH4_202)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2 0xffe80020 /* 16 bit SCIF */
DECL|macro|SCIF_ORER
macro_line|# define SCIF_ORER 0x0001   /* overrun error bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port) 0x38 /* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 2
DECL|macro|SCSPTR1
macro_line|# define SCSPTR1 0xffe00020 /* 16 bit SCIF */
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2 0xffe80020 /* 16 bit SCIF */
DECL|macro|SCIF_ORER
macro_line|# define SCIF_ORER 0x0001   /* overrun error bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x38 /* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH5_101) || defined(CONFIG_CPU_SUBTYPE_SH5_103)
macro_line|# include &lt;asm/hardware.h&gt;
DECL|macro|SCIF_BASE_ADDR
macro_line|# define SCIF_BASE_ADDR    0x01030000
DECL|macro|SCIF_ADDR_SH5
macro_line|# define SCIF_ADDR_SH5     PHYS_PERIPHERAL_BLOCK+SCIF_BASE_ADDR
DECL|macro|SCIF_PTR2_OFFS
macro_line|# define SCIF_PTR2_OFFS    0x0000020
DECL|macro|SCIF_LSR2_OFFS
macro_line|# define SCIF_LSR2_OFFS    0x0000024
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCI_INIT
macro_line|# define SCI_INIT { &bslash;&n;  { {}, PORT_SCIF, 0, &bslash;&n;     SH5_SCIF_IRQS, sci_init_pins_scif }  &bslash;&n;}
DECL|macro|SCSPTR2
macro_line|# define SCSPTR2           ((port-&gt;mapbase)+SCIF_PTR2_OFFS) /* 16 bit SCIF */
DECL|macro|SCLSR2
macro_line|# define SCLSR2            ((port-&gt;mapbase)+SCIF_LSR2_OFFS) /* 16 bit SCIF */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)  0x38                           /* TIE=0,RIE=0,&n;&t;&t;&t;&t;&t;&t;&t;     TE=1,RE=1,REIE=1 */
DECL|macro|SCIF_ONLY
macro_line|# define SCIF_ONLY
macro_line|#elif defined(CONFIG_H83007) || defined(CONFIG_H83068)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 3
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x30 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCI_ONLY
macro_line|# define SCI_ONLY
DECL|macro|H8300_SCI_DR
macro_line|# define H8300_SCI_DR(ch) *(volatile char *)(P1DR + h8300_sci_pins[ch].port)
macro_line|#elif defined(CONFIG_H8S2678)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 3
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x30 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCI_ONLY
macro_line|# define SCI_ONLY
DECL|macro|H8300_SCI_DR
macro_line|# define H8300_SCI_DR(ch) *(volatile char *)(P1DR + h8300_sci_pins[ch].port)
macro_line|#else
macro_line|# error CPU subtype not defined
macro_line|#endif
multiline_comment|/* SCSCR */
DECL|macro|SCI_CTRL_FLAGS_TIE
mdefine_line|#define SCI_CTRL_FLAGS_TIE  0x80 /* all */
DECL|macro|SCI_CTRL_FLAGS_RIE
mdefine_line|#define SCI_CTRL_FLAGS_RIE  0x40 /* all */
DECL|macro|SCI_CTRL_FLAGS_TE
mdefine_line|#define SCI_CTRL_FLAGS_TE   0x20 /* all */
DECL|macro|SCI_CTRL_FLAGS_RE
mdefine_line|#define SCI_CTRL_FLAGS_RE   0x10 /* all */
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751)
DECL|macro|SCI_CTRL_FLAGS_REIE
mdefine_line|#define SCI_CTRL_FLAGS_REIE 0x08 /* 7750 SCIF */
macro_line|#else
DECL|macro|SCI_CTRL_FLAGS_REIE
mdefine_line|#define SCI_CTRL_FLAGS_REIE 0
macro_line|#endif
multiline_comment|/*      SCI_CTRL_FLAGS_MPIE 0x08  * 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
multiline_comment|/*      SCI_CTRL_FLAGS_TEIE 0x04  * 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
multiline_comment|/*      SCI_CTRL_FLAGS_CKE1 0x02  * all */
multiline_comment|/*      SCI_CTRL_FLAGS_CKE0 0x01  * 7707 SCI/SCIF, 7708 SCI, 7709 SCI/SCIF, 7750 SCI */
multiline_comment|/* SCxSR SCI */
DECL|macro|SCI_TDRE
mdefine_line|#define SCI_TDRE  0x80 /* 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
DECL|macro|SCI_RDRF
mdefine_line|#define SCI_RDRF  0x40 /* 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
DECL|macro|SCI_ORER
mdefine_line|#define SCI_ORER  0x20 /* 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
DECL|macro|SCI_FER
mdefine_line|#define SCI_FER   0x10 /* 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
DECL|macro|SCI_PER
mdefine_line|#define SCI_PER   0x08 /* 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
DECL|macro|SCI_TEND
mdefine_line|#define SCI_TEND  0x04 /* 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
multiline_comment|/*      SCI_MPB   0x02  * 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
multiline_comment|/*      SCI_MPBT  0x01  * 7707 SCI, 7708 SCI, 7709 SCI, 7750 SCI */
DECL|macro|SCI_ERRORS
mdefine_line|#define SCI_ERRORS ( SCI_PER | SCI_FER | SCI_ORER)
multiline_comment|/* SCxSR SCIF */
DECL|macro|SCIF_ER
mdefine_line|#define SCIF_ER    0x0080 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_TEND
mdefine_line|#define SCIF_TEND  0x0040 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_TDFE
mdefine_line|#define SCIF_TDFE  0x0020 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_BRK
mdefine_line|#define SCIF_BRK   0x0010 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_FER
mdefine_line|#define SCIF_FER   0x0008 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_PER
mdefine_line|#define SCIF_PER   0x0004 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_RDF
mdefine_line|#define SCIF_RDF   0x0002 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_DR
mdefine_line|#define SCIF_DR    0x0001 /* 7705 SCIF, 7707 SCIF, 7709 SCIF, 7750 SCIF */
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300) || defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|SCIF_ORER
mdefine_line|#define SCIF_ORER    0x0200
DECL|macro|SCIF_ERRORS
mdefine_line|#define SCIF_ERRORS ( SCIF_PER | SCIF_FER | SCIF_ER | SCIF_BRK | SCIF_ORER)
DECL|macro|SCIF_RFDC_MASK
mdefine_line|#define SCIF_RFDC_MASK 0x007f
DECL|macro|SCIF_TXROOM_MAX
mdefine_line|#define SCIF_TXROOM_MAX 64
macro_line|#else
DECL|macro|SCIF_ERRORS
mdefine_line|#define SCIF_ERRORS ( SCIF_PER | SCIF_FER | SCIF_ER | SCIF_BRK)
DECL|macro|SCIF_RFDC_MASK
mdefine_line|#define SCIF_RFDC_MASK 0x001f
DECL|macro|SCIF_TXROOM_MAX
mdefine_line|#define SCIF_TXROOM_MAX 16
macro_line|#endif
macro_line|#if defined(SCI_ONLY)
DECL|macro|SCxSR_TEND
macro_line|# define SCxSR_TEND(port)&t;&t;SCI_TEND
DECL|macro|SCxSR_ERRORS
macro_line|# define SCxSR_ERRORS(port)&t;&t;SCI_ERRORS
DECL|macro|SCxSR_RDxF
macro_line|# define SCxSR_RDxF(port)               SCI_RDRF
DECL|macro|SCxSR_TDxE
macro_line|# define SCxSR_TDxE(port)               SCI_TDRE
DECL|macro|SCxSR_ORER
macro_line|# define SCxSR_ORER(port)&t;&t;SCI_ORER
DECL|macro|SCxSR_FER
macro_line|# define SCxSR_FER(port)&t;&t;SCI_FER
DECL|macro|SCxSR_PER
macro_line|# define SCxSR_PER(port)&t;&t;SCI_PER
DECL|macro|SCxSR_BRK
macro_line|# define SCxSR_BRK(port)&t;&t;0x00
DECL|macro|SCxSR_RDxF_CLEAR
macro_line|# define SCxSR_RDxF_CLEAR(port)&t;&t;0xbc
DECL|macro|SCxSR_ERROR_CLEAR
macro_line|# define SCxSR_ERROR_CLEAR(port)&t;0xc4
DECL|macro|SCxSR_TDxE_CLEAR
macro_line|# define SCxSR_TDxE_CLEAR(port)&t;&t;0x78
DECL|macro|SCxSR_BREAK_CLEAR
macro_line|# define SCxSR_BREAK_CLEAR(port)   &t;0xc4
macro_line|#elif defined(SCIF_ONLY)
DECL|macro|SCxSR_TEND
macro_line|# define SCxSR_TEND(port)&t;&t;SCIF_TEND
DECL|macro|SCxSR_ERRORS
macro_line|# define SCxSR_ERRORS(port)&t;&t;SCIF_ERRORS
DECL|macro|SCxSR_RDxF
macro_line|# define SCxSR_RDxF(port)               SCIF_RDF
DECL|macro|SCxSR_TDxE
macro_line|# define SCxSR_TDxE(port)               SCIF_TDFE
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300) || defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|SCxSR_ORER
macro_line|# define SCxSR_ORER(port)&t;&t;SCIF_ORER
macro_line|#else
DECL|macro|SCxSR_ORER
macro_line|# define SCxSR_ORER(port)&t;&t;0x0000
macro_line|#endif
DECL|macro|SCxSR_FER
macro_line|# define SCxSR_FER(port)&t;&t;SCIF_FER
DECL|macro|SCxSR_PER
macro_line|# define SCxSR_PER(port)&t;&t;SCIF_PER
DECL|macro|SCxSR_BRK
macro_line|# define SCxSR_BRK(port)&t;&t;SCIF_BRK
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300) || defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|SCxSR_RDxF_CLEAR
macro_line|# define SCxSR_RDxF_CLEAR(port)         (sci_in(port,SCxSR)&amp;0xfffc)
DECL|macro|SCxSR_ERROR_CLEAR
macro_line|# define SCxSR_ERROR_CLEAR(port)        (sci_in(port,SCxSR)&amp;0xfd73)
DECL|macro|SCxSR_TDxE_CLEAR
macro_line|# define SCxSR_TDxE_CLEAR(port)         (sci_in(port,SCxSR)&amp;0xffdf)
DECL|macro|SCxSR_BREAK_CLEAR
macro_line|# define SCxSR_BREAK_CLEAR(port)        (sci_in(port,SCxSR)&amp;0xffe3)
macro_line|#else
multiline_comment|/* SH7705 can also use this, clearing is same between 7705 and 7709 and 7300 */
DECL|macro|SCxSR_RDxF_CLEAR
macro_line|# define SCxSR_RDxF_CLEAR(port)&t;&t;0x00fc
DECL|macro|SCxSR_ERROR_CLEAR
macro_line|# define SCxSR_ERROR_CLEAR(port)&t;0x0073
DECL|macro|SCxSR_TDxE_CLEAR
macro_line|# define SCxSR_TDxE_CLEAR(port)&t;&t;0x00df
DECL|macro|SCxSR_BREAK_CLEAR
macro_line|# define SCxSR_BREAK_CLEAR(port)   &t;0x00e3
macro_line|#endif
macro_line|#else
DECL|macro|SCxSR_TEND
macro_line|# define SCxSR_TEND(port)&t; (((port)-&gt;type == PORT_SCI) ? SCI_TEND   : SCIF_TEND)
DECL|macro|SCxSR_ERRORS
macro_line|# define SCxSR_ERRORS(port)&t; (((port)-&gt;type == PORT_SCI) ? SCI_ERRORS : SCIF_ERRORS)
DECL|macro|SCxSR_RDxF
macro_line|# define SCxSR_RDxF(port)        (((port)-&gt;type == PORT_SCI) ? SCI_RDRF   : SCIF_RDF)
DECL|macro|SCxSR_TDxE
macro_line|# define SCxSR_TDxE(port)        (((port)-&gt;type == PORT_SCI) ? SCI_TDRE   : SCIF_TDFE)
DECL|macro|SCxSR_ORER
macro_line|# define SCxSR_ORER(port)        (((port)-&gt;type == PORT_SCI) ? SCI_ORER   : 0x0000)
DECL|macro|SCxSR_FER
macro_line|# define SCxSR_FER(port)         (((port)-&gt;type == PORT_SCI) ? SCI_FER    : SCIF_FER)
DECL|macro|SCxSR_PER
macro_line|# define SCxSR_PER(port)         (((port)-&gt;type == PORT_SCI) ? SCI_PER    : SCIF_PER)
DECL|macro|SCxSR_BRK
macro_line|# define SCxSR_BRK(port)         (((port)-&gt;type == PORT_SCI) ? 0x00       : SCIF_BRK)
DECL|macro|SCxSR_RDxF_CLEAR
macro_line|# define SCxSR_RDxF_CLEAR(port)&t; (((port)-&gt;type == PORT_SCI) ? 0xbc : 0x00fc)
DECL|macro|SCxSR_ERROR_CLEAR
macro_line|# define SCxSR_ERROR_CLEAR(port) (((port)-&gt;type == PORT_SCI) ? 0xc4 : 0x0073)
DECL|macro|SCxSR_TDxE_CLEAR
macro_line|# define SCxSR_TDxE_CLEAR(port)  (((port)-&gt;type == PORT_SCI) ? 0x78 : 0x00df)
DECL|macro|SCxSR_BREAK_CLEAR
macro_line|# define SCxSR_BREAK_CLEAR(port) (((port)-&gt;type == PORT_SCI) ? 0xc4 : 0x00e3)
macro_line|#endif
multiline_comment|/* SCFCR */
DECL|macro|SCFCR_RFRST
mdefine_line|#define SCFCR_RFRST 0x0002
DECL|macro|SCFCR_TFRST
mdefine_line|#define SCFCR_TFRST 0x0004
DECL|macro|SCFCR_TCRST
mdefine_line|#define SCFCR_TCRST 0x4000
DECL|macro|SCFCR_MCE
mdefine_line|#define SCFCR_MCE   0x0008
DECL|macro|SCI_MAJOR
mdefine_line|#define SCI_MAJOR&t;&t;204
DECL|macro|SCI_MINOR_START
mdefine_line|#define SCI_MINOR_START&t;&t;8
multiline_comment|/* Generic serial flags */
DECL|macro|SCI_RX_THROTTLE
mdefine_line|#define SCI_RX_THROTTLE&t;&t;0x0000001
DECL|macro|SCI_MAGIC
mdefine_line|#define SCI_MAGIC 0xbabeface
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|SCI_EVENT_WRITE_WAKEUP
mdefine_line|#define SCI_EVENT_WRITE_WAKEUP&t;0
DECL|struct|sci_port
r_struct
id|sci_port
(brace
DECL|member|port
r_struct
id|uart_port
id|port
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|irqs
r_int
r_char
id|irqs
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ERI, RXI, TXI, BRI */
DECL|member|init_pins
r_void
(paren
op_star
id|init_pins
)paren
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|cflag
)paren
suffix:semicolon
DECL|member|break_flag
r_int
id|break_flag
suffix:semicolon
DECL|member|break_timer
r_struct
id|timer_list
id|break_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCI_IN
mdefine_line|#define SCI_IN(size, offset)&t;&t;&t;&t;&t;&bslash;&n;  unsigned int addr = port-&gt;mapbase + (offset);&t;&t;&t;&bslash;&n;  if ((size) == 8) { &t;&t;&t;&t;&t;&t;&bslash;&n;    return ctrl_inb(addr);&t;&t;&t;&t;&t;&bslash;&n;  } else {&t;&t;&t;&t;&t; &t;&t;&bslash;&n;    return ctrl_inw(addr);&t;&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|SCI_OUT
mdefine_line|#define SCI_OUT(size, offset, value)&t;&t;&t;&t;&bslash;&n;  unsigned int addr = port-&gt;mapbase + (offset);&t;&t;&t;&bslash;&n;  if ((size) == 8) { &t;&t;&t;&t;&t;&t;&bslash;&n;    ctrl_outb(value, addr);&t;&t;&t;&t;&t;&bslash;&n;  } else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    ctrl_outw(value, addr);&t;&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|CPU_SCIx_FNS
mdefine_line|#define CPU_SCIx_FNS(name, sci_offset, sci_size, scif_offset, scif_size)&bslash;&n;  static inline unsigned int sci_##name##_in(struct uart_port *port)&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (port-&gt;type == PORT_SCI) { &t;&t;&t;&t;&t;&bslash;&n;      SCI_IN(sci_size, sci_offset)&t;&t;&t;&t;&t;&bslash;&n;    } else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      SCI_IN(scif_size, scif_offset);&t;&t; &t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  static inline void sci_##name##_out(struct uart_port *port, unsigned int value) &bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (port-&gt;type == PORT_SCI) {&t;&t;&t;&t;&t;&bslash;&n;      SCI_OUT(sci_size, sci_offset, value)&t;&t;&t;&t;&bslash;&n;    } else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      SCI_OUT(scif_size, scif_offset, value);&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|CPU_SCIF_FNS
mdefine_line|#define CPU_SCIF_FNS(name, scif_offset, scif_size)&t;&t;&t;&t;&bslash;&n;  static inline unsigned int sci_##name##_in(struct uart_port *port)&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    SCI_IN(scif_size, scif_offset);&t;&t; &t;&t;&t;&bslash;&n;  }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  static inline void sci_##name##_out(struct uart_port *port, unsigned int value) &bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    SCI_OUT(scif_size, scif_offset, value);&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|CPU_SCI_FNS
mdefine_line|#define CPU_SCI_FNS(name, sci_offset, sci_size)&t;&t;&t;&t;&bslash;&n;  static inline unsigned int sci_##name##_in(struct uart_port* port)&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    SCI_IN(sci_size, sci_offset);&t;&t; &t;&t;&t;&bslash;&n;  }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  static inline void sci_##name##_out(struct uart_port* port, unsigned int value) &bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    SCI_OUT(sci_size, sci_offset, value);&t;&t;&t;&t;&bslash;&n;  }
macro_line|#ifdef CONFIG_CPU_SH3
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300) || defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|SCIF_FNS
mdefine_line|#define SCIF_FNS(name, scif_offset, scif_size) &bslash;&n;  CPU_SCIF_FNS(name, scif_offset, scif_size)
macro_line|#else
DECL|macro|SCIx_FNS
mdefine_line|#define SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh4_sci_offset, sh4_sci_size, &bslash;&n;&t;&t; sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size, &bslash;&n;                 h8_sci_offset, h8_sci_size) &bslash;&n;  CPU_SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh3_scif_offset, sh3_scif_size)
DECL|macro|SCIF_FNS
mdefine_line|#define SCIF_FNS(name, sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size) &bslash;&n;  CPU_SCIF_FNS(name, sh3_scif_offset, sh3_scif_size)
macro_line|#endif
macro_line|#elif defined(__H8300H__) || defined(__H8300S__)
DECL|macro|SCIx_FNS
mdefine_line|#define SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh4_sci_offset, sh4_sci_size, &bslash;&n;&t;&t; sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size, &bslash;&n;                 h8_sci_offset, h8_sci_size) &bslash;&n;  CPU_SCI_FNS(name, h8_sci_offset, h8_sci_size)
DECL|macro|SCIF_FNS
mdefine_line|#define SCIF_FNS(name, sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size)
macro_line|#else
DECL|macro|SCIx_FNS
mdefine_line|#define SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh4_sci_offset, sh4_sci_size, &bslash;&n;&t;&t; sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size, &bslash;&n;&t;&t; h8_sci_offset, h8_sci_size) &bslash;&n;  CPU_SCIx_FNS(name, sh4_sci_offset, sh4_sci_size, sh4_scif_offset, sh4_scif_size)
DECL|macro|SCIF_FNS
mdefine_line|#define SCIF_FNS(name, sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size) &bslash;&n;  CPU_SCIF_FNS(name, sh4_scif_offset, sh4_scif_size)
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300) || defined(CONFIG_CPU_SUBTYPE_SH7705)
id|SCIF_FNS
c_func
(paren
id|SCSMR
comma
l_int|0x00
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCBRR
comma
l_int|0x04
comma
l_int|8
)paren
id|SCIF_FNS
c_func
(paren
id|SCSCR
comma
l_int|0x08
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCTDSR
comma
l_int|0x0c
comma
l_int|8
)paren
id|SCIF_FNS
c_func
(paren
id|SCFER
comma
l_int|0x10
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCxSR
comma
l_int|0x14
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCFCR
comma
l_int|0x18
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCFDR
comma
l_int|0x1c
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCxTDR
comma
l_int|0x20
comma
l_int|8
)paren
id|SCIF_FNS
c_func
(paren
id|SCxRDR
comma
l_int|0x24
comma
l_int|8
)paren
id|SCIF_FNS
c_func
(paren
id|SCLSR
comma
l_int|0x24
comma
l_int|16
)paren
macro_line|#else
multiline_comment|/*      reg      SCI/SH3   SCI/SH4  SCIF/SH3   SCIF/SH4  SCI/H8*/
multiline_comment|/*      name     off  sz   off  sz   off  sz   off  sz   off  sz*/
id|SCIx_FNS
c_func
(paren
id|SCSMR
comma
l_int|0x00
comma
l_int|8
comma
l_int|0x00
comma
l_int|8
comma
l_int|0x00
comma
l_int|8
comma
l_int|0x00
comma
l_int|16
comma
l_int|0x00
comma
l_int|8
)paren
id|SCIx_FNS
c_func
(paren
id|SCBRR
comma
l_int|0x02
comma
l_int|8
comma
l_int|0x04
comma
l_int|8
comma
l_int|0x02
comma
l_int|8
comma
l_int|0x04
comma
l_int|8
comma
l_int|0x01
comma
l_int|8
)paren
id|SCIx_FNS
c_func
(paren
id|SCSCR
comma
l_int|0x04
comma
l_int|8
comma
l_int|0x08
comma
l_int|8
comma
l_int|0x04
comma
l_int|8
comma
l_int|0x08
comma
l_int|16
comma
l_int|0x02
comma
l_int|8
)paren
id|SCIx_FNS
c_func
(paren
id|SCxTDR
comma
l_int|0x06
comma
l_int|8
comma
l_int|0x0c
comma
l_int|8
comma
l_int|0x06
comma
l_int|8
comma
l_int|0x0C
comma
l_int|8
comma
l_int|0x03
comma
l_int|8
)paren
id|SCIx_FNS
c_func
(paren
id|SCxSR
comma
l_int|0x08
comma
l_int|8
comma
l_int|0x10
comma
l_int|8
comma
l_int|0x08
comma
l_int|16
comma
l_int|0x10
comma
l_int|16
comma
l_int|0x04
comma
l_int|8
)paren
id|SCIx_FNS
c_func
(paren
id|SCxRDR
comma
l_int|0x0a
comma
l_int|8
comma
l_int|0x14
comma
l_int|8
comma
l_int|0x0A
comma
l_int|8
comma
l_int|0x14
comma
l_int|8
comma
l_int|0x05
comma
l_int|8
)paren
id|SCIF_FNS
c_func
(paren
id|SCFCR
comma
l_int|0x0c
comma
l_int|8
comma
l_int|0x18
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCFDR
comma
l_int|0x0e
comma
l_int|16
comma
l_int|0x1C
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCSPTR
comma
l_int|0
comma
l_int|0
comma
l_int|0x20
comma
l_int|16
)paren
id|SCIF_FNS
c_func
(paren
id|SCLSR
comma
l_int|0
comma
l_int|0
comma
l_int|0x24
comma
l_int|16
)paren
macro_line|#endif
DECL|macro|sci_in
mdefine_line|#define sci_in(port, reg) sci_##reg##_in(port)
DECL|macro|sci_out
mdefine_line|#define sci_out(port, reg, value) sci_##reg##_out(port, value)
multiline_comment|/* H8/300 series SCI pins assignment */
macro_line|#if defined(__H8300H__) || defined(__H8300S__)
r_static
r_const
r_struct
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* GPIO port no */
DECL|member|rx
DECL|member|tx
r_int
r_int
id|rx
comma
id|tx
suffix:semicolon
multiline_comment|/* GPIO bit no */
DECL|variable|h8300_sci_pins
)brace
id|h8300_sci_pins
(braket
)braket
op_assign
(brace
macro_line|#if defined(CONFIG_H83007) || defined(CONFIG_H83068)
(brace
multiline_comment|/* SCI0 */
dot
id|port
op_assign
id|H8300_GPIO_P9
comma
dot
id|rx
op_assign
id|H8300_GPIO_B2
comma
dot
id|tx
op_assign
id|H8300_GPIO_B0
comma
)brace
comma
(brace
multiline_comment|/* SCI1 */
dot
id|port
op_assign
id|H8300_GPIO_P9
comma
dot
id|rx
op_assign
id|H8300_GPIO_B3
comma
dot
id|tx
op_assign
id|H8300_GPIO_B1
comma
)brace
comma
(brace
multiline_comment|/* SCI2 */
dot
id|port
op_assign
id|H8300_GPIO_PB
comma
dot
id|rx
op_assign
id|H8300_GPIO_B7
comma
dot
id|tx
op_assign
id|H8300_GPIO_B6
comma
)brace
macro_line|#elif defined(CONFIG_H8S2678)
(brace
multiline_comment|/* SCI0 */
dot
id|port
op_assign
id|H8300_GPIO_P3
comma
dot
id|rx
op_assign
id|H8300_GPIO_B2
comma
dot
id|tx
op_assign
id|H8300_GPIO_B0
comma
)brace
comma
(brace
multiline_comment|/* SCI1 */
dot
id|port
op_assign
id|H8300_GPIO_P3
comma
dot
id|rx
op_assign
id|H8300_GPIO_B3
comma
dot
id|tx
op_assign
id|H8300_GPIO_B1
comma
)brace
comma
(brace
multiline_comment|/* SCI2 */
dot
id|port
op_assign
id|H8300_GPIO_P5
comma
dot
id|rx
op_assign
id|H8300_GPIO_B1
comma
dot
id|tx
op_assign
id|H8300_GPIO_B0
comma
)brace
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7708)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xfffffe80
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCSPTR
)paren
op_amp
l_int|0x01
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCI */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7707) || defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xfffffe80
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x01
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCI */
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xa4000150
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x10
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xa4000140
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x04
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* IRDA */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|SCIF0
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x04
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* IRDA */
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|SCIF2
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x10
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_SH7751) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_SH4_202)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
macro_line|#ifndef SCIF_ONLY
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xffe00000
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCSPTR1
)paren
op_amp
l_int|0x01
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCI */
macro_line|#endif
macro_line|#ifndef SCI_ONLY
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xffe80000
)paren
r_return
id|ctrl_inw
c_func
(paren
id|SCSPTR2
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7760)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xfe600000
)paren
r_return
id|ctrl_inw
c_func
(paren
id|SCSPTR0
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xfe610000
)paren
r_return
id|ctrl_inw
c_func
(paren
id|SCSPTR1
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xfe620000
)paren
r_return
id|ctrl_inw
c_func
(paren
id|SCSPTR2
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7300)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xa4430000
)paren
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x01
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF0 */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH73180)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|ctrl_inb
c_func
(paren
id|SCPDR
)paren
op_amp
l_int|0x01
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF0 */
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
l_int|0xffe00000
)paren
r_return
id|ctrl_inw
c_func
(paren
id|SCSPTR1
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
r_else
r_return
id|ctrl_inw
c_func
(paren
id|SCSPTR2
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
)brace
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH5_101) || defined(CONFIG_CPU_SUBTYPE_SH5_103)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|sci_in
c_func
(paren
id|port
comma
id|SCSPTR
)paren
op_amp
l_int|0x0001
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* SCIF */
)brace
macro_line|#elif defined(__H8300H__) || defined(__H8300S__)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
id|ch
op_assign
(paren
id|port-&gt;mapbase
op_minus
id|SMR0
)paren
op_rshift
l_int|3
suffix:semicolon
r_return
(paren
id|H8300_SCI_DR
c_func
(paren
id|ch
)paren
op_amp
id|h8300_sci_pins
(braket
id|ch
)braket
dot
id|rx
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Values for the BitRate Register (SCBRR)&n; *&n; * The values are actually divisors for a frequency which can&n; * be internal to the SH3 (14.7456MHz) or derived from an external&n; * clock source.  This driver assumes the internal clock is used;&n; * to support using an external clock source, config options or&n; * possibly command-line options would need to be added.&n; *&n; * Also, to support speeds below 2400 (why?) the lower 2 bits of&n; * the SCSMR register would also need to be set to non-zero values.&n; *&n; * -- Greg Banks 27Feb2000&n; *&n; * Answer: The SCBRR register is only eight bits, and the value in&n; * it gets larger with lower baud rates. At around 2400 (depending on&n; * the peripherial module clock) you run out of bits. However the&n; * lower two bits of SCSMR allow the module clock to be divided down,&n; * scaling the value which is needed in SCBRR.&n; *&n; * -- Stuart Menefy - 23 May 2000&n; *&n; * I meant, why would anyone bother with bitrates below 2400.&n; *&n; * -- Greg Banks - 7Jul2000&n; *&n; * You &quot;speedist&quot;!  How will I use my 110bps ASR-33 teletype with paper&n; * tape reader as a console!&n; *&n; * -- Mitch Davis - 15 Jul 2000&n; */
DECL|macro|PCLK
mdefine_line|#define PCLK           (current_cpu_data.module_clock)
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300)
DECL|macro|SCBRR_VALUE
mdefine_line|#define SCBRR_VALUE(bps) ((PCLK+16*bps)/(16*bps)-1)
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|SCBRR_VALUE
mdefine_line|#define SCBRR_VALUE(bps) (((PCLK*2)+16*bps)/(32*bps)-1)
macro_line|#elif !defined(__H8300H__) &amp;&amp; !defined(__H8300S__)
DECL|macro|SCBRR_VALUE
mdefine_line|#define SCBRR_VALUE(bps) ((PCLK+16*bps)/(32*bps)-1)
macro_line|#else
DECL|macro|SCBRR_VALUE
mdefine_line|#define SCBRR_VALUE(bps) (((CONFIG_CPU_CLOCK*1000/32)/bps)-1)
macro_line|#endif
DECL|macro|BPS_2400
mdefine_line|#define BPS_2400       SCBRR_VALUE(2400)
DECL|macro|BPS_4800
mdefine_line|#define BPS_4800       SCBRR_VALUE(4800)
DECL|macro|BPS_9600
mdefine_line|#define BPS_9600       SCBRR_VALUE(9600)
DECL|macro|BPS_19200
mdefine_line|#define BPS_19200      SCBRR_VALUE(19200)
DECL|macro|BPS_38400
mdefine_line|#define BPS_38400      SCBRR_VALUE(38400)
DECL|macro|BPS_57600
mdefine_line|#define BPS_57600      SCBRR_VALUE(57600)
DECL|macro|BPS_115200
mdefine_line|#define BPS_115200     SCBRR_VALUE(115200)
eof
