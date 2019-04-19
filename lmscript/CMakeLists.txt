cmake_minimum_required(VERSION 2.8)

project(lmscript)

LIST(APPEND script_files
    example.lms
    lms.xml
    syslex.py)

add_custom_target(script ALL SOURCES  ${script_files})

