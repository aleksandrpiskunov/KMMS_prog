target_sources(${PROJECT_NAME}
	PRIVATE
		app_factory.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(console)
if(GAME_TYPE STREQUAL "Qt")
	add_subdirectory(qt)
endif()
