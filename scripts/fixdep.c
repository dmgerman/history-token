multiline_comment|/*&n; * &quot;Optimize&quot; a list of dependencies as spit out by gcc -MD &n; * for the kernel build&n; * ===========================================================================&n; *&n; * Author       Kai Germaschewski&n; * Copyright    2002 by Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; *&n; * Introduction:&n; * &n; * gcc produces a very nice and correct list of dependencies which&n; * tells make when to remake a file.&n; *&n; * To use this list as-is however has the drawback that virtually&n; * every file in the kernel includes &lt;linux/config.h&gt; which then again&n; * includes &lt;linux/autoconf.h&gt;&n; *&n; * If the user re-runs make *config, linux/autoconf.h will be&n; * regenerated.  make notices that and will rebuild every file which&n; * includes autconf.h, i.e. basically all files. This is extremely&n; * annoying if the user just changed CONFIG_HIS_DRIVER from n to m.&n; * &n; * So we play the same trick that &quot;mkdep&quot; played before. We replace&n; * the dependency on linux/autoconf.h by a dependency on every config&n; * option which is mentioned in any of the listed prequisites.&n; *  &n; * To be exact, split-include populates a tree in include/config/,&n; * e.g. include/config/his/driver.h, which contains the #define/#undef&n; * for the CONFIG_HIS_DRIVER option.&n; *&n; * So if the user changes his CONFIG_HIS_DRIVER option, only the objects&n; * which depend on &quot;include/linux/config/his/driver.h&quot; will be rebuilt,&n; * so most likely only his driver ;-) &n; *&n; * The idea above dates, by the way, back to Michael E Chastain, AFAIK.&n; * &n; * So to get dependencies right, there two issues:&n; * o if any of the files the compiler read changed, we need to rebuild&n; * o if the command line given to the compile the file changed, we&n; *   better rebuild as well.&n; *&n; * The former is handled by using the -MD output, the later by saving&n; * the command line used to compile the old object and comparing it&n; * to the one we would now use.&n; *&n; * Again, also this idea is pretty old and has been discussed on&n; * kbuild-devel a long time ago. I don&squot;t have a sensibly working&n; * internet connection right now, so I rather don&squot;t mention names&n; * without double checking.&n; *&n; * This code here has been based partially based on mkdep.c, which&n; * says the following about its history:&n; *&n; *   Copyright abandoned, Michael Chastain, &lt;mailto:mec@shout.net&gt;.&n; *   This is a C version of syncdep.pl by Werner Almesberger.&n; *&n; *&n; * It is invoked as&n; *&n; *   fixdep &lt;depfile&gt; &lt;target&gt; &lt;topdir&gt; &lt;cmdline&gt;&n; *&n; * and will read the dependency file &lt;depfile&gt;&n; *&n; * The transformed dependency snipped is written to stdout.&n; *&n; * It first generates a line&n; *&n; *   cmd_&lt;target&gt; = &lt;cmdline&gt;&n; *&n; * and then basically copies the .&lt;target&gt;.d file to stdout, in the&n; * process filtering out the dependency on linux/autconf.h and adding&n; * dependencies on include/config/my/option.h for every&n; * CONFIG_MY_OPTION encountered in any of the prequisites.&n; *&n; * It will also filter out all the dependencies on *.ver. We need&n; * to make sure that the generated version checksum are globally up&n; * to date before even starting the recursive build, so it&squot;s too late&n; * at this point anyway.&n; *&n; * The algorithm to grep for &quot;CONFIG_...&quot; is bit unusual, but should&n; * be fast ;-) We don&squot;t even try to really parse the header files, but&n; * merely grep, i.e. if CONFIG_FOO is mentioned in a comment, it will&n; * be picked up as well. It&squot;s not a problem with respect to&n; * correctness, since that can only give too many dependencies, thus&n; * we cannot miss a rebuild. Since people tend to not mention totally&n; * unrelated CONFIG_ options all over the place, it&squot;s not an&n; * efficiency problem either.&n; * &n; * (Note: it&squot;d be easy to port over the complete mkdep state machine,&n; *  but I don&squot;t think the added complexity is worth it)&n; */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
DECL|macro|INT_CONF
mdefine_line|#define INT_CONF ntohl(0x434f4e46)
DECL|macro|INT_ONFI
mdefine_line|#define INT_ONFI ntohl(0x4f4e4649)
DECL|macro|INT_NFIG
mdefine_line|#define INT_NFIG ntohl(0x4e464947)
DECL|macro|INT_FIG_
mdefine_line|#define INT_FIG_ ntohl(0x4649475f)
DECL|variable|topdir
r_char
op_star
id|topdir
suffix:semicolon
DECL|variable|target
r_char
op_star
id|target
suffix:semicolon
DECL|variable|depfile
r_char
op_star
id|depfile
suffix:semicolon
DECL|variable|cmdline
r_char
op_star
id|cmdline
suffix:semicolon
DECL|function|usage
r_void
id|usage
c_func
(paren
r_void
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Usage: fixdep &lt;depfile&gt; &lt;target&gt; &lt;topdir&gt; &lt;cmdline&gt;&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|print_cmdline
r_void
id|print_cmdline
c_func
(paren
r_void
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;cmd_%s := %s&bslash;n&bslash;n&quot;
comma
id|target
comma
id|cmdline
)paren
suffix:semicolon
)brace
DECL|variable|str_config
r_char
op_star
id|str_config
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|size_config
r_int
id|size_config
op_assign
l_int|0
suffix:semicolon
DECL|variable|len_config
r_int
id|len_config
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Grow the configuration string to a desired length.&n; * Usually the first growth is plenty.&n; */
DECL|function|grow_config
r_void
id|grow_config
c_func
(paren
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len_config
op_plus
id|len
OG
id|size_config
)paren
(brace
r_if
c_cond
(paren
id|size_config
op_eq
l_int|0
)paren
id|size_config
op_assign
l_int|2048
suffix:semicolon
id|str_config
op_assign
id|realloc
c_func
(paren
id|str_config
comma
id|size_config
op_mul_assign
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str_config
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;fixdep:malloc&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Lookup a value in the configuration string.&n; */
DECL|function|is_defined_config
r_int
id|is_defined_config
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_const
r_char
op_star
id|pconfig
suffix:semicolon
r_const
r_char
op_star
id|plast
op_assign
id|str_config
op_plus
id|len_config
op_minus
id|len
suffix:semicolon
r_for
c_loop
(paren
id|pconfig
op_assign
id|str_config
op_plus
l_int|1
suffix:semicolon
id|pconfig
OL
id|plast
suffix:semicolon
id|pconfig
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pconfig
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|pconfig
(braket
id|len
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|pconfig
comma
id|name
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a new value to the configuration string.&n; */
DECL|function|define_config
r_void
id|define_config
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
id|grow_config
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|str_config
op_plus
id|len_config
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|len_config
op_add_assign
id|len
suffix:semicolon
id|str_config
(braket
id|len_config
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the set of configuration strings.&n; */
DECL|function|clear_config
r_void
id|clear_config
c_func
(paren
r_void
)paren
(brace
id|len_config
op_assign
l_int|0
suffix:semicolon
id|define_config
c_func
(paren
l_string|&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Record the use of a CONFIG_* word.&n; */
DECL|function|use_config
r_void
id|use_config
c_func
(paren
r_char
op_star
id|m
comma
r_int
id|slen
)paren
(brace
r_char
id|s
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|is_defined_config
c_func
(paren
id|m
comma
id|slen
)paren
)paren
r_return
suffix:semicolon
id|define_config
c_func
(paren
id|m
comma
id|slen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|s
comma
id|m
comma
id|slen
)paren
suffix:semicolon
id|s
(braket
id|slen
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|s
suffix:semicolon
id|p
OL
id|s
op_plus
id|slen
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;_&squot;
)paren
op_star
id|p
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_else
op_star
id|p
op_assign
id|tolower
c_func
(paren
(paren
r_int
r_char
)paren
op_star
id|p
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;    $(wildcard %s/include/config/%s.h) &bslash;&bslash;&bslash;n&quot;
comma
id|topdir
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|parse_config_file
r_void
id|parse_config_file
c_func
(paren
r_char
op_star
id|map
comma
r_int
id|len
)paren
(brace
r_int
op_star
id|end
op_assign
(paren
r_int
op_star
)paren
(paren
id|map
op_plus
id|len
)paren
suffix:semicolon
singleline_comment|// start at +1, so that p can never be &lt; map
r_int
op_star
id|m
op_assign
(paren
r_int
op_star
)paren
id|map
op_plus
l_int|1
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|m
OL
id|end
suffix:semicolon
id|m
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|m
op_eq
id|INT_CONF
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|m
suffix:semicolon
r_goto
id|conf
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|m
op_eq
id|INT_ONFI
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|m
op_minus
l_int|1
suffix:semicolon
r_goto
id|conf
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|m
op_eq
id|INT_NFIG
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|m
op_minus
l_int|2
suffix:semicolon
r_goto
id|conf
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|m
op_eq
id|INT_FIG_
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|m
op_minus
l_int|3
suffix:semicolon
r_goto
id|conf
suffix:semicolon
)brace
r_continue
suffix:semicolon
id|conf
suffix:colon
r_if
c_cond
(paren
id|p
OG
id|map
op_plus
id|len
op_minus
l_int|7
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;CONFIG_&quot;
comma
l_int|7
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|p
op_plus
l_int|7
suffix:semicolon
id|q
OL
id|map
op_plus
id|len
suffix:semicolon
id|q
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|isalnum
c_func
(paren
op_star
id|q
)paren
op_logical_or
op_star
id|q
op_eq
l_char|&squot;_&squot;
)paren
)paren
r_goto
id|found
suffix:semicolon
)brace
r_continue
suffix:semicolon
id|found
suffix:colon
id|use_config
c_func
(paren
id|p
op_plus
l_int|7
comma
id|q
op_minus
id|p
op_minus
l_int|7
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* test is s ends in sub */
DECL|function|strrcmp
r_int
id|strrcmp
c_func
(paren
r_char
op_star
id|s
comma
r_char
op_star
id|sub
)paren
(brace
r_int
id|slen
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|sublen
op_assign
id|strlen
c_func
(paren
id|sub
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sublen
OG
id|slen
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|memcmp
c_func
(paren
id|s
op_plus
id|slen
op_minus
id|sublen
comma
id|sub
comma
id|sublen
)paren
suffix:semicolon
)brace
DECL|function|do_config_file
r_void
id|do_config_file
c_func
(paren
r_char
op_star
id|filename
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;fixdep: &quot;
)paren
suffix:semicolon
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
m_exit
(paren
l_int|2
)paren
suffix:semicolon
)brace
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st.st_size
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|st.st_size
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|map
op_eq
op_minus
l_int|1
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;fixdep: mmap&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|parse_config_file
c_func
(paren
id|map
comma
id|st.st_size
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|st.st_size
)paren
suffix:semicolon
)brace
DECL|function|parse_dep_file
r_void
id|parse_dep_file
c_func
(paren
r_void
op_star
id|map
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|m
op_assign
id|map
suffix:semicolon
r_char
op_star
id|end
op_assign
id|map
op_plus
id|len
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_char
id|s
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|m
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;fixdep: parse error&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|s
comma
id|m
comma
id|p
op_minus
id|m
)paren
suffix:semicolon
id|s
(braket
id|p
op_minus
id|m
)braket
op_assign
l_int|0
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;deps_%s := &bslash;&bslash;&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
id|m
op_assign
id|p
op_plus
l_int|1
suffix:semicolon
id|clear_config
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|m
OL
id|end
)paren
(brace
r_while
c_loop
(paren
id|m
OL
id|end
op_logical_and
(paren
op_star
id|m
op_eq
l_char|&squot; &squot;
op_logical_or
op_star
id|m
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_or
op_star
id|m
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
id|m
op_increment
suffix:semicolon
id|p
op_assign
id|m
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
op_logical_and
op_star
id|p
op_ne
l_char|&squot; &squot;
)paren
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|end
)paren
(brace
r_do
id|p
op_decrement
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|isalnum
c_func
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|s
comma
id|m
comma
id|p
op_minus
id|m
)paren
suffix:semicolon
id|s
(braket
id|p
op_minus
id|m
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strrcmp
c_func
(paren
id|s
comma
l_string|&quot;include/linux/autoconf.h&quot;
)paren
op_logical_and
id|strrcmp
c_func
(paren
id|s
comma
l_string|&quot;.ver&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;  %s &bslash;&bslash;&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
id|do_config_file
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
id|m
op_assign
id|p
op_plus
l_int|1
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s: $(deps_%s)&bslash;n&bslash;n&quot;
comma
id|target
comma
id|target
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;$(deps_%s):&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
)brace
DECL|function|print_deps
r_void
id|print_deps
c_func
(paren
r_void
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|depfile
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;fixdep: &quot;
)paren
suffix:semicolon
id|perror
c_func
(paren
id|depfile
)paren
suffix:semicolon
m_exit
(paren
l_int|2
)paren
suffix:semicolon
)brace
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st.st_size
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;fixdep: %s is empty&bslash;n&quot;
comma
id|depfile
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|st.st_size
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|map
op_eq
op_minus
l_int|1
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;fixdep: mmap&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|parse_dep_file
c_func
(paren
id|map
comma
id|st.st_size
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|st.st_size
)paren
suffix:semicolon
)brace
DECL|function|traps
r_void
id|traps
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|test
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
op_assign
l_string|&quot;CONF&quot;
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
op_star
)paren
id|test
op_ne
id|INT_CONF
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;fixdep: sizeof(int) != 4 or wrong endianess? %#x&bslash;n&quot;
comma
op_star
(paren
r_int
op_star
)paren
id|test
)paren
suffix:semicolon
m_exit
(paren
l_int|2
)paren
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
id|traps
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|5
)paren
id|usage
c_func
(paren
)paren
suffix:semicolon
id|depfile
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|target
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
id|topdir
op_assign
id|argv
(braket
l_int|3
)braket
suffix:semicolon
id|cmdline
op_assign
id|argv
(braket
l_int|4
)braket
suffix:semicolon
id|print_cmdline
c_func
(paren
)paren
suffix:semicolon
id|print_deps
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
