multiline_comment|/*&n; * atari_scsi.h -- Header file for the Atari native SCSI driver&n; *&n; * Copyright 1994 Roman Hodek &lt;Roman.Hodek@informatik.uni-erlangen.de&gt;&n; *&n; * (Loosely based on the work of Robert De Vries&squot; team)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#ifndef ATARI_SCSI_H
DECL|macro|ATARI_SCSI_H
mdefine_line|#define ATARI_SCSI_H
multiline_comment|/* (I_HAVE_OVERRUNS stuff removed) */
macro_line|#ifndef ASM
r_int
id|atari_scsi_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|atari_scsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|atari_scsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|atari_scsi_queue_command
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
id|atari_scsi_reset
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|atari_scsi_proc_info
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|atari_scsi_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|atari_scsi_release
mdefine_line|#define atari_scsi_release NULL
macro_line|#endif
multiline_comment|/* The values for CMD_PER_LUN and CAN_QUEUE are somehow arbitrary. Higher&n; * values should work, too; try it! (but cmd_per_lun costs memory!) */
multiline_comment|/* But there seems to be a bug somewhere that requires CAN_QUEUE to be&n; * 2*CMD_PER_LUN. At least on a TT, no spurious timeouts seen since&n; * changed CMD_PER_LUN... */
multiline_comment|/* Note: The Falcon currently uses 8/1 setting due to unsolved problems with&n; * cmd_per_lun != 1 */
DECL|macro|ATARI_TT_CAN_QUEUE
mdefine_line|#define ATARI_TT_CAN_QUEUE&t;&t;16
DECL|macro|ATARI_TT_CMD_PER_LUN
mdefine_line|#define ATARI_TT_CMD_PER_LUN&t;&t;8
DECL|macro|ATARI_TT_SG_TABLESIZE
mdefine_line|#define ATARI_TT_SG_TABLESIZE&t;&t;SG_ALL
DECL|macro|ATARI_FALCON_CAN_QUEUE
mdefine_line|#define ATARI_FALCON_CAN_QUEUE&t;&t;8
DECL|macro|ATARI_FALCON_CMD_PER_LUN
mdefine_line|#define ATARI_FALCON_CMD_PER_LUN&t;1
DECL|macro|ATARI_FALCON_SG_TABLESIZE
mdefine_line|#define ATARI_FALCON_SG_TABLESIZE&t;SG_NONE
DECL|macro|DEFAULT_USE_TAGGED_QUEUING
mdefine_line|#define&t;DEFAULT_USE_TAGGED_QUEUING&t;0
DECL|macro|ATARI_SCSI
mdefine_line|#define ATARI_SCSI {    proc_info:         atari_scsi_proc_info,&t;&bslash;&n;&t;&t;&t;name:              &quot;Atari native SCSI&quot;,&t;&t;&bslash;&n;&t;&t;&t;detect:            atari_scsi_detect,&t;&t;&bslash;&n;&t;&t;&t;release:           atari_scsi_release,&t;&t;&bslash;&n;&t;&t;&t;info:              atari_scsi_info,&t;&t;&bslash;&n;&t;&t;&t;queuecommand:      atari_scsi_queue_command,&t;&bslash;&n;&t;&t;&t;abort:             atari_scsi_abort,&t;&t;&bslash;&n;&t;&t;&t;reset:             atari_scsi_reset,&t;&t;&bslash;&n;&t;&t;&t;can_queue:         0, /* initialized at run-time */&t;&bslash;&n;&t;&t;&t;this_id:           0, /* initialized at run-time */&t;&bslash;&n;&t;&t;&t;sg_tablesize:      0, /* initialized at run-time */&t;&bslash;&n;&t;&t;&t;cmd_per_lun:       0, /* initialized at run-time */&t;&bslash;&n;&t;&t;&t;use_clustering:&t;   DISABLE_CLUSTERING }
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define&t;NCR5380_implementation_fields&t;/* none */
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;  atari_scsi_reg_read( reg )
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) atari_scsi_reg_write( reg, value )
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr atari_scsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command atari_scsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort atari_scsi_abort
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info atari_scsi_proc_info
DECL|macro|NCR5380_dma_read_setup
mdefine_line|#define NCR5380_dma_read_setup(inst,d,c) atari_scsi_dma_setup (inst, d, c, 0)
DECL|macro|NCR5380_dma_write_setup
mdefine_line|#define NCR5380_dma_write_setup(inst,d,c) atari_scsi_dma_setup (inst, d, c, 1)
DECL|macro|NCR5380_dma_residual
mdefine_line|#define NCR5380_dma_residual(inst) atari_scsi_dma_residual( inst )
DECL|macro|NCR5380_dma_xfer_len
mdefine_line|#define&t;NCR5380_dma_xfer_len(i,cmd,phase) &bslash;&n;&t;atari_dma_xfer_len(cmd-&gt;SCp.this_residual,cmd,((phase) &amp; SR_IO) ? 0 : 1)
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
macro_line|#endif /* ndef ASM */
macro_line|#endif /* ATARI_SCSI_H */
eof
