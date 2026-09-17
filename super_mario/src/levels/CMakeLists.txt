target_sources(${PROJECT_NAME}
	PRIVATE
		first_level.cpp
		game_level.cpp
		second_level.cpp
		third_level.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
