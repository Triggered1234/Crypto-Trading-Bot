#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp> // Include SSL components

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "App_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }

    // Step 1: Initialize SSL context and socket
    net::io_context ioc;
    ssl::context ctx(ssl::context::tlsv12_client);
    ctx.set_default_verify_paths();

    tcp::resolver resolver(ioc);
    tcp::socket socket(ioc); // Using tcp::socket instead of beast::tcp_stream

    // Step 2: Resolve and connect
    auto const results = resolver.resolve("api.binance.com", "https");
    net::connect(socket, results.begin(), results.end());

    // Step 3: Perform SSL handshake
    ssl::stream<tcp::socket&> stream(socket, ctx);
    stream.handshake(ssl::stream_base::client);

    // Step 4: Prepare and send HTTP request
    http::request<http::string_body> req(http::verb::get, "/api/v3/ticker/price?symbol=BTCUSDT", 11);
    req.set(http::field::host, "api.binance.com");
    req.set(http::field::user_agent, "Boost Beast Example");
    http::write(stream, req);

    // Step 5: Receive and print HTTP response
    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(stream, buffer, res);
    std::cout << res << std::endl;

    // Step 6: Shutdown SSL stream
    beast::error_code ec;
    stream.shutdown(ec);
    if (ec && ec != beast::errc::not_connected)
    {
        std::cerr << "shutdown: " << ec.message() << std::endl;
    }

    MainWindow w;
    w.show();
    // If we get here, the request was successful

    return a.exec();
}
