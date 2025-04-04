#include <nanobind/nanobind.h>

#include "routing.h"


NB_MODULE(routing, m) {

  namespace nb = nanobind;

  nb::class_<Routing>(m, "routing")
    .def(nb::init<const std::string &, const std::string&, const std::string&, const std::string&>())
    .def("distance", &Routing::distance)
    .def("route", &Routing::route);

  nb::enum_<Routing::Mode>(m, "Mode")
    .value("Car", Routing::Mode::car)
    .value("Bike", Routing::Mode::bike)
    .value("Foot", Routing::Mode::foot)
    .value("Train", Routing::Mode::train)
    .export_values();
}
