multiline_comment|/* $Id: esp.h,v 1.29 2001/12/11 04:55:47 davem Exp $&n; * esp.h:  Defines and structures for the Sparc ESP (Enhanced SCSI&n; *         Processor) driver under Linux.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ESP_H
DECL|macro|_SPARC_ESP_H
mdefine_line|#define _SPARC_ESP_H
multiline_comment|/* For dvma controller register definitions. */
macro_line|#include &lt;asm/dma.h&gt;
multiline_comment|/* The ESP SCSI controllers have their register sets in three&n; * &quot;classes&quot;:&n; *&n; * 1) Registers which are both read and write.&n; * 2) Registers which are read only.&n; * 3) Registers which are write only.&n; *&n; * Yet, they all live within the same IO space.&n; */
multiline_comment|/* All the ESP registers are one byte each and are accessed longwords&n; * apart with a big-endian ordering to the bytes.&n; */
multiline_comment|/* Access    Description              Offset */
DECL|macro|ESP_TCLOW
mdefine_line|#define ESP_TCLOW&t;0x00UL&t;&t;/* rw  Low bits of the transfer count 0x00   */
DECL|macro|ESP_TCMED
mdefine_line|#define ESP_TCMED&t;0x04UL&t;&t;/* rw  Mid bits of the transfer count 0x04   */
DECL|macro|ESP_FDATA
mdefine_line|#define ESP_FDATA&t;0x08UL&t;&t;/* rw  FIFO data bits                 0x08   */
DECL|macro|ESP_CMD
mdefine_line|#define ESP_CMD&t;&t;0x0cUL&t;&t;/* rw  SCSI command bits              0x0c   */
DECL|macro|ESP_STATUS
mdefine_line|#define ESP_STATUS&t;0x10UL&t;&t;/* ro  ESP status register            0x10   */
DECL|macro|ESP_BUSID
mdefine_line|#define ESP_BUSID&t;ESP_STATUS&t;/* wo  Bus ID for select/reselect     0x10   */
DECL|macro|ESP_INTRPT
mdefine_line|#define ESP_INTRPT&t;0x14UL&t;&t;/* ro  Kind of interrupt              0x14   */
DECL|macro|ESP_TIMEO
mdefine_line|#define ESP_TIMEO&t;ESP_INTRPT&t;/* wo  Timeout value for select/resel 0x14   */
DECL|macro|ESP_SSTEP
mdefine_line|#define ESP_SSTEP&t;0x18UL&t;&t;/* ro  Sequence step register         0x18   */
DECL|macro|ESP_STP
mdefine_line|#define ESP_STP&t;&t;ESP_SSTEP&t;/* wo  Transfer period per sync       0x18   */
DECL|macro|ESP_FFLAGS
mdefine_line|#define ESP_FFLAGS&t;0x1cUL&t;&t;/* ro  Bits of current FIFO info      0x1c   */
DECL|macro|ESP_SOFF
mdefine_line|#define ESP_SOFF&t;ESP_FFLAGS&t;/* wo  Sync offset                    0x1c   */
DECL|macro|ESP_CFG1
mdefine_line|#define ESP_CFG1&t;0x20UL&t;&t;/* rw  First configuration register   0x20   */
DECL|macro|ESP_CFACT
mdefine_line|#define ESP_CFACT&t;0x24UL&t;&t;/* wo  Clock conversion factor        0x24   */
DECL|macro|ESP_STATUS2
mdefine_line|#define ESP_STATUS2&t;ESP_CFACT&t;/* ro  HME status2 register           0x24   */
DECL|macro|ESP_CTEST
mdefine_line|#define ESP_CTEST&t;0x28UL&t;&t;/* wo  Chip test register             0x28   */
DECL|macro|ESP_CFG2
mdefine_line|#define ESP_CFG2&t;0x2cUL&t;&t;/* rw  Second configuration register  0x2c   */
DECL|macro|ESP_CFG3
mdefine_line|#define ESP_CFG3&t;0x30UL&t;&t;/* rw  Third configuration register   0x30   */
DECL|macro|ESP_TCHI
mdefine_line|#define ESP_TCHI&t;0x38UL&t;&t;/* rw  High bits of transfer count    0x38   */
DECL|macro|ESP_UID
mdefine_line|#define ESP_UID&t;&t;ESP_TCHI&t;/* ro  Unique ID code                 0x38   */
DECL|macro|FAS_RLO
mdefine_line|#define FAS_RLO&t;&t;ESP_TCHI&t;/* rw  HME extended counter           0x38   */
DECL|macro|ESP_FGRND
mdefine_line|#define ESP_FGRND&t;0x3cUL&t;&t;/* rw  Data base for fifo             0x3c   */
DECL|macro|FAS_RHI
mdefine_line|#define FAS_RHI&t;&t;ESP_FGRND&t;/* rw  HME extended counter           0x3c   */
DECL|macro|ESP_REG_SIZE
mdefine_line|#define ESP_REG_SIZE&t;0x40UL
multiline_comment|/* Various revisions of the ESP board. */
DECL|enum|esp_rev
r_enum
id|esp_rev
(brace
DECL|enumerator|esp100
id|esp100
op_assign
l_int|0x00
comma
multiline_comment|/* NCR53C90 - very broken */
DECL|enumerator|esp100a
id|esp100a
op_assign
l_int|0x01
comma
multiline_comment|/* NCR53C90A */
DECL|enumerator|esp236
id|esp236
op_assign
l_int|0x02
comma
DECL|enumerator|fas236
id|fas236
op_assign
l_int|0x03
comma
DECL|enumerator|fas100a
id|fas100a
op_assign
l_int|0x04
comma
DECL|enumerator|fast
id|fast
op_assign
l_int|0x05
comma
DECL|enumerator|fashme
id|fashme
op_assign
l_int|0x06
comma
DECL|enumerator|espunknown
id|espunknown
op_assign
l_int|0x07
)brace
suffix:semicolon
multiline_comment|/* We get one of these for each ESP probed. */
DECL|struct|esp
r_struct
id|esp
(brace
DECL|member|eregs
r_int
r_int
id|eregs
suffix:semicolon
multiline_comment|/* ESP controller registers */
DECL|member|dregs
r_int
r_int
id|dregs
suffix:semicolon
multiline_comment|/* DMA controller registers */
DECL|member|dma
r_struct
id|sbus_dma
op_star
id|dma
suffix:semicolon
multiline_comment|/* DMA controller sw state */
DECL|member|ehost
r_struct
id|Scsi_Host
op_star
id|ehost
suffix:semicolon
multiline_comment|/* Backpointer to SCSI Host */
DECL|member|sdev
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
multiline_comment|/* Pointer to SBus entry */
multiline_comment|/* ESP Configuration Registers */
DECL|member|config1
id|u8
id|config1
suffix:semicolon
multiline_comment|/* Copy of the 1st config register */
DECL|member|config2
id|u8
id|config2
suffix:semicolon
multiline_comment|/* Copy of the 2nd config register */
DECL|member|config3
id|u8
id|config3
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Copy of the 3rd config register */
multiline_comment|/* The current command we are sending to the ESP chip.  This esp_command&n;&t; * ptr needs to be mapped in DVMA area so we can send commands and read&n;&t; * from the ESP fifo without burning precious CPU cycles.  Programmed I/O&n;&t; * sucks when we have the DVMA to do it for us.  The ESP is stupid and will&n;&t; * only send out 6, 10, and 12 byte SCSI commands, others we need to send&n;&t; * one byte at a time.  esp_slowcmd being set says that we are doing one&n;&t; * of the command types ESP doesn&squot;t understand, esp_scmdp keeps track of&n;&t; * which byte we are sending, esp_scmdleft says how many bytes to go.&n;&t; */
DECL|member|esp_command
r_volatile
id|u8
op_star
id|esp_command
suffix:semicolon
multiline_comment|/* Location of command (CPU view)  */
DECL|member|esp_command_dvma
id|__u32
id|esp_command_dvma
suffix:semicolon
multiline_comment|/* Location of command (DVMA view) */
DECL|member|esp_clen
r_int
r_char
id|esp_clen
suffix:semicolon
multiline_comment|/* Length of this command */
DECL|member|esp_slowcmd
r_int
r_char
id|esp_slowcmd
suffix:semicolon
DECL|member|esp_scmdp
r_int
r_char
op_star
id|esp_scmdp
suffix:semicolon
DECL|member|esp_scmdleft
r_int
r_char
id|esp_scmdleft
suffix:semicolon
multiline_comment|/* The following are used to determine the cause of an IRQ. Upon every&n;&t; * IRQ entry we synchronize these with the hardware registers.&n;&t; */
DECL|member|ireg
id|u8
id|ireg
suffix:semicolon
multiline_comment|/* Copy of ESP interrupt register */
DECL|member|sreg
id|u8
id|sreg
suffix:semicolon
multiline_comment|/* Copy of ESP status register */
DECL|member|seqreg
id|u8
id|seqreg
suffix:semicolon
multiline_comment|/* Copy of ESP sequence step register */
DECL|member|sreg2
id|u8
id|sreg2
suffix:semicolon
multiline_comment|/* Copy of HME status2 register */
multiline_comment|/* To save register writes to the ESP, which can be expensive, we&n;&t; * keep track of the previous value that various registers had for&n;&t; * the last target we connected to.  If they are the same for the&n;&t; * current target, we skip the register writes as they are not needed.&n;&t; */
DECL|member|prev_soff
DECL|member|prev_stp
id|u8
id|prev_soff
comma
id|prev_stp
suffix:semicolon
DECL|member|prev_cfg3
DECL|member|__cache_pad
id|u8
id|prev_cfg3
comma
id|__cache_pad
suffix:semicolon
multiline_comment|/* We also keep a cache of the previous FAS/HME DMA CSR register value.  */
DECL|member|prev_hme_dmacsr
id|u32
id|prev_hme_dmacsr
suffix:semicolon
multiline_comment|/* The HME is the biggest piece of shit I have ever seen. */
DECL|member|hme_fifo_workaround_buffer
id|u8
id|hme_fifo_workaround_buffer
(braket
l_int|16
op_star
l_int|2
)braket
suffix:semicolon
DECL|member|hme_fifo_workaround_count
id|u8
id|hme_fifo_workaround_count
suffix:semicolon
multiline_comment|/* For each target we keep track of save/restore data&n;&t; * pointer information.  This needs to be updated majorly&n;&t; * when we add support for tagged queueing.  -DaveM&n;&t; */
DECL|struct|esp_pointers
r_struct
id|esp_pointers
(brace
DECL|member|saved_ptr
r_char
op_star
id|saved_ptr
suffix:semicolon
DECL|member|saved_buffer
r_struct
id|scatterlist
op_star
id|saved_buffer
suffix:semicolon
DECL|member|saved_this_residual
r_int
id|saved_this_residual
suffix:semicolon
DECL|member|saved_buffers_residual
r_int
id|saved_buffers_residual
suffix:semicolon
DECL|member|data_pointers
)brace
id|data_pointers
(braket
l_int|16
)braket
multiline_comment|/*XXX [MAX_TAGS_PER_TARGET]*/
suffix:semicolon
multiline_comment|/* Clock periods, frequencies, synchronization, etc. */
DECL|member|cfreq
r_int
r_int
id|cfreq
suffix:semicolon
multiline_comment|/* Clock frequency in HZ */
DECL|member|cfact
r_int
r_int
id|cfact
suffix:semicolon
multiline_comment|/* Clock conversion factor */
DECL|member|raw_cfact
r_int
r_int
id|raw_cfact
suffix:semicolon
multiline_comment|/* Raw copy from probing */
DECL|member|ccycle
r_int
r_int
id|ccycle
suffix:semicolon
multiline_comment|/* One ESP clock cycle */
DECL|member|ctick
r_int
r_int
id|ctick
suffix:semicolon
multiline_comment|/* One ESP clock time */
DECL|member|radelay
r_int
r_int
id|radelay
suffix:semicolon
multiline_comment|/* FAST chip req/ack delay */
DECL|member|neg_defp
r_int
r_int
id|neg_defp
suffix:semicolon
multiline_comment|/* Default negotiation period */
DECL|member|sync_defp
r_int
r_int
id|sync_defp
suffix:semicolon
multiline_comment|/* Default sync transfer period */
DECL|member|max_period
r_int
r_int
id|max_period
suffix:semicolon
multiline_comment|/* longest our period can be */
DECL|member|min_period
r_int
r_int
id|min_period
suffix:semicolon
multiline_comment|/* shortest period we can withstand */
DECL|member|next
r_struct
id|esp
op_star
id|next
suffix:semicolon
multiline_comment|/* Next ESP we probed or NULL */
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Name of ESP device from prom */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* Prom node where ESP found */
DECL|member|esp_id
r_int
id|esp_id
suffix:semicolon
multiline_comment|/* Unique per-ESP ID number */
multiline_comment|/* For slow to medium speed input clock rates we shoot for 5mb/s,&n;&t; * but for high input clock rates we try to do 10mb/s although I&n;&t; * don&squot;t think a transfer can even run that fast with an ESP even&n;&t; * with DMA2 scatter gather pipelining.&n;&t; */
DECL|macro|SYNC_DEFP_SLOW
mdefine_line|#define SYNC_DEFP_SLOW            0x32   /* 5mb/s  */
DECL|macro|SYNC_DEFP_FAST
mdefine_line|#define SYNC_DEFP_FAST            0x19   /* 10mb/s */
DECL|member|snip
r_int
r_int
id|snip
suffix:semicolon
multiline_comment|/* Sync. negotiation in progress */
DECL|member|wnip
r_int
r_int
id|wnip
suffix:semicolon
multiline_comment|/* WIDE negotiation in progress */
DECL|member|targets_present
r_int
r_int
id|targets_present
suffix:semicolon
multiline_comment|/* targets spoken to before */
DECL|member|current_transfer_size
r_int
id|current_transfer_size
suffix:semicolon
multiline_comment|/* Set at beginning of data dma */
DECL|member|espcmdlog
id|u8
id|espcmdlog
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Log of current esp cmds sent. */
DECL|member|espcmdent
id|u8
id|espcmdent
suffix:semicolon
multiline_comment|/* Current entry in esp cmd log. */
multiline_comment|/* Misc. info about this ESP */
DECL|member|erev
r_enum
id|esp_rev
id|erev
suffix:semicolon
multiline_comment|/* ESP revision */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* SBus IRQ for this ESP */
DECL|member|scsi_id
r_int
id|scsi_id
suffix:semicolon
multiline_comment|/* Who am I as initiator? */
DECL|member|scsi_id_mask
r_int
id|scsi_id_mask
suffix:semicolon
multiline_comment|/* Bitmask of &squot;me&squot;. */
DECL|member|diff
r_int
id|diff
suffix:semicolon
multiline_comment|/* Differential SCSI bus? */
DECL|member|bursts
r_int
id|bursts
suffix:semicolon
multiline_comment|/* Burst sizes our DVMA supports */
multiline_comment|/* Our command queues, only one cmd lives in the current_SC queue. */
DECL|member|issue_SC
id|Scsi_Cmnd
op_star
id|issue_SC
suffix:semicolon
multiline_comment|/* Commands to be issued */
DECL|member|current_SC
id|Scsi_Cmnd
op_star
id|current_SC
suffix:semicolon
multiline_comment|/* Who is currently working the bus */
DECL|member|disconnected_SC
id|Scsi_Cmnd
op_star
id|disconnected_SC
suffix:semicolon
multiline_comment|/* Commands disconnected from the bus */
multiline_comment|/* Message goo */
DECL|member|cur_msgout
id|u8
id|cur_msgout
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cur_msgin
id|u8
id|cur_msgin
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|prevmsgout
DECL|member|prevmsgin
id|u8
id|prevmsgout
comma
id|prevmsgin
suffix:semicolon
DECL|member|msgout_len
DECL|member|msgin_len
id|u8
id|msgout_len
comma
id|msgin_len
suffix:semicolon
DECL|member|msgout_ctr
DECL|member|msgin_ctr
id|u8
id|msgout_ctr
comma
id|msgin_ctr
suffix:semicolon
multiline_comment|/* States that we cannot keep in the per cmd structure because they&n;&t; * cannot be assosciated with any specific command.&n;&t; */
DECL|member|resetting_bus
id|u8
id|resetting_bus
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bitfield meanings for the above registers. */
multiline_comment|/* ESP config reg 1, read-write, found on all ESP chips */
DECL|macro|ESP_CONFIG1_ID
mdefine_line|#define ESP_CONFIG1_ID        0x07             /* My BUS ID bits */
DECL|macro|ESP_CONFIG1_CHTEST
mdefine_line|#define ESP_CONFIG1_CHTEST    0x08             /* Enable ESP chip tests */
DECL|macro|ESP_CONFIG1_PENABLE
mdefine_line|#define ESP_CONFIG1_PENABLE   0x10             /* Enable parity checks */
DECL|macro|ESP_CONFIG1_PARTEST
mdefine_line|#define ESP_CONFIG1_PARTEST   0x20             /* Parity test mode enabled? */
DECL|macro|ESP_CONFIG1_SRRDISAB
mdefine_line|#define ESP_CONFIG1_SRRDISAB  0x40             /* Disable SCSI reset reports */
DECL|macro|ESP_CONFIG1_SLCABLE
mdefine_line|#define ESP_CONFIG1_SLCABLE   0x80             /* Enable slow cable mode */
multiline_comment|/* ESP config reg 2, read-write, found only on esp100a+esp200+esp236 chips */
DECL|macro|ESP_CONFIG2_DMAPARITY
mdefine_line|#define ESP_CONFIG2_DMAPARITY 0x01             /* enable DMA Parity (200,236) */
DECL|macro|ESP_CONFIG2_REGPARITY
mdefine_line|#define ESP_CONFIG2_REGPARITY 0x02             /* enable reg Parity (200,236) */
DECL|macro|ESP_CONFIG2_BADPARITY
mdefine_line|#define ESP_CONFIG2_BADPARITY 0x04             /* Bad parity target abort  */
DECL|macro|ESP_CONFIG2_SCSI2ENAB
mdefine_line|#define ESP_CONFIG2_SCSI2ENAB 0x08             /* Enable SCSI-2 features (tmode only) */
DECL|macro|ESP_CONFIG2_HI
mdefine_line|#define ESP_CONFIG2_HI        0x10             /* High Impedance DREQ ???  */
DECL|macro|ESP_CONFIG2_HMEFENAB
mdefine_line|#define ESP_CONFIG2_HMEFENAB  0x10             /* HME features enable */
DECL|macro|ESP_CONFIG2_BCM
mdefine_line|#define ESP_CONFIG2_BCM       0x20             /* Enable byte-ctrl (236)   */
DECL|macro|ESP_CONFIG2_DISPINT
mdefine_line|#define ESP_CONFIG2_DISPINT   0x20             /* Disable pause irq (hme) */
DECL|macro|ESP_CONFIG2_FENAB
mdefine_line|#define ESP_CONFIG2_FENAB     0x40             /* Enable features (fas100,esp216)      */
DECL|macro|ESP_CONFIG2_SPL
mdefine_line|#define ESP_CONFIG2_SPL       0x40             /* Enable status-phase latch (esp236)   */
DECL|macro|ESP_CONFIG2_MKDONE
mdefine_line|#define ESP_CONFIG2_MKDONE    0x40             /* HME magic feature */
DECL|macro|ESP_CONFIG2_HME32
mdefine_line|#define ESP_CONFIG2_HME32     0x80             /* HME 32 extended */
DECL|macro|ESP_CONFIG2_MAGIC
mdefine_line|#define ESP_CONFIG2_MAGIC     0xe0             /* Invalid bits... */
multiline_comment|/* ESP config register 3 read-write, found only esp236+fas236+fas100a+hme chips */
DECL|macro|ESP_CONFIG3_FCLOCK
mdefine_line|#define ESP_CONFIG3_FCLOCK    0x01             /* FAST SCSI clock rate (esp100a/hme) */
DECL|macro|ESP_CONFIG3_TEM
mdefine_line|#define ESP_CONFIG3_TEM       0x01             /* Enable thresh-8 mode (esp/fas236)  */
DECL|macro|ESP_CONFIG3_FAST
mdefine_line|#define ESP_CONFIG3_FAST      0x02             /* Enable FAST SCSI     (esp100a/hme) */
DECL|macro|ESP_CONFIG3_ADMA
mdefine_line|#define ESP_CONFIG3_ADMA      0x02             /* Enable alternate-dma (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TENB
mdefine_line|#define ESP_CONFIG3_TENB      0x04             /* group2 SCSI2 support (esp100a/hme) */
DECL|macro|ESP_CONFIG3_SRB
mdefine_line|#define ESP_CONFIG3_SRB       0x04             /* Save residual byte   (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TMS
mdefine_line|#define ESP_CONFIG3_TMS       0x08             /* Three-byte msg&squot;s ok  (esp100a/hme) */
DECL|macro|ESP_CONFIG3_FCLK
mdefine_line|#define ESP_CONFIG3_FCLK      0x08             /* Fast SCSI clock rate (esp/fas236)  */
DECL|macro|ESP_CONFIG3_IDMSG
mdefine_line|#define ESP_CONFIG3_IDMSG     0x10             /* ID message checking  (esp100a/hme) */
DECL|macro|ESP_CONFIG3_FSCSI
mdefine_line|#define ESP_CONFIG3_FSCSI     0x10             /* Enable FAST SCSI     (esp/fas236)  */
DECL|macro|ESP_CONFIG3_GTM
mdefine_line|#define ESP_CONFIG3_GTM       0x20             /* group2 SCSI2 support (esp/fas236)  */
DECL|macro|ESP_CONFIG3_IDBIT3
mdefine_line|#define ESP_CONFIG3_IDBIT3    0x20             /* Bit 3 of HME SCSI-ID (hme)         */
DECL|macro|ESP_CONFIG3_TBMS
mdefine_line|#define ESP_CONFIG3_TBMS      0x40             /* Three-byte msg&squot;s ok  (esp/fas236)  */
DECL|macro|ESP_CONFIG3_EWIDE
mdefine_line|#define ESP_CONFIG3_EWIDE     0x40             /* Enable Wide-SCSI     (hme)         */
DECL|macro|ESP_CONFIG3_IMS
mdefine_line|#define ESP_CONFIG3_IMS       0x80             /* ID msg chk&squot;ng        (esp/fas236)  */
DECL|macro|ESP_CONFIG3_OBPUSH
mdefine_line|#define ESP_CONFIG3_OBPUSH    0x80             /* Push odd-byte to dma (hme)         */
multiline_comment|/* ESP command register read-write */
multiline_comment|/* Group 1 commands:  These may be sent at any point in time to the ESP&n; *                    chip.  None of them can generate interrupts &squot;cept&n; *                    the &quot;SCSI bus reset&quot; command if you have not disabled&n; *                    SCSI reset interrupts in the config1 ESP register.&n; */
DECL|macro|ESP_CMD_NULL
mdefine_line|#define ESP_CMD_NULL          0x00             /* Null command, ie. a nop */
DECL|macro|ESP_CMD_FLUSH
mdefine_line|#define ESP_CMD_FLUSH         0x01             /* FIFO Flush */
DECL|macro|ESP_CMD_RC
mdefine_line|#define ESP_CMD_RC            0x02             /* Chip reset */
DECL|macro|ESP_CMD_RS
mdefine_line|#define ESP_CMD_RS            0x03             /* SCSI bus reset */
multiline_comment|/* Group 2 commands:  ESP must be an initiator and connected to a target&n; *                    for these commands to work.&n; */
DECL|macro|ESP_CMD_TI
mdefine_line|#define ESP_CMD_TI            0x10             /* Transfer Information */
DECL|macro|ESP_CMD_ICCSEQ
mdefine_line|#define ESP_CMD_ICCSEQ        0x11             /* Initiator cmd complete sequence */
DECL|macro|ESP_CMD_MOK
mdefine_line|#define ESP_CMD_MOK           0x12             /* Message okie-dokie */
DECL|macro|ESP_CMD_TPAD
mdefine_line|#define ESP_CMD_TPAD          0x18             /* Transfer Pad */
DECL|macro|ESP_CMD_SATN
mdefine_line|#define ESP_CMD_SATN          0x1a             /* Set ATN */
DECL|macro|ESP_CMD_RATN
mdefine_line|#define ESP_CMD_RATN          0x1b             /* De-assert ATN */
multiline_comment|/* Group 3 commands:  ESP must be in the MSGOUT or MSGIN state and be connected&n; *                    to a target as the initiator for these commands to work.&n; */
DECL|macro|ESP_CMD_SMSG
mdefine_line|#define ESP_CMD_SMSG          0x20             /* Send message */
DECL|macro|ESP_CMD_SSTAT
mdefine_line|#define ESP_CMD_SSTAT         0x21             /* Send status */
DECL|macro|ESP_CMD_SDATA
mdefine_line|#define ESP_CMD_SDATA         0x22             /* Send data */
DECL|macro|ESP_CMD_DSEQ
mdefine_line|#define ESP_CMD_DSEQ          0x23             /* Discontinue Sequence */
DECL|macro|ESP_CMD_TSEQ
mdefine_line|#define ESP_CMD_TSEQ          0x24             /* Terminate Sequence */
DECL|macro|ESP_CMD_TCCSEQ
mdefine_line|#define ESP_CMD_TCCSEQ        0x25             /* Target cmd cmplt sequence */
DECL|macro|ESP_CMD_DCNCT
mdefine_line|#define ESP_CMD_DCNCT         0x27             /* Disconnect */
DECL|macro|ESP_CMD_RMSG
mdefine_line|#define ESP_CMD_RMSG          0x28             /* Receive Message */
DECL|macro|ESP_CMD_RCMD
mdefine_line|#define ESP_CMD_RCMD          0x29             /* Receive Command */
DECL|macro|ESP_CMD_RDATA
mdefine_line|#define ESP_CMD_RDATA         0x2a             /* Receive Data */
DECL|macro|ESP_CMD_RCSEQ
mdefine_line|#define ESP_CMD_RCSEQ         0x2b             /* Receive cmd sequence */
multiline_comment|/* Group 4 commands:  The ESP must be in the disconnected state and must&n; *                    not be connected to any targets as initiator for&n; *                    these commands to work.&n; */
DECL|macro|ESP_CMD_RSEL
mdefine_line|#define ESP_CMD_RSEL          0x40             /* Reselect */
DECL|macro|ESP_CMD_SEL
mdefine_line|#define ESP_CMD_SEL           0x41             /* Select w/o ATN */
DECL|macro|ESP_CMD_SELA
mdefine_line|#define ESP_CMD_SELA          0x42             /* Select w/ATN */
DECL|macro|ESP_CMD_SELAS
mdefine_line|#define ESP_CMD_SELAS         0x43             /* Select w/ATN &amp; STOP */
DECL|macro|ESP_CMD_ESEL
mdefine_line|#define ESP_CMD_ESEL          0x44             /* Enable selection */
DECL|macro|ESP_CMD_DSEL
mdefine_line|#define ESP_CMD_DSEL          0x45             /* Disable selections */
DECL|macro|ESP_CMD_SA3
mdefine_line|#define ESP_CMD_SA3           0x46             /* Select w/ATN3 */
DECL|macro|ESP_CMD_RSEL3
mdefine_line|#define ESP_CMD_RSEL3         0x47             /* Reselect3 */
multiline_comment|/* This bit enables the ESP&squot;s DMA on the SBus */
DECL|macro|ESP_CMD_DMA
mdefine_line|#define ESP_CMD_DMA           0x80             /* Do DMA? */
multiline_comment|/* ESP status register read-only */
DECL|macro|ESP_STAT_PIO
mdefine_line|#define ESP_STAT_PIO          0x01             /* IO phase bit */
DECL|macro|ESP_STAT_PCD
mdefine_line|#define ESP_STAT_PCD          0x02             /* CD phase bit */
DECL|macro|ESP_STAT_PMSG
mdefine_line|#define ESP_STAT_PMSG         0x04             /* MSG phase bit */
DECL|macro|ESP_STAT_PMASK
mdefine_line|#define ESP_STAT_PMASK        0x07             /* Mask of phase bits */
DECL|macro|ESP_STAT_TDONE
mdefine_line|#define ESP_STAT_TDONE        0x08             /* Transfer Completed */
DECL|macro|ESP_STAT_TCNT
mdefine_line|#define ESP_STAT_TCNT         0x10             /* Transfer Counter Is Zero */
DECL|macro|ESP_STAT_PERR
mdefine_line|#define ESP_STAT_PERR         0x20             /* Parity error */
DECL|macro|ESP_STAT_SPAM
mdefine_line|#define ESP_STAT_SPAM         0x40             /* Real bad error */
multiline_comment|/* This indicates the &squot;interrupt pending&squot; condition on esp236, it is a reserved&n; * bit on other revs of the ESP.&n; */
DECL|macro|ESP_STAT_INTR
mdefine_line|#define ESP_STAT_INTR         0x80             /* Interrupt */
multiline_comment|/* HME only: status 2 register */
DECL|macro|ESP_STAT2_SCHBIT
mdefine_line|#define ESP_STAT2_SCHBIT      0x01 /* Upper bits 3-7 of sstep enabled */
DECL|macro|ESP_STAT2_FFLAGS
mdefine_line|#define ESP_STAT2_FFLAGS      0x02 /* The fifo flags are now latched */
DECL|macro|ESP_STAT2_XCNT
mdefine_line|#define ESP_STAT2_XCNT        0x04 /* The transfer counter is latched */
DECL|macro|ESP_STAT2_CREGA
mdefine_line|#define ESP_STAT2_CREGA       0x08 /* The command reg is active now */
DECL|macro|ESP_STAT2_WIDE
mdefine_line|#define ESP_STAT2_WIDE        0x10 /* Interface on this adapter is wide */
DECL|macro|ESP_STAT2_F1BYTE
mdefine_line|#define ESP_STAT2_F1BYTE      0x20 /* There is one byte at top of fifo */
DECL|macro|ESP_STAT2_FMSB
mdefine_line|#define ESP_STAT2_FMSB        0x40 /* Next byte in fifo is most significant */
DECL|macro|ESP_STAT2_FEMPTY
mdefine_line|#define ESP_STAT2_FEMPTY      0x80 /* FIFO is empty */
multiline_comment|/* The status register can be masked with ESP_STAT_PMASK and compared&n; * with the following values to determine the current phase the ESP&n; * (at least thinks it) is in.  For our purposes we also add our own&n; * software &squot;done&squot; bit for our phase management engine.&n; */
DECL|macro|ESP_DOP
mdefine_line|#define ESP_DOP   (0)                                       /* Data Out  */
DECL|macro|ESP_DIP
mdefine_line|#define ESP_DIP   (ESP_STAT_PIO)                            /* Data In   */
DECL|macro|ESP_CMDP
mdefine_line|#define ESP_CMDP  (ESP_STAT_PCD)                            /* Command   */
DECL|macro|ESP_STATP
mdefine_line|#define ESP_STATP (ESP_STAT_PCD|ESP_STAT_PIO)               /* Status    */
DECL|macro|ESP_MOP
mdefine_line|#define ESP_MOP   (ESP_STAT_PMSG|ESP_STAT_PCD)              /* Message Out */
DECL|macro|ESP_MIP
mdefine_line|#define ESP_MIP   (ESP_STAT_PMSG|ESP_STAT_PCD|ESP_STAT_PIO) /* Message In */
multiline_comment|/* ESP interrupt register read-only */
DECL|macro|ESP_INTR_S
mdefine_line|#define ESP_INTR_S            0x01             /* Select w/o ATN */
DECL|macro|ESP_INTR_SATN
mdefine_line|#define ESP_INTR_SATN         0x02             /* Select w/ATN */
DECL|macro|ESP_INTR_RSEL
mdefine_line|#define ESP_INTR_RSEL         0x04             /* Reselected */
DECL|macro|ESP_INTR_FDONE
mdefine_line|#define ESP_INTR_FDONE        0x08             /* Function done */
DECL|macro|ESP_INTR_BSERV
mdefine_line|#define ESP_INTR_BSERV        0x10             /* Bus service */
DECL|macro|ESP_INTR_DC
mdefine_line|#define ESP_INTR_DC           0x20             /* Disconnect */
DECL|macro|ESP_INTR_IC
mdefine_line|#define ESP_INTR_IC           0x40             /* Illegal command given */
DECL|macro|ESP_INTR_SR
mdefine_line|#define ESP_INTR_SR           0x80             /* SCSI bus reset detected */
multiline_comment|/* Interrupt status macros */
DECL|macro|ESP_SRESET_IRQ
mdefine_line|#define ESP_SRESET_IRQ(esp)  ((esp)-&gt;intreg &amp; (ESP_INTR_SR))
DECL|macro|ESP_ILLCMD_IRQ
mdefine_line|#define ESP_ILLCMD_IRQ(esp)  ((esp)-&gt;intreg &amp; (ESP_INTR_IC))
DECL|macro|ESP_SELECT_WITH_ATN_IRQ
mdefine_line|#define ESP_SELECT_WITH_ATN_IRQ(esp)     ((esp)-&gt;intreg &amp; (ESP_INTR_SATN))
DECL|macro|ESP_SELECT_WITHOUT_ATN_IRQ
mdefine_line|#define ESP_SELECT_WITHOUT_ATN_IRQ(esp)  ((esp)-&gt;intreg &amp; (ESP_INTR_S))
DECL|macro|ESP_SELECTION_IRQ
mdefine_line|#define ESP_SELECTION_IRQ(esp)  ((ESP_SELECT_WITH_ATN_IRQ(esp)) ||         &bslash;&n;&t;&t;&t;&t; (ESP_SELECT_WITHOUT_ATN_IRQ(esp)))
DECL|macro|ESP_RESELECTION_IRQ
mdefine_line|#define ESP_RESELECTION_IRQ(esp)         ((esp)-&gt;intreg &amp; (ESP_INTR_RSEL))
multiline_comment|/* ESP sequence step register read-only */
DECL|macro|ESP_STEP_VBITS
mdefine_line|#define ESP_STEP_VBITS        0x07             /* Valid bits */
DECL|macro|ESP_STEP_ASEL
mdefine_line|#define ESP_STEP_ASEL         0x00             /* Selection&amp;Arbitrate cmplt */
DECL|macro|ESP_STEP_SID
mdefine_line|#define ESP_STEP_SID          0x01             /* One msg byte sent */
DECL|macro|ESP_STEP_NCMD
mdefine_line|#define ESP_STEP_NCMD         0x02             /* Was not in command phase */
DECL|macro|ESP_STEP_PPC
mdefine_line|#define ESP_STEP_PPC          0x03             /* Early phase chg caused cmnd&n;                                                * bytes to be lost&n;                                                */
DECL|macro|ESP_STEP_FINI4
mdefine_line|#define ESP_STEP_FINI4        0x04             /* Command was sent ok */
multiline_comment|/* Ho hum, some ESP&squot;s set the step register to this as well... */
DECL|macro|ESP_STEP_FINI5
mdefine_line|#define ESP_STEP_FINI5        0x05
DECL|macro|ESP_STEP_FINI6
mdefine_line|#define ESP_STEP_FINI6        0x06
DECL|macro|ESP_STEP_FINI7
mdefine_line|#define ESP_STEP_FINI7        0x07
multiline_comment|/* ESP chip-test register read-write */
DECL|macro|ESP_TEST_TARG
mdefine_line|#define ESP_TEST_TARG         0x01             /* Target test mode */
DECL|macro|ESP_TEST_INI
mdefine_line|#define ESP_TEST_INI          0x02             /* Initiator test mode */
DECL|macro|ESP_TEST_TS
mdefine_line|#define ESP_TEST_TS           0x04             /* Tristate test mode */
multiline_comment|/* ESP unique ID register read-only, found on fas236+fas100a only */
DECL|macro|ESP_UID_F100A
mdefine_line|#define ESP_UID_F100A         0x00             /* ESP FAS100A  */
DECL|macro|ESP_UID_F236
mdefine_line|#define ESP_UID_F236          0x02             /* ESP FAS236   */
DECL|macro|ESP_UID_REV
mdefine_line|#define ESP_UID_REV           0x07             /* ESP revision */
DECL|macro|ESP_UID_FAM
mdefine_line|#define ESP_UID_FAM           0xf8             /* ESP family   */
multiline_comment|/* ESP fifo flags register read-only */
multiline_comment|/* Note that the following implies a 16 byte FIFO on the ESP. */
DECL|macro|ESP_FF_FBYTES
mdefine_line|#define ESP_FF_FBYTES         0x1f             /* Num bytes in FIFO */
DECL|macro|ESP_FF_ONOTZERO
mdefine_line|#define ESP_FF_ONOTZERO       0x20             /* offset ctr not zero (esp100) */
DECL|macro|ESP_FF_SSTEP
mdefine_line|#define ESP_FF_SSTEP          0xe0             /* Sequence step */
multiline_comment|/* ESP clock conversion factor register write-only */
DECL|macro|ESP_CCF_F0
mdefine_line|#define ESP_CCF_F0            0x00             /* 35.01MHz - 40MHz */
DECL|macro|ESP_CCF_NEVER
mdefine_line|#define ESP_CCF_NEVER         0x01             /* Set it to this and die */
DECL|macro|ESP_CCF_F2
mdefine_line|#define ESP_CCF_F2            0x02             /* 10MHz */
DECL|macro|ESP_CCF_F3
mdefine_line|#define ESP_CCF_F3            0x03             /* 10.01MHz - 15MHz */
DECL|macro|ESP_CCF_F4
mdefine_line|#define ESP_CCF_F4            0x04             /* 15.01MHz - 20MHz */
DECL|macro|ESP_CCF_F5
mdefine_line|#define ESP_CCF_F5            0x05             /* 20.01MHz - 25MHz */
DECL|macro|ESP_CCF_F6
mdefine_line|#define ESP_CCF_F6            0x06             /* 25.01MHz - 30MHz */
DECL|macro|ESP_CCF_F7
mdefine_line|#define ESP_CCF_F7            0x07             /* 30.01MHz - 35MHz */
multiline_comment|/* HME only... */
DECL|macro|ESP_BUSID_RESELID
mdefine_line|#define ESP_BUSID_RESELID     0x10
DECL|macro|ESP_BUSID_CTR32BIT
mdefine_line|#define ESP_BUSID_CTR32BIT    0x40
DECL|macro|ESP_BUS_TIMEOUT
mdefine_line|#define ESP_BUS_TIMEOUT        275             /* In milli-seconds */
DECL|macro|ESP_TIMEO_CONST
mdefine_line|#define ESP_TIMEO_CONST       8192
DECL|macro|ESP_NEG_DEFP
mdefine_line|#define ESP_NEG_DEFP(mhz, cfact) &bslash;&n;        ((ESP_BUS_TIMEOUT * ((mhz) / 1000)) / (8192 * (cfact)))
DECL|macro|ESP_MHZ_TO_CYCLE
mdefine_line|#define ESP_MHZ_TO_CYCLE(mhertz)  ((1000000000) / ((mhertz) / 1000))
DECL|macro|ESP_TICK
mdefine_line|#define ESP_TICK(ccf, cycle)  ((7682 * (ccf) * (cycle) / 1000))
r_extern
r_int
id|esp_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|esp_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_queue
c_func
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
r_extern
r_int
id|esp_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|esp_proc_info
c_func
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
r_extern
r_int
id|esp_revoke
c_func
(paren
id|Scsi_Device
op_star
id|SDptr
)paren
suffix:semicolon
DECL|macro|SCSI_SPARC_ESP
mdefine_line|#define SCSI_SPARC_ESP {                                        &bslash;&n;&t;&t;proc_name:      &quot;esp&quot;,&t;&t;&t;&t;&bslash;&n;&t;&t;proc_info:      &amp;esp_proc_info,&t;&t;&t;&bslash;&n;&t;&t;name:           &quot;Sun ESP 100/100a/200&quot;,&t;&t;&bslash;&n;&t;&t;detect:         esp_detect,&t;&t;&t;&bslash;&n;&t;&t;revoke:&t;&t;esp_revoke,&t;&t;&t;&bslash;&n;&t;&t;info:           esp_info,&t;&t;&t;&bslash;&n;&t;&t;command:        esp_command,&t;&t;&t;&bslash;&n;&t;&t;queuecommand:   esp_queue,&t;&t;&t;&bslash;&n;&t;&t;abort:          esp_abort,&t;&t;&t;&bslash;&n;&t;&t;reset:          esp_reset,&t;&t;&t;&bslash;&n;&t;&t;can_queue:      7,&t;&t;&t;&t;&bslash;&n;&t;&t;this_id:        7,&t;&t;&t;&t;&bslash;&n;&t;&t;sg_tablesize:   SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;&t;cmd_per_lun:    1,&t;&t;&t;&t;&bslash;&n;&t;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&bslash;&n;&t;&t;highmem_io:&t;1,&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/* For our interrupt engine. */
DECL|macro|for_each_esp
mdefine_line|#define for_each_esp(esp) &bslash;&n;        for((esp) = espchain; (esp); (esp) = (esp)-&gt;next)
macro_line|#endif /* !(_SPARC_ESP_H) */
eof
