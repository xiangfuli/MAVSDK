#include "hil_gps_impl.h"

namespace mavsdk {


HilGpsImpl::HilGpsImpl(System& system) : PluginImplBase(system)
{
    _system_impl->register_plugin(this);
}

HilGpsImpl::HilGpsImpl(std::shared_ptr<System> system) : PluginImplBase(std::move(system))
{
    _system_impl->register_plugin(this);
}


HilGpsImpl::~HilGpsImpl()
{

    _system_impl->unregister_plugin(this);

}

HilGps::Result HilGpsImpl::set_hil_gps(HilGps::HilGpsInfo hil_gps_info) {
    if (!_system_impl->is_connected()) {
        return HilGps::Result::NoSystem;
    }

    return send_hil_gps(hil_gps_info);
}

void HilGpsImpl::init() {}

void HilGpsImpl::deinit() {}


void HilGpsImpl::enable() {}

void HilGpsImpl::disable() {}



HilGps::Result HilGpsImpl::send_hil_gps(HilGps::HilGpsInfo hil_gps_info)
{
    const uint64_t autopilot_time_usec =
        (!hil_gps_info.time_usec) ?
            std::chrono::duration_cast<std::chrono::microseconds>(
                _system_impl->get_autopilot_time().now().time_since_epoch())
                .count() :
            std::chrono::duration_cast<std::chrono::microseconds>(
                _system_impl->get_autopilot_time()
                    .time_in(SystemTimePoint(
                        std::chrono::microseconds(hil_gps_info.time_usec)))
                    .time_since_epoch())
                .count();

    return _system_impl->queue_message([&](MavlinkAddress mavlink_address, uint8_t channel) {
        mavlink_message_t message;
        mavlink_msg_hil_gps_pack_chan(
            mavlink_address.system_id,
            mavlink_address.component_id,
            channel,
            &message,
            autopilot_time_usec,
            hil_gps_info.fix_type,
            hil_gps_info.lat,
            hil_gps_info.lon,
            hil_gps_info.alt,
            hil_gps_info.eph,
            hil_gps_info.epv,
            hil_gps_info.vel,
            hil_gps_info.vn,
            hil_gps_info.ve,
            hil_gps_info.vd,
            hil_gps_info.cog,
            hil_gps_info.satellites_visible,
            hil_gps_info.id,
            hil_gps_info.yaw); // FIXME: reset_counter not set
        return message;
    }) ?
               HilGps::Result::Success :
               HilGps::Result::ConnectionError;
}



} // namespace mavsdk