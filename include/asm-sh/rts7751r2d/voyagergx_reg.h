multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/* voyagergx_reg.h                                                      */
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*  This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Copyright 2003 (c) Lineo uSolutions,Inc.&n;*/
multiline_comment|/* -------------------------------------------------------------------- */
macro_line|#ifndef _VOYAGER_GX_REG_H
DECL|macro|_VOYAGER_GX_REG_H
mdefine_line|#define _VOYAGER_GX_REG_H
DECL|macro|VOYAGER_BASE
mdefine_line|#define VOYAGER_BASE&t;&t;&t;0xb3e00000
DECL|macro|VOYAGER_USBH_BASE
mdefine_line|#define VOYAGER_USBH_BASE&t;&t;(0x40000 + VOYAGER_BASE)
DECL|macro|VOYAGER_UART_BASE
mdefine_line|#define VOYAGER_UART_BASE&t;&t;(0x30000 + VOYAGER_BASE)
DECL|macro|VOYAGER_AC97_BASE
mdefine_line|#define&t;VOYAGER_AC97_BASE&t;&t;(0xa0000 + VOYAGER_BASE)
DECL|macro|VOYAGER_IRQ_NUM
mdefine_line|#define VOYAGER_IRQ_NUM&t;&t;&t;32
DECL|macro|VOYAGER_IRQ_BASE
mdefine_line|#define VOYAGER_IRQ_BASE&t;&t;50
DECL|macro|VOYAGER_USBH_IRQ
mdefine_line|#define VOYAGER_USBH_IRQ&t;&t;VOYAGER_IRQ_BASE + 6
DECL|macro|VOYAGER_8051_IRQ
mdefine_line|#define VOYAGER_8051_IRQ&t;&t;VOYAGER_IRQ_BASE + 10
DECL|macro|VOYAGER_UART0_IRQ
mdefine_line|#define VOYAGER_UART0_IRQ&t;&t;VOYAGER_IRQ_BASE + 12
DECL|macro|VOYAGER_UART1_IRQ
mdefine_line|#define VOYAGER_UART1_IRQ&t;&t;VOYAGER_IRQ_BASE + 13
DECL|macro|VOYAGER_AC97_IRQ
mdefine_line|#define&t;VOYAGER_AC97_IRQ&t;&t;VOYAGER_IRQ_BASE + 17
multiline_comment|/* ----- MISC controle  register ------------------------------ */
DECL|macro|MISC_CTRL
mdefine_line|#define MISC_CTRL&t;&t;&t;(0x000004 + VOYAGER_BASE)
DECL|macro|MISC_CTRL_USBCLK_48
mdefine_line|#define MISC_CTRL_USBCLK_48&t;&t;(3 &lt;&lt; 28)
DECL|macro|MISC_CTRL_USBCLK_96
mdefine_line|#define MISC_CTRL_USBCLK_96&t;&t;(2 &lt;&lt; 28)
DECL|macro|MISC_CTRL_USBCLK_CRYSTAL
mdefine_line|#define MISC_CTRL_USBCLK_CRYSTAL&t;(1 &lt;&lt; 28)
multiline_comment|/* ----- GPIO[31:0] register --------------------------------- */
DECL|macro|GPIO_MUX_LOW
mdefine_line|#define GPIO_MUX_LOW&t;&t;&t;(0x000008 + VOYAGER_BASE)
DECL|macro|GPIO_MUX_LOW_AC97
mdefine_line|#define GPIO_MUX_LOW_AC97&t;&t;0x1F000000
DECL|macro|GPIO_MUX_LOW_8051
mdefine_line|#define GPIO_MUX_LOW_8051&t;&t;0x0000ffff
DECL|macro|GPIO_MUX_LOW_PWM
mdefine_line|#define GPIO_MUX_LOW_PWM&t;&t;(1 &lt;&lt; 29)
multiline_comment|/* ----- GPIO[63:32] register --------------------------------- */
DECL|macro|GPIO_MUX_HIGH
mdefine_line|#define GPIO_MUX_HIGH&t;&t;&t;(0x00000C + VOYAGER_BASE)
multiline_comment|/* ----- DRAM controle  register ------------------------------- */
DECL|macro|DRAM_CTRL
mdefine_line|#define DRAM_CTRL&t;&t;&t;(0x000010 + VOYAGER_BASE)
DECL|macro|DRAM_CTRL_EMBEDDED
mdefine_line|#define DRAM_CTRL_EMBEDDED&t;&t;(1 &lt;&lt; 31)
DECL|macro|DRAM_CTRL_CPU_BURST_1
mdefine_line|#define DRAM_CTRL_CPU_BURST_1&t;&t;(0 &lt;&lt; 28)
DECL|macro|DRAM_CTRL_CPU_BURST_2
mdefine_line|#define DRAM_CTRL_CPU_BURST_2&t;&t;(1 &lt;&lt; 28)
DECL|macro|DRAM_CTRL_CPU_BURST_4
mdefine_line|#define DRAM_CTRL_CPU_BURST_4&t;&t;(2 &lt;&lt; 28)
DECL|macro|DRAM_CTRL_CPU_BURST_8
mdefine_line|#define DRAM_CTRL_CPU_BURST_8&t;&t;(3 &lt;&lt; 28)
DECL|macro|DRAM_CTRL_CPU_CAS_LATENCY
mdefine_line|#define DRAM_CTRL_CPU_CAS_LATENCY&t;(1 &lt;&lt; 27)
DECL|macro|DRAM_CTRL_CPU_SIZE_2
mdefine_line|#define DRAM_CTRL_CPU_SIZE_2&t;&t;(0 &lt;&lt; 24)
DECL|macro|DRAM_CTRL_CPU_SIZE_4
mdefine_line|#define DRAM_CTRL_CPU_SIZE_4&t;&t;(1 &lt;&lt; 24)
DECL|macro|DRAM_CTRL_CPU_SIZE_64
mdefine_line|#define DRAM_CTRL_CPU_SIZE_64&t;&t;(4 &lt;&lt; 24)
DECL|macro|DRAM_CTRL_CPU_SIZE_32
mdefine_line|#define DRAM_CTRL_CPU_SIZE_32&t;&t;(5 &lt;&lt; 24)
DECL|macro|DRAM_CTRL_CPU_SIZE_16
mdefine_line|#define DRAM_CTRL_CPU_SIZE_16&t;&t;(6 &lt;&lt; 24)
DECL|macro|DRAM_CTRL_CPU_SIZE_8
mdefine_line|#define DRAM_CTRL_CPU_SIZE_8&t;&t;(7 &lt;&lt; 24)
DECL|macro|DRAM_CTRL_CPU_COLUMN_SIZE_1024
mdefine_line|#define DRAM_CTRL_CPU_COLUMN_SIZE_1024&t;(0 &lt;&lt; 22)
DECL|macro|DRAM_CTRL_CPU_COLUMN_SIZE_512
mdefine_line|#define DRAM_CTRL_CPU_COLUMN_SIZE_512&t;(2 &lt;&lt; 22)
DECL|macro|DRAM_CTRL_CPU_COLUMN_SIZE_256
mdefine_line|#define DRAM_CTRL_CPU_COLUMN_SIZE_256&t;(3 &lt;&lt; 22)
DECL|macro|DRAM_CTRL_CPU_ACTIVE_PRECHARGE
mdefine_line|#define DRAM_CTRL_CPU_ACTIVE_PRECHARGE&t;(1 &lt;&lt; 21)
DECL|macro|DRAM_CTRL_CPU_RESET
mdefine_line|#define DRAM_CTRL_CPU_RESET&t;&t;(1 &lt;&lt; 20)
DECL|macro|DRAM_CTRL_CPU_BANKS
mdefine_line|#define DRAM_CTRL_CPU_BANKS&t;&t;(1 &lt;&lt; 19)
DECL|macro|DRAM_CTRL_CPU_WRITE_PRECHARGE
mdefine_line|#define DRAM_CTRL_CPU_WRITE_PRECHARGE&t;(1 &lt;&lt; 18)
DECL|macro|DRAM_CTRL_BLOCK_WRITE
mdefine_line|#define DRAM_CTRL_BLOCK_WRITE&t;&t;(1 &lt;&lt; 17)
DECL|macro|DRAM_CTRL_REFRESH_COMMAND
mdefine_line|#define DRAM_CTRL_REFRESH_COMMAND&t;(1 &lt;&lt; 16)
DECL|macro|DRAM_CTRL_SIZE_4
mdefine_line|#define DRAM_CTRL_SIZE_4&t;&t;(0 &lt;&lt; 13)
DECL|macro|DRAM_CTRL_SIZE_8
mdefine_line|#define DRAM_CTRL_SIZE_8&t;&t;(1 &lt;&lt; 13)
DECL|macro|DRAM_CTRL_SIZE_16
mdefine_line|#define DRAM_CTRL_SIZE_16&t;&t;(2 &lt;&lt; 13)
DECL|macro|DRAM_CTRL_SIZE_32
mdefine_line|#define DRAM_CTRL_SIZE_32&t;&t;(3 &lt;&lt; 13)
DECL|macro|DRAM_CTRL_SIZE_64
mdefine_line|#define DRAM_CTRL_SIZE_64&t;&t;(4 &lt;&lt; 13)
DECL|macro|DRAM_CTRL_SIZE_2
mdefine_line|#define DRAM_CTRL_SIZE_2&t;&t;(5 &lt;&lt; 13)
DECL|macro|DRAM_CTRL_COLUMN_SIZE_256
mdefine_line|#define DRAM_CTRL_COLUMN_SIZE_256&t;(0 &lt;&lt; 11)
DECL|macro|DRAM_CTRL_COLUMN_SIZE_512
mdefine_line|#define DRAM_CTRL_COLUMN_SIZE_512&t;(2 &lt;&lt; 11)
DECL|macro|DRAM_CTRL_COLUMN_SIZE_1024
mdefine_line|#define DRAM_CTRL_COLUMN_SIZE_1024&t;(3 &lt;&lt; 11)
DECL|macro|DRAM_CTRL_BLOCK_WRITE_TIME
mdefine_line|#define DRAM_CTRL_BLOCK_WRITE_TIME&t;(1 &lt;&lt; 10)
DECL|macro|DRAM_CTRL_BLOCK_WRITE_PRECHARGE
mdefine_line|#define DRAM_CTRL_BLOCK_WRITE_PRECHARGE&t;(1 &lt;&lt; 9)
DECL|macro|DRAM_CTRL_ACTIVE_PRECHARGE
mdefine_line|#define DRAM_CTRL_ACTIVE_PRECHARGE&t;(1 &lt;&lt; 8)
DECL|macro|DRAM_CTRL_RESET
mdefine_line|#define DRAM_CTRL_RESET&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|DRAM_CTRL_REMAIN_ACTIVE
mdefine_line|#define DRAM_CTRL_REMAIN_ACTIVE&t;&t;(1 &lt;&lt; 6)
DECL|macro|DRAM_CTRL_BANKS
mdefine_line|#define DRAM_CTRL_BANKS&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|DRAM_CTRL_WRITE_PRECHARGE
mdefine_line|#define DRAM_CTRL_WRITE_PRECHARGE&t;(1 &lt;&lt; 0)
multiline_comment|/* ----- Arvitration control register -------------------------- */
DECL|macro|ARBITRATION_CTRL
mdefine_line|#define ARBITRATION_CTRL&t;&t;(0x000014 + VOYAGER_BASE)
DECL|macro|ARBITRATION_CTRL_CPUMEM
mdefine_line|#define ARBITRATION_CTRL_CPUMEM&t;&t;(1 &lt;&lt; 29)
DECL|macro|ARBITRATION_CTRL_INTMEM
mdefine_line|#define ARBITRATION_CTRL_INTMEM&t;&t;(1 &lt;&lt; 28)
DECL|macro|ARBITRATION_CTRL_USB_OFF
mdefine_line|#define ARBITRATION_CTRL_USB_OFF&t;(0 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_1&t;(1 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_2&t;(2 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_3&t;(3 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_4&t;(4 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_5&t;(5 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_6&t;(6 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_USB_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_USB_PRIORITY_7&t;(7 &lt;&lt; 24)
DECL|macro|ARBITRATION_CTRL_PANEL_OFF
mdefine_line|#define ARBITRATION_CTRL_PANEL_OFF&t;(0 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_1&t;(1 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_2&t;(2 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_3&t;(3 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_4&t;(4 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_5&t;(5 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_6&t;(6 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_PANEL_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_PANEL_PRIORITY_7&t;(7 &lt;&lt; 20)
DECL|macro|ARBITRATION_CTRL_ZVPORT_OFF
mdefine_line|#define ARBITRATION_CTRL_ZVPORT_OFF&t;(0 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_1&t;(1 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_2&t;(2 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_3&t;(3 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_4&t;(4 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_5&t;(5 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_6&t;(6 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_ZVPORTL_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_ZVPORTL_PRIORITY_7&t;(7 &lt;&lt; 16)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_OFF
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_OFF&t;(0 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_1&t;(1 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_2&t;(2 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_3&t;(3 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_4&t;(4 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_5&t;(5 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_6&t;(6 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_CMD_INTPR_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_CMD_INTPR_PRIORITY_7&t;(7 &lt;&lt; 12)
DECL|macro|ARBITRATION_CTRL_DMA_OFF
mdefine_line|#define ARBITRATION_CTRL_DMA_OFF&t;(0 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_1&t;(1 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_2&t;(2 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_3&t;(3 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_4&t;(4 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_5&t;(5 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_6&t;(6 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_DMA_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_DMA_PRIORITY_7&t;(7 &lt;&lt; 8)
DECL|macro|ARBITRATION_CTRL_VIDEO_OFF
mdefine_line|#define ARBITRATION_CTRL_VIDEO_OFF&t;(0 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_1&t;(1 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_2&t;(2 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_3&t;(3 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_4&t;(4 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_5&t;(5 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_6&t;(6 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_VIDEO_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_VIDEO_PRIORITY_7&t;(7 &lt;&lt; 4)
DECL|macro|ARBITRATION_CTRL_CRT_OFF
mdefine_line|#define ARBITRATION_CTRL_CRT_OFF&t;(0 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_1
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_1&t;(1 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_2
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_2&t;(2 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_3
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_3&t;(3 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_4
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_4&t;(4 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_5
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_5&t;(5 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_6
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_6&t;(6 &lt;&lt; 0)
DECL|macro|ARBITRATION_CTRL_CRT_PRIORITY_7
mdefine_line|#define ARBITRATION_CTRL_CRT_PRIORITY_7&t;(7 &lt;&lt; 0)
multiline_comment|/* ----- Command list status register -------------------------- */
DECL|macro|CMD_INTPR_STATUS
mdefine_line|#define CMD_INTPR_STATUS&t;&t;(0x000024 + VOYAGER_BASE)
multiline_comment|/* ----- Interrupt status register ----------------------------- */
DECL|macro|INT_STATUS
mdefine_line|#define INT_STATUS&t;&t;&t;(0x00002c + VOYAGER_BASE)
DECL|macro|INT_STATUS_UH
mdefine_line|#define INT_STATUS_UH&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|INT_STATUS_MC
mdefine_line|#define INT_STATUS_MC&t;&t;&t;(1 &lt;&lt; 10)
DECL|macro|INT_STATUS_U0
mdefine_line|#define INT_STATUS_U0&t;&t;&t;(1 &lt;&lt; 12)
DECL|macro|INT_STATUS_U1
mdefine_line|#define INT_STATUS_U1&t;&t;&t;(1 &lt;&lt; 13)
DECL|macro|INT_STATUS_AC
mdefine_line|#define&t;INT_STATUS_AC&t;&t;&t;(1 &lt;&lt; 17)
multiline_comment|/* ----- Interrupt mask register ------------------------------ */
DECL|macro|VOYAGER_INT_MASK
mdefine_line|#define VOYAGER_INT_MASK&t;&t;(0x000030 + VOYAGER_BASE)
DECL|macro|VOYAGER_INT_MASK_AC
mdefine_line|#define VOYAGER_INT_MASK_AC&t;&t;(1 &lt;&lt; 17)
multiline_comment|/* ----- Current Gate register ---------------------------------*/
DECL|macro|CURRENT_GATE
mdefine_line|#define CURRENT_GATE&t;&t;&t;(0x000038 + VOYAGER_BASE)
multiline_comment|/* ----- Power mode 0 gate register --------------------------- */
DECL|macro|POWER_MODE0_GATE
mdefine_line|#define POWER_MODE0_GATE&t;&t;(0x000040 + VOYAGER_BASE)
DECL|macro|POWER_MODE0_GATE_G
mdefine_line|#define POWER_MODE0_GATE_G&t;&t;(1 &lt;&lt; 6)
DECL|macro|POWER_MODE0_GATE_U0
mdefine_line|#define POWER_MODE0_GATE_U0&t;&t;(1 &lt;&lt; 7)
DECL|macro|POWER_MODE0_GATE_U1
mdefine_line|#define POWER_MODE0_GATE_U1&t;&t;(1 &lt;&lt; 8)
DECL|macro|POWER_MODE0_GATE_UH
mdefine_line|#define POWER_MODE0_GATE_UH&t;&t;(1 &lt;&lt; 11)
DECL|macro|POWER_MODE0_GATE_AC
mdefine_line|#define&t;POWER_MODE0_GATE_AC&t;&t;(1 &lt;&lt; 18)
multiline_comment|/* ----- Power mode 1 gate register --------------------------- */
DECL|macro|POWER_MODE1_GATE
mdefine_line|#define POWER_MODE1_GATE&t;&t;(0x000048 + VOYAGER_BASE)
DECL|macro|POWER_MODE1_GATE_G
mdefine_line|#define POWER_MODE1_GATE_G&t;&t;(1 &lt;&lt; 6)
DECL|macro|POWER_MODE1_GATE_U0
mdefine_line|#define POWER_MODE1_GATE_U0&t;&t;(1 &lt;&lt; 7)
DECL|macro|POWER_MODE1_GATE_U1
mdefine_line|#define POWER_MODE1_GATE_U1&t;&t;(1 &lt;&lt; 8)
DECL|macro|POWER_MODE1_GATE_UH
mdefine_line|#define POWER_MODE1_GATE_UH&t;&t;(1 &lt;&lt; 11)
DECL|macro|POWER_MODE1_GATE_AC
mdefine_line|#define&t;POWER_MODE1_GATE_AC&t;&t;(1 &lt;&lt; 18)
multiline_comment|/* ----- Power mode 0 clock register -------------------------- */
DECL|macro|POWER_MODE0_CLOCK
mdefine_line|#define POWER_MODE0_CLOCK&t;&t;(0x000044 + VOYAGER_BASE)
multiline_comment|/* ----- Power mode 1 clock register -------------------------- */
DECL|macro|POWER_MODE1_CLOCK
mdefine_line|#define POWER_MODE1_CLOCK&t;&t;(0x00004C + VOYAGER_BASE)
multiline_comment|/* ----- Power mode controll register ------------------------- */
DECL|macro|POWER_MODE_CTRL
mdefine_line|#define POWER_MODE_CTRL&t;&t;&t;(0x000054 + VOYAGER_BASE)
multiline_comment|/* ----- Miscellaneous Timing register ------------------------ */
DECL|macro|SYSTEM_DRAM_CTRL
mdefine_line|#define SYSTEM_DRAM_CTRL&t;&t;(0x000068 + VOYAGER_BASE)
multiline_comment|/* ----- PWM register ------------------------------------------*/
DECL|macro|PWM_0
mdefine_line|#define PWM_0&t;&t;&t;&t;(0x010020 + VOYAGER_BASE)
DECL|macro|PWM_0_HC
mdefine_line|#define PWM_0_HC(x)&t;&t;&t;(((x)&amp;0x0fff)&lt;&lt;20)
DECL|macro|PWM_0_LC
mdefine_line|#define PWM_0_LC(x)&t;&t;&t;(((x)&amp;0x0fff)&lt;&lt;8 )
DECL|macro|PWM_0_CLK_DEV
mdefine_line|#define PWM_0_CLK_DEV(x)&t;&t;(((x)&amp;0x000f)&lt;&lt;4 )
DECL|macro|PWM_0_EN
mdefine_line|#define PWM_0_EN&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/* ----- I2C register ----------------------------------------- */
DECL|macro|I2C_BYTECOUNT
mdefine_line|#define I2C_BYTECOUNT&t;&t;&t;(0x010040 + VOYAGER_BASE)
DECL|macro|I2C_CONTROL
mdefine_line|#define I2C_CONTROL&t;&t;&t;(0x010041 + VOYAGER_BASE)
DECL|macro|I2C_STATUS
mdefine_line|#define I2C_STATUS&t;&t;&t;(0x010042 + VOYAGER_BASE)
DECL|macro|I2C_RESET
mdefine_line|#define I2C_RESET&t;&t;&t;(0x010042 + VOYAGER_BASE)
DECL|macro|I2C_SADDRESS
mdefine_line|#define I2C_SADDRESS&t;&t;&t;(0x010043 + VOYAGER_BASE)
DECL|macro|I2C_DATA
mdefine_line|#define I2C_DATA&t;&t;&t;(0x010044 + VOYAGER_BASE)
multiline_comment|/* ----- Controle register bits ----------------------------------------- */
DECL|macro|I2C_CONTROL_E
mdefine_line|#define I2C_CONTROL_E&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|I2C_CONTROL_MODE
mdefine_line|#define I2C_CONTROL_MODE&t;&t;(1 &lt;&lt; 1)
DECL|macro|I2C_CONTROL_STATUS
mdefine_line|#define I2C_CONTROL_STATUS&t;&t;(1 &lt;&lt; 2)
DECL|macro|I2C_CONTROL_INT
mdefine_line|#define I2C_CONTROL_INT&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|I2C_CONTROL_INTACK
mdefine_line|#define I2C_CONTROL_INTACK&t;&t;(1 &lt;&lt; 5)
DECL|macro|I2C_CONTROL_REPEAT
mdefine_line|#define I2C_CONTROL_REPEAT&t;&t;(1 &lt;&lt; 6)
multiline_comment|/* ----- Status register bits ----------------------------------------- */
DECL|macro|I2C_STATUS_BUSY
mdefine_line|#define I2C_STATUS_BUSY&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|I2C_STATUS_ACK
mdefine_line|#define I2C_STATUS_ACK&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|I2C_STATUS_ERROR
mdefine_line|#define I2C_STATUS_ERROR&t;&t;(1 &lt;&lt; 2)
DECL|macro|I2C_STATUS_COMPLETE
mdefine_line|#define I2C_STATUS_COMPLETE&t;&t;(1 &lt;&lt; 3)
multiline_comment|/* ----- Reset register  ---------------------------------------------- */
DECL|macro|I2C_RESET_ERROR
mdefine_line|#define I2C_RESET_ERROR&t;&t;&t;(1 &lt;&lt; 2)
multiline_comment|/* ----- transmission frequencies ------------------------------------- */
DECL|macro|I2C_SADDRESS_SELECT
mdefine_line|#define I2C_SADDRESS_SELECT&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* ----- Display Controll register ----------------------------------------- */
DECL|macro|PANEL_DISPLAY_CTRL
mdefine_line|#define PANEL_DISPLAY_CTRL&t;&t;(0x080000 + VOYAGER_BASE)
DECL|macro|PANEL_DISPLAY_CTRL_BIAS
mdefine_line|#define PANEL_DISPLAY_CTRL_BIAS         (1&lt;&lt;26)
DECL|macro|PANEL_PAN_CTRL
mdefine_line|#define PANEL_PAN_CTRL&t;&t;&t;(0x080004 + VOYAGER_BASE)
DECL|macro|PANEL_COLOR_KEY
mdefine_line|#define PANEL_COLOR_KEY&t;&t;&t;(0x080008 + VOYAGER_BASE)
DECL|macro|PANEL_FB_ADDRESS
mdefine_line|#define PANEL_FB_ADDRESS&t;&t;(0x08000C + VOYAGER_BASE)
DECL|macro|PANEL_FB_WIDTH
mdefine_line|#define PANEL_FB_WIDTH&t;&t;&t;(0x080010 + VOYAGER_BASE)
DECL|macro|PANEL_WINDOW_WIDTH
mdefine_line|#define PANEL_WINDOW_WIDTH&t;&t;(0x080014 + VOYAGER_BASE)
DECL|macro|PANEL_WINDOW_HEIGHT
mdefine_line|#define PANEL_WINDOW_HEIGHT&t;&t;(0x080018 + VOYAGER_BASE)
DECL|macro|PANEL_PLANE_TL
mdefine_line|#define PANEL_PLANE_TL&t;&t;&t;(0x08001C + VOYAGER_BASE)
DECL|macro|PANEL_PLANE_BR
mdefine_line|#define PANEL_PLANE_BR&t;&t;&t;(0x080020 + VOYAGER_BASE)
DECL|macro|PANEL_HORIZONTAL_TOTAL
mdefine_line|#define PANEL_HORIZONTAL_TOTAL&t;&t;(0x080024 + VOYAGER_BASE)
DECL|macro|PANEL_HORIZONTAL_SYNC
mdefine_line|#define PANEL_HORIZONTAL_SYNC&t;&t;(0x080028 + VOYAGER_BASE)
DECL|macro|PANEL_VERTICAL_TOTAL
mdefine_line|#define PANEL_VERTICAL_TOTAL&t;&t;(0x08002C + VOYAGER_BASE)
DECL|macro|PANEL_VERTICAL_SYNC
mdefine_line|#define PANEL_VERTICAL_SYNC&t;&t;(0x080030 + VOYAGER_BASE)
DECL|macro|PANEL_CURRENT_LINE
mdefine_line|#define PANEL_CURRENT_LINE&t;&t;(0x080034 + VOYAGER_BASE)
DECL|macro|VIDEO_DISPLAY_CTRL
mdefine_line|#define VIDEO_DISPLAY_CTRL&t;&t;(0x080040 + VOYAGER_BASE)
DECL|macro|VIDEO_FB_0_ADDRESS
mdefine_line|#define VIDEO_FB_0_ADDRESS&t;&t;(0x080044 + VOYAGER_BASE)
DECL|macro|VIDEO_FB_WIDTH
mdefine_line|#define VIDEO_FB_WIDTH&t;&t;&t;(0x080048 + VOYAGER_BASE)
DECL|macro|VIDEO_FB_0_LAST_ADDRESS
mdefine_line|#define VIDEO_FB_0_LAST_ADDRESS&t;&t;(0x08004C + VOYAGER_BASE)
DECL|macro|VIDEO_PLANE_TL
mdefine_line|#define VIDEO_PLANE_TL&t;&t;&t;(0x080050 + VOYAGER_BASE)
DECL|macro|VIDEO_PLANE_BR
mdefine_line|#define VIDEO_PLANE_BR&t;&t;&t;(0x080054 + VOYAGER_BASE)
DECL|macro|VIDEO_SCALE
mdefine_line|#define VIDEO_SCALE&t;&t;&t;(0x080058 + VOYAGER_BASE)
DECL|macro|VIDEO_INITIAL_SCALE
mdefine_line|#define VIDEO_INITIAL_SCALE&t;&t;(0x08005C + VOYAGER_BASE)
DECL|macro|VIDEO_YUV_CONSTANTS
mdefine_line|#define VIDEO_YUV_CONSTANTS&t;&t;(0x080060 + VOYAGER_BASE)
DECL|macro|VIDEO_FB_1_ADDRESS
mdefine_line|#define VIDEO_FB_1_ADDRESS&t;&t;(0x080064 + VOYAGER_BASE)
DECL|macro|VIDEO_FB_1_LAST_ADDRESS
mdefine_line|#define VIDEO_FB_1_LAST_ADDRESS&t;&t;(0x080068 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_DISPLAY_CTRL
mdefine_line|#define VIDEO_ALPHA_DISPLAY_CTRL&t;(0x080080 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_FB_ADDRESS
mdefine_line|#define VIDEO_ALPHA_FB_ADDRESS&t;&t;(0x080084 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_FB_WIDTH
mdefine_line|#define VIDEO_ALPHA_FB_WIDTH&t;&t;(0x080088 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_FB_LAST_ADDRESS
mdefine_line|#define VIDEO_ALPHA_FB_LAST_ADDRESS&t;(0x08008C + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_PLANE_TL
mdefine_line|#define VIDEO_ALPHA_PLANE_TL&t;&t;(0x080090 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_PLANE_BR
mdefine_line|#define VIDEO_ALPHA_PLANE_BR&t;&t;(0x080094 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_SCALE
mdefine_line|#define VIDEO_ALPHA_SCALE&t;&t;(0x080098 + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_INITIAL_SCALE
mdefine_line|#define VIDEO_ALPHA_INITIAL_SCALE&t;(0x08009C + VOYAGER_BASE)
DECL|macro|VIDEO_ALPHA_CHROMA_KEY
mdefine_line|#define VIDEO_ALPHA_CHROMA_KEY&t;&t;(0x0800A0 + VOYAGER_BASE)
DECL|macro|PANEL_HWC_ADDRESS
mdefine_line|#define PANEL_HWC_ADDRESS&t;&t;(0x0800F0 + VOYAGER_BASE)
DECL|macro|PANEL_HWC_LOCATION
mdefine_line|#define PANEL_HWC_LOCATION&t;&t;(0x0800F4 + VOYAGER_BASE)
DECL|macro|PANEL_HWC_COLOR_12
mdefine_line|#define PANEL_HWC_COLOR_12&t;&t;(0x0800F8 + VOYAGER_BASE)
DECL|macro|PANEL_HWC_COLOR_3
mdefine_line|#define PANEL_HWC_COLOR_3&t;&t;(0x0800FC + VOYAGER_BASE)
DECL|macro|ALPHA_DISPLAY_CTRL
mdefine_line|#define ALPHA_DISPLAY_CTRL&t;&t;(0x080100 + VOYAGER_BASE)
DECL|macro|ALPHA_FB_ADDRESS
mdefine_line|#define ALPHA_FB_ADDRESS&t;&t;(0x080104 + VOYAGER_BASE)
DECL|macro|ALPHA_FB_WIDTH
mdefine_line|#define ALPHA_FB_WIDTH&t;&t;&t;(0x080108 + VOYAGER_BASE)
DECL|macro|ALPHA_PLANE_TL
mdefine_line|#define ALPHA_PLANE_TL&t;&t;&t;(0x08010C + VOYAGER_BASE)
DECL|macro|ALPHA_PLANE_BR
mdefine_line|#define ALPHA_PLANE_BR&t;&t;&t;(0x080110 + VOYAGER_BASE)
DECL|macro|ALPHA_CHROMA_KEY
mdefine_line|#define ALPHA_CHROMA_KEY&t;&t;(0x080114 + VOYAGER_BASE)
DECL|macro|CRT_DISPLAY_CTRL
mdefine_line|#define CRT_DISPLAY_CTRL&t;&t;(0x080200 + VOYAGER_BASE)
DECL|macro|CRT_FB_ADDRESS
mdefine_line|#define CRT_FB_ADDRESS&t;&t;&t;(0x080204 + VOYAGER_BASE)
DECL|macro|CRT_FB_WIDTH
mdefine_line|#define CRT_FB_WIDTH&t;&t;&t;(0x080208 + VOYAGER_BASE)
DECL|macro|CRT_HORIZONTAL_TOTAL
mdefine_line|#define CRT_HORIZONTAL_TOTAL&t;&t;(0x08020C + VOYAGER_BASE)
DECL|macro|CRT_HORIZONTAL_SYNC
mdefine_line|#define CRT_HORIZONTAL_SYNC&t;&t;(0x080210 + VOYAGER_BASE)
DECL|macro|CRT_VERTICAL_TOTAL
mdefine_line|#define CRT_VERTICAL_TOTAL&t;&t;(0x080214 + VOYAGER_BASE)
DECL|macro|CRT_VERTICAL_SYNC
mdefine_line|#define CRT_VERTICAL_SYNC&t;&t;(0x080218 + VOYAGER_BASE)
DECL|macro|CRT_SIGNATURE_ANALYZER
mdefine_line|#define CRT_SIGNATURE_ANALYZER&t;&t;(0x08021C + VOYAGER_BASE)
DECL|macro|CRT_CURRENT_LINE
mdefine_line|#define CRT_CURRENT_LINE&t;&t;(0x080220 + VOYAGER_BASE)
DECL|macro|CRT_MONITOR_DETECT
mdefine_line|#define CRT_MONITOR_DETECT&t;&t;(0x080224 + VOYAGER_BASE)
DECL|macro|CRT_HWC_ADDRESS
mdefine_line|#define CRT_HWC_ADDRESS&t;&t;&t;(0x080230 + VOYAGER_BASE)
DECL|macro|CRT_HWC_LOCATION
mdefine_line|#define CRT_HWC_LOCATION&t;&t;(0x080234 + VOYAGER_BASE)
DECL|macro|CRT_HWC_COLOR_12
mdefine_line|#define CRT_HWC_COLOR_12&t;&t;(0x080238 + VOYAGER_BASE)
DECL|macro|CRT_HWC_COLOR_3
mdefine_line|#define CRT_HWC_COLOR_3&t;&t;&t;(0x08023C + VOYAGER_BASE)
DECL|macro|CRT_PALETTE_RAM
mdefine_line|#define CRT_PALETTE_RAM&t;&t;&t;(0x080400 + VOYAGER_BASE)
DECL|macro|PANEL_PALETTE_RAM
mdefine_line|#define PANEL_PALETTE_RAM&t;&t;(0x080800 + VOYAGER_BASE)
DECL|macro|VIDEO_PALETTE_RAM
mdefine_line|#define VIDEO_PALETTE_RAM&t;&t;(0x080C00 + VOYAGER_BASE)
multiline_comment|/* ----- 8051 Controle register ----------------------------------------- */
DECL|macro|VOYAGER_8051_BASE
mdefine_line|#define VOYAGER_8051_BASE&t;&t;(0x000c0000 + VOYAGER_BASE)
DECL|macro|VOYAGER_8051_RESET
mdefine_line|#define VOYAGER_8051_RESET&t;&t;(0x000b0000 + VOYAGER_BASE)
DECL|macro|VOYAGER_8051_SELECT
mdefine_line|#define VOYAGER_8051_SELECT&t;&t;(0x000b0004 + VOYAGER_BASE)
DECL|macro|VOYAGER_8051_CPU_INT
mdefine_line|#define VOYAGER_8051_CPU_INT&t;&t;(0x000b000c + VOYAGER_BASE)
multiline_comment|/* ----- AC97 Controle register ----------------------------------------- */
DECL|macro|AC97_TX_SLOT0
mdefine_line|#define AC97_TX_SLOT0&t;&t;&t;(0x00000000 + VOYAGER_AC97_BASE)
DECL|macro|AC97_CONTROL_STATUS
mdefine_line|#define AC97_CONTROL_STATUS&t;&t;(0x00000080 + VOYAGER_AC97_BASE)
DECL|macro|AC97C_READ
mdefine_line|#define AC97C_READ&t;&t;&t;(1 &lt;&lt; 19)
DECL|macro|AC97C_WD_BIT
mdefine_line|#define AC97C_WD_BIT&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|AC97C_INDEX_MASK
mdefine_line|#define AC97C_INDEX_MASK&t;&t;0x7f
multiline_comment|/* -------------------------------------------------------------------- */
macro_line|#endif /* _VOYAGER_GX_REG_H */
eof
