
my_build=build

if [ ! -d "$my_build" ]; then
    mkdir $my_build
fi

cd $my_build

qmake ../Match3Model
make

qmake ../Match3
make

./Match3
