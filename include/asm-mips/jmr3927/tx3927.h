multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Toshiba Corporation&n; */
macro_line|#ifndef __ASM_TX3927_H
DECL|macro|__ASM_TX3927_H
mdefine_line|#define __ASM_TX3927_H
macro_line|#include &lt;asm/jmr3927/txx927.h&gt;
DECL|macro|TX3927_SDRAMC_REG
mdefine_line|#define TX3927_SDRAMC_REG&t;0xfffe8000
DECL|macro|TX3927_ROMC_REG
mdefine_line|#define TX3927_ROMC_REG&t;&t;0xfffe9000
DECL|macro|TX3927_DMA_REG
mdefine_line|#define TX3927_DMA_REG&t;&t;0xfffeb000
DECL|macro|TX3927_IRC_REG
mdefine_line|#define TX3927_IRC_REG&t;&t;0xfffec000
DECL|macro|TX3927_PCIC_REG
mdefine_line|#define TX3927_PCIC_REG&t;&t;0xfffed000
DECL|macro|TX3927_CCFG_REG
mdefine_line|#define TX3927_CCFG_REG&t;&t;0xfffee000
DECL|macro|TX3927_NR_TMR
mdefine_line|#define TX3927_NR_TMR&t;3
DECL|macro|TX3927_TMR_REG
mdefine_line|#define TX3927_TMR_REG(ch)&t;(0xfffef000 + (ch) * 0x100)
DECL|macro|TX3927_NR_SIO
mdefine_line|#define TX3927_NR_SIO&t;2
DECL|macro|TX3927_SIO_REG
mdefine_line|#define TX3927_SIO_REG(ch)&t;(0xfffef300 + (ch) * 0x100)
DECL|macro|TX3927_PIO_REG
mdefine_line|#define TX3927_PIO_REG&t;&t;0xfffef500
macro_line|#ifndef __ASSEMBLY__
DECL|struct|tx3927_sdramc_reg
r_struct
id|tx3927_sdramc_reg
(brace
DECL|member|cr
r_volatile
r_int
r_int
id|cr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|tr
r_volatile
r_int
r_int
id|tr
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmd
r_volatile
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|smrs
r_volatile
r_int
r_int
id|smrs
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx3927_romc_reg
r_struct
id|tx3927_romc_reg
(brace
DECL|member|cr
r_volatile
r_int
r_int
id|cr
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx3927_dma_reg
r_struct
id|tx3927_dma_reg
(brace
DECL|struct|tx3927_dma_ch_reg
r_struct
id|tx3927_dma_ch_reg
(brace
DECL|member|cha
r_volatile
r_int
r_int
id|cha
suffix:semicolon
DECL|member|sar
r_volatile
r_int
r_int
id|sar
suffix:semicolon
DECL|member|dar
r_volatile
r_int
r_int
id|dar
suffix:semicolon
DECL|member|cntr
r_volatile
r_int
r_int
id|cntr
suffix:semicolon
DECL|member|sair
r_volatile
r_int
r_int
id|sair
suffix:semicolon
DECL|member|dair
r_volatile
r_int
r_int
id|dair
suffix:semicolon
DECL|member|ccr
r_volatile
r_int
r_int
id|ccr
suffix:semicolon
DECL|member|csr
r_volatile
r_int
r_int
id|csr
suffix:semicolon
DECL|member|ch
)brace
id|ch
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dbr
r_volatile
r_int
r_int
id|dbr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|tdhr
r_volatile
r_int
r_int
id|tdhr
suffix:semicolon
DECL|member|mcr
r_volatile
r_int
r_int
id|mcr
suffix:semicolon
DECL|member|unused0
r_volatile
r_int
r_int
id|unused0
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx3927_irc_reg
r_struct
id|tx3927_irc_reg
(brace
DECL|member|cer
r_volatile
r_int
r_int
id|cer
suffix:semicolon
DECL|member|cr
r_volatile
r_int
r_int
id|cr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|unused0
r_volatile
r_int
r_int
id|unused0
suffix:semicolon
DECL|member|ilr
r_volatile
r_int
r_int
id|ilr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|unused1
r_volatile
r_int
r_int
id|unused1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|imr
r_volatile
r_int
r_int
id|imr
suffix:semicolon
DECL|member|unused2
r_volatile
r_int
r_int
id|unused2
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|scr
r_volatile
r_int
r_int
id|scr
suffix:semicolon
DECL|member|unused3
r_volatile
r_int
r_int
id|unused3
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|ssr
r_volatile
r_int
r_int
id|ssr
suffix:semicolon
DECL|member|unused4
r_volatile
r_int
r_int
id|unused4
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|csr
r_volatile
r_int
r_int
id|csr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|endian_def_s2
mdefine_line|#define endian_def_s2(e1,e2)&t;&bslash;&n;&t;volatile unsigned short e1,e2
DECL|macro|endian_def_sb2
mdefine_line|#define endian_def_sb2(e1,e2,e3)&t;&bslash;&n;&t;volatile unsigned short e1;volatile unsigned char e2,e3
DECL|macro|endian_def_b2s
mdefine_line|#define endian_def_b2s(e1,e2,e3)&t;&bslash;&n;&t;volatile unsigned char e1,e2;volatile unsigned short e3
DECL|macro|endian_def_b4
mdefine_line|#define endian_def_b4(e1,e2,e3,e4)&t;&bslash;&n;&t;volatile unsigned char e1,e2,e3,e4
macro_line|#else
DECL|macro|endian_def_s2
mdefine_line|#define endian_def_s2(e1,e2)&t;&bslash;&n;&t;volatile unsigned short e2,e1
DECL|macro|endian_def_sb2
mdefine_line|#define endian_def_sb2(e1,e2,e3)&t;&bslash;&n;&t;volatile unsigned char e3,e2;volatile unsigned short e1
DECL|macro|endian_def_b2s
mdefine_line|#define endian_def_b2s(e1,e2,e3)&t;&bslash;&n;&t;volatile unsigned short e3;volatile unsigned char e2,e1
DECL|macro|endian_def_b4
mdefine_line|#define endian_def_b4(e1,e2,e3,e4)&t;&bslash;&n;&t;volatile unsigned char e4,e3,e2,e1
macro_line|#endif
DECL|struct|tx3927_pcic_reg
r_struct
id|tx3927_pcic_reg
(brace
id|endian_def_s2
c_func
(paren
id|did
comma
id|vid
)paren
suffix:semicolon
id|endian_def_s2
c_func
(paren
id|pcistat
comma
id|pcicmd
)paren
suffix:semicolon
id|endian_def_b4
c_func
(paren
id|cc
comma
id|scc
comma
id|rpli
comma
id|rid
)paren
suffix:semicolon
id|endian_def_b4
c_func
(paren
id|unused0
comma
id|ht
comma
id|mlt
comma
id|cls
)paren
suffix:semicolon
DECL|member|ioba
r_volatile
r_int
r_int
id|ioba
suffix:semicolon
multiline_comment|/* +10 */
DECL|member|mba
r_volatile
r_int
r_int
id|mba
suffix:semicolon
DECL|member|unused1
r_volatile
r_int
r_int
id|unused1
(braket
l_int|5
)braket
suffix:semicolon
id|endian_def_s2
c_func
(paren
id|svid
comma
id|ssvid
)paren
suffix:semicolon
DECL|member|unused2
r_volatile
r_int
r_int
id|unused2
suffix:semicolon
multiline_comment|/* +30 */
id|endian_def_sb2
c_func
(paren
id|unused3
comma
id|unused4
comma
id|capptr
)paren
suffix:semicolon
DECL|member|unused5
r_volatile
r_int
r_int
id|unused5
suffix:semicolon
id|endian_def_b4
c_func
(paren
id|ml
comma
id|mg
comma
id|ip
comma
id|il
)paren
suffix:semicolon
DECL|member|unused6
r_volatile
r_int
r_int
id|unused6
suffix:semicolon
multiline_comment|/* +40 */
DECL|member|istat
r_volatile
r_int
r_int
id|istat
suffix:semicolon
DECL|member|iim
r_volatile
r_int
r_int
id|iim
suffix:semicolon
DECL|member|rrt
r_volatile
r_int
r_int
id|rrt
suffix:semicolon
DECL|member|unused7
r_volatile
r_int
r_int
id|unused7
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* +50 */
DECL|member|ipbmma
r_volatile
r_int
r_int
id|ipbmma
suffix:semicolon
DECL|member|ipbioma
r_volatile
r_int
r_int
id|ipbioma
suffix:semicolon
multiline_comment|/* +60 */
DECL|member|ilbmma
r_volatile
r_int
r_int
id|ilbmma
suffix:semicolon
DECL|member|ilbioma
r_volatile
r_int
r_int
id|ilbioma
suffix:semicolon
DECL|member|unused8
r_volatile
r_int
r_int
id|unused8
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|tc
r_volatile
r_int
r_int
id|tc
suffix:semicolon
multiline_comment|/* +90 */
DECL|member|tstat
r_volatile
r_int
r_int
id|tstat
suffix:semicolon
DECL|member|tim
r_volatile
r_int
r_int
id|tim
suffix:semicolon
DECL|member|tccmd
r_volatile
r_int
r_int
id|tccmd
suffix:semicolon
DECL|member|pcirrt
r_volatile
r_int
r_int
id|pcirrt
suffix:semicolon
multiline_comment|/* +a0 */
DECL|member|pcirrt_cmd
r_volatile
r_int
r_int
id|pcirrt_cmd
suffix:semicolon
DECL|member|pcirrdt
r_volatile
r_int
r_int
id|pcirrdt
suffix:semicolon
DECL|member|unused9
r_volatile
r_int
r_int
id|unused9
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tlboap
r_volatile
r_int
r_int
id|tlboap
suffix:semicolon
DECL|member|tlbiap
r_volatile
r_int
r_int
id|tlbiap
suffix:semicolon
DECL|member|tlbmma
r_volatile
r_int
r_int
id|tlbmma
suffix:semicolon
multiline_comment|/* +c0 */
DECL|member|tlbioma
r_volatile
r_int
r_int
id|tlbioma
suffix:semicolon
DECL|member|sc_msg
r_volatile
r_int
r_int
id|sc_msg
suffix:semicolon
DECL|member|sc_be
r_volatile
r_int
r_int
id|sc_be
suffix:semicolon
DECL|member|tbl
r_volatile
r_int
r_int
id|tbl
suffix:semicolon
multiline_comment|/* +d0 */
DECL|member|unused10
r_volatile
r_int
r_int
id|unused10
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|pwmng
r_volatile
r_int
r_int
id|pwmng
suffix:semicolon
multiline_comment|/* +e0 */
DECL|member|pwmngs
r_volatile
r_int
r_int
id|pwmngs
suffix:semicolon
DECL|member|unused11
r_volatile
r_int
r_int
id|unused11
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|req_trace
r_volatile
r_int
r_int
id|req_trace
suffix:semicolon
multiline_comment|/* +100 */
DECL|member|pbapmc
r_volatile
r_int
r_int
id|pbapmc
suffix:semicolon
DECL|member|pbapms
r_volatile
r_int
r_int
id|pbapms
suffix:semicolon
DECL|member|pbapmim
r_volatile
r_int
r_int
id|pbapmim
suffix:semicolon
DECL|member|bm
r_volatile
r_int
r_int
id|bm
suffix:semicolon
multiline_comment|/* +110 */
DECL|member|cpcibrs
r_volatile
r_int
r_int
id|cpcibrs
suffix:semicolon
DECL|member|cpcibgs
r_volatile
r_int
r_int
id|cpcibgs
suffix:semicolon
DECL|member|pbacs
r_volatile
r_int
r_int
id|pbacs
suffix:semicolon
DECL|member|iobas
r_volatile
r_int
r_int
id|iobas
suffix:semicolon
multiline_comment|/* +120 */
DECL|member|mbas
r_volatile
r_int
r_int
id|mbas
suffix:semicolon
DECL|member|lbc
r_volatile
r_int
r_int
id|lbc
suffix:semicolon
DECL|member|lbstat
r_volatile
r_int
r_int
id|lbstat
suffix:semicolon
DECL|member|lbim
r_volatile
r_int
r_int
id|lbim
suffix:semicolon
multiline_comment|/* +130 */
DECL|member|pcistatim
r_volatile
r_int
r_int
id|pcistatim
suffix:semicolon
DECL|member|ica
r_volatile
r_int
r_int
id|ica
suffix:semicolon
DECL|member|icd
r_volatile
r_int
r_int
id|icd
suffix:semicolon
DECL|member|iiadp
r_volatile
r_int
r_int
id|iiadp
suffix:semicolon
multiline_comment|/* +140 */
DECL|member|iscdp
r_volatile
r_int
r_int
id|iscdp
suffix:semicolon
DECL|member|mmas
r_volatile
r_int
r_int
id|mmas
suffix:semicolon
DECL|member|iomas
r_volatile
r_int
r_int
id|iomas
suffix:semicolon
DECL|member|ipciaddr
r_volatile
r_int
r_int
id|ipciaddr
suffix:semicolon
multiline_comment|/* +150 */
DECL|member|ipcidata
r_volatile
r_int
r_int
id|ipcidata
suffix:semicolon
DECL|member|ipcibe
r_volatile
r_int
r_int
id|ipcibe
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx3927_ccfg_reg
r_struct
id|tx3927_ccfg_reg
(brace
DECL|member|ccfg
r_volatile
r_int
r_int
id|ccfg
suffix:semicolon
DECL|member|crir
r_volatile
r_int
r_int
id|crir
suffix:semicolon
DECL|member|pcfg
r_volatile
r_int
r_int
id|pcfg
suffix:semicolon
DECL|member|tear
r_volatile
r_int
r_int
id|tear
suffix:semicolon
DECL|member|pdcr
r_volatile
r_int
r_int
id|pdcr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * SDRAMC&n; */
multiline_comment|/*&n; * ROMC&n; */
multiline_comment|/*&n; * DMA&n; */
multiline_comment|/* bits for MCR */
DECL|macro|TX3927_DMA_MCR_EIS
mdefine_line|#define TX3927_DMA_MCR_EIS(ch)&t;(0x10000000&lt;&lt;(ch))
DECL|macro|TX3927_DMA_MCR_DIS
mdefine_line|#define TX3927_DMA_MCR_DIS(ch)&t;(0x01000000&lt;&lt;(ch))
DECL|macro|TX3927_DMA_MCR_RSFIF
mdefine_line|#define TX3927_DMA_MCR_RSFIF&t;0x00000080
DECL|macro|TX3927_DMA_MCR_FIFUM
mdefine_line|#define TX3927_DMA_MCR_FIFUM(ch)&t;(0x00000008&lt;&lt;(ch))
DECL|macro|TX3927_DMA_MCR_LE
mdefine_line|#define TX3927_DMA_MCR_LE&t;0x00000004
DECL|macro|TX3927_DMA_MCR_RPRT
mdefine_line|#define TX3927_DMA_MCR_RPRT&t;0x00000002
DECL|macro|TX3927_DMA_MCR_MSTEN
mdefine_line|#define TX3927_DMA_MCR_MSTEN&t;0x00000001
multiline_comment|/* bits for CCRn */
DECL|macro|TX3927_DMA_CCR_DBINH
mdefine_line|#define TX3927_DMA_CCR_DBINH&t;0x04000000
DECL|macro|TX3927_DMA_CCR_SBINH
mdefine_line|#define TX3927_DMA_CCR_SBINH&t;0x02000000
DECL|macro|TX3927_DMA_CCR_CHRST
mdefine_line|#define TX3927_DMA_CCR_CHRST&t;0x01000000
DECL|macro|TX3927_DMA_CCR_RVBYTE
mdefine_line|#define TX3927_DMA_CCR_RVBYTE&t;0x00800000
DECL|macro|TX3927_DMA_CCR_ACKPOL
mdefine_line|#define TX3927_DMA_CCR_ACKPOL&t;0x00400000
DECL|macro|TX3927_DMA_CCR_REQPL
mdefine_line|#define TX3927_DMA_CCR_REQPL&t;0x00200000
DECL|macro|TX3927_DMA_CCR_EGREQ
mdefine_line|#define TX3927_DMA_CCR_EGREQ&t;0x00100000
DECL|macro|TX3927_DMA_CCR_CHDN
mdefine_line|#define TX3927_DMA_CCR_CHDN&t;0x00080000
DECL|macro|TX3927_DMA_CCR_DNCTL
mdefine_line|#define TX3927_DMA_CCR_DNCTL&t;0x00060000
DECL|macro|TX3927_DMA_CCR_EXTRQ
mdefine_line|#define TX3927_DMA_CCR_EXTRQ&t;0x00010000
DECL|macro|TX3927_DMA_CCR_INTRQD
mdefine_line|#define TX3927_DMA_CCR_INTRQD&t;0x0000e000
DECL|macro|TX3927_DMA_CCR_INTENE
mdefine_line|#define TX3927_DMA_CCR_INTENE&t;0x00001000
DECL|macro|TX3927_DMA_CCR_INTENC
mdefine_line|#define TX3927_DMA_CCR_INTENC&t;0x00000800
DECL|macro|TX3927_DMA_CCR_INTENT
mdefine_line|#define TX3927_DMA_CCR_INTENT&t;0x00000400
DECL|macro|TX3927_DMA_CCR_CHNEN
mdefine_line|#define TX3927_DMA_CCR_CHNEN&t;0x00000200
DECL|macro|TX3927_DMA_CCR_XFACT
mdefine_line|#define TX3927_DMA_CCR_XFACT&t;0x00000100
DECL|macro|TX3927_DMA_CCR_SNOP
mdefine_line|#define TX3927_DMA_CCR_SNOP&t;0x00000080
DECL|macro|TX3927_DMA_CCR_DSTINC
mdefine_line|#define TX3927_DMA_CCR_DSTINC&t;0x00000040
DECL|macro|TX3927_DMA_CCR_SRCINC
mdefine_line|#define TX3927_DMA_CCR_SRCINC&t;0x00000020
DECL|macro|TX3927_DMA_CCR_XFSZ
mdefine_line|#define TX3927_DMA_CCR_XFSZ(order)&t;(((order) &lt;&lt; 2) &amp; 0x0000001c)
DECL|macro|TX3927_DMA_CCR_XFSZ_1W
mdefine_line|#define TX3927_DMA_CCR_XFSZ_1W&t;TX3927_DMA_CCR_XFSZ(2)
DECL|macro|TX3927_DMA_CCR_XFSZ_4W
mdefine_line|#define TX3927_DMA_CCR_XFSZ_4W&t;TX3927_DMA_CCR_XFSZ(4)
DECL|macro|TX3927_DMA_CCR_XFSZ_8W
mdefine_line|#define TX3927_DMA_CCR_XFSZ_8W&t;TX3927_DMA_CCR_XFSZ(5)
DECL|macro|TX3927_DMA_CCR_XFSZ_16W
mdefine_line|#define TX3927_DMA_CCR_XFSZ_16W&t;TX3927_DMA_CCR_XFSZ(6)
DECL|macro|TX3927_DMA_CCR_XFSZ_32W
mdefine_line|#define TX3927_DMA_CCR_XFSZ_32W&t;TX3927_DMA_CCR_XFSZ(7)
DECL|macro|TX3927_DMA_CCR_MEMIO
mdefine_line|#define TX3927_DMA_CCR_MEMIO&t;0x00000002
DECL|macro|TX3927_DMA_CCR_ONEAD
mdefine_line|#define TX3927_DMA_CCR_ONEAD&t;0x00000001
multiline_comment|/* bits for CSRn */
DECL|macro|TX3927_DMA_CSR_CHNACT
mdefine_line|#define TX3927_DMA_CSR_CHNACT&t;0x00000100
DECL|macro|TX3927_DMA_CSR_ABCHC
mdefine_line|#define TX3927_DMA_CSR_ABCHC&t;0x00000080
DECL|macro|TX3927_DMA_CSR_NCHNC
mdefine_line|#define TX3927_DMA_CSR_NCHNC&t;0x00000040
DECL|macro|TX3927_DMA_CSR_NTRNFC
mdefine_line|#define TX3927_DMA_CSR_NTRNFC&t;0x00000020
DECL|macro|TX3927_DMA_CSR_EXTDN
mdefine_line|#define TX3927_DMA_CSR_EXTDN&t;0x00000010
DECL|macro|TX3927_DMA_CSR_CFERR
mdefine_line|#define TX3927_DMA_CSR_CFERR&t;0x00000008
DECL|macro|TX3927_DMA_CSR_CHERR
mdefine_line|#define TX3927_DMA_CSR_CHERR&t;0x00000004
DECL|macro|TX3927_DMA_CSR_DESERR
mdefine_line|#define TX3927_DMA_CSR_DESERR&t;0x00000002
DECL|macro|TX3927_DMA_CSR_SORERR
mdefine_line|#define TX3927_DMA_CSR_SORERR&t;0x00000001
multiline_comment|/*&n; * IRC&n; */
DECL|macro|TX3927_IR_MAX_LEVEL
mdefine_line|#define TX3927_IR_MAX_LEVEL&t;7
multiline_comment|/* IRCER : Int. Control Enable */
DECL|macro|TX3927_IRCER_ICE
mdefine_line|#define TX3927_IRCER_ICE&t;0x00000001
multiline_comment|/* IRCR : Int. Control */
DECL|macro|TX3927_IRCR_LOW
mdefine_line|#define TX3927_IRCR_LOW&t;0x00000000
DECL|macro|TX3927_IRCR_HIGH
mdefine_line|#define TX3927_IRCR_HIGH&t;0x00000001
DECL|macro|TX3927_IRCR_DOWN
mdefine_line|#define TX3927_IRCR_DOWN&t;0x00000002
DECL|macro|TX3927_IRCR_UP
mdefine_line|#define TX3927_IRCR_UP&t;0x00000003
multiline_comment|/* IRSCR : Int. Status Control */
DECL|macro|TX3927_IRSCR_EIClrE
mdefine_line|#define TX3927_IRSCR_EIClrE&t;0x00000100
DECL|macro|TX3927_IRSCR_EIClr_MASK
mdefine_line|#define TX3927_IRSCR_EIClr_MASK&t;0x0000000f
multiline_comment|/* IRCSR : Int. Current Status */
DECL|macro|TX3927_IRCSR_IF
mdefine_line|#define TX3927_IRCSR_IF&t;0x00010000
DECL|macro|TX3927_IRCSR_ILV_MASK
mdefine_line|#define TX3927_IRCSR_ILV_MASK&t;0x00000700
DECL|macro|TX3927_IRCSR_IVL_MASK
mdefine_line|#define TX3927_IRCSR_IVL_MASK&t;0x0000001f
DECL|macro|TX3927_IR_INT0
mdefine_line|#define TX3927_IR_INT0&t;0
DECL|macro|TX3927_IR_INT1
mdefine_line|#define TX3927_IR_INT1&t;1
DECL|macro|TX3927_IR_INT2
mdefine_line|#define TX3927_IR_INT2&t;2
DECL|macro|TX3927_IR_INT3
mdefine_line|#define TX3927_IR_INT3&t;3
DECL|macro|TX3927_IR_INT4
mdefine_line|#define TX3927_IR_INT4&t;4
DECL|macro|TX3927_IR_INT5
mdefine_line|#define TX3927_IR_INT5&t;5
DECL|macro|TX3927_IR_SIO0
mdefine_line|#define TX3927_IR_SIO0&t;6
DECL|macro|TX3927_IR_SIO1
mdefine_line|#define TX3927_IR_SIO1&t;7
DECL|macro|TX3927_IR_SIO
mdefine_line|#define TX3927_IR_SIO(ch)&t;(6 + (ch))
DECL|macro|TX3927_IR_DMA
mdefine_line|#define TX3927_IR_DMA&t;8
DECL|macro|TX3927_IR_PIO
mdefine_line|#define TX3927_IR_PIO&t;9
DECL|macro|TX3927_IR_PCI
mdefine_line|#define TX3927_IR_PCI&t;10
DECL|macro|TX3927_IR_TMR0
mdefine_line|#define TX3927_IR_TMR0&t;13
DECL|macro|TX3927_IR_TMR1
mdefine_line|#define TX3927_IR_TMR1&t;14
DECL|macro|TX3927_IR_TMR2
mdefine_line|#define TX3927_IR_TMR2&t;15
DECL|macro|TX3927_NUM_IR
mdefine_line|#define TX3927_NUM_IR&t;16
multiline_comment|/*&n; * PCIC&n; */
multiline_comment|/* bits for PCICMD */
multiline_comment|/* see PCI_COMMAND_XXX in linux/pci.h */
multiline_comment|/* bits for PCISTAT */
multiline_comment|/* see PCI_STATUS_XXX in linux/pci.h */
DECL|macro|PCI_STATUS_NEW_CAP
mdefine_line|#define PCI_STATUS_NEW_CAP&t;0x0010
multiline_comment|/* bits for TC */
DECL|macro|TX3927_PCIC_TC_OF16E
mdefine_line|#define TX3927_PCIC_TC_OF16E&t;0x00000020
DECL|macro|TX3927_PCIC_TC_IF8E
mdefine_line|#define TX3927_PCIC_TC_IF8E&t;0x00000010
DECL|macro|TX3927_PCIC_TC_OF8E
mdefine_line|#define TX3927_PCIC_TC_OF8E&t;0x00000008
multiline_comment|/* bits for IOBA/MBA */
multiline_comment|/* see PCI_BASE_ADDRESS_XXX in linux/pci.h */
multiline_comment|/* bits for PBAPMC */
DECL|macro|TX3927_PCIC_PBAPMC_RPBA
mdefine_line|#define TX3927_PCIC_PBAPMC_RPBA&t;0x00000004
DECL|macro|TX3927_PCIC_PBAPMC_PBAEN
mdefine_line|#define TX3927_PCIC_PBAPMC_PBAEN&t;0x00000002
DECL|macro|TX3927_PCIC_PBAPMC_BMCEN
mdefine_line|#define TX3927_PCIC_PBAPMC_BMCEN&t;0x00000001
multiline_comment|/* bits for LBSTAT/LBIM */
DECL|macro|TX3927_PCIC_LBIM_ALL
mdefine_line|#define TX3927_PCIC_LBIM_ALL&t;0x0000003e
multiline_comment|/* bits for PCISTATIM (see also PCI_STATUS_XXX in linux/pci.h */
DECL|macro|TX3927_PCIC_PCISTATIM_ALL
mdefine_line|#define TX3927_PCIC_PCISTATIM_ALL&t;0x0000f900
multiline_comment|/* bits for LBC */
DECL|macro|TX3927_PCIC_LBC_IBSE
mdefine_line|#define TX3927_PCIC_LBC_IBSE&t;0x00004000
DECL|macro|TX3927_PCIC_LBC_TIBSE
mdefine_line|#define TX3927_PCIC_LBC_TIBSE&t;0x00002000
DECL|macro|TX3927_PCIC_LBC_TMFBSE
mdefine_line|#define TX3927_PCIC_LBC_TMFBSE&t;0x00001000
DECL|macro|TX3927_PCIC_LBC_HRST
mdefine_line|#define TX3927_PCIC_LBC_HRST&t;0x00000800
DECL|macro|TX3927_PCIC_LBC_SRST
mdefine_line|#define TX3927_PCIC_LBC_SRST&t;0x00000400
DECL|macro|TX3927_PCIC_LBC_EPCAD
mdefine_line|#define TX3927_PCIC_LBC_EPCAD&t;0x00000200
DECL|macro|TX3927_PCIC_LBC_MSDSE
mdefine_line|#define TX3927_PCIC_LBC_MSDSE&t;0x00000100
DECL|macro|TX3927_PCIC_LBC_CRR
mdefine_line|#define TX3927_PCIC_LBC_CRR&t;0x00000080
DECL|macro|TX3927_PCIC_LBC_ILMDE
mdefine_line|#define TX3927_PCIC_LBC_ILMDE&t;0x00000040
DECL|macro|TX3927_PCIC_LBC_ILIDE
mdefine_line|#define TX3927_PCIC_LBC_ILIDE&t;0x00000020
DECL|macro|TX3927_PCIC_IDSEL_AD_TO_SLOT
mdefine_line|#define TX3927_PCIC_IDSEL_AD_TO_SLOT(ad)&t;((ad) - 11)
DECL|macro|TX3927_PCIC_MAX_DEVNU
mdefine_line|#define TX3927_PCIC_MAX_DEVNU&t;TX3927_PCIC_IDSEL_AD_TO_SLOT(32)
multiline_comment|/*&n; * CCFG&n; */
multiline_comment|/* CCFG : Chip Configuration */
DECL|macro|TX3927_CCFG_TLBOFF
mdefine_line|#define TX3927_CCFG_TLBOFF&t;0x00020000
DECL|macro|TX3927_CCFG_BEOW
mdefine_line|#define TX3927_CCFG_BEOW&t;0x00010000
DECL|macro|TX3927_CCFG_WR
mdefine_line|#define TX3927_CCFG_WR&t;0x00008000
DECL|macro|TX3927_CCFG_TOE
mdefine_line|#define TX3927_CCFG_TOE&t;0x00004000
DECL|macro|TX3927_CCFG_PCIXARB
mdefine_line|#define TX3927_CCFG_PCIXARB&t;0x00002000
DECL|macro|TX3927_CCFG_PCI3
mdefine_line|#define TX3927_CCFG_PCI3&t;0x00001000
DECL|macro|TX3927_CCFG_PSNP
mdefine_line|#define TX3927_CCFG_PSNP&t;0x00000800
DECL|macro|TX3927_CCFG_PPRI
mdefine_line|#define TX3927_CCFG_PPRI&t;0x00000400
DECL|macro|TX3927_CCFG_PLLM
mdefine_line|#define TX3927_CCFG_PLLM&t;0x00000030
DECL|macro|TX3927_CCFG_ENDIAN
mdefine_line|#define TX3927_CCFG_ENDIAN&t;0x00000004
DECL|macro|TX3927_CCFG_HALT
mdefine_line|#define TX3927_CCFG_HALT&t;0x00000002
DECL|macro|TX3927_CCFG_ACEHOLD
mdefine_line|#define TX3927_CCFG_ACEHOLD&t;0x00000001
multiline_comment|/* PCFG : Pin Configuration */
DECL|macro|TX3927_PCFG_SYSCLKEN
mdefine_line|#define TX3927_PCFG_SYSCLKEN&t;0x08000000
DECL|macro|TX3927_PCFG_SDRCLKEN_ALL
mdefine_line|#define TX3927_PCFG_SDRCLKEN_ALL&t;0x07c00000
DECL|macro|TX3927_PCFG_SDRCLKEN
mdefine_line|#define TX3927_PCFG_SDRCLKEN(ch)&t;(0x00400000&lt;&lt;(ch))
DECL|macro|TX3927_PCFG_PCICLKEN_ALL
mdefine_line|#define TX3927_PCFG_PCICLKEN_ALL&t;0x003c0000
DECL|macro|TX3927_PCFG_PCICLKEN
mdefine_line|#define TX3927_PCFG_PCICLKEN(ch)&t;(0x00040000&lt;&lt;(ch))
DECL|macro|TX3927_PCFG_SELALL
mdefine_line|#define TX3927_PCFG_SELALL&t;0x0003ffff
DECL|macro|TX3927_PCFG_SELCS
mdefine_line|#define TX3927_PCFG_SELCS&t;0x00020000
DECL|macro|TX3927_PCFG_SELDSF
mdefine_line|#define TX3927_PCFG_SELDSF&t;0x00010000
DECL|macro|TX3927_PCFG_SELSIOC_ALL
mdefine_line|#define TX3927_PCFG_SELSIOC_ALL&t;0x0000c000
DECL|macro|TX3927_PCFG_SELSIOC
mdefine_line|#define TX3927_PCFG_SELSIOC(ch)&t;(0x00004000&lt;&lt;(ch))
DECL|macro|TX3927_PCFG_SELSIO_ALL
mdefine_line|#define TX3927_PCFG_SELSIO_ALL&t;0x00003000
DECL|macro|TX3927_PCFG_SELSIO
mdefine_line|#define TX3927_PCFG_SELSIO(ch)&t;(0x00001000&lt;&lt;(ch))
DECL|macro|TX3927_PCFG_SELTMR_ALL
mdefine_line|#define TX3927_PCFG_SELTMR_ALL&t;0x00000e00
DECL|macro|TX3927_PCFG_SELTMR
mdefine_line|#define TX3927_PCFG_SELTMR(ch)&t;(0x00000200&lt;&lt;(ch))
DECL|macro|TX3927_PCFG_SELDONE
mdefine_line|#define TX3927_PCFG_SELDONE&t;0x00000100
DECL|macro|TX3927_PCFG_INTDMA_ALL
mdefine_line|#define TX3927_PCFG_INTDMA_ALL&t;0x000000f0
DECL|macro|TX3927_PCFG_INTDMA
mdefine_line|#define TX3927_PCFG_INTDMA(ch)&t;(0x00000010&lt;&lt;(ch))
DECL|macro|TX3927_PCFG_SELDMA_ALL
mdefine_line|#define TX3927_PCFG_SELDMA_ALL&t;0x0000000f
DECL|macro|TX3927_PCFG_SELDMA
mdefine_line|#define TX3927_PCFG_SELDMA(ch)&t;(0x00000001&lt;&lt;(ch))
macro_line|#ifndef __ASSEMBLY__
DECL|macro|tx3927_sdramcptr
mdefine_line|#define tx3927_sdramcptr&t;((struct tx3927_sdramc_reg *)TX3927_SDRAMC_REG)
DECL|macro|tx3927_romcptr
mdefine_line|#define tx3927_romcptr&t;&t;((struct tx3927_romc_reg *)TX3927_ROMC_REG)
DECL|macro|tx3927_dmaptr
mdefine_line|#define tx3927_dmaptr&t;&t;((struct tx3927_dma_reg *)TX3927_DMA_REG)
DECL|macro|tx3927_ircptr
mdefine_line|#define tx3927_ircptr&t;&t;((struct tx3927_irc_reg *)TX3927_IRC_REG)
DECL|macro|tx3927_pcicptr
mdefine_line|#define tx3927_pcicptr&t;&t;((struct tx3927_pcic_reg *)TX3927_PCIC_REG)
DECL|macro|tx3927_ccfgptr
mdefine_line|#define tx3927_ccfgptr&t;&t;((struct tx3927_ccfg_reg *)TX3927_CCFG_REG)
DECL|macro|tx3927_tmrptr
mdefine_line|#define tx3927_tmrptr(ch)&t;((struct txx927_tmr_reg *)TX3927_TMR_REG(ch))
DECL|macro|tx3927_sioptr
mdefine_line|#define tx3927_sioptr(ch)&t;((struct txx927_sio_reg *)TX3927_SIO_REG(ch))
DECL|macro|tx3927_pioptr
mdefine_line|#define tx3927_pioptr&t;&t;((struct txx927_pio_reg *)TX3927_PIO_REG)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_TX3927_H */
eof
