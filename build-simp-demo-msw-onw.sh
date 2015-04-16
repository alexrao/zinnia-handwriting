export QT_MOC=../../../../../usr/qt-5.4.1-o-msw/5.4/mingw491_32/bin/moc
export BUILD_ROOT=../..
cd stand-alone/simple-demo/
make CROSS_COMPILER=i686-w64-mingw32- MINGW32=1 OUT=out \
  GCCONW=1 ID_QT_VERSION=0x050401
