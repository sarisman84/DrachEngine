include "../Premake/vendor_common.lua"

local source = os.realpath(directory.editor_vendor .. "source/")

local foundFiles = os.matchfiles(os.realpath(source .. "/*"))
local foundDirectories = os.matchdirs(os.realpath(source .. "/*"))
if #foundFiles > 0 or #foundDirectories > 0 then

    print("Bulding Vendor for Editor")
    group("Editor")
    project "Vendor[Editor]"
    location "."
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    output = "%{cfg.buildcfg}"
    solutionDir = ("%{wks.location}" .. "/")
    prjName = "%{prj.name}"

    targetdir(directory.editor_lib)
    objdir(directory.tempOutput .. prjName)
    debugdir(directory.editor_lib)

    targetname("%{prj.name}_%{cfg.buildcfg}")
    files {
        source .. "**.h",
        source .. "**.hpp",
        source .. "**.c",
        source .. "**.cpp",
        source .. "../util/vcpkg/packages/freetype_**/include/"
    }

    fetchVendorInclude(source)

    excludes {
        "ffmpeg-2.0/**.h",
        "ffmpeg-2.0/**.c",
        "ffmpeg-2.0/**.cpp",
        "DirectXTex/DirectXTex/**",
        "DirectXTex/DDSView/**",
        "DirectXTex/Texassemble/**",
        "DirectXTex/Texconv/**",
        "DirectXTex/Texdiag/**",
        "DirectXTex/DDSTextureLoader/DDSTextureLoader9.**",
        "DirectXTex/DDSTextureLoader/DDSTextureLoader12.**",
        "DirectXTex/ScreenGrab/ScreenGrab9.**",
        "DirectXTex/ScreenGrab/ScreenGrab12.**",
        "DirectXTex/WICTextureLoader/WICTextureLoader9.**",
        "DirectXTex/WICTextureLoader/WICTextureLoader12.**"
    }

    includedirs {
        ".",
        source,
        source .. "nlohmann/",
        source .. "imgui/",
        source .. "imguizmo/"
    }

    includeLibraries(directory.global_vendor .. "source/")

    libdirs {
        directory.editor_lib,
        source .. "../util/vcpkg/packages/freetype_**/lib/"
    }

    defines {
        "_CONSOLE"
    }

    filter "configurations:Debug"
    defines {
        "_DEBUG"
    }
    runtime "Debug"
    symbols "on"
    filter "configurations:Release"
    defines "_RELEASE"
    runtime "Release"
    optimize "on"
    filter "configurations:Retail"
    defines "_RETAIL"
    runtime "Release"
    optimize "on"

    filter "system:windows"
    kind "StaticLib"
    staticruntime "off"
    symbols "On"
    systemversion "latest"
    -- warnings "Extra"
    -- conformanceMode "On"
    -- buildoptions { "/permissive" }
    flags { --	"FatalWarnings", -- would be both compile and lib, the original didn't set lib
        --	"FatalCompileWarnings",
        "MultiProcessorCompile"
    }
    links {
        "DXGI",
        "dxguid"
    }
    defines {
        "_WIN32_WINNT=0x0601"
    }

else
    print("No Vendor Libraries found: Skipping building vendor for editor!")
end
