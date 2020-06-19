#Build script

#Build Dependencies
./scripts/build_deps.sh

#Build InfinitRight
echo "Building InfinitRight"
mkdir build
cd build
cmake ..
make