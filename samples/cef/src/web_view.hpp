#pragma once

#include <iostream>
#include <memory>

#include <include/cef_app.h>
#include <include/cef_client.h>

#include <texture2d.hpp>

class WebView : public CefClient, public CefLifeSpanHandler, public CefRenderHandler {
 public:
  WebView(unsigned int width, unsigned int height);

  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override;

  virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;

  virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                       PaintElementType type,
                       const RectList& dirtyRects,
                       const void* buffer,
                       int width,
                       int height) override;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  void resize(unsigned int width, unsigned int height);
  void bind_texture() const;

 private:
  unsigned int m_width = 1024;
  unsigned int m_height = 1024;

  std::unique_ptr<gl::Texture2d> m_texture;

  IMPLEMENT_REFCOUNTING(WebView);
  DISALLOW_COPY_AND_ASSIGN(WebView);
};
