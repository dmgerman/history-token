multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM53C8XX_H
DECL|macro|SYM53C8XX_H
mdefine_line|#define SYM53C8XX_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *  Use normal IO if configured.&n; *  Normal IO forced for alpha.&n; *  Forced to MMIO for sparc.&n; */
macro_line|#if defined(__alpha__)
DECL|macro|SYM_CONF_IOMAPPED
mdefine_line|#define&t;SYM_CONF_IOMAPPED
macro_line|#elif defined(__sparc__)
DECL|macro|SYM_CONF_IOMAPPED
macro_line|#undef SYM_CONF_IOMAPPED
multiline_comment|/* #elif defined(__powerpc__) */
multiline_comment|/* #define&t;SYM_CONF_IOMAPPED */
multiline_comment|/* #define SYM_OPT_NO_BUS_MEMORY_MAPPING */
macro_line|#elif defined(CONFIG_SCSI_SYM53C8XX_IOMAPPED)
DECL|macro|SYM_CONF_IOMAPPED
mdefine_line|#define&t;SYM_CONF_IOMAPPED
macro_line|#endif
multiline_comment|/*&n; *  DMA addressing mode.&n; *&n; *  0 : 32 bit addressing for all chips.&n; *  1 : 40 bit addressing when supported by chip.&n; *  2 : 64 bit addressing when supported by chip,&n; *      limited to 16 segments of 4 GB -&gt; 64 GB max.&n; */
DECL|macro|SYM_CONF_DMA_ADDRESSING_MODE
mdefine_line|#define&t;SYM_CONF_DMA_ADDRESSING_MODE CONFIG_SCSI_SYM53C8XX_DMA_ADDRESSING_MODE
multiline_comment|/*&n; *  NCR PQS/PDS special device support.&n; */
macro_line|#if 1
DECL|macro|SYM_CONF_PQS_PDS_SUPPORT
mdefine_line|#define SYM_CONF_PQS_PDS_SUPPORT
macro_line|#endif
multiline_comment|/*&n; *  NVRAM support.&n; */
macro_line|#if 1
DECL|macro|SYM_CONF_NVRAM_SUPPORT
mdefine_line|#define SYM_CONF_NVRAM_SUPPORT&t;&t;(1)
DECL|macro|SYM_SETUP_SYMBIOS_NVRAM
mdefine_line|#define SYM_SETUP_SYMBIOS_NVRAM&t;&t;(1)
DECL|macro|SYM_SETUP_TEKRAM_NVRAM
mdefine_line|#define SYM_SETUP_TEKRAM_NVRAM&t;&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  These options are not tunable from &squot;make config&squot;&n; */
macro_line|#if 1
DECL|macro|SYM_LINUX_PROC_INFO_SUPPORT
mdefine_line|#define&t;SYM_LINUX_PROC_INFO_SUPPORT
DECL|macro|SYM_LINUX_BOOT_COMMAND_LINE_SUPPORT
mdefine_line|#define SYM_LINUX_BOOT_COMMAND_LINE_SUPPORT
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
DECL|member|reverse_probe
id|u_char
id|reverse_probe
suffix:semicolon
DECL|member|verbose
id|u_char
id|verbose
suffix:semicolon
DECL|member|debug
id|u_short
id|debug
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
multiline_comment|/* Always enable parity. */
DECL|macro|SYM_SETUP_PCI_PARITY
mdefine_line|#define SYM_SETUP_PCI_PARITY&t;&t;1
DECL|macro|SYM_SETUP_SCSI_PARITY
mdefine_line|#define SYM_SETUP_SCSI_PARITY&t;&t;1
multiline_comment|/*&n; *  Initial setup.&n; *&n; *  Can be overriden at startup by a command line.&n; */
DECL|macro|SYM_LINUX_DRIVER_SETUP
mdefine_line|#define SYM_LINUX_DRIVER_SETUP&t;{&t;&t;&t;&t;&bslash;&n;&t;.max_tag&t;= CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS,&t;&bslash;&n;&t;.burst_order&t;= 7,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_led&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_diff&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.irq_mode&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_bus_check&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.host_id&t;= 7,&t;&t;&t;&t;&t;&bslash;&n;&t;.reverse_probe&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.verbose&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.debug&t;&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.settle_delay&t;= 3,&t;&t;&t;&t;&t;&bslash;&n;&t;.use_nvram&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; *  Boot fail safe setup.&n; *&n; *  Override initial setup from boot command line:&n; *    sym53c8xx=safe:y&n; */
DECL|macro|SYM_LINUX_DRIVER_SAFE_SETUP
mdefine_line|#define SYM_LINUX_DRIVER_SAFE_SETUP {&t;&t;&t;&t;&bslash;&n;&t;.max_tag&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.burst_order&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_led&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_diff&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;&t;.irq_mode&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.scsi_bus_check&t;= 2,&t;&t;&t;&t;&t;&bslash;&n;&t;.host_id&t;= 7,&t;&t;&t;&t;&t;&bslash;&n;&t;.reverse_probe&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.verbose&t;= 2,&t;&t;&t;&t;&t;&bslash;&n;&t;.debug&t;&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.settle_delay&t;= 10,&t;&t;&t;&t;&t;&bslash;&n;&t;.use_nvram&t;= 1,&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; *  This structure is initialized from linux config options.&n; *  It can be overridden at boot-up by the boot command line.&n; */
macro_line|#ifdef SYM_GLUE_C
r_struct
id|sym_driver_setup
DECL|variable|sym_driver_setup
id|sym_driver_setup
op_assign
id|SYM_LINUX_DRIVER_SETUP
suffix:semicolon
macro_line|#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
DECL|variable|sym_debug_flags
id|u_int
id|sym_debug_flags
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#else
r_extern
r_struct
id|sym_driver_setup
id|sym_driver_setup
suffix:semicolon
macro_line|#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
r_extern
id|u_int
id|sym_debug_flags
suffix:semicolon
macro_line|#endif
macro_line|#endif /* SYM_GLUE_C */
macro_line|#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
DECL|macro|DEBUG_FLAGS
mdefine_line|#define DEBUG_FLAGS&t;sym_debug_flags
macro_line|#endif
DECL|macro|boot_verbose
mdefine_line|#define boot_verbose&t;sym_driver_setup.verbose
macro_line|#endif /* SYM53C8XX_H */
eof
