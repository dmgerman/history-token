multiline_comment|/* Driver for SCM Microsystems USB-ATAPI cable&n; * Header File&n; *&n; * $Id: shuttle_usbat.h,v 1.5 2000/09/17 14:44:52 groovyjava Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 Robert Baruch (autophile@dol.net)&n; *&n; * See scm.c for more explanation&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_SHUTTLE_USBAT_H
DECL|macro|_USB_SHUTTLE_USBAT_H
mdefine_line|#define _USB_SHUTTLE_USBAT_H
DECL|macro|USBAT_EPP_PORT
mdefine_line|#define USBAT_EPP_PORT&t;&t;0x10
DECL|macro|USBAT_EPP_REGISTER
mdefine_line|#define USBAT_EPP_REGISTER&t;0x30
DECL|macro|USBAT_ATA
mdefine_line|#define USBAT_ATA&t;&t;0x40
DECL|macro|USBAT_ISA
mdefine_line|#define USBAT_ISA&t;&t;0x50
multiline_comment|/* SCM User I/O Data registers */
DECL|macro|USBAT_UIO_EPAD
mdefine_line|#define USBAT_UIO_EPAD&t;&t;0x80 
singleline_comment|// Enable Peripheral Control Signals
DECL|macro|USBAT_UIO_CDT
mdefine_line|#define USBAT_UIO_CDT&t;&t;0x40 
singleline_comment|// Card Detect (Read Only)
singleline_comment|// CDT = ACKD &amp; !UI1 &amp; !UI0
DECL|macro|USBAT_UIO_1
mdefine_line|#define USBAT_UIO_1&t;&t;0x20 
singleline_comment|// I/O 1
DECL|macro|USBAT_UIO_0
mdefine_line|#define USBAT_UIO_0&t;&t;0x10 
singleline_comment|// I/O 0
DECL|macro|USBAT_UIO_EPP_ATA
mdefine_line|#define USBAT_UIO_EPP_ATA&t;0x08 
singleline_comment|// 1=EPP mode, 0=ATA mode
DECL|macro|USBAT_UIO_UI1
mdefine_line|#define USBAT_UIO_UI1&t;&t;0x04 
singleline_comment|// Input 1
DECL|macro|USBAT_UIO_UI0
mdefine_line|#define USBAT_UIO_UI0&t;&t;0x02 
singleline_comment|// Input 0
DECL|macro|USBAT_UIO_INTR_ACK
mdefine_line|#define USBAT_UIO_INTR_ACK&t;0x01 
singleline_comment|// Interrupt (ATA &amp; ISA)/Acknowledge (EPP)
multiline_comment|/* SCM User I/O Enable registers */
DECL|macro|USBAT_UIO_DRVRST
mdefine_line|#define USBAT_UIO_DRVRST&t;0x80 
singleline_comment|// Reset Peripheral
DECL|macro|USBAT_UIO_ACKD
mdefine_line|#define USBAT_UIO_ACKD&t;&t;0x40 
singleline_comment|// Enable Card Detect
DECL|macro|USBAT_UIO_OE1
mdefine_line|#define USBAT_UIO_OE1&t;&t;0x20 
singleline_comment|// I/O 1 set=output/clr=input
singleline_comment|// If ACKD=1, set OE1 to 1 also.
DECL|macro|USBAT_UIO_OE0
mdefine_line|#define USBAT_UIO_OE0&t;&t;0x10 
singleline_comment|// I/O 0 set=output/clr=input
DECL|macro|USBAT_UIO_ADPRST
mdefine_line|#define USBAT_UIO_ADPRST&t;0x01 
singleline_comment|// Reset SCM chip
multiline_comment|/* USBAT-specific commands */
r_extern
r_int
id|usbat_read
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
id|access
comma
r_int
r_char
id|reg
comma
r_int
r_char
op_star
id|content
)paren
suffix:semicolon
r_extern
r_int
id|usbat_write
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
id|access
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|content
)paren
suffix:semicolon
r_extern
r_int
id|usbat_read_block
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
id|access
comma
r_int
r_char
id|reg
comma
r_int
r_char
op_star
id|content
comma
r_int
r_int
id|len
comma
r_int
id|use_sg
)paren
suffix:semicolon
r_extern
r_int
id|usbat_write_block
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
id|access
comma
r_int
r_char
id|reg
comma
r_int
r_char
op_star
id|content
comma
r_int
r_int
id|len
comma
r_int
id|use_sg
comma
r_int
id|minutes
)paren
suffix:semicolon
r_extern
r_int
id|usbat_multiple_write
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
id|access
comma
r_int
r_char
op_star
id|registers
comma
r_int
r_char
op_star
id|data_out
comma
r_int
r_int
id|num_registers
)paren
suffix:semicolon
r_extern
r_int
id|usbat_read_user_io
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
op_star
id|data_flags
)paren
suffix:semicolon
r_extern
r_int
id|usbat_write_user_io
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
id|enable_flags
comma
r_int
r_char
id|data_flags
)paren
suffix:semicolon
multiline_comment|/* HP 8200e stuff */
r_extern
r_int
id|hp8200e_transport
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
suffix:semicolon
r_extern
r_int
id|init_8200e
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
suffix:semicolon
macro_line|#endif
eof
