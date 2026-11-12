target_sources(${PROJECT_NAME}
	PRIVATE
		linux_control_settings.cpp
		linux_keyboard.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
