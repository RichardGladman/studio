cmake_minimum_required(VERSION 3.19)
project(studio LANGUAGES CXX)

include_directories(${Qt6_INCLUDE_DIRS})

list(APPEND CMAKE_PREFIX_PATH "/home/richard/Qt/6.12.0/gcc_64")
find_package(Qt6 6.12 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

qt_add_executable(studio
    WIN32 MACOSX_BUNDLE
    main.cpp dbinitialiser.h dbinitialiser.cpp
    mainwindow.h mainwindow.cpp 
    resources.qrc
    common/listdata.h
    about/aboutdialog.h about/aboutdialog.cpp
    projects/projectmodel.h projects/projectmodel.cpp
    projects/projectrepository.h projects/projectrepository.cpp
    projects/projectframe.h projects/projectframe.cpp
    projects/projectform.h projects/projectform.cpp
    reports/projecttaskframe.h reports/projecttaskframe.cpp
    reports/bystartdateframe.h reports/bystartdateframe.cpp
    reports/exporter.h reports/exporter.cpp
    settings/settingsmodel.h settings/settingsmodel.cpp
    settings/settingsrepository.h settings/settingsrepository.cpp
    settings/settingsframe.h settings/settingsframe.cpp
    staff/staffmodel.h staff/staffmodel.cpp
    staff/staffrepository.h staff/staffrepository.cpp
    tasks/taskmodel.h tasks/taskmodel.cpp
    tasks/taskrepository.h tasks/taskrepository.cpp
    tasks/taskform.h tasks/taskform.cpp
    tasks/taskframe.h tasks/taskframe.cpp
    tasktimer/tasktimermodel.h tasktimer/tasktimermodel.cpp
    tasktimer/tasktimerrepository.h tasktimer/tasktimerrepository.cpp
    
)

target_link_libraries(studio
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

install(TARGETS studio
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET studio
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
