multiline_comment|/*&n; * This driver adapted from Drew Eckhardt&squot;s Trantor T128 driver&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 666-5836&n; *&n; *  ( Based on T128 - DISTRIBUTION RELEASE 3. ) &n; *&n; * Modified to work with the Pro Audio Spectrum/Studio 16&n; * by John Weidman.&n; *&n; *&n; * For more information, please consult &n; *&n; * Media Vision&n; * (510) 770-8600&n; * (800) 348-7116&n; * &n; * and &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
macro_line|#ifndef PAS16_H
DECL|macro|PAS16_H
mdefine_line|#define PAS16_H
DECL|macro|PAS16_PUBLIC_RELEASE
mdefine_line|#define PAS16_PUBLIC_RELEASE 3
DECL|macro|PDEBUG_INIT
mdefine_line|#define PDEBUG_INIT&t;0x1
DECL|macro|PDEBUG_TRANSFER
mdefine_line|#define PDEBUG_TRANSFER 0x2
DECL|macro|PAS16_DEFAULT_BASE_1
mdefine_line|#define PAS16_DEFAULT_BASE_1  0x388
DECL|macro|PAS16_DEFAULT_BASE_2
mdefine_line|#define PAS16_DEFAULT_BASE_2  0x384
DECL|macro|PAS16_DEFAULT_BASE_3
mdefine_line|#define PAS16_DEFAULT_BASE_3  0x38c
DECL|macro|PAS16_DEFAULT_BASE_4
mdefine_line|#define PAS16_DEFAULT_BASE_4  0x288
DECL|macro|PAS16_DEFAULT_BOARD_1_IRQ
mdefine_line|#define PAS16_DEFAULT_BOARD_1_IRQ 10
DECL|macro|PAS16_DEFAULT_BOARD_2_IRQ
mdefine_line|#define PAS16_DEFAULT_BOARD_2_IRQ 12
DECL|macro|PAS16_DEFAULT_BOARD_3_IRQ
mdefine_line|#define PAS16_DEFAULT_BOARD_3_IRQ 14
DECL|macro|PAS16_DEFAULT_BOARD_4_IRQ
mdefine_line|#define PAS16_DEFAULT_BOARD_4_IRQ 15
multiline_comment|/*&n; * The Pro Audio Spectrum boards are I/O mapped. They use a Zilog 5380&n; * SCSI controller, which is the equivalent of NCR&squot;s 5380.  &quot;Pseudo-DMA&quot;&n; * architecture is used, where a PAL drives the DMA signals on the 5380&n; * allowing fast, blind transfers with proper handshaking. &n; */
multiline_comment|/* The Time-out Counter register is used to safe-guard against a stuck&n; * bus (in the case of RDY driven handshake) or a stuck byte (if 16-Bit&n; * DMA conversion is used).  The counter uses a 28.224MHz clock&n; * divided by 14 as its clock source.  In the case of a stuck byte in&n; * the holding register, an interrupt is generated (and mixed with the&n; * one with the drive) using the CD-ROM interrupt pointer.&n; */
DECL|macro|P_TIMEOUT_COUNTER_REG
mdefine_line|#define P_TIMEOUT_COUNTER_REG&t;0x4000
DECL|macro|P_TC_DISABLE
mdefine_line|#define P_TC_DISABLE&t;0x80&t;/* Set to 0 to enable timeout int. */
multiline_comment|/* Bits D6-D0 contain timeout count */
DECL|macro|P_TIMEOUT_STATUS_REG_OFFSET
mdefine_line|#define P_TIMEOUT_STATUS_REG_OFFSET&t;0x4001
DECL|macro|P_TS_TIM
mdefine_line|#define P_TS_TIM&t;&t;0x80&t;/* check timeout status */
multiline_comment|/* Bits D6-D4 N/U */
DECL|macro|P_TS_ARM_DRQ_INT
mdefine_line|#define P_TS_ARM_DRQ_INT&t;0x08&t;/* Arm DRQ Int.  When set high,&n;&t;&t;&t;&t;&t; * the next rising edge will&n;&t;&t;&t;&t;&t; * cause a CD-ROM interrupt.&n;&t;&t;&t;&t;&t; * When set low, the interrupt&n;&t;&t;&t;&t;&t; * will be cleared.  There is&n;&t;&t;&t;&t;&t; * no status available for&n;&t;&t;&t;&t;&t; * this interrupt.&n;&t;&t;&t;&t;&t; */
DECL|macro|P_TS_ENABLE_TO_ERR_INTERRUPT
mdefine_line|#define P_TS_ENABLE_TO_ERR_INTERRUPT&t;/* Enable timeout error int. */
DECL|macro|P_TS_ENABLE_WAIT
mdefine_line|#define P_TS_ENABLE_WAIT&t;&t;/* Enable Wait */
DECL|macro|P_TS_CT
mdefine_line|#define P_TS_CT&t;&t;&t;0x01&t;/* clear timeout. Note: writing&n;&t;&t;&t;&t;&t; * to this register clears the&n;&t;&t;&t;&t;&t; * timeout error int. or status&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * The data register reads/writes to/from the 5380 in pseudo-DMA mode&n; */
DECL|macro|P_DATA_REG_OFFSET
mdefine_line|#define P_DATA_REG_OFFSET&t;0x5c00&t;/* rw */
DECL|macro|P_STATUS_REG_OFFSET
mdefine_line|#define P_STATUS_REG_OFFSET&t;0x5c01&t;/* ro */
DECL|macro|P_ST_RDY
mdefine_line|#define P_ST_RDY&t;&t;0x80&t;/* 5380 DDRQ Status */
DECL|macro|P_IRQ_STATUS
mdefine_line|#define P_IRQ_STATUS&t;&t;0x5c03
DECL|macro|P_IS_IRQ
mdefine_line|#define P_IS_IRQ&t;&t;0x80&t;/* DIRQ status */
DECL|macro|PCB_CONFIG
mdefine_line|#define PCB_CONFIG 0x803
DECL|macro|MASTER_ADDRESS_PTR
mdefine_line|#define MASTER_ADDRESS_PTR 0x9a01  /* Fixed position - no relo */
DECL|macro|SYS_CONFIG_4
mdefine_line|#define SYS_CONFIG_4 0x8003
DECL|macro|WAIT_STATE
mdefine_line|#define WAIT_STATE 0xbc00
DECL|macro|OPERATION_MODE_1
mdefine_line|#define OPERATION_MODE_1 0xec03
DECL|macro|IO_CONFIG_3
mdefine_line|#define IO_CONFIG_3 0xf002
macro_line|#ifndef ASM
r_int
id|pas16_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|pas16_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|pas16_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|pas16_queue_command
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
r_int
id|pas16_reset
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
id|pas16_proc_info
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
mdefine_line|#define CAN_QUEUE 32 
macro_line|#endif
multiline_comment|/* &n; * I hadn&squot;t thought of this with the earlier drivers - but to prevent&n; * macro definition conflicts, we shouldn&squot;t define all of the internal&n; * macros when this is being used solely for the host stub.&n; */
DECL|macro|MV_PAS16
mdefine_line|#define MV_PAS16 {&t;&t;&t;&t;&t;&bslash;&n;&t;name:           &quot;Pro Audio Spectrum-16 SCSI&quot;, &t;&bslash;&n;&t;detect:         pas16_detect, &t;&t;&t;&bslash;&n;&t;queuecommand:   pas16_queue_command,&t;&t;&bslash;&n;&t;abort:          pas16_abort,&t;&t;&t;&bslash;&n;&t;reset:          pas16_reset,&t;&t;&t;&bslash;&n;&t;bios_param:     pas16_biosparam, &t;&t;&bslash;&n;&t;can_queue:      CAN_QUEUE,&t;&t;&t;&bslash;&n;&t;this_id:        7,&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:   SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:    CMD_PER_LUN ,&t;&t;&t;&bslash;&n;&t;use_clustering: DISABLE_CLUSTERING}
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    volatile unsigned short io_port
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;    volatile unsigned short io_port
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;    io_port = (instance)-&gt;io_port
DECL|macro|PAS16_io_port
mdefine_line|#define PAS16_io_port(reg) ( io_port + pas16_offset[(reg)] )
macro_line|#if !(PDEBUG &amp; PDEBUG_TRANSFER) 
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) ( inb(PAS16_io_port(reg)) )
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) ( outb((value),PAS16_io_port(reg)) )
macro_line|#else
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;&t;&t;&t;&t;&bslash;&n;    (((unsigned char) printk(&quot;scsi%d : read register %d at io_port %04x&bslash;n&quot;&bslash;&n;    , instance-&gt;hostno, (reg), PAS16_io_port(reg))), inb( PAS16_io_port(reg)) )
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) &t;&t;&t;&t;&t;&bslash;&n;    (printk(&quot;scsi%d : write %02x to register %d at io_port %04x&bslash;n&quot;, &t;&bslash;&n;&t;    instance-&gt;hostno, (value), (reg), PAS16_io_port(reg)),&t;&bslash;&n;    outb( (value),PAS16_io_port(reg) ) )
macro_line|#endif
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr pas16_intr
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr do_pas16_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command pas16_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort pas16_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset pas16_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info pas16_proc_info
multiline_comment|/* 15 14 12 10 7 5 3 &n;   1101 0100 1010 1000 */
DECL|macro|PAS16_IRQS
mdefine_line|#define PAS16_IRQS 0xd4a8 
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* PAS16_H */
eof
