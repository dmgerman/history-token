multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;ITE 8172 Interrupt Numbering&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or support@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _MIPS_ITEINT_H
DECL|macro|_MIPS_ITEINT_H
mdefine_line|#define _MIPS_ITEINT_H
multiline_comment|/*&n; * Here&squot;s the &quot;strategy&quot;:&n; * We number the LPC serial irqs from 0 to 15,&n; * the local bus irqs from 16 to 31,&n; * the pci dev register interrupts from 32 to 47,&n; * and the non-maskable ints from 48 to 53.&n; */
DECL|macro|IT8172_LPC_IRQ_BASE
mdefine_line|#define IT8172_LPC_IRQ_BASE  0    /* first LPC int number */
DECL|macro|IT8172_SERIRQ_0
mdefine_line|#define IT8172_SERIRQ_0      (IT8172_LPC_IRQ_BASE + 0)
DECL|macro|IT8172_SERIRQ_1
mdefine_line|#define IT8172_SERIRQ_1      (IT8172_LPC_IRQ_BASE + 1)
DECL|macro|IT8172_SERIRQ_2
mdefine_line|#define IT8172_SERIRQ_2      (IT8172_LPC_IRQ_BASE + 2)
DECL|macro|IT8172_SERIRQ_3
mdefine_line|#define IT8172_SERIRQ_3      (IT8172_LPC_IRQ_BASE + 3)
DECL|macro|IT8172_SERIRQ_4
mdefine_line|#define IT8172_SERIRQ_4      (IT8172_LPC_IRQ_BASE + 4)
DECL|macro|IT8172_SERIRQ_5
mdefine_line|#define IT8172_SERIRQ_5      (IT8172_LPC_IRQ_BASE + 5)
DECL|macro|IT8172_SERIRQ_6
mdefine_line|#define IT8172_SERIRQ_6      (IT8172_LPC_IRQ_BASE + 6)
DECL|macro|IT8172_SERIRQ_7
mdefine_line|#define IT8172_SERIRQ_7      (IT8172_LPC_IRQ_BASE + 7)
DECL|macro|IT8172_SERIRQ_8
mdefine_line|#define IT8172_SERIRQ_8      (IT8172_LPC_IRQ_BASE + 8)
DECL|macro|IT8172_SERIRQ_9
mdefine_line|#define IT8172_SERIRQ_9      (IT8172_LPC_IRQ_BASE + 9)
DECL|macro|IT8172_SERIRQ_10
mdefine_line|#define IT8172_SERIRQ_10     (IT8172_LPC_IRQ_BASE + 10)
DECL|macro|IT8172_SERIRQ_11
mdefine_line|#define IT8172_SERIRQ_11     (IT8172_LPC_IRQ_BASE + 11)
DECL|macro|IT8172_SERIRQ_12
mdefine_line|#define IT8172_SERIRQ_12     (IT8172_LPC_IRQ_BASE + 12)
DECL|macro|IT8172_SERIRQ_13
mdefine_line|#define IT8172_SERIRQ_13     (IT8172_LPC_IRQ_BASE + 13)
DECL|macro|IT8172_SERIRQ_14
mdefine_line|#define IT8172_SERIRQ_14     (IT8172_LPC_IRQ_BASE + 14)
DECL|macro|IT8172_SERIRQ_15
mdefine_line|#define IT8172_SERIRQ_15     (IT8172_LPC_IRQ_BASE + 15)
DECL|macro|IT8172_LB_IRQ_BASE
mdefine_line|#define IT8172_LB_IRQ_BASE  16   /* first local bus int number */
DECL|macro|IT8172_PPR_IRQ
mdefine_line|#define IT8172_PPR_IRQ          (IT8172_LB_IRQ_BASE + 0) /* parallel port */
DECL|macro|IT8172_TIMER0_IRQ
mdefine_line|#define IT8172_TIMER0_IRQ       (IT8172_LB_IRQ_BASE + 1)
DECL|macro|IT8172_TIMER1_IRQ
mdefine_line|#define IT8172_TIMER1_IRQ       (IT8172_LB_IRQ_BASE + 2)
DECL|macro|IT8172_I2C_IRQ
mdefine_line|#define IT8172_I2C_IRQ          (IT8172_LB_IRQ_BASE + 3)
DECL|macro|IT8172_GPIO_IRQ
mdefine_line|#define IT8172_GPIO_IRQ         (IT8172_LB_IRQ_BASE + 4)
DECL|macro|IT8172_CIR0_IRQ
mdefine_line|#define IT8172_CIR0_IRQ         (IT8172_LB_IRQ_BASE + 5)
DECL|macro|IT8172_CIR1_IRQ
mdefine_line|#define IT8172_CIR1_IRQ         (IT8172_LB_IRQ_BASE + 6)
DECL|macro|IT8172_UART_IRQ
mdefine_line|#define IT8172_UART_IRQ         (IT8172_LB_IRQ_BASE + 7)
DECL|macro|IT8172_SCR0_IRQ
mdefine_line|#define IT8172_SCR0_IRQ         (IT8172_LB_IRQ_BASE + 8)
DECL|macro|IT8172_SCR1_IRQ
mdefine_line|#define IT8172_SCR1_IRQ         (IT8172_LB_IRQ_BASE + 9)
DECL|macro|IT8172_RTC_IRQ
mdefine_line|#define IT8172_RTC_IRQ          (IT8172_LB_IRQ_BASE + 10)
DECL|macro|IT8172_IOCHK_IRQ
mdefine_line|#define IT8172_IOCHK_IRQ        (IT8172_LB_IRQ_BASE + 11)
multiline_comment|/* 12 - 15 reserved */
multiline_comment|/*&n; * Note here that the pci dev registers includes bits for more than&n; * just the pci devices.&n; */
DECL|macro|IT8172_PCI_DEV_IRQ_BASE
mdefine_line|#define IT8172_PCI_DEV_IRQ_BASE  32   /* first pci dev irq */
DECL|macro|IT8172_AC97_IRQ
mdefine_line|#define IT8172_AC97_IRQ          (IT8172_PCI_DEV_IRQ_BASE + 0)
DECL|macro|IT8172_MC68K_IRQ
mdefine_line|#define IT8172_MC68K_IRQ         (IT8172_PCI_DEV_IRQ_BASE + 1)
DECL|macro|IT8172_IDE_IRQ
mdefine_line|#define IT8172_IDE_IRQ           (IT8172_PCI_DEV_IRQ_BASE + 2)
DECL|macro|IT8172_USB_IRQ
mdefine_line|#define IT8172_USB_IRQ           (IT8172_PCI_DEV_IRQ_BASE + 3)
DECL|macro|IT8172_BRIDGE_MASTER_IRQ
mdefine_line|#define IT8172_BRIDGE_MASTER_IRQ (IT8172_PCI_DEV_IRQ_BASE + 4)
DECL|macro|IT8172_BRIDGE_TARGET_IRQ
mdefine_line|#define IT8172_BRIDGE_TARGET_IRQ (IT8172_PCI_DEV_IRQ_BASE + 5)
DECL|macro|IT8172_PCI_INTA_IRQ
mdefine_line|#define IT8172_PCI_INTA_IRQ      (IT8172_PCI_DEV_IRQ_BASE + 6)
DECL|macro|IT8172_PCI_INTB_IRQ
mdefine_line|#define IT8172_PCI_INTB_IRQ      (IT8172_PCI_DEV_IRQ_BASE + 7)
DECL|macro|IT8172_PCI_INTC_IRQ
mdefine_line|#define IT8172_PCI_INTC_IRQ      (IT8172_PCI_DEV_IRQ_BASE + 8)
DECL|macro|IT8172_PCI_INTD_IRQ
mdefine_line|#define IT8172_PCI_INTD_IRQ      (IT8172_PCI_DEV_IRQ_BASE + 9)
DECL|macro|IT8172_S_INTA_IRQ
mdefine_line|#define IT8172_S_INTA_IRQ        (IT8172_PCI_DEV_IRQ_BASE + 10)
DECL|macro|IT8172_S_INTB_IRQ
mdefine_line|#define IT8172_S_INTB_IRQ        (IT8172_PCI_DEV_IRQ_BASE + 11)
DECL|macro|IT8172_S_INTC_IRQ
mdefine_line|#define IT8172_S_INTC_IRQ        (IT8172_PCI_DEV_IRQ_BASE + 12)
DECL|macro|IT8172_S_INTD_IRQ
mdefine_line|#define IT8172_S_INTD_IRQ        (IT8172_PCI_DEV_IRQ_BASE + 13)
DECL|macro|IT8172_CDMA_IRQ
mdefine_line|#define IT8172_CDMA_IRQ          (IT8172_PCI_DEV_IRQ_BASE + 14)
DECL|macro|IT8172_DMA_IRQ
mdefine_line|#define IT8172_DMA_IRQ           (IT8172_PCI_DEV_IRQ_BASE + 15)
DECL|macro|IT8172_NMI_IRQ_BASE
mdefine_line|#define IT8172_NMI_IRQ_BASE      48
DECL|macro|IT8172_SER_NMI_IRQ
mdefine_line|#define IT8172_SER_NMI_IRQ       (IT8172_NMI_IRQ_BASE + 0)
DECL|macro|IT8172_PCI_NMI_IRQ
mdefine_line|#define IT8172_PCI_NMI_IRQ       (IT8172_NMI_IRQ_BASE + 1)
DECL|macro|IT8172_RTC_NMI_IRQ
mdefine_line|#define IT8172_RTC_NMI_IRQ       (IT8172_NMI_IRQ_BASE + 2)
DECL|macro|IT8172_CPUIF_NMI_IRQ
mdefine_line|#define IT8172_CPUIF_NMI_IRQ     (IT8172_NMI_IRQ_BASE + 3)
DECL|macro|IT8172_PMER_NMI_IRQ
mdefine_line|#define IT8172_PMER_NMI_IRQ      (IT8172_NMI_IRQ_BASE + 4)
DECL|macro|IT8172_POWER_NMI_IRQ
mdefine_line|#define IT8172_POWER_NMI_IRQ     (IT8172_NMI_IRQ_BASE + 5)
multiline_comment|/* Finally, let&squot;s move over here the mips cpu timer interrupt.&n; * This is more or less strictly for statistics.&n; */
DECL|macro|MIPS_CPU_TIMER_IRQ
mdefine_line|#define MIPS_CPU_TIMER_IRQ       (IT8172_NMI_IRQ_BASE + 6)
DECL|macro|IT8172_INT_END
mdefine_line|#define IT8172_INT_END           MIPS_CPU_TIMER_IRQ
multiline_comment|/* &n; * IT8172 Interrupt Controller Registers&n; */
DECL|struct|it8172_intc_regs
r_struct
id|it8172_intc_regs
(brace
DECL|member|lb_req
r_volatile
r_int
r_int
id|lb_req
suffix:semicolon
multiline_comment|/* offset 0 */
DECL|member|lb_mask
r_volatile
r_int
r_int
id|lb_mask
suffix:semicolon
DECL|member|lb_trigger
r_volatile
r_int
r_int
id|lb_trigger
suffix:semicolon
DECL|member|lb_level
r_volatile
r_int
r_int
id|lb_level
suffix:semicolon
DECL|member|pad0
r_int
r_char
id|pad0
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|lpc_req
r_volatile
r_int
r_int
id|lpc_req
suffix:semicolon
multiline_comment|/* offset 0x10 */
DECL|member|lpc_mask
r_volatile
r_int
r_int
id|lpc_mask
suffix:semicolon
DECL|member|lpc_trigger
r_volatile
r_int
r_int
id|lpc_trigger
suffix:semicolon
DECL|member|lpc_level
r_volatile
r_int
r_int
id|lpc_level
suffix:semicolon
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pci_req
r_volatile
r_int
r_int
id|pci_req
suffix:semicolon
multiline_comment|/* offset 0x20 */
DECL|member|pci_mask
r_volatile
r_int
r_int
id|pci_mask
suffix:semicolon
DECL|member|pci_trigger
r_volatile
r_int
r_int
id|pci_trigger
suffix:semicolon
DECL|member|pci_level
r_volatile
r_int
r_int
id|pci_level
suffix:semicolon
DECL|member|pad2
r_int
r_char
id|pad2
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|nmi_req
r_volatile
r_int
r_int
id|nmi_req
suffix:semicolon
multiline_comment|/* offset 0x30 */
DECL|member|nmi_mask
r_volatile
r_int
r_int
id|nmi_mask
suffix:semicolon
DECL|member|nmi_trigger
r_volatile
r_int
r_int
id|nmi_trigger
suffix:semicolon
DECL|member|nmi_level
r_volatile
r_int
r_int
id|nmi_level
suffix:semicolon
DECL|member|pad3
r_int
r_char
id|pad3
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|nmi_redir
r_volatile
r_int
r_int
id|nmi_redir
suffix:semicolon
multiline_comment|/* offset 0x3E */
DECL|member|pad4
r_int
r_char
id|pad4
(braket
l_int|0xBE
)braket
suffix:semicolon
DECL|member|intstatus
r_volatile
r_int
r_int
id|intstatus
suffix:semicolon
multiline_comment|/* offset 0xFE */
)brace
suffix:semicolon
macro_line|#endif /* _MIPS_ITEINT_H */
eof
