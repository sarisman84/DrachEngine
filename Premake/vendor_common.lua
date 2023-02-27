include "common.lua"

function importNlohmann(projectDir)
    local message = "--Importing Nlohmann"
    local nlohmannDir = projectDir .. "nlohmann/"
    if readSettings().use_single_include then
        message = message .. " as SINGLE_INCLUDE"
        files {
            nlohmannDir .. "single_include/nlohmann/*"
        }

    else
        message = message .. " as NORMAL"
        files {
            nlohmannDir .. "include/nlohmann/*"
        }

    end
    print(message)
end

function importEntt(projectDir)
    local message = "--Importing ENTT"
    local enttDir = projectDir .. "entt/"

    if readSettings().use_single_include then
        files {
            enttDir .. "single_include/**.hpp",
            enttDir .. "single_include/**.h"
        }
        message = message .. " as SINGLE_INCLUDE"

    else
        files {
            enttDir .. "**.h",
            enttDir .. "**.hpp",
            enttDir .. "**.c",
            enttDir .. "**.cpp"
        }
        message = message .. " as NORMAL"

    end
    print(message)
end

function importFBXSDK(projectDir)
    local message = "--Importing Autodesk FBX - SDK"
    local fbxSDKDir = projectDir .. "fbx_sdk/"

    files {
        fbxSDKDir .. "2020.3.2/**.h",
        fbxSDKDir .. "2020.3.2/**.cpp",
        fbxSDKDir .. "2020.3.2/**.cxx"
    }

    -- libdirs {
    --     fbxSDKDir .. "2020.3.2/lib/vs2019/x64/debug"
    -- }

    -- links {
    --     "libfbxsdk-md",
    --     "libxml2-md",
    --     "zlib-md"
    -- }

    message = message .. " as NORMAL"
    print(message)
end

function includeFBXSDK(projectDir)

    local originalScope
    local fbxSDKDir = projectDir .. "fbx_sdk/"

    print("--Included FBX SDK")

    includedirs {
        os.realpath(fbxSDKDir .. "2020.3.2/include")
    }

    -- filter "system:windows"
    -- buildoptions "/MD"
    -- filter {}

end

function includeEntt(projectDir)
    local enttDir = projectDir .. "entt/"
    if readSettings().use_single_include then
        includedirs {
            enttDir .. "single_include/"
        }
    else
        includedirs {
            enttDir .. "src/"
        }
    end
    print("--Included ENTT")
end

function includeNlohmann(projectDir)
    local nlohmannDir = projectDir .. "nlohmann/"
    if readSettings().use_single_include then
        includedirs {
            nlohmannDir .. "single_include/"
        }
    else
        includedirs {
            nlohmannDir .. "include/"
        }
    end

    print("--Included Nlohmann")
end
-- External Libraries
importLibrary = {}
importLibrary[os.realpath(directory.global_vendor .. "source/entt")] = importEntt
importLibrary[os.realpath(directory.global_vendor .. "source/nlohmann")] = importNlohmann
importLibrary[os.realpath(directory.global_vendor .. "source/fbx_sdk")] = importFBXSDK

-- External Includes
includeLibrary = {}
includeLibrary[os.realpath(directory.global_vendor .. "source/entt")] = includeEntt
includeLibrary[os.realpath(directory.global_vendor .. "source/nlohmann")] = includeNlohmann
includeLibrary[os.realpath(directory.global_vendor .. "source/fbx_sdk")] = includeFBXSDK

function importLibraries(projectDir)

    local directories = os.matchdirs(projectDir .. "*")

    for i, directory in ipairs(directories) do
        if importLibrary[os.realpath(directory)] ~= nil then
            importLibrary[os.realpath(directory)](projectDir)
        end
    end

end

function includeLibraries(projectDir)
    local directories = os.matchdirs(projectDir .. "*")

    for i, directory in ipairs(directories) do
        if includeLibrary[os.realpath(directory)] ~= nil then
            includeLibrary[os.realpath(directory)](projectDir)
        end
    end
end
