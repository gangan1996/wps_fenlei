TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=  -ldl
        -L/libs
        -ljieba
        -lsvm
        -ltf_idf

SOURCES += \
    predict.cpp \

DISTFILES += \
    dict/README.md \
    dict/user.dict.utf8 \
    dict/stop_words.utf8 \
    dict/jieba.dict.utf8 \
    dict/idf.utf8 \
    dict/hmm_model.utf8 \
    dict/pos_dict/prob_trans.utf8 \
    dict/pos_dict/prob_start.utf8 \
    dict/pos_dict/prob_emit.utf8 \
    dict/pos_dict/char_state_tab.utf8
