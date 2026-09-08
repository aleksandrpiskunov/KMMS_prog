target_sources(${PROJECT_NAME}
	PRIVATE
		console_game_map.cpp
		console_ui_factory.cpp
		console_ui_obj_rect_adapter.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(ui_objects)
