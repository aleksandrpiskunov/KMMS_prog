target_sources(${PROJECT_NAME}
	PRIVATE
		collisionable.cpp
		game_map.cpp
		movable.cpp
		rect.cpp
		rect_map_movable_adapter.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
