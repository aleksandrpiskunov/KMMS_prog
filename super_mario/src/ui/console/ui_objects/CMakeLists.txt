target_sources(${PROJECT_NAME}
	PRIVATE
		console_box.cpp
		console_enemy.cpp
		console_full_box.cpp
		console_mario.cpp
		console_money.cpp
		console_ship.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
