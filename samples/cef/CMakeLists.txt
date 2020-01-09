include_directories(src)
add_executable(cef
    src/main.cpp
    src/web_view.cpp
    ${CEF_CMAKE_EXECUTABLE_RESOURCES}
)
target_link_libraries(cef gl cefdll_wrapper)
