multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifdef __FreeBSD__
macro_line|#include &lt;dev/sym/sym_glue.h&gt;
macro_line|#else
macro_line|#include &quot;sym_glue.h&quot;
macro_line|#endif
multiline_comment|/*&n; *  Some poor and bogus sync table that refers to Tekram NVRAM layout.&n; */
macro_line|#if SYM_CONF_NVRAM_SUPPORT
DECL|variable|Tekram_sync
r_static
id|u_char
id|Tekram_sync
(braket
l_int|16
)braket
op_assign
(brace
l_int|25
comma
l_int|31
comma
l_int|37
comma
l_int|43
comma
l_int|50
comma
l_int|62
comma
l_int|75
comma
l_int|125
comma
l_int|12
comma
l_int|15
comma
l_int|18
comma
l_int|21
comma
l_int|6
comma
l_int|7
comma
l_int|9
comma
l_int|10
)brace
suffix:semicolon
macro_line|#ifdef&t;SYM_CONF_DEBUG_NVRAM
DECL|variable|Tekram_boot_delay
r_static
id|u_char
id|Tekram_boot_delay
(braket
l_int|7
)braket
op_assign
(brace
l_int|3
comma
l_int|5
comma
l_int|10
comma
l_int|20
comma
l_int|30
comma
l_int|60
comma
l_int|120
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; *  Get host setup from NVRAM.&n; */
DECL|function|sym_nvram_setup_host
r_void
id|sym_nvram_setup_host
(paren
id|hcb_p
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvram
)paren
(brace
macro_line|#if SYM_CONF_NVRAM_SUPPORT
multiline_comment|/*&n;&t; *  Get parity checking, host ID, verbose mode &n;&t; *  and miscellaneous host flags from NVRAM.&n;&t; */
r_switch
c_cond
(paren
id|nvram-&gt;type
)paren
(brace
r_case
id|SYM_SYMBIOS_NVRAM
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nvram-&gt;data.Symbios.flags
op_amp
id|SYMBIOS_PARITY_ENABLE
)paren
)paren
id|np-&gt;rv_scntl0
op_and_assign
op_complement
l_int|0x0a
suffix:semicolon
id|np-&gt;myaddr
op_assign
id|nvram-&gt;data.Symbios.host_id
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|nvram-&gt;data.Symbios.flags
op_amp
id|SYMBIOS_VERBOSE_MSGS
)paren
id|np-&gt;verbose
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nvram-&gt;data.Symbios.flags1
op_amp
id|SYMBIOS_SCAN_HI_LO
)paren
id|np-&gt;usrflags
op_or_assign
id|SYM_SCAN_TARGETS_HILO
suffix:semicolon
r_if
c_cond
(paren
id|nvram-&gt;data.Symbios.flags2
op_amp
id|SYMBIOS_AVOID_BUS_RESET
)paren
id|np-&gt;usrflags
op_or_assign
id|SYM_AVOID_BUS_RESET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYM_TEKRAM_NVRAM
suffix:colon
id|np-&gt;myaddr
op_assign
id|nvram-&gt;data.Tekram.host_id
op_amp
l_int|0x0f
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; *  Get target setup from NVRAM.&n; */
macro_line|#if SYM_CONF_NVRAM_SUPPORT
r_static
r_void
id|sym_Symbios_setup_target
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
comma
id|Symbios_nvram
op_star
id|nvram
)paren
suffix:semicolon
r_static
r_void
id|sym_Tekram_setup_target
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
comma
id|Tekram_nvram
op_star
id|nvram
)paren
suffix:semicolon
macro_line|#endif
DECL|function|sym_nvram_setup_target
r_void
id|sym_nvram_setup_target
(paren
id|hcb_p
id|np
comma
r_int
id|target
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
(brace
macro_line|#if SYM_CONF_NVRAM_SUPPORT
r_switch
c_cond
(paren
id|nvp-&gt;type
)paren
(brace
r_case
id|SYM_SYMBIOS_NVRAM
suffix:colon
id|sym_Symbios_setup_target
(paren
id|np
comma
id|target
comma
op_amp
id|nvp-&gt;data.Symbios
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYM_TEKRAM_NVRAM
suffix:colon
id|sym_Tekram_setup_target
(paren
id|np
comma
id|target
comma
op_amp
id|nvp-&gt;data.Tekram
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#if SYM_CONF_NVRAM_SUPPORT
multiline_comment|/*&n; *  Get target set-up from Symbios format NVRAM.&n; */
r_static
r_void
DECL|function|sym_Symbios_setup_target
id|sym_Symbios_setup_target
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
comma
id|Symbios_nvram
op_star
id|nvram
)paren
(brace
id|tcb_p
id|tp
op_assign
op_amp
id|np-&gt;target
(braket
id|target
)braket
suffix:semicolon
id|Symbios_target
op_star
id|tn
op_assign
op_amp
id|nvram-&gt;target
(braket
id|target
)braket
suffix:semicolon
id|tp-&gt;tinfo.user.period
op_assign
id|tn-&gt;sync_period
ques
c_cond
(paren
id|tn-&gt;sync_period
op_plus
l_int|3
)paren
op_div
l_int|4
suffix:colon
l_int|0
suffix:semicolon
id|tp-&gt;tinfo.user.width
op_assign
id|tn-&gt;bus_width
op_eq
l_int|0x10
ques
c_cond
id|BUS_16_BIT
suffix:colon
id|BUS_8_BIT
suffix:semicolon
id|tp-&gt;usrtags
op_assign
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_QUEUE_TAGS_ENABLED
)paren
ques
c_cond
id|SYM_SETUP_MAX_TAG
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_DISCONNECT_ENABLE
)paren
)paren
id|tp-&gt;usrflags
op_and_assign
op_complement
id|SYM_DISC_ENABLED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_SCAN_AT_BOOT_TIME
)paren
)paren
id|tp-&gt;usrflags
op_or_assign
id|SYM_SCAN_BOOT_DISABLED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_SCAN_LUNS
)paren
)paren
id|tp-&gt;usrflags
op_or_assign
id|SYM_SCAN_LUNS_DISABLED
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get target set-up from Tekram format NVRAM.&n; */
r_static
r_void
DECL|function|sym_Tekram_setup_target
id|sym_Tekram_setup_target
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
comma
id|Tekram_nvram
op_star
id|nvram
)paren
(brace
id|tcb_p
id|tp
op_assign
op_amp
id|np-&gt;target
(braket
id|target
)braket
suffix:semicolon
r_struct
id|Tekram_target
op_star
id|tn
op_assign
op_amp
id|nvram-&gt;target
(braket
id|target
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_SYNC_NEGO
)paren
(brace
id|i
op_assign
id|tn-&gt;sync_index
op_amp
l_int|0xf
suffix:semicolon
id|tp-&gt;tinfo.user.period
op_assign
id|Tekram_sync
(braket
id|i
)braket
suffix:semicolon
)brace
id|tp-&gt;tinfo.user.width
op_assign
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_WIDE_NEGO
)paren
ques
c_cond
id|BUS_16_BIT
suffix:colon
id|BUS_8_BIT
suffix:semicolon
r_if
c_cond
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_TAGGED_COMMANDS
)paren
(brace
id|tp-&gt;usrtags
op_assign
l_int|2
op_lshift
id|nvram-&gt;max_tags_index
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_DISCONNECT_ENABLE
)paren
id|tp-&gt;usrflags
op_or_assign
id|SYM_DISC_ENABLED
suffix:semicolon
multiline_comment|/* If any device does not support parity, we will not use this option */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_PARITY_CHECK
)paren
)paren
id|np-&gt;rv_scntl0
op_and_assign
op_complement
l_int|0x0a
suffix:semicolon
multiline_comment|/* SCSI parity checking disabled */
)brace
macro_line|#ifdef&t;SYM_CONF_DEBUG_NVRAM
multiline_comment|/*&n; *  Dump Symbios format NVRAM for debugging purpose.&n; */
DECL|function|sym_display_Symbios_nvram
r_static
r_void
id|sym_display_Symbios_nvram
c_func
(paren
id|sdev_p
id|np
comma
id|Symbios_nvram
op_star
id|nvram
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* display Symbios nvram host data */
id|printf
c_func
(paren
l_string|&quot;%s: HOST ID=%d%s%s%s%s%s%s&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
id|nvram-&gt;host_id
op_amp
l_int|0x0f
comma
(paren
id|nvram-&gt;flags
op_amp
id|SYMBIOS_SCAM_ENABLE
)paren
ques
c_cond
l_string|&quot; SCAM&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|SYMBIOS_PARITY_ENABLE
)paren
ques
c_cond
l_string|&quot; PARITY&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|SYMBIOS_VERBOSE_MSGS
)paren
ques
c_cond
l_string|&quot; VERBOSE&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|SYMBIOS_CHS_MAPPING
)paren
ques
c_cond
l_string|&quot; CHS_ALT&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags2
op_amp
id|SYMBIOS_AVOID_BUS_RESET
)paren
ques
c_cond
l_string|&quot; NO_RESET&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags1
op_amp
id|SYMBIOS_SCAN_HI_LO
)paren
ques
c_cond
l_string|&quot; HI_LO&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* display Symbios nvram drive data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|15
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|Symbios_target
op_star
id|tn
op_assign
op_amp
id|nvram-&gt;target
(braket
id|i
)braket
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s-%d:%s%s%s%s WIDTH=%d SYNC=%d TMO=%d&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
id|i
comma
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_DISCONNECT_ENABLE
)paren
ques
c_cond
l_string|&quot; DISC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_SCAN_AT_BOOT_TIME
)paren
ques
c_cond
l_string|&quot; SCAN_BOOT&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_SCAN_LUNS
)paren
ques
c_cond
l_string|&quot; SCAN_LUNS&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|SYMBIOS_QUEUE_TAGS_ENABLED
)paren
ques
c_cond
l_string|&quot; TCQ&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tn-&gt;bus_width
comma
id|tn-&gt;sync_period
op_div
l_int|4
comma
id|tn-&gt;timeout
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Dump TEKRAM format NVRAM for debugging purpose.&n; */
DECL|function|sym_display_Tekram_nvram
r_static
r_void
id|sym_display_Tekram_nvram
c_func
(paren
id|sdev_p
id|np
comma
id|Tekram_nvram
op_star
id|nvram
)paren
(brace
r_int
id|i
comma
id|tags
comma
id|boot_delay
suffix:semicolon
r_char
op_star
id|rem
suffix:semicolon
multiline_comment|/* display Tekram nvram host data */
id|tags
op_assign
l_int|2
op_lshift
id|nvram-&gt;max_tags_index
suffix:semicolon
id|boot_delay
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nvram-&gt;boot_delay_index
OL
l_int|6
)paren
id|boot_delay
op_assign
id|Tekram_boot_delay
(braket
id|nvram-&gt;boot_delay_index
)braket
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_REMOVABLE_FLAGS
)paren
op_rshift
l_int|6
)paren
(brace
r_default
suffix:colon
r_case
l_int|0
suffix:colon
id|rem
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|rem
op_assign
l_string|&quot; REMOVABLE=boot device&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|rem
op_assign
l_string|&quot; REMOVABLE=all&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s: HOST ID=%d%s%s%s%s%s%s%s%s%s BOOT DELAY=%d tags=%d&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
id|nvram-&gt;host_id
op_amp
l_int|0x0f
comma
(paren
id|nvram-&gt;flags1
op_amp
id|SYMBIOS_SCAM_ENABLE
)paren
ques
c_cond
l_string|&quot; SCAM&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_MORE_THAN_2_DRIVES
)paren
ques
c_cond
l_string|&quot; &gt;2DRIVES&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_DRIVES_SUP_1GB
)paren
ques
c_cond
l_string|&quot; &gt;1GB&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_RESET_ON_POWER_ON
)paren
ques
c_cond
l_string|&quot; RESET&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_ACTIVE_NEGATION
)paren
ques
c_cond
l_string|&quot; ACT_NEG&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_IMMEDIATE_SEEK
)paren
ques
c_cond
l_string|&quot; IMM_SEEK&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags
op_amp
id|TEKRAM_SCAN_LUNS
)paren
ques
c_cond
l_string|&quot; SCAN_LUNS&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|nvram-&gt;flags1
op_amp
id|TEKRAM_F2_F6_ENABLED
)paren
ques
c_cond
l_string|&quot; F2_F6&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|rem
comma
id|boot_delay
comma
id|tags
)paren
suffix:semicolon
multiline_comment|/* display Tekram nvram drive data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|15
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|sync
comma
id|j
suffix:semicolon
r_struct
id|Tekram_target
op_star
id|tn
op_assign
op_amp
id|nvram-&gt;target
(braket
id|i
)braket
suffix:semicolon
id|j
op_assign
id|tn-&gt;sync_index
op_amp
l_int|0xf
suffix:semicolon
id|sync
op_assign
id|Tekram_sync
(braket
id|j
)braket
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s-%d:%s%s%s%s%s%s PERIOD=%d&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
id|i
comma
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_PARITY_CHECK
)paren
ques
c_cond
l_string|&quot; PARITY&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_SYNC_NEGO
)paren
ques
c_cond
l_string|&quot; SYNC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_DISCONNECT_ENABLE
)paren
ques
c_cond
l_string|&quot; DISC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_START_CMD
)paren
ques
c_cond
l_string|&quot; START&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_TAGGED_COMMANDS
)paren
ques
c_cond
l_string|&quot; TCQ&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|tn-&gt;flags
op_amp
id|TEKRAM_WIDE_NEGO
)paren
ques
c_cond
l_string|&quot; WIDE&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|sync
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* SYM_CONF_DEBUG_NVRAM */
macro_line|#endif&t;/* SYM_CONF_NVRAM_SUPPORT */
multiline_comment|/*&n; *  Try reading Symbios or Tekram NVRAM&n; */
macro_line|#if SYM_CONF_NVRAM_SUPPORT
r_static
r_int
id|sym_read_Symbios_nvram
(paren
id|sdev_p
id|np
comma
id|Symbios_nvram
op_star
id|nvram
)paren
suffix:semicolon
r_static
r_int
id|sym_read_Tekram_nvram
(paren
id|sdev_p
id|np
comma
id|Tekram_nvram
op_star
id|nvram
)paren
suffix:semicolon
macro_line|#endif
DECL|function|sym_read_nvram
r_int
id|sym_read_nvram
(paren
id|sdev_p
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
(brace
macro_line|#if SYM_CONF_NVRAM_SUPPORT
multiline_comment|/*&n;&t; *  Try to read SYMBIOS nvram.&n;&t; *  Try to read TEKRAM nvram if Symbios nvram not found.&n;&t; */
r_if
c_cond
(paren
id|SYM_SETUP_SYMBIOS_NVRAM
op_logical_and
op_logical_neg
id|sym_read_Symbios_nvram
(paren
id|np
comma
op_amp
id|nvp-&gt;data.Symbios
)paren
)paren
(brace
id|nvp-&gt;type
op_assign
id|SYM_SYMBIOS_NVRAM
suffix:semicolon
macro_line|#ifdef SYM_CONF_DEBUG_NVRAM
id|sym_display_Symbios_nvram
c_func
(paren
id|np
comma
op_amp
id|nvp-&gt;data.Symbios
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|SYM_SETUP_TEKRAM_NVRAM
op_logical_and
op_logical_neg
id|sym_read_Tekram_nvram
(paren
id|np
comma
op_amp
id|nvp-&gt;data.Tekram
)paren
)paren
(brace
id|nvp-&gt;type
op_assign
id|SYM_TEKRAM_NVRAM
suffix:semicolon
macro_line|#ifdef SYM_CONF_DEBUG_NVRAM
id|sym_display_Tekram_nvram
c_func
(paren
id|np
comma
op_amp
id|nvp-&gt;data.Tekram
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|nvp-&gt;type
op_assign
l_int|0
suffix:semicolon
macro_line|#else
id|nvp-&gt;type
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_return
id|nvp-&gt;type
suffix:semicolon
)brace
macro_line|#if SYM_CONF_NVRAM_SUPPORT
multiline_comment|/*&n; *  24C16 EEPROM reading.&n; *&n; *  GPOI0 - data in/data out&n; *  GPIO1 - clock&n; *  Symbios NVRAM wiring now also used by Tekram.&n; */
DECL|macro|SET_BIT
mdefine_line|#define SET_BIT 0
DECL|macro|CLR_BIT
mdefine_line|#define CLR_BIT 1
DECL|macro|SET_CLK
mdefine_line|#define SET_CLK 2
DECL|macro|CLR_CLK
mdefine_line|#define CLR_CLK 3
multiline_comment|/*&n; *  Set/clear data/clock bit in GPIO0&n; */
DECL|function|S24C16_set_bit
r_static
r_void
id|S24C16_set_bit
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
id|write_bit
comma
id|u_char
op_star
id|gpreg
comma
r_int
id|bit_mode
)paren
(brace
id|UDELAY
(paren
l_int|5
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|bit_mode
)paren
(brace
r_case
id|SET_BIT
suffix:colon
op_star
id|gpreg
op_or_assign
id|write_bit
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CLR_BIT
suffix:colon
op_star
id|gpreg
op_and_assign
l_int|0xfe
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SET_CLK
suffix:colon
op_star
id|gpreg
op_or_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CLR_CLK
suffix:colon
op_star
id|gpreg
op_and_assign
l_int|0xfd
suffix:semicolon
r_break
suffix:semicolon
)brace
id|OUTB
(paren
id|nc_gpreg
comma
op_star
id|gpreg
)paren
suffix:semicolon
id|UDELAY
(paren
l_int|5
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Send START condition to NVRAM to wake it up.&n; */
DECL|function|S24C16_start
r_static
r_void
id|S24C16_start
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|gpreg
)paren
(brace
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|1
comma
id|gpreg
comma
id|SET_BIT
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|SET_CLK
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|CLR_BIT
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|CLR_CLK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Send STOP condition to NVRAM - puts NVRAM to sleep... ZZzzzz!!&n; */
DECL|function|S24C16_stop
r_static
r_void
id|S24C16_stop
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|gpreg
)paren
(brace
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|SET_CLK
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|1
comma
id|gpreg
comma
id|SET_BIT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Read or write a bit to the NVRAM,&n; *  read if GPIO0 input else write if GPIO0 output&n; */
DECL|function|S24C16_do_bit
r_static
r_void
id|S24C16_do_bit
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|read_bit
comma
id|u_char
id|write_bit
comma
id|u_char
op_star
id|gpreg
)paren
(brace
id|S24C16_set_bit
c_func
(paren
id|np
comma
id|write_bit
comma
id|gpreg
comma
id|SET_BIT
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|SET_CLK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_bit
)paren
op_star
id|read_bit
op_assign
id|INB
(paren
id|nc_gpreg
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|CLR_CLK
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|gpreg
comma
id|CLR_BIT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Output an ACK to the NVRAM after reading,&n; *  change GPIO0 to output and when done back to an input&n; */
DECL|function|S24C16_write_ack
r_static
r_void
id|S24C16_write_ack
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
id|write_bit
comma
id|u_char
op_star
id|gpreg
comma
id|u_char
op_star
id|gpcntl
)paren
(brace
id|OUTB
(paren
id|nc_gpcntl
comma
op_star
id|gpcntl
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|S24C16_do_bit
c_func
(paren
id|np
comma
l_int|0
comma
id|write_bit
comma
id|gpreg
)paren
suffix:semicolon
id|OUTB
(paren
id|nc_gpcntl
comma
op_star
id|gpcntl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Input an ACK from NVRAM after writing,&n; *  change GPIO0 to input and when done back to an output&n; */
DECL|function|S24C16_read_ack
r_static
r_void
id|S24C16_read_ack
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|read_bit
comma
id|u_char
op_star
id|gpreg
comma
id|u_char
op_star
id|gpcntl
)paren
(brace
id|OUTB
(paren
id|nc_gpcntl
comma
op_star
id|gpcntl
op_or
l_int|0x01
)paren
suffix:semicolon
id|S24C16_do_bit
c_func
(paren
id|np
comma
id|read_bit
comma
l_int|1
comma
id|gpreg
)paren
suffix:semicolon
id|OUTB
(paren
id|nc_gpcntl
comma
op_star
id|gpcntl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  WRITE a byte to the NVRAM and then get an ACK to see it was accepted OK,&n; *  GPIO0 must already be set as an output&n; */
DECL|function|S24C16_write_byte
r_static
r_void
id|S24C16_write_byte
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|ack_data
comma
id|u_char
id|write_data
comma
id|u_char
op_star
id|gpreg
comma
id|u_char
op_star
id|gpcntl
)paren
(brace
r_int
id|x
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|8
suffix:semicolon
id|x
op_increment
)paren
id|S24C16_do_bit
c_func
(paren
id|np
comma
l_int|0
comma
(paren
id|write_data
op_rshift
(paren
l_int|7
op_minus
id|x
)paren
)paren
op_amp
l_int|0x01
comma
id|gpreg
)paren
suffix:semicolon
id|S24C16_read_ack
c_func
(paren
id|np
comma
id|ack_data
comma
id|gpreg
comma
id|gpcntl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  READ a byte from the NVRAM and then send an ACK to say we have got it,&n; *  GPIO0 must already be set as an input&n; */
DECL|function|S24C16_read_byte
r_static
r_void
id|S24C16_read_byte
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|read_data
comma
id|u_char
id|ack_data
comma
id|u_char
op_star
id|gpreg
comma
id|u_char
op_star
id|gpcntl
)paren
(brace
r_int
id|x
suffix:semicolon
id|u_char
id|read_bit
suffix:semicolon
op_star
id|read_data
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|8
suffix:semicolon
id|x
op_increment
)paren
(brace
id|S24C16_do_bit
c_func
(paren
id|np
comma
op_amp
id|read_bit
comma
l_int|1
comma
id|gpreg
)paren
suffix:semicolon
op_star
id|read_data
op_or_assign
(paren
(paren
id|read_bit
op_amp
l_int|0x01
)paren
op_lshift
(paren
l_int|7
op_minus
id|x
)paren
)paren
suffix:semicolon
)brace
id|S24C16_write_ack
c_func
(paren
id|np
comma
id|ack_data
comma
id|gpreg
comma
id|gpcntl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Read &squot;len&squot; bytes starting at &squot;offset&squot;.&n; */
DECL|function|sym_read_S24C16_nvram
r_static
r_int
id|sym_read_S24C16_nvram
(paren
id|sdev_p
id|np
comma
r_int
id|offset
comma
id|u_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|u_char
id|gpcntl
comma
id|gpreg
suffix:semicolon
id|u_char
id|old_gpcntl
comma
id|old_gpreg
suffix:semicolon
id|u_char
id|ack_data
suffix:semicolon
r_int
id|retv
op_assign
l_int|1
suffix:semicolon
r_int
id|x
suffix:semicolon
multiline_comment|/* save current state of GPCNTL and GPREG */
id|old_gpreg
op_assign
id|INB
(paren
id|nc_gpreg
)paren
suffix:semicolon
id|old_gpcntl
op_assign
id|INB
(paren
id|nc_gpcntl
)paren
suffix:semicolon
id|gpcntl
op_assign
id|old_gpcntl
op_amp
l_int|0x1c
suffix:semicolon
multiline_comment|/* set up GPREG &amp; GPCNTL to set GPIO0 and GPIO1 in to known state */
id|OUTB
(paren
id|nc_gpreg
comma
id|old_gpreg
)paren
suffix:semicolon
id|OUTB
(paren
id|nc_gpcntl
comma
id|gpcntl
)paren
suffix:semicolon
multiline_comment|/* this is to set NVRAM into a known state with GPIO0/1 both low */
id|gpreg
op_assign
id|old_gpreg
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
op_amp
id|gpreg
comma
id|CLR_CLK
)paren
suffix:semicolon
id|S24C16_set_bit
c_func
(paren
id|np
comma
l_int|0
comma
op_amp
id|gpreg
comma
id|CLR_BIT
)paren
suffix:semicolon
multiline_comment|/* now set NVRAM inactive with GPIO0/1 both high */
id|S24C16_stop
c_func
(paren
id|np
comma
op_amp
id|gpreg
)paren
suffix:semicolon
multiline_comment|/* activate NVRAM */
id|S24C16_start
c_func
(paren
id|np
comma
op_amp
id|gpreg
)paren
suffix:semicolon
multiline_comment|/* write device code and random address MSB */
id|S24C16_write_byte
c_func
(paren
id|np
comma
op_amp
id|ack_data
comma
l_int|0xa0
op_or
(paren
(paren
id|offset
op_rshift
l_int|7
)paren
op_amp
l_int|0x0e
)paren
comma
op_amp
id|gpreg
comma
op_amp
id|gpcntl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack_data
op_amp
l_int|0x01
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* write random address LSB */
id|S24C16_write_byte
c_func
(paren
id|np
comma
op_amp
id|ack_data
comma
id|offset
op_amp
l_int|0xff
comma
op_amp
id|gpreg
comma
op_amp
id|gpcntl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack_data
op_amp
l_int|0x01
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* regenerate START state to set up for reading */
id|S24C16_start
c_func
(paren
id|np
comma
op_amp
id|gpreg
)paren
suffix:semicolon
multiline_comment|/* rewrite device code and address MSB with read bit set (lsb = 0x01) */
id|S24C16_write_byte
c_func
(paren
id|np
comma
op_amp
id|ack_data
comma
l_int|0xa1
op_or
(paren
(paren
id|offset
op_rshift
l_int|7
)paren
op_amp
l_int|0x0e
)paren
comma
op_amp
id|gpreg
comma
op_amp
id|gpcntl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack_data
op_amp
l_int|0x01
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* now set up GPIO0 for inputting data */
id|gpcntl
op_or_assign
l_int|0x01
suffix:semicolon
id|OUTB
(paren
id|nc_gpcntl
comma
id|gpcntl
)paren
suffix:semicolon
multiline_comment|/* input all requested data - only part of total NVRAM */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|len
suffix:semicolon
id|x
op_increment
)paren
id|S24C16_read_byte
c_func
(paren
id|np
comma
op_amp
id|data
(braket
id|x
)braket
comma
(paren
id|x
op_eq
(paren
id|len
op_minus
l_int|1
)paren
)paren
comma
op_amp
id|gpreg
comma
op_amp
id|gpcntl
)paren
suffix:semicolon
multiline_comment|/* finally put NVRAM back in inactive mode */
id|gpcntl
op_and_assign
l_int|0xfe
suffix:semicolon
id|OUTB
(paren
id|nc_gpcntl
comma
id|gpcntl
)paren
suffix:semicolon
id|S24C16_stop
c_func
(paren
id|np
comma
op_amp
id|gpreg
)paren
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* return GPIO0/1 to original states after having accessed NVRAM */
id|OUTB
(paren
id|nc_gpcntl
comma
id|old_gpcntl
)paren
suffix:semicolon
id|OUTB
(paren
id|nc_gpreg
comma
id|old_gpreg
)paren
suffix:semicolon
r_return
id|retv
suffix:semicolon
)brace
DECL|macro|SET_BIT
macro_line|#undef SET_BIT
DECL|macro|CLR_BIT
macro_line|#undef CLR_BIT
DECL|macro|SET_CLK
macro_line|#undef SET_CLK
DECL|macro|CLR_CLK
macro_line|#undef CLR_CLK
multiline_comment|/*&n; *  Try reading Symbios NVRAM.&n; *  Return 0 if OK.&n; */
DECL|function|sym_read_Symbios_nvram
r_static
r_int
id|sym_read_Symbios_nvram
(paren
id|sdev_p
id|np
comma
id|Symbios_nvram
op_star
id|nvram
)paren
(brace
r_static
id|u_char
id|Symbios_trailer
(braket
l_int|6
)braket
op_assign
(brace
l_int|0xfe
comma
l_int|0xfe
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|u_char
op_star
id|data
op_assign
(paren
id|u_char
op_star
)paren
id|nvram
suffix:semicolon
r_int
id|len
op_assign
r_sizeof
(paren
op_star
id|nvram
)paren
suffix:semicolon
id|u_short
id|csum
suffix:semicolon
r_int
id|x
suffix:semicolon
multiline_comment|/* probe the 24c16 and read the SYMBIOS 24c16 area */
r_if
c_cond
(paren
id|sym_read_S24C16_nvram
(paren
id|np
comma
id|SYMBIOS_NVRAM_ADDRESS
comma
id|data
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* check valid NVRAM signature, verify byte count and checksum */
r_if
c_cond
(paren
id|nvram-&gt;type
op_ne
l_int|0
op_logical_or
id|bcmp
c_func
(paren
id|nvram-&gt;trailer
comma
id|Symbios_trailer
comma
l_int|6
)paren
op_logical_or
id|nvram-&gt;byte_count
op_ne
id|len
op_minus
l_int|12
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* verify checksum */
r_for
c_loop
(paren
id|x
op_assign
l_int|6
comma
id|csum
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|len
op_minus
l_int|6
suffix:semicolon
id|x
op_increment
)paren
id|csum
op_add_assign
id|data
(braket
id|x
)braket
suffix:semicolon
r_if
c_cond
(paren
id|csum
op_ne
id|nvram-&gt;checksum
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  93C46 EEPROM reading.&n; *&n; *  GPOI0 - data in&n; *  GPIO1 - data out&n; *  GPIO2 - clock&n; *  GPIO4 - chip select&n; *&n; *  Used by Tekram.&n; */
multiline_comment|/*&n; *  Pulse clock bit in GPIO0&n; */
DECL|function|T93C46_Clk
r_static
r_void
id|T93C46_Clk
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|gpreg
)paren
(brace
id|OUTB
(paren
id|nc_gpreg
comma
op_star
id|gpreg
op_or
l_int|0x04
)paren
suffix:semicolon
id|UDELAY
(paren
l_int|2
)paren
suffix:semicolon
id|OUTB
(paren
id|nc_gpreg
comma
op_star
id|gpreg
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *  Read bit from NVRAM&n; */
DECL|function|T93C46_Read_Bit
r_static
r_void
id|T93C46_Read_Bit
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|read_bit
comma
id|u_char
op_star
id|gpreg
)paren
(brace
id|UDELAY
(paren
l_int|2
)paren
suffix:semicolon
id|T93C46_Clk
c_func
(paren
id|np
comma
id|gpreg
)paren
suffix:semicolon
op_star
id|read_bit
op_assign
id|INB
(paren
id|nc_gpreg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Write bit to GPIO0&n; */
DECL|function|T93C46_Write_Bit
r_static
r_void
id|T93C46_Write_Bit
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
id|write_bit
comma
id|u_char
op_star
id|gpreg
)paren
(brace
r_if
c_cond
(paren
id|write_bit
op_amp
l_int|0x01
)paren
op_star
id|gpreg
op_or_assign
l_int|0x02
suffix:semicolon
r_else
op_star
id|gpreg
op_and_assign
l_int|0xfd
suffix:semicolon
op_star
id|gpreg
op_or_assign
l_int|0x10
suffix:semicolon
id|OUTB
(paren
id|nc_gpreg
comma
op_star
id|gpreg
)paren
suffix:semicolon
id|UDELAY
(paren
l_int|2
)paren
suffix:semicolon
id|T93C46_Clk
c_func
(paren
id|np
comma
id|gpreg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Send STOP condition to NVRAM - puts NVRAM to sleep... ZZZzzz!!&n; */
DECL|function|T93C46_Stop
r_static
r_void
id|T93C46_Stop
c_func
(paren
id|sdev_p
id|np
comma
id|u_char
op_star
id|gpreg
)paren
(brace
op_star
id|gpreg
op_and_assign
l_int|0xef
suffix:semicolon
id|OUTB
(paren
id|nc_gpreg
comma
op_star
id|gpreg
)paren
suffix:semicolon
id|UDELAY
(paren
l_int|2
)paren
suffix:semicolon
id|T93C46_Clk
c_func
(paren
id|np
comma
id|gpreg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Send read command and address to NVRAM&n; */
DECL|function|T93C46_Send_Command
r_static
r_void
id|T93C46_Send_Command
c_func
(paren
id|sdev_p
id|np
comma
id|u_short
id|write_data
comma
id|u_char
op_star
id|read_bit
comma
id|u_char
op_star
id|gpreg
)paren
(brace
r_int
id|x
suffix:semicolon
multiline_comment|/* send 9 bits, start bit (1), command (2), address (6)  */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|9
suffix:semicolon
id|x
op_increment
)paren
id|T93C46_Write_Bit
c_func
(paren
id|np
comma
(paren
id|u_char
)paren
(paren
id|write_data
op_rshift
(paren
l_int|8
op_minus
id|x
)paren
)paren
comma
id|gpreg
)paren
suffix:semicolon
op_star
id|read_bit
op_assign
id|INB
(paren
id|nc_gpreg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  READ 2 bytes from the NVRAM&n; */
DECL|function|T93C46_Read_Word
r_static
r_void
id|T93C46_Read_Word
c_func
(paren
id|sdev_p
id|np
comma
id|u_short
op_star
id|nvram_data
comma
id|u_char
op_star
id|gpreg
)paren
(brace
r_int
id|x
suffix:semicolon
id|u_char
id|read_bit
suffix:semicolon
op_star
id|nvram_data
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|16
suffix:semicolon
id|x
op_increment
)paren
(brace
id|T93C46_Read_Bit
c_func
(paren
id|np
comma
op_amp
id|read_bit
comma
id|gpreg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_bit
op_amp
l_int|0x01
)paren
op_star
id|nvram_data
op_or_assign
(paren
l_int|0x01
op_lshift
(paren
l_int|15
op_minus
id|x
)paren
)paren
suffix:semicolon
r_else
op_star
id|nvram_data
op_and_assign
op_complement
(paren
l_int|0x01
op_lshift
(paren
l_int|15
op_minus
id|x
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Read Tekram NvRAM data.&n; */
DECL|function|T93C46_Read_Data
r_static
r_int
id|T93C46_Read_Data
c_func
(paren
id|sdev_p
id|np
comma
id|u_short
op_star
id|data
comma
r_int
id|len
comma
id|u_char
op_star
id|gpreg
)paren
(brace
id|u_char
id|read_bit
suffix:semicolon
r_int
id|x
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|len
suffix:semicolon
id|x
op_increment
)paren
(brace
multiline_comment|/* output read command and address */
id|T93C46_Send_Command
c_func
(paren
id|np
comma
l_int|0x180
op_or
id|x
comma
op_amp
id|read_bit
comma
id|gpreg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_bit
op_amp
l_int|0x01
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Bad */
id|T93C46_Read_Word
c_func
(paren
id|np
comma
op_amp
id|data
(braket
id|x
)braket
comma
id|gpreg
)paren
suffix:semicolon
id|T93C46_Stop
c_func
(paren
id|np
comma
id|gpreg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Try reading 93C46 Tekram NVRAM.&n; */
DECL|function|sym_read_T93C46_nvram
r_static
r_int
id|sym_read_T93C46_nvram
(paren
id|sdev_p
id|np
comma
id|Tekram_nvram
op_star
id|nvram
)paren
(brace
id|u_char
id|gpcntl
comma
id|gpreg
suffix:semicolon
id|u_char
id|old_gpcntl
comma
id|old_gpreg
suffix:semicolon
r_int
id|retv
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* save current state of GPCNTL and GPREG */
id|old_gpreg
op_assign
id|INB
(paren
id|nc_gpreg
)paren
suffix:semicolon
id|old_gpcntl
op_assign
id|INB
(paren
id|nc_gpcntl
)paren
suffix:semicolon
multiline_comment|/* set up GPREG &amp; GPCNTL to set GPIO0/1/2/4 in to known state, 0 in,&n;&t;   1/2/4 out */
id|gpreg
op_assign
id|old_gpreg
op_amp
l_int|0xe9
suffix:semicolon
id|OUTB
(paren
id|nc_gpreg
comma
id|gpreg
)paren
suffix:semicolon
id|gpcntl
op_assign
(paren
id|old_gpcntl
op_amp
l_int|0xe9
)paren
op_or
l_int|0x09
suffix:semicolon
id|OUTB
(paren
id|nc_gpcntl
comma
id|gpcntl
)paren
suffix:semicolon
multiline_comment|/* input all of NVRAM, 64 words */
id|retv
op_assign
id|T93C46_Read_Data
c_func
(paren
id|np
comma
(paren
id|u_short
op_star
)paren
id|nvram
comma
r_sizeof
(paren
op_star
id|nvram
)paren
op_div
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|gpreg
)paren
suffix:semicolon
multiline_comment|/* return GPIO0/1/2/4 to original states after having accessed NVRAM */
id|OUTB
(paren
id|nc_gpcntl
comma
id|old_gpcntl
)paren
suffix:semicolon
id|OUTB
(paren
id|nc_gpreg
comma
id|old_gpreg
)paren
suffix:semicolon
r_return
id|retv
suffix:semicolon
)brace
multiline_comment|/*&n; *  Try reading Tekram NVRAM.&n; *  Return 0 if OK.&n; */
DECL|function|sym_read_Tekram_nvram
r_static
r_int
id|sym_read_Tekram_nvram
(paren
id|sdev_p
id|np
comma
id|Tekram_nvram
op_star
id|nvram
)paren
(brace
id|u_char
op_star
id|data
op_assign
(paren
id|u_char
op_star
)paren
id|nvram
suffix:semicolon
r_int
id|len
op_assign
r_sizeof
(paren
op_star
id|nvram
)paren
suffix:semicolon
id|u_short
id|csum
suffix:semicolon
r_int
id|x
suffix:semicolon
r_switch
c_cond
(paren
id|np-&gt;device_id
)paren
(brace
r_case
id|PCI_ID_SYM53C885
suffix:colon
r_case
id|PCI_ID_SYM53C895
suffix:colon
r_case
id|PCI_ID_SYM53C896
suffix:colon
id|x
op_assign
id|sym_read_S24C16_nvram
c_func
(paren
id|np
comma
id|TEKRAM_24C16_NVRAM_ADDRESS
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_ID_SYM53C875
suffix:colon
id|x
op_assign
id|sym_read_S24C16_nvram
c_func
(paren
id|np
comma
id|TEKRAM_24C16_NVRAM_ADDRESS
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_break
suffix:semicolon
r_default
suffix:colon
id|x
op_assign
id|sym_read_T93C46_nvram
c_func
(paren
id|np
comma
id|nvram
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* verify checksum */
r_for
c_loop
(paren
id|x
op_assign
l_int|0
comma
id|csum
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|len
op_minus
l_int|1
suffix:semicolon
id|x
op_add_assign
l_int|2
)paren
id|csum
op_add_assign
id|data
(braket
id|x
)braket
op_plus
(paren
id|data
(braket
id|x
op_plus
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csum
op_ne
l_int|0x1234
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* SYM_CONF_NVRAM_SUPPORT */
eof
