multiline_comment|/*&n; * FILE NAME&n; *&t;include/asm-mips/vr41xx/eagle.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for NEC Eagle board.&n; *&n; * Author: MontaVista Software, Inc.&n; *         yyuasa@mvista.com or source@mvista.com&n; *&n; * Copyright 2001-2003 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __NEC_EAGLE_H
DECL|macro|__NEC_EAGLE_H
mdefine_line|#define __NEC_EAGLE_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * Board specific address mapping&n; */
DECL|macro|VR41XX_PCI_MEM1_BASE
mdefine_line|#define VR41XX_PCI_MEM1_BASE&t;&t;0x10000000
DECL|macro|VR41XX_PCI_MEM1_SIZE
mdefine_line|#define VR41XX_PCI_MEM1_SIZE&t;&t;0x04000000
DECL|macro|VR41XX_PCI_MEM1_MASK
mdefine_line|#define VR41XX_PCI_MEM1_MASK&t;&t;0x7c000000
DECL|macro|VR41XX_PCI_MEM2_BASE
mdefine_line|#define VR41XX_PCI_MEM2_BASE&t;&t;0x14000000
DECL|macro|VR41XX_PCI_MEM2_SIZE
mdefine_line|#define VR41XX_PCI_MEM2_SIZE&t;&t;0x02000000
DECL|macro|VR41XX_PCI_MEM2_MASK
mdefine_line|#define VR41XX_PCI_MEM2_MASK&t;&t;0x7e000000
DECL|macro|VR41XX_PCI_IO_BASE
mdefine_line|#define VR41XX_PCI_IO_BASE&t;&t;0x16000000
DECL|macro|VR41XX_PCI_IO_SIZE
mdefine_line|#define VR41XX_PCI_IO_SIZE&t;&t;0x02000000
DECL|macro|VR41XX_PCI_IO_MASK
mdefine_line|#define VR41XX_PCI_IO_MASK&t;&t;0x7e000000
DECL|macro|VR41XX_PCI_IO_START
mdefine_line|#define VR41XX_PCI_IO_START&t;&t;0x01000000
DECL|macro|VR41XX_PCI_IO_END
mdefine_line|#define VR41XX_PCI_IO_END&t;&t;0x01ffffff
DECL|macro|VR41XX_PCI_MEM_START
mdefine_line|#define VR41XX_PCI_MEM_START&t;&t;0x12000000
DECL|macro|VR41XX_PCI_MEM_END
mdefine_line|#define VR41XX_PCI_MEM_END&t;&t;0x15ffffff
DECL|macro|IO_PORT_BASE
mdefine_line|#define IO_PORT_BASE&t;&t;&t;KSEG1ADDR(VR41XX_PCI_IO_BASE)
DECL|macro|IO_PORT_RESOURCE_START
mdefine_line|#define IO_PORT_RESOURCE_START&t;&t;0
DECL|macro|IO_PORT_RESOURCE_END
mdefine_line|#define IO_PORT_RESOURCE_END&t;&t;VR41XX_PCI_IO_SIZE
DECL|macro|IO_MEM1_RESOURCE_START
mdefine_line|#define IO_MEM1_RESOURCE_START&t;&t;VR41XX_PCI_MEM1_BASE
DECL|macro|IO_MEM1_RESOURCE_END
mdefine_line|#define IO_MEM1_RESOURCE_END&t;&t;(VR41XX_PCI_MEM1_BASE + VR41XX_PCI_MEM1_SIZE)
DECL|macro|IO_MEM2_RESOURCE_START
mdefine_line|#define IO_MEM2_RESOURCE_START&t;&t;VR41XX_PCI_MEM2_BASE
DECL|macro|IO_MEM2_RESOURCE_END
mdefine_line|#define IO_MEM2_RESOURCE_END&t;&t;(VR41XX_PCI_MEM2_BASE + VR41XX_PCI_MEM2_SIZE)
multiline_comment|/*&n; * General-Purpose I/O Pin Number&n; */
DECL|macro|VRC4173_PIN
mdefine_line|#define VRC4173_PIN&t;&t;&t;1
DECL|macro|PCISLOT_PIN
mdefine_line|#define PCISLOT_PIN&t;&t;&t;4
DECL|macro|FPGA_PIN
mdefine_line|#define FPGA_PIN&t;&t;&t;5
DECL|macro|DCD_PIN
mdefine_line|#define DCD_PIN&t;&t;&t;&t;15
multiline_comment|/*&n; * Interrupt Number&n; */
DECL|macro|VRC4173_CASCADE_IRQ
mdefine_line|#define VRC4173_CASCADE_IRQ&t;&t;GIU_IRQ(VRC4173_PIN)
DECL|macro|PCISLOT_IRQ
mdefine_line|#define PCISLOT_IRQ&t;&t;&t;GIU_IRQ(PCISLOT_PIN)
DECL|macro|FPGA_CASCADE_IRQ
mdefine_line|#define FPGA_CASCADE_IRQ&t;&t;GIU_IRQ(FPGA_PIN)
DECL|macro|DCD_IRQ
mdefine_line|#define DCD_IRQ&t;&t;&t;&t;GIU_IRQ(DCD_PIN)
DECL|macro|SDBINT_IRQ_BASE
mdefine_line|#define SDBINT_IRQ_BASE&t;&t;&t;88
DECL|macro|SDBINT_IRQ
mdefine_line|#define SDBINT_IRQ(x)&t;&t;&t;(SDBINT_IRQ_BASE + (x))
multiline_comment|/* RFU */
DECL|macro|DEG_IRQ
mdefine_line|#define DEG_IRQ&t;&t;&t;&t;SDBINT_IRQ(1)
DECL|macro|ENUM_IRQ
mdefine_line|#define ENUM_IRQ&t;&t;&t;SDBINT_IRQ(2)
DECL|macro|SIO1INT_IRQ
mdefine_line|#define SIO1INT_IRQ&t;&t;&t;SDBINT_IRQ(3)
DECL|macro|SIO2INT_IRQ
mdefine_line|#define SIO2INT_IRQ&t;&t;&t;SDBINT_IRQ(4)
DECL|macro|PARINT_IRQ
mdefine_line|#define PARINT_IRQ&t;&t;&t;SDBINT_IRQ(5)
DECL|macro|SDBINT_IRQ_LAST
mdefine_line|#define SDBINT_IRQ_LAST&t;&t;&t;PARINT_IRQ
DECL|macro|PCIINT_IRQ_BASE
mdefine_line|#define PCIINT_IRQ_BASE&t;&t;&t;96
DECL|macro|PCIINT_IRQ
mdefine_line|#define PCIINT_IRQ(x)&t;&t;&t;(PCIINT_IRQ_BASE + (x))
DECL|macro|CP_INTA_IRQ
mdefine_line|#define CP_INTA_IRQ&t;&t;&t;PCIINT_IRQ(0)
DECL|macro|CP_INTB_IRQ
mdefine_line|#define CP_INTB_IRQ&t;&t;&t;PCIINT_IRQ(1)
DECL|macro|CP_INTC_IRQ
mdefine_line|#define CP_INTC_IRQ&t;&t;&t;PCIINT_IRQ(2)
DECL|macro|CP_INTD_IRQ
mdefine_line|#define CP_INTD_IRQ&t;&t;&t;PCIINT_IRQ(3)
DECL|macro|LANINTA_IRQ
mdefine_line|#define LANINTA_IRQ&t;&t;&t;PCIINT_IRQ(4)
DECL|macro|PCIINT_IRQ_LAST
mdefine_line|#define PCIINT_IRQ_LAST&t;&t;&t;LANINTA_IRQ
multiline_comment|/*&n; * On board Devices I/O Mapping&n; */
DECL|macro|NEC_EAGLE_SIO1RB
mdefine_line|#define NEC_EAGLE_SIO1RB&t;&t;KSEG1ADDR(0x0DFFFEC0)
DECL|macro|NEC_EAGLE_SIO1TH
mdefine_line|#define NEC_EAGLE_SIO1TH&t;&t;KSEG1ADDR(0x0DFFFEC0)
DECL|macro|NEC_EAGLE_SIO1IE
mdefine_line|#define NEC_EAGLE_SIO1IE&t;&t;KSEG1ADDR(0x0DFFFEC2)
DECL|macro|NEC_EAGLE_SIO1IID
mdefine_line|#define NEC_EAGLE_SIO1IID&t;&t;KSEG1ADDR(0x0DFFFEC4)
DECL|macro|NEC_EAGLE_SIO1FC
mdefine_line|#define NEC_EAGLE_SIO1FC&t;&t;KSEG1ADDR(0x0DFFFEC4)
DECL|macro|NEC_EAGLE_SIO1LC
mdefine_line|#define NEC_EAGLE_SIO1LC&t;&t;KSEG1ADDR(0x0DFFFEC6)
DECL|macro|NEC_EAGLE_SIO1MC
mdefine_line|#define NEC_EAGLE_SIO1MC&t;&t;KSEG1ADDR(0x0DFFFEC8)
DECL|macro|NEC_EAGLE_SIO1LS
mdefine_line|#define NEC_EAGLE_SIO1LS&t;&t;KSEG1ADDR(0x0DFFFECA)
DECL|macro|NEC_EAGLE_SIO1MS
mdefine_line|#define NEC_EAGLE_SIO1MS&t;&t;KSEG1ADDR(0x0DFFFECC)
DECL|macro|NEC_EAGLE_SIO1SC
mdefine_line|#define NEC_EAGLE_SIO1SC&t;&t;KSEG1ADDR(0x0DFFFECE)
DECL|macro|NEC_EAGLE_SIO2TH
mdefine_line|#define NEC_EAGLE_SIO2TH&t;&t;KSEG1ADDR(0x0DFFFED0)
DECL|macro|NEC_EAGLE_SIO2IE
mdefine_line|#define NEC_EAGLE_SIO2IE&t;&t;KSEG1ADDR(0x0DFFFED2)
DECL|macro|NEC_EAGLE_SIO2IID
mdefine_line|#define NEC_EAGLE_SIO2IID&t;&t;KSEG1ADDR(0x0DFFFED4)
DECL|macro|NEC_EAGLE_SIO2FC
mdefine_line|#define NEC_EAGLE_SIO2FC&t;&t;KSEG1ADDR(0x0DFFFED4)
DECL|macro|NEC_EAGLE_SIO2LC
mdefine_line|#define NEC_EAGLE_SIO2LC&t;&t;KSEG1ADDR(0x0DFFFED6)
DECL|macro|NEC_EAGLE_SIO2MC
mdefine_line|#define NEC_EAGLE_SIO2MC&t;&t;KSEG1ADDR(0x0DFFFED8)
DECL|macro|NEC_EAGLE_SIO2LS
mdefine_line|#define NEC_EAGLE_SIO2LS&t;&t;KSEG1ADDR(0x0DFFFEDA)
DECL|macro|NEC_EAGLE_SIO2MS
mdefine_line|#define NEC_EAGLE_SIO2MS&t;&t;KSEG1ADDR(0x0DFFFEDC)
DECL|macro|NEC_EAGLE_SIO2SC
mdefine_line|#define NEC_EAGLE_SIO2SC&t;&t;KSEG1ADDR(0x0DFFFEDE)
DECL|macro|NEC_EAGLE_PIOPP_DATA
mdefine_line|#define NEC_EAGLE_PIOPP_DATA&t;&t;KSEG1ADDR(0x0DFFFEE0)
DECL|macro|NEC_EAGLE_PIOPP_STATUS
mdefine_line|#define NEC_EAGLE_PIOPP_STATUS&t;&t;KSEG1ADDR(0x0DFFFEE2)
DECL|macro|NEC_EAGLE_PIOPP_CNT
mdefine_line|#define NEC_EAGLE_PIOPP_CNT&t;&t;KSEG1ADDR(0x0DFFFEE4)
DECL|macro|NEC_EAGLE_PIOPP_EPPADDR
mdefine_line|#define NEC_EAGLE_PIOPP_EPPADDR&t;&t;KSEG1ADDR(0x0DFFFEE6)
DECL|macro|NEC_EAGLE_PIOPP_EPPDATA0
mdefine_line|#define NEC_EAGLE_PIOPP_EPPDATA0&t;KSEG1ADDR(0x0DFFFEE8)
DECL|macro|NEC_EAGLE_PIOPP_EPPDATA1
mdefine_line|#define NEC_EAGLE_PIOPP_EPPDATA1&t;KSEG1ADDR(0x0DFFFEEA)
DECL|macro|NEC_EAGLE_PIOPP_EPPDATA2
mdefine_line|#define NEC_EAGLE_PIOPP_EPPDATA2&t;KSEG1ADDR(0x0DFFFEEC)
DECL|macro|NEC_EAGLE_PIOECP_DATA
mdefine_line|#define NEC_EAGLE_PIOECP_DATA&t;&t;KSEG1ADDR(0x0DFFFEF0)
DECL|macro|NEC_EAGLE_PIOECP_CONFIG
mdefine_line|#define NEC_EAGLE_PIOECP_CONFIG&t;&t;KSEG1ADDR(0x0DFFFEF2)
DECL|macro|NEC_EAGLE_PIOECP_EXTCNT
mdefine_line|#define NEC_EAGLE_PIOECP_EXTCNT&t;&t;KSEG1ADDR(0x0DFFFEF4)
multiline_comment|/*&n; *  FLSHCNT Register&n; */
DECL|macro|NEC_EAGLE_FLSHCNT
mdefine_line|#define NEC_EAGLE_FLSHCNT&t;&t;KSEG1ADDR(0x0DFFFFA0)
DECL|macro|NEC_EAGLE_FLSHCNT_FRDY
mdefine_line|#define NEC_EAGLE_FLSHCNT_FRDY&t;&t;0x80
DECL|macro|NEC_EAGLE_FLSHCNT_VPPE
mdefine_line|#define NEC_EAGLE_FLSHCNT_VPPE&t;&t;0x40
DECL|macro|NEC_EAGLE_FLSHCNT_WP2
mdefine_line|#define NEC_EAGLE_FLSHCNT_WP2&t;&t;0x01
multiline_comment|/*&n; * FLSHBANK Register&n; */
DECL|macro|NEC_EAGLE_FLSHBANK
mdefine_line|#define NEC_EAGLE_FLSHBANK&t;&t;KSEG1ADDR(0x0DFFFFA4)
DECL|macro|NEC_EAGLE_FLSHBANK_S_BANK2
mdefine_line|#define NEC_EAGLE_FLSHBANK_S_BANK2&t;0x40
DECL|macro|NEC_EAGLE_FLSHBANK_S_BANK1
mdefine_line|#define NEC_EAGLE_FLSHBANK_S_BANK1&t;0x20
DECL|macro|NEC_EAGLE_FLSHBANK_BNKQ4
mdefine_line|#define NEC_EAGLE_FLSHBANK_BNKQ4&t;0x10
DECL|macro|NEC_EAGLE_FLSHBANK_BNKQ3
mdefine_line|#define NEC_EAGLE_FLSHBANK_BNKQ3&t;0x08
DECL|macro|NEC_EAGLE_FLSHBANK_BNKQ2
mdefine_line|#define NEC_EAGLE_FLSHBANK_BNKQ2&t;0x04
DECL|macro|NEC_EAGLE_FLSHBANK_BNKQ1
mdefine_line|#define NEC_EAGLE_FLSHBANK_BNKQ1&t;0x02
DECL|macro|NEC_EAGLE_FLSHBANK_BNKQ0
mdefine_line|#define NEC_EAGLE_FLSHBANK_BNKQ0&t;0x01
multiline_comment|/*&n; * SWITCH Setting Register&n; */
DECL|macro|NEC_EAGLE_SWTCHSET
mdefine_line|#define NEC_EAGLE_SWTCHSET&t;&t;KSEG1ADDR(0x0DFFFFA8)
DECL|macro|NEC_EAGLE_SWTCHSET_DP2SW4
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP2SW4&t;0x80
DECL|macro|NEC_EAGLE_SWTCHSET_DP2SW3
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP2SW3&t;0x40
DECL|macro|NEC_EAGLE_SWTCHSET_DP2SW2
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP2SW2&t;0x20
DECL|macro|NEC_EAGLE_SWTCHSET_DP2SW1
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP2SW1&t;0x10
DECL|macro|NEC_EAGLE_SWTCHSET_DP1SW4
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP1SW4&t;0x08
DECL|macro|NEC_EAGLE_SWTCHSET_DP1SW3
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP1SW3&t;0x04
DECL|macro|NEC_EAGLE_SWTCHSET_DP1SW2
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP1SW2&t;0x02
DECL|macro|NEC_EAGLE_SWTCHSET_DP1SW1
mdefine_line|#define NEC_EAGLE_SWTCHSET_DP1SW1&t;0x01
multiline_comment|/*&n; * PPT Parallel Port Device Controller&n; */
DECL|macro|NEC_EAGLE_PPT_WRITE_DATA
mdefine_line|#define NEC_EAGLE_PPT_WRITE_DATA&t;KSEG1ADDR(0x0DFFFFB0)
DECL|macro|NEC_EAGLE_PPT_READ_DATA
mdefine_line|#define NEC_EAGLE_PPT_READ_DATA&t;&t;KSEG1ADDR(0x0DFFFFB2)
DECL|macro|NEC_EAGLE_PPT_CNT
mdefine_line|#define NEC_EAGLE_PPT_CNT&t;&t;KSEG1ADDR(0x0DFFFFB4)
DECL|macro|NEC_EAGLE_PPT_CNT2
mdefine_line|#define NEC_EAGLE_PPT_CNT2&t;&t;KSEG1ADDR(0x0DFFFFB4)
multiline_comment|/* Control Register */
DECL|macro|NEC_EAGLE_PPT_INTMSK
mdefine_line|#define NEC_EAGLE_PPT_INTMSK&t;&t;0x20
DECL|macro|NEC_EAGLE_PPT_PARIINT
mdefine_line|#define NEC_EAGLE_PPT_PARIINT&t;&t;0x10
DECL|macro|NEC_EAGLE_PPT_SELECTIN
mdefine_line|#define NEC_EAGLE_PPT_SELECTIN&t;&t;0x08
DECL|macro|NEC_EAGLE_PPT_INIT
mdefine_line|#define NEC_EAGLE_PPT_INIT&t;&t;0x04
DECL|macro|NEC_EAGLE_PPT_AUTOFD
mdefine_line|#define NEC_EAGLE_PPT_AUTOFD&t;&t;0x02
DECL|macro|NEC_EAGLE_PPT_STROBE
mdefine_line|#define NEC_EAGLE_PPT_STROBE&t;&t;0x01
multiline_comment|/* Control Rgister 2 */
DECL|macro|NEC_EAGLE_PPT_PAREN
mdefine_line|#define NEC_EAGLE_PPT_PAREN&t;&t;0x80
DECL|macro|NEC_EAGLE_PPT_AUTOEN
mdefine_line|#define NEC_EAGLE_PPT_AUTOEN&t;&t;0x20
DECL|macro|NEC_EAGLE_PPT_BUSY
mdefine_line|#define NEC_EAGLE_PPT_BUSY&t;&t;0x10
DECL|macro|NEC_EAGLE_PPT_ACK
mdefine_line|#define NEC_EAGLE_PPT_ACK&t;&t;0x08
DECL|macro|NEC_EAGLE_PPT_PE
mdefine_line|#define NEC_EAGLE_PPT_PE&t;&t;0x04
DECL|macro|NEC_EAGLE_PPT_SELECT
mdefine_line|#define NEC_EAGLE_PPT_SELECT&t;&t;0x02
DECL|macro|NEC_EAGLE_PPT_FAULT
mdefine_line|#define NEC_EAGLE_PPT_FAULT&t;&t;0x01
multiline_comment|/*&n; * LEDWR Register&n; */
DECL|macro|NEC_EAGLE_LEDWR1
mdefine_line|#define NEC_EAGLE_LEDWR1&t;&t;KSEG1ADDR(0x0DFFFFC0)
DECL|macro|NEC_EAGLE_LEDWR2
mdefine_line|#define NEC_EAGLE_LEDWR2&t;&t;KSEG1ADDR(0x0DFFFFC4)
multiline_comment|/*&n; * SDBINT Register&n; */
DECL|macro|NEC_EAGLE_SDBINT
mdefine_line|#define NEC_EAGLE_SDBINT&t;&t;KSEG1ADDR(0x0DFFFFD0)
DECL|macro|NEC_EAGLE_SDBINT_PARINT
mdefine_line|#define NEC_EAGLE_SDBINT_PARINT&t;&t;0x20
DECL|macro|NEC_EAGLE_SDBINT_SIO2INT
mdefine_line|#define NEC_EAGLE_SDBINT_SIO2INT&t;0x10
DECL|macro|NEC_EAGLE_SDBINT_SIO1INT
mdefine_line|#define NEC_EAGLE_SDBINT_SIO1INT&t;0x08
DECL|macro|NEC_EAGLE_SDBINT_ENUM
mdefine_line|#define NEC_EAGLE_SDBINT_ENUM&t;&t;0x04
DECL|macro|NEC_EAGLE_SDBINT_DEG
mdefine_line|#define NEC_EAGLE_SDBINT_DEG&t;&t;0x02
multiline_comment|/*&n; * SDB INTMSK Register&n; */
DECL|macro|NEC_EAGLE_SDBINTMSK
mdefine_line|#define NEC_EAGLE_SDBINTMSK&t;&t;KSEG1ADDR(0x0DFFFFD4)
DECL|macro|NEC_EAGLE_SDBINTMSK_MSKPAR
mdefine_line|#define NEC_EAGLE_SDBINTMSK_MSKPAR&t;0x20
DECL|macro|NEC_EAGLE_SDBINTMSK_MSKSIO2
mdefine_line|#define NEC_EAGLE_SDBINTMSK_MSKSIO2&t;0x10
DECL|macro|NEC_EAGLE_SDBINTMSK_MSKSIO1
mdefine_line|#define NEC_EAGLE_SDBINTMSK_MSKSIO1&t;0x08
DECL|macro|NEC_EAGLE_SDBINTMSK_MSKENUM
mdefine_line|#define NEC_EAGLE_SDBINTMSK_MSKENUM&t;0x04
DECL|macro|NEC_EAGLE_SDBINTMSK_MSKDEG
mdefine_line|#define NEC_EAGLE_SDBINTMSK_MSKDEG&t;0x02
multiline_comment|/*&n; * RSTREG Register&n; */
DECL|macro|NEC_EAGLE_RSTREG
mdefine_line|#define NEC_EAGLE_RSTREG&t;&t;KSEG1ADDR(0x0DFFFFD8)
DECL|macro|NEC_EAGLE_RST_RSTSW
mdefine_line|#define NEC_EAGLE_RST_RSTSW&t;&t;0x02
DECL|macro|NEC_EAGLE_RST_LEDOFF
mdefine_line|#define NEC_EAGLE_RST_LEDOFF&t;&t;0x01
multiline_comment|/*&n; * PCI INT Rgister&n; */
DECL|macro|NEC_EAGLE_PCIINTREG
mdefine_line|#define NEC_EAGLE_PCIINTREG&t;&t;KSEG1ADDR(0x0DFFFFDC)
DECL|macro|NEC_EAGLE_PCIINT_LANINT
mdefine_line|#define NEC_EAGLE_PCIINT_LANINT&t;&t;0x10
DECL|macro|NEC_EAGLE_PCIINT_CP_INTD
mdefine_line|#define NEC_EAGLE_PCIINT_CP_INTD&t;0x08
DECL|macro|NEC_EAGLE_PCIINT_CP_INTC
mdefine_line|#define NEC_EAGLE_PCIINT_CP_INTC&t;0x04
DECL|macro|NEC_EAGLE_PCIINT_CP_INTB
mdefine_line|#define NEC_EAGLE_PCIINT_CP_INTB&t;0x02
DECL|macro|NEC_EAGLE_PCIINT_CP_INTA
mdefine_line|#define NEC_EAGLE_PCIINT_CP_INTA&t;0x01
multiline_comment|/*&n; * PCI INT Mask Register&n; */
DECL|macro|NEC_EAGLE_PCIINTMSKREG
mdefine_line|#define NEC_EAGLE_PCIINTMSKREG&t;&t;KSEG1ADDR(0x0DFFFFE0)
DECL|macro|NEC_EAGLE_PCIINTMSK_MSKLANINT
mdefine_line|#define NEC_EAGLE_PCIINTMSK_MSKLANINT&t;0x10
DECL|macro|NEC_EAGLE_PCIINTMSK_MSKCP_INTD
mdefine_line|#define NEC_EAGLE_PCIINTMSK_MSKCP_INTD&t;0x08
DECL|macro|NEC_EAGLE_PCIINTMSK_MSKCP_INTC
mdefine_line|#define NEC_EAGLE_PCIINTMSK_MSKCP_INTC&t;0x04
DECL|macro|NEC_EAGLE_PCIINTMSK_MSKCP_INTB
mdefine_line|#define NEC_EAGLE_PCIINTMSK_MSKCP_INTB&t;0x02
DECL|macro|NEC_EAGLE_PCIINTMSK_MSKCP_INTA
mdefine_line|#define NEC_EAGLE_PCIINTMSK_MSKCP_INTA&t;0x01
multiline_comment|/*&n; * CLK Division Register&n; */
DECL|macro|NEC_EAGLE_CLKDIV
mdefine_line|#define NEC_EAGLE_CLKDIV&t;&t;KSEG1ADDR(0x0DFFFFE4)
DECL|macro|NEC_EAGLE_CLKDIV_PCIDIV1
mdefine_line|#define NEC_EAGLE_CLKDIV_PCIDIV1&t;0x10
DECL|macro|NEC_EAGLE_CLKDIV_PCIDIV0
mdefine_line|#define NEC_EAGLE_CLKDIV_PCIDIV0&t;0x08
DECL|macro|NEC_EAGLE_CLKDIV_VTDIV2
mdefine_line|#define NEC_EAGLE_CLKDIV_VTDIV2&t;&t;0x04
DECL|macro|NEC_EAGLE_CLKDIV_VTDIV1
mdefine_line|#define NEC_EAGLE_CLKDIV_VTDIV1&t;&t;0x02
DECL|macro|NEC_EAGLE_CLKDIV_VTDIV0
mdefine_line|#define NEC_EAGLE_CLKDIV_VTDIV0&t;&t;0x01
multiline_comment|/*&n; * Source Revision Register&n; */
DECL|macro|NEC_EAGLE_REVISION
mdefine_line|#define NEC_EAGLE_REVISION&t;&t;KSEG1ADDR(0x0DFFFFE8)
macro_line|#endif /* __NEC_EAGLE_H */
eof
