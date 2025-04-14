#include "routing.h"

#include "osrm/route_parameters.hpp"
#include "osrm/coordinate.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/json_container.hpp"
#include "osrm/osrm.hpp"
#include "osrm/status.hpp"
#include "engine/polyline_compressor.hpp"

#include <cmath>
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include <cstdlib>
#include <iomanip>
#include <string>


using namespace osrm;

typedef std::vector<std::pair<double, double>> result_vector;


Routing::Routing(const std::string& car, const std::string& bike, const std::string& foot, const std::string& train){

  EngineConfig config_car;
  config_car.storage_config = {car.c_str()};
  config_car.use_shared_memory = false;
  config_car.algorithm = EngineConfig::Algorithm::MLD;

  EngineConfig config_bike;
  config_bike.storage_config = {bike.c_str()};
  config_bike.use_shared_memory = false;
  config_bike.algorithm = EngineConfig::Algorithm::MLD;

  EngineConfig config_foot;
  config_foot.storage_config = {foot.c_str()};
  config_foot.use_shared_memory = false;
  config_foot.algorithm = EngineConfig::Algorithm::MLD;

  EngineConfig config_train;
  config_train.storage_config = {train.c_str()};
  config_train.use_shared_memory = false;
  config_train.algorithm = EngineConfig::Algorithm::MLD;

  osrm_car = std::make_unique<OSRM>(config_car);
  osrm_bike = std::make_unique<OSRM>(config_bike);
  osrm_foot = std::make_unique<OSRM>(config_foot);
  osrm_train = std::make_unique<OSRM>(config_train);
}


nanobind::tuple Routing::distance(double source_x, double source_y, double dest_x, double dest_y, const Mode& travel_type){

  RouteParameters params;
  params.steps = false;
  params.alternatives = false;
  params.overview = RouteParameters::OverviewType::False;
  params.geometries = RouteParameters::GeometriesType::Polyline;
  params.coordinates.push_back({util::FloatLongitude{source_x}, util::FloatLatitude{source_y}});
  params.coordinates.push_back({util::FloatLongitude{dest_x}, util::FloatLatitude{dest_y}});

  engine::api::ResultT result = json::Object();

  auto status = Status::Error;

  if (travel_type == Routing::Mode::car){
    status = osrm_car->Route(params, result);
  }
  else if(travel_type == Routing::Mode::bike){
    status = osrm_bike->Route(params, result);
  }
  else if(travel_type == Routing::Mode::foot){
    status = osrm_foot->Route(params, result);
  }
  else if(travel_type == Routing::Mode::train){
    status = osrm_train->Route(params, result);
  }
  else{
    std::cerr << "wrong travel type " << travel_type << "\n";
    exit(1);
  }

  auto &json_result = std::get<json::Object>(result);

  if (status == Status::Ok){
    auto &routes = std::get<json::Array>(json_result.values["routes"]);
    auto &route = std::get<json::Object>(routes.values.at(0));

    // We return duration in minutes as this is our delta_t
    auto duration_in_s = std::get<json::Number>(route.values["duration"]).value;
    std::chrono::hh_mm_ss time{std::chrono::seconds(static_cast<int>(std::ceil(duration_in_s)))};
    auto minutes = 60 * time.hours().count() + time.minutes().count();
    if(time.seconds().count() > 0){
      minutes += 1;
    }
    return nanobind::make_tuple(std::get<json::Number>(route.values["duration"]).value, minutes);
  }
  else{
    const auto code = std::get<json::String>(json_result.values["code"]).value;
    const auto message = std::get<json::String>(json_result.values["message"]).value;

    std::cerr << "Code: " << code << "\n";
    std::cerr << "Message: " << message << "\n";
    return nanobind::make_tuple(-1, -1);
  }
}


result_vector Routing::route(double source_x, double source_y, double dest_x, double dest_y, const Mode& travel_type){

  RouteParameters params;
  params.steps = false;
  params.alternatives = false;
  params.overview = RouteParameters::OverviewType::Full;
  params.geometries = RouteParameters::GeometriesType::GeoJSON;
  params.coordinates.push_back({util::FloatLongitude{source_x}, util::FloatLatitude{source_y}});
  params.coordinates.push_back({util::FloatLongitude{dest_x}, util::FloatLatitude{dest_y}});

  engine::api::ResultT result = json::Object();

  auto status = Status::Error;

  if (travel_type == Routing::Mode::car){
    status = osrm_car->Route(params, result);
  }
  else if(travel_type == Routing::Mode::bike){
    status = osrm_bike->Route(params, result);
  }
  else if(travel_type == Routing::Mode::foot){
    status = osrm_foot->Route(params, result);
  }
  else if(travel_type == Routing::Mode::train){
    status = osrm_train->Route(params, result);
  }
  else{
    std::cerr << "wrong travel type " << travel_type << "\n";
    exit(1);
  }

  auto &json_result = std::get<json::Object>(result);

  result_vector result_coords;

  if (status == Status::Ok){
    auto &routes = std::get<json::Array>(json_result.values["routes"]);
    auto &route = std::get<json::Object>(routes.values.at(0));

    const auto geometry = std::get<json::Object>(route.values.at("geometry")).values["coordinates"];
    const auto coordinates = std::get<json::Array>(geometry).values;

    for (size_t i = 0; i < coordinates.size(); i++){
      const auto location = std::get<json::Array>(coordinates.at(i)).values;
      const auto x = std::get<json::Number>(location[0]).value;
      const auto y = std::get<json::Number>(location[1]).value;

      result_coords.emplace_back(std::make_pair(x, y));
    }
    return result_coords;
  }
  else{
    const auto code = std::get<json::String>(json_result.values["code"]).value;
    const auto message = std::get<json::String>(json_result.values["message"]).value;

    std::cerr << "Code: " << code << "\n";
    std::cerr << "Message: " << message << "\n";
    return result_coords;
  }
}
