multiline_comment|/*&n; * Copyright (c) 2002-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#ifndef _ASM_IA64_SN_SNDRV_H
DECL|macro|_ASM_IA64_SN_SNDRV_H
mdefine_line|#define _ASM_IA64_SN_SNDRV_H
multiline_comment|/* ioctl commands */
DECL|macro|SNDRV_GET_ROUTERINFO
mdefine_line|#define SNDRV_GET_ROUTERINFO&t;&t;1
DECL|macro|SNDRV_GET_INFOSIZE
mdefine_line|#define SNDRV_GET_INFOSIZE&t;&t;2
DECL|macro|SNDRV_GET_HUBINFO
mdefine_line|#define SNDRV_GET_HUBINFO&t;&t;3
DECL|macro|SNDRV_GET_FLASHLOGSIZE
mdefine_line|#define SNDRV_GET_FLASHLOGSIZE&t;&t;4
DECL|macro|SNDRV_SET_FLASHSYNC
mdefine_line|#define SNDRV_SET_FLASHSYNC&t;&t;5
DECL|macro|SNDRV_GET_FLASHLOGDATA
mdefine_line|#define SNDRV_GET_FLASHLOGDATA&t;&t;6
DECL|macro|SNDRV_GET_FLASHLOGALL
mdefine_line|#define SNDRV_GET_FLASHLOGALL&t;&t;7
DECL|macro|SNDRV_SET_HISTOGRAM_TYPE
mdefine_line|#define SNDRV_SET_HISTOGRAM_TYPE&t;14
DECL|macro|SNDRV_ELSC_COMMAND
mdefine_line|#define SNDRV_ELSC_COMMAND&t;&t;19
DECL|macro|SNDRV_CLEAR_LOG
mdefine_line|#define&t;SNDRV_CLEAR_LOG&t;&t;&t;20
DECL|macro|SNDRV_INIT_LOG
mdefine_line|#define&t;SNDRV_INIT_LOG&t;&t;&t;21
DECL|macro|SNDRV_GET_PIMM_PSC
mdefine_line|#define&t;SNDRV_GET_PIMM_PSC&t;&t;22
DECL|macro|SNDRV_SET_PARTITION
mdefine_line|#define SNDRV_SET_PARTITION&t;&t;23
DECL|macro|SNDRV_GET_PARTITION
mdefine_line|#define SNDRV_GET_PARTITION&t;&t;24
multiline_comment|/* see synergy_perf_ioctl() */
DECL|macro|SNDRV_GET_SYNERGY_VERSION
mdefine_line|#define SNDRV_GET_SYNERGY_VERSION&t;30
DECL|macro|SNDRV_GET_SYNERGY_STATUS
mdefine_line|#define SNDRV_GET_SYNERGY_STATUS&t;31
DECL|macro|SNDRV_GET_SYNERGYINFO
mdefine_line|#define SNDRV_GET_SYNERGYINFO&t;&t;32
DECL|macro|SNDRV_SYNERGY_APPEND
mdefine_line|#define SNDRV_SYNERGY_APPEND&t;&t;33
DECL|macro|SNDRV_SYNERGY_ENABLE
mdefine_line|#define SNDRV_SYNERGY_ENABLE&t;&t;34
DECL|macro|SNDRV_SYNERGY_FREQ
mdefine_line|#define SNDRV_SYNERGY_FREQ&t;&t;35
multiline_comment|/* see shubstats_ioctl() */
DECL|macro|SNDRV_SHUB_INFOSIZE
mdefine_line|#define SNDRV_SHUB_INFOSIZE&t;&t;40
DECL|macro|SNDRV_SHUB_CONFIGURE
mdefine_line|#define SNDRV_SHUB_CONFIGURE&t;&t;41
DECL|macro|SNDRV_SHUB_RESETSTATS
mdefine_line|#define SNDRV_SHUB_RESETSTATS&t;&t;42
DECL|macro|SNDRV_SHUB_GETSTATS
mdefine_line|#define SNDRV_SHUB_GETSTATS&t;&t;43
DECL|macro|SNDRV_SHUB_GETNASID
mdefine_line|#define SNDRV_SHUB_GETNASID&t;&t;44
multiline_comment|/* Devices */
DECL|macro|SNDRV_UKNOWN_DEVICE
mdefine_line|#define SNDRV_UKNOWN_DEVICE&t;&t;-1
DECL|macro|SNDRV_ROUTER_DEVICE
mdefine_line|#define SNDRV_ROUTER_DEVICE&t;&t;1
DECL|macro|SNDRV_HUB_DEVICE
mdefine_line|#define SNDRV_HUB_DEVICE&t;&t;2
DECL|macro|SNDRV_ELSC_NVRAM_DEVICE
mdefine_line|#define SNDRV_ELSC_NVRAM_DEVICE&t;&t;3
DECL|macro|SNDRV_ELSC_CONTROLLER_DEVICE
mdefine_line|#define SNDRV_ELSC_CONTROLLER_DEVICE&t;4
DECL|macro|SNDRV_SYSCTL_SUBCH
mdefine_line|#define SNDRV_SYSCTL_SUBCH&t;&t;5
DECL|macro|SNDRV_SYNERGY_DEVICE
mdefine_line|#define SNDRV_SYNERGY_DEVICE&t;&t;6
macro_line|#endif /* _ASM_IA64_SN_SNDRV_H */
eof
