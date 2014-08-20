/**
 * This example implements a simple, not performance-optimized, 2D
 * smoother on a regular grid with constant boundary conditions.
 */

#include <iostream>
#include <libgeodecomp.h>

using namespace LibGeoDecomp;

/**
 * The simulation model: one double value per cell, values will be set
 * to the average of their neighbors (up, left, right, down).
 */
class Cell
{
public:
    inline Cell(const double value = 0) :
        value(value)
    {}

    template<typename NEIGHBORHOOD>
    inline void update(const NEIGHBORHOOD& hood, int nanoStep)
    {
        value = (hood[Coord<2>( 0, -1)].value +
                 hood[Coord<2>(-1,  0)].value +
                 hood[Coord<2>( 1,  0)].value +
                 hood[Coord<2>( 0,  1)].value) * 0.25;
    }

    double value;
};

/**
 * The initializer will set up the grid, in this case with arbitraty values:
 */
class CellInitializer : public SimpleInitializer<Cell>
{
public:
    CellInitializer(const Coord<2>& dim, const int maxSteps) :
        SimpleInitializer<Cell>(dim, maxSteps)
    {}

    virtual void grid(GridBase<Cell, 2> *target)
    {
        CoordBox<2> box = target->boundingBox();

        for (CoordBox<2>::Iterator i = box.begin(); i != box.end(); ++i) {
            Cell cell(i->x() * i->y() + 47.11);
            target->set(*i, cell);
        }
    }
};

int main(int argc, char **argv)
{
    // create a 100x50 grid and run for 200 time steps:
    Coord<2> gridDimensions(100, 50);
    int maxSteps = 200;

    // this is the equivalent of a "Hello World", so we won't be using
    // any sophisticated simulator, just the very most simple one:
    SerialSimulator<Cell> sim(new CellInitializer(gridDimensions, maxSteps));

    // add output components:
    sim.addWriter(new TracingWriter<Cell>());
    sim.addWriter(new PPMWriter<Cell>(&Cell::value, 0.0, 10000.0, "smoother"));

    // start the simulation:
    sim.run();

    return 0;
}
