
INCLUDE_DIRECTORIES(../)



ADD_EXECUTABLE(test_countdownlatch ../countdownlatch.cpp test_countdownlatch.cpp)

TARGET_LINK_LIBRARIES(test_countdownlatch pthread)


ADD_EXECUTABLE(test_threadpool ../threadpool.cpp test_threadpool.cpp)

TARGET_LINK_LIBRARIES(test_threadpool pthread)