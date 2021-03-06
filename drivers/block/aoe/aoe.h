multiline_comment|/* Copyright (c) 2004 Coraid, Inc.  See COPYING for GPL terms. */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;5&quot;
DECL|macro|AOE_MAJOR
mdefine_line|#define AOE_MAJOR 152
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;aoe&quot;
macro_line|#ifndef AOE_PARTITIONS
DECL|macro|AOE_PARTITIONS
mdefine_line|#define AOE_PARTITIONS 16
macro_line|#endif
DECL|macro|SYSMINOR
mdefine_line|#define SYSMINOR(aoemajor, aoeminor) ((aoemajor) * 10 + (aoeminor))
DECL|macro|AOEMAJOR
mdefine_line|#define AOEMAJOR(sysminor) ((sysminor) / 10)
DECL|macro|AOEMINOR
mdefine_line|#define AOEMINOR(sysminor) ((sysminor) % 10)
DECL|macro|WHITESPACE
mdefine_line|#define WHITESPACE &quot; &bslash;t&bslash;v&bslash;f&bslash;n&quot;
r_enum
(brace
DECL|enumerator|AOECMD_ATA
id|AOECMD_ATA
comma
DECL|enumerator|AOECMD_CFG
id|AOECMD_CFG
comma
DECL|enumerator|AOEFL_RSP
id|AOEFL_RSP
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
DECL|enumerator|AOEFL_ERR
id|AOEFL_ERR
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
DECL|enumerator|AOEAFL_EXT
id|AOEAFL_EXT
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
DECL|enumerator|AOEAFL_DEV
id|AOEAFL_DEV
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
DECL|enumerator|AOEAFL_ASYNC
id|AOEAFL_ASYNC
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|AOEAFL_WRITE
id|AOEAFL_WRITE
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|AOECCMD_READ
id|AOECCMD_READ
op_assign
l_int|0
comma
DECL|enumerator|AOECCMD_TEST
id|AOECCMD_TEST
comma
DECL|enumerator|AOECCMD_PTEST
id|AOECCMD_PTEST
comma
DECL|enumerator|AOECCMD_SET
id|AOECCMD_SET
comma
DECL|enumerator|AOECCMD_FSET
id|AOECCMD_FSET
comma
DECL|enumerator|AOE_HVER
id|AOE_HVER
op_assign
l_int|0x10
comma
)brace
suffix:semicolon
DECL|struct|aoe_hdr
r_struct
id|aoe_hdr
(brace
DECL|member|dst
r_int
r_char
id|dst
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|src
r_int
r_char
id|src
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|verfl
r_int
r_char
id|verfl
suffix:semicolon
DECL|member|err
r_int
r_char
id|err
suffix:semicolon
DECL|member|major
r_int
r_char
id|major
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|minor
r_int
r_char
id|minor
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
suffix:semicolon
DECL|member|tag
r_int
r_char
id|tag
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aoe_atahdr
r_struct
id|aoe_atahdr
(brace
DECL|member|aflags
r_int
r_char
id|aflags
suffix:semicolon
DECL|member|errfeat
r_int
r_char
id|errfeat
suffix:semicolon
DECL|member|scnt
r_int
r_char
id|scnt
suffix:semicolon
DECL|member|cmdstat
r_int
r_char
id|cmdstat
suffix:semicolon
DECL|member|lba0
r_int
r_char
id|lba0
suffix:semicolon
DECL|member|lba1
r_int
r_char
id|lba1
suffix:semicolon
DECL|member|lba2
r_int
r_char
id|lba2
suffix:semicolon
DECL|member|lba3
r_int
r_char
id|lba3
suffix:semicolon
DECL|member|lba4
r_int
r_char
id|lba4
suffix:semicolon
DECL|member|lba5
r_int
r_char
id|lba5
suffix:semicolon
DECL|member|res
r_int
r_char
id|res
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aoe_cfghdr
r_struct
id|aoe_cfghdr
(brace
DECL|member|bufcnt
r_int
r_char
id|bufcnt
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fwver
r_int
r_char
id|fwver
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|res
r_int
r_char
id|res
suffix:semicolon
DECL|member|aoeccmd
r_int
r_char
id|aoeccmd
suffix:semicolon
DECL|member|cslen
r_int
r_char
id|cslen
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|DEVFL_UP
id|DEVFL_UP
op_assign
l_int|1
comma
multiline_comment|/* device is installed in system and ready for AoE-&gt;ATA commands */
DECL|enumerator|DEVFL_TKILL
id|DEVFL_TKILL
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* flag for timer to know when to kill self */
DECL|enumerator|DEVFL_EXT
id|DEVFL_EXT
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* device accepts lba48 commands */
DECL|enumerator|DEVFL_CLOSEWAIT
id|DEVFL_CLOSEWAIT
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* device is waiting for all closes to revalidate */
DECL|enumerator|DEVFL_WC_UPDATE
id|DEVFL_WC_UPDATE
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* this device needs to update write cache status */
DECL|enumerator|DEVFL_WORKON
id|DEVFL_WORKON
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
DECL|enumerator|BUFFL_FAIL
id|BUFFL_FAIL
op_assign
l_int|1
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|MAXATADATA
id|MAXATADATA
op_assign
l_int|1024
comma
DECL|enumerator|NPERSHELF
id|NPERSHELF
op_assign
l_int|10
comma
DECL|enumerator|FREETAG
id|FREETAG
op_assign
op_minus
l_int|1
comma
DECL|enumerator|MIN_BUFS
id|MIN_BUFS
op_assign
l_int|8
comma
)brace
suffix:semicolon
DECL|struct|buf
r_struct
id|buf
(brace
DECL|member|bufs
r_struct
id|list_head
id|bufs
suffix:semicolon
DECL|member|flags
id|ulong
id|flags
suffix:semicolon
DECL|member|nframesout
id|ulong
id|nframesout
suffix:semicolon
DECL|member|bufaddr
r_char
op_star
id|bufaddr
suffix:semicolon
DECL|member|resid
id|ulong
id|resid
suffix:semicolon
DECL|member|bv_resid
id|ulong
id|bv_resid
suffix:semicolon
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
DECL|member|bv
r_struct
id|bio_vec
op_star
id|bv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|frame
r_struct
id|frame
(brace
DECL|member|tag
r_int
id|tag
suffix:semicolon
DECL|member|waited
id|ulong
id|waited
suffix:semicolon
DECL|member|buf
r_struct
id|buf
op_star
id|buf
suffix:semicolon
DECL|member|bufaddr
r_char
op_star
id|bufaddr
suffix:semicolon
DECL|member|writedatalen
r_int
id|writedatalen
suffix:semicolon
DECL|member|ndata
r_int
id|ndata
suffix:semicolon
multiline_comment|/* largest possible */
DECL|member|data
r_int
r_char
id|data
(braket
r_sizeof
(paren
r_struct
id|aoe_hdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|aoe_atahdr
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aoedev
r_struct
id|aoedev
(brace
DECL|member|next
r_struct
id|aoedev
op_star
id|next
suffix:semicolon
DECL|member|addr
r_int
r_char
id|addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* remote mac addr */
DECL|member|flags
id|ushort
id|flags
suffix:semicolon
DECL|member|sysminor
id|ulong
id|sysminor
suffix:semicolon
DECL|member|aoemajor
id|ulong
id|aoemajor
suffix:semicolon
DECL|member|aoeminor
id|ulong
id|aoeminor
suffix:semicolon
DECL|member|nopen
id|ulong
id|nopen
suffix:semicolon
multiline_comment|/* (bd_openers isn&squot;t available without sleeping) */
DECL|member|rttavg
id|ulong
id|rttavg
suffix:semicolon
multiline_comment|/* round trip average of requests/responses */
DECL|member|fw_ver
id|u16
id|fw_ver
suffix:semicolon
multiline_comment|/* version of blade&squot;s firmware */
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
multiline_comment|/* disk create work struct */
DECL|member|gd
r_struct
id|gendisk
op_star
id|gd
suffix:semicolon
DECL|member|blkq
id|request_queue_t
id|blkq
suffix:semicolon
DECL|member|geo
r_struct
id|hd_geometry
id|geo
suffix:semicolon
DECL|member|ssize
id|sector_t
id|ssize
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ifp
r_struct
id|net_device
op_star
id|ifp
suffix:semicolon
multiline_comment|/* interface ed is attached to */
DECL|member|skblist
r_struct
id|sk_buff
op_star
id|skblist
suffix:semicolon
multiline_comment|/* packets needing to be sent */
DECL|member|bufpool
id|mempool_t
op_star
id|bufpool
suffix:semicolon
multiline_comment|/* for deadlock-free Buf allocation */
DECL|member|bufq
r_struct
id|list_head
id|bufq
suffix:semicolon
multiline_comment|/* queue of bios to work on */
DECL|member|inprocess
r_struct
id|buf
op_star
id|inprocess
suffix:semicolon
multiline_comment|/* the one we&squot;re currently working on */
DECL|member|lasttag
id|ulong
id|lasttag
suffix:semicolon
multiline_comment|/* last tag sent */
DECL|member|nframes
id|ulong
id|nframes
suffix:semicolon
multiline_comment|/* number of frames below */
DECL|member|frames
r_struct
id|frame
op_star
id|frames
suffix:semicolon
)brace
suffix:semicolon
r_int
id|aoeblk_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoeblk_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoeblk_gdalloc
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|aoedisk_rm_sysfs
c_func
(paren
r_struct
id|aoedev
op_star
id|d
)paren
suffix:semicolon
r_int
id|aoechr_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoechr_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoechr_error
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_void
id|aoecmd_work
c_func
(paren
r_struct
id|aoedev
op_star
id|d
)paren
suffix:semicolon
r_void
id|aoecmd_cfg
c_func
(paren
id|ushort
comma
r_int
r_char
)paren
suffix:semicolon
r_void
id|aoecmd_ata_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|aoecmd_cfg_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_int
id|aoedev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoedev_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|aoedev
op_star
id|aoedev_bymac
c_func
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
r_void
id|aoedev_downdev
c_func
(paren
r_struct
id|aoedev
op_star
id|d
)paren
suffix:semicolon
r_struct
id|aoedev
op_star
id|aoedev_set
c_func
(paren
id|ulong
comma
r_int
r_char
op_star
comma
r_struct
id|net_device
op_star
comma
id|ulong
)paren
suffix:semicolon
r_int
id|aoedev_busy
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|aoenet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoenet_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|aoenet_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_int
id|is_aoe_netif
c_func
(paren
r_struct
id|net_device
op_star
id|ifp
)paren
suffix:semicolon
r_int
id|set_aoe_iflist
c_func
(paren
r_const
r_char
id|__user
op_star
id|str
comma
r_int
id|size
)paren
suffix:semicolon
id|u64
id|mac_addr
c_func
(paren
r_char
id|addr
(braket
l_int|6
)braket
)paren
suffix:semicolon
eof
