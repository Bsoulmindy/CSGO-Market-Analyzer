#include "internet.hpp"
#include <string>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>

#include <nlohmann/json.hpp>

#include "../class/Weapon_Skin_Wear.hpp"
#include "database.hpp"

using namespace boost::beast;
using namespace boost::asio;
using json = nlohmann::json;
using tcp = boost::asio::ip::tcp;    // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;    // from <boost/asio/ssl.hpp>
namespace http = boost::beast::http; // from <boost/beast/http.hpp>
namespace beast = boost::beast;

/**
 * @brief Get HTML page
 * @param host example "www.google.com"
 * @param path example "/"
 * @param port example "443"
 */
http::response<http::string_body> get_html_page(const std::string &host, const std::string &path, const std::string &port)
{
    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::sslv23_client};

    io_service svc;

    ssl::stream<ip::tcp::socket> ssocket = {svc, ctx};

    // Set SNI Hostname (many hosts need this to handshake successfully)
    if (!SSL_set_tlsext_host_name(ssocket.native_handle(), host.c_str()))
    {
        boost::system::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
        throw boost::system::system_error{ec};
    }
    ip::tcp::resolver resolver(svc);
    auto it = resolver.resolve(host, port);
    connect(ssocket.lowest_layer(), it);
    ssocket.handshake(ssl::stream_base::handshake_type::client);
    http::request<http::string_body> req{http::verb::get, path, 11};
    req.set(http::field::host, host);
    http::write(ssocket, req);
    http::response<http::string_body> res;
    flat_buffer buffer;
    http::read(ssocket, buffer, res);

    return res;
}

void get_offers(Weapon_Skin_Wear &wear)
{
    for (Wear_Info const &info : get_profitation_of_wear(wear))
    {
        const std::string host = "steamcommunity.com";
        std::stringstream ss;
        ss << "/market/listings/730/" << wear.get_link() << "/render?start=0&count=100&currency=1&language=english";
        const std::string path = ss.str();
        const std::string port = "443";

        json root = json::parse(get_html_page(host, path, port).body());

        if (root.at("success") == false)
            throw std::runtime_error("Error while getting offers");

        for (auto it = root.at("listinginfo").rbegin(); it != root.at("listinginfo").rend(); it++)
        {
            float offer_price = it->at("converted_price_per_unit").get<int>() / 100.0f;
            if (offer_price > info.get_actual_price())
                continue;
            std::string offer_id = it.key();
            long offer_long_id = std::stol(offer_id);
            std::string offer_inspect_id = it->at("asset").at("id").get<std::string>();

            const std::string host2 = "api.csgofloat.com";
            std::stringstream ss2;
            ss2 << "/?m=" << offer_id << "&a=" << offer_inspect_id << "&d=123";
            const std::string path2 = ss2.str();
            json j = json::parse(get_html_page(host2, path2, port).body());

            float offer_wear = j.at("iteminfo").at("floatvalue").get<float>();
            if (offer_wear < info.get_interval().get_min() || offer_wear > info.get_interval().get_max())
            {
                continue;
            }
            Weapon_Skin_Offer offer = Weapon_Skin_Offer(offer_long_id, offer_price / 100, offer_wear);
            wear.add_offer(offer);
        }
    }
}

void get_actual_price(Weapon_Skin_Wear &wear)
{
    const std::string host = "steamcommunity.com";
    std::stringstream ss;
    ss << "/market/listings/730/" << wear.get_link() << "/render?start=0&count=100&currency=1&language=english";
    const std::string path = ss.str();
    const std::string port = "443";

    json root = json::parse(get_html_page(host, path, port).body());
    if (root.at("success") == false)
        throw std::runtime_error("Error while getting offers");

    int actual_price = 0;

    for (auto it = root.at("listinginfo").begin(); it != root.at("listinginfo").end(); it++)
    {
        int price = it->at("converted_price_per_unit").get<int>();
        if (actual_price > price || actual_price == 0)
            actual_price = price;
    }

    wear.set_actual_price(actual_price);
}