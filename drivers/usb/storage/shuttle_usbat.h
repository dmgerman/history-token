multiline_comment|/* Driver for SCM Microsystems USB-ATAPI cable&n; * Header File&n; *&n; * $Id: shuttle_usbat.h,v 1.5 2000/09/17 14:44:52 groovyjava Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 Robert Baruch (autophile@dol.net)&n; *   (c) 2004, 2005 Daniel Drake &lt;dsd@gentoo.org&gt;&n; *&n; * See shuttle_usbat.c for more explanation&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_SHUTTLE_USBAT_H
DECL|macro|_USB_SHUTTLE_USBAT_H
mdefine_line|#define _USB_SHUTTLE_USBAT_H
multiline_comment|/* Supported device types */
DECL|macro|USBAT_DEV_HP8200
mdefine_line|#define USBAT_DEV_HP8200&t;0x01
DECL|macro|USBAT_DEV_FLASH
mdefine_line|#define USBAT_DEV_FLASH&t;&t;0x02
DECL|macro|USBAT_EPP_PORT
mdefine_line|#define USBAT_EPP_PORT&t;&t;0x10
DECL|macro|USBAT_EPP_REGISTER
mdefine_line|#define USBAT_EPP_REGISTER&t;0x30
DECL|macro|USBAT_ATA
mdefine_line|#define USBAT_ATA&t;&t;0x40
DECL|macro|USBAT_ISA
mdefine_line|#define USBAT_ISA&t;&t;0x50
multiline_comment|/* Commands (need to be logically OR&squot;d with an access type */
DECL|macro|USBAT_CMD_READ_REG
mdefine_line|#define USBAT_CMD_READ_REG&t;&t;0x00
DECL|macro|USBAT_CMD_WRITE_REG
mdefine_line|#define USBAT_CMD_WRITE_REG&t;&t;0x01
DECL|macro|USBAT_CMD_READ_BLOCK
mdefine_line|#define USBAT_CMD_READ_BLOCK&t;0x02
DECL|macro|USBAT_CMD_WRITE_BLOCK
mdefine_line|#define USBAT_CMD_WRITE_BLOCK&t;0x03
DECL|macro|USBAT_CMD_COND_READ_BLOCK
mdefine_line|#define USBAT_CMD_COND_READ_BLOCK&t;0x04
DECL|macro|USBAT_CMD_COND_WRITE_BLOCK
mdefine_line|#define USBAT_CMD_COND_WRITE_BLOCK&t;0x05
DECL|macro|USBAT_CMD_WRITE_REGS
mdefine_line|#define USBAT_CMD_WRITE_REGS&t;0x07
multiline_comment|/* Commands (these don&squot;t need an access type) */
DECL|macro|USBAT_CMD_EXEC_CMD
mdefine_line|#define USBAT_CMD_EXEC_CMD&t;0x80
DECL|macro|USBAT_CMD_SET_FEAT
mdefine_line|#define USBAT_CMD_SET_FEAT&t;0x81
DECL|macro|USBAT_CMD_UIO
mdefine_line|#define USBAT_CMD_UIO&t;&t;0x82
multiline_comment|/* Methods of accessing UIO register */
DECL|macro|USBAT_UIO_READ
mdefine_line|#define USBAT_UIO_READ&t;1
DECL|macro|USBAT_UIO_WRITE
mdefine_line|#define USBAT_UIO_WRITE&t;0
multiline_comment|/* Qualifier bits */
DECL|macro|USBAT_QUAL_FCQ
mdefine_line|#define USBAT_QUAL_FCQ&t;0x20 
singleline_comment|// full compare
DECL|macro|USBAT_QUAL_ALQ
mdefine_line|#define USBAT_QUAL_ALQ&t;0x10 
singleline_comment|// auto load subcount
multiline_comment|/* USBAT Flash Media status types */
DECL|macro|USBAT_FLASH_MEDIA_NONE
mdefine_line|#define USBAT_FLASH_MEDIA_NONE&t;0
DECL|macro|USBAT_FLASH_MEDIA_CF
mdefine_line|#define USBAT_FLASH_MEDIA_CF&t;1
multiline_comment|/* USBAT Flash Media change types */
DECL|macro|USBAT_FLASH_MEDIA_SAME
mdefine_line|#define USBAT_FLASH_MEDIA_SAME&t;0
DECL|macro|USBAT_FLASH_MEDIA_CHANGED
mdefine_line|#define USBAT_FLASH_MEDIA_CHANGED&t;1
multiline_comment|/* USBAT ATA registers */
DECL|macro|USBAT_ATA_DATA
mdefine_line|#define USBAT_ATA_DATA      0x10  
singleline_comment|// read/write data (R/W)
DECL|macro|USBAT_ATA_FEATURES
mdefine_line|#define USBAT_ATA_FEATURES  0x11  
singleline_comment|// set features (W)
DECL|macro|USBAT_ATA_ERROR
mdefine_line|#define USBAT_ATA_ERROR     0x11  
singleline_comment|// error (R)
DECL|macro|USBAT_ATA_SECCNT
mdefine_line|#define USBAT_ATA_SECCNT    0x12  
singleline_comment|// sector count (R/W)
DECL|macro|USBAT_ATA_SECNUM
mdefine_line|#define USBAT_ATA_SECNUM    0x13  
singleline_comment|// sector number (R/W)
DECL|macro|USBAT_ATA_LBA_ME
mdefine_line|#define USBAT_ATA_LBA_ME    0x14  
singleline_comment|// cylinder low (R/W)
DECL|macro|USBAT_ATA_LBA_HI
mdefine_line|#define USBAT_ATA_LBA_HI    0x15  
singleline_comment|// cylinder high (R/W)
DECL|macro|USBAT_ATA_DEVICE
mdefine_line|#define USBAT_ATA_DEVICE    0x16  
singleline_comment|// head/device selection (R/W)
DECL|macro|USBAT_ATA_STATUS
mdefine_line|#define USBAT_ATA_STATUS    0x17  
singleline_comment|// device status (R)
DECL|macro|USBAT_ATA_CMD
mdefine_line|#define USBAT_ATA_CMD       0x17  
singleline_comment|// device command (W)
DECL|macro|USBAT_ATA_ALTSTATUS
mdefine_line|#define USBAT_ATA_ALTSTATUS 0x0E  
singleline_comment|// status (no clear IRQ) (R)
multiline_comment|/* USBAT User I/O Data registers */
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
multiline_comment|/* USBAT User I/O Enable registers */
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
multiline_comment|/* USBAT Features */
DECL|macro|USBAT_FEAT_ETEN
mdefine_line|#define USBAT_FEAT_ETEN&t;0x80 
singleline_comment|// External trigger enable
DECL|macro|USBAT_FEAT_U1
mdefine_line|#define USBAT_FEAT_U1&t;0x08
DECL|macro|USBAT_FEAT_U0
mdefine_line|#define USBAT_FEAT_U0&t;0x04
DECL|macro|USBAT_FEAT_ET1
mdefine_line|#define USBAT_FEAT_ET1&t;0x02
DECL|macro|USBAT_FEAT_ET2
mdefine_line|#define USBAT_FEAT_ET2&t;0x01
multiline_comment|/* Transport functions */
r_int
id|usbat_hp8200e_transport
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
suffix:semicolon
r_int
id|usbat_flash_transport
c_func
(paren
r_struct
id|scsi_cmnd
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
id|usbat_transport
c_func
(paren
r_struct
id|scsi_cmnd
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
id|init_usbat
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
suffix:semicolon
DECL|struct|usbat_info
r_struct
id|usbat_info
(brace
DECL|member|devicetype
r_int
id|devicetype
suffix:semicolon
multiline_comment|/* Used for Flash readers only */
DECL|member|sectors
r_int
r_int
id|sectors
suffix:semicolon
singleline_comment|// total sector count
DECL|member|ssize
r_int
r_int
id|ssize
suffix:semicolon
singleline_comment|// sector size in bytes
DECL|member|sense_key
r_int
r_char
id|sense_key
suffix:semicolon
DECL|member|sense_asc
r_int
r_int
id|sense_asc
suffix:semicolon
singleline_comment|// additional sense code
DECL|member|sense_ascq
r_int
r_int
id|sense_ascq
suffix:semicolon
singleline_comment|// additional sense code qualifier
)brace
suffix:semicolon
macro_line|#endif
eof
