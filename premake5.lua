workspace "AltEngine"
   configurations { "Debug", "Release" }

   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AltEngine"
   kind "ConsoleApp"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "on"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "on"
