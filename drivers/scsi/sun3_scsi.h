multiline_comment|/*&n; * Sun3 SCSI stuff by Erik Verbruggen (erik@bigmama.xtdnet.nl)&n; *&n; * Sun3 DMA additions by Sam Creasey (sammy@oh.verio.com)&n; *&n; * Adapted from mac_scsinew.h:&n; */
multiline_comment|/*&n; * Cumana Generic NCR5380 driver defines&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: cumana_NCR5380.h,v $&n; */
macro_line|#ifndef SUN3_NCR5380_H
DECL|macro|SUN3_NCR5380_H
mdefine_line|#define SUN3_NCR5380_H
DECL|macro|SUN3SCSI_PUBLIC_RELEASE
mdefine_line|#define SUN3SCSI_PUBLIC_RELEASE 1
multiline_comment|/*&n; * Int: level 2 autovector&n; * IO: type 1, base 0x00140000, 5 bits phys space: A&lt;4..0&gt;&n; */
DECL|macro|IRQ_SUN3_SCSI
mdefine_line|#define IRQ_SUN3_SCSI 2
DECL|macro|IOBASE_SUN3_SCSI
mdefine_line|#define IOBASE_SUN3_SCSI 0x00140000
r_int
id|sun3scsi_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|sun3scsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|sun3scsi_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|sun3scsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|sun3scsi_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|sun3scsi_queue_command
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|sun3scsi_proc_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 2
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 16
macro_line|#endif
macro_line|#ifndef SG_TABLESIZE
DECL|macro|SG_TABLESIZE
mdefine_line|#define SG_TABLESIZE SG_NONE
macro_line|#endif
macro_line|#ifndef USE_TAGGED_QUEUING
DECL|macro|USE_TAGGED_QUEUING
mdefine_line|#define&t;USE_TAGGED_QUEUING 0
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|macro|SUN3_NCR5380
mdefine_line|#define SUN3_NCR5380 {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;name:&t;&t;&t;&quot;Sun3 NCR5380 SCSI&quot;,&t;&t;&t;&t;&bslash;&n;detect:&t;&t;&t;sun3scsi_detect,&t;&t;&t;&t;&bslash;&n;release:&t;&t;sun3scsi_release,&t;/* Release */&t;&t;&bslash;&n;info:&t;&t;&t;sun3scsi_info,&t;&t;&t;&t;&t;&bslash;&n;queuecommand:&t;&t;sun3scsi_queue_command,&t;&t;&t;&t;&bslash;&n;abort:&t;&t;&t;sun3scsi_abort,&t;&t;&t; &t;&t;&bslash;&n;reset:&t;&t;&t;sun3scsi_reset,&t;&t;&t;&t;&t;&bslash;&n;bios_param:&t;&t;scsicam_bios_param,&t;/* biosparam */&t;&t;&bslash;&n;can_queue:&t;&t;CAN_QUEUE,&t;&t;/* can queue */&t;&t;&bslash;&n;this_id:&t;&t;7,&t;&t;&t;/* id */&t;&t;&bslash;&n;sg_tablesize:&t;&t;SG_ALL,&t;&t;&t;/* sg_tablesize */&t;&bslash;&n;cmd_per_lun:&t;&t;CMD_PER_LUN,&t;&t;/* cmd per lun */&t;&bslash;&n;unchecked_isa_dma:&t;0,&t;&t;&t;/* unchecked_isa_dma */&t;&bslash;&n;use_clustering:&t;&t;DISABLE_CLUSTERING&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;        struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;        _instance = instance
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) sun3scsi_read(reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) sun3scsi_write(reg, value)
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr sun3scsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command sun3scsi_queue_command
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset sun3scsi_reset
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort sun3scsi_abort
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info sun3scsi_proc_info
DECL|macro|NCR5380_dma_xfer_len
mdefine_line|#define NCR5380_dma_xfer_len(i, cmd, phase) &bslash;&n;        sun3scsi_dma_xfer_len(cmd-&gt;SCp.this_residual,cmd,((phase) &amp; SR_IO) ? 0 : 1)
DECL|macro|NCR5380_dma_write_setup
mdefine_line|#define NCR5380_dma_write_setup(instance, data, count) sun3scsi_dma_setup(data, count, 1)
DECL|macro|NCR5380_dma_read_setup
mdefine_line|#define NCR5380_dma_read_setup(instance, data, count) sun3scsi_dma_setup(data, count, 0)
DECL|macro|NCR5380_dma_residual
mdefine_line|#define NCR5380_dma_residual sun3scsi_dma_residual
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
multiline_comment|/* additional registers - mainly DMA control regs */
multiline_comment|/* these start at regbase + 8 -- directly after the NCR regs */
DECL|struct|sun3_dma_regs
r_struct
id|sun3_dma_regs
(brace
DECL|member|vmeregs
r_int
r_int
id|vmeregs
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* unimpl vme stuff */
DECL|member|udc_data
r_int
r_int
id|udc_data
suffix:semicolon
multiline_comment|/* udc dma data reg */
DECL|member|udc_addr
r_int
r_int
id|udc_addr
suffix:semicolon
multiline_comment|/* uda dma addr reg */
DECL|member|fifo_data
r_int
r_int
id|fifo_data
suffix:semicolon
multiline_comment|/* fifo data reg, holds extra byte on&n;&t;&t;&t;&t;     odd dma reads */
DECL|member|fifo_count
r_int
r_int
id|fifo_count
suffix:semicolon
DECL|member|csr
r_int
r_int
id|csr
suffix:semicolon
multiline_comment|/* control/status reg */
)brace
suffix:semicolon
multiline_comment|/* ucd chip specific regs - live in dvma space */
DECL|struct|sun3_udc_regs
r_struct
id|sun3_udc_regs
(brace
DECL|member|rsel
r_int
r_int
id|rsel
suffix:semicolon
multiline_comment|/* select regs to load */
DECL|member|addr_hi
r_int
r_int
id|addr_hi
suffix:semicolon
multiline_comment|/* high word of addr */
DECL|member|addr_lo
r_int
r_int
id|addr_lo
suffix:semicolon
multiline_comment|/* low word */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* words to be xfer&squot;d */
DECL|member|mode_hi
r_int
r_int
id|mode_hi
suffix:semicolon
multiline_comment|/* high word of channel mode */
DECL|member|mode_lo
r_int
r_int
id|mode_lo
suffix:semicolon
multiline_comment|/* low word of channel mode */
)brace
suffix:semicolon
multiline_comment|/* addresses of the udc registers */
DECL|macro|UDC_MODE
mdefine_line|#define UDC_MODE 0x38 
DECL|macro|UDC_CSR
mdefine_line|#define UDC_CSR 0x2e /* command/status */
DECL|macro|UDC_CHN_HI
mdefine_line|#define UDC_CHN_HI 0x26 /* chain high word */
DECL|macro|UDC_CHN_LO
mdefine_line|#define UDC_CHN_LO 0x22 /* chain lo word */
DECL|macro|UDC_CURA_HI
mdefine_line|#define UDC_CURA_HI 0x1a /* cur reg A high */
DECL|macro|UDC_CURA_LO
mdefine_line|#define UDC_CURA_LO 0x0a /* cur reg A low */
DECL|macro|UDC_CURB_HI
mdefine_line|#define UDC_CURB_HI 0x12 /* cur reg B high */
DECL|macro|UDC_CURB_LO
mdefine_line|#define UDC_CURB_LO 0x02 /* cur reg B low */
DECL|macro|UDC_MODE_HI
mdefine_line|#define UDC_MODE_HI 0x56 /* mode reg high */
DECL|macro|UDC_MODE_LO
mdefine_line|#define UDC_MODE_LO 0x52 /* mode reg low */
DECL|macro|UDC_COUNT
mdefine_line|#define UDC_COUNT 0x32 /* words to xfer */
multiline_comment|/* some udc commands */
DECL|macro|UDC_RESET
mdefine_line|#define UDC_RESET 0
DECL|macro|UDC_CHN_START
mdefine_line|#define UDC_CHN_START 0xa0 /* start chain */
DECL|macro|UDC_INT_ENABLE
mdefine_line|#define UDC_INT_ENABLE 0x32 /* channel 1 int on */
multiline_comment|/* udc mode words */
DECL|macro|UDC_MODE_HIWORD
mdefine_line|#define UDC_MODE_HIWORD 0x40
DECL|macro|UDC_MODE_LSEND
mdefine_line|#define UDC_MODE_LSEND 0xc2
DECL|macro|UDC_MODE_LRECV
mdefine_line|#define UDC_MODE_LRECV 0xd2
multiline_comment|/* udc reg selections */
DECL|macro|UDC_RSEL_SEND
mdefine_line|#define UDC_RSEL_SEND 0x282
DECL|macro|UDC_RSEL_RECV
mdefine_line|#define UDC_RSEL_RECV 0x182
multiline_comment|/* bits in csr reg */
DECL|macro|CSR_DMA_ACTIVE
mdefine_line|#define CSR_DMA_ACTIVE 0x8000
DECL|macro|CSR_DMA_CONFLICT
mdefine_line|#define CSR_DMA_CONFLICT 0x4000
DECL|macro|CSR_DMA_BUSERR
mdefine_line|#define CSR_DMA_BUSERR 0x2000
DECL|macro|CSR_FIFO_EMPTY
mdefine_line|#define CSR_FIFO_EMPTY 0x400 /* fifo flushed? */
DECL|macro|CSR_SDB_INT
mdefine_line|#define CSR_SDB_INT 0x200 /* sbc interrupt pending */
DECL|macro|CSR_DMA_INT
mdefine_line|#define CSR_DMA_INT 0x100 /* dma interrupt pending */
DECL|macro|CSR_SEND
mdefine_line|#define CSR_SEND 0x8 /* 1 = send  0 = recv */
DECL|macro|CSR_FIFO
mdefine_line|#define CSR_FIFO 0x2 /* reset fifo */
DECL|macro|CSR_INTR
mdefine_line|#define CSR_INTR 0x4 /* interrupt enable */
DECL|macro|CSR_SCSI
mdefine_line|#define CSR_SCSI 0x1 
singleline_comment|// debugging printk&squot;s, taken from atari_scsi.h 
multiline_comment|/* Debugging printk definitions:&n; *&n; *  ARB  -&gt; arbitration&n; *  ASEN -&gt; auto-sense&n; *  DMA  -&gt; DMA&n; *  HSH  -&gt; PIO handshake&n; *  INF  -&gt; information transfer&n; *  INI  -&gt; initialization&n; *  INT  -&gt; interrupt&n; *  LNK  -&gt; linked commands&n; *  MAIN -&gt; NCR5380_main() control flow&n; *  NDAT -&gt; no data-out phase&n; *  NWR  -&gt; no write commands&n; *  PIO  -&gt; PIO transfers&n; *  PDMA -&gt; pseudo DMA (unused on Atari)&n; *  QU   -&gt; queues&n; *  RSL  -&gt; reselections&n; *  SEL  -&gt; selections&n; *  USL  -&gt; usleep cpde (unused on Atari)&n; *  LBS  -&gt; last byte sent (unused on Atari)&n; *  RSS  -&gt; restarting of selections&n; *  EXT  -&gt; extended messages&n; *  ABRT -&gt; aborting and resetting&n; *  TAG  -&gt; queue tag handling&n; *  MER  -&gt; merging of consec. buffers&n; *&n; */
macro_line|#if NDEBUG &amp; NDEBUG_ARBITRATION
DECL|macro|ARB_PRINTK
mdefine_line|#define ARB_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|ARB_PRINTK
mdefine_line|#define ARB_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_AUTOSENSE
DECL|macro|ASEN_PRINTK
mdefine_line|#define ASEN_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|ASEN_PRINTK
mdefine_line|#define ASEN_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_DMA
DECL|macro|DMA_PRINTK
mdefine_line|#define DMA_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|DMA_PRINTK
mdefine_line|#define DMA_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_HANDSHAKE
DECL|macro|HSH_PRINTK
mdefine_line|#define HSH_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|HSH_PRINTK
mdefine_line|#define HSH_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_INFORMATION
DECL|macro|INF_PRINTK
mdefine_line|#define INF_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|INF_PRINTK
mdefine_line|#define INF_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_INIT
DECL|macro|INI_PRINTK
mdefine_line|#define INI_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|INI_PRINTK
mdefine_line|#define INI_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_INTR
DECL|macro|INT_PRINTK
mdefine_line|#define INT_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|INT_PRINTK
mdefine_line|#define INT_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_LINKED
DECL|macro|LNK_PRINTK
mdefine_line|#define LNK_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|LNK_PRINTK
mdefine_line|#define LNK_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_MAIN
DECL|macro|MAIN_PRINTK
mdefine_line|#define MAIN_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|MAIN_PRINTK
mdefine_line|#define MAIN_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_NO_DATAOUT
DECL|macro|NDAT_PRINTK
mdefine_line|#define NDAT_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|NDAT_PRINTK
mdefine_line|#define NDAT_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_NO_WRITE
DECL|macro|NWR_PRINTK
mdefine_line|#define NWR_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|NWR_PRINTK
mdefine_line|#define NWR_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_PIO
DECL|macro|PIO_PRINTK
mdefine_line|#define PIO_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|PIO_PRINTK
mdefine_line|#define PIO_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_PSEUDO_DMA
DECL|macro|PDMA_PRINTK
mdefine_line|#define PDMA_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|PDMA_PRINTK
mdefine_line|#define PDMA_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_QUEUES
DECL|macro|QU_PRINTK
mdefine_line|#define QU_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|QU_PRINTK
mdefine_line|#define QU_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_RESELECTION
DECL|macro|RSL_PRINTK
mdefine_line|#define RSL_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|RSL_PRINTK
mdefine_line|#define RSL_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_SELECTION
DECL|macro|SEL_PRINTK
mdefine_line|#define SEL_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|SEL_PRINTK
mdefine_line|#define SEL_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_USLEEP
DECL|macro|USL_PRINTK
mdefine_line|#define USL_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|USL_PRINTK
mdefine_line|#define USL_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_LAST_BYTE_SENT
DECL|macro|LBS_PRINTK
mdefine_line|#define LBS_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|LBS_PRINTK
mdefine_line|#define LBS_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_RESTART_SELECT
DECL|macro|RSS_PRINTK
mdefine_line|#define RSS_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|RSS_PRINTK
mdefine_line|#define RSS_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_EXTENDED
DECL|macro|EXT_PRINTK
mdefine_line|#define EXT_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|EXT_PRINTK
mdefine_line|#define EXT_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_ABORT
DECL|macro|ABRT_PRINTK
mdefine_line|#define ABRT_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|ABRT_PRINTK
mdefine_line|#define ABRT_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_TAGS
DECL|macro|TAG_PRINTK
mdefine_line|#define TAG_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|TAG_PRINTK
mdefine_line|#define TAG_PRINTK(format, args...)
macro_line|#endif
macro_line|#if NDEBUG &amp; NDEBUG_MERGING
DECL|macro|MER_PRINTK
mdefine_line|#define MER_PRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG format , ## args)
macro_line|#else
DECL|macro|MER_PRINTK
mdefine_line|#define MER_PRINTK(format, args...)
macro_line|#endif
multiline_comment|/* conditional macros for NCR5380_print_{,phase,status} */
DECL|macro|NCR_PRINT
mdefine_line|#define NCR_PRINT(mask)&t;&bslash;&n;&t;((NDEBUG &amp; (mask)) ? NCR5380_print(instance) : (void)0)
DECL|macro|NCR_PRINT_PHASE
mdefine_line|#define NCR_PRINT_PHASE(mask) &bslash;&n;&t;((NDEBUG &amp; (mask)) ? NCR5380_print_phase(instance) : (void)0)
DECL|macro|NCR_PRINT_STATUS
mdefine_line|#define NCR_PRINT_STATUS(mask) &bslash;&n;&t;((NDEBUG &amp; (mask)) ? NCR5380_print_status(instance) : (void)0)
DECL|macro|NDEBUG_ANY
mdefine_line|#define NDEBUG_ANY&t;0xffffffff
macro_line|#endif /* ndef HOSTS_C */
macro_line|#endif /* SUN3_NCR5380_H */
eof
