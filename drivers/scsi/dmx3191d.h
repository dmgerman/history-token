multiline_comment|/*&n;    dmx3191d.h - defines for the Domex DMX3191D SCSI card.&n;    Copyright (C) 2000 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;*/
macro_line|#ifndef __DMX3191D_H
DECL|macro|__DMX3191D_H
mdefine_line|#define __DMX3191D_H
DECL|macro|DMX3191D_DRIVER_NAME
mdefine_line|#define DMX3191D_DRIVER_NAME&t;&quot;dmx3191d&quot;
DECL|macro|DMX3191D_REGION
mdefine_line|#define DMX3191D_REGION&t;&t;8
macro_line|#ifndef PCI_VENDOR_ID_DOMEX
DECL|macro|PCI_VENDOR_ID_DOMEX
mdefine_line|#define PCI_VENDOR_ID_DOMEX&t;&t;0x134a
DECL|macro|PCI_DEVICE_ID_DOMEX_DMX3191D
mdefine_line|#define PCI_DEVICE_ID_DOMEX_DMX3191D&t;0x0001
macro_line|#endif
DECL|macro|dmx3191d_printk
mdefine_line|#define dmx3191d_printk( args... )&t;printk(__FILE__&quot;: &quot; ##args)
macro_line|#ifndef ASM
r_int
id|dmx3191d_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|dmx3191d_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|dmx3191d_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|dmx3191d_proc_info
c_func
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
r_int
id|dmx3191d_queue_command
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
id|dmx3191d_release_resources
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|dmx3191d_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|DMX3191D
mdefine_line|#define DMX3191D {&t;&t;&t;&t;&bslash;&n;&t;proc_info:&t;dmx3191d_proc_info,&t;&t;&bslash;&n;&t;name:&t;&t;&quot;Domex DMX3191D&quot;,&t;&t;&bslash;&n;&t;detect:&t;&t;dmx3191d_detect,&t;&t;&bslash;&n;&t;release:&t;dmx3191d_release_resources,&t;&bslash;&n;&t;info:&t;&t;dmx3191d_info,&t;&t;&t;&bslash;&n;&t;queuecommand:&t;dmx3191d_queue_command,&t;&t;&bslash;&n;&t;abort:&t;&t;dmx3191d_abort,&t;&t;&t;&bslash;&n;&t;reset:&t;&t;dmx3191d_reset, &t;&t;&bslash;&n;&t;bios_param:&t;NULL,&t;&t;&t;&t;&bslash;&n;&t;can_queue:&t;32,&t;&t;&t;&t;&bslash;&n;        this_id:&t;7,&t;&t;&t;&t;&bslash;&n;        sg_tablesize:&t;SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;2,&t;&t;&t;&t;&bslash;&n;        use_clustering:&t;DISABLE_CLUSTERING&t;&t;&bslash;&n;}
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;&t;inb(port + reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value)&t;&t;outb(value, port + reg)
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields&t;&t;unsigned int port
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare()&t;&t;&t;NCR5380_implementation_fields
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance)&t;&t;&t;port = instance-&gt;io_port
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort&t;&t;&t;&t;dmx3191d_abort
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr&t;&t;&t;&t;dmx3191d_do_intr
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr&t;&t;&t;&t;dmx3191d_intr
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info&t;&t;&t;dmx3191d_proc_info
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command&t;&t;&t;dmx3191d_queue_command
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset&t;&t;&t;&t;dmx3191d_reset
macro_line|#endif&t;/* ASM */
macro_line|#endif&t;/* __DMX3191D_H */
eof
