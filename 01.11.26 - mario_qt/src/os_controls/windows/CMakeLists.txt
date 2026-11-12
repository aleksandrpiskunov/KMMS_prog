target_sources(${PROJECT_NAME}
	PRIVATE
		windows_control_settings.cpp
		windows_keyboard.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
