set_project("libBG")

function housekeeping()  -- default options
    set_languages("c99","cxx98")
    set_warnings("all")
    add_includedirs("$(buildir)")

    if is_mode("release") then
        add_cxflags("-march=native")
        set_optimize("fastest")

    elseif is_mode("debug") then
        set_optimize("fast")
        set_symbols("debug")
    end
end

target("bg")  -- main target
    housekeeping()
    set_kind("$(kind)")

    add_files("src/bigint.cpp")
    add_headers("src/bigint.h")

    add_defines("BIGINT_FFT_TRIGGER=0x1000000")
    add_cxflags("-ffast-math")
    if is_mode("release") then add_cxxflags("-fno-rtti") end
target_end()

function maketest(op)  -- test targets
    target("testprog" .. op)
        add_deps("bg")
        housekeeping()
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
