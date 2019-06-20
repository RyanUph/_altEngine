workspace "AltEngine"
	architecture "x86"
	architecture "x64"
	configurations { "Debug", "Release" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AltEngine"
	location "AltEngine"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	systemversion "latest"
	
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "on"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"
