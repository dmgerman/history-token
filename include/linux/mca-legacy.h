multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* This is the function prototypes for the old legacy MCA interface&n; *&n; * Please move your driver to the new sysfs based one instead */
macro_line|#ifndef _LINUX_MCA_LEGACY_H
DECL|macro|_LINUX_MCA_LEGACY_H
mdefine_line|#define _LINUX_MCA_LEGACY_H
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#warning &quot;MCA legacy - please move your driver to the new sysfs api&quot;
multiline_comment|/* MCA_NOTFOUND is an error condition.  The other two indicate&n; * motherboard POS registers contain the adapter.  They might be&n; * returned by the mca_find_adapter() function, and can be used as&n; * arguments to mca_read_stored_pos().  I&squot;m not going to allow direct&n; * access to the motherboard registers until we run across an adapter&n; * that requires it.  We don&squot;t know enough about them to know if it&squot;s&n; * safe.&n; *&n; * See Documentation/mca.txt or one of the existing drivers for&n; * more information.&n; */
DECL|macro|MCA_NOTFOUND
mdefine_line|#define MCA_NOTFOUND&t;(-1)
multiline_comment|/* Returns the slot of the first enabled adapter matching id.  User can&n; * specify a starting slot beyond zero, to deal with detecting multiple&n; * devices.  Returns MCA_NOTFOUND if id not found.  Also checks the&n; * integrated adapters.&n; */
r_extern
r_int
id|mca_find_adapter
c_func
(paren
r_int
id|id
comma
r_int
id|start
)paren
suffix:semicolon
r_extern
r_int
id|mca_find_unused_adapter
c_func
(paren
r_int
id|id
comma
r_int
id|start
)paren
suffix:semicolon
r_extern
r_int
id|mca_is_adapter_used
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|mca_mark_as_used
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_void
id|mca_mark_as_unused
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
multiline_comment|/* gets a byte out of POS register (stored in memory) */
r_extern
r_int
r_char
id|mca_read_stored_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
)paren
suffix:semicolon
multiline_comment|/* This can be expanded later.  Right now, it gives us a way of&n; * getting meaningful information into the MCA_info structure,&n; * so we can have a more interesting /proc/mca.&n; */
r_extern
r_void
id|mca_set_adapter_name
c_func
(paren
r_int
id|slot
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* These routines actually mess with the hardware POS registers.  They&n; * temporarily disable the device (and interrupts), so make sure you know&n; * what you&squot;re doing if you use them.  Furthermore, writing to a POS may&n; * result in two devices trying to share a resource, which in turn can&n; * result in multiple devices sharing memory spaces, IRQs, or even trashing&n; * hardware.  YOU HAVE BEEN WARNED.&n; *&n; * You can only access slots with this.  Motherboard registers are off&n; * limits.&n; */
multiline_comment|/* read a byte from the specified POS register. */
r_extern
r_int
r_char
id|mca_read_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
)paren
suffix:semicolon
multiline_comment|/* write a byte to the specified POS register. */
r_extern
r_void
id|mca_write_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
comma
r_int
r_char
id|byte
)paren
suffix:semicolon
macro_line|#endif
eof
