multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/mman.h&quot;
DECL|variable|vm_stack_flags
r_int
r_int
id|vm_stack_flags
op_assign
id|__VM_STACK_FLAGS
suffix:semicolon
DECL|variable|vm_stack_flags32
r_int
r_int
id|vm_stack_flags32
op_assign
id|__VM_STACK_FLAGS
suffix:semicolon
DECL|variable|vm_data_default_flags
r_int
r_int
id|vm_data_default_flags
op_assign
id|__VM_DATA_DEFAULT_FLAGS
suffix:semicolon
DECL|variable|vm_data_default_flags32
r_int
r_int
id|vm_data_default_flags32
op_assign
id|__VM_DATA_DEFAULT_FLAGS
suffix:semicolon
DECL|variable|vm_force_exec32
r_int
r_int
id|vm_force_exec32
op_assign
id|PROT_EXEC
suffix:semicolon
multiline_comment|/* Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
