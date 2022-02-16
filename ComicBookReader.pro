QT += quick
CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2


INCLUDEPATH += $$PWD/src

#files for libarchive
INCLUDEPATH += $$PWD/libarchive/include
LIBS += -L"$$PWD\\libarchive\\lib" \
    -larchive
LIBS += -L"$$PWD\\libarchive\\lib" \
    -larchive_static
LIBS += -L"$$PWD\\libarchive\\bin\\archive.dll"

#Files for opencv
INCLUDEPATH += C:/opencv/build/include
LIBS += C:/opencv/build/bin/libopencv_core454.dll
LIBS += C:/opencv/build/bin/libopencv_imgcodecs454.dll
LIBS += C:/opencv/build/bin/libopencv_imgproc454.dll
LIBS += C:/opencv/build/bin/libopencv_highgui454.dll
LIBS += C:/opencv/build/bin/libopencv_features2d454.dll
LIBS += C:/opencv/build/bin/libopencv_calib3d454.dll


HEADERS += \
    src/ArchiveExtraction.h \
    src/Archives.h \
    src/FournisseurImage.h \
    src/Image.h \
    src/ParametresChargementImage.h \
    src/TraitementImage.h \
    src/cache.hpp \
    src/chargerimagecache.h


SOURCES += \
    src/main.cpp \
    src/FournisseurImage.cpp \
    src/ArchiveExtraction.cpp \
    src/Archives.cpp \
    src/TraitementImage.cpp \
    src/chargerimagecache.cpp

RESOURCES += src/qml.qrc


DISTFILES += \
    src/CustomButton.qml \
    src/CustomSlider.qml \
    src/main.qml


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

