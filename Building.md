# Introduction #
This page is a set of useful reminders and hints for building from source.

## OS X Qt configuration ##
This is a generic configuration line for building Qt on OS X, with support for Universal binaries. This can quite easily be expanded to work for other platforms, and will be soon.

```
configure -static -release -universal -prefix $PWD -no-exceptions -no-stl -no-webkit -no-xmlpatterns -no-phonon -no-phonon-backend -no-qt3support -no-opengl -D QT_NO_STYLE_CDE -D QT_NO_STYLE_CLEANLOOKS -D QT_NO_STYLE_MOTIF -D QT_NO_STYLE_PLASTIQUE -D QT_NO_COLORDIALOG -D QT_NO_ERRORMESSAGE -D QT_NO_FONTDIALOG -D QT_NO_PRINTDIALOG -D QT_NO_TABDIALOG -D QT_NO_DATAWIDGETMAPPER -D QT_NO_COLUMNVIEW -D QT_NO_XMLSTREAM -D QT_NO_COP -D QT_NO_HOSTINFO -D QT_NO_NETWORKPROXY -D QT_NO_UDPSOCKET -D QT_NO_URLINFO -D QT_NO_DIRECTPAINTER -D QT_NO_PAINTONSCREEN -D QT_NO_PICTURE -D QT_NO_COMPLETER -D QT_NO_UNDOCOMMAND -D QT_NO_LCDNUMBER -D QT_NO_FONTCOMBOBOX -D QT_NO_DIAL -D QT_NO_GRAPHICSVIEW -D QT_NO_MDIAREA -D QT_NO_TOOLBOX -nomake examples -nomake demos -confirm-license
```