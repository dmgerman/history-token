multiline_comment|/* Serialport functions for debugging&n; *&n; * Copyright (c) 2000 Axis Communications AB&n; *&n; * Authors:  Bjorn Wesen&n; *&n; * Exports:&n; *    console_print_etrax(char *buf)&n; *    int getDebugChar()&n; *    putDebugChar(int)&n; *    enableDebugIRQ()&n; *    init_etrax_debug()&n; *&n; * $Log: debugport.c,v $&n; * Revision 1.14  2004/05/17 13:11:29  starvik&n; * Disable DMA until real serial driver is up&n; *&n; * Revision 1.13  2004/05/14 07:58:01  starvik&n; * Merge of changes from 2.4&n; *&n; * Revision 1.12  2003/09/11 07:29:49  starvik&n; * Merge of Linux 2.6.0-test5&n; *&n; * Revision 1.11  2003/07/07 09:53:36  starvik&n; * Revert all the 2.5.74 merge changes to make the console work again&n; *&n; * Revision 1.9  2003/02/17 17:07:23  starvik&n; * Solved the problem with corrupted debug output (from Linux 2.4)&n; *   * Wait until DMA, FIFO and pipe is empty before and after transmissions&n; *   * Buffer data until a FIFO flush can be triggered.&n; *&n; * Revision 1.8  2003/01/22 06:48:36  starvik&n; * Fixed warnings issued by GCC 3.2.1&n; *&n; * Revision 1.7  2002/12/12 08:26:32  starvik&n; * Don&squot;t use C-comments inside CVS comments&n; *&n; * Revision 1.6  2002/12/11 15:42:02  starvik&n; * Extracted v10 (ETRAX 100LX) specific stuff from arch/cris/kernel/&n; *&n; * Revision 1.5  2002/11/20 06:58:03  starvik&n; * Compiles with kgdb&n; *&n; * Revision 1.4  2002/11/19 14:35:24  starvik&n; * Changes from linux 2.4&n; * Changed struct initializer syntax to the currently prefered notation&n; *&n; * Revision 1.3  2002/11/06 09:47:03  starvik&n; * Modified for new interrupt macros&n; *&n; * Revision 1.2  2002/01/21 15:21:50  bjornw&n; * Update for kdev_t changes&n; *&n; * Revision 1.6  2001/04/17 13:58:39  orjanf&n; * * Renamed CONFIG_KGDB to CONFIG_ETRAX_KGDB.&n; *&n; * Revision 1.5  2001/03/26 14:22:05  bjornw&n; * Namechange of some config options&n; *&n; * Revision 1.4  2000/10/06 12:37:26  bjornw&n; * Use physical addresses when talking to DMA&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
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
DECL|variable|serial_driver
r_static
r_struct
id|tty_driver
op_star
id|serial_driver
suffix:semicolon
DECL|typedef|debugport_write_function
r_typedef
r_int
(paren
op_star
id|debugport_write_function
)paren
(paren
r_int
id|i
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
suffix:semicolon
DECL|variable|debug_write_function
id|debugport_write_function
id|debug_write_function
op_assign
l_int|NULL
suffix:semicolon
r_static
r_void
DECL|function|console_write_direct
id|console_write_direct
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
r_int
id|i
suffix:semicolon
multiline_comment|/* Send data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Wait until transmitter is ready and send.*/
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
op_star
id|DEBUG_WRITE
op_assign
id|buf
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
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
r_return
suffix:semicolon
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug_write_function
)paren
r_if
c_cond
(paren
id|debug_write_function
c_func
(paren
id|co-&gt;index
comma
id|buf
comma
id|len
)paren
)paren
r_return
suffix:semicolon
id|console_write_direct
c_func
(paren
id|co
comma
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
r_struct
id|tty_driver
op_star
DECL|function|console_device
id|console_device
c_func
(paren
r_struct
id|console
op_star
id|c
comma
r_int
op_star
id|index
)paren
(brace
op_star
id|index
op_assign
id|c-&gt;index
suffix:semicolon
r_return
id|serial_driver
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
macro_line|#if CONFIG_ETRAX_DEBUG_PORT_NULL
r_return
suffix:semicolon
macro_line|#endif
macro_line|#if DEBUG_PORT_IDX == 0
id|genconfig_shadow
op_and_assign
op_complement
id|IO_MASK
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma6
)paren
suffix:semicolon
id|genconfig_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma6
comma
id|unused
)paren
suffix:semicolon
macro_line|#elif DEBUG_PORT_IDX == 1
id|genconfig_shadow
op_and_assign
op_complement
id|IO_MASK
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma8
)paren
suffix:semicolon
id|genconfig_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma8
comma
id|usb
)paren
suffix:semicolon
macro_line|#elif DEBUG_PORT_IDX == 2
id|genconfig_shadow
op_and_assign
op_complement
id|IO_MASK
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma2
)paren
suffix:semicolon
id|genconfig_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma2
comma
id|par0
)paren
suffix:semicolon
macro_line|#elif DEBUG_PORT_IDX == 3
id|genconfig_shadow
op_and_assign
op_complement
id|IO_MASK
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma4
)paren
suffix:semicolon
id|genconfig_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_GEN_CONFIG
comma
id|dma4
comma
id|par1
)paren
suffix:semicolon
macro_line|#endif
op_star
id|R_GEN_CONFIG
op_assign
id|genconfig_shadow
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|sercons
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|init_console
id|init_console
c_func
(paren
r_void
)paren
(brace
id|serial_driver
op_assign
id|alloc_tty_driver
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial_driver
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
