multiline_comment|/******************************************************************************&n; *                  QLOGIC LINUX SOFTWARE&n; *&n; * QLogic ISP2x00 device driver for Linux 2.6.x&n; * Copyright (C) 2003 QLogic Corporation&n; * (www.qlogic.com)&n; *&n; * Portions (C) Arjan van de Ven &lt;arjanv@redhat.com&gt; for Red Hat, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; ******************************************************************************/
macro_line|#ifndef __QLA_OS_H
DECL|macro|__QLA_OS_H
mdefine_line|#define __QLA_OS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
singleline_comment|//TODO Fix this!!!
multiline_comment|/*&n;* String arrays&n;*/
DECL|macro|LINESIZE
mdefine_line|#define LINESIZE    256
DECL|macro|MAXARGS
mdefine_line|#define MAXARGS      26
multiline_comment|/***********************************************************************&n;* We use the struct scsi_pointer structure that&squot;s included with each &n;* command SCSI_Cmnd as a scratchpad. &n;*&n;* SCp is defined as follows:&n;*  - SCp.ptr  -- &gt; pointer to the SRB&n;*  - SCp.this_residual  -- &gt; HBA completion status for ioctl code. &n;*&n;* Cmnd-&gt;host_scribble --&gt; Used to hold the hba actived handle (1..255).&n;***********************************************************************/
DECL|macro|CMD_SP
mdefine_line|#define&t;CMD_SP(Cmnd)&t;&t;((Cmnd)-&gt;SCp.ptr)
DECL|macro|CMD_COMPL_STATUS
mdefine_line|#define CMD_COMPL_STATUS(Cmnd)  ((Cmnd)-&gt;SCp.this_residual)
multiline_comment|/* Additional fields used by ioctl passthru */
DECL|macro|CMD_RESID_LEN
mdefine_line|#define CMD_RESID_LEN(Cmnd)&t;((Cmnd)-&gt;SCp.buffers_residual)
DECL|macro|CMD_SCSI_STATUS
mdefine_line|#define CMD_SCSI_STATUS(Cmnd)&t;((Cmnd)-&gt;SCp.Status)
DECL|macro|CMD_ACTUAL_SNSLEN
mdefine_line|#define CMD_ACTUAL_SNSLEN(Cmnd)&t;((Cmnd)-&gt;SCp.Message)
DECL|macro|CMD_ENTRY_STATUS
mdefine_line|#define CMD_ENTRY_STATUS(Cmnd)&t;((Cmnd)-&gt;SCp.have_data_in)
macro_line|#endif
eof
