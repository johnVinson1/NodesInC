cmake_minimum_required(VERSION 3.10)
project(Node C)
add_executable(Node node.cxx)

configure_file(src/headers/node.h.in node.h)
target_include_directories(
		Node PUBLIC
		"${PROJECT_BINARY_DIR}"
	)

