echo "This script is going to call premake now. Make sure that premake5 and make are installed on your device."
premake5 gmake2
echo "Building binaries..."
make
