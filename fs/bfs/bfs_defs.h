DECL|macro|printf
mdefine_line|#define printf(format, args...) &bslash;&n;&t;printk(KERN_ERR &quot;BFS-fs: %s(): &quot; format, __FUNCTION__, ## args)
eof
