TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=  -ldl


SOURCES += \
    train.cpp

DISTFILES += \
    ../build-train-Desktop_Qt_5_10_1_GCC_64bit-Debug/libdemo.so \
    dict/jieba.dict.utf8 \
    dict/README.md \
    dict/user.dict.utf8 \
    dict/stop_words.utf8 \
    dict/idf.utf8 \
    dict/hmm_model.utf8
    ../build-tf_idf-Desktop_Qt_5_10_1_GCC_64bit-Debug/libtf_idf.so
