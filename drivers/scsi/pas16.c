DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
DECL|macro|PSEUDO_DMA
mdefine_line|#define PSEUDO_DMA
DECL|macro|FOO
mdefine_line|#define FOO
DECL|macro|UNSAFE
mdefine_line|#define UNSAFE  /* Not unsafe for PAS16 -- use it */
multiline_comment|/*&n; * This driver adapted from Drew Eckhardt&squot;s Trantor T128 driver&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 666-5836&n; *&n; *  ( Based on T128 - DISTRIBUTION RELEASE 3. ) &n; *&n; * Modified to work with the Pro Audio Spectrum/Studio 16&n; * by John Weidman.&n; *&n; *&n; * For more information, please consult &n; *&n; * Media Vision&n; * (510) 770-8600&n; * (800) 348-7116&n; * &n; * and &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * Options : &n; * AUTOSENSE - if defined, REQUEST SENSE will be performed automatically&n; *      for commands that return with a CHECK CONDITION status. &n; *&n; * LIMIT_TRANSFERSIZE - if defined, limit the pseudo-dma transfers to 512&n; *      bytes at a time.  Since interrupts are disabled by default during&n; *      these transfers, we might need this to give reasonable interrupt&n; *      service time if the transfer size gets too large.&n; *&n; * PSEUDO_DMA - enables PSEUDO-DMA hardware, should give a 3-4X performance&n; * increase compared to polled I/O.&n; *&n; * PARITY - enable parity checking.  Not supported.&n; * &n; * SCSI2 - enable support for SCSI-II tagged queueing.  Untested.&n; *&n; * UNSAFE - leave interrupts enabled during pseudo-DMA transfers.  This&n; *&t;    parameter comes from the NCR5380 code.  It is NOT unsafe with&n; *&t;    the PAS16 and you should use it.  If you don&squot;t you will have&n; *&t;    a problem with dropped characters during high speed&n; *&t;    communications during SCSI transfers.  If you really don&squot;t&n; *&t;    want to use UNSAFE you can try defining LIMIT_TRANSFERSIZE or&n; *&t;    twiddle with the transfer size in the high level code.&n; *&n; * USLEEP - enable support for devices that don&squot;t disconnect.  Untested.&n; *&n; * The card is detected and initialized in one of several ways : &n; * 1.  Autoprobe (default) - There are many different models of&n; *     the Pro Audio Spectrum/Studio 16, and I only have one of&n; *     them, so this may require a little tweaking.  An interrupt&n; *     is triggered to autoprobe for the interrupt line.  Note:&n; *     with the newer model boards, the interrupt is set via&n; *     software after reset using the default_irq for the&n; *     current board number.&n; *&n; * 2.  With command line overrides - pas16=port,irq may be &n; *     used on the LILO command line to override the defaults.&n; *&n; * 3.  With the PAS16_OVERRIDE compile time define.  This is &n; *     specified as an array of address, irq tuples.  Ie, for&n; *     one board at the default 0x388 address, IRQ10, I could say &n; *     -DPAS16_OVERRIDE={{0x388, 10}}&n; *     NOTE:  Untested.&n; *&t;&n; * 4.  When included as a module, with arguments passed on the command line:&n; *         pas16_irq=xx&t;&t;the interrupt&n; *         pas16_addr=xx&t;the port&n; *     e.g. &quot;modprobe pas16 pas16_addr=0x388 pas16_irq=5&quot;&n; *&n; *     Note that if the override methods are used, place holders must&n; *     be specified for other boards in the system.&n; *&n; *&n; * Configuration notes :&n; *   The current driver does not support interrupt sharing with the&n; *   sound portion of the card.  If you use the same irq for the&n; *   scsi port and sound you will have problems.  Either use&n; *   a different irq for the scsi port or don&squot;t use interrupts&n; *   for the scsi port.&n; *&n; *   If you have problems with your card not being recognized, use&n; *   the LILO command line override.  Try to get it recognized without&n; *   interrupts.  Ie, for a board at the default 0x388 base port,&n; *   boot: linux pas16=0x388,255&n; *&n; *   IRQ_NONE (255) should be specified for no interrupt,&n; *   IRQ_AUTO (254) to autoprobe for an IRQ line if overridden&n; *   on the command line.&n; *&n; *   (IRQ_AUTO == 254, IRQ_NONE == 255 in NCR5380.h)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;pas16.h&quot;
DECL|macro|AUTOPROBE_IRQ
mdefine_line|#define AUTOPROBE_IRQ
macro_line|#include &quot;NCR5380.h&quot;
macro_line|#include &quot;constants.h&quot;
macro_line|#include &quot;sd.h&quot;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|pas_maxi
r_static
r_int
id|pas_maxi
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas_wmaxi
r_static
r_int
id|pas_wmaxi
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas16_addr
r_static
r_int
r_int
id|pas16_addr
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas16_irq
r_static
r_int
id|pas16_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|scsi_irq_translate
r_int
id|scsi_irq_translate
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|0
comma
l_int|10
comma
l_int|11
)brace
suffix:semicolon
multiline_comment|/* The default_irqs array contains values used to set the irq into the&n; * board via software (as must be done on newer model boards without&n; * irq jumpers on the board).  The first value in the array will be&n; * assigned to logical board 0, the next to board 1, etc.&n; */
DECL|variable|__initdata
r_int
id|default_irqs
(braket
)braket
id|__initdata
op_assign
(brace
id|PAS16_DEFAULT_BOARD_1_IRQ
comma
id|PAS16_DEFAULT_BOARD_2_IRQ
comma
id|PAS16_DEFAULT_BOARD_3_IRQ
comma
id|PAS16_DEFAULT_BOARD_4_IRQ
)brace
suffix:semicolon
DECL|struct|override
r_static
r_struct
id|override
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
)brace
id|overrides
macro_line|#ifdef PAS16_OVERRIDE
DECL|variable|__initdata
(braket
)braket
id|__initdata
op_assign
id|PAS16_OVERRIDE
suffix:semicolon
macro_line|#else
(braket
l_int|4
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0
comma
id|IRQ_AUTO
)brace
comma
(brace
l_int|0
comma
id|IRQ_AUTO
)brace
comma
(brace
l_int|0
comma
id|IRQ_AUTO
)brace
comma
(brace
l_int|0
comma
id|IRQ_AUTO
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|NO_OVERRIDES
mdefine_line|#define NO_OVERRIDES (sizeof(overrides) / sizeof(struct override))
DECL|struct|base
r_static
r_struct
id|base
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|noauto
r_int
id|noauto
suffix:semicolon
DECL|variable|__initdata
)brace
id|bases
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|PAS16_DEFAULT_BASE_1
comma
l_int|0
)brace
comma
(brace
id|PAS16_DEFAULT_BASE_2
comma
l_int|0
)brace
comma
(brace
id|PAS16_DEFAULT_BASE_3
comma
l_int|0
)brace
comma
(brace
id|PAS16_DEFAULT_BASE_4
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NO_BASES
mdefine_line|#define NO_BASES (sizeof (bases) / sizeof (struct base))
DECL|variable|pas16_offset
r_int
r_int
id|pas16_offset
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x1c00
comma
multiline_comment|/* OUTPUT_DATA_REG */
l_int|0x1c01
comma
multiline_comment|/* INITIATOR_COMMAND_REG */
l_int|0x1c02
comma
multiline_comment|/* MODE_REG */
l_int|0x1c03
comma
multiline_comment|/* TARGET_COMMAND_REG */
l_int|0x3c00
comma
multiline_comment|/* STATUS_REG ro, SELECT_ENABLE_REG wo */
l_int|0x3c01
comma
multiline_comment|/* BUS_AND_STATUS_REG ro, START_DMA_SEND_REG wo */
l_int|0x3c02
comma
multiline_comment|/* INPUT_DATA_REGISTER ro, (N/A on PAS16 ?)&n;&t;&t;    * START_DMA_TARGET_RECEIVE_REG wo&n;&t;&t;    */
l_int|0x3c03
comma
multiline_comment|/* RESET_PARITY_INTERRUPT_REG ro,&n;&t;&t;    * START_DMA_INITIATOR_RECEIVE_REG wo&n;&t;&t;    */
)brace
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* the following will set the monitor border color (useful to find&n; where something crashed or gets stuck at */
multiline_comment|/* 1 = blue&n; 2 = green&n; 3 = cyan&n; 4 = red&n; 5 = magenta&n; 6 = yellow&n; 7 = white&n;*/
macro_line|#if 1
DECL|macro|rtrc
mdefine_line|#define rtrc(i) {inb(0x3da); outb(0x31, 0x3c0); outb((i), 0x3c0);}
macro_line|#else
DECL|macro|rtrc
mdefine_line|#define rtrc(i) {}
macro_line|#endif
multiline_comment|/*&n; * Function : enable_board( int  board_num, unsigned short port )&n; *&n; * Purpose :  set address in new model board&n; *&n; * Inputs : board_num - logical board number 0-3, port - base address&n; *&n; */
r_static
r_void
id|__init
DECL|function|enable_board
id|enable_board
c_func
(paren
r_int
id|board_num
comma
r_int
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0xbc
op_plus
id|board_num
comma
id|MASTER_ADDRESS_PTR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|port
op_rshift
l_int|2
comma
id|MASTER_ADDRESS_PTR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : init_board( unsigned short port, int irq )&n; *&n; * Purpose :  Set the board up to handle the SCSI interface&n; *&n; * Inputs : port - base address of the board,&n; *&t;    irq - irq to assign to the SCSI port&n; *&t;    force_irq - set it even if it conflicts with sound driver&n; *&n; */
r_static
r_void
id|__init
DECL|function|init_board
id|init_board
c_func
(paren
r_int
r_int
id|io_port
comma
r_int
id|irq
comma
r_int
id|force_irq
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|pas_irq_code
suffix:semicolon
multiline_comment|/* Initialize the SCSI part of the board */
id|outb
c_func
(paren
l_int|0x30
comma
id|io_port
op_plus
id|P_TIMEOUT_COUNTER_REG
)paren
suffix:semicolon
multiline_comment|/* Timeout counter */
id|outb
c_func
(paren
l_int|0x01
comma
id|io_port
op_plus
id|P_TIMEOUT_STATUS_REG_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Reset TC */
id|outb
c_func
(paren
l_int|0x01
comma
id|io_port
op_plus
id|WAIT_STATE
)paren
suffix:semicolon
multiline_comment|/* 1 Wait state */
id|NCR5380_read
c_func
(paren
id|RESET_PARITY_INTERRUPT_REG
)paren
suffix:semicolon
multiline_comment|/* Set the SCSI interrupt pointer without mucking up the sound&n;&t; * interrupt pointer in the same byte.&n;&t; */
id|pas_irq_code
op_assign
(paren
id|irq
OL
l_int|16
)paren
ques
c_cond
id|scsi_irq_translate
(braket
id|irq
)braket
suffix:colon
l_int|0
suffix:semicolon
id|tmp
op_assign
id|inb
c_func
(paren
id|io_port
op_plus
id|IO_CONFIG_3
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|tmp
op_amp
l_int|0x0f
)paren
op_eq
id|pas_irq_code
)paren
op_logical_and
id|pas_irq_code
OG
l_int|0
op_logical_and
op_logical_neg
id|force_irq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pas16: WARNING: Can&squot;t use same irq as sound &quot;
l_string|&quot;driver -- interrupts disabled&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Set up the drive parameters, disable 5380 interrupts */
id|outb
c_func
(paren
l_int|0x4d
comma
id|io_port
op_plus
id|SYS_CONFIG_4
)paren
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
(paren
id|tmp
op_amp
l_int|0x0f
)paren
op_or
(paren
id|pas_irq_code
op_lshift
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|tmp
comma
id|io_port
op_plus
id|IO_CONFIG_3
)paren
suffix:semicolon
multiline_comment|/* Set up the drive parameters and enable 5380 interrupts */
id|outb
c_func
(paren
l_int|0x6d
comma
id|io_port
op_plus
id|SYS_CONFIG_4
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function : pas16_hw_detect( unsigned short board_num )&n; *&n; * Purpose : determine if a pas16 board is present&n; * &n; * Inputs : board_num - logical board number ( 0 - 3 )&n; *&n; * Returns : 0 if board not found, 1 if found.&n; */
r_static
r_int
id|__init
DECL|function|pas16_hw_detect
id|pas16_hw_detect
c_func
(paren
r_int
r_int
id|board_num
)paren
(brace
r_int
r_char
id|board_rev
comma
id|tmp
suffix:semicolon
r_int
r_int
id|io_port
op_assign
id|bases
(braket
id|board_num
)braket
dot
id|io_port
suffix:semicolon
multiline_comment|/* See if we can find a PAS16 board at the address associated&n;     * with this logical board number.&n;     */
multiline_comment|/* First, attempt to take a newer model board out of reset and&n;     * give it a base address.  This shouldn&squot;t affect older boards.&n;     */
id|enable_board
c_func
(paren
id|board_num
comma
id|io_port
)paren
suffix:semicolon
multiline_comment|/* Now see if it looks like a PAS16 board */
id|board_rev
op_assign
id|inb
c_func
(paren
id|io_port
op_plus
id|PCB_CONFIG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_rev
op_eq
l_int|0xff
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
id|board_rev
op_xor
l_int|0xe0
suffix:semicolon
id|outb
c_func
(paren
id|tmp
comma
id|io_port
op_plus
id|PCB_CONFIG
)paren
suffix:semicolon
id|tmp
op_assign
id|inb
c_func
(paren
id|io_port
op_plus
id|PCB_CONFIG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|board_rev
comma
id|io_port
op_plus
id|PCB_CONFIG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_rev
op_ne
id|tmp
)paren
(brace
multiline_comment|/* Not a PAS-16 */
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|io_port
op_plus
id|OPERATION_MODE_1
)paren
op_amp
l_int|0x03
)paren
op_ne
l_int|0x03
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* return if no SCSI interface found */
multiline_comment|/* Mediavision has some new model boards that return ID bits&n;     * that indicate a SCSI interface, but they&squot;re not (LMS).  We&squot;ll&n;     * put in an additional test to try to weed them out.&n;     */
id|outb
c_func
(paren
l_int|0x01
comma
id|io_port
op_plus
id|WAIT_STATE
)paren
suffix:semicolon
multiline_comment|/* 1 Wait state */
id|NCR5380_write
c_func
(paren
id|MODE_REG
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Is it really SCSI? */
r_if
c_cond
(paren
id|NCR5380_read
c_func
(paren
id|MODE_REG
)paren
op_ne
l_int|0x20
)paren
(brace
multiline_comment|/* Write to a reg.    */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* and try to read    */
id|NCR5380_write
c_func
(paren
id|MODE_REG
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* it back.&t;      */
r_if
c_cond
(paren
id|NCR5380_read
c_func
(paren
id|MODE_REG
)paren
op_ne
l_int|0x00
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : pas16_setup(char *str, int *ints)&n; *&n; * Purpose : LILO command line initialization of the overrides array,&n; * &n; * Inputs : str - unused, ints - array of integer parameters with ints[0]&n; *&t;equal to the number of ints.&n; *&n; */
DECL|function|pas16_setup
r_void
id|__init
id|pas16_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_static
r_int
id|commandline_current
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ne
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;pas16_setup : usage pas16=io_port,irq&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|commandline_current
OL
id|NO_OVERRIDES
)paren
(brace
id|overrides
(braket
id|commandline_current
)braket
dot
id|io_port
op_assign
(paren
r_int
r_int
)paren
id|ints
(braket
l_int|1
)braket
suffix:semicolon
id|overrides
(braket
id|commandline_current
)braket
dot
id|irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NO_BASES
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|bases
(braket
id|i
)braket
dot
id|io_port
op_eq
(paren
r_int
r_int
)paren
id|ints
(braket
l_int|1
)braket
)paren
(brace
id|bases
(braket
id|i
)braket
dot
id|noauto
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
op_increment
id|commandline_current
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Function : int pas16_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : detects and initializes PAS16 controllers&n; *&t;that were autoprobed, overridden on the LILO command line, &n; *&t;or specified at compile time.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; * &n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n; */
DECL|function|pas16_detect
r_int
id|__init
id|pas16_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_int
id|current_override
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|current_base
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
r_int
r_int
id|io_port
suffix:semicolon
r_int
id|count
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;pas16&quot;
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|pas16_proc_info
suffix:semicolon
r_if
c_cond
(paren
id|pas16_addr
op_ne
l_int|0
)paren
(brace
id|overrides
(braket
l_int|0
)braket
dot
id|io_port
op_assign
id|pas16_addr
suffix:semicolon
multiline_comment|/*&n;&t;*  This is how we avoid seeing more than&n;&t;*  one host adapter at the same I/O port.&n;&t;*  Cribbed shamelessly from pas16_setup().&n;&t;*/
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|NO_BASES
suffix:semicolon
op_increment
id|count
)paren
r_if
c_cond
(paren
id|bases
(braket
id|count
)braket
dot
id|io_port
op_eq
id|pas16_addr
)paren
(brace
id|bases
(braket
id|count
)braket
dot
id|noauto
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pas16_irq
op_ne
l_int|0
)paren
id|overrides
(braket
l_int|0
)braket
dot
id|irq
op_assign
id|pas16_irq
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|current_override
OL
id|NO_OVERRIDES
suffix:semicolon
op_increment
id|current_override
)paren
(brace
id|io_port
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|overrides
(braket
id|current_override
)braket
dot
id|io_port
)paren
(brace
id|io_port
op_assign
id|overrides
(braket
id|current_override
)braket
dot
id|io_port
suffix:semicolon
id|enable_board
c_func
(paren
id|current_override
comma
id|io_port
)paren
suffix:semicolon
id|init_board
c_func
(paren
id|io_port
comma
id|overrides
(braket
id|current_override
)braket
dot
id|irq
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
suffix:semicolon
op_logical_neg
id|io_port
op_logical_and
(paren
id|current_base
OL
id|NO_BASES
)paren
suffix:semicolon
op_increment
id|current_base
)paren
(brace
macro_line|#if (PDEBUG &amp; PDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-pas16 : probing io_port %04x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|bases
(braket
id|current_base
)braket
dot
id|io_port
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|bases
(braket
id|current_base
)braket
dot
id|noauto
op_logical_and
id|pas16_hw_detect
c_func
(paren
id|current_base
)paren
)paren
(brace
id|io_port
op_assign
id|bases
(braket
id|current_base
)braket
dot
id|io_port
suffix:semicolon
id|init_board
c_func
(paren
id|io_port
comma
id|default_irqs
(braket
id|current_base
)braket
comma
l_int|0
)paren
suffix:semicolon
macro_line|#if (PDEBUG &amp; PDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-pas16 : detected board.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#if defined(PDEBUG) &amp;&amp; (PDEBUG &amp; PDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-pas16 : io_port = %04x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|io_port
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|io_port
)paren
r_break
suffix:semicolon
id|instance
op_assign
id|scsi_register
(paren
id|tpnt
comma
r_sizeof
(paren
r_struct
id|NCR5380_hostdata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance
op_eq
l_int|NULL
)paren
(brace
r_break
suffix:semicolon
)brace
id|instance-&gt;io_port
op_assign
id|io_port
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|instance
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|overrides
(braket
id|current_override
)braket
dot
id|irq
op_ne
id|IRQ_AUTO
)paren
id|instance-&gt;irq
op_assign
id|overrides
(braket
id|current_override
)braket
dot
id|irq
suffix:semicolon
r_else
id|instance-&gt;irq
op_assign
id|NCR5380_probe_irq
c_func
(paren
id|instance
comma
id|PAS16_IRQS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|IRQ_NONE
)paren
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|instance-&gt;irq
comma
id|do_pas16_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;pas16&quot;
comma
id|instance
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d : IRQ%d not free, interrupts disabled&bslash;n&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|IRQ_NONE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d : interrupts not enabled. for better interactive performance,&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi%d : please jumper the board for a free IRQ.&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
multiline_comment|/* Disable 5380 interrupts, leave drive params the same */
id|outb
c_func
(paren
l_int|0x4d
comma
id|io_port
op_plus
id|SYS_CONFIG_4
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|io_port
op_plus
id|IO_CONFIG_3
)paren
op_amp
l_int|0x0f
)paren
comma
id|io_port
op_plus
id|IO_CONFIG_3
)paren
suffix:semicolon
)brace
macro_line|#if defined(PDEBUG) &amp;&amp; (PDEBUG &amp; PDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi%d : irq = %d&bslash;n&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;scsi%d : at 0x%04x&quot;
comma
id|instance-&gt;host_no
comma
(paren
r_int
)paren
id|instance-&gt;io_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|IRQ_NONE
)paren
id|printk
(paren
l_string|&quot; interrupts disabled&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot; irq %d&quot;
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; options CAN_QUEUE=%d  CMD_PER_LUN=%d release=%d&quot;
comma
id|CAN_QUEUE
comma
id|CMD_PER_LUN
comma
id|PAS16_PUBLIC_RELEASE
)paren
suffix:semicolon
id|NCR5380_print_options
c_func
(paren
id|instance
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_increment
id|current_override
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : int pas16_biosparam(Disk *disk, kdev_t dev, int *ip)&n; *&n; * Purpose : Generates a BIOS / DOS compatible H-C-S mapping for &n; *&t;the specified device / size.&n; * &n; * Inputs : size = size of device in sectors (512 bytes), dev = block device&n; *&t;major / minor, ip[] = {heads, sectors, cylinders}  &n; *&n; * Returns : always 0 (success), initializes ip&n; *&t;&n; */
multiline_comment|/* &n; * XXX Most SCSI boards use this mapping, I could be incorrect.  Some one&n; * using hard disks on a trantor should verify that this mapping corresponds&n; * to that used by the BIOS / ASPI driver by running the linux fdisk program&n; * and matching the H_C_S coordinates to what DOS uses.&n; */
DECL|function|pas16_biosparam
r_int
id|pas16_biosparam
c_func
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
op_star
id|ip
)paren
(brace
r_int
id|size
op_assign
id|disk-&gt;capacity
suffix:semicolon
id|ip
(braket
l_int|0
)braket
op_assign
l_int|64
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|32
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|size
op_rshift
l_int|11
suffix:semicolon
multiline_comment|/* I think I have it as /(32*64) */
r_if
c_cond
(paren
id|ip
(braket
l_int|2
)braket
OG
l_int|1024
)paren
(brace
multiline_comment|/* yes, &gt;, not &gt;= */
id|ip
(braket
l_int|0
)braket
op_assign
l_int|255
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|63
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|size
op_div
(paren
l_int|63
op_star
l_int|255
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
(braket
l_int|2
)braket
OG
l_int|1023
)paren
(brace
multiline_comment|/* yes &gt;1023... */
id|ip
(braket
l_int|2
)braket
op_assign
l_int|1023
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : int NCR5380_pread (struct Scsi_Host *instance, &n; *&t;unsigned char *dst, int len)&n; *&n; * Purpose : Fast 5380 pseudo-dma read function, transfers len bytes to &n; *&t;dst&n; * &n; * Inputs : dst = destination, len = length in bytes&n; *&n; * Returns : 0 on success, non zero on a failure such as a watchdog &n; * &t;timeout.&n; */
DECL|function|NCR5380_pread
r_static
r_inline
r_int
id|NCR5380_pread
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|dst
comma
r_int
id|len
)paren
(brace
r_register
r_int
r_char
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_register
r_int
r_int
id|reg
op_assign
(paren
r_int
r_int
)paren
(paren
id|instance-&gt;io_port
op_plus
id|P_DATA_REG_OFFSET
)paren
suffix:semicolon
r_register
r_int
id|i
op_assign
id|len
suffix:semicolon
r_int
id|ii
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|instance-&gt;io_port
op_plus
id|P_STATUS_REG_OFFSET
)paren
op_amp
id|P_ST_RDY
)paren
)paren
op_increment
id|ii
suffix:semicolon
id|insb
c_func
(paren
id|reg
comma
id|d
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|instance-&gt;io_port
op_plus
id|P_TIMEOUT_STATUS_REG_OFFSET
)paren
op_amp
id|P_TS_TIM
)paren
(brace
id|outb
c_func
(paren
id|P_TS_CT
comma
id|instance-&gt;io_port
op_plus
id|P_TIMEOUT_STATUS_REG_OFFSET
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi%d : watchdog timer fired in NCR5380_pread()&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ii
OG
id|pas_maxi
)paren
id|pas_maxi
op_assign
id|ii
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : int NCR5380_pwrite (struct Scsi_Host *instance, &n; *&t;unsigned char *src, int len)&n; *&n; * Purpose : Fast 5380 pseudo-dma write function, transfers len bytes from&n; *&t;src&n; * &n; * Inputs : src = source, len = length in bytes&n; *&n; * Returns : 0 on success, non zero on a failure such as a watchdog &n; * &t;timeout.&n; */
DECL|function|NCR5380_pwrite
r_static
r_inline
r_int
id|NCR5380_pwrite
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|src
comma
r_int
id|len
)paren
(brace
r_register
r_int
r_char
op_star
id|s
op_assign
id|src
suffix:semicolon
r_register
r_int
r_int
id|reg
op_assign
(paren
id|instance-&gt;io_port
op_plus
id|P_DATA_REG_OFFSET
)paren
suffix:semicolon
r_register
r_int
id|i
op_assign
id|len
suffix:semicolon
r_int
id|ii
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
(paren
id|inb
c_func
(paren
id|instance-&gt;io_port
op_plus
id|P_STATUS_REG_OFFSET
)paren
)paren
op_amp
id|P_ST_RDY
)paren
)paren
op_increment
id|ii
suffix:semicolon
id|outsb
c_func
(paren
id|reg
comma
id|s
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|instance-&gt;io_port
op_plus
id|P_TIMEOUT_STATUS_REG_OFFSET
)paren
op_amp
id|P_TS_TIM
)paren
(brace
id|outb
c_func
(paren
id|P_TS_CT
comma
id|instance-&gt;io_port
op_plus
id|P_TIMEOUT_STATUS_REG_OFFSET
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi%d : watchdog timer fired in NCR5380_pwrite()&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ii
OG
id|pas_maxi
)paren
id|pas_wmaxi
op_assign
id|ii
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#include &quot;NCR5380.c&quot;
multiline_comment|/* Eventually this will go into an include file, but this will be later */
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|MV_PAS16
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
macro_line|#ifdef MODULE
id|MODULE_PARM
c_func
(paren
id|pas16_addr
comma
l_string|&quot;h&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pas16_irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
