# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

target_sources(app PRIVATE
    src/main.c
    src/static_resources.c
)

# Include custom iterable section for HTTP resources
zephyr_linker_sources(SECTIONS http_iterables.ld)

zephyr_linker_section(NAME
    http_resource_desc_http_service
    KVMA RAM_REGION GROUP RODATA_REGION
    SUBALIGN ${CONFIG_LINKER_ITERABLE_SUBALIGN}
)

# Collect all files used by the frontend build process
# (may need to be updated if any image assets are added)
file(GLOB_RECURSE FRONTEND_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.js
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.jsx
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.html
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.css
)

# Exclusions from glob pattern above
list(FILTER FRONTEND_SOURCES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/frontend/node_modules/.*)
list(FILTER FRONTEND_SOURCES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/frontend/dist/.*)

set(FRONTEND_BUILD_OUTPUTS
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/dist/index.html
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/dist/assets/index.js
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/dist/assets/index.css
)

# Custom command for the frontend build
add_custom_command(
    OUTPUT ${FRONTEND_BUILD_OUTPUTS}
    COMMAND npm run build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/frontend
    DEPENDS ${FRONTEND_SOURCES}
    COMMENT "Running frontend build"
    VERBATIM
)

# Custom target for the frontend build
add_custom_target(frontend_build
    DEPENDS ${FRONTEND_BUILD_OUTPUTS}
)

# App build depends on the frontend build
add_dependencies(app frontend_build)

# Generate gzipped static resources
set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

foreach(web_resource
    index.html
    assets/index.js
    assets/index.css
)
    generate_inc_file_for_target(
        app
        frontend/dist/${web_resource}
        ${gen_dir}/${web_resource}.gz.inc
        --gzip
    )
endforeach()
