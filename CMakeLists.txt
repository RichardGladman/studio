cmake_minimum_required(VERSION 3.19)
project(studio LANGUAGES CXX)

include_directories(${Qt6_INCLUDE_DIRS})

list(APPEND CMAKE_PREFIX_PATH "/home/richard/Qt/6.12.0")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)
find_package(MySQL REQUIRED)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON) 

qt_add_executable(studio
    WIN32 MACOSX_BUNDLE
    main.cpp dbinitialiser.h dbinitialiser.cpp
    mainwindow.h mainwindow.cpp 
    resources.qrc
    common/listdata.h
    about/aboutdialog.h about/aboutdialog.cpp
    address/addressmodel.h address/addressmodel.cpp
    customers/customerform.h customers/customerform.cpp
    customers/customerframe.h customers/customerframe.cpp
    customers/customermodel.h customers/customermodel.cpp
    customers/customerrepository.h customers/customerrepository.cpp
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
    staff/resetform.h staff/resetform.cpp
    staff/staffform.h staff/staffform.cpp
    staff/staffframe.h staff/staffframe.cpp
    staff/staffmodel.h staff/staffmodel.cpp
    staff/staffrepository.h staff/staffrepository.cpp
    tasks/taskmodel.h tasks/taskmodel.cpp
    tasks/taskrepository.h tasks/taskrepository.cpp
    tasks/taskform.h tasks/taskform.cpp
    tasks/taskframe.h tasks/taskframe.cpp
    tasktimer/tasktimermodel.h tasktimer/tasktimermodel.cpp
    tasktimer/tasktimerrepository.h tasktimer/tasktimerrepository.cpp
    teams/teamform.h teams/teamform.cpp
    teams/teamframe.h teams/teamframe.cpp
    teams/teammodel.h teams/teammodel.cpp
    teams/teamrepository.h teams/teamrepository.cpp
    users/loginform.h users/loginform.cpp
    users/usermodel.h users/usermodel.cpp
    users/userrepository.h users/userrepository.cpp 
    users/userutils.h users/userutils.cpp   
)

target_link_libraries(studio
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        mysqlclient
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
