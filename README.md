spreload
========

Simple preload tool

Usage:
<pre>
	spreload [file|directory]
	
	spreload-profile [executable]
	cat spreload_out | spreload
</pre>
Logs files opened by <executable> into spreload_out file, which can be fed
into spreload tool. <br><br>
*preloads files into page cache<br>
*any gain on ssd's is doubtful due to low access times<br>
*should work on recent linux distros (>=linux 2.4.13,>=glibc-2.3)<br>
*readahead() call used for preloading<br>

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
.
├── drop_caches.sh
├── Makefile
├── README.md
├── spreload
├── spreload.c
├── spreload.h
├── spreload-profile
├── spreload_profile.c
├── sprofile.so
└── TODO
</pre>
