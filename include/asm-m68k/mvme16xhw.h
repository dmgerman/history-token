macro_line|#ifndef _M68K_MVME16xHW_H_
DECL|macro|_M68K_MVME16xHW_H_
mdefine_line|#define _M68K_MVME16xHW_H_
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* Board ID data structure - pointer to this retrieved from Bug by head.S */
multiline_comment|/* Note, bytes 12 and 13 are board no in BCD (0162,0166,0167,0177,etc) */
r_extern
r_int
id|mvme_bdid_ptr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|bdid
r_char
id|bdid
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rev
DECL|member|mth
DECL|member|day
DECL|member|yr
id|u_char
id|rev
comma
id|mth
comma
id|day
comma
id|yr
suffix:semicolon
DECL|member|size
DECL|member|reserved
id|u_short
id|size
comma
id|reserved
suffix:semicolon
DECL|member|brdno
id|u_short
id|brdno
suffix:semicolon
DECL|member|brdsuffix
r_char
id|brdsuffix
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|options
id|u_long
id|options
suffix:semicolon
DECL|member|clun
DECL|member|dlun
DECL|member|ctype
DECL|member|dnum
id|u_short
id|clun
comma
id|dlun
comma
id|ctype
comma
id|dnum
suffix:semicolon
DECL|member|option2
id|u_long
id|option2
suffix:semicolon
DECL|typedef|t_bdid
DECL|typedef|p_bdid
)brace
id|t_bdid
comma
op_star
id|p_bdid
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ack_icr
id|u_char
id|ack_icr
comma
DECL|member|flt_icr
id|flt_icr
comma
DECL|member|sel_icr
id|sel_icr
comma
DECL|member|pe_icr
id|pe_icr
comma
DECL|member|bsy_icr
id|bsy_icr
comma
DECL|member|spare1
id|spare1
comma
DECL|member|isr
id|isr
comma
DECL|member|cr
id|cr
comma
DECL|member|spare2
id|spare2
comma
DECL|member|spare3
id|spare3
comma
DECL|member|spare4
id|spare4
comma
DECL|member|data
id|data
suffix:semicolon
DECL|typedef|MVMElp
DECL|typedef|MVMElpPtr
)brace
id|MVMElp
comma
op_star
id|MVMElpPtr
suffix:semicolon
DECL|macro|MVME_LPR_BASE
mdefine_line|#define MVME_LPR_BASE&t;0xfff42030
DECL|macro|mvmelp
mdefine_line|#define mvmelp   ((*(volatile MVMElpPtr)(MVME_LPR_BASE)))
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
DECL|typedef|MK48T08_t
DECL|typedef|MK48T08ptr_t
)brace
id|MK48T08_t
comma
op_star
id|MK48T08ptr_t
suffix:semicolon
DECL|macro|RTC_WRITE
mdefine_line|#define RTC_WRITE&t;0x80
DECL|macro|RTC_READ
mdefine_line|#define RTC_READ&t;0x40
DECL|macro|RTC_STOP
mdefine_line|#define RTC_STOP&t;0x20
DECL|macro|MVME_RTC_BASE
mdefine_line|#define MVME_RTC_BASE&t;0xfffc1ff8
DECL|macro|MVME_I596_BASE
mdefine_line|#define MVME_I596_BASE&t;0xfff46000
DECL|macro|MVME_SCC_A_ADDR
mdefine_line|#define MVME_SCC_A_ADDR&t;0xfff45005
DECL|macro|MVME_SCC_B_ADDR
mdefine_line|#define MVME_SCC_B_ADDR&t;0xfff45001
DECL|macro|MVME_SCC_PCLK
mdefine_line|#define MVME_SCC_PCLK&t;10000000
DECL|macro|MVME162_IRQ_TYPE_PRIO
mdefine_line|#define MVME162_IRQ_TYPE_PRIO&t;0
DECL|macro|MVME167_IRQ_PRN
mdefine_line|#define MVME167_IRQ_PRN&t;&t;0x54
DECL|macro|MVME16x_IRQ_I596
mdefine_line|#define MVME16x_IRQ_I596&t;0x57
DECL|macro|MVME16x_IRQ_SCSI
mdefine_line|#define MVME16x_IRQ_SCSI&t;0x55
DECL|macro|MVME16x_IRQ_FLY
mdefine_line|#define MVME16x_IRQ_FLY&t;&t;0x7f
DECL|macro|MVME167_IRQ_SER_ERR
mdefine_line|#define MVME167_IRQ_SER_ERR&t;0x5c
DECL|macro|MVME167_IRQ_SER_MODEM
mdefine_line|#define MVME167_IRQ_SER_MODEM&t;0x5d
DECL|macro|MVME167_IRQ_SER_TX
mdefine_line|#define MVME167_IRQ_SER_TX&t;0x5e
DECL|macro|MVME167_IRQ_SER_RX
mdefine_line|#define MVME167_IRQ_SER_RX&t;0x5f
DECL|macro|MVME16x_IRQ_TIMER
mdefine_line|#define MVME16x_IRQ_TIMER&t;0x59
DECL|macro|MVME167_IRQ_ABORT
mdefine_line|#define MVME167_IRQ_ABORT&t;0x6e
DECL|macro|MVME162_IRQ_ABORT
mdefine_line|#define MVME162_IRQ_ABORT&t;0x5e
multiline_comment|/* SCC interrupts, for MVME162 */
DECL|macro|MVME162_IRQ_SCC_BASE
mdefine_line|#define MVME162_IRQ_SCC_BASE&t;&t;0x40
DECL|macro|MVME162_IRQ_SCCB_TX
mdefine_line|#define MVME162_IRQ_SCCB_TX&t;&t;0x40
DECL|macro|MVME162_IRQ_SCCB_STAT
mdefine_line|#define MVME162_IRQ_SCCB_STAT&t;&t;0x42
DECL|macro|MVME162_IRQ_SCCB_RX
mdefine_line|#define MVME162_IRQ_SCCB_RX&t;&t;0x44
DECL|macro|MVME162_IRQ_SCCB_SPCOND
mdefine_line|#define MVME162_IRQ_SCCB_SPCOND&t;&t;0x46
DECL|macro|MVME162_IRQ_SCCA_TX
mdefine_line|#define MVME162_IRQ_SCCA_TX&t;&t;0x48
DECL|macro|MVME162_IRQ_SCCA_STAT
mdefine_line|#define MVME162_IRQ_SCCA_STAT&t;&t;0x4a
DECL|macro|MVME162_IRQ_SCCA_RX
mdefine_line|#define MVME162_IRQ_SCCA_RX&t;&t;0x4c
DECL|macro|MVME162_IRQ_SCCA_SPCOND
mdefine_line|#define MVME162_IRQ_SCCA_SPCOND&t;&t;0x4e
multiline_comment|/* MVME162 version register */
DECL|macro|MVME162_VERSION_REG
mdefine_line|#define MVME162_VERSION_REG&t;0xfff4202e
r_extern
r_int
r_int
id|mvme16x_config
suffix:semicolon
multiline_comment|/* Lower 8 bits must match the revision register in the MC2 chip */
DECL|macro|MVME16x_CONFIG_SPEED_32
mdefine_line|#define MVME16x_CONFIG_SPEED_32&t;&t;0x0001
DECL|macro|MVME16x_CONFIG_NO_VMECHIP2
mdefine_line|#define MVME16x_CONFIG_NO_VMECHIP2&t;0x0002
DECL|macro|MVME16x_CONFIG_NO_SCSICHIP
mdefine_line|#define MVME16x_CONFIG_NO_SCSICHIP&t;0x0004
DECL|macro|MVME16x_CONFIG_NO_ETHERNET
mdefine_line|#define MVME16x_CONFIG_NO_ETHERNET&t;0x0008
DECL|macro|MVME16x_CONFIG_GOT_FPU
mdefine_line|#define MVME16x_CONFIG_GOT_FPU&t;&t;0x0010
DECL|macro|MVME16x_CONFIG_GOT_LP
mdefine_line|#define MVME16x_CONFIG_GOT_LP&t;&t;0x0100
DECL|macro|MVME16x_CONFIG_GOT_CD2401
mdefine_line|#define MVME16x_CONFIG_GOT_CD2401&t;0x0200
DECL|macro|MVME16x_CONFIG_GOT_SCCA
mdefine_line|#define MVME16x_CONFIG_GOT_SCCA&t;&t;0x0400
DECL|macro|MVME16x_CONFIG_GOT_SCCB
mdefine_line|#define MVME16x_CONFIG_GOT_SCCB&t;&t;0x0800
macro_line|#endif
eof
