macro_line|#ifndef _MVME147HW_H_
DECL|macro|_MVME147HW_H_
mdefine_line|#define _MVME147HW_H_
r_typedef
r_struct
(brace
r_int
r_char
DECL|member|ctrl
id|ctrl
comma
DECL|member|bcd_sec
id|bcd_sec
comma
DECL|member|bcd_min
id|bcd_min
comma
DECL|member|bcd_hr
id|bcd_hr
comma
DECL|member|bcd_dow
id|bcd_dow
comma
DECL|member|bcd_dom
id|bcd_dom
comma
DECL|member|bcd_mth
id|bcd_mth
comma
DECL|member|bcd_year
id|bcd_year
suffix:semicolon
DECL|typedef|MK48T02
)brace
id|MK48T02
suffix:semicolon
DECL|macro|RTC_WRITE
mdefine_line|#define RTC_WRITE&t;0x80
DECL|macro|RTC_READ
mdefine_line|#define RTC_READ&t;0x40
DECL|macro|RTC_STOP
mdefine_line|#define RTC_STOP&t;0x20
DECL|macro|m147_rtc
mdefine_line|#define m147_rtc ((MK48T02 * volatile)0xfffe07f8)
DECL|struct|pcc_regs
r_struct
id|pcc_regs
(brace
DECL|member|dma_tadr
r_volatile
id|u_long
id|dma_tadr
suffix:semicolon
DECL|member|dma_dadr
r_volatile
id|u_long
id|dma_dadr
suffix:semicolon
DECL|member|dma_bcr
r_volatile
id|u_long
id|dma_bcr
suffix:semicolon
DECL|member|dma_hr
r_volatile
id|u_long
id|dma_hr
suffix:semicolon
DECL|member|t1_preload
r_volatile
id|u_short
id|t1_preload
suffix:semicolon
DECL|member|t1_count
r_volatile
id|u_short
id|t1_count
suffix:semicolon
DECL|member|t2_preload
r_volatile
id|u_short
id|t2_preload
suffix:semicolon
DECL|member|t2_count
r_volatile
id|u_short
id|t2_count
suffix:semicolon
DECL|member|t1_int_cntrl
r_volatile
id|u_char
id|t1_int_cntrl
suffix:semicolon
DECL|member|t1_cntrl
r_volatile
id|u_char
id|t1_cntrl
suffix:semicolon
DECL|member|t2_int_cntrl
r_volatile
id|u_char
id|t2_int_cntrl
suffix:semicolon
DECL|member|t2_cntrl
r_volatile
id|u_char
id|t2_cntrl
suffix:semicolon
DECL|member|ac_fail
r_volatile
id|u_char
id|ac_fail
suffix:semicolon
DECL|member|watchdog
r_volatile
id|u_char
id|watchdog
suffix:semicolon
DECL|member|lpt_intr
r_volatile
id|u_char
id|lpt_intr
suffix:semicolon
DECL|member|lpt_cntrl
r_volatile
id|u_char
id|lpt_cntrl
suffix:semicolon
DECL|member|dma_intr
r_volatile
id|u_char
id|dma_intr
suffix:semicolon
DECL|member|dma_cntrl
r_volatile
id|u_char
id|dma_cntrl
suffix:semicolon
DECL|member|bus_error
r_volatile
id|u_char
id|bus_error
suffix:semicolon
DECL|member|dma_status
r_volatile
id|u_char
id|dma_status
suffix:semicolon
DECL|member|abort
r_volatile
id|u_char
m_abort
suffix:semicolon
DECL|member|ta_fnctl
r_volatile
id|u_char
id|ta_fnctl
suffix:semicolon
DECL|member|serial_cntrl
r_volatile
id|u_char
id|serial_cntrl
suffix:semicolon
DECL|member|general_cntrl
r_volatile
id|u_char
id|general_cntrl
suffix:semicolon
DECL|member|lan_cntrl
r_volatile
id|u_char
id|lan_cntrl
suffix:semicolon
DECL|member|general_status
r_volatile
id|u_char
id|general_status
suffix:semicolon
DECL|member|scsi_interrupt
r_volatile
id|u_char
id|scsi_interrupt
suffix:semicolon
DECL|member|slave
r_volatile
id|u_char
id|slave
suffix:semicolon
DECL|member|soft1_cntrl
r_volatile
id|u_char
id|soft1_cntrl
suffix:semicolon
DECL|member|int_base
r_volatile
id|u_char
id|int_base
suffix:semicolon
DECL|member|soft2_cntrl
r_volatile
id|u_char
id|soft2_cntrl
suffix:semicolon
DECL|member|revision_level
r_volatile
id|u_char
id|revision_level
suffix:semicolon
DECL|member|lpt_data
r_volatile
id|u_char
id|lpt_data
suffix:semicolon
DECL|member|lpt_status
r_volatile
id|u_char
id|lpt_status
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|m147_pcc
mdefine_line|#define m147_pcc ((struct pcc_regs * volatile)0xfffe1000)
DECL|macro|PCC_INT_ENAB
mdefine_line|#define PCC_INT_ENAB&t;&t;0x08
DECL|macro|PCC_TIMER_INT_CLR
mdefine_line|#define PCC_TIMER_INT_CLR&t;0x80
DECL|macro|PCC_TIMER_PRELOAD
mdefine_line|#define PCC_TIMER_PRELOAD&t;63936l
DECL|macro|PCC_LEVEL_ABORT
mdefine_line|#define PCC_LEVEL_ABORT&t;&t;0x07
DECL|macro|PCC_LEVEL_SERIAL
mdefine_line|#define PCC_LEVEL_SERIAL&t;0x04
DECL|macro|PCC_LEVEL_ETH
mdefine_line|#define PCC_LEVEL_ETH&t;&t;0x04
DECL|macro|PCC_LEVEL_TIMER1
mdefine_line|#define PCC_LEVEL_TIMER1&t;0x04
DECL|macro|PCC_LEVEL_SCSI_PORT
mdefine_line|#define PCC_LEVEL_SCSI_PORT&t;0x04
DECL|macro|PCC_LEVEL_SCSI_DMA
mdefine_line|#define PCC_LEVEL_SCSI_DMA&t;0x04
DECL|macro|PCC_IRQ_AC_FAIL
mdefine_line|#define PCC_IRQ_AC_FAIL&t;&t;0x40
DECL|macro|PCC_IRQ_BERR
mdefine_line|#define PCC_IRQ_BERR&t;&t;0x41
DECL|macro|PCC_IRQ_ABORT
mdefine_line|#define PCC_IRQ_ABORT&t;&t;0x42
multiline_comment|/* #define PCC_IRQ_SERIAL&t;0x43 */
DECL|macro|PCC_IRQ_PRINTER
mdefine_line|#define PCC_IRQ_PRINTER&t;&t;0x47
DECL|macro|PCC_IRQ_TIMER1
mdefine_line|#define PCC_IRQ_TIMER1&t;&t;0x48
DECL|macro|PCC_IRQ_TIMER2
mdefine_line|#define PCC_IRQ_TIMER2&t;&t;0x49
DECL|macro|PCC_IRQ_SOFTWARE1
mdefine_line|#define PCC_IRQ_SOFTWARE1&t;0x4a
DECL|macro|PCC_IRQ_SOFTWARE2
mdefine_line|#define PCC_IRQ_SOFTWARE2&t;0x4b
DECL|macro|M147_SCC_A_ADDR
mdefine_line|#define M147_SCC_A_ADDR&t;&t;0xfffe3002
DECL|macro|M147_SCC_B_ADDR
mdefine_line|#define M147_SCC_B_ADDR&t;&t;0xfffe3000
DECL|macro|M147_SCC_PCLK
mdefine_line|#define M147_SCC_PCLK&t;&t;5000000
DECL|macro|MVME147_IRQ_SCSI_PORT
mdefine_line|#define MVME147_IRQ_SCSI_PORT&t;0x45
DECL|macro|MVME147_IRQ_SCSI_DMA
mdefine_line|#define MVME147_IRQ_SCSI_DMA&t;0x46
multiline_comment|/* SCC interrupts, for MVME147 */
DECL|macro|MVME147_IRQ_TYPE_PRIO
mdefine_line|#define MVME147_IRQ_TYPE_PRIO&t;0
DECL|macro|MVME147_IRQ_SCC_BASE
mdefine_line|#define MVME147_IRQ_SCC_BASE&t;&t;0x60
DECL|macro|MVME147_IRQ_SCCB_TX
mdefine_line|#define MVME147_IRQ_SCCB_TX&t;&t;0x60
DECL|macro|MVME147_IRQ_SCCB_STAT
mdefine_line|#define MVME147_IRQ_SCCB_STAT&t;&t;0x62
DECL|macro|MVME147_IRQ_SCCB_RX
mdefine_line|#define MVME147_IRQ_SCCB_RX&t;&t;0x64
DECL|macro|MVME147_IRQ_SCCB_SPCOND
mdefine_line|#define MVME147_IRQ_SCCB_SPCOND&t;&t;0x66
DECL|macro|MVME147_IRQ_SCCA_TX
mdefine_line|#define MVME147_IRQ_SCCA_TX&t;&t;0x68
DECL|macro|MVME147_IRQ_SCCA_STAT
mdefine_line|#define MVME147_IRQ_SCCA_STAT&t;&t;0x6a
DECL|macro|MVME147_IRQ_SCCA_RX
mdefine_line|#define MVME147_IRQ_SCCA_RX&t;&t;0x6c
DECL|macro|MVME147_IRQ_SCCA_SPCOND
mdefine_line|#define MVME147_IRQ_SCCA_SPCOND&t;&t;0x6e
DECL|macro|MVME147_LANCE_BASE
mdefine_line|#define MVME147_LANCE_BASE&t;0xfffe1800
DECL|macro|MVME147_LANCE_IRQ
mdefine_line|#define MVME147_LANCE_IRQ&t;0x44
DECL|macro|ETHERNET_ADDRESS
mdefine_line|#define ETHERNET_ADDRESS 0xfffe0778
macro_line|#endif
eof
