multiline_comment|/* vlclient.h: Volume Location Service client interface&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_VLCLIENT_H
DECL|macro|_LINUX_AFS_VLCLIENT_H
mdefine_line|#define _LINUX_AFS_VLCLIENT_H
macro_line|#include &quot;types.h&quot;
DECL|enum|AFSVL_Errors
r_enum
id|AFSVL_Errors
(brace
DECL|enumerator|AFSVL_IDEXIST
id|AFSVL_IDEXIST
op_assign
l_int|363520
comma
multiline_comment|/* Volume Id entry exists in vl database */
DECL|enumerator|AFSVL_IO
id|AFSVL_IO
op_assign
l_int|363521
comma
multiline_comment|/* I/O related error */
DECL|enumerator|AFSVL_NAMEEXIST
id|AFSVL_NAMEEXIST
op_assign
l_int|363522
comma
multiline_comment|/* Volume name entry exists in vl database */
DECL|enumerator|AFSVL_CREATEFAIL
id|AFSVL_CREATEFAIL
op_assign
l_int|363523
comma
multiline_comment|/* Internal creation failure */
DECL|enumerator|AFSVL_NOENT
id|AFSVL_NOENT
op_assign
l_int|363524
comma
multiline_comment|/* No such entry */
DECL|enumerator|AFSVL_EMPTY
id|AFSVL_EMPTY
op_assign
l_int|363525
comma
multiline_comment|/* Vl database is empty */
DECL|enumerator|AFSVL_ENTDELETED
id|AFSVL_ENTDELETED
op_assign
l_int|363526
comma
multiline_comment|/* Entry is deleted (soft delete) */
DECL|enumerator|AFSVL_BADNAME
id|AFSVL_BADNAME
op_assign
l_int|363527
comma
multiline_comment|/* Volume name is illegal */
DECL|enumerator|AFSVL_BADINDEX
id|AFSVL_BADINDEX
op_assign
l_int|363528
comma
multiline_comment|/* Index is out of range */
DECL|enumerator|AFSVL_BADVOLTYPE
id|AFSVL_BADVOLTYPE
op_assign
l_int|363529
comma
multiline_comment|/* Bad volume type */
DECL|enumerator|AFSVL_BADSERVER
id|AFSVL_BADSERVER
op_assign
l_int|363530
comma
multiline_comment|/* Illegal server number (out of range) */
DECL|enumerator|AFSVL_BADPARTITION
id|AFSVL_BADPARTITION
op_assign
l_int|363531
comma
multiline_comment|/* Bad partition number */
DECL|enumerator|AFSVL_REPSFULL
id|AFSVL_REPSFULL
op_assign
l_int|363532
comma
multiline_comment|/* Run out of space for Replication sites */
DECL|enumerator|AFSVL_NOREPSERVER
id|AFSVL_NOREPSERVER
op_assign
l_int|363533
comma
multiline_comment|/* No such Replication server site exists */
DECL|enumerator|AFSVL_DUPREPSERVER
id|AFSVL_DUPREPSERVER
op_assign
l_int|363534
comma
multiline_comment|/* Replication site already exists */
DECL|enumerator|AFSVL_RWNOTFOUND
id|AFSVL_RWNOTFOUND
op_assign
l_int|363535
comma
multiline_comment|/* Parent R/W entry not found */
DECL|enumerator|AFSVL_BADREFCOUNT
id|AFSVL_BADREFCOUNT
op_assign
l_int|363536
comma
multiline_comment|/* Illegal Reference Count number */
DECL|enumerator|AFSVL_SIZEEXCEEDED
id|AFSVL_SIZEEXCEEDED
op_assign
l_int|363537
comma
multiline_comment|/* Vl size for attributes exceeded */
DECL|enumerator|AFSVL_BADENTRY
id|AFSVL_BADENTRY
op_assign
l_int|363538
comma
multiline_comment|/* Bad incoming vl entry */
DECL|enumerator|AFSVL_BADVOLIDBUMP
id|AFSVL_BADVOLIDBUMP
op_assign
l_int|363539
comma
multiline_comment|/* Illegal max volid increment */
DECL|enumerator|AFSVL_IDALREADYHASHED
id|AFSVL_IDALREADYHASHED
op_assign
l_int|363540
comma
multiline_comment|/* RO/BACK id already hashed */
DECL|enumerator|AFSVL_ENTRYLOCKED
id|AFSVL_ENTRYLOCKED
op_assign
l_int|363541
comma
multiline_comment|/* Vl entry is already locked */
DECL|enumerator|AFSVL_BADVOLOPER
id|AFSVL_BADVOLOPER
op_assign
l_int|363542
comma
multiline_comment|/* Bad volume operation code */
DECL|enumerator|AFSVL_BADRELLOCKTYPE
id|AFSVL_BADRELLOCKTYPE
op_assign
l_int|363543
comma
multiline_comment|/* Bad release lock type */
DECL|enumerator|AFSVL_RERELEASE
id|AFSVL_RERELEASE
op_assign
l_int|363544
comma
multiline_comment|/* Status report: last release was aborted */
DECL|enumerator|AFSVL_BADSERVERFLAG
id|AFSVL_BADSERVERFLAG
op_assign
l_int|363545
comma
multiline_comment|/* Invalid replication site server &#xfffd;ag */
DECL|enumerator|AFSVL_PERM
id|AFSVL_PERM
op_assign
l_int|363546
comma
multiline_comment|/* No permission access */
DECL|enumerator|AFSVL_NOMEM
id|AFSVL_NOMEM
op_assign
l_int|363547
comma
multiline_comment|/* malloc/realloc failed to alloc enough memory */
)brace
suffix:semicolon
multiline_comment|/* maps to &quot;struct vldbentry&quot; in vvl-spec.pdf */
DECL|struct|afs_vldbentry
r_struct
id|afs_vldbentry
(brace
DECL|member|name
r_char
id|name
(braket
l_int|65
)braket
suffix:semicolon
multiline_comment|/* name of volume (including NUL char) */
DECL|member|type
id|afs_voltype_t
id|type
suffix:semicolon
multiline_comment|/* volume type */
DECL|member|num_servers
r_int
id|num_servers
suffix:semicolon
multiline_comment|/* num servers that hold instances of this vol */
DECL|member|clone_id
r_int
id|clone_id
suffix:semicolon
multiline_comment|/* cloning ID */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|macro|AFS_VLF_RWEXISTS
mdefine_line|#define AFS_VLF_RWEXISTS&t;0x1000&t;&t;/* R/W volume exists */
DECL|macro|AFS_VLF_ROEXISTS
mdefine_line|#define AFS_VLF_ROEXISTS&t;0x2000&t;&t;/* R/O volume exists */
DECL|macro|AFS_VLF_BACKEXISTS
mdefine_line|#define AFS_VLF_BACKEXISTS&t;0x4000&t;&t;/* backup volume exists */
DECL|member|volume_ids
id|afs_volid_t
id|volume_ids
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* volume IDs */
r_struct
(brace
DECL|member|addr
r_struct
id|in_addr
id|addr
suffix:semicolon
multiline_comment|/* server address */
DECL|member|partition
r_int
id|partition
suffix:semicolon
multiline_comment|/* partition ID on this server */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* server specific flags */
DECL|macro|AFS_VLSF_NEWREPSITE
mdefine_line|#define AFS_VLSF_NEWREPSITE&t;0x0001&t;/* unused */
DECL|macro|AFS_VLSF_ROVOL
mdefine_line|#define AFS_VLSF_ROVOL&t;&t;0x0002&t;/* this server holds a R/O instance of the volume */
DECL|macro|AFS_VLSF_RWVOL
mdefine_line|#define AFS_VLSF_RWVOL&t;&t;0x0004&t;/* this server holds a R/W instance of the volume */
DECL|macro|AFS_VLSF_BACKVOL
mdefine_line|#define AFS_VLSF_BACKVOL&t;0x0008&t;/* this server holds a backup instance of the volume */
DECL|member|servers
)brace
id|servers
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* look up a volume location database entry by name */
r_extern
r_int
id|afs_rxvl_get_entry_by_name
c_func
(paren
r_struct
id|afs_server
op_star
id|server
comma
r_const
r_char
op_star
id|volname
comma
r_int
id|volnamesz
comma
r_struct
id|afs_cache_vlocation
op_star
id|entry
)paren
suffix:semicolon
multiline_comment|/* look up a volume location database entry by ID */
r_extern
r_int
id|afs_rxvl_get_entry_by_id
c_func
(paren
r_struct
id|afs_server
op_star
id|server
comma
id|afs_volid_t
id|volid
comma
id|afs_voltype_t
id|voltype
comma
r_struct
id|afs_cache_vlocation
op_star
id|entry
)paren
suffix:semicolon
r_extern
r_int
id|afs_rxvl_get_entry_by_id_async
c_func
(paren
r_struct
id|afs_async_op
op_star
id|op
comma
id|afs_volid_t
id|volid
comma
id|afs_voltype_t
id|voltype
)paren
suffix:semicolon
r_extern
r_int
id|afs_rxvl_get_entry_by_id_async2
c_func
(paren
r_struct
id|afs_async_op
op_star
id|op
comma
r_struct
id|afs_cache_vlocation
op_star
id|entry
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_VLCLIENT_H */
eof
