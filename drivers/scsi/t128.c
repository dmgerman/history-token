DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
DECL|macro|PSEUDO_DMA
mdefine_line|#define PSEUDO_DMA
multiline_comment|/*&n; * Trantor T128/T128F/T228 driver&n; *&t;Note : architecturally, the T100 and T130 are different and won&squot;t &n; * &t;work&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * DISTRIBUTION RELEASE 3.&n; *&n; * For more information, please consult &n; *&n; * Trantor Systems, Ltd.&n; * T128/T128F/T228 SCSI Host Adapter&n; * Hardware Specifications&n; * &n; * Trantor Systems, Ltd. &n; * 5415 Randall Place&n; * Fremont, CA 94538&n; * 1+ (415) 770-1400, FAX 1+ (415) 770-9910&n; * &n; * and &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * Options : &n; * AUTOSENSE - if defined, REQUEST SENSE will be performed automatically&n; *      for commands that return with a CHECK CONDITION status. &n; *&n; * PSEUDO_DMA - enables PSEUDO-DMA hardware, should give a 3-4X performance&n; * increase compared to polled I/O.&n; *&n; * PARITY - enable parity checking.  Not supported.&n; * &n; * SCSI2 - enable support for SCSI-II tagged queueing.  Untested.&n; *&n; *&n; * UNSAFE - leave interrupts enabled during pseudo-DMA transfers.  You&n; *          only really want to use this if you&squot;re having a problem with&n; *          dropped characters during high speed communications, and even&n; *          then, you&squot;re going to be better off twiddling with transfersize.&n; *&n; * USLEEP - enable support for devices that don&squot;t disconnect.  Untested.&n; *&n; * The card is detected and initialized in one of several ways : &n; * 1.  Autoprobe (default) - since the board is memory mapped, &n; *     a BIOS signature is scanned for to locate the registers.&n; *     An interrupt is triggered to autoprobe for the interrupt&n; *     line.&n; *&n; * 2.  With command line overrides - t128=address,irq may be &n; *     used on the LILO command line to override the defaults.&n; *&n; * 3.  With the T128_OVERRIDE compile time define.  This is &n; *     specified as an array of address, irq tuples.  Ie, for&n; *     one board at the default 0xcc000 address, IRQ5, I could say &n; *     -DT128_OVERRIDE={{0xcc000, 5}}&n; *&t;&n; *     Note that if the override methods are used, place holders must&n; *     be specified for other boards in the system.&n; * &n; * T128/T128F jumper/dipswitch settings (note : on my sample, the switches &n; * were epoxy&squot;d shut, meaning I couldn&squot;t change the 0xcc000 base address) :&n; *&n; * T128    Sw7 Sw8 Sw6 = 0ws Sw5 = boot &n; * T128F   Sw6 Sw7 Sw5 = 0ws Sw4 = boot Sw8 = floppy disable&n; * cc000   off off      &n; * c8000   off on&n; * dc000   on  off&n; * d8000   on  on&n; *&n; * &n; * Interrupts &n; * There is a 12 pin jumper block, jp1, numbered as follows : &n; *   T128 (JP1)  &t; T128F (J5)&n; * 2 4 6 8 10 12&t;11 9  7 5 3 1&n; * 1 3 5 7 9  11&t;12 10 8 6 4 2&n; *&n; * 3   2-4&n; * 5   1-3&n; * 7   3-5&n; * T128F only &n; * 10 8-10&n; * 12 7-9&n; * 14 10-12&n; * 15 9-11&n; */
multiline_comment|/*&n; * $Log: t128.c,v $&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;t128.h&quot;
DECL|macro|AUTOPROBE_IRQ
mdefine_line|#define AUTOPROBE_IRQ
macro_line|#include &quot;NCR5380.h&quot;
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
macro_line|#ifdef T128_OVERRIDE
DECL|variable|__initdata
(braket
)braket
id|__initdata
op_assign
id|T128_OVERRIDE
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
DECL|variable|__initdata
)brace
id|signatures
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_string|&quot;TSROM: SCSI BIOS, Version 1.12&quot;
comma
l_int|0x36
)brace
comma
)brace
suffix:semicolon
DECL|macro|NO_SIGNATURES
mdefine_line|#define NO_SIGNATURES (sizeof (signatures) /  sizeof (struct signature))
multiline_comment|/*&n; * Function : t128_setup(char *str, int *ints)&n; *&n; * Purpose : LILO command line initialization of the overrides array,&n; * &n; * Inputs : str - unused, ints - array of integer parameters with ints[0]&n; *&t;equal to the number of ints.&n; *&n; */
DECL|function|t128_setup
r_void
id|__init
(def_block
id|t128_setup
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
l_string|&quot;t128_setup : usage t128=address,irq&bslash;n&quot;
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
multiline_comment|/* &n; * Function : int t128_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : detects and initializes T128,T128F, or T228 controllers&n; *&t;that were autoprobed, overridden on the LILO command line, &n; *&t;or specified at compile time.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; * &n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n; */
DECL|function|t128_detect
r_int
id|__init
(def_block
id|t128_detect
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
l_string|&quot;t128&quot;
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|t128_proc_info
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
r_void
id|__iomem
op_star
id|p
suffix:semicolon
macro_line|#if (TDEBUG &amp; TDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-t128 : probing address %08x&bslash;n&quot;
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
r_if
c_cond
(paren
id|bases
(braket
id|current_base
)braket
dot
id|noauto
)paren
r_continue
suffix:semicolon
id|p
op_assign
id|ioremap
c_func
(paren
id|bases
(braket
id|current_base
)braket
dot
id|address
comma
l_int|0x2000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_continue
suffix:semicolon
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
id|check_signature
c_func
(paren
id|p
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
macro_line|#if (TDEBUG &amp; TDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-t128 : detected board.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
macro_line|#if defined(TDEBUG) &amp;&amp; (TDEBUG &amp; TDEBUG_INIT)
id|printk
c_func
(paren
l_string|&quot;scsi-t128 : base = %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
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
id|T128_IRQS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|SCSI_IRQ_NONE
)paren
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|instance-&gt;irq
comma
id|t128_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;t128&quot;
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
id|SCSI_IRQ_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|SCSI_IRQ_NONE
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
macro_line|#if defined(TDEBUG) &amp;&amp; (TDEBUG &amp; TDEBUG_INIT)
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
l_string|&quot;scsi%d : at 0x%08lx&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|SCSI_IRQ_NONE
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
id|T128_PUBLIC_RELEASE
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
DECL|function|t128_release
r_static
r_int
id|t128_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_if
c_cond
(paren
id|shost-&gt;irq
)paren
id|free_irq
c_func
(paren
id|shost-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
id|NCR5380_exit
c_func
(paren
id|shost
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;io_port
op_logical_and
id|shost-&gt;n_io_port
)paren
id|release_region
c_func
(paren
id|shost-&gt;io_port
comma
id|shost-&gt;n_io_port
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : int t128_biosparam(Disk * disk, struct block_device *dev, int *ip)&n; *&n; * Purpose : Generates a BIOS / DOS compatible H-C-S mapping for &n; *&t;the specified device / size.&n; * &n; * Inputs : size = size of device in sectors (512 bytes), dev = block device&n; *&t;major / minor, ip[] = {heads, sectors, cylinders}  &n; *&n; * Returns : always 0 (success), initializes ip&n; *&t;&n; */
multiline_comment|/* &n; * XXX Most SCSI boards use this mapping, I could be incorrect.  Some one&n; * using hard disks on a trantor should verify that this mapping corresponds&n; * to that used by the BIOS / ASPI driver by running the linux fdisk program&n; * and matching the H_C_S coordinates to what DOS uses.&n; */
DECL|function|t128_biosparam
r_int
id|t128_biosparam
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
id|bdev
comma
id|sector_t
id|capacity
comma
r_int
op_star
id|ip
)paren
(brace
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
id|capacity
op_rshift
l_int|11
suffix:semicolon
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
r_int
r_int
id|reg
op_assign
id|instance-&gt;base
op_plus
id|T_DATA_REG_OFFSET
suffix:semicolon
r_int
r_char
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|i
op_assign
id|len
suffix:semicolon
macro_line|#if 0
r_for
c_loop
(paren
suffix:semicolon
id|i
suffix:semicolon
op_decrement
id|i
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|isa_readb
c_func
(paren
id|instance-&gt;base
op_plus
id|T_STATUS_REG_OFFSET
)paren
op_amp
id|T_ST_RDY
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_while
c_loop
(paren
op_logical_neg
(paren
id|isa_readb
c_func
(paren
id|instance-&gt;base
op_plus
id|T_STATUS_REG_OFFSET
)paren
op_amp
id|T_ST_RDY
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
suffix:semicolon
op_decrement
id|i
)paren
(brace
macro_line|#endif
op_star
id|d
op_increment
op_assign
id|isa_readb
c_func
(paren
id|reg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isa_readb
c_func
(paren
id|instance-&gt;base
op_plus
id|T_STATUS_REG_OFFSET
)paren
op_amp
id|T_ST_TIM
)paren
(brace
r_int
r_char
id|tmp
suffix:semicolon
r_int
r_int
id|foo
suffix:semicolon
id|foo
op_assign
id|instance-&gt;base
op_plus
id|T_CONTROL_REG_OFFSET
suffix:semicolon
id|tmp
op_assign
id|isa_readb
c_func
(paren
id|foo
)paren
suffix:semicolon
id|isa_writeb
c_func
(paren
id|tmp
op_or
id|T_CR_CT
comma
id|foo
)paren
suffix:semicolon
id|isa_writeb
c_func
(paren
id|tmp
comma
id|foo
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
r_else
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
r_int
r_int
id|reg
op_assign
id|instance-&gt;base
op_plus
id|T_DATA_REG_OFFSET
suffix:semicolon
r_int
r_char
op_star
id|s
op_assign
id|src
suffix:semicolon
r_register
r_int
id|i
op_assign
id|len
suffix:semicolon
macro_line|#if 0
r_for
c_loop
(paren
suffix:semicolon
id|i
suffix:semicolon
op_decrement
id|i
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|isa_readb
c_func
(paren
id|instance-&gt;base
op_plus
id|T_STATUS_REG_OFFSET
)paren
op_amp
id|T_ST_RDY
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_while
c_loop
(paren
op_logical_neg
(paren
id|isa_readb
c_func
(paren
id|instance-&gt;base
op_plus
id|T_STATUS_REG_OFFSET
)paren
op_amp
id|T_ST_RDY
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
suffix:semicolon
op_decrement
id|i
)paren
(brace
macro_line|#endif
id|isa_writeb
c_func
(paren
op_star
id|s
op_increment
comma
id|reg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isa_readb
c_func
(paren
id|instance-&gt;base
op_plus
id|T_STATUS_REG_OFFSET
)paren
op_amp
id|T_ST_TIM
)paren
(brace
r_int
r_char
id|tmp
suffix:semicolon
r_int
r_int
id|foo
suffix:semicolon
id|foo
op_assign
id|instance-&gt;base
op_plus
id|T_CONTROL_REG_OFFSET
suffix:semicolon
id|tmp
op_assign
id|isa_readb
c_func
(paren
id|foo
)paren
suffix:semicolon
id|isa_writeb
c_func
(paren
id|tmp
op_or
id|T_CR_CT
comma
id|foo
)paren
suffix:semicolon
id|isa_writeb
c_func
(paren
id|tmp
comma
id|foo
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
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#include &quot;NCR5380.c&quot;
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Trantor T128/T128F/T228&quot;
comma
dot
id|detect
op_assign
id|t128_detect
comma
dot
id|release
op_assign
id|t128_release
comma
dot
id|queuecommand
op_assign
id|t128_queue_command
comma
dot
id|eh_abort_handler
op_assign
id|t128_abort
comma
dot
id|eh_bus_reset_handler
op_assign
id|t128_bus_reset
comma
dot
id|eh_host_reset_handler
op_assign
id|t128_host_reset
comma
dot
id|eh_device_reset_handler
op_assign
id|t128_device_reset
comma
dot
id|bios_param
op_assign
id|t128_biosparam
comma
dot
id|can_queue
op_assign
id|CAN_QUEUE
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
dot
id|cmd_per_lun
op_assign
id|CMD_PER_LUN
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
comma
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
