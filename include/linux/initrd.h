DECL|macro|INITRD_MINOR
mdefine_line|#define INITRD_MINOR 250 /* shouldn&squot;t collide with /dev/ram* too soon ... */
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* starting block # of image */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* 1 if it is not an error if initrd_start &lt; memory_start */
r_extern
r_int
id|initrd_below_start_ok
suffix:semicolon
multiline_comment|/* free_initrd_mem always gets called with the next two as arguments.. */
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_void
id|free_initrd_mem
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|real_root_dev
suffix:semicolon
eof
