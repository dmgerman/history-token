multiline_comment|/* $Id: sgiarcs.h,v 1.4 1999/12/04 03:59:12 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * ARC firmware interface defines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SGIARCS_H
DECL|macro|_ASM_SGIARCS_H
mdefine_line|#define _ASM_SGIARCS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arc/types.h&gt;
multiline_comment|/* Various ARCS error codes. */
DECL|macro|PROM_ESUCCESS
mdefine_line|#define PROM_ESUCCESS                   0x00
DECL|macro|PROM_E2BIG
mdefine_line|#define PROM_E2BIG                      0x01
DECL|macro|PROM_EACCESS
mdefine_line|#define PROM_EACCESS                    0x02
DECL|macro|PROM_EAGAIN
mdefine_line|#define PROM_EAGAIN                     0x03
DECL|macro|PROM_EBADF
mdefine_line|#define PROM_EBADF                      0x04
DECL|macro|PROM_EBUSY
mdefine_line|#define PROM_EBUSY                      0x05
DECL|macro|PROM_EFAULT
mdefine_line|#define PROM_EFAULT                     0x06
DECL|macro|PROM_EINVAL
mdefine_line|#define PROM_EINVAL                     0x07
DECL|macro|PROM_EIO
mdefine_line|#define PROM_EIO                        0x08
DECL|macro|PROM_EISDIR
mdefine_line|#define PROM_EISDIR                     0x09
DECL|macro|PROM_EMFILE
mdefine_line|#define PROM_EMFILE                     0x0a
DECL|macro|PROM_EMLINK
mdefine_line|#define PROM_EMLINK                     0x0b
DECL|macro|PROM_ENAMETOOLONG
mdefine_line|#define PROM_ENAMETOOLONG               0x0c
DECL|macro|PROM_ENODEV
mdefine_line|#define PROM_ENODEV                     0x0d
DECL|macro|PROM_ENOENT
mdefine_line|#define PROM_ENOENT                     0x0e
DECL|macro|PROM_ENOEXEC
mdefine_line|#define PROM_ENOEXEC                    0x0f
DECL|macro|PROM_ENOMEM
mdefine_line|#define PROM_ENOMEM                     0x10
DECL|macro|PROM_ENOSPC
mdefine_line|#define PROM_ENOSPC                     0x11
DECL|macro|PROM_ENOTDIR
mdefine_line|#define PROM_ENOTDIR                    0x12
DECL|macro|PROM_ENOTTY
mdefine_line|#define PROM_ENOTTY                     0x13
DECL|macro|PROM_ENXIO
mdefine_line|#define PROM_ENXIO                      0x14
DECL|macro|PROM_EROFS
mdefine_line|#define PROM_EROFS                      0x15
multiline_comment|/* SGI ARCS specific errno&squot;s. */
DECL|macro|PROM_EADDRNOTAVAIL
mdefine_line|#define PROM_EADDRNOTAVAIL              0x1f
DECL|macro|PROM_ETIMEDOUT
mdefine_line|#define PROM_ETIMEDOUT                  0x20
DECL|macro|PROM_ECONNABORTED
mdefine_line|#define PROM_ECONNABORTED               0x21
DECL|macro|PROM_ENOCONNECT
mdefine_line|#define PROM_ENOCONNECT                 0x22
multiline_comment|/* Device classes, types, and identifiers for prom&n; * device inventory queries.&n; */
DECL|enum|linux_devclass
r_enum
id|linux_devclass
(brace
DECL|enumerator|system
DECL|enumerator|processor
DECL|enumerator|cache
DECL|enumerator|adapter
DECL|enumerator|controller
DECL|enumerator|peripheral
DECL|enumerator|memory
id|system
comma
id|processor
comma
id|cache
comma
id|adapter
comma
id|controller
comma
id|peripheral
comma
id|memory
)brace
suffix:semicolon
DECL|enum|linux_devtypes
r_enum
id|linux_devtypes
(brace
multiline_comment|/* Generic stuff. */
DECL|enumerator|Arc
DECL|enumerator|Cpu
DECL|enumerator|Fpu
id|Arc
comma
id|Cpu
comma
id|Fpu
comma
multiline_comment|/* Primary insn and data caches. */
DECL|enumerator|picache
DECL|enumerator|pdcache
id|picache
comma
id|pdcache
comma
multiline_comment|/* Secondary insn, data, and combined caches. */
DECL|enumerator|sicache
DECL|enumerator|sdcache
DECL|enumerator|sccache
id|sicache
comma
id|sdcache
comma
id|sccache
comma
DECL|enumerator|memdev
DECL|enumerator|eisa_adapter
DECL|enumerator|tc_adapter
DECL|enumerator|scsi_adapter
DECL|enumerator|dti_adapter
id|memdev
comma
id|eisa_adapter
comma
id|tc_adapter
comma
id|scsi_adapter
comma
id|dti_adapter
comma
DECL|enumerator|multifunc_adapter
DECL|enumerator|dsk_controller
DECL|enumerator|tp_controller
DECL|enumerator|cdrom_controller
id|multifunc_adapter
comma
id|dsk_controller
comma
id|tp_controller
comma
id|cdrom_controller
comma
DECL|enumerator|worm_controller
DECL|enumerator|serial_controller
DECL|enumerator|net_controller
DECL|enumerator|disp_controller
id|worm_controller
comma
id|serial_controller
comma
id|net_controller
comma
id|disp_controller
comma
DECL|enumerator|parallel_controller
DECL|enumerator|ptr_controller
DECL|enumerator|kbd_controller
DECL|enumerator|audio_controller
id|parallel_controller
comma
id|ptr_controller
comma
id|kbd_controller
comma
id|audio_controller
comma
DECL|enumerator|misc_controller
DECL|enumerator|disk_peripheral
DECL|enumerator|flpy_peripheral
DECL|enumerator|tp_peripheral
id|misc_controller
comma
id|disk_peripheral
comma
id|flpy_peripheral
comma
id|tp_peripheral
comma
DECL|enumerator|modem_peripheral
DECL|enumerator|monitor_peripheral
DECL|enumerator|printer_peripheral
id|modem_peripheral
comma
id|monitor_peripheral
comma
id|printer_peripheral
comma
DECL|enumerator|ptr_peripheral
DECL|enumerator|kbd_peripheral
DECL|enumerator|term_peripheral
DECL|enumerator|line_peripheral
id|ptr_peripheral
comma
id|kbd_peripheral
comma
id|term_peripheral
comma
id|line_peripheral
comma
DECL|enumerator|net_peripheral
DECL|enumerator|misc_peripheral
DECL|enumerator|anon
id|net_peripheral
comma
id|misc_peripheral
comma
id|anon
)brace
suffix:semicolon
DECL|enum|linux_identifier
r_enum
id|linux_identifier
(brace
DECL|enumerator|bogus
DECL|enumerator|ronly
DECL|enumerator|removable
DECL|enumerator|consin
DECL|enumerator|consout
DECL|enumerator|input
DECL|enumerator|output
id|bogus
comma
id|ronly
comma
id|removable
comma
id|consin
comma
id|consout
comma
id|input
comma
id|output
)brace
suffix:semicolon
multiline_comment|/* A prom device tree component. */
DECL|struct|linux_component
r_struct
id|linux_component
(brace
DECL|member|class
r_enum
id|linux_devclass
r_class
suffix:semicolon
multiline_comment|/* node class */
DECL|member|type
r_enum
id|linux_devtypes
id|type
suffix:semicolon
multiline_comment|/* node type */
DECL|member|iflags
r_enum
id|linux_identifier
id|iflags
suffix:semicolon
multiline_comment|/* node flags */
DECL|member|vers
id|USHORT
id|vers
suffix:semicolon
multiline_comment|/* node version */
DECL|member|rev
id|USHORT
id|rev
suffix:semicolon
multiline_comment|/* node revision */
DECL|member|key
id|ULONG
id|key
suffix:semicolon
multiline_comment|/* completely magic */
DECL|member|amask
id|ULONG
id|amask
suffix:semicolon
multiline_comment|/* XXX affinity mask??? */
DECL|member|cdsize
id|ULONG
id|cdsize
suffix:semicolon
multiline_comment|/* size of configuration data */
DECL|member|ilen
id|ULONG
id|ilen
suffix:semicolon
multiline_comment|/* length of string identifier */
DECL|member|iname
id|_PULONG
id|iname
suffix:semicolon
multiline_comment|/* string identifier */
)brace
suffix:semicolon
DECL|typedef|pcomponent
r_typedef
r_struct
id|linux_component
id|pcomponent
suffix:semicolon
DECL|struct|linux_sysid
r_struct
id|linux_sysid
(brace
DECL|member|vend
DECL|member|prod
r_char
id|vend
(braket
l_int|8
)braket
comma
id|prod
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ARCS prom memory descriptors. */
DECL|enum|arcs_memtypes
r_enum
id|arcs_memtypes
(brace
DECL|enumerator|arcs_eblock
id|arcs_eblock
comma
multiline_comment|/* exception block */
DECL|enumerator|arcs_rvpage
id|arcs_rvpage
comma
multiline_comment|/* ARCS romvec page */
DECL|enumerator|arcs_fcontig
id|arcs_fcontig
comma
multiline_comment|/* Contiguous and free */
DECL|enumerator|arcs_free
id|arcs_free
comma
multiline_comment|/* Generic free memory */
DECL|enumerator|arcs_bmem
id|arcs_bmem
comma
multiline_comment|/* Borken memory, don&squot;t use */
DECL|enumerator|arcs_prog
id|arcs_prog
comma
multiline_comment|/* A loaded program resides here */
DECL|enumerator|arcs_atmp
id|arcs_atmp
comma
multiline_comment|/* ARCS temporary storage area, wish Sparc OpenBoot told this */
DECL|enumerator|arcs_aperm
id|arcs_aperm
comma
multiline_comment|/* ARCS permanent storage... */
)brace
suffix:semicolon
multiline_comment|/* ARC has slightly different types than ARCS */
DECL|enum|arc_memtypes
r_enum
id|arc_memtypes
(brace
DECL|enumerator|arc_eblock
id|arc_eblock
comma
multiline_comment|/* exception block */
DECL|enumerator|arc_rvpage
id|arc_rvpage
comma
multiline_comment|/* romvec page */
DECL|enumerator|arc_free
id|arc_free
comma
multiline_comment|/* Generic free memory */
DECL|enumerator|arc_bmem
id|arc_bmem
comma
multiline_comment|/* Borken memory, don&squot;t use */
DECL|enumerator|arc_prog
id|arc_prog
comma
multiline_comment|/* A loaded program resides here */
DECL|enumerator|arc_atmp
id|arc_atmp
comma
multiline_comment|/* temporary storage area */
DECL|enumerator|arc_aperm
id|arc_aperm
comma
multiline_comment|/* permanent storage */
DECL|enumerator|arc_fcontig
id|arc_fcontig
comma
multiline_comment|/* Contiguous and free */
)brace
suffix:semicolon
DECL|union|linux_memtypes
r_union
id|linux_memtypes
(brace
DECL|member|arcs
r_enum
id|arcs_memtypes
id|arcs
suffix:semicolon
DECL|member|arc
r_enum
id|arc_memtypes
id|arc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_mdesc
r_struct
id|linux_mdesc
(brace
DECL|member|type
r_union
id|linux_memtypes
id|type
suffix:semicolon
DECL|member|base
id|ULONG
id|base
suffix:semicolon
DECL|member|pages
id|ULONG
id|pages
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Time of day descriptor. */
DECL|struct|linux_tinfo
r_struct
id|linux_tinfo
(brace
DECL|member|yr
r_int
r_int
id|yr
suffix:semicolon
DECL|member|mnth
r_int
r_int
id|mnth
suffix:semicolon
DECL|member|day
r_int
r_int
id|day
suffix:semicolon
DECL|member|hr
r_int
r_int
id|hr
suffix:semicolon
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
DECL|member|sec
r_int
r_int
id|sec
suffix:semicolon
DECL|member|msec
r_int
r_int
id|msec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ARCS virtual dirents. */
DECL|struct|linux_vdirent
r_struct
id|linux_vdirent
(brace
DECL|member|namelen
id|ULONG
id|namelen
suffix:semicolon
DECL|member|attr
r_int
r_char
id|attr
suffix:semicolon
DECL|member|fname
r_char
id|fname
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* XXX imperical, should be a define */
)brace
suffix:semicolon
multiline_comment|/* Other stuff for files. */
DECL|enum|linux_omode
r_enum
id|linux_omode
(brace
DECL|enumerator|rdonly
DECL|enumerator|wronly
DECL|enumerator|rdwr
DECL|enumerator|wronly_creat
DECL|enumerator|rdwr_creat
id|rdonly
comma
id|wronly
comma
id|rdwr
comma
id|wronly_creat
comma
id|rdwr_creat
comma
DECL|enumerator|wronly_ssede
DECL|enumerator|rdwr_ssede
DECL|enumerator|dirent
DECL|enumerator|dirent_creat
id|wronly_ssede
comma
id|rdwr_ssede
comma
id|dirent
comma
id|dirent_creat
)brace
suffix:semicolon
DECL|enum|linux_seekmode
r_enum
id|linux_seekmode
(brace
DECL|enumerator|absolute
DECL|enumerator|relative
id|absolute
comma
id|relative
)brace
suffix:semicolon
DECL|enum|linux_mountops
r_enum
id|linux_mountops
(brace
DECL|enumerator|media_load
DECL|enumerator|media_unload
id|media_load
comma
id|media_unload
)brace
suffix:semicolon
multiline_comment|/* This prom has a bolixed design. */
DECL|struct|linux_bigint
r_struct
id|linux_bigint
(brace
macro_line|#ifdef __MIPSEL__
DECL|member|lo
r_int
r_int
id|lo
suffix:semicolon
DECL|member|hi
r_int
id|hi
suffix:semicolon
macro_line|#else /* !(__MIPSEL__) */
r_int
id|hi
suffix:semicolon
r_int
r_int
id|lo
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|linux_finfo
r_struct
id|linux_finfo
(brace
DECL|member|begin
r_struct
id|linux_bigint
id|begin
suffix:semicolon
DECL|member|end
r_struct
id|linux_bigint
id|end
suffix:semicolon
DECL|member|cur
r_struct
id|linux_bigint
id|cur
suffix:semicolon
DECL|member|dtype
r_enum
id|linux_devtypes
id|dtype
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
DECL|member|attr
r_int
r_char
id|attr
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* XXX imperical, should be define */
)brace
suffix:semicolon
multiline_comment|/* This describes the vector containing function pointers to the ARC&n;   firmware functions.  */
DECL|struct|linux_romvec
r_struct
id|linux_romvec
(brace
DECL|member|load
id|LONG
id|load
suffix:semicolon
multiline_comment|/* Load an executable image. */
DECL|member|invoke
id|LONG
id|invoke
suffix:semicolon
multiline_comment|/* Invoke a standalong image. */
DECL|member|exec
id|LONG
id|exec
suffix:semicolon
multiline_comment|/* Load and begin execution of a&n;&t;&t;&t;&t;&t;   standalone image. */
DECL|member|halt
id|LONG
id|halt
suffix:semicolon
multiline_comment|/* Halt the machine. */
DECL|member|pdown
id|LONG
id|pdown
suffix:semicolon
multiline_comment|/* Power down the machine. */
DECL|member|restart
id|LONG
id|restart
suffix:semicolon
multiline_comment|/* XXX soft reset??? */
DECL|member|reboot
id|LONG
id|reboot
suffix:semicolon
multiline_comment|/* Reboot the machine. */
DECL|member|imode
id|LONG
id|imode
suffix:semicolon
multiline_comment|/* Enter PROM interactive mode. */
DECL|member|_unused1
id|LONG
id|_unused1
suffix:semicolon
multiline_comment|/* Was ReturnFromMain(). */
multiline_comment|/* PROM device tree interface. */
DECL|member|next_component
id|LONG
id|next_component
suffix:semicolon
DECL|member|child_component
id|LONG
id|child_component
suffix:semicolon
DECL|member|parent_component
id|LONG
id|parent_component
suffix:semicolon
DECL|member|component_data
id|LONG
id|component_data
suffix:semicolon
DECL|member|child_add
id|LONG
id|child_add
suffix:semicolon
DECL|member|comp_del
id|LONG
id|comp_del
suffix:semicolon
DECL|member|component_by_path
id|LONG
id|component_by_path
suffix:semicolon
multiline_comment|/* Misc. stuff. */
DECL|member|cfg_save
id|LONG
id|cfg_save
suffix:semicolon
DECL|member|get_sysid
id|LONG
id|get_sysid
suffix:semicolon
multiline_comment|/* Probing for memory. */
DECL|member|get_mdesc
id|LONG
id|get_mdesc
suffix:semicolon
DECL|member|_unused2
id|LONG
id|_unused2
suffix:semicolon
multiline_comment|/* was Signal() */
DECL|member|get_tinfo
id|LONG
id|get_tinfo
suffix:semicolon
DECL|member|get_rtime
id|LONG
id|get_rtime
suffix:semicolon
multiline_comment|/* File type operations. */
DECL|member|get_vdirent
id|LONG
id|get_vdirent
suffix:semicolon
DECL|member|open
id|LONG
id|open
suffix:semicolon
DECL|member|close
id|LONG
id|close
suffix:semicolon
DECL|member|read
id|LONG
id|read
suffix:semicolon
DECL|member|get_rstatus
id|LONG
id|get_rstatus
suffix:semicolon
DECL|member|write
id|LONG
id|write
suffix:semicolon
DECL|member|seek
id|LONG
id|seek
suffix:semicolon
DECL|member|mount
id|LONG
id|mount
suffix:semicolon
multiline_comment|/* Dealing with firmware environment variables. */
DECL|member|get_evar
id|LONG
id|get_evar
suffix:semicolon
DECL|member|set_evar
id|LONG
id|set_evar
suffix:semicolon
DECL|member|get_finfo
id|LONG
id|get_finfo
suffix:semicolon
DECL|member|set_finfo
id|LONG
id|set_finfo
suffix:semicolon
multiline_comment|/* Miscellaneous. */
DECL|member|cache_flush
id|LONG
id|cache_flush
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The SGI ARCS parameter block is in a fixed location for standalone&n; * programs to access PROM facilities easily.&n; */
DECL|struct|_SYSTEM_PARAMETER_BLOCK
r_typedef
r_struct
id|_SYSTEM_PARAMETER_BLOCK
(brace
DECL|member|magic
id|ULONG
id|magic
suffix:semicolon
multiline_comment|/* magic cookie */
DECL|macro|PROMBLOCK_MAGIC
mdefine_line|#define PROMBLOCK_MAGIC      0x53435241
DECL|member|len
id|ULONG
id|len
suffix:semicolon
multiline_comment|/* length of parm block */
DECL|member|ver
id|USHORT
id|ver
suffix:semicolon
multiline_comment|/* ARCS firmware version */
DECL|member|rev
id|USHORT
id|rev
suffix:semicolon
multiline_comment|/* ARCS firmware revision */
DECL|member|rs_block
id|_PLONG
id|rs_block
suffix:semicolon
multiline_comment|/* Restart block. */
DECL|member|dbg_block
id|_PLONG
id|dbg_block
suffix:semicolon
multiline_comment|/* Debug block. */
DECL|member|gevect
id|_PLONG
id|gevect
suffix:semicolon
multiline_comment|/* XXX General vector??? */
DECL|member|utlbvect
id|_PLONG
id|utlbvect
suffix:semicolon
multiline_comment|/* XXX UTLB vector??? */
DECL|member|rveclen
id|ULONG
id|rveclen
suffix:semicolon
multiline_comment|/* Size of romvec struct. */
DECL|member|romvec
id|_PVOID
id|romvec
suffix:semicolon
multiline_comment|/* Function interface. */
DECL|member|pveclen
id|ULONG
id|pveclen
suffix:semicolon
multiline_comment|/* Length of private vector. */
DECL|member|pvector
id|_PVOID
id|pvector
suffix:semicolon
multiline_comment|/* Private vector. */
DECL|member|adap_cnt
id|ULONG
id|adap_cnt
suffix:semicolon
multiline_comment|/* Adapter count. */
DECL|member|adap_typ0
id|ULONG
id|adap_typ0
suffix:semicolon
multiline_comment|/* First adapter type. */
DECL|member|adap_vcnt0
id|ULONG
id|adap_vcnt0
suffix:semicolon
multiline_comment|/* Adapter 0 vector count. */
DECL|member|adap_vector
id|_PVOID
id|adap_vector
suffix:semicolon
multiline_comment|/* Adapter 0 vector ptr. */
DECL|member|adap_typ1
id|ULONG
id|adap_typ1
suffix:semicolon
multiline_comment|/* Second adapter type. */
DECL|member|adap_vcnt1
id|ULONG
id|adap_vcnt1
suffix:semicolon
multiline_comment|/* Adapter 1 vector count. */
DECL|member|adap_vector1
id|_PVOID
id|adap_vector1
suffix:semicolon
multiline_comment|/* Adapter 1 vector ptr. */
multiline_comment|/* More adapter vectors go here... */
DECL|typedef|SYSTEM_PARAMETER_BLOCK
DECL|typedef|PSYSTEM_PARAMETER_BLOCK
)brace
id|SYSTEM_PARAMETER_BLOCK
comma
op_star
id|PSYSTEM_PARAMETER_BLOCK
suffix:semicolon
DECL|macro|PROMBLOCK
mdefine_line|#define PROMBLOCK ((PSYSTEM_PARAMETER_BLOCK) (int)0xA0001000)
DECL|macro|ROMVECTOR
mdefine_line|#define ROMVECTOR ((struct linux_romvec *) (long)(PROMBLOCK)-&gt;romvec)
multiline_comment|/* Cache layout parameter block. */
DECL|union|linux_cache_key
r_union
id|linux_cache_key
(brace
DECL|struct|param
r_struct
id|param
(brace
macro_line|#ifdef __MIPSEL__
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|lsize
r_int
r_char
id|lsize
suffix:semicolon
DECL|member|bsize
r_int
r_char
id|bsize
suffix:semicolon
macro_line|#else /* !(__MIPSEL__) */
r_int
r_char
id|bsize
suffix:semicolon
r_int
r_char
id|lsize
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
macro_line|#endif
DECL|member|info
)brace
id|info
suffix:semicolon
DECL|member|allinfo
r_int
r_int
id|allinfo
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Configuration data. */
DECL|struct|linux_cdata
r_struct
id|linux_cdata
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|mlen
r_int
id|mlen
suffix:semicolon
DECL|member|type
r_enum
id|linux_devtypes
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Common SGI ARCS firmware file descriptors. */
DECL|macro|SGIPROM_STDIN
mdefine_line|#define SGIPROM_STDIN     0
DECL|macro|SGIPROM_STDOUT
mdefine_line|#define SGIPROM_STDOUT    1
multiline_comment|/* Common SGI ARCS firmware file types. */
DECL|macro|SGIPROM_ROFILE
mdefine_line|#define SGIPROM_ROFILE    0x01  /* read-only file */
DECL|macro|SGIPROM_HFILE
mdefine_line|#define SGIPROM_HFILE     0x02  /* hidden file */
DECL|macro|SGIPROM_SFILE
mdefine_line|#define SGIPROM_SFILE     0x04  /* System file */
DECL|macro|SGIPROM_AFILE
mdefine_line|#define SGIPROM_AFILE     0x08  /* Archive file */
DECL|macro|SGIPROM_DFILE
mdefine_line|#define SGIPROM_DFILE     0x10  /* Directory file */
DECL|macro|SGIPROM_DELFILE
mdefine_line|#define SGIPROM_DELFILE   0x20  /* Deleted file */
multiline_comment|/* SGI ARCS boot record information. */
DECL|struct|sgi_partition
r_struct
id|sgi_partition
(brace
DECL|member|flag
r_int
r_char
id|flag
suffix:semicolon
DECL|macro|SGIPART_UNUSED
mdefine_line|#define SGIPART_UNUSED 0x00
DECL|macro|SGIPART_ACTIVE
mdefine_line|#define SGIPART_ACTIVE 0x80
DECL|member|shead
DECL|member|ssect
DECL|member|scyl
r_int
r_char
id|shead
comma
id|ssect
comma
id|scyl
suffix:semicolon
multiline_comment|/* unused */
DECL|member|systype
r_int
r_char
id|systype
suffix:semicolon
multiline_comment|/* OS type, Irix or NT */
DECL|member|ehead
DECL|member|esect
DECL|member|ecyl
r_int
r_char
id|ehead
comma
id|esect
comma
id|ecyl
suffix:semicolon
multiline_comment|/* unused */
DECL|member|rsect0
DECL|member|rsect1
DECL|member|rsect2
DECL|member|rsect3
r_int
r_char
id|rsect0
comma
id|rsect1
comma
id|rsect2
comma
id|rsect3
suffix:semicolon
DECL|member|tsect0
DECL|member|tsect1
DECL|member|tsect2
DECL|member|tsect3
r_int
r_char
id|tsect0
comma
id|tsect1
comma
id|tsect2
comma
id|tsect3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SGIBBLOCK_MAGIC
mdefine_line|#define SGIBBLOCK_MAGIC   0xaa55
DECL|macro|SGIBBLOCK_MAXPART
mdefine_line|#define SGIBBLOCK_MAXPART 0x0004
DECL|struct|sgi_bootblock
r_struct
id|sgi_bootblock
(brace
DECL|member|_unused
r_int
r_char
id|_unused
(braket
l_int|446
)braket
suffix:semicolon
DECL|member|partitions
r_struct
id|sgi_partition
id|partitions
(braket
id|SGIBBLOCK_MAXPART
)braket
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* BIOS parameter block. */
DECL|struct|sgi_bparm_block
r_struct
id|sgi_bparm_block
(brace
DECL|member|bytes_sect
r_int
r_int
id|bytes_sect
suffix:semicolon
multiline_comment|/* bytes per sector */
DECL|member|sect_clust
r_int
r_char
id|sect_clust
suffix:semicolon
multiline_comment|/* sectors per cluster */
DECL|member|sect_resv
r_int
r_int
id|sect_resv
suffix:semicolon
multiline_comment|/* reserved sectors */
DECL|member|nfats
r_int
r_char
id|nfats
suffix:semicolon
multiline_comment|/* # of allocation tables */
DECL|member|nroot_dirents
r_int
r_int
id|nroot_dirents
suffix:semicolon
multiline_comment|/* # of root directory entries */
DECL|member|sect_volume
r_int
r_int
id|sect_volume
suffix:semicolon
multiline_comment|/* sectors in volume */
DECL|member|media_type
r_int
r_char
id|media_type
suffix:semicolon
multiline_comment|/* media descriptor */
DECL|member|sect_fat
r_int
r_int
id|sect_fat
suffix:semicolon
multiline_comment|/* sectors per allocation table */
DECL|member|sect_track
r_int
r_int
id|sect_track
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|nheads
r_int
r_int
id|nheads
suffix:semicolon
multiline_comment|/* # of heads */
DECL|member|nhsects
r_int
r_int
id|nhsects
suffix:semicolon
multiline_comment|/* # of hidden sectors */
)brace
suffix:semicolon
DECL|struct|sgi_bsector
r_struct
id|sgi_bsector
(brace
DECL|member|jmpinfo
r_int
r_char
id|jmpinfo
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|manuf_name
r_int
r_char
id|manuf_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|info
r_struct
id|sgi_bparm_block
id|info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Debugging block used with SGI symmon symbolic debugger. */
DECL|macro|SMB_DEBUG_MAGIC
mdefine_line|#define SMB_DEBUG_MAGIC   0xfeeddead
DECL|struct|linux_smonblock
r_struct
id|linux_smonblock
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Breakpoint routine. */
DECL|member|dtable_base
r_int
r_int
id|dtable_base
suffix:semicolon
multiline_comment|/* Base addr of dbg table. */
DECL|member|printf
r_int
(paren
op_star
id|printf
)paren
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|member|btable_base
r_int
r_int
id|btable_base
suffix:semicolon
multiline_comment|/* Breakpoint table. */
DECL|member|mpflushreqs
r_int
r_int
id|mpflushreqs
suffix:semicolon
multiline_comment|/* SMP cache flush request list. */
DECL|member|ntab
r_int
r_int
id|ntab
suffix:semicolon
multiline_comment|/* Name table. */
DECL|member|stab
r_int
r_int
id|stab
suffix:semicolon
multiline_comment|/* Symbol table. */
DECL|member|smax
r_int
id|smax
suffix:semicolon
multiline_comment|/* Max # of symbols. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Macros for calling a 32-bit ARC implementation from 64-bit code&n; */
macro_line|#ifdef CONFIG_ARC32
DECL|macro|__arc_clobbers
mdefine_line|#define __arc_clobbers&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$7&quot;,&quot;$8&quot;,&quot;$9&quot;,&quot;$10&quot;,&quot;$11&quot;,&t;&t;&bslash;&n;&t;&quot;$12&quot;,&quot;$13&quot;,&quot;$14&quot;,&quot;$15&quot;,&quot;$16&quot;,&quot;$24&quot;,&quot;25&quot;,&quot;$31&quot;
DECL|macro|ARC_CALL0
mdefine_line|#define ARC_CALL0(dest)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __vec = (long) romvec-&gt;dest;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;dsubu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jalr&bslash;t%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;daddu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0, $2&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res), &quot;=r&quot; (__vec)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;1&quot; (__vec)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: __arc_clobbers);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned long) __res;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL1
mdefine_line|#define ARC_CALL1(dest,a1)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register signed int __a1 __asm__(&quot;$4&quot;) = (int) (long) (a1);&t;&bslash;&n;&t;long __vec = (long) romvec-&gt;dest;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;dsubu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jalr&bslash;t%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;daddu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0, $2&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res), &quot;=r&quot; (__vec)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;1&quot; (__vec), &quot;r&quot; (__a1)&t;&t;&t;&t;&t;&bslash;&n;&t;: __arc_clobbers);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned long) __res;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL2
mdefine_line|#define ARC_CALL2(dest,a1,a2)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register signed int __a1 __asm__(&quot;$4&quot;) = (int) (long) (a1);&t;&bslash;&n;&t;register signed int __a2 __asm__(&quot;$5&quot;) = (int) (long) (a2);&t;&bslash;&n;&t;long __vec = (long) romvec-&gt;dest;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;dsubu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jalr&bslash;t%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;daddu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0, $2&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res), &quot;=r&quot; (__vec)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;1&quot; (__vec), &quot;r&quot; (__a1), &quot;r&quot; (__a2)&t;&t;&t;&t;&bslash;&n;&t;: __arc_clobbers);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL3
mdefine_line|#define ARC_CALL3(dest,a1,a2,a3)&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register signed int __a1 __asm__(&quot;$4&quot;) = (int) (long) (a1);&t;&bslash;&n;&t;register signed int __a2 __asm__(&quot;$5&quot;) = (int) (long) (a2);&t;&bslash;&n;&t;register signed int __a3 __asm__(&quot;$6&quot;) = (int) (long) (a3);&t;&bslash;&n;&t;long __vec = (long) romvec-&gt;dest;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;dsubu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jalr&bslash;t%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;daddu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0, $2&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res), &quot;=r&quot; (__vec)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;1&quot; (__vec), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;r&quot; (__a3)&t;&t;&bslash;&n;&t;: __arc_clobbers);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL4
mdefine_line|#define ARC_CALL4(dest,a1,a2,a3,a4)&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register signed int __a1 __asm__(&quot;$4&quot;) = (int) (long) (a1);&t;&bslash;&n;&t;register signed int __a2 __asm__(&quot;$5&quot;) = (int) (long) (a2);&t;&bslash;&n;&t;register signed int __a3 __asm__(&quot;$6&quot;) = (int) (long) (a3);&t;&bslash;&n;&t;register signed int __a4 __asm__(&quot;$7&quot;) = (int) (long) (a4);&t;&bslash;&n;&t;long __vec = (long) romvec-&gt;dest;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;dsubu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jalr&bslash;t%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;daddu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0, $2&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res), &quot;=r&quot; (__vec)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;1&quot; (__vec), &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;r&quot; (__a3), &t;&t;&bslash;&n;&t;  &quot;r&quot; (__a4)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: __arc_clobbers);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL5
mdefine_line|#define ARC_CALL5(dest,a1,a2,a3,a4,a5)&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register signed int __a1 __asm__(&quot;$4&quot;) = (int) (long) (a1);&t;&bslash;&n;&t;register signed int __a2 __asm__(&quot;$5&quot;) = (int) (long) (a2);&t;&bslash;&n;&t;register signed int __a3 __asm__(&quot;$6&quot;) = (int) (long) (a3);&t;&bslash;&n;&t;register signed int __a4 __asm__(&quot;$7&quot;) = (int) (long) (a4);&t;&bslash;&n;&t;register signed int __a5 = (a5);&t;&t;&t;&t;&bslash;&n;&t;long __vec = (long) romvec-&gt;dest;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;dsubu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t%6, 16($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jalr&bslash;t%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;daddu&bslash;t$29, 32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0, $2&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__res), &quot;=r&quot; (__vec)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;1&quot; (__vec),&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;r&quot; (__a1), &quot;r&quot; (__a2), &quot;r&quot; (__a3), &quot;r&quot; (__a4),&t;&t;&bslash;&n;&t;  &quot;r&quot; (__a5)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: __arc_clobbers);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* CONFIG_ARC32 */
macro_line|#ifdef CONFIG_ARC64
DECL|macro|ARC_CALL0
mdefine_line|#define ARC_CALL0(dest)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long (*__vec)(void) = (void *) romvec-&gt;dest;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = __vec();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL1
mdefine_line|#define ARC_CALL1(dest,a1)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __a1 = (long) (a1);&t;&t;&t;&t;&t;&bslash;&n;&t;long (*__vec)(long) = (void *) romvec-&gt;dest;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = __vec(__a1);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL2
mdefine_line|#define ARC_CALL2(dest,a1,a2)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __a1 = (long) (a1);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a2 = (long) (a2);&t;&t;&t;&t;&t;&bslash;&n;&t;long (*__vec)(long, long) = (void *) romvec-&gt;dest;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = __vec(__a1, __a2);&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL3
mdefine_line|#define ARC_CALL3(dest,a1,a2,a3)&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __a1 = (long) (a1);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a2 = (long) (a2);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a3 = (long) (a3);&t;&t;&t;&t;&t;&bslash;&n;&t;long (*__vec)(long, long, long)&t;= (void *) romvec-&gt;dest;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = __vec(__a1, __a2, __a3);&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL4
mdefine_line|#define ARC_CALL4(dest,a1,a2,a3,a4)&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __a1 = (long) (a1);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a2 = (long) (a2);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a3 = (long) (a3);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a4 = (long) (a4);&t;&t;&t;&t;&t;&bslash;&n;&t;long (*__vec)(long, long, long, long) = (void *) romvec-&gt;dest;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = __vec(__a1, __a2, __a3, __a4);&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ARC_CALL5
mdefine_line|#define ARC_CALL5(dest,a1,a2,a3,a4,a5)&t;&t;&t;&t;&t;&bslash;&n;({&t;long __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __a1 = (long) (a1);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a2 = (long) (a2);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a3 = (long) (a3);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a4 = (long) (a4);&t;&t;&t;&t;&t;&bslash;&n;&t;long __a5 = (long) (a5);&t;&t;&t;&t;&t;&bslash;&n;&t;long (*__vec)(long, long, long, long, long);&t;&t;&t;&bslash;&n;&t;__vec = (void *) romvec-&gt;dest;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res = __vec(__a1, __a2, __a3, __a4, __a5);&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* CONFIG_ARC64 */
macro_line|#endif /* _ASM_SGIARCS_H */
eof
