multiline_comment|/*&n; * pi1.h: Definitions for SGI PI1 parallel port&n; */
macro_line|#ifndef _SGI_PI1_H
DECL|macro|_SGI_PI1_H
mdefine_line|#define _SGI_PI1_H
DECL|struct|pi1_regs
r_struct
id|pi1_regs
(brace
DECL|member|_data
id|u8
id|_data
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_volatile
id|u8
id|data
suffix:semicolon
DECL|member|_ctrl
id|u8
id|_ctrl
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ctrl
r_volatile
id|u8
id|ctrl
suffix:semicolon
DECL|macro|PI1_CTRL_STROBE_N
mdefine_line|#define PI1_CTRL_STROBE_N&t;0x01
DECL|macro|PI1_CTRL_AFD_N
mdefine_line|#define PI1_CTRL_AFD_N&t;&t;0x02
DECL|macro|PI1_CTRL_INIT_N
mdefine_line|#define PI1_CTRL_INIT_N&t;&t;0x04
DECL|macro|PI1_CTRL_SLIN_N
mdefine_line|#define PI1_CTRL_SLIN_N&t;&t;0x08
DECL|macro|PI1_CTRL_IRQ_ENA
mdefine_line|#define PI1_CTRL_IRQ_ENA&t;0x10
DECL|macro|PI1_CTRL_DIR
mdefine_line|#define PI1_CTRL_DIR&t;&t;0x20
DECL|macro|PI1_CTRL_SEL
mdefine_line|#define PI1_CTRL_SEL&t;&t;0x40
DECL|member|_status
id|u8
id|_status
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|status
r_volatile
id|u8
id|status
suffix:semicolon
DECL|macro|PI1_STAT_DEVID
mdefine_line|#define PI1_STAT_DEVID&t;&t;0x03&t;/* bits 0-1 */
DECL|macro|PI1_STAT_NOINK
mdefine_line|#define PI1_STAT_NOINK&t;&t;0x04&t;/* SGI MODE only */
DECL|macro|PI1_STAT_ERROR
mdefine_line|#define PI1_STAT_ERROR&t;&t;0x08
DECL|macro|PI1_STAT_ONLINE
mdefine_line|#define PI1_STAT_ONLINE&t;&t;0x10
DECL|macro|PI1_STAT_PE
mdefine_line|#define PI1_STAT_PE&t;&t;0x20
DECL|macro|PI1_STAT_ACK
mdefine_line|#define PI1_STAT_ACK&t;&t;0x40
DECL|macro|PI1_STAT_BUSY
mdefine_line|#define PI1_STAT_BUSY&t;&t;0x80
DECL|member|_dmactrl
id|u8
id|_dmactrl
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dmactrl
r_volatile
id|u8
id|dmactrl
suffix:semicolon
DECL|macro|PI1_DMACTRL_FIFO_EMPTY
mdefine_line|#define PI1_DMACTRL_FIFO_EMPTY&t;0x01    /* fifo empty R/O */
DECL|macro|PI1_DMACTRL_ABORT
mdefine_line|#define PI1_DMACTRL_ABORT&t;0x02    /* reset DMA and internal fifo W/O */
DECL|macro|PI1_DMACTRL_STDMODE
mdefine_line|#define PI1_DMACTRL_STDMODE&t;0x00    /* bits 2-3 */
DECL|macro|PI1_DMACTRL_SGIMODE
mdefine_line|#define PI1_DMACTRL_SGIMODE&t;0x04    /* bits 2-3 */
DECL|macro|PI1_DMACTRL_RICOHMODE
mdefine_line|#define PI1_DMACTRL_RICOHMODE&t;0x08    /* bits 2-3 */
DECL|macro|PI1_DMACTRL_HPMODE
mdefine_line|#define PI1_DMACTRL_HPMODE&t;0x0c    /* bits 2-3 */
DECL|macro|PI1_DMACTRL_BLKMODE
mdefine_line|#define PI1_DMACTRL_BLKMODE&t;0x10    /* block mode */
DECL|macro|PI1_DMACTRL_FIFO_CLEAR
mdefine_line|#define PI1_DMACTRL_FIFO_CLEAR&t;0x20    /* clear fifo W/O */
DECL|macro|PI1_DMACTRL_READ
mdefine_line|#define PI1_DMACTRL_READ&t;0x40    /* read */
DECL|macro|PI1_DMACTRL_RUN
mdefine_line|#define PI1_DMACTRL_RUN&t;&t;0x80    /* pedal to the metal */
DECL|member|_intstat
id|u8
id|_intstat
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|intstat
r_volatile
id|u8
id|intstat
suffix:semicolon
DECL|macro|PI1_INTSTAT_ACK
mdefine_line|#define PI1_INTSTAT_ACK&t;&t;0x04
DECL|macro|PI1_INTSTAT_FEMPTY
mdefine_line|#define PI1_INTSTAT_FEMPTY&t;0x08
DECL|macro|PI1_INTSTAT_NOINK
mdefine_line|#define PI1_INTSTAT_NOINK&t;0x10
DECL|macro|PI1_INTSTAT_ONLINE
mdefine_line|#define PI1_INTSTAT_ONLINE&t;0x20
DECL|macro|PI1_INTSTAT_ERR
mdefine_line|#define PI1_INTSTAT_ERR&t;&t;0x40
DECL|macro|PI1_INTSTAT_PE
mdefine_line|#define PI1_INTSTAT_PE&t;&t;0x80
DECL|member|_intmask
id|u8
id|_intmask
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|intmask
r_volatile
id|u8
id|intmask
suffix:semicolon
multiline_comment|/* enabled low, reset high*/
DECL|macro|PI1_INTMASK_ACK
mdefine_line|#define PI1_INTMASK_ACK&t;&t;0x04
DECL|macro|PI1_INTMASK_FIFO_EMPTY
mdefine_line|#define PI1_INTMASK_FIFO_EMPTY&t;0x08
DECL|macro|PI1_INTMASK_NOINK
mdefine_line|#define PI1_INTMASK_NOINK&t;0x10
DECL|macro|PI1_INTMASK_ONLINE
mdefine_line|#define PI1_INTMASK_ONLINE&t;0x20
DECL|macro|PI1_INTMASK_ERR
mdefine_line|#define PI1_INTMASK_ERR&t;&t;0x40
DECL|macro|PI1_INTMASK_PE
mdefine_line|#define PI1_INTMASK_PE&t;&t;0x80
DECL|member|_timer1
id|u8
id|_timer1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer1
r_volatile
id|u8
id|timer1
suffix:semicolon
DECL|macro|PI1_TIME1
mdefine_line|#define PI1_TIME1&t;&t;0x27
DECL|member|_timer2
id|u8
id|_timer2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer2
r_volatile
id|u8
id|timer2
suffix:semicolon
DECL|macro|PI1_TIME2
mdefine_line|#define PI1_TIME2&t;&t;0x13
DECL|member|_timer3
id|u8
id|_timer3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer3
r_volatile
id|u8
id|timer3
suffix:semicolon
DECL|macro|PI1_TIME3
mdefine_line|#define PI1_TIME3&t;&t;0x10
DECL|member|_timer4
id|u8
id|_timer4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer4
r_volatile
id|u8
id|timer4
suffix:semicolon
DECL|macro|PI1_TIME4
mdefine_line|#define PI1_TIME4&t;&t;0x00
)brace
suffix:semicolon
macro_line|#endif
eof
