spreload
========

Simple preload tool

Usage: spreload [[OPT_PATH]] || pipe(stdin)

*should work on recent linux distros (>=linux 2.4.13,>=glibc-2.3)<br>
*one simple C file<br>
*originally written to speed up loading of firefox profile<br>
*readahead() call used for preloading<br>
*standard libraries used only (virtually no dependencies on desktop)<br>
*Fairly dumb tool ;-)<br>

Firefox startup time measurements<br>
-tested using about:startup plugin
<pre> https://addons.mozilla.org/en-US/firefox/addon/about-startup/ </pre>
sessionRestored -- timing was considered
-all caches were dropped prior to startup

<pre>
$ firefox
sessionRestored = 11404 (ms)
$ time spreload ~/.mozilla/ && firefox
sessionRestored = 8825 (ms)
time spreload = 0.174 (s*,total)
TOTAL TIME WITH SPRELOAD = 8999 (ms)

SPEEDUP = avgfirefox / avgspreloadfirefox = 1.267 -> ~27% speedup (cold start)

Note1: Averaged from 3 runs with 3 windows and several tabs (same ff settings),
in all cases deviation was <500ms compared to average.
Note2: Only userprofile and extensions were preloaded (~/.mozilla/), not
firefox binary/libraries etc.
</pre>

Any suggestions or bugreports are wellcome.

<pre>
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
</pre>

<pre>
$ tree
.
├── drop_caches.sh
├── Makefile
├── README.md
├── spreload.c
└── TODO

0 directories, 6 files
</pre>
