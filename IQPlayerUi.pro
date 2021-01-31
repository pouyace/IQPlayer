QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ddcgroupbox.cpp \
    draghandler.cpp \
    fftgroupbox.cpp \
    informationgroupbox.cpp \
    iqmediaplayer.cpp \
    main.cpp \
    iqplayer.cpp \
    playlistview.cpp \
    qcustomplot.cpp \
    tableitemdelegate.cpp \
    tablemodel.cpp

HEADERS += \
    ddcgroupbox.h \
    draghandler.h \
    fftgroupbox.h \
    informationgroupbox.h \
    iqmediaplayer.h \
    iqplayer.h \
    playlistview.h \
    qcustomplot.h \
    tableitemdelegate.h \
    tablemodel.h

FORMS += \
    ddcgroupbox.ui \
    fftgroupbox.ui \
    informationgroupbox.ui \
    iqmediaplayer.ui \
    iqplayer.ui \
    playlistview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc \
    styles.qrc

win32:CONFIG(release, debug|release): LIBS += -LE:/sharedlibraries/OTMLib/bin/ -lOTMWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/sharedlibraries/OTMLib/bin/ -lOTMWidgetsd
else:unix: LIBS += -LE:/sharedlibraries/OTMLib/bin/ -lOTMWidgets

INCLUDEPATH += E:/sharedlibraries/OTMLib/inc/OTMWidgets
DEPENDPATH += E:/sharedlibraries/OTMLib/inc/OTMWidgets

win32:CONFIG(release, debug|release): LIBS += -LE:/sharedlibraries/AMRLib/bin/ -lFilters
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/sharedlibraries/AMRLib/bin/ -lFiltersd
else:unix: LIBS += -LE:/sharedlibraries/AMRLib/bin/ -lFilters

INCLUDEPATH += E:/sharedlibraries/AMRLib/inc/Filters
DEPENDPATH += E:/sharedlibraries/AMRLib/inc/Filters
