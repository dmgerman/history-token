multiline_comment|/* Serialport functions for debugging&n; *&n; * Copyright (c) 2000 Axis Communications AB&n; *&n; * Authors:  Bjorn Wesen&n; *&n; * Exports:&n; *    console_print_etrax(char *buf)&n; *    int getDebugChar()&n; *    putDebugChar(int)&n; *    enableDebugIRQ()&n; *    init_etrax_debug()&n; *&n; * $Log: debugport.c,v $&n; * Revision 1.11  2003/07/07 09:53:36  starvik&n; * Revert all the 2.5.74 merge changes to make the console work again&n; *&n; * Revision 1.9  2003/02/17 17:07:23  starvik&n; * Solved the problem with corrupted debug output (from Linux 2.4)&n; *   * Wait until DMA, FIFO and pipe is empty before and after transmissions&n; *   * Buffer data until a FIFO flush can be triggered.&n; *&n; * Revision 1.8  2003/01/22 06:48:36  starvik&n; * Fixed warnings issued by GCC 3.2.1&n; *&n; * Revision 1.7  2002/12/12 08:26:32  starvik&n; * Don&squot;t use C-comments inside CVS comments&n; *&n; * Revision 1.6  2002/12/11 15:42:02  starvik&n; * Extracted v10 (ETRAX 100LX) specific stuff from arch/cris/kernel/&n; *&n; * Revision 1.5  2002/11/20 06:58:03  starvik&n; * Compiles with kgdb&n; *&n; * Revision 1.4  2002/11/19 14:35:24  starvik&n; * Changes from linux 2.4&n; * Changed struct initializer syntax to the currently prefered notation&n; *&n; * Revision 1.3  2002/11/06 09:47:03  starvik&n; * Modified for new interrupt macros&n; *&n; * Revision 1.2  2002/01/21 15:21:50  bjornw&n; * Update for kdev_t changes&n; *&n; * Revision 1.6  2001/04/17 13:58:39  orjanf&n; * * Renamed CONFIG_KGDB to CONFIG_ETRAX_KGDB.&n; *&n; * Revision 1.5  2001/03/26 14:22:05  bjornw&n; * Namechange of some config options&n; *&n; * Revision 1.4  2000/10/06 12:37:26  bjornw&n; * Use physical addresses when talking to DMA&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/arch/svinto.h&gt;
macro_line|#include &lt;asm/io.h&gt;             /* Get SIMCOUT. */
multiline_comment|/* Which serial-port is our debug port ? */
macro_line|#if defined(CONFIG_ETRAX_DEBUG_PORT0) || defined(CONFIG_ETRAX_DEBUG_PORT_NULL)
DECL|macro|DEBUG_PORT_IDX
mdefine_line|#define DEBUG_PORT_IDX 0
DECL|macro|DEBUG_OCMD
mdefine_line|#define DEBUG_OCMD R_DMA_CH6_CMD
DECL|macro|DEBUG_FIRST
mdefine_line|#define DEBUG_FIRST R_DMA_CH6_FIRST
DECL|macro|DEBUG_OCLRINT
mdefine_line|#define DEBUG_OCLRINT R_DMA_CH6_CLR_INTR
DECL|macro|DEBUG_STATUS
mdefine_line|#define DEBUG_STATUS R_DMA_CH6_STATUS
DECL|macro|DEBUG_READ
mdefine_line|#define DEBUG_READ R_SERIAL0_READ
DECL|macro|DEBUG_WRITE
mdefine_line|#define DEBUG_WRITE R_SERIAL0_TR_DATA
DECL|macro|DEBUG_TR_CTRL
mdefine_line|#define DEBUG_TR_CTRL R_SERIAL0_TR_CTRL
DECL|macro|DEBUG_REC_CTRL
mdefine_line|#define DEBUG_REC_CTRL R_SERIAL0_REC_CTRL
DECL|macro|DEBUG_IRQ
mdefine_line|#define DEBUG_IRQ IO_STATE(R_IRQ_MASK1_SET, ser0_data, set)
DECL|macro|DEBUG_DMA_IRQ_CLR
mdefine_line|#define DEBUG_DMA_IRQ_CLR IO_STATE(R_IRQ_MASK2_CLR, dma6_descr, clr)
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_DEBUG_PORT1
DECL|macro|DEBUG_PORT_IDX
mdefine_line|#define DEBUG_PORT_IDX 1
DECL|macro|DEBUG_OCMD
mdefine_line|#define DEBUG_OCMD R_DMA_CH8_CMD
DECL|macro|DEBUG_FIRST
mdefine_line|#define DEBUG_FIRST R_DMA_CH8_FIRST
DECL|macro|DEBUG_OCLRINT
mdefine_line|#define DEBUG_OCLRINT R_DMA_CH8_CLR_INTR
DECL|macro|DEBUG_STATUS
mdefine_line|#define DEBUG_STATUS R_DMA_CH8_STATUS
DECL|macro|DEBUG_READ
mdefine_line|#define DEBUG_READ R_SERIAL1_READ
DECL|macro|DEBUG_WRITE
mdefine_line|#define DEBUG_WRITE R_SERIAL1_TR_DATA
DECL|macro|DEBUG_TR_CTRL
mdefine_line|#define DEBUG_TR_CTRL R_SERIAL1_TR_CTRL
DECL|macro|DEBUG_REC_CTRL
mdefine_line|#define DEBUG_REC_CTRL R_SERIAL1_REC_CTRL
DECL|macro|DEBUG_IRQ
mdefine_line|#define DEBUG_IRQ IO_STATE(R_IRQ_MASK1_SET, ser1_data, set)
DECL|macro|DEBUG_DMA_IRQ_CLR
mdefine_line|#define DEBUG_DMA_IRQ_CLR IO_STATE(R_IRQ_MASK2_CLR, dma8_descr, clr)
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_DEBUG_PORT2
DECL|macro|DEBUG_PORT_IDX
mdefine_line|#define DEBUG_PORT_IDX 2
DECL|macro|DEBUG_OCMD
mdefine_line|#define DEBUG_OCMD R_DMA_CH2_CMD
DECL|macro|DEBUG_FIRST
mdefine_line|#define DEBUG_FIRST R_DMA_CH2_FIRST
DECL|macro|DEBUG_OCLRINT
mdefine_line|#define DEBUG_OCLRINT R_DMA_CH2_CLR_INTR
DECL|macro|DEBUG_STATUS
mdefine_line|#define DEBUG_STATUS R_DMA_CH2_STATUS
DECL|macro|DEBUG_READ
mdefine_line|#define DEBUG_READ R_SERIAL2_READ
DECL|macro|DEBUG_WRITE
mdefine_line|#define DEBUG_WRITE R_SERIAL2_TR_DATA
DECL|macro|DEBUG_TR_CTRL
mdefine_line|#define DEBUG_TR_CTRL R_SERIAL2_TR_CTRL
DECL|macro|DEBUG_REC_CTRL
mdefine_line|#define DEBUG_REC_CTRL R_SERIAL2_REC_CTRL
DECL|macro|DEBUG_IRQ
mdefine_line|#define DEBUG_IRQ IO_STATE(R_IRQ_MASK1_SET, ser2_data, set)
DECL|macro|DEBUG_DMA_IRQ_CLR
mdefine_line|#define DEBUG_DMA_IRQ_CLR IO_STATE(R_IRQ_MASK2_CLR, dma2_descr, clr)
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_DEBUG_PORT3
DECL|macro|DEBUG_PORT_IDX
mdefine_line|#define DEBUG_PORT_IDX 3
DECL|macro|DEBUG_OCMD
mdefine_line|#define DEBUG_OCMD R_DMA_CH4_CMD
DECL|macro|DEBUG_FIRST
mdefine_line|#define DEBUG_FIRST R_DMA_CH4_FIRST
DECL|macro|DEBUG_OCLRINT
mdefine_line|#define DEBUG_OCLRINT R_DMA_CH4_CLR_INTR
DECL|macro|DEBUG_STATUS
mdefine_line|#define DEBUG_STATUS R_DMA_CH4_STATUS
DECL|macro|DEBUG_READ
mdefine_line|#define DEBUG_READ R_SERIAL3_READ
DECL|macro|DEBUG_WRITE
mdefine_line|#define DEBUG_WRITE R_SERIAL3_TR_DATA
DECL|macro|DEBUG_TR_CTRL
mdefine_line|#define DEBUG_TR_CTRL R_SERIAL3_TR_CTRL
DECL|macro|DEBUG_REC_CTRL
mdefine_line|#define DEBUG_REC_CTRL R_SERIAL3_REC_CTRL
DECL|macro|DEBUG_IRQ
mdefine_line|#define DEBUG_IRQ IO_STATE(R_IRQ_MASK1_SET, ser3_data, set)
DECL|macro|DEBUG_DMA_IRQ_CLR
mdefine_line|#define DEBUG_DMA_IRQ_CLR IO_STATE(R_IRQ_MASK2_CLR, dma4_descr, clr)
macro_line|#endif
DECL|macro|MIN_SIZE
mdefine_line|#define MIN_SIZE 32 /* Size that triggers the FIFO to flush characters to interface */
multiline_comment|/* Write a string of count length to the console (debug port) using DMA, polled&n; * for completion. Interrupts are disabled during the whole process. Some&n; * caution needs to be taken to not interfere with ttyS business on this port.&n; */
r_static
r_void
DECL|function|console_write
id|console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_static
r_struct
id|etrax_dma_descr
id|descr
suffix:semicolon
r_static
r_struct
id|etrax_dma_descr
id|descr2
suffix:semicolon
r_static
r_char
id|tmp_buf
(braket
id|MIN_SIZE
)braket
suffix:semicolon
r_static
r_int
id|tmp_size
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_DEBUG_PORT_NULL
multiline_comment|/* no debug printout at all */
r_return
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SVINTO_SIM
multiline_comment|/* no use to simulate the serial debug output */
id|SIMCOUT
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_KGDB
multiline_comment|/* kgdb needs to output debug info using the gdb protocol */
id|putDebugString
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif
multiline_comment|/* To make this work together with the real serial port driver&n;&t; * we have to make sure that everything is flushed when we leave&n;&t; * here. The following steps are made to assure this:&n;&t; * 1. Wait until DMA stops, FIFO is empty and serial port pipeline empty.&n;&t; * 2. Write at least half the FIFO to trigger flush to serial port.&n;&t; * 3. Wait until DMA stops, FIFO is empty and serial port pipeline empty.&n;         */
multiline_comment|/* Do we have enough characters to make the DMA/FIFO happy? */
r_if
c_cond
(paren
id|tmp_size
op_plus
id|len
OL
id|MIN_SIZE
)paren
(brace
r_int
id|size
op_assign
id|min
c_func
(paren
(paren
r_int
)paren
(paren
id|MIN_SIZE
op_minus
id|tmp_size
)paren
comma
(paren
r_int
)paren
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tmp_buf
(braket
id|tmp_size
)braket
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|tmp_size
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
multiline_comment|/* Pad with space if complete line */
r_if
c_cond
(paren
id|tmp_buf
(braket
id|tmp_size
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|memset
c_func
(paren
op_amp
id|tmp_buf
(braket
id|tmp_size
op_minus
l_int|1
)braket
comma
l_char|&squot; &squot;
comma
id|MIN_SIZE
op_minus
id|tmp_size
)paren
suffix:semicolon
id|tmp_buf
(braket
id|MIN_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|tmp_size
op_assign
id|MIN_SIZE
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Wait for more characters */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* make sure the transmitter is enabled. &n;&t; * NOTE: this overrides any setting done in ttySx, to 8N1, no auto-CTS.&n;&t; * in the future, move the tr/rec_ctrl shadows from etrax100ser.c to&n;&t; * shadows.c and use it here as well...&n;&t; */
op_star
id|DEBUG_TR_CTRL
op_assign
l_int|0x40
suffix:semicolon
r_while
c_loop
(paren
op_star
id|DEBUG_OCMD
op_amp
l_int|7
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Until DMA is not running */
r_while
c_loop
(paren
op_star
id|DEBUG_STATUS
op_amp
l_int|0x7f
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* wait until output FIFO is empty as well */
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Wait for last two characters to leave the serial transmitter */
r_if
c_cond
(paren
id|tmp_size
)paren
(brace
id|descr.ctrl
op_assign
id|len
ques
c_cond
l_int|0
suffix:colon
id|d_eop
op_or
id|d_wait
op_or
id|d_eol
suffix:semicolon
id|descr.sw_len
op_assign
id|tmp_size
suffix:semicolon
id|descr.buf
op_assign
id|virt_to_phys
c_func
(paren
id|tmp_buf
)paren
suffix:semicolon
id|descr.next
op_assign
id|virt_to_phys
c_func
(paren
op_amp
id|descr2
)paren
suffix:semicolon
id|descr2.ctrl
op_assign
id|d_eop
op_or
id|d_wait
op_or
id|d_eol
suffix:semicolon
id|descr2.sw_len
op_assign
id|len
suffix:semicolon
id|descr2.buf
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_char
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
id|descr.ctrl
op_assign
id|d_eop
op_or
id|d_wait
op_or
id|d_eol
suffix:semicolon
id|descr.sw_len
op_assign
id|len
suffix:semicolon
id|descr.buf
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_char
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
op_star
id|DEBUG_FIRST
op_assign
id|virt_to_phys
c_func
(paren
op_amp
id|descr
)paren
suffix:semicolon
multiline_comment|/* write to R_DMAx_FIRST */
op_star
id|DEBUG_OCMD
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* dma command start -&gt; R_DMAx_CMD */
multiline_comment|/* wait until the output dma channel is ready again */
r_while
c_loop
(paren
op_star
id|DEBUG_OCMD
op_amp
l_int|7
)paren
(brace
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|DEBUG_STATUS
op_amp
l_int|0x7f
)paren
(brace
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|tmp_size
op_assign
l_int|0
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* legacy function */
r_void
DECL|function|console_print_etrax
id|console_print_etrax
c_func
(paren
r_const
r_char
op_star
id|buf
)paren
(brace
id|console_write
c_func
(paren
l_int|NULL
comma
id|buf
comma
id|strlen
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Use polling to get a single character FROM the debug port */
r_int
DECL|function|getDebugChar
id|getDebugChar
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|readval
suffix:semicolon
r_do
(brace
id|readval
op_assign
op_star
id|DEBUG_READ
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|readval
op_amp
id|IO_MASK
c_func
(paren
id|R_SERIAL0_READ
comma
id|data_avail
)paren
)paren
)paren
(brace
suffix:semicolon
)brace
r_return
(paren
id|readval
op_amp
id|IO_MASK
c_func
(paren
id|R_SERIAL0_READ
comma
id|data_in
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Use polling to put a single character to the debug port */
r_void
DECL|function|putDebugChar
id|putDebugChar
c_func
(paren
r_int
id|val
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
op_star
id|DEBUG_READ
op_amp
id|IO_MASK
c_func
(paren
id|R_SERIAL0_READ
comma
id|tr_ready
)paren
)paren
)paren
(brace
suffix:semicolon
)brace
suffix:semicolon
op_star
id|DEBUG_WRITE
op_assign
id|val
suffix:semicolon
)brace
multiline_comment|/* Enable irq for receiving chars on the debug port, used by kgdb */
r_void
DECL|function|enableDebugIRQ
id|enableDebugIRQ
c_func
(paren
r_void
)paren
(brace
op_star
id|R_IRQ_MASK1_SET
op_assign
id|DEBUG_IRQ
suffix:semicolon
multiline_comment|/* use R_VECT_MASK directly, since we really bypass Linux normal&n;&t; * IRQ handling in kgdb anyway, we don&squot;t need to use enable_irq&n;&t; */
op_star
id|R_VECT_MASK_SET
op_assign
id|IO_STATE
c_func
(paren
id|R_VECT_MASK_SET
comma
id|serial
comma
id|set
)paren
suffix:semicolon
op_star
id|DEBUG_REC_CTRL
op_assign
id|IO_STATE
c_func
(paren
id|R_SERIAL0_REC_CTRL
comma
id|rec_enable
comma
id|enable
)paren
suffix:semicolon
)brace
r_static
id|kdev_t
DECL|function|console_device
id|console_device
c_func
(paren
r_struct
id|console
op_star
id|c
)paren
(brace
r_return
id|mk_kdev
c_func
(paren
id|TTY_MAJOR
comma
l_int|64
op_plus
id|c-&gt;index
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|console_setup
id|console_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sercons
r_static
r_struct
id|console
id|sercons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyS&quot;
comma
dot
id|write
op_assign
id|console_write
comma
dot
id|read
op_assign
l_int|NULL
comma
dot
id|device
op_assign
id|console_device
comma
dot
id|unblank
op_assign
l_int|NULL
comma
dot
id|setup
op_assign
id|console_setup
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
id|DEBUG_PORT_IDX
comma
dot
id|cflag
op_assign
l_int|0
comma
dot
id|next
op_assign
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; *      Register console (for printk&squot;s etc)&n; */
r_void
id|__init
DECL|function|init_etrax_debug
id|init_etrax_debug
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|sercons
)paren
suffix:semicolon
)brace
eof
