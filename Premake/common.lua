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
    files {
        aDirectory .. "**.h",
        aDirectory .. "**.hpp",
        aDirectory .. "**.c",
        aDirectory .. "**.cpp"
    }

    includedirs(aDirectory)
end

function precompileHeader(precompileHeaderName, projectDir)
    print("Assigning precompile header and source files")

    local precompileHeaderDir = projectDir .. "source/precompile-header"

    if not os.isdir(precompileHeaderDir) then
        os.mkdir(precompileHeaderDir)
    end

    local hFile = precompileHeaderDir .. "/" .. precompileHeaderName .. ".h"
    local cppFile = precompileHeaderDir .. "/" .. precompileHeaderName .. ".cpp"

    if os.isfile(hFile) then
        os.remove(hFile)
        print("---Found previous precompile header file: removing")
    end

    if os.isfile(cppFile) then
        os.remove(cppFile)
        print("---Found previous source file: removing!")
    end

    print("---Generating header and source files")

    local hF = io.open(hFile, "w")

    hF:write("#pragma once\n\n")
    hF:write("#include <iostream>\n")
    hF:write("#include <string>\n")
    hF:write("#include <vector>\n")
    hF:write("#include <unordered_map>\n")

    local vendorDir = directory.global_vendor .. "source/"

    if os.isdir(vendorDir .. "entt/") then
        print("---External ENTT project found! Adding include to precompile header!")
        hF:write("#include \"entt/single_include/entt/entt.hpp\"")
    end
    hF:close()

    local cppF = io.open(cppFile, "w")
    cppF:write("#include \"precompile-header/" .. precompileHeaderName .. ".h\"\n\n")
    cppF:close()

    local hFileIncludePath = "precompile-header/" .. precompileHeaderName .. ".h"
    local cppFileIncludePath = "precompile-header/" .. precompileHeaderName .. ".cpp"

    pchheader(hFileIncludePath)
    pchsource(cppFile)

    -- pchdir(path.join(directory.resources, "pch", "%{prj.name}-%{cfg.buildcfg}.pch"))
    -- precompiledheader(hFileIncludePath, cppFileIncludePath)
    buildoptions {
        "/Yc" .. cppFileIncludePath
    }

    print("Precompile header and source files generated!")

    updateSourceFiles(precompileHeaderName, projectDir .. "source/")
end

function trim(s)
    return (s:gsub("^%s*(.-)%s*$", "%1"))
end

function updateSourceFiles(precompileHeaderName, projectDir)
    local header = "#include \"" .. "precompile-header/" .. precompileHeaderName .. ".h\""
    print("Updating source files to include the precompiled header!")
    local cppFiles = os.matchfiles(projectDir .. "/**.cpp")
    for i, file in ipairs(cppFiles) do

        if file:find(precompileHeaderName .. ".cpp") then
            goto continue
        end

        local f = io.open(file, "r")
        local content = f:read("*all")
        f:close()
        local contentCheck = trim(content)
        local trimmedHeader = trim(header)

        local pattern = header
        local attempts = 10
        while content:find(pattern, attempts, true) and attempts > 0 do
            print("---Removing duplicate header in file: " .. file)
            local newContent = string.gsub(content, header, "")
            f = io.open(file, "w")
            f:write(newContent)
            f:close()
            attempts = attempts - 1
        end

        if not content:find(pattern, 1, true) then
            content = header .. "\n" .. content
            f = io.open(file, "w")
            f:write(content)
            f:close()
            print("---Added precompiled header include to " .. file)
        end
        ::continue::
    end
    print("Finished updating source files!")
end
