multiline_comment|/* $Id: sh-sci.h,v 1.8 2000/03/08 15:19:39 gniibe Exp $&n; *&n; *  linux/drivers/char/sh-sci.h&n; *&n; *  SuperH on-chip serial module support.  (SCI with no FIFO / with FIFO)&n; *  Copyright (C) 1999, 2000  Niibe Yutaka&n; *  Copyright (C) 2000  Greg Banks&n; *  Modified to support multiple serial ports. Stuart Menefy (May 2000).&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Values for sci_port-&gt;type */
DECL|macro|PORT_SCI
mdefine_line|#define PORT_SCI  0
DECL|macro|PORT_SCIF
mdefine_line|#define PORT_SCIF 1
DECL|macro|PORT_IRDA
mdefine_line|#define PORT_IRDA 1&t;&t;/* XXX: temporary assignment */
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
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7708)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 1
DECL|macro|SCI_INIT
macro_line|# define SCI_INIT { &bslash;&n;  { {}, PORT_SCI,  0xfffffe80, SCI_IRQS,      sci_init_pins_sci  } &bslash;&n;}
DECL|macro|SCSPTR
macro_line|# define SCSPTR 0xffffff7c /* 8 bit */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x30 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCI_ONLY
macro_line|# define SCI_ONLY
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7707) || defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 3
DECL|macro|SCI_INIT
macro_line|# define SCI_INIT { &bslash;&n;  { {}, PORT_SCI,  0xfffffe80, SCI_IRQS,      sci_init_pins_sci  }, &bslash;&n;  { {}, PORT_SCIF, 0xA4000150, SH3_SCIF_IRQS, sci_init_pins_scif }, &bslash;&n;  { {}, PORT_SCIF, 0xA4000140, SH3_IRDA_IRQS, sci_init_pins_irda }  &bslash;&n;}
DECL|macro|SCPCR
macro_line|# define SCPCR  0xA4000116 /* 16 bit SCI and SCIF */
DECL|macro|SCPDR
macro_line|# define SCPDR  0xA4000136 /* 8  bit SCI and SCIF */
DECL|macro|SCSCR_INIT
macro_line|# define SCSCR_INIT(port)          0x30 /* TIE=0,RIE=0,TE=1,RE=1 */
DECL|macro|SCI_AND_SCIF
macro_line|# define SCI_AND_SCIF
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 2
DECL|macro|SCI_INIT
macro_line|# define SCI_INIT { &bslash;&n;  { {}, PORT_SCI,  0xffe00000, SCI_IRQS,      sci_init_pins_sci  }, &bslash;&n;  { {}, PORT_SCIF, 0xFFE80000, SH4_SCIF_IRQS, sci_init_pins_scif }  &bslash;&n;}
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
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|SCI_NPORTS
macro_line|# define SCI_NPORTS 2
DECL|macro|SCI_INIT
macro_line|# define SCI_INIT { &bslash;&n;  { {}, PORT_SCIF, 0xffe00000, STB1_SCIF1_IRQS, sci_init_pins_scif }, &bslash;&n;  { {}, PORT_SCIF, 0xffe80000, SH4_SCIF_IRQS,   sci_init_pins_scif }  &bslash;&n;}
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
multiline_comment|/*      SCI_CTRL_FLAGS_REIE 0x08  * 7750 SCIF */
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
mdefine_line|#define SCIF_ER    0x0080 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_TEND
mdefine_line|#define SCIF_TEND  0x0040 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_TDFE
mdefine_line|#define SCIF_TDFE  0x0020 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_BRK
mdefine_line|#define SCIF_BRK   0x0010 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_FER
mdefine_line|#define SCIF_FER   0x0008 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_PER
mdefine_line|#define SCIF_PER   0x0004 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_RDF
mdefine_line|#define SCIF_RDF   0x0002 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_DR
mdefine_line|#define SCIF_DR    0x0001 /* 7707 SCIF, 7709 SCIF, 7750 SCIF */
DECL|macro|SCIF_ERRORS
mdefine_line|#define SCIF_ERRORS ( SCIF_PER | SCIF_FER | SCIF_ER | SCIF_BRK)
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
DECL|macro|SCxSR_ORER
macro_line|# define SCxSR_ORER(port)&t;&t;0x0000
DECL|macro|SCxSR_FER
macro_line|# define SCxSR_FER(port)&t;&t;SCIF_FER
DECL|macro|SCxSR_PER
macro_line|# define SCxSR_PER(port)&t;&t;SCIF_PER
DECL|macro|SCxSR_BRK
macro_line|# define SCxSR_BRK(port)&t;&t;SCIF_BRK
DECL|macro|SCxSR_RDxF_CLEAR
macro_line|# define SCxSR_RDxF_CLEAR(port)&t;&t;0x00fc
DECL|macro|SCxSR_ERROR_CLEAR
macro_line|# define SCxSR_ERROR_CLEAR(port)&t;0x0073
DECL|macro|SCxSR_TDxE_CLEAR
macro_line|# define SCxSR_TDxE_CLEAR(port)&t;&t;0x00df
DECL|macro|SCxSR_BREAK_CLEAR
macro_line|# define SCxSR_BREAK_CLEAR(port)   &t;0x00e3
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
DECL|macro|SCFCR_MCE
mdefine_line|#define SCFCR_MCE   0x0008
DECL|macro|SCI_MAJOR
mdefine_line|#define SCI_MAJOR&t;&t;204
DECL|macro|SCI_MINOR_START
mdefine_line|#define SCI_MINOR_START&t;&t;8
multiline_comment|/* Generic serial flags */
DECL|macro|SCI_RX_THROTTLE
mdefine_line|#define SCI_RX_THROTTLE&t;&t;0x0000001
multiline_comment|/* generic serial tty */
DECL|macro|O_OTHER
mdefine_line|#define O_OTHER(tty)    &bslash;&n;      ((O_OLCUC(tty))  ||&bslash;&n;      (O_ONLCR(tty))   ||&bslash;&n;      (O_OCRNL(tty))   ||&bslash;&n;      (O_ONOCR(tty))   ||&bslash;&n;      (O_ONLRET(tty))  ||&bslash;&n;      (O_OFILL(tty))   ||&bslash;&n;      (O_OFDEL(tty))   ||&bslash;&n;      (O_NLDLY(tty))   ||&bslash;&n;      (O_CRDLY(tty))   ||&bslash;&n;      (O_TABDLY(tty))  ||&bslash;&n;      (O_BSDLY(tty))   ||&bslash;&n;      (O_VTDLY(tty))   ||&bslash;&n;      (O_FFDLY(tty)))
DECL|macro|I_OTHER
mdefine_line|#define I_OTHER(tty)    &bslash;&n;      ((I_INLCR(tty))  ||&bslash;&n;      (I_IGNCR(tty))   ||&bslash;&n;      (I_ICRNL(tty))   ||&bslash;&n;      (I_IUCLC(tty))   ||&bslash;&n;      (L_ISIG(tty)))
DECL|macro|SCI_MAGIC
mdefine_line|#define SCI_MAGIC 0xbabeface
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|SCI_EVENT_WRITE_WAKEUP
mdefine_line|#define SCI_EVENT_WRITE_WAKEUP&t;0
DECL|struct|sci_port
r_struct
id|sci_port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
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
id|sci_port
op_star
id|port
comma
r_int
r_int
id|cflag
)paren
suffix:semicolon
DECL|member|old_cflag
r_int
r_int
id|old_cflag
suffix:semicolon
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCI_IN
mdefine_line|#define SCI_IN(size, offset)&t;&t;&t;&t;&t;&bslash;&n;  unsigned int addr = port-&gt;base + (offset);&t;&t;&t;&bslash;&n;  if ((size) == 8) { &t;&t;&t;&t;&t;&t;&bslash;&n;    return ctrl_inb(addr);&t;&t;&t;&t;&t;&bslash;&n;  } else {&t;&t;&t;&t;&t; &t;&t;&bslash;&n;    return ctrl_inw(addr);&t;&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|SCI_OUT
mdefine_line|#define SCI_OUT(size, offset, value)&t;&t;&t;&t;&bslash;&n;  unsigned int addr = port-&gt;base + (offset);&t;&t;&t;&bslash;&n;  if ((size) == 8) { &t;&t;&t;&t;&t;&t;&bslash;&n;    ctrl_outb(value, addr);&t;&t;&t;&t;&t;&bslash;&n;  } else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    ctrl_outw(value, addr);&t;&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|CPU_SCIx_FNS
mdefine_line|#define CPU_SCIx_FNS(name, sci_offset, sci_size, scif_offset, scif_size)&bslash;&n;  static inline unsigned int sci_##name##_in(struct sci_port* port)&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (port-&gt;type == PORT_SCI) { &t;&t;&t;&t;&t;&bslash;&n;      SCI_IN(sci_size, sci_offset)&t;&t;&t;&t;&t;&bslash;&n;    } else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      SCI_IN(scif_size, scif_offset);&t;&t; &t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  static inline void sci_##name##_out(struct sci_port* port, unsigned int value) &bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (port-&gt;type == PORT_SCI) {&t;&t;&t;&t;&t;&bslash;&n;      SCI_OUT(sci_size, sci_offset, value)&t;&t;&t;&t;&bslash;&n;    } else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      SCI_OUT(scif_size, scif_offset, value);&t;&t;&t;&t;&bslash;&n;    }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  }
DECL|macro|CPU_SCIF_FNS
mdefine_line|#define CPU_SCIF_FNS(name, scif_offset, scif_size)&t;&t;&t;&t;&bslash;&n;  static inline unsigned int sci_##name##_in(struct sci_port* port)&t;&bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    SCI_IN(scif_size, scif_offset);&t;&t; &t;&t;&t;&bslash;&n;  }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  static inline void sci_##name##_out(struct sci_port* port, unsigned int value) &bslash;&n;  {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    SCI_OUT(scif_size, scif_offset, value);&t;&t;&t;&t;&bslash;&n;  }
macro_line|#ifdef __sh3__
DECL|macro|SCIx_FNS
mdefine_line|#define SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh4_sci_offset, sh4_sci_size, &bslash;&n;&t;&t; sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size) &bslash;&n;  CPU_SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh3_scif_offset, sh3_scif_size)
DECL|macro|SCIF_FNS
mdefine_line|#define SCIF_FNS(name, sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size) &bslash;&n;  CPU_SCIF_FNS(name, sh3_scif_offset, sh3_scif_size)
macro_line|#else
DECL|macro|SCIx_FNS
mdefine_line|#define SCIx_FNS(name, sh3_sci_offset, sh3_sci_size, sh4_sci_offset, sh4_sci_size, &bslash;&n;&t;&t; sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size) &bslash;&n;  CPU_SCIx_FNS(name, sh4_sci_offset, sh4_sci_size, sh4_scif_offset, sh4_scif_size)
DECL|macro|SCIF_FNS
mdefine_line|#define SCIF_FNS(name, sh3_scif_offset, sh3_scif_size, sh4_scif_offset, sh4_scif_size) &bslash;&n;  CPU_SCIF_FNS(name, sh4_scif_offset, sh4_scif_size)
macro_line|#endif
multiline_comment|/*      reg      SCI/SH3   SCI/SH4  SCIF/SH3   SCIF/SH4  */
multiline_comment|/*      name     off  sz   off  sz   off  sz   off  sz   */
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
DECL|macro|sci_in
mdefine_line|#define sci_in(port, reg) sci_##reg##_in(port)
DECL|macro|sci_out
mdefine_line|#define sci_out(port, reg, value) sci_##reg##_out(port, value)
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7708)
DECL|function|sci_rxd_in
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|sci_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;base
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
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|sci_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;base
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
id|port-&gt;base
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
id|port-&gt;base
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
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750)
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|sci_port
op_star
id|port
)paren
(brace
macro_line|#ifndef SCIF_ONLY
r_if
c_cond
(paren
id|port-&gt;base
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
id|port-&gt;base
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
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_ST40STB1)
r_static
r_inline
r_int
id|sci_rxd_in
c_func
(paren
r_struct
id|sci_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;base
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
macro_line|#endif
multiline_comment|/*&n; * Values for the BitRate Register (SCBRR)&n; *&n; * The values are actually divisors for a frequency which can&n; * be internal to the SH3 (14.7456MHz) or derived from an external&n; * clock source.  This driver assumes the internal clock is used;&n; * to support using an external clock source, config options or&n; * possibly command-line options would need to be added.&n; *&n; * Also, to support speeds below 2400 (why?) the lower 2 bits of&n; * the SCSMR register would also need to be set to non-zero values.&n; *&n; * -- Greg Banks 27Feb2000&n; *&n; * Answer: The SCBRR register is only eight bits, and the value in&n; * it gets larger with lower baud rates. At around 2400 (depending on&n; * the peripherial module clock) you run out of bits. However the&n; * lower two bits of SCSMR allow the module clock to be divided down,&n; * scaling the value which is needed in SCBRR.&n; *&n; * -- Stuart Menefy - 23 May 2000&n; *&n; * I meant, why would anyone bother with bitrates below 2400.&n; *&n; * -- Greg Banks - 7Jul2000&n; *&n; * You &quot;speedist&quot;!  How will I use my 110bps ASR-33 teletype with paper&n; * tape reader as a console!&n; *&n; * -- Mitch Davis - 15 Jul 2000&n; */
DECL|macro|PCLK
mdefine_line|#define PCLK           (current_cpu_data.module_clock)
DECL|macro|SCBRR_VALUE
mdefine_line|#define SCBRR_VALUE(bps) ((PCLK+16*bps)/(32*bps)-1)
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
