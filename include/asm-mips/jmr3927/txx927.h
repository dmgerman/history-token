multiline_comment|/*&n; * Common definitions for TX3927/TX4927&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Toshiba Corporation&n; */
macro_line|#ifndef __ASM_TXX927_H
DECL|macro|__ASM_TXX927_H
mdefine_line|#define __ASM_TXX927_H
macro_line|#ifndef __ASSEMBLY__
DECL|struct|txx927_tmr_reg
r_struct
id|txx927_tmr_reg
(brace
DECL|member|tcr
r_volatile
r_int
r_int
id|tcr
suffix:semicolon
DECL|member|tisr
r_volatile
r_int
r_int
id|tisr
suffix:semicolon
DECL|member|cpra
r_volatile
r_int
r_int
id|cpra
suffix:semicolon
DECL|member|cprb
r_volatile
r_int
r_int
id|cprb
suffix:semicolon
DECL|member|itmr
r_volatile
r_int
r_int
id|itmr
suffix:semicolon
DECL|member|unused0
r_volatile
r_int
r_int
id|unused0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ccdr
r_volatile
r_int
r_int
id|ccdr
suffix:semicolon
DECL|member|unused1
r_volatile
r_int
r_int
id|unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|pgmr
r_volatile
r_int
r_int
id|pgmr
suffix:semicolon
DECL|member|unused2
r_volatile
r_int
r_int
id|unused2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|wtmr
r_volatile
r_int
r_int
id|wtmr
suffix:semicolon
DECL|member|unused3
r_volatile
r_int
r_int
id|unused3
(braket
l_int|43
)braket
suffix:semicolon
DECL|member|trr
r_volatile
r_int
r_int
id|trr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|txx927_sio_reg
r_struct
id|txx927_sio_reg
(brace
DECL|member|lcr
r_volatile
r_int
r_int
id|lcr
suffix:semicolon
DECL|member|dicr
r_volatile
r_int
r_int
id|dicr
suffix:semicolon
DECL|member|disr
r_volatile
r_int
r_int
id|disr
suffix:semicolon
DECL|member|cisr
r_volatile
r_int
r_int
id|cisr
suffix:semicolon
DECL|member|fcr
r_volatile
r_int
r_int
id|fcr
suffix:semicolon
DECL|member|flcr
r_volatile
r_int
r_int
id|flcr
suffix:semicolon
DECL|member|bgr
r_volatile
r_int
r_int
id|bgr
suffix:semicolon
DECL|member|tfifo
r_volatile
r_int
r_int
id|tfifo
suffix:semicolon
DECL|member|rfifo
r_volatile
r_int
r_int
id|rfifo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|txx927_pio_reg
r_struct
id|txx927_pio_reg
(brace
DECL|member|dout
r_volatile
r_int
r_int
id|dout
suffix:semicolon
DECL|member|din
r_volatile
r_int
r_int
id|din
suffix:semicolon
DECL|member|dir
r_volatile
r_int
r_int
id|dir
suffix:semicolon
DECL|member|od
r_volatile
r_int
r_int
id|od
suffix:semicolon
DECL|member|flag
r_volatile
r_int
r_int
id|flag
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pol
r_volatile
r_int
r_int
id|pol
suffix:semicolon
DECL|member|intc
r_volatile
r_int
r_int
id|intc
suffix:semicolon
DECL|member|maskcpu
r_volatile
r_int
r_int
id|maskcpu
suffix:semicolon
DECL|member|maskext
r_volatile
r_int
r_int
id|maskext
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * TMR&n; */
multiline_comment|/* TMTCR : Timer Control */
DECL|macro|TXx927_TMTCR_TCE
mdefine_line|#define TXx927_TMTCR_TCE&t;0x00000080
DECL|macro|TXx927_TMTCR_CCDE
mdefine_line|#define TXx927_TMTCR_CCDE&t;0x00000040
DECL|macro|TXx927_TMTCR_CRE
mdefine_line|#define TXx927_TMTCR_CRE&t;0x00000020
DECL|macro|TXx927_TMTCR_ECES
mdefine_line|#define TXx927_TMTCR_ECES&t;0x00000008
DECL|macro|TXx927_TMTCR_CCS
mdefine_line|#define TXx927_TMTCR_CCS&t;0x00000004
DECL|macro|TXx927_TMTCR_TMODE_MASK
mdefine_line|#define TXx927_TMTCR_TMODE_MASK&t;0x00000003
DECL|macro|TXx927_TMTCR_TMODE_ITVL
mdefine_line|#define TXx927_TMTCR_TMODE_ITVL&t;0x00000000
multiline_comment|/* TMTISR : Timer Int. Status */
DECL|macro|TXx927_TMTISR_TPIBS
mdefine_line|#define TXx927_TMTISR_TPIBS&t;0x00000004
DECL|macro|TXx927_TMTISR_TPIAS
mdefine_line|#define TXx927_TMTISR_TPIAS&t;0x00000002
DECL|macro|TXx927_TMTISR_TIIS
mdefine_line|#define TXx927_TMTISR_TIIS&t;0x00000001
multiline_comment|/* TMTITMR : Interval Timer Mode */
DECL|macro|TXx927_TMTITMR_TIIE
mdefine_line|#define TXx927_TMTITMR_TIIE&t;0x00008000
DECL|macro|TXx927_TMTITMR_TZCE
mdefine_line|#define TXx927_TMTITMR_TZCE&t;0x00000001
multiline_comment|/*&n; * SIO&n; */
multiline_comment|/* SILCR : Line Control */
DECL|macro|TXx927_SILCR_SCS_MASK
mdefine_line|#define TXx927_SILCR_SCS_MASK&t;0x00000060
DECL|macro|TXx927_SILCR_SCS_IMCLK
mdefine_line|#define TXx927_SILCR_SCS_IMCLK&t;0x00000000
DECL|macro|TXx927_SILCR_SCS_IMCLK_BG
mdefine_line|#define TXx927_SILCR_SCS_IMCLK_BG&t;0x00000020
DECL|macro|TXx927_SILCR_SCS_SCLK
mdefine_line|#define TXx927_SILCR_SCS_SCLK&t;0x00000040
DECL|macro|TXx927_SILCR_SCS_SCLK_BG
mdefine_line|#define TXx927_SILCR_SCS_SCLK_BG&t;0x00000060
DECL|macro|TXx927_SILCR_UEPS
mdefine_line|#define TXx927_SILCR_UEPS&t;0x00000010
DECL|macro|TXx927_SILCR_UPEN
mdefine_line|#define TXx927_SILCR_UPEN&t;0x00000008
DECL|macro|TXx927_SILCR_USBL_MASK
mdefine_line|#define TXx927_SILCR_USBL_MASK&t;0x00000004
DECL|macro|TXx927_SILCR_USBL_1BIT
mdefine_line|#define TXx927_SILCR_USBL_1BIT&t;0x00000004
DECL|macro|TXx927_SILCR_USBL_2BIT
mdefine_line|#define TXx927_SILCR_USBL_2BIT&t;0x00000000
DECL|macro|TXx927_SILCR_UMODE_MASK
mdefine_line|#define TXx927_SILCR_UMODE_MASK&t;0x00000003
DECL|macro|TXx927_SILCR_UMODE_8BIT
mdefine_line|#define TXx927_SILCR_UMODE_8BIT&t;0x00000000
DECL|macro|TXx927_SILCR_UMODE_7BIT
mdefine_line|#define TXx927_SILCR_UMODE_7BIT&t;0x00000001
multiline_comment|/* SIDICR : DMA/Int. Control */
DECL|macro|TXx927_SIDICR_TDE
mdefine_line|#define TXx927_SIDICR_TDE&t;0x00008000
DECL|macro|TXx927_SIDICR_RDE
mdefine_line|#define TXx927_SIDICR_RDE&t;0x00004000
DECL|macro|TXx927_SIDICR_TIE
mdefine_line|#define TXx927_SIDICR_TIE&t;0x00002000
DECL|macro|TXx927_SIDICR_RIE
mdefine_line|#define TXx927_SIDICR_RIE&t;0x00001000
DECL|macro|TXx927_SIDICR_SPIE
mdefine_line|#define TXx927_SIDICR_SPIE&t;0x00000800
DECL|macro|TXx927_SIDICR_CTSAC
mdefine_line|#define TXx927_SIDICR_CTSAC&t;0x00000600
DECL|macro|TXx927_SIDICR_STIE_MASK
mdefine_line|#define TXx927_SIDICR_STIE_MASK&t;0x0000003f
DECL|macro|TXx927_SIDICR_STIE_OERS
mdefine_line|#define TXx927_SIDICR_STIE_OERS&t;&t;0x00000020
DECL|macro|TXx927_SIDICR_STIE_CTSS
mdefine_line|#define TXx927_SIDICR_STIE_CTSS&t;&t;0x00000010
DECL|macro|TXx927_SIDICR_STIE_RBRKD
mdefine_line|#define TXx927_SIDICR_STIE_RBRKD&t;0x00000008
DECL|macro|TXx927_SIDICR_STIE_TRDY
mdefine_line|#define TXx927_SIDICR_STIE_TRDY&t;&t;0x00000004
DECL|macro|TXx927_SIDICR_STIE_TXALS
mdefine_line|#define TXx927_SIDICR_STIE_TXALS&t;0x00000002
DECL|macro|TXx927_SIDICR_STIE_UBRKD
mdefine_line|#define TXx927_SIDICR_STIE_UBRKD&t;0x00000001
multiline_comment|/* SIDISR : DMA/Int. Status */
DECL|macro|TXx927_SIDISR_UBRK
mdefine_line|#define TXx927_SIDISR_UBRK&t;0x00008000
DECL|macro|TXx927_SIDISR_UVALID
mdefine_line|#define TXx927_SIDISR_UVALID&t;0x00004000
DECL|macro|TXx927_SIDISR_UFER
mdefine_line|#define TXx927_SIDISR_UFER&t;0x00002000
DECL|macro|TXx927_SIDISR_UPER
mdefine_line|#define TXx927_SIDISR_UPER&t;0x00001000
DECL|macro|TXx927_SIDISR_UOER
mdefine_line|#define TXx927_SIDISR_UOER&t;0x00000800
DECL|macro|TXx927_SIDISR_ERI
mdefine_line|#define TXx927_SIDISR_ERI&t;0x00000400
DECL|macro|TXx927_SIDISR_TOUT
mdefine_line|#define TXx927_SIDISR_TOUT&t;0x00000200
DECL|macro|TXx927_SIDISR_TDIS
mdefine_line|#define TXx927_SIDISR_TDIS&t;0x00000100
DECL|macro|TXx927_SIDISR_RDIS
mdefine_line|#define TXx927_SIDISR_RDIS&t;0x00000080
DECL|macro|TXx927_SIDISR_STIS
mdefine_line|#define TXx927_SIDISR_STIS&t;0x00000040
DECL|macro|TXx927_SIDISR_RFDN_MASK
mdefine_line|#define TXx927_SIDISR_RFDN_MASK&t;0x0000001f
multiline_comment|/* SICISR : Change Int. Status */
DECL|macro|TXx927_SICISR_OERS
mdefine_line|#define TXx927_SICISR_OERS&t;0x00000020
DECL|macro|TXx927_SICISR_CTSS
mdefine_line|#define TXx927_SICISR_CTSS&t;0x00000010
DECL|macro|TXx927_SICISR_RBRKD
mdefine_line|#define TXx927_SICISR_RBRKD&t;0x00000008
DECL|macro|TXx927_SICISR_TRDY
mdefine_line|#define TXx927_SICISR_TRDY&t;0x00000004
DECL|macro|TXx927_SICISR_TXALS
mdefine_line|#define TXx927_SICISR_TXALS&t;0x00000002
DECL|macro|TXx927_SICISR_UBRKD
mdefine_line|#define TXx927_SICISR_UBRKD&t;0x00000001
multiline_comment|/* SIFCR : FIFO Control */
DECL|macro|TXx927_SIFCR_SWRST
mdefine_line|#define TXx927_SIFCR_SWRST&t;0x00008000
DECL|macro|TXx927_SIFCR_RDIL_MASK
mdefine_line|#define TXx927_SIFCR_RDIL_MASK&t;0x00000180
DECL|macro|TXx927_SIFCR_RDIL_1
mdefine_line|#define TXx927_SIFCR_RDIL_1&t;0x00000000
DECL|macro|TXx927_SIFCR_RDIL_4
mdefine_line|#define TXx927_SIFCR_RDIL_4&t;0x00000080
DECL|macro|TXx927_SIFCR_RDIL_8
mdefine_line|#define TXx927_SIFCR_RDIL_8&t;0x00000100
DECL|macro|TXx927_SIFCR_RDIL_12
mdefine_line|#define TXx927_SIFCR_RDIL_12&t;0x00000180
DECL|macro|TXx927_SIFCR_RDIL_MAX
mdefine_line|#define TXx927_SIFCR_RDIL_MAX&t;0x00000180
DECL|macro|TXx927_SIFCR_TDIL_MASK
mdefine_line|#define TXx927_SIFCR_TDIL_MASK&t;0x00000018
DECL|macro|TXx927_SIFCR_TDIL_MASK
mdefine_line|#define TXx927_SIFCR_TDIL_MASK&t;0x00000018
DECL|macro|TXx927_SIFCR_TDIL_1
mdefine_line|#define TXx927_SIFCR_TDIL_1&t;0x00000000
DECL|macro|TXx927_SIFCR_TDIL_4
mdefine_line|#define TXx927_SIFCR_TDIL_4&t;0x00000001
DECL|macro|TXx927_SIFCR_TDIL_8
mdefine_line|#define TXx927_SIFCR_TDIL_8&t;0x00000010
DECL|macro|TXx927_SIFCR_TDIL_MAX
mdefine_line|#define TXx927_SIFCR_TDIL_MAX&t;0x00000010
DECL|macro|TXx927_SIFCR_TFRST
mdefine_line|#define TXx927_SIFCR_TFRST&t;0x00000004
DECL|macro|TXx927_SIFCR_RFRST
mdefine_line|#define TXx927_SIFCR_RFRST&t;0x00000002
DECL|macro|TXx927_SIFCR_FRSTE
mdefine_line|#define TXx927_SIFCR_FRSTE&t;0x00000001
DECL|macro|TXx927_SIO_TX_FIFO
mdefine_line|#define TXx927_SIO_TX_FIFO&t;8
DECL|macro|TXx927_SIO_RX_FIFO
mdefine_line|#define TXx927_SIO_RX_FIFO&t;16
multiline_comment|/* SIFLCR : Flow Control */
DECL|macro|TXx927_SIFLCR_RCS
mdefine_line|#define TXx927_SIFLCR_RCS&t;0x00001000
DECL|macro|TXx927_SIFLCR_TES
mdefine_line|#define TXx927_SIFLCR_TES&t;0x00000800
DECL|macro|TXx927_SIFLCR_RTSSC
mdefine_line|#define TXx927_SIFLCR_RTSSC&t;0x00000200
DECL|macro|TXx927_SIFLCR_RSDE
mdefine_line|#define TXx927_SIFLCR_RSDE&t;0x00000100
DECL|macro|TXx927_SIFLCR_TSDE
mdefine_line|#define TXx927_SIFLCR_TSDE&t;0x00000080
DECL|macro|TXx927_SIFLCR_RTSTL_MASK
mdefine_line|#define TXx927_SIFLCR_RTSTL_MASK&t;0x0000001e
DECL|macro|TXx927_SIFLCR_RTSTL_MAX
mdefine_line|#define TXx927_SIFLCR_RTSTL_MAX&t;0x0000001e
DECL|macro|TXx927_SIFLCR_TBRK
mdefine_line|#define TXx927_SIFLCR_TBRK&t;0x00000001
multiline_comment|/* SIBGR : Baudrate Control */
DECL|macro|TXx927_SIBGR_BCLK_MASK
mdefine_line|#define TXx927_SIBGR_BCLK_MASK&t;0x00000300
DECL|macro|TXx927_SIBGR_BCLK_T0
mdefine_line|#define TXx927_SIBGR_BCLK_T0&t;0x00000000
DECL|macro|TXx927_SIBGR_BCLK_T2
mdefine_line|#define TXx927_SIBGR_BCLK_T2&t;0x00000100
DECL|macro|TXx927_SIBGR_BCLK_T4
mdefine_line|#define TXx927_SIBGR_BCLK_T4&t;0x00000200
DECL|macro|TXx927_SIBGR_BCLK_T6
mdefine_line|#define TXx927_SIBGR_BCLK_T6&t;0x00000300
DECL|macro|TXx927_SIBGR_BRD_MASK
mdefine_line|#define TXx927_SIBGR_BRD_MASK&t;0x000000ff
multiline_comment|/*&n; * PIO&n; */
macro_line|#endif /* __ASM_TXX927_H */
eof
