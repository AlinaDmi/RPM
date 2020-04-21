QT += widgets

HEADERS       = \
                Snap.h \
                calculator.h
SOURCES       = \
                Snap.cpp \
                calculator.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/calculator
INSTALLS += target
