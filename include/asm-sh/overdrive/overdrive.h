multiline_comment|/* &n; * Copyright (C) 2000 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.                            &n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __OVERDRIVE_H__
DECL|macro|__OVERDRIVE_H__
mdefine_line|#define __OVERDRIVE_H__
DECL|macro|OVERDRIVE_INT_CT
mdefine_line|#define OVERDRIVE_INT_CT 0xa3a00000
DECL|macro|OVERDRIVE_INT_DT
mdefine_line|#define OVERDRIVE_INT_DT 0xa3b00000
DECL|macro|OVERDRIVE_CTRL
mdefine_line|#define OVERDRIVE_CTRL    0xa3000000
multiline_comment|/* Shoving all these bits into the same register is not a good idea. &n; * As soon as I get a spare moment, I&squot;ll change the FPGA and put each &n; * bit in a separate register&n; */
DECL|macro|VALID_CTRL_BITS
mdefine_line|#define VALID_CTRL_BITS&t;&t;          0x1f
DECL|macro|ENABLE_RS232_MASK
mdefine_line|#define ENABLE_RS232_MASK&t;  &t;  0x1e
DECL|macro|DISABLE_RS232_BIT
mdefine_line|#define DISABLE_RS232_BIT&t;&t;  0x01
DECL|macro|ENABLE_NMI_MASK
mdefine_line|#define ENABLE_NMI_MASK&t;&t;&t;  0x1d
DECL|macro|DISABLE_NMI_BIT
mdefine_line|#define DISABLE_NMI_BIT&t;&t;&t;  0x02
DECL|macro|RESET_PCI_MASK
mdefine_line|#define RESET_PCI_MASK&t;&t;&t;  0x1b
DECL|macro|ENABLE_PCI_BIT
mdefine_line|#define ENABLE_PCI_BIT&t;&t;&t;  0x04
DECL|macro|ENABLE_LED_MASK
mdefine_line|#define ENABLE_LED_MASK&t;&t;&t;  0x17
DECL|macro|DISABLE_LED_BIT
mdefine_line|#define DISABLE_LED_BIT&t;&t;&t;  0x08
DECL|macro|RESET_FPGA_MASK
mdefine_line|#define RESET_FPGA_MASK&t;&t;&t;  0x0f
DECL|macro|ENABLE_FPGA_BIT
mdefine_line|#define ENABLE_FPGA_BIT&t;&t;&t;  0x10
DECL|macro|FPGA_DCLK_ADDRESS
mdefine_line|#define FPGA_DCLK_ADDRESS           0xA3C00000
DECL|macro|FPGA_DATA
mdefine_line|#define FPGA_DATA        0x01&t;/*   W */
DECL|macro|FPGA_CONFDONE
mdefine_line|#define FPGA_CONFDONE    0x02&t;/* R   */
DECL|macro|FPGA_NOT_STATUS
mdefine_line|#define FPGA_NOT_STATUS  0x04&t;/* R   */
DECL|macro|FPGA_INITDONE
mdefine_line|#define FPGA_INITDONE    0x08&t;/* R   */
DECL|macro|FPGA_TIMEOUT
mdefine_line|#define FPGA_TIMEOUT     100000
multiline_comment|/* Interrupts for the overdrive. Note that these numbers have &n; * nothing to do with the actual IRQ numbers they appear on, &n; * this is all programmable. This is simply the position in the &n; * INT_CT register.&n; */
DECL|macro|OVERDRIVE_PCI_INTA
mdefine_line|#define OVERDRIVE_PCI_INTA              0
DECL|macro|OVERDRIVE_PCI_INTB
mdefine_line|#define OVERDRIVE_PCI_INTB              1
DECL|macro|OVERDRIVE_PCI_INTC
mdefine_line|#define OVERDRIVE_PCI_INTC              2
DECL|macro|OVERDRIVE_PCI_INTD
mdefine_line|#define OVERDRIVE_PCI_INTD              3
DECL|macro|OVERDRIVE_GALILEO_INT
mdefine_line|#define OVERDRIVE_GALILEO_INT           4
DECL|macro|OVERDRIVE_GALILEO_LOCAL_INT
mdefine_line|#define OVERDRIVE_GALILEO_LOCAL_INT     5
DECL|macro|OVERDRIVE_AUDIO_INT
mdefine_line|#define OVERDRIVE_AUDIO_INT             6
DECL|macro|OVERDRIVE_KEYBOARD_INT
mdefine_line|#define OVERDRIVE_KEYBOARD_INT          7
multiline_comment|/* Which Linux IRQ should we assign to each interrupt source? */
DECL|macro|OVERDRIVE_PCI_IRQ1
mdefine_line|#define OVERDRIVE_PCI_IRQ1              2
macro_line|#ifdef CONFIG_HACKED_NE2K
DECL|macro|OVERDRIVE_PCI_IRQ2
mdefine_line|#define OVERDRIVE_PCI_IRQ2              7
macro_line|#else
DECL|macro|OVERDRIVE_PCI_IRQ2
mdefine_line|#define OVERDRIVE_PCI_IRQ2              2
DECL|macro|OVERDRIVE_PCI_INTB
macro_line|#undef OVERDRIVE_PCI_INTB 
DECL|macro|OVERDRIVE_PCI_INTB
mdefine_line|#define OVERDRIVE_PCI_INTB OVERDRIVE_PCI_INTA
macro_line|#endif
multiline_comment|/* Put the ESS solo audio chip on IRQ 4 */
DECL|macro|OVERDRIVE_ESS_IRQ
mdefine_line|#define OVERDRIVE_ESS_IRQ               4
multiline_comment|/* Where the memory behind the PCI bus appears */
DECL|macro|PCI_DRAM_BASE
mdefine_line|#define PCI_DRAM_BASE   0xb7000000
DECL|macro|PCI_DRAM_SIZE
mdefine_line|#define PCI_DRAM_SIZE (16*1024*1024)
DECL|macro|PCI_DRAM_FINISH
mdefine_line|#define PCI_DRAM_FINISH (PCI_DRAM_BASE+PCI_DRAM_SIZE-1)
multiline_comment|/* Where the IO region appears in the memory */
DECL|macro|PCI_GTIO_BASE
mdefine_line|#define PCI_GTIO_BASE   0xb8000000
macro_line|#endif
eof
