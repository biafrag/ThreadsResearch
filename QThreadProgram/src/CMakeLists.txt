target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
	        #Q_OBJECT Classes
        ${CMAKE_INCLUDE_PATH}/mainwindow.h
)