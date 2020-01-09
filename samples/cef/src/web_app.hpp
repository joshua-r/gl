#include <include/cef_app.h>

class WebApp : public CefApp, public CefBrowserProcessHandler {
 public:
  WebApp();

  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

  virtual void OnContextInitialized() override;

 private:
  IMPLEMENT_REFCOUNTING(WebApp);
};
