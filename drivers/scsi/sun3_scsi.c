multiline_comment|/*&n; * Sun3 SCSI stuff by Erik Verbruggen (erik@bigmama.xtdnet.nl)&n; *&n; * Sun3 DMA routines added by Sam Creasey (sammy@sammy.net)&n; *&n; * Adapted from mac_scsinew.c:&n; */
multiline_comment|/*&n; * Generic Macintosh NCR5380 driver&n; *&n; * Copyright 1998, Michael Schmitz &lt;mschmitz@lbl.gov&gt;&n; *&n; * derived in part from:&n; */
multiline_comment|/*&n; * Generic Generic NCR5380 driver&n; *&n; * Copyright 1995, Russell King&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * This is from mac_scsi.h, but hey, maybe this is useful for Sun3 too! :)&n; *&n; * Options :&n; *&n; * PARITY - enable parity checking.  Not supported.&n; *&n; * SCSI2 - enable support for SCSI-II tagged queueing.  Untested.&n; *&n; * USLEEP - enable support for devices that don&squot;t disconnect.  Untested.&n; */
multiline_comment|/*&n; * $Log: sun3_NCR5380.c,v $&n; */
DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sun3ints.h&gt;
macro_line|#include &lt;asm/dvma.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/machines.h&gt;
multiline_comment|/* dma on! */
DECL|macro|REAL_DMA
mdefine_line|#define REAL_DMA
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;sun3_scsi.h&quot;
macro_line|#include &quot;NCR5380.h&quot;
DECL|macro|USE_WRAPPER
mdefine_line|#define USE_WRAPPER
DECL|macro|RESET_BOOT
mdefine_line|#define RESET_BOOT
DECL|macro|DRIVER_SETUP
mdefine_line|#define DRIVER_SETUP
DECL|macro|NDEBUG
mdefine_line|#define NDEBUG 0
multiline_comment|/*&n; * BUG can be used to trigger a strange code-size related hang on 2.1 kernels&n; */
macro_line|#ifdef BUG
DECL|macro|RESET_BOOT
macro_line|#undef RESET_BOOT
DECL|macro|DRIVER_SETUP
macro_line|#undef DRIVER_SETUP
macro_line|#endif
DECL|macro|SUPPORT_TAGS
macro_line|#undef SUPPORT_TAGS
DECL|macro|ENABLE_IRQ
mdefine_line|#define&t;ENABLE_IRQ()&t;enable_irq( IRQ_SUN3_SCSI ); 
r_static
r_void
id|scsi_sun3_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_static
r_inline
r_int
r_char
id|sun3scsi_read
c_func
(paren
r_int
id|reg
)paren
suffix:semicolon
r_static
r_inline
r_void
id|sun3scsi_write
c_func
(paren
r_int
id|reg
comma
r_int
id|value
)paren
suffix:semicolon
DECL|variable|setup_can_queue
r_static
r_int
id|setup_can_queue
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|setup_cmd_per_lun
r_static
r_int
id|setup_cmd_per_lun
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|setup_sg_tablesize
r_static
r_int
id|setup_sg_tablesize
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef SUPPORT_TAGS
DECL|variable|setup_use_tagged_queuing
r_static
r_int
id|setup_use_tagged_queuing
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
DECL|variable|setup_hostid
r_static
r_int
id|setup_hostid
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|sun3_dma_setup_done
r_static
id|Scsi_Cmnd
op_star
id|sun3_dma_setup_done
op_assign
l_int|NULL
suffix:semicolon
DECL|macro|AFTER_RESET_DELAY
mdefine_line|#define&t;AFTER_RESET_DELAY&t;(HZ/2)
multiline_comment|/* ms to wait after hitting dma regs */
DECL|macro|SUN3_DMA_DELAY
mdefine_line|#define SUN3_DMA_DELAY 10
multiline_comment|/* dvma buffer to allocate -- 32k should hopefully be more than sufficient */
DECL|macro|SUN3_DVMA_BUFSIZE
mdefine_line|#define SUN3_DVMA_BUFSIZE 0xe000
multiline_comment|/* minimum number of bytes to do dma on */
DECL|macro|SUN3_DMA_MINSIZE
mdefine_line|#define SUN3_DMA_MINSIZE 128
DECL|variable|sun3_scsi_regp
r_static
r_volatile
r_int
r_char
op_star
id|sun3_scsi_regp
suffix:semicolon
DECL|variable|dregs
r_static
r_volatile
r_struct
id|sun3_dma_regs
op_star
id|dregs
suffix:semicolon
DECL|variable|dmabuf
r_static
r_int
r_char
op_star
id|dmabuf
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* dma memory buffer */
DECL|variable|udc_regs
r_static
r_struct
id|sun3_udc_regs
op_star
id|udc_regs
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sun3_dma_orig_addr
r_static
r_int
r_char
op_star
id|sun3_dma_orig_addr
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sun3_dma_orig_count
r_static
r_int
r_int
id|sun3_dma_orig_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|sun3_dma_active
r_static
r_int
id|sun3_dma_active
op_assign
l_int|0
suffix:semicolon
DECL|variable|last_residual
r_static
r_int
r_int
id|last_residual
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * NCR 5380 register access functions&n; */
DECL|function|sun3scsi_read
r_static
r_inline
r_int
r_char
id|sun3scsi_read
c_func
(paren
r_int
id|reg
)paren
(brace
r_return
id|sun3_scsi_regp
(braket
id|reg
)braket
suffix:semicolon
)brace
DECL|function|sun3scsi_write
r_static
r_inline
r_void
id|sun3scsi_write
c_func
(paren
r_int
id|reg
comma
r_int
id|value
)paren
(brace
id|sun3_scsi_regp
(braket
id|reg
)braket
op_assign
id|value
suffix:semicolon
)brace
multiline_comment|/* dma controller register access functions */
DECL|function|sun3_udc_read
r_static
r_inline
r_int
r_int
id|sun3_udc_read
c_func
(paren
r_int
r_char
id|reg
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|dregs-&gt;udc_addr
op_assign
id|UDC_CSR
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
id|ret
op_assign
id|dregs-&gt;udc_data
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sun3_udc_write
r_static
r_inline
r_void
id|sun3_udc_write
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_char
id|reg
)paren
(brace
id|dregs-&gt;udc_addr
op_assign
id|reg
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
id|dregs-&gt;udc_data
op_assign
id|val
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX: status debug&n; */
DECL|variable|default_instance
r_static
r_struct
id|Scsi_Host
op_star
id|default_instance
suffix:semicolon
multiline_comment|/*&n; * Function : int sun3scsi_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : initializes mac NCR5380 driver based on the&n; *&t;command line / compile time port and irq definitions.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; *&n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n; */
DECL|function|sun3scsi_detect
r_int
id|sun3scsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_int
r_int
id|ioaddr
comma
id|iopte
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|called
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
multiline_comment|/* check that this machine has an onboard 5380 */
r_switch
c_cond
(paren
id|idprom-&gt;id_machtype
)paren
(brace
r_case
id|SM_SUN3
op_or
id|SM_3_50
suffix:colon
r_case
id|SM_SUN3
op_or
id|SM_3_60
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|called
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;Sun3 5380 SCSI&quot;
suffix:semicolon
multiline_comment|/* setup variables */
id|tpnt-&gt;can_queue
op_assign
(paren
id|setup_can_queue
OG
l_int|0
)paren
ques
c_cond
id|setup_can_queue
suffix:colon
id|CAN_QUEUE
suffix:semicolon
id|tpnt-&gt;cmd_per_lun
op_assign
(paren
id|setup_cmd_per_lun
OG
l_int|0
)paren
ques
c_cond
id|setup_cmd_per_lun
suffix:colon
id|CMD_PER_LUN
suffix:semicolon
id|tpnt-&gt;sg_tablesize
op_assign
(paren
id|setup_sg_tablesize
op_ge
l_int|0
)paren
ques
c_cond
id|setup_sg_tablesize
suffix:colon
id|SG_TABLESIZE
suffix:semicolon
r_if
c_cond
(paren
id|setup_hostid
op_ge
l_int|0
)paren
id|tpnt-&gt;this_id
op_assign
id|setup_hostid
suffix:semicolon
r_else
(brace
multiline_comment|/* use 7 as default */
id|tpnt-&gt;this_id
op_assign
l_int|7
suffix:semicolon
)brace
multiline_comment|/* Taken from Sammy&squot;s lance driver: */
multiline_comment|/* IOBASE_SUN3_SCSI can be found within the IO pmeg with some effort */
r_for
c_loop
(paren
id|ioaddr
op_assign
l_int|0xfe00000
suffix:semicolon
id|ioaddr
OL
(paren
l_int|0xfe00000
op_plus
id|SUN3_PMEG_SIZE
)paren
suffix:semicolon
id|ioaddr
op_add_assign
id|SUN3_PTE_SIZE
)paren
(brace
id|iopte
op_assign
id|sun3_get_pte
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iopte
op_amp
id|SUN3_PAGE_TYPE_IO
)paren
)paren
(brace
multiline_comment|/* this an io page? */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|iopte
op_amp
id|SUN3_PAGE_PGNUM_MASK
)paren
op_lshift
id|PAGE_SHIFT
)paren
op_eq
id|IOBASE_SUN3_SCSI
)paren
(brace
id|count
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
op_logical_neg
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No Sun3 NCR5380 found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sun3_scsi_regp
op_assign
(paren
r_int
r_char
op_star
)paren
id|ioaddr
suffix:semicolon
id|dregs
op_assign
(paren
r_struct
id|sun3_dma_regs
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|ioaddr
)paren
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|udc_regs
op_assign
id|dvma_malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sun3_udc_regs
)paren
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SUN3 Scsi couldn&squot;t allocate DVMA memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef OLDDMA
r_if
c_cond
(paren
(paren
id|dmabuf
op_assign
id|dvma_malloc_align
c_func
(paren
id|SUN3_DVMA_BUFSIZE
comma
l_int|0x10000
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SUN3 Scsi couldn&squot;t allocate DVMA memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SUPPORT_TAGS
r_if
c_cond
(paren
id|setup_use_tagged_queuing
OL
l_int|0
)paren
id|setup_use_tagged_queuing
op_assign
id|DEFAULT_USE_TAGGED_QUEUING
suffix:semicolon
macro_line|#endif
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
r_return
l_int|0
suffix:semicolon
)brace
id|default_instance
op_assign
id|instance
suffix:semicolon
id|instance-&gt;io_port
op_assign
(paren
r_int
r_int
)paren
id|ioaddr
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_SUN3_SCSI
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|instance
comma
l_int|0
)paren
suffix:semicolon
id|instance-&gt;n_io_port
op_assign
l_int|32
suffix:semicolon
(paren
(paren
r_struct
id|NCR5380_hostdata
op_star
)paren
id|instance-&gt;hostdata
)paren
op_member_access_from_pointer
id|ctrl
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|instance-&gt;irq
comma
id|scsi_sun3_intr
comma
l_int|0
comma
l_string|&quot;Sun3SCSI-5380&quot;
comma
l_int|NULL
)paren
)paren
(brace
macro_line|#ifndef REAL_DMA
id|printk
c_func
(paren
l_string|&quot;scsi%d: IRQ%d not free, interrupts disabled&bslash;n&quot;
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
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;scsi%d: IRQ%d not free, bailing out&bslash;n&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: Sun3 5380 at port %lX irq&quot;
comma
id|instance-&gt;host_no
comma
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
l_string|&quot;s disabled&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot; %d&quot;
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; options CAN_QUEUE=%d CMD_PER_LUN=%d release=%d&quot;
comma
id|instance-&gt;can_queue
comma
id|instance-&gt;cmd_per_lun
comma
id|SUN3SCSI_PUBLIC_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nscsi%d:&quot;
comma
id|instance-&gt;host_no
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
id|dregs-&gt;csr
op_assign
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
id|dregs-&gt;csr
op_assign
id|CSR_SCSI
op_or
id|CSR_FIFO
op_or
id|CSR_INTR
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
id|dregs-&gt;fifo_count
op_assign
l_int|0
suffix:semicolon
id|called
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sun3scsi_release
r_int
id|sun3scsi_release
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
(brace
r_if
c_cond
(paren
id|shpnt-&gt;irq
op_ne
id|IRQ_NONE
)paren
id|free_irq
(paren
id|shpnt-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef RESET_BOOT
multiline_comment|/*&n; * Our &squot;bus reset on boot&squot; function&n; */
DECL|function|sun3_scsi_reset_boot
r_static
r_void
id|sun3_scsi_reset_boot
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
r_int
r_int
id|end
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
multiline_comment|/*&n;&t; * Do a SCSI reset to clean up the bus during initialization. No&n;&t; * messing with the queues, interrupts, or locks necessary here.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;Sun3 SCSI: resetting the SCSI bus...&quot;
)paren
suffix:semicolon
multiline_comment|/* switch off SCSI IRQ - catch an interrupt without IRQ bit set else */
id|sun3_disable_irq
c_func
(paren
id|IRQ_SUN3_SCSI
)paren
suffix:semicolon
multiline_comment|/* get in phase */
id|NCR5380_write
c_func
(paren
id|TARGET_COMMAND_REG
comma
id|PHASE_SR_TO_TCR
c_func
(paren
id|NCR5380_read
c_func
(paren
id|STATUS_REG
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* assert RST */
id|NCR5380_write
c_func
(paren
id|INITIATOR_COMMAND_REG
comma
id|ICR_BASE
op_or
id|ICR_ASSERT_RST
)paren
suffix:semicolon
multiline_comment|/* The min. reset hold time is 25us, so 40us should be enough */
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/* reset RST and interrupt */
id|NCR5380_write
c_func
(paren
id|INITIATOR_COMMAND_REG
comma
id|ICR_BASE
)paren
suffix:semicolon
id|NCR5380_read
c_func
(paren
id|RESET_PARITY_INTERRUPT_REG
)paren
suffix:semicolon
r_for
c_loop
(paren
id|end
op_assign
id|jiffies
op_plus
id|AFTER_RESET_DELAY
suffix:semicolon
id|time_before
c_func
(paren
id|jiffies
comma
id|end
)paren
suffix:semicolon
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* switch on SCSI IRQ again */
id|sun3_enable_irq
c_func
(paren
id|IRQ_SUN3_SCSI
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; done&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sun3scsi_info
r_const
r_char
op_star
id|sun3scsi_info
(paren
r_struct
id|Scsi_Host
op_star
id|spnt
)paren
(brace
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
singleline_comment|// safe bits for the CSR
DECL|macro|CSR_GOOD
mdefine_line|#define CSR_GOOD 0x060f
DECL|function|scsi_sun3_intr
r_static
r_void
id|scsi_sun3_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|csr
op_assign
id|dregs-&gt;csr
suffix:semicolon
r_if
c_cond
(paren
id|csr
op_amp
op_complement
id|CSR_GOOD
)paren
(brace
r_if
c_cond
(paren
id|csr
op_amp
id|CSR_DMA_BUSERR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: bus error in dma&bslash;n&quot;
comma
id|default_instance-&gt;host_no
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr
op_amp
id|CSR_DMA_CONFLICT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: dma conflict&bslash;n&quot;
comma
id|default_instance-&gt;host_no
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|csr
op_amp
(paren
id|CSR_SDB_INT
op_or
id|CSR_DMA_INT
)paren
)paren
(brace
id|NCR5380_intr
c_func
(paren
id|irq
comma
id|dummy
comma
id|fp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Debug stuff - to be called on NMI, or sysrq key. Use at your own risk; &n; * reentering NCR5380_print_status seems to have ugly side effects&n; */
multiline_comment|/* this doesn&squot;t seem to get used at all -- sam */
macro_line|#if 0
r_void
id|sun3_sun3_debug
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|NCR5380_local_declare
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|default_instance
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|NCR5380_print_status
c_func
(paren
id|default_instance
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* sun3scsi_dma_setup() -- initialize the dma controller for a read/write */
DECL|function|sun3scsi_dma_setup
r_static
r_int
r_int
id|sun3scsi_dma_setup
c_func
(paren
r_void
op_star
id|data
comma
r_int
r_int
id|count
comma
r_int
id|write_flag
)paren
(brace
macro_line|#ifdef OLDDMA
r_if
c_cond
(paren
id|write_flag
)paren
(brace
id|memcpy
c_func
(paren
id|dmabuf
comma
id|data
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
id|sun3_dma_orig_addr
op_assign
id|data
suffix:semicolon
id|sun3_dma_orig_count
op_assign
id|count
suffix:semicolon
)brace
macro_line|#else
r_void
op_star
id|addr
suffix:semicolon
singleline_comment|//&t;addr = sun3_dvma_page((unsigned long)data, (unsigned long)dmabuf);
id|addr
op_assign
(paren
r_void
op_star
)paren
id|dvma_map
c_func
(paren
(paren
r_int
r_int
)paren
id|data
comma
id|count
)paren
suffix:semicolon
id|sun3_dma_orig_addr
op_assign
id|addr
suffix:semicolon
id|sun3_dma_orig_count
op_assign
id|count
suffix:semicolon
macro_line|#endif
id|dregs-&gt;fifo_count
op_assign
l_int|0
suffix:semicolon
id|sun3_udc_write
c_func
(paren
id|UDC_RESET
comma
id|UDC_CSR
)paren
suffix:semicolon
multiline_comment|/* reset fifo */
id|dregs-&gt;csr
op_and_assign
op_complement
id|CSR_FIFO
suffix:semicolon
id|dregs-&gt;csr
op_or_assign
id|CSR_FIFO
suffix:semicolon
multiline_comment|/* set direction */
r_if
c_cond
(paren
id|write_flag
)paren
(brace
id|dregs-&gt;csr
op_or_assign
id|CSR_SEND
suffix:semicolon
)brace
r_else
id|dregs-&gt;csr
op_and_assign
op_complement
id|CSR_SEND
suffix:semicolon
multiline_comment|/* byte count for fifo */
id|dregs-&gt;fifo_count
op_assign
id|count
suffix:semicolon
id|sun3_udc_write
c_func
(paren
id|UDC_RESET
comma
id|UDC_CSR
)paren
suffix:semicolon
multiline_comment|/* reset fifo */
id|dregs-&gt;csr
op_and_assign
op_complement
id|CSR_FIFO
suffix:semicolon
id|dregs-&gt;csr
op_or_assign
id|CSR_FIFO
suffix:semicolon
r_if
c_cond
(paren
id|dregs-&gt;fifo_count
op_ne
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: fifo_mismatch %04x not %04x&bslash;n&quot;
comma
id|default_instance-&gt;host_no
comma
id|dregs-&gt;fifo_count
comma
(paren
r_int
r_int
)paren
id|count
)paren
suffix:semicolon
id|NCR5380_print
c_func
(paren
id|default_instance
)paren
suffix:semicolon
)brace
multiline_comment|/* setup udc */
macro_line|#ifdef OLDDMA
id|udc_regs-&gt;addr_hi
op_assign
(paren
(paren
id|dvma_vtob
c_func
(paren
id|dmabuf
)paren
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|udc_regs-&gt;addr_lo
op_assign
(paren
id|dvma_vtob
c_func
(paren
id|dmabuf
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
macro_line|#else
id|udc_regs-&gt;addr_hi
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|addr
)paren
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|udc_regs-&gt;addr_lo
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|addr
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
macro_line|#endif
id|udc_regs-&gt;count
op_assign
id|count
op_div
l_int|2
suffix:semicolon
multiline_comment|/* count in words */
id|udc_regs-&gt;mode_hi
op_assign
id|UDC_MODE_HIWORD
suffix:semicolon
r_if
c_cond
(paren
id|write_flag
)paren
(brace
r_if
c_cond
(paren
id|count
op_amp
l_int|1
)paren
(brace
id|udc_regs-&gt;count
op_increment
suffix:semicolon
)brace
id|udc_regs-&gt;mode_lo
op_assign
id|UDC_MODE_LSEND
suffix:semicolon
id|udc_regs-&gt;rsel
op_assign
id|UDC_RSEL_SEND
suffix:semicolon
)brace
r_else
(brace
id|udc_regs-&gt;mode_lo
op_assign
id|UDC_MODE_LRECV
suffix:semicolon
id|udc_regs-&gt;rsel
op_assign
id|UDC_RSEL_RECV
suffix:semicolon
)brace
multiline_comment|/* announce location of regs block */
id|sun3_udc_write
c_func
(paren
(paren
(paren
id|dvma_vtob
c_func
(paren
id|udc_regs
)paren
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|8
)paren
comma
id|UDC_CHN_HI
)paren
suffix:semicolon
id|sun3_udc_write
c_func
(paren
(paren
id|dvma_vtob
c_func
(paren
id|udc_regs
)paren
op_amp
l_int|0xffff
)paren
comma
id|UDC_CHN_LO
)paren
suffix:semicolon
multiline_comment|/* set dma master on */
id|sun3_udc_write
c_func
(paren
l_int|0xd
comma
id|UDC_MODE
)paren
suffix:semicolon
multiline_comment|/* interrupt enable */
id|sun3_udc_write
c_func
(paren
id|UDC_INT_ENABLE
comma
id|UDC_CSR
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|sun3scsi_dma_count
r_static
r_inline
r_int
r_int
id|sun3scsi_dma_count
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
r_int
r_int
id|resid
suffix:semicolon
id|dregs-&gt;udc_addr
op_assign
l_int|0x32
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
id|resid
op_assign
id|dregs-&gt;udc_data
suffix:semicolon
id|udelay
c_func
(paren
id|SUN3_DMA_DELAY
)paren
suffix:semicolon
id|resid
op_mul_assign
l_int|2
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|resid
suffix:semicolon
)brace
DECL|function|sun3scsi_dma_residual
r_static
r_inline
r_int
r_int
id|sun3scsi_dma_residual
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
r_return
id|last_residual
suffix:semicolon
)brace
DECL|function|sun3scsi_dma_xfer_len
r_static
r_inline
r_int
r_int
id|sun3scsi_dma_xfer_len
c_func
(paren
r_int
r_int
id|wanted
comma
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|write_flag
)paren
(brace
r_if
c_cond
(paren
(paren
id|cmd-&gt;request-&gt;cmd
op_eq
l_int|0
)paren
op_logical_or
(paren
id|cmd-&gt;request-&gt;cmd
op_eq
l_int|1
)paren
)paren
(brace
r_return
id|wanted
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* clean up after our dma is done */
DECL|function|sun3scsi_dma_finish
r_static
r_int
id|sun3scsi_dma_finish
c_func
(paren
r_int
id|write_flag
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|fifo
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|sun3_dma_active
op_assign
l_int|0
suffix:semicolon
singleline_comment|// check to empty the fifo on a read
r_if
c_cond
(paren
op_logical_neg
id|write_flag
)paren
(brace
r_int
id|tmo
op_assign
l_int|200000
suffix:semicolon
multiline_comment|/* 2 sec */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|dregs-&gt;csr
op_amp
id|CSR_FIFO_EMPTY
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|tmo
op_le
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
)brace
id|count
op_assign
id|sun3scsi_dma_count
c_func
(paren
id|default_instance
)paren
suffix:semicolon
macro_line|#ifdef OLDDMA
multiline_comment|/* if we&squot;ve finished a read, copy out the data we read */
r_if
c_cond
(paren
id|sun3_dma_orig_addr
)paren
(brace
multiline_comment|/* check for residual bytes after dma end */
r_if
c_cond
(paren
id|count
op_logical_and
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
(paren
id|BASR_PHASE_MATCH
op_or
id|BASR_ACK
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: sun3_scsi_finish: read overrun baby... &quot;
comma
id|default_instance-&gt;host_no
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;basr now %02x&bslash;n&quot;
comma
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|count
suffix:semicolon
)brace
multiline_comment|/* copy in what we dma&squot;d no matter what */
id|memcpy
c_func
(paren
id|sun3_dma_orig_addr
comma
id|dmabuf
comma
id|sun3_dma_orig_count
)paren
suffix:semicolon
id|sun3_dma_orig_addr
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#else
id|fifo
op_assign
id|dregs-&gt;fifo_count
suffix:semicolon
id|last_residual
op_assign
id|fifo
suffix:semicolon
multiline_comment|/* empty bytes from the fifo which didn&squot;t make it */
r_if
c_cond
(paren
(paren
op_logical_neg
id|write_flag
)paren
op_logical_and
(paren
id|count
op_minus
id|fifo
)paren
op_eq
l_int|2
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
r_int
r_char
op_star
id|vaddr
suffix:semicolon
id|data
op_assign
id|dregs-&gt;fifo_data
suffix:semicolon
id|vaddr
op_assign
(paren
r_int
r_char
op_star
)paren
id|dvma_btov
c_func
(paren
id|sun3_dma_orig_addr
)paren
suffix:semicolon
id|vaddr
op_add_assign
(paren
id|sun3_dma_orig_count
op_minus
id|fifo
)paren
suffix:semicolon
id|vaddr
(braket
op_minus
l_int|2
)braket
op_assign
(paren
id|data
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
suffix:semicolon
id|vaddr
(braket
op_minus
l_int|1
)braket
op_assign
(paren
id|data
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
id|dvma_unmap
c_func
(paren
id|sun3_dma_orig_addr
)paren
suffix:semicolon
macro_line|#endif
id|sun3_udc_write
c_func
(paren
id|UDC_RESET
comma
id|UDC_CSR
)paren
suffix:semicolon
id|dregs-&gt;fifo_count
op_assign
l_int|0
suffix:semicolon
id|dregs-&gt;csr
op_and_assign
op_complement
id|CSR_SEND
suffix:semicolon
multiline_comment|/* reset fifo */
id|dregs-&gt;csr
op_and_assign
op_complement
id|CSR_FIFO
suffix:semicolon
id|dregs-&gt;csr
op_or_assign
id|CSR_FIFO
suffix:semicolon
id|sun3_dma_setup_done
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#include &quot;sun3_NCR5380.c&quot;
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|SUN3_NCR5380
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
