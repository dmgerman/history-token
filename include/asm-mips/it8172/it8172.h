multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;IT8172 system controller defines.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or support@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __IT8172__H__
DECL|macro|__IT8172__H__
mdefine_line|#define __IT8172__H__
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|macro|IT8172_BASE
mdefine_line|#define IT8172_BASE&t;&t;&t;0x18000000&t;
DECL|macro|IT8172_PCI_IO_BASE
mdefine_line|#define IT8172_PCI_IO_BASE&t;&t;0x14000000
DECL|macro|IT8172_PCI_MEM_BASE
mdefine_line|#define IT8172_PCI_MEM_BASE&t;&t;0x10000000
singleline_comment|// System registers offsets from IT8172_BASE
DECL|macro|IT_CMFPCR
mdefine_line|#define IT_CMFPCR&t;&t;&t;0x0
DECL|macro|IT_DSRR
mdefine_line|#define IT_DSRR&t;&t;&t;&t;0x2
DECL|macro|IT_PCDCR
mdefine_line|#define IT_PCDCR&t;&t;&t;0x4
DECL|macro|IT_SPLLCR
mdefine_line|#define IT_SPLLCR&t;&t;&t;0x6
DECL|macro|IT_CIDR
mdefine_line|#define IT_CIDR&t;&t;&t;&t;0x10
DECL|macro|IT_CRNR
mdefine_line|#define IT_CRNR&t;&t;&t;&t;0x12
DECL|macro|IT_CPUTR
mdefine_line|#define IT_CPUTR&t;&t;&t;0x14
DECL|macro|IT_CTCR
mdefine_line|#define IT_CTCR&t;&t;&t;&t;0x16
DECL|macro|IT_SDPR
mdefine_line|#define IT_SDPR&t;&t;&t;&t;0xF0
singleline_comment|// Power management register offset from IT8172_PCI_IO_BASE
singleline_comment|// Power Management Device Standby Register
DECL|macro|IT_PM_DSR
mdefine_line|#define IT_PM_DSR&t;&t;0x15800
DECL|macro|IT_PM_DSR_TMR0SB
mdefine_line|#define IT_PM_DSR_TMR0SB&t;0x0001
DECL|macro|IT_PM_DSR_TMR1SB
mdefine_line|#define IT_PM_DSR_TMR1SB&t;0x0002
DECL|macro|IT_PM_DSR_CIR0SB
mdefine_line|#define IT_PM_DSR_CIR0SB&t;0x0004
DECL|macro|IT_PM_DSR_CIR1SB
mdefine_line|#define IT_PM_DSR_CIR1SB&t;0x0008
DECL|macro|IT_PM_DSR_SCR0SB
mdefine_line|#define IT_PM_DSR_SCR0SB&t;0x0010
DECL|macro|IT_PM_DSR_SCR1SB
mdefine_line|#define IT_PM_DSR_SCR1SB&t;0x0020
DECL|macro|IT_PM_DSR_PPSB
mdefine_line|#define IT_PM_DSR_PPSB&t;&t;0x0040
DECL|macro|IT_PM_DSR_I2CSB
mdefine_line|#define IT_PM_DSR_I2CSB&t;&t;0x0080
DECL|macro|IT_PM_DSR_UARTSB
mdefine_line|#define IT_PM_DSR_UARTSB&t;0x0100
DECL|macro|IT_PM_DSR_IDESB
mdefine_line|#define IT_PM_DSR_IDESB&t;&t;0x0200
DECL|macro|IT_PM_DSR_ACSB
mdefine_line|#define IT_PM_DSR_ACSB&t;&t;0x0400
DECL|macro|IT_PM_DSR_M68KSB
mdefine_line|#define IT_PM_DSR_M68KSB&t;0x0800
singleline_comment|// Power Management PCI Device Software Reset Register
DECL|macro|IT_PM_PCISR
mdefine_line|#define IT_PM_PCISR             0x15802
DECL|macro|IT_PM_PCISR_IDESR
mdefine_line|#define IT_PM_PCISR_IDESR       0x0001
DECL|macro|IT_PM_PCISR_CDMASR
mdefine_line|#define IT_PM_PCISR_CDMASR      0x0002
DECL|macro|IT_PM_PCISR_USBSR
mdefine_line|#define IT_PM_PCISR_USBSR       0x0004
DECL|macro|IT_PM_PCISR_DMASR
mdefine_line|#define IT_PM_PCISR_DMASR       0x0008
DECL|macro|IT_PM_PCISR_ACSR
mdefine_line|#define IT_PM_PCISR_ACSR        0x0010
DECL|macro|IT_PM_PCISR_MEMSR
mdefine_line|#define IT_PM_PCISR_MEMSR       0x0020
DECL|macro|IT_PM_PCISR_68KSR
mdefine_line|#define IT_PM_PCISR_68KSR       0x0040
singleline_comment|// PCI Configuration address and data register offsets
singleline_comment|// from IT8172_BASE
DECL|macro|IT_CONFADDR
mdefine_line|#define IT_CONFADDR&t;&t;&t;0x4000
DECL|macro|IT_BUSNUM_SHF
mdefine_line|#define IT_BUSNUM_SHF                   16
DECL|macro|IT_DEVNUM_SHF
mdefine_line|#define IT_DEVNUM_SHF                   11
DECL|macro|IT_FUNCNUM_SHF
mdefine_line|#define IT_FUNCNUM_SHF                  8
DECL|macro|IT_REGNUM_SHF
mdefine_line|#define IT_REGNUM_SHF                   2
DECL|macro|IT_CONFDATA
mdefine_line|#define IT_CONFDATA&t;&t;&t;0x4004
singleline_comment|// PCI configuration header common register offsets
DECL|macro|IT_VID
mdefine_line|#define IT_VID&t;&t;&t;&t;0x00
DECL|macro|IT_DID
mdefine_line|#define IT_DID&t;&t;&t;&t;0x02
DECL|macro|IT_PCICMD
mdefine_line|#define IT_PCICMD&t;&t;&t;0x04
DECL|macro|IT_PCISTS
mdefine_line|#define IT_PCISTS&t;&t;&t;0x06
DECL|macro|IT_RID
mdefine_line|#define IT_RID&t;&t;&t;&t;0x08
DECL|macro|IT_CLASSC
mdefine_line|#define IT_CLASSC&t;&t;&t;0x09
DECL|macro|IT_HEADT
mdefine_line|#define IT_HEADT&t;&t;&t;0x0E
DECL|macro|IT_SERIRQC
mdefine_line|#define IT_SERIRQC&t;&t;&t;0x49
singleline_comment|// PCI to Internal/LPC Bus Bridge configuration header register offset
DECL|macro|IT_P2I_BCR
mdefine_line|#define IT_P2I_BCR&t;&t;&t;&t;0x4C
DECL|macro|IT_P2I_D0IOSC
mdefine_line|#define IT_P2I_D0IOSC&t;&t;&t;&t;0x50 
DECL|macro|IT_P2I_D1IOSC
mdefine_line|#define IT_P2I_D1IOSC&t;&t;&t;&t;0x54
DECL|macro|IT_P2I_D2IOSC
mdefine_line|#define IT_P2I_D2IOSC&t;&t;&t;&t;0x58 
DECL|macro|IT_P2I_D3IOSC
mdefine_line|#define IT_P2I_D3IOSC&t;&t;&t;&t;0x5C 
DECL|macro|IT_P2I_D4IOSC
mdefine_line|#define IT_P2I_D4IOSC&t;&t;&t;&t;0x60 
DECL|macro|IT_P2I_D5IOSC
mdefine_line|#define IT_P2I_D5IOSC&t;&t;&t;&t;0x64 
DECL|macro|IT_P2I_D6IOSC
mdefine_line|#define IT_P2I_D6IOSC&t;&t;&t;&t;0x68 
DECL|macro|IT_P2I_D7IOSC
mdefine_line|#define IT_P2I_D7IOSC&t;&t;&t;&t;0x6C 
DECL|macro|IT_P2I_D8IOSC
mdefine_line|#define IT_P2I_D8IOSC&t;&t;&t;&t;0x70 
DECL|macro|IT_P2I_D9IOSC
mdefine_line|#define IT_P2I_D9IOSC&t;&t;&t;&t;0x74 
DECL|macro|IT_P2I_D10IOSC
mdefine_line|#define IT_P2I_D10IOSC&t;&t;&t;&t;0x78 
DECL|macro|IT_P2I_D11IOSC
mdefine_line|#define IT_P2I_D11IOSC&t;&t;&t;&t;0x7C 
singleline_comment|// Memory controller register offsets from IT8172_BASE
DECL|macro|IT_MC_SDRMR
mdefine_line|#define IT_MC_SDRMR&t;&t;&t;&t;&t;0x1000
DECL|macro|IT_MC_SDRTR
mdefine_line|#define IT_MC_SDRTR&t;&t;&t;&t;&t;0x1004
DECL|macro|IT_MC_MCR
mdefine_line|#define IT_MC_MCR&t;&t;&t;&t;&t;0x1008
DECL|macro|IT_MC_SDTYPE
mdefine_line|#define IT_MC_SDTYPE&t;&t;&t;&t;&t;0x100C
DECL|macro|IT_MC_WPBA
mdefine_line|#define IT_MC_WPBA&t;&t;&t;&t;&t;0x1010
DECL|macro|IT_MC_WPTA
mdefine_line|#define IT_MC_WPTA&t;&t;&t;&t;&t;0x1014
DECL|macro|IT_MC_HATR
mdefine_line|#define IT_MC_HATR&t;&t;&t;&t;&t;0x1018
DECL|macro|IT_MC_PCICR
mdefine_line|#define IT_MC_PCICR&t;&t;&t;&t;&t;0x101C
singleline_comment|// Flash/ROM control register offsets from IT8172_BASE
DECL|macro|IT_FC_BRCR
mdefine_line|#define IT_FC_BRCR&t;&t;&t;&t;&t;0x2000
DECL|macro|IT_FC_FCR
mdefine_line|#define IT_FC_FCR&t;&t;&t;&t;&t;0x2004
DECL|macro|IT_FC_DCR
mdefine_line|#define IT_FC_DCR&t;&t;&t;&t;&t;0x2008
singleline_comment|// M68K interface bridge configuration header register offset
DECL|macro|IT_M68K_MBCSR
mdefine_line|#define IT_M68K_MBCSR&t;&t;&t;&t;&t;0x54
DECL|macro|IT_M68K_TMR
mdefine_line|#define IT_M68K_TMR&t;&t;&t;&t;&t;0x58
DECL|macro|IT_M68K_BCR
mdefine_line|#define IT_M68K_BCR&t;&t;&t;&t;&t;0x5C
DECL|macro|IT_M68K_BSR
mdefine_line|#define IT_M68K_BSR&t;&t;&t;&t;&t;0x5D
DECL|macro|IT_M68K_DTR
mdefine_line|#define IT_M68K_DTR&t;&t;&t;&t;&t;0x5F
singleline_comment|// Register offset from IT8172_PCI_IO_BASE 
singleline_comment|// These registers are accessible through 8172 PCI IO window.
singleline_comment|// INTC 
DECL|macro|IT_INTC_BASE
mdefine_line|#define IT_INTC_BASE&t;&t;&t;&t;0x10000
DECL|macro|IT_INTC_LBDNIRR
mdefine_line|#define IT_INTC_LBDNIRR&t;&t;&t;&t;0x10000
DECL|macro|IT_INTC_LBDNIMR
mdefine_line|#define IT_INTC_LBDNIMR&t;&t;&t;&t;0x10002
DECL|macro|IT_INTC_LBDNITR
mdefine_line|#define IT_INTC_LBDNITR&t;&t;&t;&t;0x10004
DECL|macro|IT_INTC_LBDNIAR
mdefine_line|#define IT_INTC_LBDNIAR&t;&t;&t;&t;0x10006
DECL|macro|IT_INTC_LPCNIRR
mdefine_line|#define IT_INTC_LPCNIRR&t;&t;&t;&t;0x10010
DECL|macro|IT_INTC_LPCNIMR
mdefine_line|#define IT_INTC_LPCNIMR&t;&t;&t;&t;0x10012
DECL|macro|IT_INTC_LPCNITR
mdefine_line|#define IT_INTC_LPCNITR&t;&t;&t;&t;0x10014
DECL|macro|IT_INTC_LPCNIAR
mdefine_line|#define IT_INTC_LPCNIAR&t;&t;&t;&t;0x10016
DECL|macro|IT_INTC_PDNIRR
mdefine_line|#define IT_INTC_PDNIRR&t;&t;&t;&t;0x10020
DECL|macro|IT_INTC_PDNIMR
mdefine_line|#define IT_INTC_PDNIMR&t;&t;&t;&t;0x10022
DECL|macro|IT_INTC_PDNITR
mdefine_line|#define IT_INTC_PDNITR&t;&t;&t;&t;0x10024
DECL|macro|IT_INTC_PDNIAR
mdefine_line|#define IT_INTC_PDNIAR&t;&t;&t;&t;0x10026
DECL|macro|IT_INTC_UMNIRR
mdefine_line|#define IT_INTC_UMNIRR&t;&t;&t;&t;0x10030
DECL|macro|IT_INTC_UMNITR
mdefine_line|#define IT_INTC_UMNITR&t;&t;&t;&t;0x10034
DECL|macro|IT_INTC_UMNIAR
mdefine_line|#define IT_INTC_UMNIAR&t;&t;&t;&t;0x10036
DECL|macro|IT_INTC_TYPER
mdefine_line|#define IT_INTC_TYPER&t;&t;&t;&t;0x107FE
singleline_comment|// IT8172 PCI device number
DECL|macro|IT_C2P_DEVICE
mdefine_line|#define IT_C2P_DEVICE&t;&t;&t;&t;0
DECL|macro|IT_AUDIO_DEVICE
mdefine_line|#define IT_AUDIO_DEVICE&t;&t;&t;&t;1
DECL|macro|IT_DMAC_DEVICE
mdefine_line|#define IT_DMAC_DEVICE&t;&t;&t;&t;1
DECL|macro|IT_CDMAC_DEVICE
mdefine_line|#define IT_CDMAC_DEVICE&t;&t;&t;&t;1
DECL|macro|IT_USB_DEVICE
mdefine_line|#define IT_USB_DEVICE&t;&t;&t;&t;1
DECL|macro|IT_P2I_DEVICE
mdefine_line|#define IT_P2I_DEVICE&t;&t;&t;&t;1
DECL|macro|IT_IDE_DEVICE
mdefine_line|#define IT_IDE_DEVICE&t;&t;&t;&t;1
DECL|macro|IT_M68K_DEVICE
mdefine_line|#define IT_M68K_DEVICE&t;&t;&t;&t;1
singleline_comment|// IT8172 PCI function number
DECL|macro|IT_C2P_FUNCION
mdefine_line|#define IT_C2P_FUNCION&t;&t;&t;&t;0
DECL|macro|IT_AUDIO_FUNCTION
mdefine_line|#define IT_AUDIO_FUNCTION&t;&t;&t;0
DECL|macro|IT_DMAC_FUNCTION
mdefine_line|#define IT_DMAC_FUNCTION&t;&t;&t;1
DECL|macro|IT_CDMAC_FUNCTION
mdefine_line|#define IT_CDMAC_FUNCTION&t;&t;&t;2
DECL|macro|IT_USB_FUNCTION
mdefine_line|#define IT_USB_FUNCTION&t;&t;&t;&t;3
DECL|macro|IT_P2I_FUNCTION
mdefine_line|#define IT_P2I_FUNCTION&t;&t;&t;&t;4
DECL|macro|IT_IDE_FUNCTION
mdefine_line|#define IT_IDE_FUNCTION&t;&t;&t;&t;5
DECL|macro|IT_M68K_FUNCTION
mdefine_line|#define IT_M68K_FUNCTION&t;&t;&t;6
singleline_comment|// IT8172 GPIO
DECL|macro|IT_GPADR
mdefine_line|#define IT_GPADR&t;&t;&t;&t;0x13800
DECL|macro|IT_GPBDR
mdefine_line|#define IT_GPBDR&t;&t;&t;&t;0x13808
DECL|macro|IT_GPCDR
mdefine_line|#define IT_GPCDR&t;&t;&t;&t;0x13810
DECL|macro|IT_GPACR
mdefine_line|#define IT_GPACR&t;&t;&t;&t;0x13802
DECL|macro|IT_GPBCR
mdefine_line|#define IT_GPBCR&t;&t;&t;&t;0x1380A
DECL|macro|IT_GPCCR
mdefine_line|#define IT_GPCCR&t;&t;&t;&t;0x13812
DECL|macro|IT_GPAICR
mdefine_line|#define IT_GPAICR&t;&t;&t;&t;0x13804
DECL|macro|IT_GPBICR
mdefine_line|#define IT_GPBICR&t;&t;&t;&t;0x1380C
DECL|macro|IT_GPCICR
mdefine_line|#define IT_GPCICR&t;&t;&t;&t;0x13814
DECL|macro|IT_GPAISR
mdefine_line|#define IT_GPAISR&t;&t;&t;&t;0x13806
DECL|macro|IT_GPBISR
mdefine_line|#define IT_GPBISR&t;&t;&t;&t;0x1380E
DECL|macro|IT_GPCISR
mdefine_line|#define IT_GPCISR&t;&t;&t;&t;0x13816
DECL|macro|IT_GCR
mdefine_line|#define IT_GCR&t;&t;&t;&t;&t;0x13818
singleline_comment|// IT8172 RTC
DECL|macro|IT_RTC_BASE
mdefine_line|#define IT_RTC_BASE&t;&t;&t;&t;0x14800
DECL|macro|IT_RTC_RIR0
mdefine_line|#define IT_RTC_RIR0&t;&t;&t;&t;0x00
DECL|macro|IT_RTC_RTR0
mdefine_line|#define IT_RTC_RTR0&t;&t;&t;&t;0x01
DECL|macro|IT_RTC_RIR1
mdefine_line|#define IT_RTC_RIR1&t;&t;&t;&t;0x02
DECL|macro|IT_RTC_RTR1
mdefine_line|#define IT_RTC_RTR1&t;&t;&t;&t;0x03
DECL|macro|IT_RTC_RIR2
mdefine_line|#define IT_RTC_RIR2&t;&t;&t;&t;0x04
DECL|macro|IT_RTC_RTR2
mdefine_line|#define IT_RTC_RTR2&t;&t;&t;&t;0x05
DECL|macro|IT_RTC_RCTR
mdefine_line|#define IT_RTC_RCTR&t;&t;&t;&t;0x08
DECL|macro|IT_RTC_RA
mdefine_line|#define IT_RTC_RA&t;&t;&t;&t;0x0A
DECL|macro|IT_RTC_RB
mdefine_line|#define IT_RTC_RB&t;&t;&t;&t;0x0B
DECL|macro|IT_RTC_RC
mdefine_line|#define IT_RTC_RC&t;&t;&t;&t;0x0C
DECL|macro|IT_RTC_RD
mdefine_line|#define IT_RTC_RD&t;&t;&t;&t;0x0D
DECL|macro|RTC_SEC_INDEX
mdefine_line|#define RTC_SEC_INDEX&t;&t;&t;&t;0x00
DECL|macro|RTC_MIN_INDEX
mdefine_line|#define RTC_MIN_INDEX&t;&t;&t;&t;0x02
DECL|macro|RTC_HOUR_INDEX
mdefine_line|#define RTC_HOUR_INDEX&t;&t;&t;&t;0x04
DECL|macro|RTC_DAY_INDEX
mdefine_line|#define RTC_DAY_INDEX&t;&t;&t;&t;0x06
DECL|macro|RTC_DATE_INDEX
mdefine_line|#define RTC_DATE_INDEX&t;&t;&t;&t;0x07
DECL|macro|RTC_MONTH_INDEX
mdefine_line|#define RTC_MONTH_INDEX&t;&t;&t;&t;0x08
DECL|macro|RTC_YEAR_INDEX
mdefine_line|#define RTC_YEAR_INDEX&t;&t;&t;&t;0x09
singleline_comment|// IT8172 internal device registers
DECL|macro|IT_TIMER_BASE
mdefine_line|#define IT_TIMER_BASE&t;&t;&t;&t;0x10800
DECL|macro|IT_CIR0_BASE
mdefine_line|#define IT_CIR0_BASE&t;&t;&t;&t;0x11000
DECL|macro|IT_UART_BASE
mdefine_line|#define IT_UART_BASE&t;&t;&t;&t;0x11800
DECL|macro|IT_SCR0_BASE
mdefine_line|#define IT_SCR0_BASE&t;&t;&t;&t;0x12000
DECL|macro|IT_SCR1_BASE
mdefine_line|#define IT_SCR1_BASE&t;&t;&t;&t;0x12800
DECL|macro|IT_PP_BASE
mdefine_line|#define IT_PP_BASE&t;&t;&t;&t;0x13000
DECL|macro|IT_I2C_BASE
mdefine_line|#define IT_I2C_BASE&t;&t;&t;&t;0x14000
DECL|macro|IT_CIR1_BASE
mdefine_line|#define IT_CIR1_BASE&t;&t;&t;&t;0x15000
singleline_comment|// IT8172 Smart Card Reader offsets from IT_SCR*_BASE
DECL|macro|IT_SCR_SFR
mdefine_line|#define IT_SCR_SFR&t;&t;&t;&t;0x08
DECL|macro|IT_SCR_SCDR
mdefine_line|#define IT_SCR_SCDR&t;&t;&t;&t;0x09
singleline_comment|// IT8172 IT_SCR_SFR bit definition &amp; mask
DECL|macro|IT_SCR_SFR_GATE_UART
mdefine_line|#define&t;IT_SCR_SFR_GATE_UART&t;&t;&t;0x40
DECL|macro|IT_SCR_SFR_GATE_UART_BIT
mdefine_line|#define&t;IT_SCR_SFR_GATE_UART_BIT&t;&t;6
DECL|macro|IT_SCR_SFR_GATE_UART_OFF
mdefine_line|#define IT_SCR_SFR_GATE_UART_OFF&t;&t;0
DECL|macro|IT_SCR_SFR_GATE_UART_ON
mdefine_line|#define&t;IT_SCR_SFR_GATE_UART_ON&t;&t;&t;1
DECL|macro|IT_SCR_SFR_FET_CHARGE
mdefine_line|#define&t;IT_SCR_SFR_FET_CHARGE&t;&t;&t;0x30
DECL|macro|IT_SCR_SFR_FET_CHARGE_BIT
mdefine_line|#define&t;IT_SCR_SFR_FET_CHARGE_BIT&t;&t;4
DECL|macro|IT_SCR_SFR_FET_CHARGE_3_3_US
mdefine_line|#define IT_SCR_SFR_FET_CHARGE_3_3_US&t;&t;3
DECL|macro|IT_SCR_SFR_FET_CHARGE_13_US
mdefine_line|#define IT_SCR_SFR_FET_CHARGE_13_US&t;&t;2
DECL|macro|IT_SCR_SFR_FET_CHARGE_53_US
mdefine_line|#define IT_SCR_SFR_FET_CHARGE_53_US&t;&t;1
DECL|macro|IT_SCR_SFR_FET_CHARGE_213_US
mdefine_line|#define IT_SCR_SFR_FET_CHARGE_213_US&t;&t;0
DECL|macro|IT_SCR_SFR_CARD_FREQ
mdefine_line|#define&t;IT_SCR_SFR_CARD_FREQ&t;&t;&t;0x0C
DECL|macro|IT_SCR_SFR_CARD_FREQ_BIT
mdefine_line|#define&t;IT_SCR_SFR_CARD_FREQ_BIT&t;&t;2
DECL|macro|IT_SCR_SFR_CARD_FREQ_STOP
mdefine_line|#define IT_SCR_SFR_CARD_FREQ_STOP&t;&t;3
DECL|macro|IT_SCR_SFR_CARD_FREQ_3_5_MHZ
mdefine_line|#define IT_SCR_SFR_CARD_FREQ_3_5_MHZ&t;&t;0
DECL|macro|IT_SCR_SFR_CARD_FREQ_7_1_MHZ
mdefine_line|#define IT_SCR_SFR_CARD_FREQ_7_1_MHZ&t;&t;2
DECL|macro|IT_SCR_SFR_CARD_FREQ_96_DIV_MHZ
mdefine_line|#define IT_SCR_SFR_CARD_FREQ_96_DIV_MHZ&t;&t;1
DECL|macro|IT_SCR_SFR_FET_ACTIVE
mdefine_line|#define&t;IT_SCR_SFR_FET_ACTIVE&t;&t;&t;0x02
DECL|macro|IT_SCR_SFR_FET_ACTIVE_BIT
mdefine_line|#define&t;IT_SCR_SFR_FET_ACTIVE_BIT&t;&t;1
DECL|macro|IT_SCR_SFR_FET_ACTIVE_INVERT
mdefine_line|#define IT_SCR_SFR_FET_ACTIVE_INVERT&t;&t;0
DECL|macro|IT_SCR_SFR_FET_ACTIVE_NONINVERT
mdefine_line|#define IT_SCR_SFR_FET_ACTIVE_NONINVERT&t;&t;1
DECL|macro|IT_SCR_SFR_ENABLE
mdefine_line|#define&t;IT_SCR_SFR_ENABLE&t;&t;&t;0x01
DECL|macro|IT_SCR_SFR_ENABLE_BIT
mdefine_line|#define&t;IT_SCR_SFR_ENABLE_BIT&t;&t;&t;0
DECL|macro|IT_SCR_SFR_ENABLE_OFF
mdefine_line|#define IT_SCR_SFR_ENABLE_OFF&t;&t;&t;0
DECL|macro|IT_SCR_SFR_ENABLE_ON
mdefine_line|#define IT_SCR_SFR_ENABLE_ON&t;&t;&t;1
singleline_comment|// IT8172 IT_SCR_SCDR bit definition &amp; mask
DECL|macro|IT_SCR_SCDR_RESET_MODE
mdefine_line|#define&t;IT_SCR_SCDR_RESET_MODE&t;&t;&t;0x80
DECL|macro|IT_SCR_SCDR_RESET_MODE_BIT
mdefine_line|#define&t;IT_SCR_SCDR_RESET_MODE_BIT&t;&t;7
DECL|macro|IT_SCR_SCDR_RESET_MODE_ASYNC
mdefine_line|#define&t;IT_SCR_SCDR_RESET_MODE_ASYNC&t;&t;0
DECL|macro|IT_SCR_SCDR_RESET_MODE_SYNC
mdefine_line|#define IT_SCR_SCDR_RESET_MODE_SYNC&t;&t;1
DECL|macro|IT_SCR_SCDR_DIVISOR
mdefine_line|#define&t;IT_SCR_SCDR_DIVISOR&t;&t;&t;0x7F
DECL|macro|IT_SCR_SCDR_DIVISOR_BIT
mdefine_line|#define&t;IT_SCR_SCDR_DIVISOR_BIT&t;&t;&t;0
DECL|macro|IT_SCR_SCDR_DIVISOR_STOP_VAL_1
mdefine_line|#define&t;IT_SCR_SCDR_DIVISOR_STOP_VAL_1&t;&t;0x00
DECL|macro|IT_SCR_SCDR_DIVISOR_STOP_VAL_2
mdefine_line|#define&t;IT_SCR_SCDR_DIVISOR_STOP_VAL_2&t;&t;0x01
DECL|macro|IT_SCR_SCDR_DIVISOR_STOP_VAL_3
mdefine_line|#define&t;IT_SCR_SCDR_DIVISOR_STOP_VAL_3&t;&t;0x7F
singleline_comment|// IT8172 DMA
DECL|macro|IT_DMAC_BASE
mdefine_line|#define IT_DMAC_BASE&t;&t;&t;&t;0x16000
DECL|macro|IT_DMAC_BCAR0
mdefine_line|#define IT_DMAC_BCAR0&t;&t;&t;&t;0x00
DECL|macro|IT_DMAC_BCAR1
mdefine_line|#define IT_DMAC_BCAR1&t;&t;&t;&t;0x04
DECL|macro|IT_DMAC_BCAR2
mdefine_line|#define IT_DMAC_BCAR2&t;&t;&t;&t;0x08
DECL|macro|IT_DMAC_BCAR3
mdefine_line|#define IT_DMAC_BCAR3&t;&t;&t;&t;0x0C
DECL|macro|IT_DMAC_BCCR0
mdefine_line|#define IT_DMAC_BCCR0&t;&t;&t;&t;0x02
DECL|macro|IT_DMAC_BCCR1
mdefine_line|#define IT_DMAC_BCCR1&t;&t;&t;&t;0x06
DECL|macro|IT_DMAC_BCCR2
mdefine_line|#define IT_DMAC_BCCR2&t;&t;&t;&t;0x0a
DECL|macro|IT_DMAC_BCCR3
mdefine_line|#define IT_DMAC_BCCR3&t;&t;&t;&t;0x0e
DECL|macro|IT_DMAC_CR
mdefine_line|#define IT_DMAC_CR&t;&t;&t;&t;0x10
DECL|macro|IT_DMAC_SR
mdefine_line|#define IT_DMAC_SR&t;&t;&t;&t;0x12
DECL|macro|IT_DMAC_ESR
mdefine_line|#define IT_DMAC_ESR&t;&t;&t;&t;0x13
DECL|macro|IT_DMAC_RQR
mdefine_line|#define IT_DMAC_RQR&t;&t;&t;&t;0x14
DECL|macro|IT_DMAC_MR
mdefine_line|#define IT_DMAC_MR&t;&t;&t;&t;0x16
DECL|macro|IT_DMAC_EMR
mdefine_line|#define IT_DMAC_EMR&t;&t;&t;&t;0x17
DECL|macro|IT_DMAC_MKR
mdefine_line|#define IT_DMAC_MKR&t;&t;&t;&t;0x18
DECL|macro|IT_DMAC_PAR0
mdefine_line|#define IT_DMAC_PAR0&t;&t;&t;&t;0x20
DECL|macro|IT_DMAC_PAR1
mdefine_line|#define IT_DMAC_PAR1&t;&t;&t;&t;0x22
DECL|macro|IT_DMAC_PAR2
mdefine_line|#define IT_DMAC_PAR2&t;&t;&t;&t;0x24
DECL|macro|IT_DMAC_PAR3
mdefine_line|#define IT_DMAC_PAR3&t;&t;&t;&t;0x26
singleline_comment|// IT8172 IDE
DECL|macro|IT_IDE_BASE
mdefine_line|#define IT_IDE_BASE&t;&t;&t;&t;0x17800
DECL|macro|IT_IDE_STATUS
mdefine_line|#define IT_IDE_STATUS&t;&t;&t;&t;0x1F7
singleline_comment|// IT8172 Audio Controller
DECL|macro|IT_AC_BASE
mdefine_line|#define IT_AC_BASE&t;&t;&t;&t;0x17000
DECL|macro|IT_AC_PCMOV
mdefine_line|#define&t;IT_AC_PCMOV&t;&t;&t;&t;0x00
DECL|macro|IT_AC_FMOV
mdefine_line|#define IT_AC_FMOV&t;&t;&t;&t;0x02
DECL|macro|IT_AC_I2SV
mdefine_line|#define&t;IT_AC_I2SV&t;&t;&t;&t;0x04
DECL|macro|IT_AC_DRSS
mdefine_line|#define IT_AC_DRSS&t;&t;&t;&t;0x06
DECL|macro|IT_AC_PCC
mdefine_line|#define IT_AC_PCC&t;&t;&t;&t;0x08
DECL|macro|IT_AC_PCDL
mdefine_line|#define IT_AC_PCDL&t;&t;&t;&t;0x0A
DECL|macro|IT_AC_PCB1STA
mdefine_line|#define IT_AC_PCB1STA&t;&t;&t;&t;0x0C
DECL|macro|IT_AC_PCB2STA
mdefine_line|#define IT_AC_PCB2STA&t;&t;&t;&t;0x10
DECL|macro|IT_AC_CAPCC
mdefine_line|#define IT_AC_CAPCC&t;&t;&t;&t;0x14
DECL|macro|IT_AC_CAPCDL
mdefine_line|#define IT_AC_CAPCDL&t;&t;&t;&t;0x16
DECL|macro|IT_AC_CAPB1STA
mdefine_line|#define IT_AC_CAPB1STA&t;&t;&t;&t;0x18
DECL|macro|IT_AC_CAPB2STA
mdefine_line|#define IT_AC_CAPB2STA&t;&t;&t;&t;0x1C
DECL|macro|IT_AC_CODECC
mdefine_line|#define IT_AC_CODECC&t;&t;&t;&t;0x22
DECL|macro|IT_AC_I2SMC
mdefine_line|#define IT_AC_I2SMC&t;&t;&t;&t;0x24
DECL|macro|IT_AC_VS
mdefine_line|#define IT_AC_VS&t;&t;&t;&t;0x26
DECL|macro|IT_AC_SRCS
mdefine_line|#define IT_AC_SRCS&t;&t;&t;&t;0x28
DECL|macro|IT_AC_CIRCP
mdefine_line|#define IT_AC_CIRCP&t;&t;&t;&t;0x2A
DECL|macro|IT_AC_CIRDP
mdefine_line|#define IT_AC_CIRDP&t;&t;&t;&t;0x2C
DECL|macro|IT_AC_TM
mdefine_line|#define IT_AC_TM&t;&t;&t;&t;0x4A
DECL|macro|IT_AC_PFDP
mdefine_line|#define IT_AC_PFDP&t;&t;&t;&t;0x4C
DECL|macro|IT_AC_GC
mdefine_line|#define IT_AC_GC&t;&t;&t;&t;0x54
DECL|macro|IT_AC_IMC
mdefine_line|#define IT_AC_IMC&t;&t;&t;&t;0x56
DECL|macro|IT_AC_ISC
mdefine_line|#define IT_AC_ISC&t;&t;&t;&t;0x5B
DECL|macro|IT_AC_OPL3SR
mdefine_line|#define IT_AC_OPL3SR&t;&t;&t;&t;0x68
DECL|macro|IT_AC_OPL3DWDR
mdefine_line|#define IT_AC_OPL3DWDR&t;&t;&t;&t;0x69
DECL|macro|IT_AC_OPL3AB1W
mdefine_line|#define IT_AC_OPL3AB1W&t;&t;&t;&t;0x6A
DECL|macro|IT_AC_OPL3DW
mdefine_line|#define IT_AC_OPL3DW&t;&t;&t;&t;0x6B
DECL|macro|IT_AC_BPDC
mdefine_line|#define IT_AC_BPDC&t;&t;&t;&t;0x70
singleline_comment|// Audio : IT_AC_PCC bit definition &amp; mask
DECL|macro|PCC_SM
mdefine_line|#define&t;PCC_SM&t;&t;&t;&t;&t;0x8000
DECL|macro|PCC_SM_BIT
mdefine_line|#define&t;PCC_SM_BIT&t;&t;&t;&t;15
DECL|macro|PCC_SM_STEREO
mdefine_line|#define&t;PCC_SM_STEREO&t;&t;&t;&t;1
DECL|macro|PCC_SM_MONO
mdefine_line|#define PCC_SM_MONO&t;&t;&t;&t;0
DECL|macro|PCC_DF
mdefine_line|#define&t;PCC_DF&t;&t;&t;&t;&t;0x4000
DECL|macro|PCC_DF_BIT
mdefine_line|#define PCC_DF_BIT&t;&t;&t;&t;14
DECL|macro|PCC_DF_8
mdefine_line|#define&t;PCC_DF_8&t;&t;&t;&t;0
DECL|macro|PCC_DF_16
mdefine_line|#define PCC_DF_16&t;&t;&t;&t;1
DECL|macro|PCC_CF
mdefine_line|#define&t;PCC_CF&t;&t;&t;&t;&t;0x3000
DECL|macro|PCC_CF_BIT
mdefine_line|#define PCC_CF_BIT&t;&t;&t;&t;12
DECL|macro|PCC_CF_2
mdefine_line|#define&t;PCC_CF_2&t;&t;&t;&t;0
DECL|macro|PCC_CF_4
mdefine_line|#define PCC_CF_4&t;&t;&t;&t;1
DECL|macro|PCC_CF_6
mdefine_line|#define PCC_CF_6&t;&t;&t;&t;2
DECL|macro|PCC_SR
mdefine_line|#define PCC_SR&t;&t;&t;&t;&t;0x0F00
DECL|macro|PCC_SR_BIT
mdefine_line|#define PCC_SR_BIT&t;&t;&t;&t;8
DECL|macro|PCC_SR_5500
mdefine_line|#define&t;PCC_SR_5500&t;&t;&t;&t;0
DECL|macro|PCC_SR_8000
mdefine_line|#define&t;PCC_SR_8000&t;&t;&t;&t;1
DECL|macro|PCC_SR_9600
mdefine_line|#define&t;PCC_SR_9600&t;&t;&t;&t;2
DECL|macro|PCC_SR_11025
mdefine_line|#define&t;PCC_SR_11025&t;&t;&t;&t;3
DECL|macro|PCC_SR_16000
mdefine_line|#define&t;PCC_SR_16000&t;&t;&t;&t;4
DECL|macro|PCC_SR_19200
mdefine_line|#define&t;PCC_SR_19200&t;&t;&t;&t;5
DECL|macro|PCC_SR_22050
mdefine_line|#define&t;PCC_SR_22050&t;&t;&t;&t;6
DECL|macro|PCC_SR_32000
mdefine_line|#define&t;PCC_SR_32000&t;&t;&t;&t;7
DECL|macro|PCC_SR_38400
mdefine_line|#define&t;PCC_SR_38400&t;&t;&t;&t;8
DECL|macro|PCC_SR_44100
mdefine_line|#define&t;PCC_SR_44100&t;&t;&t;&t;9
DECL|macro|PCC_SR_48000
mdefine_line|#define&t;PCC_SR_48000&t;&t;&t;&t;10
DECL|macro|PCC_CSP
mdefine_line|#define PCC_CSP&t;&t;&t;&t;&t;0x0080
DECL|macro|PCC_CSP_BIT
mdefine_line|#define PCC_CSP_BIT&t;&t;&t;&t;7
DECL|macro|PCC_CSP_STOP
mdefine_line|#define PCC_CSP_STOP&t;&t;&t;&t;0
DECL|macro|PCC_CSP_STOP_NOW
mdefine_line|#define PCC_CSP_STOP_NOW&t;&t;&t;1
DECL|macro|PCC_CP
mdefine_line|#define PCC_CP&t;&t;&t;&t;&t;0x0040
DECL|macro|PCC_CP_BIT
mdefine_line|#define&t;PCC_CP_BIT&t;&t;&t;&t;6
DECL|macro|PCC_CP_NORMAL
mdefine_line|#define PCC_CP_NORMAL&t;&t;&t;&t;0
DECL|macro|PCC_CP_PAUSE
mdefine_line|#define PCC_CP_PAUSE&t;&t;&t;&t;1
DECL|macro|PCC_CA
mdefine_line|#define PCC_CA&t;&t;&t;&t;&t;0x0020
DECL|macro|PCC_CA_BIT
mdefine_line|#define PCC_CA_BIT&t;&t;&t;&t;5
DECL|macro|PCC_CA_NO_START
mdefine_line|#define PCC_CA_NO_START&t;&t;&t;&t;0
DECL|macro|PCC_CA_START
mdefine_line|#define PCC_CA_START&t;&t;&t;&t;1
DECL|macro|PCC_CB2L
mdefine_line|#define PCC_CB2L&t;&t;&t;&t;0x0004
DECL|macro|PCC_CB2L_BIT
mdefine_line|#define PCC_CB2L_BIT&t;&t;&t;&t;2
DECL|macro|PCC_CB2L_NO
mdefine_line|#define PCC_CB2L_NO&t;&t;&t;&t;0
DECL|macro|PCC_CB2L_YES
mdefine_line|#define PCC_CB2L_YES&t;&t;&t;&t;1
DECL|macro|PCC_CB1L
mdefine_line|#define PCC_CB1L&t;&t;&t;&t;0x0002
DECL|macro|PCC_CB1L_BIT
mdefine_line|#define PCC_CB1L_BIT&t;&t;&t;&t;1
DECL|macro|PCC_CB1L_NO
mdefine_line|#define PCC_CB1L_NO&t;&t;&t;&t;0
DECL|macro|PCC_CB1L_YES
mdefine_line|#define PCC_CB1L_YES&t;&t;&t;&t;1
DECL|macro|PCC_DE
mdefine_line|#define PCC_DE&t;&t;&t;&t;&t;0x0001
DECL|macro|PCC_DE_BIT
mdefine_line|#define PCC_DE_BIT&t;&t;&t;&t;0
DECL|macro|PCC_DE_NOT_EMPTY
mdefine_line|#define PCC_DE_NOT_EMPTY&t;&t;&t;0
DECL|macro|PCC_DE_EMPTY
mdefine_line|#define PCC_DE_EMPTY&t;&t;&t;&t;1
singleline_comment|// IT8172 Timer
DECL|macro|IT_TIMER_BASE
mdefine_line|#define IT_TIMER_BASE&t;&t;&t;&t;0x10800
DECL|macro|TIMER_TCVR0
mdefine_line|#define&t;TIMER_TCVR0&t;&t;&t;&t;0x00
DECL|macro|TIMER_TRVR0
mdefine_line|#define TIMER_TRVR0&t;&t;&t;&t;0x02
DECL|macro|TIMER_TCR0
mdefine_line|#define&t;TIMER_TCR0&t;&t;&t;&t;0x04
DECL|macro|TIMER_TIRR
mdefine_line|#define TIMER_TIRR&t;&t;&t;&t;0x06
DECL|macro|TIMER_TCVR1
mdefine_line|#define&t;TIMER_TCVR1&t;&t;&t;&t;0x08
DECL|macro|TIMER_TRVR1
mdefine_line|#define TIMER_TRVR1&t;&t;&t;&t;0x0A
DECL|macro|TIMER_TCR1
mdefine_line|#define&t;TIMER_TCR1&t;&t;&t;&t;0x0C
DECL|macro|TIMER_TIDR
mdefine_line|#define TIMER_TIDR&t;&t;&t;&t;0x0E
DECL|macro|IT_WRITE
mdefine_line|#define IT_WRITE(ofs, data) *(volatile u32 *)KSEG1ADDR((IT8172_BASE+ofs)) = data
DECL|macro|IT_READ
mdefine_line|#define IT_READ(ofs, data)  data = *(volatile u32 *)KSEG1ADDR((IT8172_BASE+ofs))
DECL|macro|IT_IO_WRITE
mdefine_line|#define IT_IO_WRITE(ofs, data) *(volatile u32 *)KSEG1ADDR((IT8172_PCI_IO_BASE+ofs)) = data
DECL|macro|IT_IO_READ
mdefine_line|#define IT_IO_READ(ofs, data)  data = *(volatile u32 *)KSEG1ADDR((IT8172_PCI_IO_BASE+ofs))
DECL|macro|IT_IO_WRITE16
mdefine_line|#define IT_IO_WRITE16(ofs, data) *(volatile u16 *)KSEG1ADDR((IT8172_PCI_IO_BASE+ofs)) = data
DECL|macro|IT_IO_READ16
mdefine_line|#define IT_IO_READ16(ofs, data)  data = *(volatile u16 *)KSEG1ADDR((IT8172_PCI_IO_BASE+ofs))
macro_line|#endif
eof
