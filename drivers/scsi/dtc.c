DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
DECL|macro|PSEUDO_DMA
mdefine_line|#define PSEUDO_DMA
DECL|macro|DONT_USE_INTR
mdefine_line|#define DONT_USE_INTR
DECL|macro|UNSAFE
mdefine_line|#define UNSAFE&t;&t;/* Leave interrupts enabled during pseudo-dma I/O */
DECL|macro|xNDEBUG
mdefine_line|#define xNDEBUG (NDEBUG_INTR+NDEBUG_RESELECTION+&bslash;&n;&t;&t; NDEBUG_SELECTION+NDEBUG_ARBITRATION)
DECL|macro|DMA_WORKS_RIGHT
mdefine_line|#define DMA_WORKS_RIGHT
multiline_comment|/*&n; * DTC 3180/3280 driver, by&n; *&t;Ray Van Tassle&t;rayvt@comm.mot.com&n; *&n; *&t;taken from ...&n; *&t;Trantor T128/T128F/T228 driver by...&n; *&n; * &t;Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * DISTRIBUTION RELEASE 1.&n; *&n; * For more information, please consult &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n;*/
multiline_comment|/*&n; * Options : &n; * AUTOSENSE - if defined, REQUEST SENSE will be performed automatically&n; *      for commands that return with a CHECK CONDITION status. &n; *&n; * PSEUDO_DMA - enables PSEUDO-DMA hardware, should give a 3-4X performance&n; * increase compared to polled I/O.&n; *&n; * PARITY - enable parity checking.  Not supported.&n; *&n; * UNSAFE - leave interrupts enabled during pseudo-DMA transfers. &n; *&t;&t;You probably want this.&n; *&n; * The card is detected and initialized in one of several ways : &n; * 1.  Autoprobe (default) - since the board is memory mapped, &n; *     a BIOS signature is scanned for to locate the registers.&n; *     An interrupt is triggered to autoprobe for the interrupt&n; *     line.&n; *&n; * 2.  With command line overrides - dtc=address,irq may be &n; *     used on the LILO command line to override the defaults.&n; * &n;*/
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* the following will set the monitor border color (useful to find&n; where something crashed or gets stuck at */
multiline_comment|/* 1 = blue&n; 2 = green&n; 3 = cyan&n; 4 = red&n; 5 = magenta&n; 6 = yellow&n; 7 = white&n;*/
macro_line|#if 0
mdefine_line|#define rtrc(i) {inb(0x3da); outb(0x31, 0x3c0); outb((i), 0x3c0);}
macro_line|#else
DECL|macro|rtrc
mdefine_line|#define rtrc(i) {}
macro_line|#endif
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;dtc.h&quot;
DECL|macro|AUTOPROBE_IRQ
mdefine_line|#define AUTOPROBE_IRQ
macro_line|#include &quot;NCR5380.h&quot;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|DTC_PUBLIC_RELEASE
mdefine_line|#define DTC_PUBLIC_RELEASE 2
multiline_comment|/*#define DTCDEBUG 0x1*/
DECL|macro|DTCDEBUG_INIT
mdefine_line|#define DTCDEBUG_INIT&t;0x1
DECL|macro|DTCDEBUG_TRANSFER
mdefine_line|#define DTCDEBUG_TRANSFER 0x2
multiline_comment|/*&n; * The DTC3180 &amp; 3280 boards are memory mapped.&n; * &n; */
multiline_comment|/*&n; */
multiline_comment|/* Offset from DTC_5380_OFFSET */
DECL|macro|DTC_CONTROL_REG
mdefine_line|#define DTC_CONTROL_REG&t;&t;0x100&t;/* rw */
DECL|macro|D_CR_ACCESS
mdefine_line|#define D_CR_ACCESS&t;&t;0x80&t;/* ro set=can access 3280 registers */
DECL|macro|CSR_DIR_READ
mdefine_line|#define CSR_DIR_READ&t;&t;0x40&t;/* rw direction, 1 = read 0 = write */
DECL|macro|CSR_RESET
mdefine_line|#define CSR_RESET              0x80    /* wo  Resets 53c400 */
DECL|macro|CSR_5380_REG
mdefine_line|#define CSR_5380_REG           0x80    /* ro  5380 registers can be accessed */
DECL|macro|CSR_TRANS_DIR
mdefine_line|#define CSR_TRANS_DIR          0x40    /* rw  Data transfer direction */
DECL|macro|CSR_SCSI_BUFF_INTR
mdefine_line|#define CSR_SCSI_BUFF_INTR     0x20    /* rw  Enable int on transfer ready */
DECL|macro|CSR_5380_INTR
mdefine_line|#define CSR_5380_INTR          0x10    /* rw  Enable 5380 interrupts */
DECL|macro|CSR_SHARED_INTR
mdefine_line|#define CSR_SHARED_INTR        0x08    /* rw  Interrupt sharing */
DECL|macro|CSR_HOST_BUF_NOT_RDY
mdefine_line|#define CSR_HOST_BUF_NOT_RDY   0x04    /* ro  Host buffer not ready */
DECL|macro|CSR_SCSI_BUF_RDY
mdefine_line|#define CSR_SCSI_BUF_RDY       0x02    /* ro  SCSI buffer ready */
DECL|macro|CSR_GATED_5380_IRQ
mdefine_line|#define CSR_GATED_5380_IRQ     0x01    /* ro  Last block xferred */
DECL|macro|CSR_INT_BASE
mdefine_line|#define CSR_INT_BASE (CSR_SCSI_BUFF_INTR | CSR_5380_INTR)
DECL|macro|DTC_BLK_CNT
mdefine_line|#define DTC_BLK_CNT&t;&t;0x101   /* rw &n;&t;&t;&t;&t;&t; * # of 128-byte blocks to transfer */
DECL|macro|D_CR_ACCESS
mdefine_line|#define D_CR_ACCESS             0x80    /* ro set=can access 3280 registers */
DECL|macro|DTC_SWITCH_REG
mdefine_line|#define DTC_SWITCH_REG&t;&t;0x3982&t;/* ro - DIP switches */
DECL|macro|DTC_RESUME_XFER
mdefine_line|#define DTC_RESUME_XFER&t;&t;0x3982&t;/* wo - resume data xfer &n;&t;&t;&t;&t;&t;   * after disconnect/reconnect*/
DECL|macro|DTC_5380_OFFSET
mdefine_line|#define DTC_5380_OFFSET&t;&t;0x3880&t;/* 8 registers here, see NCR5380.h */
multiline_comment|/*!!!! for dtc, it&squot;s a 128 byte buffer at 3900 !!! */
DECL|macro|DTC_DATA_BUF
mdefine_line|#define DTC_DATA_BUF&t;&t;0x3900  /* rw 128 bytes long */
DECL|struct|override
r_static
r_struct
id|override
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
)brace
id|overrides
macro_line|#ifdef OVERRIDE
DECL|variable|__initdata
(braket
)braket
id|__initdata
op_assign
id|OVERRIDE
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
DECL|member|address
r_int
r_int
id|address
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
l_int|0xcc000
comma
l_int|0
)brace
comma
(brace
l_int|0xc8000
comma
l_int|0
)brace
comma
(brace
l_int|0xdc000
comma
l_int|0
)brace
comma
(brace
l_int|0xd8000
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NO_BASES
mdefine_line|#define NO_BASES (sizeof (bases) / sizeof (struct base))
DECL|struct|signature
r_static
r_const
r_struct
id|signature
(brace
DECL|member|string
r_const
r_char
op_star
id|string
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|variable|signatures
)brace
id|signatures
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;DATA TECHNOLOGY CORPORATION BIOS&quot;
comma
l_int|0x25
)brace
comma
)brace
suffix:semicolon
DECL|macro|NO_SIGNATURES
mdefine_line|#define NO_SIGNATURES (sizeof (signatures) /  sizeof (struct signature))
multiline_comment|/*&n; * Function : dtc_setup(char *str, int *ints)&n; *&n; * Purpose : LILO command line initialization of the overrides array,&n; * &n; * Inputs : str - unused, ints - array of integer parameters with ints[0]&n; *&t;equal to the number of ints.&n; *&n;*/
DECL|function|dtc_setup
r_void
id|__init
(def_block
id|dtc_setup
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
l_string|&quot;dtc_setup: usage dtc=address,irq&bslash;n&quot;
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
id|address
op_assign
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
id|address
op_eq
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
)def_block
multiline_comment|/* &n; * Function : int dtc_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : detects and initializes DTC 3180/3280 controllers&n; *&t;that were autoprobed, overridden on the LILO command line, &n; *&t;or specified at compile time.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; * &n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n;*/
DECL|function|dtc_detect
r_int
id|__init
(def_block
id|dtc_detect
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
comma
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
id|base
suffix:semicolon
r_int
id|sig
comma
id|count
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;dtc3x80&quot;
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|dtc_proc_info
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
id|base
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
id|address
)paren
id|base
op_assign
id|overrides
(braket
id|current_override
)braket
dot
id|address
suffix:semicolon
r_else
r_for
c_loop
(paren
suffix:semicolon
op_logical_neg
id|base
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
macro_line|#if (DTCDEBUG &amp; DTCDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-dtc : probing address %08x&bslash;n&quot;
comma
id|bases
(braket
id|current_base
)braket
dot
id|address
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|sig
op_assign
l_int|0
suffix:semicolon
id|sig
OL
id|NO_SIGNATURES
suffix:semicolon
op_increment
id|sig
)paren
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
id|isa_check_signature
c_func
(paren
id|bases
(braket
id|current_base
)braket
dot
id|address
op_plus
id|signatures
(braket
id|sig
)braket
dot
id|offset
comma
id|signatures
(braket
id|sig
)braket
dot
id|string
comma
id|strlen
c_func
(paren
id|signatures
(braket
id|sig
)braket
dot
id|string
)paren
)paren
)paren
(brace
id|base
op_assign
id|bases
(braket
id|current_base
)braket
dot
id|address
suffix:semicolon
macro_line|#if (DTCDEBUG &amp; DTCDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-dtc : detected board.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
)brace
macro_line|#if defined(DTCDEBUG) &amp;&amp; (DTCDEBUG &amp; DTCDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-dtc : base = %08x&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|base
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
id|instance-&gt;base
op_assign
id|base
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|instance
comma
l_int|0
)paren
suffix:semicolon
id|NCR5380_write
c_func
(paren
id|DTC_CONTROL_REG
comma
id|CSR_5380_INTR
)paren
suffix:semicolon
multiline_comment|/* Enable int&squot;s */
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
id|DTC_IRQS
)paren
suffix:semicolon
macro_line|#ifndef DONT_USE_INTR
multiline_comment|/* With interrupts enabled, it will sometimes hang when doing heavy&n; * reads. So better not enable them until I finger it out. */
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
id|do_dtc_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;dtc&quot;
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
)brace
macro_line|#else
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|IRQ_NONE
)paren
id|printk
c_func
(paren
l_string|&quot;scsi%d : interrupts not used. Might as well not jumper it.&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_NONE
suffix:semicolon
macro_line|#endif
macro_line|#if defined(DTCDEBUG) &amp;&amp; (DTCDEBUG &amp; DTCDEBUG_INIT)
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
l_string|&quot;scsi%d : at 0x%05X&quot;
comma
id|instance-&gt;host_no
comma
(paren
r_int
)paren
id|instance-&gt;base
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
id|DTC_PUBLIC_RELEASE
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
)def_block
multiline_comment|/*&n; * Function : int dtc_biosparam(Disk * disk, struct block_device *dev, int *ip)&n; *&n; * Purpose : Generates a BIOS / DOS compatible H-C-S mapping for &n; *&t;the specified device / size.&n; * &n; * Inputs : size = size of device in sectors (512 bytes), dev = block device&n; *&t;major / minor, ip[] = {heads, sectors, cylinders}  &n; *&n; * Returns : always 0 (success), initializes ip&n; *&t;&n;*/
multiline_comment|/* &n; * XXX Most SCSI boards use this mapping, I could be incorrect.  Some one&n; * using hard disks on a trantor should verify that this mapping corresponds&n; * to that used by the BIOS / ASPI driver by running the linux fdisk program&n; * and matching the H_C_S coordinates to what DOS uses.&n;*/
DECL|function|dtc_biosparam
r_int
id|dtc_biosparam
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|dev
comma
id|sector_t
id|capacity
comma
r_int
op_star
id|ip
)paren
(brace
r_int
id|size
op_assign
id|capacity
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; * Function : int NCR5380_pread (struct Scsi_Host *instance, &n; *&t;unsigned char *dst, int len)&n; *&n; * Purpose : Fast 5380 pseudo-dma read function, reads len bytes to &n; *&t;dst&n; * &n; * Inputs : dst = destination, len = length in bytes&n; *&n; * Returns : 0 on success, non zero on a failure such as a watchdog &n; * &t;timeout.&n;*/
DECL|variable|dtc_maxi
r_static
r_int
id|dtc_maxi
op_assign
l_int|0
suffix:semicolon
DECL|variable|dtc_wmaxi
r_static
r_int
id|dtc_wmaxi
op_assign
l_int|0
suffix:semicolon
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
r_int
r_char
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* For counting time spent in the poll-loop */
id|NCR5380_local_declare
c_func
(paren
)paren
suffix:semicolon
id|NCR5380_setup
c_func
(paren
id|instance
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|NCR5380_read
c_func
(paren
id|RESET_PARITY_INTERRUPT_REG
)paren
suffix:semicolon
id|NCR5380_write
c_func
(paren
id|MODE_REG
comma
id|MR_ENABLE_EOP_INTR
op_or
id|MR_DMA_MODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|IRQ_NONE
)paren
id|NCR5380_write
c_func
(paren
id|DTC_CONTROL_REG
comma
id|CSR_DIR_READ
)paren
suffix:semicolon
r_else
id|NCR5380_write
c_func
(paren
id|DTC_CONTROL_REG
comma
id|CSR_DIR_READ
op_or
id|CSR_INT_BASE
)paren
suffix:semicolon
id|NCR5380_write
c_func
(paren
id|DTC_BLK_CNT
comma
id|len
op_rshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Block count */
id|rtrc
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|rtrc
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|NCR5380_read
c_func
(paren
id|DTC_CONTROL_REG
)paren
op_amp
id|CSR_HOST_BUF_NOT_RDY
)paren
op_increment
id|i
suffix:semicolon
id|rtrc
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|d
comma
id|base
op_plus
id|DTC_DATA_BUF
comma
l_int|128
)paren
suffix:semicolon
id|d
op_add_assign
l_int|128
suffix:semicolon
id|len
op_sub_assign
l_int|128
suffix:semicolon
id|rtrc
c_func
(paren
l_int|7
)paren
suffix:semicolon
multiline_comment|/*** with int&squot;s on, it sometimes hangs after here.&n;&t;&t; * Looks like something makes HBNR go away. */
)brace
id|rtrc
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|DTC_CONTROL_REG
)paren
op_amp
id|D_CR_ACCESS
)paren
)paren
op_increment
id|i
suffix:semicolon
id|NCR5380_write
c_func
(paren
id|MODE_REG
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear the operating mode */
id|rtrc
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|NCR5380_read
c_func
(paren
id|RESET_PARITY_INTERRUPT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|dtc_maxi
)paren
id|dtc_maxi
op_assign
id|i
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; * Function : int NCR5380_pwrite (struct Scsi_Host *instance, &n; *&t;unsigned char *src, int len)&n; *&n; * Purpose : Fast 5380 pseudo-dma write function, transfers len bytes from&n; *&t;src&n; * &n; * Inputs : src = source, len = length in bytes&n; *&n; * Returns : 0 on success, non zero on a failure such as a watchdog &n; * &t;timeout.&n;*/
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
r_int
id|i
suffix:semicolon
id|NCR5380_local_declare
c_func
(paren
)paren
suffix:semicolon
id|NCR5380_setup
c_func
(paren
id|instance
)paren
suffix:semicolon
id|NCR5380_read
c_func
(paren
id|RESET_PARITY_INTERRUPT_REG
)paren
suffix:semicolon
id|NCR5380_write
c_func
(paren
id|MODE_REG
comma
id|MR_ENABLE_EOP_INTR
op_or
id|MR_DMA_MODE
)paren
suffix:semicolon
multiline_comment|/* set direction (write) */
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|IRQ_NONE
)paren
id|NCR5380_write
c_func
(paren
id|DTC_CONTROL_REG
comma
l_int|0
)paren
suffix:semicolon
r_else
id|NCR5380_write
c_func
(paren
id|DTC_CONTROL_REG
comma
id|CSR_5380_INTR
)paren
suffix:semicolon
id|NCR5380_write
c_func
(paren
id|DTC_BLK_CNT
comma
id|len
op_rshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Block count */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rtrc
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Poll until the host buffer can accept data. */
r_while
c_loop
(paren
id|NCR5380_read
c_func
(paren
id|DTC_CONTROL_REG
)paren
op_amp
id|CSR_HOST_BUF_NOT_RDY
)paren
op_increment
id|i
suffix:semicolon
id|rtrc
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|isa_memcpy_toio
c_func
(paren
id|base
op_plus
id|DTC_DATA_BUF
comma
id|src
comma
l_int|128
)paren
suffix:semicolon
id|src
op_add_assign
l_int|128
suffix:semicolon
id|len
op_sub_assign
l_int|128
suffix:semicolon
)brace
id|rtrc
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|DTC_CONTROL_REG
)paren
op_amp
id|D_CR_ACCESS
)paren
)paren
op_increment
id|i
suffix:semicolon
id|rtrc
c_func
(paren
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Wait until the last byte has been sent to the disk */
r_while
c_loop
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|TARGET_COMMAND_REG
)paren
op_amp
id|TCR_LAST_BYTE_SENT
)paren
)paren
op_increment
id|i
suffix:semicolon
id|rtrc
c_func
(paren
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Check for parity error here. fixme. */
id|NCR5380_write
c_func
(paren
id|MODE_REG
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear the operating mode */
id|rtrc
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|dtc_wmaxi
)paren
id|dtc_wmaxi
op_assign
id|i
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#include &quot;NCR5380.c&quot;
multiline_comment|/* Eventually this will go into an include file, but this will be later */
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|DTC3x80
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
