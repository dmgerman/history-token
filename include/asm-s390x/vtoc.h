macro_line|#ifndef __KERNEL__
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/dasd.h&gt;
DECL|macro|LINE_LENGTH
mdefine_line|#define LINE_LENGTH 80
DECL|macro|VTOC_START_CC
mdefine_line|#define VTOC_START_CC 0x0
DECL|macro|VTOC_START_HH
mdefine_line|#define VTOC_START_HH 0x1
DECL|enum|failure
DECL|enumerator|unable_to_open
r_enum
id|failure
(brace
id|unable_to_open
comma
DECL|enumerator|unable_to_seek
id|unable_to_seek
comma
DECL|enumerator|unable_to_write
id|unable_to_write
comma
DECL|enumerator|unable_to_read
id|unable_to_read
)brace
suffix:semicolon
DECL|struct|ttr
r_typedef
r_struct
id|ttr
(brace
DECL|member|tt
id|__u16
id|tt
suffix:semicolon
DECL|member|r
id|__u8
id|r
suffix:semicolon
DECL|typedef|ttr_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ttr_t
suffix:semicolon
DECL|struct|cchhb
r_typedef
r_struct
id|cchhb
(brace
DECL|member|cc
id|__u16
id|cc
suffix:semicolon
DECL|member|hh
id|__u16
id|hh
suffix:semicolon
DECL|member|b
id|__u8
id|b
suffix:semicolon
DECL|typedef|cchhb_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|cchhb_t
suffix:semicolon
DECL|struct|cchh
r_typedef
r_struct
id|cchh
(brace
DECL|member|cc
id|__u16
id|cc
suffix:semicolon
DECL|member|hh
id|__u16
id|hh
suffix:semicolon
DECL|typedef|cchh_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|cchh_t
suffix:semicolon
DECL|struct|labeldate
r_typedef
r_struct
id|labeldate
(brace
DECL|member|year
id|__u8
id|year
suffix:semicolon
DECL|member|day
id|__u16
id|day
suffix:semicolon
DECL|typedef|labeldate_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|labeldate_t
suffix:semicolon
DECL|struct|volume_label
r_typedef
r_struct
id|volume_label
(brace
DECL|member|volkey
r_char
id|volkey
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* volume key = volume label                 */
DECL|member|vollbl
r_char
id|vollbl
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* volume label                              */
DECL|member|volid
r_char
id|volid
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* volume identifier                         */
DECL|member|security
id|__u8
id|security
suffix:semicolon
multiline_comment|/* security byte                             */
DECL|member|vtoc
id|cchhb_t
id|vtoc
suffix:semicolon
multiline_comment|/* VTOC address                              */
DECL|member|res1
r_char
id|res1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved                                  */
DECL|member|cisize
r_char
id|cisize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* CI-size for FBA,...                       */
multiline_comment|/* ...blanks for CKD                         */
DECL|member|blkperci
r_char
id|blkperci
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* no of blocks per CI (FBA), blanks for CKD */
DECL|member|labperci
r_char
id|labperci
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* no of labels per CI (FBA), blanks for CKD */
DECL|member|res2
r_char
id|res2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved                                  */
DECL|member|lvtoc
r_char
id|lvtoc
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* owner code for LVTOC                      */
DECL|member|res3
r_char
id|res3
(braket
l_int|29
)braket
suffix:semicolon
multiline_comment|/* reserved                                  */
DECL|typedef|volume_label_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|volume_label_t
suffix:semicolon
DECL|struct|extent
r_typedef
r_struct
id|extent
(brace
DECL|member|typeind
id|__u8
id|typeind
suffix:semicolon
multiline_comment|/* extent type indicator                     */
DECL|member|seqno
id|__u8
id|seqno
suffix:semicolon
multiline_comment|/* extent sequence number                    */
DECL|member|llimit
id|cchh_t
id|llimit
suffix:semicolon
multiline_comment|/* starting point of this extent             */
DECL|member|ulimit
id|cchh_t
id|ulimit
suffix:semicolon
multiline_comment|/* ending point of this extent               */
DECL|typedef|extent_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|extent_t
suffix:semicolon
DECL|struct|dev_const
r_typedef
r_struct
id|dev_const
(brace
DECL|member|DS4DSCYL
id|__u16
id|DS4DSCYL
suffix:semicolon
multiline_comment|/* number of logical cyls                  */
DECL|member|DS4DSTRK
id|__u16
id|DS4DSTRK
suffix:semicolon
multiline_comment|/* number of tracks in a logical cylinder  */
DECL|member|DS4DEVTK
id|__u16
id|DS4DEVTK
suffix:semicolon
multiline_comment|/* device track length                     */
DECL|member|DS4DEVI
id|__u8
id|DS4DEVI
suffix:semicolon
multiline_comment|/* non-last keyed record overhead          */
DECL|member|DS4DEVL
id|__u8
id|DS4DEVL
suffix:semicolon
multiline_comment|/* last keyed record overhead              */
DECL|member|DS4DEVK
id|__u8
id|DS4DEVK
suffix:semicolon
multiline_comment|/* non-keyed record overhead differential  */
DECL|member|DS4DEVFG
id|__u8
id|DS4DEVFG
suffix:semicolon
multiline_comment|/* flag byte                               */
DECL|member|DS4DEVTL
id|__u16
id|DS4DEVTL
suffix:semicolon
multiline_comment|/* device tolerance                        */
DECL|member|DS4DEVDT
id|__u8
id|DS4DEVDT
suffix:semicolon
multiline_comment|/* number of DSCB&squot;s per track              */
DECL|member|DS4DEVDB
id|__u8
id|DS4DEVDB
suffix:semicolon
multiline_comment|/* number of directory blocks per track    */
DECL|typedef|dev_const_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|dev_const_t
suffix:semicolon
DECL|struct|format1_label
r_typedef
r_struct
id|format1_label
(brace
DECL|member|DS1DSNAM
r_char
id|DS1DSNAM
(braket
l_int|44
)braket
suffix:semicolon
multiline_comment|/* data set name                           */
DECL|member|DS1FMTID
id|__u8
id|DS1FMTID
suffix:semicolon
multiline_comment|/* format identifier                       */
DECL|member|DS1DSSN
r_char
id|DS1DSSN
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* data set serial number                  */
DECL|member|DS1VOLSQ
id|__u16
id|DS1VOLSQ
suffix:semicolon
multiline_comment|/* volume sequence number                  */
DECL|member|DS1CREDT
id|labeldate_t
id|DS1CREDT
suffix:semicolon
multiline_comment|/* creation date: ydd                      */
DECL|member|DS1EXPDT
id|labeldate_t
id|DS1EXPDT
suffix:semicolon
multiline_comment|/* expiration date                         */
DECL|member|DS1NOEPV
id|__u8
id|DS1NOEPV
suffix:semicolon
multiline_comment|/* number of extents on volume             */
DECL|member|DS1NOBDB
id|__u8
id|DS1NOBDB
suffix:semicolon
multiline_comment|/* no. of bytes used in last direction blk */
DECL|member|DS1FLAG1
id|__u8
id|DS1FLAG1
suffix:semicolon
multiline_comment|/* flag 1                                  */
DECL|member|DS1SYSCD
r_char
id|DS1SYSCD
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* system code                             */
DECL|member|DS1REFD
id|labeldate_t
id|DS1REFD
suffix:semicolon
multiline_comment|/* date last referenced                    */
DECL|member|DS1SMSFG
id|__u8
id|DS1SMSFG
suffix:semicolon
multiline_comment|/* system managed storage indicators       */
DECL|member|DS1SCXTF
id|__u8
id|DS1SCXTF
suffix:semicolon
multiline_comment|/* sec. space extension flag byte          */
DECL|member|DS1SCXTV
id|__u16
id|DS1SCXTV
suffix:semicolon
multiline_comment|/* secondary space extension value         */
DECL|member|DS1DSRG1
id|__u8
id|DS1DSRG1
suffix:semicolon
multiline_comment|/* data set organisation byte 1            */
DECL|member|DS1DSRG2
id|__u8
id|DS1DSRG2
suffix:semicolon
multiline_comment|/* data set organisation byte 2            */
DECL|member|DS1RECFM
id|__u8
id|DS1RECFM
suffix:semicolon
multiline_comment|/* record format                           */
DECL|member|DS1OPTCD
id|__u8
id|DS1OPTCD
suffix:semicolon
multiline_comment|/* option code                             */
DECL|member|DS1BLKL
id|__u16
id|DS1BLKL
suffix:semicolon
multiline_comment|/* block length                            */
DECL|member|DS1LRECL
id|__u16
id|DS1LRECL
suffix:semicolon
multiline_comment|/* record length                           */
DECL|member|DS1KEYL
id|__u8
id|DS1KEYL
suffix:semicolon
multiline_comment|/* key length                              */
DECL|member|DS1RKP
id|__u16
id|DS1RKP
suffix:semicolon
multiline_comment|/* relative key position                   */
DECL|member|DS1DSIND
id|__u8
id|DS1DSIND
suffix:semicolon
multiline_comment|/* data set indicators                     */
DECL|member|DS1SCAL1
id|__u8
id|DS1SCAL1
suffix:semicolon
multiline_comment|/* secondary allocation flag byte          */
DECL|member|DS1SCAL3
r_char
id|DS1SCAL3
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* secondary allocation quantity           */
DECL|member|DS1LSTAR
id|ttr_t
id|DS1LSTAR
suffix:semicolon
multiline_comment|/* last used track and block on track      */
DECL|member|DS1TRBAL
id|__u16
id|DS1TRBAL
suffix:semicolon
multiline_comment|/* space remaining on last used track      */
DECL|member|res1
id|__u16
id|res1
suffix:semicolon
multiline_comment|/* reserved                                */
DECL|member|DS1EXT1
id|extent_t
id|DS1EXT1
suffix:semicolon
multiline_comment|/* first extent description                */
DECL|member|DS1EXT2
id|extent_t
id|DS1EXT2
suffix:semicolon
multiline_comment|/* second extent description               */
DECL|member|DS1EXT3
id|extent_t
id|DS1EXT3
suffix:semicolon
multiline_comment|/* third extent description                */
DECL|member|DS1PTRDS
id|cchhb_t
id|DS1PTRDS
suffix:semicolon
multiline_comment|/* possible pointer to f2 or f3 DSCB       */
DECL|typedef|format1_label_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|format1_label_t
suffix:semicolon
DECL|struct|format4_label
r_typedef
r_struct
id|format4_label
(brace
DECL|member|DS4KEYCD
r_char
id|DS4KEYCD
(braket
l_int|44
)braket
suffix:semicolon
multiline_comment|/* key code for VTOC labels: 44 times 0x04 */
DECL|member|DS4IDFMT
id|__u8
id|DS4IDFMT
suffix:semicolon
multiline_comment|/* format identifier                       */
DECL|member|DS4HPCHR
id|cchhb_t
id|DS4HPCHR
suffix:semicolon
multiline_comment|/* highest address of a format 1 DSCB      */
DECL|member|DS4DSREC
id|__u16
id|DS4DSREC
suffix:semicolon
multiline_comment|/* number of available DSCB&squot;s              */
DECL|member|DS4HCCHH
id|cchh_t
id|DS4HCCHH
suffix:semicolon
multiline_comment|/* CCHH of next available alternate track  */
DECL|member|DS4NOATK
id|__u16
id|DS4NOATK
suffix:semicolon
multiline_comment|/* number of remaining alternate tracks    */
DECL|member|DS4VTOCI
id|__u8
id|DS4VTOCI
suffix:semicolon
multiline_comment|/* VTOC indicators                         */
DECL|member|DS4NOEXT
id|__u8
id|DS4NOEXT
suffix:semicolon
multiline_comment|/* number of extents in VTOC               */
DECL|member|DS4SMSFG
id|__u8
id|DS4SMSFG
suffix:semicolon
multiline_comment|/* system managed storage indicators       */
DECL|member|DS4DEVAC
id|__u8
id|DS4DEVAC
suffix:semicolon
multiline_comment|/* number of alternate cylinders. &n;                                     Subtract from first two bytes of &n;                                     DS4DEVSZ to get number of usable&n;&t;&t;&t;&t;     cylinders. can be zero. valid&n;&t;&t;&t;&t;     only if DS4DEVAV on.                    */
DECL|member|DS4DEVCT
id|dev_const_t
id|DS4DEVCT
suffix:semicolon
multiline_comment|/* device constants                        */
DECL|member|DS4AMTIM
r_char
id|DS4AMTIM
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* VSAM time stamp                         */
DECL|member|DS4AMCAT
r_char
id|DS4AMCAT
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* VSAM catalog indicator                  */
DECL|member|DS4R2TIM
r_char
id|DS4R2TIM
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* VSAM volume/catalog match time stamp    */
DECL|member|res1
r_char
id|res1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved                                */
DECL|member|DS4F6PTR
r_char
id|DS4F6PTR
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* pointer to first format 6 DSCB          */
DECL|member|DS4VTOCE
id|extent_t
id|DS4VTOCE
suffix:semicolon
multiline_comment|/* VTOC extent description                 */
DECL|member|res2
r_char
id|res2
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* reserved                                */
DECL|member|DS4EFLVL
id|__u8
id|DS4EFLVL
suffix:semicolon
multiline_comment|/* extended free-space management level    */
DECL|member|DS4EFPTR
id|cchhb_t
id|DS4EFPTR
suffix:semicolon
multiline_comment|/* pointer to extended free-space info     */
DECL|member|res3
r_char
id|res3
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* reserved                                */
DECL|typedef|format4_label_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|format4_label_t
suffix:semicolon
r_char
op_star
id|vtoc_ebcdic_enc
(paren
r_int
r_char
id|source
(braket
id|LINE_LENGTH
)braket
comma
r_int
r_char
id|target
(braket
id|LINE_LENGTH
)braket
comma
r_int
id|l
)paren
suffix:semicolon
r_char
op_star
id|vtoc_ebcdic_dec
(paren
r_int
r_char
id|source
(braket
id|LINE_LENGTH
)braket
comma
r_int
r_char
id|target
(braket
id|LINE_LENGTH
)braket
comma
r_int
id|l
)paren
suffix:semicolon
r_void
id|vtoc_set_extent
(paren
id|extent_t
op_star
id|ext
comma
id|__u8
id|typeind
comma
id|__u8
id|seqno
comma
id|cchh_t
op_star
id|lower
comma
id|cchh_t
op_star
id|upper
)paren
suffix:semicolon
r_void
id|vtoc_set_cchh
(paren
id|cchh_t
op_star
id|addr
comma
id|__u16
id|cc
comma
id|__u16
id|hh
)paren
suffix:semicolon
r_void
id|vtoc_set_cchhb
(paren
id|cchhb_t
op_star
id|addr
comma
id|__u16
id|cc
comma
id|__u16
id|hh
comma
id|__u8
id|b
)paren
suffix:semicolon
r_void
id|vtoc_set_date
(paren
id|labeldate_t
op_star
id|d
comma
id|__u8
id|year
comma
id|__u16
id|day
)paren
suffix:semicolon
r_int
id|vtoc_read_volume_label
(paren
r_char
op_star
id|device
comma
r_int
r_int
id|vlabel_start
comma
id|volume_label_t
op_star
id|vlabel
)paren
suffix:semicolon
r_int
id|vtoc_write_volume_label
(paren
r_char
op_star
id|device
comma
r_int
r_int
id|vlabel_start
comma
id|volume_label_t
op_star
id|vlabel
)paren
suffix:semicolon
r_void
id|vtoc_read_label
(paren
r_char
op_star
id|device
comma
r_int
r_int
id|position
comma
id|format4_label_t
op_star
id|f4
comma
id|format1_label_t
op_star
id|f1
)paren
suffix:semicolon
r_void
id|vtoc_write_label
(paren
r_char
op_star
id|device
comma
r_int
r_int
id|position
comma
id|format4_label_t
op_star
id|f4
comma
id|format1_label_t
op_star
id|f1
)paren
suffix:semicolon
r_void
id|vtoc_init_format4_label
(paren
r_struct
id|hd_geometry
op_star
id|geo
comma
id|format4_label_t
op_star
id|f4lbl
comma
r_int
r_int
id|usable_partitions
comma
r_int
r_int
id|cylinders
comma
r_int
r_int
id|tracks
comma
r_int
r_int
id|blocks
)paren
suffix:semicolon
r_void
id|vtoc_init_format1_label
(paren
r_char
op_star
id|volid
comma
r_int
r_int
id|blksize
comma
id|extent_t
op_star
id|part_extent
comma
id|format1_label_t
op_star
id|f1
)paren
suffix:semicolon
r_void
id|vtoc_update_format4_label
(paren
id|format4_label_t
op_star
id|f4
comma
id|cchhb_t
op_star
id|highest_f1
comma
id|__u8
id|unused_update
comma
id|__u16
id|freespace_update
)paren
suffix:semicolon
eof
