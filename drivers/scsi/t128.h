multiline_comment|/*&n; * Trantor T128/T128F/T228 defines&n; *&t;Note : architecturally, the T100 and T128 are different and won&squot;t work&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * DISTRIBUTION RELEASE 3. &n; *&n; * For more information, please consult &n; *&n; * Trantor Systems, Ltd.&n; * T128/T128F/T228 SCSI Host Adapter&n; * Hardware Specifications&n; * &n; * Trantor Systems, Ltd. &n; * 5415 Randall Place&n; * Fremont, CA 94538&n; * 1+ (415) 770-1400, FAX 1+ (415) 770-9910&n; * &n; * and &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: t128.h,v $&n; */
macro_line|#ifndef T128_H
DECL|macro|T128_H
mdefine_line|#define T128_H
DECL|macro|T128_PUBLIC_RELEASE
mdefine_line|#define T128_PUBLIC_RELEASE 3
DECL|macro|TDEBUG_INIT
mdefine_line|#define TDEBUG_INIT&t;0x1
DECL|macro|TDEBUG_TRANSFER
mdefine_line|#define TDEBUG_TRANSFER 0x2
multiline_comment|/*&n; * The trantor boards are memory mapped. They use an NCR5380 or &n; * equivalent (my sample board had part second sourced from ZILOG).&n; * NCR&squot;s recommended &quot;Pseudo-DMA&quot; architecture is used, where &n; * a PAL drives the DMA signals on the 5380 allowing fast, blind&n; * transfers with proper handshaking. &n; */
multiline_comment|/*&n; * Note : a boot switch is provided for the purpose of informing the &n; * firmware to boot or not boot from attached SCSI devices.  So, I imagine&n; * there are fewer people who&squot;ve yanked the ROM like they do on the Seagate&n; * to make bootup faster, and I&squot;ll probably use this for autodetection.&n; */
DECL|macro|T_ROM_OFFSET
mdefine_line|#define T_ROM_OFFSET&t;&t;0
multiline_comment|/*&n; * Note : my sample board *WAS NOT* populated with the SRAM, so this&n; * can&squot;t be used for autodetection without a ROM present.&n; */
DECL|macro|T_RAM_OFFSET
mdefine_line|#define T_RAM_OFFSET&t;&t;0x1800
multiline_comment|/*&n; * All of the registers are allocated 32 bytes of address space, except&n; * for the data register (read/write to/from the 5380 in pseudo-DMA mode)&n; */
DECL|macro|T_CONTROL_REG_OFFSET
mdefine_line|#define T_CONTROL_REG_OFFSET&t;0x1c00&t;/* rw */
DECL|macro|T_CR_INT
mdefine_line|#define T_CR_INT&t;&t;0x10&t;/* Enable interrupts */
DECL|macro|T_CR_CT
mdefine_line|#define T_CR_CT&t;&t;&t;0x02&t;/* Reset watchdog timer */
DECL|macro|T_STATUS_REG_OFFSET
mdefine_line|#define T_STATUS_REG_OFFSET&t;0x1c20&t;/* ro */
DECL|macro|T_ST_BOOT
mdefine_line|#define T_ST_BOOT&t;&t;0x80&t;/* Boot switch */
DECL|macro|T_ST_S3
mdefine_line|#define T_ST_S3&t;&t;&t;0x40&t;/* User settable switches, */
DECL|macro|T_ST_S2
mdefine_line|#define T_ST_S2&t;&t;&t;0x20&t;/* read 0 when switch is on, 1 off */
DECL|macro|T_ST_S1
mdefine_line|#define T_ST_S1&t;&t;&t;0x10
DECL|macro|T_ST_PS2
mdefine_line|#define T_ST_PS2&t;&t;0x08&t;/* Set for Microchannel 228 */
DECL|macro|T_ST_RDY
mdefine_line|#define T_ST_RDY&t;&t;0x04&t;/* 5380 DRQ */
DECL|macro|T_ST_TIM
mdefine_line|#define T_ST_TIM&t;&t;0x02&t;/* indicates 40us watchdog timer fired */
DECL|macro|T_ST_ZERO
mdefine_line|#define T_ST_ZERO&t;&t;0x01&t;/* Always zero */
DECL|macro|T_5380_OFFSET
mdefine_line|#define T_5380_OFFSET&t;&t;0x1d00&t;/* 8 registers here, see NCR5380.h */
DECL|macro|T_DATA_REG_OFFSET
mdefine_line|#define T_DATA_REG_OFFSET&t;0x1e00&t;/* rw 512 bytes long */
macro_line|#ifndef ASM
r_int
id|t128_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|t128_biosparam
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
id|t128_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|t128_queue_command
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
id|t128_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
id|reset_flags
)paren
suffix:semicolon
r_int
id|t128_proc_info
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
DECL|macro|TRANTOR_T128
mdefine_line|#define TRANTOR_T128 {&t;&t;&t;&t;&t;&bslash;&n;&t;name:           &quot;Trantor T128/T128F/T228&quot;,&t;&bslash;&n;&t;detect:         t128_detect,&t;&t;&t;&bslash;&n;&t;queuecommand:   t128_queue_command,&t;&t;&bslash;&n;&t;abort:          t128_abort,&t;&t;&t;&bslash;&n;&t;reset:          t128_reset,&t;&t;&t;&bslash;&n;&t;bios_param:     t128_biosparam,&t;&t;&t;&bslash;&n;&t;can_queue:      CAN_QUEUE,&t;&t;&t;&bslash;&n;        this_id:        7,&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:   SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:    CMD_PER_LUN,&t;&t;&t;&bslash;&n;&t;use_clustering: DISABLE_CLUSTERING}
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    unsigned long base
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;    unsigned long base
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;    base = (instance)-&gt;base
DECL|macro|T128_address
mdefine_line|#define T128_address(reg) (base + T_5380_OFFSET + ((reg) * 0x20))
macro_line|#if !(TDEBUG &amp; TDEBUG_TRANSFER) 
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) isa_readb(T128_address(reg))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) isa_writeb((value),(T128_address(reg)))
macro_line|#else
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;&t;&t;&t;&t;&bslash;&n;    (((unsigned char) printk(&quot;scsi%d : read register %d at address %08x&bslash;n&quot;&bslash;&n;    , instance-&gt;hostno, (reg), T128_address(reg))), isa_readb(T128_address(reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) {&t;&t;&t;&t;&t;&bslash;&n;    printk(&quot;scsi%d : write %02x to register %d at address %08x&bslash;n&quot;, &t;&bslash;&n;&t;    instance-&gt;hostno, (value), (reg), T128_address(reg));&t;&bslash;&n;    isa_writeb((value), (T128_address(reg)));&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr t128_intr
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr do_t128_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command t128_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort t128_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset t128_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info t128_proc_info
multiline_comment|/* 15 14 12 10 7 5 3 &n;   1101 0100 1010 1000 */
DECL|macro|T128_IRQS
mdefine_line|#define T128_IRQS 0xc4a8 
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* T128_H */
eof
