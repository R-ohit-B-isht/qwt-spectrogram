cmake_minimum_required(VERSION 3.5)

project(qwtgrsp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
)

add_executable(qwtgrsp
    main.cpp
    widget.cpp
    widget.h
)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qwtgrsp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation


#target_link_libraries(qwtgrsp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(qwtgrsp Qt5::Widgets)
target_link_libraries(qwtgrsp qwt-qt5)



install(TARGETS qwtgrsp)

