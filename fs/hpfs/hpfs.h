multiline_comment|/*&n; *  linux/fs/hpfs/hpfs.h&n; *&n; *  HPFS structures by Chris Smith, 1993&n; *&n; *  a little bit modified by Mikulas Patocka, 1998-1999&n; */
multiline_comment|/* The paper&n;&n;     Duncan, Roy&n;     Design goals and implementation of the new High Performance File System&n;     Microsoft Systems Journal  Sept 1989  v4 n5 p1(13)&n;&n;   describes what HPFS looked like when it was new, and it is the source&n;   of most of the information given here.  The rest is conjecture.&n;&n;   For definitive information on the Duncan paper, see it, not this file.&n;   For definitive information on HPFS, ask somebody else -- this is guesswork.&n;   There are certain to be many mistakes. */
multiline_comment|/* Notation */
DECL|typedef|secno
r_typedef
r_int
id|secno
suffix:semicolon
multiline_comment|/* sector number, partition relative */
DECL|typedef|dnode_secno
r_typedef
id|secno
id|dnode_secno
suffix:semicolon
multiline_comment|/* sector number of a dnode */
DECL|typedef|fnode_secno
r_typedef
id|secno
id|fnode_secno
suffix:semicolon
multiline_comment|/* sector number of an fnode */
DECL|typedef|anode_secno
r_typedef
id|secno
id|anode_secno
suffix:semicolon
multiline_comment|/* sector number of an anode */
multiline_comment|/* sector 0 */
multiline_comment|/* The boot block is very like a FAT boot block, except that the&n;   29h signature byte is 28h instead, and the ID string is &quot;HPFS&quot;. */
DECL|macro|BB_MAGIC
mdefine_line|#define BB_MAGIC 0xaa55
DECL|struct|hpfs_boot_block
r_struct
id|hpfs_boot_block
(brace
DECL|member|jmp
r_int
r_char
id|jmp
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|oem_id
r_int
r_char
id|oem_id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bytes_per_sector
r_int
r_char
id|bytes_per_sector
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 512 */
DECL|member|sectors_per_cluster
r_int
r_char
id|sectors_per_cluster
suffix:semicolon
DECL|member|n_reserved_sectors
r_int
r_char
id|n_reserved_sectors
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|n_fats
r_int
r_char
id|n_fats
suffix:semicolon
DECL|member|n_rootdir_entries
r_int
r_char
id|n_rootdir_entries
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|n_sectors_s
r_int
r_char
id|n_sectors_s
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|media_byte
r_int
r_char
id|media_byte
suffix:semicolon
DECL|member|sectors_per_fat
r_int
r_int
id|sectors_per_fat
suffix:semicolon
DECL|member|sectors_per_track
r_int
r_int
id|sectors_per_track
suffix:semicolon
DECL|member|heads_per_cyl
r_int
r_int
id|heads_per_cyl
suffix:semicolon
DECL|member|n_hidden_sectors
r_int
r_int
id|n_hidden_sectors
suffix:semicolon
DECL|member|n_sectors_l
r_int
r_int
id|n_sectors_l
suffix:semicolon
multiline_comment|/* size of partition */
DECL|member|drive_number
r_int
r_char
id|drive_number
suffix:semicolon
DECL|member|mbz
r_int
r_char
id|mbz
suffix:semicolon
DECL|member|sig_28h
r_int
r_char
id|sig_28h
suffix:semicolon
multiline_comment|/* 28h */
DECL|member|vol_serno
r_int
r_char
id|vol_serno
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|vol_label
r_int
r_char
id|vol_label
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|sig_hpfs
r_int
r_char
id|sig_hpfs
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* &quot;HPFS    &quot; */
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|448
)braket
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* aa55 */
)brace
suffix:semicolon
multiline_comment|/* sector 16 */
multiline_comment|/* The super block has the pointer to the root directory. */
DECL|macro|SB_MAGIC
mdefine_line|#define SB_MAGIC 0xf995e849
DECL|struct|hpfs_super_block
r_struct
id|hpfs_super_block
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* f995 e849 */
DECL|member|magic1
r_int
id|magic1
suffix:semicolon
multiline_comment|/* fa53 e9c5, more magic? */
multiline_comment|/*unsigned huh202;*/
multiline_comment|/* ?? 202 = N. of B. in 1.00390625 S.*/
DECL|member|version
r_char
id|version
suffix:semicolon
multiline_comment|/* version of a filesystem  usually 2 */
DECL|member|funcversion
r_char
id|funcversion
suffix:semicolon
multiline_comment|/* functional version - oldest version&n;  &t;&t;&t;&t;&t;   of filesystem that can understand&n;&t;&t;&t;&t;&t;   this disk */
DECL|member|zero
r_int
r_int
r_int
id|zero
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|root
id|fnode_secno
id|root
suffix:semicolon
multiline_comment|/* fnode of root directory */
DECL|member|n_sectors
id|secno
id|n_sectors
suffix:semicolon
multiline_comment|/* size of filesystem */
DECL|member|n_badblocks
r_int
id|n_badblocks
suffix:semicolon
multiline_comment|/* number of bad blocks */
DECL|member|bitmaps
id|secno
id|bitmaps
suffix:semicolon
multiline_comment|/* pointers to free space bit maps */
DECL|member|zero1
r_int
id|zero1
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|badblocks
id|secno
id|badblocks
suffix:semicolon
multiline_comment|/* bad block list */
DECL|member|zero3
r_int
id|zero3
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|last_chkdsk
id|time_t
id|last_chkdsk
suffix:semicolon
multiline_comment|/* date last checked, 0 if never */
multiline_comment|/*unsigned zero4;*/
multiline_comment|/* 0 */
DECL|member|last_optimize
id|time_t
id|last_optimize
suffix:semicolon
multiline_comment|/* date last optimized, 0 if never */
DECL|member|n_dir_band
id|secno
id|n_dir_band
suffix:semicolon
multiline_comment|/* number of sectors in dir band */
DECL|member|dir_band_start
id|secno
id|dir_band_start
suffix:semicolon
multiline_comment|/* first sector in dir band */
DECL|member|dir_band_end
id|secno
id|dir_band_end
suffix:semicolon
multiline_comment|/* last sector in dir band */
DECL|member|dir_band_bitmap
id|secno
id|dir_band_bitmap
suffix:semicolon
multiline_comment|/* free space map, 1 dnode per bit */
DECL|member|volume_name
r_char
id|volume_name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* not used */
DECL|member|user_id_table
id|secno
id|user_id_table
suffix:semicolon
multiline_comment|/* 8 preallocated sectors - user id */
DECL|member|zero6
r_int
id|zero6
(braket
l_int|103
)braket
suffix:semicolon
multiline_comment|/* 0 */
)brace
suffix:semicolon
multiline_comment|/* sector 17 */
multiline_comment|/* The spare block has pointers to spare sectors.  */
DECL|macro|SP_MAGIC
mdefine_line|#define SP_MAGIC 0xf9911849
DECL|struct|hpfs_spare_block
r_struct
id|hpfs_spare_block
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* f991 1849 */
DECL|member|magic1
r_int
id|magic1
suffix:semicolon
multiline_comment|/* fa52 29c5, more magic? */
DECL|member|dirty
r_int
id|dirty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 clean, 1 &quot;improperly stopped&quot; */
multiline_comment|/*unsigned flag1234: 4;*/
multiline_comment|/* unknown flags */
DECL|member|sparedir_used
r_int
id|sparedir_used
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* spare dirblks used */
DECL|member|hotfixes_used
r_int
id|hotfixes_used
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* hotfixes used */
DECL|member|bad_sector
r_int
id|bad_sector
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* bad sector, corrupted disk (???) */
DECL|member|bad_bitmap
r_int
id|bad_bitmap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* bad bitmap */
DECL|member|fast
r_int
id|fast
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* partition was fast formatted */
DECL|member|old_wrote
r_int
id|old_wrote
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* old version wrote to partion */
DECL|member|old_wrote_1
r_int
id|old_wrote_1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* old version wrote to partion (?) */
DECL|member|install_dasd_limits
r_int
id|install_dasd_limits
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* HPFS386 flags */
DECL|member|resynch_dasd_limits
r_int
id|resynch_dasd_limits
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dasd_limits_operational
r_int
id|dasd_limits_operational
suffix:colon
l_int|1
suffix:semicolon
DECL|member|multimedia_active
r_int
id|multimedia_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dce_acls_active
r_int
id|dce_acls_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dasd_limits_dirty
r_int
id|dasd_limits_dirty
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag67
r_int
id|flag67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|mm_contlgulty
r_int
r_char
id|mm_contlgulty
suffix:semicolon
DECL|member|unused
r_int
r_char
id|unused
suffix:semicolon
DECL|member|hotfix_map
id|secno
id|hotfix_map
suffix:semicolon
multiline_comment|/* info about remapped bad sectors */
DECL|member|n_spares_used
r_int
id|n_spares_used
suffix:semicolon
multiline_comment|/* number of hotfixes */
DECL|member|n_spares
r_int
id|n_spares
suffix:semicolon
multiline_comment|/* number of spares in hotfix map */
DECL|member|n_dnode_spares_free
r_int
id|n_dnode_spares_free
suffix:semicolon
multiline_comment|/* spare dnodes unused */
DECL|member|n_dnode_spares
r_int
id|n_dnode_spares
suffix:semicolon
multiline_comment|/* length of spare_dnodes[] list,&n;&t;&t;&t;&t;&t;   follows in this block*/
DECL|member|code_page_dir
id|secno
id|code_page_dir
suffix:semicolon
multiline_comment|/* code page directory block */
DECL|member|n_code_pages
r_int
id|n_code_pages
suffix:semicolon
multiline_comment|/* number of code pages */
multiline_comment|/*unsigned large_numbers[2];*/
multiline_comment|/* ?? */
DECL|member|super_crc
r_int
id|super_crc
suffix:semicolon
multiline_comment|/* on HPFS386 and LAN Server this is&n;  &t;&t;&t;&t;&t;   checksum of superblock, on normal&n;&t;&t;&t;&t;&t;   OS/2 unused */
DECL|member|spare_crc
r_int
id|spare_crc
suffix:semicolon
multiline_comment|/* on HPFS386 checksum of spareblock */
DECL|member|zero1
r_int
id|zero1
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|spare_dnodes
id|dnode_secno
id|spare_dnodes
(braket
l_int|100
)braket
suffix:semicolon
multiline_comment|/* emergency free dnode list */
DECL|member|zero2
r_int
id|zero2
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* room for more? */
)brace
suffix:semicolon
multiline_comment|/* The bad block list is 4 sectors long.  The first word must be zero,&n;   the remaining words give n_badblocks bad block numbers.&n;   I bet you can see it coming... */
DECL|macro|BAD_MAGIC
mdefine_line|#define BAD_MAGIC 0
multiline_comment|/* The hotfix map is 4 sectors long.  It looks like&n;&n;       secno from[n_spares];&n;       secno to[n_spares];&n;&n;   The to[] list is initialized to point to n_spares preallocated empty&n;   sectors.  The from[] list contains the sector numbers of bad blocks&n;   which have been remapped to corresponding sectors in the to[] list.&n;   n_spares_used gives the length of the from[] list. */
multiline_comment|/* Sectors 18 and 19 are preallocated and unused.&n;   Maybe they&squot;re spares for 16 and 17, but simple substitution fails. */
multiline_comment|/* The code page info pointed to by the spare block consists of an index&n;   block and blocks containing uppercasing tables.  I don&squot;t know what&n;   these are for (CHKDSK, maybe?) -- OS/2 does not seem to use them&n;   itself.  Linux doesn&squot;t use them either. */
multiline_comment|/* block pointed to by spareblock-&gt;code_page_dir */
DECL|macro|CP_DIR_MAGIC
mdefine_line|#define CP_DIR_MAGIC 0x494521f7
DECL|struct|code_page_directory
r_struct
id|code_page_directory
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* 4945 21f7 */
DECL|member|n_code_pages
r_int
id|n_code_pages
suffix:semicolon
multiline_comment|/* number of pointers following */
DECL|member|zero1
r_int
id|zero1
(braket
l_int|2
)braket
suffix:semicolon
r_struct
(brace
DECL|member|ix
r_int
r_int
id|ix
suffix:semicolon
multiline_comment|/* index */
DECL|member|code_page_number
r_int
r_int
id|code_page_number
suffix:semicolon
multiline_comment|/* code page number */
DECL|member|bounds
r_int
id|bounds
suffix:semicolon
multiline_comment|/* matches corresponding word&n;&t;&t;&t;&t;&t;   in data block */
DECL|member|code_page_data
id|secno
id|code_page_data
suffix:semicolon
multiline_comment|/* sector number of a code_page_data&n;&t;&t;&t;&t;&t;   containing c.p. array */
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
multiline_comment|/* index in c.p. array in that sector*/
DECL|member|unknown
r_int
r_int
id|unknown
suffix:semicolon
multiline_comment|/* some unknown value; usually 0;&n;    &t;&t;&t;&t;&t;   2 in Japanese version */
DECL|member|array
)brace
id|array
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* unknown length */
)brace
suffix:semicolon
multiline_comment|/* blocks pointed to by code_page_directory */
DECL|macro|CP_DATA_MAGIC
mdefine_line|#define CP_DATA_MAGIC 0x894521f7
DECL|struct|code_page_data
r_struct
id|code_page_data
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* 8945 21f7 */
DECL|member|n_used
r_int
id|n_used
suffix:semicolon
multiline_comment|/* # elements used in c_p_data[] */
DECL|member|bounds
r_int
id|bounds
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* looks a bit like&n;&t;&t;&t;&t;&t;     (beg1,end1), (beg2,end2)&n;&t;&t;&t;&t;&t;   one byte each */
DECL|member|offs
r_int
r_int
id|offs
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* offsets from start of sector&n;&t;&t;&t;&t;&t;   to start of c_p_data[ix] */
r_struct
(brace
DECL|member|ix
r_int
r_int
id|ix
suffix:semicolon
multiline_comment|/* index */
DECL|member|code_page_number
r_int
r_int
id|code_page_number
suffix:semicolon
multiline_comment|/* code page number */
DECL|member|unknown
r_int
r_int
id|unknown
suffix:semicolon
multiline_comment|/* the same as in cp directory */
DECL|member|map
r_int
r_char
id|map
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* upcase table for chars 80..ff */
DECL|member|zero2
r_int
r_int
id|zero2
suffix:semicolon
DECL|member|code_page
)brace
id|code_page
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|incognita
r_int
r_char
id|incognita
(braket
l_int|78
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Free space bitmaps are 4 sectors long, which is 16384 bits.&n;   16384 sectors is 8 meg, and each 8 meg band has a 4-sector bitmap.&n;   Bit order in the maps is little-endian.  0 means taken, 1 means free.&n;&n;   Bit map sectors are marked allocated in the bit maps, and so are sectors &n;   off the end of the partition.&n;&n;   Band 0 is sectors 0-3fff, its map is in sectors 18-1b.&n;   Band 1 is 4000-7fff, its map is in 7ffc-7fff.&n;   Band 2 is 8000-ffff, its map is in 8000-8003.&n;   The remaining bands have maps in their first (even) or last (odd) 4 sectors&n;     -- if the last, partial, band is odd its map is in its last 4 sectors.&n;&n;   The bitmap locations are given in a table pointed to by the super block.&n;   No doubt they aren&squot;t constrained to be at 18, 7ffc, 8000, ...; that is&n;   just where they usually are.&n;&n;   The &quot;directory band&quot; is a bunch of sectors preallocated for dnodes.&n;   It has a 4-sector free space bitmap of its own.  Each bit in the map&n;   corresponds to one 4-sector dnode, bit 0 of the map corresponding to&n;   the first 4 sectors of the directory band.  The entire band is marked&n;   allocated in the main bitmap.   The super block gives the locations&n;   of the directory band and its bitmap.  (&quot;band&quot; doesn&squot;t mean it is&n;   8 meg long; it isn&squot;t.)  */
multiline_comment|/* dnode: directory.  4 sectors long */
multiline_comment|/* A directory is a tree of dnodes.  The fnode for a directory&n;   contains one pointer, to the root dnode of the tree.  The fnode&n;   never moves, the dnodes do the B-tree thing, splitting and merging&n;   as files are added and removed.  */
DECL|macro|DNODE_MAGIC
mdefine_line|#define DNODE_MAGIC   0x77e40aae
DECL|struct|dnode
r_struct
id|dnode
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* 77e4 0aae */
DECL|member|first_free
r_int
id|first_free
suffix:semicolon
multiline_comment|/* offset from start of dnode to&n;&t;&t;&t;&t;&t;   first free dir entry */
DECL|member|root_dnode
r_int
id|root_dnode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Is it root dnode? */
DECL|member|increment_me
r_int
id|increment_me
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* some kind of activity counter?&n;&t;&t;&t;&t;&t;   Neither HPFS.IFS nor CHKDSK cares&n;&t;&t;&t;&t;&t;   if you change this word */
DECL|member|up
id|secno
id|up
suffix:semicolon
multiline_comment|/* (root dnode) directory&squot;s fnode&n;&t;&t;&t;&t;&t;   (nonroot) parent dnode */
DECL|member|self
id|dnode_secno
id|self
suffix:semicolon
multiline_comment|/* pointer to this dnode */
DECL|member|dirent
r_int
r_char
id|dirent
(braket
l_int|2028
)braket
suffix:semicolon
multiline_comment|/* one or more dirents */
)brace
suffix:semicolon
DECL|struct|hpfs_dirent
r_struct
id|hpfs_dirent
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* offset to next dirent */
DECL|member|first
r_int
id|first
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set on phony ^A^A (&quot;.&quot;) entry */
DECL|member|has_acl
r_int
id|has_acl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|down
r_int
id|down
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* down pointer present (after name) */
DECL|member|last
r_int
id|last
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set on phony &bslash;377 entry */
DECL|member|has_ea
r_int
id|has_ea
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* entry has EA */
DECL|member|has_xtd_perm
r_int
id|has_xtd_perm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* has extended perm list (???) */
DECL|member|has_explicit_acl
r_int
id|has_explicit_acl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_needea
r_int
id|has_needea
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ?? some EA has NEEDEA set&n;&t;&t;&t;&t;&t;   I have no idea why this is&n;&t;&t;&t;&t;&t;   interesting in a dir entry */
DECL|member|read_only
r_int
id|read_only
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dos attrib */
DECL|member|hidden
r_int
id|hidden
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dos attrib */
DECL|member|system
r_int
id|system
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dos attrib */
DECL|member|flag11
r_int
id|flag11
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* would be volume label dos attrib */
DECL|member|directory
r_int
id|directory
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dos attrib */
DECL|member|archive
r_int
id|archive
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dos attrib */
DECL|member|not_8x3
r_int
id|not_8x3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* name is not 8.3 */
DECL|member|flag15
r_int
id|flag15
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fnode
id|fnode_secno
id|fnode
suffix:semicolon
multiline_comment|/* fnode giving allocation info */
DECL|member|write_date
id|time_t
id|write_date
suffix:semicolon
multiline_comment|/* mtime */
DECL|member|file_size
r_int
id|file_size
suffix:semicolon
multiline_comment|/* file length, bytes */
DECL|member|read_date
id|time_t
id|read_date
suffix:semicolon
multiline_comment|/* atime */
DECL|member|creation_date
id|time_t
id|creation_date
suffix:semicolon
multiline_comment|/* ctime */
DECL|member|ea_size
r_int
id|ea_size
suffix:semicolon
multiline_comment|/* total EA length, bytes */
DECL|member|no_of_acls
r_int
r_char
id|no_of_acls
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* number of ACL&squot;s */
DECL|member|reserver
r_int
r_char
id|reserver
suffix:colon
l_int|5
suffix:semicolon
DECL|member|ix
r_int
r_char
id|ix
suffix:semicolon
multiline_comment|/* code page index (of filename), see&n;&t;&t;&t;&t;&t;   struct code_page_data */
DECL|member|namelen
DECL|member|name
r_int
r_char
id|namelen
comma
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* file name */
multiline_comment|/* dnode_secno down;&t;  btree down pointer, if present,&n;     &t;&t;&t;  follows name on next word boundary, or maybe it&n;&t;&t;&t;  precedes next dirent, which is on a word boundary. */
)brace
suffix:semicolon
multiline_comment|/* B+ tree: allocation info in fnodes and anodes */
multiline_comment|/* dnodes point to fnodes which are responsible for listing the sectors&n;   assigned to the file.  This is done with trees of (length,address)&n;   pairs.  (Actually triples, of (length, file-address, disk-address)&n;   which can represent holes.  Find out if HPFS does that.)&n;   At any rate, fnodes contain a small tree; if subtrees are needed&n;   they occupy essentially a full block in anodes.  A leaf-level tree node&n;   has 3-word entries giving sector runs, a non-leaf node has 2-word&n;   entries giving subtree pointers.  A flag in the header says which. */
DECL|struct|bplus_leaf_node
r_struct
id|bplus_leaf_node
(brace
DECL|member|file_secno
r_int
id|file_secno
suffix:semicolon
multiline_comment|/* first file sector in extent */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* length, sectors */
DECL|member|disk_secno
id|secno
id|disk_secno
suffix:semicolon
multiline_comment|/* first corresponding disk sector */
)brace
suffix:semicolon
DECL|struct|bplus_internal_node
r_struct
id|bplus_internal_node
(brace
DECL|member|file_secno
r_int
id|file_secno
suffix:semicolon
multiline_comment|/* subtree maps sectors &lt; this  */
DECL|member|down
id|anode_secno
id|down
suffix:semicolon
multiline_comment|/* pointer to subtree */
)brace
suffix:semicolon
DECL|struct|bplus_header
r_struct
id|bplus_header
(brace
DECL|member|hbff
r_int
id|hbff
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* high bit of first free entry offset */
DECL|member|flag1
r_int
id|flag1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag2
r_int
id|flag2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag3
r_int
id|flag3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag4
r_int
id|flag4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fnode_parent
r_int
id|fnode_parent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ? we&squot;re pointed to by an fnode,&n;&t;&t;&t;&t;&t;   the data btree or some ea or the&n;&t;&t;&t;&t;&t;   main ea bootage pointer ea_secno */
multiline_comment|/* also can get set in fnodes, which&n;&t;&t;&t;&t;&t;   may be a chkdsk glitch or may mean&n;&t;&t;&t;&t;&t;   this bit is irrelevant in fnodes,&n;&t;&t;&t;&t;&t;   or this interpretation is all wet */
DECL|member|binary_search
r_int
id|binary_search
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suggest binary search (unused) */
DECL|member|internal
r_int
id|internal
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 -&gt; (internal) tree of anodes&n;&t;&t;&t;&t;&t;   0 -&gt; (leaf) list of extents */
DECL|member|fill
r_int
r_char
id|fill
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|n_free_nodes
r_int
r_char
id|n_free_nodes
suffix:semicolon
multiline_comment|/* free nodes in following array */
DECL|member|n_used_nodes
r_int
r_char
id|n_used_nodes
suffix:semicolon
multiline_comment|/* used nodes in following array */
DECL|member|first_free
r_int
r_int
id|first_free
suffix:semicolon
multiline_comment|/* offset from start of header to&n;&t;&t;&t;&t;&t;   first free node in array */
r_union
(brace
DECL|member|internal
r_struct
id|bplus_internal_node
id|internal
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* (internal) 2-word entries giving&n;&t;&t;&t;&t;&t;       subtree pointers */
DECL|member|external
r_struct
id|bplus_leaf_node
id|external
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* (external) 3-word entries giving&n;&t;&t;&t;&t;&t;       sector runs */
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* fnode: root of allocation b+ tree, and EA&squot;s */
multiline_comment|/* Every file and every directory has one fnode, pointed to by the directory&n;   entry and pointing to the file&squot;s sectors or directory&squot;s root dnode.  EA&squot;s&n;   are also stored here, and there are said to be ACL&squot;s somewhere here too. */
DECL|macro|FNODE_MAGIC
mdefine_line|#define FNODE_MAGIC 0xf7e40aae
DECL|struct|fnode
r_struct
id|fnode
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* f7e4 0aae */
DECL|member|zero1
r_int
id|zero1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* read history */
DECL|member|len
DECL|member|name
r_int
r_char
id|len
comma
id|name
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* true length, truncated name */
DECL|member|up
id|fnode_secno
id|up
suffix:semicolon
multiline_comment|/* pointer to file&squot;s directory fnode */
multiline_comment|/*unsigned zero2[3];*/
DECL|member|acl_size_l
id|secno
id|acl_size_l
suffix:semicolon
DECL|member|acl_secno
id|secno
id|acl_secno
suffix:semicolon
DECL|member|acl_size_s
r_int
r_int
id|acl_size_s
suffix:semicolon
DECL|member|acl_anode
r_char
id|acl_anode
suffix:semicolon
DECL|member|zero2
r_char
id|zero2
suffix:semicolon
multiline_comment|/* history bit count */
DECL|member|ea_size_l
r_int
id|ea_size_l
suffix:semicolon
multiline_comment|/* length of disk-resident ea&squot;s */
DECL|member|ea_secno
id|secno
id|ea_secno
suffix:semicolon
multiline_comment|/* first sector of disk-resident ea&squot;s*/
DECL|member|ea_size_s
r_int
r_int
id|ea_size_s
suffix:semicolon
multiline_comment|/* length of fnode-resident ea&squot;s */
DECL|member|flag0
r_int
id|flag0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ea_anode
r_int
id|ea_anode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 -&gt; ea_secno is an anode */
DECL|member|flag2
r_int
id|flag2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag3
r_int
id|flag3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag4
r_int
id|flag4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag5
r_int
id|flag5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag6
r_int
id|flag6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag7
r_int
id|flag7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dirflag
r_int
id|dirflag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 -&gt; directory.  first &amp; only extent&n;&t;&t;&t;&t;&t;   points to dnode. */
DECL|member|flag9
r_int
id|flag9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag10
r_int
id|flag10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag11
r_int
id|flag11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag12
r_int
id|flag12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag13
r_int
id|flag13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag14
r_int
id|flag14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag15
r_int
id|flag15
suffix:colon
l_int|1
suffix:semicolon
DECL|member|btree
r_struct
id|bplus_header
id|btree
suffix:semicolon
multiline_comment|/* b+ tree, 8 extents or 12 subtrees */
r_union
(brace
DECL|member|external
r_struct
id|bplus_leaf_node
id|external
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|internal
r_struct
id|bplus_internal_node
id|internal
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|file_size
r_int
id|file_size
suffix:semicolon
multiline_comment|/* file length, bytes */
DECL|member|n_needea
r_int
id|n_needea
suffix:semicolon
multiline_comment|/* number of EA&squot;s with NEEDEA set */
DECL|member|user_id
r_char
id|user_id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|ea_offs
r_int
id|ea_offs
suffix:semicolon
multiline_comment|/* offset from start of fnode&n;&t;&t;&t;&t;&t;   to first fnode-resident ea */
DECL|member|dasd_limit_treshhold
r_char
id|dasd_limit_treshhold
suffix:semicolon
DECL|member|dasd_limit_delta
r_char
id|dasd_limit_delta
suffix:semicolon
DECL|member|dasd_limit
r_int
id|dasd_limit
suffix:semicolon
DECL|member|dasd_usage
r_int
id|dasd_usage
suffix:semicolon
multiline_comment|/*unsigned zero5[2];*/
DECL|member|ea
r_int
r_char
id|ea
(braket
l_int|316
)braket
suffix:semicolon
multiline_comment|/* zero or more EA&squot;s, packed together&n;&t;&t;&t;&t;&t;   with no alignment padding.&n;&t;&t;&t;&t;&t;   (Do not use this name, get here&n;&t;&t;&t;&t;&t;   via fnode + ea_offs. I think.) */
)brace
suffix:semicolon
multiline_comment|/* anode: 99.44% pure allocation tree */
DECL|macro|ANODE_MAGIC
mdefine_line|#define ANODE_MAGIC 0x37e40aae
DECL|struct|anode
r_struct
id|anode
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* 37e4 0aae */
DECL|member|self
id|anode_secno
id|self
suffix:semicolon
multiline_comment|/* pointer to this anode */
DECL|member|up
id|secno
id|up
suffix:semicolon
multiline_comment|/* parent anode or fnode */
DECL|member|btree
r_struct
id|bplus_header
id|btree
suffix:semicolon
multiline_comment|/* b+tree, 40 extents or 60 subtrees */
r_union
(brace
DECL|member|external
r_struct
id|bplus_leaf_node
id|external
(braket
l_int|40
)braket
suffix:semicolon
DECL|member|internal
r_struct
id|bplus_internal_node
id|internal
(braket
l_int|60
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|fill
r_int
id|fill
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* unused */
)brace
suffix:semicolon
multiline_comment|/* extended attributes.&n;&n;   A file&squot;s EA info is stored as a list of (name,value) pairs.  It is&n;   usually in the fnode, but (if it&squot;s large) it is moved to a single&n;   sector run outside the fnode, or to multiple runs with an anode tree&n;   that points to them.&n;&n;   The value of a single EA is stored along with the name, or (if large)&n;   it is moved to a single sector run, or multiple runs pointed to by an&n;   anode tree, pointed to by the value field of the (name,value) pair.&n;&n;   Flags in the EA tell whether the value is immediate, in a single sector&n;   run, or in multiple runs.  Flags in the fnode tell whether the EA list&n;   is immediate, in a single run, or in multiple runs. */
DECL|struct|extended_attribute
r_struct
id|extended_attribute
(brace
DECL|member|indirect
r_int
id|indirect
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 -&gt; value gives sector number&n;&t;&t;&t;&t;&t;   where real value starts */
DECL|member|anode
r_int
id|anode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 -&gt; sector is an anode&n;&t;&t;&t;&t;&t;   that points to fragmented value */
DECL|member|flag2
r_int
id|flag2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag3
r_int
id|flag3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag4
r_int
id|flag4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag5
r_int
id|flag5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flag6
r_int
id|flag6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|needea
r_int
id|needea
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* required ea */
DECL|member|namelen
r_int
r_char
id|namelen
suffix:semicolon
multiline_comment|/* length of name, bytes */
DECL|member|valuelen
r_int
r_int
id|valuelen
suffix:semicolon
multiline_comment|/* length of value, bytes */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/*&n;    unsigned char name[namelen];&t;ascii attrib name&n;    unsigned char nul;&t;&t;&t;terminating &squot;&bslash;0&squot;, not counted&n;    unsigned char value[valuelen];&t;value, arbitrary&n;      if this.indirect, valuelen is 8 and the value is&n;        unsigned length;&t;&t;real length of value, bytes&n;        secno secno;&t;&t;&t;sector address where it starts&n;      if this.anode, the above sector number is the root of an anode tree&n;        which points to the value.&n;  */
)brace
suffix:semicolon
multiline_comment|/*&n;   Local Variables:&n;   comment-column: 40&n;   End:&n;*/
eof
