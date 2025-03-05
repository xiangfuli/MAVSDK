#pragma once

#include "plugins/hil_gps/hil_gps.h"

#include "plugin_impl_base.h"


namespace mavsdk {


class HilGpsImpl : public PluginImplBase {
public:
    explicit HilGpsImpl(System& system);
    explicit HilGpsImpl(std::shared_ptr<System> system);

    ~HilGpsImpl() override;

    void init() override;
    void deinit() override;


    void enable() override;
    void disable() override;


    HilGps::Result set_hil_gps(HilGps::HilGpsInfo hil_gps_info);

private:
    HilGps::Result send_hil_gps(HilGps::HilGpsInfo hil_gps_info);
};

} // namespace mavsdk