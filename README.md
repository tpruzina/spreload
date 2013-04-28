spreload
========

Simple preload tool

<pre>
Usage: spreload [[OPT_PATH]] || PIPE (stdin)
		OPT_PATH - path to file or directory
</pre>

*should work on recent linux distros (>=linux 2.4.13,>=glibc-2.3)
*one simple C file
*originally written to speed up loading of firefox profile
*readahead() call used for preloading
*standard libraries used only (virtually no dependencies on desktop)
*Fairly dumb tool ;-)

Any suggestions or bugreports are wellcome.

License: WTFPLv2
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
.
├── drop_caches.sh
├── Makefile
├── README.md
├── spreload
├── spreload.c
└── TODO

0 directories, 6 files
</pre>
