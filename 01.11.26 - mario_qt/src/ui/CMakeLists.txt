add_subdirectory(console)
if(GAME_TYPE STREQUAL "Qt")
	add_subdirectory(qt)
endif()
