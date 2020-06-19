#Build Deps

cd ..
#Build Gravity
if [ ! -f "/gravity/build/libgravityapi_s.a" ] 
then
    if [ ! -d "/gravity/" ] 
    then
        git clone https://github.com/marcobambini/gravity.git
        cd gravity
    else
        cd gravity
    fi
    mkdir build
fi

cd build
cmake ..
make