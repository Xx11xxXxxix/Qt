cmake_minimum_required(VERSION 3.16)

project(bangtuitui_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_PREFIX_PATH "D:/ailipan/Qt/6.8.0/mingw_64/lib/cmake")
set(Qt_DIR "D:/ailipan/Qt/6.8.0/mingw_64/lib/cmake/Qt6")


find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network Sql Multimedia )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/netease)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    netease/loginwidget.cpp
    netease/loginwidget.h
    netease/qrcodewidget.cpp
    netease/qrcodewidget.h
    netease/api/recommendapi.cpp
    netease/api/recommendapi.h
    netease/api/songapi.h
    netease/api/songapi.cpp
    netease/models/song.h
    netease/models/song.cpp
    netease/models/cookie.h
    netease/models/cookie.cpp
    netease/mainpage/mainpage.cpp
    netease/mainpage/mainpage.h
    netease/widgets/audioplayer.cpp
    netease/widgets/audioplayer.h


)

qt_add_executable(bangtuitui_qt
    ${PROJECT_SOURCES}
    apilogger.h apilogger.cpp
    netease/api/recommendapi.cpp netease/api/recommendapi.h netease/models/song.cpp netease/models/song.h netease/widgets/recommendwidget.cpp netease/widgets/recommendwidget.h
    netease/mainpage/mainpage.cpp netease/mainpage/mainpage.h
    netease/models/cookie.cpp netease/models/cookie.h
    netease/api/songapi.cpp netease/api/songapi.h
    netease/widgets/audioplayer.cpp netease/widgets/audioplayer.h
    admin/api/admin_api.cpp admin/api/admin_api.h admin/models/admin_user.cpp admin/models/admin_user.h admin/widgets/admin_widgets.cpp admin/widgets/admin_widgets.h
    common/database/account_mapper.cpp common/database/account_mapper.h

)

target_link_libraries(bangtuitui_qt
    PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Sql
    Qt6::Multimedia
)
