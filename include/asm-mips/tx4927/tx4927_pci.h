multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2001 Toshiba Corporation&n; */
macro_line|#ifndef __ASM_TX4927_TX4927_PCI_H 
DECL|macro|__ASM_TX4927_TX4927_PCI_H
mdefine_line|#define __ASM_TX4927_TX4927_PCI_H 
DECL|macro|TX4927_CCFG_TOE
mdefine_line|#define TX4927_CCFG_TOE 0x00004000
DECL|macro|TX4927_PCIMEM
mdefine_line|#define TX4927_PCIMEM      0x08000000
DECL|macro|TX4927_PCIMEM_SIZE
mdefine_line|#define TX4927_PCIMEM_SIZE 0x08000000
DECL|macro|TX4927_PCIIO
mdefine_line|#define TX4927_PCIIO       0x16000000
DECL|macro|TX4927_PCIIO_SIZE
mdefine_line|#define TX4927_PCIIO_SIZE  0x01000000
DECL|macro|TX4927_SDRAMC_REG
mdefine_line|#define TX4927_SDRAMC_REG       0xff1f8000
DECL|macro|TX4927_EBUSC_REG
mdefine_line|#define TX4927_EBUSC_REG        0xff1f9000
DECL|macro|TX4927_PCIC_REG
mdefine_line|#define TX4927_PCIC_REG         0xff1fd000
DECL|macro|TX4927_CCFG_REG
mdefine_line|#define TX4927_CCFG_REG         0xff1fe000
DECL|macro|TX4927_IRC_REG
mdefine_line|#define TX4927_IRC_REG          0xff1ff600
DECL|macro|TX4927_CE3
mdefine_line|#define TX4927_CE3      0x17f00000      /* 1M */
DECL|macro|TX4927_PCIRESET_ADDR
mdefine_line|#define TX4927_PCIRESET_ADDR    0x1c00f006
DECL|macro|TX4927_PCI_CLK_ADDR
mdefine_line|#define TX4927_PCI_CLK_ADDR     (KSEG1 + TX4927_CE3 + 0x00040020)
DECL|macro|TX4927_IMSTAT_ADDR
mdefine_line|#define TX4927_IMSTAT_ADDR(n)   (KSEG1 + TX4927_CE3 + 0x0004001a + (n))
DECL|macro|tx4927_imstat_ptr
mdefine_line|#define tx4927_imstat_ptr(n)    &bslash;&n;        ((volatile unsigned char *)TX4927_IMSTAT_ADDR(n))
multiline_comment|/* bits for ISTAT3/IMASK3/IMSTAT3 */
DECL|macro|TX4927_INT3B_PCID
mdefine_line|#define TX4927_INT3B_PCID       0
DECL|macro|TX4927_INT3B_PCIC
mdefine_line|#define TX4927_INT3B_PCIC       1
DECL|macro|TX4927_INT3B_PCIB
mdefine_line|#define TX4927_INT3B_PCIB       2
DECL|macro|TX4927_INT3B_PCIA
mdefine_line|#define TX4927_INT3B_PCIA       3
DECL|macro|TX4927_INT3F_PCID
mdefine_line|#define TX4927_INT3F_PCID       (1 &lt;&lt; TX4927_INT3B_PCID)
DECL|macro|TX4927_INT3F_PCIC
mdefine_line|#define TX4927_INT3F_PCIC       (1 &lt;&lt; TX4927_INT3B_PCIC)
DECL|macro|TX4927_INT3F_PCIB
mdefine_line|#define TX4927_INT3F_PCIB       (1 &lt;&lt; TX4927_INT3B_PCIB)
DECL|macro|TX4927_INT3F_PCIA
mdefine_line|#define TX4927_INT3F_PCIA       (1 &lt;&lt; TX4927_INT3B_PCIA)
multiline_comment|/* bits for PCI_CLK (S6) */
DECL|macro|TX4927_PCI_CLK_HOST
mdefine_line|#define TX4927_PCI_CLK_HOST     0x80
DECL|macro|TX4927_PCI_CLK_MASK
mdefine_line|#define TX4927_PCI_CLK_MASK     (0x0f &lt;&lt; 3)
DECL|macro|TX4927_PCI_CLK_33
mdefine_line|#define TX4927_PCI_CLK_33       (0x01 &lt;&lt; 3)
DECL|macro|TX4927_PCI_CLK_25
mdefine_line|#define TX4927_PCI_CLK_25       (0x04 &lt;&lt; 3)
DECL|macro|TX4927_PCI_CLK_66
mdefine_line|#define TX4927_PCI_CLK_66       (0x09 &lt;&lt; 3)
DECL|macro|TX4927_PCI_CLK_50
mdefine_line|#define TX4927_PCI_CLK_50       (0x0c &lt;&lt; 3)
DECL|macro|TX4927_PCI_CLK_ACK
mdefine_line|#define TX4927_PCI_CLK_ACK      0x04
DECL|macro|TX4927_PCI_CLK_ACE
mdefine_line|#define TX4927_PCI_CLK_ACE      0x02
DECL|macro|TX4927_PCI_CLK_ENDIAN
mdefine_line|#define TX4927_PCI_CLK_ENDIAN   0x01
DECL|macro|TX4927_NR_IRQ_LOCAL
mdefine_line|#define TX4927_NR_IRQ_LOCAL     (8+16)
DECL|macro|TX4927_NR_IRQ_IRC
mdefine_line|#define TX4927_NR_IRQ_IRC       32      /* On-Chip IRC */
DECL|macro|TX4927_IR_PCIC
mdefine_line|#define TX4927_IR_PCIC  &t;16
DECL|macro|TX4927_IR_PCIERR
mdefine_line|#define TX4927_IR_PCIERR        22
DECL|macro|TX4927_IR_PCIPMA
mdefine_line|#define TX4927_IR_PCIPMA        23
DECL|macro|TX4927_IRQ_IRC_PCIC
mdefine_line|#define TX4927_IRQ_IRC_PCIC     (TX4927_NR_IRQ_LOCAL + TX4927_IR_PCIC)
DECL|macro|TX4927_IRQ_IRC_PCIERR
mdefine_line|#define TX4927_IRQ_IRC_PCIERR   (TX4927_NR_IRQ_LOCAL + TX4927_IR_PCIERR)
DECL|macro|TX4927_IRQ_IOC1
mdefine_line|#define TX4927_IRQ_IOC1         (TX4927_NR_IRQ_LOCAL + TX4927_NR_IRQ_IRC)
DECL|macro|TX4927_IRQ_IOC_PCID
mdefine_line|#define TX4927_IRQ_IOC_PCID     (TX4927_IRQ_IOC1 + TX4927_INT3B_PCID)
DECL|macro|TX4927_IRQ_IOC_PCIC
mdefine_line|#define TX4927_IRQ_IOC_PCIC     (TX4927_IRQ_IOC1 + TX4927_INT3B_PCIC)
DECL|macro|TX4927_IRQ_IOC_PCIB
mdefine_line|#define TX4927_IRQ_IOC_PCIB     (TX4927_IRQ_IOC1 + TX4927_INT3B_PCIB)
DECL|macro|TX4927_IRQ_IOC_PCIA
mdefine_line|#define TX4927_IRQ_IOC_PCIA     (TX4927_IRQ_IOC1 + TX4927_INT3B_PCIA)
macro_line|#ifdef _LANGUAGE_ASSEMBLY
DECL|macro|_CONST64
mdefine_line|#define _CONST64(c)     c
macro_line|#else
DECL|macro|_CONST64
mdefine_line|#define _CONST64(c)     c##ull
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|tx4927_pcireset_ptr
mdefine_line|#define tx4927_pcireset_ptr     &bslash;&n;        ((volatile unsigned char *)TX4927_PCIRESET_ADDR)
DECL|macro|tx4927_pci_clk_ptr
mdefine_line|#define tx4927_pci_clk_ptr      &bslash;&n;        ((volatile unsigned char *)TX4927_PCI_CLK_ADDR)
DECL|struct|tx4927_sdramc_reg
r_struct
id|tx4927_sdramc_reg
(brace
DECL|member|cr
r_volatile
r_int
r_int
r_int
id|cr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|unused0
r_volatile
r_int
r_int
r_int
id|unused0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|tr
r_volatile
r_int
r_int
r_int
id|tr
suffix:semicolon
DECL|member|unused1
r_volatile
r_int
r_int
r_int
id|unused1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cmd
r_volatile
r_int
r_int
r_int
id|cmd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx4927_ebusc_reg
r_struct
id|tx4927_ebusc_reg
(brace
DECL|member|cr
r_volatile
r_int
r_int
r_int
id|cr
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx4927_ccfg_reg
r_struct
id|tx4927_ccfg_reg
(brace
DECL|member|ccfg
r_volatile
r_int
r_int
r_int
id|ccfg
suffix:semicolon
DECL|member|crir
r_volatile
r_int
r_int
r_int
id|crir
suffix:semicolon
DECL|member|pcfg
r_volatile
r_int
r_int
r_int
id|pcfg
suffix:semicolon
DECL|member|tear
r_volatile
r_int
r_int
r_int
id|tear
suffix:semicolon
DECL|member|clkctr
r_volatile
r_int
r_int
r_int
id|clkctr
suffix:semicolon
DECL|member|unused0
r_volatile
r_int
r_int
r_int
id|unused0
suffix:semicolon
DECL|member|garbc
r_volatile
r_int
r_int
r_int
id|garbc
suffix:semicolon
DECL|member|unused1
r_volatile
r_int
r_int
r_int
id|unused1
suffix:semicolon
DECL|member|unused2
r_volatile
r_int
r_int
r_int
id|unused2
suffix:semicolon
DECL|member|ramp
r_volatile
r_int
r_int
r_int
id|ramp
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx4927_irc_reg
r_struct
id|tx4927_irc_reg
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
DECL|struct|tx4927_pcic_reg
r_struct
id|tx4927_pcic_reg
(brace
DECL|member|pciid
r_volatile
r_int
r_int
id|pciid
suffix:semicolon
DECL|member|pcistatus
r_volatile
r_int
r_int
id|pcistatus
suffix:semicolon
DECL|member|pciccrev
r_volatile
r_int
r_int
id|pciccrev
suffix:semicolon
DECL|member|pcicfg1
r_volatile
r_int
r_int
id|pcicfg1
suffix:semicolon
DECL|member|p2gm0plbase
r_volatile
r_int
r_int
id|p2gm0plbase
suffix:semicolon
multiline_comment|/* +10 */
DECL|member|p2gm0pubase
r_volatile
r_int
r_int
id|p2gm0pubase
suffix:semicolon
DECL|member|p2gm1plbase
r_volatile
r_int
r_int
id|p2gm1plbase
suffix:semicolon
DECL|member|p2gm1pubase
r_volatile
r_int
r_int
id|p2gm1pubase
suffix:semicolon
DECL|member|p2gm2pbase
r_volatile
r_int
r_int
id|p2gm2pbase
suffix:semicolon
multiline_comment|/* +20 */
DECL|member|p2giopbase
r_volatile
r_int
r_int
id|p2giopbase
suffix:semicolon
DECL|member|unused0
r_volatile
r_int
r_int
id|unused0
suffix:semicolon
DECL|member|pcisid
r_volatile
r_int
r_int
id|pcisid
suffix:semicolon
DECL|member|unused1
r_volatile
r_int
r_int
id|unused1
suffix:semicolon
multiline_comment|/* +30 */
DECL|member|pcicapptr
r_volatile
r_int
r_int
id|pcicapptr
suffix:semicolon
DECL|member|unused2
r_volatile
r_int
r_int
id|unused2
suffix:semicolon
DECL|member|pcicfg2
r_volatile
r_int
r_int
id|pcicfg2
suffix:semicolon
DECL|member|g2ptocnt
r_volatile
r_int
r_int
id|g2ptocnt
suffix:semicolon
multiline_comment|/* +40 */
DECL|member|unused3
r_volatile
r_int
r_int
id|unused3
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|g2pstatus
r_volatile
r_int
r_int
id|g2pstatus
suffix:semicolon
multiline_comment|/* +80 */
DECL|member|g2pmask
r_volatile
r_int
r_int
id|g2pmask
suffix:semicolon
DECL|member|pcisstatus
r_volatile
r_int
r_int
id|pcisstatus
suffix:semicolon
DECL|member|pcimask
r_volatile
r_int
r_int
id|pcimask
suffix:semicolon
DECL|member|p2gcfg
r_volatile
r_int
r_int
id|p2gcfg
suffix:semicolon
multiline_comment|/* +90 */
DECL|member|p2gstatus
r_volatile
r_int
r_int
id|p2gstatus
suffix:semicolon
DECL|member|p2gmask
r_volatile
r_int
r_int
id|p2gmask
suffix:semicolon
DECL|member|p2gccmd
r_volatile
r_int
r_int
id|p2gccmd
suffix:semicolon
DECL|member|unused4
r_volatile
r_int
r_int
id|unused4
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* +a0 */
DECL|member|pbareqport
r_volatile
r_int
r_int
id|pbareqport
suffix:semicolon
multiline_comment|/* +100 */
DECL|member|pbacfg
r_volatile
r_int
r_int
id|pbacfg
suffix:semicolon
DECL|member|pbastatus
r_volatile
r_int
r_int
id|pbastatus
suffix:semicolon
DECL|member|pbamask
r_volatile
r_int
r_int
id|pbamask
suffix:semicolon
DECL|member|pbabm
r_volatile
r_int
r_int
id|pbabm
suffix:semicolon
multiline_comment|/* +110 */
DECL|member|pbacreq
r_volatile
r_int
r_int
id|pbacreq
suffix:semicolon
DECL|member|pbacgnt
r_volatile
r_int
r_int
id|pbacgnt
suffix:semicolon
DECL|member|pbacstate
r_volatile
r_int
r_int
id|pbacstate
suffix:semicolon
DECL|member|g2pmgbase
r_volatile
r_int
r_int
r_int
id|g2pmgbase
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* +120 */
DECL|member|g2piogbase
r_volatile
r_int
r_int
r_int
id|g2piogbase
suffix:semicolon
DECL|member|g2pmmask
r_volatile
r_int
r_int
id|g2pmmask
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* +140 */
DECL|member|g2piomask
r_volatile
r_int
r_int
id|g2piomask
suffix:semicolon
DECL|member|g2pmpbase
r_volatile
r_int
r_int
r_int
id|g2pmpbase
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* +150 */
DECL|member|g2piopbase
r_volatile
r_int
r_int
r_int
id|g2piopbase
suffix:semicolon
DECL|member|pciccfg
r_volatile
r_int
r_int
id|pciccfg
suffix:semicolon
multiline_comment|/* +170 */
DECL|member|pcicstatus
r_volatile
r_int
r_int
id|pcicstatus
suffix:semicolon
DECL|member|pcicmask
r_volatile
r_int
r_int
id|pcicmask
suffix:semicolon
DECL|member|unused5
r_volatile
r_int
r_int
id|unused5
suffix:semicolon
DECL|member|p2gmgbase
r_volatile
r_int
r_int
r_int
id|p2gmgbase
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* +180 */
DECL|member|p2giogbase
r_volatile
r_int
r_int
r_int
id|p2giogbase
suffix:semicolon
DECL|member|g2pcfgadrs
r_volatile
r_int
r_int
id|g2pcfgadrs
suffix:semicolon
multiline_comment|/* +1a0 */
DECL|member|g2pcfgdata
r_volatile
r_int
r_int
id|g2pcfgdata
suffix:semicolon
DECL|member|unused6
r_volatile
r_int
r_int
id|unused6
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|g2pintack
r_volatile
r_int
r_int
id|g2pintack
suffix:semicolon
DECL|member|g2pspc
r_volatile
r_int
r_int
id|g2pspc
suffix:semicolon
DECL|member|unused7
r_volatile
r_int
r_int
id|unused7
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* +1d0 */
DECL|member|pdmca
r_volatile
r_int
r_int
r_int
id|pdmca
suffix:semicolon
multiline_comment|/* +200 */
DECL|member|pdmga
r_volatile
r_int
r_int
r_int
id|pdmga
suffix:semicolon
DECL|member|pdmpa
r_volatile
r_int
r_int
r_int
id|pdmpa
suffix:semicolon
DECL|member|pdmcut
r_volatile
r_int
r_int
r_int
id|pdmcut
suffix:semicolon
DECL|member|pdmcnt
r_volatile
r_int
r_int
r_int
id|pdmcnt
suffix:semicolon
multiline_comment|/* +220 */
DECL|member|pdmsts
r_volatile
r_int
r_int
r_int
id|pdmsts
suffix:semicolon
DECL|member|unused8
r_volatile
r_int
r_int
r_int
id|unused8
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pdmdb
r_volatile
r_int
r_int
r_int
id|pdmdb
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* +240 */
DECL|member|pdmtdh
r_volatile
r_int
r_int
r_int
id|pdmtdh
suffix:semicolon
multiline_comment|/* +260 */
DECL|member|pdmdms
r_volatile
r_int
r_int
r_int
id|pdmdms
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
multiline_comment|/* IRCSR : Int. Current Status */
DECL|macro|TX4927_IRCSR_IF
mdefine_line|#define TX4927_IRCSR_IF         0x00010000
DECL|macro|TX4927_IRCSR_ILV_MASK
mdefine_line|#define TX4927_IRCSR_ILV_MASK   0x00000700
DECL|macro|TX4927_IRCSR_IVL_MASK
mdefine_line|#define TX4927_IRCSR_IVL_MASK   0x0000001f
multiline_comment|/*&n; * PCIC&n; */
multiline_comment|/* bits for G2PSTATUS/G2PMASK */
DECL|macro|TX4927_PCIC_G2PSTATUS_ALL
mdefine_line|#define TX4927_PCIC_G2PSTATUS_ALL       0x00000003
DECL|macro|TX4927_PCIC_G2PSTATUS_TTOE
mdefine_line|#define TX4927_PCIC_G2PSTATUS_TTOE      0x00000002
DECL|macro|TX4927_PCIC_G2PSTATUS_RTOE
mdefine_line|#define TX4927_PCIC_G2PSTATUS_RTOE      0x00000001
multiline_comment|/* bits for PCIMASK (see also PCI_STATUS_XXX in linux/pci.h */
DECL|macro|TX4927_PCIC_PCISTATUS_ALL
mdefine_line|#define TX4927_PCIC_PCISTATUS_ALL       0x0000f900
multiline_comment|/* bits for PBACFG */
DECL|macro|TX4927_PCIC_PBACFG_RPBA
mdefine_line|#define TX4927_PCIC_PBACFG_RPBA 0x00000004
DECL|macro|TX4927_PCIC_PBACFG_PBAEN
mdefine_line|#define TX4927_PCIC_PBACFG_PBAEN        0x00000002
DECL|macro|TX4927_PCIC_PBACFG_BMCEN
mdefine_line|#define TX4927_PCIC_PBACFG_BMCEN        0x00000001
multiline_comment|/* bits for G2PMnGBASE */
DECL|macro|TX4927_PCIC_G2PMnGBASE_BSDIS
mdefine_line|#define TX4927_PCIC_G2PMnGBASE_BSDIS    _CONST64(0x0000002000000000)
DECL|macro|TX4927_PCIC_G2PMnGBASE_ECHG
mdefine_line|#define TX4927_PCIC_G2PMnGBASE_ECHG     _CONST64(0x0000001000000000)
multiline_comment|/* bits for G2PIOGBASE */
DECL|macro|TX4927_PCIC_G2PIOGBASE_BSDIS
mdefine_line|#define TX4927_PCIC_G2PIOGBASE_BSDIS    _CONST64(0x0000002000000000)
DECL|macro|TX4927_PCIC_G2PIOGBASE_ECHG
mdefine_line|#define TX4927_PCIC_G2PIOGBASE_ECHG     _CONST64(0x0000001000000000)
multiline_comment|/* bits for PCICSTATUS/PCICMASK */
DECL|macro|TX4927_PCIC_PCICSTATUS_ALL
mdefine_line|#define TX4927_PCIC_PCICSTATUS_ALL      0x000007dc
multiline_comment|/* bits for PCICCFG */
DECL|macro|TX4927_PCIC_PCICCFG_LBWC_MASK
mdefine_line|#define TX4927_PCIC_PCICCFG_LBWC_MASK   0x0fff0000
DECL|macro|TX4927_PCIC_PCICCFG_HRST
mdefine_line|#define TX4927_PCIC_PCICCFG_HRST        0x00000800
DECL|macro|TX4927_PCIC_PCICCFG_SRST
mdefine_line|#define TX4927_PCIC_PCICCFG_SRST        0x00000400
DECL|macro|TX4927_PCIC_PCICCFG_IRBER
mdefine_line|#define TX4927_PCIC_PCICCFG_IRBER       0x00000200
DECL|macro|TX4927_PCIC_PCICCFG_IMSE0
mdefine_line|#define TX4927_PCIC_PCICCFG_IMSE0       0x00000100
DECL|macro|TX4927_PCIC_PCICCFG_IMSE1
mdefine_line|#define TX4927_PCIC_PCICCFG_IMSE1       0x00000080
DECL|macro|TX4927_PCIC_PCICCFG_IMSE2
mdefine_line|#define TX4927_PCIC_PCICCFG_IMSE2       0x00000040
DECL|macro|TX4927_PCIC_PCICCFG_IISE
mdefine_line|#define TX4927_PCIC_PCICCFG_IISE        0x00000020
DECL|macro|TX4927_PCIC_PCICCFG_ATR
mdefine_line|#define TX4927_PCIC_PCICCFG_ATR 0x00000010
DECL|macro|TX4927_PCIC_PCICCFG_ICAE
mdefine_line|#define TX4927_PCIC_PCICCFG_ICAE        0x00000008
multiline_comment|/* bits for P2GMnGBASE */
DECL|macro|TX4927_PCIC_P2GMnGBASE_TMEMEN
mdefine_line|#define TX4927_PCIC_P2GMnGBASE_TMEMEN   _CONST64(0x0000004000000000)
DECL|macro|TX4927_PCIC_P2GMnGBASE_TBSDIS
mdefine_line|#define TX4927_PCIC_P2GMnGBASE_TBSDIS   _CONST64(0x0000002000000000)
DECL|macro|TX4927_PCIC_P2GMnGBASE_TECHG
mdefine_line|#define TX4927_PCIC_P2GMnGBASE_TECHG    _CONST64(0x0000001000000000)
multiline_comment|/* bits for P2GIOGBASE */
DECL|macro|TX4927_PCIC_P2GIOGBASE_TIOEN
mdefine_line|#define TX4927_PCIC_P2GIOGBASE_TIOEN    _CONST64(0x0000004000000000)
DECL|macro|TX4927_PCIC_P2GIOGBASE_TBSDIS
mdefine_line|#define TX4927_PCIC_P2GIOGBASE_TBSDIS   _CONST64(0x0000002000000000)
DECL|macro|TX4927_PCIC_P2GIOGBASE_TECHG
mdefine_line|#define TX4927_PCIC_P2GIOGBASE_TECHG    _CONST64(0x0000001000000000)
DECL|macro|TX4927_PCIC_IDSEL_AD_TO_SLOT
mdefine_line|#define TX4927_PCIC_IDSEL_AD_TO_SLOT(ad)        ((ad) - 11)
DECL|macro|TX4927_PCIC_MAX_DEVNU
mdefine_line|#define TX4927_PCIC_MAX_DEVNU   TX4927_PCIC_IDSEL_AD_TO_SLOT(32)
multiline_comment|/*&n; * CCFG&n; */
multiline_comment|/* CCFG : Chip Configuration */
DECL|macro|TX4927_CCFG_PCI66
mdefine_line|#define TX4927_CCFG_PCI66       0x00800000
DECL|macro|TX4927_CCFG_PCIMIDE
mdefine_line|#define TX4927_CCFG_PCIMIDE     0x00400000
DECL|macro|TX4927_CCFG_PCIXARB
mdefine_line|#define TX4927_CCFG_PCIXARB     0x00002000
DECL|macro|TX4927_CCFG_PCIDIVMODE_MASK
mdefine_line|#define TX4927_CCFG_PCIDIVMODE_MASK     0x00001800
DECL|macro|TX4927_CCFG_PCIDIVMODE_2_5
mdefine_line|#define TX4927_CCFG_PCIDIVMODE_2_5      0x00000000
DECL|macro|TX4927_CCFG_PCIDIVMODE_3
mdefine_line|#define TX4927_CCFG_PCIDIVMODE_3        0x00000800
DECL|macro|TX4927_CCFG_PCIDIVMODE_5
mdefine_line|#define TX4927_CCFG_PCIDIVMODE_5        0x00001000
DECL|macro|TX4927_CCFG_PCIDIVMODE_6
mdefine_line|#define TX4927_CCFG_PCIDIVMODE_6        0x00001800
multiline_comment|/* PCFG : Pin Configuration */
DECL|macro|TX4927_PCFG_PCICLKEN_ALL
mdefine_line|#define TX4927_PCFG_PCICLKEN_ALL        0x003f0000
DECL|macro|TX4927_PCFG_PCICLKEN
mdefine_line|#define TX4927_PCFG_PCICLKEN(ch)        (0x00010000&lt;&lt;(ch))
multiline_comment|/* CLKCTR : Clock Control */
DECL|macro|TX4927_CLKCTR_PCICKD
mdefine_line|#define TX4927_CLKCTR_PCICKD    0x00400000
DECL|macro|TX4927_CLKCTR_PCIRST
mdefine_line|#define TX4927_CLKCTR_PCIRST    0x00000040
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|macro|tx4927_sdramcptr
mdefine_line|#define tx4927_sdramcptr        ((struct tx4927_sdramc_reg *)TX4927_SDRAMC_REG)
DECL|macro|tx4927_pcicptr
mdefine_line|#define tx4927_pcicptr          ((struct tx4927_pcic_reg *)TX4927_PCIC_REG)
DECL|macro|tx4927_ccfgptr
mdefine_line|#define tx4927_ccfgptr          ((struct tx4927_ccfg_reg *)TX4927_CCFG_REG)
DECL|macro|tx4927_ebuscptr
mdefine_line|#define tx4927_ebuscptr         ((struct tx4927_ebusc_reg *)TX4927_EBUSC_REG)
DECL|macro|tx4927_ircptr
mdefine_line|#define tx4927_ircptr           ((struct tx4927_irc_reg *)TX4927_IRC_REG)
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
macro_line|#endif /* __ASM_TX4927_TX4927_PCI_H */
eof
