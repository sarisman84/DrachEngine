-- Directories
directory = {}

directory["solution"] = os.realpath("../")
directory["engine"] = os.realpath(directory.solution .. "/engine/")
directory["launcher"] = os.realpath(directory.solution .. "/launcher/")
directory["editor"] = os.realpath(directory.solution .. "/editor/")



directory["engine_vendor"] = directory.engine .. "vendor/"
directory["editor_vendor"] = directory.editor .. "vendor/"
directory["global_vendor"] = os.realpath(directory.solution .. "vendor/")

directory["output"] = os.realpath(directory.solution .. "/bin/")
directory["resources"] = directory.output .. "resources/"
directory["engineOutput"] = directory.output .. "engine/"
directory["editorOutput"] = directory.output .. "editor/"
directory["shaderOutput"] = directory.resources .. "shaders/"
directory["tempOutput"] = os.realpath(directory.solution .. "/temp/")
directory["workingDirectory"] = directory.output

directory["engine_lib"] = os.realpath(directory.engineOutput .. "lib/")
directory["editor_lib"] = os.realpath(directory.editorOutput .. "lib/")
directory["global_lib"] = os.realpath(directory.output .. "lib/")

-- Helper methods
function fetchVendorInclude(src)
    removefiles {
        src .. "nlohmann/include/**",
        src .. "nlohmann/tests/**",
        src .. "nlohmann/tools/**",
        src .. "nlohmann/docs/**",
        src .. "imguizmo/example/**",
        src .. "imguizmo/vcpkg-example/**",
        src .. "imgui/examples/**",
        src .. "imgui/backends/**",
        src .. "imnodes/example/**",
        src .. "imnodes/img/**",
        src .. "imnodes/vcpkg/**",
        src .. "imnodes/.github/**",
        src .. "entt/src/**",
        src .. "entt/test/**",
        src .. "entt/conan/**"
    }
    files {
        src .. "imgui/backends/imgui_impl_dx11.**",
        src .. "imgui/backends/imgui_impl_win32.**"
    }
end

function includeEntt(aDirectory)

    

    includedirs {
        aDirectory .. "entt\\single_include\\entt\\"
    }
    removefiles {
        -- aDirectory .. "entt/build/**",
        -- aDirectory .. "entt/cmake/**",
        -- aDirectory .. "entt/conan/**",
        -- aDirectory .. "entt/docs/**",
        -- aDirectory .. "entt/natvis/**",
        -- aDirectory .. "entt/scripts/**",
        -- aDirectory .. "entt/src/**",
        -- aDirectory .. "entt/test/**",
        aDirectory .. "entt/**"
    }
    files {
        aDirectory .. "entt/single_include/entt/*.hpp"
    }

    print("---Imported ENTT!")
end

function includeImgui(aDirectory)

    files {
        aDirectory .. "imgui/*.h",
        aDirectory .. "imgui/*.hpp",
        aDirectory .. "imgui/*.c",
        aDirectory .. "imgui/*.cpp",

        aDirectory .. "imguizmo/*.h",
        aDirectory .. "imguizmo/*.hpp",
        aDirectory .. "imguizmo/*.c",
        aDirectory .. "imguizmo/*.cpp",

        aDirectory .. "imnodes/*.h",
        aDirectory .. "imnodes/*.hpp",
        aDirectory .. "imnodes/*.c",
        aDirectory .. "imnodes/*.cpp"
    }
    includedirs {
        aDirectory .. "imgui/",
        aDirectory .. "imguizmo/",
        aDirectory .. "imnodes/"
    }

    removefiles {
        aDirectory .. "imguizmo/example/**",
        aDirectory .. "imguizmo/vcpkg-example/**",
        aDirectory .. "imgui/examples/**",
        aDirectory .. "imgui/backends/**",
        aDirectory .. "imnodes/example/**",
        aDirectory .. "imnodes/img/**",
        aDirectory .. "imnodes/vcpkg/**",
        aDirectory .. "imnodes/.github/**"
    }

    files {
        aDirectory .. "imgui/backends/imgui_impl_dx11.**",
        aDirectory .. "imgui/backends/imgui_impl_win32.**"
    }

    print("---Imported Imgui, ImGuizmo and Imnodes!")
end

function includeNlohmann(aDirectory)
    includedirs {
        aDirectory .. "nlohmann/"
    }
    removefiles {
        aDirectory .. "nlohmann\\include\\**",
        aDirectory .. "nlohmann\\tests\\**",
        aDirectory .. "nlohmann\\tools\\**",
        aDirectory .. "nlohmann\\docs\\**",
        aDirectory .. "nlohmann\\single_include\\nlohmann\\json_fwd.hpp"
    }

    print("---Imported Nlohmann's Json Library!")
end

function includeDirectXTex(aDirectory)

    includedirs {
        aDirectory .. "DirectXTex/"
    }
   
    removefiles {
        aDirectory .. "DirectXTex\\DirectXTex\\**",
        aDirectory .. "DirectXTex\\DDSView\\**",
        aDirectory .. "DirectXTex\\Texassemble\\**",
        aDirectory .. "DirectXTex\\Texconv\\**",
        aDirectory .. "DirectXTex\\Texdiag\\**",
        aDirectory .. "DirectXTex\\DDSTextureLoader\\DDSTextureLoader9.**",
        aDirectory .. "DirectXTex\\DDSTextureLoader\\DDSTextureLoader12.**",
        aDirectory .. "DirectXTex\\ScreenGrab\\ScreenGrab9.**",
        aDirectory .. "DirectXTex\\ScreenGrab\\ScreenGrab12.**",
        aDirectory .. "DirectXTex\\WICTextureLoader\\WICTextureLoader9.**",
        aDirectory .. "DirectXTex\\WICTextureLoader\\WICTextureLoader12.**"
    }

    print("---Imported DirectXTex!")
end

function includeFreeType(aDirectory)
    includedirs {
        aDirectory .. "freetype_**/include/"
    }
    print("---Imported Free Type!")

end

function beginInclude(aDirectory)
    files 
    {
        aDirectory .. "**.h",
        aDirectory .. "**.hpp",
        aDirectory .. "**.c",
        aDirectory .. "**.cpp"
    }

    includedirs(aDirectory)
end

