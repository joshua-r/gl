#include <web_app.hpp>

WebApp::WebApp() {}

CefRefPtr<CefBrowserProcessHandler> WebApp::GetBrowserProcessHandler() {
  return this;
}

void WebApp::OnContextInitialized() {}
