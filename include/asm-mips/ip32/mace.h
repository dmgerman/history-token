multiline_comment|/*&n; * Definitions for the SGI MACE (Multimedia, Audio and Communications Engine)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; * Copyright (C) 2004 Ladislav Michl&n; */
macro_line|#ifndef __ASM_MACE_H__
DECL|macro|__ASM_MACE_H__
mdefine_line|#define __ASM_MACE_H__
multiline_comment|/*&n; * Address map&n; */
DECL|macro|MACE_BASE
mdefine_line|#define MACE_BASE&t;0x1f000000&t;/* physical */
DECL|macro|BIT
macro_line|#undef BIT
DECL|macro|BIT
mdefine_line|#define BIT(x) (1UL &lt;&lt; (x))
multiline_comment|/*&n; * PCI interface&n; */
DECL|struct|mace_pci
r_struct
id|mace_pci
(brace
DECL|member|error_addr
r_volatile
r_int
r_int
id|error_addr
suffix:semicolon
DECL|member|error
r_volatile
r_int
r_int
id|error
suffix:semicolon
DECL|macro|MACEPCI_ERROR_MASTER_ABORT
mdefine_line|#define MACEPCI_ERROR_MASTER_ABORT&t;&t;BIT(31)
DECL|macro|MACEPCI_ERROR_TARGET_ABORT
mdefine_line|#define MACEPCI_ERROR_TARGET_ABORT&t;&t;BIT(30)
DECL|macro|MACEPCI_ERROR_DATA_PARITY_ERR
mdefine_line|#define MACEPCI_ERROR_DATA_PARITY_ERR&t;&t;BIT(29)
DECL|macro|MACEPCI_ERROR_RETRY_ERR
mdefine_line|#define MACEPCI_ERROR_RETRY_ERR&t;&t;&t;BIT(28)
DECL|macro|MACEPCI_ERROR_ILLEGAL_CMD
mdefine_line|#define MACEPCI_ERROR_ILLEGAL_CMD&t;&t;BIT(27)
DECL|macro|MACEPCI_ERROR_SYSTEM_ERR
mdefine_line|#define MACEPCI_ERROR_SYSTEM_ERR&t;&t;BIT(26)
DECL|macro|MACEPCI_ERROR_INTERRUPT_TEST
mdefine_line|#define MACEPCI_ERROR_INTERRUPT_TEST&t;&t;BIT(25)
DECL|macro|MACEPCI_ERROR_PARITY_ERR
mdefine_line|#define MACEPCI_ERROR_PARITY_ERR&t;&t;BIT(24)
DECL|macro|MACEPCI_ERROR_OVERRUN
mdefine_line|#define MACEPCI_ERROR_OVERRUN&t;&t;&t;BIT(23)
DECL|macro|MACEPCI_ERROR_RSVD
mdefine_line|#define MACEPCI_ERROR_RSVD&t;&t;&t;BIT(22)
DECL|macro|MACEPCI_ERROR_MEMORY_ADDR
mdefine_line|#define MACEPCI_ERROR_MEMORY_ADDR&t;&t;BIT(21)
DECL|macro|MACEPCI_ERROR_CONFIG_ADDR
mdefine_line|#define MACEPCI_ERROR_CONFIG_ADDR&t;&t;BIT(20)
DECL|macro|MACEPCI_ERROR_MASTER_ABORT_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_MASTER_ABORT_ADDR_VALID&t;BIT(19)
DECL|macro|MACEPCI_ERROR_TARGET_ABORT_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_TARGET_ABORT_ADDR_VALID&t;BIT(18)
DECL|macro|MACEPCI_ERROR_DATA_PARITY_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_DATA_PARITY_ADDR_VALID&t;BIT(17)
DECL|macro|MACEPCI_ERROR_RETRY_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_RETRY_ADDR_VALID&t;&t;BIT(16)
DECL|macro|MACEPCI_ERROR_SIG_TABORT
mdefine_line|#define MACEPCI_ERROR_SIG_TABORT&t;&t;BIT(4)
DECL|macro|MACEPCI_ERROR_DEVSEL_MASK
mdefine_line|#define MACEPCI_ERROR_DEVSEL_MASK&t;&t;0xc0
DECL|macro|MACEPCI_ERROR_DEVSEL_FAST
mdefine_line|#define MACEPCI_ERROR_DEVSEL_FAST&t;&t;0
DECL|macro|MACEPCI_ERROR_DEVSEL_MED
mdefine_line|#define MACEPCI_ERROR_DEVSEL_MED&t;&t;0x40
DECL|macro|MACEPCI_ERROR_DEVSEL_SLOW
mdefine_line|#define MACEPCI_ERROR_DEVSEL_SLOW&t;&t;0x80
DECL|macro|MACEPCI_ERROR_FBB
mdefine_line|#define MACEPCI_ERROR_FBB&t;&t;&t;BIT(1)
DECL|macro|MACEPCI_ERROR_66MHZ
mdefine_line|#define MACEPCI_ERROR_66MHZ&t;&t;&t;BIT(0)
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
DECL|macro|MACEPCI_CONTROL_INT
mdefine_line|#define MACEPCI_CONTROL_INT(x)&t;&t;&t;BIT(x)
DECL|macro|MACEPCI_CONTROL_INT_MASK
mdefine_line|#define MACEPCI_CONTROL_INT_MASK&t;&t;0xff
DECL|macro|MACEPCI_CONTROL_SERR_ENA
mdefine_line|#define MACEPCI_CONTROL_SERR_ENA&t;&t;BIT(8)
DECL|macro|MACEPCI_CONTROL_ARB_N6
mdefine_line|#define MACEPCI_CONTROL_ARB_N6&t;&t;&t;BIT(9)
DECL|macro|MACEPCI_CONTROL_PARITY_ERR
mdefine_line|#define MACEPCI_CONTROL_PARITY_ERR&t;&t;BIT(10)
DECL|macro|MACEPCI_CONTROL_MRMRA_ENA
mdefine_line|#define MACEPCI_CONTROL_MRMRA_ENA&t;&t;BIT(11)
DECL|macro|MACEPCI_CONTROL_ARB_N3
mdefine_line|#define MACEPCI_CONTROL_ARB_N3&t;&t;&t;BIT(12)
DECL|macro|MACEPCI_CONTROL_ARB_N4
mdefine_line|#define MACEPCI_CONTROL_ARB_N4&t;&t;&t;BIT(13)
DECL|macro|MACEPCI_CONTROL_ARB_N5
mdefine_line|#define MACEPCI_CONTROL_ARB_N5&t;&t;&t;BIT(14)
DECL|macro|MACEPCI_CONTROL_PARK_LIU
mdefine_line|#define MACEPCI_CONTROL_PARK_LIU&t;&t;BIT(15)
DECL|macro|MACEPCI_CONTROL_INV_INT
mdefine_line|#define MACEPCI_CONTROL_INV_INT(x)&t;&t;BIT(16+x)
DECL|macro|MACEPCI_CONTROL_INV_INT_MASK
mdefine_line|#define MACEPCI_CONTROL_INV_INT_MASK&t;&t;0x00ff0000
DECL|macro|MACEPCI_CONTROL_OVERRUN_INT
mdefine_line|#define MACEPCI_CONTROL_OVERRUN_INT&t;&t;BIT(24)
DECL|macro|MACEPCI_CONTROL_PARITY_INT
mdefine_line|#define MACEPCI_CONTROL_PARITY_INT&t;&t;BIT(25)
DECL|macro|MACEPCI_CONTROL_SERR_INT
mdefine_line|#define MACEPCI_CONTROL_SERR_INT&t;&t;BIT(26)
DECL|macro|MACEPCI_CONTROL_IT_INT
mdefine_line|#define MACEPCI_CONTROL_IT_INT&t;&t;&t;BIT(27)
DECL|macro|MACEPCI_CONTROL_RE_INT
mdefine_line|#define MACEPCI_CONTROL_RE_INT&t;&t;&t;BIT(28)
DECL|macro|MACEPCI_CONTROL_DPED_INT
mdefine_line|#define MACEPCI_CONTROL_DPED_INT&t;&t;BIT(29)
DECL|macro|MACEPCI_CONTROL_TAR_INT
mdefine_line|#define MACEPCI_CONTROL_TAR_INT&t;&t;&t;BIT(30)
DECL|macro|MACEPCI_CONTROL_MAR_INT
mdefine_line|#define MACEPCI_CONTROL_MAR_INT&t;&t;&t;BIT(31)
DECL|member|rev
r_volatile
r_int
r_int
id|rev
suffix:semicolon
DECL|member|_pad
r_int
r_int
id|_pad
(braket
l_int|0xcf8
op_div
l_int|4
op_minus
l_int|4
)braket
suffix:semicolon
DECL|member|config_addr
r_volatile
r_int
r_int
id|config_addr
suffix:semicolon
r_union
(brace
DECL|member|b
r_volatile
r_int
r_char
id|b
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|w
r_volatile
r_int
r_int
id|w
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_volatile
r_int
r_int
id|l
suffix:semicolon
DECL|member|config_data
)brace
id|config_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MACEPCI_LOW_MEMORY
mdefine_line|#define MACEPCI_LOW_MEMORY&t;&t;0x1a000000
DECL|macro|MACEPCI_LOW_IO
mdefine_line|#define MACEPCI_LOW_IO&t;&t;&t;0x18000000
DECL|macro|MACEPCI_SWAPPED_VIEW
mdefine_line|#define MACEPCI_SWAPPED_VIEW&t;&t;0
DECL|macro|MACEPCI_NATIVE_VIEW
mdefine_line|#define MACEPCI_NATIVE_VIEW&t;&t;0x40000000
DECL|macro|MACEPCI_IO
mdefine_line|#define MACEPCI_IO&t;&t;&t;0x80000000
DECL|macro|MACEPCI_HI_MEMORY
mdefine_line|#define MACEPCI_HI_MEMORY&t;&t;0x280000000
DECL|macro|MACEPCI_HI_IO
mdefine_line|#define MACEPCI_HI_IO&t;&t;&t;0x100000000
multiline_comment|/*&n; * Video interface&n; */
DECL|struct|mace_video
r_struct
id|mace_video
(brace
DECL|member|xxx
r_int
r_int
id|xxx
suffix:semicolon
multiline_comment|/* later... */
)brace
suffix:semicolon
multiline_comment|/* &n; * Ethernet interface&n; */
DECL|struct|mace_ethernet
r_struct
id|mace_ethernet
(brace
DECL|member|mac_ctrl
r_volatile
r_int
r_int
id|mac_ctrl
suffix:semicolon
DECL|member|int_stat
r_volatile
r_int
r_int
id|int_stat
suffix:semicolon
DECL|member|dma_ctrl
r_volatile
r_int
r_int
id|dma_ctrl
suffix:semicolon
DECL|member|timer
r_volatile
r_int
r_int
id|timer
suffix:semicolon
DECL|member|tx_int_al
r_volatile
r_int
r_int
id|tx_int_al
suffix:semicolon
DECL|member|rx_int_al
r_volatile
r_int
r_int
id|rx_int_al
suffix:semicolon
DECL|member|tx_info
r_volatile
r_int
r_int
id|tx_info
suffix:semicolon
DECL|member|tx_info_al
r_volatile
r_int
r_int
id|tx_info_al
suffix:semicolon
DECL|member|rx_buff
r_volatile
r_int
r_int
id|rx_buff
suffix:semicolon
DECL|member|rx_buff_al1
r_volatile
r_int
r_int
id|rx_buff_al1
suffix:semicolon
DECL|member|rx_buff_al2
r_volatile
r_int
r_int
id|rx_buff_al2
suffix:semicolon
DECL|member|diag
r_volatile
r_int
r_int
id|diag
suffix:semicolon
DECL|member|phy_data
r_volatile
r_int
r_int
id|phy_data
suffix:semicolon
DECL|member|phy_regs
r_volatile
r_int
r_int
id|phy_regs
suffix:semicolon
DECL|member|phy_trans_go
r_volatile
r_int
r_int
id|phy_trans_go
suffix:semicolon
DECL|member|backoff_seed
r_volatile
r_int
r_int
id|backoff_seed
suffix:semicolon
multiline_comment|/*===================================*/
DECL|member|imq_reserved
r_volatile
r_int
r_int
id|imq_reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|mac_addr
r_volatile
r_int
r_int
id|mac_addr
suffix:semicolon
DECL|member|mac_addr2
r_volatile
r_int
r_int
id|mac_addr2
suffix:semicolon
DECL|member|mcast_filter
r_volatile
r_int
r_int
id|mcast_filter
suffix:semicolon
DECL|member|tx_ring_base
r_volatile
r_int
r_int
id|tx_ring_base
suffix:semicolon
multiline_comment|/* Following are read-only registers for debugging */
DECL|member|tx_pkt1_hdr
r_volatile
r_int
r_int
id|tx_pkt1_hdr
suffix:semicolon
DECL|member|tx_pkt1_ptr
r_volatile
r_int
r_int
id|tx_pkt1_ptr
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tx_pkt2_hdr
r_volatile
r_int
r_int
id|tx_pkt2_hdr
suffix:semicolon
DECL|member|tx_pkt2_ptr
r_volatile
r_int
r_int
id|tx_pkt2_ptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/*===================================*/
DECL|member|rx_fifo
r_volatile
r_int
r_int
id|rx_fifo
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Peripherals&n; */
multiline_comment|/* Audio registers */
DECL|struct|mace_audio
r_struct
id|mace_audio
(brace
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
DECL|member|codec_control
r_volatile
r_int
r_int
id|codec_control
suffix:semicolon
multiline_comment|/* codec status control */
DECL|member|codec_mask
r_volatile
r_int
r_int
id|codec_mask
suffix:semicolon
multiline_comment|/* codec status input mask */
DECL|member|codec_read
r_volatile
r_int
r_int
id|codec_read
suffix:semicolon
multiline_comment|/* codec status read data */
r_struct
(brace
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
multiline_comment|/* channel control */
DECL|member|read_ptr
r_volatile
r_int
r_int
id|read_ptr
suffix:semicolon
multiline_comment|/* channel read pointer */
DECL|member|write_ptr
r_volatile
r_int
r_int
id|write_ptr
suffix:semicolon
multiline_comment|/* channel write pointer */
DECL|member|depth
r_volatile
r_int
r_int
id|depth
suffix:semicolon
multiline_comment|/* channel depth */
DECL|member|chan
)brace
id|chan
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ISA Control and DMA registers */
DECL|struct|mace_isactrl
r_struct
id|mace_isactrl
(brace
DECL|member|ringbase
r_volatile
r_int
r_int
id|ringbase
suffix:semicolon
DECL|macro|MACEISA_RINGBUFFERS_SIZE
mdefine_line|#define MACEISA_RINGBUFFERS_SIZE&t;(8 * 4096)
DECL|member|misc
r_volatile
r_int
r_int
id|misc
suffix:semicolon
DECL|macro|MACEISA_FLASH_WE
mdefine_line|#define MACEISA_FLASH_WE&t;&t;BIT(0)&t;/* 1=&gt; Enable FLASH writes */
DECL|macro|MACEISA_PWD_CLEAR
mdefine_line|#define MACEISA_PWD_CLEAR&t;&t;BIT(1)&t;/* 1=&gt; PWD CLEAR jumper detected */
DECL|macro|MACEISA_NIC_DEASSERT
mdefine_line|#define MACEISA_NIC_DEASSERT&t;&t;BIT(2)
DECL|macro|MACEISA_NIC_DATA
mdefine_line|#define MACEISA_NIC_DATA&t;&t;BIT(3)
DECL|macro|MACEISA_LED_RED
mdefine_line|#define MACEISA_LED_RED&t;&t;&t;BIT(4)&t;/* 0=&gt; Illuminate red LED */
DECL|macro|MACEISA_LED_GREEN
mdefine_line|#define MACEISA_LED_GREEN&t;&t;BIT(5)&t;/* 0=&gt; Illuminate green LED */
DECL|macro|MACEISA_DP_RAM_ENABLE
mdefine_line|#define MACEISA_DP_RAM_ENABLE&t;&t;BIT(6)
DECL|member|istat
r_volatile
r_int
r_int
id|istat
suffix:semicolon
DECL|member|imask
r_volatile
r_int
r_int
id|imask
suffix:semicolon
DECL|macro|MACEISA_AUDIO_SW_INT
mdefine_line|#define MACEISA_AUDIO_SW_INT&t;&t;BIT(0)
DECL|macro|MACEISA_AUDIO_SC_INT
mdefine_line|#define MACEISA_AUDIO_SC_INT&t;&t;BIT(1)
DECL|macro|MACEISA_AUDIO1_DMAT_INT
mdefine_line|#define MACEISA_AUDIO1_DMAT_INT&t;&t;BIT(2)
DECL|macro|MACEISA_AUDIO1_OF_INT
mdefine_line|#define MACEISA_AUDIO1_OF_INT&t;&t;BIT(3)
DECL|macro|MACEISA_AUDIO2_DMAT_INT
mdefine_line|#define MACEISA_AUDIO2_DMAT_INT&t;&t;BIT(4)
DECL|macro|MACEISA_AUDIO2_MERR_INT
mdefine_line|#define MACEISA_AUDIO2_MERR_INT&t;&t;BIT(5)
DECL|macro|MACEISA_AUDIO3_DMAT_INT
mdefine_line|#define MACEISA_AUDIO3_DMAT_INT&t;&t;BIT(6)
DECL|macro|MACEISA_AUDIO3_MERR_INT
mdefine_line|#define MACEISA_AUDIO3_MERR_INT&t;&t;BIT(7)
DECL|macro|MACEISA_RTC_INT
mdefine_line|#define MACEISA_RTC_INT&t;&t;&t;BIT(8)
DECL|macro|MACEISA_KEYB_INT
mdefine_line|#define MACEISA_KEYB_INT&t;&t;BIT(9)
DECL|macro|MACEISA_KEYB_POLL_INT
mdefine_line|#define MACEISA_KEYB_POLL_INT&t;&t;BIT(10)
DECL|macro|MACEISA_MOUSE_INT
mdefine_line|#define MACEISA_MOUSE_INT&t;&t;BIT(11)
DECL|macro|MACEISA_MOUSE_POLL_INT
mdefine_line|#define MACEISA_MOUSE_POLL_INT&t;&t;BIT(12)
DECL|macro|MACEISA_TIMER0_INT
mdefine_line|#define MACEISA_TIMER0_INT&t;&t;BIT(13)
DECL|macro|MACEISA_TIMER1_INT
mdefine_line|#define MACEISA_TIMER1_INT&t;&t;BIT(14)
DECL|macro|MACEISA_TIMER2_INT
mdefine_line|#define MACEISA_TIMER2_INT&t;&t;BIT(15)
DECL|macro|MACEISA_PARALLEL_INT
mdefine_line|#define MACEISA_PARALLEL_INT&t;&t;BIT(16)
DECL|macro|MACEISA_PAR_CTXA_INT
mdefine_line|#define MACEISA_PAR_CTXA_INT&t;&t;BIT(17)
DECL|macro|MACEISA_PAR_CTXB_INT
mdefine_line|#define MACEISA_PAR_CTXB_INT&t;&t;BIT(18)
DECL|macro|MACEISA_PAR_MERR_INT
mdefine_line|#define MACEISA_PAR_MERR_INT&t;&t;BIT(19)
DECL|macro|MACEISA_SERIAL1_INT
mdefine_line|#define MACEISA_SERIAL1_INT&t;&t;BIT(20)
DECL|macro|MACEISA_SERIAL1_TDMAT_INT
mdefine_line|#define MACEISA_SERIAL1_TDMAT_INT&t;BIT(21)
DECL|macro|MACEISA_SERIAL1_TDMAPR_INT
mdefine_line|#define MACEISA_SERIAL1_TDMAPR_INT&t;BIT(22)
DECL|macro|MACEISA_SERIAL1_TDMAME_INT
mdefine_line|#define MACEISA_SERIAL1_TDMAME_INT&t;BIT(23)
DECL|macro|MACEISA_SERIAL1_RDMAT_INT
mdefine_line|#define MACEISA_SERIAL1_RDMAT_INT&t;BIT(24)
DECL|macro|MACEISA_SERIAL1_RDMAOR_INT
mdefine_line|#define MACEISA_SERIAL1_RDMAOR_INT&t;BIT(25)
DECL|macro|MACEISA_SERIAL2_INT
mdefine_line|#define MACEISA_SERIAL2_INT&t;&t;BIT(26)
DECL|macro|MACEISA_SERIAL2_TDMAT_INT
mdefine_line|#define MACEISA_SERIAL2_TDMAT_INT&t;BIT(27)
DECL|macro|MACEISA_SERIAL2_TDMAPR_INT
mdefine_line|#define MACEISA_SERIAL2_TDMAPR_INT&t;BIT(28)
DECL|macro|MACEISA_SERIAL2_TDMAME_INT
mdefine_line|#define MACEISA_SERIAL2_TDMAME_INT&t;BIT(29)
DECL|macro|MACEISA_SERIAL2_RDMAT_INT
mdefine_line|#define MACEISA_SERIAL2_RDMAT_INT&t;BIT(30)
DECL|macro|MACEISA_SERIAL2_RDMAOR_INT
mdefine_line|#define MACEISA_SERIAL2_RDMAOR_INT&t;BIT(31)
DECL|member|_pad
r_volatile
r_int
r_int
id|_pad
(braket
l_int|0x2000
op_div
l_int|8
op_minus
l_int|4
)braket
suffix:semicolon
DECL|member|dp_ram
r_volatile
r_int
r_int
id|dp_ram
(braket
l_int|0x400
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Keyboard &amp; Mouse registers&n; * -&gt; drivers/input/serio/maceps2.c */
DECL|struct|mace_ps2port
r_struct
id|mace_ps2port
(brace
DECL|member|tx
r_volatile
r_int
r_int
id|tx
suffix:semicolon
DECL|member|rx
r_volatile
r_int
r_int
id|rx
suffix:semicolon
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mace_ps2
r_struct
id|mace_ps2
(brace
DECL|member|keyb
r_struct
id|mace_ps2port
id|keyb
suffix:semicolon
DECL|member|mouse
r_struct
id|mace_ps2port
id|mouse
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I2C registers&n; * -&gt; drivers/i2c/algos/i2c-algo-sgi.c */
DECL|struct|mace_i2c
r_struct
id|mace_i2c
(brace
DECL|member|config
r_volatile
r_int
r_int
id|config
suffix:semicolon
DECL|macro|MACEI2C_RESET
mdefine_line|#define MACEI2C_RESET           BIT(0)
DECL|macro|MACEI2C_FAST
mdefine_line|#define MACEI2C_FAST            BIT(1)
DECL|macro|MACEI2C_DATA_OVERRIDE
mdefine_line|#define MACEI2C_DATA_OVERRIDE   BIT(2)
DECL|macro|MACEI2C_CLOCK_OVERRIDE
mdefine_line|#define MACEI2C_CLOCK_OVERRIDE  BIT(3)
DECL|macro|MACEI2C_DATA_STATUS
mdefine_line|#define MACEI2C_DATA_STATUS     BIT(4)
DECL|macro|MACEI2C_CLOCK_STATUS
mdefine_line|#define MACEI2C_CLOCK_STATUS    BIT(5)
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
DECL|member|data
r_volatile
r_int
r_int
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Timer registers */
r_typedef
r_union
(brace
DECL|member|ust_msc
r_volatile
r_int
r_int
id|ust_msc
suffix:semicolon
DECL|struct|reg
r_struct
id|reg
(brace
DECL|member|ust
r_volatile
r_int
r_int
id|ust
suffix:semicolon
DECL|member|msc
r_volatile
r_int
r_int
id|msc
suffix:semicolon
DECL|member|reg
)brace
id|reg
suffix:semicolon
DECL|typedef|timer_reg
)brace
id|timer_reg
suffix:semicolon
DECL|struct|mace_timers
r_struct
id|mace_timers
(brace
DECL|member|ust
r_volatile
r_int
r_int
id|ust
suffix:semicolon
DECL|macro|MACE_UST_PERIOD_NS
mdefine_line|#define MACE_UST_PERIOD_NS&t;960
DECL|member|compare1
r_volatile
r_int
r_int
id|compare1
suffix:semicolon
DECL|member|compare2
r_volatile
r_int
r_int
id|compare2
suffix:semicolon
DECL|member|compare3
r_volatile
r_int
r_int
id|compare3
suffix:semicolon
DECL|member|audio_in
id|timer_reg
id|audio_in
suffix:semicolon
DECL|member|audio_out1
id|timer_reg
id|audio_out1
suffix:semicolon
DECL|member|audio_out2
id|timer_reg
id|audio_out2
suffix:semicolon
DECL|member|video_in1
id|timer_reg
id|video_in1
suffix:semicolon
DECL|member|video_in2
id|timer_reg
id|video_in2
suffix:semicolon
DECL|member|video_out
id|timer_reg
id|video_out
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mace_perif
r_struct
id|mace_perif
(brace
DECL|member|audio
r_struct
id|mace_audio
id|audio
suffix:semicolon
DECL|member|_pad0
r_char
id|_pad0
(braket
l_int|0x10000
op_minus
r_sizeof
(paren
r_struct
id|mace_audio
)paren
)braket
suffix:semicolon
DECL|member|ctrl
r_struct
id|mace_isactrl
id|ctrl
suffix:semicolon
DECL|member|_pad1
r_char
id|_pad1
(braket
l_int|0x10000
op_minus
r_sizeof
(paren
r_struct
id|mace_isactrl
)paren
)braket
suffix:semicolon
DECL|member|ps2
r_struct
id|mace_ps2
id|ps2
suffix:semicolon
DECL|member|_pad2
r_char
id|_pad2
(braket
l_int|0x10000
op_minus
r_sizeof
(paren
r_struct
id|mace_ps2
)paren
)braket
suffix:semicolon
DECL|member|i2c
r_struct
id|mace_i2c
id|i2c
suffix:semicolon
DECL|member|_pad3
r_char
id|_pad3
(braket
l_int|0x10000
op_minus
r_sizeof
(paren
r_struct
id|mace_i2c
)paren
)braket
suffix:semicolon
DECL|member|timers
r_struct
id|mace_timers
id|timers
suffix:semicolon
DECL|member|_pad4
r_char
id|_pad4
(braket
l_int|0x10000
op_minus
r_sizeof
(paren
r_struct
id|mace_timers
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * ISA peripherals&n; */
multiline_comment|/* Parallel port */
DECL|struct|mace_parallel
r_struct
id|mace_parallel
(brace
multiline_comment|/* later... */
)brace
suffix:semicolon
DECL|struct|mace_ecp1284
r_struct
id|mace_ecp1284
(brace
multiline_comment|/* later... */
)brace
suffix:semicolon
multiline_comment|/* Serial port */
DECL|struct|mace_serial
r_struct
id|mace_serial
(brace
DECL|member|xxx
r_volatile
r_int
r_int
id|xxx
suffix:semicolon
multiline_comment|/* later... */
)brace
suffix:semicolon
DECL|struct|mace_isa
r_struct
id|mace_isa
(brace
DECL|member|parallel
r_struct
id|mace_parallel
id|parallel
suffix:semicolon
DECL|member|_pad1
r_char
id|_pad1
(braket
l_int|0x8000
op_minus
r_sizeof
(paren
r_struct
id|mace_parallel
)paren
)braket
suffix:semicolon
DECL|member|ecp1284
r_struct
id|mace_ecp1284
id|ecp1284
suffix:semicolon
DECL|member|_pad2
r_char
id|_pad2
(braket
l_int|0x8000
op_minus
r_sizeof
(paren
r_struct
id|mace_ecp1284
)paren
)braket
suffix:semicolon
DECL|member|serial1
r_struct
id|mace_serial
id|serial1
suffix:semicolon
DECL|member|_pad3
r_char
id|_pad3
(braket
l_int|0x8000
op_minus
r_sizeof
(paren
r_struct
id|mace_serial
)paren
)braket
suffix:semicolon
DECL|member|serial2
r_struct
id|mace_serial
id|serial2
suffix:semicolon
DECL|member|_pad4
r_char
id|_pad4
(braket
l_int|0x8000
op_minus
r_sizeof
(paren
r_struct
id|mace_serial
)paren
)braket
suffix:semicolon
DECL|member|rtc
r_volatile
r_int
r_char
id|rtc
(braket
l_int|0x10000
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgi_mace
r_struct
id|sgi_mace
(brace
DECL|member|_reserved
r_char
id|_reserved
(braket
l_int|0x80000
)braket
suffix:semicolon
DECL|member|pci
r_struct
id|mace_pci
id|pci
suffix:semicolon
DECL|member|_pad0
r_char
id|_pad0
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_pci
)paren
)braket
suffix:semicolon
DECL|member|video_in1
r_struct
id|mace_video
id|video_in1
suffix:semicolon
DECL|member|_pad1
r_char
id|_pad1
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_video
)paren
)braket
suffix:semicolon
DECL|member|video_in2
r_struct
id|mace_video
id|video_in2
suffix:semicolon
DECL|member|_pad2
r_char
id|_pad2
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_video
)paren
)braket
suffix:semicolon
DECL|member|video_out
r_struct
id|mace_video
id|video_out
suffix:semicolon
DECL|member|_pad3
r_char
id|_pad3
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_video
)paren
)braket
suffix:semicolon
DECL|member|eth
r_struct
id|mace_ethernet
id|eth
suffix:semicolon
DECL|member|_pad4
r_char
id|_pad4
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_ethernet
)paren
)braket
suffix:semicolon
DECL|member|perif
r_struct
id|mace_perif
id|perif
suffix:semicolon
DECL|member|_pad5
r_char
id|_pad5
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_perif
)paren
)braket
suffix:semicolon
DECL|member|isa
r_struct
id|mace_isa
id|isa
suffix:semicolon
DECL|member|_pad6
r_char
id|_pad6
(braket
l_int|0x80000
op_minus
r_sizeof
(paren
r_struct
id|mace_isa
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sgi_mace
op_star
id|mace
suffix:semicolon
macro_line|#endif /* __ASM_MACE_H__ */
eof
