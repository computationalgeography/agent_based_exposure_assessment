#include "osrm/match_parameters.hpp"
#include "osrm/nearest_parameters.hpp"
#include "osrm/route_parameters.hpp"
#include "osrm/table_parameters.hpp"
#include "osrm/trip_parameters.hpp"

#include "osrm/coordinate.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/json_container.hpp"

#include "osrm/osrm.hpp"
#include "osrm/status.hpp"

#include <nanobind/nanobind.h>

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include <cstdlib>
#include <iomanip>
#include <string>

#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/pair.h>


class Routing
{
public:

  enum Mode {
    car = 0,
    bike = 1,
    foot = 2,
    train = 3
  };

  Routing(const std::string& car, const std::string& bike, const std::string& foot, const std::string& train);

  // Returns travel distance in metres and duration in minutes
  nanobind::tuple distance(double source_x, double source_y, double dest_x, double dest_y, const Mode& travel_type);

  // Returns coordinate pairs of the route
  std::vector<std::pair<double, double>> route(double source_x, double source_y, double dest_x, double dest_y, const Mode& travel_type);

private:
  std::unique_ptr<osrm::OSRM> osrm_car;
  std::unique_ptr<osrm::OSRM> osrm_bike;
  std::unique_ptr<osrm::OSRM> osrm_foot;
  std::unique_ptr<osrm::OSRM> osrm_train;
};
