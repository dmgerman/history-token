multiline_comment|/* &n; * tms380tr.h: TI TMS380 Token Ring driver for Linux&n; *&n; * Authors:&n; * - Christoph Goos &lt;cgoos@syskonnect.de&gt;&n; * - Adam Fritzler &lt;mid@auk.cx&gt;&n; */
macro_line|#ifndef __LINUX_TMS380TR_H
DECL|macro|__LINUX_TMS380TR_H
mdefine_line|#define __LINUX_TMS380TR_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* module prototypes */
r_int
id|tms380tr_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|tms380tr_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|tms380tr_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|tmsdev_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|dmalimit
comma
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
r_void
id|tmsdev_term
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|tms380tr_wait
c_func
(paren
r_int
r_int
id|time
)paren
suffix:semicolon
DECL|macro|TMS380TR_MAX_ADAPTERS
mdefine_line|#define TMS380TR_MAX_ADAPTERS 7
DECL|macro|SEND_TIMEOUT
mdefine_line|#define SEND_TIMEOUT 10*HZ
DECL|macro|TR_RCF_LONGEST_FRAME_MASK
mdefine_line|#define TR_RCF_LONGEST_FRAME_MASK 0x0070
DECL|macro|TR_RCF_FRAME4K
mdefine_line|#define TR_RCF_FRAME4K 0x0030
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*  Bit order for adapter communication with DMA&t;&t;    */
multiline_comment|/*  --------------------------------------------------------------  */
multiline_comment|/*  Bit  8 | 9| 10| 11|| 12| 13| 14| 15|| 0| 1| 2| 3|| 4| 5| 6| 7|  */
multiline_comment|/*  --------------------------------------------------------------  */
multiline_comment|/*  The bytes in a word must be byte swapped. Also, if a double&t;    */
multiline_comment|/*  word is used for storage, then the words, as well as the bytes, */
multiline_comment|/*  must be swapped. &t;&t;&t;&t;&t;&t;    */
multiline_comment|/*  Bit order for adapter communication with DIO &t;&t;    */
multiline_comment|/*  --------------------------------------------------------------  */
multiline_comment|/*  Bit  0 | 1| 2| 3|| 4| 5| 6| 7|| 8| 9| 10| 11|| 12| 13| 14| 15|  */
multiline_comment|/*  --------------------------------------------------------------  */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Swap words of a long.                        */
DECL|macro|SWAPW
mdefine_line|#define SWAPW(x) (((x) &lt;&lt; 16) | ((x) &gt;&gt; 16))
multiline_comment|/* Get the low byte of a word.                      */
DECL|macro|LOBYTE
mdefine_line|#define LOBYTE(w)       ((unsigned char)(w))
multiline_comment|/* Get the high byte of a word.                     */
DECL|macro|HIBYTE
mdefine_line|#define HIBYTE(w)       ((unsigned char)((unsigned short)(w) &gt;&gt; 8))
multiline_comment|/* Get the low word of a long.                      */
DECL|macro|LOWORD
mdefine_line|#define LOWORD(l)       ((unsigned short)(l))
multiline_comment|/* Get the high word of a long.                     */
DECL|macro|HIWORD
mdefine_line|#define HIWORD(l)       ((unsigned short)((unsigned long)(l) &gt;&gt; 16))
multiline_comment|/* Token ring adapter I/O addresses for normal mode. */
multiline_comment|/*&n; * The SIF registers.  Common to all adapters.&n; */
multiline_comment|/* Basic SIF (SRSX = 0) */
DECL|macro|SIFDAT
mdefine_line|#define SIFDAT      &t;&t;0x00&t;/* SIF/DMA data. */
DECL|macro|SIFINC
mdefine_line|#define SIFINC      &t;&t;0x02  &t;/* IO Word data with auto increment. */
DECL|macro|SIFINH
mdefine_line|#define SIFINH      &t;&t;0x03  &t;/* IO Byte data with auto increment. */
DECL|macro|SIFADR
mdefine_line|#define SIFADR      &t;&t;0x04  &t;/* SIF/DMA Address. */
DECL|macro|SIFCMD
mdefine_line|#define SIFCMD      &t;&t;0x06  &t;/* SIF Command. */
DECL|macro|SIFSTS
mdefine_line|#define SIFSTS      &t;&t;0x06  &t;/* SIF Status. */
multiline_comment|/* &quot;Extended&quot; SIF (SRSX = 1) */
DECL|macro|SIFACL
mdefine_line|#define SIFACL      &t;&t;0x08  &t;/* SIF Adapter Control Register. */
DECL|macro|SIFADD
mdefine_line|#define SIFADD      &t;&t;0x0a &t;/* SIF/DMA Address. -- 0x0a */
DECL|macro|SIFADX
mdefine_line|#define SIFADX      &t;&t;0x0c     /* 0x0c */
DECL|macro|DMALEN
mdefine_line|#define DMALEN      &t;&t;0x0e &t;/* SIF DMA length. -- 0x0e */
multiline_comment|/*&n; * POS Registers.  Only for ISA Adapters.&n; */
DECL|macro|POSREG
mdefine_line|#define POSREG      &t;&t;0x10 &t;/* Adapter Program Option Select (POS)&n;&t;&t;&t; &t;&t; * Register: base IO address + 16 byte.&n;&t;&t;&t; &t;&t; */
DECL|macro|POSREG_2
mdefine_line|#define POSREG_2    &t;&t;24L &t;/* only for TR4/16+ adapter&n;&t;&t;&t; &t;&t; * base IO address + 24 byte. -- 0x18&n;&t;&t;&t; &t;&t; */
multiline_comment|/* SIFCMD command codes (high-low) */
DECL|macro|CMD_INTERRUPT_ADAPTER
mdefine_line|#define CMD_INTERRUPT_ADAPTER   0x8000  /* Cause internal adapter interrupt */
DECL|macro|CMD_ADAPTER_RESET
mdefine_line|#define CMD_ADAPTER_RESET   &t;0x4000  /* Hardware reset of adapter */
DECL|macro|CMD_SSB_CLEAR
mdefine_line|#define CMD_SSB_CLEAR&t;&t;0x2000  /* Acknowledge to adapter to&n;&t;&t;&t;&t;&t; * system interrupts.&n;&t;&t;&t;&t;&t; */
DECL|macro|CMD_EXECUTE
mdefine_line|#define CMD_EXECUTE&t;&t;0x1000&t;/* Execute SCB command */
DECL|macro|CMD_SCB_REQUEST
mdefine_line|#define CMD_SCB_REQUEST&t;&t;0x0800  /* Request adapter to interrupt&n;&t;&t;&t;&t;&t; * system when SCB is available for&n;&t;&t;&t;&t;&t; * another command.&n;&t;&t;&t;&t;&t; */
DECL|macro|CMD_RX_CONTINUE
mdefine_line|#define CMD_RX_CONTINUE&t;&t;0x0400  /* Continue receive after odd pointer&n;&t;&t;&t;&t;&t; * stop. (odd pointer receive method)&n;&t;&t;&t;&t;&t; */
DECL|macro|CMD_RX_VALID
mdefine_line|#define CMD_RX_VALID&t;&t;0x0200  /* Now actual RPL is valid. */
DECL|macro|CMD_TX_VALID
mdefine_line|#define CMD_TX_VALID&t;&t;0x0100  /* Now actual TPL is valid. (valid&n;&t;&t;&t;&t;&t; * bit receive/transmit method)&n;&t;&t;&t;&t;&t; */
DECL|macro|CMD_SYSTEM_IRQ
mdefine_line|#define CMD_SYSTEM_IRQ&t;&t;0x0080  /* Adapter-to-attached-system&n;&t;&t;&t;&t;&t; * interrupt is reset.&n;&t;&t;&t;&t;&t; */
DECL|macro|CMD_CLEAR_SYSTEM_IRQ
mdefine_line|#define CMD_CLEAR_SYSTEM_IRQ&t;0x0080&t;/* Clear SYSTEM_INTERRUPT bit.&n;&t;&t;&t;&t;&t; * (write: 1=ignore, 0=reset)&n;&t;&t;&t;&t;&t; */
DECL|macro|EXEC_SOFT_RESET
mdefine_line|#define EXEC_SOFT_RESET&t;&t;0xFF00  /* adapter soft reset. (restart&n;&t;&t;&t;&t;&t; * adapter after hardware reset)&n;&t;&t;&t;&t;&t; */
multiline_comment|/* ACL commands (high-low) */
DECL|macro|ACL_SWHLDA
mdefine_line|#define ACL_SWHLDA&t;&t;0x0800  /* Software hold acknowledge. */
DECL|macro|ACL_SWDDIR
mdefine_line|#define ACL_SWDDIR&t;&t;0x0400  /* Data transfer direction. */
DECL|macro|ACL_SWHRQ
mdefine_line|#define ACL_SWHRQ&t;&t;0x0200  /* Pseudo DMA operation. */
DECL|macro|ACL_PSDMAEN
mdefine_line|#define ACL_PSDMAEN&t;&t;0x0100  /* Enable pseudo system DMA. */
DECL|macro|ACL_ARESET
mdefine_line|#define ACL_ARESET&t;&t;0x0080  /* Adapter hardware reset command.&n;&t;&t;&t;&t;&t; * (held in reset condition as&n;&t;&t;&t;&t;&t; * long as bit is set)&n;&t;&t;&t;&t;&t; */
DECL|macro|ACL_CPHALT
mdefine_line|#define ACL_CPHALT&t;&t;0x0040  /* Communication processor halt.&n;&t;&t;&t;&t;&t; * (can only be set while ACL_ARESET&n;&t;&t;&t;&t;&t; * bit is set; prevents adapter&n;&t;&t;&t;&t;&t; * processor from executing code while&n;&t;&t;&t;&t;&t; * downloading firmware)&n;&t;&t;&t;&t;&t; */
DECL|macro|ACL_BOOT
mdefine_line|#define ACL_BOOT&t;&t;0x0020
DECL|macro|ACL_SINTEN
mdefine_line|#define ACL_SINTEN&t;&t;0x0008  /* System interrupt enable/disable&n;&t;&t;&t;&t;&t; * (1/0): can be written if ACL_ARESET&n;&t;&t;&t;&t;&t; * is zero.&n;&t;&t;&t;&t;&t; */
DECL|macro|ACL_PEN
mdefine_line|#define ACL_PEN                 0x0004
DECL|macro|ACL_NSELOUT0
mdefine_line|#define ACL_NSELOUT0            0x0002 
DECL|macro|ACL_NSELOUT1
mdefine_line|#define ACL_NSELOUT1            0x0001&t;/* NSELOUTx have a card-specific&n;&t;&t;&t;&t;&t; * meaning for setting ring speed.&n;&t;&t;&t;&t;&t; */
DECL|macro|PS_DMA_MASK
mdefine_line|#define PS_DMA_MASK&t;&t;(ACL_SWHRQ | ACL_PSDMAEN)
multiline_comment|/* SIFSTS register return codes (high-low) */
DECL|macro|STS_SYSTEM_IRQ
mdefine_line|#define STS_SYSTEM_IRQ&t;&t;0x0080&t;/* Adapter-to-attached-system&n;&t;&t;&t;&t;&t; * interrupt is valid.&n;&t;&t;&t;&t;&t; */
DECL|macro|STS_INITIALIZE
mdefine_line|#define STS_INITIALIZE&t;&t;0x0040  /* INITIALIZE status. (ready to&n;&t;&t;&t;&t;&t; * initialize)&n;&t;&t;&t;&t;&t; */
DECL|macro|STS_TEST
mdefine_line|#define STS_TEST&t;&t;0x0020  /* TEST status. (BUD not completed) */
DECL|macro|STS_ERROR
mdefine_line|#define STS_ERROR&t;&t;0x0010  /* ERROR status. (unrecoverable&n;&t;&t;&t;&t;&t; * HW error occurred)&n;&t;&t;&t;&t;&t; */
DECL|macro|STS_MASK
mdefine_line|#define STS_MASK&t;&t;0x00F0  /* Mask interesting status bits. */
DECL|macro|STS_ERROR_MASK
mdefine_line|#define STS_ERROR_MASK&t;&t;0x000F  /* Get Error Code by masking the&n;&t;&t;&t;&t;&t; * interrupt code bits.&n;&t;&t;&t;&t;&t; */
DECL|macro|ADAPTER_INT_PTRS
mdefine_line|#define ADAPTER_INT_PTRS&t;0x0A00  /* Address offset of adapter internal&n;&t;&t;&t;&t;&t; * pointers 01:0a00 (high-low) have to&n;&t;&t;&t;&t;&t; * be read after init and before open.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* Interrupt Codes (only MAC IRQs) */
DECL|macro|STS_IRQ_ADAPTER_CHECK
mdefine_line|#define STS_IRQ_ADAPTER_CHECK&t;0x0000&t;/* unrecoverable hardware or&n;&t;&t;&t;&t;&t; * software error.&n;&t;&t;&t;&t;&t; */ 
DECL|macro|STS_IRQ_RING_STATUS
mdefine_line|#define STS_IRQ_RING_STATUS&t;0x0004  /* SSB is updated with ring status. */
DECL|macro|STS_IRQ_LLC_STATUS
mdefine_line|#define STS_IRQ_LLC_STATUS&t;0x0005&t;/* Not used in MAC-only microcode */
DECL|macro|STS_IRQ_SCB_CLEAR
mdefine_line|#define STS_IRQ_SCB_CLEAR&t;0x0006&t;/* SCB clear, following an&n;&t;&t;&t;&t;&t; * SCB_REQUEST IRQ.&n;&t;&t;&t;&t;&t; */
DECL|macro|STS_IRQ_TIMER
mdefine_line|#define STS_IRQ_TIMER&t;&t;0x0007&t;/* Not normally used in MAC ucode */
DECL|macro|STS_IRQ_COMMAND_STATUS
mdefine_line|#define STS_IRQ_COMMAND_STATUS&t;0x0008&t;/* SSB is updated with command &n;&t;&t;&t;&t;&t; * status.&n;&t;&t;&t;&t;&t; */ 
DECL|macro|STS_IRQ_RECEIVE_STATUS
mdefine_line|#define STS_IRQ_RECEIVE_STATUS&t;0x000A&t;/* SSB is updated with receive&n;&t;&t;&t;&t;&t; * status.&n;&t;&t;&t;&t;&t; */
DECL|macro|STS_IRQ_TRANSMIT_STATUS
mdefine_line|#define STS_IRQ_TRANSMIT_STATUS&t;0x000C&t;/* SSB is updated with transmit&n;                                         * status&n;&t;&t;&t;&t;&t; */
DECL|macro|STS_IRQ_RECEIVE_PENDING
mdefine_line|#define STS_IRQ_RECEIVE_PENDING&t;0x000E&t;/* Not used in MAC-only microcode */
DECL|macro|STS_IRQ_MASK
mdefine_line|#define STS_IRQ_MASK&t;&t;0x000F&t;/* = STS_ERROR_MASK. */
multiline_comment|/* TRANSMIT_STATUS completion code: (SSB.Parm[0]) */
DECL|macro|COMMAND_COMPLETE
mdefine_line|#define COMMAND_COMPLETE&t;0x0080&t;/* TRANSMIT command completed&n;                                         * (avoid this!) issue another transmit&n;&t;&t;&t;&t;&t; * to send additional frames.&n;&t;&t;&t;&t;&t; */
DECL|macro|FRAME_COMPLETE
mdefine_line|#define FRAME_COMPLETE&t;&t;0x0040&t;/* Frame has been transmitted;&n;&t;&t;&t;&t;&t; * INTERRUPT_FRAME bit was set in the&n;&t;&t;&t;&t;&t; * CSTAT request; indication of possibly&n;&t;&t;&t;&t;&t; * more than one frame transmissions!&n;&t;&t;&t;&t;&t; * SSB.Parm[0-1]: 32 bit pointer to&n;&t;&t;&t;&t;&t; * TPL of last frame.&n;&t;&t;&t;&t;&t; */
DECL|macro|LIST_ERROR
mdefine_line|#define LIST_ERROR&t;&t;0x0020&t;/* Error in one of the TPLs that&n;&t;&t;&t;&t;&t; * compose the frame; TRANSMIT&n;&t;&t;&t;&t;&t; * terminated; Parm[1-2]: 32bit pointer&n;&t;&t;&t;&t;&t; * to TPL which starts the error&n;&t;&t;&t;&t;&t; * frame; error details in bits 8-13.&n;&t;&t;&t;&t;&t; * (14?)&n;&t;&t;&t;&t;&t; */
DECL|macro|FRAME_SIZE_ERROR
mdefine_line|#define FRAME_SIZE_ERROR&t;0x8000&t;/* FRAME_SIZE does not equal the sum of&n;&t;&t;&t;&t;&t; * the valid DATA_COUNT fields;&n;&t;&t;&t;&t;&t; * FRAME_SIZE less than header plus&n;&t;&t;&t;&t;&t; * information field. (15 bytes +&n;&t;&t;&t;&t;&t; * routing field) Or if FRAME_SIZE&n;&t;&t;&t;&t;&t; * was specified as zero in one list.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_THRESHOLD
mdefine_line|#define TX_THRESHOLD&t;&t;0x4000&t;/* FRAME_SIZE greater than (BUFFER_SIZE&n;&t;&t;&t;&t;&t; * - 9) * TX_BUF_MAX.&n;&t;&t;&t;&t;&t; */
DECL|macro|ODD_ADDRESS
mdefine_line|#define ODD_ADDRESS&t;&t;0x2000&t;/* Odd forward pointer value is&n;&t;&t;&t;&t;&t; * read on a list without END_FRAME&n;&t;&t;&t;&t;&t; * indication.&n;&t;&t;&t;&t;&t; */
DECL|macro|FRAME_ERROR
mdefine_line|#define FRAME_ERROR&t;&t;0x1000&t;/* START_FRAME bit (not) anticipated,&n;&t;&t;&t;&t;&t; * but (not) set.&n;&t;&t;&t;&t;&t; */
DECL|macro|ACCESS_PRIORITY_ERROR
mdefine_line|#define ACCESS_PRIORITY_ERROR&t;0x0800&t;/* Access priority requested has not&n;&t;&t;&t;&t;&t; * been allowed.&n;&t;&t;&t;&t;&t; */
DECL|macro|UNENABLED_MAC_FRAME
mdefine_line|#define UNENABLED_MAC_FRAME&t;0x0400&t;/* MAC frame has source class of zero&n;&t;&t;&t;&t;&t; * or MAC frame PCF ATTN field is&n;&t;&t;&t;&t;&t; * greater than one.&n;&t;&t;&t;&t;&t; */
DECL|macro|ILLEGAL_FRAME_FORMAT
mdefine_line|#define ILLEGAL_FRAME_FORMAT&t;0x0200&t;/* Bit 0 or FC field was set to one. */
multiline_comment|/*&n; * Since we need to support some functions even if the adapter is in a&n; * CLOSED state, we have a (pseudo-) command queue which holds commands&n; * that are outstandig to be executed.&n; *&n; * Each time a command completes, an interrupt occurs and the next&n; * command is executed. The command queue is actually a simple word with &n; * a bit for each outstandig command. Therefore the commands will not be&n; * executed in the order they have been queued.&n; *&n; * The following defines the command code bits and the command queue:&n; */
DECL|macro|OC_OPEN
mdefine_line|#define OC_OPEN&t;&t;&t;0x0001&t;/* OPEN command */
DECL|macro|OC_TRANSMIT
mdefine_line|#define OC_TRANSMIT&t;&t;0x0002&t;/* TRANSMIT command */
DECL|macro|OC_TRANSMIT_HALT
mdefine_line|#define OC_TRANSMIT_HALT&t;0x0004&t;/* TRANSMIT_HALT command */
DECL|macro|OC_RECEIVE
mdefine_line|#define OC_RECEIVE&t;&t;0x0008&t;/* RECEIVE command */
DECL|macro|OC_CLOSE
mdefine_line|#define OC_CLOSE&t;&t;0x0010&t;/* CLOSE command */
DECL|macro|OC_SET_GROUP_ADDR
mdefine_line|#define OC_SET_GROUP_ADDR&t;0x0020&t;/* SET_GROUP_ADDR command */
DECL|macro|OC_SET_FUNCT_ADDR
mdefine_line|#define OC_SET_FUNCT_ADDR&t;0x0040&t;/* SET_FUNCT_ADDR command */
DECL|macro|OC_READ_ERROR_LOG
mdefine_line|#define OC_READ_ERROR_LOG&t;0x0080&t;/* READ_ERROR_LOG command */
DECL|macro|OC_READ_ADAPTER
mdefine_line|#define OC_READ_ADAPTER&t;&t;0x0100&t;/* READ_ADAPTER command */
DECL|macro|OC_MODIFY_OPEN_PARMS
mdefine_line|#define OC_MODIFY_OPEN_PARMS&t;0x0400&t;/* MODIFY_OPEN_PARMS command */
DECL|macro|OC_RESTORE_OPEN_PARMS
mdefine_line|#define OC_RESTORE_OPEN_PARMS&t;0x0800&t;/* RESTORE_OPEN_PARMS command */
DECL|macro|OC_SET_FIRST_16_GROUP
mdefine_line|#define OC_SET_FIRST_16_GROUP&t;0x1000&t;/* SET_FIRST_16_GROUP command */
DECL|macro|OC_SET_BRIDGE_PARMS
mdefine_line|#define OC_SET_BRIDGE_PARMS&t;0x2000&t;/* SET_BRIDGE_PARMS command */
DECL|macro|OC_CONFIG_BRIDGE_PARMS
mdefine_line|#define OC_CONFIG_BRIDGE_PARMS&t;0x4000&t;/* CONFIG_BRIDGE_PARMS command */
DECL|macro|OPEN
mdefine_line|#define OPEN&t;&t;&t;0x0300&t;/* C: open command. S: completion. */
DECL|macro|TRANSMIT
mdefine_line|#define TRANSMIT&t;&t;0x0400&t;/* C: transmit command. S: completion&n;&t;&t;&t;&t;&t; * status. (reject: COMMAND_REJECT if&n;&t;&t;&t;&t;&t; * adapter not opened, TRANSMIT already&n;&t;&t;&t;&t;&t; * issued or address passed in the SCB&n;&t;&t;&t;&t;&t; * not word aligned)&n;&t;&t;&t;&t;&t; */
DECL|macro|TRANSMIT_HALT
mdefine_line|#define TRANSMIT_HALT&t;&t;0x0500&t;/* C: interrupt TX TPL chain; if no&n;&t;&t;&t;&t;&t; * TRANSMIT command issued, the command&n;&t;&t;&t;&t;&t; * is ignored (completion with TRANSMIT&n;&t;&t;&t;&t;&t; * status (0x0400)!)&n;&t;&t;&t;&t;&t; */
DECL|macro|RECEIVE
mdefine_line|#define RECEIVE&t;&t;&t;0x0600&t;/* C: receive command. S: completion&n;&t;&t;&t;&t;&t; * status. (reject: COMMAND_REJECT if&n;&t;&t;&t;&t;&t; * adapter not opened, RECEIVE already&n;&t;&t;&t;&t;&t; * issued or address passed in the SCB &n;&t;&t;&t;&t;&t; * not word aligned)&n;&t;&t;&t;&t;&t; */
DECL|macro|CLOSE
mdefine_line|#define CLOSE&t;&t;&t;0x0700&t;/* C: close adapter. S: completion.&n;&t;&t;&t;&t;&t; * (COMMAND_REJECT if adapter not open)&n;&t;&t;&t;&t;&t; */
DECL|macro|SET_GROUP_ADDR
mdefine_line|#define SET_GROUP_ADDR&t;&t;0x0800&t;/* C: alter adapter group address after&n;&t;&t;&t;&t;&t; * OPEN. S: completion. (COMMAND_REJECT&n;&t;&t;&t;&t;&t; * if adapter not open)&n;&t;&t;&t;&t;&t; */
DECL|macro|SET_FUNCT_ADDR
mdefine_line|#define SET_FUNCT_ADDR&t;&t;0x0900&t;/* C: alter adapter functional address&n;&t;&t;&t;&t;&t; * after OPEN. S: completion.&n;&t;&t;&t;&t;&t; * (COMMAND_REJECT if adapter not open)&n;&t;&t;&t;&t;&t; */
DECL|macro|READ_ERROR_LOG
mdefine_line|#define READ_ERROR_LOG&t;&t;0x0A00&t;/* C: read adapter error counters.&n;&t;&t;&t;&t;&t; * S: completion. (command ignored&n;&t;&t;&t;&t;&t; * if adapter not open!)&n;&t;&t;&t;&t;&t; */
DECL|macro|READ_ADAPTER
mdefine_line|#define READ_ADAPTER&t;&t;0x0B00&t;/* C: read data from adapter memory.&n;&t;&t;&t;&t;&t; * (important: after init and before&n;&t;&t;&t;&t;&t; * open!) S: completion. (ADAPTER_CHECK&n;&t;&t;&t;&t;&t; * interrupt if undefined storage area&n;&t;&t;&t;&t;&t; * read)&n;&t;&t;&t;&t;&t; */
DECL|macro|MODIFY_OPEN_PARMS
mdefine_line|#define MODIFY_OPEN_PARMS&t;0x0D00&t;/* C: modify some adapter operational&n;&t;&t;&t;&t;&t; * parameters. (bit correspondend to&n;&t;&t;&t;&t;&t; * WRAP_INTERFACE is ignored)&n;&t;&t;&t;&t;&t; * S: completion. (reject: &n;&t;&t;&t;&t;&t; * COMMAND_REJECT)&n;&t;&t;&t;&t;&t; */
DECL|macro|RESTORE_OPEN_PARMS
mdefine_line|#define RESTORE_OPEN_PARMS&t;0x0E00&t;/* C: modify some adapter operational&n;&t;&t;&t;&t;&t; * parameters. (bit correspondend&n;&t;&t;&t;&t;&t; * to WRAP_INTERFACE is ignored)&n;&t;&t;&t;&t;&t; * S: completion. (reject:&n;&t;&t;&t;&t;&t; * COMMAND_REJECT)&n;&t;&t;&t;&t;&t; */
DECL|macro|SET_FIRST_16_GROUP
mdefine_line|#define SET_FIRST_16_GROUP&t;0x0F00&t;/* C: alter the first two bytes in&n;&t;&t;&t;&t;&t; * adapter group address.&n;&t;&t;&t;&t;&t; * S: completion. (reject:&n;&t;&t;&t;&t;&t; * COMMAND_REJECT)&n;&t;&t;&t;&t;&t; */
DECL|macro|SET_BRIDGE_PARMS
mdefine_line|#define SET_BRIDGE_PARMS&t;0x1000&t;/* C: values and conditions for the&n;&t;&t;&t;&t;&t; * adapter hardware to use when frames&n;&t;&t;&t;&t;&t; * are copied for forwarding.&n;&t;&t;&t;&t;&t; * S: completion. (reject:&n;&t;&t;&t;&t;&t; * COMMAND_REJECT)&n;&t;&t;&t;&t;&t; */
DECL|macro|CONFIG_BRIDGE_PARMS
mdefine_line|#define CONFIG_BRIDGE_PARMS&t;0x1100&t;/* C: ..&n;&t;&t;&t;&t;&t; * S: completion. (reject:&n;&t;&t;&t;&t;&t; * COMMAND_REJECT)&n;&t;&t;&t;&t;&t; */
DECL|macro|SPEED_4
mdefine_line|#define SPEED_4&t;&t;&t;4
DECL|macro|SPEED_16
mdefine_line|#define SPEED_16&t;&t;16&t;/* Default transmission speed  */
multiline_comment|/* Initialization Parameter Block (IPB); word alignment necessary! */
DECL|macro|BURST_SIZE
mdefine_line|#define BURST_SIZE&t;0x0018&t;/* Default burst size */
DECL|macro|BURST_MODE
mdefine_line|#define BURST_MODE&t;0x9F00&t;/* Burst mode enable */
DECL|macro|DMA_RETRIES
mdefine_line|#define DMA_RETRIES&t;0x0505&t;/* Magic DMA retry number... */
DECL|macro|CYCLE_TIME
mdefine_line|#define CYCLE_TIME&t;3&t;/* Default AT-bus cycle time: 500 ns&n;&t;&t;&t;&t; * (later adapter version: fix  cycle time!)&n;&t;&t;&t;&t; */
DECL|macro|LINE_SPEED_BIT
mdefine_line|#define LINE_SPEED_BIT&t;0x80
multiline_comment|/* Macro definition for the wait function. */
DECL|macro|ONE_SECOND_TICKS
mdefine_line|#define ONE_SECOND_TICKS&t;1000000
DECL|macro|HALF_SECOND
mdefine_line|#define HALF_SECOND&t;&t;(ONE_SECOND_TICKS / 2)
DECL|macro|ONE_SECOND
mdefine_line|#define ONE_SECOND&t;&t;(ONE_SECOND_TICKS)
DECL|macro|TWO_SECONDS
mdefine_line|#define TWO_SECONDS&t;&t;(ONE_SECOND_TICKS * 2)
DECL|macro|THREE_SECONDS
mdefine_line|#define THREE_SECONDS&t;&t;(ONE_SECOND_TICKS * 3)
DECL|macro|FOUR_SECONDS
mdefine_line|#define FOUR_SECONDS&t;&t;(ONE_SECOND_TICKS * 4)
DECL|macro|FIVE_SECONDS
mdefine_line|#define FIVE_SECONDS&t;&t;(ONE_SECOND_TICKS * 5)
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE &t;&t;2048&t;/* Buffers on Adapter */
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|Init_Options
r_int
r_int
id|Init_Options
suffix:semicolon
multiline_comment|/* Initialize with burst mode;&n;&t;&t;&t;&t;&t; * LLC disabled. (MAC only)&n;&t;&t;&t;&t;&t; */
multiline_comment|/* Interrupt vectors the adapter places on attached system bus. */
DECL|member|CMD_Status_IV
id|u_int8_t
id|CMD_Status_IV
suffix:semicolon
multiline_comment|/* Interrupt vector: command status. */
DECL|member|TX_IV
id|u_int8_t
id|TX_IV
suffix:semicolon
multiline_comment|/* Interrupt vector: transmit. */
DECL|member|RX_IV
id|u_int8_t
id|RX_IV
suffix:semicolon
multiline_comment|/* Interrupt vector: receive. */
DECL|member|Ring_Status_IV
id|u_int8_t
id|Ring_Status_IV
suffix:semicolon
multiline_comment|/* Interrupt vector: ring status. */
DECL|member|SCB_Clear_IV
id|u_int8_t
id|SCB_Clear_IV
suffix:semicolon
multiline_comment|/* Interrupt vector: SCB clear. */
DECL|member|Adapter_CHK_IV
id|u_int8_t
id|Adapter_CHK_IV
suffix:semicolon
multiline_comment|/* Interrupt vector: adapter check. */
DECL|member|RX_Burst_Size
id|u_int16_t
id|RX_Burst_Size
suffix:semicolon
multiline_comment|/* Max. number of transfer cycles. */
DECL|member|TX_Burst_Size
id|u_int16_t
id|TX_Burst_Size
suffix:semicolon
multiline_comment|/* During DMA burst; even value! */
DECL|member|DMA_Abort_Thrhld
id|u_int16_t
id|DMA_Abort_Thrhld
suffix:semicolon
multiline_comment|/* Number of DMA retries. */
DECL|member|SCB_Addr
id|u_int32_t
id|SCB_Addr
suffix:semicolon
multiline_comment|/* SCB address: even, word aligned, high-low */
DECL|member|SSB_Addr
id|u_int32_t
id|SSB_Addr
suffix:semicolon
multiline_comment|/* SSB address: even, word aligned, high-low */
DECL|typedef|IPB
DECL|typedef|IPB_Ptr
)brace
id|IPB
comma
op_star
id|IPB_Ptr
suffix:semicolon
macro_line|#pragma pack()
multiline_comment|/*&n; * OPEN Command Parameter List (OCPL) (can be reused, if the adapter has to&n; * be reopened)&n; */
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;2048&t;&t;/* Buffers on Adapter. */
DECL|macro|TPL_SIZE
mdefine_line|#define TPL_SIZE&t;8+6*TX_FRAG_NUM /* Depending on fragments per TPL. */
DECL|macro|RPL_SIZE
mdefine_line|#define RPL_SIZE&t;14&t;&t;/* (with TI firmware v2.26 handling&n;&t;&t;&t;&t;&t; * up to nine fragments possible)&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_BUF_MIN
mdefine_line|#define TX_BUF_MIN&t;20&t;&t;/* ??? (Stephan: calculation with */
DECL|macro|TX_BUF_MAX
mdefine_line|#define TX_BUF_MAX&t;40&t;&t;/* BUFFER_SIZE and MAX_FRAME_SIZE) ??? &n;&t;&t;&t;&t;&t; */
DECL|macro|DISABLE_EARLY_TOKEN_RELEASE
mdefine_line|#define DISABLE_EARLY_TOKEN_RELEASE &t;0x1000
multiline_comment|/* OPEN Options (high-low) */
DECL|macro|WRAP_INTERFACE
mdefine_line|#define WRAP_INTERFACE&t;&t;0x0080&t;/* Inserting omitted for test&n;&t;&t;&t;&t;&t; * purposes; transmit data appears&n;&t;&t;&t;&t;&t; * as receive data. (usefull for&n;&t;&t;&t;&t;&t; * testing; change: CLOSE necessary)&n;&t;&t;&t;&t;&t; */
DECL|macro|DISABLE_HARD_ERROR
mdefine_line|#define DISABLE_HARD_ERROR&t;0x0040&t;/* On HARD_ERROR &amp; TRANSMIT_BEACON&n;&t;&t;&t;&t;&t; * no RING.STATUS interrupt.&n;&t;&t;&t;&t;&t; */
DECL|macro|DISABLE_SOFT_ERROR
mdefine_line|#define DISABLE_SOFT_ERROR&t;0x0020&t;/* On SOFT_ERROR, no RING.STATUS&n;&t;&t;&t;&t;&t; * interrupt.&n;&t;&t;&t;&t;&t; */
DECL|macro|PASS_ADAPTER_MAC_FRAMES
mdefine_line|#define PASS_ADAPTER_MAC_FRAMES&t;0x0010&t;/* Passing unsupported MAC frames&n;&t;&t;&t;&t;&t; * to system.&n;&t;&t;&t;&t;&t; */
DECL|macro|PASS_ATTENTION_FRAMES
mdefine_line|#define PASS_ATTENTION_FRAMES&t;0x0008&t;/* All changed attention MAC frames are&n;&t;&t;&t;&t;&t; * passed to the system.&n;&t;&t;&t;&t;&t; */
DECL|macro|PAD_ROUTING_FIELD
mdefine_line|#define PAD_ROUTING_FIELD&t;0x0004&t;/* Routing field is padded to 18&n;&t;&t;&t;&t;&t; * bytes.&n;&t;&t;&t;&t;&t; */
DECL|macro|FRAME_HOLD
mdefine_line|#define FRAME_HOLD&t;&t;0x0002&t;/*Adapter waits for entire frame before&n;&t;&t;&t;&t;&t; * initiating DMA transfer; otherwise:&n;&t;&t;&t;&t;&t; * DMA transfer initiation if internal&n;&t;&t;&t;&t;&t; * buffer filled.&n;&t;&t;&t;&t;&t; */
DECL|macro|CONTENDER
mdefine_line|#define CONTENDER&t;&t;0x0001&t;/* Adapter participates in the monitor&n;&t;&t;&t;&t;&t; * contention process.&n;&t;&t;&t;&t;&t; */
DECL|macro|PASS_BEACON_MAC_FRAMES
mdefine_line|#define PASS_BEACON_MAC_FRAMES&t;0x8000&t;/* Adapter passes beacon MAC frames&n;&t;&t;&t;&t;&t; * to the system.&n;&t;&t;&t;&t;&t; */
DECL|macro|EARLY_TOKEN_RELEASE
mdefine_line|#define EARLY_TOKEN_RELEASE &t;0x1000&t;/* Only valid in 16 Mbps operation;&n;&t;&t;&t;&t;&t; * 0 = ETR. (no effect in 4 Mbps&n;&t;&t;&t;&t;&t; * operation)&n;&t;&t;&t;&t;&t; */
DECL|macro|COPY_ALL_MAC_FRAMES
mdefine_line|#define COPY_ALL_MAC_FRAMES&t;0x0400&t;/* All MAC frames are copied to&n;&t;&t;&t;&t;&t; * the system. (after OPEN: duplicate&n;&t;&t;&t;&t;&t; * address test (DAT) MAC frame is &n;&t;&t;&t;&t;&t; * first received frame copied to the&n;&t;&t;&t;&t;&t; * system)&n;&t;&t;&t;&t;&t; */
DECL|macro|COPY_ALL_NON_MAC_FRAMES
mdefine_line|#define COPY_ALL_NON_MAC_FRAMES&t;0x0200&t;/* All non MAC frames are copied to&n;&t;&t;&t;&t;&t; * the system.&n;&t;&t;&t;&t;&t; */
DECL|macro|PASS_FIRST_BUF_ONLY
mdefine_line|#define PASS_FIRST_BUF_ONLY&t;0x0100&t;/* Passes only first internal buffer&n;&t;&t;&t;&t;&t; * of each received frame; FrameSize&n;&t;&t;&t;&t;&t; * of RPLs must contain internal&n;&t;&t;&t;&t;&t; * BUFFER_SIZE bits for promiscous mode.&n;&t;&t;&t;&t;&t; */
DECL|macro|ENABLE_FULL_DUPLEX_SELECTION
mdefine_line|#define ENABLE_FULL_DUPLEX_SELECTION&t;0x2000 
multiline_comment|/* Enable the use of full-duplex&n;&t;&t;&t;&t;&t; * settings with bits in byte 22 in&n;&t;&t;&t;&t;&t; * ocpl. (new feature in firmware&n;&t;&t;&t;&t;&t; * version 3.09)&n;&t;&t;&t;&t;&t; */
multiline_comment|/* Full-duplex settings */
DECL|macro|OPEN_FULL_DUPLEX_OFF
mdefine_line|#define OPEN_FULL_DUPLEX_OFF&t;0x0000
DECL|macro|OPEN_FULL_DUPLEX_ON
mdefine_line|#define OPEN_FULL_DUPLEX_ON&t;0x00c0
DECL|macro|OPEN_FULL_DUPLEX_AUTO
mdefine_line|#define OPEN_FULL_DUPLEX_AUTO&t;0x0080
DECL|macro|PROD_ID_SIZE
mdefine_line|#define PROD_ID_SIZE&t;18&t;/* Length of product ID. */
DECL|macro|TX_FRAG_NUM
mdefine_line|#define TX_FRAG_NUM&t;3&t; /* Number of fragments used in one TPL. */
DECL|macro|TX_MORE_FRAGMENTS
mdefine_line|#define TX_MORE_FRAGMENTS 0x8000 /* Bit set in DataCount to indicate more&n;&t;&t;&t;&t;  * fragments following.&n;&t;&t;&t;&t;  */
DECL|macro|ISA_MAX_ADDRESS
mdefine_line|#define ISA_MAX_ADDRESS &t;0x00ffffff
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|OPENOptions
id|u_int16_t
id|OPENOptions
suffix:semicolon
DECL|member|NodeAddr
id|u_int8_t
id|NodeAddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Adapter node address; use ROM &n;&t;&t;&t;&t; * address&n;&t;&t;&t;&t; */
DECL|member|GroupAddr
id|u_int32_t
id|GroupAddr
suffix:semicolon
multiline_comment|/* Multicast: high order&n;&t;&t;&t;&t; * bytes = 0xC000&n;&t;&t;&t;&t; */
DECL|member|FunctAddr
id|u_int32_t
id|FunctAddr
suffix:semicolon
multiline_comment|/* High order bytes = 0xC000 */
DECL|member|RxListSize
id|u_int16_t
id|RxListSize
suffix:semicolon
multiline_comment|/* RPL size: 0 (=26), 14, 20 or&n;&t;&t;&t;&t; * 26 bytes read by the adapter.&n;&t;&t;&t;&t; * (Depending on the number of &n;&t;&t;&t;&t; * fragments/list)&n;&t;&t;&t;&t; */
DECL|member|TxListSize
id|u_int16_t
id|TxListSize
suffix:semicolon
multiline_comment|/* TPL size */
DECL|member|BufSize
id|u_int16_t
id|BufSize
suffix:semicolon
multiline_comment|/* Is automatically rounded up to the&n;&t;&t;&t;&t; * nearest nK boundary.&n;&t;&t;&t;&t; */
DECL|member|FullDuplex
id|u_int16_t
id|FullDuplex
suffix:semicolon
DECL|member|Reserved
id|u_int16_t
id|Reserved
suffix:semicolon
DECL|member|TXBufMin
id|u_int8_t
id|TXBufMin
suffix:semicolon
multiline_comment|/* Number of adapter buffers reserved&n;&t;&t;&t;&t; * for transmission a minimum of 2&n;&t;&t;&t;&t; * buffers must be allocated.&n;&t;&t;&t;&t; */
DECL|member|TXBufMax
id|u_int8_t
id|TXBufMax
suffix:semicolon
multiline_comment|/* Maximum number of adapter buffers&n;&t;&t;&t;&t; * for transmit; a minimum of 2 buffers&n;&t;&t;&t;&t; * must be available for receive.&n;&t;&t;&t;&t; * Default: 6&n;&t;&t;&t;&t; */
DECL|member|ProdIDAddr
id|u_int16_t
id|ProdIDAddr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Pointer to product ID. */
DECL|typedef|OPB
DECL|typedef|OPB_Ptr
)brace
id|OPB
comma
op_star
id|OPB_Ptr
suffix:semicolon
macro_line|#pragma pack()
multiline_comment|/*&n; * SCB: adapter commands enabled by the host system started by writing&n; * CMD_INTERRUPT_ADAPTER | CMD_EXECUTE (|SCB_REQUEST) to the SIFCMD IO&n; * register. (special case: | CMD_SYSTEM_IRQ for initialization)&n; */
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|CMD
id|u_int16_t
id|CMD
suffix:semicolon
multiline_comment|/* Command code */
DECL|member|Parm
id|u_int16_t
id|Parm
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Pointer to Command Parameter Block */
DECL|typedef|SCB
)brace
id|SCB
suffix:semicolon
multiline_comment|/* System Command Block (32 bit physical address; big endian)*/
macro_line|#pragma pack()
multiline_comment|/*&n; * SSB: adapter command return status can be evaluated after COMMAND_STATUS&n; * adapter to system interrupt after reading SSB, the availability of the SSB&n; * has to be told the adapter by writing CMD_INTERRUPT_ADAPTER | CMD_SSB_CLEAR&n; * in the SIFCMD IO register.&n; */
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|STS
id|u_int16_t
id|STS
suffix:semicolon
multiline_comment|/* Status code */
DECL|member|Parm
id|u_int16_t
id|Parm
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Parameter or pointer to Status Parameter&n;&t;&t;&t;&t; * Block.&n;&t;&t;&t;&t; */
DECL|typedef|SSB
)brace
id|SSB
suffix:semicolon
multiline_comment|/* System Status Block (big endian - physical address)  */
macro_line|#pragma pack()
r_typedef
r_struct
(brace
DECL|member|BurnedInAddrPtr
r_int
r_int
id|BurnedInAddrPtr
suffix:semicolon
multiline_comment|/* Pointer to adapter burned in&n;&t;&t;&t;&t;&t; * address. (BIA)&n;&t;&t;&t;&t;&t; */
DECL|member|SoftwareLevelPtr
r_int
r_int
id|SoftwareLevelPtr
suffix:semicolon
multiline_comment|/* Pointer to software level data. */
DECL|member|AdapterAddrPtr
r_int
r_int
id|AdapterAddrPtr
suffix:semicolon
multiline_comment|/* Pointer to adapter addresses. */
DECL|member|AdapterParmsPtr
r_int
r_int
id|AdapterParmsPtr
suffix:semicolon
multiline_comment|/* Pointer to adapter parameters. */
DECL|member|MACBufferPtr
r_int
r_int
id|MACBufferPtr
suffix:semicolon
multiline_comment|/* Pointer to MAC buffer. (internal) */
DECL|member|LLCCountersPtr
r_int
r_int
id|LLCCountersPtr
suffix:semicolon
multiline_comment|/* Pointer to LLC counters.  */
DECL|member|SpeedFlagPtr
r_int
r_int
id|SpeedFlagPtr
suffix:semicolon
multiline_comment|/* Pointer to data rate flag.&n;&t;&t;&t;&t;&t; * (4/16 Mbps)&n;&t;&t;&t;&t;&t; */
DECL|member|AdapterRAMPtr
r_int
r_int
id|AdapterRAMPtr
suffix:semicolon
multiline_comment|/* Pointer to adapter RAM found. (KB) */
DECL|typedef|INTPTRS
)brace
id|INTPTRS
suffix:semicolon
multiline_comment|/* Adapter internal pointers */
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|Line_Error
id|u_int8_t
id|Line_Error
suffix:semicolon
multiline_comment|/* Line error: code violation in&n;&t;&t;&t;&t;&t; * frame or in a token, or FCS error.&n;&t;&t;&t;&t;&t; */
DECL|member|Internal_Error
id|u_int8_t
id|Internal_Error
suffix:semicolon
multiline_comment|/* IBM specific. (Reserved_1) */
DECL|member|Burst_Error
id|u_int8_t
id|Burst_Error
suffix:semicolon
DECL|member|ARI_FCI_Error
id|u_int8_t
id|ARI_FCI_Error
suffix:semicolon
multiline_comment|/* ARI/FCI bit zero in AMP or&n;&t;&t;&t;&t;&t; * SMP MAC frame.&n;&t;&t;&t;&t;&t; */
DECL|member|AbortDelimeters
id|u_int8_t
id|AbortDelimeters
suffix:semicolon
multiline_comment|/* IBM specific. (Reserved_2) */
DECL|member|Reserved_3
id|u_int8_t
id|Reserved_3
suffix:semicolon
DECL|member|Lost_Frame_Error
id|u_int8_t
id|Lost_Frame_Error
suffix:semicolon
multiline_comment|/* Receive of end of transmitted&n;&t;&t;&t;&t;&t; * frame failed.&n;&t;&t;&t;&t;&t; */
DECL|member|Rx_Congest_Error
id|u_int8_t
id|Rx_Congest_Error
suffix:semicolon
multiline_comment|/* Adapter in repeat mode has not&n;&t;&t;&t;&t;&t; * enough buffer space to copy incoming&n;&t;&t;&t;&t;&t; * frame.&n;&t;&t;&t;&t;&t; */
DECL|member|Frame_Copied_Error
id|u_int8_t
id|Frame_Copied_Error
suffix:semicolon
multiline_comment|/* ARI bit not zero in frame&n;&t;&t;&t;&t;&t; * addressed to adapter.&n;&t;&t;&t;&t;&t; */
DECL|member|Frequency_Error
id|u_int8_t
id|Frequency_Error
suffix:semicolon
multiline_comment|/* IBM specific. (Reserved_4) */
DECL|member|Token_Error
id|u_int8_t
id|Token_Error
suffix:semicolon
multiline_comment|/* (active only in monitor station) */
DECL|member|Reserved_5
id|u_int8_t
id|Reserved_5
suffix:semicolon
DECL|member|DMA_Bus_Error
id|u_int8_t
id|DMA_Bus_Error
suffix:semicolon
multiline_comment|/* DMA bus errors not exceeding the&n;&t;&t;&t;&t;&t; * abort thresholds.&n;&t;&t;&t;&t;&t; */
DECL|member|DMA_Parity_Error
id|u_int8_t
id|DMA_Parity_Error
suffix:semicolon
multiline_comment|/* DMA parity errors not exceeding&n;&t;&t;&t;&t;&t; * the abort thresholds.&n;&t;&t;&t;&t;&t; */
DECL|typedef|ERRORTAB
)brace
id|ERRORTAB
suffix:semicolon
multiline_comment|/* Adapter error counters */
macro_line|#pragma pack()
multiline_comment|/*--------------------- Send and Receive definitions -------------------*/
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|DataCount
id|u_int16_t
id|DataCount
suffix:semicolon
multiline_comment|/* Value 0, even and odd values are&n;&t;&t;&t;&t; * permitted; value is unaltered most&n;&t;&t;&t;&t; * significant bit set: following&n;&t;&t;&t;&t; * fragments last fragment: most&n;&t;&t;&t;&t; * significant bit is not evaluated.&n;&t;&t;&t;&t; * (???)&n;&t;&t;&t;&t; */
DECL|member|DataAddr
id|u_int32_t
id|DataAddr
suffix:semicolon
multiline_comment|/* Pointer to frame data fragment;&n;&t;&t;&t;&t; * even or odd.&n;&t;&t;&t;&t; */
DECL|typedef|Fragment
)brace
id|Fragment
suffix:semicolon
macro_line|#pragma pack()
DECL|macro|MAX_FRAG_NUMBERS
mdefine_line|#define MAX_FRAG_NUMBERS    9&t;/* Maximal number of fragments possible to use&n;&t;&t;&t;&t; * in one RPL/TPL. (depending on TI firmware &n;&t;&t;&t;&t; * version)&n;&t;&t;&t;&t; */
DECL|macro|MAX_TX_QUEUE
mdefine_line|#define MAX_TX_QUEUE&t;    10&t;/* Maximal number of skb&squot;s queued in driver. */
multiline_comment|/*&n; * AC (1), FC (1), Dst (6), Src (6), RIF (18), Data (4472) = 4504&n; * The packet size can be one of the follows: 548, 1502, 2084, 4504, 8176,&n; * 11439, 17832. Refer to TMS380 Second Generation Token Ring User&squot;s Guide&n; * Page 2-27.&n; */
DECL|macro|HEADER_SIZE
mdefine_line|#define HEADER_SIZE&t;&t;(1 + 1 + 6 + 6)
DECL|macro|SRC_SIZE
mdefine_line|#define SRC_SIZE&t;&t;18
DECL|macro|MIN_DATA_SIZE
mdefine_line|#define MIN_DATA_SIZE&t;&t;516
DECL|macro|DEFAULT_DATA_SIZE
mdefine_line|#define DEFAULT_DATA_SIZE&t;4472
DECL|macro|MAX_DATA_SIZE
mdefine_line|#define MAX_DATA_SIZE&t;&t;17800
DECL|macro|DEFAULT_PACKET_SIZE
mdefine_line|#define DEFAULT_PACKET_SIZE (HEADER_SIZE + SRC_SIZE + DEFAULT_DATA_SIZE)
DECL|macro|MIN_PACKET_SIZE
mdefine_line|#define MIN_PACKET_SIZE     (HEADER_SIZE + SRC_SIZE + MIN_DATA_SIZE)
DECL|macro|MAX_PACKET_SIZE
mdefine_line|#define MAX_PACKET_SIZE     (HEADER_SIZE + SRC_SIZE + MAX_DATA_SIZE)
multiline_comment|/*&n; * Macros to deal with the frame status field.&n; */
DECL|macro|AC_NOT_RECOGNIZED
mdefine_line|#define AC_NOT_RECOGNIZED&t;0x00
DECL|macro|GROUP_BIT
mdefine_line|#define GROUP_BIT&t;&t;0x80
DECL|macro|GET_TRANSMIT_STATUS_HIGH_BYTE
mdefine_line|#define GET_TRANSMIT_STATUS_HIGH_BYTE(Ts) ((unsigned char)((Ts) &gt;&gt; 8))
DECL|macro|GET_FRAME_STATUS_HIGH_AC
mdefine_line|#define GET_FRAME_STATUS_HIGH_AC(Fs)&t;  ((unsigned char)(((Fs) &amp; 0xC0) &gt;&gt; 6))
DECL|macro|GET_FRAME_STATUS_LOW_AC
mdefine_line|#define GET_FRAME_STATUS_LOW_AC(Fs)       ((unsigned char)(((Fs) &amp; 0x0C) &gt;&gt; 2))
DECL|macro|DIRECTED_FRAME
mdefine_line|#define DIRECTED_FRAME(Context)           (!((Context)-&gt;MData[2] &amp; GROUP_BIT))
multiline_comment|/*--------------------- Send Functions ---------------------------------*/
multiline_comment|/* define TX_CSTAT _REQUEST (R) and _COMPLETE (C) values (high-low) */
DECL|macro|TX_VALID
mdefine_line|#define TX_VALID&t;&t;0x0080&t;/* R: set via TRANSMIT.VALID interrupt.&n;&t;&t;&t;&t;&t; * C: always reset to zero!&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_FRAME_COMPLETE
mdefine_line|#define TX_FRAME_COMPLETE&t;0x0040&t;/* R: must be reset to zero.&n;&t;&t;&t;&t;&t; * C: set to one.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_START_FRAME
mdefine_line|#define TX_START_FRAME&t;&t;0x0020  /* R: start of a frame: 1 &n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_END_FRAME
mdefine_line|#define TX_END_FRAME&t;&t;0x0010  /* R: end of a frame: 1&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_FRAME_IRQ
mdefine_line|#define TX_FRAME_IRQ&t;&t;0x0008  /* R: request interrupt generation&n;&t;&t;&t;&t;&t; * after transmission.&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_ERROR
mdefine_line|#define TX_ERROR&t;&t;0x0004  /* R: reserved.&n;&t;&t;&t;&t;&t; * C: set to one if Error occurred.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_INTERFRAME_WAIT
mdefine_line|#define TX_INTERFRAME_WAIT&t;0x0004
DECL|macro|TX_PASS_CRC
mdefine_line|#define TX_PASS_CRC&t;&t;0x0002  /* R: set if CRC value is already&n;&t;&t;&t;&t;&t; * calculated. (valid only in&n;&t;&t;&t;&t;&t; * FRAME_START TPL)&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_PASS_SRC_ADDR
mdefine_line|#define TX_PASS_SRC_ADDR&t;0x0001  /* R: adapter uses explicit frame&n;&t;&t;&t;&t;&t; * source address and does not overwrite&n;&t;&t;&t;&t;&t; * with the adapter node address.&n;&t;&t;&t;&t;&t; * (valid only in FRAME_START TPL)&n;&t;&t;&t;&t;&t; *&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_STRIP_FS
mdefine_line|#define TX_STRIP_FS&t;&t;0xFF00  /* R: reserved.&n;&t;&t;&t;&t;&t; * C: if no Transmission Error,&n;&t;&t;&t;&t;&t; * field contains copy of FS byte after&n;&t;&t;&t;&t;&t; * stripping of frame.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Structure of Transmit Parameter Lists (TPLs) (only one frame every TPL,&n; * but possibly multiple TPLs for one frame) the length of the TPLs has to be&n; * initialized in the OPL. (OPEN parameter list)&n; */
DECL|macro|TPL_NUM
mdefine_line|#define TPL_NUM&t;&t;3&t;/* Number of Transmit Parameter Lists.&n;&t;&t;&t;&t; * !! MUST BE &gt;= 3 !!&n;&t;&t;&t;&t; */
macro_line|#pragma pack(1)
DECL|typedef|TPL
r_typedef
r_struct
id|s_TPL
id|TPL
suffix:semicolon
DECL|struct|s_TPL
r_struct
id|s_TPL
(brace
multiline_comment|/* Transmit Parameter List (align on even word boundaries) */
DECL|member|NextTPLAddr
id|u_int32_t
id|NextTPLAddr
suffix:semicolon
multiline_comment|/* Pointer to next TPL in chain; if&n;&t;&t;&t;&t;&t; * pointer is odd: this is the last&n;&t;&t;&t;&t;&t; * TPL. Pointing to itself can cause&n;&t;&t;&t;&t;&t; * problems!&n;&t;&t;&t;&t;&t; */
DECL|member|Status
r_volatile
id|u_int16_t
id|Status
suffix:semicolon
multiline_comment|/* Initialized by the adapter:&n;&t;&t;&t;&t;&t; * CSTAT_REQUEST important: update least&n;&t;&t;&t;&t;&t; * significant bit first! Set by the&n;&t;&t;&t;&t;&t; * adapter: CSTAT_COMPLETE status.&n;&t;&t;&t;&t;&t; */
DECL|member|FrameSize
id|u_int16_t
id|FrameSize
suffix:semicolon
multiline_comment|/* Number of bytes to be transmitted&n;&t;&t;&t;&t;&t; * as a frame including AC/FC,&n;&t;&t;&t;&t;&t; * Destination, Source, Routing field&n;&t;&t;&t;&t;&t; * not including CRC, FS, End Delimiter&n;&t;&t;&t;&t;&t; * (valid only if START_FRAME bit in &n;&t;&t;&t;&t;&t; * CSTAT nonzero) must not be zero in&n;&t;&t;&t;&t;&t; * any list; maximum value: (BUFFER_SIZE&n;&t;&t;&t;&t;&t; * - 8) * TX_BUF_MAX sum of DataCount&n;&t;&t;&t;&t;&t; * values in FragmentList must equal&n;&t;&t;&t;&t;&t; * Frame_Size value in START_FRAME TPL!&n;&t;&t;&t;&t;&t; * frame data fragment list.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* TPL/RPL size in OPEN parameter list depending on maximal&n;&t; * numbers of fragments used in one parameter list.&n;&t; */
DECL|member|FragList
id|Fragment
id|FragList
(braket
id|TX_FRAG_NUM
)braket
suffix:semicolon
multiline_comment|/* Maximum: nine frame fragments in one&n;&t;&t;&t;&t;&t; * TPL actual version of firmware: 9&n;&t;&t;&t;&t;&t; * fragments possible.&n;&t;&t;&t;&t;&t; */
macro_line|#pragma pack()
multiline_comment|/* Special proprietary data and precalculations */
DECL|member|NextTPLPtr
id|TPL
op_star
id|NextTPLPtr
suffix:semicolon
multiline_comment|/* Pointer to next TPL in chain. */
DECL|member|MData
r_int
r_char
op_star
id|MData
suffix:semicolon
DECL|member|Skb
r_struct
id|sk_buff
op_star
id|Skb
suffix:semicolon
DECL|member|TPLIndex
r_int
r_char
id|TPLIndex
suffix:semicolon
DECL|member|BusyFlag
r_volatile
r_int
r_char
id|BusyFlag
suffix:semicolon
multiline_comment|/* Flag: TPL busy? */
DECL|member|DMABuff
id|dma_addr_t
id|DMABuff
suffix:semicolon
multiline_comment|/* DMA IO bus address from pci_map */
)brace
suffix:semicolon
multiline_comment|/* ---------------------Receive Functions-------------------------------*&n; * define RECEIVE_CSTAT_REQUEST (R) and RECEIVE_CSTAT_COMPLETE (C) values.&n; * (high-low)&n; */
DECL|macro|RX_VALID
mdefine_line|#define RX_VALID&t;&t;0x0080&t;/* R: set; tell adapter with&n;&t;&t;&t;&t;&t; * RECEIVE.VALID interrupt.&n;&t;&t;&t;&t;&t; * C: reset to zero.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_FRAME_COMPLETE
mdefine_line|#define RX_FRAME_COMPLETE&t;0x0040  /* R: must be reset to zero,&n;&t;&t;&t;&t;&t; * C: set to one.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_START_FRAME
mdefine_line|#define RX_START_FRAME&t;&t;0x0020  /* R: must be reset to zero.&n;&t;&t;&t;&t;&t; * C: set to one on the list.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_END_FRAME
mdefine_line|#define RX_END_FRAME&t;&t;0x0010  /* R: must be reset to zero.&n;&t;&t;&t;&t;&t; * C: set to one on the list&n;&t;&t;&t;&t;&t; * that ends the frame.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_FRAME_IRQ
mdefine_line|#define RX_FRAME_IRQ&t;&t;0x0008  /* R: request interrupt generation&n;&t;&t;&t;&t;&t; * after receive.&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_INTERFRAME_WAIT
mdefine_line|#define RX_INTERFRAME_WAIT&t;0x0004  /* R: after receiving a frame:&n;&t;&t;&t;&t;&t; * interrupt and wait for a&n;&t;&t;&t;&t;&t; * RECEIVE.CONTINUE.&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_PASS_CRC
mdefine_line|#define RX_PASS_CRC&t;&t;0x0002  /* R: if set, the adapter includes&n;&t;&t;&t;&t;&t; * the CRC in data passed. (last four &n;&t;&t;&t;&t;&t; * bytes; valid only if FRAME_START is&n;&t;&t;&t;&t;&t; * set)&n;&t;&t;&t;&t;&t; * C: set, if CRC is included in&n;&t;&t;&t;&t;&t; * received data.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_PASS_SRC_ADDR
mdefine_line|#define RX_PASS_SRC_ADDR&t;0x0001  /* R: adapter uses explicit frame&n;&t;&t;&t;&t;&t; * source address and does not&n;&t;&t;&t;&t;&t; * overwrite with the adapter node&n;&t;&t;&t;&t;&t; * address. (valid only if FRAME_START&n;&t;&t;&t;&t;&t; * is set)&n;&t;&t;&t;&t;&t; * C: unchanged.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_RECEIVE_FS
mdefine_line|#define RX_RECEIVE_FS&t;&t;0xFC00  /* R: reserved; must be reset to zero.&n;&t;&t;&t;&t;&t; * C: on lists with START_FRAME, field&n;&t;&t;&t;&t;&t; * contains frame status field from&n;&t;&t;&t;&t;&t; * received frame; otherwise cleared.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_ADDR_MATCH
mdefine_line|#define RX_ADDR_MATCH&t;&t;0x0300  /* R: reserved; must be reset to zero.&n;&t;&t;&t;&t;&t; * C: address match code mask.&n;&t;&t;&t;&t;&t; */ 
DECL|macro|RX_STATUS_MASK
mdefine_line|#define RX_STATUS_MASK&t;&t;0x00FF  /* Mask for receive status bits. */
DECL|macro|RX_INTERN_ADDR_MATCH
mdefine_line|#define RX_INTERN_ADDR_MATCH    0x0100  /* C: internally address match. */
DECL|macro|RX_EXTERN_ADDR_MATCH
mdefine_line|#define RX_EXTERN_ADDR_MATCH    0x0200  /* C: externally matched via&n;&t;&t;&t;&t;&t; * XMATCH/XFAIL interface.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_INTEXT_ADDR_MATCH
mdefine_line|#define RX_INTEXT_ADDR_MATCH    0x0300  /* C: internally and externally&n;&t;&t;&t;&t;&t; * matched.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_READY
mdefine_line|#define RX_READY (RX_VALID | RX_FRAME_IRQ) /* Ready for receive. */
multiline_comment|/* Constants for Command Status Interrupt.&n; * COMMAND_REJECT status field bit functions (SSB.Parm[0])&n; */
DECL|macro|ILLEGAL_COMMAND
mdefine_line|#define ILLEGAL_COMMAND&t;&t;0x0080&t;/* Set if an unknown command&n;&t;&t;&t;&t;&t; * is issued to the adapter&n;&t;&t;&t;&t;&t; */
DECL|macro|ADDRESS_ERROR
mdefine_line|#define ADDRESS_ERROR&t;&t;0x0040  /* Set if any address field in&n;&t;&t;&t;&t;&t; * the SCB is odd. (not word aligned)&n;&t;&t;&t;&t;&t; */
DECL|macro|ADAPTER_OPEN
mdefine_line|#define ADAPTER_OPEN&t;&t;0x0020  /* Command issued illegal with&n;&t;&t;&t;&t;&t; * open adapter.&n;&t;&t;&t;&t;&t; */
DECL|macro|ADAPTER_CLOSE
mdefine_line|#define ADAPTER_CLOSE&t;&t;0x0010  /* Command issued illegal with&n;&t;&t;&t;&t;&t; * closed adapter.&n;&t;&t;&t;&t;&t; */
DECL|macro|SAME_COMMAND
mdefine_line|#define SAME_COMMAND&t;&t;0x0008  /* Command issued with same command&n;&t;&t;&t;&t;&t; * already executing.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* OPEN_COMPLETION values (SSB.Parm[0], MSB) */
DECL|macro|NODE_ADDR_ERROR
mdefine_line|#define NODE_ADDR_ERROR&t;&t;0x0040  /* Wrong address or BIA read&n;&t;&t;&t;&t;&t; * zero address.&n;&t;&t;&t;&t;&t; */
DECL|macro|LIST_SIZE_ERROR
mdefine_line|#define LIST_SIZE_ERROR&t;&t;0x0020  /* If List_Size value not in 0,&n;&t;&t;&t;&t;&t; * 14, 20, 26.&n;&t;&t;&t;&t;&t; */
DECL|macro|BUF_SIZE_ERROR
mdefine_line|#define BUF_SIZE_ERROR&t;&t;0x0010  /* Not enough available memory for&n;&t;&t;&t;&t;&t; * two buffers.&n;&t;&t;&t;&t;&t; */
DECL|macro|TX_BUF_COUNT_ERROR
mdefine_line|#define TX_BUF_COUNT_ERROR&t;0x0004  /* Remaining receive buffers less than&n;&t;&t;&t;&t;&t; * two.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_ERROR
mdefine_line|#define OPEN_ERROR&t;&t;0x0002&t;/* Error during ring insertion; more&n;&t;&t;&t;&t;&t; * information in bits 8-15.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* Standard return codes */
DECL|macro|GOOD_COMPLETION
mdefine_line|#define GOOD_COMPLETION&t;&t;0x0080  /* =OPEN_SUCCESSFULL */
DECL|macro|INVALID_OPEN_OPTION
mdefine_line|#define INVALID_OPEN_OPTION&t;0x0001  /* OPEN options are not supported by&n;&t;&t;&t;&t;&t; * the adapter.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* OPEN phases; details of OPEN_ERROR (SSB.Parm[0], LSB)            */
DECL|macro|OPEN_PHASES_MASK
mdefine_line|#define OPEN_PHASES_MASK            0xF000  /* Check only the bits 8-11. */
DECL|macro|LOBE_MEDIA_TEST
mdefine_line|#define LOBE_MEDIA_TEST             0x1000
DECL|macro|PHYSICAL_INSERTION
mdefine_line|#define PHYSICAL_INSERTION          0x2000
DECL|macro|ADDRESS_VERIFICATION
mdefine_line|#define ADDRESS_VERIFICATION        0x3000
DECL|macro|PARTICIPATION_IN_RING_POLL
mdefine_line|#define PARTICIPATION_IN_RING_POLL  0x4000
DECL|macro|REQUEST_INITIALISATION
mdefine_line|#define REQUEST_INITIALISATION      0x5000
DECL|macro|FULLDUPLEX_CHECK
mdefine_line|#define FULLDUPLEX_CHECK            0x6000
multiline_comment|/* OPEN error codes; details of OPEN_ERROR (SSB.Parm[0], LSB) */
DECL|macro|OPEN_ERROR_CODES_MASK
mdefine_line|#define OPEN_ERROR_CODES_MASK&t;0x0F00  /* Check only the bits 12-15. */
DECL|macro|OPEN_FUNCTION_FAILURE
mdefine_line|#define OPEN_FUNCTION_FAILURE   0x0100  /* Unable to transmit to itself or&n;&t;&t;&t;&t;&t; * frames received before insertion.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_SIGNAL_LOSS
mdefine_line|#define OPEN_SIGNAL_LOSS&t;0x0200&t;/* Signal loss condition detected at&n;&t;&t;&t;&t;&t; * receiver.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_TIMEOUT
mdefine_line|#define OPEN_TIMEOUT&t;&t;0x0500&t;/* Insertion timer expired before&n;&t;&t;&t;&t;&t; * logical insertion.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_RING_FAILURE
mdefine_line|#define OPEN_RING_FAILURE&t;0x0600&t;/* Unable to receive own ring purge&n;&t;&t;&t;&t;&t; * MAC frames.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_RING_BEACONING
mdefine_line|#define OPEN_RING_BEACONING&t;0x0700&t;/* Beacon MAC frame received after&n;&t;&t;&t;&t;&t; * ring insertion.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_DUPLICATE_NODEADDR
mdefine_line|#define OPEN_DUPLICATE_NODEADDR&t;0x0800  /* Other station in ring found&n;&t;&t;&t;&t;&t; * with the same address.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_REQUEST_INIT
mdefine_line|#define OPEN_REQUEST_INIT&t;0x0900&t;/* RPS present but does not respond. */
DECL|macro|OPEN_REMOVE_RECEIVED
mdefine_line|#define OPEN_REMOVE_RECEIVED    0x0A00  /* Adapter received a remove adapter&n;&t;&t;&t;&t;&t; * MAC frame.&n;&t;&t;&t;&t;&t; */
DECL|macro|OPEN_FULLDUPLEX_SET
mdefine_line|#define OPEN_FULLDUPLEX_SET&t;0x0D00&t;/* Got this with full duplex on when&n;&t;&t;&t;&t;&t; * trying to connect to a normal ring.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* SET_BRIDGE_PARMS return codes: */
DECL|macro|BRIDGE_INVALID_MAX_LEN
mdefine_line|#define BRIDGE_INVALID_MAX_LEN  0x4000  /* MAX_ROUTING_FIELD_LENGTH odd,&n;&t;&t;&t;&t;&t; * less than 6 or &gt; 30.&n;&t;&t;&t;&t;&t; */
DECL|macro|BRIDGE_INVALID_SRC_RING
mdefine_line|#define BRIDGE_INVALID_SRC_RING 0x2000  /* SOURCE_RING number zero, too large&n;&t;&t;&t;&t;&t; * or = TARGET_RING.&n;&t;&t;&t;&t;&t; */
DECL|macro|BRIDGE_INVALID_TRG_RING
mdefine_line|#define BRIDGE_INVALID_TRG_RING 0x1000  /* TARGET_RING number zero, too large&n;&t;&t;&t;&t;&t; * or = SOURCE_RING.&n;&t;&t;&t;&t;&t; */
DECL|macro|BRIDGE_INVALID_BRDGE_NO
mdefine_line|#define BRIDGE_INVALID_BRDGE_NO 0x0800  /* BRIDGE_NUMBER too large. */
DECL|macro|BRIDGE_INVALID_OPTIONS
mdefine_line|#define BRIDGE_INVALID_OPTIONS  0x0400  /* Invalid bridge options. */
DECL|macro|BRIDGE_DIAGS_FAILED
mdefine_line|#define BRIDGE_DIAGS_FAILED     0x0200  /* Diagnostics of TMS380SRA failed. */
DECL|macro|BRIDGE_NO_SRA
mdefine_line|#define BRIDGE_NO_SRA           0x0100  /* The TMS380SRA does not exist in HW&n;&t;&t;&t;&t;&t; * configuration.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Bring Up Diagnostics error codes.&n; */
DECL|macro|BUD_INITIAL_ERROR
mdefine_line|#define BUD_INITIAL_ERROR       0x0
DECL|macro|BUD_CHECKSUM_ERROR
mdefine_line|#define BUD_CHECKSUM_ERROR      0x1
DECL|macro|BUD_ADAPTER_RAM_ERROR
mdefine_line|#define BUD_ADAPTER_RAM_ERROR   0x2
DECL|macro|BUD_INSTRUCTION_ERROR
mdefine_line|#define BUD_INSTRUCTION_ERROR   0x3
DECL|macro|BUD_CONTEXT_ERROR
mdefine_line|#define BUD_CONTEXT_ERROR       0x4
DECL|macro|BUD_PROTOCOL_ERROR
mdefine_line|#define BUD_PROTOCOL_ERROR      0x5
DECL|macro|BUD_INTERFACE_ERROR
mdefine_line|#define BUD_INTERFACE_ERROR&t;0x6
multiline_comment|/* BUD constants */
DECL|macro|BUD_MAX_RETRIES
mdefine_line|#define BUD_MAX_RETRIES         3
DECL|macro|BUD_MAX_LOOPCNT
mdefine_line|#define BUD_MAX_LOOPCNT         6
DECL|macro|BUD_TIMEOUT
mdefine_line|#define BUD_TIMEOUT             3000
multiline_comment|/* Initialization constants */
DECL|macro|INIT_MAX_RETRIES
mdefine_line|#define INIT_MAX_RETRIES        3&t;/* Maximum three retries. */
DECL|macro|INIT_MAX_LOOPCNT
mdefine_line|#define INIT_MAX_LOOPCNT        22      /* Maximum loop counts. */
multiline_comment|/* RING STATUS field values (high/low) */
DECL|macro|SIGNAL_LOSS
mdefine_line|#define SIGNAL_LOSS             0x0080  /* Loss of signal on the ring&n;&t;&t;&t;&t;&t; * detected.&n;&t;&t;&t;&t;&t; */
DECL|macro|HARD_ERROR
mdefine_line|#define HARD_ERROR              0x0040  /* Transmitting or receiving beacon&n;&t;&t;&t;&t;&t; * frames.&n;&t;&t;&t;&t;&t; */
DECL|macro|SOFT_ERROR
mdefine_line|#define SOFT_ERROR              0x0020  /* Report error MAC frame&n;&t;&t;&t;&t;&t; * transmitted.&n;&t;&t;&t;&t;&t; */
DECL|macro|TRANSMIT_BEACON
mdefine_line|#define TRANSMIT_BEACON         0x0010  /* Transmitting beacon frames on the&n;&t;&t;&t;&t;&t; * ring.&n;&t;&t;&t;&t;&t; */
DECL|macro|LOBE_WIRE_FAULT
mdefine_line|#define LOBE_WIRE_FAULT         0x0008  /* Open or short circuit in the&n;&t;&t;&t;&t;&t; * cable to concentrator; adapter&n;&t;&t;&t;&t;&t; * closed.&n;&t;&t;&t;&t;&t; */
DECL|macro|AUTO_REMOVAL_ERROR
mdefine_line|#define AUTO_REMOVAL_ERROR      0x0004  /* Lobe wrap test failed, deinserted;&n;&t;&t;&t;&t;&t; * adapter closed.&n;&t;&t;&t;&t;&t; */
DECL|macro|REMOVE_RECEIVED
mdefine_line|#define REMOVE_RECEIVED         0x0001  /* Received a remove ring station MAC&n;&t;&t;&t;&t;&t; * MAC frame request; adapter closed.&n;&t;&t;&t;&t;&t; */
DECL|macro|COUNTER_OVERFLOW
mdefine_line|#define COUNTER_OVERFLOW        0x8000  /* Overflow of one of the adapters&n;&t;&t;&t;&t;&t; * error counters; READ.ERROR.LOG.&n;&t;&t;&t;&t;&t; */
DECL|macro|SINGLE_STATION
mdefine_line|#define SINGLE_STATION          0x4000  /* Adapter is the only station on the&n;&t;&t;&t;&t;&t; * ring.&n;&t;&t;&t;&t;&t; */
DECL|macro|RING_RECOVERY
mdefine_line|#define RING_RECOVERY           0x2000  /* Claim token MAC frames on the ring;&n;&t;&t;&t;&t;&t; * reset after ring purge frame.&n;&t;&t;&t;&t;&t; */
DECL|macro|ADAPTER_CLOSED
mdefine_line|#define ADAPTER_CLOSED (LOBE_WIRE_FAULT | AUTO_REMOVAL_ERROR |&bslash;&n;                        REMOVE_RECEIVED)
multiline_comment|/* Adapter_check_block.Status field bit assignments: */
DECL|macro|DIO_PARITY
mdefine_line|#define DIO_PARITY              0x8000  /* Adapter detects bad parity&n;&t;&t;&t;&t;&t; * through direct I/O access.&n;&t;&t;&t;&t;&t; */
DECL|macro|DMA_READ_ABORT
mdefine_line|#define DMA_READ_ABORT          0x4000  /* Aborting DMA read operation&n;&t;&t;&t;&t;&t; * from system Parm[0]: 0=timeout,&n;&t;&t;&t;&t;&t; * 1=parity error, 2=bus error;&n;&t;&t;&t;&t;&t; * Parm[1]: 32 bit pointer to host&n;&t;&t;&t;&t;&t; * system address at failure.&n;&t;&t;&t;&t;&t; */
DECL|macro|DMA_WRITE_ABORT
mdefine_line|#define DMA_WRITE_ABORT         0x2000  /* Aborting DMA write operation&n;&t;&t;&t;&t;&t; * to system. (parameters analogous to&n;&t;&t;&t;&t;&t; * DMA_READ_ABORT)&n;&t;&t;&t;&t;&t; */
DECL|macro|ILLEGAL_OP_CODE
mdefine_line|#define ILLEGAL_OP_CODE         0x1000  /* Illegal operation code in the&n;&t;&t;&t;&t;&t; * the adapters firmware Parm[0]-2:&n;&t;&t;&t;&t;&t; * communications processor registers&n;&t;&t;&t;&t;&t; * R13-R15.&n;&t;&t;&t;&t;&t; */
DECL|macro|PARITY_ERRORS
mdefine_line|#define PARITY_ERRORS           0x0800  /* Adapter detects internal bus&n;&t;&t;&t;&t;&t; * parity error.&n;&t;&t;&t;&t;&t; */
DECL|macro|RAM_DATA_ERROR
mdefine_line|#define RAM_DATA_ERROR          0x0080  /* Valid only during RAM testing;&n;&t;&t;&t;&t;&t; * RAM data error Parm[0-1]: 32 bit&n;&t;&t;&t;&t;&t; * pointer to RAM location.&n;&t;&t;&t;&t;&t; */
DECL|macro|RAM_PARITY_ERROR
mdefine_line|#define RAM_PARITY_ERROR        0x0040  /* Valid only during RAM testing;&n;&t;&t;&t;&t;&t; * RAM parity error Parm[0-1]: 32 bit&n;&t;&t;&t;&t;&t; * pointer to RAM location.&n;&t;&t;&t;&t;&t; */
DECL|macro|RING_UNDERRUN
mdefine_line|#define RING_UNDERRUN           0x0020  /* Internal DMA underrun when&n;&t;&t;&t;&t;&t; * transmitting onto ring.&n;&t;&t;&t;&t;&t; */
DECL|macro|INVALID_IRQ
mdefine_line|#define INVALID_IRQ             0x0008  /* Unrecognized interrupt generated&n;&t;&t;&t;&t;&t; * internal to adapter Parm[0-2]:&n;&t;&t;&t;&t;&t; * adapter register R13-R15.&n;&t;&t;&t;&t;&t; */
DECL|macro|INVALID_ERROR_IRQ
mdefine_line|#define INVALID_ERROR_IRQ       0x0004  /* Unrecognized error interrupt&n;&t;&t;&t;&t;&t; * generated Parm[0-2]: adapter register&n;&t;&t;&t;&t;&t; * R13-R15.&n;&t;&t;&t;&t;&t; */
DECL|macro|INVALID_XOP
mdefine_line|#define INVALID_XOP             0x0002  /* Unrecognized XOP request in&n;&t;&t;&t;&t;&t; * communication processor Parm[0-2]:&n;&t;&t;&t;&t;&t; * adapter register R13-R15.&n;&t;&t;&t;&t;&t; */
DECL|macro|CHECKADDR
mdefine_line|#define CHECKADDR               0x05E0  /* Adapter check status information&n;&t;&t;&t;&t;&t; * address offset.&n;&t;&t;&t;&t;&t; */
DECL|macro|ROM_PAGE_0
mdefine_line|#define ROM_PAGE_0              0x0000  /* Adapter ROM page 0. */
multiline_comment|/*&n; * RECEIVE.STATUS interrupt result SSB values: (high-low)&n; * (RECEIVE_COMPLETE field bit definitions in SSB.Parm[0])&n; */
DECL|macro|RX_COMPLETE
mdefine_line|#define RX_COMPLETE             0x0080  /* SSB.Parm[0]; SSB.Parm[1]: 32&n;&t;&t;&t;&t;&t; * bit pointer to last RPL.&n;&t;&t;&t;&t;&t; */
DECL|macro|RX_SUSPENDED
mdefine_line|#define RX_SUSPENDED            0x0040  /* SSB.Parm[0]; SSB.Parm[1]: 32&n;&t;&t;&t;&t;&t; * bit pointer to RPL with odd&n;&t;&t;&t;&t;&t; * forward pointer.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* Valid receive CSTAT: */
DECL|macro|RX_FRAME_CONTROL_BITS
mdefine_line|#define RX_FRAME_CONTROL_BITS (RX_VALID | RX_START_FRAME | RX_END_FRAME | &bslash;&n;&t;&t;&t;       RX_FRAME_COMPLETE)
DECL|macro|VALID_SINGLE_BUFFER_FRAME
mdefine_line|#define VALID_SINGLE_BUFFER_FRAME (RX_START_FRAME | RX_END_FRAME | &bslash;&n;&t;&t;&t;&t;   RX_FRAME_COMPLETE)
DECL|typedef|SKB_STAT
r_typedef
r_enum
id|SKB_STAT
id|SKB_STAT
suffix:semicolon
DECL|enum|SKB_STAT
r_enum
id|SKB_STAT
(brace
DECL|enumerator|SKB_UNAVAILABLE
id|SKB_UNAVAILABLE
comma
DECL|enumerator|SKB_DMA_DIRECT
id|SKB_DMA_DIRECT
comma
DECL|enumerator|SKB_DATA_COPY
id|SKB_DATA_COPY
)brace
suffix:semicolon
multiline_comment|/* Receive Parameter List (RPL) The length of the RPLs has to be initialized &n; * in the OPL. (OPEN parameter list)&n; */
DECL|macro|RPL_NUM
mdefine_line|#define RPL_NUM&t;&t;3
DECL|macro|RX_FRAG_NUM
mdefine_line|#define RX_FRAG_NUM     1&t;/* Maximal number of used fragments in one RPL.&n;&t;&t;&t;&t; * (up to firmware v2.24: 3, now: up to 9)&n;&t;&t;&t;&t; */
macro_line|#pragma pack(1)
DECL|typedef|RPL
r_typedef
r_struct
id|s_RPL
id|RPL
suffix:semicolon
DECL|struct|s_RPL
r_struct
id|s_RPL
(brace
multiline_comment|/* Receive Parameter List */
DECL|member|NextRPLAddr
id|u_int32_t
id|NextRPLAddr
suffix:semicolon
multiline_comment|/* Pointer to next RPL in chain&n;&t;&t;&t;&t;&t; * (normalized = physical 32 bit&n;&t;&t;&t;&t;&t; * address) if pointer is odd: this&n;&t;&t;&t;&t;&t; * is last RPL. Pointing to itself can&n;&t;&t;&t;&t;&t; * cause problems!&n;&t;&t;&t;&t;&t; */
DECL|member|Status
r_volatile
id|u_int16_t
id|Status
suffix:semicolon
multiline_comment|/* Set by creation of Receive Parameter&n;&t;&t;&t;&t;&t; * List RECEIVE_CSTAT_COMPLETE set by&n;&t;&t;&t;&t;&t; * adapter in lists that start or end&n;&t;&t;&t;&t;&t; * a frame.&n;&t;&t;&t;&t;&t; */
DECL|member|FrameSize
r_volatile
id|u_int16_t
id|FrameSize
suffix:semicolon
multiline_comment|/* Number of bytes received as a&n;&t;&t;&t;&t;&t; * frame including AC/FC, Destination,&n;&t;&t;&t;&t;&t; * Source, Routing field not including &n;&t;&t;&t;&t;&t; * CRC, FS (Frame Status), End Delimiter&n;&t;&t;&t;&t;&t; * (valid only if START_FRAME bit in &n;&t;&t;&t;&t;&t; * CSTAT nonzero) must not be zero in&n;&t;&t;&t;&t;&t; * any list; maximum value: (BUFFER_SIZE&n;&t;&t;&t;&t;&t; * - 8) * TX_BUF_MAX sum of DataCount&n;&t;&t;&t;&t;&t; * values in FragmentList must equal&n;&t;&t;&t;&t;&t; * Frame_Size value in START_FRAME TPL!&n;&t;&t;&t;&t;&t; * frame data fragment list&n;&t;&t;&t;&t;&t; */
multiline_comment|/* TPL/RPL size in OPEN parameter list depending on maximal numbers&n;&t; * of fragments used in one parameter list.&n;&t; */
DECL|member|FragList
id|Fragment
id|FragList
(braket
id|RX_FRAG_NUM
)braket
suffix:semicolon
multiline_comment|/* Maximum: nine frame fragments in&n;&t;&t;&t;&t;&t; * one TPL. Actual version of firmware:&n;&t;&t;&t;&t;&t; * 9 fragments possible.&n;&t;&t;&t;&t;&t; */
macro_line|#pragma pack()
multiline_comment|/* Special proprietary data and precalculations. */
DECL|member|NextRPLPtr
id|RPL
op_star
id|NextRPLPtr
suffix:semicolon
multiline_comment|/* Logical pointer to next RPL in chain. */
DECL|member|MData
r_int
r_char
op_star
id|MData
suffix:semicolon
DECL|member|Skb
r_struct
id|sk_buff
op_star
id|Skb
suffix:semicolon
DECL|member|SkbStat
id|SKB_STAT
id|SkbStat
suffix:semicolon
DECL|member|RPLIndex
r_int
id|RPLIndex
suffix:semicolon
DECL|member|DMABuff
id|dma_addr_t
id|DMABuff
suffix:semicolon
multiline_comment|/* DMA IO bus address from pci_map */
)brace
suffix:semicolon
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|net_local
r_typedef
r_struct
id|net_local
(brace
macro_line|#pragma pack(1)
DECL|member|ipb
id|IPB
id|ipb
suffix:semicolon
multiline_comment|/* Initialization Parameter Block. */
DECL|member|scb
id|SCB
id|scb
suffix:semicolon
multiline_comment|/* System Command Block: system to adapter &n;&t;&t;&t; * communication.&n;&t;&t;&t; */
DECL|member|ssb
id|SSB
id|ssb
suffix:semicolon
multiline_comment|/* System Status Block: adapter to system &n;&t;&t;&t; * communication.&n;&t;&t;&t; */
DECL|member|ocpl
id|OPB
id|ocpl
suffix:semicolon
multiline_comment|/* Open Options Parameter Block. */
DECL|member|errorlogtable
id|ERRORTAB
id|errorlogtable
suffix:semicolon
multiline_comment|/* Adapter statistic error counters.&n;&t;&t;&t;&t; * (read from adapter memory)&n;&t;&t;&t;&t; */
DECL|member|ProductID
r_int
r_char
id|ProductID
(braket
id|PROD_ID_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Product ID */
macro_line|#pragma pack()
DECL|member|Tpl
id|TPL
id|Tpl
(braket
id|TPL_NUM
)braket
suffix:semicolon
DECL|member|TplFree
id|TPL
op_star
id|TplFree
suffix:semicolon
DECL|member|TplBusy
id|TPL
op_star
id|TplBusy
suffix:semicolon
DECL|member|LocalTxBuffers
r_int
r_char
id|LocalTxBuffers
(braket
id|TPL_NUM
)braket
(braket
id|DEFAULT_PACKET_SIZE
)braket
suffix:semicolon
DECL|member|Rpl
id|RPL
id|Rpl
(braket
id|RPL_NUM
)braket
suffix:semicolon
DECL|member|RplHead
id|RPL
op_star
id|RplHead
suffix:semicolon
DECL|member|RplTail
id|RPL
op_star
id|RplTail
suffix:semicolon
DECL|member|LocalRxBuffers
r_int
r_char
id|LocalRxBuffers
(braket
id|RPL_NUM
)braket
(braket
id|DEFAULT_PACKET_SIZE
)braket
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|DataRate
r_int
id|DataRate
suffix:semicolon
DECL|member|ScbInUse
r_int
r_char
id|ScbInUse
suffix:semicolon
DECL|member|CMDqueue
r_int
r_int
id|CMDqueue
suffix:semicolon
DECL|member|AdapterOpenFlag
r_int
r_int
id|AdapterOpenFlag
suffix:colon
l_int|1
suffix:semicolon
DECL|member|AdapterVirtOpenFlag
r_int
r_int
id|AdapterVirtOpenFlag
suffix:colon
l_int|1
suffix:semicolon
DECL|member|OpenCommandIssued
r_int
r_int
id|OpenCommandIssued
suffix:colon
l_int|1
suffix:semicolon
DECL|member|TransmitCommandActive
r_int
r_int
id|TransmitCommandActive
suffix:colon
l_int|1
suffix:semicolon
DECL|member|TransmitHaltScheduled
r_int
r_int
id|TransmitHaltScheduled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HaltInProgress
r_int
r_int
id|HaltInProgress
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LobeWireFaultLogged
r_int
r_int
id|LobeWireFaultLogged
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ReOpenInProgress
r_int
r_int
id|ReOpenInProgress
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Sleeping
r_int
r_int
id|Sleeping
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LastOpenStatus
r_int
r_int
id|LastOpenStatus
suffix:semicolon
DECL|member|CurrentRingStatus
r_int
r_int
id|CurrentRingStatus
suffix:semicolon
DECL|member|MaxPacketSize
r_int
r_int
id|MaxPacketSize
suffix:semicolon
DECL|member|StartTime
r_int
r_int
id|StartTime
suffix:semicolon
DECL|member|LastSendTime
r_int
r_int
id|LastSendTime
suffix:semicolon
DECL|member|SendSkbQueue
r_struct
id|sk_buff_head
id|SendSkbQueue
suffix:semicolon
DECL|member|QueueSkb
r_int
r_int
id|QueueSkb
suffix:semicolon
DECL|member|MacStat
r_struct
id|tr_statistics
id|MacStat
suffix:semicolon
multiline_comment|/* MAC statistics structure */
DECL|member|dmalimit
r_int
r_int
id|dmalimit
suffix:semicolon
multiline_comment|/* the max DMA address (ie, ISA) */
DECL|member|dmabuffer
id|dma_addr_t
id|dmabuffer
suffix:semicolon
multiline_comment|/* the DMA bus address corresponding to&n;&t;&t;&t;&t;    priv. Might be different from virt_to_bus()&n;&t;&t;&t;&t;    for architectures with IO MMU (Alpha) */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|wait_for_tok_int
id|wait_queue_head_t
id|wait_for_tok_int
suffix:semicolon
DECL|member|intptrs
id|INTPTRS
id|intptrs
suffix:semicolon
multiline_comment|/* Internal adapter pointer. Must be read&n;&t;&t;&t;&t; * before OPEN command.&n;&t;&t;&t;&t; */
DECL|member|setnselout
r_int
r_int
(paren
op_star
id|setnselout
)paren
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|sifreadb
r_int
r_int
(paren
op_star
id|sifreadb
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|sifwriteb
r_void
(paren
op_star
id|sifwriteb
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|sifreadw
r_int
r_int
(paren
op_star
id|sifreadw
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|sifwritew
r_void
(paren
op_star
id|sifwritew
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|tmspriv
r_void
op_star
id|tmspriv
suffix:semicolon
DECL|typedef|NET_LOCAL
)brace
id|NET_LOCAL
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_TMS380TR_H */
eof
