multiline_comment|/*&n; *  linux/include/linux/ufs_fs.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * Clean swab support by Fare &lt;fare@tunes.org&gt;&n; * just hope no one is using NNUUXXI on __?64 structure elements&n; * 64-bit clean thanks to Maciej W. Rozycki &lt;macro@ds2.pg.gda.pl&gt;&n; *&n; * 4.4BSD (FreeBSD) support added on February 1st 1998 by&n; * Niels Kristian Bech Jensen &lt;nkbj@image.dk&gt; partially based&n; * on code by Martin von Loewis &lt;martin@mira.isdn.cs.tu-berlin.de&gt;.&n; *&n; * NeXTstep support added on February 5th 1998 by&n; * Niels Kristian Bech Jensen &lt;nkbj@image.dk&gt;.&n; *&n; * Write support by Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; *&n; * HP/UX hfs filesystem support added by&n; * Martin K. Petersen &lt;mkp@mkp.net&gt;, August 1999&n; *&n; */
macro_line|#ifndef __LINUX_UFS_FS_H
DECL|macro|__LINUX_UFS_FS_H
mdefine_line|#define __LINUX_UFS_FS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
DECL|macro|UFS_BBLOCK
mdefine_line|#define UFS_BBLOCK 0
DECL|macro|UFS_BBSIZE
mdefine_line|#define UFS_BBSIZE 8192
DECL|macro|UFS_SBLOCK
mdefine_line|#define UFS_SBLOCK 8192
DECL|macro|UFS_SBSIZE
mdefine_line|#define UFS_SBSIZE 8192
DECL|macro|UFS_SECTOR_SIZE
mdefine_line|#define UFS_SECTOR_SIZE 512
DECL|macro|UFS_SECTOR_BITS
mdefine_line|#define UFS_SECTOR_BITS 9
DECL|macro|UFS_MAGIC
mdefine_line|#define UFS_MAGIC 0x00011954
DECL|macro|UFS_CIGAM
mdefine_line|#define UFS_CIGAM 0x54190100 /* byteswapped MAGIC */
multiline_comment|/* HP specific MAGIC values */
DECL|macro|UFS_MAGIC_LFN
mdefine_line|#define UFS_MAGIC_LFN   0x00095014 /* fs supports filenames &gt; 14 chars */
DECL|macro|UFS_CIGAM_LFN
mdefine_line|#define UFS_CIGAM_LFN   0x14500900 /* srahc 41 &lt; semanelif stroppus sf */
DECL|macro|UFS_MAGIC_SEC
mdefine_line|#define UFS_MAGIC_SEC   0x00612195 /* B1 security fs */
DECL|macro|UFS_CIGAM_SEC
mdefine_line|#define UFS_CIGAM_SEC   0x95216100
DECL|macro|UFS_MAGIC_FEA
mdefine_line|#define UFS_MAGIC_FEA   0x00195612 /* fs_featurebits supported */
DECL|macro|UFS_CIGAM_FEA
mdefine_line|#define UFS_CIGAM_FEA   0x12561900
DECL|macro|UFS_MAGIC_4GB
mdefine_line|#define UFS_MAGIC_4GB   0x05231994 /* fs &gt; 4 GB &amp;&amp; fs_featurebits */
DECL|macro|UFS_CIGAM_4GB
mdefine_line|#define UFS_CIGAM_4GB   0x94192305
multiline_comment|/* Seems somebody at HP goofed here. B1 and lfs are both 0x2 !?! */
DECL|macro|UFS_FSF_LFN
mdefine_line|#define UFS_FSF_LFN     0x00000001 /* long file names */
DECL|macro|UFS_FSF_B1
mdefine_line|#define UFS_FSF_B1      0x00000002 /* B1 security */
DECL|macro|UFS_FSF_LFS
mdefine_line|#define UFS_FSF_LFS     0x00000002 /* large files */
DECL|macro|UFS_FSF_LUID
mdefine_line|#define UFS_FSF_LUID    0x00000004 /* large UIDs */
multiline_comment|/* End of HP stuff */
DECL|macro|UFS_BSIZE
mdefine_line|#define UFS_BSIZE&t;8192
DECL|macro|UFS_MINBSIZE
mdefine_line|#define UFS_MINBSIZE&t;4096
DECL|macro|UFS_FSIZE
mdefine_line|#define UFS_FSIZE&t;1024
DECL|macro|UFS_MAXFRAG
mdefine_line|#define UFS_MAXFRAG&t;(UFS_BSIZE / UFS_FSIZE)
DECL|macro|UFS_NDADDR
mdefine_line|#define UFS_NDADDR 12
DECL|macro|UFS_NINDIR
mdefine_line|#define UFS_NINDIR 3
DECL|macro|UFS_IND_BLOCK
mdefine_line|#define UFS_IND_BLOCK&t;(UFS_NDADDR + 0)
DECL|macro|UFS_DIND_BLOCK
mdefine_line|#define UFS_DIND_BLOCK&t;(UFS_NDADDR + 1)
DECL|macro|UFS_TIND_BLOCK
mdefine_line|#define UFS_TIND_BLOCK&t;(UFS_NDADDR + 2)
DECL|macro|UFS_NDIR_FRAGMENT
mdefine_line|#define UFS_NDIR_FRAGMENT (UFS_NDADDR &lt;&lt; uspi-&gt;s_fpbshift)
DECL|macro|UFS_IND_FRAGMENT
mdefine_line|#define UFS_IND_FRAGMENT (UFS_IND_BLOCK &lt;&lt; uspi-&gt;s_fpbshift)
DECL|macro|UFS_DIND_FRAGMENT
mdefine_line|#define UFS_DIND_FRAGMENT (UFS_DIND_BLOCK &lt;&lt; uspi-&gt;s_fpbshift)
DECL|macro|UFS_TIND_FRAGMENT
mdefine_line|#define UFS_TIND_FRAGMENT (UFS_TIND_BLOCK &lt;&lt; uspi-&gt;s_fpbshift)
DECL|macro|UFS_ROOTINO
mdefine_line|#define UFS_ROOTINO 2
DECL|macro|UFS_FIRST_INO
mdefine_line|#define UFS_FIRST_INO (UFS_ROOTINO + 1)
DECL|macro|UFS_USEEFT
mdefine_line|#define UFS_USEEFT  ((__u16)65535)
DECL|macro|UFS_FSOK
mdefine_line|#define UFS_FSOK      0x7c269d38
DECL|macro|UFS_FSACTIVE
mdefine_line|#define UFS_FSACTIVE  ((char)0x00)
DECL|macro|UFS_FSCLEAN
mdefine_line|#define UFS_FSCLEAN   ((char)0x01)
DECL|macro|UFS_FSSTABLE
mdefine_line|#define UFS_FSSTABLE  ((char)0x02)
DECL|macro|UFS_FSOSF1
mdefine_line|#define UFS_FSOSF1    ((char)0x03)&t;/* is this correct for DEC OSF/1? */
DECL|macro|UFS_FSBAD
mdefine_line|#define UFS_FSBAD     ((char)0xff)
multiline_comment|/* From here to next blank line, s_flags for ufs_sb_info */
multiline_comment|/* directory entry encoding */
DECL|macro|UFS_DE_MASK
mdefine_line|#define UFS_DE_MASK&t;&t;0x00000010&t;/* mask for the following */
DECL|macro|UFS_DE_OLD
mdefine_line|#define UFS_DE_OLD&t;&t;0x00000000
DECL|macro|UFS_DE_44BSD
mdefine_line|#define UFS_DE_44BSD&t;&t;0x00000010
multiline_comment|/* uid encoding */
DECL|macro|UFS_UID_MASK
mdefine_line|#define UFS_UID_MASK&t;&t;0x00000060&t;/* mask for the following */
DECL|macro|UFS_UID_OLD
mdefine_line|#define UFS_UID_OLD&t;&t;0x00000000
DECL|macro|UFS_UID_44BSD
mdefine_line|#define UFS_UID_44BSD&t;&t;0x00000020
DECL|macro|UFS_UID_EFT
mdefine_line|#define UFS_UID_EFT&t;&t;0x00000040
multiline_comment|/* superblock state encoding */
DECL|macro|UFS_ST_MASK
mdefine_line|#define UFS_ST_MASK&t;&t;0x00000700&t;/* mask for the following */
DECL|macro|UFS_ST_OLD
mdefine_line|#define UFS_ST_OLD&t;&t;0x00000000
DECL|macro|UFS_ST_44BSD
mdefine_line|#define UFS_ST_44BSD&t;&t;0x00000100
DECL|macro|UFS_ST_SUN
mdefine_line|#define UFS_ST_SUN&t;&t;0x00000200
DECL|macro|UFS_ST_SUNx86
mdefine_line|#define UFS_ST_SUNx86&t;&t;0x00000400
multiline_comment|/*cylinder group encoding */
DECL|macro|UFS_CG_MASK
mdefine_line|#define UFS_CG_MASK&t;&t;0x00003000&t;/* mask for the following */
DECL|macro|UFS_CG_OLD
mdefine_line|#define UFS_CG_OLD&t;&t;0x00000000
DECL|macro|UFS_CG_44BSD
mdefine_line|#define UFS_CG_44BSD&t;&t;0x00002000
DECL|macro|UFS_CG_SUN
mdefine_line|#define UFS_CG_SUN&t;&t;0x00001000
multiline_comment|/* fs_inodefmt options */
DECL|macro|UFS_42INODEFMT
mdefine_line|#define UFS_42INODEFMT&t;-1
DECL|macro|UFS_44INODEFMT
mdefine_line|#define UFS_44INODEFMT&t;2
multiline_comment|/* mount options */
DECL|macro|UFS_MOUNT_ONERROR
mdefine_line|#define UFS_MOUNT_ONERROR&t;&t;0x0000000F
DECL|macro|UFS_MOUNT_ONERROR_PANIC
mdefine_line|#define UFS_MOUNT_ONERROR_PANIC&t;&t;0x00000001
DECL|macro|UFS_MOUNT_ONERROR_LOCK
mdefine_line|#define UFS_MOUNT_ONERROR_LOCK&t;&t;0x00000002
DECL|macro|UFS_MOUNT_ONERROR_UMOUNT
mdefine_line|#define UFS_MOUNT_ONERROR_UMOUNT&t;0x00000004
DECL|macro|UFS_MOUNT_ONERROR_REPAIR
mdefine_line|#define UFS_MOUNT_ONERROR_REPAIR&t;0x00000008
DECL|macro|UFS_MOUNT_UFSTYPE
mdefine_line|#define UFS_MOUNT_UFSTYPE&t;&t;0x00000FF0
DECL|macro|UFS_MOUNT_UFSTYPE_OLD
mdefine_line|#define UFS_MOUNT_UFSTYPE_OLD&t;&t;0x00000010
DECL|macro|UFS_MOUNT_UFSTYPE_44BSD
mdefine_line|#define UFS_MOUNT_UFSTYPE_44BSD&t;&t;0x00000020
DECL|macro|UFS_MOUNT_UFSTYPE_SUN
mdefine_line|#define UFS_MOUNT_UFSTYPE_SUN&t;&t;0x00000040
DECL|macro|UFS_MOUNT_UFSTYPE_NEXTSTEP
mdefine_line|#define UFS_MOUNT_UFSTYPE_NEXTSTEP&t;0x00000080
DECL|macro|UFS_MOUNT_UFSTYPE_NEXTSTEP_CD
mdefine_line|#define UFS_MOUNT_UFSTYPE_NEXTSTEP_CD&t;0x00000100
DECL|macro|UFS_MOUNT_UFSTYPE_OPENSTEP
mdefine_line|#define UFS_MOUNT_UFSTYPE_OPENSTEP&t;0x00000200
DECL|macro|UFS_MOUNT_UFSTYPE_SUNx86
mdefine_line|#define UFS_MOUNT_UFSTYPE_SUNx86&t;0x00000400
DECL|macro|UFS_MOUNT_UFSTYPE_HP
mdefine_line|#define UFS_MOUNT_UFSTYPE_HP&t;        0x00000800
DECL|macro|ufs_clear_opt
mdefine_line|#define ufs_clear_opt(o,opt)&t;o &amp;= ~UFS_MOUNT_##opt
DECL|macro|ufs_set_opt
mdefine_line|#define ufs_set_opt(o,opt)&t;o |= UFS_MOUNT_##opt
DECL|macro|ufs_test_opt
mdefine_line|#define ufs_test_opt(o,opt)&t;((o) &amp; UFS_MOUNT_##opt)
multiline_comment|/*&n; * MINFREE gives the minimum acceptable percentage of file system&n; * blocks which may be free. If the freelist drops below this level&n; * only the superuser may continue to allocate blocks. This may&n; * be set to 0 if no reserve of free blocks is deemed necessary,&n; * however throughput drops by fifty percent if the file system&n; * is run at between 95% and 100% full; thus the minimum default&n; * value of fs_minfree is 5%. However, to get good clustering&n; * performance, 10% is a better choice. hence we use 10% as our&n; * default value. With 10% free space, fragmentation is not a&n; * problem, so we choose to optimize for time.&n; */
DECL|macro|UFS_MINFREE
mdefine_line|#define UFS_MINFREE         5
DECL|macro|UFS_DEFAULTOPT
mdefine_line|#define UFS_DEFAULTOPT      UFS_OPTTIME
multiline_comment|/*&n; * Turn file system block numbers into disk block addresses.&n; * This maps file system blocks to device size blocks.&n; */
DECL|macro|ufs_fsbtodb
mdefine_line|#define ufs_fsbtodb(uspi, b)&t;((b) &lt;&lt; (uspi)-&gt;s_fsbtodb)
DECL|macro|ufs_dbtofsb
mdefine_line|#define&t;ufs_dbtofsb(uspi, b)&t;((b) &gt;&gt; (uspi)-&gt;s_fsbtodb)
multiline_comment|/*&n; * Cylinder group macros to locate things in cylinder groups.&n; * They calc file system addresses of cylinder group data structures.&n; */
DECL|macro|ufs_cgbase
mdefine_line|#define&t;ufs_cgbase(c)&t;(uspi-&gt;s_fpg * (c))
DECL|macro|ufs_cgstart
mdefine_line|#define ufs_cgstart(c)&t;(ufs_cgbase(c)  + uspi-&gt;s_cgoffset * ((c) &amp; ~uspi-&gt;s_cgmask))
DECL|macro|ufs_cgsblock
mdefine_line|#define&t;ufs_cgsblock(c)&t;(ufs_cgstart(c) + uspi-&gt;s_sblkno)&t;/* super blk */
DECL|macro|ufs_cgcmin
mdefine_line|#define&t;ufs_cgcmin(c)&t;(ufs_cgstart(c) + uspi-&gt;s_cblkno)&t;/* cg block */
DECL|macro|ufs_cgimin
mdefine_line|#define&t;ufs_cgimin(c)&t;(ufs_cgstart(c) + uspi-&gt;s_iblkno)&t;/* inode blk */
DECL|macro|ufs_cgdmin
mdefine_line|#define&t;ufs_cgdmin(c)&t;(ufs_cgstart(c) + uspi-&gt;s_dblkno)&t;/* 1st data */
multiline_comment|/*&n; * Macros for handling inode numbers:&n; *     inode number to file system block offset.&n; *     inode number to cylinder group number.&n; *     inode number to file system block address.&n; */
DECL|macro|ufs_inotocg
mdefine_line|#define&t;ufs_inotocg(x)&t;&t;((x) / uspi-&gt;s_ipg)
DECL|macro|ufs_inotocgoff
mdefine_line|#define&t;ufs_inotocgoff(x)&t;((x) % uspi-&gt;s_ipg)
DECL|macro|ufs_inotofsba
mdefine_line|#define&t;ufs_inotofsba(x)&t;(ufs_cgimin(ufs_inotocg(x)) + ufs_inotocgoff(x) / uspi-&gt;s_inopf)
DECL|macro|ufs_inotofsbo
mdefine_line|#define&t;ufs_inotofsbo(x)&t;((x) % uspi-&gt;s_inopf)
multiline_comment|/*&n; * Give cylinder group number for a file system block.&n; * Give cylinder group block number for a file system block.&n; */
DECL|macro|ufs_dtog
mdefine_line|#define&t;ufs_dtog(d)&t;((d) / uspi-&gt;s_fpg)
DECL|macro|ufs_dtogd
mdefine_line|#define&t;ufs_dtogd(d)&t;((d) % uspi-&gt;s_fpg)
multiline_comment|/*&n; * Compute the cylinder and rotational position of a cyl block addr.&n; */
DECL|macro|ufs_cbtocylno
mdefine_line|#define ufs_cbtocylno(bno) &bslash;&n;&t;((bno) * uspi-&gt;s_nspf / uspi-&gt;s_spc)
DECL|macro|ufs_cbtorpos
mdefine_line|#define ufs_cbtorpos(bno) &bslash;&n;&t;((((bno) * uspi-&gt;s_nspf % uspi-&gt;s_spc / uspi-&gt;s_nsect &bslash;&n;&t;* uspi-&gt;s_trackskew + (bno) * uspi-&gt;s_nspf % uspi-&gt;s_spc &bslash;&n;&t;% uspi-&gt;s_nsect * uspi-&gt;s_interleave) % uspi-&gt;s_nsect &bslash;&n;&t;* uspi-&gt;s_nrpos) / uspi-&gt;s_npsect)
multiline_comment|/*&n; * The following macros optimize certain frequently calculated&n; * quantities by using shifts and masks in place of divisions&n; * modulos and multiplications.&n; */
DECL|macro|ufs_blkoff
mdefine_line|#define ufs_blkoff(loc)&t;&t;((loc) &amp; uspi-&gt;s_qbmask)
DECL|macro|ufs_fragoff
mdefine_line|#define ufs_fragoff(loc)&t;((loc) &amp; uspi-&gt;s_qfmask)
DECL|macro|ufs_lblktosize
mdefine_line|#define ufs_lblktosize(blk)&t;((blk) &lt;&lt; uspi-&gt;s_bshift)
DECL|macro|ufs_lblkno
mdefine_line|#define ufs_lblkno(loc)&t;&t;((loc) &gt;&gt; uspi-&gt;s_bshift)
DECL|macro|ufs_numfrags
mdefine_line|#define ufs_numfrags(loc)&t;((loc) &gt;&gt; uspi-&gt;s_fshift)
DECL|macro|ufs_blkroundup
mdefine_line|#define ufs_blkroundup(size)&t;(((size) + uspi-&gt;s_qbmask) &amp; uspi-&gt;s_bmask)
DECL|macro|ufs_fragroundup
mdefine_line|#define ufs_fragroundup(size)&t;(((size) + uspi-&gt;s_qfmask) &amp; uspi-&gt;s_fmask)
DECL|macro|ufs_fragstoblks
mdefine_line|#define ufs_fragstoblks(frags)&t;((frags) &gt;&gt; uspi-&gt;s_fpbshift)
DECL|macro|ufs_blkstofrags
mdefine_line|#define ufs_blkstofrags(blks)&t;((blks) &lt;&lt; uspi-&gt;s_fpbshift)
DECL|macro|ufs_fragnum
mdefine_line|#define ufs_fragnum(fsb)&t;((fsb) &amp; uspi-&gt;s_fpbmask)
DECL|macro|ufs_blknum
mdefine_line|#define ufs_blknum(fsb)&t;&t;((fsb) &amp; ~uspi-&gt;s_fpbmask)
DECL|macro|UFS_MAXNAMLEN
mdefine_line|#define&t;UFS_MAXNAMLEN 255
DECL|macro|UFS_MAXMNTLEN
mdefine_line|#define UFS_MAXMNTLEN 512
multiline_comment|/* #define UFS_MAXCSBUFS 31 */
DECL|macro|UFS_LINK_MAX
mdefine_line|#define UFS_LINK_MAX 32000
multiline_comment|/*&n; * UFS_DIR_PAD defines the directory entries boundaries&n; * (must be a multiple of 4)&n; */
DECL|macro|UFS_DIR_PAD
mdefine_line|#define UFS_DIR_PAD&t;&t;&t;4
DECL|macro|UFS_DIR_ROUND
mdefine_line|#define UFS_DIR_ROUND&t;&t;&t;(UFS_DIR_PAD - 1)
DECL|macro|UFS_DIR_REC_LEN
mdefine_line|#define UFS_DIR_REC_LEN(name_len)&t;(((name_len) + 1 + 8 + UFS_DIR_ROUND) &amp; ~UFS_DIR_ROUND)
DECL|struct|ufs_timeval
r_struct
id|ufs_timeval
(brace
DECL|member|tv_sec
id|__s32
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|__s32
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ufs_dir_entry
r_struct
id|ufs_dir_entry
(brace
DECL|member|d_ino
id|__u32
id|d_ino
suffix:semicolon
multiline_comment|/* inode number of this entry */
DECL|member|d_reclen
id|__u16
id|d_reclen
suffix:semicolon
multiline_comment|/* length of this entry */
r_union
(brace
DECL|member|d_namlen
id|__u16
id|d_namlen
suffix:semicolon
multiline_comment|/* actual length of d_name */
r_struct
(brace
DECL|member|d_type
id|__u8
id|d_type
suffix:semicolon
multiline_comment|/* file type */
DECL|member|d_namlen
id|__u8
id|d_namlen
suffix:semicolon
multiline_comment|/* length of string in d_name */
DECL|member|d_44
)brace
id|d_44
suffix:semicolon
DECL|member|d_u
)brace
id|d_u
suffix:semicolon
DECL|member|d_name
id|__u8
id|d_name
(braket
id|UFS_MAXNAMLEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* file name */
)brace
suffix:semicolon
DECL|struct|ufs_csum
r_struct
id|ufs_csum
(brace
DECL|member|cs_ndir
id|__u32
id|cs_ndir
suffix:semicolon
multiline_comment|/* number of directories */
DECL|member|cs_nbfree
id|__u32
id|cs_nbfree
suffix:semicolon
multiline_comment|/* number of free blocks */
DECL|member|cs_nifree
id|__u32
id|cs_nifree
suffix:semicolon
multiline_comment|/* number of free inodes */
DECL|member|cs_nffree
id|__u32
id|cs_nffree
suffix:semicolon
multiline_comment|/* number of free frags */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the actual superblock, as it is laid out on the disk.&n; */
DECL|struct|ufs_super_block
r_struct
id|ufs_super_block
(brace
DECL|member|fs_link
id|__u32
id|fs_link
suffix:semicolon
multiline_comment|/* UNUSED */
DECL|member|fs_rlink
id|__u32
id|fs_rlink
suffix:semicolon
multiline_comment|/* UNUSED */
DECL|member|fs_sblkno
id|__u32
id|fs_sblkno
suffix:semicolon
multiline_comment|/* addr of super-block in filesys */
DECL|member|fs_cblkno
id|__u32
id|fs_cblkno
suffix:semicolon
multiline_comment|/* offset of cyl-block in filesys */
DECL|member|fs_iblkno
id|__u32
id|fs_iblkno
suffix:semicolon
multiline_comment|/* offset of inode-blocks in filesys */
DECL|member|fs_dblkno
id|__u32
id|fs_dblkno
suffix:semicolon
multiline_comment|/* offset of first data after cg */
DECL|member|fs_cgoffset
id|__u32
id|fs_cgoffset
suffix:semicolon
multiline_comment|/* cylinder group offset in cylinder */
DECL|member|fs_cgmask
id|__u32
id|fs_cgmask
suffix:semicolon
multiline_comment|/* used to calc mod fs_ntrak */
DECL|member|fs_time
id|__u32
id|fs_time
suffix:semicolon
multiline_comment|/* last time written -- time_t */
DECL|member|fs_size
id|__u32
id|fs_size
suffix:semicolon
multiline_comment|/* number of blocks in fs */
DECL|member|fs_dsize
id|__u32
id|fs_dsize
suffix:semicolon
multiline_comment|/* number of data blocks in fs */
DECL|member|fs_ncg
id|__u32
id|fs_ncg
suffix:semicolon
multiline_comment|/* number of cylinder groups */
DECL|member|fs_bsize
id|__u32
id|fs_bsize
suffix:semicolon
multiline_comment|/* size of basic blocks in fs */
DECL|member|fs_fsize
id|__u32
id|fs_fsize
suffix:semicolon
multiline_comment|/* size of frag blocks in fs */
DECL|member|fs_frag
id|__u32
id|fs_frag
suffix:semicolon
multiline_comment|/* number of frags in a block in fs */
multiline_comment|/* these are configuration parameters */
DECL|member|fs_minfree
id|__u32
id|fs_minfree
suffix:semicolon
multiline_comment|/* minimum percentage of free blocks */
DECL|member|fs_rotdelay
id|__u32
id|fs_rotdelay
suffix:semicolon
multiline_comment|/* num of ms for optimal next block */
DECL|member|fs_rps
id|__u32
id|fs_rps
suffix:semicolon
multiline_comment|/* disk revolutions per second */
multiline_comment|/* these fields can be computed from the others */
DECL|member|fs_bmask
id|__u32
id|fs_bmask
suffix:semicolon
multiline_comment|/* ``blkoff&squot;&squot; calc of blk offsets */
DECL|member|fs_fmask
id|__u32
id|fs_fmask
suffix:semicolon
multiline_comment|/* ``fragoff&squot;&squot; calc of frag offsets */
DECL|member|fs_bshift
id|__u32
id|fs_bshift
suffix:semicolon
multiline_comment|/* ``lblkno&squot;&squot; calc of logical blkno */
DECL|member|fs_fshift
id|__u32
id|fs_fshift
suffix:semicolon
multiline_comment|/* ``numfrags&squot;&squot; calc number of frags */
multiline_comment|/* these are configuration parameters */
DECL|member|fs_maxcontig
id|__u32
id|fs_maxcontig
suffix:semicolon
multiline_comment|/* max number of contiguous blks */
DECL|member|fs_maxbpg
id|__u32
id|fs_maxbpg
suffix:semicolon
multiline_comment|/* max number of blks per cyl group */
multiline_comment|/* these fields can be computed from the others */
DECL|member|fs_fragshift
id|__u32
id|fs_fragshift
suffix:semicolon
multiline_comment|/* block to frag shift */
DECL|member|fs_fsbtodb
id|__u32
id|fs_fsbtodb
suffix:semicolon
multiline_comment|/* fsbtodb and dbtofsb shift constant */
DECL|member|fs_sbsize
id|__u32
id|fs_sbsize
suffix:semicolon
multiline_comment|/* actual size of super block */
DECL|member|fs_csmask
id|__u32
id|fs_csmask
suffix:semicolon
multiline_comment|/* csum block offset */
DECL|member|fs_csshift
id|__u32
id|fs_csshift
suffix:semicolon
multiline_comment|/* csum block number */
DECL|member|fs_nindir
id|__u32
id|fs_nindir
suffix:semicolon
multiline_comment|/* value of NINDIR */
DECL|member|fs_inopb
id|__u32
id|fs_inopb
suffix:semicolon
multiline_comment|/* value of INOPB */
DECL|member|fs_nspf
id|__u32
id|fs_nspf
suffix:semicolon
multiline_comment|/* value of NSPF */
multiline_comment|/* yet another configuration parameter */
DECL|member|fs_optim
id|__u32
id|fs_optim
suffix:semicolon
multiline_comment|/* optimization preference, see below */
multiline_comment|/* these fields are derived from the hardware */
r_union
(brace
r_struct
(brace
DECL|member|fs_npsect
id|__u32
id|fs_npsect
suffix:semicolon
multiline_comment|/* # sectors/track including spares */
DECL|member|fs_sun
)brace
id|fs_sun
suffix:semicolon
r_struct
(brace
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_sunx86
)brace
id|fs_sunx86
suffix:semicolon
DECL|member|fs_u1
)brace
id|fs_u1
suffix:semicolon
DECL|member|fs_interleave
id|__u32
id|fs_interleave
suffix:semicolon
multiline_comment|/* hardware sector interleave */
DECL|member|fs_trackskew
id|__u32
id|fs_trackskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per track */
multiline_comment|/* a unique id for this filesystem (currently unused and unmaintained) */
multiline_comment|/* In 4.3 Tahoe this space is used by fs_headswitch and fs_trkseek */
multiline_comment|/* Neither of those fields is used in the Tahoe code right now but */
multiline_comment|/* there could be problems if they are.                            */
DECL|member|fs_id
id|__u32
id|fs_id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* file system id */
multiline_comment|/* sizes determined by number of cylinder groups and their sizes */
DECL|member|fs_csaddr
id|__u32
id|fs_csaddr
suffix:semicolon
multiline_comment|/* blk addr of cyl grp summary area */
DECL|member|fs_cssize
id|__u32
id|fs_cssize
suffix:semicolon
multiline_comment|/* size of cyl grp summary area */
DECL|member|fs_cgsize
id|__u32
id|fs_cgsize
suffix:semicolon
multiline_comment|/* cylinder group size */
multiline_comment|/* these fields are derived from the hardware */
DECL|member|fs_ntrak
id|__u32
id|fs_ntrak
suffix:semicolon
multiline_comment|/* tracks per cylinder */
DECL|member|fs_nsect
id|__u32
id|fs_nsect
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|fs_spc
id|__u32
id|fs_spc
suffix:semicolon
multiline_comment|/* sectors per cylinder */
multiline_comment|/* this comes from the disk driver partitioning */
DECL|member|fs_ncyl
id|__u32
id|fs_ncyl
suffix:semicolon
multiline_comment|/* cylinders in file system */
multiline_comment|/* these fields can be computed from the others */
DECL|member|fs_cpg
id|__u32
id|fs_cpg
suffix:semicolon
multiline_comment|/* cylinders per group */
DECL|member|fs_ipg
id|__u32
id|fs_ipg
suffix:semicolon
multiline_comment|/* inodes per group */
DECL|member|fs_fpg
id|__u32
id|fs_fpg
suffix:semicolon
multiline_comment|/* blocks per group * fs_frag */
multiline_comment|/* this data must be re-computed after crashes */
DECL|member|fs_cstotal
r_struct
id|ufs_csum
id|fs_cstotal
suffix:semicolon
multiline_comment|/* cylinder summary information */
multiline_comment|/* these fields are cleared at mount time */
DECL|member|fs_fmod
id|__s8
id|fs_fmod
suffix:semicolon
multiline_comment|/* super block modified flag */
DECL|member|fs_clean
id|__s8
id|fs_clean
suffix:semicolon
multiline_comment|/* file system is clean flag */
DECL|member|fs_ronly
id|__s8
id|fs_ronly
suffix:semicolon
multiline_comment|/* mounted read-only flag */
DECL|member|fs_flags
id|__s8
id|fs_flags
suffix:semicolon
multiline_comment|/* currently unused flag */
DECL|member|fs_fsmnt
id|__s8
id|fs_fsmnt
(braket
id|UFS_MAXMNTLEN
)braket
suffix:semicolon
multiline_comment|/* name mounted on */
multiline_comment|/* these fields retain the current block allocation info */
DECL|member|fs_cgrotor
id|__u32
id|fs_cgrotor
suffix:semicolon
multiline_comment|/* last cg searched */
DECL|member|fs_csp
id|__u32
id|fs_csp
(braket
id|UFS_MAXCSBUFS
)braket
suffix:semicolon
multiline_comment|/* list of fs_cs info buffers */
DECL|member|fs_maxcluster
id|__u32
id|fs_maxcluster
suffix:semicolon
DECL|member|fs_cpc
id|__u32
id|fs_cpc
suffix:semicolon
multiline_comment|/* cyl per cycle in postbl */
DECL|member|fs_opostbl
id|__u16
id|fs_opostbl
(braket
l_int|16
)braket
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* old rotation block list head */
r_union
(brace
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|53
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_reclaim
id|__s32
id|fs_reclaim
suffix:semicolon
DECL|member|fs_sparecon2
id|__s32
id|fs_sparecon2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_sun
)brace
id|fs_sun
suffix:semicolon
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|53
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_reclaim
id|__s32
id|fs_reclaim
suffix:semicolon
DECL|member|fs_sparecon2
id|__s32
id|fs_sparecon2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|fs_npsect
id|__u32
id|fs_npsect
suffix:semicolon
multiline_comment|/* # sectors/track including spares */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_sunx86
)brace
id|fs_sunx86
suffix:semicolon
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_contigsumsize
id|__s32
id|fs_contigsumsize
suffix:semicolon
multiline_comment|/* size of cluster summary array */
DECL|member|fs_maxsymlinklen
id|__s32
id|fs_maxsymlinklen
suffix:semicolon
multiline_comment|/* max length of an internal symlink */
DECL|member|fs_inodefmt
id|__s32
id|fs_inodefmt
suffix:semicolon
multiline_comment|/* format of on-disk inodes */
DECL|member|fs_maxfilesize
id|__u32
id|fs_maxfilesize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* max representable file size */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_44
)brace
id|fs_44
suffix:semicolon
DECL|member|fs_u2
)brace
id|fs_u2
suffix:semicolon
DECL|member|fs_postblformat
id|__s32
id|fs_postblformat
suffix:semicolon
multiline_comment|/* format of positional layout tables */
DECL|member|fs_nrpos
id|__s32
id|fs_nrpos
suffix:semicolon
multiline_comment|/* number of rotational positions */
DECL|member|fs_postbloff
id|__s32
id|fs_postbloff
suffix:semicolon
multiline_comment|/* (__s16) rotation block list head */
DECL|member|fs_rotbloff
id|__s32
id|fs_rotbloff
suffix:semicolon
multiline_comment|/* (__u8) blocks for each rotation */
DECL|member|fs_magic
id|__s32
id|fs_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|fs_space
id|__u8
id|fs_space
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* list of blocks for each rotation */
)brace
suffix:semicolon
multiline_comment|/*&n; * Preference for optimization.&n; */
DECL|macro|UFS_OPTTIME
mdefine_line|#define UFS_OPTTIME&t;0&t;/* minimize allocation time */
DECL|macro|UFS_OPTSPACE
mdefine_line|#define UFS_OPTSPACE&t;1&t;/* minimize disk fragmentation */
multiline_comment|/*&n; * Rotational layout table format types&n; */
DECL|macro|UFS_42POSTBLFMT
mdefine_line|#define UFS_42POSTBLFMT&t;&t;-1&t;/* 4.2BSD rotational table format */
DECL|macro|UFS_DYNAMICPOSTBLFMT
mdefine_line|#define UFS_DYNAMICPOSTBLFMT&t;1&t;/* dynamic rotational table format */
multiline_comment|/*&n; * Convert cylinder group to base address of its global summary info.&n; */
DECL|macro|fs_cs
mdefine_line|#define fs_cs(indx) &bslash;&n;&t;u.ufs_sb.s_csp[(indx) &gt;&gt; uspi-&gt;s_csshift][(indx) &amp; ~uspi-&gt;s_csmask]
multiline_comment|/*&n; * Cylinder group block for a file system.&n; *&n; * Writable fields in the cylinder group are protected by the associated&n; * super block lock fs-&gt;fs_lock.&n; */
DECL|macro|CG_MAGIC
mdefine_line|#define&t;CG_MAGIC&t;0x090255
DECL|macro|ufs_cg_chkmagic
mdefine_line|#define ufs_cg_chkmagic(sb, ucg) &bslash;&n;&t;(fs32_to_cpu((sb), (ucg)-&gt;cg_magic) == CG_MAGIC)
multiline_comment|/*&n; * size of this structure is 172 B&n; */
DECL|struct|ufs_cylinder_group
r_struct
id|ufs_cylinder_group
(brace
DECL|member|cg_link
id|__u32
id|cg_link
suffix:semicolon
multiline_comment|/* linked list of cyl groups */
DECL|member|cg_magic
id|__u32
id|cg_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|cg_time
id|__u32
id|cg_time
suffix:semicolon
multiline_comment|/* time last written */
DECL|member|cg_cgx
id|__u32
id|cg_cgx
suffix:semicolon
multiline_comment|/* we are the cgx&squot;th cylinder group */
DECL|member|cg_ncyl
id|__u16
id|cg_ncyl
suffix:semicolon
multiline_comment|/* number of cyl&squot;s this cg */
DECL|member|cg_niblk
id|__u16
id|cg_niblk
suffix:semicolon
multiline_comment|/* number of inode blocks this cg */
DECL|member|cg_ndblk
id|__u32
id|cg_ndblk
suffix:semicolon
multiline_comment|/* number of data blocks this cg */
DECL|member|cg_cs
r_struct
id|ufs_csum
id|cg_cs
suffix:semicolon
multiline_comment|/* cylinder summary information */
DECL|member|cg_rotor
id|__u32
id|cg_rotor
suffix:semicolon
multiline_comment|/* position of last used block */
DECL|member|cg_frotor
id|__u32
id|cg_frotor
suffix:semicolon
multiline_comment|/* position of last used frag */
DECL|member|cg_irotor
id|__u32
id|cg_irotor
suffix:semicolon
multiline_comment|/* position of last used inode */
DECL|member|cg_frsum
id|__u32
id|cg_frsum
(braket
id|UFS_MAXFRAG
)braket
suffix:semicolon
multiline_comment|/* counts of available frags */
DECL|member|cg_btotoff
id|__u32
id|cg_btotoff
suffix:semicolon
multiline_comment|/* (__u32) block totals per cylinder */
DECL|member|cg_boff
id|__u32
id|cg_boff
suffix:semicolon
multiline_comment|/* (short) free block positions */
DECL|member|cg_iusedoff
id|__u32
id|cg_iusedoff
suffix:semicolon
multiline_comment|/* (char) used inode map */
DECL|member|cg_freeoff
id|__u32
id|cg_freeoff
suffix:semicolon
multiline_comment|/* (u_char) free block map */
DECL|member|cg_nextfreeoff
id|__u32
id|cg_nextfreeoff
suffix:semicolon
multiline_comment|/* (u_char) next available space */
r_union
(brace
r_struct
(brace
DECL|member|cg_clustersumoff
id|__u32
id|cg_clustersumoff
suffix:semicolon
multiline_comment|/* (u_int32) counts of avail clusters */
DECL|member|cg_clusteroff
id|__u32
id|cg_clusteroff
suffix:semicolon
multiline_comment|/* (u_int8) free cluster map */
DECL|member|cg_nclusterblks
id|__u32
id|cg_nclusterblks
suffix:semicolon
multiline_comment|/* number of clusters this cg */
DECL|member|cg_sparecon
id|__u32
id|cg_sparecon
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|cg_44
)brace
id|cg_44
suffix:semicolon
DECL|member|cg_sparecon
id|__u32
id|cg_sparecon
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|cg_u
)brace
id|cg_u
suffix:semicolon
DECL|member|cg_space
id|__u8
id|cg_space
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* space for cylinder group maps */
multiline_comment|/* actually longer */
)brace
suffix:semicolon
multiline_comment|/*&n; * structure of an on-disk inode&n; */
DECL|struct|ufs_inode
r_struct
id|ufs_inode
(brace
DECL|member|ui_mode
id|__u16
id|ui_mode
suffix:semicolon
multiline_comment|/*  0x0 */
DECL|member|ui_nlink
id|__u16
id|ui_nlink
suffix:semicolon
multiline_comment|/*  0x2 */
r_union
(brace
r_struct
(brace
DECL|member|ui_suid
id|__u16
id|ui_suid
suffix:semicolon
multiline_comment|/*  0x4 */
DECL|member|ui_sgid
id|__u16
id|ui_sgid
suffix:semicolon
multiline_comment|/*  0x6 */
DECL|member|oldids
)brace
id|oldids
suffix:semicolon
DECL|member|ui_inumber
id|__u32
id|ui_inumber
suffix:semicolon
multiline_comment|/*  0x4 lsf: inode number */
DECL|member|ui_author
id|__u32
id|ui_author
suffix:semicolon
multiline_comment|/*  0x4 GNU HURD: author */
DECL|member|ui_u1
)brace
id|ui_u1
suffix:semicolon
DECL|member|ui_size
id|__u64
id|ui_size
suffix:semicolon
multiline_comment|/*  0x8 */
DECL|member|ui_atime
r_struct
id|ufs_timeval
id|ui_atime
suffix:semicolon
multiline_comment|/* 0x10 access */
DECL|member|ui_mtime
r_struct
id|ufs_timeval
id|ui_mtime
suffix:semicolon
multiline_comment|/* 0x18 modification */
DECL|member|ui_ctime
r_struct
id|ufs_timeval
id|ui_ctime
suffix:semicolon
multiline_comment|/* 0x20 creation */
r_union
(brace
r_struct
(brace
DECL|member|ui_db
id|__u32
id|ui_db
(braket
id|UFS_NDADDR
)braket
suffix:semicolon
multiline_comment|/* 0x28 data blocks */
DECL|member|ui_ib
id|__u32
id|ui_ib
(braket
id|UFS_NINDIR
)braket
suffix:semicolon
multiline_comment|/* 0x58 indirect blocks */
DECL|member|ui_addr
)brace
id|ui_addr
suffix:semicolon
DECL|member|ui_symlink
id|__u8
id|ui_symlink
(braket
l_int|4
op_star
(paren
id|UFS_NDADDR
op_plus
id|UFS_NINDIR
)paren
)braket
suffix:semicolon
multiline_comment|/* 0x28 fast symlink */
DECL|member|ui_u2
)brace
id|ui_u2
suffix:semicolon
DECL|member|ui_flags
id|__u32
id|ui_flags
suffix:semicolon
multiline_comment|/* 0x64 immutable, append-only... */
DECL|member|ui_blocks
id|__u32
id|ui_blocks
suffix:semicolon
multiline_comment|/* 0x68 blocks in use */
DECL|member|ui_gen
id|__u32
id|ui_gen
suffix:semicolon
multiline_comment|/* 0x6c like ext2 i_version, for NFS support */
r_union
(brace
r_struct
(brace
DECL|member|ui_shadow
id|__u32
id|ui_shadow
suffix:semicolon
multiline_comment|/* 0x70 shadow inode with security data */
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
multiline_comment|/* 0x74 long EFT version of uid */
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
multiline_comment|/* 0x78 long EFT version of gid */
DECL|member|ui_oeftflag
id|__u32
id|ui_oeftflag
suffix:semicolon
multiline_comment|/* 0x7c reserved */
DECL|member|ui_sun
)brace
id|ui_sun
suffix:semicolon
r_struct
(brace
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
multiline_comment|/* 0x70 File owner */
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
multiline_comment|/* 0x74 File group */
DECL|member|ui_spare
id|__s32
id|ui_spare
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x78 reserved */
DECL|member|ui_44
)brace
id|ui_44
suffix:semicolon
r_struct
(brace
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
multiline_comment|/* 0x70 */
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
multiline_comment|/* 0x74 */
DECL|member|ui_modeh
id|__u16
id|ui_modeh
suffix:semicolon
multiline_comment|/* 0x78 mode high bits */
DECL|member|ui_spare
id|__u16
id|ui_spare
suffix:semicolon
multiline_comment|/* 0x7A unused */
DECL|member|ui_trans
id|__u32
id|ui_trans
suffix:semicolon
multiline_comment|/* 0x7c filesystem translator */
DECL|member|ui_hurd
)brace
id|ui_hurd
suffix:semicolon
DECL|member|ui_u3
)brace
id|ui_u3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FreeBSD has these in sys/stat.h */
multiline_comment|/* ui_flags that can be set by a file owner */
DECL|macro|UFS_UF_SETTABLE
mdefine_line|#define UFS_UF_SETTABLE   0x0000ffff
DECL|macro|UFS_UF_NODUMP
mdefine_line|#define UFS_UF_NODUMP     0x00000001  /* do not dump */
DECL|macro|UFS_UF_IMMUTABLE
mdefine_line|#define UFS_UF_IMMUTABLE  0x00000002  /* immutable (can&squot;t &quot;change&quot;) */
DECL|macro|UFS_UF_APPEND
mdefine_line|#define UFS_UF_APPEND     0x00000004  /* append-only */
DECL|macro|UFS_UF_OPAQUE
mdefine_line|#define UFS_UF_OPAQUE     0x00000008  /* directory is opaque (unionfs) */
DECL|macro|UFS_UF_NOUNLINK
mdefine_line|#define UFS_UF_NOUNLINK   0x00000010  /* can&squot;t be removed or renamed */
multiline_comment|/* ui_flags that only root can set */
DECL|macro|UFS_SF_SETTABLE
mdefine_line|#define UFS_SF_SETTABLE   0xffff0000
DECL|macro|UFS_SF_ARCHIVED
mdefine_line|#define UFS_SF_ARCHIVED   0x00010000  /* archived */
DECL|macro|UFS_SF_IMMUTABLE
mdefine_line|#define UFS_SF_IMMUTABLE  0x00020000  /* immutable (can&squot;t &quot;change&quot;) */
DECL|macro|UFS_SF_APPEND
mdefine_line|#define UFS_SF_APPEND     0x00040000  /* append-only */
DECL|macro|UFS_SF_NOUNLINK
mdefine_line|#define UFS_SF_NOUNLINK   0x00100000  /* can&squot;t be removed or renamed */
multiline_comment|/*&n; * This structure is used for reading disk structures larger&n; * than the size of fragment.&n; */
DECL|struct|ufs_buffer_head
r_struct
id|ufs_buffer_head
(brace
DECL|member|fragment
r_int
id|fragment
suffix:semicolon
multiline_comment|/* first fragment */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* number of fragments */
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
(braket
id|UFS_MAXFRAG
)braket
suffix:semicolon
multiline_comment|/* buffers */
)brace
suffix:semicolon
DECL|struct|ufs_cg_private_info
r_struct
id|ufs_cg_private_info
(brace
DECL|member|ucg
r_struct
id|ufs_cylinder_group
id|ucg
suffix:semicolon
DECL|member|c_cgx
id|__u32
id|c_cgx
suffix:semicolon
multiline_comment|/* number of cylidner group */
DECL|member|c_ncyl
id|__u16
id|c_ncyl
suffix:semicolon
multiline_comment|/* number of cyl&squot;s this cg */
DECL|member|c_niblk
id|__u16
id|c_niblk
suffix:semicolon
multiline_comment|/* number of inode blocks this cg */
DECL|member|c_ndblk
id|__u32
id|c_ndblk
suffix:semicolon
multiline_comment|/* number of data blocks this cg */
DECL|member|c_rotor
id|__u32
id|c_rotor
suffix:semicolon
multiline_comment|/* position of last used block */
DECL|member|c_frotor
id|__u32
id|c_frotor
suffix:semicolon
multiline_comment|/* position of last used frag */
DECL|member|c_irotor
id|__u32
id|c_irotor
suffix:semicolon
multiline_comment|/* position of last used inode */
DECL|member|c_btotoff
id|__u32
id|c_btotoff
suffix:semicolon
multiline_comment|/* (__u32) block totals per cylinder */
DECL|member|c_boff
id|__u32
id|c_boff
suffix:semicolon
multiline_comment|/* (short) free block positions */
DECL|member|c_iusedoff
id|__u32
id|c_iusedoff
suffix:semicolon
multiline_comment|/* (char) used inode map */
DECL|member|c_freeoff
id|__u32
id|c_freeoff
suffix:semicolon
multiline_comment|/* (u_char) free block map */
DECL|member|c_nextfreeoff
id|__u32
id|c_nextfreeoff
suffix:semicolon
multiline_comment|/* (u_char) next available space */
DECL|member|c_clustersumoff
id|__u32
id|c_clustersumoff
suffix:semicolon
multiline_comment|/* (u_int32) counts of avail clusters */
DECL|member|c_clusteroff
id|__u32
id|c_clusteroff
suffix:semicolon
multiline_comment|/* (u_int8) free cluster map */
DECL|member|c_nclusterblks
id|__u32
id|c_nclusterblks
suffix:semicolon
multiline_comment|/* number of clusters this cg */
)brace
suffix:semicolon
DECL|struct|ufs_sb_private_info
r_struct
id|ufs_sb_private_info
(brace
DECL|member|s_ubh
r_struct
id|ufs_buffer_head
id|s_ubh
suffix:semicolon
multiline_comment|/* buffer containing super block */
DECL|member|s_sblkno
id|__u32
id|s_sblkno
suffix:semicolon
multiline_comment|/* offset of super-blocks in filesys */
DECL|member|s_cblkno
id|__u32
id|s_cblkno
suffix:semicolon
multiline_comment|/* offset of cg-block in filesys */
DECL|member|s_iblkno
id|__u32
id|s_iblkno
suffix:semicolon
multiline_comment|/* offset of inode-blocks in filesys */
DECL|member|s_dblkno
id|__u32
id|s_dblkno
suffix:semicolon
multiline_comment|/* offset of first data after cg */
DECL|member|s_cgoffset
id|__u32
id|s_cgoffset
suffix:semicolon
multiline_comment|/* cylinder group offset in cylinder */
DECL|member|s_cgmask
id|__u32
id|s_cgmask
suffix:semicolon
multiline_comment|/* used to calc mod fs_ntrak */
DECL|member|s_size
id|__u32
id|s_size
suffix:semicolon
multiline_comment|/* number of blocks (fragments) in fs */
DECL|member|s_dsize
id|__u32
id|s_dsize
suffix:semicolon
multiline_comment|/* number of data blocks in fs */
DECL|member|s_ncg
id|__u32
id|s_ncg
suffix:semicolon
multiline_comment|/* number of cylinder groups */
DECL|member|s_bsize
id|__u32
id|s_bsize
suffix:semicolon
multiline_comment|/* size of basic blocks */
DECL|member|s_fsize
id|__u32
id|s_fsize
suffix:semicolon
multiline_comment|/* size of fragments */
DECL|member|s_fpb
id|__u32
id|s_fpb
suffix:semicolon
multiline_comment|/* fragments per block */
DECL|member|s_minfree
id|__u32
id|s_minfree
suffix:semicolon
multiline_comment|/* minimum percentage of free blocks */
DECL|member|s_bmask
id|__u32
id|s_bmask
suffix:semicolon
multiline_comment|/* `blkoff&squot;&squot; calc of blk offsets */
DECL|member|s_fmask
id|__u32
id|s_fmask
suffix:semicolon
multiline_comment|/* s_fsize mask */
DECL|member|s_bshift
id|__u32
id|s_bshift
suffix:semicolon
multiline_comment|/* `lblkno&squot;&squot; calc of logical blkno */
DECL|member|s_fshift
id|__u32
id|s_fshift
suffix:semicolon
multiline_comment|/* s_fsize shift */
DECL|member|s_fpbshift
id|__u32
id|s_fpbshift
suffix:semicolon
multiline_comment|/* fragments per block shift */
DECL|member|s_fsbtodb
id|__u32
id|s_fsbtodb
suffix:semicolon
multiline_comment|/* fsbtodb and dbtofsb shift constant */
DECL|member|s_sbsize
id|__u32
id|s_sbsize
suffix:semicolon
multiline_comment|/* actual size of super block */
DECL|member|s_csmask
id|__u32
id|s_csmask
suffix:semicolon
multiline_comment|/* csum block offset */
DECL|member|s_csshift
id|__u32
id|s_csshift
suffix:semicolon
multiline_comment|/* csum block number */
DECL|member|s_nindir
id|__u32
id|s_nindir
suffix:semicolon
multiline_comment|/* value of NINDIR */
DECL|member|s_inopb
id|__u32
id|s_inopb
suffix:semicolon
multiline_comment|/* value of INOPB */
DECL|member|s_nspf
id|__u32
id|s_nspf
suffix:semicolon
multiline_comment|/* value of NSPF */
DECL|member|s_npsect
id|__u32
id|s_npsect
suffix:semicolon
multiline_comment|/* # sectors/track including spares */
DECL|member|s_interleave
id|__u32
id|s_interleave
suffix:semicolon
multiline_comment|/* hardware sector interleave */
DECL|member|s_trackskew
id|__u32
id|s_trackskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per track */
DECL|member|s_csaddr
id|__u32
id|s_csaddr
suffix:semicolon
multiline_comment|/* blk addr of cyl grp summary area */
DECL|member|s_cssize
id|__u32
id|s_cssize
suffix:semicolon
multiline_comment|/* size of cyl grp summary area */
DECL|member|s_cgsize
id|__u32
id|s_cgsize
suffix:semicolon
multiline_comment|/* cylinder group size */
DECL|member|s_ntrak
id|__u32
id|s_ntrak
suffix:semicolon
multiline_comment|/* tracks per cylinder */
DECL|member|s_nsect
id|__u32
id|s_nsect
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|s_spc
id|__u32
id|s_spc
suffix:semicolon
multiline_comment|/* sectors per cylinder */
DECL|member|s_ipg
id|__u32
id|s_ipg
suffix:semicolon
multiline_comment|/* inodes per group */
DECL|member|s_fpg
id|__u32
id|s_fpg
suffix:semicolon
multiline_comment|/* fragments per group */
DECL|member|s_cpc
id|__u32
id|s_cpc
suffix:semicolon
multiline_comment|/* cyl per cycle in postbl */
DECL|member|s_contigsumsize
id|__s32
id|s_contigsumsize
suffix:semicolon
multiline_comment|/* size of cluster summary array, 44bsd */
DECL|member|s_qbmask
id|__s64
id|s_qbmask
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|s_qfmask
id|__s64
id|s_qfmask
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|s_postblformat
id|__s32
id|s_postblformat
suffix:semicolon
multiline_comment|/* format of positional layout tables */
DECL|member|s_nrpos
id|__s32
id|s_nrpos
suffix:semicolon
multiline_comment|/* number of rotational positions */
DECL|member|s_postbloff
id|__s32
id|s_postbloff
suffix:semicolon
multiline_comment|/* (__s16) rotation block list head */
DECL|member|s_rotbloff
id|__s32
id|s_rotbloff
suffix:semicolon
multiline_comment|/* (__u8) blocks for each rotation */
DECL|member|s_fpbmask
id|__u32
id|s_fpbmask
suffix:semicolon
multiline_comment|/* fragments per block mask */
DECL|member|s_apb
id|__u32
id|s_apb
suffix:semicolon
multiline_comment|/* address per block */
DECL|member|s_2apb
id|__u32
id|s_2apb
suffix:semicolon
multiline_comment|/* address per block^2 */
DECL|member|s_3apb
id|__u32
id|s_3apb
suffix:semicolon
multiline_comment|/* address per block^3 */
DECL|member|s_apbmask
id|__u32
id|s_apbmask
suffix:semicolon
multiline_comment|/* address per block mask */
DECL|member|s_apbshift
id|__u32
id|s_apbshift
suffix:semicolon
multiline_comment|/* address per block shift */
DECL|member|s_2apbshift
id|__u32
id|s_2apbshift
suffix:semicolon
multiline_comment|/* address per block shift * 2 */
DECL|member|s_3apbshift
id|__u32
id|s_3apbshift
suffix:semicolon
multiline_comment|/* address per block shift * 3 */
DECL|member|s_nspfshift
id|__u32
id|s_nspfshift
suffix:semicolon
multiline_comment|/* number of sector per fragment shift */
DECL|member|s_nspb
id|__u32
id|s_nspb
suffix:semicolon
multiline_comment|/* number of sector per block */
DECL|member|s_inopf
id|__u32
id|s_inopf
suffix:semicolon
multiline_comment|/* inodes per fragment */
DECL|member|s_sbbase
id|__u32
id|s_sbbase
suffix:semicolon
multiline_comment|/* offset of NeXTstep superblock */
DECL|member|s_bpf
id|__u32
id|s_bpf
suffix:semicolon
multiline_comment|/* bits per fragment */
DECL|member|s_bpfshift
id|__u32
id|s_bpfshift
suffix:semicolon
multiline_comment|/* bits per fragment shift*/
DECL|member|s_bpfmask
id|__u32
id|s_bpfmask
suffix:semicolon
multiline_comment|/* bits per fragment mask */
DECL|member|s_maxsymlinklen
id|__u32
id|s_maxsymlinklen
suffix:semicolon
multiline_comment|/* upper limit on fast symlinks&squot; size */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sizes of this structures are:&n; *&t;ufs_super_block_first&t;512&n; *&t;ufs_super_block_second&t;512&n; *&t;ufs_super_block_third&t;356&n; */
DECL|struct|ufs_super_block_first
r_struct
id|ufs_super_block_first
(brace
DECL|member|fs_link
id|__u32
id|fs_link
suffix:semicolon
DECL|member|fs_rlink
id|__u32
id|fs_rlink
suffix:semicolon
DECL|member|fs_sblkno
id|__u32
id|fs_sblkno
suffix:semicolon
DECL|member|fs_cblkno
id|__u32
id|fs_cblkno
suffix:semicolon
DECL|member|fs_iblkno
id|__u32
id|fs_iblkno
suffix:semicolon
DECL|member|fs_dblkno
id|__u32
id|fs_dblkno
suffix:semicolon
DECL|member|fs_cgoffset
id|__u32
id|fs_cgoffset
suffix:semicolon
DECL|member|fs_cgmask
id|__u32
id|fs_cgmask
suffix:semicolon
DECL|member|fs_time
id|__u32
id|fs_time
suffix:semicolon
DECL|member|fs_size
id|__u32
id|fs_size
suffix:semicolon
DECL|member|fs_dsize
id|__u32
id|fs_dsize
suffix:semicolon
DECL|member|fs_ncg
id|__u32
id|fs_ncg
suffix:semicolon
DECL|member|fs_bsize
id|__u32
id|fs_bsize
suffix:semicolon
DECL|member|fs_fsize
id|__u32
id|fs_fsize
suffix:semicolon
DECL|member|fs_frag
id|__u32
id|fs_frag
suffix:semicolon
DECL|member|fs_minfree
id|__u32
id|fs_minfree
suffix:semicolon
DECL|member|fs_rotdelay
id|__u32
id|fs_rotdelay
suffix:semicolon
DECL|member|fs_rps
id|__u32
id|fs_rps
suffix:semicolon
DECL|member|fs_bmask
id|__u32
id|fs_bmask
suffix:semicolon
DECL|member|fs_fmask
id|__u32
id|fs_fmask
suffix:semicolon
DECL|member|fs_bshift
id|__u32
id|fs_bshift
suffix:semicolon
DECL|member|fs_fshift
id|__u32
id|fs_fshift
suffix:semicolon
DECL|member|fs_maxcontig
id|__u32
id|fs_maxcontig
suffix:semicolon
DECL|member|fs_maxbpg
id|__u32
id|fs_maxbpg
suffix:semicolon
DECL|member|fs_fragshift
id|__u32
id|fs_fragshift
suffix:semicolon
DECL|member|fs_fsbtodb
id|__u32
id|fs_fsbtodb
suffix:semicolon
DECL|member|fs_sbsize
id|__u32
id|fs_sbsize
suffix:semicolon
DECL|member|fs_csmask
id|__u32
id|fs_csmask
suffix:semicolon
DECL|member|fs_csshift
id|__u32
id|fs_csshift
suffix:semicolon
DECL|member|fs_nindir
id|__u32
id|fs_nindir
suffix:semicolon
DECL|member|fs_inopb
id|__u32
id|fs_inopb
suffix:semicolon
DECL|member|fs_nspf
id|__u32
id|fs_nspf
suffix:semicolon
DECL|member|fs_optim
id|__u32
id|fs_optim
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|fs_npsect
id|__u32
id|fs_npsect
suffix:semicolon
DECL|member|fs_sun
)brace
id|fs_sun
suffix:semicolon
r_struct
(brace
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
DECL|member|fs_sunx86
)brace
id|fs_sunx86
suffix:semicolon
DECL|member|fs_u1
)brace
id|fs_u1
suffix:semicolon
DECL|member|fs_interleave
id|__u32
id|fs_interleave
suffix:semicolon
DECL|member|fs_trackskew
id|__u32
id|fs_trackskew
suffix:semicolon
DECL|member|fs_id
id|__u32
id|fs_id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fs_csaddr
id|__u32
id|fs_csaddr
suffix:semicolon
DECL|member|fs_cssize
id|__u32
id|fs_cssize
suffix:semicolon
DECL|member|fs_cgsize
id|__u32
id|fs_cgsize
suffix:semicolon
DECL|member|fs_ntrak
id|__u32
id|fs_ntrak
suffix:semicolon
DECL|member|fs_nsect
id|__u32
id|fs_nsect
suffix:semicolon
DECL|member|fs_spc
id|__u32
id|fs_spc
suffix:semicolon
DECL|member|fs_ncyl
id|__u32
id|fs_ncyl
suffix:semicolon
DECL|member|fs_cpg
id|__u32
id|fs_cpg
suffix:semicolon
DECL|member|fs_ipg
id|__u32
id|fs_ipg
suffix:semicolon
DECL|member|fs_fpg
id|__u32
id|fs_fpg
suffix:semicolon
DECL|member|fs_cstotal
r_struct
id|ufs_csum
id|fs_cstotal
suffix:semicolon
DECL|member|fs_fmod
id|__s8
id|fs_fmod
suffix:semicolon
DECL|member|fs_clean
id|__s8
id|fs_clean
suffix:semicolon
DECL|member|fs_ronly
id|__s8
id|fs_ronly
suffix:semicolon
DECL|member|fs_flags
id|__s8
id|fs_flags
suffix:semicolon
DECL|member|fs_fsmnt
id|__s8
id|fs_fsmnt
(braket
id|UFS_MAXMNTLEN
op_minus
l_int|212
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ufs_super_block_second
r_struct
id|ufs_super_block_second
(brace
DECL|member|fs_fsmnt
id|__s8
id|fs_fsmnt
(braket
l_int|212
)braket
suffix:semicolon
DECL|member|fs_cgrotor
id|__u32
id|fs_cgrotor
suffix:semicolon
DECL|member|fs_csp
id|__u32
id|fs_csp
(braket
id|UFS_MAXCSBUFS
)braket
suffix:semicolon
DECL|member|fs_maxcluster
id|__u32
id|fs_maxcluster
suffix:semicolon
DECL|member|fs_cpc
id|__u32
id|fs_cpc
suffix:semicolon
DECL|member|fs_opostbl
id|__u16
id|fs_opostbl
(braket
l_int|82
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ufs_super_block_third
r_struct
id|ufs_super_block_third
(brace
DECL|member|fs_opostbl
id|__u16
id|fs_opostbl
(braket
l_int|46
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|53
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_reclaim
id|__s32
id|fs_reclaim
suffix:semicolon
DECL|member|fs_sparecon2
id|__s32
id|fs_sparecon2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_sun
)brace
id|fs_sun
suffix:semicolon
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|53
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_reclaim
id|__s32
id|fs_reclaim
suffix:semicolon
DECL|member|fs_sparecon2
id|__s32
id|fs_sparecon2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|fs_npsect
id|__u32
id|fs_npsect
suffix:semicolon
multiline_comment|/* # sectors/track including spares */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_sunx86
)brace
id|fs_sunx86
suffix:semicolon
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_contigsumsize
id|__s32
id|fs_contigsumsize
suffix:semicolon
multiline_comment|/* size of cluster summary array */
DECL|member|fs_maxsymlinklen
id|__s32
id|fs_maxsymlinklen
suffix:semicolon
multiline_comment|/* max length of an internal symlink */
DECL|member|fs_inodefmt
id|__s32
id|fs_inodefmt
suffix:semicolon
multiline_comment|/* format of on-disk inodes */
DECL|member|fs_maxfilesize
id|__u32
id|fs_maxfilesize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* max representable file size */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_44
)brace
id|fs_44
suffix:semicolon
DECL|member|fs_u2
)brace
id|fs_u2
suffix:semicolon
DECL|member|fs_postblformat
id|__s32
id|fs_postblformat
suffix:semicolon
DECL|member|fs_nrpos
id|__s32
id|fs_nrpos
suffix:semicolon
DECL|member|fs_postbloff
id|__s32
id|fs_postbloff
suffix:semicolon
DECL|member|fs_rotbloff
id|__s32
id|fs_rotbloff
suffix:semicolon
DECL|member|fs_magic
id|__s32
id|fs_magic
suffix:semicolon
DECL|member|fs_space
id|__u8
id|fs_space
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* balloc.c */
r_extern
r_void
id|ufs_free_fragments
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ufs_free_blocks
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ufs_new_fragments
(paren
r_struct
id|inode
op_star
comma
id|u32
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* cylinder.c */
r_extern
r_struct
id|ufs_cg_private_info
op_star
id|ufs_load_cylinder
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ufs_put_cylinder
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|inode_operations
id|ufs_dir_inode_operations
suffix:semicolon
r_extern
r_int
id|ufs_check_dir_entry
(paren
r_const
r_char
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|ufs_dir_entry
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ufs_add_link
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
id|ino_t
id|ufs_inode_by_name
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ufs_make_empty
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ufs_dir_entry
op_star
id|ufs_find_entry
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ufs_delete_entry
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ufs_dir_entry
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ufs_empty_dir
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ufs_dir_entry
op_star
id|ufs_dotdot
(paren
r_struct
id|inode
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ufs_set_link
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ufs_dir_entry
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|ufs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_file_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|ufs_aops
suffix:semicolon
multiline_comment|/* ialloc.c */
r_extern
r_void
id|ufs_free_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|ufs_new_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_int
id|ufs_frag_map
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ufs_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ufs_put_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ufs_write_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ufs_sync_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ufs_delete_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|ufs_getfrag
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|ufs_bread
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_struct
id|file_operations
id|ufs_dir_operations
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_struct
id|file_system_type
id|ufs_fs_type
suffix:semicolon
r_extern
r_void
id|ufs_warning
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ufs_error
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ufs_panic
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ufs_write_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|ufs_fast_symlink_inode_operations
suffix:semicolon
multiline_comment|/* truncate.c */
r_extern
r_void
id|ufs_truncate
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
macro_line|#include &lt;linux/ufs_fs_i.h&gt;
DECL|function|UFS_I
r_static
r_inline
r_struct
id|ufs_inode_info
op_star
id|UFS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|ufs_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __LINUX_UFS_FS_H */
eof
