set_project("libBG")
set_xmakever("2.1.3")

-- default global options for each targets
set_languages("c99","cxx98")
set_warnings("all")
add_includedirs("$(buildir)")

if is_mode("release") then
    set_optimize("aggressive")

elseif is_mode("debug") then
    set_optimize("fast")
    set_symbols("debug")

elseif is_mode("coverage") then
    set_optimize("fast")
    add_cxflags("-coverage")
    add_ldflags("-coverage")
end

target("bg")  -- main target
    set_kind("$(kind)")
    add_files("src/bigint.cpp")
    add_headers("src/bigint.h")
    add_defines("BIGINT_FFT_TRIGGER=0x1000000")
target_end()

function maketest(op)  -- test targets
    target("testprog" .. op)
        set_default(false)
        add_deps("bg")
        set_kind("binary")

        add_files("test/b" .. op .. ".cpp")
        add_links("bg")
        add_linkdirs("$(buildir)")
    target_end()
end

maketest("add")
maketest("sub")
maketest("mul")
maketest("div")
maketest("mod")
