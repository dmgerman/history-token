multiline_comment|/*&n; * DTC controller, taken from T128 driver by...&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * DISTRIBUTION RELEASE 2. &n; *&n; * For more information, please consult &n; *&n; * &n; * &n; * and &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
macro_line|#ifndef DTC3280_H
DECL|macro|DTC3280_H
mdefine_line|#define DTC3280_H
r_static
r_int
id|dtc_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtc_biosparam
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtc_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtc_queue_command
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
r_static
r_int
id|dtc_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtc_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|dtc_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 2
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 32 
macro_line|#endif
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    void __iomem *base
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;    void __iomem *base
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;    base = ((struct NCR5380_hostdata *)(instance)-&gt;hostdata)-&gt;base
DECL|macro|DTC_address
mdefine_line|#define DTC_address(reg) (base + DTC_5380_OFFSET + reg)
DECL|macro|dbNCR5380_read
mdefine_line|#define dbNCR5380_read(reg)                                              &bslash;&n;    (rval=readb(DTC_address(reg)), &bslash;&n;     (((unsigned char) printk(&quot;DTC : read register %d at addr %p is: %02x&bslash;n&quot;&bslash;&n;    , (reg), DTC_address(reg), rval)), rval ) )
DECL|macro|dbNCR5380_write
mdefine_line|#define dbNCR5380_write(reg, value) do {                                  &bslash;&n;    printk(&quot;DTC : write %02x to register %d at address %p&bslash;n&quot;,         &bslash;&n;            (value), (reg), DTC_address(reg));     &bslash;&n;    writeb(value, DTC_address(reg));} while(0)
macro_line|#if !(DTCDEBUG &amp; DTCDEBUG_TRANSFER) 
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) (readb(DTC_address(reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) (writeb(value, DTC_address(reg)))
macro_line|#else
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) (readb(DTC_address(reg)))
DECL|macro|xNCR5380_read
mdefine_line|#define xNCR5380_read(reg)&t;&t;&t;&t;&t;&t;&bslash;&n;    (((unsigned char) printk(&quot;DTC : read register %d at address %p&bslash;n&quot;&bslash;&n;    , (reg), DTC_address(reg))), readb(DTC_address(reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) do {&t;&t;&t;&t;&t;&bslash;&n;    printk(&quot;DTC : write %02x to register %d at address %p&bslash;n&quot;, &t;&bslash;&n;&t;    (value), (reg), DTC_address(reg));&t;&bslash;&n;    writeb(value, DTC_address(reg));} while(0)
macro_line|#endif
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr&t;&t;&t;dtc_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command&t;&t;dtc_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort&t;&t;&t;dtc_abort
DECL|macro|NCR5380_bus_reset
mdefine_line|#define NCR5380_bus_reset&t;&t;dtc_bus_reset
DECL|macro|NCR5380_device_reset
mdefine_line|#define NCR5380_device_reset&t;&t;dtc_device_reset
DECL|macro|NCR5380_host_reset
mdefine_line|#define NCR5380_host_reset&t;&t;dtc_host_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info&t;&t;dtc_proc_info 
multiline_comment|/* 15 12 11 10&n;   1001 1100 0000 0000 */
DECL|macro|DTC_IRQS
mdefine_line|#define DTC_IRQS 0x9c00
macro_line|#endif /* DTC3280_H */
eof
