#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T07:54:23
#
#-------------------------------------------------

QT       -= core gui

TARGET = demo
TEMPLATE = lib

DEFINES += DEMO_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    demo.cpp \
    deps/gtest/src/gtest-all.cc \
    deps/gtest/src/gtest-death-test.cc \
    deps/gtest/src/gtest-filepath.cc \
    deps/gtest/src/gtest-port.cc \
    deps/gtest/src/gtest-printers.cc \
    deps/gtest/src/gtest-test-part.cc \
    deps/gtest/src/gtest-typed-test.cc \
    deps/gtest/src/gtest.cc \
    deps/gtest/src/gtest_main.cc

HEADERS += \
    cppjieba/DictTrie.hpp \
    cppjieba/FullSegment.hpp \
    cppjieba/HMMModel.hpp \
    cppjieba/HMMSegment.hpp \
    cppjieba/Jieba.hpp \
    cppjieba/KeywordExtractor.hpp \
    cppjieba/MixSegment.hpp \
    cppjieba/MPSegment.hpp \
    cppjieba/PosTagger.hpp \
    cppjieba/PreFilter.hpp \
    cppjieba/QuerySegment.hpp \
    cppjieba/SegmentBase.hpp \
    cppjieba/SegmentTagged.hpp \
    cppjieba/TextRankExtractor.hpp \
    cppjieba/Trie.hpp \
    cppjieba/Unicode.hpp \
    demo.h \
    deps/gtest/include/gtest/internal/gtest-death-test-internal.h \
    deps/gtest/include/gtest/internal/gtest-filepath.h \
    deps/gtest/include/gtest/internal/gtest-internal.h \
    deps/gtest/include/gtest/internal/gtest-linked_ptr.h \
    deps/gtest/include/gtest/internal/gtest-param-util-generated.h \
    deps/gtest/include/gtest/internal/gtest-param-util.h \
    deps/gtest/include/gtest/internal/gtest-port.h \
    deps/gtest/include/gtest/internal/gtest-string.h \
    deps/gtest/include/gtest/internal/gtest-tuple.h \
    deps/gtest/include/gtest/internal/gtest-type-util.h \
    deps/gtest/include/gtest/gtest-death-test.h \
    deps/gtest/include/gtest/gtest-message.h \
    deps/gtest/include/gtest/gtest-param-test.h \
    deps/gtest/include/gtest/gtest-printers.h \
    deps/gtest/include/gtest/gtest-spi.h \
    deps/gtest/include/gtest/gtest-test-part.h \
    deps/gtest/include/gtest/gtest-typed-test.h \
    deps/gtest/include/gtest/gtest.h \
    deps/gtest/include/gtest/gtest_pred_impl.h \
    deps/gtest/include/gtest/gtest_prod.h \
    deps/gtest/src/gtest-internal-inl.h \
    deps/limonp/ArgvContext.hpp \
    deps/limonp/BlockingQueue.hpp \
    deps/limonp/BoundedBlockingQueue.hpp \
    deps/limonp/BoundedQueue.hpp \
    deps/limonp/Closure.hpp \
    deps/limonp/Colors.hpp \
    deps/limonp/Condition.hpp \
    deps/limonp/Config.hpp \
    deps/limonp/FileLock.hpp \
    deps/limonp/ForcePublic.hpp \
    deps/limonp/LocalVector.hpp \
    deps/limonp/Logging.hpp \
    deps/limonp/Md5.hpp \
    deps/limonp/MutexLock.hpp \
    deps/limonp/NonCopyable.hpp \
    deps/limonp/StdExtension.hpp \
    deps/limonp/StringUtil.hpp \
    deps/limonp/Thread.hpp \
    deps/limonp/ThreadPool.hpp \
    include/cppjieba/DictTrie.hpp \
    include/cppjieba/FullSegment.hpp \
    include/cppjieba/HMMModel.hpp \
    include/cppjieba/HMMSegment.hpp \
    include/cppjieba/Jieba.hpp \
    include/cppjieba/KeywordExtractor.hpp \
    include/cppjieba/MixSegment.hpp \
    include/cppjieba/MPSegment.hpp \
    include/cppjieba/PosTagger.hpp \
    include/cppjieba/PreFilter.hpp \
    include/cppjieba/QuerySegment.hpp \
    include/cppjieba/SegmentBase.hpp \
    include/cppjieba/SegmentTagged.hpp \
    include/cppjieba/TextRankExtractor.hpp \
    include/cppjieba/Trie.hpp \
    include/cppjieba/Unicode.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
