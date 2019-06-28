workspace "AltEngine"
	architecture "x64"
	configurations { "Debug", "Release" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "AltEngine/vendor/GLFW/include"
	IncludeDir["Glad"] = "AltEngine/vendor/Glad/include"
	IncludeDir["glm"] = "AltEngine/vendor/glm"

	include "AltEngine/vendor/GLFW"
	include "AltEngine/vendor/Glad"

project "AltEngine"
	location "AltEngine"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	systemversion "latest"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/vendor/glad/src",
		"%{prj.name}/vendor/glfw/include",
		"%{prj.name}/vendor/glfw/src",
		"%{prj.name}/vendor/opengl3/include",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"
