//
// Copyright (c) 2022 Alexander Mohr
// Licensed under the terms of the MIT License
//

#include <Arduino.h>
#include <esp-gui/Configuration.hpp>
#include <esp-gui/UpdateManager.hpp>
#include <esp-gui/WebServer.hpp>
#include <esp-gui/WifiManager.hpp>
#include <yal/appender/ArduinoSerial.hpp>

yal::Logger m_logger;
yal::appender::ArduinoSerial<HardwareSerial> m_serialAppender(&m_logger, &Serial, true);

esp_gui::Configuration m_config;
esp_gui::WebServer m_server(80, "demo", m_config);
esp_gui::WifiManager m_wifiMgr(m_config, m_server);

esp_gui::UpdateManager m_updateManager(m_server);


void setup() {
  m_serialAppender.begin(115200);
  m_logger.log(yal::Level::INFO, "Running setup");
  yal::Logger::setLevel(yal::Level::TRACE);
  m_config.setup();

  m_server.setPageTitle("Open-Power");
  m_wifiMgr.setup(false);
  m_updateManager.setup();
  m_server.setup(m_config.value<String>("wifi_hostname"));
}

void loop() {
  m_wifiMgr.loop();
  delay(1000);
}
