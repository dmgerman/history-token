multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SYM53C8XX_H
DECL|macro|SYM53C8XX_H
mdefine_line|#define SYM53C8XX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SCSI_SYM53C8XX_IOMAPPED
DECL|macro|SYM_CONF_IOMAPPED
mdefine_line|#define&t;SYM_CONF_IOMAPPED
macro_line|#endif
multiline_comment|/*&n; *  DMA addressing mode.&n; *&n; *  0 : 32 bit addressing for all chips.&n; *  1 : 40 bit addressing when supported by chip.&n; *  2 : 64 bit addressing when supported by chip,&n; *      limited to 16 segments of 4 GB -&gt; 64 GB max.&n; */
DECL|macro|SYM_CONF_DMA_ADDRESSING_MODE
mdefine_line|#define&t;SYM_CONF_DMA_ADDRESSING_MODE CONFIG_SCSI_SYM53C8XX_DMA_ADDRESSING_MODE
multiline_comment|/*&n; *  NVRAM support.&n; */
macro_line|#if 1
DECL|macro|SYM_CONF_NVRAM_SUPPORT
mdefine_line|#define SYM_CONF_NVRAM_SUPPORT&t;&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  These options are not tunable from &squot;make config&squot;&n; */
macro_line|#if 1
DECL|macro|SYM_LINUX_PROC_INFO_SUPPORT
mdefine_line|#define&t;SYM_LINUX_PROC_INFO_SUPPORT
DECL|macro|SYM_LINUX_USER_COMMAND_SUPPORT
mdefine_line|#define SYM_LINUX_USER_COMMAND_SUPPORT
DECL|macro|SYM_LINUX_USER_INFO_SUPPORT
mdefine_line|#define SYM_LINUX_USER_INFO_SUPPORT
DECL|macro|SYM_LINUX_DEBUG_CONTROL_SUPPORT
mdefine_line|#define SYM_LINUX_DEBUG_CONTROL_SUPPORT
macro_line|#endif
multiline_comment|/*&n; *  Also handle old NCR chips if not (0).&n; */
DECL|macro|SYM_CONF_GENERIC_SUPPORT
mdefine_line|#define SYM_CONF_GENERIC_SUPPORT&t;(1)
multiline_comment|/*&n; *  Allow tags from 2 to 256, default 8&n; */
macro_line|#ifndef CONFIG_SCSI_SYM53C8XX_MAX_TAGS
DECL|macro|CONFIG_SCSI_SYM53C8XX_MAX_TAGS
mdefine_line|#define CONFIG_SCSI_SYM53C8XX_MAX_TAGS&t;(8)
macro_line|#endif
macro_line|#if&t;CONFIG_SCSI_SYM53C8XX_MAX_TAGS &lt; 2
DECL|macro|SYM_CONF_MAX_TAG
mdefine_line|#define SYM_CONF_MAX_TAG&t;(2)
macro_line|#elif&t;CONFIG_SCSI_SYM53C8XX_MAX_TAGS &gt; 256
DECL|macro|SYM_CONF_MAX_TAG
mdefine_line|#define SYM_CONF_MAX_TAG&t;(256)
macro_line|#else
DECL|macro|SYM_CONF_MAX_TAG
mdefine_line|#define&t;SYM_CONF_MAX_TAG&t;CONFIG_SCSI_SYM53C8XX_MAX_TAGS
macro_line|#endif
macro_line|#ifndef&t;CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS
DECL|macro|CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS
mdefine_line|#define&t;CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS&t;SYM_CONF_MAX_TAG
macro_line|#endif
multiline_comment|/*&n; *  Anyway, we configure the driver for at least 64 tags per LUN. :)&n; */
macro_line|#if&t;SYM_CONF_MAX_TAG &lt;= 64
DECL|macro|SYM_CONF_MAX_TAG_ORDER
mdefine_line|#define SYM_CONF_MAX_TAG_ORDER&t;(6)
macro_line|#elif&t;SYM_CONF_MAX_TAG &lt;= 128
DECL|macro|SYM_CONF_MAX_TAG_ORDER
mdefine_line|#define SYM_CONF_MAX_TAG_ORDER&t;(7)
macro_line|#else
DECL|macro|SYM_CONF_MAX_TAG_ORDER
mdefine_line|#define SYM_CONF_MAX_TAG_ORDER&t;(8)
macro_line|#endif
multiline_comment|/*&n; *  Max number of SG entries.&n; */
DECL|macro|SYM_CONF_MAX_SG
mdefine_line|#define SYM_CONF_MAX_SG&t;&t;(96)
multiline_comment|/*&n; *  Driver setup structure.&n; *&n; *  This structure is initialized from linux config options.&n; *  It can be overridden at boot-up by the boot command line.&n; */
DECL|struct|sym_driver_setup
r_struct
id|sym_driver_setup
(brace
DECL|member|max_tag
id|u_short
id|max_tag
suffix:semicolon
DECL|member|burst_order
id|u_char
id|burst_order
suffix:semicolon
DECL|member|scsi_led
id|u_char
id|scsi_led
suffix:semicolon
DECL|member|scsi_diff
id|u_char
id|scsi_diff
suffix:semicolon
DECL|member|irq_mode
id|u_char
id|irq_mode
suffix:semicolon
DECL|member|scsi_bus_check
id|u_char
id|scsi_bus_check
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|verbose
id|u_char
id|verbose
suffix:semicolon
DECL|member|settle_delay
id|u_char
id|settle_delay
suffix:semicolon
DECL|member|use_nvram
id|u_char
id|use_nvram
suffix:semicolon
DECL|member|excludes
id|u_long
id|excludes
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|tag_ctrl
r_char
id|tag_ctrl
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SYM_SETUP_MAX_TAG
mdefine_line|#define SYM_SETUP_MAX_TAG&t;&t;sym_driver_setup.max_tag
DECL|macro|SYM_SETUP_BURST_ORDER
mdefine_line|#define SYM_SETUP_BURST_ORDER&t;&t;sym_driver_setup.burst_order
DECL|macro|SYM_SETUP_SCSI_LED
mdefine_line|#define SYM_SETUP_SCSI_LED&t;&t;sym_driver_setup.scsi_led
DECL|macro|SYM_SETUP_SCSI_DIFF
mdefine_line|#define SYM_SETUP_SCSI_DIFF&t;&t;sym_driver_setup.scsi_diff
DECL|macro|SYM_SETUP_IRQ_MODE
mdefine_line|#define SYM_SETUP_IRQ_MODE&t;&t;sym_driver_setup.irq_mode
DECL|macro|SYM_SETUP_SCSI_BUS_CHECK
mdefine_line|#define SYM_SETUP_SCSI_BUS_CHECK&t;sym_driver_setup.scsi_bus_check
DECL|macro|SYM_SETUP_HOST_ID
mdefine_line|#define SYM_SETUP_HOST_ID&t;&t;sym_driver_setup.host_id
DECL|macro|boot_verbose
mdefine_line|#define boot_verbose&t;&t;&t;sym_driver_setup.verbose
multiline_comment|/* Always enable parity. */
DECL|macro|SYM_SETUP_PCI_PARITY
mdefine_line|#define SYM_SETUP_PCI_PARITY&t;&t;1
DECL|macro|SYM_SETUP_SCSI_PARITY
mdefine_line|#define SYM_SETUP_SCSI_PARITY&t;&t;1
multiline_comment|/*&n; *  Initial setup.&n; *&n; *  Can be overriden at startup by a command line.&n; */
DECL|macro|SYM_LINUX_DRIVER_SETUP
mdefine_line|#define SYM_LINUX_DRIVER_SETUP&t;{&t;&t;&t;&t;&bslash;&n;&t;.max_tag&t;= CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS,&t;&bslash;&n;&t;.burst_order&t;= 7,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_led&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_diff&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.irq_mode&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_bus_check&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.host_id&t;= 7,&t;&t;&t;&t;&t;&bslash;&n;&t;.verbose&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.settle_delay&t;= 3,&t;&t;&t;&t;&t;&bslash;&n;&t;.use_nvram&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;}
r_extern
r_struct
id|sym_driver_setup
id|sym_driver_setup
suffix:semicolon
r_extern
r_int
r_int
id|sym_debug_flags
suffix:semicolon
DECL|macro|DEBUG_FLAGS
mdefine_line|#define DEBUG_FLAGS&t;sym_debug_flags
macro_line|#endif /* SYM53C8XX_H */
eof
