multiline_comment|/* $Id: tpam.h,v 1.1.2.1 2001/06/08 08:23:46 kai Exp $&n; *&n; * Turbo PAM ISDN driver for Linux. (Kernel Driver)&n; *&n; * Copyright 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * For all support questions please contact: &lt;support@auvertech.fr&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _TPAM_H_
DECL|macro|_TPAM_H_
mdefine_line|#define _TPAM_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* IOCTL commands */
DECL|macro|TPAM_CMD_DSPLOAD
mdefine_line|#define TPAM_CMD_DSPLOAD&t;0x0001
DECL|macro|TPAM_CMD_DSPSAVE
mdefine_line|#define TPAM_CMD_DSPSAVE&t;0x0002
DECL|macro|TPAM_CMD_DSPRUN
mdefine_line|#define TPAM_CMD_DSPRUN&t;&t;0x0003
DECL|macro|TPAM_CMD_LOOPMODEON
mdefine_line|#define TPAM_CMD_LOOPMODEON&t;0x0004
DECL|macro|TPAM_CMD_LOOPMODEOFF
mdefine_line|#define TPAM_CMD_LOOPMODEOFF&t;0x0005
multiline_comment|/* addresses of debug information zones on board */
DECL|macro|TPAM_TRAPAUDIT_REGISTER
mdefine_line|#define TPAM_TRAPAUDIT_REGISTER&t;&t;0x005493e4
DECL|macro|TPAM_NCOAUDIT_REGISTER
mdefine_line|#define TPAM_NCOAUDIT_REGISTER&t;&t;0x00500000
DECL|macro|TPAM_MSGAUDIT_REGISTER
mdefine_line|#define TPAM_MSGAUDIT_REGISTER&t;&t;0x008E30F0
multiline_comment|/* length of debug information zones on board */
DECL|macro|TPAM_TRAPAUDIT_LENGTH
mdefine_line|#define TPAM_TRAPAUDIT_LENGTH&t;&t;10000
DECL|macro|TPAM_NCOAUDIT_LENGTH
mdefine_line|#define TPAM_NCOAUDIT_LENGTH&t;&t;300000
DECL|macro|TPAM_NCOAUDIT_COUNT
mdefine_line|#define TPAM_NCOAUDIT_COUNT&t;&t;30
DECL|macro|TPAM_MSGAUDIT_LENGTH
mdefine_line|#define TPAM_MSGAUDIT_LENGTH&t;&t;60000
multiline_comment|/* IOCTL load/save parameter */
DECL|struct|tpam_dsp_ioctl
r_typedef
r_struct
id|tpam_dsp_ioctl
(brace
DECL|member|address
id|__u32
id|address
suffix:semicolon
multiline_comment|/* address to load/save data */
DECL|member|data_len
id|__u32
id|data_len
suffix:semicolon
multiline_comment|/* size of data to be loaded/saved */
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* data */
DECL|typedef|tpam_dsp_ioctl
)brace
id|tpam_dsp_ioctl
suffix:semicolon
macro_line|#endif /* _TPAM_H_ */
eof
