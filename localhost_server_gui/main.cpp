#include "pch.h"
#include "server.h"

void server_thread() {
    boost::asio::io_service io_service; 
    HTMLServer server(io_service); 

    if (!globals::is_connected.load()) {
        try {
            std::cout << "[+] Server started, local network on port: 8080." << std::endl;
            io_service.run();
            globals::is_connected.store(true, std::memory_order_relaxed);
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

int main() {
    // Previous states
    bool prev_aimbot_state = globals::settings::aimbot.load();
    bool prev_silent_aim_state = globals::settings::silent_aim.load();
    bool prev_vis_check_state = globals::settings::visibility_check.load();
    float prev_fov_value = globals::settings::fov;
    float prev_smoothness_value = globals::settings::smoothness;

    bool prev_esp_state = globals::settings::esp.load();
    bool prev_checkbox1_state = globals::settings::checkbox1.load();
    bool prev_checkbox2_state = globals::settings::checkbox2.load();

    bool prev_bunnyhop_state = globals::settings::bunnyhop.load();

    // Update the full path with the current path, what folder the .exe is executed inside
    // You can also make some other logic to find a path and create a folder and then take the path and update full_path variable.
    globals::full_path = std::filesystem::current_path().string();

    globals::server_thread = std::thread(server_thread);

    while (true) {
        // aimbot settings start
        if (globals::settings::aimbot.load() != prev_aimbot_state) {
            if (globals::settings::aimbot.load()) {
                std::cout << "  [+] Aimbot enabled." << std::endl;
            }
            else {
                std::cout << "  [+] Aimbot disabled." << std::endl;
            }
            prev_aimbot_state = globals::settings::aimbot.load();
        }

        if (globals::settings::silent_aim.load() != prev_silent_aim_state) {
            if (globals::settings::silent_aim.load()) {
                std::cout << "  [+] Silent Aim enabled." << std::endl;
            }
            else {
                std::cout << "  [+] Silent Aim disabled." << std::endl;
            }
            prev_silent_aim_state = globals::settings::silent_aim.load();
        }

        if (globals::settings::visibility_check.load() != prev_vis_check_state) {
            if (globals::settings::visibility_check.load()) {
                std::cout << "  [+] Visibility check enabled." << std::endl;
            }
            else {
                std::cout << "  [+] Visibility check disabled." << std::endl;
            }
            prev_vis_check_state = globals::settings::visibility_check.load();
        }

        if (globals::settings::fov != prev_fov_value) {
            std::cout << "  [+] FOV changed to " << globals::settings::fov << std::endl;
            prev_fov_value = globals::settings::fov;
        }

        if (globals::settings::smoothness != prev_smoothness_value) {
            std::cout << "  [+] Smoothness changed to " << globals::settings::smoothness << std::endl;
            prev_smoothness_value = globals::settings::smoothness;
        }
        // aimbot settings stop

        // esp settings start
        if (globals::settings::esp.load() != prev_esp_state) {
            if (globals::settings::esp.load()) {
                std::cout << "  [+] ESP enabled." << std::endl;
            }
            else {
                std::cout << "  [+] ESP disabled." << std::endl;
            }
            prev_esp_state = globals::settings::esp.load(); 
        }

        if (globals::settings::checkbox1.load() != prev_checkbox1_state) {
            if (globals::settings::checkbox1.load()) {
                std::cout << "  [+] Checkbox1 enabled." << std::endl;
            }
            else {
                std::cout << "  [+] Checkbox1 disabled." << std::endl;
            }
            prev_checkbox1_state = globals::settings::checkbox1.load();
        }

        if (globals::settings::checkbox2.load() != prev_checkbox2_state) {
            if (globals::settings::checkbox2.load()) {
                std::cout << "  [+] Checkbox2 enabled." << std::endl;
            }
            else {
                std::cout << "  [+] Checkbox2 disabled." << std::endl;
            }
            prev_checkbox2_state = globals::settings::checkbox2.load();
        }
        // esp settings stop

        // bunnyhop settings start
        if (globals::settings::bunnyhop.load() != prev_bunnyhop_state) {
            if (globals::settings::bunnyhop.load()) {
                std::cout << "  [+] Bunnyhop enabled." << std::endl;
            }
            else {
                std::cout << "  [+] Bunnyhop disabled." << std::endl;
            }
            prev_bunnyhop_state = globals::settings::bunnyhop.load();
        }
        // bunnyhop settings stop

        std::this_thread::sleep_for(std::chrono::milliseconds(1333));
    }

    return 0;
}
