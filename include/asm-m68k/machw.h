multiline_comment|/*&n;** linux/machw.h -- This header defines some macros and pointers for&n;**                    the various Macintosh custom hardware registers.&n;**&n;** Copyright 1997 by Michael Schmitz&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef _ASM_MACHW_H_
DECL|macro|_ASM_MACHW_H_
mdefine_line|#define _ASM_MACHW_H_
multiline_comment|/*&n; * head.S maps the videomem to VIDEOMEMBASE&n; */
DECL|macro|VIDEOMEMBASE
mdefine_line|#define VIDEOMEMBASE&t;0xf0000000
DECL|macro|VIDEOMEMSIZE
mdefine_line|#define VIDEOMEMSIZE&t;(4096*1024)
DECL|macro|VIDEOMEMMASK
mdefine_line|#define VIDEOMEMMASK&t;(-4096*1024)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#if 0
multiline_comment|/* Mac SCSI Controller 5380 */
mdefine_line|#define&t;MAC_5380_BAS&t;(0x50F10000) /* This is definitely wrong!! */
r_struct
id|MAC_5380
(brace
id|u_char
id|scsi_data
suffix:semicolon
id|u_char
id|char_dummy1
suffix:semicolon
id|u_char
id|scsi_icr
suffix:semicolon
id|u_char
id|char_dummy2
suffix:semicolon
id|u_char
id|scsi_mode
suffix:semicolon
id|u_char
id|char_dummy3
suffix:semicolon
id|u_char
id|scsi_tcr
suffix:semicolon
id|u_char
id|char_dummy4
suffix:semicolon
id|u_char
id|scsi_idstat
suffix:semicolon
id|u_char
id|char_dummy5
suffix:semicolon
id|u_char
id|scsi_dmastat
suffix:semicolon
id|u_char
id|char_dummy6
suffix:semicolon
id|u_char
id|scsi_targrcv
suffix:semicolon
id|u_char
id|char_dummy7
suffix:semicolon
id|u_char
id|scsi_inircv
suffix:semicolon
)brace
suffix:semicolon
mdefine_line|#define&t;mac_scsi       ((*(volatile struct MAC_5380 *)MAC_5380_BAS))
multiline_comment|/*&n;** SCC Z8530&n;*/
mdefine_line|#define MAC_SCC_BAS (0x50F04000)
r_struct
id|MAC_SCC
(brace
id|u_char
id|cha_a_ctrl
suffix:semicolon
id|u_char
id|char_dummy1
suffix:semicolon
id|u_char
id|cha_a_data
suffix:semicolon
id|u_char
id|char_dummy2
suffix:semicolon
id|u_char
id|cha_b_ctrl
suffix:semicolon
id|u_char
id|char_dummy3
suffix:semicolon
id|u_char
id|cha_b_data
suffix:semicolon
)brace
suffix:semicolon
macro_line|# define mac_scc ((*(volatile struct SCC*)MAC_SCC_BAS))
macro_line|#endif
multiline_comment|/* hardware stuff */
DECL|macro|MACHW_DECLARE
mdefine_line|#define MACHW_DECLARE(name)    unsigned name : 1
DECL|macro|MACHW_SET
mdefine_line|#define MACHW_SET(name)                (mac_hw_present.name = 1)
DECL|macro|MACHW_PRESENT
mdefine_line|#define MACHW_PRESENT(name)    (mac_hw_present.name)
r_struct
(brace
multiline_comment|/* video hardware */
multiline_comment|/* sound hardware */
multiline_comment|/* disk storage interfaces */
id|MACHW_DECLARE
c_func
(paren
id|MAC_SCSI_80
)paren
suffix:semicolon
multiline_comment|/* Directly mapped NCR5380 */
id|MACHW_DECLARE
c_func
(paren
id|MAC_SCSI_96
)paren
suffix:semicolon
multiline_comment|/* 53c9[46] */
id|MACHW_DECLARE
c_func
(paren
id|MAC_SCSI_96_2
)paren
suffix:semicolon
multiline_comment|/* 2nd 53c9[46] Q900 and Q950 */
id|MACHW_DECLARE
c_func
(paren
id|IDE
)paren
suffix:semicolon
multiline_comment|/* IDE Interface */
multiline_comment|/* other I/O hardware */
id|MACHW_DECLARE
c_func
(paren
id|SCC
)paren
suffix:semicolon
multiline_comment|/* Serial Communications Contr. */
multiline_comment|/* DMA */
id|MACHW_DECLARE
c_func
(paren
id|SCSI_DMA
)paren
suffix:semicolon
multiline_comment|/* DMA for the NCR5380 */
multiline_comment|/* real time clocks */
id|MACHW_DECLARE
c_func
(paren
id|RTC_CLK
)paren
suffix:semicolon
multiline_comment|/* clock chip */
multiline_comment|/* supporting hardware */
id|MACHW_DECLARE
c_func
(paren
id|VIA1
)paren
suffix:semicolon
multiline_comment|/* Versatile Interface Ad. 1 */
id|MACHW_DECLARE
c_func
(paren
id|VIA2
)paren
suffix:semicolon
multiline_comment|/* Versatile Interface Ad. 2 */
id|MACHW_DECLARE
c_func
(paren
id|RBV
)paren
suffix:semicolon
multiline_comment|/* Versatile Interface Ad. 2+ */
multiline_comment|/* NUBUS */
id|MACHW_DECLARE
c_func
(paren
id|NUBUS
)paren
suffix:semicolon
multiline_comment|/* NUBUS */
DECL|variable|mac_hw_present
)brace
id|mac_hw_present
suffix:semicolon
multiline_comment|/* extern struct mac_hw_present mac_hw_present; */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* linux/machw.h */
eof
