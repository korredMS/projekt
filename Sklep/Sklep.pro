# -------------------------------------------------
# Project created by QtCreator 2010-04-20T15:27:45
# -------------------------------------------------
QT += sql
QT       += network sql
TARGET = Sklep
TEMPLATE = app
SOURCES += main.cpp \
    sklep.cpp \
    sprzedawca.cpp \
    zamawiajacy.cpp \
    kierownik.cpp \
    ../DBProxy/dbproxy.cpp
HEADERS += sklep.h \
    sprzedawca.h \
    zamawiajacy.h \
    kierownik.h \
    ../DBProxy/dbproxy.h
FORMS += sklep.ui \
    sprzedawca.ui \
    zamawiajacy.ui \
    kierownik.ui
