# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

target_sources(app PRIVATE src/main.c)

# Include custom iterable section for HTTP resources
zephyr_linker_sources(SECTIONS http_iterables.ld)

zephyr_linker_section(NAME
    http_resource_desc_http_service
    KVMA RAM_REGION GROUP RODATA_REGION
    SUBALIGN ${CONFIG_LINKER_ITERABLE_SUBALIGN}
)

# Generate gzipped static resources
set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

foreach(web_resource
    index.html
)
    generate_inc_file_for_target(
        app
        src/static/${web_resource}
        ${gen_dir}/${web_resource}.gz.inc
        --gzip
    )
endforeach()
