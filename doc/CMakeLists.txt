cmake_minimum_required(VERSION 2.8)

project(doc)

LIST(APPEND doc_files
    lmlab-design.tex)

add_custom_target(doc ALL SOURCES  ${doc_files})

