#
#	- Если я подключу format.cpp в target_sources, то что будет?
#

target_sources(${PROJECT_NAME}
	PRIVATE
		format_templates.cpp
		logger.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
