//
// Example that uses mocap mavlink channel to send the local position estimation
// In this example, the program will send a constant position esitmation.
//

#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/hil_gps/hil_gps.h>

using namespace mavsdk;

void usage(const std::string& bin_name)
{
    std::cerr << "Usage : " << bin_name << " <connection_url>\n"
              << "Connection URL format should be :\n"
              << " For TCP : tcp://[server_host][:server_port]\n"
              << " For UDP : udp://[bind_host][:bind_port]\n"
              << " For Serial : serial:///path/to/serial/dev[:baudrate]\n"
              << "For example, to connect to the simulator use URL: udp://:14540\n";
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    std::cout << "Connecting to " << argv[1] << std::endl;

    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::CompanionComputer}};
    ConnectionResult connection_result = mavsdk.add_any_connection(argv[1]);

    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    } else {
        std::cout << "Connection succeed. \n";
    }


    auto system = mavsdk.first_autopilot(3.0);
    if (!system) {
        std::cerr << "Timed out waiting for system\n";
        return 1;
    }

    // find all th systems
    auto systems = mavsdk.systems();
    for (auto system : mavsdk.systems()) {
        std::cout << "Found system with MAVLink system ID: " << static_cast<int>(system->get_system_id())
                << ", connected: " << (system->is_connected() ? "yes" : "no")
                << ", has autopilot: " << (system->has_autopilot() ? "yes" : "no") << '\n';
    }

    auto hilgps = HilGps{system.value()};
  
    // constantly sending position estimation
    while (true) {
      HilGps::HilGpsInfo data;
      data.time_usec = 0;
      data.fix_type = 3;
      data.lat = 0.0;
      data.lon = 0.0;
      data.alt = 0.0;
      data.eph = std::numeric_limits<uint16_t>::max();
      data.epv = std::numeric_limits<uint16_t>::max();
      data.vel = std::numeric_limits<uint16_t>::max();
      data.vn = 0.0f;
      data.ve = 0.0f;
      data.vd = 0.0f;
      data.cog = std::numeric_limits<uint16_t>::max();
      data.satellites_visible = 12;
      data.id = 0;
      data.yaw = 0;
      hilgps.set_hil_gps(data);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;

}