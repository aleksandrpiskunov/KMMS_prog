target_sources(${PROJECT_NAME}
	PRIVATE
		qt_game_map.cpp
		qt_keyboard.cpp
		qt_ui_factory.cpp
		qt_resources.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
)
