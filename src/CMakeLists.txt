
set(SOURCE_FILES main.cpp
        Router.cpp ../include/controllers/HelloWorldController.h ../include/controllers/BaseController.h)

add_executable(LivePlaylist ${SOURCE_FILES})
target_link_libraries(LivePlaylist net_static pthread)