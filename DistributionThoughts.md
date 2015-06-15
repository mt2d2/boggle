Now that everything is almost feature complete, we should start thinking about how we will distribute. On OS X, that's simple, just include the Qt Framework in the app bundle-- it's large, but works well. We should aim for 10.4 compatibility.

On Winodws, we need an installer. We'll be using MSVC 2008, so there's distribs we need to ship, along with the Qt libs.

Also, think about PGO
QMAKE\_CFLAGS\_RELEASE	= -O2 -GL
QMAKE\_LFLAGS\_RELEASE += -LTCG

http://lists.trolltech.com/qt-interest/2007-11/msg00405.html