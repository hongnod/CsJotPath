list(APPEND JOTP_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/jotmainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/jotstatusbar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/defs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mainmenu.h


)

list(APPEND JOTP_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/jotmainwindow.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/jotstatusbar.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/mainmenu.cpp
   qrc_jotpath.cpp
)

include(database/database.cmake)
include(JotNaviView/jotnaviview.cmake)
include(JotDataView/jotdataview.cmake)
include(JotSideBar/jotsidebar.cmake)
include(utils/utils.cmake)

#set(RESOURCES
#    ../JotPath.qrc
#)
# run lrelease to generate translation files
#COPPERSPICE_RESOURCES(
#   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_en.ts
#   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_de.ts
#   ${CMAKE_CURRENT_SOURCE_DIR}/../resources/qt_fr.ts
#)

# run rcc to generate qrc output
COPPERSPICE_RESOURCES(
   ${CMAKE_CURRENT_SOURCE_DIR}/../JotPath.qrc
)

# run uic to generate source
#COPPERSPICE_RESOURCES(
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/mainwindow.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/chat_dialog.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/colorpicker.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/fontpicker.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/dialogs.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/html_viewer.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/international.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/line_edit.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/listview.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/musicplayer.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_cert.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_client.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/ssl_error.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/stdpath.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/style_dw.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/style_edit.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/script.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/tabdialog.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/tablewidget_view.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/xml.ui
#   ${CMAKE_CURRENT_SOURCE_DIR}/../forms/xmlpatterns.ui
#)



add_executable(JotPath  ${JOTP_INCS} ${JOTP_SRCS} ../JotPath.rc)

target_include_directories(JotPath
   PRIVATE
   ${CMAKE_SOURCE_DIR}/src
   ${CMAKE_CURRENT_SOURCE_DIR}/database
   ${CMAKE_CURRENT_SOURCE_DIR}/JotNaviView
   ${CMAKE_CURRENT_SOURCE_DIR}/JotDataView
   ${CMAKE_CURRENT_SOURCE_DIR}/JotSideBar
   ${CMAKE_CURRENT_SOURCE_DIR}/utils
)


target_link_libraries(JotPath
    CopperSpice::CsCore
    CopperSpice::CsGui
    CopperSpice::CsNetwork
    CopperSpice::CsOpenGL
    #CopperSpice::CsScript
    CopperSpice::CsSql
    CopperSpice::CsSvg
    CopperSpice::CsXml
    CopperSpice::CsXmlPatterns
)

#for future usage
#if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
#   target_link_libraries(JotPath CopperSpice::CsMultimedia
#)
#endif()
#
#if("WebKit" IN_LIST COPPERSPICE_COMPONENTS)
#   target_link_libraries(JotPath CopperSpice::CsWebKit
#)
#endif()
 
 
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
   set_target_properties(JotPath PROPERTIES OUTPUT_NAME JotPath)
   target_link_libraries(JotPath
      "-framework OpenGL"
   )

elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD|NetBSD|DragonFly)")
   set_target_properties(JotPath PROPERTIES OUTPUT_NAME JotPath)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
   # disable console on windows
     if(MSVC)
      set_target_properties(${PROJECT_NAME} PROPERTIES
                                          WIN32_EXECUTABLE YES
                                          LINK_FLAGS "/ENTRY:mainCRTStartup"
                )
           elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_link_libraries(JotPath
                               netapi32
                                                           mpr
                                                           -mwindows
                                                           )
       else()
                    message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
          endif(MSVC)
endif()
 
