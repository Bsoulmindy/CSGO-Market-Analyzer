#ifndef INTERNET_HPP_INCLUDED
#define INTERNET_HPP_INCLUDED
#include <boost/beast.hpp>
#include "../class/Weapon_Skin_Wear.hpp"

boost::beast::http::response<boost::beast::http::string_body> get_html_page(const std::string &host, const std::string &path, const std::string &port);
void get_offers(Weapon_Skin_Wear &wear);
void get_actual_price(Weapon_Skin_Wear &wear);

#endif // INTERNET_HPP_INCLUDED