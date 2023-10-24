#ifndef HTML_SERVER_H
#define HTML_SERVER_H
// Original author = REVRBE
// Github = https://github.com/REVRBE
// License = See end of file

#include "pch.h"

namespace globals {
    std::string full_path;

    std::atomic<bool> is_connected{ false };
    std::thread server_thread;

    namespace settings {
        std::atomic<bool> aimbot{ false };
        std::atomic<bool> silent_aim{ false };
        std::atomic<bool> visibility_check{ false };
        float fov;
        float smoothness;

        std::atomic<bool> esp{ false };
        std::atomic<bool> checkbox1{ false };
        std::atomic<bool> checkbox2{ false };
        float slider1;
        float slider2;

        std::atomic<bool> bunnyhop{ false };
    }
}

class HTMLServer {
public:
    HTMLServer(boost::asio::io_context& io_context)
        : acceptor_(io_context, tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            do_accept();
            });
    }

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket) : socket_(std::move(socket)) {}

        void start() { do_read(); }

    private:
        boost::asio::streambuf data_;

        void do_read() {
            auto self(shared_from_this());
            boost::asio::async_read_until(socket_, data_, "\r\n\r\n",
                [this, self](boost::system::error_code ec, std::size_t length) {
                    if (!ec) {
                        std::istream stream(&data_);
                        std::string request;
                        std::getline(stream, request); 

                        // Sanitize and process HTTP request.
                        sanitizeAndProcessRequest(request);
                        data_.consume(length); 
                        do_write(length);
                    }
                });
        }

        void sanitizeAndProcessRequest(const std::string& request) {
            // Sanitize the request here

            if (request.find("GET /?aimbot=on ") != std::string::npos) {
                // Process the request to enable Aimbot
                globals::settings::aimbot.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?aimbot=off ") != std::string::npos) {
                // Process the request to disable Aimbot
                globals::settings::aimbot.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?silent_aim=on ") != std::string::npos) {
                // Process the request to enable Silent Aim
                globals::settings::silent_aim.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?silent_aim=off ") != std::string::npos) {
                // Process the request to disable Silent Aim
                globals::settings::silent_aim.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?visibility_check=on ") != std::string::npos) {
                // Process the request to enable Visibility Check
                globals::settings::visibility_check.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?visibility_check=off ") != std::string::npos) {
                // Process the request to disable Visibility Check
                globals::settings::visibility_check.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?esp=on ") != std::string::npos) {
                // Process the request to enable ESP
                globals::settings::esp.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?esp=off ") != std::string::npos) {
                // Process the request to disable ESP
                globals::settings::esp.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?bunnyhop=on ") != std::string::npos) {
                // Process the request to enable ESP
                globals::settings::bunnyhop.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?bunnyhop=off ") != std::string::npos) {
                // Process the request to disable ESP
                globals::settings::bunnyhop.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?checkbox1=on ") != std::string::npos) {
                // Process the request to enable Checkbox1
                globals::settings::checkbox1.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?checkbox1=off ") != std::string::npos) {
                // Process the request to disable Checkbox1
                globals::settings::checkbox1.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?checkbox2=on ") != std::string::npos) {
                // Process the request to enable Checkbox2
                globals::settings::checkbox2.store(true, std::memory_order_relaxed);
            }
            else if (request.find("GET /?checkbox2=off ") != std::string::npos) {
                // Process the request to disable Checkbox2
                globals::settings::checkbox2.store(false, std::memory_order_relaxed);
            }
            else if (request.find("GET /?fov=") != std::string::npos) {
                size_t pos = request.find("GET /?fov=");
                std::string fovRequest = request.substr(pos + 10);

                size_t httpPos = fovRequest.find(" HTTP/1.1");
                if (httpPos != std::string::npos) {
                    fovRequest = fovRequest.substr(0, httpPos);

                    try {
                        float fov = std::stof(fovRequest);

                        fov = std::min(std::max(fov, 1.0f), 90.0f);

                        globals::settings::fov = fov;
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "  [-] Invalid FOV value: " << fovRequest << std::endl;
                    }
                }
            }
            else if (request.find("GET /?smoothness=") != std::string::npos) {
                size_t pos = request.find("GET /?smoothness=");
                std::string fovRequest = request.substr(pos + 17);

                size_t httpPos = fovRequest.find(" HTTP/1.1");
                if (httpPos != std::string::npos) {
                    fovRequest = fovRequest.substr(0, httpPos);

                    try {
                        float smoothness = std::stof(fovRequest);

                        smoothness = std::min(std::max(smoothness, 1.0f), 20.0f);

                        globals::settings::smoothness = smoothness;
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "  [-] Invalid Smoothness value: " << fovRequest << std::endl;
                    }
                }
            }

            // Add more requests if needed
        }

        void do_write(std::size_t length) {
            auto self(shared_from_this());

            std::string html_content = load_file(globals::full_path + "\\index.html");
            std::string css_content = load_file(globals::full_path + "\\styles.css");
            std::string js_content = load_file(globals::full_path + "\\script.js");

            // Build the HTTP response with HTML, CSS, and JavaScript included
            std::string response = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n\r\n" + html_content + "\n";

            // Include CSS
            response += "<style>" + css_content + "</style>\n";

            // Include JavaScript
            response += "<script>" + js_content + "</script>\n";

            boost::asio::async_write(socket_, boost::asio::buffer(response),
                [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                        socket_.close();
                    }
                });
        }

        std::string load_file(const std::string& filepath) {
            std::ifstream file(filepath);
            if (file.is_open()) {
                std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
                return content;
            }
            return "";
        }

        tcp::socket socket_;
    };

    tcp::acceptor acceptor_;
};

#endif

/*
MIT License

Copyright (c) 2023 REVRBE

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
