multiline_comment|/* &n; *  linux/include/linux/ufs_fs_sb.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_fs_sb.h,v 1.8 1998/05/06 12:04:40 jj Exp $&n; *&n; * Write support by Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; */
macro_line|#ifndef __LINUX_UFS_FS_SB_H
DECL|macro|__LINUX_UFS_FS_SB_H
mdefine_line|#define __LINUX_UFS_FS_SB_H
macro_line|#include &lt;linux/ufs_fs.h&gt;
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
DECL|macro|UFS_MAX_GROUP_LOADED
mdefine_line|#define UFS_MAX_GROUP_LOADED 8
DECL|macro|UFS_CGNO_EMPTY
mdefine_line|#define UFS_CGNO_EMPTY ((unsigned)-1)
DECL|struct|ufs_sb_info
r_struct
id|ufs_sb_info
(brace
DECL|member|s_uspi
r_struct
id|ufs_sb_private_info
op_star
id|s_uspi
suffix:semicolon
DECL|member|s_csp
r_struct
id|ufs_csum
op_star
id|s_csp
(braket
id|UFS_MAXCSBUFS
)braket
suffix:semicolon
DECL|member|s_swab
r_int
id|s_swab
suffix:semicolon
DECL|member|s_flags
r_int
id|s_flags
suffix:semicolon
DECL|member|s_ucg
r_struct
id|buffer_head
op_star
op_star
id|s_ucg
suffix:semicolon
DECL|member|s_ucpi
r_struct
id|ufs_cg_private_info
op_star
id|s_ucpi
(braket
id|UFS_MAX_GROUP_LOADED
)braket
suffix:semicolon
DECL|member|s_cgno
r_int
id|s_cgno
(braket
id|UFS_MAX_GROUP_LOADED
)braket
suffix:semicolon
DECL|member|s_cg_loaded
r_int
r_int
id|s_cg_loaded
suffix:semicolon
DECL|member|s_mount_opt
r_int
id|s_mount_opt
suffix:semicolon
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
macro_line|#endif /* __LINUX_UFS_FS_SB_H */
eof
